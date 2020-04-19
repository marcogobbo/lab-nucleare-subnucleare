// c++ -o compute HV_resolution.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"


using namespace std;

/*double function (double* x, double* par) {
	return sqrt((par[0]/x[0])+(par[1]*x[0]));	
}*/

void computeGraph() {
	
    ofstream OutFile ("HV_resolution.txt");
    double FWHM[16] = {
        2.35*7.3,
        2.35*7.1,
        2.35*6.9,
        2.35*6.8,
        2.35*6.6,
        2.35*6.2,
        2.35*5.9,
        2.35*5.6,
        2.35*5.5,
        2.35*5.4,
        2.35*5.3,
        2.35*5.2,
        2.35*5.2,
        2.35*5.2,
        2.35*5.1,
        2.35*5.1,
    };

    double Ch0[16] = {
        1255,
        1255,
        1255,
        1256,
        1256,
        1257,
        1258,
        1258,
        1258,
        1259,
        1259,
        1259,
        1259,
        1260,
        1260,
        1260,
    };

    double errRIS[16];
    double error = 0.1;

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
	errRIS[i] = sqrt(pow((2.35*error)/Ch0[i],2)+pow((FWHM[i]*error)/(Ch0[i]*Ch0[i]),2));
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
