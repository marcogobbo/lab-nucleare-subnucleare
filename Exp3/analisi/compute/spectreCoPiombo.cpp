// c++ -o compute spectreCoPiombo.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

double gaussFit (double* x, double* par) {
  	return par[0] * exp(-0.5*((x[0]-par[1])*(x[0]-par[1])/(par[2]*par[2])));
}

double pol0 (double*x, double* par) {
    return par[0];
}

double totalFit (double* x, double* par) {
    return gaussFit(x, par) + pol0(x, &par[3]) + gaussFit(x, &par[4]);
}

void computeHisto (string element, string nameSource, string peak, int bin, double limInf, double limSup, bool logScale, bool noData) {
    Analyzer Spectre;
    string fileName = "../data/materiali/" + element + "/" + nameSource + ".dat";

    vector<double> data;
    double min, max;

    // Carico i dati controllando che non via siano errori
    if (Spectre.loadData(fileName, data, min, max) == false) {
        cout << "Errore nel caricare il file: " << fileName.c_str() << endl;
    };

    // Imposto il numero di bin
    int nBin = bin;

    if (noData) {
        gStyle->SetOptStat("");
    }
    else {
        gStyle->SetOptFit(1112);
    }
    
    TString titleGraph = nameSource;
    TString namePDF;
    if (noData) {
        namePDF = "../graphsNoData/spectre_" + nameSource + peak + ".pdf";
    }
    else {
        namePDF = "../graphs/spectre_" + nameSource + peak + ".pdf"; 
    }
    
    TH1D* histoSpectre = new TH1D("Data", titleGraph, nBin, 0, 8192);

    for (unsigned int i = 0; i < data.size(); i++) {
        histoSpectre->SetBinContent(i, data[i]);
    }

    TCanvas* canvasSpectre = new TCanvas("canvasSpectre", "canvasSpectre", 0, 0, 800, 500);

    canvasSpectre->cd();

    histoSpectre->Draw();
    histoSpectre->SetFillColor(kYellow-10);
    histoSpectre->GetXaxis()->SetTitle("Channels [mV]");
    histoSpectre->GetYaxis()->SetTitle("Counts");
    histoSpectre->GetXaxis()->SetRangeUser(limInf, limSup);

    // Da commentare se si vuole lo spettro totale o da sostituire con il fit corretto presente in compute/codeFit/...
    TF1* funcFit = new TF1("funcFit", totalFit, limInf, limSup, 7);
    funcFit->SetParName(0,"Amp");
    funcFit->SetParName(1,"Mean");
    funcFit->SetParName(2,"Std Dev");
    funcFit->SetParName(3,"Noise");
    funcFit->SetParName(4,"Amp_PileUp");
    funcFit->SetParName(5,"Mean_PileUp");
    funcFit->SetParName(6,"Std Dev_PileUp");
    funcFit->SetParameter(0, 6000);
    funcFit->SetParameter(1, 3370);
    funcFit->SetParameter(2, 5);
    funcFit->SetParameter(3, 50);
    funcFit->SetParameter(4, 1100);
    funcFit->SetParameter(5, 3388);
    funcFit->SetParameter(6, 10);

    histoSpectre->Fit("funcFit");

    // Calcolo le aree
    TF1* gaussian = new TF1("gaussian", gaussFit, limInf, limSup, 3);
    gaussian->SetParameter(0, funcFit->GetParameter(0));
    gaussian->SetParameter(1, funcFit->GetParameter(1));
    gaussian->SetParameter(2, funcFit->GetParameter(2));
    gaussian->SetParError(0, funcFit->GetParError(0));
    gaussian->SetParError(1, funcFit->GetParError(1));
    gaussian->SetParError(2, funcFit->GetParError(2));

    fstream OutFile;
    OutFile.open("areeCoPiombo.txt", fstream::app);
    OutFile << namePDF <<":\t"<< gaussian->Integral(3360, 3380) << " +/- " << funcFit->IntegralError(3360, 3380) << endl;
    OutFile.close();

    if (logScale) {
        canvasSpectre->SetLogy();
    }

    //canvasSpectre->Print(namePDF);

    // Libero la memoria
    delete histoSpectre;
    delete canvasSpectre;
}


