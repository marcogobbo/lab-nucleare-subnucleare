// c++ -o compute attenuazioneCoRame.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        79885.5/120,
        76666.9/120,
        74552.2/120,
        71017.5/120,
        67215.4/120,
    };

    vector <double> errAmpPeak1 = {
        315.093/120,
        288.825/120,
        303.526/120,
        295.066/120,
        284.921/120
    };

    vector <double> ampPeak2 = {
        71146.1/120,
        68055/120,
        66812.6/120,
        64694.9/120,
        61418.4/120
    };

    vector <double> errAmpPeak2 = {
        289.512/120,
        281.303/120,
        279.027/120,
        272.625/120,
        264.1/120
    };

    vector <double> spessori = {
        0.11, 0.22, 0.33, 0.44, 0.55
    };

    vector <double> errSpessori(5, 0.005);

    TCanvas *canvasAtt = new TCanvas("canvasAtt", "canvasAtt", 800, 500);

    TGraphErrors *graph1 = new TGraphErrors(5, &spessori[0], &ampPeak1[0], &errSpessori[0], &errAmpPeak1[0]);
    TGraphErrors *graph2 = new TGraphErrors(5, &spessori[0], &ampPeak2[0], &errSpessori[0], &errAmpPeak2[0]);
    graph1->GetXaxis()->SetRangeUser(0, 1);
    graph1->GetYaxis()->SetRangeUser(400, 800);

    TF1 *fit1 = new TF1("fitFnc1", "[0]*exp(-[1]*x)", 0, 1);
    TF1 *fit2 = new TF1("fitFnc2", "[0]*exp(-[1]*x)", 0, 1);

    fit1->SetLineColor(9);
    fit2->SetLineColor(8);

    fit1->SetParameter(0, 79885.5/120);
    fit2->SetParameter(0, 71146.1/120);

    fit1->SetParameter(1, 0.6);
    fit2->SetParameter(1, 0.6);

    graph1->SetTitle("Attenuazione con rame ^{60}Co");
    graph1->GetYaxis()->SetTitle("Rate");
    graph1->GetXaxis()->SetTitle("Spessore [cm]");

    graph1->SetMarkerSize(2);
    graph1->SetMarkerStyle(5);

    graph2->SetMarkerSize(2);
    graph2->SetMarkerStyle(4);

    graph1->Draw("AP");
    graph2->Draw("P SAME");

    graph1->Fit("fitFnc1");
    graph2->Fit("fitFnc2");

    TLegend *leg = new TLegend(0.5, 0.8, 0.89, 0.9);
    leg->AddEntry(fit1, TString::Format("2960 mV   #mu = %.3g #pm %.2g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("3373 mV   #mu = %.3g #pm %.2g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneCoRame.pdf");
}
