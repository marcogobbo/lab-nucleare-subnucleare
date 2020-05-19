// c++ -o compute attenuazioneCoRame.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        10750,
        10370,
        9941,
        9568,
        8960,
    };

    vector <double> errAmpPeak1 = {
        50,
        46,
        51,
        49.5,
        47.6
    };

    vector <double> ampPeak2 = {
        9525,
        9041,
        8816,
        8567,
        8056
    };

    vector <double> errAmpPeak2 = {
        48.3,
        46.8,
        46.3,
        45.2,
        47.3
    };

    vector <double> spessori = {
        0.11, 0.22, 0.33, 0.44, 0.55
    };

    vector <double> errSpessori(5, 0.005);

    TCanvas *canvasAtt = new TCanvas("canvasAtt", "canvasAtt", 800, 500);

    TGraphErrors *graph1 = new TGraphErrors(5, &spessori[0], &ampPeak1[0], &errSpessori[0], &errAmpPeak1[0]);
    TGraphErrors *graph2 = new TGraphErrors(5, &spessori[0], &ampPeak2[0], &errSpessori[0], &errAmpPeak2[0]);
    graph1->GetXaxis()->SetRangeUser(0, 1);
    graph1->GetYaxis()->SetRangeUser(7000, 12000);

    TF1 *fit1 = new TF1("fitFnc1", "[0]*exp(-[1]*x)", 0, 1);
    TF1 *fit2 = new TF1("fitFnc2", "[0]*exp(-[1]*x)", 0, 1);

    fit1->SetLineColor(9);
    fit2->SetLineColor(8);

    fit1->SetParameter(0, 10750);
    fit2->SetParameter(0, 9525);

    fit1->SetParameter(1, 0.23);
    fit2->SetParameter(1, 0.23);

    graph1->SetTitle("Attenuazione con rame ^{60}Co");
    graph1->GetYaxis()->SetTitle("Rate");
    graph1->GetXaxis()->SetTitle("Spessore [cm]");

    graph1->SetMarkerSize(10);
    graph2->SetMarkerSize(10);

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
