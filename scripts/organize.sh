#!/usr/bin/env bash
set -euo pipefail
shopt -s nullglob

mkdir -p src/{oop_foundations,tracking_kinematics,energy_integration,ballistics_rk4,common}
mkdir -p report/figures/{tracking,energy,ballistics}

if [[ -f src/interp.cpp ]]; then mv src/interp.cpp src/common/; fi
if [[ -f include/interp.hpp ]]; then mkdir -p include/common; mv include/interp.hpp include/common/; fi
if [[ -f src/rk4.cpp ]]; then mv src/rk4.cpp src/common/; fi

if [[ -f src/q1.cpp ]]; then mv src/q1.cpp src/oop_foundations/main_oop.cpp; fi
if [[ -f include/player.hpp ]]; then mv include/player.hpp include/; fi

if [[ -f src/q2.cpp ]]; then mv src/q2.cpp src/tracking_kinematics/main_tracking.cpp; fi
if [[ -f src/q3.cpp ]]; then mv src/q3.cpp src/energy_integration/main_energy.cpp; fi
if [[ -f src/q4.cpp ]]; then mv src/q4.cpp src/ballistics_rk4/main_ballistics.cpp; fi
if [[ -f include/q234.hpp ]]; then mv include/q234.hpp include/; fi

for f in src/Question*.py; do
  [[ -e "$f" ]] || continue
  base=$(basename "$f")
  num=$(echo "$base" | grep -o '[0-9]\+' | head -n1)
  [[ -n "${num:-}" ]] || num="00"
  printf -v two "%02d" "$num"
  mv "$f" "src/tracking_kinematics/tracking_${two}.py"
done

for img in _import/*.png _import/*.jpg _import/*.jpeg; do
  [[ -e "$img" ]] || continue
  cp "$img" report/figures/
done

rm -rf _import 2>/dev/null || true
