// c++ -o compute calibrazione_multigamma.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"


using namespace std;

void computeGraph() {

double sigma[6] = {
	2.25,
	2.16,
	3.28,
	4.02,
	4.31,
	7.22,
};

    double Ch0[6] = {
	254,
	409,
	3540,
	6333,
	7203,
	13610,
};

    double energy[6] = {
	60,
	88,
	662,
	1173,
	1334,
	2505,
};

    double errEnergy[6];

    for (unsigned int i = 0; i < 6; i++) {
	errEnergy[i] = 0;
    }

    TF1 fitFun("fitFun", "[0]+x*[1]", 0, 200000);
    fitFun.SetParameter(0,0.001);
    fitFun.SetParameter(1,0.5);
    gStyle->SetOptFit(1112);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.45);
    TCanvas myCanv2;
    TGraphErrors graph(6, Ch0, energy, sigma, errEnergy);

    graph.SetTitle("Curva calibrazione");
    graph.GetYaxis()->SetTitle("Energia [KeV]");
    graph.GetXaxis()->SetTitle("Canali[V]");
    graph.SetMarkerSize(10);
    graph.Draw("AP");
    graph.Fit("fitFun");
    graph.GetFunction("fitFun")->SetLineColor(9);
    graph.GetFunction("fitFun")->SetParName(0,"q");
    graph.GetFunction("fitFun")->SetParName(1,"m");

    myCanv2.Print("calibrazione_multigamma.pdf", "pdf");

}

int main(int argc, char** argv) {

    computeGraph();

    return 0;
}
