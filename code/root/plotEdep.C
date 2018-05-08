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


void plotEdep(){

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
   int scintillator = 1; //mm
   const int nEvts = 1e6; // #of events

   std::stringstream scintillatorss; scintillatorss << scintillator;
   std::stringstream nEvtsss; nEvtsss << nEvts;

   // Names of the files
   std::string file1 = "acadecombo_Nevts_SciL_1e6"+scintillatorss.str()+"mudecay.root";
   std::string file2 = "acadecombo_Nevts_SciL_1e6"+scintillatorss.str()+"goldcascade.root";
   std::string file1sub = file1.substr(0,file1.find(".root"));
   std::string file2sub = file2.substr(0,file2.find(".root"));
   std::string FileName1 = ""+file1;
   std::string FileName2 = ""+file2;
   std::string plotName1 = "Plot_"+file1sub;
   std::string plotName2 = "Plot_"+file2sub;

   Float_t PDGid, EventID, TrackID, Edep, ParentID;

   /***************************************/
   /*             Parameters              */
   /***************************************/
   const int sci = 0;

   /***************************************/
   /*              Detectors              */
   /***************************************/
   float Edeptot[nEvts] = {};
   float rEdeppSciDetD0mu[nEvts] = {};
   float rEdeppSciDetD0au[nEvts] = {};


   /**************************************/
   /*             Analysis               */
   /**************************************/


   TFile* f1 = new TFile(TString(FileName1));

   //SciDetD0 [mu-decay]
   TNtuple * SciDetD0mu = (TNtuple*)f1->Get("Detector/SciDetD0");
   SciDetD0mu->SetBranchAddress("Edep", &Edep);
   SciDetD0mu->SetBranchAddress("PDGid", &PDGid);
   SciDetD0mu->SetBranchAddress("EventID", &EventID);
   SciDetD0mu->SetBranchAddress("ParentID", &ParentID);

   for (int i=0; i<SciDetD0mu->GetEntries(); ++i) {
      SciDetD0mu->GetEntry(i);
      rEdeppSciDetD0mu[i] = Edep;
   }

   
   TFile* f2 = new TFile(TString(FileName2));

   //SciDetD0 [Au-cascade]
   TNtuple * SciDetD0au = (TNtuple*)f2->Get("Detector/SciDetD0");
   SciDetD0au->SetBranchAddress("Edep", &Edep);
   SciDetD0au->SetBranchAddress("PDGid", &PDGid);
   SciDetD0au->SetBranchAddress("EventID", &EventID);
   SciDetD0au->SetBranchAddress("ParentID", &ParentID);

   for (int i=0; i<SciDetD0au->GetEntries(); ++i) {
      SciDetD0au->GetEntry(i);
      rEdeppSciDetD0au[i] = Edep;
   }


   //Plotting
   const int nbins = 100;
   const int nsamples = 400;

   float min_SciDetD0mu = *std::min_element(rEdeppSciDetD0mu,rEdeppSciDetD0mu+SciDetD0mu->GetEntries());
   float max_SciDetD0mu = *std::max_element(rEdeppSciDetD0mu,rEdeppSciDetD0mu+SciDetD0mu->GetEntries());

   float min_SciDetD0au = *std::min_element(rEdeppSciDetD0au,rEdeppSciDetD0au+SciDetD0au->GetEntries());
   float max_SciDetD0au = *std::max_element(rEdeppSciDetD0au,rEdeppSciDetD0au+SciDetD0au->GetEntries());

   // Minimum and maximum of a histogram
   float min_hist1 = std::min(min_SciDetD0mu,min_SciDetD0au);
   float max_hist1 = std::max(max_SciDetD0mu,max_SciDetD0au);
   float h1countsmu[nbins] = {};
   float h1countsau[nbins] = {};   
   float lowerbinedgesh1mu[nbins] = {};
   float upperbinedgesh1mu[nbins] = {};
   float lowerbinedgesh1au[nbins] = {};
   float upperbinedgesh1au[nbins] = {};
   float binwidthh1mu = (max_SciDetD0mu - min_SciDetD0mu)/nbins;
   float binwidthh1au = (max_SciDetD0au - min_SciDetD0au)/nbins;
   float samplewidthh1 = (max_hist1 - min_hist1)/nsamples;
   float loweredgesh1sample[nsamples] = {};
   float upperedgesh1sample[nsamples] = {};
   float normcountsh1mu[nsamples] = {0};
   float normcountsh1au[nsamples] = {};

   // Defining bin boundaries for muon-decays
   for (int i=0; i<nbins; i++) {
      if (i == 0) {
         lowerbinedgesh1mu[0] = min_SciDetD0mu;
         upperbinedgesh1mu[0] = min_SciDetD0mu + binwidthh1mu;
      } else {
         lowerbinedgesh1mu[i] = lowerbinedgesh1mu[i-1] + binwidthh1mu;
         upperbinedgesh1mu[i] = upperbinedgesh1mu[i-1] + binwidthh1mu;
      }
   }

   // Defining bin boundaries for gold cascade
   for (int i=0; i<nbins; i++) {
      if (i == 0) {
         lowerbinedgesh1au[0] = min_SciDetD0au;
         upperbinedgesh1au[0] = min_SciDetD0au + binwidthh1au;
      } else {
         lowerbinedgesh1au[i] = lowerbinedgesh1au[i-1] + binwidthh1au;
         upperbinedgesh1au[i] = upperbinedgesh1au[i-1] + binwidthh1au;
      }
   }
 
   // Defining bin boundaries for sampling
   for (int i=0; i<nsamples; i++) {
      if (i == 0) {
         loweredgesh1sample[0] = min_hist1;
         upperedgesh1sample[0] = min_hist1 + samplewidthh1;
      } else {
         loweredgesh1sample[i] = loweredgesh1sample[i-1] + samplewidthh1;
         upperedgesh1sample[i] = upperedgesh1sample[i-1] + samplewidthh1;
      }
   }


   //Creating the histograms
   TH1F *h1mu = new TH1F("SciDetD0mu", "Edep SciDetD0mu",nbins,lowerbinedgesh1mu[0],upperbinedgesh1mu[nbins-1]);
   TH1F *h1au = new TH1F("SciDetD0au", "Edep SciDetD0au",nbins,lowerbinedgesh1au[0],upperbinedgesh1au[nbins-1]);

   TH1F *normh1mu = new TH1F("normSciDetD0mu", "Edep mu norm",nsamples,loweredgesh1sample[0],upperedgesh1sample[nbins-1]);
   TH1F *normh1au = new TH1F("normSciDetD0au", "Edep au norm",nsamples,loweredgesh1sample[0],upperedgesh1sample[nbins-1]);

   //Filling the histograms
   for (int i=0; i<SciDetD0mu->GetEntries(); i++) {
      h1mu->Fill(rEdeppSciDetD0mu[i],1);
   }
   for (int i=0; i<SciDetD0au->GetEntries(); i++) {
      h1au->Fill(rEdeppSciDetD0au[i],1);
   }  

   TAxis *axish1mu = h1mu->GetXaxis();
   TAxis *axish1au = h1au->GetXaxis();

   Int_t binx1mu; //Bin number
   Int_t binx1au; 

   for (int i=0; i<nsamples; i++) {
      binx1mu = axish1mu->FindBin(loweredgesh1sample[i]);
      for (int j=0; j<binx1mu; j++) {
         normcountsh1mu[i] += (h1mu->GetBinContent(j))/(h1mu->GetEntries());
         //normcountsh1mu[i] += h1mu->GetBinContent(j);
      }      
      //std::cout << "normcount = " << normcountsh1mu[i] << " und alles " << h1mu->GetEntries() << std::endl;
   }

   for (int i=0; i<nsamples; i++) {
      binx1au = axish1au->FindBin(loweredgesh1sample[i]);
      for (int j=0; j<binx1au; j++) {
         normcountsh1au[i] += (h1au->GetBinContent(j))/(h1au->GetEntries());
         //normcountsh1au[i] += h1au->GetBinContent(j);
      }
      //std::cout << " normcount au " << normcountsh1au[i] << " und alles " << h1au->GetEntries() << std::endl;
   }

   //Filling normalised histograms
   for (int i=0; i<nsamples; i++) {
      normh1mu->SetBinContent(i,normcountsh1mu[i]);
   }
   for (int i=0; i<nsamples; i++) {
      normh1au->SetBinContent(i,normcountsh1au[i]);
   }

/*
   for (int i=0; i<nsamples; i++) {
      normh1mu->Fill(normcountsh1mu[i],1);
   }
   for (int i=0; i<nsamples; i++) {
      normh1au->Fill(normcountsh1au[i],1);
   } 
*/
   TAxis *normaxish1mu = normh1mu->GetXaxis();
   TAxis *normaxish1au = normh1au->GetXaxis(); 

/*
   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(1,3);
   c->cd(1); h1mu->Draw();
   c->cd(2); h1au->Draw();
   c->cd(3); h1mu->Draw(); axish1mu->SetRangeUser(min_hist1,max_hist1); h1au->SetLineColor(kRed); h1au->Draw("same");
   TPad *cpad = new TPad("cpad", "cpad",0,0,1,1);
   cpad->SetFillStyle(4000);
   cpad->Draw();
   cpad->cd();
   TPaveLabel *ctitle = new TPaveLabel(0.1,0.0,0.94,0.04,TString(plotName1)+" & "+TString(plotName2));
   ctitle->SetFillColor(11);
   ctitle->SetTextFont(52);
   ctitle->Draw();
   c->SaveAs("plots/pdf/partA_"+TString(plotName1)+".pdf");
   c->SaveAs("plots/png/partA_"+TString(plotName1)+".png");
   c->SaveAs("plots/C/partA_"+TString(plotName1)+".C");

  
   TCanvas *d = new TCanvas("d","Edep",800,600);
   h1mu->Draw();
   axish1mu->SetRangeUser(min_hist1,max_hist1);
   h1au->SetLineColor(kRed);
   h1au->Draw("same");
   TPad *dpad = new TPad("dpad","dpad",0,0,1,1);
   dpad->SetFillStyle(4000);
   dpad->Draw();
   dpad->cd();
   TPaveLabel *dtitle = new TPaveLabel(0.1,0.0,0.94,0.04,TString(plotName1)+" & "+TString(plotName2));
   dtitle->SetFillColor(14);
   dtitle->SetTextFont(52);
   dtitle->Draw();
   d->SaveAs("plots/pdf/partA_super_"+TString(plotName1)+".pdf");
   d->SaveAs("plots/png/partA_super_"+TString(plotName1)+".png");
   d->SaveAs("plots/C/partA_super_"+TString(plotName1)+".C");
   
*/

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


}



int main() {
   plotEdep();
   return 0;
}
