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
    return gaussFit(x, par) + pol0(x, &par[3]) + gaussFit(x, &par[4]) + gaussFit(x, &par[7]) + gaussFit(x, &par[10]);
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
    //gStyle->SetOptStat("");

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
    histoYYYYY->GetXaxis()->SetRangeUser(360, 460);

    /*TF1* funcFit = new TF1("funcFit", totalFit, 1530, 1610, 13);
    funcFit->SetParName(0,"Amp");
    funcFit->SetParName(1,"Mean");
    funcFit->SetParName(2,"Std Dev");
    funcFit->SetParName(3,"Noise");
    funcFit->SetParameter(0, 800);
    funcFit->SetParameter(1, 390);
    funcFit->SetParameter(2, 5);
    funcFit->SetParameter(3, 300);
    funcFit->SetParameter(4, 1800);
    funcFit->SetParameter(5, 405);
    funcFit->SetParameter(6, 5);
    funcFit->SetParameter(7, 1400);
    funcFit->SetParameter(8, 420);
    funcFit->SetParameter(9, 5);
    funcFit->SetParameter(10, 1400);
    funcFit->SetParameter(11, 440);
    funcFit->SetParameter(12, 7);
    
    histoYYYYY->Fit("funcFit");*/

    canvasSource->Print("graphs/spectreYYYYY/graph_YYYYY_peak10.pdf");

    delete histoYYYYY;
    delete canvasSource;
}
