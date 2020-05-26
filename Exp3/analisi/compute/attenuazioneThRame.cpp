// c++ -o compute attenuazioneThRame.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        21694.5/120,
        17527.3/120,
        13805.7/120,
        11254.2/120,
        10967.3/120
    };

    vector <double> errAmpPeak1 = {
        152.7/120,
        138.1/120,
        123.4/120,
        112.2/120,
        110.9/120
    };

    vector <double> ampPeak2 = {
        5842.68/120,
        4965.08/120,
        4265.32/120,
        3710.1/120,
        3769.13/120 
    };

    vector <double> errAmpPeak2 = {
        78.6/120,
        72.6/120,
        66.7/120,
        62.9/120,
        63.5/120
    };

    vector <double> ampPeak3 = {
        1921.7/120,
        1716.23/120,
        1526.62/120,
        1341.54/120,
        1379.01/120
    };

    vector <double> errAmpPeak3 = {
        44.4/120,
        41.8/120,
        39.5/120,
        37.3/120,
        37.6/120
    };

    vector <double> spessori = {
        0.11, 0.22, 0.33, 0.44, 0.54
    };

    vector <double> errSpessori(5, 0.005);

    TCanvas *canvasAtt = new TCanvas("canvasAtt", "canvasAtt", 800, 500);

    TGraphErrors *graph1 = new TGraphErrors(5, &spessori[0], &ampPeak1[0], &errSpessori[0], &errAmpPeak1[0]);
    TGraphErrors *graph2 = new TGraphErrors(5, &spessori[0], &ampPeak2[0], &errSpessori[0], &errAmpPeak2[0]);
    TGraphErrors *graph3 = new TGraphErrors(5, &spessori[0], &ampPeak3[0], &errSpessori[0], &errAmpPeak3[0]);

    graph1->GetXaxis()->SetRangeUser(0, 1);
    graph1->GetYaxis()->SetRangeUser(0, 300);

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

    TLegend *leg = new TLegend(0.52, 0.72, 0.9, 0.9);
    leg->AddEntry(fit1, TString::Format("238 keV   #mu = %.3g #pm %.1g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("583 keV   #mu = %.3g #pm %.1g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->AddEntry(fit3, TString::Format("2614 keV   #mu = %.3g #pm %.1g cm^{-1}", fit3->GetParameter(1), fit3->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneThRame.pdf");
}
