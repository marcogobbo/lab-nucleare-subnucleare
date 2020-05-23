// c++ -o compute massicoPb.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"


using namespace std;

void computeGraph() {
	double eTEORICO[58] = {
		1.00E-03*1000,
		1.50E-03*1000,
		2.00E-03*1000,
		2.48E-03*1000,
		2.48E-03*1000,
		2.53E-03*1000,
		2.59E-03*1000,
		2.59E-03*1000,
		3.00E-03*1000,
		3.07E-03*1000,
		3.07E-03*1000,
		3.30E-03*1000,
		3.55E-03*1000,
		3.55E-03*1000,
		3.70E-03*1000,
		3.85E-03*1000,
		3.85E-03*1000,
		4.00E-03*1000,
		5.00E-03*1000,
		6.00E-03*1000,
		8.00E-03*1000,
		1.00E-02*1000,
		1.30E-02*1000,
		1.30E-02*1000,
		1.50E-02*1000,
		1.52E-02*1000,
		1.52E-02*1000,
		1.55E-02*1000,
		1.59E-02*1000,
		1.59E-02*1000,
		2.00E-02*1000,
		3.00E-02*1000,
		4.00E-02*1000,
		5.00E-02*1000,
		6.00E-02*1000,
		8.00E-02*1000,
		8.80E-02*1000,
		8.80E-02*1000,
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

	double muTEORICO[58] = {
		5.21E+03,
		2.36E+03,
		1.29E+03,
		8.01E+02,
		1.40E+03,
		1.73E+03,
		1.94E+03,
		2.46E+03,
		1.97E+03,
		1.86E+03,
		2.15E+03,
		1.80E+03,
		1.50E+03,
		1.59E+03,
		1.44E+03,
		1.31E+03,
		1.37E+03,
		1.25E+03,
		7.30E+02,
		4.67E+02,
		2.29E+02,
		1.31E+02,
		6.70E+01,
		1.62E+02,
		1.12E+02,
		1.08E+02,
		1.49E+02,
		1.42E+02,
		1.34E+02,
		1.55E+02,
		8.64E+01,
		3.03E+01,
		1.44E+01,
		8.04E+00,
		5.02E+00,
		2.42E+00,
		1.91E+00,
		7.68E+00,
		5.55E+00,
		2.01E+00,
		9.99E-01,
		4.03E-01,
		2.32E-01,
		1.61E-01,
		1.25E-01,
		8.87E-02,
		7.10E-02,
		5.88E-02,
		5.22E-02,
		4.61E-02,
		4.23E-02,
		4.20E-02,
		4.27E-02,
		4.39E-02,
		4.68E-02,
		4.97E-02,
		5.66E-02,
		6.21E-02
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
	1.59,
	0.326,
	//Co
	0.488,
	0.435,
	//Th
	7.2,
	1.69,
	0.784,
};

    double err_Mu[8] = {
	//Na
	0.012,
	0.006,
	//Co
	0.008,
	0.008,
	//Th
	0.2,
	0.03,
	0.04,
};
    double Rho = 11.34;
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
	TGraph teorico(58, eTEORICO, muTEORICO);
    TGraphErrors graph(8, Energy, Massico, err_Energy, err_Massico);

    graph.SetTitle("Coefficiente di attenuazione massico piombo");
    graph.GetYaxis()->SetTitle("#mu/#rho [cm^{2}/g]");
    graph.GetXaxis()->SetTitle("Energia [keV]");
   
    graph.SetMarkerSize(10);
	teorico.SetMarkerSize(0.5);
	teorico.SetMarkerStyle(8);
    graph.Draw("AP");
	teorico.Draw("P SAME");
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
