// c++ -o compute attenuazioneCoPiombo.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        80230.1/120,
        76822.8/120,
        73254.3/120,
        64776.2/120,
        50207.8/120
    };

    vector <double> errAmpPeak1 = {
        316.754/120,
        308.446/120,
        299.281/120,
        290.801/120,
        242.601/120
    };

    vector <double> ampPeak2 = {
        72312.6/120,
        69392.9/120,
        67182.3/120,
        60145.5/120,
        47998.5/120
    };

    vector <double> errAmpPeak2 = {
        291.803/120,
        282.015/120,
        277.196/120,
        264.055/120,
        229.559/120
    };

    vector <double> spessori = {
        0.1, 0.21, 0.33, 0.58, 1.08
    };

    vector <double> errSpessori(5, 0.005);

    TCanvas *canvasAtt = new TCanvas("canvasAtt", "canvasAtt", 800, 500);

    TGraphErrors *graph1 = new TGraphErrors(5, &spessori[0], &ampPeak1[0], &errSpessori[0], &errAmpPeak1[0]);
    TGraphErrors *graph2 = new TGraphErrors(5, &spessori[0], &ampPeak2[0], &errSpessori[0], &errAmpPeak2[0]);
    graph1->GetXaxis()->SetRangeUser(0, 1.5);
    graph1->GetYaxis()->SetRangeUser(300, 800);

    TF1 *fit1 = new TF1("fitFnc1", "[0]*exp(-[1]*x)", 0, 1);
    TF1 *fit2 = new TF1("fitFnc2", "[0]*exp(-[1]*x)", 0, 1);

    fit1->SetLineColor(9);
    fit2->SetLineColor(8);

    fit1->SetParameter(0, 80230.1/120);
    fit2->SetParameter(0, 72312.6/120);

    fit1->SetParameter(1, 0.6);
    fit2->SetParameter(1, 0.6);

    graph1->SetTitle("Attenuazione con piombo ^{60}Co");
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

    cout << "\n" << endl;
    cout << fit1->GetChisquare()/fit1->GetNDF() << endl;
    cout << fit2->GetChisquare()/fit2->GetNDF() << endl;
    cout << "\n" << endl;

    cout << "\n" << endl;
    cout << fit1->GetProb() << endl;
    cout << fit2->GetProb() << endl;
    cout << "\n" << endl;

    TLegend *leg = new TLegend(0.48, 0.8, 0.9, 0.9);
    leg->AddEntry(fit1, TString::Format("1173 keV   #mu = %.3g #pm %.2g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("1332 keV  #mu = %.3g #pm %.2g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneCoPiombo.pdf");
}
