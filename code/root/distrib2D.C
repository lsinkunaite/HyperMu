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
   std::string filemu = "../../simdata/magnetic/adBfield_5T_simple_4mm_Al_det_BGO1e5mudecay.root";
   std::string filex = "../../simdata/magnetic/adBfield_5T_simple_4mm_Al_det_BGO1e5goldcascade.root";

   // TFiles 
   TFile* fmu = new TFile(TString(filemu));
   TFile* fx = new TFile(TString(filex));
   
   // Histograms
   TH2F *hmuSciDF = new TH2F("hmuSciDF","Edep",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hmuTubeD = new TH2F("hmuTubeD","Edep",nbins-1,-95,95,nbins-1,-95,95);
   TH2F *hmuSciDE = new TH2F("hmuSciDE","Edep",nbins-1,-50,50,nbins-1,-50,50);
   TH2F *hxSciDF = new TH2F("hxSciDF","Edep",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hxTubeD = new TH2F("hxTubeD","Edep",nbins-1,-95,95,nbins-1,-95,95);
   TH2F *hxSciDE = new TH2F("hxSciDE","Edep",nbins-1,-50,50,nbins-1,-50,50);
   
   // TTrees
   TTree *tmuSciDF = (TTree*)fmu->Get("Detector/SciDetFront");
   TTree *tmuTubeD = (TTree*)fmu->Get("Detector/TubeDet");
   TTree *tmuSciDE = (TTree*)fmu->Get("Detector/SciDetEnd");
   TTree *txSciDF = (TTree*)fx->Get("Detector/SciDetFront");
   TTree *txTubeD = (TTree*)fx->Get("Detector/TubeDet");
   TTree *txSciDE = (TTree*)fx->Get("Detector/SciDetEnd");
   
   // Drawings
   tmuSciDF->Draw("x:y>>hmuSciDF","","");
   tmuTubeD->Draw("x:y>>hmuTubeD","","");
   tmuSciDE->Draw("x:y>>hmuSciDE","","");
   txSciDF->Draw("x:y>>hxSciDF","","");
   txTubeD->Draw("x:y>>hxTubeD","","");
   txSciDE->Draw("x:y>>hxSciDE","","");


   ////////////////////////////////////////////////////// SciDetFront-mu
   TCanvas *c1 = new TCanvas("c1", "c1",800,600);
   
   // Create the three pads
   TPad *PadC1 = new TPad("PadC1", "PadC1",0.0,0.0,0.5,0.45); PadC1->Draw();
   TPad *PadR1 = new TPad("PadR1", "PadR1",0.55,0.0,1.0,0.6); PadR1->Draw();
   TPad *PadT1 = new TPad("PadT1", "PadT1",0.0,0.55,0.6,1.0); PadT1->Draw();

   TH1D * hmuSciDFx = hmuSciDF->ProjectionX();
   TH1D * hmuSciDFy = hmuSciDF->ProjectionY();

   // Drawing
   PadC1->cd();
   gStyle->SetPalette(1);
   //hmuSciDF->Draw("CONT1Z");
   //hmuSciDF->Draw("SURF3");
   hmuSciDF->Draw("COLZ");
   PadT1->cd();
   hmuSciDFx->SetFillColor(kBlue+1);
   hmuSciDFx->SetTitle("Edep vs x");
   hmuSciDFx->Draw("bar");
   PadR1->cd();
   hmuSciDFy->SetFillColor(kBlue-2);
   hmuSciDFy->SetTitle("Edep vs y");
   hmuSciDFy->Draw("hbar");

   c1->cd();
   TLatex *t1 = new TLatex();
   t1->SetTextFont(42);
   t1->SetTextSize(0.02);
   t1->DrawLatex(0.6,0.88,"#mu-decay: SciDetFront, 10^{5} generated events");
   t1->DrawLatex(0.6,0.85,"200-mm x 200-mm, 4-mm long");

   c1->SaveAs("distrib2D_muSciDF.pdf");
   c1->SaveAs("distrib2D_muSciDF.png");
   c1->SaveAs("distrib2D_muSciDF.C");


   ////////////////////////////////////////////////////////// TubeDet-mu
   TCanvas *c2 = new TCanvas("c2", "c2",800,600);
   
   // Create the three pads
   TPad *PadC2 = new TPad("PadC2", "PadC2",0.0,0.0,0.5,0.45); PadC2->Draw();
   TPad *PadR2 = new TPad("PadR2", "PadR2",0.55,0.0,1.0,0.6); PadR2->Draw();
   TPad *PadT2 = new TPad("PadT2", "PadT2",0.0,0.55,0.6,1.0); PadT2->Draw();

   TH1D * hmuTubeDx = hmuTubeD->ProjectionX();
   TH1D * hmuTubeDy = hmuTubeD->ProjectionY();
 
   // Drawing
   PadC2->cd(); 
   gStyle->SetPalette(1); 
   hmuTubeD->Draw("COLZ");
   PadT2->cd(); 
   hmuTubeDx->SetFillColor(kBlue+1); 
   hmuTubeDx->SetTitle("Edep vs x"); 
   hmuTubeDx->Draw("bar");
   PadR2->cd();
   hmuTubeDy->SetFillColor(kBlue-2);
   hmuTubeDy->SetTitle("Edep vs y");
   hmuTubeDy->Draw("hbar");

   c2->cd();
   TLatex *t2 = new TLatex();
   t2->SetTextFont(42);
   t2->SetTextSize(0.02);
   t2->DrawLatex(0.6,0.88,"#mu-decay: TubeDet, 10^{5} generated events");
   t2->DrawLatex(0.6,0.85,"50-mm round, 300-mm long");

   c2->SaveAs("distrib2D_muTubeD.pdf");
   c2->SaveAs("distrib2D_muTubeD.png");
   c2->SaveAs("distrib2D_muTubeD.C");


   //////////////////////////////////////////////////////// SciDetEnd-mu
   TCanvas *c3 = new TCanvas("c3", "c3",800,600);
   
   TPad *PadC3 = new TPad("PadC3", "PadC3",0.0,0.0,0.5,0.45); PadC3->Draw();
   TPad *PadR3 = new TPad("PadR3", "PadR3",0.55,0.0,1.0,0.6); PadR3->Draw();
   TPad *PadT3 = new TPad("PadT3", "PadT3",0.0,0.55,0.6,1.0); PadT3->Draw();

   PadC3->Draw();
   PadR3->Draw();
   PadT3->Draw();
   
   TH1D * hmuSciDEx = hmuSciDE->ProjectionX();
   TH1D * hmuSciDEy = hmuSciDE->ProjectionY();
 
   // Drawing
   PadC3->cd(); 
   gStyle->SetPalette(1); 
   hmuSciDE->Draw("COLZ");
   PadT3->cd(); 
   hmuSciDEx->SetFillColor(kBlue+1); 
   hmuSciDEx->SetTitle("Edep vs x"); 
   hmuSciDEx->Draw("bar");
   PadR3->cd();
   hmuSciDEy->SetFillColor(kBlue-2);
   hmuSciDEy->SetTitle("Edep vs y");
   hmuSciDEy->Draw("hbar");

   c3->cd();
   TLatex *t3 = new TLatex();
   t3->SetTextFont(42);
   t3->SetTextSize(0.02);
   t3->DrawLatex(0.6,0.88,"#mu-decay: SciDetEnd, 10^{5} generated events");
   t3->DrawLatex(0.6,0.85,"100-mm x 100-mm, 200-mm long");

   c3->SaveAs("distrib2D_muSciDE.pdf");
   c3->SaveAs("distrib2D_muSciDE.png");
   c3->SaveAs("distrib2D_muSciDE.C");


   /////////////////////////////////////////////////////// SciDetFront-X
   TCanvas *c4 = new TCanvas("c4", "c4",800,600);
   
   TPad *PadC4 = new TPad("PadC4", "PadC4",0.0,0.0,0.5,0.45); PadC4->Draw();
   TPad *PadR4 = new TPad("PadR4", "PadR4",0.55,0.0,1.0,0.6); PadR4->Draw();
   TPad *PadT4 = new TPad("PadT4", "PadT4",0.0,0.55,0.6,1.0); PadT4->Draw();

   TH1D * hxSciDFx = hxSciDF->ProjectionX();
   TH1D * hxSciDFy = hxSciDF->ProjectionY();

   // Drawing
   PadC4->cd();
   gStyle->SetPalette(1);
   hxSciDF->Draw("COLZ");
   PadT4->cd();
   hxSciDFx->SetFillColor(kBlue+1);
   hxSciDFx->SetTitle("Edep vs x");
   hxSciDFx->Draw("bar");
   PadR4->cd();
   hxSciDFy->SetFillColor(kBlue-2);
   hxSciDFy->SetTitle("Edep vs y");
   hxSciDFy->Draw("hbar");

   c4->cd();
   TLatex *t4 = new TLatex();
   t4->SetTextFont(42);
   t4->SetTextSize(0.02);
   t4->DrawLatex(0.6,0.88,"X-ray cascade: SciDetFront, 10^{5} generated events");
   t4->DrawLatex(0.6,0.85,"200-mm x 200-mm, 4-mm long");

   c4->SaveAs("distrib2D_xSciDF.pdf");
   c4->SaveAs("distrib2D_xSciDF.png");
   c4->SaveAs("distrib2D_xSciDF.C");


   /////////////////////////////////////////////////////////// TubeDet-X
   TCanvas *c5 = new TCanvas("c5", "c5",800,600);
   
   // Create the three pads
   TPad *PadC5 = new TPad("PadC5", "PadC5",0.0,0.0,0.5,0.45); PadC5->Draw();
   TPad *PadR5 = new TPad("PadR5", "PadR5",0.55,0.0,1.0,0.6); PadR5->Draw();
   TPad *PadT5 = new TPad("PadT5", "PadT5",0.0,0.55,0.6,1.0); PadT5->Draw();

   TH1D * hxTubeDx = hxTubeD->ProjectionX();
   TH1D * hxTubeDy = hxTubeD->ProjectionY();
 
   // Drawing
   PadC5->cd(); 
   gStyle->SetPalette(1); 
   hxTubeD->Draw("COLZ");
   PadT5->cd(); 
   hxTubeDx->SetFillColor(kBlue+1); 
   hxTubeDx->SetTitle("Edep vs x"); 
   hxTubeDx->Draw("bar");
   PadR5->cd();
   hxTubeDy->SetFillColor(kBlue-2);
   hxTubeDy->SetTitle("Edep vs y");
   hxTubeDy->Draw("hbar");

   c5->cd();
   TLatex *t5 = new TLatex();
   t5->SetTextFont(42);
   t5->SetTextSize(0.02);
   t5->DrawLatex(0.6,0.88,"X-ray cascade: TubeDet, 10^{5} generated events");
   t5->DrawLatex(0.6,0.85,"50-mm round, 300-mm long");

   c5->SaveAs("distrib2D_xTubeD.pdf");
   c5->SaveAs("distrib2D_xTubeD.png");
   c5->SaveAs("distrib2D_xTubeD.C");


   ///////////////////////////////////////////////////////// SciDetEnd-X
   TCanvas *c6 = new TCanvas("c6", "c6",800,600);
   
   TPad *PadC6 = new TPad("PadC6", "PadC6",0.0,0.0,0.5,0.45); PadC6->Draw();
   TPad *PadR6 = new TPad("PadR6", "PadR6",0.55,0.0,1.0,0.6); PadR6->Draw();
   TPad *PadT6 = new TPad("PadT6", "PadT6",0.0,0.55,0.6,1.0); PadT6->Draw();

   PadC6->Draw();
   PadR6->Draw();
   PadT6->Draw();
   
   TH1D * hxSciDEx = hxSciDE->ProjectionX();
   TH1D * hxSciDEy = hxSciDE->ProjectionY();
 
   // Drawing
   PadC6->cd(); 
   gStyle->SetPalette(1); 
   hxSciDE->Draw("COLZ");
   PadT6->cd(); 
   hxSciDEx->SetFillColor(kBlue+1); 
   hxSciDEx->SetTitle("Edep vs x"); 
   hxSciDEx->Draw("bar");
   PadR6->cd();
   hxSciDEy->SetFillColor(kBlue-2);
   hxSciDEy->SetTitle("Edep vs y");
   hxSciDEy->Draw("hbar");

   c6->cd();
   TLatex *t6 = new TLatex();
   t6->SetTextFont(42);
   t6->SetTextSize(0.02);
   t6->DrawLatex(0.6,0.88,"X-ray cascade: SciDetEnd, 10^{5} generated events");
   t6->DrawLatex(0.6,0.85,"100-mm x 100-mm, 200-mm long");

   c6->SaveAs("distrib2D_xSciDE.pdf");
   c6->SaveAs("distrib2D_xSciDE.png");
   c6->SaveAs("distrib2D_xSciDE.C");



}


int main() {
   distrib2D();
   return 0;
}  
