// c++ -o compute attenuazioneThA.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        613.059/120,
        611.725/120,
        467.16/120,
        360.756/120,
        278.914/120
    };

    vector <double> errAmpPeak1 = {
        31.9948/120,
        34.1003/120,
        31.1151/120,
        30.4207/120,
        28.3754/120
    };

    vector <double> ampPeak2 = {
        328.233/120,
        274.07/120,
        265.417/120,
        163.736/120,
        151.774/120
    };

    vector <double> errAmpPeak2 = {
        18.019/120,
        18.4706/120,
        18.7071/120,
        15.6942/120,
        15.1095/120
    };

    vector <double> ampPeak3 = {
        107.345/120,
        92.0533/120,
        79.4958/120,
        68.3814/120,
        61.1263/120
    };

    vector <double> errAmpPeak3 = {
        13.828/120,
        11.534/120,
        12.4751/120,
        11.9257/120,
        11.5486/120
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
    graph1->GetYaxis()->SetRangeUser(0, 6);

    TF1 *fit1 = new TF1("fitFnc1", "[0]*exp(-[1]*x)", 0, 30);
    TF1 *fit2 = new TF1("fitFnc2", "[0]*exp(-[1]*x)", 0, 30);
    TF1 *fit3 = new TF1("fitFnc3", "[0]*exp(-[1]*x)", 0, 30);

    fit1->SetLineColor(9);
    fit2->SetLineColor(8);
    fit3->SetLineColor(2);

    fit1->SetParameter(0, 613.059/120);
    fit2->SetParameter(0, 328.233/120);
    fit2->SetParameter(0, 107.345/120);

    fit1->SetParameter(1, 0.60);
    fit2->SetParameter(1, 0.60);
    fit2->SetParameter(1, 0.60);

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
