// c++ -o compute ST_resolution.cpp ../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../lib/analyzer.h"


using namespace std;

/*double function (double* x, double* par) {
	return sqrt((par[0]/x[0])+(par[1]*x[0]));	
}*/

void computeGraph() {
	
    ofstream OutFile ("ST_resolution.txt");    
    double FWHM_ST[6] = {
        2.35*5.3,
        2.35*4.4,
        2.35*3.9,
        2.35*4.3,
        2.35*5.2,
        2.35*43.5,
    };

    double Ch0_ST[6] = {
        1259,
	1261,
	1257,
	1279,
	1293,
	1242,
    };

    double errRIS_ST[6];
	
    double err_sigma[6] = {
	0.04,
	0.04,
	0.03,
	0.04,
	0.05,
	0.98,	
    };

    double err_Ch[6] = {
	0.04,
	0.04,
	0.03,
	0.04,
	0.05,
	0.80,	
    };

    double ST[6] = {
        0.5,
        1,
        2,
        3,
        6,
        10,
    };

    double errST[6];
    double risoluzione_ST[6];

    for (unsigned int j = 0; j < 6; j++) {
        errST[j] = 0;
	risoluzione_ST[j] = FWHM_ST[j]/Ch0_ST[j];
	errRIS_ST[j] = sqrt(pow((2.35*err_sigma[j])/Ch0_ST[j],2)+pow((FWHM_ST[j]*err_Ch[j])/(Ch0_ST[j]*Ch0_ST[j]),2));
	OutFile << risoluzione_ST[j] << endl;
    }

    TCanvas myCanv2;
    TGraphErrors graph(6, ST, risoluzione_ST, errST, errRIS_ST);

    TF1 fitFun("fitFun", "sqrt(([0]/x)+([1]*x))", 0, 200000);
    fitFun.SetParameter(0,0.001);
    fitFun.SetParameter(1,0.5);

    graph.SetTitle("Risoluzione in funzione di ST");
    graph.GetYaxis()->SetTitle("Risoluzione");
    graph.GetXaxis()->SetTitle("ST[micros]");
    graph.SetMarkerSize(10);
    graph.Fit("fitFun");
    graph.GetFunction("fitFun")->SetLineColor(9);
    graph.GetFunction("fitFun")->SetParName(0,"a");
    graph.GetFunction("fitFun")->SetParName(1,"b");
    graph.Draw("AP");
    myCanv2.Print("resolutionST.pdf", "pdf");

}

int main(int argc, char** argv) {

    computeGraph();

    return 0;
}
