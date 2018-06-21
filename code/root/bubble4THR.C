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
//#include "TVector.h"

void bubble4THR(){

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
   // With {250,500,750}-mm SciD3 3-mm Al
   std::string filemu250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filemu500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filemu750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filex250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6goldcascade.root";
   std::string filex500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_3mm_Al_1e6goldcascade.root";
   std::string filex750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_3mm_Al_1e6goldcascade.root";
   // With {250,500,750}-mm SciD3 6-mm Al
   std::string file6Almu250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Almu500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Almu750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Alx250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_6mm_Al_1e6goldcascade.root";
   std::string file6Alx500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_6mm_Al_1e6goldcascade.root";
   std::string file6Alx750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_6mm_Al_1e6goldcascade.root";
   // With {250,500,750}-mm SciD3 0-mm Al
   std::string file0Almu250 = "../../simdata/bubble4/bubble_0x5mm_250mm_SciD_Nevts_SciSphere_0mm_Al_1e6mudecay.root";
   std::string file0Almu500 = "../../simdata/bubble4/bubble_0x5mm_500mm_SciD_Nevts_SciSphere_0mm_Al_1e6mudecay.root";
   std::string file0Almu750 = "../../simdata/bubble4/bubble_0x5mm_750mm_SciD_Nevts_SciSphere_0mm_Al_1e6mudecay.root";
   std::string file0Alx250 = "../../simdata/bubble4/bubble_0x5mm_250mm_SciD_Nevts_SciSphere_0mm_Al_1e6goldcascade.root";
   std::string file0Alx500 = "../../simdata/bubble4/bubble_0x5mm_500mm_SciD_Nevts_SciSphere_0mm_Al_1e6goldcascade.root";
   std::string file0Alx750 = "../../simdata/bubble4/bubble_0x5mm_750mm_SciD_Nevts_SciSphere_0mm_Al_1e6goldcascade.root";

   /*********************************/
   /*           Analysis            */
   /*********************************/

   const int nbins = 300;
  
   // TFiles
   // 3-mm Al 
   TFile* fmu250 = new TFile(TString(filemu250));
   TFile* fmu500 = new TFile(TString(filemu500));
   TFile* fmu750 = new TFile(TString(filemu750));
   TFile* fx250 = new TFile(TString(filex250));
   TFile* fx500 = new TFile(TString(filex500));
   TFile* fx750 = new TFile(TString(filex750));
   // 6-mm Al
   TFile* f6Almu250 = new TFile(TString(file6Almu250));
   TFile* f6Almu500 = new TFile(TString(file6Almu500));
   TFile* f6Almu750 = new TFile(TString(file6Almu750));
   TFile* f6Alx250 = new TFile(TString(file6Alx250));
   TFile* f6Alx500 = new TFile(TString(file6Alx500));
   TFile* f6Alx750 = new TFile(TString(file6Alx750));
   // 0-mm Al
   TFile* f0Almu250 = new TFile(TString(file0Almu250));
   TFile* f0Almu500 = new TFile(TString(file0Almu500));
   TFile* f0Almu750 = new TFile(TString(file0Almu750));
   TFile* f0Alx250 = new TFile(TString(file0Alx250));
   TFile* f0Alx500 = new TFile(TString(file0Alx500));
   TFile* f0Alx750 = new TFile(TString(file0Alx750));

   // Histograms
   // 3-mm Al
   TH1F *hmu250SciDet1 = new TH1F("hmu250SciDet1","Edep",3*nbins+1,-0.05,45);
   TH1F *hmu250SciDet2 = new TH1F("hmu250SciDet2","Edep",3*nbins+1,-0.05,45);
   TH1F *hmu250SciDet3 = new TH1F("hmu250SciDet3","Edep",3*nbins+1,-0.05,45); // Location #1
   TH1F *hmu500SciDet1 = new TH1F("hmu500SciDet1","Edep",3*nbins+1,-0.05,45);
   TH1F *hmu500SciDet2 = new TH1F("hmu500SciDet2","Edep",3*nbins+1,-0.05,45);
   TH1F *hmu500SciDet3 = new TH1F("hmu500SciDet3","Edep",3*nbins+1,-0.05,45);
   TH1F *hmu750SciDet1 = new TH1F("hmu750SciDet1","Edep",3*nbins+1,-0.05,45);
   TH1F *hmu750SciDet2 = new TH1F("hmu750SciDet2","Edep",3*nbins+1,-0.05,45);
   TH1F *hmu750SciDet3 = new TH1F("hmu750SciDet3","Edep",3*nbins+1,-0.05,45);
   TH1F *hx250SciDet1 = new TH1F("hx250SciDet1","Edep",nbins+1,-0.05,15);
   TH1F *hx250SciDet2 = new TH1F("hx250SciDet2","Edep",nbins+1,-0.05,15);
   TH1F *hx250SciDet3 = new TH1F("hx250SciDet3","Edep",nbins+1,-0.05,15);
   TH1F *hx500SciDet1 = new TH1F("hx500SciDet1","Edep",nbins+1,-0.05,15);
   TH1F *hx500SciDet2 = new TH1F("hx500SciDet2","Edep",nbins+1,-0.05,15);
   TH1F *hx500SciDet3 = new TH1F("hx500SciDet3","Edep",nbins+1,-0.05,15);
   TH1F *hx750SciDet1 = new TH1F("hx750SciDet1","Edep",nbins+1,-0.05,15);
   TH1F *hx750SciDet2 = new TH1F("hx750SciDet2","Edep",nbins+1,-0.05,15);
   TH1F *hx750SciDet3 = new TH1F("hx750SciDet3","Edep",nbins+1,-0.05,15);
  
   // 6-mm Al
   TH1F *h6Almu250SciDet1 = new TH1F("h6Almu250SciDet1","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Almu250SciDet2 = new TH1F("h6Almu250SciDet2","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Almu250SciDet3 = new TH1F("h6Almu250SciDet3","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Almu500SciDet1 = new TH1F("h6Almu500SciDet1","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Almu500SciDet2 = new TH1F("h6Almu500SciDet2","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Almu500SciDet3 = new TH1F("h6Almu500SciDet3","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Almu750SciDet1 = new TH1F("h6Almu750SciDet1","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Almu750SciDet2 = new TH1F("h6Almu750SciDet2","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Almu750SciDet3 = new TH1F("h6Almu750SciDet3","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Alx250SciDet1 = new TH1F("h6Alx250SciDet1","Edep",nbins+1,-0.05,15);
   TH1F *h6Alx250SciDet2 = new TH1F("h6Alx250SciDet2","Edep",nbins+1,-0.05,15);
   TH1F *h6Alx250SciDet3 = new TH1F("h6Alx250SciDet3","Edep",nbins+1,-0.05,15);
   TH1F *h6Alx500SciDet1 = new TH1F("h6Alx500SciDet1","Edep",nbins+1,-0.05,15);
   TH1F *h6Alx500SciDet2 = new TH1F("h6Alx500SciDet2","Edep",nbins+1,-0.05,15);
   TH1F *h6Alx500SciDet3 = new TH1F("h6Alx500SciDet3","Edep",nbins+1,-0.05,15);
   TH1F *h6Alx750SciDet1 = new TH1F("h6Alx750SciDet1","Edep",nbins+1,-0.05,15);
   TH1F *h6Alx750SciDet2 = new TH1F("h6Alx750SciDet2","Edep",nbins+1,-0.05,15);
   TH1F *h6Alx750SciDet3 = new TH1F("h6Alx750SciDet3","Edep",nbins+1,-0.05,15);
   
   // 0-mm Al
   TH1F *h0Almu250SciDet3 = new TH1F("h0Almu250SciDet3","Edep",3*nbins+1,-0.05,45);
   TH1F *h0Almu500SciDet3 = new TH1F("h0Almu500SciDet3","Edep",3*nbins+1,-0.05,45);
   TH1F *h0Almu750SciDet3 = new TH1F("h0Almu750SciDet3","Edep",3*nbins+1,-0.05,45);
   TH1F *h0Alx250SciDet3 = new TH1F("h0Alx250SciDet3","Edep",nbins+1,-0.05,15);
   TH1F *h0Alx500SciDet3 = new TH1F("h0Alx500SciDet3","Edep",nbins+1,-0.05,15);
   TH1F *h0Alx750SciDet3 = new TH1F("h0Alx750SciDet3","Edep",nbins+1,-0.05,15);
  
     
   // TTrees
   // 3-mm Al
   TTree *tmu250SciDet1 = (TTree*)fmu250->Get("Detector/SciDet1");
   TTree *tmu250SciDet2 = (TTree*)fmu250->Get("Detector/SciDet2");
   TTree *tmu250SciDet3 = (TTree*)fmu250->Get("Detector/SciDet3");
   TTree *tmu500SciDet1 = (TTree*)fmu500->Get("Detector/SciDet1");
   TTree *tmu500SciDet2 = (TTree*)fmu500->Get("Detector/SciDet2");
   TTree *tmu500SciDet3 = (TTree*)fmu500->Get("Detector/SciDet3");
   TTree *tmu750SciDet1 = (TTree*)fmu750->Get("Detector/SciDet1");
   TTree *tmu750SciDet2 = (TTree*)fmu750->Get("Detector/SciDet2");
   TTree *tmu750SciDet3 = (TTree*)fmu750->Get("Detector/SciDet3");
   TTree *tx250SciDet1 = (TTree*)fx250->Get("Detector/SciDet1");
   TTree *tx250SciDet2 = (TTree*)fx250->Get("Detector/SciDet2");
   TTree *tx250SciDet3 = (TTree*)fx250->Get("Detector/SciDet3");
   TTree *tx500SciDet1 = (TTree*)fx500->Get("Detector/SciDet1");
   TTree *tx500SciDet2 = (TTree*)fx500->Get("Detector/SciDet2");
   TTree *tx500SciDet3 = (TTree*)fx500->Get("Detector/SciDet3");
   TTree *tx750SciDet1 = (TTree*)fx750->Get("Detector/SciDet1");
   TTree *tx750SciDet2 = (TTree*)fx750->Get("Detector/SciDet2");
   TTree *tx750SciDet3 = (TTree*)fx750->Get("Detector/SciDet3");
   // 6-mm Al
   TTree *t6Almu250SciDet1 = (TTree*)f6Almu250->Get("Detector/SciDet1");
   TTree *t6Almu250SciDet2 = (TTree*)f6Almu250->Get("Detector/SciDet2");
   TTree *t6Almu250SciDet3 = (TTree*)f6Almu250->Get("Detector/SciDet3");
   TTree *t6Almu500SciDet1 = (TTree*)f6Almu500->Get("Detector/SciDet1");
   TTree *t6Almu500SciDet2 = (TTree*)f6Almu500->Get("Detector/SciDet2");
   TTree *t6Almu500SciDet3 = (TTree*)f6Almu500->Get("Detector/SciDet3");
   TTree *t6Almu750SciDet1 = (TTree*)f6Almu750->Get("Detector/SciDet1");
   TTree *t6Almu750SciDet2 = (TTree*)f6Almu750->Get("Detector/SciDet2");
   TTree *t6Almu750SciDet3 = (TTree*)f6Almu750->Get("Detector/SciDet3");
   TTree *t6Alx250SciDet1 = (TTree*)f6Alx250->Get("Detector/SciDet1");
   TTree *t6Alx250SciDet2 = (TTree*)f6Alx250->Get("Detector/SciDet2");
   TTree *t6Alx250SciDet3 = (TTree*)f6Alx250->Get("Detector/SciDet3");
   TTree *t6Alx500SciDet1 = (TTree*)f6Alx500->Get("Detector/SciDet1");
   TTree *t6Alx500SciDet2 = (TTree*)f6Alx500->Get("Detector/SciDet2");
   TTree *t6Alx500SciDet3 = (TTree*)f6Alx500->Get("Detector/SciDet3");
   TTree *t6Alx750SciDet1 = (TTree*)f6Alx750->Get("Detector/SciDet1");
   TTree *t6Alx750SciDet2 = (TTree*)f6Alx750->Get("Detector/SciDet2");
   TTree *t6Alx750SciDet3 = (TTree*)f6Alx750->Get("Detector/SciDet3");
   // 0-mm Al
   TTree *t0Almu250SciDet3 = (TTree*)f0Almu250->Get("Detector/SciDet3");
   TTree *t0Almu500SciDet3 = (TTree*)f0Almu500->Get("Detector/SciDet3");
   TTree *t0Almu750SciDet3 = (TTree*)f0Almu750->Get("Detector/SciDet3");
   TTree *t0Alx250SciDet3 = (TTree*)f0Alx250->Get("Detector/SciDet3");
   TTree *t0Alx500SciDet3 = (TTree*)f0Alx500->Get("Detector/SciDet3");
   TTree *t0Alx750SciDet3 = (TTree*)f0Alx750->Get("Detector/SciDet3");
   
   
   // Drawings
   // 3-mm Al  
   tmu250SciDet1->Draw("Edep>>hmu250SciDet1","","");
   tmu250SciDet2->Draw("Edep>>hmu250SciDet2","","");
   tmu250SciDet3->Draw("Edep>>hmu250SciDet3","","");
   tmu500SciDet1->Draw("Edep>>hmu500SciDet1","","");
   tmu500SciDet2->Draw("Edep>>hmu500SciDet2","","");
   tmu500SciDet3->Draw("Edep>>hmu500SciDet3","","");
   tmu750SciDet1->Draw("Edep>>hmu750SciDet1","","");
   tmu750SciDet2->Draw("Edep>>hmu750SciDet2","","");
   tmu750SciDet3->Draw("Edep>>hmu750SciDet3","","");
   tx250SciDet1->Draw("Edep>>hx250SciDet1","","");
   tx250SciDet2->Draw("Edep>>hx250SciDet2","","");
   tx250SciDet3->Draw("Edep>>hx250SciDet3","","");
   tx500SciDet1->Draw("Edep>>hx500SciDet1","","");
   tx500SciDet2->Draw("Edep>>hx500SciDet2","","");
   tx500SciDet3->Draw("Edep>>hx500SciDet3","","");
   tx750SciDet1->Draw("Edep>>hx750SciDet1","","");
   tx750SciDet2->Draw("Edep>>hx750SciDet2","","");
   tx750SciDet3->Draw("Edep>>hx750SciDet3","","");
   // 6-mm Al  
   t6Almu250SciDet1->Draw("Edep>>h6Almu250SciDet1","","");
   t6Almu250SciDet2->Draw("Edep>>h6Almu250SciDet2","","");
   t6Almu250SciDet3->Draw("Edep>>h6Almu250SciDet3","","");
   t6Almu500SciDet1->Draw("Edep>>h6Almu500SciDet1","","");
   t6Almu500SciDet2->Draw("Edep>>h6Almu500SciDet2","","");
   t6Almu500SciDet3->Draw("Edep>>h6Almu500SciDet3","","");
   t6Almu750SciDet1->Draw("Edep>>h6Almu750SciDet1","","");
   t6Almu750SciDet2->Draw("Edep>>h6Almu750SciDet2","","");
   t6Almu750SciDet3->Draw("Edep>>h6Almu750SciDet3","","");
   t6Alx250SciDet1->Draw("Edep>>h6Alx250SciDet1","","");
   t6Alx250SciDet2->Draw("Edep>>h6Alx250SciDet2","","");
   t6Alx250SciDet3->Draw("Edep>>h6Alx250SciDet3","","");
   t6Alx500SciDet1->Draw("Edep>>h6Alx500SciDet1","","");
   t6Alx500SciDet2->Draw("Edep>>h6Alx500SciDet2","","");
   t6Alx500SciDet3->Draw("Edep>>h6Alx500SciDet3","","");
   t6Alx750SciDet1->Draw("Edep>>h6Alx750SciDet1","","");
   t6Alx750SciDet2->Draw("Edep>>h6Alx750SciDet2","","");
   t6Alx750SciDet3->Draw("Edep>>h6Alx750SciDet3","","");
   // 0-mm Al  
   t0Almu250SciDet3->Draw("Edep>>h0Almu250SciDet3","","");
   t0Almu500SciDet3->Draw("Edep>>h0Almu500SciDet3","","");
   t0Almu750SciDet3->Draw("Edep>>h0Almu750SciDet3","","");
   t0Alx250SciDet3->Draw("Edep>>h0Alx250SciDet3","","");
   t0Alx500SciDet3->Draw("Edep>>h0Alx500SciDet3","","");
   t0Alx750SciDet3->Draw("Edep>>h0Alx750SciDet3","","");
  
  
   // Colours 
   // 3-mm Al
   hmu250SciDet1->SetLineColor(kBlack);
   hmu250SciDet2->SetLineColor(kBlack);
   hmu250SciDet3->SetLineColor(kBlack);
   hmu500SciDet1->SetLineColor(kBlack);
   hmu500SciDet2->SetLineColor(kBlack);
   hmu500SciDet3->SetLineColor(kBlack);
   hmu750SciDet1->SetLineColor(kBlack);
   hmu750SciDet2->SetLineColor(kBlack);
   hmu750SciDet3->SetLineColor(kBlack);
   hx250SciDet1->SetLineColor(kGreen-2);
   hx250SciDet2->SetLineColor(kGreen-2);
   hx250SciDet3->SetLineColor(kGreen-2);
   hx500SciDet1->SetLineColor(kGreen-2);
   hx500SciDet2->SetLineColor(kGreen-2);
   hx500SciDet3->SetLineColor(kGreen-2);
   hx750SciDet1->SetLineColor(kGreen-2);
   hx750SciDet2->SetLineColor(kGreen-2);
   hx750SciDet3->SetLineColor(kGreen-2);
  
   // 6-mm Al
   h6Almu250SciDet1->SetLineColor(kBlack);
   h6Almu250SciDet2->SetLineColor(kBlack);
   h6Almu250SciDet3->SetLineColor(kBlack);
   h6Almu500SciDet1->SetLineColor(kBlack);
   h6Almu500SciDet2->SetLineColor(kBlack);
   h6Almu500SciDet3->SetLineColor(kBlack);
   h6Almu750SciDet1->SetLineColor(kBlack);
   h6Almu750SciDet2->SetLineColor(kBlack);
   h6Almu750SciDet3->SetLineColor(kBlack);
   h6Alx250SciDet1->SetLineColor(kGreen-2);
   h6Alx250SciDet2->SetLineColor(kGreen-2);
   h6Alx250SciDet3->SetLineColor(kGreen-2);
   h6Alx500SciDet1->SetLineColor(kGreen-2);
   h6Alx500SciDet2->SetLineColor(kGreen-2);
   h6Alx500SciDet3->SetLineColor(kGreen-2);
   h6Alx750SciDet1->SetLineColor(kGreen-2);
   h6Alx750SciDet2->SetLineColor(kGreen-2);
   h6Alx750SciDet3->SetLineColor(kGreen-2);
   
   // 0-mm Al
   h6Almu250SciDet3->SetLineColor(kBlack);
   h6Almu500SciDet3->SetLineColor(kBlack);
   h6Almu750SciDet3->SetLineColor(kBlack);
   h6Alx250SciDet3->SetLineColor(kGreen-2);
   h6Alx500SciDet3->SetLineColor(kGreen-2);
   h6Alx750SciDet3->SetLineColor(kGreen-2);
  
   
   float binCentersmu250SciDet1[nbins] = {}; // 3-mm Al
   float binCentersmu250SciDet2[nbins] = {};
   float binCentersmu250SciDet3[nbins] = {};
   float binCentersmu500SciDet1[nbins] = {};
   float binCentersmu500SciDet2[nbins] = {};
   float binCentersmu500SciDet3[nbins] = {};
   float binCentersmu750SciDet1[nbins] = {};
   float binCentersmu750SciDet2[nbins] = {};
   float binCentersmu750SciDet3[nbins] = {};
   float binCentersx250SciDet1[nbins] = {};
   float binCentersx250SciDet2[nbins] = {};
   float binCentersx250SciDet3[nbins] = {};
   float binCentersx500SciDet1[nbins] = {};
   float binCentersx500SciDet2[nbins] = {};
   float binCentersx500SciDet3[nbins] = {};
   float binCentersx750SciDet1[nbins] = {};
   float binCentersx750SciDet2[nbins] = {};
   float binCentersx750SciDet3[nbins] = {};
   float binCenters6Almu250SciDet1[nbins] = {}; // 6-mm Al
   float binCenters6Almu250SciDet2[nbins] = {};
   float binCenters6Almu250SciDet3[nbins] = {};
   float binCenters6Almu500SciDet1[nbins] = {};
   float binCenters6Almu500SciDet2[nbins] = {};
   float binCenters6Almu500SciDet3[nbins] = {};
   float binCenters6Almu750SciDet1[nbins] = {};
   float binCenters6Almu750SciDet2[nbins] = {};
   float binCenters6Almu750SciDet3[nbins] = {};
   float binCenters6Alx250SciDet1[nbins] = {};
   float binCenters6Alx250SciDet2[nbins] = {};
   float binCenters6Alx250SciDet3[nbins] = {};
   float binCenters6Alx500SciDet1[nbins] = {};
   float binCenters6Alx500SciDet2[nbins] = {};
   float binCenters6Alx500SciDet3[nbins] = {};
   float binCenters6Alx750SciDet1[nbins] = {};
   float binCenters6Alx750SciDet2[nbins] = {};
   float binCenters6Alx750SciDet3[nbins] = {};
   float binCenters0Almu250SciDet3[nbins] = {}; // 0-mm Al
   float binCenters0Almu500SciDet3[nbins] = {};
   float binCenters0Almu750SciDet3[nbins] = {};
   float binCenters0Alx250SciDet3[nbins] = {};
   float binCenters0Alx500SciDet3[nbins] = {};
   float binCenters0Alx750SciDet3[nbins] = {};
   
   float integralsmu250SciDet1[nbins] = {}; // 3-mm Al
   float integralsmu250SciDet2[nbins] = {};
   float integralsmu250SciDet3[nbins] = {};
   float integralsmu500SciDet1[nbins] = {};
   float integralsmu500SciDet2[nbins] = {};
   float integralsmu500SciDet3[nbins] = {};
   float integralsmu750SciDet1[nbins] = {};
   float integralsmu750SciDet2[nbins] = {};
   float integralsmu750SciDet3[nbins] = {};
   float integralsx250SciDet1[nbins] = {};
   float integralsx250SciDet2[nbins] = {};
   float integralsx250SciDet3[nbins] = {};
   float integralsx500SciDet1[nbins] = {};
   float integralsx500SciDet2[nbins] = {};
   float integralsx500SciDet3[nbins] = {};
   float integralsx750SciDet1[nbins] = {};
   float integralsx750SciDet2[nbins] = {};
   float integralsx750SciDet3[nbins] = {};
   float integrals6Almu250SciDet1[nbins] = {}; // 6-mm Al
   float integrals6Almu250SciDet2[nbins] = {};
   float integrals6Almu250SciDet3[nbins] = {};
   float integrals6Almu500SciDet1[nbins] = {};
   float integrals6Almu500SciDet2[nbins] = {};
   float integrals6Almu500SciDet3[nbins] = {};
   float integrals6Almu750SciDet1[nbins] = {};
   float integrals6Almu750SciDet2[nbins] = {};
   float integrals6Almu750SciDet3[nbins] = {};
   float integrals6Alx250SciDet1[nbins] = {};
   float integrals6Alx250SciDet2[nbins] = {};
   float integrals6Alx250SciDet3[nbins] = {};
   float integrals6Alx500SciDet1[nbins] = {};
   float integrals6Alx500SciDet2[nbins] = {};
   float integrals6Alx500SciDet3[nbins] = {};
   float integrals6Alx750SciDet1[nbins] = {};
   float integrals6Alx750SciDet2[nbins] = {};
   float integrals6Alx750SciDet3[nbins] = {};
   float integrals0Almu250SciDet3[nbins] = {}; // 0-mm Al
   float integrals0Almu500SciDet3[nbins] = {};
   float integrals0Almu750SciDet3[nbins] = {};
   float integrals0Alx250SciDet3[nbins] = {};
   float integrals0Alx500SciDet3[nbins] = {};
   float integrals0Alx750SciDet3[nbins] = {};

   float binCentermu250SciDet1, binCentermu250SciDet2, binCentermu250SciDet3; // 3-mm Al
   float binCentermu500SciDet1, binCentermu500SciDet2, binCentermu500SciDet3;
   float binCentermu750SciDet1, binCentermu750SciDet2, binCentermu750SciDet3;
   float binCenterx250SciDet1, binCenterx250SciDet2, binCenterx250SciDet3;
   float binCenterx500SciDet1, binCenterx500SciDet2, binCenterx500SciDet3;
   float binCenterx750SciDet1, binCenterx750SciDet2, binCenterx750SciDet3;
   float integralmu250SciDet1, integralmu250SciDet2, integralmu250SciDet3;
   float integralmu500SciDet1, integralmu500SciDet2, integralmu500SciDet3;
   float integralmu750SciDet1, integralmu750SciDet2, integralmu750SciDet3;
   float integralx250SciDet1, integralx250SciDet2, integralx250SciDet3;
   float integralx500SciDet1, integralx500SciDet2, integralx500SciDet3;
   float integralx750SciDet1, integralx750SciDet2, integralx750SciDet3;
   float binCenter6Almu250SciDet1, binCenter6Almu250SciDet2, binCenter6Almu250SciDet3; // 6-mm Al
   float binCenter6Almu500SciDet1, binCenter6Almu500SciDet2, binCenter6Almu500SciDet3;
   float binCenter6Almu750SciDet1, binCenter6Almu750SciDet2, binCenter6Almu750SciDet3;
   float binCenter6Alx250SciDet1, binCenter6Alx250SciDet2, binCenter6Alx250SciDet3;
   float binCenter6Alx500SciDet1, binCenter6Alx500SciDet2, binCenter6Alx500SciDet3;
   float binCenter6Alx750SciDet1, binCenter6Alx750SciDet2, binCenter6Alx750SciDet3;
   float integral6Almu250SciDet1, integral6Almu250SciDet2, integral6Almu250SciDet3;
   float integral6Almu500SciDet1, integral6Almu500SciDet2, integral6Almu500SciDet3;
   float integral6Almu750SciDet1, integral6Almu750SciDet2, integral6Almu750SciDet3;
   float integral6Alx250SciDet1, integral6Alx250SciDet2, integral6Alx250SciDet3;
   float integral6Alx500SciDet1, integral6Alx500SciDet2, integral6Alx500SciDet3;
   float integral6Alx750SciDet1, integral6Alx750SciDet2, integral6Alx750SciDet3;
   float binCenter0Almu250SciDet3, binCenter0Almu500SciDet3, binCenter0Almu750SciDet3; // 0-mm Al
   float binCenter0Alx250SciDet3, binCenter0Alx500SciDet3, binCenter0Alx750SciDet3;
   float integral0Almu250SciDet3, integral0Almu500SciDet3, integral0Almu750SciDet3;
   float integral0Alx250SciDet3, integral0Alx500SciDet3, integral0Alx750SciDet3;
   
   // Filling the arrays
   for (int i=1; i<=nbins; i++) {   // Location #2
	   // LS: BinCentermu250SciDet1 is not the center but the lower edge of the (i+1)th bin
	   binCentermu250SciDet1 = hmu250SciDet1->GetXaxis()->GetBinLowEdge(i+1); // 3-mm Al
	   binCentermu250SciDet2 = hmu250SciDet2->GetXaxis()->GetBinLowEdge(i+1);
	   binCentermu250SciDet3 = hmu250SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCentermu500SciDet1 = hmu500SciDet1->GetXaxis()->GetBinLowEdge(i+1);
	   binCentermu500SciDet2 = hmu500SciDet2->GetXaxis()->GetBinLowEdge(i+1);
	   binCentermu500SciDet3 = hmu500SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCentermu750SciDet1 = hmu750SciDet1->GetXaxis()->GetBinLowEdge(i+1);
	   binCentermu750SciDet2 = hmu750SciDet2->GetXaxis()->GetBinLowEdge(i+1);
	   binCentermu750SciDet3 = hmu750SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx250SciDet1 = hx250SciDet1->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx250SciDet2 = hx250SciDet2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx250SciDet3 = hx250SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx500SciDet1 = hx500SciDet1->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx500SciDet2 = hx500SciDet2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx500SciDet3 = hx500SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx750SciDet1 = hx750SciDet1->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx750SciDet2 = hx750SciDet2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx750SciDet3 = hx750SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Almu250SciDet1 = h6Almu250SciDet1->GetXaxis()->GetBinLowEdge(i+1); // 6-mm Al
	   binCenter6Almu250SciDet2 = h6Almu250SciDet2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Almu250SciDet3 = h6Almu250SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Almu500SciDet1 = h6Almu500SciDet1->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Almu500SciDet2 = h6Almu500SciDet2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Almu500SciDet3 = h6Almu500SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Almu750SciDet1 = h6Almu750SciDet1->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Almu750SciDet2 = h6Almu750SciDet2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Almu750SciDet3 = h6Almu750SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx250SciDet1 = h6Alx250SciDet1->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx250SciDet2 = h6Alx250SciDet2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx250SciDet3 = h6Alx250SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx500SciDet1 = h6Alx500SciDet1->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx500SciDet2 = h6Alx500SciDet2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx500SciDet3 = h6Alx500SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx750SciDet1 = h6Alx750SciDet1->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx750SciDet2 = h6Alx750SciDet2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx750SciDet3 = h6Alx750SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter0Almu250SciDet3 = h0Almu250SciDet3->GetXaxis()->GetBinLowEdge(i+1); // 0-mm Al
	   binCenter0Almu500SciDet3 = h0Almu500SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter0Almu750SciDet3 = h0Almu750SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter0Alx250SciDet3 = h0Alx250SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter0Alx500SciDet3 = h0Alx500SciDet3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter0Alx750SciDet3 = h0Alx750SciDet3->GetXaxis()->GetBinLowEdge(i+1);

       integralmu250SciDet1 = hmu250SciDet1->Integral(0,i,""); // 3-mm Al; includes underflow and overflow bins
       integralmu250SciDet2 = hmu250SciDet2->Integral(0,i,"");
       integralmu250SciDet3 = hmu250SciDet3->Integral(0,i,"");
       integralmu500SciDet1 = hmu500SciDet1->Integral(0,i,"");
       integralmu500SciDet2 = hmu500SciDet2->Integral(0,i,"");
       integralmu500SciDet3 = hmu500SciDet3->Integral(0,i,"");
       integralmu750SciDet1 = hmu750SciDet1->Integral(0,i,""); 
       integralmu750SciDet2 = hmu750SciDet2->Integral(0,i,"");
       integralmu750SciDet3 = hmu750SciDet3->Integral(0,i,"");
       integralx250SciDet1 = (hx250SciDet1->Integral(0,nbins+1,""))-(hx250SciDet1->Integral(0,i,""));
       integralx250SciDet2 = (hx250SciDet2->Integral(0,nbins+1,""))-(hx250SciDet2->Integral(0,i,""));
       integralx250SciDet3 = (hx250SciDet3->Integral(0,nbins+1,""))-(hx250SciDet3->Integral(0,i,""));
       integralx500SciDet1 = (hx500SciDet1->Integral(0,nbins+1,""))-(hx500SciDet1->Integral(0,i,""));
       integralx500SciDet2 = (hx500SciDet2->Integral(0,nbins+1,""))-(hx500SciDet2->Integral(0,i,""));
       integralx500SciDet3 = (hx500SciDet3->Integral(0,nbins+1,""))-(hx500SciDet3->Integral(0,i,""));
       integralx750SciDet1 = (hx750SciDet1->Integral(0,nbins+1,""))-(hx750SciDet1->Integral(0,i,""));
       integralx750SciDet2 = (hx750SciDet2->Integral(0,nbins+1,""))-(hx750SciDet2->Integral(0,i,""));
       integralx750SciDet3 = (hx750SciDet3->Integral(0,nbins+1,""))-(hx750SciDet3->Integral(0,i,""));
       integral6Almu250SciDet1 = h6Almu250SciDet1->Integral(0,i,""); // 6-mm Al
       integral6Almu250SciDet2 = h6Almu250SciDet2->Integral(0,i,"");
       integral6Almu250SciDet3 = h6Almu250SciDet3->Integral(0,i,"");
       integral6Almu500SciDet1 = h6Almu500SciDet1->Integral(0,i,"");
       integral6Almu500SciDet2 = h6Almu500SciDet2->Integral(0,i,"");
       integral6Almu500SciDet3 = h6Almu500SciDet3->Integral(0,i,"");
       integral6Almu750SciDet1 = h6Almu750SciDet1->Integral(0,i,""); 
       integral6Almu750SciDet2 = h6Almu750SciDet2->Integral(0,i,"");
       integral6Almu750SciDet3 = h6Almu750SciDet3->Integral(0,i,"");
       integral6Alx250SciDet1 = (h6Alx250SciDet1->Integral(0,nbins+1,""))-(h6Alx250SciDet1->Integral(0,i,""));
       integral6Alx250SciDet2 = (h6Alx250SciDet2->Integral(0,nbins+1,""))-(h6Alx250SciDet2->Integral(0,i,""));
       integral6Alx250SciDet3 = (h6Alx250SciDet3->Integral(0,nbins+1,""))-(h6Alx250SciDet3->Integral(0,i,""));
       integral6Alx500SciDet1 = (h6Alx500SciDet1->Integral(0,nbins+1,""))-(h6Alx500SciDet1->Integral(0,i,""));
       integral6Alx500SciDet2 = (h6Alx500SciDet2->Integral(0,nbins+1,""))-(h6Alx500SciDet2->Integral(0,i,""));
       integral6Alx500SciDet3 = (h6Alx500SciDet3->Integral(0,nbins+1,""))-(h6Alx500SciDet3->Integral(0,i,""));
       integral6Alx750SciDet1 = (h6Alx750SciDet1->Integral(0,nbins+1,""))-(h6Alx750SciDet1->Integral(0,i,""));
       integral6Alx750SciDet2 = (h6Alx750SciDet2->Integral(0,nbins+1,""))-(h6Alx750SciDet2->Integral(0,i,""));
       integral6Alx750SciDet3 = (h6Alx750SciDet3->Integral(0,nbins+1,""))-(h6Alx750SciDet3->Integral(0,i,""));
       integral0Almu250SciDet3 = h0Almu250SciDet3->Integral(0,i,""); // 0-mm Al
       integral0Almu500SciDet3 = h0Almu500SciDet3->Integral(0,i,"");
       integral0Almu750SciDet3 = h0Almu750SciDet3->Integral(0,i,"");
       integral0Alx250SciDet3 = (h0Alx250SciDet3->Integral(0,nbins+1,""))-(h0Alx250SciDet3->Integral(0,i,""));
       integral0Alx500SciDet3 = (h0Alx500SciDet3->Integral(0,nbins+1,""))-(h0Alx500SciDet3->Integral(0,i,""));
       integral0Alx750SciDet3 = (h0Alx750SciDet3->Integral(0,nbins+1,""))-(h0Alx750SciDet3->Integral(0,i,""));
      
      
	   binCentersmu250SciDet1[(const int)(i-1)] = binCentermu250SciDet1; // 3-mm Al
	   binCentersmu250SciDet2[(const int)(i-1)] = binCentermu250SciDet2;
	   binCentersmu250SciDet3[(const int)(i-1)] = binCentermu250SciDet3;
	   binCentersmu500SciDet1[(const int)(i-1)] = binCentermu500SciDet1;
	   binCentersmu500SciDet2[(const int)(i-1)] = binCentermu500SciDet2;
	   binCentersmu500SciDet3[(const int)(i-1)] = binCentermu500SciDet3;
	   binCentersmu750SciDet1[(const int)(i-1)] = binCentermu750SciDet1;
	   binCentersmu750SciDet2[(const int)(i-1)] = binCentermu750SciDet2;
	   binCentersmu750SciDet3[(const int)(i-1)] = binCentermu750SciDet3;
	   binCentersx250SciDet1[(const int)(i-1)] = binCenterx250SciDet1;
	   binCentersx250SciDet2[(const int)(i-1)] = binCenterx250SciDet2;
	   binCentersx250SciDet3[(const int)(i-1)] = binCenterx250SciDet3;
	   binCentersx500SciDet1[(const int)(i-1)] = binCenterx500SciDet1;
	   binCentersx500SciDet2[(const int)(i-1)] = binCenterx500SciDet2;
	   binCentersx500SciDet3[(const int)(i-1)] = binCenterx500SciDet3;
	   binCentersx750SciDet1[(const int)(i-1)] = binCenterx750SciDet1;
	   binCentersx750SciDet2[(const int)(i-1)] = binCenterx750SciDet2;
	   binCentersx750SciDet3[(const int)(i-1)] = binCenterx750SciDet3;
	   binCenters6Almu250SciDet1[(const int)(i-1)] = binCenter6Almu250SciDet1; // 6-mm Al
	   binCenters6Almu250SciDet2[(const int)(i-1)] = binCenter6Almu250SciDet2;
	   binCenters6Almu250SciDet3[(const int)(i-1)] = binCenter6Almu250SciDet3;
	   binCenters6Almu500SciDet1[(const int)(i-1)] = binCenter6Almu500SciDet1;
	   binCenters6Almu500SciDet2[(const int)(i-1)] = binCenter6Almu500SciDet2;
	   binCenters6Almu500SciDet3[(const int)(i-1)] = binCenter6Almu500SciDet3;
	   binCenters6Almu750SciDet1[(const int)(i-1)] = binCenter6Almu750SciDet1;
	   binCenters6Almu750SciDet2[(const int)(i-1)] = binCenter6Almu750SciDet2;
	   binCenters6Almu750SciDet3[(const int)(i-1)] = binCenter6Almu750SciDet3;
	   binCenters6Alx250SciDet1[(const int)(i-1)] = binCenter6Alx250SciDet1;
	   binCenters6Alx250SciDet2[(const int)(i-1)] = binCenter6Alx250SciDet2;
	   binCenters6Alx250SciDet3[(const int)(i-1)] = binCenter6Alx250SciDet3;
	   binCenters6Alx500SciDet1[(const int)(i-1)] = binCenter6Alx500SciDet1;
	   binCenters6Alx500SciDet2[(const int)(i-1)] = binCenter6Alx500SciDet2;
	   binCenters6Alx500SciDet3[(const int)(i-1)] = binCenter6Alx500SciDet3;
	   binCenters6Alx750SciDet1[(const int)(i-1)] = binCenter6Alx750SciDet1;
	   binCenters6Alx750SciDet2[(const int)(i-1)] = binCenter6Alx750SciDet2;
	   binCenters6Alx750SciDet3[(const int)(i-1)] = binCenter6Alx750SciDet3;
	   binCenters0Almu250SciDet3[(const int)(i-1)] = binCenter0Almu250SciDet3; // 0-mm Al
	   binCenters0Almu500SciDet3[(const int)(i-1)] = binCenter0Almu500SciDet3;
	   binCenters0Almu750SciDet3[(const int)(i-1)] = binCenter0Almu750SciDet3;
	   binCenters0Alx250SciDet3[(const int)(i-1)] = binCenter0Alx250SciDet3;
	   binCenters0Alx500SciDet3[(const int)(i-1)] = binCenter0Alx500SciDet3;
	   binCenters0Alx750SciDet3[(const int)(i-1)] = binCenter0Alx750SciDet3;
	   
	   integralsmu250SciDet1[(const int)(i-1)] = integralmu250SciDet1/(hmu250SciDet1->GetEntries()); // 3-mm Al
	   integralsmu250SciDet2[(const int)(i-1)] = integralmu250SciDet2/(hmu250SciDet2->GetEntries());
	   integralsmu250SciDet3[(const int)(i-1)] = integralmu250SciDet3/(hmu250SciDet3->GetEntries());
	   integralsmu500SciDet1[(const int)(i-1)] = integralmu500SciDet1/(hmu500SciDet1->GetEntries());
	   integralsmu500SciDet2[(const int)(i-1)] = integralmu500SciDet2/(hmu500SciDet2->GetEntries());
	   integralsmu500SciDet3[(const int)(i-1)] = integralmu500SciDet3/(hmu500SciDet3->GetEntries());
	   integralsmu750SciDet1[(const int)(i-1)] = integralmu750SciDet1/(hmu750SciDet1->GetEntries());
	   integralsmu750SciDet2[(const int)(i-1)] = integralmu750SciDet2/(hmu750SciDet2->GetEntries());
	   integralsmu750SciDet3[(const int)(i-1)] = integralmu750SciDet3/(hmu750SciDet3->GetEntries());
	   integralsx250SciDet1[(const int)(i-1)] = integralx250SciDet1/(hx250SciDet1->GetEntries());
	   integralsx250SciDet2[(const int)(i-1)] = integralx250SciDet2/(hx250SciDet2->GetEntries());
	   integralsx250SciDet3[(const int)(i-1)] = integralx250SciDet3/(hx250SciDet3->GetEntries());
	   integralsx500SciDet1[(const int)(i-1)] = integralx500SciDet1/(hx500SciDet1->GetEntries());
	   integralsx500SciDet2[(const int)(i-1)] = integralx500SciDet2/(hx500SciDet2->GetEntries());
	   integralsx500SciDet3[(const int)(i-1)] = integralx500SciDet3/(hx500SciDet3->GetEntries());
	   integralsx750SciDet1[(const int)(i-1)] = integralx750SciDet1/(hx750SciDet1->GetEntries());
	   integralsx750SciDet2[(const int)(i-1)] = integralx750SciDet2/(hx750SciDet2->GetEntries());
	   integralsx750SciDet3[(const int)(i-1)] = integralx750SciDet3/(hx750SciDet3->GetEntries());
	   integrals6Almu250SciDet1[(const int)(i-1)] = integral6Almu250SciDet1/(h6Almu250SciDet1->GetEntries()); // 6-mm Al
	   integrals6Almu250SciDet2[(const int)(i-1)] = integral6Almu250SciDet2/(h6Almu250SciDet2->GetEntries());
	   integrals6Almu250SciDet3[(const int)(i-1)] = integral6Almu250SciDet3/(h6Almu250SciDet3->GetEntries());
	   integrals6Almu500SciDet1[(const int)(i-1)] = integral6Almu500SciDet1/(h6Almu500SciDet1->GetEntries());
	   integrals6Almu500SciDet2[(const int)(i-1)] = integral6Almu500SciDet2/(h6Almu500SciDet2->GetEntries());
	   integrals6Almu500SciDet3[(const int)(i-1)] = integral6Almu500SciDet3/(h6Almu500SciDet3->GetEntries());
	   integrals6Almu750SciDet1[(const int)(i-1)] = integral6Almu750SciDet1/(h6Almu750SciDet1->GetEntries());
	   integrals6Almu750SciDet2[(const int)(i-1)] = integral6Almu750SciDet2/(h6Almu750SciDet2->GetEntries());
	   integrals6Almu750SciDet3[(const int)(i-1)] = integral6Almu750SciDet3/(h6Almu750SciDet3->GetEntries());
	   integrals6Alx250SciDet1[(const int)(i-1)] = integral6Alx250SciDet1/(h6Alx250SciDet1->GetEntries());
	   integrals6Alx250SciDet2[(const int)(i-1)] = integral6Alx250SciDet2/(h6Alx250SciDet2->GetEntries());
	   integrals6Alx250SciDet3[(const int)(i-1)] = integral6Alx250SciDet3/(h6Alx250SciDet3->GetEntries());
	   integrals6Alx500SciDet1[(const int)(i-1)] = integral6Alx500SciDet1/(h6Alx500SciDet1->GetEntries());
	   integrals6Alx500SciDet2[(const int)(i-1)] = integral6Alx500SciDet2/(h6Alx500SciDet2->GetEntries());
	   integrals6Alx500SciDet3[(const int)(i-1)] = integral6Alx500SciDet3/(h6Alx500SciDet3->GetEntries());
	   integrals6Alx750SciDet1[(const int)(i-1)] = integral6Alx750SciDet1/(h6Alx750SciDet1->GetEntries());
	   integrals6Alx750SciDet2[(const int)(i-1)] = integral6Alx750SciDet2/(h6Alx750SciDet2->GetEntries());
	   integrals6Alx750SciDet3[(const int)(i-1)] = integral6Alx750SciDet3/(h6Alx750SciDet3->GetEntries());
	   integrals0Almu250SciDet3[(const int)(i-1)] = integral0Almu250SciDet3/(h0Almu250SciDet3->GetEntries()); // 0-mm Al
	   integrals0Almu500SciDet3[(const int)(i-1)] = integral0Almu500SciDet3/(h0Almu500SciDet3->GetEntries());
	   integrals0Almu750SciDet3[(const int)(i-1)] = integral0Almu750SciDet3/(h0Almu750SciDet3->GetEntries());
	   integrals0Alx250SciDet3[(const int)(i-1)] = integral0Alx250SciDet3/(h0Alx250SciDet3->GetEntries());
	   integrals0Alx500SciDet3[(const int)(i-1)] = integral0Alx500SciDet3/(h0Alx500SciDet3->GetEntries());
	   integrals0Alx750SciDet3[(const int)(i-1)] = integral0Alx750SciDet3/(h0Alx750SciDet3->GetEntries());
	  
	  
	
   }
   
   TCanvas *c = new TCanvas("c","E_{THR}",800,600);
   c->Divide(3,2);
   c->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu250SciDet1 = new TGraph(nbins,binCentersmu250SciDet1,integralsmu250SciDet1);
   grmu250SciDet1->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciDet_{1} + 3-mm Al [250-mm SciDet_{3}]");
   grmu250SciDet1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu250SciDet1->GetXaxis()->SetRangeUser(0,1);  // Location #3
   grmu250SciDet1->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu250SciDet1->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu250SciDet1->GetYaxis()->SetTitleOffset(1.8);
   grmu250SciDet1->SetMarkerColor(kBlack);
   grmu250SciDet1->SetMarkerStyle(33);
   grmu250SciDet1->SetLineColor(kBlack);
   grmu250SciDet1->Draw("ALP");
   TGraph *grx250SciDet1 = new TGraph(nbins,binCentersx250SciDet1,integralsx250SciDet1);
   grx250SciDet1->SetMarkerColor(kRed);
   grx250SciDet1->SetMarkerStyle(31);
   grx250SciDet1->SetLineColor(kRed);
   grx250SciDet1->Draw("LP");
   leg250SciDet1 = new TLegend(0.2,-0.01,0.4,0.08);
   leg250SciDet1->AddEntry(grmu250SciDet1,"#mu - decay","lp");
   leg250SciDet1->AddEntry(grx250SciDet1,"X-rays","lp");
   leg250SciDet1->Draw();
  
   c->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu250SciDet2 = new TGraph(nbins,binCentersmu250SciDet2,integralsmu250SciDet2);
   grmu250SciDet2->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciDet_{2} + 3-mm Al [250-mm SciDet_{3}]");
   grmu250SciDet2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu250SciDet2->GetXaxis()->SetRangeUser(0,1);
   grmu250SciDet2->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu250SciDet2->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu250SciDet2->GetYaxis()->SetTitleOffset(1.8);
   grmu250SciDet2->SetMarkerColor(kBlack);
   grmu250SciDet2->SetMarkerStyle(33);
   grmu250SciDet2->SetLineColor(kBlack);
   grmu250SciDet2->Draw("ALP");
   TGraph *grx250SciDet2 = new TGraph(nbins,binCentersx250SciDet2,integralsx250SciDet2);
   grx250SciDet2->SetMarkerColor(kRed);
   grx250SciDet2->SetMarkerStyle(31);
   grx250SciDet2->SetLineColor(kRed);
   grx250SciDet2->Draw("LP");
   leg250SciDet2 = new TLegend(0.2,-0.01,0.4,0.08);
   leg250SciDet2->AddEntry(grmu250SciDet2,"#mu - decay","lp");
   leg250SciDet2->AddEntry(grx250SciDet2,"X-rays","lp");
   leg250SciDet2->Draw();

   c->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu250SciDet3 = new TGraph(nbins,binCentersmu250SciDet3,integralsmu250SciDet3);
   grmu250SciDet3->SetTitle("X-ray cascade vs #mu-decay: 250-mm SciDet_{3} + 3-mm Al [250-mm SciDet_{3}]");
   grmu250SciDet3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu250SciDet3->GetXaxis()->SetRangeUser(0,12);
   grmu250SciDet3->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu250SciDet3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu250SciDet3->GetYaxis()->SetTitleOffset(1.8);
   grmu250SciDet3->SetMarkerColor(kBlack);
   grmu250SciDet3->SetMarkerStyle(33);
   grmu250SciDet3->SetLineColor(kBlack);
   grmu250SciDet3->Draw("ALP");
   TGraph *grx250SciDet3 = new TGraph(nbins,binCentersx250SciDet3,integralsx250SciDet3);
   grx250SciDet3->SetMarkerColor(kRed);
   grx250SciDet3->SetMarkerStyle(31);
   grx250SciDet3->SetLineColor(kRed);
   grx250SciDet3->Draw("LP");
   leg250SciDet3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg250SciDet3->AddEntry(grmu250SciDet3,"#mu - decay","lp");
   leg250SciDet3->AddEntry(grx250SciDet3,"X-rays","lp");
   leg250SciDet3->Draw();
   
   c->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu250SciDet1 = new TGraph(nbins,binCenters6Almu250SciDet1,integrals6Almu250SciDet1);
   gr6Almu250SciDet1->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciDet_{1} + 6-mm Al [250-mm SciDet_{3}]");
   gr6Almu250SciDet1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu250SciDet1->GetXaxis()->SetRangeUser(0,1);
   gr6Almu250SciDet1->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu250SciDet1->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu250SciDet1->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu250SciDet1->SetMarkerColor(kBlack);
   gr6Almu250SciDet1->SetMarkerStyle(33);
   gr6Almu250SciDet1->SetLineColor(kBlack);
   gr6Almu250SciDet1->Draw("ALP");
   TGraph *gr6Alx250SciDet1 = new TGraph(nbins,binCenters6Alx250SciDet1,integrals6Alx250SciDet1);
   gr6Alx250SciDet1->SetMarkerColor(kRed);
   gr6Alx250SciDet1->SetMarkerStyle(31);
   gr6Alx250SciDet1->SetLineColor(kRed);
   gr6Alx250SciDet1->Draw("LP");
   leg6Al250SciDet1 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al250SciDet1->AddEntry(gr6Almu250SciDet1,"#mu - decay","lp");
   leg6Al250SciDet1->AddEntry(gr6Alx250SciDet1,"X-rays","lp");
   leg6Al250SciDet1->Draw();
  
   c->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu250SciDet2 = new TGraph(nbins,binCenters6Almu250SciDet2,integrals6Almu250SciDet2);
   gr6Almu250SciDet2->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciDet_{2} + 6-mm Al [250-mm SciDet_{3}]");
   gr6Almu250SciDet2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu250SciDet2->GetXaxis()->SetRangeUser(0,1);
   gr6Almu250SciDet2->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu250SciDet2->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu250SciDet2->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu250SciDet2->SetMarkerColor(kBlack);
   gr6Almu250SciDet2->SetMarkerStyle(33);
   gr6Almu250SciDet2->SetLineColor(kBlack);
   gr6Almu250SciDet2->Draw("ALP");
   TGraph *gr6Alx250SciDet2 = new TGraph(nbins,binCenters6Alx250SciDet2,integrals6Alx250SciDet2);
   gr6Alx250SciDet2->SetMarkerColor(kRed);
   gr6Alx250SciDet2->SetMarkerStyle(31);
   gr6Alx250SciDet2->SetLineColor(kRed);
   gr6Alx250SciDet2->Draw("LP");
   leg6Al250SciDet2 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al250SciDet2->AddEntry(gr6Almu250SciDet2,"#mu - decay","lp");
   leg6Al250SciDet2->AddEntry(gr6Alx250SciDet2,"X-rays","lp");
   leg6Al250SciDet2->Draw();

   c->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu250SciDet3 = new TGraph(nbins,binCenters6Almu250SciDet3,integrals6Almu250SciDet3);
   gr6Almu250SciDet3->SetTitle("X-ray cascade vs #mu-decay: 250-mm SciDet_{3} + 6-mm Al [250-mm SciDet_{3}]");
   gr6Almu250SciDet3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu250SciDet3->GetXaxis()->SetRangeUser(0,12);
   gr6Almu250SciDet3->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu250SciDet3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu250SciDet3->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu250SciDet3->SetMarkerColor(kBlack);
   gr6Almu250SciDet3->SetMarkerStyle(33);
   gr6Almu250SciDet3->SetLineColor(kBlack);
   gr6Almu250SciDet3->Draw("ALP");
   TGraph *gr6Alx250SciDet3 = new TGraph(nbins,binCenters6Alx250SciDet3,integrals6Alx250SciDet3);
   gr6Alx250SciDet3->SetMarkerColor(kRed);
   gr6Alx250SciDet3->SetMarkerStyle(31);
   gr6Alx250SciDet3->SetLineColor(kRed);
   grx250SciDet3->Draw("LP");
   leg6Al250SciDet3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al250SciDet3->AddEntry(gr6Almu250SciDet3,"#mu - decay","lp");
   leg6Al250SciDet3->AddEntry(gr6Alx250SciDet3,"X-rays","lp");
   leg6Al250SciDet3->Draw();
   
   c->SaveAs("Bubble4THR_3mm_6mm_Al_250mm_SciD3.pdf");
   c->SaveAs("Bubble4THR_3mm_6mm_Al_250mm_SciD3.png");
   c->SaveAs("Bubble4THR_3mm_6mm_Al_250mm_SciD3.C");
   
   
   
   TCanvas *d = new TCanvas("d","E_{THR}",800,600);
   d->Divide(3,2);
   d->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu500SciDet1 = new TGraph(nbins,binCentersmu500SciDet1,integralsmu500SciDet1);
   grmu500SciDet1->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciDet_{1} + 3-mm Al [500-mm SciDet_{3}]");
   grmu500SciDet1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu500SciDet1->GetXaxis()->SetRangeUser(0,1);
   grmu500SciDet1->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu500SciDet1->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu500SciDet1->GetYaxis()->SetTitleOffset(1.8);
   grmu500SciDet1->SetMarkerColor(kBlack);
   grmu500SciDet1->SetMarkerStyle(33);
   grmu500SciDet1->SetLineColor(kBlack);
   grmu500SciDet1->Draw("ALP");
   TGraph *grx500SciDet1 = new TGraph(nbins,binCentersx500SciDet1,integralsx500SciDet1);
   grx500SciDet1->SetMarkerColor(kRed);
   grx500SciDet1->SetMarkerStyle(31);
   grx500SciDet1->SetLineColor(kRed);
   grx500SciDet1->Draw("LP");
   leg500SciDet1 = new TLegend(0.2,-0.01,0.4,0.08);
   leg500SciDet1->AddEntry(grmu500SciDet1,"#mu - decay","lp");
   leg500SciDet1->AddEntry(grx500SciDet1,"X-rays","lp");
   leg500SciDet1->Draw();
  
   d->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu500SciDet2 = new TGraph(nbins,binCentersmu500SciDet2,integralsmu500SciDet2);
   grmu500SciDet2->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciDet_{2} + 3-mm Al [500-mm SciDet_{3}]");
   grmu500SciDet2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu500SciDet2->GetXaxis()->SetRangeUser(0,1);
   grmu500SciDet2->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu500SciDet2->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu500SciDet2->GetYaxis()->SetTitleOffset(1.8);
   grmu500SciDet2->SetMarkerColor(kBlack);
   grmu500SciDet2->SetMarkerStyle(33);
   grmu500SciDet2->SetLineColor(kBlack);
   grmu500SciDet2->Draw("ALP");
   TGraph *grx500SciDet2 = new TGraph(nbins,binCentersx500SciDet2,integralsx500SciDet2);
   grx500SciDet2->SetMarkerColor(kRed);
   grx500SciDet2->SetMarkerStyle(31);
   grx500SciDet2->SetLineColor(kRed);
   grx500SciDet2->Draw("LP");
   leg500SciDet2 = new TLegend(0.2,-0.01,0.4,0.08);
   leg500SciDet2->AddEntry(grmu500SciDet2,"#mu - decay","lp");
   leg500SciDet2->AddEntry(grx500SciDet2,"X-rays","lp");
   leg500SciDet2->Draw();

   d->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu500SciDet3 = new TGraph(nbins,binCentersmu500SciDet3,integralsmu500SciDet3);
   grmu500SciDet3->SetTitle("X-ray cascade vs #mu-decay: 500-mm SciDet_{3} + 3-mm Al [500-mm SciDet_{3}]");
   grmu500SciDet3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu500SciDet3->GetXaxis()->SetRangeUser(0,12);
   grmu500SciDet3->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu500SciDet3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu500SciDet3->GetYaxis()->SetTitleOffset(1.8);
   grmu500SciDet3->SetMarkerColor(kBlack);
   grmu500SciDet3->SetMarkerStyle(33);
   grmu500SciDet3->SetLineColor(kBlack);
   grmu500SciDet3->Draw("ALP");
   TGraph *grx500SciDet3 = new TGraph(nbins,binCentersx500SciDet3,integralsx500SciDet3);
   grx500SciDet3->SetMarkerColor(kRed);
   grx500SciDet3->SetMarkerStyle(31);
   grx500SciDet3->SetLineColor(kRed);
   grx500SciDet3->Draw("LP");
   leg500SciDet3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg500SciDet3->AddEntry(grmu500SciDet3,"#mu - decay","lp");
   leg500SciDet3->AddEntry(grx500SciDet3,"X-rays","lp");
   leg500SciDet3->Draw();
   
   d->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu500SciDet1 = new TGraph(nbins,binCenters6Almu500SciDet1,integrals6Almu500SciDet1);
   gr6Almu500SciDet1->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciDet_{1} + 6-mm Al [500-mm SciDet_{3}]");
   gr6Almu500SciDet1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu500SciDet1->GetXaxis()->SetRangeUser(0,1);
   gr6Almu500SciDet1->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu500SciDet1->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu500SciDet1->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu500SciDet1->SetMarkerColor(kBlack);
   gr6Almu500SciDet1->SetMarkerStyle(33);
   gr6Almu500SciDet1->SetLineColor(kBlack);
   gr6Almu500SciDet1->Draw("ALP");
   TGraph *gr6Alx500SciDet1 = new TGraph(nbins,binCenters6Alx500SciDet1,integrals6Alx500SciDet1);
   gr6Alx500SciDet1->SetMarkerColor(kRed);
   gr6Alx500SciDet1->SetMarkerStyle(31);
   gr6Alx500SciDet1->SetLineColor(kRed);
   gr6Alx250SciDet1->Draw("LP");
   leg6Al500SciDet1 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al500SciDet1->AddEntry(gr6Almu500SciDet1,"#mu - decay","lp");
   leg6Al500SciDet1->AddEntry(gr6Alx500SciDet1,"X-rays","lp");
   leg6Al500SciDet1->Draw();
  
   d->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu500SciDet2 = new TGraph(nbins,binCenters6Almu500SciDet2,integrals6Almu500SciDet2);
   gr6Almu500SciDet2->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciDet_{2} + 6-mm Al [500-mm SciDet_{3}]");
   gr6Almu500SciDet2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu500SciDet2->GetXaxis()->SetRangeUser(0,1);
   gr6Almu500SciDet2->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu500SciDet2->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu500SciDet2->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu500SciDet2->SetMarkerColor(kBlack);
   gr6Almu500SciDet2->SetMarkerStyle(33);
   gr6Almu500SciDet2->SetLineColor(kBlack);
   gr6Almu500SciDet2->Draw("ALP");
   TGraph *gr6Alx500SciDet2 = new TGraph(nbins,binCenters6Alx500SciDet2,integrals6Alx500SciDet2);
   gr6Alx500SciDet2->SetMarkerColor(kRed);
   gr6Alx500SciDet2->SetMarkerStyle(31);
   gr6Alx500SciDet2->SetLineColor(kRed);
   gr6Alx500SciDet2->Draw("LP");
   leg6Al500SciDet2 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al500SciDet2->AddEntry(gr6Almu500SciDet2,"#mu - decay","lp");
   leg6Al500SciDet2->AddEntry(gr6Alx500SciDet2,"X-rays","lp");
   leg6Al500SciDet2->Draw();

   d->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu500SciDet3 = new TGraph(nbins,binCenters6Almu500SciDet3,integrals6Almu500SciDet3);
   gr6Almu500SciDet3->SetTitle("X-ray cascade vs #mu-decay: 500-mm SciDet_{3} + 6-mm Al [500-mm SciDet_{3}]");
   gr6Almu500SciDet3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu500SciDet3->GetXaxis()->SetRangeUser(0,12);
   gr6Almu500SciDet3->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu500SciDet3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu500SciDet3->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu500SciDet3->SetMarkerColor(kBlack);
   gr6Almu500SciDet3->SetMarkerStyle(33);
   gr6Almu500SciDet3->SetLineColor(kBlack);
   gr6Almu500SciDet3->Draw("ALP");
   TGraph *gr6Alx500SciDet3 = new TGraph(nbins,binCenters6Alx500SciDet3,integrals6Alx500SciDet3);
   gr6Alx500SciDet3->SetMarkerColor(kRed);
   gr6Alx500SciDet3->SetMarkerStyle(31);
   gr6Alx500SciDet3->SetLineColor(kRed);
   grx500SciDet3->Draw("LP");
   leg6Al500SciDet3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al500SciDet3->AddEntry(gr6Almu500SciDet3,"#mu - decay","lp");
   leg6Al500SciDet3->AddEntry(gr6Alx500SciDet3,"X-rays","lp");
   leg6Al500SciDet3->Draw();
   
   d->SaveAs("Bubble4THR_3mm_6mm_Al_500mm_SciD3.pdf");
   d->SaveAs("Bubble4THR_3mm_6mm_Al_500mm_SciD3.png");
   d->SaveAs("Bubble4THR_3mm_6mm_Al_500mm_SciD3.C");
   
   
   
   TCanvas *e = new TCanvas("e","E_{THR}",800,600);
   e->Divide(3,2);
   e->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu750SciDet1 = new TGraph(nbins,binCentersmu750SciDet1,integralsmu750SciDet1);
   grmu750SciDet1->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciDet_{1} + 3-mm Al [750-mm SciDet_{3}]");
   grmu750SciDet1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu750SciDet1->GetXaxis()->SetRangeUser(0,1);
   grmu750SciDet1->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu750SciDet1->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu750SciDet1->GetYaxis()->SetTitleOffset(1.8);
   grmu750SciDet1->SetMarkerColor(kBlack);
   grmu750SciDet1->SetMarkerStyle(33);
   grmu750SciDet1->SetLineColor(kBlack);
   grmu750SciDet1->Draw("ALP");
   TGraph *grx750SciDet1 = new TGraph(nbins,binCentersx750SciDet1,integralsx750SciDet1);
   grx750SciDet1->SetMarkerColor(kRed);
   grx750SciDet1->SetMarkerStyle(31);
   grx750SciDet1->SetLineColor(kRed);
   grx750SciDet1->Draw("LP");
   leg750SciDet1 = new TLegend(0.2,-0.01,0.4,0.08);
   leg750SciDet1->AddEntry(grmu750SciDet1,"#mu - decay","lp");
   leg750SciDet1->AddEntry(grx750SciDet1,"X-rays","lp");
   leg750SciDet1->Draw();
  
   e->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu750SciDet2 = new TGraph(nbins,binCentersmu750SciDet2,integralsmu750SciDet2);
   grmu750SciDet2->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciDet_{2} + 3-mm Al [750-mm SciDet_{3}]");
   grmu750SciDet2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu750SciDet2->GetXaxis()->SetRangeUser(0,1);
   grmu750SciDet2->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu750SciDet2->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu750SciDet2->GetYaxis()->SetTitleOffset(1.8);
   grmu750SciDet2->SetMarkerColor(kBlack);
   grmu750SciDet2->SetMarkerStyle(33);
   grmu750SciDet2->SetLineColor(kBlack);
   grmu750SciDet2->Draw("ALP");
   TGraph *grx750SciDet2 = new TGraph(nbins,binCentersx750SciDet2,integralsx750SciDet2);
   grx750SciDet2->SetMarkerColor(kRed);
   grx750SciDet2->SetMarkerStyle(31);
   grx750SciDet2->SetLineColor(kRed);
   grx750SciDet2->Draw("LP");
   leg750SciDet2 = new TLegend(0.2,-0.01,0.4,0.08);
   leg750SciDet2->AddEntry(grmu750SciDet2,"#mu - decay","lp");
   leg750SciDet2->AddEntry(grx750SciDet2,"X-rays","lp");
   leg750SciDet2->Draw();

   e->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu750SciDet3 = new TGraph(nbins,binCentersmu750SciDet3,integralsmu750SciDet3);
   grmu750SciDet3->SetTitle("X-ray cascade vs #mu-decay: 750-mm SciDet_{3} + 3-mm Al [750-mm SciDet_{3}]");
   grmu750SciDet3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu750SciDet3->GetXaxis()->SetRangeUser(0,12);
   grmu750SciDet3->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu750SciDet3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu750SciDet3->GetYaxis()->SetTitleOffset(1.8);
   grmu750SciDet3->SetMarkerColor(kBlack);
   grmu750SciDet3->SetMarkerStyle(33);
   grmu750SciDet3->SetLineColor(kBlack);
   grmu750SciDet3->Draw("ALP");
   TGraph *grx750SciDet3 = new TGraph(nbins,binCentersx750SciDet3,integralsx750SciDet3);
   grx750SciDet3->SetMarkerColor(kRed);
   grx750SciDet3->SetMarkerStyle(31);
   grx750SciDet3->SetLineColor(kRed);
   grx750SciDet3->Draw("LP");
   leg750SciDet3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg750SciDet3->AddEntry(grmu750SciDet3,"#mu - decay","lp");
   leg750SciDet3->AddEntry(grx750SciDet3,"X-rays","lp");
   leg750SciDet3->Draw();
   
   e->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu750SciDet1 = new TGraph(nbins,binCenters6Almu750SciDet1,integrals6Almu750SciDet1);
   gr6Almu750SciDet1->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciDet_{1} + 6-mm Al [750-mm SciDet_{3}]");
   gr6Almu750SciDet1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu750SciDet1->GetXaxis()->SetRangeUser(0,1);
   gr6Almu750SciDet1->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu750SciDet1->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu750SciDet1->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu750SciDet1->SetMarkerColor(kBlack);
   gr6Almu750SciDet1->SetMarkerStyle(33);
   gr6Almu750SciDet1->SetLineColor(kBlack);
   gr6Almu750SciDet1->Draw("ALP");
   TGraph *gr6Alx750SciDet1 = new TGraph(nbins,binCenters6Alx750SciDet1,integrals6Alx750SciDet1);
   gr6Alx750SciDet1->SetMarkerColor(kRed);
   gr6Alx750SciDet1->SetMarkerStyle(31);
   gr6Alx750SciDet1->SetLineColor(kRed);
   gr6Alx750SciDet1->Draw("LP");
   leg6Al750SciDet1 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al750SciDet1->AddEntry(gr6Almu750SciDet1,"#mu - decay","lp");
   leg6Al750SciDet1->AddEntry(gr6Alx750SciDet1,"X-rays","lp");
   leg6Al750SciDet1->Draw();
  
   e->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu750SciDet2 = new TGraph(nbins,binCenters6Almu750SciDet2,integrals6Almu750SciDet2);
   gr6Almu750SciDet2->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciDet_{2} + 6-mm Al [750-mm SciDet_{3}]");
   gr6Almu750SciDet2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu750SciDet2->GetXaxis()->SetRangeUser(0,1);
   gr6Almu750SciDet2->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu750SciDet2->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu750SciDet2->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu750SciDet2->SetMarkerColor(kBlack);
   gr6Almu750SciDet2->SetMarkerStyle(33);
   gr6Almu750SciDet2->SetLineColor(kBlack);
   gr6Almu750SciDet2->Draw("ALP");
   TGraph *gr6Alx750SciDet2 = new TGraph(nbins,binCenters6Alx750SciDet2,integrals6Alx750SciDet2);
   gr6Alx750SciDet2->SetMarkerColor(kRed);
   gr6Alx750SciDet2->SetMarkerStyle(31);
   gr6Alx750SciDet2->SetLineColor(kRed);
   gr6Alx750SciDet2->Draw("LP");
   leg6Al750SciDet2 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al750SciDet2->AddEntry(gr6Almu750SciDet2,"#mu - decay","lp");
   leg6Al750SciDet2->AddEntry(gr6Alx750SciDet2,"X-rays","lp");
   leg6Al750SciDet2->Draw();

   e->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu750SciDet3 = new TGraph(nbins,binCenters6Almu750SciDet3,integrals6Almu750SciDet3);
   gr6Almu750SciDet3->SetTitle("X-ray cascade vs #mu-decay: 750-mm SciDet_{3} + 6-mm Al [750-mm SciDet_{3}]");
   gr6Almu750SciDet3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu750SciDet3->GetXaxis()->SetRangeUser(0,12);
   gr6Almu750SciDet3->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu750SciDet3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu750SciDet3->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu750SciDet3->SetMarkerColor(kBlack);
   gr6Almu750SciDet3->SetMarkerStyle(33);
   gr6Almu750SciDet3->SetLineColor(kBlack);
   gr6Almu750SciDet3->Draw("ALP");
   TGraph *gr6Alx750SciDet3 = new TGraph(nbins,binCenters6Alx750SciDet3,integrals6Alx750SciDet3);
   gr6Alx750SciDet3->SetMarkerColor(kRed);
   gr6Alx750SciDet3->SetMarkerStyle(31);
   gr6Alx750SciDet3->SetLineColor(kRed);
   grx750SciDet3->Draw("LP");
   leg6Al750SciDet3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al750SciDet3->AddEntry(gr6Almu750SciDet3,"#mu - decay","lp");
   leg6Al750SciDet3->AddEntry(gr6Alx750SciDet3,"X-rays","lp");
   leg6Al750SciDet3->Draw();
   
   e->SaveAs("Bubble4THR_3mm_6mm_Al_750mm_SciD3.pdf");
   e->SaveAs("Bubble4THR_3mm_6mm_Al_750mm_SciD3.png");
   e->SaveAs("Bubble4THR_3mm_6mm_Al_750mm_SciD3.C");
   
   
   
   TCanvas *f = new TCanvas("f","E_{THR}",800,600);
   f->Divide(3,2);
   f->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr0Almu250SciDet3 = new TGraph(nbins,binCenters0Almu250SciDet3,integrals0Almu250SciDet3);
   gr0Almu250SciDet3->SetTitle("X-ray cascade vs #mu-decay: 250-mm SciDet_{3} + 0-mm Al [250-mm SciDet_{3}]");
   gr0Almu250SciDet3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr0Almu250SciDet3->GetXaxis()->SetRangeUser(0,12);
   gr0Almu250SciDet3->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr0Almu250SciDet3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr0Almu250SciDet3->GetYaxis()->SetTitleOffset(1.8);
   gr0Almu250SciDet3->SetMarkerColor(kBlack);
   gr0Almu250SciDet3->SetMarkerStyle(33);
   gr0Almu250SciDet3->SetLineColor(kBlack);
   gr0Almu250SciDet3->Draw("ALP");
   TGraph *gr0Alx250SciDet3 = new TGraph(nbins,binCenters0Alx250SciDet3,integrals0Alx250SciDet3);
   gr0Alx250SciDet3->SetMarkerColor(kRed);
   gr0Alx250SciDet3->SetMarkerStyle(31);
   gr0Alx250SciDet3->SetLineColor(kRed);
   gr0Alx250SciDet3->Draw("LP");
   leg0Al250SciDet3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg0Al250SciDet3->AddEntry(gr0Almu250SciDet3,"#mu - decay","lp");
   leg0Al250SciDet3->AddEntry(gr0Alx250SciDet3,"X-rays","lp");
   leg0Al250SciDet3->Draw();
   
   f->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr0Almu500SciDet3 = new TGraph(nbins,binCenters0Almu500SciDet3,integrals0Almu500SciDet3);
   gr0Almu500SciDet3->SetTitle("X-ray cascade vs #mu-decay: 500-mm SciDet_{3} + 0-mm Al [500-mm SciDet_{3}]");
   gr0Almu500SciDet3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr0Almu500SciDet3->GetXaxis()->SetRangeUser(0,12);
   gr0Almu500SciDet3->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr0Almu500SciDet3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr0Almu500SciDet3->GetYaxis()->SetTitleOffset(1.8);
   gr0Almu500SciDet3->SetMarkerColor(kBlack);
   gr0Almu500SciDet3->SetMarkerStyle(33);
   gr0Almu500SciDet3->SetLineColor(kBlack);
   gr0Almu500SciDet3->Draw("ALP");
   TGraph *gr0Alx500SciDet3 = new TGraph(nbins,binCenters0Alx500SciDet3,integrals0Alx500SciDet3);
   gr0Alx500SciDet3->SetMarkerColor(kRed);
   gr0Alx500SciDet3->SetMarkerStyle(31);
   gr0Alx500SciDet3->SetLineColor(kRed);
   gr0Alx500SciDet3->Draw("LP");
   leg0Al500SciDet3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg0Al500SciDet3->AddEntry(gr0Almu500SciDet3,"#mu - decay","lp");
   leg0Al500SciDet3->AddEntry(gr0Alx500SciDet3,"X-rays","lp");
   leg0Al500SciDet3->Draw();
   
   f->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr0Almu750SciDet3 = new TGraph(nbins,binCenters0Almu750SciDet3,integrals0Almu750SciDet3);
   gr0Almu750SciDet3->SetTitle("X-ray cascade vs #mu-decay: 750-mm SciDet_{3} + 0-mm Al [750-mm SciDet_{3}]");
   gr0Almu750SciDet3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr0Almu750SciDet3->GetXaxis()->SetRangeUser(0,12);
   gr0Almu750SciDet3->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr0Almu750SciDet3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr0Almu750SciDet3->GetYaxis()->SetTitleOffset(1.8);
   gr0Almu750SciDet3->SetMarkerColor(kBlack);
   gr0Almu750SciDet3->SetMarkerStyle(33);
   gr0Almu750SciDet3->SetLineColor(kBlack);
   gr0Almu750SciDet3->Draw("ALP");
   TGraph *gr0Alx750SciDet3 = new TGraph(nbins,binCenters0Alx750SciDet3,integrals0Alx750SciDet3);
   gr0Alx750SciDet3->SetMarkerColor(kRed);
   gr0Alx750SciDet3->SetMarkerStyle(31);
   gr0Alx750SciDet3->SetLineColor(kRed);
   gr0Alx750SciDet3->Draw("LP");
   leg0Al750SciDet3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg0Al750SciDet3->AddEntry(gr0Almu750SciDet3,"#mu - decay","lp");
   leg0Al750SciDet3->AddEntry(gr0Alx750SciDet3,"X-rays","lp");
   leg0Al750SciDet3->Draw();
   
   f->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr0Almu250SciDet3 = new TGraph(nbins,binCenters0Almu250SciDet3,integrals0Almu250SciDet3);
   gr0Almu250SciDet3->SetTitle("X-ray cascade vs #mu-decay: 250-mm SciDet_{3} + 0-mm Al [250-mm SciDet_{3}]");
   gr0Almu250SciDet3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr0Almu250SciDet3->GetXaxis()->SetRangeUser(0,12);
   gr0Almu250SciDet3->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr0Almu250SciDet3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr0Almu250SciDet3->GetYaxis()->SetTitleOffset(1.8);
   gr0Almu250SciDet3->SetMarkerColor(kBlack);
   gr0Almu250SciDet3->SetMarkerStyle(33);
   gr0Almu250SciDet3->SetLineColor(kBlack);
   gr0Almu250SciDet3->Draw("ALP");
   TGraph *gr0Alx250SciDet3 = new TGraph(nbins,binCenters0Alx250SciDet3,integrals0Alx250SciDet3);
   gr0Alx250SciDet3->SetMarkerColor(kRed);
   gr0Alx250SciDet3->SetMarkerStyle(31);
   gr0Alx250SciDet3->SetLineColor(kRed);
   gr0Alx250SciDet3->Draw("LP");
   leg0Al250SciDet3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg0Al250SciDet3->AddEntry(gr0Almu250SciDet3,"#mu - decay","lp");
   leg0Al250SciDet3->AddEntry(gr0Alx250SciDet3,"X-rays","lp");
   leg0Al250SciDet3->Draw();
   
   f->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr0Almu500SciDet3 = new TGraph(nbins,binCenters0Almu500SciDet3,integrals0Almu500SciDet3);
   gr0Almu500SciDet3->SetTitle("X-ray cascade vs #mu-decay: 500-mm SciDet_{3} + 0-mm Al [500-mm SciDet_{3}]");
   gr0Almu500SciDet3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr0Almu500SciDet3->GetXaxis()->SetRangeUser(0,12);
   gr0Almu500SciDet3->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr0Almu500SciDet3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr0Almu500SciDet3->GetYaxis()->SetTitleOffset(1.8);
   gr0Almu500SciDet3->SetMarkerColor(kBlack);
   gr0Almu500SciDet3->SetMarkerStyle(33);
   gr0Almu500SciDet3->SetLineColor(kBlack);
   gr0Almu500SciDet3->Draw("ALP");
   TGraph *gr0Alx500SciDet3 = new TGraph(nbins,binCenters0Alx500SciDet3,integrals0Alx500SciDet3);
   gr0Alx500SciDet3->SetMarkerColor(kRed);
   gr0Alx500SciDet3->SetMarkerStyle(31);
   gr0Alx500SciDet3->SetLineColor(kRed);
   gr0Alx500SciDet3->Draw("LP");
   leg0Al500SciDet3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg0Al500SciDet3->AddEntry(gr0Almu500SciDet3,"#mu - decay","lp");
   leg0Al500SciDet3->AddEntry(gr0Alx500SciDet3,"X-rays","lp");
   leg0Al500SciDet3->Draw();
   
   f->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr0Almu750SciDet3 = new TGraph(nbins,binCenters0Almu750SciDet3,integrals0Almu750SciDet3);
   gr0Almu750SciDet3->SetTitle("X-ray cascade vs #mu-decay: 750-mm SciDet_{3} + 0-mm Al [750-mm SciDet_{3}]");
   gr0Almu750SciDet3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr0Almu750SciDet3->GetXaxis()->SetRangeUser(0,12);
   gr0Almu750SciDet3->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr0Almu750SciDet3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr0Almu750SciDet3->GetYaxis()->SetTitleOffset(1.8);
   gr0Almu750SciDet3->SetMarkerColor(kBlack);
   gr0Almu750SciDet3->SetMarkerStyle(33);
   gr0Almu750SciDet3->SetLineColor(kBlack);
   gr0Almu750SciDet3->Draw("ALP");
   TGraph *gr0Alx750SciDet3 = new TGraph(nbins,binCenters0Alx750SciDet3,integrals0Alx750SciDet3);
   gr0Alx750SciDet3->SetMarkerColor(kRed);
   gr0Alx750SciDet3->SetMarkerStyle(31);
   gr0Alx750SciDet3->SetLineColor(kRed);
   gr0Alx750SciDet3->Draw("LP");
   leg0Al750SciDet3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg0Al750SciDet3->AddEntry(gr0Almu750SciDet3,"#mu - decay","lp");
   leg0Al750SciDet3->AddEntry(gr0Alx750SciDet3,"X-rays","lp");
   leg0Al750SciDet3->Draw();
 
   f->SaveAs("Bubble4THR_0mm_Al_250mm_500mm_750mm_SciD3.pdf");
   f->SaveAs("Bubble4THR_0mm_Al_250mm_500mm_750mm_SciD3.png");
   f->SaveAs("Bubble4THR_0mm_Al_250mm_500mm_750mm_SciD3.C");


 }
 
 
 int main() {
   bubble4THR();
   return 0;
}  
