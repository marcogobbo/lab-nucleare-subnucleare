// c++ -o compute spectreUW878.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"

using namespace std;

double gauss(double* x, double* par)	{
  	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

void computeGraph(double limInf, double limSup) {
    Analyzer UW878;
    string fileName = "data/Calibration/UW878.txt";

    // Creo il vettore dove salvare i dati, min e max
    vector<double> data;
    double counts[16384], channels[16384];
    double min, max;

    // Carico i dati controllando che non via siano errori
    if (UW878.loadData(fileName, data, min, max) == false) {
        cout << "Errore nel caricare il file: " << fileName.c_str() << endl;
    };

    for (unsigned int i = 0; i < 16384; i++) {
        counts[i] = data[i];
        channels[i] = i;
    }
    gStyle->SetOptFit(1112);
    TCanvas graphUW878;
    TGraph graph(16384, channels, counts);
    TString titleGraph = "UW878";
    graph.SetTitle(titleGraph);
    graph.GetYaxis()->SetTitle("Conteggi");
    graph.GetXaxis()->SetTitle("Canali [V]");
    graph.SetMarkerSize(2);
    graph.GetXaxis()->SetLimits(limInf,limSup);

    TF1 gaussFit("gauss", gauss, limInf, limSup, 3);
    gaussFit.SetParameter(1, 7200);
    gaussFit.SetParameter(2, 10);
    gaussFit.SetParName(0,"Ampiezza");
    gaussFit.SetParName(1,"Media");
    gaussFit.SetParName(2,"Dev Std");
    graph.Fit("gauss");
    graph.Draw("AP");

    TString namePDF = "graphs/spectreUW878/graph_UW878.pdf";
    graphUW878.Print(namePDF);

}

void computeGraphCalib() {
    double channel[4] = {
        254.5,
        3541,
        6334,
        7203
    };

    double errChannel[4] = {
        2.3,
        3,
        4,
        4
    };

    double energy[4] = {

    };
}


int main() {
    computeGraph(0, 1000);
    //computeGraphCalib();
}