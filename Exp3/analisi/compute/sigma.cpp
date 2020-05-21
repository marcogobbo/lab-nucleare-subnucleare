// c++ -o compute sigma.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"


using namespace std;

void computeGraph() {

    double Z[3] = {
	//acqua
	10,
	//rame
	29,
	//piombo
	82,
};

    double Rho[3] = {
	//acqua
	1,
	//rame
	8.96,
	//piombo
	11.34,
}

    double A[3] = {
	//acqua
	18.02,
	//rame
	64.55,
	//piombo
	207.02,
}

//Cambiare di volta in volta i valori del Mu e dell'errore per ogni valore di energia del picco dal file mu_picco.txt

    double Mu[3] = {
	//acqua
	,
	//rame
	,
	//piombo
	,
}

    double err_Mu[3] = {
	//acqua
	,
	//rame
	,
	//piombo
	,
}
    double Sigma[3];
    double err_Sigma[3];
    double err_Z[3];
    for (unsigned int i = 0; i < 3; i++) {
	//Moltiplico per 10^24 per avere la sezione d'urto in barn
	Sigma[i] = (Mu[i]/Rho[i])*(A[i]/TMath::Na())*(10^24);
	err_Sigma[i] = (err_Mu[i]/Rho[i])*(A[i]/TMath::Na())*(10^24);
	err_Z[i] = 0;
    }

//Eventualmenti eliminare alcuni pezzi a seconda dell'energia che si sta valutando

    TF1 fitFun("fitFun", "[0]*(x^5) + [1]*x + [2]*(x^2)", 0, 200000);
    fitFun.SetParameter(0,);
    fitFun.SetParameter(1,);
    fitFun.SetParameter(2,);

    gStyle->SetOptFit(1112);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.9);

    TCanvas myCanv2;

    TGraphErrors graph(3, Z, Sigma, err_Z, err_Sigma);

    graph.SetTitle("Sezione d'urto in funzione di Z");
    graph.GetYaxis()->SetTitle("Sezione d'urto [barn]");
    graph.GetXaxis()->SetTitle("Z");
   
    graph.SetMarkerSize(10);
    graph.Draw("AP");
    graph.Fit("fitFun");
    graph.GetFunction("fitFun")->SetLineColor(9);
    graph.GetFunction("fitFun")->SetParName(0,"a");
    graph.GetFunction("fitFun")->SetParName(1,"b");
    graph.GetFunction("fitFun")->SetParName(2,"c");

//Aggiungere dopo _ il valore di energia del picco per avere grafici distinti

    myCanv2.Print("../graphs/sigma_.pdf");

}

int main(int argc, char** argv) {

    computeGraph();

    return 0;
}
