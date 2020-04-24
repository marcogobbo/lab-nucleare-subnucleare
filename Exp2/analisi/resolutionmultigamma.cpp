// c++ -o compute resolutionmultigamma.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"


using namespace std;

void computeGraph() {
	
    ofstream OutFile ("multigamma_resolution.txt");

//Creo i vettori contenenti FWHM, Picco, HV quelli per contenere gli errori

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

    double errsigma[6] = {
	0.1,
	0.1,
	0.1,
	0.2,
	0.2,
	1,
    };

    double errenergy[6];
    double risoluzione[6];
    double FWHM[6];
    double errRIS[6];

    for (unsigned int i = 0; i < 6; i++) {
	FWHM[i] = 2.35*sigma[i];
	risoluzione[i] = FWHM[i]/Ch0[i];
	errenergy[i] = 0;
	errRIS[i] = sqrt(pow((2.35*errsigma[i])/Ch0[i],2)+pow((FWHM[i]*sigma[i])/(Ch0[i]*Ch0[i]),2));
	OutFile << risoluzione[i] << endl;
    }

    TCanvas myCanv2;
    TGraphErrors graph(6, energy, risoluzione, errenergy, errRIS);

    TF1 fitFun("fitFun", "sqrt(([0]*[0]/x)+([1]*[1])+([2]*[2]/(x*x)))", 0, 200000);
    fitFun.SetParameter(0,0.01);
    fitFun.SetParameter(1,0.01);
    fitFun.SetParameter(2,1.0);
    gStyle->SetOptFit(1112);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.45);

    graph.SetTitle("Risoluzione in funzione di E");
    graph.GetYaxis()->SetTitle("Risoluzione");
    graph.GetXaxis()->SetTitle("Energia[KeV]");
    graph.SetMarkerSize(10);
    graph.Fit("fitFun");
    graph.GetFunction("fitFun")->SetLineColor(9);
    graph.GetFunction("fitFun")->SetParName(0,"a");
    graph.GetFunction("fitFun")->SetParName(1,"b");
    graph.GetFunction("fitFun")->SetParName(2,"c");
    graph.Draw("AP");
    myCanv2.Print("multigamma_resolution.pdf", "pdf");

}

int main(int argc, char** argv) {

    computeGraph();

    return 0;
}
