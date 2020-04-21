// c++ -o compute multigamma.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

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

void computeHisto(string value, int bin, double limInf, double limSup, double parFit0, double parFit1, double parFit2, double parFit3) {
    Analyzer gamma;
    string fileName = "data/Calibration/" + value + ".txt";

    // Creo il vettore dove salvare i dati, min e max
    vector<double> data;
    double min, max;

    // Carico i dati controllando che non via siano errori
    if (gamma.loadData(fileName, data, min, max) == false) {
        cout << "Errore nel caricare il file: " << fileName.c_str() << endl;
    };

    // Imposto il numero di bin
    int nBin = bin;

    gStyle->SetOptFit(1112);
    
    TString titleGraph = "Sorgente multigamma";
    TString namePDF = "graphs/MultiGamma/graph_" + value + ".pdf";

    TH1D* histo = new TH1D("Data", titleGraph, nBin, min, max);

    for (unsigned int i = 0; i < data.size(); i++) {
        histo->SetBinContent(i, data[i]);
    }

    TCanvas* canvas = new TCanvas("canvasHV", "canvasHV", 0, 0, 800, 500);

    canvas->cd();

    histo->Draw();
    histo->SetFillColor(kYellow-10);
    histo->GetXaxis()->SetTitle("Channels [mV]");
    histo->GetYaxis()->SetTitle("Counts");
    histo->GetXaxis()->SetRangeUser(limInf, limSup);

    TF1* funcFit = new TF1("funcFit", totalFit, limInf, limSup, 4);
    funcFit->SetParName(0,"Amp");
    funcFit->SetParName(1,"Mean");
    funcFit->SetParName(2,"Std Dev");
    funcFit->SetParName(3,"Noise");
    funcFit->SetParameter(0, parFit0);
    funcFit->SetParameter(1, parFit1);
    funcFit->SetParameter(2, parFit2);
    funcFit->SetParameter(4, parFit3);

    histo->Fit("funcFit");

    canvas->Print(namePDF);

    // Libero la memoria
    delete histo;
    delete funcFit;
    delete canvas;
}


int main() {
    computeHisto("UW878", 8192, 0, 17000, 0, 0, 0, 0);
}
