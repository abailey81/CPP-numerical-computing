cmake_minimum_required(VERSION 3.16)
project(numerical_computing_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

include_directories(include include/common)

add_library(common STATIC
  src/common/interp.cpp
  src/common/rk4.cpp
)
target_compile_options(common PRIVATE -Wall -Wextra -Wpedantic)

add_executable(oop_foundations      src/oop_foundations/main_oop.cpp)
add_executable(tracking_kinematics  src/tracking_kinematics/main_tracking.cpp)
add_executable(energy_integration   src/energy_integration/main_energy.cpp)
add_executable(ballistics_rk4       src/ballistics_rk4/main_ballistics.cpp)

target_link_libraries(oop_foundations      PRIVATE common)
target_link_libraries(tracking_kinematics  PRIVATE common)
target_link_libraries(energy_integration   PRIVATE common)
target_link_libraries(ballistics_rk4       PRIVATE common)
