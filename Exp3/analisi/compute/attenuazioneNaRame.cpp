// c++ -o compute attenuazioneNaRame.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        25580,
        24080,
        22390,
        20500,
        19050
    };

    vector <double> errAmpPeak1 = {
        77.9,
        78.9,
        73.9,
        71.4,
        69
    };

    vector <double> ampPeak2 = {
        7291,
        6773,
        6784,
        6511,
        6311
    };

    vector <double> errAmpPeak2 = {
        40.7,
        38.8,
        39.4,
        38.2,
        37.8
    }; 

    vector <double> spessori = {
        0.11, 0.22, 0.33, 0.44, 0.55
    };

    vector <double> errSpessori(5, 0.005);

    TCanvas *canvasAtt = new TCanvas("canvasAtt", "canvasAtt", 800, 500);

    TGraphErrors *graph1 = new TGraphErrors(5, &spessori[0], &ampPeak1[0], &errSpessori[0], &errAmpPeak1[0]);
    TGraphErrors *graph2 = new TGraphErrors(5, &spessori[0], &ampPeak2[0], &errSpessori[0], &errAmpPeak2[0]);
    graph1->GetXaxis()->SetRangeUser(0, 1);
    graph1->GetYaxis()->SetRangeUser(6100, 27000);

    TF1 *fit1 = new TF1("fitFnc1", "[0]*exp(-[1]*x)", 0, 1);
    TF1 *fit2 = new TF1("fitFnc2", "[0]*exp(-[1]*x)", 0, 1);

    fit1->SetLineColor(9);
    fit2->SetLineColor(8);

    fit1->SetParameter(0, 25580);
    fit2->SetParameter(0, 7291);

    fit1->SetParameter(1, 0.40);
    fit2->SetParameter(1, 0.21);

    graph1->SetTitle("Attenuazione con rame ^{22}Na");
    graph1->GetYaxis()->SetTitle("Rate");
    graph1->GetXaxis()->SetTitle("Spessore [cm]");

    graph1->SetMarkerSize(10);
    graph2->SetMarkerSize(10);

    graph1->Draw("AP");
    graph2->Draw("P SAME");

    graph1->Fit("fitFnc1");
    graph2->Fit("fitFnc2");

    TLegend *leg = new TLegend(0.5, 0.8, 0.89, 0.9);
    leg->AddEntry(fit1, TString::Format("1246 mV   #mu = %.3g #pm %.2g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("3223 mV   #mu = %.3g #pm %.2g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneNaRame.pdf");
}
