// c++ -o compute attenuazioneNaPiombo.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        25280,
        21790,
        19720,
        13690,
        5222
    };

    vector <double> errAmpPeak1 = {
        77.3,
        70,
        67.2,
        54.1,
        34.6
    };

    vector <double> ampPeak2 = {
        7771,
        8009,
        8179,
        7432,
        5030
    };

    vector <double> errAmpPeak2 = {
        42.6,
        42.9,
        43.6,
        40.7,
        62.2
    };

    vector <double> spessori = {
        0.1, 0.21, 0.33, 0.58, 1.08
    };

    vector <double> errSpessori(5, 0.005);

    TCanvas *canvasAtt = new TCanvas("canvasAtt", "canvasAtt", 800, 500);

    TGraphErrors *graph1 = new TGraphErrors(5, &spessori[0], &ampPeak1[0], &errSpessori[0], &errAmpPeak1[0]);
    TGraphErrors *graph2 = new TGraphErrors(5, &spessori[0], &ampPeak2[0], &errSpessori[0], &errAmpPeak2[0]);
    graph1->GetXaxis()->SetRangeUser(0, 1.5);
    graph1->GetYaxis()->SetRangeUser(3000, 27000);

    TF1 *fit1 = new TF1("fitFnc1", "[0]*exp(-[1]*x)", 0, 1);
    TF1 *fit2 = new TF1("fitFnc2", "[0]*exp(-[1]*x)", 0, 1);

    fit1->SetLineColor(9);
    fit2->SetLineColor(8);

    fit1->SetParameter(0, 25280);
    fit2->SetParameter(0, 8179);

    fit1->SetParameter(1, 0.75);
    fit2->SetParameter(1, 0.60);

    graph1->SetTitle("Attenuazione con piombo ^{22}Na");
    graph1->GetYaxis()->SetTitle("Rate");
    graph1->GetXaxis()->SetTitle("Spessore [cm]");

    graph1->SetMarkerSize(10);
    graph2->SetMarkerSize(10);

    graph1->Draw("AP");
    graph2->Draw("P SAME");

    graph1->Fit("fitFnc1");
    graph2->Fit("fitFnc2");

    TLegend *leg = new TLegend(0.47, 0.8, 0.89, 0.9);
    leg->AddEntry(fit1, TString::Format("1246 mV   #mu = %.3g #pm %.2g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("3223 mV   #mu = %.3g #pm %.2g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneNaPiombo.pdf");
}
