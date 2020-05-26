// c++ -o compute attenuazioneThPiombo.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        11438.4/120,
        3200.12/120,
        2214.38/120,
        423.564/120,
    };

    vector <double> errAmpPeak1 = {
        112.192/120,
        62.742/120,
        54.57/120,
        30.37/120,
    };

    vector <double> ampPeak2 = {
        5733.01/120,
        3691.61/120,
        4038.38/120,
        2584.62/120,
        983.11/120
    };

    vector <double> errAmpPeak2 = {
        77.54/120,
        62.65/120,
        65.45/120,
        52.99/120,
        33.54/120
    };

    vector <double> ampPeak3 = {
        1897.42/120,
        1498.43/120,
        1676.32/120,
        1288.42/120,
        828.686/120 
    };

    vector <double> errAmpPeak3 = {
        44.06/120,
        39.20/120,
        41.41/120,
        36.29/120,
        29.42/120
    };

    vector <double> spessori1 = {
        0.1, 0.21, 0.33, 0.58
    };

    vector <double> spessori = {
        0.1, 0.21, 0.33, 0.58, 1.08
    };

    vector <double> errSpessori1(4, 0.005);
    vector <double> errSpessori(5, 0.005);

    TCanvas *canvasAtt = new TCanvas("canvasAtt", "canvasAtt", 800, 500);

    TGraphErrors *graph1 = new TGraphErrors(4, &spessori1[0], &ampPeak1[0], &errSpessori1[0], &errAmpPeak1[0]);
    TGraphErrors *graph2 = new TGraphErrors(5, &spessori[0], &ampPeak2[0], &errSpessori[0], &errAmpPeak2[0]);
    TGraphErrors *graph3 = new TGraphErrors(5, &spessori[0], &ampPeak3[0], &errSpessori[0], &errAmpPeak3[0]);

    graph1->GetXaxis()->SetRangeUser(0, 1.5);
    graph1->GetYaxis()->SetRangeUser(0, 200);

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

    graph1->SetMarkerSize(2);
    graph1->SetMarkerStyle(5);

    graph2->SetMarkerSize(2);
    graph2->SetMarkerStyle(4);

    graph3->SetMarkerSize(2);
    graph3->SetMarkerStyle(6);

    graph1->Draw("AP");
    graph2->Draw("P SAME");
    graph3->Draw("P SAME");

    graph1->Fit("fitFnc1");
    graph2->Fit("fitFnc2");
    graph3->Fit("fitFnc3");

    cout << "\n" << endl;
    cout << fit1->GetChisquare()/fit1->GetNDF() << endl;
    cout << fit2->GetChisquare()/fit2->GetNDF() << endl;
    cout << fit3->GetChisquare()/fit3->GetNDF() << endl;
    cout << "\n" << endl;

    cout << "\n" << endl;
    cout << fit1->GetProb() << endl;
    cout << fit2->GetProb() << endl;
    cout << fit3->GetProb() << endl;
    cout << "\n" << endl;

    TLegend *leg = new TLegend(0.44, 0.7, 0.9, 0.9);
    leg->AddEntry(fit1, TString::Format("238 keV   #mu = %.3g #pm %.1g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("583 keV   #mu = %.3g #pm %.1g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->AddEntry(fit3, TString::Format("2614 keV   #mu = %.3g #pm %.1g cm^{-1}", fit3->GetParameter(1), fit3->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneThPiombo.pdf");
}
