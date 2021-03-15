////////////////////////////////////////////////
//                                            //
//              EnergyWindow.C                //
//                                            //                
//  Compares the energy of the BGO for three  //
//  different time ranges.                    //
//                                            //
////////////////////////////////////////////////


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

void EnergyWindow(){
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

   std::string runnumber = "run549/549";
  
   std::vector<int> timemin;
   std::vector<int> timemax;

   timemin.push_back(-30);
   timemax.push_back(30);
   timemin.push_back(100);
   timemax.push_back(300);
   timemin.push_back(500);
   timemax.push_back(1000);   

   // Names of the files
   // BGOs
   std::string fileBGOBackA = runnumber+"_BGO_Back_A_prep.txt";

   // Vectors with detector names
   std::vector<std::string> BGOfiles;

   // BGOs
   BGOfiles.push_back(fileBGOBackA);


   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


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


   // Prompt Au
   std::vector<double> vEnBGOAu;
   std::vector<double> vIDBGOAu;
   std::vector<double> vTmBGOAu;
   for (int s=0; s<vTimeBGOBackA.size(); s++) {
      if ((vTimeBGOBackA[s] > timemin[0]) && (vTimeBGOBackA[s] <timemax[0])) {
         if (vEkeVBGOBackA[s] < 100000) {
            vIDBGOAu.push_back(vEvIDBGOBackA[s]);
            vEnBGOAu.push_back(vEkeVBGOBackA[s]);
            vTmBGOAu.push_back(vTimeBGOBackA[s]);
         }
      }
   }

   // Neutrons
   std::vector<double> vEnBGON;
   std::vector<double> vIDBGON;
   std::vector<double> vTmBGON;
   for (int s=0; s<vTimeBGOBackA.size(); s++) {
      if ((vTimeBGOBackA[s] > timemin[1]) && (vTimeBGOBackA[s] <timemax[1])) {
         if (vEkeVBGOBackA[s] < 100000) {
            vIDBGON.push_back(vEvIDBGOBackA[s]);
            vEnBGON.push_back(vEkeVBGOBackA[s]);
            vTmBGON.push_back(vTimeBGOBackA[s]);
         }
      }
   }

   // Late-time
   std::vector<double> vEnBGOL;
   std::vector<double> vIDBGOL;
   std::vector<double> vTmBGOL;
   for (int s=0; s<vTimeBGOBackA.size(); s++) {
      if ((vTimeBGOBackA[s] > timemin[2]) && (vTimeBGOBackA[s] <timemax[2])) {
         if (vEkeVBGOBackA[s] < 100000) {
            vIDBGOL.push_back(vEvIDBGOBackA[s]);
            vEnBGOL.push_back(vEkeVBGOBackA[s]);
            vTmBGOL.push_back(vTimeBGOBackA[s]);
         }
      }
   }



   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

   TH1F *hBGOAu = new TH1F("hBGOAu","hBGOAu",50,0,21.0); // Prompt Au
   TH1F *hBGON = new TH1F("hBGON","hBGON",100,0,21.0); // Neutrons
   TH1F *hBGOL = new TH1F("hBGOL","hBGOL",50,0,21.0); // Late time

   for (int i=0; i<vEnBGOAu.size(); i++) hBGOAu->Fill(vEnBGOAu[i]/1000.0);
   for (int i=0; i<vEnBGON.size(); i++) hBGON->Fill(vEnBGON[i]/1000.0);
   for (int i=0; i<vEnBGOL.size(); i++) hBGOL->Fill(vEnBGOL[i]/1000.0);

   TCanvas *c = new TCanvas("c","c",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hBGOAu->SetTitle("");
   hBGOAu->GetXaxis()->SetTitle("E [MeV]");
   hBGOAu->SetLineWidth(3);
   hBGOAu->SetLineColor(kGray+3);
   hBGOAu->SetFillColorAlpha(kRed-7,0.9);
   hBGOAu->Draw();
   hBGON->SetLineWidth(3);
   hBGON->SetLineColor(kGray+3);
   hBGON->SetFillColorAlpha(kViolet-5,0.7);
   hBGON->Draw("same");
   hBGOL->SetLineWidth(3);
   hBGOL->SetLineColor(kGray+3);
   hBGOL->SetFillColorAlpha(kTeal-5,0.5);
   hBGOL->Draw("same");
   auto lEn = new TLegend(0.8,0.76,0.92,0.93); 
   lEn->AddEntry(hBGOAu,"Gold","f");
   lEn->AddEntry(hBGON,"Neutrons", "f");
   lEn->AddEntry(hBGOL,"Late time","f");
   lEn->Draw();
   c->SaveAs("En_BGO_diff_times_run549.pdf");


}

int main() {
   EnergyWindow();
   return 0;
} 
 
