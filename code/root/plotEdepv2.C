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


void plotEdepv2(){

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
   gStyle->SetPadLeftMargin(0.12);
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
   int scintillator1 = 5; //mm
   int scintillator2 = 10; //mm
   int scintillator3 = 20; //mm
   const int nEvts = 1e6; // # of events
   int nbins = 1000; // # of bins

   std::stringstream scintillator1ss; scintillator1ss << scintillator1;
   std::stringstream scintillator2ss; scintillator2ss << scintillator2;
   std::stringstream scintillator3ss; scintillator3ss << scintillator3;
   std::stringstream nEvtsss; nEvtsss << nEvts;

   // Names of the files
   std::string file1 = "acadecombo_Nevts_SciL_1e6"+scintillator1ss.str()+"mudecay.root";
   std::string file2 = "acadecombo_Nevts_SciL_1e6"+scintillator2ss.str()+"mudecay.root";
   std::string file3 = "acadecombo_Nevts_SciL_1e6"+scintillator3ss.str()+"mudecay.root";
   std::string file4 = "acadecombo_Nevts_SciL_1e6"+scintillator1ss.str()+"goldcascade.root";
   std::string file5 = "acadecombo_Nevts_SciL_1e6"+scintillator2ss.str()+"goldcascade.root";
   std::string file6 = "acadecombo_Nevts_SciL_1e6"+scintillator3ss.str()+"goldcascade.root";
   std::string file1sub = file1.substr(0,file1.find(".root"));
   std::string file2sub = file2.substr(0,file2.find(".root"));
   std::string file3sub = file3.substr(0,file3.find(".root"));
   std::string file4sub = file4.substr(0,file4.find(".root"));
   std::string file5sub = file5.substr(0,file5.find(".root"));
   std::string file6sub = file6.substr(0,file6.find(".root"));
   std::string FileName1 = ""+file1;
   std::string FileName2 = ""+file2;
   std::string FileName3 = ""+file3;
   std::string FileName4 = ""+file4;
   std::string FileName5 = ""+file5;
   std::string FileName6 = ""+file6;
   std::string plotName1 = "Plot_"+file1sub;
   std::string plotName4 = "Plot_"+file4sub;


   /**************************************/
   /*             Analysis               */
   /**************************************/


   // muon decay
   TFile* f1 = new TFile(TString(FileName1)); 
   TFile* f2 = new TFile(TString(FileName2));
   TFile *f3 = new TFile(TString(FileName3));
   // gold cascade
   TFile *f4 = new TFile(TString(FileName4));
   TFile *f5 = new TFile(TString(FileName5));
   TFile *f6 = new TFile(TString(FileName6));

   TH1F *h1 = new TH1F("h1","SciDetD0mu_"+TString(scintillator1ss.str())+"mm",nbins,0,3.5);
   TH1F *h2 = new TH1F("h2","SciDetD0mu_"+TString(scintillator2ss.str())+"mm",nbins,0,3.5);
   TH1F *h3 = new TH1F("h3","SciDetD0mu_"+TString(scintillator3ss.str())+"mm",nbins,0,3.5);
   TH1F *h4 = new TH1F("h4","SciDetD0au_"+TString(scintillator1ss.str())+"mm",nbins,0,3.5);
   TH1F *h5 = new TH1F("h5","SciDetD0au_"+TString(scintillator2ss.str())+"mm",nbins,0,3.5);
   TH1F *h6 = new TH1F("h6","SciDetD0au_"+TString(scintillator3ss.str())+"mm",nbins,0,3.5);

   TTree *t1 = (TTree*)f1->Get("Detector/SciDetD0");
   TTree *t2 = (TTree*)f2->Get("Detector/SciDetD0");
   TTree *t3 = (TTree*)f3->Get("Detector/SciDetD0");
   TTree *t4 = (TTree*)f4->Get("Detector/SciDetD0");
   TTree *t5 = (TTree*)f5->Get("Detector/SciDetD0");
   TTree *t6 = (TTree*)f6->Get("Detector/SciDetD0");

   t1->Draw("Edep>>h1","Edep<=3.5","");
   t2->Draw("Edep>>h2","Edep<=3.5","");
   t3->Draw("Edep>>h3","Edep<=3.5","");
   t4->Draw("Edep>>h4","Edep<=3.5","");
   t5->Draw("Edep>>h5","Edep<=3.5","");
   t6->Draw("Edep>>h6","Edep<=3.5","");

   h1->SetLineColor(kBlack);
   h2->SetLineColor(kRed);
   h3->SetLineColor(kGreen-3);
   h4->SetLineColor(kOrange);
   h5->SetLineColor(kBlue);
   h6->SetLineColor(kViolet);

   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(3,2);
   c->cd(1);
   h1->SetTitle("Scintillators "+TString(scintillator1ss.str())+" mm");
   h1->GetXaxis()->SetTitle("Edep [MeV]");
   h1->GetYaxis()->SetTitle("# of counts [a.u.]");
   h1->Draw();
   h4->Draw("same");
   TPaveStats *st1 = (TPaveStats*)h1->GetListOfFunctions()->FindObject("stats");

   c->cd(2);
   h2->SetTitle("Scintillators "+TString(scintillator2ss.str())+" mm");
   h2->GetXaxis()->SetTitle("Edep [MeV]");
   h2->GetYaxis()->SetTitle("# of counts [a.u.]");
   h2->Draw();
   h5->Draw("same");
   
   c->cd(3);
   h6->SetTitle("Scintillators "+TString(scintillator3ss.str())+" mm");
   h6->GetXaxis()->SetTitle("Edep [MeV]");
   h6->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6->Draw();
   h3->Draw("same");
 
   c->cd(4);
   h1->SetTitle("Scintillators: #mu-decay");
   h1->GetXaxis()->SetTitle("Edep [MeV]");
   h1->GetYaxis()->SetTitle("# of counts [a.u.]");
   h1->Draw();
   h2->Draw("same");
   h3->Draw("same");

   c->cd(5);
   t4->Draw("Edep>>h4","(Edep>=0.25)&&(Edep<=3.5)","");
   t5->Draw("Edep>>h5","(Edep>=0.25)&&(Edep<=3.5)","");
   t6->Draw("Edep>>h6","(Edep>=0.25)&&(Edep<=3.5)","");
   h6->SetTitle("Scintillators: Au-cascade");
   h6->GetXaxis()->SetTitle("Edep [MeV]");
   h6->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6->Draw();
   h5->Draw("same");
   h4->Draw("same");


   std::cout << "entries h1 :: " << h1->GetEntries() << std::endl;



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
   plotEdepv2();
   return 0;
}
