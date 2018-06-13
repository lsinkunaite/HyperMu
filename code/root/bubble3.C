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

// ROOT
#include "TAxis.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include "TGraph.h"
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

void bubble3(){

   //Some style definitions
   //gROOT->Reset();
   //gROOT->SetStyle("Plain");
   gStyle->SetPaperSize(26,20);
   gStyle->SetOptStat(1);
   gStyle->SetTitleXOffset(1.15);
   gStyle->SetTitleYOffset(1.15);
   gStyle->SetTitleBorderSize(0.1);
   gStyle->SetLegendBorderSize(0.1);
   gStyle->SetPadBottomMargin(0.18);
   gStyle->SetPadLeftMargin(0.18);
   gStyle->SetPadTopMargin(0.12);
   //gStyle->SetPadRightMargin(0.05);
   gStyle->SetCanvasColor(0);
   gStyle->SetPadColor(0);
   gStyle->SetPalette(1,0);
   //gStyle->SetOptTitle(kFALSE);
   gStyle->SetLabelSize(0.045,"XYZ");
   gStyle->SetTitleSize(0.05,"XYZ");
   gStyle->SetHistLineWidth(2);

   /************************************/
   /*           Input files            */
   /************************************/

   // Names of the files
   std::string filemu0 = "../../simdata/bubble3/bubble_20mm_SciD_Nevts_SciSphere_PbD_1e6mudecay0.root";
   std::string filemu2 = "../../simdata/bubble3/bubble_20mm_SciD_Nevts_SciSphere_PbD_1e6mudecay2.root";
   std::string filemu5 = "../../simdata/bubble3/bubble_20mm_SciD_Nevts_SciSphere_PbD_1e6mudecay5.root";
   std::string filex0 = "../../simdata/bubble3/bubble_20mm_SciD_Nevts_SciSphere_PbD_1e6goldcascade0.root";
   std::string filex2 = "../../simdata/bubble3/bubble_20mm_SciD_Nevts_SciSphere_PbD_1e6goldcascade2.root";
   std::string filex5 = "../../simdata/bubble3/bubble_20mm_SciD_Nevts_SciSphere_PbD_1e6goldcascade5.root";

   /************************************/
   /*             Analysis             */
   /************************************/

   const int nbins=250;

   TFile* fmu0 = new TFile(TString(filemu0));
   TFile* fmu2 = new TFile(TString(filemu2));
   TFile* fmu5 = new TFile(TString(filemu5));
   TFile* fx0 = new TFile(TString(filex0));
   TFile* fx2 = new TFile(TString(filex2));
   TFile* fx5 = new TFile(TString(filex5));

   // histograms
   TH1F *hmu0 = new TH1F("hmu0","Edep",nbins,0.01,10);
   TH1F *hmu2 = new TH1F("hmu2","Edep",nbins,0.01,10);
   TH1F *hmu5 = new TH1F("hmu5","Edep",nbins,0.01,10);
   TH1F *hx0 = new TH1F("hx0","Edep",nbins,0.01,2.5);
   TH1F *hx2 = new TH1F("hx2","Edep",nbins,0.01,2.5);
   TH1F *hx5 = new TH1F("hx5","Edep",nbins,0.01,2.5);
   // normalised histograms
   TH1F *hmu0n = new TH1F("hmu0n","Edep",nbins,0.01,18);
   TH1F *hmu2n = new TH1F("hmu2n","Edep",nbins,0.01,18);
   TH1F *hmu5n = new TH1F("hmu5n","Edep",nbins,0.01,18);
   TH1F *hx0n = new TH1F("hx0n","Edep",nbins,0.01,9);
   TH1F *hx2n = new TH1F("hx2n","Edep",nbins,0.01,9);
   TH1F *hx5n = new TH1F("hx5n","Edep",nbins,0.01,9);

   TTree *tmu0 = (TTree*)fmu0->Get("Detector/SciDet");
   TTree *tmu2 = (TTree*)fmu2->Get("Detector/SciDet");
   TTree *tmu5 = (TTree*)fmu5->Get("Detector/SciDet");
   TTree *tx0 = (TTree*)fx0->Get("Detector/SciDet");
   TTree *tx2 = (TTree*)fx2->Get("Detector/SciDet");
   TTree *tx5 = (TTree*)fx5->Get("Detector/SciDet");

   // histograms
   tmu0->Draw("Edep>>hmu0","","");
   tmu2->Draw("Edep>>hmu2","","");
   tmu5->Draw("Edep>>hmu5","","");
   tx0->Draw("Edep>>hx0","","");
   tx2->Draw("Edep>>hx2","","");
   tx5->Draw("Edep>>hx5","","");
   // normalised histograms
   tmu0->Draw("Edep>>hmu0n","","");
   tmu2->Draw("Edep>>hmu2n","","");
   tmu5->Draw("Edep>>hmu5n","","");
   tx0->Draw("Edep>>hx0n","","");
   tx2->Draw("Edep>>hx2n","","");
   tx5->Draw("Edep>>hx5n","","");

   // histograms
   hmu0->SetLineColor(kBlack);
   hmu2->SetLineColor(kRed);
   hmu5->SetLineColor(kGreen-2);
   hx0->SetLineColor(kBlack);
   hx2->SetLineColor(kRed);
   hx5->SetLineColor(kGreen-2);
   // normalised histograms
   hmu0n->SetLineColor(kBlack);
   hmu2n->SetLineColor(kRed);
   hmu5n->SetLineColor(kGreen-2);
   hx0n->SetLineColor(kBlack);
   hx2n->SetLineColor(kRed);
   hx5n->SetLineColor(kGreen-2);

   /************************************/
   /*            Plotting              */
   /************************************/

   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(2,2);
   c->cd(1);
   hmu0->SetTitle("Mu-decay: 20-mm SciD {0,2,5}-mm Pb");
   hmu0->GetXaxis()->SetTitle("Edep [MeV]");
   hmu0->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu0->GetYaxis()->SetTitleOffset(2.0);
   hmu0->Draw();
   c->Update();
   TPaveStats *stmu0 = (TPaveStats*)hmu0->GetListOfFunctions()->FindObject("stats");
   stmu0->SetY1NDC(0.4); stmu0->SetY2NDC(0.55);
   stmu0->SetTextColor(kBlack);
   hmu2->Draw("sames");
   c->Update();
   TPaveStats *stmu2 = (TPaveStats*)hmu2->GetListOfFunctions()->FindObject("stats");
   stmu2->SetY1NDC(0.6); stmu2->SetY2NDC(0.75);
   stmu2->SetTextColor(kRed);
   hmu5->Draw("sames");
   c->Update();
   TPaveStats *stmu5 = (TPaveStats*)hmu5->GetListOfFunctions()->FindObject("stats");
   stmu5->SetTextColor(kGreen-2);
   stmu5->Draw();


   c->cd(2);
   gPad->SetLogy();
   hmu0n->SetTitle("Mu-decay [log]: 20-mm SciD {0,2,5}-mm Pb");
   hmu0n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu0n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu0n->GetYaxis()->SetTitleOffset(2.0);
   hmu0n->Draw();
   c->Update();
   TPaveStats *stmu0n = (TPaveStats*)hmu0n->GetListOfFunctions()->FindObject("stats");
   stmu0n->SetY1NDC(0.4); stmu0n->SetY2NDC(0.55);
   stmu0n->SetTextColor(kBlack);
   hmu2n->Draw("sames");
   c->Update();
   TPaveStats *stmu2n = (TPaveStats*)hmu2n->GetListOfFunctions()->FindObject("stats");
   stmu2n->SetY1NDC(0.6); stmu2n->SetY2NDC(0.75);
   stmu2n->SetTextColor(kRed);
   hmu5n->Draw("sames");
   c->Update();
   TPaveStats *stmu5n = (TPaveStats*)hmu5n->GetListOfFunctions()->FindObject("stats");
   stmu5n->SetTextColor(kGreen-2);
   stmu5n->Draw();
   
   c->cd(3);
   hx0->SetTitle("X-ray cascade: 20-mm SciD {0,2,5}-mm Pb");
   hx0->GetXaxis()->SetTitle("Edep [MeV]");
   hx0->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx0->GetYaxis()->SetTitleOffset(2.0);
   hx0->Draw();
   c->Update();
   TPaveStats *stx0 = (TPaveStats*)hx0->GetListOfFunctions()->FindObject("stats");
   stx0->SetY1NDC(0.4); stx0->SetY2NDC(0.55);
   stx0->SetTextColor(kBlack);
   hx2->Draw("sames");
   c->Update();
   TPaveStats *stx2 = (TPaveStats*)hx2->GetListOfFunctions()->FindObject("stats");
   stx2->SetY1NDC(0.6); stx2->SetY2NDC(0.75);
   stx2->SetTextColor(kRed);
   hx5->Draw("sames");
   c->Update();
   TPaveStats *stx5 = (TPaveStats*)hx5->GetListOfFunctions()->FindObject("stats");
   stx5->SetTextColor(kGreen-2);
   stx5->Draw();

   c->cd(4);
   gPad->SetLogy();
   hx0n->SetTitle("X-ray cascade [log]: 20-mm SciD {0,2,5}-mm Pb");
   hx0n->GetXaxis()->SetTitle("Edep [MeV]");
   hx0n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx0n->GetYaxis()->SetTitleOffset(2.0);
   hx0n->Draw();
   c->Update();
   TPaveStats *stx0n = (TPaveStats*)hx0n->GetListOfFunctions()->FindObject("stats");
   stx0n->SetY1NDC(0.4); stx0n->SetY2NDC(0.55);
   stx0n->SetTextColor(kBlack);
   hx2n->Draw("sames");
   c->Update();
   TPaveStats *stx2n = (TPaveStats*)hx2n->GetListOfFunctions()->FindObject("stats");
   stx2n->SetY1NDC(0.6); stx2n->SetY2NDC(0.75);
   stx2n->SetTextColor(kRed);
   hx5n->Draw("sames");
   c->Update();
   TPaveStats *stx5n = (TPaveStats*)hx5n->GetListOfFunctions()->FindObject("stats");
   stx5n->SetTextColor(kGreen-2);
   stx5n->Draw();

   c->SaveAs("BubblePlot3.pdf");
   c->SaveAs("BubblePlot3.png");
   c->SaveAs("BubblePlot3.C");


}



int main() {
   bubble3();
   return 0;
}
