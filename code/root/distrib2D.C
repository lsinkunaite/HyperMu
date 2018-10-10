/*//////////////////////////////////////////////////////////*/
/*                      distrib2D.C                         */
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

void distrib2D(){
	
   //Some style definitions
   //gROOT->Reset();
   //gROOT->SetStyle("Plain");
   gStyle->SetPaperSize(26,20);
   //gStyle->SetOptStat(1);
   gStyle->SetOptStat(0);
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

   const int nbins = 150;

   // Names of the files
   std::string filemu = "../../simdata/recover/4mm_Al_4mm_SciD_4mm_Al_300mm_BGO_10mm_SciD_TB_1e5mudecay.root";
   std::string filex = "../../simdata/recover/4mm_Al_4mm_SciD_4mm_Al_300mm_BGO_10mm_SciD_TB_1e5goldcascade.root";

   // TFiles 
   TFile* fmu = new TFile(TString(filemu));
   TFile* fx = new TFile(TString(filex));
   
   // Histograms
   TH2F *hmuSciD1 = new TH2F("hmuSciD1","x vs y",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hmuSciD2 = new TH2F("hmuSciD2","x vs y",nbins-1,-5,5,nbins-1,-100,100);
   TH2F *hmuSciD3 = new TH2F("hmuSciD3","x vs y",nbins-1,-5,5,nbins-1,-100,100);
   TH2F *hmuBGOD1 = new TH2F("hmuBGOD1","x vs y",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hxSciD1 = new TH2F("hxSciD1","x vs y",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hxSciD2 = new TH2F("hxSciD2","x vs y",nbins-1,-5,5,nbins-1,-100,100);
   TH2F *hxSciD3 = new TH2F("hxSciD3","x vs y",nbins-1,-5,5,nbins-1,-100,100);
   TH2F *hxBGOD1 = new TH2F("hxBGOD1","x vs y",nbins-1,-100,100,nbins-1,-100,100);
   // Histograms for the z-projections
   TH1F *hmuSciD1z = new TH1F("hmuSciD1z","z",nbins-1,-2,2);
   TH1F *hmuSciD2z = new TH1F("hmuSciD2z","z",nbins-1,-150,150);
   TH1F *hmuSciD3z = new TH1F("hmuSciD3z","z",nbins-1,-150,150);
   TH1F *hmuBGOD1z = new TH1F("hmuBGOD1z","z",nbins-1,-150,150);
   TH1F *hxSciD1z = new TH1F("hxSciD1z","z",nbins-1,-2,2);
   TH1F *hxSciD2z = new TH1F("hxSciD2z","z",nbins-1,-150,150);
   TH1F *hxSciD3z = new TH1F("hxSciD3z","z",nbins-1,-150,150);
   TH1F *hxBGOD1z = new TH1F("hxBGOD1z","z",nbins-1,-150,150);
   
   
   // TTrees
   TTree *tmuSciD1 = (TTree*)fmu->Get("Detector/SciDet1");
   TTree *tmuSciD2 = (TTree*)fmu->Get("Detector/SciDet2");
   TTree *tmuSciD3 = (TTree*)fmu->Get("Detector/SciDet3");
   TTree *tmuBGOD1 = (TTree*)fmu->Get("Detector/BGODet1");
   TTree *txSciD1 = (TTree*)fx->Get("Detector/SciDet1");
   TTree *txSciD2 = (TTree*)fx->Get("Detector/SciDet2");
   TTree *txSciD3 = (TTree*)fx->Get("Detector/SciDet3");
   TTree *txBGOD1 = (TTree*)fx->Get("Detector/BGODet1");
   
   // Drawings
   tmuSciD1->Draw("x:y>>hmuSciD1","","");
   tmuSciD2->Draw("x:y>>hmuSciD2","","");
   tmuSciD3->Draw("x:y>>hmuSciD3","","");
   tmuBGOD1->Draw("x:y>>hmuBGOD1","","");
   txSciD1->Draw("x:y>>hxSciD1","","");
   txSciD2->Draw("x:y>>hxSciD2","","");
   txSciD3->Draw("x:y>>hxSciD3","","");
   txBGOD1->Draw("x:y>>hxBGOD1","","");
   // Z-projections
   tmuSciD1->Draw("z>>hmuSciD1z","","");
   tmuSciD2->Draw("z>>hmuSciD2z","","");
   tmuSciD3->Draw("z>>hmuSciD3z","","");
   tmuBGOD1->Draw("z>>hmuBGOD1z","","");
   txSciD1->Draw("z>>hxSciD1z","","");
   txSciD2->Draw("z>>hxSciD2z","","");
   txSciD3->Draw("z>>hxSciD3z","","");
   txBGOD1->Draw("z>>hxBGOD1z","","");
   


   ////////////////////////////////////////////////////////// SciDet1-mu
   TCanvas *c1 = new TCanvas("c1", "c1",800,600);
   
   // Create the three pads
   TPad *PadC1 = new TPad("PadC1", "PadC1",0.0,0.0,0.5,0.45); PadC1->Draw();
   TPad *PadR1 = new TPad("PadR1", "PadR1",0.55,0.0,1.0,0.6); PadR1->Draw();
   TPad *PadT1 = new TPad("PadT1", "PadT1",0.0,0.55,0.6,1.0); PadT1->Draw();
   TPad *PadV1 = new TPad("PadV1", "PadV1",0.55,0.55,1.0,1.0); PadV1->Draw();

   TH1D * hmuSciD1x = hmuSciD1->ProjectionX();
   TH1D * hmuSciD1y = hmuSciD1->ProjectionY();

   // Drawing
   PadC1->cd();
   gStyle->SetPalette(1);
   hmuSciD1->Draw("COLZ");
   PadT1->cd();
   hmuSciD1x->SetFillColor(kBlue+1);
   hmuSciD1x->SetTitle("X-projection");
   hmuSciD1x->Draw("bar");
   PadR1->cd();
   hmuSciD1y->SetFillColor(kBlue-2);
   hmuSciD1y->SetTitle("Y-projection");
   hmuSciD1y->Draw("hbar");
   PadV1->cd();
   hmuSciD1z->SetTitle("Z");
   hmuSciD1z->Draw();

   c1->cd();
   TLatex *t1 = new TLatex();
   t1->SetTextFont(42);
   t1->SetTextSize(0.02);
   t1->DrawLatex(0.11,0.52,"#mu-decay: SciDet_{1}, 10^{5} generated events");
   t1->DrawLatex(0.11,0.49,"[2 x 4-mm Al, 4-mm SciD_{1}, 300-mm BGO, 2x 10-mm SciD_{2,3}]");

   c1->SaveAs("distrib2D_muSciD1_2x4mm_Al_300mm_BGO_2x10mm_SciD.pdf");
   c1->SaveAs("distrib2D_muSciD1_2x4mm_Al_300mm_BGO_2x10mm_SciD.png");
   c1->SaveAs("distrib2D_muSciD1_2x4mm_Al_300mm_BGO_2x10mm_SciD.C");


   ////////////////////////////////////////////////////////// SciDet2-mu
   TCanvas *c2 = new TCanvas("c2", "c2",800,600);
   
   // Create the three pads
   TPad *PadC2 = new TPad("PadC2", "PadC2",0.0,0.0,0.5,0.45); PadC2->Draw();
   TPad *PadR2 = new TPad("PadR2", "PadR2",0.55,0.0,1.0,0.6); PadR2->Draw();
   TPad *PadT2 = new TPad("PadT2", "PadT2",0.0,0.55,0.6,1.0); PadT2->Draw();
   TPad *PadV2 = new TPad("PadV2", "PadV2",0.55,0.55,1.0,1.0); PadV2->Draw();

   TH1D * hmuSciD2x = hmuSciD2->ProjectionX();
   TH1D * hmuSciD2y = hmuSciD2->ProjectionY();

   // Drawing
   PadC2->cd();
   gStyle->SetPalette(1);
   hmuSciD2->Draw("COLZ");
   PadT2->cd();
   hmuSciD2x->SetFillColor(kBlue+1);
   hmuSciD2x->SetTitle("X-projection");
   hmuSciD2x->Draw("bar");
   PadR2->cd();
   hmuSciD2y->SetFillColor(kBlue-2);
   hmuSciD2y->SetTitle("Y-projection");
   hmuSciD2y->Draw("hbar");
   PadV2->cd();
   hmuSciD2z->SetTitle("Z");
   hmuSciD2z->Draw();

   c2->cd();
   TLatex *t2 = new TLatex();
   t2->SetTextFont(42);
   t2->SetTextSize(0.02);
   t2->DrawLatex(0.11,0.52,"#mu-decay: SciDet_{2}, 10^{5}, generated events");
   t2->DrawLatex(0.11,0.49,"[2 x 4-mm Al, 4-mm SciD_{1}, 300-mm BGO, 2x 10-mm SciD_{2,3}]");

   c2->SaveAs("distrib2D_muSciD2_2x4mm_Al_300mm_BGO_2x10mm_SciD.pdf");
   c2->SaveAs("distrib2D_muSciD2_2x4mm_Al_300mm_BGO_2x10mm_SciD.png");
   c2->SaveAs("distrib2D_muSciD2_2x4mm_Al_300mm_BGO_2x10mm_SciD.C");


   ////////////////////////////////////////////////////////// SciDet3-mu
   TCanvas *c3 = new TCanvas("c3", "c3",800,600);
   
   // Create the three pads
   TPad *PadC3 = new TPad("PadC3", "PadC3",0.0,0.0,0.5,0.45); PadC3->Draw();
   TPad *PadR3 = new TPad("PadR3", "PadR3",0.55,0.0,1.0,0.6); PadR3->Draw();
   TPad *PadT3 = new TPad("PadT3", "PadT3",0.0,0.55,0.6,1.0); PadT3->Draw();
   TPad *PadV3 = new TPad("PadV3", "PadV3",0.55,0.55,1.0,1.0); PadV3->Draw();

   TH1D * hmuSciD3x = hmuSciD3->ProjectionX();
   TH1D * hmuSciD3y = hmuSciD3->ProjectionY();

   // Drawing
   PadC3->cd();
   gStyle->SetPalette(1);
   hmuSciD3->Draw("COLZ");
   PadT3->cd();
   hmuSciD3x->SetFillColor(kBlue+1);
   hmuSciD3x->SetTitle("X-projection");
   hmuSciD3x->Draw("bar");
   PadR3->cd();
   hmuSciD3y->SetFillColor(kBlue-2);
   hmuSciD3y->SetTitle("Y-projection");
   hmuSciD3y->Draw("hbar");
   PadV3->cd();
   hmuSciD3z->SetTitle("Z");
   hmuSciD3z->Draw();

   c3->cd();
   TLatex *t3 = new TLatex();
   t3->SetTextFont(42);
   t3->SetTextSize(0.02);
   t3->DrawLatex(0.11,0.52,"#mu-decay: SciDet_{3}, 10^{5} generated events");
   t3->DrawLatex(0.11,0.49,"[2 x 4-mm Al, 4-mm SciD_{1}, 300-mm BGO, 2x 10-mm SciD_{2,3}]");

   c3->SaveAs("distrib2D_muSciD3_2x4mm_Al_300mm_BGO_2x10mm_SciD.pdf");
   c3->SaveAs("distrib2D_muSciD3_2x4mm_Al_300mm_BGO_2x10mm_SciD.png");
   c3->SaveAs("distrib2D_muSciD3_2x4mm_Al_300mm_BGO_2x10mm_SciD.C");


   ////////////////////////////////////////////////////////// BGODet1-mu
   TCanvas *c4 = new TCanvas("c4", "c4",800,600);
   
   // Create the three pads
   TPad *PadC4 = new TPad("PadC4", "PadC4",0.0,0.0,0.5,0.45); PadC4->Draw();
   TPad *PadR4 = new TPad("PadR4", "PadR4",0.55,0.0,1.0,0.6); PadR4->Draw();
   TPad *PadT4 = new TPad("PadT4", "PadT4",0.0,0.55,0.6,1.0); PadT4->Draw();
   TPad *PadV4 = new TPad("PadV4", "PadV4",0.55,0.55,1.0,1.0); PadV4->Draw();

   TH1D * hmuBGOD1x = hmuBGOD1->ProjectionX();
   TH1D * hmuBGOD1y = hmuBGOD1->ProjectionY();

   // Drawing
   PadC4->cd();
   gStyle->SetPalette(1);
   hmuBGOD1->Draw("COLZ");
   PadT4->cd();
   hmuBGOD1x->SetFillColor(kBlue+1);
   hmuBGOD1x->SetTitle("X-projection");
   hmuBGOD1x->Draw("bar");
   PadR4->cd();
   hmuBGOD1y->SetFillColor(kBlue-2);
   hmuBGOD1y->SetTitle("Y-projection");
   hmuBGOD1y->Draw("hbar");
   PadV4->cd();
   hmuBGOD1z->SetTitle("Z");
   hmuBGOD1z->Draw();

   c4->cd();
   TLatex *t4 = new TLatex();
   t4->SetTextFont(42);
   t4->SetTextSize(0.02);
   t4->DrawLatex(0.11,0.52,"#mu-decay: BGODet_{1}, 10^{5} generated events");
   t4->DrawLatex(0.11,0.49,"[2 x 4-mm Al, 4-mm SciD_{1}, 300-mm BGO, 2x 10-mm SciD_{2,3}]");

   c4->SaveAs("distrib2D_muBGOD1_2x4mm_Al_300mm_BGO_2x10mm_SciD.pdf");
   c4->SaveAs("distrib2D_muBGOD1_2x4mm_Al_300mm_BGO_2x10mm_SciD.png");
   c4->SaveAs("distrib2D_muBGOD1_2x4mm_Al_300mm_BGO_2x10mm_SciD.C");


   /////////////////////////////////////////////////////////// SciDet1-X
   TCanvas *c5 = new TCanvas("c5", "c5",800,600);
   
   // Create the three pads
   TPad *PadC5 = new TPad("PadC5", "PadC5",0.0,0.0,0.5,0.45); PadC5->Draw();
   TPad *PadR5 = new TPad("PadR5", "PadR5",0.55,0.0,1.0,0.6); PadR5->Draw();
   TPad *PadT5 = new TPad("PadT5", "PadT5",0.0,0.55,0.6,1.0); PadT5->Draw();
   TPad *PadV5 = new TPad("PadV5", "PadV5",0.55,0.55,1.0,1.0); PadV5->Draw();

   TH1D * hxSciD1x = hxSciD1->ProjectionX();
   TH1D * hxSciD1y = hxSciD1->ProjectionY();

   // Drawing
   PadC5->cd();
   gStyle->SetPalette(1);
   hxSciD1->Draw("COLZ");
   PadT5->cd();
   hxSciD1x->SetFillColor(kBlue+1);
   hxSciD1x->SetTitle("X-projection");
   hxSciD1x->Draw("bar");
   PadR5->cd();
   hxSciD1y->SetFillColor(kBlue-2);
   hxSciD1y->SetTitle("Y-projection");
   hxSciD1y->Draw("hbar");
   PadV5->cd();
   hxSciD1z->SetTitle("Z");
   hxSciD1z->Draw();

   c5->cd();
   TLatex *t5 = new TLatex();
   t5->SetTextFont(42);
   t5->SetTextSize(0.02);
   t5->DrawLatex(0.11,0.52,"X-cascade: SciDet_{1}, 10^{5} generated events");
   t5->DrawLatex(0.11,0.49,"[2 x 4-mm Al, 4-mm SciD_{1}, 300-mm BGO, 2x 10-mm SciD_{2,3}]");

   c5->SaveAs("distrib2D_xSciD1_2x4mm_Al_300mm_BGO_2x10mm_SciD.pdf");
   c5->SaveAs("distrib2D_xSciD1_2x4mm_Al_300mm_BGO_2x10mm_SciD.png");
   c5->SaveAs("distrib2D_xSciD1_2x4mm_Al_300mm_BGO_2x10mm_SciD.C");


   /////////////////////////////////////////////////////////// SciDet2-X
   TCanvas *c6 = new TCanvas("c6", "c6",800,600);
   
   // Create the three pads
   TPad *PadC6 = new TPad("PadC6", "PadC6",0.0,0.0,0.5,0.45); PadC6->Draw();
   TPad *PadR6 = new TPad("PadR6", "PadR6",0.55,0.0,1.0,0.6); PadR6->Draw();
   TPad *PadT6 = new TPad("PadT6", "PadT6",0.0,0.55,0.6,1.0); PadT6->Draw();
   TPad *PadV6 = new TPad("PadV6", "PadV6",0.55,0.55,1.0,1.0); PadV6->Draw();

   TH1D * hxSciD2x = hxSciD2->ProjectionX();
   TH1D * hxSciD2y = hxSciD2->ProjectionY();

   // Drawing
   PadC6->cd();
   gStyle->SetPalette(1);
   hxSciD2->Draw("COLZ");
   PadT6->cd();
   hxSciD2x->SetFillColor(kBlue+1);
   hxSciD2x->SetTitle("X-projection");
   hxSciD2x->Draw("bar");
   PadR6->cd();
   hxSciD2y->SetFillColor(kBlue-2);
   hxSciD2y->SetTitle("Y-projection");
   hxSciD2y->Draw("hbar");
   PadV6->cd();
   hxSciD2z->SetTitle("Z");
   hxSciD2z->Draw();

   c6->cd();
   TLatex *t6 = new TLatex();
   t6->SetTextFont(42);
   t6->SetTextSize(0.02);
   t6->DrawLatex(0.11,0.52,"X-cascade: SciDet_{2}, 10^{5} generated events");
   t6->DrawLatex(0.11,0.49,"[2 x 4-mm Al, 4-mm SciD_{1}, 300-mm BGO, 2x 10-mm SciD_{2,3}]");

   c6->SaveAs("distrib2D_xSciD2_2x4mm_Al_300mm_BGO_2x10mm_SciD.pdf");
   c6->SaveAs("distrib2D_xSciD2_2x4mm_Al_300mm_BGO_2x10mm_SciD.png");
   c6->SaveAs("distrib2D_xSciD2_2x4mm_Al_300mm_BGO_2x10mm_SciD.C");


   /////////////////////////////////////////////////////////// SciDet3-X
   TCanvas *c7 = new TCanvas("c7", "c7",800,600);
   
   // Create the three pads
   TPad *PadC7 = new TPad("PadC7", "PadC7",0.0,0.0,0.5,0.45); PadC7->Draw();
   TPad *PadR7 = new TPad("PadR7", "PadR7",0.55,0.0,1.0,0.6); PadR7->Draw();
   TPad *PadT7 = new TPad("PadT7", "PadT7",0.0,0.55,0.6,1.0); PadT7->Draw();
   TPad *PadV7 = new TPad("PadV7", "PadV7",0.55,0.55,1.0,1.0); PadV7->Draw();

   TH1D * hxSciD3x = hxSciD3->ProjectionX();
   TH1D * hxSciD3y = hxSciD3->ProjectionY();

   // Drawing
   PadC7->cd();
   gStyle->SetPalette(1);
   hxSciD3->Draw("COLZ");
   PadT7->cd();
   hxSciD3x->SetFillColor(kBlue+1);
   hxSciD3x->SetTitle("X-projection");
   hxSciD3x->Draw("bar");
   PadR7->cd();
   hxSciD3y->SetFillColor(kBlue-2);
   hxSciD3y->SetTitle("Y-projection");
   hxSciD3y->Draw("hbar");
   PadV7->cd();
   hxSciD3z->SetTitle("Z");
   hxSciD3z->Draw();

   c7->cd();
   TLatex *t7 = new TLatex();
   t7->SetTextFont(42);
   t7->SetTextSize(0.02);
   t7->DrawLatex(0.11,0.52,"X-cascade: SciDet_{3}, 10^{5} generated events");
   t7->DrawLatex(0.11,0.49,"[2 x 4-mm Al, 4-mm SciD_{1}, 300-mm BGO, 2x 10-mm SciD_{2,3}]");

   c7->SaveAs("distrib2D_xSciD3_2x4mm_Al_300mm_BGO_2x10mm_SciD.pdf");
   c7->SaveAs("distrib2D_xSciD3_2x4mm_Al_300mm_BGO_2x10mm_SciD.png");
   c7->SaveAs("distrib2D_xSciD3_2x4mm_Al_300mm_BGO_2x10mm_SciD.C");


   /////////////////////////////////////////////////////////// BGODet1-X
   TCanvas *c8 = new TCanvas("c8", "c8",800,600);
   
   // Create the three pads
   TPad *PadC8 = new TPad("PadC8", "PadC8",0.0,0.0,0.5,0.45); PadC8->Draw();
   TPad *PadR8 = new TPad("PadR8", "PadR8",0.55,0.0,1.0,0.6); PadR8->Draw();
   TPad *PadT8 = new TPad("PadT8", "PadT8",0.0,0.55,0.6,1.0); PadT8->Draw();
   TPad *PadV8 = new TPad("PadV8", "PadV8",0.55,0.55,1.0,1.0); PadV8->Draw();

   TH1D * hxBGOD1x = hxBGOD1->ProjectionX();
   TH1D * hxBGOD1y = hxBGOD1->ProjectionY();

   // Drawing
   PadC8->cd();
   gStyle->SetPalette(1);
   hxBGOD1->Draw("COLZ");
   PadT8->cd();
   hxBGOD1x->SetFillColor(kBlue+1);
   hxBGOD1x->SetTitle("X-projection");
   hxBGOD1x->Draw("bar");
   PadR8->cd();
   hxBGOD1y->SetFillColor(kBlue-2);
   hxBGOD1y->SetTitle("Y-projection");
   hxBGOD1y->Draw("hbar");
   PadV8->cd();
   hxBGOD1z->SetTitle("Z");
   hxBGOD1z->Draw();

   c8->cd();
   TLatex *t8 = new TLatex();
   t8->SetTextFont(42);
   t8->SetTextSize(0.02);
   t8->DrawLatex(0.11,0.52,"X-cascade: BGODet_{1}, 10^{5} generated events");
   t8->DrawLatex(0.11,0.49,"[2 x 4-mm Al, 4-mm SciD_{1}, 300-mm BGO, 2x 10-mm SciD_{2,3}]");

   c8->SaveAs("distrib2D_xBGOD1_2x4mm_Al_300mm_BGO_2x10mm_SciD.pdf");
   c8->SaveAs("distrib2D_xBGOD1_2x4mm_Al_300mm_BGO_2x10mm_SciD.png");
   c8->SaveAs("distrib2D_xBGOD1_2x4mm_Al_300mm_BGO_2x10mm_SciD.C");




}


int main() {
   distrib2D();
   return 0;
}  
