// c++ -o compute attenuazioneThA1460.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        613.059/360,
        611.725/360,
        467.16/360,
        360.756/360,
        278.914/360
    };

    vector <double> errAmpPeak1 = {
        31.9948/360,
        34.1003/360,
        31.1151/360,
        30.4207/360,
        28.3754/360
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

    graph1->GetXaxis()->SetRangeUser(0, 30);
    graph1->GetYaxis()->SetRangeUser(0, 5);

    TF1 *fit1 = new TF1("fitFnc1", "[0]", 0, 30);

    fit1->SetLineColor(9);

    fit1->SetParameter(0, 2);

    graph1->SetTitle("Attenuazione con acqua ^{228}Th picco a 1460 keV");
    graph1->GetYaxis()->SetTitle("Rate");
    graph1->GetXaxis()->SetTitle("Spessore [cm]");

    graph1->SetMarkerSize(10);

    graph1->Draw("AP");

    graph1->Fit("fitFnc1");

    cout << "\n" << endl;
    cout << fit1->GetChisquare()/fit1->GetNDF() << endl;
    cout << "\n" << endl;

    cout << "\n" << endl;
    cout << fit1->GetProb() << endl;
    cout << "\n" << endl;

    TLegend *leg = new TLegend(0.57, 0.8, 0.9, 0.9);
    leg->AddEntry(fit1, TString::Format("1460 keV   k = %.3g #pm %.1g cm^{-1}", fit1->GetParameter(0), fit1->GetParError(0)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneThA1460.pdf");
}
