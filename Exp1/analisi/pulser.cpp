// c++ -o compute pulser.cpp lib/analyzer.cc `root-config --cflags --glibs`

#include "lib/analyzer.h"

using namespace std;

double gaussFit (double* x, double* par)	{
  	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

void computeHisto(int index, int bin, int _min, int _max) {
    // Istanzio l'oggetto pulser dalla classe Analyzer
    Analyzer pulser;

    // Creo un array per le varie cartelle in Pulser
    string folder[10] = {
        "PulserCal_1.10MeV",
        "PulserCal_2.09MeV",
        "PulserCal_3.09MeV",
        "PulserCal_4.09MeV",
        "PulserCal_5.09MeV",
        "PulserCal_6.09MeV",
        "PulserCal_7.09MeV",
        "PulserCal_8.09MeV",
        "PulserCal_9.09MeV",
        "PulserCal_9.98MeV"
    };

    // Scrivo il file da analizzare, vario l'indice di folder per cambiare cartella, tanto il file tensione.txt è in tutti
    string fileName = "Pulser/" + folder[index] + "/tensione.txt";

    // Creo il vettore dove salvare i dati, min e max
    vector<double> data;
    double min;
    double max;

    // Carico i dati controllando che non via siano errori
    if (pulser.loadData(fileName, data, min, max) == false) {
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
    TH1D* h1 = new TH1D("Dati", "Pulser - 9.98 MeV", nBins, min, max);

    // Inserisco i dati nell'istogramma
    for (unsigned int i = 0; i < data.size(); i++) {
        h1->Fill(data[i]);
    }

    // Creo il canvas per stampare poi l'istogramma
    TCanvas* myCanv1 = new TCanvas("myCanv1","myCanv1",0,0,700,500);

    // Mi muovo sul canvas
    myCanv1->cd();

    // Disegno l'istogramma sul canvas
    h1->Draw();
    h1->SetFillColor(kYellow-10);
    gStyle->SetOptFit(1112);

    h1->GetXaxis()->SetTitle("Tensione [mV]");
    h1->GetYaxis()->SetTitle("Conteggi");

    // Preparo il fit
    TF1* funcFit = new TF1("funcFit", gaussFit, min, max, 3);
    funcFit->SetParameter(1, h1->GetMean());
    funcFit->SetParameter(2, h1->GetRMS());
    funcFit->SetParName(0,"Ampiezza");
    funcFit->SetParName(1,"Media");
    funcFit->SetParName(2,"Dev Std");

    // Eseguo il fit
    h1->Fit("funcFit");

    // Stampo l'istogramma che sarà poi da spostare dalla cartella analisi al quella specifica del Pulser analizzato
    myCanv1->Print("istogramma.pdf","pdf");

    //cout << max << endl;
    //cout << min << endl;
}

void computeGraph() {
    double energia[10] = {
        1.10,
        2.09,
        3.09,
        4.09,
        5.09,
        6.09,
        7.09,
        8.09,
        9.09,
        9.98
    };

    double errEnergia[10];

    double tensione[10] = {
        664.6,
        1424,
        2184,
        2945,
        3707,
        4468,
        5227,
        5983,
        6734,
        7405
    };
    double errTensione[10] = {
        7.757,
        7.851,
        7.877,
        7.742,
        7.696,
        7.785,
        7.76,
        7.748,
        7.753,
        7.736
    };

    /*for (unsigned int i = 0; i < 10; i++) {
        errEnergia[i] = 0;
        tensione[i] = tensione[i]/1000;
        errTensione[i] = errTensione[i]/1000;
    }*/

    TF1 fitFnc("fitFnc1","[0]*x+[1]",0,200000);
    fitFnc.SetParameter(0,0.001414);
    fitFnc.SetParameter(1,0);
    gStyle->SetOptFit(1112);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.45);
    TCanvas myCanv2;
    TGraphErrors graph(10, tensione, energia, errTensione, errEnergia);

    graph.SetTitle("Calibrazione");
    graph.GetYaxis()->SetTitle("Energia [MeV]");
    graph.GetXaxis()->SetTitle("Tensione [mV]");
    graph.SetMarkerSize(2);
    graph.Draw("AP");
    graph.Fit("fitFnc1");
    graph.GetFunction("fitFnc1")->SetLineColor(9);
    graph.GetFunction("fitFnc1")->SetParName(0,"m");
    graph.GetFunction("fitFnc1")->SetParName(1,"q");
    myCanv2.Print("graph.pdf", "pdf");

}

int main(int argc, char** argv) {

    //computeHisto(9, 72, 7370, 0);
    computeGraph();

    return 0;
}