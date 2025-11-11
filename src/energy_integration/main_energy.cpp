#include <iostream>
#include <iomanip>
#include <valarray>
#include <fstream>
#include <sstream>
#include <string>
#include "interp.hpp"

using namespace std;

// Question 3(e): Composite 4-point Newton-Cotes integration
// Implements a 4-point Newton-Cotes rule: evaluates a composite integral of equally spaced values
// Assumes N = 3k + 1, i.e. the number of intervals is a multiple of 3
float integrate_newton_cotes_4(const valarray<float>& f, float h) {
    size_t N = f.size();
    if (N < 4 || (N - 1) % 3 != 0) {
        cerr << "Error: Data size must be 3k+1 for 4-point Newton-Cotes rule.\n";
        return -1.0f;
    }

    float result = 0.0f;
    for (size_t i = 0; i < N - 1; i += 3) {
        // Applies the 4-point Newton-Cotes weight formula on each 3-interval group
        result += (3.0f * h / 8.0f) *
            (f[i] + 3.0f * f[i + 1] + 3.0f * f[i + 2] + f[i + 3]);
    }

    return result;
}

int main() {
    // Question 3(a): Interpolation of P(v)
    valarray<float> v_table = {0.0f, 3.0f, 5.0f, 8.0f};         // velocity samples
    valarray<float> P_table = {100.0f, 700.0f, 1100.0f, 2000.0f}; // corresponding power values

    float v_eval = 5.8f;
    float P_eval = Lagrange_N(v_table, P_table, v_eval); // interpolate power at v = 5.8
    cout << "Interpolated power at v = " << v_eval << " m/s is "
         << fixed << setprecision(2) << P_eval << " W" << endl;

    // Question 3(c): Read speed data from file
    ifstream file("player_speed.dat");
    if (!file.is_open()) {
        cerr << "Error opening player_speed.dat" << endl;
        return 1;
    }

    vector<float> t_vec, v_vec;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        float t, v;
        if (iss >> t >> v) {
            t_vec.push_back(t);  // time value
            v_vec.push_back(v);  // speed value
        }
    }
    file.close();

    // Store input vectors into valarrays for processing
    valarray<float> t_data(t_vec.data(), t_vec.size());
    valarray<float> v_data(v_vec.data(), v_vec.size());

    // Interpolate P(v(t)) for all time points
    valarray<float> p_i(v_data.size());
    for (size_t i = 0; i < v_data.size(); ++i) {
        p_i[i] = Lagrange_N(v_table, P_table, v_data[i]);  // interpolate power from speed
    }

    // Show first few values for verification
    cout << "\nFirst few interpolated power values from speed time series:" << endl;
    for (size_t i = 0; i < min<size_t>(5, p_i.size()); ++i) {
        cout << "t = " << t_data[i] << " s, v = " << v_data[i]
             << " m/s -> P = " << p_i[i] << " W" << endl;
    }

    // Question 3(d): Compute energy using trapezoidal rule
    float dt = 0.2f; // time step

    float energy_spent = dt * (
        0.5f * p_i[0] +
        valarray<float>(p_i[slice(1, p_i.size() - 2, 1)]).sum() +
        0.5f * p_i[p_i.size() - 1]
    ); // Trapezoidal integration

    cout << "\nTotal energy spent by player A over "
         << t_data[t_data.size() - 1] << " seconds is "
         << fixed << setprecision(2) << energy_spent << " J" << endl;

    // Question 3(e): Newton-Cotes 4-point integration
    // Only evaluate if data size is compatible with rule (N = 3k+1)
    if ((p_i.size() - 1) % 3 == 0) {
        float energy_nc4 = integrate_newton_cotes_4(p_i, dt);
        cout << "Energy using 4-point Newton-Cotes rule: "
             << fixed << setprecision(2) << energy_nc4 << " J" << endl;
    } else {
        cout << "Warning: p_i size incompatible with 4-point Newton-Cotes rule (must be 3k+1)." << endl;
    }

    return 0;
}
