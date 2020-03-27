// c++ -o compute energyValue.cpp `root-config --cflags --glibs`
// ./compute

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include "TMath.h"

using namespace std;

bool compatibilityTest(double& pvalue, double meas1, double err1, double meas2, double err2, double significance, string testType, double n1, double n2) {

    double stat;

    if (testType == "Normal") {
      stat   = fabs((meas1 - meas2) / sqrt(err1*err1 + err2*err2));
      pvalue = TMath::Erfc(stat/sqrt(2.));
    }
    else if (testType == "tStudent") {
        if ((err1 != 0) && (err2 != 0)) {
            stat = fabs((meas1 - meas2) / sqrt(((n1-1.)*err1*err1 + (n2-1.)*err2*err2) / (n1+n2-2.) * (1./n1 + 1./n2)));
        }
        else if ((err1 != 0) && (err2 == 0)) {
            stat = fabs((meas1 - meas2) / (err1/sqrt(n1)));
            n2   = 1;
        }
        else if ((err1 == 0) && (err2 != 0)) {
	        stat = fabs((meas1 - meas2) / (err2/sqrt(n2)));
            n1   = 1;
	    }
        pvalue = 2. * (1. - TMath::StudentI(stat,n1+n2-2.));
    }
    else  {
        cout << "[compatibilityTest]\tError: unknown test type " << testType.c_str() << endl;
        return false;
    }
    if (pvalue < significance) {
        return false;
    }
    else {
        return true;
    }
}

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
        errEnergia[i] = sqrt(pow(tensioni[i]*errM,2)+pow(1*errQ,2)+pow(m*errTensioni[i],2));
        cout << "Energia Picco " << i+1 << ": " << energia[i] << " ± " << errEnergia[i] << " MeV " << endl;
    }

    for (unsigned int i = 0; i < 4; i++) {
        energia[i] = energia[i]*1000;
        errEnergia[i] = errEnergia[i]*1000;
    }

    double tabulatedEnergyValues[4] = {
        5388,
        5443,
        5486,
        5545
    };

    double pvalue;

    ofstream OutFile ("compatibilityTestResults.txt");
    for (unsigned int i = 0; i < 4; i++) {
        if (compatibilityTest(pvalue, energia[i], errEnergia[i], tabulatedEnergyValues[i], 0, 0.05, "Normal", 1, 1) == true) {
            OutFile << "Il picco " << (i+1) << " a energia " << setprecision(2) << (float)energia[i] << " ± " << setprecision(2) << (float)errEnergia[i] << " keV è compatibile con il valore tabulato " << setprecision(2) << (float)tabulatedEnergyValues[i] << " keV con una confidenza del " << setprecision(2) << (float)pvalue*100 << "% > 5%\n";
        }
        else {
            OutFile << "Il picco " << (i+1) << " a energia " << setprecision(2) << (float)energia[i] << " ± " << setprecision(2) << (float)errEnergia[i] << " keV NON è compatibile con il valore tabulato " << setprecision(2) << (float)tabulatedEnergyValues[i] << " keV con una confidenza del " << setprecision(2) << (float)pvalue*100 << "% < 5%\n";
        }
    }

    double m_241Am = 0.001689;
    double errM_241Am = 0.0003634;
    double q_241Am = -1.326;
    double errQ_241Am = 1.463;

    if (compatibilityTest(pvalue, m_241Am, errM_241Am, m, errM, 0.05, "tStudent", 999, 999) == true) {
        OutFile << "La m della curva di calibrazione del 241-Am: " << setprecision(5) << (float)m_241Am << " ± " << setprecision(5) << (float)errM_241Am << " è compatibile con il valore trovato per la curva di calibrazione pulsar: " << setprecision(5) << (float)m << " ± " << setprecision(5) << (float)errM << " con una confidenza del " << setprecision(2) << (float)pvalue*100 << "% > 5%\n";
    }
    else {
        OutFile << "La m della curva di calibrazione del 241-Am: " << setprecision(5) << (float)m_241Am << " ± " << setprecision(5) << (float)errM_241Am << " NON è compatibile con il valore trovato per la curva di calibrazione pulsar: " << setprecision(5) << (float)m << " ± " << setprecision(5) << (float)errM << " con una confidenza del " << setprecision(2) << (float)pvalue*100 << "% < 5%\n";
    }

    if (compatibilityTest(pvalue, q_241Am, errQ_241Am, q, errQ, 0.05, "tStudent", 999, 999) == true) {
        OutFile << "La q della curva di calibrazione del 241-Am: " << setprecision(5) << (float)q_241Am << " ± " << setprecision(5) << (float)errQ_241Am << " è compatibile con il valore trovato per la curva di calibrazione pulsar: " << setprecision(5) << (float)q << " ± " << setprecision(5) << (float)errQ << " con una confidenza del " << setprecision(2) << (float)pvalue*100 << "% > 5%\n";
    }
    else {
        OutFile << "La q della curva di calibrazione del 241-Am: " << setprecision(5) << (float)q_241Am << " ± " << setprecision(5) << (float)errQ_241Am << " NON è compatibile con il valore trovato per la curva di calibrazione pulsar: " << setprecision(5) << (float)q << " ± " << setprecision(5) << (float)errQ << " con una confidenza del " << setprecision(2) << (float)pvalue*100 << "% < 5%\n";
    }


    return 0;
}