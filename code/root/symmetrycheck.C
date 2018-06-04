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
   std::string fileFull = "symmetry_Nevts_1e6goldcascade_full.root";
   std::string fileTop = "symmetry_Nevts_1e6goldcascade_top.root";
   std::string fileBottom = "symmetry_Nevts_1e6goldcascade_bottom.root";
   std::string fileFront = "symmetry_Nevts_1e6goldcascade_front.root";
   std::string fileBack = "symmetry_Nevts_1e6goldcascade_back.root";
   std::string fileLeft = "symmetry_Nevts_1e6goldcascade_left.root";
   std::string fileRight = "symmetry_Nevts_1e6goldcascade_right.root";

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

   const int nbins=200;

   TFile* fFull = new TFile(TString(fileFull)); 
   TFile* fTop = new TFile(TString(fileTop));
   TFile *fBottom = new TFile(TString(fileBottom));
   TFile *fFront = new TFile(TString(fileFront));
   TFile *fBack = new TFile(TString(fileBack));
   TFile *fLeft = new TFile(TString(fileLeft));
   TFile *fRight = new TFile(TString(fileRight));

   TH1F *hFull = new TH1F("hFull","Edep Full",nbins,0.01,4);
   TH1F *hTop = new TH1F("hTop","Edep Top",nbins,0.01,4);
   TH1F *hBottom = new TH1F("hBottom","Edep Bottom",nbins,0.01,4);
   TH1F *hFront = new TH1F("hFront","Edep Front",nbins,0.01,4);
   TH1F *hBack = new TH1F("hBack","Edep Back",nbins,0.01,4);
   TH1F *hLeft = new TH1F("hLeft","Edep Left",nbins,0.01,4);
   TH1F *hRight = new TH1F("hRight","Edep Right",nbins,0.01,4);

   TTree *tFull = (TTree*)fFull->Get("Detector/SymmetryCube");
   TTree *tTop = (TTree*)fTop->Get("Detector/SymmetryPlate");
   TTree *tBottom = (TTree*)fBottom->Get("Detector/SymmetryPlate");
   TTree *tFront = (TTree*)fFront->Get("Detector/SymmetryPlate");
   TTree *tBack = (TTree*)fBack->Get("Detector/SymmetryPlate");
   TTree *tLeft = (TTree*)fLeft->Get("Detector/SymmetryPlate");
   TTree *tRight = (TTree*)fRight->Get("Detector/SymmetryPlate");

/*   tFull->Draw("Edep>>hFull","(Edep>=0.01)&&(Edep<=4.5)","");
   tTop->Draw("Edep>>hTop","(Edep>=0.01)&&(Edep<=4.5)","");
   tBottom->Draw("Edep>>hBottom","(Edep>=0.01)&&(Edep<=4.5)","");
   tFront->Draw("Edep>>hFront","(Edep>=0.01)&&(Edep<=4.5)","");
   tBack->Draw("Edep>>hBack","(Edep>=0.01)&&(Edep<=4.5)","");
   tLeft->Draw("Edep>>hLeft","(Edep>=0.01)&&(Edep<=4.5)","");
   tRight->Draw("Edep>>hRight","(Edep>=0.01)&&(Edep<=4.5)","");
*/
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
   hFull->Draw();
   
   c->cd(2);
   hTop->SetTitle("Symmetry X-ray cascade: Top");
   hTop->GetXaxis()->SetTitle("Edep [MeV]");
   hTop->GetYaxis()->SetTitle("# of counts [a.u.]");
   hTop->Draw();
   
   c->cd(3);
   hBottom->SetTitle("Symmetry X-ray cascade: Bottom");
   hBottom->GetXaxis()->SetTitle("Edep [MeV]");
   hBottom->GetYaxis()->SetTitle("# of counts [a.u.]");
   hBottom->Draw();
 
   c->cd(4);
   hFront->SetTitle("Symmetry X-ray cascade: Front");
   hFront->GetXaxis()->SetTitle("Edep [MeV]");
   hFront->GetYaxis()->SetTitle("# of counts [a.u.]");
   hFront->Draw();

   c->cd(5);
   hBack->SetTitle("Symmetry X-ray cascade: Back");
   hBack->GetXaxis()->SetTitle("Edep [MeV]");
   hBack->GetYaxis()->SetTitle("# of counts [a.u.]");
   hBack->Draw();
  
   c->cd(6);
   hLeft->SetTitle("Symmetry X-ray cascade: Left");
   hLeft->GetXaxis()->SetTitle("Edep [MeV]");
   hLeft->GetYaxis()->SetTitle("# of counts [a.u.]");
   hLeft->Draw();
   
   c->cd(7);
   hRight->SetTitle("Symmetry X-ray cascade: Right");
   hRight->GetXaxis()->SetTitle("Edep [MeV]");
   hRight->GetYaxis()->SetTitle("# of counts [a.u.]");
   hRight->Draw();

