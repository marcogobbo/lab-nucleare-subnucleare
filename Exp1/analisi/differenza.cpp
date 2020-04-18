// c++ -o compute differenza.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"

using namespace std;

void computeGraph() {
    double deltaEnergia[4] = {
        5442-5388,
        5489-5443,
        5529-5486,
        5563-5545
    };

    double errDeltaEnergia[4] = {
        23.76,
        17.70,
        15.41,
        20.10
    };

    double energiaComputed[4] = {
        5442,
        5489,
        5529,
        5563
    };

    double errEnergiaComputed[4] = {
        0,
        0,
        0,
        0
    };

    TF1 fitFnc("fitFnc2","[0]",0,200000);
    fitFnc.SetParameter(0,35);
    gStyle->SetOptStat("");
    //gStyle->SetOptFit(1112);
    TCanvas myCanv3;
    TGraphErrors graph(4, energiaComputed, deltaEnergia, errEnergiaComputed, errDeltaEnergia);

    graph.SetTitle("Differenza energia calcolata e tabulata in funzione dell'energia calcolata");
    graph.GetYaxis()->SetTitle("Differenza di energia [keV]");
    graph.GetXaxis()->SetTitle("Energia calcolata [keV]");
    graph.SetMarkerSize(2);
    graph.Draw("AP");
    graph.Fit("fitFnc2");
    graph.GetFunction("fitFnc2")->SetLineColor(9);
    graph.GetFunction("fitFnc2")->SetParName(0,"Differenza");
    myCanv3.Print("graphDifferenza.pdf", "pdf");

}

int main(int argc, char** argv) {


    computeGraph();

    return 0;
}