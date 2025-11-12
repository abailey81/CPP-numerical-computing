#include <iostream>
#include <iomanip>
#include <valarray>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "q234.hpp"
#include "interp.hpp"

using namespace std;

/* Read a file with position timeseries data formatted
 * in 3 space-separated columns:
 * t x y
 * and return the numerical data in the form of a single
 * valarray of size N*3. The data is read line-by line,
 * so that the value of row i and column j is stored in
 * the (3*i + j)-th component of the valarray
 */
valarray<float> read_tracking_data(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return valarray<float>();
    }

    vector<float> data; // Use vector so we can .push_back()

    string line;
    int row = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        int col=0;
        while (getline(ss, cell, ' ') && col < 3) {
            try {
                data.push_back(stof(cell)); // read as float
            } catch (const invalid_argument& e) {
                cerr << "Error: Invalid data in file " << filename << " at row " << row << endl;
                return valarray<float>();
            }
            ++col;
        }
        ++row;
    }

    // Copy data of vector into valarray and return it
    valarray<float> valdata(data.data(), data.size());

    return valdata;
}


/* Add your functions here */

// Q2(a): Transform normalised to physical pitch coordinates (centre at origin)
void coord_xfm(valarray<float> &x_out, valarray<float> &y_out,
               valarray<float> x_data, valarray<float> y_data)
{
    x_out = x_data * PITCH_L - PITCH_L / 2.0f;
    y_out = y_data * PITCH_W - PITCH_W / 2.0f;
}


int main(int argc, char *argv[]) {

    valarray<float> data = read_tracking_data("tracking_data.dat");
    size_t Ndata = data.size()/3;

    /* Initialise new individual arrays by taking slices of
     * data (with stride=3) to extract the three columns  */
    valarray<float> t_varr(data[slice(0, Ndata, 3)]);
    valarray<float> x_varr(data[slice(1, Ndata, 3)]);
    valarray<float> y_varr(data[slice(2, Ndata, 3)]);

    /* Continue the main() here  */

    // Q2(b): Transform to physical coordinates
    valarray<float> x_phys(Ndata), y_phys(Ndata);
    coord_xfm(x_phys, y_phys, x_varr, y_varr);

    // Q2(c): Compute speed using centered differences
    float dt = 0.2f;

    valarray<float> x_fwd(x_phys[slice(2, Ndata - 2, 1)]);
    valarray<float> x_bwd(x_phys[slice(0, Ndata - 2, 1)]);
    valarray<float> vx = (x_fwd - x_bwd) / (2.0f * dt);

    valarray<float> y_fwd(y_phys[slice(2, Ndata - 2, 1)]);
    valarray<float> y_bwd(y_phys[slice(0, Ndata - 2, 1)]);
    valarray<float> vy = (y_fwd - y_bwd) / (2.0f * dt);

    valarray<float> v_mag = sqrt(vx * vx + vy * vy);
    valarray<float> t_centered(t_varr[slice(1, Ndata - 2, 1)]);

    // Output to file (ti, vi)
    ofstream outfile("player_speed.dat");
    outfile << fixed << setprecision(6);
    for (size_t i = 0; i < v_mag.size(); ++i) {
        outfile << t_centered[i] << " " << v_mag[i] << endl;
    }
    outfile.close();

    // Max speed
    float vmax = v_mag.max();
    cout << "Maximum speed reached: " << vmax << " m/s" << endl;

    // Q2(d): Compute acceleration using centered diff on vx, vy
    valarray<float> vx_fwd(vx[slice(2, vx.size() - 2, 1)]);
    valarray<float> vx_bwd(vx[slice(0, vx.size() - 2, 1)]);
    valarray<float> ax = (vx_fwd - vx_bwd) / (2.0f * dt);

    valarray<float> vy_fwd(vy[slice(2, vy.size() - 2, 1)]);
    valarray<float> vy_bwd(vy[slice(0, vy.size() - 2, 1)]);
    valarray<float> ay = (vy_fwd - vy_bwd) / (2.0f * dt);

    valarray<float> a_mag = sqrt(ax * ax + ay * ay);

    // Output lengths explanation for (d)
    cout << "v_mag.size() = " << v_mag.size() << " (1001 - 2 = 999(Length of v_mag))" << endl;
    cout << "a_mag.size() = " << a_mag.size() << " (999 - 2 = 997(Length of a_mag))" << endl;

    // Q2(f): Conceptual part — not coded, but here’s the answer
    cout << "\nQ2(f): To reconstruct smooth motion at 120Hz from 5Hz data,\n"
         << "we would use cubic interpolation to estimate the player’s\n"
         << "position between samples. This allows smooth motion playback\n"
         << "at a much higher frame rate.\n";

    return 0;
}
