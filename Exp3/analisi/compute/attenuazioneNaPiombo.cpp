// c++ -o compute attenuazioneNaPiombo.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        245774/120,
        207123/120,
        185472/120,
        128385/120,
        51660.2/120
    };

    vector <double> errAmpPeak1 = {
        562.284/120,
        511.238/120,
        487.445/120,
        401.402/120,
        253.892/120
    };

    vector <double> ampPeak2 = {
        63216.4/120,
        64176.7/120,
        64583.6/120,
        59677.9/120,
        47367/120
    };

    vector <double> errAmpPeak2 = {
        288.641/120,
        287.75/120,
        286/120,
        266.446/120,
        212.903/120
    };

    vector <double> spessori = {
        0.1, 0.21, 0.33, 0.58, 1.08
    };

    vector <double> errSpessori(5, 0.005);

    TCanvas *canvasAtt = new TCanvas("canvasAtt", "canvasAtt", 800, 500);

    TGraphErrors *graph1 = new TGraphErrors(5, &spessori[0], &ampPeak1[0], &errSpessori[0], &errAmpPeak1[0]);
    TGraphErrors *graph2 = new TGraphErrors(5, &spessori[0], &ampPeak2[0], &errSpessori[0], &errAmpPeak2[0]);
    /*graph1->GetXaxis()->SetRangeUser(0, 1.5);
    graph1->GetYaxis()->SetRangeUser(3000, 27000);*/

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

    TLegend *leg = new TLegend(0.47, 0.8, 0.89, 0.9);
    leg->AddEntry(fit1, TString::Format("511 keV   #mu = %.3g #pm %.2g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("1274 keV   #mu = %.3g #pm %.2g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneNaPiombo.pdf");
}
