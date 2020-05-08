#ifndef analyzer_h
#define analyzer_h

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include "TApplication.h"
#include "TGraphErrors.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TMatrixDSym.h"
#include <regex>

using namespace std;

// Definisco la classe Analyzer con solo il metodo loadData
class Analyzer {
    public:
        bool loadData(string fileName, vector<double>& data, double& min, double& max);
};

#endif