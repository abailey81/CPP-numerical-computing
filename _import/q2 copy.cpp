#include <iostream>
#include <iomanip>
#include <valarray>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
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
                data.push_back(stod(cell));
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







int main(int argc, char *argv[]) {

    valarray<float> data = read_tracking_data("tracking_data.dat");
    size_t Ndata = data.size()/3;

    /* Initialise new individual arrays by taking slices of
     * data (with stride=3) to extract the three columns  */
    valarray<float> t_varr(data[slice(0, Ndata, 3)]);
    valarray<float> x_varr(data[slice(1, Ndata, 3)]);
    valarray<float> y_varr(data[slice(2, Ndata, 3)]);

    /* Continue the main() here  */




    return 0;
}
