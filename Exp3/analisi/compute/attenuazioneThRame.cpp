// c++ -o compute attenuazioneThRame.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        2973,
        2381,
        1767,
        1532,
        1529
    };

    vector <double> errAmpPeak1 = {
        27.8,
        24.7,
        20.5,
        20.0,
        20.2
    };

    vector <double> ampPeak2 = {
        860.4,
        699.1,
        562.4,
        506,
        546.5
    };

    vector <double> errAmpPeak2 = {
        14.4,
        12.8,
        11.0,
        10.7,
        11.4
    };

    vector <double> ampPeak3 = {
        203.6,
        176.1,
        152.3,
        135.2,
        147.7
    };

    vector <double> errAmpPeak3 = {
        5.9,
        5.2,
        4.8,
        4.6,
        4.9
    };

    vector <double> spessori = {
        0.11, 0.22, 0.33, 0.44, 0.55
    };

    vector <double> errSpessori(5, 0.005);

    TCanvas *canvasAtt = new TCanvas("canvasAtt", "canvasAtt", 800, 500);

    TGraphErrors *graph1 = new TGraphErrors(5, &spessori[0], &ampPeak1[0], &errSpessori[0], &errAmpPeak1[0]);
    TGraphErrors *graph2 = new TGraphErrors(5, &spessori[0], &ampPeak2[0], &errSpessori[0], &errAmpPeak2[0]);
    TGraphErrors *graph3 = new TGraphErrors(5, &spessori[0], &ampPeak3[0], &errSpessori[0], &errAmpPeak3[0]);

    graph1->GetXaxis()->SetRangeUser(0, 1);
    graph1->GetYaxis()->SetRangeUser(0, 3000);

    TF1 *fit1 = new TF1("fitFnc1", "[0]*exp(-[1]*x)", 0, 1);
    TF1 *fit2 = new TF1("fitFnc2", "[0]*exp(-[1]*x)", 0, 1);
    TF1 *fit3 = new TF1("fitFnc3", "[0]*exp(-[1]*x)", 0, 1);

    fit1->SetLineColor(9);
    fit2->SetLineColor(8);
    fit3->SetLineColor(2);

    fit1->SetParameter(0, 2973);
    fit2->SetParameter(0, 860.4);
    fit2->SetParameter(0, 203.6);

    fit1->SetParameter(1, 1.57);
    fit2->SetParameter(1, 1.28);
    fit2->SetParameter(1, 0.87);

    graph1->SetTitle("Attenuazione con rame ^{228}Th");
    graph1->GetYaxis()->SetTitle("Rate");
    graph1->GetXaxis()->SetTitle("Spessore [cm]");

    graph1->SetMarkerSize(10);
    graph2->SetMarkerSize(10);
    graph3->SetMarkerSize(10);

    graph1->Draw("AP");
    graph2->Draw("P SAME");
    graph3->Draw("P SAME");

    graph1->Fit("fitFnc1");
    graph2->Fit("fitFnc2");
    graph3->Fit("fitFnc3");

    TLegend *leg = new TLegend(0.50, 0.7, 0.9, 0.9);
    leg->AddEntry(fit1, TString::Format("542 mV   #mu = %.3g #pm %.1g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("1434 mV   #mu = %.3g #pm %.1g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->AddEntry(fit3, TString::Format("6684 mV   #mu = %.3g #pm %.1g cm^{-1}", fit3->GetParameter(1), fit3->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneThRame.pdf");
}
