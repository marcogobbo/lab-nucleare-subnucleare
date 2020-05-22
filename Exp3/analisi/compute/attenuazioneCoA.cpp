// c++ -o compute attenuazioneCoA.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        8488.44/360,
        6655.03/360,
        5302.73/360,
        4242.99/360,
        2964.44/360
    };

    vector <double> errAmpPeak1 = {
        93.9857/360,
        83.5828/360,
        51.9204/360,
        47.839/360,
        56.1584/360
    };

    vector <double> ampPeak2 = {
        7700.77/360,
        6123/360,
        4896.18/360,
        3840.77/360,
        2991.68/360
    };

    vector <double> errAmpPeak2 = {
        87.8704/360,
        78.8846/360,
        46.4039/360,
        41.6712/360,
        39.7747/360
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

    graph1->GetXaxis()->SetRangeUser(0, 30);
    graph1->GetYaxis()->SetRangeUser(0, 35);

    fit1->SetLineColor(9);
    fit2->SetLineColor(8);

    fit1->SetParameter(0, 8488.44);
    fit2->SetParameter(0, 7700.77);

    fit1->SetParameter(1, 0.065);
    fit2->SetParameter(1, 0.065);

    graph1->SetTitle("Attenuazione con acqua ^{60}Co");
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

    TLegend *leg = new TLegend(0.53, 0.8, 0.9, 0.9);
    leg->AddEntry(fit1, TString::Format("2960 mV   #mu = %.3g #pm %.1g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("3373 mV   #mu = %.3g #pm %.1g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneCoA.pdf");
}
