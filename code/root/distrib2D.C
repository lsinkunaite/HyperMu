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
   std::string filemu = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5mudecay.root";
   std::string filex = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5goldcascade.root";

   // TFiles 
   TFile* fmu = new TFile(TString(filemu));
   TFile* fx = new TFile(TString(filex));
   
   // Histograms
   TH2F *hmuSciDFIn1 = new TH2F("hmuSciDFIn1","x vs y",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hmuSciDFIn2 = new TH2F("hmuSciDFIn2","x vs y",nbins-1,-100,100,nbins-1,-100,100);
   //TH2F *hmuSciDF = new TH2F("hmuSciDF","x vs y",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hmuTubeD = new TH2F("hmuTubeD","x vs y",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hmuSciDE = new TH2F("hmuSciDE","x vs y",nbins-1,-50,50,nbins-1,-50,50);
   TH2F *hxSciDFIn1 = new TH2F("hxSciDFIn1","x vs y",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hxSciDFIn2 = new TH2F("hxSciDFIn2","x vs y",nbins-1,-100,100,nbins-1,-100,100);
   //TH2F *hxSciDF = new TH2F("hxSciDF","x vs y",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hxTubeD = new TH2F("hxTubeD","x vs y",nbins-1,-95,95,nbins-1,-95,95);
   TH2F *hxSciDE = new TH2F("hxSciDE","x vs y",nbins-1,-50,50,nbins-1,-50,50);
   // Histograms for the z-projections
   TH2F *hmuSciDFIn1z = new TH2F("hmuSciDFIn1z","z",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hmuSciDFIn2z = new TH2F("hmuSciDFIn2z","z",nbins-1,-100,100,nbins-1,-100,100);
   //TH2F *hmuSciDFz = new TH2F("hmuSciDFz","z",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hmuTubeDz = new TH2F("hmuTubeDz","z",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hmuSciDEz = new TH2F("hmuSciDEz","z",nbins-1,-50,50,nbins-1,-50,50);
   TH2F *hxSciDFIn1z = new TH2F("hxSciDFIn1z","z",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hxSciDFIn2z = new TH2F("hxSciDFIn2z","z",nbins-1,-100,100,nbins-1,-100,100);
   //TH2F *hxSciDFz = new TH2F("hxSciDFz","z",nbins-1,-100,100,nbins-1,-100,100);
   TH2F *hxTubeDz = new TH2F("hxTubeDz","z",nbins-1,-95,95,nbins-1,-95,95);
   TH2F *hxSciDEz = new TH2F("hxSciDEz","z",nbins-1,-50,50,nbins-1,-50,50);
 
   
   // TTrees
   TTree *tmuSciDFIn1 = (TTree*)fmu->Get("Detector/H2BoxSciDetFrontIn1");
   TTree *tmuSciDFIn2 = (TTree*)fmu->Get("Detector/H2BoxSciDetFrontIn2");
   //TTree *tmuSciDF = (TTree*)fmu->Get("Detector/SciDetFront");
   TTree *tmuTubeD = (TTree*)fmu->Get("Detector/TubeDet");
   TTree *tmuSciDE = (TTree*)fmu->Get("Detector/SciDetEnd");
   TTree *txSciDFIn1 = (TTree*)fx->Get("Detector/H2BoxSciDetFrontIn1");
   TTree *txSciDFIn2 = (TTree*)fx->Get("Detector/H2BoxSciDetFrontIn2");
   //TTree *txSciDF = (TTree*)fx->Get("Detector/SciDetFront");
   TTree *txTubeD = (TTree*)fx->Get("Detector/TubeDet");
   TTree *txSciDE = (TTree*)fx->Get("Detector/SciDetEnd");
   
   // Drawings
   tmuSciDFIn1->Draw("x:y>>hmuSciDFIn1","","");
   tmuSciDFIn2->Draw("x:y>>hmuSciDFIn2","","");
   //tmuSciDF->Draw("x:y>>hmuSciDF","","");
   tmuTubeD->Draw("x:y>>hmuTubeD","","");
   tmuSciDE->Draw("x:y>>hmuSciDE","","");
   txSciDFIn1->Draw("x:y>>hxSciDFIn1","","");
   txSciDFIn2->Draw("x:y>>hxSciDFIn2","","");
   //txSciDF->Draw("x:y>>hxSciDF","","");
   txTubeD->Draw("x:y>>hxTubeD","","");
   txSciDE->Draw("x:y>>hxSciDE","","");
   // Z-projections
   tmuSciDFIn1->Draw("z>>hmuSciDFIn1z","","");
   tmuSciDFIn2->Draw("z>>hmuSciDFIn2z","","");
   //tmuSciDF->Draw("z>>hmuSciDFz","","");
   tmuTubeD->Draw("z>>hmuTubeDz","","");
   tmuSciDE->Draw("z>>hmuSciDEz","","");
   txSciDFIn1->Draw("z>>hxSciDFIn1z","","");
   txSciDFIn2->Draw("z>>hxSciDFIn2z","","");
   //txSciDF->Draw("z>>hxSciDFz","","");
   txTubeD->Draw("z>>hxTubeDz","","");
   txSciDE->Draw("z>>hxSciDEz","","");


/*
   ////////////////////////////////////////////////////// SciDetFront-mu
   TCanvas *c1 = new TCanvas("c1", "c1",800,600);
   
   // Create the three pads
   TPad *PadC1 = new TPad("PadC1", "PadC1",0.0,0.0,0.5,0.45); PadC1->Draw();
   TPad *PadR1 = new TPad("PadR1", "PadR1",0.55,0.0,1.0,0.6); PadR1->Draw();
   TPad *PadT1 = new TPad("PadT1", "PadT1",0.0,0.55,0.6,1.0); PadT1->Draw();
   TPad *PadV1 = new TPad("PadV1", "PadV1",0.55,0.55,1.0,1.0); PadV1->Draw();

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
   hmuSciDFx->SetTitle("X-projection");
   hmuSciDFx->Draw("bar");
   PadR1->cd();
   hmuSciDFy->SetFillColor(kBlue-2);
   hmuSciDFy->SetTitle("Y-projection");
   hmuSciDFy->Draw("hbar");
   PadV1->cd();
   hmuSciDFz->SetTitle("Z");
   hmuSciDFz->Draw();

   c1->cd();
   TLatex *t1 = new TLatex();
   t1->SetTextFont(42);
   t1->SetTextSize(0.02);
   t1->DrawLatex(0.11,0.52,"#mu-decay: SciDetFront [smSDE, 5mmAlBGO, 2-mm Al], 10^{5} generated events");
   t1->DrawLatex(0.11,0.49,"200-mm x 200-mm, 4-mm long");

   c1->SaveAs("distrib2D_muSciDF_5mmAlTD_2mm_Al_Scintillator.pdf");
   c1->SaveAs("distrib2D_muSciDF_5mmAlTD_2mm_Al_Scintillator.png");
   c1->SaveAs("distrib2D_muSciDF_5mmAlTD_2mm_Al_Scintillator.C");
*/

   /////////////////////////////////////////////////// SciDetFrontIn1-mu
   TCanvas *c11 = new TCanvas("c11", "c11",800,600);
   
   // Create the three pads
   TPad *PadC11 = new TPad("PadC11", "PadC11",0.0,0.0,0.5,0.45); PadC11->Draw();
   TPad *PadR11 = new TPad("PadR11", "PadR11",0.55,0.0,1.0,0.6); PadR11->Draw();
   TPad *PadT11 = new TPad("PadT11", "PadT11",0.0,0.55,0.6,1.0); PadT11->Draw();
   TPad *PadV11 = new TPad("PadV11", "PadV11",0.55,0.55,1.0,1.0); PadV11->Draw();

   TH1D * hmuSciDFIn1x = hmuSciDFIn1->ProjectionX();
   TH1D * hmuSciDFIn1y = hmuSciDFIn1->ProjectionY();

   // Drawing
   PadC11->cd();
   gStyle->SetPalette(1);
   //hmuSciDF->Draw("CONT1Z");
   //hmuSciDF->Draw("SURF3");
   hmuSciDFIn1->Draw("COLZ");
   PadT11->cd();
   hmuSciDFIn1x->SetFillColor(kBlue+1);
   hmuSciDFIn1x->SetTitle("X-projection");
   hmuSciDFIn1x->Draw("bar");
   PadR11->cd();
   hmuSciDFIn1y->SetFillColor(kBlue-2);
   hmuSciDFIn1y->SetTitle("Y-projection");
   hmuSciDFIn1y->Draw("hbar");
   PadV11->cd();
   hmuSciDFIn1z->SetTitle("Z");
   hmuSciDFIn1z->Draw();

   c11->cd();
   TLatex *t11 = new TLatex();
   t11->SetTextFont(42);
   t11->SetTextSize(0.02);
   t11->DrawLatex(0.11,0.52,"#mu-decay: SciDetFrontIn1 [smSDE, SDFInx2, 5mmAlBGO, 2-mm Al], 10^{5} generated events");
   t11->DrawLatex(0.11,0.49,"200-mm x 200-mm, 1-mm long");

   c11->SaveAs("distrib2D_muSciDFIn1_SDFInx2_5mmAlBGO_2mm_Al_Scintillator.pdf");
   c11->SaveAs("distrib2D_muSciDFIn1_SDFInx2_5mmAlBGO_2mm_Al_Scintillator.png");
   c11->SaveAs("distrib2D_muSciDFIn1_SDFInx2_5mmAlBGO_2mm_Al_Scintillator.C");


   /////////////////////////////////////////////////// SciDetFrontIn2-mu
   TCanvas *c12 = new TCanvas("c12", "c12",800,600);
   
   // Create the three pads
   TPad *PadC12 = new TPad("PadC12", "PadC12",0.0,0.0,0.5,0.45); PadC12->Draw();
   TPad *PadR12 = new TPad("PadR12", "PadR12",0.55,0.0,1.0,0.6); PadR12->Draw();
   TPad *PadT12 = new TPad("PadT12", "PadT12",0.0,0.55,0.6,1.0); PadT12->Draw();
   TPad *PadV12 = new TPad("PadV12", "PadV12",0.55,0.55,1.0,1.0); PadV12->Draw();

   TH1D * hmuSciDFIn2x = hmuSciDFIn2->ProjectionX();
   TH1D * hmuSciDFIn2y = hmuSciDFIn2->ProjectionY();

   // Drawing
   PadC12->cd();
   gStyle->SetPalette(1);
   hmuSciDFIn2->Draw("COLZ");
   PadT12->cd();
   hmuSciDFIn2x->SetFillColor(kBlue+1);
   hmuSciDFIn2x->SetTitle("X-projection");
   hmuSciDFIn2x->Draw("bar");
   PadR12->cd();
   hmuSciDFIn2y->SetFillColor(kBlue-2);
   hmuSciDFIn2y->SetTitle("Y-projection");
   hmuSciDFIn2y->Draw("hbar");
   PadV12->cd();
   hmuSciDFIn2z->SetTitle("Z");
   hmuSciDFIn2z->Draw();

   c12->cd();
   TLatex *t12 = new TLatex();
   t12->SetTextFont(42);
   t12->SetTextSize(0.02);
   t12->DrawLatex(0.11,0.52,"#mu-decay: SciDetFrontIn2 [smSDE, SDFInx2, 5mmAlBGO, 2-mm Al], 10^{5} generated events");
   t12->DrawLatex(0.11,0.49,"200-mm x 200-mm, 1-mm long");

   c12->SaveAs("distrib2D_muSciDFIn2_SDFInx2_5mmAlBGO_2mm_Al_Scintillator.pdf");
   c12->SaveAs("distrib2D_muSciDFIn2_SDFInx2_5mmAlBGO_2mm_Al_Scintillator.png");
   c12->SaveAs("distrib2D_muSciDFIn2_SDFInx2_5mmAlBGO_2mm_Al_Scintillator.C");


   ////////////////////////////////////////////////////////// TubeDet-mu
   TCanvas *c2 = new TCanvas("c2", "c2",800,600);
   
   // Create the three pads
   TPad *PadC2 = new TPad("PadC2", "PadC2",0.0,0.0,0.5,0.45); PadC2->Draw();
   TPad *PadR2 = new TPad("PadR2", "PadR2",0.55,0.0,1.0,0.6); PadR2->Draw();
   TPad *PadT2 = new TPad("PadT2", "PadT2",0.0,0.55,0.6,1.0); PadT2->Draw();
   TPad *PadV2 = new TPad("PadV2", "PadV2",0.55,0.55,1.0,1.0); PadV2->Draw();


   TH1D * hmuTubeDx = hmuTubeD->ProjectionX();
   TH1D * hmuTubeDy = hmuTubeD->ProjectionY();
 
   // Drawing
   PadC2->cd(); 
   gStyle->SetPalette(1); 
   hmuTubeD->Draw("COLZ");
   PadT2->cd(); 
   hmuTubeDx->SetFillColor(kBlue+1); 
   hmuTubeDx->SetTitle("X-projection"); 
   hmuTubeDx->Draw("bar");
   PadR2->cd();
   hmuTubeDy->SetFillColor(kBlue-2);
   hmuTubeDy->SetTitle("Y-projection");
   hmuTubeDy->Draw("hbar");
   PadV2->cd();
   hmuTubeDz->SetTitle("Z");
   hmuTubeDz->Draw();


   c2->cd();
   TLatex *t2 = new TLatex();
   t2->SetTextFont(42);
   t2->SetTextSize(0.02);
   t2->DrawLatex(0.11,0.52,"#mu-decay: TubeDet [smSDE, SDFInx2, 5mmAlBGO, 2-mm Al], 10^{5} generated events");
   t2->DrawLatex(0.11,0.49,"50-mm round, 300-mm long");

   c2->SaveAs("distrib2D_muTubeD_SDFInx2_5mmAlTD_2mm_Al_Scintillator.pdf");
   c2->SaveAs("distrib2D_muTubeD_SDFInx2_5mmAlTD_2mm_Al_Scintillator.png");
   c2->SaveAs("distrib2D_muTubeD_SDFInx2_5mmAlTD_2mm_Al_Scintillator.C");


   //////////////////////////////////////////////////////// SciDetEnd-mu
   TCanvas *c3 = new TCanvas("c3", "c3",800,600);
   
   TPad *PadC3 = new TPad("PadC3", "PadC3",0.0,0.0,0.5,0.45); PadC3->Draw();
   TPad *PadR3 = new TPad("PadR3", "PadR3",0.55,0.0,1.0,0.6); PadR3->Draw();
   TPad *PadT3 = new TPad("PadT3", "PadT3",0.0,0.55,0.6,1.0); PadT3->Draw();
   TPad *PadV3 = new TPad("PadV3", "PadV3",0.55,0.55,1.0,1.0); PadV3->Draw();
   
   TH1D * hmuSciDEx = hmuSciDE->ProjectionX();
   TH1D * hmuSciDEy = hmuSciDE->ProjectionY();
 
   // Drawing
   PadC3->cd(); 
   gStyle->SetPalette(1); 
   hmuSciDE->Draw("COLZ");
   PadT3->cd(); 
   hmuSciDEx->SetFillColor(kBlue+1); 
   hmuSciDEx->SetTitle("X-projection"); 
   hmuSciDEx->Draw("bar");
   PadR3->cd();
   hmuSciDEy->SetFillColor(kBlue-2);
   hmuSciDEy->SetTitle("Y-projection");
   hmuSciDEy->Draw("hbar");
   PadV3->cd();
   hmuSciDEz->SetTitle("Z");
   hmuSciDEz->Draw();

   c3->cd();
   TLatex *t3 = new TLatex();
   t3->SetTextFont(42);
   t3->SetTextSize(0.02);
   t3->DrawLatex(0.11,0.52,"#mu-decay: SciDetEnd [smSDE, SDFInx2, 5mmAlBGO, 2-mm Al], 10^{5} generated events");
   t3->DrawLatex(0.11,0.49,"100-mm x 100-mm, 200-mm long");

   c3->SaveAs("distrib2D_muSciDE_SDFInx2_5mmAlTD_2mm_Al_Scintillator.pdf");
   c3->SaveAs("distrib2D_muSciDE_SDFInx2_5mmAlTD_2mm_Al_Scintillator.png");
   c3->SaveAs("distrib2D_muSciDE_SDFInx2_5mmAlTD_2mm_Al_Scintillator.C");

/*
   /////////////////////////////////////////////////////// SciDetFront-X
   TCanvas *c4 = new TCanvas("c4", "c4",800,600);
   
   TPad *PadC4 = new TPad("PadC4", "PadC4",0.0,0.0,0.5,0.45); PadC4->Draw();
   TPad *PadR4 = new TPad("PadR4", "PadR4",0.55,0.0,1.0,0.6); PadR4->Draw();
   TPad *PadT4 = new TPad("PadT4", "PadT4",0.0,0.55,0.6,1.0); PadT4->Draw();
   TPad *PadV4 = new TPad("PadV4", "PadV4",0.55,0.55,1.0,1.0); PadV4->Draw();

   TH1D * hxSciDFx = hxSciDF->ProjectionX();
   TH1D * hxSciDFy = hxSciDF->ProjectionY();

   // Drawing
   PadC4->cd();
   gStyle->SetPalette(1);
   hxSciDF->Draw("COLZ");
   PadT4->cd();
   hxSciDFx->SetFillColor(kBlue+1);
   hxSciDFx->SetTitle("X-projection");
   hxSciDFx->Draw("bar");
   PadR4->cd();
   hxSciDFy->SetFillColor(kBlue-2);
   hxSciDFy->SetTitle("Y-projection");
   hxSciDFy->Draw("hbar");
   PadV4->cd();
   hxSciDFz->SetTitle("z");
   hxSciDFz->Draw();

   c4->cd();
   TLatex *t4 = new TLatex();
   t4->SetTextFont(42);
   t4->SetTextSize(0.02);
   t4->DrawLatex(0.11,0.52,"X-ray cascade: SciDetFront [smSDE, 5mmAlBGO, 2-mm Al], 10^{5} generated events");
   t4->DrawLatex(0.11,0.49,"200-mm x 200-mm, 4-mm long");

   c4->SaveAs("distrib2D_xSciDF_5mmAlTD_2mm_Al_Scintillator.pdf");
   c4->SaveAs("distrib2D_xSciDF_5mmAlTD_2mm_Al_Scintillator.png");
   c4->SaveAs("distrib2D_xSciDF_5mmAlTD_2mm_Al_Scintillator.C");
*/


   //////////////////////////////////////////////////// SciDetFrontIn1-X
   TCanvas *c41 = new TCanvas("c41", "c41",800,600);
   
   TPad *PadC41 = new TPad("PadC41", "PadC41",0.0,0.0,0.5,0.45); PadC41->Draw();
   TPad *PadR41 = new TPad("PadR41", "PadR41",0.55,0.0,1.0,0.6); PadR41->Draw();
   TPad *PadT41 = new TPad("PadT41", "PadT41",0.0,0.55,0.6,1.0); PadT41->Draw();
   TPad *PadV41 = new TPad("PadV41", "PadV41",0.55,0.55,1.0,1.0); PadV41->Draw();

   TH1D * hxSciDFIn1x = hxSciDFIn1->ProjectionX();
   TH1D * hxSciDFIn1y = hxSciDFIn1->ProjectionY();

   // Drawing
   PadC41->cd();
   gStyle->SetPalette(1);
   hxSciDFIn1->Draw("COLZ");
   PadT41->cd();
   hxSciDFIn1x->SetFillColor(kBlue+1);
   hxSciDFIn1x->SetTitle("X-projection");
   hxSciDFIn1x->Draw("bar");
   PadR41->cd();
   hxSciDFIn1y->SetFillColor(kBlue-2);
   hxSciDFIn1y->SetTitle("Y-projection");
   hxSciDFIn1y->Draw("hbar");
   PadV41->cd();
   hxSciDFIn1z->SetTitle("z");
   hxSciDFIn1z->Draw();

   c41->cd();
   TLatex *t41 = new TLatex();
   t41->SetTextFont(42);
   t41->SetTextSize(0.02);
   t41->DrawLatex(0.11,0.52,"X-ray cascade: SciDetFrontIn1 [smSDE, SDFInx2, 5mmAlBGO, 2-mm Al], 10^{5} generated events");
   t41->DrawLatex(0.11,0.49,"200-mm x 200-mm, 1-mm long");

   c41->SaveAs("distrib2D_xSciDFIn1_SDFInx2_5mmAlBGO_2mm_Al.pdf");
   c41->SaveAs("distrib2D_xSciDFIn1_SDFInx2_5mmAlBGO_2mm_Al.png");
   c41->SaveAs("distrib2D_xSciDFIn1_SDFInx2_5mmAlBGO_2mm_Al.C");


   //////////////////////////////////////////////////// SciDetFrontIn2-X
   TCanvas *c42 = new TCanvas("c42", "c42",800,600);
   
   TPad *PadC42 = new TPad("PadC42", "PadC42",0.0,0.0,0.5,0.45); PadC42->Draw();
   TPad *PadR42 = new TPad("PadR42", "PadR42",0.55,0.0,1.0,0.6); PadR42->Draw();
   TPad *PadT42 = new TPad("PadT42", "PadT42",0.0,0.55,0.6,1.0); PadT42->Draw();
   TPad *PadV42 = new TPad("PadV42", "PadV42",0.55,0.55,1.0,1.0); PadV42->Draw();

   TH1D * hxSciDFIn2x = hxSciDFIn2->ProjectionX();
   TH1D * hxSciDFIn2y = hxSciDFIn2->ProjectionY();

   // Drawing
   PadC42->cd();
   gStyle->SetPalette(1);
   hxSciDFIn2->Draw("COLZ");
   PadT42->cd();
   hxSciDFIn2x->SetFillColor(kBlue+1);
   hxSciDFIn2x->SetTitle("X-projection");
   hxSciDFIn2x->Draw("bar");
   PadR42->cd();
   hxSciDFIn2y->SetFillColor(kBlue-2);
   hxSciDFIn2y->SetTitle("Y-projection");
   hxSciDFIn2y->Draw("hbar");
   PadV42->cd();
   hxSciDFIn2z->SetTitle("z");
   hxSciDFIn2z->Draw();

   c42->cd();
   TLatex *t42 = new TLatex();
   t42->SetTextFont(42);
   t42->SetTextSize(0.02);
   t42->DrawLatex(0.11,0.52,"X-ray cascade: SciDetFrontIn2 [smSDE, SDFInx2, 5mmAlBGO, 2-mm Al], 10^{5} generated events");
   t42->DrawLatex(0.11,0.49,"200-mm x 200-mm, 1-mm long");

   c42->SaveAs("distrib2D_xSciDFIn2_SDFInx2_5mmAlBGO_2mm_Al.pdf");
   c42->SaveAs("distrib2D_xSciDFIn2_SDFInx2_5mmAlBGO_2mm_Al.png");
   c42->SaveAs("distrib2D_xSciDFIn2_SDFInx2_5mmAlBGO_2mm_Al.C");


   /////////////////////////////////////////////////////////// TubeDet-X
   TCanvas *c5 = new TCanvas("c5", "c5",800,600);
   
   // Create the three pads
   TPad *PadC5 = new TPad("PadC5", "PadC5",0.0,0.0,0.5,0.45); PadC5->Draw();
   TPad *PadR5 = new TPad("PadR5", "PadR5",0.55,0.0,1.0,0.6); PadR5->Draw();
   TPad *PadT5 = new TPad("PadT5", "PadT5",0.0,0.55,0.6,1.0); PadT5->Draw();
   TPad *PadV5 = new TPad("PadV5", "PadV5",0.55,0.55,1.0,1.0); PadV5->Draw();

   TH1D * hxTubeDx = hxTubeD->ProjectionX();
   TH1D * hxTubeDy = hxTubeD->ProjectionY();
 
   // Drawing
   PadC5->cd(); 
   gStyle->SetPalette(1); 
   hxTubeD->Draw("COLZ");
   PadT5->cd(); 
   hxTubeDx->SetFillColor(kBlue+1); 
   hxTubeDx->SetTitle("X-projection"); 
   hxTubeDx->Draw("bar");
   PadR5->cd();
   hxTubeDy->SetFillColor(kBlue-2);
   hxTubeDy->SetTitle("Y-projection");
   hxTubeDy->Draw("hbar");
   PadV5->cd();
   hxTubeDz->SetTitle("Z");
   hxTubeDz->Draw();

   c5->cd();
   TLatex *t5 = new TLatex();
   t5->SetTextFont(42);
   t5->SetTextSize(0.02);
   t5->DrawLatex(0.11,0.52,"X-ray cascade: TubeDet [smSDE, SDFInx2, 5mmAlBGO, 2-mm Al], 10^{5} generated events");
   t5->DrawLatex(0.11,0.49,"50-mm round, 300-mm long");

   c5->SaveAs("distrib2D_xTubeD_SDFInx2_5mmAlTD_2mm_Al_Scintillator.pdf");
   c5->SaveAs("distrib2D_xTubeD_SDFInx2_5mmAlTD_2mm_Al_Scintillator.png");
   c5->SaveAs("distrib2D_xTubeD_SDFInx2_5mmAlTD_2mm_Al_Scintillator.C");


   ///////////////////////////////////////////////////////// SciDetEnd-X
   TCanvas *c6 = new TCanvas("c6", "c6",800,600);
  
   TPad *PadC6 = new TPad("PadC6", "PadC6",0.0,0.0,0.5,0.45); PadC6->Draw();
   TPad *PadR6 = new TPad("PadR6", "PadR6",0.55,0.0,1.0,0.6); PadR6->Draw();
   TPad *PadT6 = new TPad("PadT6", "PadT6",0.0,0.55,0.6,1.0); PadT6->Draw();
   TPad *PadV6 = new TPad("PadV6", "PadV6",0.55,0.55,1.0,1.0); PadV6->Draw();
   
   TH1D * hxSciDEx = hxSciDE->ProjectionX();
   TH1D * hxSciDEy = hxSciDE->ProjectionY();
 
   // Drawing
   PadC6->cd(); 
   gStyle->SetPalette(1); 
   hxSciDE->Draw("COLZ");
   PadT6->cd(); 
   hxSciDEx->SetFillColor(kBlue+1); 
   hxSciDEx->SetTitle("X-projection"); 
   hxSciDEx->Draw("bar");
   PadR6->cd();
   hxSciDEy->SetFillColor(kBlue-2);
   hxSciDEy->SetTitle("Y-projection");
   hxSciDEy->Draw("hbar");
   PadV6->cd();
   hxSciDEz->SetTitle("Z");
   hxSciDEz->Draw();

   c6->cd();
   TLatex *t6 = new TLatex();
   t6->SetTextFont(42);
   t6->SetTextSize(0.02);
   t6->DrawLatex(0.11,0.52,"X-ray cascade: SciDetEnd [smSDE, SDFInx2, 5mmAlBGO, 2-mm Al], 10^{5} generated events");
   t6->DrawLatex(0.11,0.49,"100-mm x 100-mm, 200-mm long");

   c6->SaveAs("distrib2D_xSciDE_SDFInx2_5mmAlTD_2mm_Al_Scintillator.pdf");
   c6->SaveAs("distrib2D_xSciDE_SDFInx2_5mmAlTD_2mm_Al_Scintillator.png");
   c6->SaveAs("distrib2D_xSciDE_SDFInx2_5mmAlTD_2mm_Al_Scintillator.C");



}


int main() {
   distrib2D();
   return 0;
}  
