# Contributing

Thank you for your interest in contributing to the Numerical Computing Framework. This document provides guidelines and instructions for contributing.

## Prerequisites

- **C++17** compatible compiler (GCC 7+, Clang 5+, or MSVC 19.14+)
- **CMake** 3.16 or higher
- Git

## Getting Started

1. **Fork** the repository on GitHub.
2. **Clone** your fork locally:
   ```bash
   git clone https://github.com/<your-username>/CPP-numerical-computing.git
   cd CPP-numerical-computing
   ```
3. **Create a branch** for your changes:
   ```bash
   git checkout -b feature/your-feature-name
   ```
4. **Build** the project:
   ```bash
   mkdir build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   cmake --build . -j
   ```

## Code Style

- Follow existing formatting conventions in the codebase.
- Use meaningful variable and function names.
- All code must compile cleanly with strict flags:
  ```
  -Wall -Wextra -Wpedantic
  ```
- No new compiler warnings should be introduced.

## C++17 Requirements

This project targets **C++17**. You may use any standard library features available in C++17 including:

- `std::valarray` for numerical arrays
- `std::optional`, `std::variant`, `std::string_view`
- Structured bindings, `if constexpr`, fold expressions

Do **not** use features from C++20 or later standards.

## Adding a Numerical Method

When adding a new numerical method:

1. Place the implementation in the appropriate module directory under `src/`.
2. Add the header declaration in `include/` or `include/common/`.
3. Update `CMakeLists.txt` if new source files are added.
4. Validate numerical output against known analytical solutions or reference implementations.
5. Document the method order of accuracy and any limitations.

## Submitting Changes

1. **Commit** your changes with clear, descriptive messages.
2. **Push** your branch to your fork.
3. Open a **Pull Request** against the `main` branch.
4. Fill out the PR template completely.
5. Ensure the CI build passes.

## Reporting Issues

- Use the [Bug Report](https://github.com/abailey81/CPP-numerical-computing/issues/new?template=bug_report.yml) template for bugs.
- Use the [Feature Request](https://github.com/abailey81/CPP-numerical-computing/issues/new?template=feature_request.yml) template for enhancements.

## License

By contributing, you agree that your contributions will be licensed under the [MIT License](LICENSE).
