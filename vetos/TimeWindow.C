///////////////////////////////////////////////
//                                           //
//              TimeWindow.C                 //
//                                           //                
//  Creates a plot to decide on the time     // 
//  window for the Au analysis.              //
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

void TimeWindow(){
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
   gStyle->SetPadLeftMargin(0.18);
   //gStyle->SetPadTopMargin(0.32);
   gStyle->SetPadTopMargin(0.12);
   gStyle->SetPadRightMargin(0.16);
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

   std::string runnumber = "run549/549";
  
   std::vector<int> timemin;
   std::vector<int> timemax;

   timemin.push_back(-30); // gold
   timemax.push_back(30);
   timemin.push_back(100); // neutrons
   timemax.push_back(200);
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
   // Neutron search
   std::vector<double> vEnBGOBackAN;
   std::vector<double> vIDBGOBackAN;
   std::vector<double> vTmBGOBackAN;
   for (int s=0; s<vTimeBGOBackA.size(); s++) {
      if ((vTimeBGOBackA[s] > timemin[1]) && (vTimeBGOBackA[s] <timemax[1])) {
         if (vEkeVBGOBackA[s] < 100000) {
            vIDBGOBackAN.push_back(vEvIDBGOBackA[s]);
            vEnBGOBackAN.push_back(vEkeVBGOBackA[s]);
            vTmBGOBackAN.push_back(vTimeBGOBackA[s]);      
         }
      }
   }


   std::cout << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m---------------------- Matching --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;

   std::vector<double> vMatchedTime;
   std::vector<double> vMatchedGoodTime;
   for (int n=0; n<vIDBGOBackA.size(); n++) {
      for (int k=0; k<vEvIDV4A.size(); k++) {
         if (vEvIDV4A[k] == vIDBGOBackA[n]) {
            if (vInstV4A[k] == 0) {
               vMatchedGoodTime.push_back(vTimeV4A[k]-vTmBGOBackA[n]);  
            }
            vMatchedTime.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
         }
      }
   }

   // Neutron search
   std::vector<double> vMatchedTimeN;
   std::vector<double> vMatchedGoodTimeN;
   for (int n=0; n<vIDBGOBackAN.size(); n++) {
      for (int k=0; k<vEvIDV4A.size(); k++) {
         if (vEvIDV4A[k] == vIDBGOBackAN[n]) {
            if (vInstV4A[k] == 0) {
               vMatchedGoodTimeN.push_back(vTimeV4A[k]-vTmBGOBackAN[n]);
            }
            vMatchedTimeN.push_back(vTimeV4A[k]-vTmBGOBackAN[n]);
         }
      }
   }


   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

   TH1F *hTime = new TH1F("hTime","hTime",50,-50.0,500.0); // All matched time
   TH1F *hGoodTime = new TH1F("hGoodTime","hGoodTime",50,-50.0,500.0); // All matched time with incidence = 0
   for (int i=0; i<vMatchedGoodTime.size(); i++) {
      hGoodTime->Fill(vMatchedGoodTime[i]);
   }
   for (int i=0; i<vMatchedTime.size(); i++) {
      hTime->Fill(vMatchedTime[i]);
   }

   // Neutron search
   TH1F *hTimeN = new TH1F("hTimeN","hTimeN",50,-500.0,500.0); // All matched time
   TH1F *hGoodTimeN = new TH1F("hGoodTimeN","hGoodTimeN",50,-500.0,500.0); // All matched time with incidence = 0
   for (int i=0; i<vMatchedGoodTimeN.size(); i++) {
      hGoodTimeN->Fill(vMatchedGoodTimeN[i]);
   }
   for (int i=0; i<vMatchedTimeN.size(); i++) {
      hTimeN->Fill(vMatchedTimeN[i]);
   }


   TCanvas *c = new TCanvas("c","c",800,600);
   gStyle->SetOptStat(0);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   hTime->SetTitle("");
   hTime->GetXaxis()->SetTitle("t_{Veto} - t_{BGO} [ns]");
   hTime->SetLineWidth(3);
   hTime->SetLineColor(kViolet-5);
   hTime->Draw();
   hGoodTime->SetLineWidth(3);
   hGoodTime->SetLineColor(kTeal-5);
   hGoodTime->Draw("same");
   auto legend = new TLegend(0.64,0.71,0.84,0.87); 
   legend->AddEntry(hTime,"All veto events","f");
   legend->AddEntry(hGoodTime,"Good veto events","f");
   legend->Draw();
   //c->SaveAs("EffV4A_time_Au_549.pdf");

   TCanvas *cn = new TCanvas("cn","cn",800,600);
   gStyle->SetOptStat(0);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   hTimeN->SetTitle("");
   hTimeN->GetXaxis()->SetTitle("t_{Veto} - t_{BGO} [ns]");
   hTimeN->SetLineWidth(3);
   hTimeN->SetLineColor(kAzure+7);
   hTimeN->Draw();
   hGoodTimeN->SetLineWidth(3);
   hGoodTimeN->SetLineColor(kRed-7);
   hGoodTimeN->Draw("same");
   auto legendn = new TLegend(0.64,0.71,0.84,0.87); 
   legendn->AddEntry(hTimeN,"All veto events","f");
   legendn->AddEntry(hGoodTimeN,"Good veto events","f");
   legendn->Draw();
   //cn->SaveAs("EffV4A_time_window_549.pdf");




}

int main() {
   TimeWindow();
   return 0;
}  
