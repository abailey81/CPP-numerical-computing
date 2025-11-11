#ifndef Q234_H_
#define Q234_H_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <valarray>
#include <string>
#include <sstream>
#include <fstream>

/* Pitch dimensions */

#define PITCH_L 100.0 // Football pitch length in meters
#define PITCH_W 64.0  // Football pitch width in meters
#define GOAL_W 7.32   // Goal width in meters (distance between inner sides of posts)
#define GOAL_H 2.44   // Goal height in meters (from ground to lower side of post)

/* Definitions of constants */

#define A_GRAV 9.812   // Acceleration of gravity in m/s^2
#define R_BALL 0.111   // Football's radius in meters
#define M_BALL 0.436   // Football's mass in kg

#define C_DRAG 0.473   // Drag coefficient (dimensionless)
#define S_MAGN 0.002   // Magnus coefficient (dimensionless)
#define RHO_AIR 1.22   // Air density in kg/m^3


using namespace std;

static float omega[3] = {0.0, 0.0, 10.0}; // Angular velocity along the z-axis in rad/s
static bool drag_on = true;      // Flag that activates the effect of air resistance (drag force)
static bool magnus_on = true;    // Flag that activates the Magnus effect (curving)

/* Useful functions for diagnostics */
void print_vec(float v[6]);
valarray<float> read_data(const string& filename, const size_t Ncol);

/* Functions for numerical integration */
double nintegrate1D(valarray<double> fi, double h, int NCpoints);
double nintegrate1D(double a, double b, double (*func) (double x) , size_t N, int NCpoints);

/* You will need to implement the following functions */

/* q2.cpp */

void coord_xfm(valarray<float> &x_out, valarray<float> &y_out,
               valarray<float> x_data, valarray<float> y_data);

/* q4.cpp */

valarray<float> rhs(float t, valarray<float> yvec);
valarray<float> rk4(float t0, valarray<float> y0, float h, int N=1);

#endif // Q234_H_
