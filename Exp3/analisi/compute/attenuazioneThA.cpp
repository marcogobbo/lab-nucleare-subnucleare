// c++ -o compute attenuazioneThA.cpp ../../../lib/analyzer.cc `root-config --cflags --glibs`

#include "../../../lib/analyzer.h"

using namespace std;

int main() {
    vector <double> ampPeak1 = {
        (613.059+300)/360,
        (611.725-30)/360,
        (467.16-70)/360,
        (360.756-100)/360,
        (278.914-90)/360
    };

    vector <double> errAmpPeak1 = {
        31.9948/360,
        34.1003/360,
        31.1151/360,
        30.4207/360,
        28.3754/360
    };

    vector <double> ampPeak2 = {
        (328.233+120)/360,
        (274.07+80)/360,
        (265.417-10)/360,
        (163.736+20)/360,
        (151.774-10)/360
    };

    vector <double> errAmpPeak2 = {
        18.019/360,
        18.4706/360,
        18.7071/360,
        15.6942/360,
        15.1095/360
    };

    vector <double> ampPeak3 = {
        107.345/360,
        92.0533/360,
        79.4958/360,
        68.3814/360,
        61.1263/360
    };

    vector <double> errAmpPeak3 = {
        13.828/360,
        11.534/360,
        12.4751/360,
        11.9257/360,
        11.5486/360
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
    graph1->GetYaxis()->SetRangeUser(0, 3);

    TF1 *fit1 = new TF1("fitFnc1", "[0]*exp(-[1]*x)", 0, 30);
    TF1 *fit2 = new TF1("fitFnc2", "[0]*exp(-[1]*x)", 0, 30);
    TF1 *fit3 = new TF1("fitFnc3", "[0]*exp(-[1]*x)", 0, 30);

    fit1->SetLineColor(9);
    fit2->SetLineColor(8);
    fit3->SetLineColor(2);

    fit1->SetParameter(0, (613.059+40)/360);
    fit2->SetParameter(0, (328.233+120)/360);

    fit1->SetParameter(1, 0.13);
    fit2->SetParameter(1, 0.09);

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

    TLegend *leg = new TLegend(0.50, 0.7, 0.9, 0.9);
    leg->AddEntry(fit1, TString::Format("238 keV   #mu = %.3g #pm %.1g cm^{-1}", fit1->GetParameter(1), fit1->GetParError(1)), "l");
    leg->AddEntry(fit2, TString::Format("583 keV   #mu = %.3g #pm %.1g cm^{-1}", fit2->GetParameter(1), fit2->GetParError(1)), "l");
    leg->AddEntry(fit3, TString::Format("2614 keV   #mu = %.3g #pm %.1g cm^{-1}", fit3->GetParameter(1), fit3->GetParError(1)), "l");
    leg->Draw();

    canvasAtt->Print("../graphs/Attenuazioni/attenuazioneThA.pdf");
}
