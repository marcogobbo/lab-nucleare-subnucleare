// c++ -o compute spectreST.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"

using namespace std;

double gaussFit (double* x, double* par) {
  	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

double pol0 (double*x, double* par) {
    return par[0];
}

double totalFit (double* x, double* par) {
    return gaussFit(x, par) + pol0(x, &par[3]) + gaussFit(x, &par[4]);
}

void computeHisto (string valueST, int bin, double limInf, double limSup) {
    Analyzer ST;
    string fileName = "data/HPGe-ShapingTime/" + valueST + ".dat";

    // Creo il vettore dove salvare i dati, min e max
    vector<double> data;
    double min, max;

    // Carico i dati controllando che non via siano errori
    if (ST.loadData(fileName, data, min, max) == false) {
        cout << "Errore nel caricare il file: " << fileName.c_str() << endl;
    };

    // Imposto il numero di bin
    int nBin = bin;

    gStyle->SetOptFit(1112);
    
    TString titleGraph = "ST: " + valueST + "micros";
    TString namePDF = "graphs/spectreST/graph_ST" + valueST + ".pdf";

    TH1D* histoST = new TH1D("Data", titleGraph, nBin, 0, 8192);

    for (unsigned int i = 0; i < data.size(); i++) {
        histoST->SetBinContent(i, data[i]);
    }

    TCanvas* canvasST = new TCanvas("canvasST", "canvasST", 0, 0, 800, 500);

    canvasST->cd();

    histoST->Draw();
    histoST->SetFillColor(kYellow-10);
    histoST->GetXaxis()->SetTitle("Channels [mV]");
    histoST->GetYaxis()->SetTitle("Counts");
    histoST->GetXaxis()->SetRangeUser(limInf, limSup);

    /*TF1* funcFit = new TF1("funcFit", totalFit, limInf, limSup, 4);
    funcFit->SetParName(0,"Amp");
    funcFit->SetParName(1,"Mean");
    funcFit->SetParName(2,"Std Dev");
    funcFit->SetParName(3,"Noise");
    funcFit->SetParName(4,"Amp Pile-Up");
    funcFit->SetParName(5,"Mean Pile-Up");
    funcFit->SetParName(6,"Std Dev Pile-Up");

    // Blocco da sostituire con i dati presenti in parFitSpectreST.txt
    //INIZIO
    funcFit->SetParameter(0, 13500);
    funcFit->SetParameter(1, 1258);
    funcFit->SetParameter(2, 10);
    funcFit->SetParameter(3, 100);*/
    /*funcFit->SetParameter(4, 1100);
    funcFit->SetParameter(5, 1275);
    funcFit->SetParameter(6, 20);*/

    /*funcFit->SetParLimits(0, , );
    funcFit->SetParLimits(5, , );
    funcFit->SetParLimits(6, , );*/
    // FINE


    //histoST->Fit("funcFit");

    canvasST->Print(namePDF);

    // Libero la memoria
    delete histoST;
    //delete funcFit;
    delete canvasST;
}


int main() {
    //computeHisto("005", 8192, 1170, 1350);
    //computeHisto("010", 8192, 1170, 1350);
    //computeHisto("020", 8192, 1220, 1300);
    //computeHisto("030", 8192, 1170, 1400);
    //computeHisto("060", 8192, 1200, 1400);
    computeHisto("100", 8192, 0, 8192);
}