//   c->SaveAs("SymmetryPlot_v2.pdf");
//   c->SaveAs("SymmetryPlot_v2.jpg");
//   c->SaveAs("SymmetryPlot_v2.C");


/*
   TCanvas *c = new TCanvas("c","Edep mu-decay",800,600);

   t1->Draw("Edep>>h1","Edep<=3.5","");
   t2->Draw("Edep>>h2","Edep<=3.5","");
   t3->Draw("Edep>>h3","Edep<=3.5","");
   h1->SetLineColor(kBlack);
   h2->SetLineColor(kRed);
   h3->SetLineColor(kGreen-3);
   h1->Draw();
   h2->Draw("same");
   h3->Draw("same");

   TLegend *leg = new TLegend(0.7,0.75,0.9,0.6);
   leg->SetHeader("Scintillators");
   leg->SetBorderSize(0.01);
   leg->SetTextSize(0.025);
   leg->AddEntry("h1",TString(scintillator1ss.str())+" mm","l");
   leg->AddEntry("h2",TString(scintillator2ss.str())+" mm","l");
   leg->AddEntry("h3",TString(scintillator3ss.str())+" mm","l");
   leg->Draw();

   
   TCanvas *d = new TCanvas("d","Edep Au-cascade",800,600);

   t4->Draw("Edep>>h4","Edep<=3.5","");
   t5->Draw("Edep>>h5","Edep<=3.5","");
   t6->Draw("Edep>>h6","Edep<=3.5","");
   h4->SetLineColor(kYellow);
   h5->SetLineColor(kBlue);
   h6->SetLineColor(kViolet);
   h6->Draw();
   h5->Draw("same");
   h4->Draw("same");
   
   TPaveStats *ps = (TPaveStats*)d->GetPrimitive("stats");
   ps->SetName("Scintillators");
   TList *pslines = ps->GetListOfLines();
   d->Modified();
*/


   //TH1 *h1 = gDirectory->Get("h1");
   //TH1 *h2 = gDirectory->Get("h2");
   //TH1 *h3 = gDirectory->Get("h3");
   //c->SaveAs("plots/png/test.png");



/*
   TCanvas *e = new TCanvas("e","Edep",800,600);
   normh1mu->Draw();
   normaxish1mu->SetRangeUser(min_hist1,max_hist1);
   normh1au->SetLineColor(kRed);
   normh1au->Draw("same");
   TPad *epad = new TPad("epad","epad",0,0,1,1);
   epad->SetFillStyle(4000);
   epad->Draw();
   epad->cd();
   TPaveLabel *etitle = new TPaveLabel(0.1,0.0,0.94,0.04,TString(plotName1)+" & "+TString(plotName2));
   etitle->SetFillColor(17);
   etitle->SetTextFont(52);
   etitle->Draw();
   e->SaveAs("plots/pdf/partA_norm_"+TString(plotName1)+".pdf");
   e->SaveAs("plots/png/partA_norm_"+TString(plotName1)+".png");
   e->SaveAs("plots/C/partA_norm_"+TString(plotName1)+".root");
*/

}



int main() {
   symmetrycheck();
   return 0;
}
