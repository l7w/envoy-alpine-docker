#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/bpf.h>
#include <bpf/libbpf.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <errno.h>
#include <seccomp.h>
#include <cmocka.h>

// Helper to call bpf() syscall
static int bpf(enum bpf_cmd cmd, union bpf_attr *attr) {
    return syscall(__NR_bpf, cmd, attr, sizeof(*attr));
}

// Test 1: Unprivileged eBPF program loading
static void test_unprivileged_bpf(void **state) {
    union bpf_attr attr = {0};
    attr.prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
    attr.insns = (uint64_t)calloc(8, sizeof(uint64_t));
    attr.insn_cnt = 1;
    attr.license = (uint64_t)"GPL";

    // Drop privileges
    if (setuid(1000) != 0) {
        fail_msg("Failed to drop privileges");
    }

    int ret = bpf(BPF_PROG_LOAD, &attr);
    assert_int_equal(ret, -1);
    assert_int_equal(errno, EPERM);

    free((void *)attr.insns);
}

// Test 2: eBPF in kernel lockdown mode
static void test_lockdown_bpf(void **state) {
    // Simulate lockdown by checking /sys/kernel/security/lockdown
    FILE *fp = fopen("/sys/kernel/security/lockdown", "r");
    if (fp) {
        char mode[16];
        fgets(mode, sizeof(mode), fp);
        fclose(fp);
        if (strstr(mode, "confidentiality")) {
            union bpf_attr attr = {0};
            attr.prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
            attr.insns = (uint64_t)calloc(8, sizeof(uint64_t));
            attr.insn_cnt = 1;
            attr.license = (uint64_t)"GPL";

            int ret = bpf(BPF_PROG_LOAD, &attr);
            assert_int_equal(ret, -1);
            assert_int_equal(errno, EPERM);

            free((void *)attr.insns);
        } else {
            skip("Kernel lockdown not in confidentiality mode");
        }
    } else {
        skip("Lockdown status not available");
    }
}

// Test 3: Seccomp filter for bpf() syscall
static void test_seccomp_bpf(void **state) {
    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_ALLOW);
    assert_non_null(ctx);

    // Block bpf() syscall
    int ret = seccomp_rule_add(ctx, SCMP_ACT_ERRNO(EPERM), SCMP_SYS(bpf), 0);
    assert_int_equal(ret, 0);

    ret = seccomp_load(ctx);
    assert_int_equal(ret, 0);

    union bpf_attr attr = {0};
    attr.prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
    attr.insns = (uint64_t)calloc(8, sizeof(uint64_t));
    attr.insn_cnt = 1;
    attr.license = (uint64_t)"GPL";

    ret = bpf(BPF_PROG_LOAD, &attr);
    assert_int_equal(ret, -1);
    assert_int_equal(errno, EPERM);

    free((void *)attr.insns);
    seccomp_release(ctx);
}

// Test 4: Resource limits on eBPF program
static void test_bpf_resource_limits(void **state) {
    union bpf_attr attr = {0};
    attr.prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
    attr.insns = (uint64_t)calloc(10000, sizeof(uint64_t)); // Large program
    attr.insn_cnt = 10000; // Exceed typical limit
    attr.license = (uint64_t)"GPL";

    int ret = bpf(BPF_PROG_LOAD, &attr);
    assert_int_equal(ret, -1);
    assert_true(errno == E2BIG || errno == EINVAL);

    free((void *)attr.insns);
}

// Test 5: Memory safety (simplified, requires kernel verifier)
static void test_bpf_memory_safety(void **state) {
    // Load a malicious eBPF program attempting invalid memory access
    // This is a simplified test; actual memory safety is enforced by kernel verifier
    union bpf_attr attr = {0};
    attr.prog_type = BPF_PROG_TYPE_SOCKET_FILTER;
    uint64_t *insns = calloc(8, sizeof(uint64_t));
    insns[0] = 0xdeadbeef; // Invalid instruction
    attr.insns = (uint64_t)insns;
    attr.insn_cnt = 1;
    attr.license = (uint64_t)"GPL";

    int ret = bpf(BPF_PROG_LOAD, &attr);
    assert_int_equal(ret, -1);
    assert_int_equal(errno, EINVAL);

    free(insns);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_unprivileged_bpf),
        cmocka_unit_test(test_lockdown_bpf),
        cmocka_unit_test(test_seccomp_bpf),
        cmocka_unit_test(test_bpf_resource_limits),
        cmocka_unit_test(test_bpf_memory_safety),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
