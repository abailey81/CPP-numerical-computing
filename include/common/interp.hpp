#ifndef INTERP_H_
#define INTERP_H_

#include <cassert>
#include <iostream>
#include <valarray>
#include <vector>
#include <cmath>

using namespace std;

int locate(valarray<float>& xi, float x, bool uniform=true);
float Lagrange_Nk(int k, valarray<float>& xi, float x);
float Lagrange_N(valarray<float>& xi, valarray<float>& yi, float x);

/* Alternative way of performing interpolation */
valarray<float> interp_coeffs(const valarray<float>& xi, const valarray<float>& yi);
float poly_eval(const vector<float>& coeffs, const vector<float>& xi, float x);

#endif // INTERP_H_
