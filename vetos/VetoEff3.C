///////////////////////////////////////////////
//                                           //
//               VetoEff3.C                  //
//                                           //                
//  Compares the energy and the time of the  //
//  matched electron veto to its total time  //
//  or energy.                               //
//                                           //
///////////////////////////////////////////////


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

void VetoEff3(){
   // Some style definitions
   //gROOT->Reset();
   //gROOT->SetStyle("Plain");
   gStyle->SetPaperSize(26,20);
   gStyle->SetOptStat(1);
   gStyle->SetTitleXOffset(1.15);
   gStyle->SetTitleYOffset(1.15);
   gStyle->SetTitleBorderSize(1);
   gStyle->SetLegendBorderSize(1);
   //gStyle->SetPadBottomMargin(0.32);
   gStyle->SetPadBottomMargin(0.12);
   gStyle->SetPadLeftMargin(0.08);
   //gStyle->SetPadTopMargin(0.32);
   gStyle->SetPadTopMargin(0.04);
   gStyle->SetPadRightMargin(0.06);
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

   std::string runnumber = "run530/530";
  
   std::vector<int> timemin;
   std::vector<int> timemax;

   timemin.push_back(100);
   timemax.push_back(1000);
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
   std::vector<double> TmVetoMatched;  
   
   for (int n=0; n<vIDBGOBackA.size(); n++) {
      for (int k=0; k<vEvIDV4A.size(); k++) {
         if (vEvIDV4A[k] == vIDBGOBackA[n]) {
            if (vInstV4A[k] == 0) {
               if ((vTimeV4A[k] >= (vTmBGOBackA[n]-250)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+65))) {
                  EnVetoMatched.push_back(vEdepV4A[k]);
                  TmVetoMatched.push_back(vTimeV4A[k]);
               }
            }
         }
      }
   }


   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

   TH1F *hAllTm = new TH1F("hAllTm","hAllTm",50,-100.0,500.0); // Time of Veto_4_A
   TH1F *hAllEn = new TH1F("hAllEn","hAllEn",100,0,10.0); // Energy of Veto_4_A
   TH1F *hMTm = new TH1F("hMTm","hMTm",50,-100.0,500.0); // Matched time of Veto_4_A
   TH1F *hMEn = new TH1F("hMEn","hMEn",100,0.0,10.0); // Matched energy of Veto_4_A

   for (int i=0; i<vTimeV4A.size(); i++) hAllTm->Fill(vTimeV4A[i]);
   for (int i=0; i<vEdepV4A.size(); i++) hAllEn->Fill(vEdepV4A[i]/1000.0);
   for (int i=0; i<TmVetoMatched.size(); i++) hMTm->Fill(TmVetoMatched[i]);
   for (int i=0; i<EnVetoMatched.size(); i++) hMEn->Fill(EnVetoMatched[i]/1000.0);

   TCanvas *c = new TCanvas("c","c",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hAllTm->SetTitle("");
   hAllTm->GetXaxis()->SetTitle("t [ns]");
   hAllTm->SetLineWidth(3);
   hAllTm->SetLineColor(kGray+3);
   hAllTm->SetFillColorAlpha(kViolet-5,0.9);
   hAllTm->Draw();
   hMTm->SetLineWidth(3);
   hMTm->SetLineColor(kGray+3);
   hMTm->SetFillColorAlpha(kTeal-5,0.9);
   hMTm->Draw("same");
   auto lTm = new TLegend(0.8,0.76,0.92,0.93); 
   lTm->AddEntry(hAllTm,"All","f");
   lTm->AddEntry(hMTm,"Matched", "f");
   lTm->Draw();
   c->SaveAs("TmV4A_match_run530.pdf");

   TCanvas *d = new TCanvas("d","d",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hAllEn->SetTitle("");
   hAllEn->GetXaxis()->SetTitle("E [kadc]");
   hAllEn->SetLineWidth(3);
   hAllEn->SetLineColor(kGray+3);
   hAllEn->SetFillColorAlpha(kViolet-5,0.9);
   hAllEn->Draw();
   hMEn->SetLineWidth(3);
   hMEn->SetLineColor(kGray+3);
   hMEn->SetFillColorAlpha(kTeal-5,0.9);
   hMEn->Draw("same");
   auto lEn = new TLegend(0.80,0.76,0.92,0.93);
   lEn->AddEntry(hAllTm,"All","f");
   lEn->AddEntry(hMTm,"Matched", "f");
   lEn->Draw();
   d->SaveAs("EnV4A_match_run530.pdf");



}

int main() {
   VetoEff3();
   return 0;
} 
 
