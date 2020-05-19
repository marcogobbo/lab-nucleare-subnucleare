// c++ -o compute attenuazioneCoA.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        1043,
        828,
        670,
        530,
        318.3,
    };

    vector <double> errAmpPeak1 = {
        14,
        13,
        1,
        1,
        7.7
    };

    vector <double> ampPeak2 = {
        914.5,
        752.6,
        590,
        450,
        330
    };

    vector <double> errAmpPeak2 = {
        13.1,
        12.3,
        2,
        2,
        1
    };

    vector <double> spessori = {
        4,
        8,
        12,
        16,
        20
    };

    vector <double> errSpessori(5, 0.1);

    TCanvas *canvasAtt = new TCanvas("canvasAtt", "canvasAtt", 800, 500);

    TGraphErrors *graph1 = new TGraphErrors(5, &spessori[0], &ampPeak1[0], &errSpessori[0], &errAmpPeak1[0]);
    TGraphErrors *graph2 = new TGraphErrors(5, &spessori[0], &ampPeak2[0], &errSpessori[0], &errAmpPeak2[0]);

    TF1 *fit1 = new TF1("fitFnc1", "[0]*exp(-[1]*x)", 0, 30);
    TF1 *fit2 = new TF1("fitFnc2", "[0]*exp(-[1]*x)", 0, 30);

    fit1->SetLineColor(9);
    fit2->SetLineColor(8);

    fit1->SetParameter(0, 1043);
    fit2->SetParameter(0, 914.5);

    fit1->SetParameter(1, 0.028);
    fit2->SetParameter(1, 0.028);

    graph1->SetTitle("Attenuazione con acqua ^{60}Co");
    graph1->GetYaxis()->SetTitle("Rate");
    graph1->GetXaxis()->SetTitle("Spessore [cm]");

    graph1->SetMarkerSize(10);
    graph2->SetMarkerSize(10);

    graph1->Draw("AP");
    graph2->Draw("P SAME");

    graph1->Fit("fitFnc1");
    graph2->Fit("fitFnc2");

    TLegend *leg = new TLegend(0.53, 0.8, 0.89, 0.9);
    leg->AddEntry(fit1, TString::Format("2960 mV   #mu = %.3g #pm %.1g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("3373 mV   #mu = %.3g #pm %.1g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneCoA.pdf");
}
