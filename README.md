```
                                                                                              
                                                                                              
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##########################%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#*++++++++++++++++++++++*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#*++++++++=---++++++++++*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#*-----------------=++++*#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%############################%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%#***++++++++++++++++++++++++**+############%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%+++===++*%@@@%%%@@@%%%@@@%%#*##############%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%++++++***#%%%%%%%%%%%%%%%%%#################%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%#%%%@@@@@@@@@@@@@@@@@@@@@@@@@%@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%#%%%@@@@%%%###########%%%%@@@%@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%#%%%@@@%%##-.::::::-.-*#%%%@@#@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%###%%%@@@%##*:..:.::.::.+##%%@@#@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%##%%%%%#%%%@@@%##*=.-: :  : .+##%%@@#@@@@@@%%%%@@%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%%%%%%%#%%%@@@%%#*..:. :..:. +##%%@@*@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%   
   %%%%%%%%%%%%%%%%%%%%%#######%%%@@@%%%#*+++++++++*##%%%@@*@@@%@@@@%@@@%%###%%%%%%%%%%%%%%   
   %%%%%%######################%%%@@@@%%%%%#######%%%%%@@@%*@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%   
   ############################%%%@@@@@@@@@@@@@@@@@@@@@@@@#*@@%@@@%%@@@@%%@@@@@@@@@@@@@@@@@   
   ###################*########%%%%#***+++++++++++++++*****+@@@@@@**%@@@%@@@@@@@@@@@@@@@@@@   
   +======--------------::::::+%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#%*@@@%%@@@@@%%%%%%%%%%%%   
   --::::::::::::...:.........+%%%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%%%%%%   
   ...........................-###%%%%%%#%%%%%%%%%%#%%%%%%%%%%%%%%%####%#%%%%%%%%%%#%######   
   ...........................+##**---:-.-:-:----:-:-.-:-:-:-:+-##*+##*###%%%*+===++++=====   
   ........:----+###-.........*###=.:.........................=.*###%%%####=::::----:::::::   
   ...........................###*-.:....:................:.:.=.-%##%@@@%###-:........:::::   
   ................-.........=####**+++=+-==============+#+=*++++%##%%%%####*-::...........   
   ............:-=:..........=#*###########################################*#+-::..........   
   ..........................*###############################################%+-::.........   
   ...................:+=:.....*#%%%%%@@@@%@@@@@@%%%@@@@%@@@@@@@@@@@@@@@@%%%%%#+-::........   
   ............................-+******************************************++++=-::........   
   ..............--:.......................................................................   
   ...............:.................::--...................................................   
   ........................................................................................   
   ........................-...............................................................   
   ........................................................................................   
   ........................................................................................   
   ........................................................................................   
   ........................................................................................   
   ...............................................................................:...:::..   
   .......................................................................:::::::::::::::::   
                                                                                              
```

> WORK IN PROGRESS - Mitigating OWASP GenAI LLM Top 10 Vulnerabilities
```
~/backend/envoy-alpine-docker main* ❯ chmod -R 00775 {.,.*}                                                                                  16:27:24
~/backend/envoy-alpine-docker main* ❯ ls -la                                                                                                 16:27:27
total 56
drwxrwxr-x@ 11 x  staff   352 Apr 19 15:32 .
drwxr-xr-x@  3 x  staff    96 Apr 19 15:13 ..
drwxrwxr-x@ 13 x  staff   416 Apr 19 15:45 .git
drwxrwxr-x@  3 x  staff    96 Apr 19 15:15 .github
-rwxrwxr-x@  1 x  staff    10 Apr 19 15:21 .gitignore
drwxrwxr-x@  3 x  staff    96 Apr 19 15:22 builder
-rwxrwxr-x@  1 x  staff  1661 Apr 19 15:14 Dockerfile
-rwxrwxr-x@  1 x  staff  4094 Apr 19 15:32 ebpf_security_tests.c
-rwxrwxr-x@  1 x  staff  1326 Apr 19 15:14 envoy.yml
-rwxrwxr-x@  1 x  staff  1070 Apr 19 15:13 LICENSE
-rwxrwxr-x@  1 x  staff  4706 Apr 19 16:24 README.md
~/backend/envoy-alpine-docker main* ❯

```
# envoy-alpine-docker

