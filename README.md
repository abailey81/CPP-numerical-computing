# Numerical Computing Framework in Modern C++

A production-grade **numerical-analysis framework** implemented in **modern C++17**, showcasing applied mathematics, algorithmic precision, and modular software design.

This project models continuous physical systems — motion, energy, and dynamics — through discrete numerical methods.  
It demonstrates how to structure mathematical computing code for **clarity, performance, and reusability**.

---

##  Key Capabilities

| Domain | Technique | Implementation |
|:-------|:-----------|:---------------|
| **Object-Oriented Design** | Player & Team abstraction, encapsulated state, derived metrics | `src/oop_foundations/` |
| **Data-Driven Kinematics** | Coordinate transforms, numerical differentiation, velocity & acceleration | `src/tracking_kinematics/` |
| **Energy Modelling** | Lagrange interpolation, trapezoidal & Newton–Cotes integration | `src/energy_integration/` |
| **Physics Simulation** | 6-state Runge–Kutta (RK4) solver for projectile dynamics with drag & Magnus effects | `src/ballistics_rk4/` |

---

##  Architecture


.
├── src/
│   ├── oop_foundations/
│   ├── tracking_kinematics/
│   ├── energy_integration/
│   ├── ballistics_rk4/
│   └── common/               # interpolation, RK4, shared utils
├── include/
├── data/                      # raw inputs (git-ignored outputs)
├── docs/                      # PDF brief(s)
├── report/figures/            # generated plots (git-ignored)
├── CMakeLists.txt
└── README.md


The framework follows **production-engineering principles**:
- Modular, reusable code units  
- Strict compiler hygiene (`-Wall -Wextra -Wpedantic`)  
- Automated builds via **CMake**  
- Continuous-integration ready (`.github/workflows/cpp.yml`)  
- Platform-independent (tested on macOS / Linux)

---

##  Mathematical Focus

| Method | Concept | Use Case |
|:-------|:---------|:----------|
| **Finite Difference Derivatives** | Numerical gradients | Compute velocity & acceleration |
| **Lagrange Interpolation** | Polynomial curve fitting | Estimate power from speed data |
| **Composite Trapezoid Rule** | Numerical integration | Energy spent by player |
| **Newton–Cotes (4-point)** | Higher-order integration | Precision benchmarking |
| **Runge–Kutta 4 (RK4)** | ODE integration | Simulate ball trajectory |
| **Magnus Effect & Drag** | Cross-product physics | Spin-induced curve motion |

---

##  Tech Stack

| Category | Tools / Frameworks |
|-----------|--------------------|
| **Language** | C++ 17 |
| **Build System** | CMake |
| **CI/CD** | GitHub Actions |
| **Data Tools** | valarray · fstream · gnuplot (visualisation) |
| **Platforms** | macOS (clang++) · Linux (g++) |

---

##  Build & Run

```bash
# Clone and build
git clone https://github.com/abailey81/numerical-computing-cpp.git
cd numerical-computing-cpp
mkdir build && cd build
cmake ..
cmake --build . -j

# Execute modules
./oop_foundations
./tracking_kinematics
./energy_integration
./ballistics_rk4 25    # try 20–30 m/s variations
