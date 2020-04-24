// c++ -o compute curvacalibrazione.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"


using namespace std;

void computeGraph() {

double sigma[8] = {
	//NA
        2.77,
	//CO
        2.96,
        3.07,
	//TH
	2.35,
	2.62,
	2.28,
	2.45,
	3.54,
    };

    double Ch0[8] = {
	//NA
        3261,
	//CO
        2996,
        3412,
	//TH
	553,
	1265,
	1454,
	1831,
	6757,
};

    double energy[8] = {
	//NA
        1274.53,
	//CO
        1173.24,
        1332.50,
	//TH
	238.6,
	510.77,
	583.91,
	727.53,
	2614.53,
};

    double errEnergy[8];

    for (unsigned int i = 0; i < 8; i++) {
	errEnergy[i] = 0;
    }

    TF1 fitFun("fitFun", "[0]+x*[1]", 0, 200000);
    fitFun.SetParameter(0,0.001);
    fitFun.SetParameter(1,0.5);
    gStyle->SetOptFit(1112);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.45);
    TCanvas myCanv2;
    TGraphErrors graph(8, Ch0, energy, sigma, errEnergy);

    graph.SetTitle("Curva calibrazione");
    graph.GetYaxis()->SetTitle("Energia [KeV]");
    graph.GetXaxis()->SetTitle("Canali[V]");
    graph.SetMarkerSize(10);
    graph.Draw("AP");
    graph.Fit("fitFun");
    graph.GetFunction("fitFun")->SetLineColor(9);
    graph.GetFunction("fitFun")->SetParName(0,"q");
    graph.GetFunction("fitFun")->SetParName(1,"m");

    myCanv2.Print("curvacalibrazione.pdf", "pdf");

}

int main(int argc, char** argv) {

    computeGraph();

    return 0;
}
