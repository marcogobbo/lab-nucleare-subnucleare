// c++ -o compute pulser.cpp lib/analyzer.cc `root-config --cflags --glibs`

#include "lib/analyzer.h"

using namespace std;

int main(int argc, char** argv) {
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
    string fileName = "Pulser/" + folder[0] + "/tensione.txt";

    // Creo il vettore dove salvare i dati, min e max
    vector<double> data;
    double xMin;
    double xMax;

    // Carico i dati controllando che non via siano errori
    if (pulser.loadData(fileName, data, xMin, xMax) == false) {
        cout << "Errore nel caricare il file: " << fileName.c_str() << endl;
    };

    // Imposto il numero di bins
    int nBins = 100;
    
    // Creo istogramma
    TH1D* h1 = new TH1D("Dati", "Istogramma", nBins, xMin, xMax);

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

    // Stampo l'istogramma che sarà poi da spostare dalla cartella analisi al quella specifica del Pulser analizzato
    myCanv1->Print("istogramma.pdf","pdf");

    //cout << xMax << endl;
    //cout << xMin << endl;
    return 0;
}