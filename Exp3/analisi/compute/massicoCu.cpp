// c++ -o compute massicoCu.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"


using namespace std;

void computeGraph() {
	double eTEORICO[41] = {
		1.00E-03*1000,
		1.05E-03*1000,
		1.10E-03*1000,
		1.10E-03*1000,
		1.50E-03*1000,
		2.00E-03*1000,
		3.00E-03*1000,
		4.00E-03*1000,
		5.00E-03*1000,
		6.00E-03*1000,
		8.00E-03*1000,
		8.98E-03*1000,
		8.98E-03*1000,
		1.00E-02*1000,
		1.50E-02*1000,
		2.00E-02*1000,
		3.00E-02*1000,
		4.00E-02*1000,
		5.00E-02*1000,
		6.00E-02*1000,
		8.00E-02*1000,
		1.00E-01*1000,
		1.50E-01*1000,
		2.00E-01*1000,
		3.00E-01*1000,
		4.00E-01*1000,
		5.00E-01*1000,
		6.00E-01*1000,
		8.00E-01*1000,
		1.00E+00*1000,
		1.25E+00*1000,
		1.50E+00*1000,
		2.00E+00*1000,
		3.00E+00*1000,
		4.00E+00*1000,
		5.00E+00*1000,
		6.00E+00*1000,
		8.00E+00*1000,
		1.00E+01*1000,
		1.50E+01*1000,
		2.00E+01*1000
	};

	double muTEORICO[41] = {
		1.06E+04,
		9.31E+03,
		8.24E+03,
		9.35E+03,
		4.42E+03,
		2.15E+03,
		7.49E+02,
		3.47E+02,
		1.90E+02,
		1.16E+02,
		5.26E+01,
		3.83E+01,
		2.78E+02,
		2.16E+02,
		7.41E+01,
		3.38E+01,
		1.09E+01,
		4.86E+00,
		2.61E+00,
		1.59E+00,
		7.63E-01,
		4.58E-01,
		2.22E-01,
		1.56E-01,
		1.12E-01,
		9.41E-02,
		8.36E-02,
		7.63E-02,
		6.61E-02,
		5.90E-02,
		5.26E-02,
		4.80E-02,
		4.21E-02,
		3.60E-02,
		3.32E-02,
		3.18E-02,
		3.11E-02,
		3.07E-02,
		3.10E-02,
		3.25E-02,
		3.41E-02
	};
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
	TGraph teorico(41, eTEORICO, muTEORICO);
    TGraphErrors graph(8, Energy, Massico, err_Energy, err_Massico);

    graph.SetTitle("Coefficiente di attenuazione massico rame");
    graph.GetYaxis()->SetTitle("#mu/#rho [cm^{2}/g]");
    graph.GetXaxis()->SetTitle("Energia [keV]");
    graph.GetYaxis()->SetRangeUser(0, 0.2);
   
    graph.SetMarkerSize(10);
	teorico.SetMarkerSize(0.5);
	teorico.SetMarkerStyle(8);
    graph.Draw("AP");
	teorico.Draw("P SAME");
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
