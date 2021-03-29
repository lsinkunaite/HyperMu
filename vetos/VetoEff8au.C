//////////////////////////////////////////////
//                                          //
//               VetoEff8au.C                 //
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

void VetoEff8au(){
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
   std::vector<double> Eveto01;
   std::vector<double> Eveto12;
   std::vector<double> Eveto23;
   std::vector<double> Eveto34;
   std::vector<double> Eveto45;
   std::vector<double> Eveto56;
   std::vector<double> Eveto67;
   std::vector<double> Eveto78;
   std::vector<double> Eveto89; 
   
   for (int n=0; n<vIDBGOBackA.size(); n++) {
      for (int k=0; k<vEvIDV4A.size(); k++) {
         if (vEvIDV4A[k] == vIDBGOBackA[n]) {
            if (vInstV4A[k] == 0) {
               if ((vTimeV4A[k] >= (vTmBGOBackA[n]-50)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+450))) {
                  EnVetoMatched.push_back(vEdepV4A[k]);
                  EnBGOMatched.push_back(vEnBGOBackA[n]);
                  if (vEnBGOBackA[n] < 1000) {
                     Eveto01.push_back(vEdepV4A[k]);
                  } else if ((vEnBGOBackA[n] >= 1000) && (vEnBGOBackA[n] < 2000)) {
                     Eveto12.push_back(vEdepV4A[k]);
                  } else if ((vEnBGOBackA[n] >= 2000) && (vEnBGOBackA[n] < 3000)) {
                     Eveto23.push_back(vEdepV4A[k]);
                  } else if ((vEnBGOBackA[n] >= 3000) && (vEnBGOBackA[n] < 4000)) {
                     Eveto34.push_back(vEdepV4A[k]);
                  } else if ((vEnBGOBackA[n] >= 4000) && (vEnBGOBackA[n] < 5000)) {
                     Eveto45.push_back(vEdepV4A[k]);
                  } else if ((vEnBGOBackA[n] >= 5000) && (vEnBGOBackA[n] < 6000)) {
                     Eveto56.push_back(vEdepV4A[k]);
                  } else if ((vEnBGOBackA[n] >= 6000) && (vEnBGOBackA[n] < 7000)) {
                     Eveto67.push_back(vEdepV4A[k]);
                  } else if ((vEnBGOBackA[n] >= 7000) && (vEnBGOBackA[n] < 8000)) {
                     Eveto78.push_back(vEdepV4A[k]);
                  } else if ((vEnBGOBackA[n] >= 8000) && (vEnBGOBackA[n] < 9000)) {
                     Eveto89.push_back(vEdepV4A[k]);
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

   TH1F *hveto01 = new TH1F("hveto01","hveto01",20,0,8.5);
   TH1F *hveto12 = new TH1F("hveto12","hveto12",20,0,8.5);
   TH1F *hveto23 = new TH1F("hveto23","hveto23",20,0,8.5);
   TH1F *hveto34 = new TH1F("hveto34","hveto34",20,0,8.5);
   TH1F *hveto45 = new TH1F("hveto45","hveto45",20,0,8.5);
   TH1F *hveto56 = new TH1F("hveto56","hveto56",20,0,8.5);
   TH1F *hveto67 = new TH1F("hveto67","hveto67",20,0,8.5);
   TH1F *hveto78 = new TH1F("hveto78","hveto78",20,0,8.5);
   TH1F *hveto89 = new TH1F("hveto89","hveto89",20,0,8.5);
   for (int i=0; i<Eveto01.size(); i++) hveto01->Fill(Eveto01[i]/1000.0);
   for (int i=0; i<Eveto12.size(); i++) hveto12->Fill(Eveto12[i]/1000.0);
   for (int i=0; i<Eveto23.size(); i++) hveto23->Fill(Eveto23[i]/1000.0);
   for (int i=0; i<Eveto34.size(); i++) hveto34->Fill(Eveto34[i]/1000.0);
   for (int i=0; i<Eveto45.size(); i++) hveto45->Fill(Eveto45[i]/1000.0);
   for (int i=0; i<Eveto56.size(); i++) hveto56->Fill(Eveto56[i]/1000.0);
   for (int i=0; i<Eveto67.size(); i++) hveto67->Fill(Eveto67[i]/1000.0);
   for (int i=0; i<Eveto78.size(); i++) hveto78->Fill(Eveto78[i]/1000.0);
   for (int i=0; i<Eveto89.size(); i++) hveto89->Fill(Eveto89[i]/1000.0);

   hveto01->Scale(1/(hveto01->GetBinContent(hveto01->GetMaximumBin())),"nosw2");
   hveto12->Scale(1/(hveto12->GetBinContent(hveto12->GetMaximumBin())),"nosw2");
   hveto23->Scale(1/(hveto23->GetBinContent(hveto23->GetMaximumBin())),"nosw2");
   hveto34->Scale(1/(hveto34->GetBinContent(hveto34->GetMaximumBin())),"nosw2");
   hveto45->Scale(1/(hveto45->GetBinContent(hveto45->GetMaximumBin())),"nosw2");
   hveto56->Scale(1/(hveto56->GetBinContent(hveto56->GetMaximumBin())),"nosw2");
   hveto67->Scale(1/(hveto67->GetBinContent(hveto67->GetMaximumBin())),"nosw2");
   hveto78->Scale(1/(hveto78->GetBinContent(hveto78->GetMaximumBin())),"nosw2");
   hveto89->Scale(1/(hveto89->GetBinContent(hveto89->GetMaximumBin())),"nosw2");


   TCanvas *c = new TCanvas("c","c",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hveto01->SetTitle("");
   hveto01->GetXaxis()->SetTitle("E_{Veto} [kadc]");
   hveto01->SetLineColor(kRed);
   hveto01->Draw();
   hveto12->SetLineColor(kGreen-2);
   hveto12->Draw("same");
   hveto23->SetLineColor(kAzure-5);
   hveto23->Draw("same");
   hveto34->SetLineColor(kOrange+3);
   hveto34->Draw("same");
   hveto45->SetLineColor(kViolet-5);
   hveto45->Draw("same");
   hveto56->SetLineColor(kBlack);
   hveto56->Draw("same");
   hveto67->SetLineColor(kSpring+7);
   hveto67->Draw("same");
   hveto78->SetLineColor(kPink+3);
   hveto78->Draw("same");
   hveto89->SetLineColor(kYellow-4);
   hveto89->Draw("same");
   auto legend = new TLegend(0.67,0.75,0.87,0.95);
   legend->AddEntry(hveto01,"E_{BGO} #in [0, 1) MeV","l");
   legend->AddEntry(hveto12,"E_{BGO} #in [1, 2) MeV","l");
   legend->AddEntry(hveto23,"E_{BGO} #in [2, 3) MeV","l");
   legend->AddEntry(hveto34,"E_{BGO} #in [4, 4) MeV","l");
   legend->AddEntry(hveto45,"E_{BGO} #in [4, 5) MeV","l");
   legend->AddEntry(hveto56,"E_{BGO} #in [5, 6) MeV","l");
   legend->AddEntry(hveto67,"E_{BGO} #in [6, 7) MeV","l");
   legend->AddEntry(hveto78,"E_{BGO} #in [7, 8) MeV","l");
   legend->AddEntry(hveto89,"E_{BGO} #in [8, 9] MeV","l");
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
   VetoEff8au();
   return 0;
} 
 
