// c++ -o compute attenuazioneThPiombo.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        1495,
        421,
        272.7,
        61.93,
    };

    vector <double> errAmpPeak1 = {
        19.1,
        10.7,
        8.5,
        5.42,
    };

    vector <double> ampPeak2 = {
        787.5,
        491.8,
        520.8,
        355.2,
        124.5
    };

    vector <double> errAmpPeak2 = {
        13.3,
        10.5,
        10.4,
        9.1,
        5.4
    };

    vector <double> ampPeak3 = {
        187.4,
        147,
        155.5,
        136.8,
        74.7
    };

    vector <double> errAmpPeak3 = {
        5.3,
        4.8,
        4.7,
        4.8,
        3.2
    };

    vector <double> spessori = {
        0.1, 0.21, 0.33, 0.58, 1.08
    };

    vector <double> errSpessori(5, 0.005);

    TCanvas *canvasAtt = new TCanvas("canvasAtt", "canvasAtt", 800, 500);

    TGraphErrors *graph1 = new TGraphErrors(4, &spessori[0], &ampPeak1[0], &errSpessori[0], &errAmpPeak1[0]);
    TGraphErrors *graph2 = new TGraphErrors(5, &spessori[0], &ampPeak2[0], &errSpessori[0], &errAmpPeak2[0]);
    TGraphErrors *graph3 = new TGraphErrors(5, &spessori[0], &ampPeak3[0], &errSpessori[0], &errAmpPeak3[0]);

    graph1->GetXaxis()->SetRangeUser(0, 1.5);
    graph1->GetYaxis()->SetRangeUser(30, 1700);

    TF1 *fit1 = new TF1("fitFnc1", "[0]*exp(-[1]*x)", 0, 1);
    TF1 *fit2 = new TF1("fitFnc2", "[0]*exp(-[1]*x)", 0, 1);
    TF1 *fit3 = new TF1("fitFnc3", "[0]*exp(-[1]*x)", 0, 1);

    fit1->SetLineColor(9);
    fit2->SetLineColor(8);
    fit3->SetLineColor(2);

    fit1->SetParameter(0, 1495);
    fit2->SetParameter(0, 787.5);
    fit2->SetParameter(0, 187.4);

    fit1->SetParameter(1, 5.15);
    fit2->SetParameter(1, 1.25);
    fit2->SetParameter(1, 0.56);

    graph1->SetTitle("Attenuazione con piombo ^{228}Th");
    graph1->GetYaxis()->SetTitle("Rate");
    graph1->GetXaxis()->SetTitle("Spessore [cm]");

    graph1->SetMarkerSize(1);
    graph1->SetMarkerStyle(5);

    graph2->SetMarkerSize(1);
    graph2->SetMarkerStyle(4);

    graph3->SetMarkerSize(1);
    graph3->SetMarkerStyle(8);

    graph1->Draw("AP");
    graph2->Draw("P SAME");
    graph3->Draw("P SAME");

    graph1->Fit("fitFnc1");
    graph2->Fit("fitFnc2");
    graph3->Fit("fitFnc3");

    TLegend *leg = new TLegend(0.44, 0.7, 0.9, 0.9);
    leg->AddEntry(fit1, TString::Format("542 mV   #mu = %.3g #pm %.1g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("1434 mV   #mu = %.3g #pm %.1g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->AddEntry(fit3, TString::Format("6684 mV   #mu = %.3g #pm %.1g cm^{-1}", fit3->GetParameter(1), fit3->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneThPiombo.pdf");
}
