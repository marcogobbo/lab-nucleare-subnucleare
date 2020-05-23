// c++ -o compute massicoCu.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"


using namespace std;

void computeGraph() {

    double Energy[8] = {
	//Na
	511,
	1274,
	//Co
	1173,
	1332,
	//Th
	238,
	583,
	2614,
};

    double Mu[8] = {
	//Na
	0.73,
	0.301,
	//Co
	0.403,
	0.352,
	//Th
	1.74,
	1.13,
	0.872,
};

    double err_Mu[8] = {
	//Na
	0.013,
	0.014,
	//Co
	0.015,
	0.016,
	//Th
	0.04,
	0.05,
	0.08,
};

    double Rho = 8.96;
    double Massico[8];
    double err_Massico[8];
    double err_Energy[8];
    for (unsigned int i = 0; i < 8; i++) {
	Massico[i] = Mu[i]/Rho;
	err_Massico[i] = err_Mu[i]/Rho;
	err_Energy[i] = 0;
    }

    TF1 fitFun("fitFun", "[0]/(x^3.5) + [1]/x", 0, 200000);
    //fitFun.SetParameter(0,);
    //fitFun.SetParameter(1,);

    gStyle->SetOptFit(1112);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.9);

    TCanvas myCanv2;

    TGraphErrors graph(8, Energy, Massico, err_Energy, err_Massico);

    graph.SetTitle("Coefficiente di attenuazione massico rame");
    graph.GetYaxis()->SetTitle("#mu/#rho [cm^{2}/g]");
    graph.GetXaxis()->SetTitle("Energia [keV]");
    graph.GetYaxis()->SetRangeUser(0, 0.2);
   
    graph.SetMarkerSize(10);
    graph.Draw("AP");
    graph.Fit("fitFun");
    graph.GetFunction("fitFun")->SetLineColor(9);
    graph.GetFunction("fitFun")->SetParName(0,"a");
    graph.GetFunction("fitFun")->SetParName(1,"b");

    myCanv2.Print("../graphs/massicoCu.pdf");

}

int main(int argc, char** argv) {

    computeGraph();

    return 0;
}
