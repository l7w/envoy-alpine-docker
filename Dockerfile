# Build stage for Envoy and eBPF tests
FROM alpine:3.20 AS build
RUN apk add --no-cache build-base cmake git libbpf-dev libcmocka-dev libseccomp-dev \
    && git clone https://github.com/envoyproxy/envoy \
    && cd envoy && bazel build //source/exe:envoy-static \
    && git clone https://github.com/libbpf/libbpf \
    && cd libbpf/src && make && make install

# Build eBPF test suite
COPY ebpf_security_tests.c /build/
RUN gcc -o /build/ebpf_tests /build/ebpf_security_tests.c -lcmocka -lbpf -lseccomp

# Runtime stage
FROM alpine:3.20
RUN apk add --no-cache libstdc++ libbpf libcmocka libseccomp \
    && addgroup -S envoy && adduser -S -G envoy envoy \
    && rm -rf /var/cache/apk/* /tmp/* \
    && find / -xdev -type d -perm +0002 -exec chmod o-w {} + \
    && find / -xdev -type f -perm +0002 -exec chmod o-w {} + \
    && sed -i -r '/^(envoy|root)/!d' /etc/group \
    && sed -i -r '/^(envoy|root)/!d' /etc/passwd \
    && sed -i -r '/^envoy:/! s#^(.*):[^:]*$#\1:/sbin/nologin#' /etc/passwd \
    && find /bin /sbin /usr -xdev \( -name su -o -name chmod -o -name chown \) -delete \
    && find /bin /etc /lib /sbin /usr -xdev -type d -exec chown root:root {} \; -exec chmod 0755 {} \;

# Copy Envoy binary and config
COPY --from=build /envoy/bazel-bin/source/exe/envoy-static /usr/local/bin/envoy
COPY envoy.yaml /etc/envoy/envoy.yaml
COPY --from=build /build/ebpf_tests /usr/local/bin/ebpf_tests

# Set permissions
RUN chown -R envoy:envoy /usr/local/bin/envoy /etc/envoy \
    && chmod 0755 /usr/local/bin/ebpf_tests

# Run as non-root
USER envoy
EXPOSE 10000

# Default command runs Envoy
CMD ["/usr/local/bin/envoy", "-c", "/etc/envoy/envoy.yaml"]
