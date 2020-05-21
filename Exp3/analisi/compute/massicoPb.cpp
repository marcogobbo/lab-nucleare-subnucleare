// c++ -o compute massicoPb.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

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
	,
	,
	//Co
	,
	,
	//Th
	,
	,
	,
};

    double err_Mu[8] = {
	//Na
	,
	,
	//Co
	,
	,
	//Th
	,
	,
	,
}
    double Rho = 8.96;
    double Mu/Rho[8];
    double err_Mu/rho[8];
    double err_Energy[8];
    for (unsigned int i = 0; i < 8; i++) {
	Mu/Rho[i] = Mu[i]/Rho;
	err_Mu/Rho[i] = err_Mu[i]/Rho;
	err_Energy[i] = 0;
    }

    TF1 fitFun("fitFun", "[0]/(x^3.5) + [1]/x", 0, 200000);
    fitFun.SetParameter(0,);
    fitFun.SetParameter(1,);

    gStyle->SetOptFit(1112);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.9);

    TCanvas myCanv2;

    TGraphErrors graph(8, Energy, Mu/Rho, err_Energy, err_Mu/Rho);

    graph.SetTitle("Coefficiente di attenuazione massico piombo");
    graph.GetYaxis()->SetTitle("Attenuazione massico [cm^2/g]");
    graph.GetXaxis()->SetTitle("Energia [KeV]");
   
    graph.SetMarkerSize(10);
    graph.Draw("AP");
    graph.Fit("fitFun");
    graph.GetFunction("fitFun")->SetLineColor(9);
    graph.GetFunction("fitFun")->SetParName(0,"a");
    graph.GetFunction("fitFun")->SetParName(1,"b");

    myCanv2.Print("../graphs/massicoPb.pdf");

}

int main(int argc, char** argv) {

    computeGraph();

    return 0;
}
