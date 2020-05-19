// c++ -o compute attenuazioneNaA.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        1983,
        1412,
        931.7,
        693.5,
        447.2
    };

    vector <double> errAmpPeak1 = {
        17.9,
        15.2,
        12.4,
        11.0,
        8.7
    };

    vector <double> ampPeak2 = {
        700.4,
        580.2,
        444.5,
        378.1,
        251
    };

    vector <double> errAmpPeak2 = {
        11.4,
        10.7,
        9.1,
        8.9,
        6.9
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

    graph1->GetXaxis()->SetRangeUser(0, 30);
    graph1->GetYaxis()->SetRangeUser(100, 3000);

    TF1 *fit1 = new TF1("fitFnc1", "[0]*exp(-[1]*x)", 0, 30);
    TF1 *fit2 = new TF1("fitFnc2", "[0]*exp(-[1]*x)", 0, 30);

    fit1->SetLineColor(9);
    fit2->SetLineColor(8);

    fit1->SetParameter(0, 1983);
    fit2->SetParameter(0, 700.4);

    fit1->SetParameter(1, 0.0628);
    fit2->SetParameter(1, 0.0378);

    graph1->SetTitle("Attenuazione con acqua ^{22}Na");
    graph1->GetYaxis()->SetTitle("Rate");
    graph1->GetXaxis()->SetTitle("Spessore [cm]");

    graph1->SetMarkerSize(10);
    graph2->SetMarkerSize(10);

    graph1->Draw("AP");
    graph2->Draw("P SAME");

    graph1->Fit("fitFnc1");
    graph2->Fit("fitFnc2");

    TLegend *leg = new TLegend(0.53, 0.8, 0.9, 0.9);
    leg->AddEntry(fit1, TString::Format("1246 mV   #mu = %.3g #pm %.1g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("3223 mV   #mu = %.3g #pm %.1g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneNaA.pdf");
}
