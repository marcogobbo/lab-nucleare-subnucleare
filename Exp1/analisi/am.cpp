// c++ -o compute am.cpp lib/analyzer.cc `root-config --cflags --glibs`
// ./compute

#include "lib/analyzer.h"

using namespace std;

double gaussFit1 (double* x, double* par) {
  	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

double gaussFit2 (double* x, double* par) {
  	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

double gaussFit3 (double* x, double* par) {
  	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

double gaussFit4 (double* x, double* par) {
  	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

double totalFit (double* x, double* par) {
    return gaussFit1(x, par) + gaussFit2(x, &par[3]) + gaussFit3(x, &par[6]) + gaussFit4(x, &par[9]);
}

void computeHisto(int bin, double _min, double _max) {
    Analyzer am;

    string fileName = "241Am/tensione.txt";

    // Creo il vettore dove salvare i dati, min e max
    vector<double> data;
    double min;
    double max;

    // Carico i dati controllando che non via siano errori
    if (am.loadData(fileName, data, min, max) == false) {
        cout << "Errore nel caricare il file: " << fileName.c_str() << endl;
    };

    // Imposto il numero di bins
    int nBins = bin;

    // Imposto minimo e massimo
    if (_min != 0) {
        min = _min;
    }

    if (_max != 0) {
        max = _max;
    }

    // Creo istogramma
    TH1D* h1 = new TH1D("Dati", "Istogramma 241-Am", nBins, min, max);
    gStyle->SetOptStat("");
    // Inserisco i dati nell'istogramma
    for (unsigned int i = 0; i < data.size(); i++) {
        h1->Fill(data[i]);
    }

    // Creo il canvas per stampare poi l'istogramma
    TCanvas* myCanv1 = new TCanvas("myCanv1", "myCanv1", 0, 0, 800, 500);

    // Mi muovo sul canvas
    myCanv1->cd();

    // Disegno l'istogramma sul canvas
    h1->Draw();
    h1->SetFillColor(kYellow-10);
    //gStyle->SetOptFit(1112);

    h1->GetXaxis()->SetTitle("Tensione [mV]");
    h1->GetYaxis()->SetTitle("Conteggi");

    TF1* funcFit = new TF1("funcFit", totalFit, 3930, 4100, 12);
    funcFit->SetParName(0,"Amp (Peak 1)");
    funcFit->SetParName(1,"Mean (Peak 1)");
    funcFit->SetParName(2,"Std Dev (Peak 1)");
    funcFit->SetParameter(0, 300);
    funcFit->SetParameter(1, 3960);
    funcFit->SetParameter(2, 10);

    funcFit->SetParName(3,"Amp (Peak 2)");
    funcFit->SetParName(4,"Mean (Peak 2)");
    funcFit->SetParName(5,"Std Dev (Peak 2)");
    funcFit->SetParameter(3, 1800);
    funcFit->SetParameter(4, 4010);
    funcFit->SetParameter(5, 10);

    funcFit->SetParName(6,"Amp (Peak 3)");
    funcFit->SetParName(7,"Mean (Peak 3)");
    funcFit->SetParName(8,"Std Dev (Peak 3)");
    funcFit->SetParameter(6, 1100);
    funcFit->SetParameter(7, 4040);
    funcFit->SetParameter(8, 10);

    funcFit->SetParName(9,"Amp (Peak 4)");
    funcFit->SetParName(10,"Mean (Peak 4)");
    funcFit->SetParName(11,"Std Dev (Peak 4)");
    funcFit->SetParameter(9, 770);
    funcFit->SetParameter(10, 4070);
    funcFit->SetParameter(11, 10);

    h1->Fit("funcFit");
    myCanv1->Print("241-Am.pdf", "pdf");
} 

void computeGraph() {
    double tabulatedEnergyValues[4] = {
        5.388,
        5.443,
        5.486,
        5.545
    };

    double errTabulatedEnergyValues[4];

    double tensioni[4] = {
        3970,
        4006,
        4036,
        4062
    };

    double errTensioni[4] = {
        17,
        12,
        10,
        14
    };

    TF1 fitFnc("fitFnc1","[0]*x+[1]",0,200000);
    fitFnc.SetParameter(0,0.001359);
    fitFnc.SetParameter(1,0);
    gStyle->SetOptStat("");
    //gStyle->SetOptFit(1112);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.45);

    TCanvas myCanv2;
    TGraphErrors graph(4, tensioni, tabulatedEnergyValues, errTensioni, errTabulatedEnergyValues);

    graph.SetTitle("Calibrazione 241-Am");
    graph.GetYaxis()->SetTitle("Energia Tabulata [MeV]");
    graph.GetXaxis()->SetTitle("Tensione [mV]");
    graph.SetMarkerSize(2);
    graph.Draw("AP");
    graph.Fit("fitFnc1");
    graph.GetFunction("fitFnc1")->SetLineColor(9);
    graph.GetFunction("fitFnc1")->SetParName(0,"m");
    graph.GetFunction("fitFnc1")->SetParName(1,"q");
    myCanv2.Print("graph_241-Am.pdf", "pdf");

}

int main(int argc, char** argv) {
    //computeHisto(170, 3930, 4100);
    
    computeGraph();
    return 0;
}