// c++ -o compute resolutionHV.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"


using namespace std;

void computeGraph() {
	
    ofstream OutFile ("HV_resolution.txt");

    //Creo i vettori contenenti FWHM, Picco, HV quelli per contenere gli errori
    double FWHM[16] = {
        2.35*6.75,
        2.35*7.14,
        2.35*7.28,
        2.35*7.64,
        2.35*7.70,
        2.35*7.97,
        2.35*8.10,
        2.35*8.25,
        2.35*8.35,
        2.35*8.40,
        2.35*8.24,
        2.35*8.32,
        2.35*8.31,
        2.35*8.45,
        2.35*8.52,
        2.35*8.48,
    };

    double Ch0[16] = {
        1171,
        1274,
        1352,
        1444,
        1502,
        1642,
        1731,
        1843,
        1892,
        1936,
        1965,
        1999,
        1995,
        2006,
        2052,
        2064,
    };

    double errRIS[16];

    double HV[16] = {
        2000,
        2200,
        2400,
        2600,
        2800,
        3000,
        3200,
        3400,
        3600,
        3800,
        4000,
        4200,
        4400,
        4600,
        4800,
        5000,
    };

    double errHV[16];
    double risoluzione[16];

    for (unsigned int i = 0; i < 16; i++) {
        errHV[i] = 0;
	risoluzione[i] = FWHM[i]/Ch0[i];
	errRIS[i] = 0;
	//sqrt(pow((2.35*error)/Ch0[i],2)+pow((FWHM[i]*error)/(Ch0[i]*Ch0[i]),2));
	OutFile << risoluzione[i] << endl;
    }

    TCanvas myCanv2;
    TGraphErrors graph(16, HV, risoluzione, errHV, errRIS);

    TF1 fitFun("fitFun", "sqrt(([0]/x)+([1]*x))", 0, 200000);
    fitFun.SetParameter(0,0.001);
    fitFun.SetParameter(1,0.5);

    graph.SetTitle("Risoluzione in funzione di HV");
    graph.GetYaxis()->SetTitle("Risoluzione");
    graph.GetXaxis()->SetTitle("HV[V]");
    graph.SetMarkerSize(10);
    graph.Fit("fitFun");
    graph.GetFunction("fitFun")->SetLineColor(9);
    graph.GetFunction("fitFun")->SetParName(0,"a");
    graph.GetFunction("fitFun")->SetParName(1,"b");
    graph.Draw("AP");
    myCanv2.Print("resolutionHV.pdf", "pdf");

}

int main(int argc, char** argv) {

    computeGraph();

    return 0;
}
