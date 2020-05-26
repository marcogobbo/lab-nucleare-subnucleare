// c++ -o compute attenuazioneNaA.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        20174.4/360,
        14272.3/360,
        9438.53/360,
        6669.1/360,
        4638.96/360
    };

    vector <double> errAmpPeak1 = {
        272.333/360,
        229.874/360,
        99.96/360,
        158.277/360,
        71.131/360
    };

    vector <double> ampPeak2 = {
        6080.33/360,
        4813.54/360,
        3769.91/360,
        2960.57/360,
        2179.57/360
    };

    vector <double> errAmpPeak2 = {
        145.59/360,
        130.701/360,
        112.821/360,
        101.81/360,
        47.672/360
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

    /*graph1->GetXaxis()->SetRangeUser(0, 30);
    graph1->GetYaxis()->SetRangeUser(0, 100);*/

    TF1 *fit1 = new TF1("fitFnc1", "[0]*exp(-[1]*x)", 0, 30);
    TF1 *fit2 = new TF1("fitFnc2", "[0]*exp(-[1]*x)", 0, 30);

    fit1->SetLineColor(9);
    fit2->SetLineColor(8);

    fit1->SetParameter(0, 1983);
    fit2->SetParameter(0, 700.4);

    fit1->SetParameter(1, 0.0628);
    fit2->SetParameter(1, 0.0378);

    graph1->SetTitle("Attenuazione con acqua ^{22}Na");
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

    TLegend *leg = new TLegend(0.53, 0.8, 0.9, 0.9);
    leg->AddEntry(fit1, TString::Format("511 keV   #mu = %.3g #pm %.1g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("1274 keV   #mu = %.3g #pm %.1g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneNaA.pdf");
}
