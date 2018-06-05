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


void symmetrycheck(){

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
   std::string fileFull = "TEST_symmetry_Nevts_1e6goldcascade_full.root";
   std::string fileTop = "TEST_symmetry_Nevts_1e6goldcascade_top.root";
   std::string fileBottom = "TEST_symmetry_Nevts_1e6goldcascade_bottom.root";
   std::string fileFront = "TEST_symmetry_Nevts_1e6goldcascade_front.root";
   std::string fileBack = "TEST_symmetry_Nevts_1e6goldcascade_back.root";
   std::string fileLeft = "TEST_symmetry_Nevts_1e6goldcascade_left.root";
   std::string fileRight = "TEST_symmetry_Nevts_1e6goldcascade_right.root";

   std::string fileFullsub = fileFull.substr(0,fileFull.find(".root"));
   std::string fileTopsub = fileTop.substr(0,fileTop.find(".root"));
   std::string fileBottomsub = fileBottom.substr(0,fileBottom.find(".root"));
   std::string fileFrontsub = fileFront.substr(0,fileFront.find(".root"));
   std::string fileBacksub = fileBack.substr(0,fileBack.find(".root"));
   std::string fileLeftsub = fileLeft.substr(0,fileLeft.find(".root"));
   std::string fileRightsub = fileRight.substr(0,fileRight.find(".root"));


   /**************************************/
   /*             Analysis               */
   /**************************************/

   const int nbins=100;

   TFile* fFull = new TFile(TString(fileFull)); 
   TFile* fTop = new TFile(TString(fileTop));
   TFile *fBottom = new TFile(TString(fileBottom));
   TFile *fFront = new TFile(TString(fileFront));
   TFile *fBack = new TFile(TString(fileBack));
   TFile *fLeft = new TFile(TString(fileLeft));
   TFile *fRight = new TFile(TString(fileRight));

   TH1F *hFull = new TH1F("hFull","Edep Full",nbins,0.01,14);
   TH1F *hTop = new TH1F("hTop","Edep Top",nbins,0.01,10);
   TH1F *hBottom = new TH1F("hBottom","Edep Bottom",nbins,0.01,10);
   TH1F *hFront = new TH1F("hFront","Edep Front",nbins,0.01,10);
   TH1F *hBack = new TH1F("hBack","Edep Back",nbins,0.01,10);
   TH1F *hLeft = new TH1F("hLeft","Edep Left",nbins,0.01,10);
   TH1F *hRight = new TH1F("hRight","Edep Right",nbins,0.01,10);

   TTree *tFull = (TTree*)fFull->Get("Detector/SymmetryCube");
   TTree *tTop = (TTree*)fTop->Get("Detector/SymmetryPlate");
   TTree *tBottom = (TTree*)fBottom->Get("Detector/SymmetryPlate");
   TTree *tFront = (TTree*)fFront->Get("Detector/SymmetryPlate");
   TTree *tBack = (TTree*)fBack->Get("Detector/SymmetryPlate");
   TTree *tLeft = (TTree*)fLeft->Get("Detector/SymmetryPlate");
   TTree *tRight = (TTree*)fRight->Get("Detector/SymmetryPlate");

   tFull->Draw("Edep>>hFull","","");
   tTop->Draw("Edep>>hTop","","");
   tBottom->Draw("Edep>>hBottom","","");
   tFront->Draw("Edep>>hFront","","");
   tBack->Draw("Edep>>hBack","","");
   tLeft->Draw("Edep>>hLeft","","");
   tRight->Draw("Edep>>hRight","","");
   
   hFull->SetLineColor(kBlack);
   hTop->SetLineColor(kRed);
   hBottom->SetLineColor(kGreen-3);
   hFront->SetLineColor(kOrange);
   hBack->SetLineColor(kBlue);
   hLeft->SetLineColor(kViolet);
   hRight->SetLineColor(kRed+3);

   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(4,2);
   c->cd(1);
   hFull->SetTitle("Symmetry X-ray cascade: Full");
   hFull->GetXaxis()->SetTitle("Edep [MeV]");
   hFull->GetYaxis()->SetTitle("# of counts [a.u.]");
   hFull->GetYaxis()->SetTitleOffset(2.0);
   hFull->Draw();
   
   c->cd(2);
   hTop->SetTitle("Symmetry X-ray cascade: Top");
   hTop->GetXaxis()->SetTitle("Edep [MeV]");
   hTop->GetYaxis()->SetTitle("# of counts [a.u.]");
   hTop->GetYaxis()->SetTitleOffset(2.0);
   hTop->Draw();
   
   c->cd(3);
   hBottom->SetTitle("Symmetry X-ray cascade: Bottom");
   hBottom->GetXaxis()->SetTitle("Edep [MeV]");
   hBottom->GetYaxis()->SetTitle("# of counts [a.u.]");
   hBottom->GetYaxis()->SetTitleOffset(2.0);
   hBottom->Draw();
 
   c->cd(4);
   hFront->SetTitle("Symmetry X-ray cascade: Front");
   hFront->GetXaxis()->SetTitle("Edep [MeV]");
   hFront->GetYaxis()->SetTitle("# of counts [a.u.]");
   hFront->GetYaxis()->SetTitleOffset(2.0);
   hFront->Draw();

   c->cd(5);
   hBack->SetTitle("Symmetry X-ray cascade: Back");
   hBack->GetXaxis()->SetTitle("Edep [MeV]");
   hBack->GetYaxis()->SetTitle("# of counts [a.u.]");
   hBack->GetYaxis()->SetTitleOffset(2.0);
   hBack->Draw();
  
   c->cd(6);
   hLeft->SetTitle("Symmetry X-ray cascade: Left");
   hLeft->GetXaxis()->SetTitle("Edep [MeV]");
   hLeft->GetYaxis()->SetTitle("# of counts [a.u.]");
   hLeft->GetYaxis()->SetTitleOffset(2.0);
   hLeft->Draw();
   
   c->cd(7);
   hRight->SetTitle("Symmetry X-ray cascade: Right");
   hRight->GetXaxis()->SetTitle("Edep [MeV]");
   hRight->GetYaxis()->SetTitle("# of counts [a.u.]");
   hRight->GetYaxis()->SetTitleOffset(2.0);
   hRight->Draw();

   c->SaveAs("SymmetryPlot.pdf");
   c->SaveAs("SymmetryPlot.jpg");
   c->SaveAs("SymmetryPlot.C");


}



int main() {
   symmetrycheck();
   return 0;
}
