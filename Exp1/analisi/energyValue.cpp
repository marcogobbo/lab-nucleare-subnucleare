// c++ -o compute energyValue.cpp
// ./compute

#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char** argv) {
    double m = 0.001317;
    double errM = 0.000001;
    double q = 0.2131;
    double errQ = 0.0069;

    double tensioni[4] = {
        3970,
        4006,
        4036,
        4062
    };

    double errTensioni[4] = {
        17,
        12,
        10,
        14
    };

    double energia[4];
    double errEnergia[4];

    for (unsigned int i = 0; i < 4; i++) {
        energia[i] = tensioni[i]*m + q;
        errEnergia[i] = sqrt(pow(tensioni[i]*errM,2)+pow(1*errQ,2));
        cout << "Energia Picco " << i+1 << ": " << energia[i] << " ± " << errEnergia[i] << " MeV " << endl;
    }

    return 0;
}