```
┌──────────────────────────────────────────────────────────────┐
│          Envoy Proxy on Alpine Linux Docker Image             │
└──────────────────────────────────────────────────────────────┘
```

This project provides a lightweight, secure Envoy proxy running in an Alpine Linux-based Docker container. Envoy is configured for high-performance proxying, suitable for service mesh, API gateways, or load balancing. This README includes a security checklist to harden the deployment and a severity matrix for OWASP Top 10 for Large Language Model (LLM) Applications 2025, addressing potential risks if Envoy routes traffic to LLM services.

## Table of Contents
- [OWASP Top 10 LLM 2025 Severity Matrix](#owasp-top-10-llm-2025-severity-matrix)
- [Security Checklist](#security-checklist)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## OWASP Top 10 LLM 2025 Severity Matrix

```
┌──────────────────────────────────────────────────────────────┐
│        OWASP Top 10 for LLM Applications 2025 Matrix         │
└──────────────────────────────────────────────────────────────┘
```
```
The following matrix outlines the OWASP Top 10 vulnerabilities for LLM applications, with severity levels based on impact, exploitability, and prevalence. This is relevant if the Envoy proxy routes traffic to LLM-based services.

| Rank | Vulnerability                    | Description                                                                 | Severity | Rationale                                                                 |
|------|----------------------------------|-----------------------------------------------------------------------------|----------|---------------------------------------------------------------------------|
| LLM01 | Prompt Injection                | Attackers manipulate prompts to alter model behavior or execute unauthorized actions.   | Critical | High impact: unauthorized access, data exposure. Easy to exploit via crafted inputs. |
| LLM02 | Sensitive Information Disclosure | LLMs expose sensitive data (e.g., PII, algorithms) through outputs.         | Critical  | Severe risk of privacy violations, IP theft. Common without data sanitization.   |
| LLM03 | Supply Chain Vulnerabilities    | Compromised training data or components lead to biased outputs or breaches.  | High      | Impacts model integrity. Moderately complex but prevalent due to external data.  |
| LLM04 | Insecure Output Handling        | Unvalidated LLM outputs risk code execution (e.g., XSS, SQL injection).      | High      | High impact in sensitive contexts. Common without output encoding.  |
| LLM05 | Excessive Agency                | Over-autonomous LLMs perform unintended actions due to excessive permissions | High    | Critical in agentic setups. Exploitation depends on config but severe impact. |
| LLM06 | Training Data Poisoning         | Malicious data in training compromises model performance or ethics.          | High      | Long-term impact on reliability. Complex but devastating if successful.    |
| LLM07 | System Prompt Leakage           | Exposure of sensitive system prompts reveals configurations.                 | Medium    | Enables targeted attacks. Less prevalent but significant in poor setups.   |
| LLM08 | Vector and Embedding Weaknesses | Exploits in vector storage affect RAG-based applications.                    | Medium    | Emerging risk in RAG systems. Moderate impact, increasing prevalence.      |
| LLM09 | Misinformation                  | LLMs generate false information, impacting trust and decisions.              | Medium    | Broad societal impact. Straightforward but context-dependent exploitation. |
| LLM10 | Unbounded Consumption           | Uncontrolled LLM resource usage causes disruptions or high costs.            | Medium    | Impacts availability, costs. Easy to exploit via resource-intensive inputs. |
````
### Notes
- **Severity Definitions**:
  - **Critical**: Immediate, severe impact (e.g., data breaches); easy to exploit; highly prevalent.
  - **High**: Significant impact; moderately complex; common.
  - **Medium**: Moderate impact; specific conditions; emerging.
  - **Low**: Limited impact; difficult; rare.
- Source: [OWASP Top 10 for LLM Applications 2025](https://owasp.org/www-project-top-10-for-large-language-model-applications/).
- Prioritize mitigating Prompt Injection and Sensitive Information Disclosure for LLM traffic.

## Security Checklist

```
┌──────────────────────────────────────────────────────────────┐
│            Security Checklist for envoy-alpine-docker         │
└──────────────────────────────────────────────────────────────┘
```

Use this checklist to secure the `envoy-alpine-docker` deployment, addressing container, network, and LLM-related risks.

### 1. Docker Image Security
- [ ] **Use Minimal Base Image**: Use `alpine:3.20` to minimize attack surface. Source from `docker.io/alpine`.
- [ ] **Pin Image Version**: Specify exact version (e.g., `alpine:3.20`) to avoid untested updates.
- [ ] **Scan for Vulnerabilities**: Run `trivy image envoy-alpine-docker` or Docker Scout to detect CVEs.
- [ ] **Remove Unnecessary Packages**: Ensure only essential packages are installed (e.g., `envoy` binary).

### 2. Envoy Configuration Security
- [ ] **Enable TLS**: Configure Envoy to use TLS for all traffic (e.g., `transport_socket` with TLS certs).
- [ ] **Validate Inputs**: If routing to LLMs, filter inputs to mitigate Prompt Injection (LLM01). Use Envoy's `ext_proc` filter for validation.
- [ ] **Sanitize Outputs**: Encode LLM outputs to prevent Insecure Output Handling (LLM04) risks like XSS.
- [ ] **Restrict Permissions**: Limit Envoy's access to only necessary endpoints, reducing Excessive Agency (LLM05) risks.

### 3. Container Security
- [ ] **Run as Non-Root**: Use `USER nobody` in Dockerfile to reduce privilege escalation risks.
- [ ] **Read-Only Filesystem**: Set `--read-only` in Docker run command for immutable containers.
- [ ] **Limit Resources**: Use `--memory` and `--cpus` to prevent Unbounded Consumption (LLM10) attacks.
- [ ] **Drop Capabilities**: Add `--cap-drop=ALL` and only allow necessary capabilities (e.g., `NET_BIND_SERVICE`).

### 4. Network Security
- [ ] **Restrict Ports**: Expose only necessary ports (e.g., `8080`, `8443`) in Dockerfile and Docker run.
- [ ] **Use Network Policies**: In Kubernetes, apply network policies to limit ingress/egress traffic.
- [ ] **Enable Rate Limiting**: Configure Envoy's `rate_limit` filter to mitigate DoS or Unbounded Consumption (LLM10).

### 5. Monitoring and Logging
- [ ] **Enable Access Logs**: Configure Envoy access logs to monitor for suspicious activity (e.g., prompt injection attempts).
- [ ] **Audit Logs Regularly**: Check for signs of Sensitive Information Disclosure (LLM02) in logs.
- [ ] **Use SIEM**: Integrate with a SIEM tool for real-time threat detection.

### 6. Supply Chain Security
- [ ] **Verify Envoy Binary**: Download Envoy from official releases (`getenvoy.io`) and verify checksums.
- [ ] **Secure Build Pipeline**: Use signed commits and trusted CI/CD to prevent Supply Chain Vulnerabilities (LLM03).
- [ ] **Update Regularly**: Monitor for Envoy and Alpine updates to patch known vulnerabilities.

## Installation

```bash
# Build the Docker image
docker build -t envoy-alpine-docker .

# Run the container
docker run -d -p 8080:8080 --read-only --cap-drop=ALL --cap-add=NET_BIND_SERVICE envoy-alpine-docker
```

## Usage

1. Configure Envoy via `envoy.yaml` in the project root.
2. Mount the configuration file into the container:
   ```bash
   docker run -v $(pwd)/envoy.yaml:/etc/envoy/envoy.yaml envoy-alpine-docker
   ```
3. Test the proxy:
   ```bash
   curl http://localhost:8080
   ```

## Contributing

Contributions are welcome! Please:
1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/xyz`).
3. Commit changes (`git commit -m 'Add feature xyz'`).
4. Push to the branch (`git push origin feature/xyz`).
5. Open a pull request.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

```
┌──────────────────────────────────────────────────────────────┐
│               Maintained by [Your Name/Org]                   │
└──────────────────────────────────────────────────────────────┘
```
