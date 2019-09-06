/*//////////////////////////////////////////////////////////*/
/*                                                          */
/*  LS: to draw a full spectrum of mu-decay for >= 250-mm   */
/*  scintillator, SciD3, increase the number of array ele-  */
/*  ments in the location #1, modify the # of bins when     */
/*  filling the arrays in the locations #2 and change the   */
/*  range in the location #3.                               */
/*                                                          */
//////////////////////////////////////////////////////////////

// I/O
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdio>
#include <stdlib>
#include <vector>
using namespace std;

// ROOT
#include "TAttMarker.h"
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

void plothist(){

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

   const int nsamps = 101;
   const int nbins = 200;

   // TFiles 
   // E = 0 MeV ; P = 0 MeV
   TFile* f1020 = new TFile("../../simdata/finead/d_1mm_Cu_20mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f1025 = new TFile("../../simdata/finead/d_1mm_Cu_25mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f1030 = new TFile("../../simdata/finead/d_1mm_Cu_30mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f1035 = new TFile("../../simdata/finead/d_1mm_Cu_35mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f1040 = new TFile("../../simdata/finead/d_1mm_Cu_40mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f3020 = new TFile("../../simdata/finead/d_3mm_Cu_20mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f3025 = new TFile("../../simdata/finead/d_3mm_Cu_25mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f3030 = new TFile("../../simdata/finead/d_3mm_Cu_30mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f3035 = new TFile("../../simdata/finead/d_3mm_Cu_35mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f3040 = new TFile("../../simdata/finead/d_3mm_Cu_40mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f5020 = new TFile("../../simdata/finead/d_5mm_Cu_20mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f5025 = new TFile("../../simdata/finead/d_5mm_Cu_25mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f5030 = new TFile("../../simdata/finead/d_5mm_Cu_30mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f5035 = new TFile("../../simdata/finead/d_5mm_Cu_35mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f5040 = new TFile("../../simdata/finead/d_5mm_Cu_40mm_P_0_0MeV_BGO_1e5mudecay.root");

   // E = 5 MeV ; P = 32.89 MeV
   TFile* f1520 = new TFile("../../simdata/finead/d_1mm_Cu_20mm_P_32_89MeV_BGO_1e5mudecay.root");
   TFile* f1525 = new TFile("../../simdata/finead/d_1mm_Cu_25mm_P_32_89MeV_BGO_1e5mudecay.root");
   TFile* f1530 = new TFile("../../simdata/finead/d_1mm_Cu_30mm_P_32_89MeV_BGO_1e5mudecay.root");
   TFile* f1535 = new TFile("../../simdata/finead/d_1mm_Cu_35mm_P_32_89MeV_BGO_1e5mudecay.root");
   TFile* f1540 = new TFile("../../simdata/finead/d_1mm_Cu_40mm_P_32_89MeV_BGO_1e5mudecay.root");
   TFile* f3520 = new TFile("../../simdata/finead/d_3mm_Cu_20mm_P_32_89MeV_BGO_1e5mudecay.root");
   TFile* f3525 = new TFile("../../simdata/finead/d_3mm_Cu_25mm_P_32_89MeV_BGO_1e5mudecay.root");
   TFile* f3530 = new TFile("../../simdata/finead/d_3mm_Cu_30mm_P_32_89MeV_BGO_1e5mudecay.root");
   TFile* f3535 = new TFile("../../simdata/finead/d_3mm_Cu_35mm_P_32_89MeV_BGO_1e5mudecay.root");
   TFile* f3540 = new TFile("../../simdata/finead/d_3mm_Cu_40mm_P_32_89MeV_BGO_1e5mudecay.root");
   TFile* f5520 = new TFile("../../simdata/finead/d_5mm_Cu_20mm_P_32_89MeV_BGO_1e5mudecay.root");
   TFile* f5525 = new TFile("../../simdata/finead/d_5mm_Cu_25mm_P_32_89MeV_BGO_1e5mudecay.root");
   TFile* f5530 = new TFile("../../simdata/finead/d_5mm_Cu_30mm_P_32_89MeV_BGO_1e5mudecay.root");
   TFile* f5535 = new TFile("../../simdata/finead/d_5mm_Cu_35mm_P_32_89MeV_BGO_1e5mudecay.root");
   TFile* f5540 = new TFile("../../simdata/finead/d_5mm_Cu_40mm_P_32_89MeV_BGO_1e5mudecay.root");

   // E = 10 MeV ; P = 47.04 MeV
   TFile* f11020 = new TFile("../../simdata/finead/d_1mm_Cu_20mm_P_47_04MeV_BGO_1e5mudecay.root");
   TFile* f11025 = new TFile("../../simdata/finead/d_1mm_Cu_25mm_P_47_04MeV_BGO_1e5mudecay.root");
   TFile* f11030 = new TFile("../../simdata/finead/d_1mm_Cu_30mm_P_47_04MeV_BGO_1e5mudecay.root");
   TFile* f11035 = new TFile("../../simdata/finead/d_1mm_Cu_35mm_P_47_04MeV_BGO_1e5mudecay.root");
   TFile* f11040 = new TFile("../../simdata/finead/d_1mm_Cu_40mm_P_47_04MeV_BGO_1e5mudecay.root");
   TFile* f31020 = new TFile("../../simdata/finead/d_3mm_Cu_20mm_P_47_04MeV_BGO_1e5mudecay.root");
   TFile* f31025 = new TFile("../../simdata/finead/d_3mm_Cu_25mm_P_47_04MeV_BGO_1e5mudecay.root");
   TFile* f31030 = new TFile("../../simdata/finead/d_3mm_Cu_30mm_P_47_04MeV_BGO_1e5mudecay.root");
   TFile* f31035 = new TFile("../../simdata/finead/d_3mm_Cu_35mm_P_47_04MeV_BGO_1e5mudecay.root");
   TFile* f31040 = new TFile("../../simdata/finead/d_3mm_Cu_40mm_P_47_04MeV_BGO_1e5mudecay.root");
   TFile* f51020 = new TFile("../../simdata/finead/d_5mm_Cu_20mm_P_47_04MeV_BGO_1e5mudecay.root");
   TFile* f51025 = new TFile("../../simdata/finead/d_5mm_Cu_25mm_P_47_04MeV_BGO_1e5mudecay.root");
   TFile* f51030 = new TFile("../../simdata/finead/d_5mm_Cu_30mm_P_47_04MeV_BGO_1e5mudecay.root");
   TFile* f51035 = new TFile("../../simdata/finead/d_5mm_Cu_35mm_P_47_04MeV_BGO_1e5mudecay.root");
   TFile* f51040 = new TFile("../../simdata/finead/d_5mm_Cu_40mm_P_47_04MeV_BGO_1e5mudecay.root");



   // Histograms
   //E = 0 MeV
   TH1F *h1020 = new TH1F("h1020","Edep",nbins,0,40);
   TH1F *h1025 = new TH1F("h1025","Edep",nbins,0,40);
   TH1F *h1030 = new TH1F("h1030","Edep",nbins,0,40);   
   TH1F *h1035 = new TH1F("h1035","Edep",nbins,0,40);
   TH1F *h1040 = new TH1F("h1040","Edep",nbins,0,40);
   TH1F *h3020 = new TH1F("h3020","Edep",nbins,0,40);
   TH1F *h3025 = new TH1F("h3025","Edep",nbins,0,40);
   TH1F *h3030 = new TH1F("h3030","Edep",nbins,0,40);   
   TH1F *h3035 = new TH1F("h3035","Edep",nbins,0,40);
   TH1F *h3040 = new TH1F("h3040","Edep",nbins,0,40);
   TH1F *h5020 = new TH1F("h5020","Edep",nbins,0,40);   
   TH1F *h5025 = new TH1F("h5025","Edep",nbins,0,40);
   TH1F *h5030 = new TH1F("h5030","Edep",nbins,0,40);   
   TH1F *h5035 = new TH1F("h5035","Edep",nbins,0,40);
   TH1F *h5040 = new TH1F("h5040","Edep",nbins,0,40);
   
   //E = 5 MeV
   TH1F *h1520 = new TH1F("h1520","Edep",nbins,0,40);
   TH1F *h1525 = new TH1F("h1525","Edep",nbins,0,40);
   TH1F *h1530 = new TH1F("h1530","Edep",nbins,0,40);   
   TH1F *h1535 = new TH1F("h1535","Edep",nbins,0,40);
   TH1F *h1540 = new TH1F("h1540","Edep",nbins,0,40);
   TH1F *h3520 = new TH1F("h3520","Edep",nbins,0,40);
   TH1F *h3525 = new TH1F("h3525","Edep",nbins,0,40);
   TH1F *h3530 = new TH1F("h3530","Edep",nbins,0,40);   
   TH1F *h3535 = new TH1F("h3535","Edep",nbins,0,40);
   TH1F *h3540 = new TH1F("h3540","Edep",nbins,0,40);
   TH1F *h5520 = new TH1F("h5520","Edep",nbins,0,40);   
   TH1F *h5525 = new TH1F("h5525","Edep",nbins,0,40);
   TH1F *h5530 = new TH1F("h5530","Edep",nbins,0,40);   
   TH1F *h5535 = new TH1F("h5535","Edep",nbins,0,40);
   TH1F *h5540 = new TH1F("h5540","Edep",nbins,0,40);

   //E = 10 MeV
   TH1F *h11020 = new TH1F("h11020","Edep",nbins,0,40);
   TH1F *h11025 = new TH1F("h11025","Edep",nbins,0,40);
   TH1F *h11030 = new TH1F("h11030","Edep",nbins,0,40);   
   TH1F *h11035 = new TH1F("h11035","Edep",nbins,0,40);
   TH1F *h11040 = new TH1F("h11040","Edep",nbins,0,40);
   TH1F *h31020 = new TH1F("h31020","Edep",nbins,0,40);
   TH1F *h31025 = new TH1F("h31025","Edep",nbins,0,40);
   TH1F *h31030 = new TH1F("h31030","Edep",nbins,0,40);   
   TH1F *h31035 = new TH1F("h31035","Edep",nbins,0,40);
   TH1F *h31040 = new TH1F("h31040","Edep",nbins,0,40);
   TH1F *h51020 = new TH1F("h51020","Edep",nbins,0,40);   
   TH1F *h51025 = new TH1F("h51025","Edep",nbins,0,40);
   TH1F *h51030 = new TH1F("h51030","Edep",nbins,0,40);   
   TH1F *h51035 = new TH1F("h51035","Edep",nbins,0,40);
   TH1F *h51040 = new TH1F("h51040","Edep",nbins,0,40);
   
   
   
   // TTrees
   // E = 0 MeV
   TTree *t1020 = (TTree*)f1020->Get("Detector/BGOD1");
   TTree *t1025 = (TTree*)f1025->Get("Detector/BGOD1");
   TTree *t1030 = (TTree*)f1030->Get("Detector/BGOD1");
   TTree *t1035 = (TTree*)f1035->Get("Detector/BGOD1");
   TTree *t1040 = (TTree*)f1040->Get("Detector/BGOD1");
   TTree *t3020 = (TTree*)f3020->Get("Detector/BGOD1");
   TTree *t3025 = (TTree*)f3025->Get("Detector/BGOD1");
   TTree *t3030 = (TTree*)f3030->Get("Detector/BGOD1");
   TTree *t3035 = (TTree*)f3035->Get("Detector/BGOD1");
   TTree *t3040 = (TTree*)f3040->Get("Detector/BGOD1");
   TTree *t5020 = (TTree*)f5020->Get("Detector/BGOD1");
   TTree *t5025 = (TTree*)f5025->Get("Detector/BGOD1");
   TTree *t5030 = (TTree*)f5030->Get("Detector/BGOD1");
   TTree *t5035 = (TTree*)f5035->Get("Detector/BGOD1");
   TTree *t5040 = (TTree*)f5040->Get("Detector/BGOD1");

   // E = 5 MeV
   TTree *t1520 = (TTree*)f1520->Get("Detector/BGOD1");
   TTree *t1525 = (TTree*)f1525->Get("Detector/BGOD1");
   TTree *t1530 = (TTree*)f1530->Get("Detector/BGOD1");
   TTree *t1535 = (TTree*)f1535->Get("Detector/BGOD1");
   TTree *t1540 = (TTree*)f1540->Get("Detector/BGOD1");
   TTree *t3520 = (TTree*)f3520->Get("Detector/BGOD1");
   TTree *t3525 = (TTree*)f3525->Get("Detector/BGOD1");
   TTree *t3530 = (TTree*)f3530->Get("Detector/BGOD1");
   TTree *t3535 = (TTree*)f3535->Get("Detector/BGOD1");
   TTree *t3540 = (TTree*)f3540->Get("Detector/BGOD1");
   TTree *t5520 = (TTree*)f5520->Get("Detector/BGOD1");
   TTree *t5525 = (TTree*)f5525->Get("Detector/BGOD1");
   TTree *t5530 = (TTree*)f5530->Get("Detector/BGOD1");
   TTree *t5535 = (TTree*)f5535->Get("Detector/BGOD1");
   TTree *t5540 = (TTree*)f5540->Get("Detector/BGOD1");

   // E = 10 MeV
   TTree *t11020 = (TTree*)f11020->Get("Detector/BGOD1");
   TTree *t11025 = (TTree*)f11025->Get("Detector/BGOD1");
   TTree *t11030 = (TTree*)f11030->Get("Detector/BGOD1");
   TTree *t11035 = (TTree*)f11035->Get("Detector/BGOD1");
   TTree *t11040 = (TTree*)f11040->Get("Detector/BGOD1");
   TTree *t31020 = (TTree*)f31020->Get("Detector/BGOD1");
   TTree *t31025 = (TTree*)f31025->Get("Detector/BGOD1");
   TTree *t31030 = (TTree*)f31030->Get("Detector/BGOD1");
   TTree *t31035 = (TTree*)f31035->Get("Detector/BGOD1");
   TTree *t31040 = (TTree*)f31040->Get("Detector/BGOD1");
   TTree *t51020 = (TTree*)f51020->Get("Detector/BGOD1");
   TTree *t51025 = (TTree*)f51025->Get("Detector/BGOD1");
   TTree *t51030 = (TTree*)f51030->Get("Detector/BGOD1");
   TTree *t51035 = (TTree*)f51035->Get("Detector/BGOD1");
   TTree *t51040 = (TTree*)f51040->Get("Detector/BGOD1");



   // Drawings
   // E = 0 MeV
   t1020->Draw("Edep>>h1020","","");
   t1025->Draw("Edep>>h1025","","");
   t1030->Draw("Edep>>h1030","","");
   t1035->Draw("Edep>>h1035","","");
   t1040->Draw("Edep>>h1040","","");
   t3020->Draw("Edep>>h3020","","");
   t3025->Draw("Edep>>h3025","","");
   t3030->Draw("Edep>>h3030","","");
   t3035->Draw("Edep>>h3035","","");
   t3040->Draw("Edep>>h3040","","");
   t5020->Draw("Edep>>h5020","","");
   t5025->Draw("Edep>>h5025","","");
   t5030->Draw("Edep>>h5030","","");
   t5035->Draw("Edep>>h5035","","");
   t5040->Draw("Edep>>h5040","","");

   // E = 5 MeV
   t1520->Draw("Edep>>h1520","","");
   t1525->Draw("Edep>>h1525","","");
   t1530->Draw("Edep>>h1530","","");
   t1535->Draw("Edep>>h1535","","");
   t1540->Draw("Edep>>h1540","","");
   t3520->Draw("Edep>>h3520","","");
   t3525->Draw("Edep>>h3525","","");
   t3530->Draw("Edep>>h3530","","");
   t3535->Draw("Edep>>h3535","","");
   t3540->Draw("Edep>>h3540","","");
   t5520->Draw("Edep>>h5520","","");
   t5525->Draw("Edep>>h5525","","");
   t5530->Draw("Edep>>h5530","","");
   t5535->Draw("Edep>>h5535","","");
   t5540->Draw("Edep>>h5540","","");

   // E = 10 MeV
   t11020->Draw("Edep>>h11020","","");
   t11025->Draw("Edep>>h11025","","");
   t11030->Draw("Edep>>h11030","","");
   t11035->Draw("Edep>>h11035","","");
   t11040->Draw("Edep>>h11040","","");
   t31020->Draw("Edep>>h31020","","");
   t31025->Draw("Edep>>h31025","","");
   t31030->Draw("Edep>>h31030","","");
   t31035->Draw("Edep>>h31035","","");
   t31040->Draw("Edep>>h31040","","");
   t51020->Draw("Edep>>h51020","","");
   t51025->Draw("Edep>>h51025","","");
   t51030->Draw("Edep>>h51030","","");
   t51035->Draw("Edep>>h51035","","");
   t51040->Draw("Edep>>h51040","","");



   // Colours
   // E = 0 MeV
   h1020->SetLineColor(kRed);
   h1025->SetLineColor(kRed-10);
   h1030->SetLineColor(kMagenta-1);
   h1035->SetLineColor(kMagenta-8);
   h1040->SetLineColor(kAzure+10);
   h3020->SetLineColor(kGreen+2);
   h3025->SetLineColor(kCyan+1);
   h3030->SetLineColor(kBlue);
   h3035->SetLineColor(kYellow-7);
   h3040->SetLineColor(kMagenta+1);
   h5020->SetLineColor(kOrange);
   h5025->SetLineColor(kGreen-8);
   h5030->SetLineColor(kRed-9);
   h5035->SetLineColor(kBlue-8);
   h5040->SetLineColor(kOrange+1);

   // E = 5 MeV
   h1520->SetLineColor(kMagenta-1);
   h1525->SetLineColor(kMagenta-8);
   h1530->SetLineColor(kAzure+10);
   h1535->SetLineColor(kGreen+2);
   h1540->SetLineColor(kCyan+1);
   h3520->SetLineColor(kBlue);
   h3525->SetLineColor(kYellow-7);
   h3530->SetLineColor(kMagenta+1);
   h3535->SetLineColor(kOrange);
   h3540->SetLineColor(kGreen-8);
   h5520->SetLineColor(kRed-9);
   h5525->SetLineColor(kBlue-8);
   h5530->SetLineColor(kOrange+1);
   h5535->SetLineColor(kRed);
   h5540->SetLineColor(kRed-10);

   // E = 10 MeV
   h11020->SetLineColor(kAzure+10);
   h11025->SetLineColor(kGreen+2);
   h11030->SetLineColor(kCyan+1);
   h11035->SetLineColor(kBlue);
   h11040->SetLineColor(kYellow-7);
   h31020->SetLineColor(kMagenta+1);
   h31025->SetLineColor(kOrange);
   h31030->SetLineColor(kGreen-8);
   h31035->SetLineColor(kRed-9);
   h31040->SetLineColor(kBlue-8);
   h51020->SetLineColor(kOrange+1);
   h51025->SetLineColor(kRed);
   h51030->SetLineColor(kRed-10);
   h51035->SetLineColor(kMagenta-1);
   h51040->SetLineColor(kMagenta-8);



   //-------------------------------------------------------------------
   //                          Plotting 
   //-------------------------------------------------------------------


   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(2,3);
   c->cd(1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1020->SetTitle("");
   h1020->GetXaxis()->SetTitle("E [MeV]");
   h1020->GetYaxis()->SetTitle("# of counts");
   h1020->GetYaxis()->SetTitleOffset(1.0);
   h1020->Draw();
   h3020->Draw("same");  
   h5020->Draw("same");  
   auto legend020 = new TLegend(0.55,0.7,0.89,0.85);
   legend020->AddEntry(h1020,"d=1 mm, E=0 MeV, w_{Cu}=20 mm","l");
   legend020->AddEntry(h3020,"d=3 mm, E=0 MeV, w_{Cu}=20 mm","l");
   legend020->AddEntry(h5020,"d=5 mm, E=0 MeV, w_{Cu}=20 mm","l");
   legend020->Draw();

   c->cd(2);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1025->SetTitle("");
   h1025->GetXaxis()->SetTitle("E [MeV]");
   h1025->GetYaxis()->SetTitle("# of counts");
   h1025->GetYaxis()->SetTitleOffset(1.0);
   h1025->Draw();
   h3025->Draw("same");  
   h5025->Draw("same");  
   auto legend025 = new TLegend(0.55,0.7,0.89,0.85);
   legend025->AddEntry(h1025,"d=1 mm, E=0 MeV, w_{Cu}=25 mm","l");
   legend025->AddEntry(h3025,"d=3 mm, E=0 MeV, w_{Cu}=25 mm","l");
   legend025->AddEntry(h5025,"d=5 mm, E=0 MeV, w_{Cu}=25 mm","l");
   legend025->Draw();
   
   c->cd(3);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1030->SetTitle("");
   h1030->GetXaxis()->SetTitle("E [MeV]");
   h1030->GetYaxis()->SetTitle("# of counts");
   h1030->GetYaxis()->SetTitleOffset(1.0);
   h1030->Draw();
   h3030->Draw("same");  
   h5030->Draw("same");  
   auto legend030 = new TLegend(0.55,0.7,0.89,0.85);
   legend030->AddEntry(h1030,"d=1 mm, E=0 MeV, w_{Cu}=30 mm","l");
   legend030->AddEntry(h3030,"d=3 mm, E=0 MeV, w_{Cu}=30 mm","l");
   legend030->AddEntry(h5030,"d=5 mm, E=0 MeV, w_{Cu}=30 mm","l");
   legend030->Draw();
   
   c->cd(4);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1035->SetTitle("");
   h1035->GetXaxis()->SetTitle("E [MeV]");
   h1035->GetYaxis()->SetTitle("# of counts");
   h1035->GetYaxis()->SetTitleOffset(1.0);
   h1035->Draw();
   h3035->Draw("same");  
   h5035->Draw("same");  
   auto legend035 = new TLegend(0.55,0.7,0.89,0.85);
   legend035->AddEntry(h1035,"d=1 mm, E=0 MeV, w_{Cu}=35 mm","l");
   legend035->AddEntry(h3035,"d=3 mm, E=0 MeV, w_{Cu}=35 mm","l");
   legend035->AddEntry(h5035,"d=5 mm, E=0 MeV, w_{Cu}=35 mm","l");
   legend035->Draw();
   
   c->cd(5);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1040->SetTitle("");
   h1040->GetXaxis()->SetTitle("E [MeV]");
   h1040->GetYaxis()->SetTitle("# of counts");
   h1040->GetYaxis()->SetTitleOffset(1.0);
   h1040->Draw();
   h3040->Draw("same");  
   h5040->Draw("same");  
   auto legend040 = new TLegend(0.55,0.7,0.89,0.85);
   legend040->AddEntry(h1040,"d=1 mm, E=0 MeV, w_{Cu}=40 mm","l");
   legend040->AddEntry(h3040,"d=3 mm, E=0 MeV, w_{Cu}=40 mm","l");
   legend040->AddEntry(h5040,"d=5 mm, E=0 MeV, w_{Cu}=40 mm","l");
   legend040->Draw();
      
   c->SaveAs("d_comp_E_0MeV.pdf");
   c->SaveAs("d_comp_E_0MeV.png");
   c->SaveAs("d_comp_E_0MeV.C");
 


   TCanvas *c2 = new TCanvas("c2","Edep",800,600);
   c2->Divide(2,3);
   c2->cd(1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1520->SetTitle("");
   h1520->GetXaxis()->SetTitle("E [MeV]");
   h1520->GetYaxis()->SetTitle("# of counts");
   h1520->GetYaxis()->SetTitleOffset(1.0);
   h1520->Draw();
   h3520->Draw("same");  
   h5520->Draw("same");  
   auto legend520 = new TLegend(0.55,0.7,0.89,0.85);
   legend520->AddEntry(h1520,"d=1 mm, E=5 MeV, w_{Cu}=20 mm","l");
   legend520->AddEntry(h3520,"d=3 mm, E=5 MeV, w_{Cu}=20 mm","l");
   legend520->AddEntry(h5520,"d=5 mm, E=5 MeV, w_{Cu}=20 mm","l");
   legend520->Draw();

   c2->cd(2);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1525->SetTitle("");
   h1525->GetXaxis()->SetTitle("E [MeV]");
   h1525->GetYaxis()->SetTitle("# of counts");
   h1525->GetYaxis()->SetTitleOffset(1.0);
   h1525->Draw();
   h3525->Draw("same");  
   h5525->Draw("same");  
   auto legend525 = new TLegend(0.55,0.7,0.89,0.85);
   legend525->AddEntry(h1525,"d=1 mm, E=5 MeV, w_{Cu}=25 mm","l");
   legend525->AddEntry(h3525,"d=3 mm, E=5 MeV, w_{Cu}=25 mm","l");
   legend525->AddEntry(h5525,"d=5 mm, E=5 MeV, w_{Cu}=25 mm","l");
   legend525->Draw();
   
   c2->cd(3);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1530->SetTitle("");
   h1530->GetXaxis()->SetTitle("E [MeV]");
   h1530->GetYaxis()->SetTitle("# of counts");
   h1530->GetYaxis()->SetTitleOffset(1.0);
   h1530->Draw();
   h3530->Draw("same");  
   h5530->Draw("same");  
   auto legend530 = new TLegend(0.55,0.7,0.89,0.85);
   legend530->AddEntry(h1530,"d=1 mm, E=5 MeV, w_{Cu}=30 mm","l");
   legend530->AddEntry(h3530,"d=3 mm, E=5 MeV, w_{Cu}=30 mm","l");
   legend530->AddEntry(h5530,"d=5 mm, E=5 MeV, w_{Cu}=30 mm","l");
   legend530->Draw();
   
   c2->cd(4);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1535->SetTitle("");
   h1535->GetXaxis()->SetTitle("E [MeV]");
   h1535->GetYaxis()->SetTitle("# of counts");
   h1535->GetYaxis()->SetTitleOffset(1.0);
   h1535->Draw();
   h3535->Draw("same");  
   h5535->Draw("same");  
   auto legend535 = new TLegend(0.55,0.7,0.89,0.85);
   legend535->AddEntry(h1535,"d=1 mm, E=5 MeV, w_{Cu}=35 mm","l");
   legend535->AddEntry(h3535,"d=3 mm, E=5 MeV, w_{Cu}=35 mm","l");
   legend535->AddEntry(h5535,"d=5 mm, E=5 MeV, w_{Cu}=35 mm","l");
   legend535->Draw();
   
   c2->cd(5);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1540->SetTitle("");
   h1540->GetXaxis()->SetTitle("E [MeV]");
   h1540->GetYaxis()->SetTitle("# of counts");
   h1540->GetYaxis()->SetTitleOffset(1.0);
   h1540->Draw();
   h3540->Draw("same");  
   h5540->Draw("same");  
   auto legend540 = new TLegend(0.55,0.7,0.89,0.85);
   legend540->AddEntry(h1540,"d=1 mm, E=5 MeV, w_{Cu}=40 mm","l");
   legend540->AddEntry(h3540,"d=3 mm, E=5 MeV, w_{Cu}=40 mm","l");
   legend540->AddEntry(h5540,"d=5 mm, E=5 MeV, w_{Cu}=40 mm","l");
   legend540->Draw();
   
   c2->SaveAs("d_comp_E_5MeV.pdf");
   c2->SaveAs("d_comp_E_5MeV.png");
   c2->SaveAs("d_comp_E_5MeV.C");



   TCanvas *c3 = new TCanvas("c3","Edep",800,600);
   c3->Divide(2,3);
   c3->cd(1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h11020->SetTitle("");
   h11020->GetXaxis()->SetTitle("E [MeV]");
   h11020->GetYaxis()->SetTitle("# of counts");
   h11020->GetYaxis()->SetTitleOffset(1.0);
   h11020->Draw();
   h31020->Draw("same");  
   h51020->Draw("same");  
   auto legend1020 = new TLegend(0.55,0.7,0.89,0.85);
   legend1020->AddEntry(h11020,"d=1 mm, E=10 MeV, w_{Cu}=20 mm","l");
   legend1020->AddEntry(h31020,"d=3 mm, E=10 MeV, w_{Cu}=20 mm","l");
   legend1020->AddEntry(h51020,"d=5 mm, E=10 MeV, w_{Cu}=20 mm","l");
   legend1020->Draw();

   c3->cd(2);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h11025->SetTitle("");
   h11025->GetXaxis()->SetTitle("E [MeV]");
   h11025->GetYaxis()->SetTitle("# of counts");
   h11025->GetYaxis()->SetTitleOffset(1.0);
   h11025->Draw();
   h31025->Draw("same");  
   h51025->Draw("same");  
   auto legend1025 = new TLegend(0.55,0.7,0.89,0.85);
   legend1025->AddEntry(h11025,"d=1 mm, E=10 MeV, w_{Cu}=25 mm","l");
   legend1025->AddEntry(h31025,"d=3 mm, E=10 MeV, w_{Cu}=25 mm","l");
   legend1025->AddEntry(h51025,"d=5 mm, E=10 MeV, w_{Cu}=25 mm","l");
   legend1025->Draw();
   
   c3->cd(3);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h11030->SetTitle("");
   h11030->GetXaxis()->SetTitle("E [MeV]");
   h11030->GetYaxis()->SetTitle("# of counts");
   h11030->GetYaxis()->SetTitleOffset(1.0);
   h11030->Draw();
   h31030->Draw("same");  
   h51030->Draw("same");  
   auto legend1030 = new TLegend(0.55,0.7,0.89,0.85);
   legend1030->AddEntry(h11030,"d=1 mm, E=10 MeV, w_{Cu}=30 mm","l");
   legend1030->AddEntry(h31030,"d=3 mm, E=10 MeV, w_{Cu}=30 mm","l");
   legend1030->AddEntry(h51030,"d=5 mm, E=10 MeV, w_{Cu}=30 mm","l");
   legend1030->Draw();
   
   c3->cd(4);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h11035->SetTitle("");
   h11035->GetXaxis()->SetTitle("E [MeV]");
   h11035->GetYaxis()->SetTitle("# of counts");
   h11035->GetYaxis()->SetTitleOffset(1.0);
   h11035->Draw();
   h31035->Draw("same");  
   h51035->Draw("same");  
   auto legend1035 = new TLegend(0.55,0.7,0.89,0.85);
   legend1035->AddEntry(h11035,"d=1 mm, E=10 MeV, w_{Cu}=35 mm","l");
   legend1035->AddEntry(h31035,"d=3 mm, E=10 MeV, w_{Cu}=35 mm","l");
   legend1035->AddEntry(h51035,"d=5 mm, E=10 MeV, w_{Cu}=35 mm","l");
   legend1035->Draw();
   
   c3->cd(5);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h11040->SetTitle("");
   h11040->GetXaxis()->SetTitle("E [MeV]");
   h11040->GetYaxis()->SetTitle("# of counts");
   h11040->GetYaxis()->SetTitleOffset(1.0);
   h11040->Draw();
   h31040->Draw("same");  
   h51040->Draw("same");  
   auto legend1040 = new TLegend(0.55,0.7,0.89,0.85);
   legend1040->AddEntry(h11040,"d=1 mm, E=10 MeV, w_{Cu}=40 mm","l");
   legend1040->AddEntry(h31040,"d=3 mm, E=10 MeV, w_{Cu}=40 mm","l");
   legend1040->AddEntry(h51040,"d=5 mm, E=10 MeV, w_{Cu}=40 mm","l");
   legend1040->Draw();
   
   c3->SaveAs("d_comp_E_10MeV.pdf");
   c3->SaveAs("d_comp_E_10MeV.png");
   c3->SaveAs("d_comp_E_10MeV.C");



   TCanvas *d = new TCanvas("d","Edep",800,600);
   d->Divide(1,3);
   d->cd(1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1020->SetTitle("");
   h1020->GetXaxis()->SetTitle("E [MeV]");
   h1020->GetYaxis()->SetTitle("# of counts");
   h1020->GetYaxis()->SetTitleOffset(1.0);
   h1020->Draw();
   h1025->Draw("same");  
   h1030->Draw("same");
   h1035->Draw("same");
   h1040->Draw("same");  
   auto legend10 = new TLegend(0.55,0.6,0.89,0.85);
   legend10->AddEntry(h1020,"d=1 mm, E=0 MeV, w_{Cu}=20 mm","l");
   legend10->AddEntry(h1025,"d=1 mm, E=0 MeV, w_{Cu}=25 mm","l");
   legend10->AddEntry(h1030,"d=1 mm, E=0 MeV, w_{Cu}=30 mm","l");
   legend10->AddEntry(h1035,"d=1 mm, E=0 MeV, w_{Cu}=35 mm","l");
   legend10->AddEntry(h1040,"d=1 mm, E=0 MeV, w_{Cu}=40 mm","l");
   legend10->Draw();

   d->cd(2);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h3020->SetTitle("");
   h3020->GetXaxis()->SetTitle("E [MeV]");
   h3020->GetYaxis()->SetTitle("# of counts");
   h3020->GetYaxis()->SetTitleOffset(1.0);
   h3020->Draw();
   h3025->Draw("same");  
   h3030->Draw("same");
   h3035->Draw("same");
   h3040->Draw("same");  
   auto legend30 = new TLegend(0.55,0.6,0.89,0.85);
   legend30->AddEntry(h3020,"d=3 mm, E=0 MeV, w_{Cu}=20 mm","l");
   legend30->AddEntry(h3025,"d=3 mm, E=0 MeV, w_{Cu}=25 mm","l");
   legend30->AddEntry(h3030,"d=3 mm, E=0 MeV, w_{Cu}=30 mm","l");
   legend30->AddEntry(h3035,"d=3 mm, E=0 MeV, w_{Cu}=35 mm","l");
   legend30->AddEntry(h3040,"d=3 mm, E=0 MeV, w_{Cu}=40 mm","l");
   legend30->Draw();
   
   d->cd(3);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h5020->SetTitle("");
   h5020->GetXaxis()->SetTitle("E [MeV]");
   h5020->GetYaxis()->SetTitle("# of counts");
   h5020->GetYaxis()->SetTitleOffset(1.0);
   h5020->Draw();
   h5025->Draw("same");  
   h5030->Draw("same");
   h5035->Draw("same");
   h5040->Draw("same");  
   auto legend50 = new TLegend(0.55,0.6,0.89,0.85);
   legend50->AddEntry(h5020,"d=5 mm, E=0 MeV, w_{Cu}=20 mm","l");
   legend50->AddEntry(h5025,"d=5 mm, E=0 MeV, w_{Cu}=35 mm","l");
   legend50->AddEntry(h5030,"d=5 mm, E=0 MeV, w_{Cu}=30 mm","l");
   legend50->AddEntry(h5035,"d=5 mm, E=0 MeV, w_{Cu}=35 mm","l");
   legend50->AddEntry(h5040,"d=5 mm, E=0 MeV, w_{Cu}=40 mm","l");
   legend50->Draw();
   
   d->SaveAs("w_comp_E_0MeV.pdf");
   d->SaveAs("w_comp_E_0MeV.png");
   d->SaveAs("w_comp_E_0MeV.C");
 


   TCanvas *d2 = new TCanvas("d2","Edep",800,600);
   d2->Divide(1,3);
   d2->cd(1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1520->SetTitle("");
   h1520->GetXaxis()->SetTitle("E [MeV]");
   h1520->GetYaxis()->SetTitle("# of counts");
   h1520->GetYaxis()->SetTitleOffset(1.0);
   h1520->Draw();
   h1525->Draw("same");  
   h1530->Draw("same");
   h1535->Draw("same");
   h1540->Draw("same");  
   auto legend15 = new TLegend(0.55,0.6,0.89,0.85);
   legend15->AddEntry(h1520,"d=1 mm, E=5 MeV, w_{Cu}=20 mm","l");
   legend15->AddEntry(h1525,"d=1 mm, E=5 MeV, w_{Cu}=25 mm","l");
   legend15->AddEntry(h1530,"d=1 mm, E=5 MeV, w_{Cu}=30 mm","l");
   legend15->AddEntry(h1535,"d=1 mm, E=5 MeV, w_{Cu}=35 mm","l");
   legend15->AddEntry(h1540,"d=1 mm, E=5 MeV, w_{Cu}=40 mm","l");
   legend15->Draw();

   d2->cd(2);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h3520->SetTitle("");
   h3520->GetXaxis()->SetTitle("E [MeV]");
   h3520->GetYaxis()->SetTitle("# of counts");
   h3520->GetYaxis()->SetTitleOffset(1.0);
   h3520->Draw();
   h3525->Draw("same");  
   h3530->Draw("same");
   h3535->Draw("same");
   h3540->Draw("same");  
   auto legend35 = new TLegend(0.55,0.6,0.89,0.85);
   legend35->AddEntry(h3520,"d=3 mm, E=5 MeV, w_{Cu}=20 mm","l");
   legend35->AddEntry(h3525,"d=3 mm, E=5 MeV, w_{Cu}=25 mm","l");
   legend35->AddEntry(h3530,"d=3 mm, E=5 MeV, w_{Cu}=30 mm","l");
   legend35->AddEntry(h3535,"d=3 mm, E=5 MeV, w_{Cu}=35 mm","l");
   legend35->AddEntry(h3540,"d=3 mm, E=5 MeV, w_{Cu}=40 mm","l");
   legend35->Draw();
   
   d2->cd(3);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h5520->SetTitle("");
   h5520->GetXaxis()->SetTitle("E [MeV]");
   h5520->GetYaxis()->SetTitle("# of counts");
   h5520->GetYaxis()->SetTitleOffset(1.0);
   h5520->Draw();
   h5525->Draw("same");  
   h5530->Draw("same");
   h5535->Draw("same");
   h5540->Draw("same");  
   auto legend55 = new TLegend(0.55,0.6,0.89,0.85);
   legend55->AddEntry(h5520,"d=5 mm, E=5 MeV, w_{Cu}=20 mm","l");
   legend55->AddEntry(h5525,"d=5 mm, E=5 MeV, w_{Cu}=25 mm","l");
   legend55->AddEntry(h5530,"d=5 mm, E=5 MeV, w_{Cu}=30 mm","l");
   legend55->AddEntry(h5535,"d=5 mm, E=5 MeV, w_{Cu}=35 mm","l");
   legend55->AddEntry(h5540,"d=5 mm, E=5 MeV, w_{Cu}=40 mm","l");
   legend55->Draw();
   
   d2->SaveAs("w_comp_E_5MeV.pdf");
   d2->SaveAs("w_comp_E_5MeV.png");
   d2->SaveAs("w_comp_E_5MeV.C");



   TCanvas *d3 = new TCanvas("d3","Edep",800,600);
   d3->Divide(1,3);
   d3->cd(1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h11020->SetTitle("");
   h11020->GetXaxis()->SetTitle("E [MeV]");
   h11020->GetYaxis()->SetTitle("# of counts");
   h11020->GetYaxis()->SetTitleOffset(1.0);
   h11020->Draw();
   h11025->Draw("same");  
   h11030->Draw("same");
   h11035->Draw("same");
   h11040->Draw("same");  
   auto legend110 = new TLegend(0.55,0.6,0.89,0.85);
   legend110->AddEntry(h11020,"d=1 mm, E=10 MeV, w_{Cu}=20 mm","l");
   legend110->AddEntry(h11025,"d=1 mm, E=10 MeV, w_{Cu}=25 mm","l");
   legend110->AddEntry(h11030,"d=1 mm, E=10 MeV, w_{Cu}=30 mm","l");
   legend110->AddEntry(h11035,"d=1 mm, E=10 MeV, w_{Cu}=35 mm","l");
   legend110->AddEntry(h11040,"d=1 mm, E=10 MeV, w_{Cu}=40 mm","l");
   legend110->Draw();

   d3->cd(2);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h31020->SetTitle("");
   h31020->GetXaxis()->SetTitle("E [MeV]");
   h31020->GetYaxis()->SetTitle("# of counts");
   h31020->GetYaxis()->SetTitleOffset(1.0);
   h31020->Draw();
   h31025->Draw("same");  
   h31030->Draw("same");
   h31035->Draw("same");
   h31040->Draw("same");  
   auto legend310 = new TLegend(0.55,0.6,0.89,0.85);
   legend310->AddEntry(h31020,"d=3 mm, E=10 MeV, w_{Cu}=20 mm","l");
   legend310->AddEntry(h31025,"d=3 mm, E=10 MeV, w_{Cu}=25 mm","l");
   legend310->AddEntry(h31030,"d=3 mm, E=10 MeV, w_{Cu}=30 mm","l");
   legend310->AddEntry(h31035,"d=3 mm, E=10 MeV, w_{Cu}=35 mm","l");
   legend310->AddEntry(h31040,"d=3 mm, E=10 MeV, w_{Cu}=40 mm","l");
   legend310->Draw();
   
   d3->cd(3);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h51020->SetTitle("");
   h51020->GetXaxis()->SetTitle("E [MeV]");
   h51020->GetYaxis()->SetTitle("# of counts");
   h51020->GetYaxis()->SetTitleOffset(1.0);
   h51020->Draw();
   h51025->Draw("same");  
   h51030->Draw("same");
   h51035->Draw("same");
   h51040->Draw("same");  
   auto legend510 = new TLegend(0.55,0.6,0.89,0.85);
   legend510->AddEntry(h51020,"d=5 mm, E=10 MeV, w_{Cu}=20 mm","l");
   legend510->AddEntry(h51025,"d=5 mm, E=10 MeV, w_{Cu}=25 mm","l");
   legend510->AddEntry(h51030,"d=5 mm, E=10 MeV, w_{Cu}=30 mm","l");
   legend510->AddEntry(h51035,"d=5 mm, E=10 MeV, w_{Cu}=35 mm","l");
   legend510->AddEntry(h51040,"d=5 mm, E=10 MeV, w_{Cu}=40 mm","l");
   legend510->Draw();
      
   d3->SaveAs("w_comp_E_10MeV.pdf");
   d3->SaveAs("w_comp_E_10MeV.png");
   d3->SaveAs("w_comp_E_10MeV.C");



   TCanvas *e = new TCanvas("e","Edep",800,600);
   e->Divide(2,3);
   e->cd(1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1020->SetTitle("");
   h1020->GetXaxis()->SetTitle("E [MeV]");
   h1020->GetYaxis()->SetTitle("# of counts");
   h1020->GetYaxis()->SetTitleOffset(1.0);
   h1020->Draw();
   h1520->Draw("same");  
   h11020->Draw("same");  
   auto legend120 = new TLegend(0.55,0.7,0.89,0.85);
   legend120->AddEntry(h1020,"d=1 mm, E=0 MeV, w_{Cu}=20 mm","l");
   legend120->AddEntry(h1520,"d=1 mm, E=5 MeV, w_{Cu}=20 mm","l");
   legend120->AddEntry(h11020,"d=1 mm, E=10 MeV, w_{Cu}=20 mm","l");
   legend120->Draw();

   e->cd(2);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1025->SetTitle("");
   h1025->GetXaxis()->SetTitle("E [MeV]");
   h1025->GetYaxis()->SetTitle("# of counts");
   h1025->GetYaxis()->SetTitleOffset(1.0);
   h1025->Draw();
   h1525->Draw("same");  
   h11025->Draw("same");  
   auto legend125 = new TLegend(0.55,0.7,0.89,0.85);
   legend125->AddEntry(h1025,"d=1 mm, E=0 MeV, w_{Cu}=25 mm","l");
   legend125->AddEntry(h1525,"d=1 mm, E=5 MeV, w_{Cu}=25 mm","l");
   legend125->AddEntry(h11025,"d=1 mm, E=10 MeV, w_{Cu}=25 mm","l");
   legend125->Draw();
   
   e->cd(3);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1030->SetTitle("");
   h1030->GetXaxis()->SetTitle("E [MeV]");
   h1030->GetYaxis()->SetTitle("# of counts");
   h1030->GetYaxis()->SetTitleOffset(1.0);
   h1030->Draw();
   h1530->Draw("same");  
   h11030->Draw("same");  
   auto legend130 = new TLegend(0.55,0.7,0.89,0.85);
   legend130->AddEntry(h1030,"d=1 mm, E=0 MeV, w_{Cu}=30 mm","l");
   legend130->AddEntry(h1530,"d=1 mm, E=5 MeV, w_{Cu}=30 mm","l");
   legend130->AddEntry(h11030,"d=1 mm, E=10 MeV, w_{Cu}=30 mm","l");
   legend130->Draw();
   
   e->cd(4);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1035->SetTitle("");
   h1035->GetXaxis()->SetTitle("E [MeV]");
   h1035->GetYaxis()->SetTitle("# of counts");
   h1035->GetYaxis()->SetTitleOffset(1.0);
   h1035->Draw();
   h1535->Draw("same");  
   h11035->Draw("same");  
   auto legend135 = new TLegend(0.55,0.7,0.89,0.85);
   legend135->AddEntry(h1035,"d=1 mm, E=0 MeV, w_{Cu}=35 mm","l");
   legend135->AddEntry(h1535,"d=1 mm, E=5 MeV, w_{Cu}=35 mm","l");
   legend135->AddEntry(h11035,"d=1 mm, E=10 MeV, w_{Cu}=35 mm","l");
   legend135->Draw();
   
   e->cd(5);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h1040->SetTitle("");
   h1040->GetXaxis()->SetTitle("E [MeV]");
   h1040->GetYaxis()->SetTitle("# of counts");
   h1040->GetYaxis()->SetTitleOffset(1.0);
   h1040->Draw();
   h1540->Draw("same");  
   h11040->Draw("same");  
   auto legend140 = new TLegend(0.55,0.7,0.89,0.85);
   legend140->AddEntry(h1040,"d=1 mm, E=0 MeV, w_{Cu}=40 mm","l");
   legend140->AddEntry(h1540,"d=1 mm, E=5 MeV, w_{Cu}=40 mm","l");
   legend140->AddEntry(h11040,"d=1 mm, E=10 MeV, w_{Cu}=40 mm","l");
   legend140->Draw();
      
   e->SaveAs("E_comp_d_1mm.pdf");
   e->SaveAs("E_comp_d_1mm.png");
   e->SaveAs("E_comp_d_1mm.C");
 
 
 
   TCanvas *e2 = new TCanvas("e2","Edep",800,600);
   e2->Divide(2,3);
   e2->cd(1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h3020->SetTitle("");
   h3020->GetXaxis()->SetTitle("E [MeV]");
   h3020->GetYaxis()->SetTitle("# of counts");
   h3020->GetYaxis()->SetTitleOffset(1.0);
   h3020->Draw();
   h3520->Draw("same");  
   h31020->Draw("same");  
   auto legend320 = new TLegend(0.55,0.7,0.89,0.85);
   legend320->AddEntry(h3020,"d=3 mm, E=0 MeV, w_{Cu}=20 mm","l");
   legend320->AddEntry(h3520,"d=3 mm, E=5 MeV, w_{Cu}=20 mm","l");
   legend320->AddEntry(h31020,"d=3 mm, E=10 MeV, w_{Cu}=20 mm","l");
   legend320->Draw();

   e2->cd(2);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h3025->SetTitle("");
   h3025->GetXaxis()->SetTitle("E [MeV]");
   h3025->GetYaxis()->SetTitle("# of counts");
   h3025->GetYaxis()->SetTitleOffset(1.0);
   h3025->Draw();
   h3525->Draw("same");  
   h31025->Draw("same");  
   auto legend325 = new TLegend(0.55,0.7,0.89,0.85);
   legend325->AddEntry(h3025,"d=3 mm, E=0 MeV, w_{Cu}=25 mm","l");
   legend325->AddEntry(h3525,"d=3 mm, E=5 MeV, w_{Cu}=25 mm","l");
   legend325->AddEntry(h31025,"d=3 mm, E=10 MeV, w_{Cu}=25 mm","l");
   legend325->Draw();
   
   e2->cd(3);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h3030->SetTitle("");
   h3030->GetXaxis()->SetTitle("E [MeV]");
   h3030->GetYaxis()->SetTitle("# of counts");
   h3030->GetYaxis()->SetTitleOffset(1.0);
   h3030->Draw();
   h3530->Draw("same");  
   h31030->Draw("same");  
   auto legend330 = new TLegend(0.55,0.7,0.89,0.85);
   legend330->AddEntry(h3030,"d=3 mm, E=0 MeV, w_{Cu}=30 mm","l");
   legend330->AddEntry(h3530,"d=3 mm, E=5 MeV, w_{Cu}=30 mm","l");
   legend330->AddEntry(h31030,"d=3 mm, E=10 MeV, w_{Cu}=30 mm","l");
   legend330->Draw();
   
   e2->cd(4);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h3035->SetTitle("");
   h3035->GetXaxis()->SetTitle("E [MeV]");
   h3035->GetYaxis()->SetTitle("# of counts");
   h3035->GetYaxis()->SetTitleOffset(1.0);
   h3035->Draw();
   h3535->Draw("same");  
   h31035->Draw("same");  
   auto legend335 = new TLegend(0.55,0.7,0.89,0.85);
   legend335->AddEntry(h3035,"d=3 mm, E=0 MeV, w_{Cu}=35 mm","l");
   legend335->AddEntry(h3535,"d=3 mm, E=5 MeV, w_{Cu}=35 mm","l");
   legend335->AddEntry(h31035,"d=3 mm, E=10 MeV, w_{Cu}=35 mm","l");
   legend335->Draw();
   
   e2->cd(5);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h3040->SetTitle("");
   h3040->GetXaxis()->SetTitle("E [MeV]");
   h3040->GetYaxis()->SetTitle("# of counts");
   h3040->GetYaxis()->SetTitleOffset(1.0);
   h3040->Draw();
   h3540->Draw("same");  
   h31040->Draw("same");  
   auto legend340 = new TLegend(0.55,0.7,0.89,0.85);
   legend340->AddEntry(h3040,"d=3 mm, E=0 MeV, w_{Cu}=40 mm","l");
   legend340->AddEntry(h3540,"d=3 mm, E=5 MeV, w_{Cu}=40 mm","l");
   legend340->AddEntry(h31040,"d=3 mm, E=10 MeV, w_{Cu}=40 mm","l");
   legend340->Draw();
   
   e2->SaveAs("E_comp_d_3mm.pdf");
   e2->SaveAs("E_comp_d_3mm.png");
   e2->SaveAs("E_comp_d_3mm.C");
   
   
   
   TCanvas *e3 = new TCanvas("e3","Edep",800,600);
   e3->Divide(2,3);
   e3->cd(1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h5020->SetTitle("");
   h5020->GetXaxis()->SetTitle("E [MeV]");
   h5020->GetYaxis()->SetTitle("# of counts");
   h5020->GetYaxis()->SetTitleOffset(1.0);
   h5020->Draw();
   h5520->Draw("same");  
   h51020->Draw("same");  
   auto legend5202 = new TLegend(0.55,0.7,0.89,0.85);
   legend5202->AddEntry(h11020,"d=5 mm, E=0 MeV, w_{Cu}=20 mm","l");
   legend5202->AddEntry(h31020,"d=5 mm, E=5 MeV, w_{Cu}=20 mm","l");
   legend5202->AddEntry(h51020,"d=5 mm, E=10 MeV, w_{Cu}=20 mm","l");
   legend5202->Draw();

   e3->cd(2);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h5025->SetTitle("");
   h5025->GetXaxis()->SetTitle("E [MeV]");
   h5025->GetYaxis()->SetTitle("# of counts");
   h5025->GetYaxis()->SetTitleOffset(1.0);
   h5025->Draw();
   h5525->Draw("same");  
   h51025->Draw("same");  
   auto legend5252 = new TLegend(0.55,0.7,0.89,0.85);
   legend5252->AddEntry(h5025,"d=5 mm, E=0 MeV, w_{Cu}=25 mm","l");
   legend5252->AddEntry(h5525,"d=5 mm, E=5 MeV, w_{Cu}=25 mm","l");
   legend5252->AddEntry(h51025,"d=5 mm, E=10 MeV, w_{Cu}=25 mm","l");
   legend5252->Draw();
   
   e3->cd(3);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h5030->SetTitle("");
   h5030->GetXaxis()->SetTitle("E [MeV]");
   h5030->GetYaxis()->SetTitle("# of counts");
   h5030->GetYaxis()->SetTitleOffset(1.0);
   h5030->Draw();
   h5530->Draw("same");  
   h51030->Draw("same");  
   auto legend5302 = new TLegend(0.55,0.7,0.89,0.85);
   legend5302->AddEntry(h5030,"d=5 mm, E=0 MeV, w_{Cu}=30 mm","l");
   legend5302->AddEntry(h5530,"d=5 mm, E=5 MeV, w_{Cu}=30 mm","l");
   legend5302->AddEntry(h51030,"d=5 mm, E=10 MeV, w_{Cu}=30 mm","l");
   legend5302->Draw();
   
   e3->cd(4);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h5035->SetTitle("");
   h5035->GetXaxis()->SetTitle("E [MeV]");
   h5035->GetYaxis()->SetTitle("# of counts");
   h5035->GetYaxis()->SetTitleOffset(1.0);
   h5035->Draw();
   h5535->Draw("same");  
   h51035->Draw("same");  
   auto legend5352 = new TLegend(0.55,0.7,0.89,0.85);
   legend5352->AddEntry(h5035,"d=5 mm, E=0 MeV, w_{Cu}=35 mm","l");
   legend5352->AddEntry(h5535,"d=5 mm, E=5 MeV, w_{Cu}=35 mm","l");
   legend5352->AddEntry(h51035,"d=5 mm, E=10 MeV, w_{Cu}=35 mm","l");
   legend5352->Draw();
   
   e3->cd(5);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h5040->SetTitle("");
   h5040->GetXaxis()->SetTitle("E [MeV]");
   h5040->GetYaxis()->SetTitle("# of counts");
   h5040->GetYaxis()->SetTitleOffset(1.0);
   h5040->Draw();
   h5540->Draw("same");  
   h51040->Draw("same");  
   auto legend5402 = new TLegend(0.55,0.7,0.89,0.85);
   legend5402->AddEntry(h5040,"d=5 mm, E=0 MeV, w_{Cu}=40 mm","l");
   legend5402->AddEntry(h5540,"d=5 mm, E=5 MeV, w_{Cu}=40 mm","l");
   legend5402->AddEntry(h51040,"d=5 mm, E=10 MeV, w_{Cu}=40 mm","l");
   legend5402->Draw();
   
   e3->SaveAs("E_comp_d_5mm.pdf");
   e3->SaveAs("E_comp_d_5mm.png");
   e3->SaveAs("E_comp_d_5mm.C");


} 
 
 int main() {
   plothist();
   return 0;
}  
