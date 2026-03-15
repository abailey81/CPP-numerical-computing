# Security Policy

## Supported Versions

| Version | Supported |
|:--------|:---------:|
| Latest on `main` | Yes |
| Older commits | No |

## Scope

This is a numerical computing framework for educational and research purposes. It processes local data files and does not handle user authentication, network communication, or sensitive data. Security concerns are primarily related to:

- **Buffer overflows** in data parsing routines
- **Numerical instability** that could produce unsafe outputs if used in safety-critical applications
- **Build system vulnerabilities** in CMake configurations or CI workflows

## Reporting a Vulnerability

If you discover a security issue, please report it responsibly:

1. **Do not** open a public GitHub issue for security vulnerabilities.
2. **Email** the maintainer directly with a description of the vulnerability, steps to reproduce, and any suggested fixes.
3. You will receive an acknowledgement within 72 hours.
4. A fix will be developed and released as soon as practical.

## Best Practices

When using this framework:

- Validate all input data files before processing.
- Do not use raw output from numerical simulations in safety-critical systems without independent verification.
- Keep your compiler and build tools up to date.
