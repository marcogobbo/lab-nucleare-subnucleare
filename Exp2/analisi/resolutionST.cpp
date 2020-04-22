// c++ -o compute resolutionST.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"


using namespace std;

void computeGraph() {
	
    ofstream OutFile ("ST_resolution.txt");

//Creo i vettori contenenti FWHM, Picco, HV quelli per contenere gli errori

double sigma[5] = {
        5.39,
        4.04,
        3.70,
        3.99,
        4.62,
    };

    double Ch0[5] = {
        1259,
        1261,
        1256,
        1279,
        1292,
    };

    double ST[] = {
        5,
        10,
        20,
        30,
        60,
};

    double errsigma[5] = {
        0.011,
        0.013,
        0.013,
        0.013,
        0.014,
    };

    double errST[5];
    double risoluzione[5];
    double FWHM[5];
    double errRIS[5];

    for (unsigned int i = 0; i < 5; i++) {
	FWHM[i] = 2.35*sigma[i];
	risoluzione[i] = FWHM[i]/Ch0[i];
	errST[i] = 0;
	errRIS[i] = sqrt(pow((2.35*errsigma[i])/Ch0[i],2)+pow((FWHM[i]*sigma[i])/(Ch0[i]*Ch0[i]),2));
	OutFile << risoluzione[i] << endl;
    }

    TCanvas myCanv2;
    TGraphErrors graph(5, ST, risoluzione, errST, errRIS);

    TF1 fitFun("fitFun", "sqrt(([0]/x)+([1]*x))", 0, 200000);
    fitFun.SetParameter(0,0.001);
    fitFun.SetParameter(1,0.5);

    graph.SetTitle("Risoluzione in funzione di ST");
    graph.GetYaxis()->SetTitle("Risoluzione");
    graph.GetXaxis()->SetTitle("ST[micros]");
    graph.SetMarkerSize(10);
    graph.Fit("fitFun");
    graph.GetFunction("fitFun")->SetLineColor(9);
    graph.GetFunction("fitFun")->SetParName(0.5,"a");
    graph.GetFunction("fitFun")->SetParName(2,"b");
    graph.Draw("AP");
    myCanv2.Print("resolutionST.pdf", "pdf");

}

int main(int argc, char** argv) {

    computeGraph();

    return 0;
}
