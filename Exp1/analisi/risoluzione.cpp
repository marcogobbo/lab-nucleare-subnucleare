// c++ -o compute risoluzione.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"


using namespace std;

double function (double* x, double* par) {
	return par[0]/(sqrt(x[0]));	
}

void computeGraph() {
	
    ofstream OutFile ("risoluzioni.txt");
    double FWHM[4] = {
        2.35*17,
        2.35*12,
        2.35*10,
        2.35*14
    };

    double errFWHM[4];

    double picco[4] = {
        3970,
        4006,
        4036,
        4062
    };
    double energie[4] = {
        5441,
        5489,
        5528,
        5561
    };
    double errEnergia[4] = {
        7.96,
        7.98,
        7.99,
        8.01
    };
    double risoluzione[4];
    double risoluzioneenergetica[4];

    for (unsigned int i = 0; i < 4; i++) {
        errFWHM[i] = 0;
	risoluzione[i] = FWHM[i]/picco[i];
	risoluzioneenergetica[i] = risoluzione[i]*energie[i];
	OutFile << risoluzione[i] << endl;
	
	
    }

    OutFile << "La risoluzione energetica dei picchi è:" << endl;
    for (unsigned int i = 0; i < 4; i++) {
	OutFile << risoluzioneenergetica[i] << endl;
	
    }

    TCanvas myCanv2;
    TGraphErrors graph(4, energie, risoluzioneenergetica, errEnergia, errFWHM);

    graph.SetTitle("Risoluzione relativa");
    graph.GetYaxis()->SetTitle("Risoluzione in energia [keV]");
    graph.GetXaxis()->SetTitle("Picchi energia [keV]");
    graph.SetMarkerSize(10);
    graph.Draw("AP");
    myCanv2.Print("risoluzione.pdf", "pdf");

}

int main(int argc, char** argv) {

    computeGraph();

    return 0;
}
