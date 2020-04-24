// c++ -o compute resolutionsources.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"


using namespace std;

void computeGraph() {
	
    ofstream OutFile ("sources_resolution.txt");

//Creo i vettori contenenti FWHM, Picco, HV quelli per contenere gli errori

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

    double errsigma[8] = {
	//NA
	0.25,
	//CO
        0.16,
        0.13,   
	//TH
	0.042,
	0.131,
	0.058,
	0.196,
	0.166,
    };

    double errenergy[8];
    double risoluzione[8];
    double FWHM[8];
    double errRIS[8];

    for (unsigned int i = 0; i < 8; i++) {
	FWHM[i] = 2.35*sigma[i];
	risoluzione[i] = FWHM[i]/Ch0[i];
	errenergy[i] = 0;
	errRIS[i] = sqrt(pow((2.35*errsigma[i])/Ch0[i],2)+pow((FWHM[i]*sigma[i])/(Ch0[i]*Ch0[i]),2));
	OutFile << risoluzione[i] << endl;
    }

    TCanvas myCanv2;
    TGraphErrors graph(8, energy, risoluzione, errenergy, errRIS);

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
    myCanv2.Print("sources_resolution.pdf", "pdf");

}

int main(int argc, char** argv) {

    computeGraph();

    return 0;
}
