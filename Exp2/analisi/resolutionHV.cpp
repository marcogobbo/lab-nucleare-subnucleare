// c++ -o compute resolutionHV.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"


using namespace std;

void computeGraph() {
	
    ofstream OutFile ("HV_resolution.txt");

    //Creo i vettori contenenti FWHM, Picco, HV quelli per contenere gli errori

double sigma[16] = {
        7.22,
        7.03,
        6.79,
        6.66,
        6.48,
        6.13,
        5.91,
        5.63,
        5.55,
        5.46,
        5.32,
        5.30,
        5.29,
        5.23,
        5.29,
        5.19,
    };

    double Ch0[16] = {
        1254,
        1255,
        1255,
        1255,
        1255,
        1256,
        1257,
        1257,
        1258,
        1258,
        1258,
        1259,
        1259,
        1259,
        1259,
        1260,
    };

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

    double errsigma[16] = {
        0.017,
        0.016,
        0.015,
        0.014,
        0.014,
        0.013,
        0.012,
        0.012,
        0.012,
        0.011,
        0.011,
        0.011,
        0.011,
        0.010,
        0.011,
        0.010,
    };

    double errHV[16];
    double risoluzione[16];
    double FWHM[16];
    double errRIS[16];

    for (unsigned int i = 0; i < 16; i++) {
	FWHM[i] = 2.35*sigma[i];
	risoluzione[i] = FWHM[i]/Ch0[i];
	errHV[i] = 0;
	errRIS[i] = sqrt(pow((2.35*errsigma[i])/Ch0[i],2)+pow((FWHM[i]*sigma[i])/(Ch0[i]*Ch0[i]),2));
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