int main() {
    // COBALTO PIOMBO 0.1 cm
    //computeHisto ("piombo", "cobalto_piombo_01cm", "", 8192, 0, 8192, false, false);
    //computeHisto ("piombo", "cobalto_piombo_01cm", "", 8192, 0, 8192, false, true);


    // PICCO 1 COBALTO PIOMBO 0.1 cm
    //computeHisto ("piombo", "cobalto_piombo_01cm", "1", 8192, 2941, 3020, false, false);
    //computeHisto ("piombo", "cobalto_piombo_01cm", "1", 8192, 2941, 3020, false, true);


    // PICCO 2 COBALTO PIOMBO 0.1 cm
    //computeHisto ("piombo", "cobalto_piombo_01cm", "2", 8192, 3353, 3420, false, false);
    //computeHisto ("piombo", "cobalto_piombo_01cm", "2", 8192, 3353, 3420, false, true);


  
    // COBALTO PIOMBO 0.21 cm
    //computeHisto ("piombo", "cobalto_piombo_021cm", "", 8192, 0, 8192, false, false);
    //computeHisto ("piombo", "cobalto_piombo_021cm", "", 8192, 0, 8192, false, true);


    // PICCO 1 COBALTO PIOMBO 0.21 cm
    //computeHisto ("piombo", "cobalto_piombo_021cm", "1", 8192, 2941, 3020, false, false);
    //computeHisto ("piombo", "cobalto_piombo_021cm", "1", 8192, 2941, 3020, false, true);


    // PICCO 2 COBALTO PIOMBO 0.21 cm
    //computeHisto ("piombo", "cobalto_piombo_021cm", "2", 8192, 3353, 3420, false, false);
    //computeHisto ("piombo", "cobalto_piombo_021cm", "2", 8192, 3353, 3420, false, true);



    // COBALTO PIOMBO 0.33 cm
    //computeHisto ("piombo", "cobalto_piombo_033cm", "", 8192, 0, 8192, false, false);
    //computeHisto ("piombo", "cobalto_piombo_033cm", "", 8192, 0, 8192, false, true);


    // PICCO 1 COBALTO PIOMBO 0.33 cm
    //computeHisto ("piombo", "cobalto_piombo_033cm", "1", 8192, 2941, 3020, false, false);
    //computeHisto ("piombo", "cobalto_piombo_033cm", "1", 8192, 2941, 3020, false, true);


    // PICCO 2 COBALTO PIOMBO 0.33 cm
    //computeHisto ("piombo", "cobalto_piombo_033cm", "2", 8192, 3353, 3420, false, false);
    //computeHisto ("piombo", "cobalto_piombo_033cm", "2", 8192, 3353, 3420, false, true);


  
    // COBALTO PIOMBO 0.58 cm
    //computeHisto ("piombo", "cobalto_piombo_058cm", "", 8192, 0, 8192, false, false);
    //computeHisto ("piombo", "cobalto_piombo_058cm", "", 8192, 0, 8192, false, true);


    // PICCO 1 COBALTO PIOMBO 0.58 cm
    //computeHisto ("piombo", "cobalto_piombo_058cm", "1", 8192, 2941, 3020, false, false);
    //computeHisto ("piombo", "cobalto_piombo_058cm", "1", 8192, 2941, 3020, false, true);


    // PICCO 2 COBALTO PIOMBO 0.58 cm
    //computeHisto ("piombo", "cobalto_piombo_058cm", "2", 8192, 3353, 3420, false, false);
    //computeHisto ("piombo", "cobalto_piombo_058cm", "2", 8192, 3353, 3420, false, true);    


    
    // COBALTO PIOMBO 1.08 cm
    //computeHisto ("piombo", "cobalto_piombo_108cm", "", 8192, 0, 8192, false, false);
    //computeHisto ("piombo", "cobalto_piombo_108cm", "", 8192, 0, 8192, false, true);


    // PICCO 1 COBALTO PIOMBO 1.08 cm
    //computeHisto ("piombo", "cobalto_piombo_108cm", "1", 8192, 2941, 3020, false, false);
    //computeHisto ("piombo", "cobalto_piombo_108cm", "1", 8192, 2941, 3020, false, true);


    // PICCO 2 COBALTO PIOMBO 1.08 cm
    computeHisto ("piombo", "cobalto_piombo_108cm", "2", 8192, 3353, 3420, false, false);
    //computeHisto ("piombo", "cobalto_piombo_108cm", "2", 8192, 3353, 3420, false, true);
}
