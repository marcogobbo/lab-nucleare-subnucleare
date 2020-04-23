// c++ -o compute sources.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

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

void computeHisto (string nameSource, double limInf, double limSup) {
    Analyzer Source;
    string fileName = "data/Sources/" + nameSource + ".dat";

    // Creo il vettore dove salvare i dati, min e max
    vector<double> data;
    double min, max;

    // Carico i dati controllando che non via siano errori
    if (Source.loadData(fileName, data, min, max) == false) {
        cout << "Errore nel caricare il file: " << fileName.c_str() << endl;
    };

    // Imposto il numero di bin
    const int nBin = 8192;

    gStyle->SetOptFit(1112);
    
    TString titleGraph = nameSource;
    TString namePDF = "graphs/spectreSources/graph_" + nameSource + ".pdf";

    TH1D* histoSource = new TH1D("Data", titleGraph, nBin, 0, 8192);

    for (unsigned int i = 0; i < data.size(); i++) {
        histoSource->SetBinContent(i, data[i]);
    }

    TCanvas* canvasSource = new TCanvas("canvasSource", "canvasSource", 0, 0, 800, 500);

    canvasSource->cd();

    histoSource->Draw();
    histoSource->SetFillColor(kYellow-10);
    histoSource->GetXaxis()->SetTitle("Channels [mV]");
    histoSource->GetYaxis()->SetTitle("Counts");
    histoSource->GetXaxis()->SetRangeUser(limInf, limSup);

    TF1* funcFit = new TF1("funcFit", totalFit, limInf, limSup, 4);
    funcFit->SetParName(0,"Amp");
    funcFit->SetParName(1,"Mean");
    funcFit->SetParName(2,"Std Dev");
    funcFit->SetParName(3,"Noise");
    funcFit->SetParameter(0, 900);
    funcFit->SetParameter(1, 3261);
    funcFit->SetParameter(2, 15);
    funcFit->SetParameter(3, 100);

    histoSource->Fit("funcFit");

    canvasSource->Print(namePDF);

    // Libero la memoria
    delete histoSource;
    delete funcFit;
    delete canvasSource;
}


int main() {
    computeHisto("228Th", 0, 8192);
}
