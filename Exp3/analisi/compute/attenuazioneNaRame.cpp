// c++ -o compute attenuazioneNaRame.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        247601/120,
        238159/120,
        219232/120,
        196893/120,
        184529/120
    };

    vector <double> errAmpPeak1 = {
        567.531/120,
        560.388/120,
        531.355/120,
        511.432/120,
        490.667/120
    };

    vector <double> ampPeak2 = {
        59197.7/120,
        57874.2/120,
        55738/120,
        53534.5/120,
        52392/120
    };

    vector <double> errAmpPeak2 = {
        267.604/120,
        260.243/120,
        259.476/120,
        249.051/120,
        246.87/120
    }; 

    vector <double> spessori = {
        0.11, 0.22, 0.33, 0.44, 0.54
    };

    vector <double> errSpessori(5, 0.005);

    TCanvas *canvasAtt = new TCanvas("canvasAtt", "canvasAtt", 800, 500);

    TGraphErrors *graph1 = new TGraphErrors(5, &spessori[0], &ampPeak1[0], &errSpessori[0], &errAmpPeak1[0]);
    TGraphErrors *graph2 = new TGraphErrors(5, &spessori[0], &ampPeak2[0], &errSpessori[0], &errAmpPeak2[0]);

    graph1->GetXaxis()->SetRangeUser(0, 1);
    graph1->GetYaxis()->SetRangeUser(400, 2100);

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

    TLegend *leg = new TLegend(0.5, 0.8, 0.89, 0.9);
    leg->AddEntry(fit1, TString::Format("511 keV   #mu = %.3g #pm %.2g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("1274 keV   #mu = %.3g #pm %.2g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneNaRame.pdf");
}
