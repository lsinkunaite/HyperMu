//////////////////////////////////////////
//                                      //
//               VetoEff9.C             //
//                                      //         
//  Plots Efficiency of V4 OR V5 OR V6  //
//  versus the threshold in the BGO.    //
//                                      //
//////////////////////////////////////////


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

void VetoEff9() {
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
   gStyle->SetPadLeftMargin(0.12);
   //gStyle->SetPadTopMargin(0.32);
   gStyle->SetPadTopMargin(0.06);
   gStyle->SetPadRightMargin(0.08);
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

   // Uncomment for PE-target
   //std::string runnumber = "run530/530";
   // Uncomment for Au-target
   std::string runnumber = "run547/547";
  
   std::vector<int> timemin;
   std::vector<int> timemax;

   // Uncomment for PE-target
   //timemin.push_back(100);
   //timemax.push_back(1000);
   // Uncomment for Au-target
   timemin.push_back(-30);
   timemax.push_back(30);

   // Names of the files
   // Electron Vetos
   std::string fileVeto4A = runnumber+"_Veto4_A_prep.txt";
   std::string fileVeto4B = runnumber+"_Veto4_B_prep.txt";
   std::string fileVeto5A = runnumber+"_Veto5_A_prep.txt";
   std::string fileVeto5B = runnumber+"_Veto5_B_prep.txt";
   std::string fileVeto6A = runnumber+"_Veto6_A_prep.txt";
   std::string fileVeto6B = runnumber+"_Veto6_B_prep.txt";
   // BGOs
   std::string fileBGOBackA = runnumber+"_BGO_Back_A_prep.txt";

   // Vectors with detector names
   std::vector<std::string> BGOfiles;
   std::vector<std::string> Vetofiles;

   // Electron Vetos
   Vetofiles.push_back(fileVeto4A);
   Vetofiles.push_back(fileVeto4B);
   Vetofiles.push_back(fileVeto5A);
   Vetofiles.push_back(fileVeto5B);
   Vetofiles.push_back(fileVeto6A);
   Vetofiles.push_back(fileVeto6B);
   // BGOs
   BGOfiles.push_back(fileBGOBackA);


   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   

   // Veto_4_A
   std::ifstream fVeto4A(Vetofiles[0]);
   std::vector<double> vEvIDV4A;
   std::vector<double> vEdepV4A;
   std::vector<double> vTimeV4A;
   while (!fVeto4A.eof()) {  
      double EvIDV4A, InstV4A, EdepV4A, TimeV4A;
      fVeto4A >> EvIDV4A >> InstV4A >> EdepV4A >> TimeV4A;
      vEvIDV4A.push_back(EvIDV4A);
      vEdepV4A.push_back(EdepV4A);
      vTimeV4A.push_back(TimeV4A);
   }
   vEvIDV4A.pop_back();
   vEdepV4A.pop_back();
   vTimeV4A.pop_back();
   fVeto4A.close();


   // Veto_4_B
   std::ifstream fVeto4B(Vetofiles[1]);
   std::vector<double> vEvIDV4B;
   std::vector<double> vEdepV4B;
   std::vector<double> vTimeV4B;
   while (!fVeto4B.eof()) {  
      double EvIDV4B, InstV4B, EdepV4B, TimeV4B;
      fVeto4B >> EvIDV4B >> InstV4B >> EdepV4B >> TimeV4B;
      vEvIDV4B.push_back(EvIDV4B);
      vEdepV4B.push_back(EdepV4B);
      vTimeV4B.push_back(TimeV4B);
   }
   vEvIDV4B.pop_back();
   vEdepV4B.pop_back();
   vTimeV4B.pop_back();
   fVeto4B.close();


   // Veto_5_A
   std::ifstream fVeto5A(Vetofiles[2]);
   std::vector<double> vEvIDV5A;
   std::vector<double> vEdepV5A;
   std::vector<double> vTimeV5A;
   while (!fVeto5A.eof()) {
      double EvIDV5A, InstV5A, EdepV5A, TimeV5A;
      fVeto5A >> EvIDV5A >> InstV5A >> EdepV5A >> TimeV5A;
      vEvIDV5A.push_back(EvIDV5A);
      vEdepV5A.push_back(EdepV5A);
      vTimeV5A.push_back(TimeV5A);
   }
   vEvIDV5A.pop_back();
   vEdepV5A.pop_back();
   vTimeV5A.pop_back();
   fVeto5A.close();


   // Veto_5_B
   std::ifstream fVeto5B(Vetofiles[3]);
   std::vector<double> vEvIDV5B;
   std::vector<double> vEdepV5B;
   std::vector<double> vTimeV5B;
   while (!fVeto5B.eof()) {
      double EvIDV5B, InstV5B, EdepV5B, TimeV5B;
      fVeto5B >> EvIDV5B >> InstV5B >> EdepV5B >> TimeV5B;
      vEvIDV5B.push_back(EvIDV5B);
      vEdepV5B.push_back(EdepV5B);
      vTimeV5B.push_back(TimeV5B);
   }
   vEvIDV5B.pop_back();
   vEdepV5B.pop_back();
   vTimeV5B.pop_back();
   fVeto5B.close();

   
   // Veto_6_A
   std::ifstream fVeto6A(Vetofiles[4]);
   std::vector<double> vEvIDV6A;
   std::vector<double> vEdepV6A;
   std::vector<double> vTimeV6A;
   while (!fVeto6A.eof()) {
      double EvIDV6A, InstV6A, EdepV6A, TimeV6A;
      fVeto6A >> EvIDV6A >> InstV6A >> EdepV6A >> TimeV6A;
      vEvIDV6A.push_back(EvIDV6A);
      vEdepV6A.push_back(EdepV6A);
      vTimeV6A.push_back(TimeV6A);
   }
   vEvIDV6A.pop_back();
   vEdepV6A.pop_back();
   vTimeV6A.pop_back();
   fVeto6A.close();


   // Veto_6_B
   std::ifstream fVeto6B(Vetofiles[5]);
   std::vector<double> vEvIDV6B;
   std::vector<double> vEdepV6B;
   std::vector<double> vTimeV6B;
   while (!fVeto6B.eof()) {
      double EvIDV6B, InstV6B, EdepV6B, TimeV6B;
      fVeto6B >> EvIDV6B >> InstV6B >> EdepV6B >> TimeV6B;
      vEvIDV6B.push_back(EvIDV6B);
      vEdepV6B.push_back(EdepV6B);
      vTimeV6B.push_back(TimeV6B);
   }
   vEvIDV6B.pop_back();
   vEdepV6B.pop_back();
   vTimeV6B.pop_back();
   fVeto6B.close();


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


   // Veto_4_B
   std::vector<double> vInstV4B; // Vector of repeating instances
   int EvIDV4B;
   for (int s=0; s<vEvIDV4B.size(); s++) {
      if ((s > 0) && (s < (vEvIDV4B.size()-1))) {
         if ((vEvIDV4B[s] == vEvIDV4B[s+1]) || (vEvIDV4B[s] == vEvIDV4B[s-1])) {
            vInstV4B.push_back(1);
         } else {
            vInstV4B.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDV4B[s] == vEvIDV4B[s+1]) {
            vInstV4B.push_back(1);
         } else {
            vInstV4B.push_back(0);
         }
      } else if (vEvIDV4B[s] == vEvIDV4B[s-1]) {
         vInstV4B.push_back(1);
      } else {
         vInstV4B.push_back(0);
      }
   }


   // Veto_5_A
   std::vector<double> vInstV5A; // Vector of repeating instances
   int EvIDV5A;
   for (int s=0; s<vEvIDV5A.size(); s++) {
      if ((s > 0) && (s < (vEvIDV5A.size()-1))) {
         if ((vEvIDV5A[s] == vEvIDV5A[s+1]) || (vEvIDV5A[s] == vEvIDV5A[s-1])) {
            vInstV5A.push_back(1);
         } else {
            vInstV5A.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDV5A[s] == vEvIDV5A[s+1]) {
            vInstV5A.push_back(1);
         } else {
            vInstV5A.push_back(0);
         }
      } else if (vEvIDV5A[s] == vEvIDV5A[s-1]) {
         vInstV5A.push_back(1);
      } else {
         vInstV5A.push_back(0);
      }
   }


   // Veto_5_B
   std::vector<double> vInstV5B; // Vector of repeating instances
   int EvIDV5B;
   for (int s=0; s<vEvIDV5B.size(); s++) {
      if ((s > 0) && (s < (vEvIDV5B.size()-1))) {
         if ((vEvIDV5B[s] == vEvIDV5B[s+1]) || (vEvIDV5B[s] == vEvIDV5B[s-1])) {
            vInstV5B.push_back(1);
         } else {
            vInstV5B.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDV5B[s] == vEvIDV5B[s+1]) {
            vInstV5B.push_back(1);
         } else {
            vInstV5B.push_back(0);
         }
      } else if (vEvIDV5B[s] == vEvIDV5B[s-1]) {
         vInstV5B.push_back(1);
      } else {
         vInstV5B.push_back(0);
      }
   }


   // Veto_6_A
   std::vector<double> vInstV6A; // Vector of repeating instances
   int EvIDV6A;
   for (int s=0; s<vEvIDV6A.size(); s++) {
      if ((s > 0) && (s < (vEvIDV6A.size()-1))) {
         if ((vEvIDV6A[s] == vEvIDV6A[s+1]) || (vEvIDV6A[s] == vEvIDV6A[s-1])) {
            vInstV6A.push_back(1);
         } else {
            vInstV6A.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDV6A[s] == vEvIDV6A[s+1]) {
            vInstV6A.push_back(1);
         } else {
            vInstV6A.push_back(0);
         }
      } else if (vEvIDV6A[s] == vEvIDV6A[s-1]) {
         vInstV6A.push_back(1);
      } else {
         vInstV6A.push_back(0);
      }
   }


   // Veto_6_B
   std::vector<double> vInstV6B; // Vector of repeating instances
   int EvIDV6B;
   for (int s=0; s<vEvIDV6B.size(); s++) {
      if ((s > 0) && (s < (vEvIDV6B.size()-1))) {
         if ((vEvIDV6B[s] == vEvIDV6B[s+1]) || (vEvIDV6B[s] == vEvIDV6B[s-1])) {
            vInstV6B.push_back(1);
         } else {
            vInstV6B.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDV6B[s] == vEvIDV6B[s+1]) {
            vInstV6B.push_back(1);
         } else {
            vInstV6B.push_back(0);
         }
      } else if (vEvIDV6B[s] == vEvIDV6B[s-1]) {
         vInstV6B.push_back(1);
      } else {
         vInstV6B.push_back(0);
      }
   }


   // BGO_Back_A
   std::vector<double> vEnBGOBackA;
   std::vector<double> vIDBGOBackA;
   std::vector<double> vTmBGOBackA;
   for (int s=0; s<vTimeBGOBackA.size(); s++) {
      if ((vTimeBGOBackA[s] > timemin[0]) && (vTimeBGOBackA[s] <timemax[0])) {
         // Uncomment for PE-target  
         //if ((vEkeVBGOBackA[s] >= 5000) && (vEkeVBGOBackA[s] <= 20000)) {
         // Uncomment for Au-target
         if ((vEkeVBGOBackA[s] >= 500) && (vEkeVBGOBackA[s] <= 6000)) {
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

   const int nbins = 15;
   double Estep = 1500.0/(nbins);
   std::vector<double> Ethr;
   Ethr.push_back(0.0);
   for (int i=1; i<=nbins; i++) Ethr.push_back(Ethr[i-1]+Estep);

   std::vector<double> Effand1;
   std::vector<double> Effand2;
   std::vector<double> Effand3;
   std::vector<double> Effor1;
   std::vector<double> Effor2;
   std::vector<double> Effor3;
   std::vector<double> EffVetoA1;
   std::vector<double> EffVetoA2;
   std::vector<double> EffVetoA3; 
   std::vector<double> EffVetoB1;
   std::vector<double> EffVetoB2;
   std::vector<double> EffVetoB3;
   
   std::vector<double> EffAllAnd1;
   std::vector<double> EffAllAnd2;
   std::vector<double> EffAllAnd3;
   std::vector<double> EffAnd1;
   std::vector<double> EffAnd2;
   std::vector<double> EffAnd3;
   std::vector<double> EffOr1;
   std::vector<double> EffOr2;
   std::vector<double> EffOr3;

   for (int m=0; m<Ethr.size(); m++) {
      double MCountV4A1=0, MCountV4A2=0, MCountV4A3=0, TCountV4A=0;
      double MCountV4B1=0, MCountV4B2=0, MCountV4B3=0, TCountV4B=0;
      double MCountV5A1=0, MCountV5A2=0, MCountV5A3=0, TCountV5A=0;
      double MCountV5B1=0, MCountV5B2=0, MCountV5B3=0, TCountV5B=0;
      double MCountV6A1=0, MCountV6A2=0, MCountV6A3=0, TCountV6A=0;
      double MCountV6B1=0, MCountV6B2=0, MCountV6B3=0, TCountV6B=0;

      std::vector<double> vMBGOV4A1;
      std::vector<double> vMBGOV4A2;
      std::vector<double> vMBGOV4A3;
      std::vector<double> vMBGOV4B1;
      std::vector<double> vMBGOV4B2;
      std::vector<double> vMBGOV4B3;
      std::vector<double> vMBGOV5A1;
      std::vector<double> vMBGOV5A2;
      std::vector<double> vMBGOV5A3;
      std::vector<double> vMBGOV5B1;
      std::vector<double> vMBGOV5B2;
      std::vector<double> vMBGOV5B3;
      std::vector<double> vMBGOV6A1;
      std::vector<double> vMBGOV6A2;
      std::vector<double> vMBGOV6A3;
      std::vector<double> vMBGOV6B1;
      std::vector<double> vMBGOV6B2;
      std::vector<double> vMBGOV6B3;

      for (int n=0; n<vIDBGOBackA.size(); n++) {
         // Veto_4_A
         int UnmatchedV4A1 = 0;
         int UnmatchedV4A2 = 0;
         int UnmatchedV4A3 = 0;
         int GoodEventV4A = 0;
         for (int k=0; k<vEvIDV4A.size(); k++) {
            if (vEvIDV4A[k] == vIDBGOBackA[n]) {
               if (vInstV4A[k] == 0) {
                  if (vEdepV4A[k] >= Ethr[m]) {
                     // Uncomment for PE-target
                     //if ((vTimeV4A[k] >= (vTmBGOBackA[n]-250)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+65))) {
                     // Uncomment for Au-target
                     if ((vTimeV4A[k] >= (vTmBGOBackA[n]-50)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+450))) {
                        // Uncomment for PE-target
                        //if ((vTimeV4A[k] >= (vTmBGOBackA[n]-60)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+35))) {
                        // Uncomment for PE-target
                        if ((vTimeV4A[k] >= (vTmBGOBackA[n]-40)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+160))) {
                           // Uncomment for PE-target
                           //if ((vTimeV4A[k] >= (vTmBGOBackA[n]-30)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+30))) {
                           // Uncomment for Au-target
                           if ((vTimeV4A[k] >= (vTmBGOBackA[n]-25)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+25))) {
                              MCountV4A1++;
                              UnmatchedV4A1 = 1;
                           }
                           MCountV4A2++;
                           UnmatchedV4A2 = 1;
                        }
                        MCountV4A3++;
                        UnmatchedV4A3 = 1;
                     }
                  }
               } else {
                  GoodEventV4A = 1;
               }
            }
         }
         if (GoodEventV4A == 0) {
            TCountV4A++;
            if (UnmatchedV4A3 == 0) {
               vMBGOV4A3.push_back(0);
            } else {
               vMBGOV4A3.push_back(1);
            }
            if (UnmatchedV4A2 == 0) {
               vMBGOV4A2.push_back(0);
            } else {
               vMBGOV4A2.push_back(1);
            }
            if (UnmatchedV4A1 == 0) {
               vMBGOV4A1.push_back(0);
            } else {
               vMBGOV4A1.push_back(1);
            } 
         } else {
            vMBGOV4A1.push_back(-1);
            vMBGOV4A2.push_back(-1);
            vMBGOV4A3.push_back(-1);
         }   

         // Veto_4_B
         int UnmatchedV4B1 = 0;
         int UnmatchedV4B2 = 0;
         int UnmatchedV4B3 = 0;
         int GoodEventV4B = 0;
         for (int k=0; k<vEvIDV4B.size(); k++) {
            if (vEvIDV4B[k] == vIDBGOBackA[n]) {
               if (vInstV4B[k] == 0) {
                  if (vEdepV4B[k] >= Ethr[m]) {
                     // Uncomment for PE-target
                     //if ((vTimeV4B[k] >= (vTmBGOBackA[n]-250)) && (vTimeV4B[k] <= (vTmBGOBackA[n]+65))) {
                     // Uncomment for Au-target
                     if ((vTimeV4B[k] >= (vTmBGOBackA[n]-50)) && (vTimeV4B[k] <= (vTmBGOBackA[n]+450))) {
                        // Uncomment for PE-target
                        //if ((vTimeV4B[k] >= (vTmBGOBackA[n]-60)) && (vTimeV4B[k] <= (vTmBGOBackA[n]+35))) {
                        // Uncomment for Au-target
                        if ((vTimeV4B[k] >= (vTmBGOBackA[n]-40)) && (vTimeV4B[k] <= (vTmBGOBackA[n]+160))) {
                           // Uncomment for PE-target
                           //if ((vTimeV4B[k] >= (vTmBGOBackA[n]-30)) && (vTimeV4B[k] <= (vTmBGOBackA[n]+30))) {
                           // Uncomment for Au-target
                           if ((vTimeV4B[k] >= (vTmBGOBackA[n]-25)) && (vTimeV4B[k] <= (vTmBGOBackA[n]+25))) {
                              MCountV4B1++;
                              UnmatchedV4B1 = 1;
                           }
                           MCountV4B2++;
                           UnmatchedV4B2 = 1;
                        }
                        MCountV4B3++;
                        UnmatchedV4B3 = 1;
                     }
                  }
               } else {
                  GoodEventV4B = 1;
               }
            }
         } 
         if (GoodEventV4B == 0) {
            TCountV4B++;
            if (UnmatchedV4B3 == 0) {
               vMBGOV4B3.push_back(0);
            } else {
               vMBGOV4B3.push_back(1);
            }
            if (UnmatchedV4B2 == 0) {
                  vMBGOV4B2.push_back(0);
            } else {
               vMBGOV4B2.push_back(1);
            }
            if (UnmatchedV4B1 == 0) {
               vMBGOV4B1.push_back(0);
            } else {
               vMBGOV4B1.push_back(1);
            }
         } else {
            vMBGOV4B1.push_back(-1);
            vMBGOV4B2.push_back(-1);
            vMBGOV4B3.push_back(-1);
         }

         // Veto_5_A
         int UnmatchedV5A1 = 0;
         int UnmatchedV5A2 = 0;
         int UnmatchedV5A3 = 0;
         int GoodEventV5A = 0;
         for (int k=0; k<vEvIDV5A.size(); k++) {
            if (vEvIDV5A[k] == vIDBGOBackA[n]) {
               if (vInstV5A[k] == 0) {
                  if (vEdepV5A[k] >= Ethr[m]) {
                     // Uncomment for PE-target
                     //if ((vTimeV5A[k] >= (vTmBGOBackA[n]-250)) && (vTimeV5A[k] <= (vTmBGOBackA[n]+65))) {
                     // Uncomment for Au-target
                     if ((vTimeV5A[k] >= (vTmBGOBackA[n]-50)) && (vTimeV5A[k] <= (vTmBGOBackA[n]+450))) {
                        // Uncomment for PE-target
                        //if ((vTimeV5A[k] >= (vTmBGOBackA[n]-60)) && (vTimeV5A[k] <= (vTmBGOBackA[n]+35))) {
                        // Uncomment for Au-target
                        if ((vTimeV5A[k] >= (vTmBGOBackA[n]-40)) && (vTimeV5A[k] <= (vTmBGOBackA[n]+160))) {
                           // Uncomment for PE-target
                           //if ((vTimeV5A[k] >= (vTmBGOBackA[n]-30)) && (vTimeV5A[k] <= (vTmBGOBackA[n]+30))) {
                           // Uncomment for Au-target
                           if ((vTimeV5A[k] >= (vTmBGOBackA[n]-25)) && (vTimeV5A[k] <= (vTmBGOBackA[n]+25))) {
                              MCountV5A1++;
                              UnmatchedV5A1 = 1;
                           }
                           MCountV5A2++;
                           UnmatchedV5A2 = 1;
                        }
                        MCountV5A3++;
                        UnmatchedV5A3 = 1;
                     }
                  }
               } else {
                  GoodEventV5A = 1;
               }
            }
         }
         if (GoodEventV5A == 0) {
            TCountV5A++;
            if (UnmatchedV5A3 == 0) {
               vMBGOV5A3.push_back(0);
            } else {
               vMBGOV5A3.push_back(1);
            }
            if (UnmatchedV5A2 == 0) {
               vMBGOV5A2.push_back(0);
            } else {
               vMBGOV5A2.push_back(1);
            }
            if (UnmatchedV5A1 == 0) {
               vMBGOV5A1.push_back(0); 
            } else {
               vMBGOV5A1.push_back(1);
            }
         } else {
            vMBGOV5A1.push_back(-1);
            vMBGOV5A2.push_back(-1);
            vMBGOV5A3.push_back(-1);
         }        

         // Veto_5_B
         int UnmatchedV5B1 = 0;
         int UnmatchedV5B2 = 0;
         int UnmatchedV5B3 = 0;
         int GoodEventV5B = 0;
         for (int k=0; k<vEvIDV5B.size(); k++) {
            if (vEvIDV5B[k] == vIDBGOBackA[n]) {
               if (vInstV5B[k] == 0) {
                  if (vEdepV5B[k] >= Ethr[m]) {
                     // Uncomment for PE-target
                     //if ((vTimeV5B[k] >= (vTmBGOBackA[n]-250)) && (vTimeV5B[k] <= (vTmBGOBackA[n]+65))) {
                     // Uncomment for Au-target
                     if ((vTimeV5B[k] >= (vTmBGOBackA[n]-50)) && (vTimeV5B[k] <= (vTmBGOBackA[n]+450))) {
                        // Uncomment for PE-target
                        //if ((vTimeV5B[k] >= (vTmBGOBackA[n]-60)) && (vTimeV5B[k] <= (vTmBGOBackA[n]+35))) {
                        // Uncomment for Au-target
                        if ((vTimeV5B[k] >= (vTmBGOBackA[n]-40)) && (vTimeV5B[k] <= (vTmBGOBackA[n]+160))) {
                           // Uncomment for PE-target
                           //if ((vTimeV5B[k] >= (vTmBGOBackA[n]-30)) && (vTimeV5B[k] <= (vTmBGOBackA[n]+30))) {
                           // Uncomment for Au-target
                           if ((vTimeV5B[k] >= (vTmBGOBackA[n]-25)) && (vTimeV5B[k] <= (vTmBGOBackA[n]+25))) {
                              MCountV5B1++;
                              UnmatchedV5B1 = 1;
                           }
                           MCountV5B2++;
                           UnmatchedV5B2 = 1;
                        }
                        MCountV5B3++;
                        UnmatchedV5B3 = 1;
                     }
                  }
               } else {
                  GoodEventV5B = 1;
               }
            }
         }
         if (GoodEventV5B == 0) {
            TCountV5B++;
            if (UnmatchedV5B3 == 0) {
               vMBGOV5B3.push_back(0);
            } else {
               vMBGOV5B3.push_back(1);
            }
            if (UnmatchedV5B2 == 0) {
               vMBGOV5B2.push_back(0);
            } else {
               vMBGOV5B2.push_back(1);
            }
            if (UnmatchedV5B1 == 0) {
               vMBGOV5B1.push_back(0);
            } else {
               vMBGOV5B1.push_back(1);
            }
         } else {
            vMBGOV5B1.push_back(-1);
            vMBGOV5B2.push_back(-1);
            vMBGOV5B3.push_back(-1);
         }

         // Veto_6_A
         int UnmatchedV6A1 = 0;
         int UnmatchedV6A2 = 0;
         int UnmatchedV6A3 = 0;
         int GoodEventV6A = 0;
         for (int k=0; k<vEvIDV6A.size(); k++) {
            if (vEvIDV6A[k] == vIDBGOBackA[n]) {
               if (vInstV6A[k] == 0) {
                  if (vEdepV6A[k] >= Ethr[m]) {
                     // Uncomment for PE-target
                     //if ((vTimeV6A[k] >= (vTmBGOBackA[n]-250)) && (vTimeV6A[k] <= (vTmBGOBackA[n]+65))) {
                     // Uncomment for Au-target
                     if ((vTimeV5A[k] >= (vTmBGOBackA[n]-50)) && (vTimeV5A[k] <= (vTmBGOBackA[n]+450))) {
                        // Uncomment for PE-target
                        //if ((vTimeV6A[k] >= (vTmBGOBackA[n]-60)) && (vTimeV6A[k] <= (vTmBGOBackA[n]+35))) {
                        // Uncomment for Au-target
                        if ((vTimeV6A[k] >= (vTmBGOBackA[n]-40)) && (vTimeV6A[k] <= (vTmBGOBackA[n]+160))) {
                           // Uncomment for PE-target
                           //if ((vTimeV6A[k] >= (vTmBGOBackA[n]-30)) && (vTimeV6A[k] <= (vTmBGOBackA[n]+30))) {
                           // Uncomment for Au-target
                           if ((vTimeV6A[k] >= (vTmBGOBackA[n]-25)) && (vTimeV6A[k] <= (vTmBGOBackA[n]+25))) {
                              MCountV6A1++;
                              UnmatchedV6A1 = 1;
                           }
                           MCountV6A2++;
                           UnmatchedV6A2 = 1;
                        }
                        MCountV6A3++;
                        UnmatchedV6A3 = 1;
                     }
                  }
               } else {
                  GoodEventV6A = 1;
               }
            }
         }
         if (GoodEventV6A == 0) {
            TCountV6A++;
            if (UnmatchedV6A3 == 0) {
               vMBGOV6A3.push_back(0);
            } else {
               vMBGOV6A3.push_back(1);
            }
            if (UnmatchedV6A2 == 0) {
               vMBGOV6A2.push_back(0);
            } else {
               vMBGOV6A2.push_back(1);
            }
            if (UnmatchedV6A1 == 0) {
               vMBGOV6A1.push_back(0);
            } else {
               vMBGOV6A1.push_back(1);
            }
         } else {
            vMBGOV6A1.push_back(-1);
            vMBGOV6A2.push_back(-1);
            vMBGOV6A3.push_back(-1);
         }

         // Veto_6_B
         int UnmatchedV6B1 = 0;
         int UnmatchedV6B2 = 0;
         int UnmatchedV6B3 = 0;
         int GoodEventV6B = 0;
         for (int k=0; k<vEvIDV6B.size(); k++) {
            if (vEvIDV6B[k] == vIDBGOBackA[n]) {
               if (vInstV6B[k] == 0) {
                  if (vEdepV6B[k] >= Ethr[m]) {
                     // Uncomment for PE-target
                     //if ((vTimeV6B[k] >= (vTmBGOBackA[n]-250)) && (vTimeV6B[k] <= (vTmBGOBackA[n]+65))) {
                     // Uncomment for Au-target
                     if ((vTimeV6B[k] >= (vTmBGOBackA[n]-50)) && (vTimeV6B[k] <= (vTmBGOBackA[n]+450))) {
                        // Uncomment for PE-target
                        //if ((vTimeV6B[k] >= (vTmBGOBackA[n]-60)) && (vTimeV6B[k] <= (vTmBGOBackA[n]+35))) {
                        // Uncomment for Au-target
                        if ((vTimeV6B[k] >= (vTmBGOBackA[n]-40)) && (vTimeV6B[k] <= (vTmBGOBackA[n]+160))) {
                           // Uncomment for PE-target
                           //if ((vTimeV6B[k] >= (vTmBGOBackA[n]-30)) && (vTimeV6B[k] <= (vTmBGOBackA[n]+30))) {
                           // Uncomment for Au-target
                           if ((vTimeV6B[k] >= (vTmBGOBackA[n]-25)) && (vTimeV6B[k] <= (vTmBGOBackA[n]+25))) {
                              MCountV6B1++;
                              UnmatchedV6B1 = 1;
                           }
                           MCountV6B2++;
                           UnmatchedV6B2 = 1;
                        }
                        MCountV6B3++;
                        UnmatchedV6B3 = 1;
                     }
                  }
               } else {
                  GoodEventV6B = 1;
               }
            }
         }
         if (GoodEventV6B == 0) {
            TCountV6B++;
            if (UnmatchedV6B3 == 0) {
               vMBGOV6B3.push_back(0);
            } else {
               vMBGOV6B3.push_back(1);
            }
            if (UnmatchedV6B2 == 0) {
               vMBGOV6B2.push_back(0);
            } else {
               vMBGOV6B2.push_back(1);
            }
            if (UnmatchedV6B1 == 0) {
               vMBGOV6B1.push_back(0);
            } else {
               vMBGOV6B1.push_back(1);
            }
         } else {
            vMBGOV6B1.push_back(-1);
            vMBGOV6B2.push_back(-1);      
            vMBGOV6B3.push_back(-1);
         }

      }
      //std::cout << "Ethr = " << Ethr[m] << ", V4A :: Eff1 = " << MCountA1/TCountA << ", Eff2 = " << MCountA2/TCountA << ", Eff3 = " << MCountA3/TCountA << std::endl;
      //std::cout << "Ethr = " << Ethr[m] << ", V4B :: Eff1 = " << MCountB1/TCountB << ", Eff2 =  " << MCountB2/TCountB << ", Eff3 = " << MCountB3/TCountB << std::endl;
      std::cout << std::endl;
      EffVetoA1.push_back(MCountV4A1/TCountV4A);
      EffVetoA2.push_back(MCountV4A2/TCountV4A);
      EffVetoA3.push_back(MCountV4A3/TCountV4A);
      EffVetoB1.push_back(MCountV4B1/TCountV4B);
      EffVetoB2.push_back(MCountV4B2/TCountV4B);
      EffVetoB3.push_back(MCountV4B3/TCountV4B);

      // EDIT FROM HERE !!! /////////////////////////////////////////////////////////////////////////////////////
      
      // Veto_4_A && Veto_4_B
      double V4ANDCount1 = 0;
      double V4ANDCount2 = 0;
      double V4ANDCount3 = 0;
      double V4ORCount1 = 0;
      double V4ORCount2 = 0;
      double V4ORCount3 = 0;
      double V4TotCount1 = 0;
      double V4TotCount2 = 0;
      double V4TotCount3 = 0;

      // Veto_4_A_B && Veto_5_A_B && Veto_6_A_B
      double ALLANDCount1 = 0;
      double ALLANDCount2 = 0;
      double ALLANDCount3 = 0;
      double ANDCount1 = 0;
      double ANDCount2 = 0;
      double ANDCount3 = 0;
      double ORCount1 = 0;
      double ORCount2 = 0;
      double ORCount3 = 0;
      double TotCount1 = 0;
      double TotCount2 = 0;
      double TotCount3 = 0;

      for (int j=0; j<vMBGOV4B1.size(); j++) {
         // Large time selection
         if ((vMBGOV4A3[j] == 1) && (vMBGOV4B3[j] == 1)) {
            V4ANDCount3++;
            V4ORCount3++;
            V4TotCount3++;
         } else if ((vMBGOV4A3[j] == 1) || (vMBGOV4B3[j] == 1)) {
            V4ORCount3++;
            V4TotCount3++;
         } else if ((vMBGOV4A3[j] + vMBGOV4B3[j]) == 0) {
            V4TotCount3++;
         }
         // Intermediate time selection
         if ((vMBGOV4A2[j] == 1) && (vMBGOV4B2[j] == 1)) {
            V4ANDCount2++;
            V4ORCount2++;
            V4TotCount2++;
         } else if ((vMBGOV4A2[j] == 1) || (vMBGOV4B2[j] == 1)) {
            V4ORCount2++;
            V4TotCount2++;
         } else if ((vMBGOV4A2[j] + vMBGOV4B2[j]) == 0) {
            V4TotCount2++;
         }
         // Small time selection
         if ((vMBGOV4A1[j] == 1) && (vMBGOV4B1[j] == 1)) {
            V4ANDCount1++;
            V4ORCount1++;
            V4TotCount1++;
         } else if ((vMBGOV4A1[j] == 1) || (vMBGOV4B1[j] == 1)) {
            V4ORCount1++;
            V4TotCount1++;
         } else if ((vMBGOV4A1[j] + vMBGOV4B1[j]) == 0) {
            V4TotCount1++;
         }
      }
      Effand1.push_back(V4ANDCount1/V4TotCount1);
      Effor1.push_back(V4ORCount1/V4TotCount1);
      Effand2.push_back(V4ANDCount2/V4TotCount2);
      Effor2.push_back(V4ORCount2/V4TotCount2);
      Effand3.push_back(V4ANDCount3/V4TotCount3);
      Effor3.push_back(V4ORCount3/V4TotCount3);

      for (int j=0; j<vMBGOV4B1.size(); j++) {
         // Large time selection
         if ((vMBGOV4A3[j] == 1) && (vMBGOV4B3[j] == 1) && (vMBGOV5A3[j] == 1) && (vMBGOV5B3[j] == 1) && (vMBGOV6A3[j] == 1) && (vMBGOV6B3[j] == 1)) {
            ALLANDCount3++;
            ANDCount3++; 
            ORCount3++;
            TotCount3++;
         } else if (((vMBGOV4A3[j] == 1) || (vMBGOV4B3[j] == 1)) && ((vMBGOV5A3[j] == 1) || (vMBGOV5B3[j] == 1)) && ((vMBGOV6A3[j] == 1) || (vMBGOV6B3[j] == 1))) {
            ANDCount3++;
            ORCount3++;
            TotCount3++;
         } else if ((vMBGOV4A3[j] == 1) || (vMBGOV4B3[j] == 1) || (vMBGOV5A3[j] == 1) || (vMBGOV5B3[j] == 1) || (vMBGOV6A3[j] == 1) || (vMBGOV6B3[j] == 1)) {
            ORCount3++;
            TotCount3++;
         } else if ((vMBGOV4A3[j] + vMBGOV4B3[j] + vMBGOV5A3[j] + vMBGOV5B3[j] + vMBGOV6A3[j] + vMBGOV6B3[j]) == 0) {
            TotCount3++;
         }  
         // Intermediate time selection
         if ((vMBGOV4A2[j] == 1) && (vMBGOV4B2[j] == 1) && (vMBGOV5A2[j] == 1) && (vMBGOV5B2[j] == 1) && (vMBGOV6A2[j] == 1) && (vMBGOV6B2[j] == 1)) {
            ALLANDCount2++;
            ANDCount2++; 
            ORCount2++;
            TotCount2++;
         } else if (((vMBGOV4A2[j] == 1) || (vMBGOV4B2[j] == 1)) && ((vMBGOV5A2[j] == 1) || (vMBGOV5B2[j] == 1)) && ((vMBGOV6A2[j] == 1) || (vMBGOV6B2[j] == 1))) {
            ANDCount2++;
            ORCount2++;
            TotCount2++; 
         } else if ((vMBGOV4A2[j] == 1) || (vMBGOV4B2[j] == 1) || (vMBGOV5A2[j] == 1) || (vMBGOV5B2[j] == 1) || (vMBGOV6A2[j] == 1) || (vMBGOV6B2[j] == 1)) {
            ORCount2++;
            TotCount2++;
         } else if ((vMBGOV4A2[j] + vMBGOV4B2[j] + vMBGOV5A2[j] + vMBGOV5B2[j] + vMBGOV6A2[j] + vMBGOV6B2[j]) == 0) {
            TotCount2++;
         }  
         // Small time selection
         if ((vMBGOV4A1[j] == 1) && (vMBGOV4B1[j] == 1) && (vMBGOV5A1[j] == 1) && (vMBGOV5B1[j] == 1) && (vMBGOV6A1[j] == 1) && (vMBGOV6B1[j] == 1)) {
            ALLANDCount1++;
            ANDCount1++;        
            ORCount1++;
            TotCount1++;
         } else if (((vMBGOV4A1[j] == 1) || (vMBGOV4B1[j] == 1)) && ((vMBGOV5A1[j] == 1) || (vMBGOV5B1[j] == 1)) && ((vMBGOV6A1[j] == 1) || (vMBGOV6B1[j] == 1))) {
            ANDCount1++;
            ORCount1++;
            TotCount1++;       
         } else if ((vMBGOV4A1[j] == 1) || (vMBGOV4B1[j] == 1) || (vMBGOV5A1[j] == 1) || (vMBGOV5B1[j] == 1) || (vMBGOV6A1[j] == 1) || (vMBGOV6B1[j] == 1)) {
            ORCount1++;
            TotCount1++;
         } else if ((vMBGOV4A1[j] + vMBGOV4B1[j] + vMBGOV5A1[j] + vMBGOV5B1[j] + vMBGOV6A1[j] + vMBGOV6B1[j]) == 0) {
            TotCount1++;
         }
      }

      EffAllAnd1.push_back(ALLANDCount1/TotCount1);
      EffAllAnd2.push_back(ALLANDCount2/TotCount2);
      EffAllAnd3.push_back(ALLANDCount3/TotCount3);
      EffAnd1.push_back(ANDCount1/TotCount1);
      EffAnd2.push_back(ANDCount2/TotCount2);
      EffAnd3.push_back(ANDCount3/TotCount3);
      EffOr1.push_back(ORCount1/TotCount1);
      EffOr2.push_back(ORCount2/TotCount2);
      EffOr3.push_back(ORCount3/TotCount3);

      std::cout << "Ethr = " << Ethr[m] << ", Eff1 = " << EffOr1[m] << ", Eff2 = " << EffOr2[m] << " Effor3 = " << EffOr3[m] << std::endl;

   }


   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

   // Efficiency V4_A || V4_B
   float Effor3arr[nbins+1] = {}; 
   // Threshold
   float Ethrarr[nbins+1] = {};
   // Efficiency V4, V5, V6
   float EffAllAnd1arr[nbins+1] = {};
   float EffAllAnd2arr[nbins+1] = {};
   float EffAllAnd3arr[nbins+1] = {};
   float EffAnd1arr[nbins+1] = {};
   float EffAnd2arr[nbins+1] = {};
   float EffAnd3arr[nbins+1] = {};
   float EffOr1arr[nbins+1] = {};
   float EffOr2arr[nbins+1] = {};
   float EffOr3arr[nbins+1] = {};

   for (int i=0; i<(nbins+1); i++) {
      Effor3arr[i] = Effor3[i]; 
      Ethrarr[i] = Ethr[i];
      EffAllAnd1arr[i] = EffAllAnd1[i];
      EffAllAnd2arr[i] = EffAllAnd2[i];
      EffAllAnd3arr[i] = EffAllAnd3[i];
      EffAnd1arr[i] = EffAnd1[i];
      EffAnd2arr[i] = EffAnd2[i];
      EffAnd3arr[i] = EffAnd3[i];
      EffOr1arr[i] = EffOr1[i];
      EffOr2arr[i] = EffOr2[i];
      EffOr3arr[i] = EffOr3[i];
   }


   TCanvas *c = new TCanvas("c","c",800,600);
   gPad->SetGrid(1,1);
   TGraph *grOr3 = new TGraph(nbins+1,Ethrarr,EffOr3arr);
   grOr3->SetTitle("");
   grOr3->GetXaxis()->SetTitle("E_{Veto} > E_{THR} [adc]");
   grOr3->GetYaxis()->SetTitle("Eff");
   grOr3->GetYaxis()->SetTitleOffset(1.1);
   //grV4A3->GetYaxis()->SetRangeUser(0.975,0.99); // PE-target
   //grV4A3->GetYaxis()->SetRangeUser(0.05,0.36); // Au-target
   grOr3->GetYaxis()->SetRangeUser(0.0,0.65);
   grOr3->GetXaxis()->SetRangeUser(0,1100.00);
   grOr3->SetLineWidth(3);
   grOr3->SetLineColor(kViolet-5);
   grOr3->Draw("ALP");
   TGraph *grV4or3 = new TGraph(nbins+1,Ethrarr,Effor3arr);
   grV4or3->SetLineWidth(3);
   grV4or3->SetLineColor(kTeal-5);
   grV4or3->Draw("LP");
   TGraph *grAnd3 = new TGraph(nbins+1,Ethrarr,EffAnd3arr);
   grAnd3->SetLineWidth(3);
   grAnd3->SetLineColor(kOrange-3);
   grAnd3->Draw("LP");
   TGraph *grAllAnd3 = new TGraph(nbins+1,Ethrarr,EffAllAnd3arr);
   grAllAnd3->SetLineWidth(3);
   grAllAnd3->SetLineColor(kRed-7);
   grAllAnd3->Draw("LP");
   auto legend = new TLegend(0.79,0.77,0.92,0.94);
   //auto legend = new TLegend(0.12,0.12,0.25,0.29); 
   legend->AddEntry(grV4or3,"V4_A OR V4_B","l");
   legend->AddEntry(grOr3,"OR","l");
   legend->AddEntry(grAnd3,"AND","l");
   legend->AddEntry(grAllAnd3,"All AND","l");
   legend->Draw();
   //c->SaveAs("Eff_OR_PE_run530.pdf");
   c->SaveAs("Eff_OR_Au_run547.pdf");




}

int main() {
   VetoEff9();
   return 0;
}  
