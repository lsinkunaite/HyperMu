// I/O
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdio>
#include <stdlib>
using namespace std;

//ROOT includes
#include "TAxis.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TList.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveStats.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TText.h"
//#include "TVector.h"


void alsizecheck(){

   //Some style definitions
   //gROOT->Reset();
   //gROOT->SetStyle("Plain");
   gStyle->SetPaperSize(26,20);
   gStyle->SetOptStat(1);
   gStyle->SetTitleXOffset(1.15);
   gStyle->SetTitleYOffset(1.15);
   gStyle->SetTitleBorderSize(0.1);
   gStyle->SetLegendBorderSize(0.1);
   gStyle->SetPadBottomMargin(0.12);
   gStyle->SetPadLeftMargin(0.18);
   gStyle->SetPadTopMargin(0.12);
   //gStyle->SetPadRightMargin(0.05);
   gStyle->SetCanvasColor(0);
   gStyle->SetPadColor(0);
   gStyle->SetTitleFillColor(0);
   gStyle->SetPalette(1,0);
   //gStyle->SetOptTitle(kFALSE);
   gStyle->SetLabelSize(0.045,"XYZ");
   gStyle->SetTitleSize(0.05,"XYZ");
   gStyle->SetHistLineWidth(2);

   /*******************************/
   /*        Input files          */
   /*******************************/

   // Names of the files
   // mu-decay [big plate]
   std::string filemu52b = "alacadecombo_Nevts_SciL_alL_1e65mudecay2big_1000x1000.root";
   std::string filemu55b = "alacadecombo_Nevts_SciL_alL_1e65mudecay5big_1000x1000.root";
   std::string filemu102b = "alacadecombo_Nevts_SciL_alL_1e610mudecay2big_1000x1000.root";
   std::string filemu105b = "alacadecombo_Nevts_SciL_alL_1e610mudecay5big_1000x1000.root";
   std::string filemu202b = "alacadecombo_Nevts_SciL_alL_1e620mudecay2big_1000x1000.root";
   std::string filemu205b = "alacadecombo_Nevts_SciL_alL_1e620mudecay5big_1000x1000.root";
   // mu-decay [small plate]
   std::string filemu52s = "alacadecombo_Nevts_SciL_alL_1e65mudecay2small_250x250.root";
   std::string filemu55s = "alacadecombo_Nevts_SciL_alL_1e65mudecay5small_250x250.root";
   std::string filemu102s = "alacadecombo_Nevts_SciL_alL_1e610mudecay2small_250x250.root";
   std::string filemu105s = "alacadecombo_Nevts_SciL_alL_1e610mudecay5small_250x250.root";
   std::string filemu202s = "alacadecombo_Nevts_SciL_alL_1e620mudecay2small_250x250.root";
   std::string filemu205s = "alacadecombo_Nevts_SciL_alL_1e620mudecay5small_250x250.root";

   // X-ray cascade [big plate]
   std::string filex52b = "alacadecombo_Nevts_SciL_alL_1e65goldcascade2big_1000x1000.root";
   std::string filex55b = "alacadecombo_Nevts_SciL_alL_1e65goldcascade5big_1000x1000.root";
   std::string filex102b = "alacadecombo_Nevts_SciL_alL_1e610goldcascade2big_1000x1000.root";
   std::string filex105b = "alacadecombo_Nevts_SciL_alL_1e610goldcascade5big_1000x1000.root";
   std::string filex202b = "alacadecombo_Nevts_SciL_alL_1e620goldcascade2big_1000x1000.root";
   std::string filex205b = "alacadecombo_Nevts_SciL_alL_1e620goldcascade5big_1000x1000.root";
   // X-ray cascade [small plate]
   std::string filex52s = "alacadecombo_Nevts_SciL_alL_1e65goldcascade2small_250x250.root";
   std::string filex55s = "alacadecombo_Nevts_SciL_alL_1e65goldcascade5small_250x250.root";
   std::string filex102s = "alacadecombo_Nevts_SciL_alL_1e610goldcascade2small_250x250.root";
   std::string filex105s = "alacadecombo_Nevts_SciL_alL_1e610goldcascade5small_250x250.root";
   std::string filex202s = "alacadecombo_Nevts_SciL_alL_1e620goldcascade2small_250x250.root";
   std::string filex205s = "alacadecombo_Nevts_SciL_alL_1e620goldcascade5small_250x250.root";


   /**************************************/
   /*             Analysis               */
   /**************************************/

   const int nbins=200;

   // mu-decay
   TFile* fmu52b = new TFile(TString(filemu52b));
   TFile* fmu55b = new TFile(TString(filemu55b));
   TFile* fmu102b = new TFile(TString(filemu102b));
   TFile* fmu105b = new TFile(TString(filemu105b));
   TFile* fmu202b = new TFile(TString(filemu202b));
   TFile* fmu205b = new TFile(TString(filemu205b));
   TFile* fmu52s = new TFile(TString(filemu52s));
   TFile* fmu55s = new TFile(TString(filemu55s));
   TFile* fmu102s = new TFile(TString(filemu102s));
   TFile* fmu105s = new TFile(TString(filemu105s));
   TFile* fmu202s = new TFile(TString(filemu202s));
   TFile* fmu205s = new TFile(TString(filemu205s));

   // gold-cascade
   TFile* fx52b = new TFile(TString(filex52b));
   TFile* fx55b = new TFile(TString(filex55b));
   TFile* fx102b = new TFile(TString(filex102b));
   TFile* fx105b = new TFile(TString(filex105b));
   TFile* fx202b = new TFile(TString(filex202b));
   TFile* fx205b = new TFile(TString(filex205b));
   TFile* fx52s = new TFile(TString(filex52s));
   TFile* fx55s = new TFile(TString(filex55s));
   TFile* fx102s = new TFile(TString(filex102s));
   TFile* fx105s = new TFile(TString(filex105s));
   TFile* fx202s = new TFile(TString(filex202s));
   TFile* fx205s = new TFile(TString(filex205s));


   // mu-decay
   TH1F *hmu52b = new TH1F("hmu52b","Edep",nbins,0.01,15);
   TH1F *hmu55b = new TH1F("hmu55b","Edep",nbins,0.01,15);
   TH1F *hmu102b = new TH1F("hmu102b","Edep",nbins,0.01,15);
   TH1F *hmu105b = new TH1F("hmu105b","Edep",nbins,0.01,15);
   TH1F *hmu202b = new TH1F("hmu202b","Edep",nbins,0.01,15);
   TH1F *hmu205b = new TH1F("hmu205b","Edep",nbins,0.01,15);
   TH1F *hmu52s = new TH1F("hmu52s","Edep",nbins,0.01,15);
   TH1F *hmu55s = new TH1F("hmu55s","Edep",nbins,0.01,15);
   TH1F *hmu102s = new TH1F("hmu102s","Edep",nbins,0.01,15);
   TH1F *hmu105s = new TH1F("hmu105s","Edep",nbins,0.01,15);
   TH1F *hmu202s = new TH1F("hmu202s","Edep",nbins,0.01,15);
   TH1F *hmu205s = new TH1F("hmu205s","Edep",nbins,0.01,15);

   // gold-cascade
   TH1F *hx52b = new TH1F("hx52b","Edep",nbins,0.01,15);
   TH1F *hx55b = new TH1F("hx55b","Edep",nbins,0.01,15);
   TH1F *hx102b = new TH1F("hx102b","Edep",nbins,0.01,15);
   TH1F *hx105b = new TH1F("hx105b","Edep",nbins,0.01,15);
   TH1F *hx202b = new TH1F("hx202b","Edep",nbins,0.01,15);
   TH1F *hx205b = new TH1F("hx205b","Edep",nbins,0.01,15);
   TH1F *hx52s = new TH1F("hx52s","Edep",nbins,0.01,15);
   TH1F *hx55s = new TH1F("hx55s","Edep",nbins,0.01,15);
   TH1F *hx102s = new TH1F("hx102s","Edep",nbins,0.01,15);
   TH1F *hx105s = new TH1F("hx105s","Edep",nbins,0.01,15);
   TH1F *hx202s = new TH1F("hx202s","Edep",nbins,0.01,15);
   TH1F *hx205s = new TH1F("hx205s","Edep",nbins,0.01,15);


   // mu-decay
   TTree *tmu52b = (TTree*)fmu52b->Get("Detector/SciDetD0");
   TTree *tmu55b = (TTree*)fmu55b->Get("Detector/SciDetD0");
   TTree *tmu102b = (TTree*)fmu102b->Get("Detector/SciDetD0");
   TTree *tmu105b = (TTree*)fmu105b->Get("Detector/SciDetD0");
   TTree *tmu202b = (TTree*)fmu202b->Get("Detector/SciDetD0");
   TTree *tmu205b = (TTree*)fmu205b->Get("Detector/SciDetD0");
   TTree *tmu52s = (TTree*)fmu52s->Get("Detector/SciDetD0");
   TTree *tmu55s = (TTree*)fmu55s->Get("Detector/SciDetD0");
   TTree *tmu102s = (TTree*)fmu102s->Get("Detector/SciDetD0");
   TTree *tmu105s = (TTree*)fmu105s->Get("Detector/SciDetD0");
   TTree *tmu202s = (TTree*)fmu202s->Get("Detector/SciDetD0");
   TTree *tmu205s = (TTree*)fmu205s->Get("Detector/SciDetD0");

   // gold-cascade
   TTree *tx52b = (TTree*)fx52b->Get("Detector/SciDetD0");
   TTree *tx55b = (TTree*)fx55b->Get("Detector/SciDetD0");
   TTree *tx102b = (TTree*)fx102b->Get("Detector/SciDetD0");
   TTree *tx105b = (TTree*)fx105b->Get("Detector/SciDetD0");
   TTree *tx202b = (TTree*)fx202b->Get("Detector/SciDetD0");
   TTree *tx205b = (TTree*)fx205b->Get("Detector/SciDetD0");
   TTree *tx52s = (TTree*)fx52s->Get("Detector/SciDetD0");
   TTree *tx55s = (TTree*)fx55s->Get("Detector/SciDetD0");
   TTree *tx102s = (TTree*)fx102s->Get("Detector/SciDetD0");
   TTree *tx105s = (TTree*)fx105s->Get("Detector/SciDetD0");
   TTree *tx202s = (TTree*)fx202s->Get("Detector/SciDetD0");
   TTree *tx205s = (TTree*)fx205s->Get("Detector/SciDetD0");


   // mu-decay
   tmu52b->Draw("Edep>>hmu52b","","");
   tmu55b->Draw("Edep>>hmu55b","","");
   tmu102b->Draw("Edep>>hmu102b","","");
   tmu105b->Draw("Edep>>hmu105b","","");
   tmu202b->Draw("Edep>>hmu202b","","");
   tmu205b->Draw("Edep>>hmu205b","","");
   tmu52s->Draw("Edep>>hmu52s","","");
   tmu55s->Draw("Edep>>hmu55s","","");
   tmu102s->Draw("Edep>>hmu102s","","");
   tmu105s->Draw("Edep>>hmu105s","","");
   tmu202s->Draw("Edep>>hmu202s","","");
   tmu205s->Draw("Edep>>hmu205s","","");

   // gold-cascade
   tx52b->Draw("Edep>>hx52b","","");
   tx55b->Draw("Edep>>hx55b","","");
   tx102b->Draw("Edep>>hx102b","","");
   tx105b->Draw("Edep>>hx105b","","");
   tx202b->Draw("Edep>>hx202b","","");
   tx205b->Draw("Edep>>hx205b","","");
   tx52s->Draw("Edep>>hx52s","","");
   tx55s->Draw("Edep>>hx55s","","");
   tx102s->Draw("Edep>>hx102s","","");
   tx105s->Draw("Edep>>hx105s","","");
   tx202s->Draw("Edep>>hx202s","","");
   tx205s->Draw("Edep>>hx205s","","");

   hmu52b->SetLineColor(kBlack);
   hmu55b->SetLineColor(kBlack);
   hmu102b->SetLineColor(kBlack);
   hmu105b->SetLineColor(kBlack);
   hmu202b->SetLineColor(kBlack);
   hmu205b->SetLineColor(kBlack);
   hmu52s->SetLineColor(kRed);
   hmu55s->SetLineColor(kRed);
   hmu102s->SetLineColor(kRed);
   hmu105s->SetLineColor(kRed);
   hmu202s->SetLineColor(kRed);
   hmu205s->SetLineColor(kRed);

   hx52b->SetLineColor(kBlack);
   hx55b->SetLineColor(kBlack);
   hx102b->SetLineColor(kBlack);
   hx105b->SetLineColor(kBlack);
   hx202b->SetLineColor(kBlack);
   hx205b->SetLineColor(kBlack);
   hx52s->SetLineColor(kRed);
   hx55s->SetLineColor(kRed);
   hx102s->SetLineColor(kRed);
   hx105s->SetLineColor(kRed);
   hx202s->SetLineColor(kRed);
   hx205s->SetLineColor(kRed);



   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(3,2);
   c->cd(1);
   hmu52b->SetTitle("Mu-decay: SciL 5mm AlL 2mm");
   hmu52b->GetXaxis()->SetTitle("Edep [MeV]");
   hmu52b->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu52b->Draw();
   hmu52s->Draw("sames");  
   
   c->cd(2);
   hmu55b->SetTitle("Mu-decay: SciL 5mm AlL 5mm");
   hmu55b->GetXaxis()->SetTitle("Edep [MeV]");
   hmu55b->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu55b->Draw();
   hmu55s->Draw("sames");
   
   c->cd(3);
   hmu102b->SetTitle("Mu-decay: SciL 10mm AlL 2mm");
   hmu102b->GetXaxis()->SetTitle("Edep [MeV]");
   hmu102b->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu102b->Draw();
   hmu102s->Draw("sames");
 
   c->cd(4);
   hmu105b->SetTitle("Mu-decay: SciL 10mm AlL 5mm");
   hmu105b->GetXaxis()->SetTitle("Edep [MeV]");
   hmu105b->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu105b->Draw();
   hmu105s->Draw("sames");

   c->cd(5);
   hmu202b->SetTitle("Mu-decay: SciL 20mm AlL 2mm");
   hmu205b->GetXaxis()->SetTitle("Edep [MeV]");
   hmu205b->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu205b->Draw();
   hmu205s->Draw("sames");
  
   c->cd(6);
   hmu205b->SetTitle("Mu-decay: SciL 20mm AlL 5mm");
   hmu205b->GetXaxis()->SetTitle("Edep [MeV]");
   hmu205b->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu205b->Draw();
   hmu205s->Draw("sames");
   
   c->SaveAs("AlSizeCheckPlotmu.pdf");
   c->SaveAs("AlSizeCheckPlotmu.png");
   c->SaveAs("AlSizeCheckPlotmu.C");

  
   TCanvas *d = new TCanvas("d","Edep",800,600);
   d->Divide(3,2);
   d->cd(1);
   hx52b->SetTitle("Au-cascade: SciL 5mm AlL 2mm");
   hx52b->GetXaxis()->SetTitle("Edep [MeV]");
   hx52b->GetXaxis()->SetTitle("# of counts [a.u.]");
   hx52b->Draw();
   hx52s->Draw("sames");

   d->cd(2);
   hx55b->SetTitle("Au-cascade: SciL 5mm AlL 5mm");
   hx55b->GetXaxis()->SetTitle("Edep [MeV]");
   hx55b->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx55b->Draw();
   hx55s->Draw("sames");

   d->cd(3);
   hx102b->SetTitle("Au-cascade: SciL 10mm AlL 2mm");
   hx102b->GetXaxis()->SetTitle("Edep [MeV]");
   hx102b->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx102b->Draw();
   hx102s->Draw("sames");

   d->cd(4);
   hx105b->SetTitle("Au-cascade: SciL 10mm AlL 5mm");
   hx105b->GetXaxis()->SetTitle("Edep [MeV]");
   hx105b->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx105b->Draw();
   hx105s->Draw("sames");

   d->cd(5);
   hx202b->SetTitle("Au-cascade: SciL 20mm AlL 2mm");
   hx202b->GetXaxis()->SetTitle("Edep [MeV]");
   hx202b->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx202b->Draw();
   hx202s->Draw("sames");

   d->cd(6);
   hx205b->SetTitle("Au-cascade: SciL 20mm AlL 5mm");
   hx205b->GetXaxis()->SetTitle("Edep [MeV]");
   hx205b->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx205b->Draw();
   hx205s->Draw("sames");

   d->SaveAs("AlSizeCheckPlotX.pdf");
   d->SaveAs("AlSizeCheckPlotX.png");
   d->SaveAs("AlSizeCheckPlotX.C");


}



int main() {
   alsizecheck();
   return 0;
}
