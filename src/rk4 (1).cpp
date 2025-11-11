#include <valarray>
#include "q234.hpp"

using namespace std;


// Runge-Kutta 4th order method
valarray<float> rk4(float t0, valarray<float> y0, float h, int N) {
    float t = t0;
    valarray<float> y = y0;
    valarray<float> k1, k2, k3, k4;

    // Evolution loop for 4th order Runge-Kutta
    for (int i=0; i<N; i++) {
        k1 = h * rhs(t, y);
        k2 = h * rhs(t + h / 2.0, y + k1 / 2.0);
        k3 = h * rhs(t + h / 2.0, y + k2 / 2.0);
        k4 = h * rhs(t + h, y + k3);

        // Update y using the weighted average of slopes
        y += (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;

        // Move to the next step
        t += h;
    }

    return y;
}
