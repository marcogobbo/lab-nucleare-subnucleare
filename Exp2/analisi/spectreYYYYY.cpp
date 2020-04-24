// c++ -o compute spectreYYYYY.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"

using namespace std;

double gaussFit (double* x, double* par) {
  	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

double pol0 (double*x, double* par) {
    return par[0];
}

double totalFit (double* x, double* par) {
    return gaussFit(x, par) + pol0(x, &par[3]);
}



int main() {
    Analyzer YYYYY, noise;
    string fileName = "data/Calibration/YYYYY.txt";
    string fileName1 = "data/Calibration/noise.txt";

    vector<double> data, dataNoise;
    double min, max;

    if (YYYYY.loadData(fileName, data, min, max) == false) {
        cout << "Errore nel caricare il file: " << fileName.c_str() << endl;
    };
    if (noise.loadData(fileName1, dataNoise, min, max) == false) {
        cout << "Errore nel caricare il file: " << fileName1.c_str() << endl;
    };

    gStyle->SetOptFit(1112);

    TH1D* histoYYYYY = new TH1D("Data", "YYYYY", 16384, 0, 16384);

    for (unsigned int i = 0; i < data.size(); i++) {
        histoYYYYY->SetBinContent(i, abs(data[i]-dataNoise[i]));
    }

    TCanvas* canvasSource = new TCanvas("canvasSource", "canvasSource", 0, 0, 800, 500);

    canvasSource->cd();

    histoYYYYY->Draw();
    histoYYYYY->SetFillColor(kYellow-10);
    histoYYYYY->GetXaxis()->SetTitle("Channels [mV]");
    histoYYYYY->GetYaxis()->SetTitle("Counts");
    histoYYYYY->GetXaxis()->SetRangeUser(0, 16384);

    canvasSource->Print("graphs/spectreYYYYY/graph_YYYYY.pdf");

    delete histoYYYYY;
    delete canvasSource;
}
