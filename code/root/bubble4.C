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
   // With {250,500,750}-mm BGO 3-mm Al
   std::string filemu250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filemu500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filemu750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filex250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6goldcascade.root";
   std::string filex500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_3mm_Al_1e6goldcascade.root";
   std::string filex750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_3mm_Al_1e6goldcascade.root";
   // With {250,500,750}-mm BGO 6-mm Al
   std::string file6Almu250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Almu500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Almu750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Alx250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_6mm_Al_1e6goldcascade.root";
   std::string file6Alx500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_6mm_Al_1e6goldcascade.root";
   std::string file6Alx750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_6mm_Al_1e6goldcascade.root";
 

   /*********************************/
   /*           Analysis            */
   /*********************************/

   const int nbins = 150;
  
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

   // Histograms
   // 3-mm Al
   TH1F *hmu250SciDet1 = new TH1F("hmu250SciDet1","Edep",nbins,0,10);
   TH1F *hmu250SciDet2 = new TH1F("hmu250SciDet2","Edep",nbins,0,10);
   TH1F *hmu250SciDet3 = new TH1F("hmu250SciDet3","Edep",nbins,0,60);
   TH1F *hmu500SciDet1 = new TH1F("hmu500SciDet1","Edep",nbins,0,10);
   TH1F *hmu500SciDet2 = new TH1F("hmu500SciDet2","Edep",nbins,0,10);
   TH1F *hmu500SciDet3 = new TH1F("hmu500SciDet3","Edep",nbins,0,60);
   TH1F *hmu750SciDet1 = new TH1F("hmu750SciDet1","Edep",nbins,0,10);
   TH1F *hmu750SciDet2 = new TH1F("hmu750SciDet2","Edep",nbins,0,10);
   TH1F *hmu750SciDet3 = new TH1F("hmu750SciDet3","Edep",nbins,0,60);
   TH1F *hx250SciDet1 = new TH1F("hx250SciDet1","Edep",nbins,0,6);
   TH1F *hx250SciDet2 = new TH1F("hx250SciDet2","Edep",nbins,0,6);
   TH1F *hx250SciDet3 = new TH1F("hx250SciDet3","Edep",nbins,0,12);
   TH1F *hx500SciDet1 = new TH1F("hx500SciDet1","Edep",nbins,0,6);
   TH1F *hx500SciDet2 = new TH1F("hx500SciDet2","Edep",nbins,0,6);
   TH1F *hx500SciDet3 = new TH1F("hx500SciDet3","Edep",nbins,0,12);
   TH1F *hx750SciDet1 = new TH1F("hx750SciDet1","Edep",nbins,0,6);
   TH1F *hx750SciDet2 = new TH1F("hx750SciDet2","Edep",nbins,0,6);
   TH1F *hx750SciDet3 = new TH1F("hx750SciDet3","Edep",nbins,0,12);
   // 3-mm Al [copies]
   TH1F *hmu250SciDet1n = new TH1F("hmu250SciDet1n","Edep",nbins,0,9);
   TH1F *hmu250SciDet2n = new TH1F("hmu250SciDet2n","Edep",nbins,0,9);
   TH1F *hmu250SciDet3n = new TH1F("hmu250SciDet3n","Edep",nbins,0,50);
   TH1F *hmu500SciDet1n = new TH1F("hmu500SciDet1n","Edep",nbins,0,9);
   TH1F *hmu500SciDet2n = new TH1F("hmu500SciDet2n","Edep",nbins,0,9);
   TH1F *hmu500SciDet3n = new TH1F("hmu500SciDet3n","Edep",nbins,0,50);
   TH1F *hmu750SciDet1n = new TH1F("hmu750SciDet1n","Edep",nbins,0,9);
   TH1F *hmu750SciDet2n = new TH1F("hmu750SciDet2n","Edep",nbins,0,9);
   TH1F *hmu750SciDet3n = new TH1F("hmu750SciDet3n","Edep",nbins,0,50);
   TH1F *hx250SciDet1n = new TH1F("hx250SciDet1n","Edep",nbins,0,9);
   TH1F *hx250SciDet2n = new TH1F("hx250SciDet2n","Edep",nbins,0,9);
   TH1F *hx250SciDet3n = new TH1F("hx250SciDet3n","Edep",nbins,0,50);
   TH1F *hx500SciDet1n = new TH1F("hx500SciDet1n","Edep",nbins,0,9);
   TH1F *hx500SciDet2n = new TH1F("hx500SciDet2n","Edep",nbins,0,9);
   TH1F *hx500SciDet3n = new TH1F("hx500SciDet3n","Edep",nbins,0,50);
   TH1F *hx750SciDet1n = new TH1F("hx750SciDet1n","Edep",nbins,0,9);
   TH1F *hx750SciDet2n = new TH1F("hx750SciDet2n","Edep",nbins,0,9);
   TH1F *hx750SciDet3n = new TH1F("hx750SciDet3n","Edep",nbins,0,50);
   // 6-mm Al
   TH1F *h6Almu250SciDet1 = new TH1F("h6Almu250SciDet1","Edep",nbins,0,10);
   TH1F *h6Almu250SciDet2 = new TH1F("h6Almu250SciDet2","Edep",nbins,0,10);
   TH1F *h6Almu250SciDet3 = new TH1F("h6Almu250SciDet3","Edep",nbins,0,60);
   TH1F *h6Almu500SciDet1 = new TH1F("h6Almu500SciDet1","Edep",nbins,0,10);
   TH1F *h6Almu500SciDet2 = new TH1F("h6Almu500SciDet2","Edep",nbins,0,10);
   TH1F *h6Almu500SciDet3 = new TH1F("h6Almu500SciDet3","Edep",nbins,0,60);
   TH1F *h6Almu750SciDet1 = new TH1F("h6Almu750SciDet1","Edep",nbins,0,10);
   TH1F *h6Almu750SciDet2 = new TH1F("h6Almu750SciDet2","Edep",nbins,0,10);
   TH1F *h6Almu750SciDet3 = new TH1F("h6Almu750SciDet3","Edep",nbins,0,60);
   TH1F *h6Alx250SciDet1 = new TH1F("h6Alx250SciDet1","Edep",nbins,0,6);
   TH1F *h6Alx250SciDet2 = new TH1F("h6Alx250SciDet2","Edep",nbins,0,6);
   TH1F *h6Alx250SciDet3 = new TH1F("h6Alx250SciDet3","Edep",nbins,0,12);
   TH1F *h6Alx500SciDet1 = new TH1F("h6Alx500SciDet1","Edep",nbins,0,6);
   TH1F *h6Alx500SciDet2 = new TH1F("h6Alx500SciDet2","Edep",nbins,0,6);
   TH1F *h6Alx500SciDet3 = new TH1F("h6Alx500SciDet3","Edep",nbins,0,12);
   TH1F *h6Alx750SciDet1 = new TH1F("h6Alx750SciDet1","Edep",nbins,0,6);
   TH1F *h6Alx750SciDet2 = new TH1F("h6Alx750SciDet2","Edep",nbins,0,6);
   TH1F *h6Alx750SciDet3 = new TH1F("h6Alx750SciDet3","Edep",nbins,0,12);
   // 6-mm Al [copies]
   TH1F *h6Almu250SciDet1n = new TH1F("h6Almu250SciDet1n","Edep",nbins,0,9);
   TH1F *h6Almu250SciDet2n = new TH1F("h6Almu250SciDet2n","Edep",nbins,0,9);
   TH1F *h6Almu250SciDet3n = new TH1F("h6Almu250SciDet3n","Edep",nbins,0,50);
   TH1F *h6Almu500SciDet1n = new TH1F("h6Almu500SciDet1n","Edep",nbins,0,9);
   TH1F *h6Almu500SciDet2n = new TH1F("h6Almu500SciDet2n","Edep",nbins,0,9);
   TH1F *h6Almu500SciDet3n = new TH1F("h6Almu500SciDet3n","Edep",nbins,0,50);
   TH1F *h6Almu750SciDet1n = new TH1F("h6Almu750SciDet1n","Edep",nbins,0,9);
   TH1F *h6Almu750SciDet2n = new TH1F("h6Almu750SciDet2n","Edep",nbins,0,9);
   TH1F *h6Almu750SciDet3n = new TH1F("h6Almu750SciDet3n","Edep",nbins,0,50);
   TH1F *h6Alx250SciDet1n = new TH1F("h6Alx250SciDet1n","Edep",nbins,0,9);
   TH1F *h6Alx250SciDet2n = new TH1F("h6Alx250SciDet2n","Edep",nbins,0,9);
   TH1F *h6Alx250SciDet3n = new TH1F("h6Alx250SciDet3n","Edep",nbins,0,50);
   TH1F *h6Alx500SciDet1n = new TH1F("h6Alx500SciDet1n","Edep",nbins,0,9);
   TH1F *h6Alx500SciDet2n = new TH1F("h6Alx500SciDet2n","Edep",nbins,0,9);
   TH1F *h6Alx500SciDet3n = new TH1F("h6Alx500SciDet3n","Edep",nbins,0,50);
   TH1F *h6Alx750SciDet1n = new TH1F("h6Alx750SciDet1n","Edep",nbins,0,9);
   TH1F *h6Alx750SciDet2n = new TH1F("h6Alx750SciDet2n","Edep",nbins,0,9);
   TH1F *h6Alx750SciDet3n = new TH1F("h6Alx750SciDet3n","Edep",nbins,0,50);
     
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
   // 3-mm Al [copies]
   tmu250SciDet1->Draw("Edep>>hmu250SciDet1n","","");
   tmu250SciDet2->Draw("Edep>>hmu250SciDet2n","","");
   tmu250SciDet3->Draw("Edep>>hmu250SciDet3n","","");
   tmu500SciDet1->Draw("Edep>>hmu500SciDet1n","","");
   tmu500SciDet2->Draw("Edep>>hmu500SciDet2n","","");
   tmu500SciDet3->Draw("Edep>>hmu500SciDet3n","","");
   tmu750SciDet1->Draw("Edep>>hmu750SciDet1n","","");
   tmu750SciDet2->Draw("Edep>>hmu750SciDet2n","","");
   tmu750SciDet3->Draw("Edep>>hmu750SciDet3n","","");
   tx250SciDet1->Draw("Edep>>hx250SciDet1n","","");
   tx250SciDet2->Draw("Edep>>hx250SciDet2n","","");
   tx250SciDet3->Draw("Edep>>hx250SciDet3n","","");
   tx500SciDet1->Draw("Edep>>hx500SciDet1n","","");
   tx500SciDet2->Draw("Edep>>hx500SciDet2n","","");
   tx500SciDet3->Draw("Edep>>hx500SciDet3n","","");
   tx750SciDet1->Draw("Edep>>hx750SciDet1n","","");
   tx750SciDet2->Draw("Edep>>hx750SciDet2n","","");
   tx750SciDet3->Draw("Edep>>hx750SciDet3n","","");
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
   // 6-mm Al [copies]
   t6Almu250SciDet1->Draw("Edep>>h6Almu250SciDet1n","","");
   t6Almu250SciDet2->Draw("Edep>>h6Almu250SciDet2n","","");
   t6Almu250SciDet3->Draw("Edep>>h6Almu250SciDet3n","","");
   t6Almu500SciDet1->Draw("Edep>>h6Almu500SciDet1n","","");
   t6Almu500SciDet2->Draw("Edep>>h6Almu500SciDet2n","","");
   t6Almu500SciDet3->Draw("Edep>>h6Almu500SciDet3n","","");
   t6Almu750SciDet1->Draw("Edep>>h6Almu750SciDet1n","","");
   t6Almu750SciDet2->Draw("Edep>>h6Almu750SciDet2n","","");
   t6Almu750SciDet3->Draw("Edep>>h6Almu750SciDet3n","","");
   t6Alx250SciDet1->Draw("Edep>>h6Alx250SciDet1n","","");
   t6Alx250SciDet2->Draw("Edep>>h6Alx250SciDet2n","","");
   t6Alx250SciDet3->Draw("Edep>>h6Alx250SciDet3n","","");
   t6Alx500SciDet1->Draw("Edep>>h6Alx500SciDet1n","","");
   t6Alx500SciDet2->Draw("Edep>>h6Alx500SciDet2n","","");
   t6Alx500SciDet3->Draw("Edep>>h6Alx500SciDet3n","","");
   t6Alx750SciDet1->Draw("Edep>>h6Alx750SciDet1n","","");
   t6Alx750SciDet2->Draw("Edep>>h6Alx750SciDet2n","","");
   t6Alx750SciDet3->Draw("Edep>>h6Alx750SciDet3n","","");
  
  
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
   hx250SciDet1->SetLineColor(kBlack);
   hx250SciDet2->SetLineColor(kBlack);
   hx250SciDet3->SetLineColor(kBlack);
   hx500SciDet1->SetLineColor(kBlack);
   hx500SciDet2->SetLineColor(kBlack);
   hx500SciDet3->SetLineColor(kBlack);
   hx750SciDet1->SetLineColor(kBlack);
   hx750SciDet2->SetLineColor(kBlack);
   hx750SciDet3->SetLineColor(kBlack);
   // 3-mm Al [copies]
   hmu250SciDet1n->SetLineColor(kBlack);
   hmu250SciDet2n->SetLineColor(kBlack);
   hmu250SciDet3n->SetLineColor(kBlack);
   hmu500SciDet1n->SetLineColor(kBlack);
   hmu500SciDet2n->SetLineColor(kBlack);
   hmu500SciDet3n->SetLineColor(kBlack);
   hmu750SciDet1n->SetLineColor(kBlack);
   hmu750SciDet2n->SetLineColor(kBlack);
   hmu750SciDet3n->SetLineColor(kBlack);
   hx250SciDet1n->SetLineColor(kRed);
   hx250SciDet2n->SetLineColor(kRed);
   hx250SciDet3n->SetLineColor(kRed);
   hx500SciDet1n->SetLineColor(kRed);
   hx500SciDet2n->SetLineColor(kRed);
   hx500SciDet3n->SetLineColor(kRed);
   hx750SciDet1n->SetLineColor(kRed);
   hx750SciDet2n->SetLineColor(kRed);
   hx750SciDet3n->SetLineColor(kRed);
   // 6-mm Al
   h6Almu250SciDet1->SetLineColor(kGreen-2);
   h6Almu250SciDet2->SetLineColor(kGreen-2);
   h6Almu250SciDet3->SetLineColor(kGreen-2);
   h6Almu500SciDet1->SetLineColor(kGreen-2);
   h6Almu500SciDet2->SetLineColor(kGreen-2);
   h6Almu500SciDet3->SetLineColor(kGreen-2);
   h6Almu750SciDet1->SetLineColor(kGreen-2);
   h6Almu750SciDet2->SetLineColor(kGreen-2);
   h6Almu750SciDet3->SetLineColor(kGreen-2);
   h6Alx250SciDet1->SetLineColor(kGreen-2);
   h6Alx250SciDet2->SetLineColor(kGreen-2);
   h6Alx250SciDet3->SetLineColor(kGreen-2);
   h6Alx500SciDet1->SetLineColor(kGreen-2);
   h6Alx500SciDet2->SetLineColor(kGreen-2);
   h6Alx500SciDet3->SetLineColor(kGreen-2);
   h6Alx750SciDet1->SetLineColor(kGreen-2);
   h6Alx750SciDet2->SetLineColor(kGreen-2);
   h6Alx750SciDet3->SetLineColor(kGreen-2);
   // 6-mm Al [copies]
   h6Almu250SciDet1n->SetLineColor(kBlack);
   h6Almu250SciDet2n->SetLineColor(kBlack);
   h6Almu250SciDet3n->SetLineColor(kBlack);
   h6Almu500SciDet1n->SetLineColor(kBlack);
   h6Almu500SciDet2n->SetLineColor(kBlack);
   h6Almu500SciDet3n->SetLineColor(kBlack);
   h6Almu750SciDet1n->SetLineColor(kBlack);
   h6Almu750SciDet2n->SetLineColor(kBlack);
   h6Almu750SciDet3n->SetLineColor(kBlack);
   h6Alx250SciDet1n->SetLineColor(kRed);
   h6Alx250SciDet2n->SetLineColor(kRed);
   h6Alx250SciDet3n->SetLineColor(kRed);
   h6Alx500SciDet1n->SetLineColor(kRed);
   h6Alx500SciDet2n->SetLineColor(kRed);
   h6Alx500SciDet3n->SetLineColor(kRed);
   h6Alx750SciDet1n->SetLineColor(kRed);
   h6Alx750SciDet2n->SetLineColor(kRed);
   h6Alx750SciDet3n->SetLineColor(kRed);
 
 
   /********************************/
   /*           Plotting           */
   /********************************/

   // Mu-decay: 3-mm/ 6-mm Al 250-mm/ 500-mm/ 750-mm SciD3
   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(3,3);
   c->cd(1);
   gPad->SetLogy();
   hmu250SciDet1->SetTitle("Mu-decay: 5-mm SciD_{1} with 3-mm/6-mm Al [250-mm SciD_{3}]");
   hmu250SciDet1->GetXaxis()->SetTitle("Edep [MeV]");
   hmu250SciDet1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu250SciDet1->GetYaxis()->SetTitleOffset(2.0);
   hmu250SciDet1->Draw();
   c->Update();
   TPaveStats *stmu250SciDet1 = (TPaveStats*)hmu250SciDet1->GetListOfFunctions()->FindObject("stats");
   stmu250SciDet1->SetY1NDC(0.63); stmu250SciDet1->SetY2NDC(0.78);
   h6Almu250SciDet1->Draw("sames");
   c->Update();
   TPaveStats *st6Almu250SciDet1 = (TPaveStats*)h6Almu250SciDet1->GetListOfFunctions()->FindObject("stats");
   st6Almu250SciDet1->SetTextColor(kGreen-2);
   st6Almu250SciDet1->Draw();

   c->cd(2);
   gPad->SetLogy();
   hmu250SciDet2->SetTitle("Mu-decay: 5-mm SciD_{2} with 3-mm/6-mm Al [250-mm SciD_{3}]");
   hmu250SciDet2->GetXaxis()->SetTitle("Edep [MeV]");
   hmu250SciDet2->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu250SciDet2->GetYaxis()->SetTitleOffset(2.0);
   hmu250SciDet2->Draw();
   c->Update();
   TPaveStats *stmu250SciDet2 = (TPaveStats*)hmu250SciDet2->GetListOfFunctions()->FindObject("stats");
   stmu250SciDet2->SetY1NDC(0.63); stmu250SciDet2->SetY2NDC(0.78);
   h6Almu250SciDet2->Draw("sames");
   c->Update();
   TPaveStats *st6Almu250SciDet2 = (TPaveStats*)h6Almu250SciDet2->GetListOfFunctions()->FindObject("stats");
   st6Almu250SciDet2->SetTextColor(kGreen-2);
   st6Almu250SciDet2->Draw();

   c->cd(3);
   gPad->SetLogy();
   hmu250SciDet3->SetTitle("Mu-decay: 5-mm SciD_{3} with 3-mm/6-mm Al [250-mm SciD_{4}]");
   hmu250SciDet3->GetXaxis()->SetTitle("Edep [MeV]");
   hmu250SciDet3->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu250SciDet3->GetYaxis()->SetTitleOffset(2.0);
   hmu250SciDet3->Draw();
   c->Update();
   TPaveStats *stmu250SciDet3 = (TPaveStats*)hmu250SciDet3->GetListOfFunctions()->FindObject("stats");
   stmu250SciDet3->SetY1NDC(0.63); stmu250SciDet3->SetY2NDC(0.78);
   h6Almu250SciDet3->Draw("sames");
   c->Update();
   TPaveStats *st6Almu250SciDet3 = (TPaveStats*)h6Almu250SciDet3->GetListOfFunctions()->FindObject("stats");
   st6Almu250SciDet3->SetTextColor(kGreen-2);
   st6Almu250SciDet3->Draw();
   
   c->cd(4);
   gPad->SetLogy();
   hmu500SciDet1->SetTitle("Mu-decay: 5-mm SciD_{1} with 3-mm/6-mm Al [500-mm SciD_{3}]");
   hmu500SciDet1->GetXaxis()->SetTitle("Edep [MeV]");
   hmu500SciDet1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu500SciDet1->GetYaxis()->SetTitleOffset(2.0);
   hmu500SciDet1->Draw();
   c->Update();
   TPaveStats *stmu500SciDet1 = (TPaveStats*)hmu500SciDet1->GetListOfFunctions()->FindObject("stats");
   stmu500SciDet1->SetY1NDC(0.63); stmu500SciDet1->SetY2NDC(0.78);
   h6Almu500SciDet1->Draw("sames");
   c->Update();
   TPaveStats *st6Almu500SciDet1 = (TPaveStats*)h6Almu500SciDet1->GetListOfFunctions()->FindObject("stats");
   st6Almu500SciDet1->SetTextColor(kGreen-2);
   st6Almu500SciDet1->Draw();

   c->cd(5);
   gPad->SetLogy();
   hmu500SciDet2->SetTitle("Mu-decay: 5-mm SciD_{2} with 3-mm/6-mm Al [500-mm SciD_{3}]");
   hmu500SciDet2->GetXaxis()->SetTitle("Edep [MeV]");
   hmu500SciDet2->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu500SciDet2->GetYaxis()->SetTitleOffset(2.0);
   hmu500SciDet2->Draw();
   c->Update();
   TPaveStats *stmu500SciDet2 = (TPaveStats*)hmu500SciDet2->GetListOfFunctions()->FindObject("stats");
   stmu500SciDet2->SetY1NDC(0.63); stmu500SciDet2->SetY2NDC(0.78);
   h6Almu500SciDet2->Draw("sames");
   c->Update();
   TPaveStats *st6Almu500SciDet2 = (TPaveStats*)h6Almu500SciDet2->GetListOfFunctions()->FindObject("stats");
   st6Almu500SciDet2->SetTextColor(kGreen-2);
   st6Almu500SciDet2->Draw();

   c->cd(6);
   gPad->SetLogy();
   hmu500SciDet3->SetTitle("Mu-decay: 5-mm SciD_{3} with 3-mm/6-mm Al [500-mm SciD_{4}]");
   hmu500SciDet3->GetXaxis()->SetTitle("Edep [MeV]");
   hmu500SciDet3->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu500SciDet3->GetYaxis()->SetTitleOffset(2.0);
   hmu500SciDet3->Draw();
   c->Update();
   TPaveStats *stmu500SciDet3 = (TPaveStats*)hmu500SciDet3->GetListOfFunctions()->FindObject("stats");
   stmu500SciDet3->SetY1NDC(0.63); stmu500SciDet3->SetY2NDC(0.78);
   h6Almu500SciDet3->Draw("sames");
   c->Update();
   TPaveStats *st6Almu500SciDet3 = (TPaveStats*)h6Almu500SciDet3->GetListOfFunctions()->FindObject("stats");
   st6Almu500SciDet3->SetTextColor(kGreen-2);
   st6Almu500SciDet3->Draw();

   c->cd(7);
   gPad->SetLogy();
   hmu750SciDet1->SetTitle("Mu-decay: 5-mm SciD_{1} with 3-mm/6-mm Al [750-mm SciD_{3}]");
   hmu750SciDet1->GetXaxis()->SetTitle("Edep [MeV]");
   hmu750SciDet1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu750SciDet1->GetYaxis()->SetTitleOffset(2.0);
   hmu750SciDet1->Draw();
   c->Update();
   TPaveStats *stmu750SciDet1 = (TPaveStats*)hmu750SciDet1->GetListOfFunctions()->FindObject("stats");
   stmu750SciDet1->SetY1NDC(0.63); stmu750SciDet1->SetY2NDC(0.78);
   h6Almu750SciDet1->Draw("sames");
   c->Update();
   TPaveStats *st6Almu750SciDet1 = (TPaveStats*)h6Almu750SciDet1->GetListOfFunctions()->FindObject("stats");
   st6Almu750SciDet1->SetTextColor(kGreen-2);
   st6Almu750SciDet1->Draw();

   c->cd(8);
   gPad->SetLogy();
   hmu750SciDet2->SetTitle("Mu-decay: 5-mm SciD_{2} with 3-mm/6-mm Al [750-mm SciD_{3}]");
   hmu750SciDet2->GetXaxis()->SetTitle("Edep [MeV]");
   hmu750SciDet2->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu750SciDet2->GetYaxis()->SetTitleOffset(2.0);
   hmu750SciDet2->Draw();
   c->Update();
   TPaveStats *stmu750SciDet2 = (TPaveStats*)hmu750SciDet2->GetListOfFunctions()->FindObject("stats");
   stmu750SciDet2->SetY1NDC(0.63); stmu750SciDet2->SetY2NDC(0.78);
   h6Almu750SciDet2->Draw("sames");
   c->Update();
   TPaveStats *st6Almu750SciDet2 = (TPaveStats*)h6Almu750SciDet2->GetListOfFunctions()->FindObject("stats");
   st6Almu750SciDet2->SetTextColor(kGreen-2);
   st6Almu750SciDet2->Draw();

   c->cd(9);
   gPad->SetLogy();
   hmu750SciDet3->SetTitle("Mu-decay: 5-mm SciD_{3} with 3-mm/6-mm Al [750-mm SciD_{4}]");
   hmu750SciDet3->GetXaxis()->SetTitle("Edep [MeV]");
   hmu750SciDet3->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu750SciDet3->GetYaxis()->SetTitleOffset(2.0);
   hmu750SciDet3->Draw();
   c->Update();
   TPaveStats *stmu750SciDet3 = (TPaveStats*)hmu750SciDet3->GetListOfFunctions()->FindObject("stats");
   stmu750SciDet3->SetY1NDC(0.63); stmu750SciDet3->SetY2NDC(0.78);
   h6Almu750SciDet3->Draw("sames");
   c->Update();
   TPaveStats *st6Almu750SciDet3 = (TPaveStats*)h6Almu750SciDet3->GetListOfFunctions()->FindObject("stats");
   st6Almu750SciDet3->SetTextColor(kGreen-2);
   st6Almu750SciDet3->Draw();

   c->SaveAs("BubblePlot4_mudecay_3mm_6mm_Al.pdf");
   c->SaveAs("BubblePlot4_mudecay_3mm_6mm_Al.png");
   c->SaveAs("BubblePlot4_mudecay_3mm_6mm_Al.C");



   // X-ray cascade: 3-mm/ 6-mm Al 250-mm/ 500-mm/ 750-mm SciD3
   TCanvas *d = new TCanvas("d","Edep",800,600);
   d->Divide(3,3);
   d->cd(1);
   gPad->SetLogy();
   hx250SciDet1->SetTitle("X-ray cascade: 5-mm SciD_{1} with 3-mm/6-mm Al [250-mm SciD_{3}]");
   hx250SciDet1->GetXaxis()->SetTitle("Edep [MeV]");
   hx250SciDet1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx250SciDet1->GetYaxis()->SetTitleOffset(2.0);
   hx250SciDet1->Draw();
   d->Update();
   TPaveStats *stx250SciDet1 = (TPaveStats*)hx250SciDet1->GetListOfFunctions()->FindObject("stats");
   stx250SciDet1->SetY1NDC(0.63); stx250SciDet1->SetY2NDC(0.78);
   h6Alx250SciDet1->Draw("sames");
   d->Update();
   TPaveStats *st6Alx250SciDet1 = (TPaveStats*)h6Alx250SciDet1->GetListOfFunctions()->FindObject("stats");
   st6Alx250SciDet1->SetTextColor(kGreen-2);
   st6Alx250SciDet1->Draw();

   d->cd(2);
   gPad->SetLogy();
   hx250SciDet2->SetTitle("X-ray cascade: 5-mm SciD_{2} with 3-mm/6-mm Al [250-mm SciD_{3}]");
   hx250SciDet2->GetXaxis()->SetTitle("Edep [MeV]");
   hx250SciDet2->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx250SciDet2->GetYaxis()->SetTitleOffset(2.0);
   hx250SciDet2->Draw();
   d->Update();
   TPaveStats *stx250SciDet2 = (TPaveStats*)hx250SciDet2->GetListOfFunctions()->FindObject("stats");
   stx250SciDet2->SetY1NDC(0.63); stx250SciDet2->SetY2NDC(0.78);
   h6Alx250SciDet2->Draw("sames");
   d->Update();
   TPaveStats *st6Alx250SciDet2 = (TPaveStats*)h6Alx250SciDet2->GetListOfFunctions()->FindObject("stats");
   st6Alx250SciDet2->SetTextColor(kGreen-2);
   st6Alx250SciDet2->Draw();

   d->cd(3);
   gPad->SetLogy();
   hx250SciDet3->SetTitle("X-ray cascade: 5-mm SciD_{3} with 3-mm/6-mm Al [250-mm SciD_{4}]");
   hx250SciDet3->GetXaxis()->SetTitle("Edep [MeV]");
   hx250SciDet3->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx250SciDet3->GetYaxis()->SetTitleOffset(2.0);
   hx250SciDet3->Draw();
   d->Update();
   TPaveStats *stx250SciDet3 = (TPaveStats*)hx250SciDet3->GetListOfFunctions()->FindObject("stats");
   stx250SciDet3->SetY1NDC(0.63); stx250SciDet3->SetY2NDC(0.78);
   h6Alx250SciDet3->Draw("sames");
   d->Update();
   TPaveStats *st6Alx250SciDet3 = (TPaveStats*)h6Alx250SciDet3->GetListOfFunctions()->FindObject("stats");
   st6Alx250SciDet3->SetTextColor(kGreen-2);
   st6Alx250SciDet3->Draw();

   d->cd(4);
   gPad->SetLogy();
   hx500SciDet1->SetTitle("X-ray cascade: 5-mm SciD_{1} with 3-mm/6-mm Al [500-mm SciD_{3}]");
   hx500SciDet1->GetXaxis()->SetTitle("Edep [MeV]");
   hx500SciDet1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx500SciDet1->GetYaxis()->SetTitleOffset(2.0);
   hx500SciDet1->Draw();
   d->Update();
   TPaveStats *stx500SciDet1 = (TPaveStats*)hx500SciDet1->GetListOfFunctions()->FindObject("stats");
   stx500SciDet1->SetY1NDC(0.63); stx500SciDet1->SetY2NDC(0.78);
   h6Alx500SciDet1->Draw("sames");
   d->Update();
   TPaveStats *st6Alx500SciDet1 = (TPaveStats*)h6Alx500SciDet1->GetListOfFunctions()->FindObject("stats");
   st6Alx500SciDet1->SetTextColor(kGreen-2);
   st6Alx500SciDet1->Draw();

   d->cd(5);
   gPad->SetLogy();
   hx500SciDet2->SetTitle("X-ray cascade: 5-mm SciD_{2} with 3-mm/6-mm Al [500-mm SciD_{3}]");
   hx500SciDet2->GetXaxis()->SetTitle("Edep [MeV]");
   hx500SciDet2->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx500SciDet2->GetYaxis()->SetTitleOffset(2.0);
   hx500SciDet2->Draw();
   d->Update();
   TPaveStats *stx500SciDet2 = (TPaveStats*)hx500SciDet2->GetListOfFunctions()->FindObject("stats");
   stx500SciDet2->SetY1NDC(0.63); stx500SciDet2->SetY2NDC(0.78);
   h6Alx500SciDet2->Draw("sames");
   d->Update();
   TPaveStats *st6Alx500SciDet2 = (TPaveStats*)h6Alx500SciDet2->GetListOfFunctions()->FindObject("stats");
   st6Alx500SciDet2->SetTextColor(kGreen-2);
   st6Alx500SciDet2->Draw();

   d->cd(6);
   gPad->SetLogy();
   hx500SciDet3->SetTitle("X-ray cascade: 5-mm SciD_{3} with 3-mm/6-mm Al [500-mm SciD_{4}]");
   hx500SciDet3->GetXaxis()->SetTitle("Edep [MeV]");
   hx500SciDet3->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx500SciDet3->GetYaxis()->SetTitleOffset(2.0);
   hx500SciDet3->Draw();
   d->Update();
   TPaveStats *stx500SciDet3 = (TPaveStats*)hx500SciDet3->GetListOfFunctions()->FindObject("stats");
   stx500SciDet3->SetY1NDC(0.63); stx500SciDet3->SetY2NDC(0.78);
   h6Alx500SciDet3->Draw("sames");
   d->Update();
   TPaveStats *st6Alx500SciDet3 = (TPaveStats*)h6Alx500SciDet3->GetListOfFunctions()->FindObject("stats");
   st6Alx500SciDet3->SetTextColor(kGreen-2);
   st6Alx500SciDet3->Draw();

   d->cd(7);
   gPad->SetLogy();
   hx750SciDet1->SetTitle("X-ray cascade: 5-mm SciD_{1} with 3-mm/6-mm Al [750-mm SciD_{3}]");
   hx750SciDet1->GetXaxis()->SetTitle("Edep [MeV]");
   hx750SciDet1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx750SciDet1->GetYaxis()->SetTitleOffset(2.0);
   hx750SciDet1->Draw();
   d->Update();
   TPaveStats *stx750SciDet1 = (TPaveStats*)hx750SciDet1->GetListOfFunctions()->FindObject("stats");
   stx750SciDet1->SetY1NDC(0.63); stx750SciDet1->SetY2NDC(0.78);
   h6Alx750SciDet1->Draw("sames");
   d->Update();
   TPaveStats *st6Alx750SciDet1 = (TPaveStats*)h6Alx750SciDet1->GetListOfFunctions()->FindObject("stats");
   st6Alx750SciDet1->SetTextColor(kGreen-2);
   st6Alx750SciDet1->Draw();

   d->cd(8);
   gPad->SetLogy();
   hx750SciDet2->SetTitle("X-ray cascade: 5-mm SciD_{2} with 3-mm/6-mm Al [750-mm SciD_{3}]");
   hx750SciDet2->GetXaxis()->SetTitle("Edep [MeV]");
   hx750SciDet2->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx750SciDet2->GetYaxis()->SetTitleOffset(2.0);
   hx750SciDet2->Draw();
   d->Update();
   TPaveStats *stx750SciDet2 = (TPaveStats*)hx750SciDet2->GetListOfFunctions()->FindObject("stats");
   stx750SciDet2->SetY1NDC(0.63); stx750SciDet2->SetY2NDC(0.78);
   h6Alx750SciDet2->Draw("sames");
   d->Update();
   TPaveStats *st6Alx750SciDet2 = (TPaveStats*)h6Alx750SciDet2->GetListOfFunctions()->FindObject("stats");
   st6Alx750SciDet2->SetTextColor(kGreen-2);
   st6Alx750SciDet2->Draw();

   d->cd(9);
   gPad->SetLogy();
   hx750SciDet3->SetTitle("X-ray cascade: 5-mm SciD_{3} with 3-mm/6-mm Al [750-mm SciD_{4}]");
   hx750SciDet3->GetXaxis()->SetTitle("Edep [MeV]");
   hx750SciDet3->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx750SciDet3->GetYaxis()->SetTitleOffset(2.0);
   hx750SciDet3->Draw();
   d->Update();
   TPaveStats *stx750SciDet3 = (TPaveStats*)hx750SciDet3->GetListOfFunctions()->FindObject("stats");
   stx750SciDet3->SetY1NDC(0.63); stx750SciDet3->SetY2NDC(0.78);
   h6Alx750SciDet3->Draw("sames");
   d->Update();
   TPaveStats *st6Alx750SciDet3 = (TPaveStats*)h6Alx750SciDet3->GetListOfFunctions()->FindObject("stats");
   st6Alx750SciDet3->SetTextColor(kGreen-2);
   st6Alx750SciDet3->Draw();

   d->SaveAs("BubblePlot4_goldcascade_3mm_6mm_Al.pdf");
   d->SaveAs("BubblePlot4_goldcascade_3mm_6mm_Al.png");
   d->SaveAs("BubblePlot4_goldcascade_3mm_6mm_Al.C");

 
 
   // X-ray vs mu-decay with 3-mm Al, {250,500,750}-mm SciD3
   TCanvas *e = new TCanvas("e","Edep",800,600);
   e->Divide(3,3);
   e->cd(1);
   gPad->SetLogy();
   hx250SciDet1n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{1} with 3-mm Al [250-mm SciD_{3}]");
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
   hx250SciDet2n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{2} with 3-mm Al [250-mm SciD_{3}]");
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
   hx250SciDet3n->SetTitle("X-ray cascade vs #mu-decay: 250-mm SciD_{3} with 3-mm Al [250-mm SciD_{3}]");
   hx250SciDet3n->GetXaxis()->SetTitle("Edep [MeV]");
   hx250SciDet3n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx250SciDet3n->GetYaxis()->SetTitleOffset(2.0);
   hx250SciDet3n->Draw();
   e->Update();
   TPaveStats *stx250SciDet3n = (TPaveStats*)hx250SciDet3n->GetListOfFunctions()->FindObject("stats");
   stx250SciDet3n->SetY1NDC(0.63); stx250SciDet3n->SetY2NDC(0.78);
   stx250SciDet3n->SetTextColor(kRed);
   hmu250SciDet3n->Draw("sames");
   e->Update();
   TPaveStats *stmu250SciDet3n = (TPaveStats*)hmu250SciDet3n->GetListOfFunctions()->FindObject("stats");
   stmu250SciDet3n->Draw();

   e->cd(4);
   gPad->SetLogy();
   hx500SciDet1n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{1} with 3-mm Al [500-mm SciD_{3}]");
   hx500SciDet1n->GetXaxis()->SetTitle("Edep [MeV]");
   hx500SciDet1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx500SciDet1n->GetYaxis()->SetTitleOffset(2.0);
   hx500SciDet1n->Draw();
   e->Update();
   TPaveStats *stx500SciDet1n = (TPaveStats*)hx500SciDet1n->GetListOfFunctions()->FindObject("stats");
   stx500SciDet1n->SetY1NDC(0.63); stx500SciDet1n->SetY2NDC(0.78);
   stx500SciDet1n->SetTextColor(kRed);
   hmu500SciDet1n->Draw("sames");
   e->Update();
   TPaveStats *stmu500SciDet1n = (TPaveStats*)hmu500SciDet1n->GetListOfFunctions()->FindObject("stats");
   stmu500SciDet1n->Draw();

   e->cd(5);
   gPad->SetLogy();
   hx500SciDet2n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{2} with 3-mm Al [500-mm SciD_{3}]");
   hx500SciDet2n->GetXaxis()->SetTitle("Edep [MeV]");
   hx500SciDet2n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx500SciDet2n->GetYaxis()->SetTitleOffset(2.0);
   hx500SciDet2n->Draw();
   e->Update();
   TPaveStats *stx500SciDet2n = (TPaveStats*)hx500SciDet2n->GetListOfFunctions()->FindObject("stats");
   stx500SciDet2n->SetY1NDC(0.63); stx500SciDet2n->SetY2NDC(0.78);
   stx500SciDet2n->SetTextColor(kRed);
   hmu500SciDet2n->Draw("sames");
   e->Update();
   TPaveStats *stmu500SciDet2n = (TPaveStats*)hmu500SciDet2n->GetListOfFunctions()->FindObject("stats");
   stmu500SciDet2n->Draw();

   e->cd(6);
   gPad->SetLogy();
   hx500SciDet3n->SetTitle("X-ray cascade vs #mu-decay: 500-mm SciD_{3} with 3-mm Al [500-mm SciD_{3}]");
   hx500SciDet3n->GetXaxis()->SetTitle("Edep [MeV]");
   hx500SciDet3n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx500SciDet3n->GetYaxis()->SetTitleOffset(2.0);
   hx500SciDet3n->Draw();
   e->Update();
   TPaveStats *stx500SciDet3n = (TPaveStats*)hx500SciDet3n->GetListOfFunctions()->FindObject("stats");
   stx500SciDet3n->SetY1NDC(0.63); stx500SciDet3n->SetY2NDC(0.78);
   stx500SciDet3n->SetTextColor(kRed);
   hmu500SciDet3n->Draw("sames");
   e->Update();
   TPaveStats *stmu500SciDet3n = (TPaveStats*)hmu500SciDet3n->GetListOfFunctions()->FindObject("stats");
   stmu500SciDet3n->Draw();
   
   e->cd(7);
   gPad->SetLogy();
   hx750SciDet1n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{1} with 3-mm Al [750-mm SciD_{3}]");
   hx750SciDet1n->GetXaxis()->SetTitle("Edep [MeV]");
   hx750SciDet1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx750SciDet1n->GetYaxis()->SetTitleOffset(2.0);
   hx750SciDet1n->Draw();
   e->Update();
   TPaveStats *stx750SciDet1n = (TPaveStats*)hx750SciDet1n->GetListOfFunctions()->FindObject("stats");
   stx750SciDet1n->SetY1NDC(0.63); stx750SciDet1n->SetY2NDC(0.78);
   stx750SciDet1n->SetTextColor(kRed);
   hmu750SciDet1n->Draw("sames");
   e->Update();
   TPaveStats *stmu750SciDet1n = (TPaveStats*)hmu750SciDet1n->GetListOfFunctions()->FindObject("stats");
   stmu750SciDet1n->Draw();

   e->cd(8);
   gPad->SetLogy();
   hx750SciDet2n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{2} with 3-mm Al [750-mm SciD_{3}]");
   hx750SciDet2n->GetXaxis()->SetTitle("Edep [MeV]");
   hx750SciDet2n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx750SciDet2n->GetYaxis()->SetTitleOffset(2.0);
   hx750SciDet2n->Draw();
   e->Update();
   TPaveStats *stx750SciDet2n = (TPaveStats*)hx750SciDet2n->GetListOfFunctions()->FindObject("stats");
   stx750SciDet2n->SetY1NDC(0.63); stx750SciDet2n->SetY2NDC(0.78);
   stx750SciDet2n->SetTextColor(kRed);
   hmu750SciDet2n->Draw("sames");
   e->Update();
   TPaveStats *stmu750SciDet2n = (TPaveStats*)hmu750SciDet2n->GetListOfFunctions()->FindObject("stats");
   stmu750SciDet2n->Draw();

   e->cd(9);
   gPad->SetLogy();
   hx750SciDet3n->SetTitle("X-ray cascade vs #mu-decay: 750-mm SciD_{3} with 3-mm Al [750-mm SciD_{3}]");
   hx750SciDet3n->GetXaxis()->SetTitle("Edep [MeV]");
   hx750SciDet3n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx750SciDet3n->GetYaxis()->SetTitleOffset(2.0);
   hx750SciDet3n->Draw();
   e->Update();
   TPaveStats *stx750SciDet3n = (TPaveStats*)hx750SciDet3n->GetListOfFunctions()->FindObject("stats");
   stx750SciDet3n->SetY1NDC(0.63); stx750SciDet3n->SetY2NDC(0.78);
   stx750SciDet3n->SetTextColor(kRed);
   hmu750SciDet3n->Draw("sames");
   e->Update();
   TPaveStats *stmu750SciDet3n = (TPaveStats*)hmu750SciDet3n->GetListOfFunctions()->FindObject("stats");
   stmu750SciDet3n->Draw();
   
   e->SaveAs("BubblePlot4_muX_3mm_Al.pdf");
   e->SaveAs("BubblePlot4_muX_3mm_Al.png");
   e->SaveAs("BubblePlot4_muX_3mm_Al.C");
   
   
   
   // X-ray vs mu-decay with 6-mm Al, {250,500,750}-mm SciD3
   TCanvas *f = new TCanvas("f","Edep",800,600);
   f->Divide(3,3);
   f->cd(1);
   gPad->SetLogy();
   h6Alx250SciDet1n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{1} with 6-mm Al [250-mm SciD_{3}]");
   h6Alx250SciDet1n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx250SciDet1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx250SciDet1n->GetYaxis()->SetTitleOffset(2.0);
   h6Alx250SciDet1n->Draw();
   f->Update();
   TPaveStats *st6Alx250SciDet1n = (TPaveStats*)h6Alx250SciDet1n->GetListOfFunctions()->FindObject("stats");
   st6Alx250SciDet1n->SetY1NDC(0.63); st6Alx250SciDet1n->SetY2NDC(0.78);
   st6Alx250SciDet1n->SetTextColor(kRed);
   h6Almu250SciDet1n->Draw("sames");
   f->Update();
   TPaveStats *st6Almu250SciDet1n = (TPaveStats*)h6Almu250SciDet1n->GetListOfFunctions()->FindObject("stats");
   st6Almu250SciDet1n->Draw();

   f->cd(2);
   gPad->SetLogy();
   h6Alx250SciDet2n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{2} with 6-mm Al [250-mm SciD_{3}]");
   h6Alx250SciDet2n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx250SciDet2n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx250SciDet2n->GetYaxis()->SetTitleOffset(2.0);
   h6Alx250SciDet2n->Draw();
   f->Update();
   TPaveStats *st6Alx250SciDet2n = (TPaveStats*)h6Alx250SciDet2n->GetListOfFunctions()->FindObject("stats");
   st6Alx250SciDet2n->SetY1NDC(0.63); st6Alx250SciDet2n->SetY2NDC(0.78);
   st6Alx250SciDet2n->SetTextColor(kRed);
   h6Almu250SciDet2n->Draw("sames");
   f->Update();
   TPaveStats *st6Almu250SciDet2n = (TPaveStats*)h6Almu250SciDet2n->GetListOfFunctions()->FindObject("stats");
   st6Almu250SciDet2n->Draw();

   f->cd(3);
   gPad->SetLogy();
   h6Alx250SciDet3n->SetTitle("X-ray cascade vs #mu-decay: 250-mm SciD_{3} with 6-mm Al [250-mm SciD_{3}]");
   h6Alx250SciDet3n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx250SciDet3n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx250SciDet3n->GetYaxis()->SetTitleOffset(2.0);
   h6Alx250SciDet3n->Draw();
   f->Update();
   TPaveStats *st6Alx250SciDet3n = (TPaveStats*)h6Alx250SciDet3n->GetListOfFunctions()->FindObject("stats");
   st6Alx250SciDet3n->SetY1NDC(0.63); st6Alx250SciDet3n->SetY2NDC(0.78);
   st6Alx250SciDet3n->SetTextColor(kRed);
   h6Almu250SciDet3n->Draw("sames");
   f->Update();
   TPaveStats *st6Almu250SciDet3n = (TPaveStats*)h6Almu250SciDet3n->GetListOfFunctions()->FindObject("stats");
   st6Almu250SciDet3n->Draw();

   f->cd(4);
   gPad->SetLogy();
   h6Alx500SciDet1n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{1} with 6-mm Al [500-mm SciD_{3}]");
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
   h6Alx500SciDet2n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{2} with 6-mm Al [500-mm SciD_{3}]");
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
   h6Alx500SciDet3n->SetTitle("X-ray cascade vs #mu-decay: 500-mm SciD_{3} with 6-mm Al [500-mm SciD_{3}]");
   h6Alx500SciDet3n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx500SciDet3n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx500SciDet3n->GetYaxis()->SetTitleOffset(2.0);
   h6Alx500SciDet3n->Draw();
   f->Update();
   TPaveStats *st6Alx500SciDet3n = (TPaveStats*)h6Alx500SciDet3n->GetListOfFunctions()->FindObject("stats");
   st6Alx500SciDet3n->SetY1NDC(0.63); st6Alx500SciDet3n->SetY2NDC(0.78);
   st6Alx500SciDet3n->SetTextColor(kRed);
   h6Almu500SciDet3n->Draw("sames");
   f->Update();
   TPaveStats *st6Almu500SciDet3n = (TPaveStats*)h6Almu500SciDet3n->GetListOfFunctions()->FindObject("stats");
   st6Almu500SciDet3n->Draw();
   
   f->cd(7);
   gPad->SetLogy();
   h6Alx750SciDet1n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{1} with 6-mm Al [750-mm SciD_{3}]");
   h6Alx750SciDet1n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx750SciDet1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx750SciDet1n->GetYaxis()->SetTitleOffset(2.0);
   h6Alx750SciDet1n->Draw();
   f->Update();
   TPaveStats *st6Alx750SciDet1n = (TPaveStats*)h6Alx750SciDet1n->GetListOfFunctions()->FindObject("stats");
   st6Alx750SciDet1n->SetY1NDC(0.63); st6Alx750SciDet1n->SetY2NDC(0.78);
   st6Alx750SciDet1n->SetTextColor(kRed);
   h6Almu750SciDet1n->Draw("sames");
   f->Update();
   TPaveStats *st6Almu750SciDet1n = (TPaveStats*)h6Almu750SciDet1n->GetListOfFunctions()->FindObject("stats");
   st6Almu750SciDet1n->Draw();

   f->cd(8);
   gPad->SetLogy();
   h6Alx750SciDet2n->SetTitle("X-ray cascade vs #mu-decay: 5-mm SciD_{2} with 6-mm Al [750-mm SciD_{3}]");
   h6Alx750SciDet2n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx750SciDet2n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx750SciDet2n->GetYaxis()->SetTitleOffset(2.0);
   h6Alx750SciDet2n->Draw();
   f->Update();
   TPaveStats *st6Alx750SciDet2n = (TPaveStats*)h6Alx750SciDet2n->GetListOfFunctions()->FindObject("stats");
   st6Alx750SciDet2n->SetY1NDC(0.63); st6Alx750SciDet2n->SetY2NDC(0.78);
   st6Alx750SciDet2n->SetTextColor(kRed);
   h6Almu750SciDet2n->Draw("sames");
   f->Update();
   TPaveStats *st6Almu750SciDet2n = (TPaveStats*)h6Almu750SciDet2n->GetListOfFunctions()->FindObject("stats");
   st6Almu750SciDet2n->Draw();

   f->cd(9);
   gPad->SetLogy();
   h6Alx750SciDet3n->SetTitle("X-ray cascade vs #mu-decay: 750-mm SciD_{3} with 6-mm Al [750-mm SciD_{3}]");
   h6Alx750SciDet3n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Alx750SciDet3n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Alx750SciDet3n->GetYaxis()->SetTitleOffset(2.0);
   h6Alx750SciDet3n->Draw();
   f->Update();
   TPaveStats *st6Alx750SciDet3n = (TPaveStats*)h6Alx750SciDet3n->GetListOfFunctions()->FindObject("stats");
   st6Alx750SciDet3n->SetY1NDC(0.63); st6Alx750SciDet3n->SetY2NDC(0.78);
   st6Alx750SciDet3n->SetTextColor(kRed);
   h6Almu750SciDet3n->Draw("sames");
   f->Update();
   TPaveStats *st6Almu750SciDet3n = (TPaveStats*)h6Almu750SciDet3n->GetListOfFunctions()->FindObject("stats");
   st6Almu750SciDet3n->Draw();
   
   f->SaveAs("BubblePlot4_muX_6mm_Al.pdf");
   f->SaveAs("BubblePlot4_muX_6mm_Al.png");
   f->SaveAs("BubblePlot4_muX_6mm_Al.C");



}


int main() {
   bubble4();
   return 0;
}
