#include "lib/analyzer.h"

using namespace std;

double function (double* x, double* par) {
	return par[0]/(sqrt(x[0]));	
}

void computeGraph() {
    double FWHM[4] = {
        2.35*17,
        2.35*12,
        2.35*10,
        2.35*14
    };

    double errFWHM[4];

    double picco[4] = {
        5388,
        5443,
        5486,
        5545
    };
    double errTensione[4] = {
        17,
        12,
        10,
        14
    };
    double risoluzione[4];

    for (unsigned int i = 0; i < 4; i++) {
        errFWHM[i] = 0;
	risoluzione[i] = FWHM[i]/picco[i];
    }

    TCanvas myCanv2;
    TGraphErrors graph(4, picco, risoluzione, errTensione, errFWHM);

    graph.SetTitle("Risoluzione impulsatore");
    graph.GetYaxis()->SetTitle("Risoluzione");
    graph.GetXaxis()->SetTitle("Picco [KeV]");
    graph.SetMarkerSize(2);
    graph.Draw("AP");
    myCanv2.Print("risoluzione.pdf", "pdf");

}

int main(int argc, char** argv) {

    computeGraph();

    return 0;
}
