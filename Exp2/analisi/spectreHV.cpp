// c++ -o compute spectreHV.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

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

void computeHisto (string valueHV, int bin, double limInf, double limSup) {
    Analyzer HV;
    string fileName = "data/HPGe-Bias/" + valueHV + ".dat";

    // Creo il vettore dove salvare i dati, min e max
    vector<double> data;
    double min, max;

    // Carico i dati controllando che non via siano errori
    if (HV.loadData(fileName, data, min, max) == false) {
        cout << "Errore nel caricare il file: " << fileName.c_str() << endl;
    };

    // Imposto il numero di bin
    int nBin = bin;

    gStyle->SetOptFit(1112);
    
    TString titleGraph = "HV: " + valueHV + "V";
    TString namePDF = "graphs/spectreHV/graph_HV" + valueHV + ".pdf";

    TH1D* histoHV = new TH1D("Data", titleGraph, nBin, 0, 8192);

    for (unsigned int i = 0; i < data.size(); i++) {
        histoHV->SetBinContent(i, data[i]);
    }

    TCanvas* canvasHV = new TCanvas("canvasHV", "canvasHV", 0, 0, 800, 500);

    canvasHV->cd();

    histoHV->Draw();
    histoHV->SetFillColor(kYellow-10);
    histoHV->GetXaxis()->SetTitle("Channels [mV]");
    histoHV->GetYaxis()->SetTitle("Counts");
    histoHV->GetXaxis()->SetRangeUser(limInf, limSup);

    TF1* funcFit = new TF1("funcFit", totalFit, limInf, limSup, 4);
    funcFit->SetParName(0,"Amp");
    funcFit->SetParName(1,"Mean");
    funcFit->SetParName(2,"Std Dev");
    funcFit->SetParName(3,"Noise");
    funcFit->SetParameter(0, 7800);
    funcFit->SetParameter(1, 1250);
    funcFit->SetParameter(2, 10);
    funcFit->SetParameter(4, 150);

    histoHV->Fit("funcFit");

    canvasHV->Print(namePDF);

    // Libero la memoria
    delete histoHV;
    delete funcFit;
    delete canvasHV;
}


int main() {
    computeHisto("2000", 8192, 1150, 1350);
}