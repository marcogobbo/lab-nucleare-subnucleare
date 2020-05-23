// c++ -o compute massicoAcqua.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"


using namespace std;

void computeGraph() {
	double eTEORICO[36] = {
		1.00E-03*1000,
		1.50E-03*1000,
		2.00E-03*1000,
		3.00E-03*1000,
		4.00E-03*1000,
		5.00E-03*1000,
		6.00E-03*1000,
		8.00E-03*1000,
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

	double muTEORICO[36] = {
		4.08E+03,
		1.38E+03,
		6.17E+02,
		1.93E+02,
		8.28E+01,
		4.26E+01,
		2.46E+01,
		1.04E+01,
		5.33E+00,
		1.67E+00,
		8.10E-01,
		3.76E-01,
		2.68E-01,
		2.27E-01,
		2.06E-01,
		1.84E-01,
		1.71E-01,
		1.51E-01,
		1.37E-01,
		1.19E-01,
		1.06E-01,
		9.69E-02,
		8.96E-02,
		7.87E-02,
		7.07E-02,
		6.32E-02,
		5.75E-02,
		4.94E-02,
		3.97E-02,
		3.40E-02,
		3.03E-02,
		2.77E-02,
		2.43E-02,
		2.22E-02,
		1.94E-02,
		1.81E-02
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
	0.0925,
	0.064,
	//Co
	0.0623,
	0.0668,
	//Th
	0.103,
	0.0728,
	0.0359,
};

    double err_Mu[8] = {
	//Na
	0.001,
	0.002,
	//Co
	0.001,
	0.001,
	//Th
	0.007,
	0.005,
	0.01,
};

    double err_Energy[8];
    for (unsigned int i = 0; i < 8; i++) {
	err_Energy[i] = 0;
    }

    TF1 fitFun("fitFun", "[0]/x", 0, 200000);
    //fitFun.SetParameter(0,);
    //fitFun.SetParameter(1,);

    gStyle->SetOptFit(1112);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.9);

    TCanvas myCanv2;
	TGraph teorico(36, eTEORICO, muTEORICO);
    TGraphErrors graph(8, Energy, Mu, err_Energy, err_Mu);

    graph.SetTitle("Coefficiente di attenuazione massico acqua");
    graph.GetYaxis()->SetTitle("#mu/#rho [cm^{2}/g]");
    graph.GetXaxis()->SetTitle("Energia [keV]");
   
    graph.SetMarkerSize(10);
	teorico.SetMarkerSize(0.5);
	teorico.SetMarkerStyle(8);
    graph.Draw("AP");
	teorico.Draw("P SAME");
    graph.Fit("fitFun");
	graph.GetFunction("fitFun")->SetLineColor(9);
    graph.GetFunction("fitFun")->SetParName(0, "a");
    //graph.GetFunction("fitFun")->SetParName(1, "b");

    myCanv2.Print("../graphs/massicoAcqua.pdf");

}

int main(int argc, char** argv) {

    computeGraph();

    return 0;
}
