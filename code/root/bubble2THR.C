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

void bubble2THR(){

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
   // With 0-mm Al layer
   std::string filemu1 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6mudecay1.root";
   std::string filemu2 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6mudecay2.root";
   std::string filemu3 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6mudecay3.root";
   std::string filemu5 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6mudecay5.root";
   std::string filemu10 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6mudecay10.root";
   std::string filemu20 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6mudecay20.root";
   std::string filex1 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6goldcascade1.root";
   std::string filex2 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6goldcascade2.root";
   std::string filex3 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6goldcascade3.root";
   std::string filex5 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6goldcascade5.root";
   std::string filex10 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6goldcascade10.root";
   std::string filex20 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6goldcascade20.root";
   // With a 3-mm Al layer
   std::string fileAlmu1 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay1.root";
   std::string fileAlmu2 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay2.root";
   std::string fileAlmu3 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay3.root";
   std::string fileAlmu5 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay5.root";
   std::string fileAlmu10 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay10.root";
   std::string fileAlmu20 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay20.root";
   std::string fileAlx1 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade1.root";
   std::string fileAlx2 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade2.root";
   std::string fileAlx3 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade3.root";
   std::string fileAlx5 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade5.root";
   std::string fileAlx10 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade10.root";
   std::string fileAlx20 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade20.root"; 

   /*********************************/
   /*           Analysis            */
   /*********************************/

   const int nbins = 150;
  
   // 0-mm Al layer 
   TFile* fmu1 = new TFile(TString(filemu1));
   TFile* fmu2 = new TFile(TString(filemu2));
   TFile* fmu3 = new TFile(TString(filemu3));
   TFile* fmu5 = new TFile(TString(filemu5));
   TFile* fmu10 = new TFile(TString(filemu10));
   TFile* fmu20 = new TFile(TString(filemu20));
   TFile* fx1 = new TFile(TString(filex1));
   TFile* fx2 = new TFile(TString(filex2));
   TFile* fx3 = new TFile(TString(filex3));
   TFile* fx5 = new TFile(TString(filex5));
   TFile* fx10 = new TFile(TString(filex10));
   TFile* fx20 = new TFile(TString(filex20));
   // 3-mm Al layer
   TFile* fAlmu1 = new TFile(TString(fileAlmu1));
   TFile* fAlmu2 = new TFile(TString(fileAlmu2));
   TFile* fAlmu3 = new TFile(TString(fileAlmu3));
   TFile* fAlmu5 = new TFile(TString(fileAlmu5));
   TFile* fAlmu10 = new TFile(TString(fileAlmu10));
   TFile* fAlmu20 = new TFile(TString(fileAlmu20));
   TFile* fAlx1 = new TFile(TString(fileAlx1));
   TFile* fAlx2 = new TFile(TString(fileAlx2));
   TFile* fAlx3 = new TFile(TString(fileAlx3));
   TFile* fAlx5 = new TFile(TString(fileAlx5));
   TFile* fAlx10 = new TFile(TString(fileAlx10));
   TFile* fAlx20 = new TFile(TString(fileAlx20));

   // 0-mm Al layer
   TH1F *hmu1 = new TH1F("hmu1","Edep",3*nbins,0,45);
   TH1F *hmu2 = new TH1F("hmu2","Edep",3*nbins,0,45);
   TH1F *hmu3 = new TH1F("hmu3","Edep",3*nbins,0,45);
   TH1F *hmu5 = new TH1F("hmu5","Edep",3*nbins,0,45);
   TH1F *hmu10 = new TH1F("hmu10","Edep",3*nbins,0,45);
   TH1F *hmu20 = new TH1F("hmu20","Edep",3*nbins,0,45);
   TH1F *hx1 = new TH1F("hx1","Edep",nbins,0,15);
   TH1F *hx2 = new TH1F("hx2","Edep",nbins,0,15);
   TH1F *hx3 = new TH1F("hx3","Edep",nbins,0,15);
   TH1F *hx5 = new TH1F("hx5","Edep",nbins,0,15);
   TH1F *hx10 = new TH1F("hx10","Edep",nbins,0,15);
   TH1F *hx20 = new TH1F("hx20","Edep",nbins,0,15);
   // 3-mm Al layer
   TH1F *hAlmu1 = new TH1F("hAlmu1","Edep",3*nbins,0,45);
   TH1F *hAlmu2 = new TH1F("hAlmu2","Edep",3*nbins,0,45);
   TH1F *hAlmu3 = new TH1F("hAlmu3","Edep",3*nbins,0,45);
   TH1F *hAlmu5 = new TH1F("hAlmu5","Edep",3*nbins,0,45);
   TH1F *hAlmu10 = new TH1F("hAlmu10","Edep",3*nbins,0,45);
   TH1F *hAlmu20 = new TH1F("hAlmu20","Edep",3*nbins,0,45);
   TH1F *hAlx1 = new TH1F("hAlx1","Edep",nbins,0,15);
   TH1F *hAlx2 = new TH1F("hAlx2","Edep",nbins,0,15);
   TH1F *hAlx3 = new TH1F("hAlx3","Edep",nbins,0,15);
   TH1F *hAlx5 = new TH1F("hAlx5","Edep",nbins,0,15);
   TH1F *hAlx10 = new TH1F("hAlx10","Edep",nbins,0,15);
   TH1F *hAlx20 = new TH1F("hAlx20","Edep",nbins,0,15);
   
   // 0-mm Al layer
   TTree *tmu1 = (TTree*)fmu1->Get("Detector/SciDet");
   TTree *tmu2 = (TTree*)fmu2->Get("Detector/SciDet");
   TTree *tmu3 = (TTree*)fmu3->Get("Detector/SciDet");
   TTree *tmu5 = (TTree*)fmu5->Get("Detector/SciDet");
   TTree *tmu10 = (TTree*)fmu10->Get("Detector/SciDet");
   TTree *tmu20 = (TTree*)fmu20->Get("Detector/SciDet");
   TTree *tx1 = (TTree*)fx1->Get("Detector/SciDet");
   TTree *tx2 = (TTree*)fx2->Get("Detector/SciDet");
   TTree *tx3 = (TTree*)fx3->Get("Detector/SciDet");
   TTree *tx5 = (TTree*)fx5->Get("Detector/SciDet");
   TTree *tx10 = (TTree*)fx10->Get("Detector/SciDet");
   TTree *tx20 = (TTree*)fx20->Get("Detector/SciDet");
   // 3-mm Al layer
   TTree *tAlmu1 = (TTree*)fAlmu1->Get("Detector/SciDet");
   TTree *tAlmu2 = (TTree*)fAlmu2->Get("Detector/SciDet");
   TTree *tAlmu3 = (TTree*)fAlmu3->Get("Detector/SciDet");
   TTree *tAlmu5 = (TTree*)fAlmu5->Get("Detector/SciDet");
   TTree *tAlmu10 = (TTree*)fAlmu10->Get("Detector/SciDet");
   TTree *tAlmu20 = (TTree*)fAlmu20->Get("Detector/SciDet");
   TTree *tAlx1 = (TTree*)fAlx1->Get("Detector/SciDet");
   TTree *tAlx2 = (TTree*)fAlx2->Get("Detector/SciDet");
   TTree *tAlx3 = (TTree*)fAlx3->Get("Detector/SciDet");
   TTree *tAlx5 = (TTree*)fAlx5->Get("Detector/SciDet");
   TTree *tAlx10 = (TTree*)fAlx10->Get("Detector/SciDet");
   TTree *tAlx20 = (TTree*)fAlx20->Get("Detector/SciDet"); 
   
   // 0-mm Al layer   
   tmu1->Draw("Edep>>hmu1","","");
   tmu2->Draw("Edep>>hmu2","","");
   tmu3->Draw("Edep>>hmu3","","");
   tmu5->Draw("Edep>>hmu5","","");
   tmu10->Draw("Edep>>hmu10","","");
   tmu20->Draw("Edep>>hmu20","","");
   tx1->Draw("Edep>>hx1","","");
   tx2->Draw("Edep>>hx2","","");
   tx3->Draw("Edep>>hx3","","");
   tx5->Draw("Edep>>hx5","","");
   tx10->Draw("Edep>>hx10","","");
   tx20->Draw("Edep>>hx20","","");
   // 3-mm Al layer
   tAlmu1->Draw("Edep>>hAlmu1","","");
   tAlmu2->Draw("Edep>>hAlmu2","","");
   tAlmu3->Draw("Edep>>hAlmu3","","");
   tAlmu5->Draw("Edep>>hAlmu5","","");
   tAlmu10->Draw("Edep>>hAlmu10","","");
   tAlmu20->Draw("Edep>>hAlmu20","","");
   tAlx1->Draw("Edep>>hAlx1","","");
   tAlx2->Draw("Edep>>hAlx2","","");
   tAlx3->Draw("Edep>>hAlx3","","");
   tAlx5->Draw("Edep>>hAlx5","","");
   tAlx10->Draw("Edep>>hAlx10","","");
   tAlx20->Draw("Edep>>hAlx20","","");
   
   // 0-mm Al layer
   hmu1->SetLineColor(kBlack);
   hmu2->SetLineColor(kBlack);
   hmu3->SetLineColor(kBlack);
   hmu5->SetLineColor(kBlack);
   hmu10->SetLineColor(kBlack);
   hmu20->SetLineColor(kBlack);
   hx1->SetLineColor(kBlack);
   hx2->SetLineColor(kBlack);
   hx3->SetLineColor(kBlack);
   hx5->SetLineColor(kBlack);
   hx10->SetLineColor(kBlack);
   hx20->SetLineColor(kBlack);
   // 3-mm Al layer
   hAlmu1->SetLineColor(kRed);
   hAlmu2->SetLineColor(kRed);
   hAlmu3->SetLineColor(kRed);
   hAlmu5->SetLineColor(kRed);
   hAlmu10->SetLineColor(kRed);
   hAlmu20->SetLineColor(kRed);
   hAlx1->SetLineColor(kRed);
   hAlx2->SetLineColor(kRed);
   hAlx3->SetLineColor(kRed);
   hAlx5->SetLineColor(kRed);
   hAlx10->SetLineColor(kRed);
   hAlx20->SetLineColor(kRed);
   
   float binCentersmu1[nbins] = {};
   float binCentersAlmu1[nbins] = {};
   float binCentersx1[nbins] = {};
   float binCentersAlx1[nbins] = {};
   float binCentersmu2[nbins] = {};
   float binCentersAlmu2[nbins] = {};
   float binCentersx2[nbins] = {};
   float binCentersAlx2[nbins] = {};
   float binCentersmu3[nbins] = {};
   float binCentersAlmu3[nbins] = {};
   float binCentersx3[nbins] = {};
   float binCentersAlx3[nbins] = {};
   float binCentersmu5[nbins] = {};
   float binCentersAlmu5[nbins] = {};
   float binCentersx5[nbins] = {};
   float binCentersAlx5[nbins] = {};
   float binCentersmu10[nbins] = {};
   float binCentersAlmu10[nbins] = {};
   float binCentersx10[nbins] = {};
   float binCentersAlx10[nbins] = {};
   float binCentersmu20[nbins] = {};
   float binCentersAlmu20[nbins] = {};
   float binCentersx20[nbins] = {};
   float binCentersAlx20[nbins] = {};

   float integralsmu1[nbins] = {};
   float integralsAlmu1[nbins] = {};
   float integralsx1[nbins] = {};
   float integralsAlx1[nbins] = {};
   float integralsmu2[nbins] = {};
   float integralsAlmu2[nbins] = {};
   float integralsx2[nbins] = {};
   float integralsAlx2[nbins] = {};
   float integralsmu3[nbins] = {};
   float integralsAlmu3[nbins] = {};
   float integralsx3[nbins] = {};
   float integralsAlx3[nbins] = {};
   float integralsmu5[nbins] = {};
   float integralsAlmu5[nbins] = {};
   float integralsx5[nbins] = {};
   float integralsAlx5[nbins] = {};
   float integralsmu10[nbins] = {};
   float integralsAlmu10[nbins] = {};
   float integralsx10[nbins] = {};
   float integralsAlx10[nbins] = {};
   float integralsmu20[nbins] = {};
   float integralsAlmu20[nbins] = {};
   float integralsx20[nbins] = {};
   float integralsAlx20[nbins] = {};

   float binCentermu1, binCenterAlmu1, binCenterx1, binCenterAlx1;
   float integralmu1, integralAlmu1, integralx1, integralAlx1;
   float binCentermu2, binCenterAlmu2, binCenterx2, binCenterAlx2;
   float integralmu2, integralAlmu2, integralx2, integralAlx2;
   float binCentermu3, binCenterAlmu3, binCenterx3, binCenterAlx3;
   float integralmu3, integralAlmu3, integralx3, integralAlx3;
   float binCentermu5, binCenterAlmu5, binCenterx5, binCenterAlx5;
   float integralmu5, integralAlmu5, integralx5, integralAlx5;
   float binCentermu10, binCenterAlmu10, binCenterx10, binCenterAlx10;
   float integralmu10, integralAlmu10, integralx10, integralAlx10;
   float binCentermu20, binCenterAlmu20, binCenterx20, binCenterAlx20;
   float integralmu20, integralAlmu20, integralx20, integralAlx20;
   
   
   // 1-mm SciD
   for (int i=1; i<=nbins; i++) {
	   binCentermu1 = hmu1->GetXaxis()->GetBinCenter(i);
	   binCenterAlmu1 = hAlmu1->GetXaxis()->GetBinCenter(i);
	   binCenterx1 = hx1->GetXaxis()->GetBinCenter(i);
	   binCenterAlx1 = hAlx1->GetXaxis()->GetBinCenter(i);
	   binCentermu2 = hmu2->GetXaxis()->GetBinCenter(i);
	   binCenterAlmu2 = hAlmu2->GetXaxis()->GetBinCenter(i);
	   binCenterx2 = hx2->GetXaxis()->GetBinCenter(i);
	   binCenterAlx2 = hAlx2->GetXaxis()->GetBinCenter(i);
	   binCentermu3 = hmu3->GetXaxis()->GetBinCenter(i);
	   binCenterAlmu3 = hAlmu3->GetXaxis()->GetBinCenter(i);
	   binCenterx3 = hx3->GetXaxis()->GetBinCenter(i);
	   binCenterAlx3 = hAlx3->GetXaxis()->GetBinCenter(i);
	   binCentermu5 = hmu5->GetXaxis()->GetBinCenter(i);
	   binCenterAlmu5 = hAlmu5->GetXaxis()->GetBinCenter(i);
	   binCenterx5 = hx5->GetXaxis()->GetBinCenter(i);
	   binCenterAlx5 = hAlx5->GetXaxis()->GetBinCenter(i);
	   binCentermu10 = hmu10->GetXaxis()->GetBinCenter(i);
	   binCenterAlmu10 = hAlmu10->GetXaxis()->GetBinCenter(i);
	   binCenterx10 = hx10->GetXaxis()->GetBinCenter(i);
	   binCenterAlx10 = hAlx10->GetXaxis()->GetBinCenter(i);
	   binCentermu20 = hmu20->GetXaxis()->GetBinCenter(i);
	   binCenterAlmu20 = hAlmu20->GetXaxis()->GetBinCenter(i);
	   binCenterx20 = hx20->GetXaxis()->GetBinCenter(i);
	   binCenterAlx20 = hAlx20->GetXaxis()->GetBinCenter(i);
	   
	   integralmu1 = hmu1->Integral(0,i+1,""); // includes underflow and overflow bins
	   integralAlmu1 = hAlmu1->Integral(0,i+1,"");
	   integralx1 = hx1->Integral(0,i+1,"");
	   integralAlx1 = hAlx1->Integral(0,i+1,"");
	   integralmu2 = hmu2->Integral(0,i+1,""); // includes underflow and overflow bins
	   integralAlmu2 = hAlmu2->Integral(0,i+1,"");
	   integralx2 = hx2->Integral(0,i+1,"");
	   integralAlx2 = hAlx2->Integral(0,i+1,"");
	   integralmu3 = hmu3->Integral(0,i+1,""); // includes underflow and overflow bins
	   integralAlmu3 = hAlmu3->Integral(0,i+1,"");
	   integralx3 = hx3->Integral(0,i+1,"");
	   integralAlx3 = hAlx3->Integral(0,i+1,"");
	   integralmu5 = hmu5->Integral(0,i+1,""); // includes underflow and overflow bins
	   integralAlmu5 = hAlmu5->Integral(0,i+1,"");
	   integralx5 = hx5->Integral(0,i+1,"");
	   integralAlx5 = hAlx5->Integral(0,i+1,"");
	   integralmu10 = hmu10->Integral(0,i+1,""); // includes underflow and overflow bins
	   integralAlmu10 = hAlmu10->Integral(0,i+1,"");
	   integralx10 = hx10->Integral(0,i+1,"");
	   integralAlx10 = hAlx10->Integral(0,i+1,"");
	   integralmu20 = hmu20->Integral(0,i+1,""); // includes underflow and overflow bins
	   integralAlmu20 = hAlmu20->Integral(0,i+1,"");
	   integralx20 = hx20->Integral(0,i+1,"");
	   integralAlx20 = hAlx20->Integral(0,i+1,"");
	   
       binCentersmu1[(const int)(i-1)] = binCentermu1;
       binCentersAlmu1[(const int)(i-1)] = binCenterAlmu1;
       binCentersx1[(const int)(i-1)] = binCenterx1;
       binCentersAlx1[(const int)(i-1)] = binCenterAlx1;
       binCentersmu2[(const int)(i-1)] = binCentermu2;
       binCentersAlmu2[(const int)(i-1)] = binCenterAlmu2;
       binCentersx2[(const int)(i-1)] = binCenterx2;
       binCentersAlx2[(const int)(i-1)] = binCenterAlx2;
       binCentersmu3[(const int)(i-1)] = binCentermu3;
       binCentersAlmu3[(const int)(i-1)] = binCenterAlmu3;
       binCentersx3[(const int)(i-1)] = binCenterx3;
       binCentersAlx3[(const int)(i-1)] = binCenterAlx3;
       binCentersmu5[(const int)(i-1)] = binCentermu5;
       binCentersAlmu5[(const int)(i-1)] = binCenterAlmu5;
       binCentersx5[(const int)(i-1)] = binCenterx5;
       binCentersAlx5[(const int)(i-1)] = binCenterAlx5;
       binCentersmu10[(const int)(i-1)] = binCentermu10;
       binCentersAlmu10[(const int)(i-1)] = binCenterAlmu10;
       binCentersx10[(const int)(i-1)] = binCenterx10;
       binCentersAlx10[(const int)(i-1)] = binCenterAlx10;
       binCentersmu20[(const int)(i-1)] = binCentermu20;
       binCentersAlmu20[(const int)(i-1)] = binCenterAlmu20;
       binCentersx20[(const int)(i-1)] = binCenterx20;
       binCentersAlx20[(const int)(i-1)] = binCenterAlx20;
       
       integralsmu1[(const int)(i-1)] = integralmu1/(hmu1->GetEntries());
       integralsAlmu1[(const int)(i-1)] = integralAlmu1/(1e6);
       integralsx1[(const int)(i-1)] = integralx1/(hx1->GetEntries());
       integralsAlx1[(const int)(i-1)] = integralAlx1/(hAlx1->GetEntries());
       integralsmu2[(const int)(i-1)] = integralmu2/(hmu2->GetEntries());
       integralsAlmu2[(const int)(i-1)] = integralAlmu2/(1e6);
       integralsx2[(const int)(i-1)] = integralx2/(hx2->GetEntries());
       integralsAlx2[(const int)(i-1)] = integralAlx2/(hAlx2->GetEntries());
       integralsmu3[(const int)(i-1)] = integralmu3/(hmu3->GetEntries());
       integralsAlmu3[(const int)(i-1)] = integralAlmu3/(1e6);
       integralsx3[(const int)(i-1)] = integralx3/(hx3->GetEntries());
       integralsAlx3[(const int)(i-1)] = integralAlx3/(hAlx3->GetEntries());
       integralsmu5[(const int)(i-1)] = integralmu5/(hmu5->GetEntries());
       integralsAlmu5[(const int)(i-1)] = integralAlmu5/(1e6);
       integralsx5[(const int)(i-1)] = integralx5/(hx5->GetEntries());
       integralsAlx5[(const int)(i-1)] = integralAlx5/(hAlx5->GetEntries());
       integralsmu10[(const int)(i-1)] = integralmu10/(hmu10->GetEntries());
       integralsAlmu10[(const int)(i-1)] = integralAlmu10/(1e6);
       integralsx10[(const int)(i-1)] = integralx10/(hx10->GetEntries());
       integralsAlx10[(const int)(i-1)] = integralAlx10/(hAlx10->GetEntries());
       integralsmu20[(const int)(i-1)] = integralmu20/(hmu20->GetEntries());
       integralsAlmu20[(const int)(i-1)] = integralAlmu20/(1e6);
       integralsx20[(const int)(i-1)] = integralx20/(hx20->GetEntries());
       integralsAlx20[(const int)(i-1)] = integralAlx20/(hAlx20->GetEntries());
   }
   



   TCanvas *c = new TCanvas("c","E_{THR}",800,600);
   c->Divide(3,2);
   c->cd(1);
   TGraph *grmu1 = new TGraph(nbins,binCentersmu1,integralsmu1);
   grmu1->SetTitle("1-mm SciD + 0-mm Al");
   grmu1->GetXaxis()->SetTitle("Edep [MeV]");
   grmu1->GetXaxis()->SetRangeUser(0,2);
   grmu1->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu1->GetYaxis()->SetTitleOffset(1.8);
   grmu1->SetMarkerColorAlpha(kBlack,0.35);
   grmu1->SetLineColor(kBlack);
   grmu1->Draw("AC*");
   TGraph *grx1 = new TGraph(nbins,binCentersx1,integralsx1);
   grx1->SetMarkerColor(kRed);
   grx1->SetLineColor(kRed);
   grx1->Draw("C*");
   
   c->cd(2);
   TGraph *grmu2 = new TGraph(nbins,binCentersmu2,integralsmu2);
   grmu2->SetTitle("2-mm SciD + 0-mm Al");
   grmu2->GetXaxis()->SetTitle("Edep [MeV]");
   grmu2->GetXaxis()->SetRangeUser(0,2);
   grmu2->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu2->GetYaxis()->SetTitleOffset(1.8);
   grmu2->SetMarkerColorAlpha(kBlack,0.35);
   grmu2->SetLineColor(kBlack);
   grmu2->Draw("AC*");
   TGraph *grx2 = new TGraph(nbins,binCentersx2,integralsx2);
   grx2->SetMarkerColor(kRed);
   grx2->SetLineColor(kRed);
   grx2->Draw("LC*");

   c->cd(3);
   TGraph *grmu3 = new TGraph(nbins,binCentersmu3,integralsmu3);
   grmu3->SetTitle("3-mm SciD + 0-mm Al");
   grmu3->GetXaxis()->SetTitle("Edep [MeV]");
   grmu3->GetXaxis()->SetRangeUser(0,2);
   grmu3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu3->GetYaxis()->SetTitleOffset(1.8);
   grmu3->SetMarkerColorAlpha(kBlack,0.35);
   grmu3->SetLineColor(kBlack);
   grmu3->Draw("AC*");
   TGraph *grx3 = new TGraph(nbins,binCentersx3,integralsx3);
   grx3->SetMarkerColor(kRed);
   grx3->SetLineColor(kRed);
   grx3->Draw("LC*");
   
   c->cd(4);
   TGraph *grmu5 = new TGraph(nbins,binCentersmu5,integralsmu5);
   grmu5->SetTitle("5-mm SciD + 0-mm Al");
   grmu5->GetXaxis()->SetTitle("Edep [MeV]");
   grmu5->GetXaxis()->SetRangeUser(0,2.5);
   grmu5->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu5->GetYaxis()->SetTitleOffset(1.8);
   grmu5->SetMarkerColorAlpha(kBlack,0.35);
   grmu5->SetLineColor(kBlack);
   grmu5->Draw("AC*");
   TGraph *grx5 = new TGraph(nbins,binCentersx5,integralsx5);
   grx5->SetMarkerColor(kRed);
   grx5->SetLineColor(kRed);
   grx5->Draw("LC*");
   
   c->cd(5);
   TGraph *grmu10 = new TGraph(nbins,binCentersmu10,integralsmu10);
   grmu10->SetTitle("10-mm SciD + 0-mm Al");
   grmu10->GetXaxis()->SetTitle("Edep [MeV]");
   grmu10->GetXaxis()->SetRangeUser(0,6);
   grmu10->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu10->GetYaxis()->SetTitleOffset(1.8);
   grmu10->SetMarkerColorAlpha(kBlack,0.35);
   grmu10->SetLineColor(kBlack);
   grmu10->Draw("AC*");
   TGraph *grx10 = new TGraph(nbins,binCentersx10,integralsx10);
   grx10->SetMarkerColor(kRed);
   grx10->SetLineColor(kRed);
   grx10->Draw("LC*");
     
   c->cd(6);
   TGraph *grmu20 = new TGraph(nbins,binCentersmu20,integralsmu20);
   grmu20->SetTitle("20-mm SciD + 0-mm Al");
   grmu20->GetXaxis()->SetTitle("Edep [MeV]");
   grmu20->GetXaxis()->SetRangeUser(0,11);
   grmu20->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu20->GetYaxis()->SetTitleOffset(1.8);
   grmu20->SetMarkerColorAlpha(kBlack,0.35);
   grmu20->SetLineColor(kBlack);
   grmu20->Draw("AC*");
   TGraph *grx20 = new TGraph(nbins,binCentersx20,integralsx20);
   grx20->SetMarkerColor(kRed);
   grx20->SetLineColor(kRed);
   grx20->Draw("LC*");
   
   c->SaveAs("BubbleTHR_0mm_Al.pdf");
   c->SaveAs("BubbleTHR_0mm_Al.png");
   c->SaveAs("BubbleTHR_0mm_Al.C");
   
   
   
   TCanvas *d = new TCanvas("d","E_{THR}",800,600);
   d->Divide(3,2);
   d->cd(1);
   TGraph *grAlmu1 = new TGraph(nbins,binCentersAlmu1,integralsAlmu1);
   grAlmu1->SetTitle("1-mm SciD + 3-mm Al");
   grAlmu1->GetXaxis()->SetTitle("Edep [MeV]");
   grAlmu1->GetXaxis()->SetRangeUser(0,2);
   grAlmu1->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grAlmu1->GetYaxis()->SetTitleOffset(1.8);
   grAlmu1->SetMarkerColorAlpha(kBlack,0.35);
   grAlmu1->SetLineColor(kBlack);
   grAlmu1->Draw("AC*");
   TGraph *grAlx1 = new TGraph(nbins,binCentersAlx1,integralsAlx1);
   grAlx1->SetMarkerColor(kRed);
   grAlx1->SetLineColor(kRed);
   grAlx1->Draw("LC*");
   
   d->cd(2);
   TGraph *grAlmu2 = new TGraph(nbins,binCentersAlmu2,integralsAlmu2);
   grAlmu2->SetTitle("2-mm SciD + 3-mm Al");
   grAlmu2->GetXaxis()->SetTitle("Edep [MeV]");
   grAlmu2->GetXaxis()->SetRangeUser(0,2);
   grAlmu2->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grAlmu2->GetYaxis()->SetTitleOffset(1.8);
   grAlmu2->SetMarkerColorAlpha(kBlack,0.35);
   grAlmu2->SetLineColor(kBlack);
   grAlmu2->Draw("AC*");
   TGraph *grAlx2 = new TGraph(nbins,binCentersAlx2,integralsAlx2);
   grAlx2->SetMarkerColor(kRed);
   grAlx2->SetLineColor(kRed);
   grAlx2->Draw("LC*");

   d->cd(3);
   TGraph *grAlmu3 = new TGraph(nbins,binCentersAlmu3,integralsAlmu3);
   grAlmu3->SetTitle("3-mm SciD + 3-mm Al");
   grAlmu3->GetXaxis()->SetTitle("Edep [MeV]");
   grAlmu3->GetXaxis()->SetRangeUser(0,2);
   grAlmu3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grAlmu3->GetYaxis()->SetTitleOffset(1.8);
   grAlmu3->SetMarkerColorAlpha(kBlack,0.35);
   grAlmu3->SetLineColor(kBlack);
   grAlmu3->Draw("AC*");
   TGraph *grAlx3 = new TGraph(nbins,binCentersAlx3,integralsAlx3);
   grAlx3->SetMarkerColor(kRed);
   grAlx3->SetLineColor(kRed);
   grAlx3->Draw("LC*");
   
   d->cd(4);
   TGraph *grAlmu5 = new TGraph(nbins,binCentersAlmu5,integralsAlmu5);
   grAlmu5->SetTitle("5-mm SciD + 3-mm Al");
   grAlmu5->GetXaxis()->SetTitle("Edep [MeV]");
   grAlmu5->GetXaxis()->SetRangeUser(0,3);
   grAlmu5->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grAlmu5->GetYaxis()->SetTitleOffset(1.8);
   grAlmu5->SetMarkerColorAlpha(kBlack,0.35);
   grAlmu5->SetLineColor(kBlack);
   grAlmu5->Draw("AC*");
   TGraph *grAlx5 = new TGraph(nbins,binCentersAlx5,integralsAlx5);
   grAlx5->SetMarkerColor(kRed);
   grAlx5->SetLineColor(kRed);
   grAlx5->Draw("LC*");
   
   d->cd(5);
   TGraph *grAlmu10 = new TGraph(nbins,binCentersAlmu10,integralsAlmu10);
   grAlmu10->SetTitle("10-mm SciD + 3-mm Al");
   grAlmu10->GetXaxis()->SetTitle("Edep [MeV]");
   grAlmu10->GetXaxis()->SetRangeUser(0,6);
   grAlmu10->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grAlmu10->GetYaxis()->SetTitleOffset(1.8);
   grAlmu10->SetMarkerColorAlpha(kBlack,0.35);
   grAlmu10->SetLineColor(kBlack);
   grAlmu10->Draw("AC*");
   TGraph *grAlx10 = new TGraph(nbins,binCentersAlx10,integralsAlx10);
   grAlx10->SetMarkerColor(kRed);
   grAlx10->SetLineColor(kRed);
   grAlx10->Draw("LC*");
     
   d->cd(6);
   TGraph *grAlmu20 = new TGraph(nbins,binCentersAlmu20,integralsAlmu20);
   grAlmu20->SetTitle("20-mm SciD + 3-mm Al");
   grAlmu20->GetXaxis()->SetTitle("Edep [MeV]");
   grAlmu20->GetXaxis()->SetRangeUser(0,11);
   grAlmu20->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grAlmu20->GetYaxis()->SetTitleOffset(1.8);
   grAlmu20->SetMarkerColorAlpha(kBlack,0.35);
   grAlmu20->SetLineColor(kBlack);
   grAlmu20->Draw("AC*");
   TGraph *grAlx20 = new TGraph(nbins,binCentersAlx20,integralsAlx20);
   grAlx20->SetMarkerColor(kRed);
   grAlx20->SetLineColor(kRed);
   grAlx20->Draw("LC*");
   
   d->SaveAs("BubbleTHR_3mm_Al.pdf");
   d->SaveAs("BubbleTHR_3mm_Al.png");
   d->SaveAs("BubbleTHR_3mm_Al.C");

 }
 
 
 int main() {
   bubble2THR();
   return 0;
}  
