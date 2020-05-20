// c++ -o compute attenuazioneThA.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        70.64,
        72.7,
        64.05,
        44.45,
        37.81
    };

    vector <double> errAmpPeak1 = {
        5.56,
        5.0,
        5.00,
        4.58,
        4.44
    };

    vector <double> ampPeak2 = {
        28.35,
        33.66,
        32.2,
        20.66,
        22.28
    };

    vector <double> errAmpPeak2 = {
        2.57,
        2.92,
        2.7,
        2.34,
        2.51
    };

    vector <double> ampPeak3 = {
        9.34,
        11.12,
        12.95,
        9.18,
        12.95
    };

    vector <double> errAmpPeak3 = {
        1.475,
        1.54,
        1.69,
        1.28,
        1.73
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
    TGraphErrors *graph3 = new TGraphErrors(5, &spessori[0], &ampPeak3[0], &errSpessori[0], &errAmpPeak3[0]);

    graph1->GetXaxis()->SetRangeUser(0, 30);
    graph1->GetYaxis()->SetRangeUser(0, 100);

    TF1 *fit1 = new TF1("fitFnc1", "[0]*exp(-[1]*x)", 0, 30);
    TF1 *fit2 = new TF1("fitFnc2", "[0]*exp(-[1]*x)", 0, 30);
    TF1 *fit3 = new TF1("fitFnc3", "[0]*exp(-[1]*x)", 0, 30);

    fit1->SetLineColor(9);
    fit2->SetLineColor(8);
    fit3->SetLineColor(2);

    fit1->SetParameter(0, 72.7);
    fit2->SetParameter(0, 33.66);
    fit2->SetParameter(0, 1.475);

    fit1->SetParameter(1, 0.010);
    fit2->SetParameter(1, 0.010);
    fit2->SetParameter(1, 0.010);

    graph1->SetTitle("Attenuazione con acqua ^{228}Th");
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

    TLegend *leg = new TLegend(0.53, 0.7, 0.9, 0.9);
    leg->AddEntry(fit1, TString::Format("542 mV   #mu = %.3g #pm %.1g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("1434 mV   #mu = %.3g #pm %.1g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->AddEntry(fit3, TString::Format("6684 mV   #mu = %.3g #pm %.1g cm^{-1}", fit3->GetParameter(1), fit3->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneThA.pdf");
}
