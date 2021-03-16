///////////////////////////////////////////////
//                                           //
//              TimeWindow2.C                //
//                                           //                
//  Creates a plot of time difference for    // 
//  different energy ranges of the BGO.      //
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

void TimeWindow2(){
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
   gStyle->SetPadLeftMargin(0.06);
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

   std::vector<double> vMTime;
   std::vector<double> vLEnTime;
   std::vector<double> vREnTime;
   std::vector<double> vHEnTime;
   for (int n=0; n<vIDBGOBackA.size(); n++) {
      for (int k=0; k<vEvIDV4A.size(); k++) {
         if (vEvIDV4A[k] == vIDBGOBackA[n]) {
            if (vInstV4A[k] == 0) {
               vMTime.push_back(vTimeV4A[k]-vTmBGOBackA[n]); 
               if (vEnBGOBackA[n] < 500) {
                  vLEnTime.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
               } else if ((vEnBGOBackA[n] > 5000) && (vEnBGOBackA[n] < 15000)) {
                  vREnTime.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
               } else if (vEnBGOBackA[n] > 20000) {
                  vHEnTime.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
               }
            }
         }
      }
   }



   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m---------------------- Plotting --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

   TH1F *hMTime = new TH1F("hTime","hTime",35,-250.0,65.0); // All matched time
   TH1F *hLEnTime = new TH1F("hLEnTime","hLEnTime",45,-250.0,65.0); // Low energy
   TH1F *hREnTime = new TH1F("hREnTime","hREnTime",45,-250.0,65.0); // ROI energy
   TH1F *hREnTimeCP = new TH1F("hREnTimeCP","hREnTimeCP",45,-250.0,65.0); //ROI energy [copy]
   TH1F *hHEnTime = new TH1F("hHEnTime","hHEnTime",35,-250.0,65.0); // High energy
   for (int i=0; i<vMTime.size(); i++) hMTime->Fill(vMTime[i]);
   for (int i=0; i<vLEnTime.size(); i++) hLEnTime->Fill(vLEnTime[i]);
   for (int i=0; i<vREnTime.size(); i++) hREnTime->Fill(vREnTime[i]);
   for (int i=0; i<vREnTime.size(); i++) hREnTimeCP->Fill(vREnTime[i]);
   for (int i=0; i<vHEnTime.size(); i++) hHEnTime->Fill(vHEnTime[i]);


   TCanvas *c = new TCanvas("c","c",800,600);
   gStyle->SetOptStat(0);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   hMTime->SetTitle("");
   hMTime->GetXaxis()->SetTitle("t_{Veto} - t_{BGO} [ns]");
   hMTime->SetLineWidth(3);
   hMTime->SetLineColor(kGray+3);
   hMTime->SetFillColorAlpha(kOrange-5,0.3);
   hMTime->Draw();
   hLEnTime->SetLineWidth(3);
   hLEnTime->SetLineColor(kGray+3);
   hLEnTime->SetFillColorAlpha(kTeal-5,0.5);
   hLEnTime->Draw("same");
   hREnTime->SetLineWidth(3);
   hREnTime->SetLineColor(kGray+3);
   hREnTime->SetFillColorAlpha(kRed-7,0.7);
   hREnTime->Draw("same");
   hREnTimeCP->SetLineColor(kGray+3);
   hREnTimeCP->SetFillColorAlpha(kGray+3,0.7);
   hREnTimeCP->SetFillStyle(3344);
   hREnTimeCP->Draw("same");
   hHEnTime->SetLineWidth(3);
   hHEnTime->SetLineColor(kGray+3);
   hHEnTime->SetFillColorAlpha(kViolet-5,0.5);
   hHEnTime->Draw("same");
   auto legend = new TLegend(0.08,0.76,0.28,0.93); 
   legend->AddEntry(hMTime,"All energies","f");
   legend->AddEntry(hLEnTime,"Low energy","f");
   legend->AddEntry(hREnTime,"ROI energy","f");
   legend->AddEntry(hHEnTime,"High energy","f");
   legend->Draw();
   c->SaveAs("TmV4A_BGO_530.pdf");


}

int main() {
   TimeWindow2();
   return 0;
}  
