// c++ -o compute spectreST.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"

using namespace std;

double gauss(double* x, double* par)	{
  	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

void computeGraph(string valueST, double limInf, double limSup) {
    Analyzer ST;
    string fileName = "data/HPGe-ShapingTime/" + valueST + ".dat";

    // Creo il vettore dove salvare i dati, min e max
    vector<double> data;
    double counts[8192], channels[8192];
    double min, max;

    // Carico i dati controllando che non via siano errori
    if (ST.loadData(fileName, data, min, max) == false) {
        cout << "Errore nel caricare il file: " << fileName.c_str() << endl;
    };

    for (unsigned int i = 0; i < 8192; i++) {
        counts[i] = data[i];
        channels[i] = i;
    }
    gStyle->SetOptFit(1112);
    TCanvas graphST;
    TGraph graph(8192, channels, counts);
    TString titleGraph = "ST: " + valueST + "μs";
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

    TString namePDF = "graphs/spectreST/graph_ST" + valueST + ".pdf";
    graphST.Print(namePDF);

}


int main() {
    for (int i = 0; i < 6; i ++) {
        computeGraph(to_string(i), 1200, 1400);
    }
}
