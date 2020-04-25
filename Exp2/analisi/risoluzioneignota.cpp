// c++ -o compute risoluzioneignota.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"


using namespace std;

void computeGraph() {
	
    ofstream OutFile ("risoluzione_sorgente_ignota.txt");

    double sigma[15] = {
	2.5,
	2.5,
	3.1,
	2.5,
	2.7,
	2.5,
	2.8,
	3.1,
	2.9,
	2.9,
	3.3,
	3.8,
	3.9,
	3.9,
	6.0,
};

    double Ch0[15] = {
	337.6,
	349.9,
	389.9,
	633.4,
	1232,
	1244,
	1404,
	1443,
	1567,
	1775,
	3111,
	4902,
	5195,
	5218,
	14200,
};

    double energy[15] = {
	75.20,
	77.45,
	84.78,
	129.39,
	239.05,
	241.25,
	270.56,
	277.71,
	300.42,
	338.53,
	583.29,
	911.40,
	965.07,
	969.29,
	2614.79,
};

    double errsigma[15] = {
	0.031,
	0.020,
	0.097,
	0.047,
	0.009,
	0.035,
	0.050,
	0.080,
	0.052,
	0.023,
	0.020,
	0.025,
	0.076,
	0.038,
	0.062
};

    double errenergy[15];
    double risoluzione[15];
    double FWHM[15];
    double errRIS[15];

    for (unsigned int i = 0; i < 15; i++) {
	FWHM[i] = 2.35*sigma[i];
	risoluzione[i] = FWHM[i]/Ch0[i];
	errenergy[i] = 0;
	errRIS[i] = sqrt(pow((2.35*errsigma[i])/Ch0[i],2)+pow((FWHM[i]*sigma[i])/(Ch0[i]*Ch0[i]),2));
	OutFile << risoluzione[i] << endl;
    }

    TCanvas myCanv2;
    TGraphErrors graph(15, energy, risoluzione, errenergy, errRIS);

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
    myCanv2.Print("risoluzione_ignota.pdf", "pdf");

}

int main(int argc, char** argv) {

    computeGraph();

    return 0;
}
