// c++ -o compute spectreHV.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"

using namespace std;

double gauss(double* x, double* par)	{
  	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

void computeGraph(string valueHV, double limInf, double limSup) {
    Analyzer HV;
    string fileName = "data/HPGe-Bias/" + valueHV + ".dat";

    // Creo il vettore dove salvare i dati, min e max
    vector<double> data;
    double counts[8192], channels[8192];
    double min, max;

    // Carico i dati controllando che non via siano errori
    if (HV.loadData(fileName, data, min, max) == false) {
        cout << "Errore nel caricare il file: " << fileName.c_str() << endl;
    };

    for (unsigned int i = 0; i < 8192; i++) {
        counts[i] = data[i];
        channels[i] = i;
    }
    gStyle->SetOptFit(1112);
    TCanvas graphHV;
    TGraph graph(5000, channels, counts);
    TString titleGraph = "HV: " + valueHV + "V";
    graph.SetTitle(titleGraph);
    graph.GetYaxis()->SetTitle("Conteggi");
    graph.GetXaxis()->SetTitle("Canali [V]");
    graph.SetMarkerSize(2);
    graph.GetXaxis()->SetLimits(limInf,limSup);

    TF1 gaussFit("gauss", gauss, limInf, limSup, 3);
    gaussFit.SetParameter(1, 1255);
    gaussFit.SetParameter(2, 50);
    gaussFit.SetParName(0,"Ampiezza");
    gaussFit.SetParName(1,"Media");
    gaussFit.SetParName(2,"Dev Std");
    graph.Fit("gauss");
    graph.Draw("AP");

    TString namePDF = "graphs/spectreHV/graph_HV" + valueHV + ".pdf";
    graphHV.Print(namePDF);

}


int main() {
    for (int i = 2000; i < 5200; i += 200) {
        computeGraph(to_string(i), 1200, 1300);
    }
}