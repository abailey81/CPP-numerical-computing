<div align="center">

# Numerical Computing Framework

### Modern C++17 Numerical Analysis for Sports Analytics

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=for-the-badge&logo=cplusplus&logoColor=white)](https://en.cppreference.com/w/cpp/17)
[![CMake](https://img.shields.io/badge/CMake-3.16+-064F8C.svg?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](LICENSE)
[![Build](https://img.shields.io/github/actions/workflow/status/abailey81/CPP-numerical-computing/cpp.yml?branch=main&style=for-the-badge&logo=githubactions&logoColor=white&label=CI)](https://github.com/abailey81/CPP-numerical-computing/actions/workflows/cpp.yml)
[![Stars](https://img.shields.io/github/stars/abailey81/CPP-numerical-computing?style=for-the-badge&logo=github&color=gold)](https://github.com/abailey81/CPP-numerical-computing/stargazers)
[![Forks](https://img.shields.io/github/forks/abailey81/CPP-numerical-computing?style=for-the-badge&logo=github&color=silver)](https://github.com/abailey81/CPP-numerical-computing/network/members)

---

A production-grade numerical analysis framework that models continuous physical systems through discrete computational methods. Built for **clarity**, **performance**, and **mathematical rigour**.

[Getting Started](#-getting-started) · [Modules](#-module-overview) · [Methods](#-numerical-methods) · [Physics](#-physics-model) · [Contributing](CONTRIBUTING.md)

</div>

---

## Highlights

<table>
<tr>
<td align="center" width="25%">

**OOP Design**

Player & Team abstractions with encapsulated state and derived metrics

</td>
<td align="center" width="25%">

**Numerical Derivatives**

Central finite differences for velocity and acceleration from tracking data

</td>
<td align="center" width="25%">

**Integration**

Lagrange interpolation with trapezoidal and Newton-Cotes quadrature

</td>
<td align="center" width="25%">

**ODE Solvers**

4th-order Runge-Kutta with drag and Magnus force physics

</td>
</tr>
</table>

---

## Module Overview

| # | Module | Description | Key Files |
|:-:|:-------|:-----------|:----------|
| 1 | **OOP Foundations** | Player and Team class hierarchy with encapsulated attributes, derived statistics, and polymorphic behaviour | `src/oop_foundations/` `include/player.hpp` `include/team.hpp` |
| 2 | **Tracking Kinematics** | Coordinate transforms from normalised to physical pitch coordinates, numerical differentiation via central differences to compute velocity and acceleration from 5 Hz tracking data (1001 frames) | `src/q2.cpp` `data/tracking_data.dat` |
| 3 | **Energy Integration** | Lagrange polynomial interpolation of power-speed curves, composite trapezoidal rule and 4-point Newton-Cotes integration for total energy expenditure | `src/q3.cpp` `data/speed_A.dat` |
| 4 | **Ballistics RK4** | 6-state ODE system solved via RK4 for 3D soccer ball trajectory with configurable drag, Magnus spin effect, and goal-line analysis | `src/q4.cpp` `include/q234.hpp` |

---

## Numerical Methods

| Method | Order | Application | Module |
|:-------|:-----:|:-----------|:------:|
| **Central Finite Differences** | O(h²) | Velocity and acceleration from position time series | Kinematics |
| **Lagrange Interpolation** | O(n) | Polynomial curve fitting for power-speed relationship | Integration |
| **Horner’s Method** | O(n) | Efficient polynomial evaluation | Integration |
| **Composite Trapezoidal Rule** | O(h²) | Numerical integration of energy expenditure | Integration |
| **Newton-Cotes 4-Point** | O(h⁵) | Higher-order composite integration for precision benchmarking | Integration |
| **Runge-Kutta 4th Order** | O(h⁴) | Time integration of 3D projectile ODE system | Ballistics |
| **Cross-Product Magnus** | Analytical | Spin-induced lateral force on rotating sphere | Ballistics |

---

## Physics Model

The ballistics module simulates a soccer ball as a 3D projectile subject to three forces: gravity, aerodynamic drag, and the Magnus effect from spin.

<details>
<summary><strong>Mathematical Formulations</strong></summary>

<br>

**State Vector (6 components):**
```
Y = [x, y, z, vx, vy, vz]
```

**Equations of Motion:**
```
dx/dt = vx          dvx/dt = a_drag_x + a_magnus_x
dy/dt = vy          dvy/dt = a_drag_y + a_magnus_y
dz/dt = vz          dvz/dt = -g + a_drag_z
```

**Drag Force:**
```
a_drag = -(1/2) * C_d * rho * A * |v| * v / m

where:
  C_d   = 0.473       (drag coefficient)
  rho   = 1.22 kg/m³ (air density)
  A     = pi * R²    (cross-sectional area)
  R     = 0.111 m     (ball radius)
  m     = 0.436 kg    (ball mass)
```

**Magnus Effect:**
```
a_magnus = (S / m) * (omega x v)

where:
  S     = 0.002       (Magnus coefficient)
  omega = [0, 0, 10]  rad/s (spin angular velocity)
```

**RK4 Integration:**
```
k1 = h * f(t_n, y_n)
k2 = h * f(t_n + h/2, y_n + k1/2)
k3 = h * f(t_n + h/2, y_n + k2/2)
k4 = h * f(t_n + h, y_n + k3)

y_{n+1} = y_n + (k1 + 2*k2 + 2*k3 + k4) / 6
```

**Central Finite Difference (velocity from position):**
```
v_i = (x_{i+1} - x_{i-1}) / (2 * dt)

where dt = 0.2 s (5 Hz sampling)
```

**Composite Trapezoidal Rule:**
```
integral = h * [f_0/2 + f_1 + f_2 + ... + f_{N-1} + f_N/2]
```

**Newton-Cotes 4-Point (Simpson’s 3/8):**
```
integral = (3h/8) * [f_0 + 3*f_1 + 3*f_2 + f_3]

applied compositely over groups of 3 sub-intervals (N = 3k+1 points)
```

</details>

### Physical Constants

| Parameter | Symbol | Value | Unit |
|:----------|:------:|:-----:|:----:|
| Gravitational acceleration | g | 9.812 | m/s² |
| Ball radius | R | 0.111 | m |
| Ball mass | m | 0.436 | kg |
| Drag coefficient | C_d | 0.473 | -- |
| Magnus coefficient | S | 0.002 | -- |
| Air density | rho | 1.22 | kg/m³ |
| Spin rate | omega_z | 10.0 | rad/s |
| Pitch length | L | 100.0 | m |
| Pitch width | W | 64.0 | m |
| Goal width | -- | 7.32 | m |
| Goal height | -- | 2.44 | m |

---

## Getting Started

### Prerequisites

- **C++17** compatible compiler (GCC 7+, Clang 5+, MSVC 19.14+)
- **CMake** 3.16 or higher

### Build

```bash
git clone https://github.com/abailey81/CPP-numerical-computing.git
cd CPP-numerical-computing
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j
```

### Run

```bash
# Execute individual modules
./oop_foundations
./tracking_kinematics
./energy_integration
./ballistics_rk4            # default: 25 m/s launch
./ballistics_rk4 30         # custom velocity: 30 m/s
```

> **Note:** Data files (`tracking_data.dat`, `speed_A.dat`) must be in the working directory or the `data/` folder.

---

## Project Structure

```
CPP-numerical-computing/
|-- .github/
|   |-- workflows/
|   |   +-- cpp.yml              # CI: build on every push & PR
|   |-- ISSUE_TEMPLATE/          # Bug report & feature request forms
|   +-- PULL_REQUEST_TEMPLATE.md
|-- include/
|   |-- common/
|   |   +-- interp.hpp           # Lagrange interpolation interface
|   |-- player.hpp               # Player class declaration
|   |-- team.hpp                 # Team class declaration
|   +-- q234.hpp                 # Physics constants, RK4 & RHS prototypes
|-- src/
|   |-- common/
|   |   +-- interp.cpp           # Interpolation implementation
|   |-- oop_foundations/
|   |   +-- main_oop.cpp         # Module 1: OOP design patterns
|   |-- q2.cpp                   # Module 2: Tracking kinematics
|   |-- q3.cpp                   # Module 3: Energy integration
|   +-- q4.cpp                   # Module 4: Ballistics RK4
|-- data/
|   |-- tracking_data.dat        # 1001 frames, 5 Hz player tracking
|   +-- speed_A.dat              # Speed time series for energy calc
|-- docs/                        # Assignment briefs & reports
|-- CMakeLists.txt               # Build configuration
|-- LICENSE                      # MIT License
|-- CONTRIBUTING.md              # Contribution guidelines
|-- SECURITY.md                  # Security policy
+-- README.md
```

---

## Compiler Flags

All targets are compiled with strict diagnostics enabled:

```
-Wall -Wextra -Wpedantic
```

This ensures maximum code quality and catches potential issues at compile time.

---

<div align="center">

**Built with modern C++ and mathematical precision.**

[Report a Bug](.github/ISSUE_TEMPLATE/bug_report.yml) · [Request a Feature](.github/ISSUE_TEMPLATE/feature_request.yml) · [Contribute](CONTRIBUTING.md)

MIT License -- Copyright 2025 Tamer Atesyakar

</div>
