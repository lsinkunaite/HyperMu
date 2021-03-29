//////////////////////////////////////////////
//                                          //
//               VetoEff8.C                 //
//                                          //                
//  Plots 2D histograms in energy and time  //
//  for the matched veto and BGO.           //
//                                          //
//////////////////////////////////////////////


// I/O
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <fstream>
#include <numeric>
#include <string>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

// ROOT
#include "TAttMarker.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TList.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveStats.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TText.h"

void VetoEff8(){
   // Some style definitions
   //gROOT->Reset();
   //gROOT->SetStyle("Plain");
   gStyle->SetPaperSize(26,20);
   gStyle->SetOptStat(1);
   gStyle->SetTitleXOffset(1.15);
   gStyle->SetTitleYOffset(0.95);
   gStyle->SetTitleBorderSize(1);
   gStyle->SetLegendBorderSize(1);
   //gStyle->SetPadBottomMargin(0.32);
   gStyle->SetPadBottomMargin(0.12);
   gStyle->SetPadLeftMargin(0.12);
   //gStyle->SetPadTopMargin(0.32);
   gStyle->SetPadTopMargin(0.04);
   gStyle->SetPadRightMargin(0.12);
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

   std::string runnumber = "run548/548";
  
   std::vector<int> timemin;
   std::vector<int> timemax;

   timemin.push_back(-30);
   timemax.push_back(30);
   double toffsetV4A = 3.0;   

   // Names of the files
   // Electron Vetos
   std::string fileVeto4A = runnumber+"_Veto4_A_prep.txt";
   // BGOs
   std::string fileBGOBackA = runnumber+"_BGO_Back_A_prep.txt";

   // Vectors with detector names
   std::vector<std::string> BGOfiles;
   std::vector<std::string> Vetofiles;

   // Electron Vetos
   Vetofiles.push_back(fileVeto4A);
   // BGOs
   BGOfiles.push_back(fileBGOBackA);


   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   

   // Veto4_A
   std::ifstream fVeto4A(Vetofiles[0]);
   std::vector<double> vEvIDV4A;
   std::vector<double> vEdepV4A;
   std::vector<double> vTimeV4A;
   while (!fVeto4A.eof()) {  
      double EvIDV4A, InstV4A, EdepV4A, TimeV4A;
      fVeto4A >> EvIDV4A >> InstV4A >> EdepV4A >> TimeV4A;
      vEvIDV4A.push_back(EvIDV4A);
      vEdepV4A.push_back(EdepV4A);
      vTimeV4A.push_back(TimeV4A+toffsetV4A);
   }
   vEvIDV4A.pop_back();
   vEdepV4A.pop_back();
   vTimeV4A.pop_back();
   fVeto4A.close();


   // BGO_Back_A
   std::ifstream fBGOBackA(BGOfiles[0]);
   std::vector<double> vEvIDBGOBackA;
   std::vector<double> vEdepBGOBackA;
   std::vector<double> vEkeVBGOBackA;
   std::vector<double> vTimeBGOBackA;
   double kbgobacka = 1.74;
   double bbgobacka = 12.46;
   while (!fBGOBackA.eof()) {
      double EvIDBGOBackA, InstBGOBackA, EdepBGOBackA, TimeBGOBackA;
      fBGOBackA >> EvIDBGOBackA >> InstBGOBackA >> EdepBGOBackA >> TimeBGOBackA;
      double EkeVBGOBackA;
      vEvIDBGOBackA.push_back(EvIDBGOBackA);
      vEdepBGOBackA.push_back(EdepBGOBackA);
      vTimeBGOBackA.push_back(TimeBGOBackA); 
      EkeVBGOBackA = EdepBGOBackA*kbgobacka+bbgobacka;
      vEkeVBGOBackA.push_back(EkeVBGOBackA);     
   }
   vEvIDBGOBackA.pop_back();
   vEdepBGOBackA.pop_back();
   vTimeBGOBackA.pop_back();
   vEkeVBGOBackA.pop_back();
   fBGOBackA.close();


   std::cout << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m--------------------- Reading II -------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;

   // Veto_4_A
   std::vector<double> vInstV4A; // Vector of repeating instances
   int EvIDV4A;
   for (int s=0; s<vEvIDV4A.size(); s++) {
      if ((s > 0) && (s < (vEvIDV4A.size()-1))) {
         if ((vEvIDV4A[s] == vEvIDV4A[s+1]) || (vEvIDV4A[s] == vEvIDV4A[s-1])) {
            vInstV4A.push_back(1);
         } else {
            vInstV4A.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDV4A[s] == vEvIDV4A[s+1]) {
            vInstV4A.push_back(1);
         } else {
            vInstV4A.push_back(0);
         }
      } else if (vEvIDV4A[s] == vEvIDV4A[s-1]) {
         vInstV4A.push_back(1);
      } else {
         vInstV4A.push_back(0);
      }
   }


   // BGO_Back_A
   std::vector<double> vEnBGOBackA;
   std::vector<double> vIDBGOBackA;
   std::vector<double> vTmBGOBackA;
   for (int s=0; s<vTimeBGOBackA.size(); s++) {
      if ((vTimeBGOBackA[s] > timemin[0]) && (vTimeBGOBackA[s] <timemax[0])) {
         if (vEkeVBGOBackA[s] < 100000) {
            vIDBGOBackA.push_back(vEvIDBGOBackA[s]);
            vEnBGOBackA.push_back(vEkeVBGOBackA[s]);
            vTmBGOBackA.push_back(vTimeBGOBackA[s]);
         }
      }
   }


   std::cout << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m---------------------- Matching --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;


   std::vector<double> EnVetoMatched;
   std::vector<double> EnBGOMatched; 
   std::vector<double> Eveto03;
   std::vector<double> Eveto36;
   std::vector<double> Eveto69;
   std::vector<double> Eveto912;
   std::vector<double> Eveto1215;
   std::vector<double> Eveto1518;
   std::vector<double> Eveto1821; 
   
   for (int n=0; n<vIDBGOBackA.size(); n++) {
      for (int k=0; k<vEvIDV4A.size(); k++) {
         if (vEvIDV4A[k] == vIDBGOBackA[n]) {
            if (vInstV4A[k] == 0) {
               if ((vTimeV4A[k] >= (vTmBGOBackA[n]-50)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+450))) {
                  EnVetoMatched.push_back(vEdepV4A[k]);
                  EnBGOMatched.push_back(vEnBGOBackA[n]);
                  if (vEnBGOBackA[n] < 3000) {
                     Eveto03.push_back(vEdepV4A[k]);
                  } else if ((vEnBGOBackA[n] >= 3000) && (vEnBGOBackA[n] < 6000)) {
                     Eveto36.push_back(vEdepV4A[k]);
                  } else if ((vEnBGOBackA[n] >= 6000) && (vEnBGOBackA[n] < 9000)) {
                     Eveto69.push_back(vEdepV4A[k]);
                  } else if ((vEnBGOBackA[n] >= 9000) && (vEnBGOBackA[n] < 12000)) {
                     Eveto912.push_back(vEdepV4A[k]);
                  } else if ((vEnBGOBackA[n] >= 12000) && (vEnBGOBackA[n] < 15000)) {
                     Eveto1215.push_back(vEdepV4A[k]);
                  } else if ((vEnBGOBackA[n] >= 15000) && (vEnBGOBackA[n] < 18000)) {
                     Eveto1518.push_back(vEdepV4A[k]);
                  } else if ((vEnBGOBackA[n] >= 18000) && (vEnBGOBackA[n] < 21000)) {
                     Eveto1821.push_back(vEdepV4A[k]);
                  } 
               }
            }
         }
      }
   }


   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

   TH1F *hveto03 = new TH1F("hveto03","hveto03",20,0,8.5);
   TH1F *hveto36 = new TH1F("hveto36","hveto36",20,0,8.5);
   TH1F *hveto69 = new TH1F("hveto69","hveto69",20,0,8.5);
   TH1F *hveto912 = new TH1F("hveto912","hveto912",20,0,8.5);
   TH1F *hveto1215 = new TH1F("hveto1215","hveto1215",20,0,8.5);
   TH1F *hveto1518 = new TH1F("hveto1518","hveto1518",20,0,8.5);
   TH1F *hveto1821 = new TH1F("hveto1821","hveto1821",20,0,8.5);
   for (int i=0; i<Eveto03.size(); i++) hveto03->Fill(Eveto03[i]/1000.0);
   for (int i=0; i<Eveto36.size(); i++) hveto36->Fill(Eveto36[i]/1000.0);
   for (int i=0; i<Eveto69.size(); i++) hveto69->Fill(Eveto69[i]/1000.0);
   for (int i=0; i<Eveto912.size(); i++) hveto912->Fill(Eveto912[i]/1000.0);
   for (int i=0; i<Eveto1215.size(); i++) hveto1215->Fill(Eveto1215[i]/1000.0);
   for (int i=0; i<Eveto1518.size(); i++) hveto1518->Fill(Eveto1518[i]/1000.0);
   for (int i=0; i<Eveto1821.size(); i++) hveto1821->Fill(Eveto1821[i]/1000.0);

   hveto03->Scale(1/(hveto03->GetBinContent(hveto03->GetMaximumBin())),"nosw2");
   hveto36->Scale(1/(hveto36->GetBinContent(hveto36->GetMaximumBin())),"nosw2");
   hveto69->Scale(1/(hveto69->GetBinContent(hveto69->GetMaximumBin())),"nosw2");
   hveto912->Scale(1/(hveto912->GetBinContent(hveto912->GetMaximumBin())),"nosw2");
   hveto1215->Scale(1/(hveto1215->GetBinContent(hveto1215->GetMaximumBin())),"nosw2");
   hveto1518->Scale(1/(hveto1518->GetBinContent(hveto1518->GetMaximumBin())),"nosw2");
   hveto1821->Scale(1/(hveto1821->GetBinContent(hveto1821->GetMaximumBin())),"nosw2");


   TCanvas *c = new TCanvas("c","c",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hveto03->SetTitle("");
   hveto03->GetXaxis()->SetTitle("E_{Veto} [kadc]");
   hveto03->SetLineColor(kRed);
   hveto03->Draw();
   hveto36->SetLineColor(kGreen-2);
   hveto36->Draw("same");
   hveto69->SetLineColor(kAzure-5);
   hveto69->Draw("same");
   hveto912->SetLineColor(kOrange+3);
   hveto912->Draw("same");
   hveto1215->SetLineColor(kViolet-5);
   hveto1215->Draw("same");
   hveto1518->SetLineColor(kBlack);
   hveto1518->Draw("same");
   hveto1821->SetLineColor(kSpring+7);
   hveto1821->Draw("same");
   auto legend = new TLegend(0.67,0.75,0.87,0.95);
   legend->AddEntry(hveto03,"E_{BGO} #in [0, 3) MeV","l");
   legend->AddEntry(hveto36,"E_{BGO} #in [3, 6) MeV","l");
   legend->AddEntry(hveto69,"E_{BGO} #in [6, 9) MeV","l");
   legend->AddEntry(hveto912,"E_{BGO} #in [9, 12) MeV","l");
   legend->AddEntry(hveto1215,"E_{BGO} #in [12, 15) MeV","l");
   legend->AddEntry(hveto1518,"E_{BGO} #in [15, 18) MeV","l");
   legend->AddEntry(hveto1821,"E_{BGO} #in [18, 21) MeV","l");
   legend->Draw();


/*
   TH1F *hRatioMatchedVeto = new TH1F("hRatioMatchedVeto","hRatioMatchedVeto",100,0.0,20.0);
   TH1F *hRatioMatchedBGO = new TH1F("hRatioMatchedBGO","hRatioMatchedBGO",100,0.0,250.0);
   for (int i=0; i<EnVetoMatched.size(); i++) {
      hRatioMatchedVeto->Fill(EnVetoMatched[i]/EnBGOMatched[i]);
      hRatioMatchedBGO->Fill(EnBGOMatched[i]/EnVetoMatched[i]);
   }

   TCanvas *cvratio = new TCanvas("cvratio","cvratio",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hRatioMatchedVeto->SetTitle("");
   hRatioMatchedVeto->GetXaxis()->SetTitle("E_{Veto}/E_{BGO}");
   hRatioMatchedVeto->Draw();
  
   TCanvas *cbratio = new TCanvas("cbratio","cbratio",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hRatioMatchedBGO->SetTitle("");
   hRatioMatchedBGO->GetXaxis()->SetTitle("E_{BGO}/E_{Veto}");
   hRatioMatchedBGO->Draw();
*/
/*
   TH2F *hRatioMatched2Veto = new TH2F("hRatioMatched2Veto","hRatioMatched2Veto",25,0,8.5,25,0,20.0);
   TH2F *hRatioMatched2BGO = new TH2F("hRatioMatched2BGO","hRatioMatched2BGO",25,0.0,10.0,25,0,250.0);
   for (int i=0; i <EnVetoMatched.size(); i++) {
      hRatioMatched2Veto->Fill((EnVetoMatched[i]/1000.0),EnVetoMatched[i]/EnBGOMatched[i]);
      hRatioMatched2BGO->Fill((EnBGOMatched[i]/1000.0),EnBGOMatched[i]/EnVetoMatched[i]);
   }

   TCanvas *cvratio2 = new TCanvas("cvratio2","cvratio2",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogz();
   hRatioMatched2Veto->SetTitle("");
   hRatioMatched2Veto->GetXaxis()->SetTitle("E_{Veto} [kadc]");
   hRatioMatched2Veto->GetYaxis()->SetTitle("E_{Veto}/E_{BGO}");
   hRatioMatched2Veto->Draw("COLZ");

   TCanvas *cbratio2 = new TCanvas("cbratio2","cbratio2",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogz();
   hRatioMatched2BGO->SetTitle("");
   hRatioMatched2BGO->GetXaxis()->SetTitle("E_{BGO} [MeV]");
   hRatioMatched2BGO->GetYaxis()->SetTitle("E_{BGO}/E_{Veto}");
   hRatioMatched2BGO->Draw("COLZ");
*/

}

int main() {
   VetoEff8();
   return 0;
} 
 
