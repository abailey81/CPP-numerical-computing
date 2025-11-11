#include <iostream>
#include <fstream>
#include <sstream>
#include <valarray>
#include <cmath>
#include <cstdlib>
#include "q234.hpp"

using namespace std;

// RHS of the ODE system: gravity, drag, Magnus
valarray<float> rhs(float t, valarray<float> Y) {
    valarray<float> dY(6);
    float vx = Y[3], vy = Y[4], vz = Y[5];
    float v_mag = sqrt(vx * vx + vy * vy + vz * vz); // speed magnitude

    float ax = 0.0f, ay = 0.0f, az = -A_GRAV; // default gravity acceleration

    // Air resistance (drag), acts opposite to velocity direction
    if (drag_on) {
        float A = M_PI * R_BALL * R_BALL;
        float drag_coeff = 0.5f * C_DRAG * RHO_AIR * A / M_BALL;
        ax += -drag_coeff * v_mag * vx;
        ay += -drag_coeff * v_mag * vy;
        az += -drag_coeff * v_mag * vz;
    }

    // Magnus effect (lift due to spin), applied perpendicularly to velocity and spin
    if (magnus_on) {
        float wz = omega[2]; // spin along z-axis
        float magnus_term = S_MAGN / M_BALL;
        ax += magnus_term * wz * vy;
        ay += -magnus_term * wz * vx;
    }

    dY[0] = vx;
    dY[1] = vy;
    dY[2] = vz;
    dY[3] = ax;
    dY[4] = ay;
    dY[5] = az;

    return dY;
}

int main(int argc, char* argv[]) {
    float v0 = 25.0f;
    if (argc > 1) v0 = atof(argv[1]); // allows command-line velocity override

    float t = 0.0f, dt = 0.01f;
    float angle = 20.0f * M_PI / 180.0f; // convert degrees to radians
    float x0 = PITCH_L / 2 - 20.0f;      // 20m from goal line
    float y0 = 3.0f;                     // 3m left from center
    float z0 = R_BALL;                  // touching the ground
    float vx0 = v0 * cos(angle);
    float vy0 = 0.0f;
    float vz0 = v0 * sin(angle);

    valarray<float> Y = {x0, y0, z0, vx0, vy0, vz0};

    // Print initial state to stdout with z adjusted to start from 0
    cout << t << " " << Y[0] << " " << Y[1] << " " << (Y[2] - R_BALL)
         << " " << Y[3] << " " << Y[4] << " " << Y[5] << "\n";

    // Output file name depends on enabled physics
    ostringstream fname;
    fname << "v" << int(v0);
    if (drag_on) fname << "_drag";
    if (magnus_on) fname << "_magnus";
    fname << ".dat";

    ofstream fout(fname.str());
    if (!fout) {
        cerr << "Error: could not open output file.\n";
        return 1;
    }

    // Initial line to output file (z adjusted to zero level)
    fout << t << " " << Y[0] << " " << Y[1] << " " << (Y[2] - R_BALL)
         << " " << Y[3] << " " << Y[4] << " " << Y[5] << "\n";

    // RK4 integration loop until ball hits ground or passes goal line
    while (Y[0] < PITCH_L / 2 && Y[2] > R_BALL) {
        Y = rk4(t, Y, dt, 1);
        t += dt;

        // Write to file (z adjusted)
        fout << t << " " << Y[0] << " " << Y[1] << " " << (Y[2] - R_BALL)
             << " " << Y[3] << " " << Y[4] << " " << Y[5] << "\n";

        // Also print to stdout (raw z, not adjusted)
        cout << t << " " << Y[0] << " " << Y[1] << " " << (Y[2] - R_BALL)
             << " " << Y[3] << " " << Y[4] << " " << Y[5] << "\n";
    }

    fout.close();

    // Print outcome analysis to stderr
    cerr << "v0 = " << v0 << " → ";
    if (Y[0] >= PITCH_L / 2) {
        if (Y[2] <= GOAL_H) {
            cerr << "The Shot is GOOD – under the bar.\n";
        } else {
            cerr << "The Shot is OVER – went above the bar.\n";
        }

        float y_left = -GOAL_W / 2.0f;
        float y_right = GOAL_W / 2.0f;
        float dist_left = fabs(Y[1] - y_left);
        float dist_right = fabs(Y[1] - y_right);
        float z_diff = fabs(Y[2] - GOAL_H);

        cerr << "Y-position at goal line: " << Y[1] << " m\n";
        cerr << "Distance to left post at y = " << y_left << ": " << dist_left << " m\n";
        cerr << "Distance to right post at y = " << y_right << ": " << dist_right << " m\n";
        cerr << "Vertical distance from crossbar: " << z_diff << " m\n";
        cerr << "Time to cross goal line: " << t << " s\n";
    } else {
        cerr << "The Shot is WEAK – hit the ground before goal.\n";
    }

    return 0;
}