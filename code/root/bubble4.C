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

void bubble4(){

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
   gStyle->SetPalette(1,0);
   //gStyle->SetOptTitle(kFALSE);
   gStyle->SetLabelSize(0.045,"XYZ");
   gStyle->SetTitleSize(0.05,"XYZ");
   gStyle->SetHistLineWidth(2);

   /*********************************/
   /*         Input files           */
   /*********************************/

   // Names of the files
   // With {250,500}-mm BGO 3-mm Al
   std::string filemu250 = "../../simdata/bubble4/bubble_250mm_BGO_2x5mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filemu500 = "../../simdata/bubble4/bubble_500mm_BGO_2x5mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filex250 = "../../simdata/bubble4/bubble_250mm_BGO_2x5mm_SciD_Nevts_SciSphere_3mm_Al_1e6goldcascade.root";
   std::string filex500 = "../../simdata/bubble4/bubble_500mm_BGO_2x5mm_SciD_Nevts_SciSphere_3mm_Al_1e6goldcascade.root";
   // With {250,500}-mm BGO 6-mm Al
   std::string file6Almu250 = "../../simdata/bubble4/bubble_250mm_BGO_2x5mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Almu500 = "../../simdata/bubble4/bubble_500mm_BGO_2x5mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Alx250 = "../../simdata/bubble4/bubble_250mm_BGO_2x5mm_SciD_Nevts_SciSphere_6mm_Al_1e6goldcascade.root";
   std::string file6Alx500 = "../../simdata/bubble4/bubble_500mm_BGO_2x5mm_SciD_Nevts_SciSphere_6mm_Al_1e6goldcascade.root";
 

   /*********************************/
   /*           Analysis            */
   /*********************************/

   const int nbins = 150;
  
   // TFiles
   // 3-mm Al 
   TFile* fmu250 = new TFile(TString(filemu250));
   TFile* fmu500 = new TFile(TString(filemu500));
   TFile* fx250 = new TFile(TString(filex250));
   TFile* fx500 = new TFile(TString(filex500));
   // 6-mm Al
   TFile* f6Almu250 = new TFile(TString(file6Almu250));
   TFile* f6Almu500 = new TFile(TString(file6Almu500));
   TFile* f6Alx250 = new TFile(TString(file6Alx250));
   TFile* f6Alx500 = new TFile(TString(file6Alx500));

   // Histograms
   // 3-mm Al
   TH1F *hmu250SciDet1 = new TH1F("hmu250SciDet1","Edep",nbins,0,10);
   TH1F *hmu250SciDet2 = new TH1F("hmu250SciDet2","Edep",nbins,0,10);
   TH1F *hmu250BGODet = new TH1F("hmu250BGODet","Edep",nbins,0,60);
   TH1F *hmu500SciDet1 = new TH1F("hmu500SciDet1","Edep",nbins,0,10);
   TH1F *hmu500SciDet2 = new TH1F("hmu500SciDet2","Edep",nbins,0,10);
   TH1F *hmu500BGODet = new TH1F("hmu500BGODet","Edep",nbins,0,60);
   TH1F *hx250SciDet1 = new TH1F("hx250SciDet1","Edep",nbins,0,6);
   TH1F *hx250SciDet2 = new TH1F("hx250SciDet2","Edep",nbins,0,6);
   TH1F *hx250BGODet = new TH1F("hx250BGODet","Edep",nbins,0,12);
   TH1F *hx500SciDet1 = new TH1F("hx500SciDet1","Edep",nbins,0,6);
   TH1F *hx500SciDet2 = new TH1F("hx500SciDet2","Edep",nbins,0,6);
   TH1F *hx500BGODet = new TH1F("hx500BGODet","Edep",nbins,0,12);
   // 3-mm Al [copies]
   TH1F *hmu250SciDet1n = new TH1F("hmu250SciDet1n","Edep",nbins,0,9);
   TH1F *hmu250SciDet2n = new TH1F("hmu250SciDet2n","Edep",nbins,0,9);
   TH1F *hmu250BGODetn = new TH1F("hmu250BGODetn","Edep",nbins,0,50);
   TH1F *hmu500SciDet1n = new TH1F("hmu500SciDet1n","Edep",nbins,0,9);
   TH1F *hmu500SciDet2n = new TH1F("hmu500SciDet2n","Edep",nbins,0,9);
   TH1F *hmu500BGODetn = new TH1F("hmu500BGODetn","Edep",nbins,0,50);
   TH1F *hx250SciDet1n = new TH1F("hx250SciDet1n","Edep",nbins,0,9);
   TH1F *hx250SciDet2n = new TH1F("hx250SciDet2n","Edep",nbins,0,9);
   TH1F *hx250BGODetn = new TH1F("hx250BGODetn","Edep",nbins,0,50);
   TH1F *hx500SciDet1n = new TH1F("hx500SciDet1n","Edep",nbins,0,9);
   TH1F *hx500SciDet2n = new TH1F("hx500SciDet2n","Edep",nbins,0,9);
   TH1F *hx500BGODetn = new TH1F("hx500BGODetn","Edep",nbins,0,50);
   // 6-mm Al
   TH1F *h6Almu250SciDet1 = new TH1F("h6Almu250SciDet1","Edep",nbins,0,10);
   TH1F *h6Almu250SciDet2 = new TH1F("h6Almu250SciDet2","Edep",nbins,0,10);
   TH1F *h6Almu250BGODet = new TH1F("h6Almu250BGODet","Edep",nbins,0,60);
   TH1F *h6Almu500SciDet1 = new TH1F("h6Almu500SciDet1","Edep",nbins,0,10);
   TH1F *h6Almu500SciDet2 = new TH1F("h6Almu500SciDet2","Edep",nbins,0,10);
   TH1F *h6Almu500BGODet = new TH1F("h6Almu500BGODet","Edep",nbins,0,60);
   TH1F *h6Alx250SciDet1 = new TH1F("h6Alx250SciDet1","Edep",nbins,0,6);
   TH1F *h6Alx250SciDet2 = new TH1F("h6Alx250SciDet2","Edep",nbins,0,6);
   TH1F *h6Alx250BGODet = new TH1F("h6Alx250BGODet","Edep",nbins,0,12);
   TH1F *h6Alx500SciDet1 = new TH1F("h6Alx500SciDet1","Edep",nbins,0,6);
   TH1F *h6Alx500SciDet2 = new TH1F("h6Alx500SciDet2","Edep",nbins,0,6);
   TH1F *h6Alx500BGODet = new TH1F("h6Alx500BGODet","Edep",nbins,0,12);
   // 6-mm Al [copies]
   TH1F *h6Almu250SciDet1n = new TH1F("h6Almu250SciDet1n","Edep",nbins,0,9);
   TH1F *h6Almu250SciDet2n = new TH1F("h6Almu250SciDet2n","Edep",nbins,0,9);
   TH1F *h6Almu250BGODetn = new TH1F("h6Almu250BGODetn","Edep",nbins,0,50);
   TH1F *h6Almu500SciDet1n = new TH1F("h6Almu500SciDet1n","Edep",nbins,0,9);
   TH1F *h6Almu500SciDet2n = new TH1F("h6Almu500SciDet2n","Edep",nbins,0,9);
   TH1F *h6Almu500BGODetn = new TH1F("h6Almu500BGODetn","Edep",nbins,0,50);
   TH1F *h6Alx250SciDet1n = new TH1F("h6Alx250SciDet1n","Edep",nbins,0,9);
   TH1F *h6Alx250SciDet2n = new TH1F("h6Alx250SciDet2n","Edep",nbins,0,9);
   TH1F *h6Alx250BGODetn = new TH1F("h6Alx250BGODetn","Edep",nbins,0,50);
   TH1F *h6Alx500SciDet1n = new TH1F("h6Alx500SciDet1n","Edep",nbins,0,9);
   TH1F *h6Alx500SciDet2n = new TH1F("h6Alx500SciDet2n","Edep",nbins,0,9);
   TH1F *h6Alx500BGODetn = new TH1F("h6Alx500BGODetn","Edep",nbins,0,50);
     
   // TTrees
   // 3-mm Al
   TTree *tmu250SciDet1 = (TTree*)fmu250->Get("Detector/SciDet1");
   TTree *tmu250SciDet2 = (TTree*)fmu250->Get("Detector/SciDet2");
   TTree *tmu250BGODet = (TTree*)fmu250->Get("Detector/BGODet");
   TTree *tmu500SciDet1 = (TTree*)fmu500->Get("Detector/SciDet1");
   TTree *tmu500SciDet2 = (TTree*)fmu500->Get("Detector/SciDet2");
   TTree *tmu500BGODet = (TTree*)fmu500->Get("Detector/BGODet");
   TTree *tx250SciDet1 = (TTree*)fx250->Get("Detector/SciDet1");
   TTree *tx250SciDet2 = (TTree*)fx250->Get("Detector/SciDet2");
   TTree *tx250BGODet = (TTree*)fx250->Get("Detector/BGODet");
   TTree *tx500SciDet1 = (TTree*)fx500->Get("Detector/SciDet1");
   TTree *tx500SciDet2 = (TTree*)fx500->Get("Detector/SciDet2");
   TTree *tx500BGODet = (TTree*)fx500->Get("Detector/BGODet");
   // 6-mm Al
   TTree *t6Almu250SciDet1 = (TTree*)f6Almu250->Get("Detector/SciDet1");
   TTree *t6Almu250SciDet2 = (TTree*)f6Almu250->Get("Detector/SciDet2");
   TTree *t6Almu250BGODet = (TTree*)f6Almu250->Get("Detector/BGODet");
   TTree *t6Almu500SciDet1 = (TTree*)f6Almu500->Get("Detector/SciDet1");
   TTree *t6Almu500SciDet2 = (TTree*)f6Almu500->Get("Detector/SciDet2");
   TTree *t6Almu500BGODet = (TTree*)f6Almu500->Get("Detector/BGODet");
   TTree *t6Alx250SciDet1 = (TTree*)f6Alx250->Get("Detector/SciDet1");
   TTree *t6Alx250SciDet2 = (TTree*)f6Alx250->Get("Detector/SciDet2");
   TTree *t6Alx250BGODet = (TTree*)f6Alx250->Get("Detector/BGODet");
   TTree *t6Alx500SciDet1 = (TTree*)f6Alx500->Get("Detector/SciDet1");
   TTree *t6Alx500SciDet2 = (TTree*)f6Alx500->Get("Detector/SciDet2");
   TTree *t6Alx500BGODet = (TTree*)f6Alx500->Get("Detector/BGODet");
   
   
   // Drawings
   // 3-mm Al  
   tmu250SciDet1->Draw("Edep>>hmu250SciDet1","","");
   tmu250SciDet2->Draw("Edep>>hmu250SciDet2","","");
   tmu250BGODet->Draw("Edep>>hmu250BGODet","","");
   tmu500SciDet1->Draw("Edep>>hmu500SciDet1","","");
   tmu500SciDet2->Draw("Edep>>hmu500SciDet2","","");
   tmu500BGODet->Draw("Edep>>hmu500BGODet","","");
   tx250SciDet1->Draw("Edep>>hx250SciDet1","","");
   tx250SciDet2->Draw("Edep>>hx250SciDet2","","");
   tx250BGODet->Draw("Edep>>hx250BGODet","","");
   tx500SciDet1->Draw("Edep>>hx500SciDet1","","");
   tx500SciDet2->Draw("Edep>>hx500SciDet2","","");
   tx500BGODet->Draw("Edep>>hx500BGODet","","");
   // 3-mm Al [copies]
   tmu250SciDet1->Draw("Edep>>hmu250SciDet1n","","");
   tmu250SciDet2->Draw("Edep>>hmu250SciDet2n","","");
   tmu250BGODet->Draw("Edep>>hmu250BGODetn","","");
   tmu500SciDet1->Draw("Edep>>hmu500SciDet1n","","");
   tmu500SciDet2->Draw("Edep>>hmu500SciDet2n","","");
   tmu500BGODet->Draw("Edep>>hmu500BGODetn","","");
   tx250SciDet1->Draw("Edep>>hx250SciDet1n","","");
   tx250SciDet2->Draw("Edep>>hx250SciDet2n","","");
   tx250BGODet->Draw("Edep>>hx250BGODetn","","");
   tx500SciDet1->Draw("Edep>>hx500SciDet1n","","");
   tx500SciDet2->Draw("Edep>>hx500SciDet2n","","");
   tx500BGODet->Draw("Edep>>hx500BGODetn","","");
   // 6-mm Al  
   t6Almu250SciDet1->Draw("Edep>>h6Almu250SciDet1","","");
   t6Almu250SciDet2->Draw("Edep>>h6Almu250SciDet2","","");
   t6Almu250BGODet->Draw("Edep>>h6Almu250BGODet","","");
   t6Almu500SciDet1->Draw("Edep>>h6Almu500SciDet1","","");
   t6Almu500SciDet2->Draw("Edep>>h6Almu500SciDet2","","");
   t6Almu500BGODet->Draw("Edep>>h6Almu500BGODet","","");
   t6Alx250SciDet1->Draw("Edep>>h6Alx250SciDet1","","");
   t6Alx250SciDet2->Draw("Edep>>h6Alx250SciDet2","","");
   t6Alx250BGODet->Draw("Edep>>h6Alx250BGODet","","");
   t6Alx500SciDet1->Draw("Edep>>h6Alx500SciDet1","","");
   t6Alx500SciDet2->Draw("Edep>>h6Alx500SciDet2","","");
   t6Alx500BGODet->Draw("Edep>>h6Alx500BGODet","","");
   // 6-mm Al [copies]
   t6Almu250SciDet1->Draw("Edep>>h6Almu250SciDet1n","","");
   t6Almu250SciDet2->Draw("Edep>>h6Almu250SciDet2n","","");
   t6Almu250BGODet->Draw("Edep>>h6Almu250BGODetn","","");
   t6Almu500SciDet1->Draw("Edep>>h6Almu500SciDet1n","","");
   t6Almu500SciDet2->Draw("Edep>>h6Almu500SciDet2n","","");
   t6Almu500BGODet->Draw("Edep>>h6Almu500BGODetn","","");
   t6Alx250SciDet1->Draw("Edep>>h6Alx250SciDet1n","","");
   t6Alx250SciDet2->Draw("Edep>>h6Alx250SciDet2n","","");
   t6Alx250BGODet->Draw("Edep>>h6Alx250BGODetn","","");
   t6Alx500SciDet1->Draw("Edep>>h6Alx500SciDet1n","","");
   t6Alx500SciDet2->Draw("Edep>>h6Alx500SciDet2n","","");
   t6Alx500BGODet->Draw("Edep>>h6Alx500BGODetn","","");
  
  
   // Colours 
   // 3-mm Al
   hmu250SciDet1->SetLineColor(kBlack);
   hmu250SciDet2->SetLineColor(kBlack);
   hmu250BGODet->SetLineColor(kBlack);
   hmu500SciDet1->SetLineColor(kGreen-2);
   hmu500SciDet2->SetLineColor(kGreen-2);
   hmu500BGODet->SetLineColor(kGreen-2);
   hx250SciDet1->SetLineColor(kBlack);
   hx250SciDet2->SetLineColor(kBlack);
   hx250BGODet->SetLineColor(kBlack);
   hx500SciDet1->SetLineColor(kGreen-2);
   hx500SciDet2->SetLineColor(kGreen-2);
   hx500BGODet->SetLineColor(kGreen-2);
   // 3-mm Al [copies]
   hmu250SciDet1n->SetLineColor(kBlack);
   hmu250SciDet2n->SetLineColor(kBlack);
   hmu250BGODetn->SetLineColor(kBlack);
   hmu500SciDet1n->SetLineColor(kBlack);
   hmu500SciDet2n->SetLineColor(kBlack);
   hmu500BGODetn->SetLineColor(kBlack);
   hx250SciDet1n->SetLineColor(kRed);
   hx250SciDet2n->SetLineColor(kRed);
   hx250BGODetn->SetLineColor(kRed);
   hx500SciDet1n->SetLineColor(kRed);
   hx500SciDet2n->SetLineColor(kRed);
   hx500BGODetn->SetLineColor(kRed);
   // 6-mm Al
   h6Almu250SciDet1->SetLineColor(kBlack);
   h6Almu250SciDet2->SetLineColor(kBlack);
   h6Almu250BGODet->SetLineColor(kBlack);
   h6Almu500SciDet1->SetLineColor(kGreen-2);
   h6Almu500SciDet2->SetLineColor(kGreen-2);
   h6Almu500BGODet->SetLineColor(kGreen-2);
   h6Alx250SciDet1->SetLineColor(kBlack);
   h6Alx250SciDet2->SetLineColor(kBlack);
   h6Alx250BGODet->SetLineColor(kBlack);
   h6Alx500SciDet1->SetLineColor(kGreen-2);
   h6Alx500SciDet2->SetLineColor(kGreen-2);
   h6Alx500BGODet->SetLineColor(kGreen-2);
   // 6-mm Al [copies]
   h6Almu250SciDet1n->SetLineColor(kBlack);
   h6Almu250SciDet2n->SetLineColor(kBlack);
   h6Almu250BGODetn->SetLineColor(kBlack);
   h6Almu500SciDet1n->SetLineColor(kBlack);
   h6Almu500SciDet2n->SetLineColor(kBlack);
   h6Almu500BGODetn->SetLineColor(kBlack);
   h6Alx250SciDet1n->SetLineColor(kRed);
   h6Alx250SciDet2n->SetLineColor(kRed);
   h6Alx250BGODetn->SetLineColor(kRed);
   h6Alx500SciDet1n->SetLineColor(kRed);
   h6Alx500SciDet2n->SetLineColor(kRed);
   h6Alx500BGODetn->SetLineColor(kRed);
 
 
   /********************************/
   /*           Plotting           */
   /********************************/

   // Mu-decay: 3-mm/ 6-mm Al 250-mm/ 500-mm BGO
   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(3,2);
   c->cd(1);
   gPad->SetLogy();
   hmu250SciDet1->SetTitle("Mu-decay: 5-mm SciD_{1} with 3-mm Al");
   hmu250SciDet1->GetXaxis()->SetTitle("Edep [MeV]");
   hmu250SciDet1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu250SciDet1->GetYaxis()->SetTitleOffset(2.0);
   hmu250SciDet1->Draw();
   c->Update();
   TPaveStats *stmu250SciDet1 = (TPaveStats*)hmu250SciDet1->GetListOfFunctions()->FindObject("stats");
   stmu250SciDet1->SetY1NDC(0.63); stmu250SciDet1->SetY2NDC(0.78);
   hmu500SciDet1->Draw("sames");
   c->Update();
   TPaveStats *stmu500SciDet1 = (TPaveStats*)hmu500SciDet1->GetListOfFunctions()->FindObject("stats");
   stmu500SciDet1->SetTextColor(kGreen-2);
   stmu500SciDet1->Draw();

   c->cd(2);
   gPad->SetLogy();
   hmu250SciDet2->SetTitle("Mu-decay: 5-mm SciD_{2} with 3-mm Al");
   hmu250SciDet2->GetXaxis()->SetTitle("Edep [MeV]");
   hmu250SciDet2->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu250SciDet2->GetYaxis()->SetTitleOffset(2.0);
   hmu250SciDet2->Draw();
   c->Update();
   TPaveStats *stmu250SciDet2 = (TPaveStats*)hmu250SciDet2->GetListOfFunctions()->FindObject("stats");
   stmu250SciDet2->SetY1NDC(0.63); stmu250SciDet2->SetY2NDC(0.78);
   hmu500SciDet2->Draw("sames");
   c->Update();
   TPaveStats *stmu500SciDet2 = (TPaveStats*)hmu500SciDet2->GetListOfFunctions()->FindObject("stats");
   stmu500SciDet2->SetTextColor(kGreen-2);
   stmu500SciDet2->Draw();

   c->cd(3);
   gPad->SetLogy();
   hmu250BGODet->SetTitle("Mu-decay: {250,500}-mm BGODet with 3-mm Al");
   hmu250BGODet->GetXaxis()->SetTitle("Edep [MeV]");
   hmu250BGODet->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu250BGODet->GetYaxis()->SetTitleOffset(2.0);
   hmu250BGODet->Draw();
   c->Update();
   TPaveStats *stmu250BGODet = (TPaveStats*)hmu250BGODet->GetListOfFunctions()->FindObject("stats");
   stmu250BGODet->SetY1NDC(0.63); stmu250BGODet->SetY2NDC(0.78);
   hmu500BGODet->Draw("sames");
   c->Update();
   TPaveStats *stmu500BGODet = (TPaveStats*)hmu500BGODet->GetListOfFunctions()->FindObject("stats");
   stmu500BGODet->SetTextColor(kGreen-2);
   stmu500BGODet->Draw();
   
   c->cd(4);
   gPad->SetLogy();
   h6Almu250SciDet1->SetTitle("Mu-decay: 5-mm SciD_{1} with 6-mm Al");
   h6Almu250SciDet1->GetXaxis()->SetTitle("Edep [MeV]");
   h6Almu250SciDet1->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Almu250SciDet1->GetYaxis()->SetTitleOffset(2.0);
   h6Almu250SciDet1->Draw();
   c->Update();
   TPaveStats *st6Almu250SciDet1 = (TPaveStats*)h6Almu250SciDet1->GetListOfFunctions()->FindObject("stats");
   st6Almu250SciDet1->SetY1NDC(0.63); st6Almu250SciDet1->SetY2NDC(0.78);
   h6Almu500SciDet1->Draw("sames");
   c->Update();
   TPaveStats *st6Almu500SciDet1 = (TPaveStats*)h6Almu500SciDet1->GetListOfFunctions()->FindObject("stats");
   st6Almu500SciDet1->SetTextColor(kGreen-2);
   st6Almu500SciDet1->Draw();

   c->cd(5);
   gPad->SetLogy();
   h6Almu250SciDet2->SetTitle("Mu-decay: 5-mm SciD_{2} with 6-mm Al");
   h6Almu250SciDet2->GetXaxis()->SetTitle("Edep [MeV]");
   h6Almu250SciDet2->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Almu250SciDet2->GetYaxis()->SetTitleOffset(2.0);
   h6Almu250SciDet2->Draw();
   c->Update();
   TPaveStats *st6Almu250SciDet2 = (TPaveStats*)h6Almu250SciDet2->GetListOfFunctions()->FindObject("stats");
   st6Almu250SciDet2->SetY1NDC(0.63); st6Almu250SciDet2->SetY2NDC(0.78);
   h6Almu500SciDet2->Draw("sames");
   c->Update();
   TPaveStats *st6Almu500SciDet2 = (TPaveStats*)h6Almu500SciDet2->GetListOfFunctions()->FindObject("stats");
   st6Almu500SciDet2->SetTextColor(kGreen-2);
   st6Almu500SciDet2->Draw();

   c->cd(6);
   gPad->SetLogy();
   h6Almu250BGODet->SetTitle("Mu-decay: {250,500}-mm BGODet with 6-mm Al");
   h6Almu250BGODet->GetXaxis()->SetTitle("Edep [MeV]");
   h6Almu250BGODet->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Almu250BGODet->GetYaxis()->SetTitleOffset(2.0);
   h6Almu250BGODet->Draw();
   c->Update();
   TPaveStats *st6Almu250BGODet = (TPaveStats*)h6Almu250BGODet->GetListOfFunctions()->FindObject("stats");
   st6Almu250BGODet->SetY1NDC(0.63); st6Almu250BGODet->SetY2NDC(0.78);
   h6Almu500BGODet->Draw("sames");
   c->Update();
   TPaveStats *st6Almu500BGODet = (TPaveStats*)h6Almu500BGODet->GetListOfFunctions()->FindObject("stats");
   st6Almu500BGODet->SetTextColor(kGreen-2);
   st6Almu500BGODet->Draw();

   c->SaveAs("BubblePlot4_mudecay_3mm_6mm_Al.pdf");
   c->SaveAs("BubblePlot4_mudecay_3mm_6mm_Al.png");
   c->SaveAs("BubblePlot4_mudecay_3mm_6mm_Al.C");



   // X-ray cascade: 3-mm/ 6-mm Al 250-mm/ 500-mm BGO
   TCanvas *d = new TCanvas("d","Edep",800,600);
   d->Divide(3,2);
   d->cd(1);
   gPad->SetLogy();
   hx250SciDet1->SetTitle("X-ray cascade: 5-mm SciD_{1} with 3-mm Al");
   hx250SciDet1->GetXaxis()->SetTitle("Edep [MeV]");
   hx250SciDet1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx250SciDet1->GetYaxis()->SetTitleOffset(2.0);
   hx250SciDet1->Draw();
   d->Update();
   TPaveStats *stx250SciDet1 = (TPaveStats*)hx250SciDet1->GetListOfFunctions()->FindObject("stats");
   stx250SciDet1->SetY1NDC(0.63); stx250SciDet1->SetY2NDC(0.78);
   hx500SciDet1->Draw("sames");
   d->Update();
   TPaveStats *stx500SciDet1 = (TPaveStats*)hx500SciDet1->GetListOfFunctions()->FindObject("stats");
   stx500SciDet1->SetTextColor(kGreen-2);
   stx500SciDet1->Draw();

   d->cd(2);
   gPad->SetLogy();
   hx250SciDet2->SetTitle("X-ray cascade: 5-mm SciD_{2} with 3-mm Al");
   hx250SciDet2->GetXaxis()->SetTitle("Edep [MeV]");
   hx250SciDet2->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx250SciDet2->GetYaxis()->SetTitleOffset(2.0);
   hx250SciDet2->Draw();
   d->Update();
   TPaveStats *stx250SciDet2 = (TPaveStats*)hx250SciDet2->GetListOfFunctions()->FindObject("stats");
   stx250SciDet2->SetY1NDC(0.63); stx250SciDet2->SetY2NDC(0.78);
   hx500SciDet2->Draw("sames");
   d->Update();
   TPaveStats *stx500SciDet2 = (TPaveStats*)hx500SciDet2->GetListOfFunctions()->FindObject("stats");
   stx500SciDet2->SetTextColor(kGreen-2);
   stx500SciDet2->Draw();

   d->cd(3);
   gPad->SetLogy();
   hx500BGODet->SetTitle("X-ray cascade: {250,500}-mm BGODet with 3-mm Al");
   hx500BGODet->GetXaxis()->SetTitle("Edep [MeV]");
   hx500BGODet->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx500BGODet->GetYaxis()->SetTitleOffset(2.0);
   hx500BGODet->Draw();
   d->Update();
   TPaveStats *stx500BGODet = (TPaveStats*)hx500BGODet->GetListOfFunctions()->FindObject("stats");
   stx500BGODet->SetTextColor(kGreen-2);
   hx250BGODet->Draw("sames");
   d->Update();
   TPaveStats *stx250BGODet = (TPaveStats*)hx250BGODet->GetListOfFunctions()->FindObject("stats");
   stx250BGODet->SetY1NDC(0.63); stx250BGODet->SetY2NDC(0.78);
   stx250BGODet->Draw();
   
   d->cd(4);
   gPad->SetLogy();
   h6Alx250SciDet1->SetTitle("X-ray cascade: 5-mm SciD_{1} with 6-mm Al");
   h6Alx250SciDet1->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx250SciDet1->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx250SciDet1->GetYaxis()->SetTitleOffset(2.0);
   h6Alx250SciDet1->Draw();
   d->Update();
   TPaveStats *st6Alx250SciDet1 = (TPaveStats*)h6Alx250SciDet1->GetListOfFunctions()->FindObject("stats");
   st6Alx250SciDet1->SetY1NDC(0.63); st6Alx250SciDet1->SetY2NDC(0.78);
   h6Alx500SciDet1->Draw("sames");
   d->Update();
   TPaveStats *st6Alx500SciDet1 = (TPaveStats*)h6Alx500SciDet1->GetListOfFunctions()->FindObject("stats");
   st6Alx500SciDet1->SetTextColor(kGreen-2);
   st6Alx500SciDet1->Draw();

   d->cd(5);
   gPad->SetLogy();
   h6Alx250SciDet2->SetTitle("X-ray cascade: 5-mm SciD_{2} with 6-mm Al");
   h6Alx250SciDet2->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx250SciDet2->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx250SciDet2->GetYaxis()->SetTitleOffset(2.0);
   h6Alx250SciDet2->Draw();
   d->Update();
   TPaveStats *st6Alx250SciDet2 = (TPaveStats*)h6Alx250SciDet2->GetListOfFunctions()->FindObject("stats");
   st6Alx250SciDet2->SetY1NDC(0.63); st6Alx250SciDet2->SetY2NDC(0.78);
   h6Alx500SciDet2->Draw("sames");
   d->Update();
   TPaveStats *st6Alx500SciDet2 = (TPaveStats*)h6Alx500SciDet2->GetListOfFunctions()->FindObject("stats");
   st6Alx500SciDet2->SetTextColor(kGreen-2);
   st6Alx500SciDet2->Draw();

   d->cd(6);
   gPad->SetLogy();
   h6Alx500BGODet->SetTitle("X-ray cascade: {250,500}-mm BGODet with 6-mm Al");
   h6Alx500BGODet->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx500BGODet->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx500BGODet->GetYaxis()->SetTitleOffset(2.0);
   h6Alx500BGODet->Draw();
   d->Update();
   TPaveStats *st6Alx500BGODet = (TPaveStats*)h6Alx500BGODet->GetListOfFunctions()->FindObject("stats");
   st6Alx500BGODet->SetTextColor(kGreen-2);
   h6Alx250BGODet->Draw("sames");
   d->Update();
   TPaveStats *st6Alx250BGODet = (TPaveStats*)h6Alx250BGODet->GetListOfFunctions()->FindObject("stats");
   st6Alx250BGODet->SetY1NDC(0.63); st6Alx250BGODet->SetY2NDC(0.78);
   st6Alx250BGODet->Draw();

   d->SaveAs("BubblePlot4_goldcascade_3mm_6mm_Al.pdf");
   d->SaveAs("BubblePlot4_goldcascade_3mm_6mm_Al.png");
   d->SaveAs("BubblePlot4_goldcascade_3mm_6mm_Al.C");

   
   
   // X-ray vs mu-decay with {3,6}-mm Al, 250-mm BGO
   TCanvas *e = new TCanvas("e","Edep",800,600);
   e->Divide(3,2);
   e->cd(1);
   gPad->SetLogy();
   hx250SciDet1n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{1} with 3-mm Al [250-mm BGO]");
   hx250SciDet1n->GetXaxis()->SetTitle("Edep [MeV]");
   hx250SciDet1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx250SciDet1n->GetYaxis()->SetTitleOffset(2.0);
   hx250SciDet1n->Draw();
   e->Update();
   TPaveStats *stx250SciDet1n = (TPaveStats*)hx250SciDet1n->GetListOfFunctions()->FindObject("stats");
   stx250SciDet1n->SetY1NDC(0.63); stx250SciDet1n->SetY2NDC(0.78);
   stx250SciDet1n->SetTextColor(kRed);
   hmu250SciDet1n->Draw("sames");
   e->Update();
   TPaveStats *stmu250SciDet1n = (TPaveStats*)hmu250SciDet1n->GetListOfFunctions()->FindObject("stats");
   stmu250SciDet1n->Draw();

   e->cd(2);
   gPad->SetLogy();
   hx250SciDet2n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{2} with 3-mm Al [250-mm BGO]");
   hx250SciDet2n->GetXaxis()->SetTitle("Edep [MeV]");
   hx250SciDet2n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx250SciDet2n->GetYaxis()->SetTitleOffset(2.0);
   hx250SciDet2n->Draw();
   e->Update();
   TPaveStats *stx250SciDet2n = (TPaveStats*)hx250SciDet2n->GetListOfFunctions()->FindObject("stats");
   stx250SciDet2n->SetY1NDC(0.63); stx250SciDet2n->SetY2NDC(0.78);
   stx250SciDet2n->SetTextColor(kRed);
   hmu250SciDet2n->Draw("sames");
   e->Update();
   TPaveStats *stmu250SciDet2n = (TPaveStats*)hmu250SciDet2n->GetListOfFunctions()->FindObject("stats");
   stmu250SciDet2n->Draw();

   e->cd(3);
   gPad->SetLogy();
   hx250BGODetn->SetTitle("X-ray cascade vs #mu-decay: 250-mm BGODet with 3-mm Al [250-mm BGO]");
   hx250BGODetn->GetXaxis()->SetTitle("Edep [MeV]");
   hx250BGODetn->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx250BGODetn->GetYaxis()->SetTitleOffset(2.0);
   hx250BGODetn->Draw();
   e->Update();
   TPaveStats *stx250BGODetn = (TPaveStats*)hx250BGODetn->GetListOfFunctions()->FindObject("stats");
   stx250BGODetn->SetY1NDC(0.63); stx250BGODetn->SetY2NDC(0.78);
   stx250BGODetn->SetTextColor(kRed);
   hmu250BGODetn->Draw("sames");
   e->Update();
   TPaveStats *stmu250BGODetn = (TPaveStats*)hmu250BGODetn->GetListOfFunctions()->FindObject("stats");
   stmu250BGODetn->Draw();
   
   e->cd(4);
   gPad->SetLogy();
   h6Alx250SciDet1n->SetTitle("X-ray cascade vs #mu-decay : 5-mm SciD_{1} with 6-mm Al [250-mm BGO]");
   h6Alx250SciDet1n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx250SciDet1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx250SciDet1n->GetYaxis()->SetTitleOffset(2.0);
   h6Alx250SciDet1n->Draw();
   e->Update();
   TPaveStats *st6Alx250SciDet1n = (TPaveStats*)h6Alx250SciDet1n->GetListOfFunctions()->FindObject("stats");
   st6Alx250SciDet1n->SetY1NDC(0.63); st6Alx250SciDet1n->SetY2NDC(0.78);
   st6Alx250SciDet1n->SetTextColor(kRed);
   h6Almu250SciDet1n->Draw("sames");
   e->Update();
   TPaveStats *st6Almu250SciDet1n = (TPaveStats*)h6Almu250SciDet1n->GetListOfFunctions()->FindObject("stats");
   st6Almu250SciDet1n->Draw();

   e->cd(5);
   gPad->SetLogy();
   h6Alx250SciDet2n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{2} with 6-mm Al [250-mm BGO]");
   h6Alx250SciDet2n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx250SciDet2n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx250SciDet2n->GetYaxis()->SetTitleOffset(2.0);
   h6Alx250SciDet2n->Draw();
   e->Update();
   TPaveStats *st6Alx250SciDet2n = (TPaveStats*)h6Alx250SciDet2n->GetListOfFunctions()->FindObject("stats");
   st6Alx250SciDet2n->SetY1NDC(0.63); st6Alx250SciDet2n->SetY2NDC(0.78);
   st6Alx250SciDet2n->SetTextColor(kRed);
   h6Almu250SciDet2n->Draw("sames");
   e->Update();
   TPaveStats *st6Almu250SciDet2n = (TPaveStats*)h6Almu250SciDet2n->GetListOfFunctions()->FindObject("stats");
   st6Almu250SciDet2n->Draw();

   e->cd(6);
   gPad->SetLogy();
   h6Alx250BGODetn->SetTitle("X-ray cascade vs #mu-decay: 250-mm BGODet with 6-mm Al [250-mm BGO]");
   h6Alx250BGODetn->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx250BGODetn->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx250BGODetn->GetYaxis()->SetTitleOffset(2.0);
   h6Alx250BGODetn->Draw();
   e->Update();
   TPaveStats *st6Alx250BGODetn = (TPaveStats*)h6Alx250BGODetn->GetListOfFunctions()->FindObject("stats");
   st6Alx250BGODetn->SetY1NDC(0.63); st6Alx250BGODetn->SetY2NDC(0.78);
   st6Alx250BGODetn->SetTextColor(kRed);
   h6Almu250BGODetn->Draw("sames");
   e->Update();
   TPaveStats *st6Almu250BGODetn = (TPaveStats*)h6Almu250BGODetn->GetListOfFunctions()->FindObject("stats");
   st6Almu250BGODetn->Draw();

   e->SaveAs("BubblePlot4_muX_250mm_BGO_3mm_6mm_Al.pdf");
   e->SaveAs("BubblePlot4_muX_250mm_BGO_3mm_6mm_Al.png");
   e->SaveAs("BubblePlot4_muX_250mm_BGO_3mm_6mm_Al.C");
   
   
   
   // X-ray vs mu-decay with {3,6}-mm Al, 500-mm BGO
   TCanvas *f = new TCanvas("f","Edep",800,600);
   f->Divide(3,2);
   f->cd(1);
   gPad->SetLogy();
   hx500SciDet1n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{1} with 3-mm Al [500-mm BGO]");
   hx500SciDet1n->GetXaxis()->SetTitle("Edep [MeV]");
   hx500SciDet1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx500SciDet1n->GetYaxis()->SetTitleOffset(2.0);
   hx500SciDet1n->Draw();
   f->Update();
   TPaveStats *stx500SciDet1n = (TPaveStats*)hx500SciDet1n->GetListOfFunctions()->FindObject("stats");
   stx500SciDet1n->SetY1NDC(0.63); stx500SciDet1n->SetY2NDC(0.78);
   stx500SciDet1n->SetTextColor(kRed);
   hmu500SciDet1n->Draw("sames");
   f->Update();
   TPaveStats *stmu500SciDet1n = (TPaveStats*)hmu500SciDet1n->GetListOfFunctions()->FindObject("stats");
   stmu500SciDet1n->Draw();

   f->cd(2);
   gPad->SetLogy();
   hx500SciDet2n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{2} with 3-mm Al [500-mm BGO]");
   hx500SciDet2n->GetXaxis()->SetTitle("Edep [MeV]");
   hx500SciDet2n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx500SciDet2n->GetYaxis()->SetTitleOffset(2.0);
   hx500SciDet2n->Draw();
   f->Update();
   TPaveStats *stx500SciDet2n = (TPaveStats*)hx500SciDet2n->GetListOfFunctions()->FindObject("stats");
   stx500SciDet2n->SetY1NDC(0.63); stx500SciDet2n->SetY2NDC(0.78);
   stx500SciDet2n->SetTextColor(kRed);
   hmu500SciDet2n->Draw("sames");
   f->Update();
   TPaveStats *stmu500SciDet2n = (TPaveStats*)hmu500SciDet2n->GetListOfFunctions()->FindObject("stats");
   stmu500SciDet2n->Draw();

   f->cd(3);
   gPad->SetLogy();
   hx500BGODetn->SetTitle("X-ray cascade vs #mu-decay: 500-mm BGODet with 3-mm Al [500-mm BGO]");
   hx500BGODetn->GetXaxis()->SetTitle("Edep [MeV]");
   hx500BGODetn->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx500BGODetn->GetYaxis()->SetTitleOffset(2.0);
   hx500BGODetn->Draw();
   f->Update();
   TPaveStats *stx500BGODetn = (TPaveStats*)hx500BGODetn->GetListOfFunctions()->FindObject("stats");
   stx500BGODetn->SetY1NDC(0.63); stx500BGODetn->SetY2NDC(0.78);
   stx500BGODetn->SetTextColor(kRed);
   hmu500BGODetn->Draw("sames");
   f->Update();
   TPaveStats *stmu500BGODetn = (TPaveStats*)hmu500BGODetn->GetListOfFunctions()->FindObject("stats");
   stmu500BGODetn->Draw();
   
   f->cd(4);
   gPad->SetLogy();
   h6Alx500SciDet1n->SetTitle("X-ray cascade vs #mu-decay : 5-mm SciD_{1} with 6-mm Al [500-mm BGO]");
   h6Alx500SciDet1n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx500SciDet1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx500SciDet1n->GetYaxis()->SetTitleOffset(2.0);
   h6Alx500SciDet1n->Draw();
   f->Update();
   TPaveStats *st6Alx500SciDet1n = (TPaveStats*)h6Alx500SciDet1n->GetListOfFunctions()->FindObject("stats");
   st6Alx500SciDet1n->SetY1NDC(0.63); st6Alx500SciDet1n->SetY2NDC(0.78);
   st6Alx500SciDet1n->SetTextColor(kRed);
   h6Almu500SciDet1n->Draw("sames");
   f->Update();
   TPaveStats *st6Almu500SciDet1n = (TPaveStats*)h6Almu500SciDet1n->GetListOfFunctions()->FindObject("stats");
   st6Almu500SciDet1n->Draw();

   f->cd(5);
   gPad->SetLogy();
   h6Alx500SciDet2n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{2} with 6-mm Al [500-mm BGO]");
   h6Alx500SciDet2n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx500SciDet2n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx500SciDet2n->GetYaxis()->SetTitleOffset(2.0);
   h6Alx500SciDet2n->Draw();
   f->Update();
   TPaveStats *st6Alx500SciDet2n = (TPaveStats*)h6Alx500SciDet2n->GetListOfFunctions()->FindObject("stats");
   st6Alx500SciDet2n->SetY1NDC(0.63); st6Alx500SciDet2n->SetY2NDC(0.78);
   st6Alx500SciDet2n->SetTextColor(kRed);
   h6Almu500SciDet2n->Draw("sames");
   f->Update();
   TPaveStats *st6Almu500SciDet2n = (TPaveStats*)h6Almu500SciDet2n->GetListOfFunctions()->FindObject("stats");
   st6Almu500SciDet2n->Draw();

   f->cd(6);
   gPad->SetLogy();
   h6Alx500BGODetn->SetTitle("X-ray cascade vs #mu-decay: 500-mm BGODet with 6-mm Al [500-mm BGO]");
   h6Alx500BGODetn->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx500BGODetn->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx500BGODetn->GetYaxis()->SetTitleOffset(2.0);
   h6Alx500BGODetn->Draw();
   f->Update();
   TPaveStats *st6Alx500BGODetn = (TPaveStats*)h6Alx500BGODetn->GetListOfFunctions()->FindObject("stats");
   st6Alx500BGODetn->SetY1NDC(0.63); st6Alx500BGODetn->SetY2NDC(0.78);
   st6Alx500BGODetn->SetTextColor(kRed);
   h6Almu500BGODetn->Draw("sames");
   f->Update();
   TPaveStats *st6Almu500BGODetn = (TPaveStats*)h6Almu500BGODetn->GetListOfFunctions()->FindObject("stats");
   st6Almu500BGODetn->Draw();

   f->SaveAs("BubblePlot4_muX_500mm_BGO_3mm_6mm_Al.pdf");
   f->SaveAs("BubblePlot4_muX_500mm_BGO_3mm_6mm_Al.png");
   f->SaveAs("BubblePlot4_muX_500mm_BGO_3mm_6mm_Al.C");
   
   



}


int main() {
   bubble4();
   return 0;
}
