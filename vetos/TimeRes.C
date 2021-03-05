//////////////////////////////////////////////////////////////
/*                                                          */
/*                        TimeRes.C                         */
/*                                                          */
/*  LS: Time resolution of the electron vetos for the spe-  */
/*  cial case when there were only 4 BGOs at the back.      */
/*                                                          */
//////////////////////////////////////////////////////////////

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

void TimeRes(){

   // Some style definitions
   //gROOT->Reset();
   //gROOT->SetStyle("Plain");
   gStyle->SetPaperSize(26,20);
   gStyle->SetOptStat(1);
   gStyle->SetTitleXOffset(1.15);
   gStyle->SetTitleYOffset(1.15);
   gStyle->SetTitleBorderSize(0);
   gStyle->SetLegendBorderSize(1);
   gStyle->SetPadBottomMargin(0.32);
   gStyle->SetPadBottomMargin(0.12);
   gStyle->SetPadLeftMargin(0.12);
   gStyle->SetPadTopMargin(0.32);
   gStyle->SetPadTopMargin(0.12);
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
   
   std::string runnumber = "run549/549";                                               
   std::vector<int> timemin;
   std::vector<int> timemax;                                                     
   //timemin.push_back(100);  // Min time for BGOs                       
   //timemax.push_back(1000); // Max time for BGOs
   timemin.push_back(-100);
   timemax.push_back(100);

   double toffsetV4A = 3.0;
   double toffsetV5A = -2.0;

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


   /*********************************/
   /*           Analysis            */
   /*********************************/
   
   // Elelectron vetos 
   std::vector< std::vector< double > > allEvIDVeto4A;
   std::vector< std::vector< double > > allEdepVeto4A;
   std::vector< std::vector< double > > allTimeVeto4A;
   std::vector< std::vector< double > > allEvIDVeto4B;
   std::vector< std::vector< double > > allEdepVeto4B;
   std::vector< std::vector< double > > allTimeVeto4B;
   std::vector< std::vector< double > > allEvIDVeto5A;
   std::vector< std::vector< double > > allEdepVeto5A;
   std::vector< std::vector< double > > allTimeVeto5A;
   std::vector< std::vector< double > > allEvIDVeto5B;
   std::vector< std::vector< double > > allEdepVeto5B;
   std::vector< std::vector< double > > allTimeVeto5B;
   std::vector< std::vector< double > > allEvIDVeto6A;
   std::vector< std::vector< double > > allEdepVeto6A;
   std::vector< std::vector< double > > allTimeVeto6A;
   std::vector< std::vector< double > > allEvIDVeto6B;
   std::vector< std::vector< double > > allEdepVeto6B; 
   std::vector< std::vector< double > > allTimeVeto6B;


   
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;



   // Veto4_A
   std::ifstream fVeto4A(Vetofiles[0]);
   std::vector<double> vEvIDV4A;
   std::vector<double> vEdepV4A;
   std::vector<double> vTimeV4A;
   std::vector<double> vTOffV4A;
   while (!fVeto4A.eof()) {
      double EvIDV4A, InstV4A, EdepV4A, TimeV4A;
      fVeto4A >> EvIDV4A >> InstV4A >> EdepV4A >> TimeV4A;
      vEvIDV4A.push_back(EvIDV4A);
      vEdepV4A.push_back(EdepV4A);
      vTOffV4A.push_back(TimeV4A+toffsetV4A);
      vTimeV4A.push_back(TimeV4A);
   }
   vEvIDV4A.pop_back();
   vEdepV4A.pop_back();
   vTimeV4A.pop_back();
   vTOffV4A.pop_back();
   fVeto4A.close();


   // Veto4_B
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


   // Veto5_A
   std::ifstream fVeto5A(Vetofiles[2]);
   std::vector<double> vEvIDV5A;
   std::vector<double> vEdepV5A;
   std::vector<double> vTimeV5A;
   std::vector<double> vTOffV5A;
   while (!fVeto5A.eof()) {
      double EvIDV5A, InstV5A, EdepV5A, TimeV5A;
      fVeto5A >> EvIDV5A >> InstV5A >> EdepV5A >> TimeV5A;
      vEvIDV5A.push_back(EvIDV5A);
      vEdepV5A.push_back(EdepV5A);
      vTimeV5A.push_back(TimeV5A);
      vTOffV5A.push_back(TimeV5A+toffsetV5A);
   }
   vEvIDV5A.pop_back();
   vEdepV5A.pop_back();
   vTimeV5A.pop_back();
   vTOffV5A.pop_back();
   fVeto5A.close();


   // Veto5_B
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


   // Veto6_A
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


   // Veto6_B
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
   std::cout << "\033[1;35m---------------------- Reading II ------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;

   // Veto4_A
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


   // Veto4_B
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


   // Veto5_A
   std::vector<double> vInstV5A; // Vector of repeating instances
   int EvIDV5A;
   for (int s=0; s<vEvIDV5A.size(); s++) {
      if ((s > 0) && (s < (vEvIDV4A.size()-1))) {
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


   // Veto5_B
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


   // Veto6_A
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


   // Veto6_B
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
   int cBackBGOA;
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


   const int nsamps = 100;
   double Estep = 25000.0/(nsamps);
   std::vector<double> Ethr;
   Ethr.push_back(0.0);
   for (int i=1; i<nsamps; i++) Ethr.push_back(Ethr[i-1]+Estep);
   std::vector<double> EffVeto4A;
   std::vector<double> EffVeto4A2;
   std::vector<double> EffVeto4A3;

   std::vector<double> vMatchedEnergyV4A;
   std::vector<double> vMatchedEnergyV4A2;
   std::vector<double> vMatchedEnergyV4A3;
   std::vector<double> vMatchedTimeV4A0MeV;
   std::vector<double> vMatchedTimeV4A5MeV;
   std::vector<double> vMatchedTimeV4A10MeV;
   std::vector<double> vMatchedTimeV4A15MeV;
   std::vector<double> vMatchedTimeV4A20MeV;
   std::vector<double> vMatchedTimeV4A2500;
   std::vector<double> vMatchedTimeV4A5000;
   std::vector<double> vMatchedTimeV4A7500;

   // 2-D Plot
   std::vector<double> vMatchedBGOEn0;
   std::vector<double> vMatchedBGOTm0;
   std::vector<double> vMatchedVetoEn0;
   std::vector<double> vTimedBGOEn0;
   std::vector<double> vTimedBGOTm0;

   std::vector<double> vLowV4A0MeV;
   std::vector<double> vHighV4A0MeV;
   std::vector<double> vLowV4A2MeV;
   std::vector<double> vHighV4A2MeV;
   std::vector<double> vLowV4A12MeV;
   std::vector<double> vHighV4A12MeV;

   for (int m=0; m<Ethr.size(); m++) {
      double MatchCounter=0;
      double TotalCounter=0;
      double MatchCounter2=0;
      double MatchCounter3=0;
      for (int n=0; n<vIDBGOBackA.size(); n++) {
         if (vEnBGOBackA[n] >= Ethr[m]) {
            int GoodEvent = 0;
            for (int k=0; k<vEvIDV4A.size(); k++) {
               if (vEvIDV4A[k] == vIDBGOBackA[n]) {
                  if (vInstV4A[k] == 0) {
                     if (Ethr[m] == 0) {
                        vMatchedBGOEn0.push_back(vEnBGOBackA[n]); // 2D plot
                        vMatchedVetoEn0.push_back(vEdepV4A[k]); // 2D plot
                        vMatchedBGOTm0.push_back(vTOffV4A[k]-vTmBGOBackA[n]); // 2D plot
                     }
                     if (Ethr[m] < 5000) {
                        vMatchedTimeV4A0MeV.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
                     } else if ((Ethr[m] >= 5000) && (Ethr[m] < 10000)) {
                        vMatchedTimeV4A5MeV.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
                     } else if ((Ethr[m] >= 10000) && (Ethr[m] < 15000)) {
                        vMatchedTimeV4A10MeV.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
                     } else if ((Ethr[m] >= 15000) && (Ethr[m] < 20000)) {
                        vMatchedTimeV4A15MeV.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
                     } else if ((Ethr[m] >= 20000) && (Ethr[m] <25000)) {
                        vMatchedTimeV4A20MeV.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
                     }                     
                     //if (Ethr[m] == 5000) {
                        //vMatchedTimeV4A5MeV.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
                     //} else if (Ethr[m] == 10000) {
                        //vMatchedTimeV4A10MeV.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
                     //} else if (Ethr[m] == 15000) {
                        //vMatchedTimeV4A15MeV.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
                     //}
                     if ((vTOffV4A[k] >= (vTmBGOBackA[n]-250)) && (vTOffV4A[k] <= (vTmBGOBackA[n]+250))) {
                        if ((vTOffV4A[k] >= (vTmBGOBackA[n]-65)) && (vTOffV4A[k] <= (vTmBGOBackA[n]+65))) {
                           if ((vTOffV4A[k] >= (vTmBGOBackA[n]-30)) && (vTOffV4A[k] <= (vTmBGOBackA[n]+30))) {
                              MatchCounter++;
                              vMatchedEnergyV4A.push_back(vEdepV4A[k]);
                           }   
                           MatchCounter2++;
                           vMatchedEnergyV4A2.push_back(vEdepV4A[k]);
                        }
                        MatchCounter3++;
                        vMatchedEnergyV4A3.push_back(vEdepV4A[k]);
                        
                        if (Ethr[m] == 0) {
                           vTimedBGOEn0.push_back(vEnBGOBackA[n]); // 2d plot
                           //vTimedBGOTm0.push_back(vTimeV4A[k] - vTmBGOBackA[n]); // 2D plot
                           vTimedBGOTm0.push_back(vTimeV4A[k]);
                        }
                        if (Ethr[m] < 2000) {
                           if (vEdepV4A[k] <= 500) {
                              vLowV4A0MeV.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
                           } else {
                              vHighV4A0MeV.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
                           }
                        } else if ((Ethr[m] >= 2000) && (Ethr[m] < 12000)) {
                           if (vEdepV4A[k] <= 500) {
                              vLowV4A2MeV.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
                           } else {
                              vHighV4A2MeV.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
                           }
                        } else if ((Ethr[m] >= 12000) && (Ethr[m] < 25000)) {
                           if (vEdepV4A[k] <= 500) {
                              vLowV4A12MeV.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
                           } else {
                              vHighV4A12MeV.push_back(vTimeV4A[k]-vTmBGOBackA[n]);
                           }
                       }

                        if ((vEdepV4A[k] >= 2400) && (vEdepV4A[k] <= 2600)) {
                           vMatchedTimeV4A2500.push_back(vTimeV4A[k] - vTmBGOBackA[n]);
                        } else if ((vEdepV4A[k] >= 4900) && (vEdepV4A[k] <= 5100)) {
                           vMatchedTimeV4A5000.push_back(vTimeV4A[k] - vTmBGOBackA[n]);
                        } else if ((vEdepV4A[k] >= 7400) && (vEdepV4A[k] <= 7600)) {
                           vMatchedTimeV4A7500.push_back(vTimeV4A[k] - vTmBGOBackA[n]);
                        }   
                     }
                  } else {
                     GoodEvent = 1;
                  }
               }
            }
            if (GoodEvent == 0) {
               TotalCounter++;
            }
         }
      }

      std::cout << "Ethr = " << Ethr[m] << ", Eff1 = " << MatchCounter/TotalCounter << ", Eff2 = " << MatchCounter2/TotalCounter << ", Eff3 = " << MatchCounter3/TotalCounter << std::endl;
      EffVeto4A.push_back(MatchCounter/TotalCounter);
      EffVeto4A2.push_back(MatchCounter2/TotalCounter);
      EffVeto4A3.push_back(MatchCounter3/TotalCounter);
   }



   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


   TH1F *hVetoTime = new TH1F("hVetoTime","Time",15,-16.0,44.0);
   TH1F *hVetoTOff = new TH1F("hVetoTOff","Time",15,-16.0,44.0);
   for (int i=0; i<vTimeV4A.size(); i++) {
      hVetoTime->Fill(vTimeV4A[i]);
      hVetoTOff->Fill(vTOffV4A[i]);
   }

   TCanvas *vz = new TCanvas("vz","Veto4_A",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hVetoTime->GetXaxis()->SetTitle("t [ns]");
   hVetoTime->SetTitle("");
   hVetoTime->SetLineColor(kBlue+1);
   hVetoTime->Draw();
   hVetoTOff->SetLineColor(kRed);
   hVetoTOff->SetLineStyle(kDashed);
   hVetoTOff->Draw("same");
   //vz->SaveAs("TOffset_V5A.pdf");
   //vz->SaveAs("Time_BBGO_A.pdf");

   TH1F *hVetoTime2 = new TH1F("hVetoTime2","Time",15,-16.0,44.0);
   TH1F *hVetoTOff2 = new TH1F("hVetoTOff2","Time",15,-16.0,44.0);
   for (int i=0; i<vTimeV5A.size(); i++) {
      hVetoTime2->Fill(vTimeV5A[i]);
      hVetoTOff2->Fill(vTOffV5A[i]);
   }
 
   TCanvas *vz2 = new TCanvas("vz2","Veto4_A",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hVetoTime2->GetXaxis()->SetTitle("t [ns]");
   hVetoTime2->SetTitle("");
   hVetoTime2->SetLineColor(kBlue+1);
   hVetoTime2->Draw();
   hVetoTOff2->SetLineColor(kRed);
   hVetoTOff2->SetLineStyle(kDashed);
   hVetoTOff2->Draw("same");
   //vz2->SaveAs("TOffset_V5A2.pdf");


   TH1F *hMatchedTime = new TH1F("hMatchedTimeVeto","Time",100,-500.0,10000.0);
   for (int i=0; i<vTimedBGOEn0.size(); i++) {
      hMatchedTime->Fill(vTimedBGOEn0[i]);
      //hMatchedTime->Fill(vTimeV5A[i]);
   }

   TCanvas *z = new TCanvas("z","Veto5_A",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hMatchedTime->SetTitle("Veto5_A");
   hMatchedTime->Draw();
   


   // 2D plots of Energy-Time of matched Veto
   TH2F *hMatchedBGOEnTm = new TH2F("hMatchedBGOEnTm","En-Time",21,-100.0,100.0,25,0,10.0);
   TH2F *hMatchedVetoEnTm = new TH2F("hMatchedVetoEnTm","En-Time",21,-100.0,100.0,25,0,8.0);
   TH2F *hMatchedBGOVeto = new TH2F("hMatchedBGOVeto","En-Time",25,0,10.0,25,0,8.0);
   for (int i=0; i<vMatchedBGOTm0.size(); i++) {
      for (int j=0; j<vMatchedBGOEn0.size(); j++) {
         hMatchedBGOEnTm->Fill(vMatchedBGOTm0[i],(vMatchedBGOEn0[j]/1000.0));
         hMatchedVetoEnTm->Fill(vMatchedBGOTm0[i],(vMatchedVetoEn0[j]/1000.0));
         hMatchedBGOVeto->Fill((vMatchedBGOEn0[i]/1000.0),(vMatchedVetoEn0[j]/1000.0));
      }
   }
/*
   TCanvas *u = new TCanvas("u","Veto4_A",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   hMatchedBGOEnTm->GetXaxis()->SetTitle("t_{Veto}-t_{BGO}");
   hMatchedBGOEnTm->GetYaxis()->SetTitle("E_{BGO}");
   hMatchedBGOEnTm->SetTitle("Veto_4_A");
   hMatchedBGOEnTm->Draw("COLZ");
   u->SaveAs("EnTm_V4_A.pdf");
*/
   TCanvas *ulbgo = new TCanvas("ulbgo","Veto4_A",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogz();
   hMatchedBGOEnTm->GetXaxis()->SetTitle("t_{Veto}-t_{BGO} [ns]");
   hMatchedBGOEnTm->GetYaxis()->SetTitle("E_{BGO} [MeV]");
   hMatchedBGOEnTm->SetTitle("");
   hMatchedBGOEnTm->Draw("COLZ");
   ulbgo->SaveAs("549_EnTm_V4_A_BGO.pdf");

   TCanvas *ulveto = new TCanvas("ulveto","Veto4_A",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogz();
   hMatchedVetoEnTm->GetXaxis()->SetTitle("t_{Veto}-t_{BGO} [ns]");
   hMatchedVetoEnTm->GetYaxis()->SetTitle("E_{Veto} [kadc]");
   hMatchedVetoEnTm->SetTitle("");
   hMatchedVetoEnTm->Draw("COLZ");
   ulveto->SaveAs("549_EnTm_V4_A_Veto.pdf");

   TCanvas *ulbgoveto = new TCanvas("ulbgoveto","Veto4_A",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogz();
   hMatchedBGOVeto->GetXaxis()->SetTitle("E_{BGO} [MeV]");
   hMatchedBGOVeto->GetYaxis()->SetTitle("E_{Veto} [kadc]");
   hMatchedBGOVeto->SetTitle("");
   hMatchedBGOVeto->Draw("COLZ");
   ulbgoveto->SaveAs("549_BGO_Veto_V4_A.pdf");

/*

   // 2D plots of Energy-Time of matched and timedVeto
   TH2F *hTimedBGOEnTm = new TH2F("hTimedBGOEnTm","En-Time",25,-200.0,200.0,20,0,10.0);
   for (int i=0; i<vTimedBGOTm0.size(); i++) {
      for (int j=0; j<vTimedBGOEn0.size(); j++) {
         hTimedBGOEnTm->Fill(vTimedBGOTm0[i],(vTimedBGOEn0[j]/1000.0));
      }
   }
   
   TCanvas *t = new TCanvas("t","Veto4_A",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   hTimedBGOEnTm->GetXaxis()->SetTitle("t_{Veto}-t_{BGO}");
   hTimedBGOEnTm->GetYaxis()->SetTitle("E_{BGO}");
   hTimedBGOEnTm->SetTitle("Veto_4_A");
   hTimedBGOEnTm->Draw("COLZ");
   t->SaveAs("EnTm_timed_V4_A.pdf");

   TCanvas *tl = new TCanvas("tl","Veto6_B",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogz();
   hTimedBGOEnTm->GetYaxis()->SetNdivisions(805);
   hTimedBGOEnTm->GetXaxis()->SetTitle("t_{Veto}-t_{BGO} [ns]");
   hTimedBGOEnTm->GetYaxis()->SetTitle("E_{BGO}");
   hTimedBGOEnTm->SetTitle("Veto_6_B");
   hTimedBGOEnTm->Draw("COLZ");
   //tl->SaveAs(TString(runnumber+"_EnTm_timed_V6_B_ROI.pdf"));
*/

/*
   // Time resolution of the vetos, for different time cuts

   TH1F *hLowV4A0MeV = new TH1F("hLowV4A0MeV","Low0MeV",50,-250.0,50.0);
   TH1F *hHighV4A0MeV = new TH1F("hHigh0MeV","High0MeV",50,-250.0,50.0);
   TH1F *hLowV4A2MeV = new TH1F("hLowV4A2MeV","Low2MeV",50,-250.0,50.0);
   TH1F *hHighV4A2MeV = new TH1F("hHighV4A2MeV","High2MeV",50,-250.0,50.0);
   TH1F *hLowV4A12MeV = new TH1F("hLowV4A12MeV","Low12MeV",50,-250.0,50.0);
   TH1F *hHighV4A12MeV = new TH1F("hHighV4A12MeV","High12Mev",50,-250.0,50.0);

   for (int i=0; i<vLowV4A0MeV.size(); i++)  hLowV4A0MeV->Fill(vLowV4A0MeV[i]);
   for (int i=0; i<vHighV4A0MeV.size(); i++)  hHighV4A0MeV->Fill(vHighV4A0MeV[i]);
   for (int i=0; i<vLowV4A2MeV.size(); i++)  hLowV4A2MeV->Fill(vLowV4A2MeV[i]);
   for (int i=0; i<vHighV4A2MeV.size(); i++)  hHighV4A2MeV->Fill(vHighV4A2MeV[i]);
   for (int i=0; i<vLowV4A12MeV.size(); i++)  hLowV4A12MeV->Fill(vLowV4A12MeV[i]);
   for (int i=0; i<vHighV4A12MeV.size(); i++)  hHighV4A12MeV->Fill(vHighV4A12MeV[i]);
*/
/*
   TCanvas *rv = new TCanvas("rv","Veto4A",800,600);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   gStyle->SetOptStat(0);
   hHighV4A2MeV->GetXaxis()->SetTitle("t_{Veto} - t_{BGO}");
   hHighV4A2MeV->SetTitle("Veto_4_A");
   hHighV4A2MeV->SetLineColor(kTeal-5);
   hHighV4A2MeV->SetLineWidth(3);
   hHighV4A2MeV->Draw();
   hHighV4A12MeV->SetLineColor(kViolet-5);
   hHighV4A12MeV->SetLineWidth(3);
   hHighV4A12MeV->Draw("SAME");
   hHighV4A0MeV->SetLineColor(kOrange-5);
   hHighV4A0MeV->SetLineWidth(3);
   hHighV4A0MeV->Draw("SAME");
   hLowV4A2MeV->SetLineColor(kRed-7);
   hLowV4A2MeV->SetLineWidth(3);
   hLowV4A2MeV->Draw("SAME");
   hLowV4A12MeV->SetLineColor(kSpring-9);
   hLowV4A12MeV->SetLineWidth(3);
   hLowV4A12MeV->Draw("SAME");
   hLowV4A0MeV->SetLineColor(kYellow-4);
   hLowV4A0MeV->SetLineWidth(3);
   hLowV4A0MeV->Draw("SAME");
   auto legendrv = new TLegend(0.84,0.81,0.98,0.97);
   legendrv->AddEntry(hLowV4A0MeV,"E_{BGO} #in [0..2) MeV, E_{Veto} <= 1 kadc","f");
   legendrv->AddEntry(hHighV4A0MeV,"E_{BGO} #in [0..2) MeV, E_{Veto} > 1 kadc","f");
   legendrv->AddEntry(hLowV4A2MeV,"E_{BGO} #in [2..12) MeV, E_{Veto} <= 1 kadc","f");
   legendrv->AddEntry(hHighV4A2MeV,"E_{BGO} #in [2..12) MeV, E_{Veto} > 1 kadc","f");
   legendrv->AddEntry(hLowV4A12MeV,"E_{BGO} #in [12..25) MeV, E_{Veto} <= 1 kadc","f");
   legendrv->AddEntry(hHighV4A12MeV,"E_{BGO} #in [12..25) MeV, E_{veto} > 1 kadc","f"); 
   legendrv->Draw();
   rv->SaveAs("Veto4_A_time_Encuts.pdf");
*/
/*
   TCanvas *rvLow = new TCanvas("rvLow","Veto4A",800,600);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   gStyle->SetOptStat(0);
   hLowV4A2MeV->GetXaxis()->SetTitle("t_{Veto} - t_{BGO}");
   hLowV4A2MeV->SetTitle("Veto_4_A");
   hLowV4A2MeV->SetLineColor(kRed-7);
   hLowV4A2MeV->SetLineWidth(3);
   hLowV4A2MeV->Draw();
   hLowV4A12MeV->SetLineColor(kSpring-9);   
   hLowV4A12MeV->SetLineWidth(3);
   hLowV4A12MeV->Draw("SAME");
   hLowV4A0MeV->SetLineColor(kYellow-4);
   hLowV4A0MeV->SetLineWidth(3);
   hLowV4A0MeV->Draw("SAME");
   auto legendrvLow = new TLegend(0.84,0.81,0.98,0.97);
   legendrvLow->AddEntry(hLowV4A0MeV,"E_{BGO} #in [0..2) MeV, E_{Veto} <= 500 adc","f");
   legendrvLow->AddEntry(hLowV4A2MeV,"E_{BGO} #in [2..12) MeV, E_{Veto} <= 500 adc","f");
   legendrvLow->AddEntry(hLowV4A12MeV,"E_{BGO} #in [12..25) MeV, E_{Veto} <= 500 adc","f");
   legendrvLow->Draw();
   rvLow->SaveAs("Veto4_A_time_Encuts_Low.pdf");


   TCanvas *rvHigh = new TCanvas("rvHigh","Veto4A",800,600);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   gStyle->SetOptStat(0);
   hHighV4A2MeV->GetXaxis()->SetTitle("t_{Veto} - t_{BGO}");
   hHighV4A2MeV->SetTitle("Veto_4_A");
   hHighV4A2MeV->SetLineColor(kTeal-5);
   hHighV4A2MeV->SetLineWidth(3);
   hHighV4A2MeV->Draw();
   hHighV4A12MeV->SetLineColor(kViolet-5);   
   hHighV4A12MeV->SetLineWidth(3);
   hHighV4A12MeV->Draw("SAME");
   hHighV4A0MeV->SetLineColor(kOrange-5);
   hHighV4A0MeV->SetLineWidth(3);
   hHighV4A0MeV->Draw("SAME");
   auto legendrvHigh = new TLegend(0.84,0.81,0.98,0.97);
   legendrvHigh->AddEntry(hHighV4A0MeV,"E_{BGO} #in [0..2) MeV, E_{Veto} > 500 adc","f");
   legendrvHigh->AddEntry(hHighV4A2MeV,"E_{BGO} #in [2..12) MeV, E_{Veto} > 500 adc","f");
   legendrvHigh->AddEntry(hHighV4A12MeV,"E_{BGO} #in [12..25) MeV, E_{Veto} > 500 adc","f");
   legendrvHigh->Draw();
   rvHigh->SaveAs("Veto4_A_time_Encuts_High.pdf");


   TCanvas *rv0 = new TCanvas("rv0","Veto4A",800,600);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   gStyle->SetOptStat(0);
   hHighV4A0MeV->GetXaxis()->SetTitle("t_{Veto} - t_{BGO}");
   hHighV4A0MeV->SetTitle("Veto_4_A");
   hHighV4A0MeV->SetLineColor(kOrange-5);
   hHighV4A0MeV->SetLineWidth(3);
   hHighV4A0MeV->Draw();
   hLowV4A0MeV->SetLineColor(kYellow-4);
   hLowV4A0MeV->SetLineWidth(3);
   hLowV4A0MeV->Draw("SAME");
   auto legendrv0 = new TLegend(0.84,0.81,0.98,0.97);
   legendrv0->AddEntry(hHighV4A0MeV,"E_{BGO} #in [0..2) MeV, E_{Veto} > 500 adc","f");
   legendrv0->AddEntry(hLowV4A0MeV,"E_{BGO} #in [0..2) MeV, E_{Veto} <= 500 adc","f");
   legendrv0->Draw();
   rv0->SaveAs("Veto4_A_time_Encuts_0MeV.pdf");


   TCanvas *rv2 = new TCanvas("rv2","Veto4A",800,600);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   gStyle->SetOptStat(0);
   hHighV4A2MeV->GetXaxis()->SetTitle("t_{Veto} - t_{BGO}");
   hHighV4A2MeV->SetTitle("Veto_4_A");
   hHighV4A2MeV->SetLineColor(kTeal-5);
   hHighV4A2MeV->SetLineWidth(3);
   hHighV4A2MeV->Draw();
   hLowV4A2MeV->SetLineColor(kRed-7);
   hLowV4A2MeV->SetLineWidth(3);
   hLowV4A2MeV->Draw("SAME");
   auto legendrv2 = new TLegend(0.84,0.81,0.98,0.97);
   legendrv2->AddEntry(hHighV4A2MeV,"E_{BGO} #in [2..12) MeV, E_{Veto} > 500 adc","f");
   legendrv2->AddEntry(hLowV4A2MeV,"E_{BGO} #in [2..12) MeV, E_{Veto} <= 500 adc","f");
   legendrv2->Draw();
   rv2->SaveAs("Veto4_A_time_Encuts_2MeV.pdf");


   TCanvas *rv12 = new TCanvas("rv12","Veto4A",800,600);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   gStyle->SetOptStat(0);
   hHighV4A12MeV->GetXaxis()->SetTitle("t_{Veto} - t_{BGO}");
   hHighV4A12MeV->SetTitle("Veto_4_A");
   hHighV4A12MeV->SetLineColor(kViolet-5);
   hHighV4A12MeV->SetLineWidth(3);
   hHighV4A12MeV->Draw();
   hLowV4A12MeV->SetLineColor(kSpring-9);
   hLowV4A12MeV->SetLineWidth(3);
   hLowV4A12MeV->Draw("SAME");
   auto legendrv12 = new TLegend(0.84,0.81,0.98,0.97);
   legendrv12->AddEntry(hHighV4A12MeV,"E_{BGO} #in [12..25) MeV, E_{Veto} > 500 adc","f");
   legendrv12->AddEntry(hLowV4A12MeV,"E_{BGO} #in [12..25) MeV, E_{Veto} <= 500 adc","f");
   legendrv12->Draw();
   rv12->SaveAs("Veto4_A_time_Encuts_12MeV.pdf");
*/

   // Time resolution of the vetos [real]
/*
   TH1F *hTime0MeV = new TH1F("htime0MeV","0MeV",100,-800.0,800.0);
   TH1F *hTime5MeV = new TH1F("hTime5MeV","5MeV",100,-800.0,800.0);
   TH1F *hTime10MeV = new TH1F("hTime10MeV","10MeV",100,-800.0,800.0);
   TH1F *hTime15MeV = new TH1F("hTime15MeV","15MeV",100,-800.0,800.0);
   TH1F *hTime20MeV = new TH1F("hTime20MeV","20MeV",100,-800.0,800.0);

   for (int i=0; i<vMatchedTimeV4A0MeV.size(); i++)  hTime0MeV->Fill(vMatchedTimeV4A0MeV[i]);
   for (int i=0; i<vMatchedTimeV4A5MeV.size(); i++)  hTime5MeV->Fill(vMatchedTimeV4A5MeV[i]);
   for (int i=0; i<vMatchedTimeV4A10MeV.size(); i++) hTime10MeV->Fill(vMatchedTimeV4A10MeV[i]);
   for (int i=0; i<vMatchedTimeV4A15MeV.size(); i++) hTime15MeV->Fill(vMatchedTimeV4A15MeV[i]);
   for (int i=0; i<vMatchedTimeV4A20MeV.size(); i++) hTime20MeV->Fill(vMatchedTimeV4A20MeV[i]);


   TCanvas *w = new TCanvas("w","Veto5B",800,600);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   gStyle->SetOptStat(0);
   hTime5MeV->GetXaxis()->SetTitle("t_{Veto} - t_{BGO}");
   hTime5MeV->SetTitle("Veto_5_B");
   hTime5MeV->SetLineColor(kTeal-5);
   hTime5MeV->SetLineWidth(3);
   hTime5MeV->Draw();
   hTime0MeV->SetLineColor(kViolet-5);
   hTime0MeV->SetLineWidth(3);
   hTime0MeV->Draw("SAME");
   hTime10MeV->SetLineColor(kOrange-5);
   hTime10MeV->SetLineWidth(3);
   hTime10MeV->Draw("SAME");
   hTime15MeV->SetLineColor(kRed-7);
   hTime15MeV->SetLineWidth(3);
   hTime15MeV->Draw("SAME");
   hTime20MeV->SetLineColor(kSpring-9);
   hTime20MeV->SetLineWidth(3);
   hTime20MeV->Draw("SAME");
   auto legend = new TLegend(0.84,0.81,0.98,0.97);
   legend->AddEntry(hTime0MeV,"E_{BGO} #in [0..0.5) MeV","f");
   legend->AddEntry(hTime5MeV,"E_{BGO} #in [0.5..10) MeV","f");
   legend->AddEntry(hTime10MeV,"E_{BGO} #in [10..15) MeV","f");
   legend->AddEntry(hTime15MeV,"E_{BGO} #in [15..20) MeV","f");
   legend->AddEntry(hTime20MeV,"E_{BGO} #in [20..25) MeV","f");
   legend->Draw();
   w->SaveAs("Veto5_B_time_full.pdf");


   TH1F *hTime0MeVp = new TH1F("hTime0MeVp","0MeV",50,-250.0,50.0);
   TH1F *hTime5MeVp = new TH1F("hTime5MeVp","5MeV",50,-250.0,50.0);
   TH1F *hTime10MeVp = new TH1F("hTime10MeVp","10MeV",50,-250.0,50.0);
   TH1F *hTime15MeVp = new TH1F("hTime15MeVp","15MeV",50,-250.0,50.0);
   TH1F *hTime20MeVp = new TH1F("hTime20MeVp","20MeV",50,-250.0,50.0);

   for (int i=0; i<vMatchedTimeV4A0MeV.size(); i++)  hTime0MeVp->Fill(vMatchedTimeV4A0MeV[i]);
   for (int i=0; i<vMatchedTimeV4A5MeV.size(); i++)  hTime5MeVp->Fill(vMatchedTimeV4A5MeV[i]);
   for (int i=0; i<vMatchedTimeV4A10MeV.size(); i++) hTime10MeVp->Fill(vMatchedTimeV4A10MeV[i]);
   for (int i=0; i<vMatchedTimeV4A15MeV.size(); i++) hTime15MeVp->Fill(vMatchedTimeV4A15MeV[i]);
   for (int i=0; i<vMatchedTimeV4A20MeV.size(); i++) hTime20MeVp->Fill(vMatchedTimeV4A20MeV[i]);

   TCanvas *wp = new TCanvas("wp","Veto5B",800,600);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   gStyle->SetOptStat(0);
   hTime5MeVp->GetXaxis()->SetTitle("t_{Veto} - t_{BGO}");
   hTime5MeVp->SetTitle("Veto_5_B");
   hTime5MeVp->SetLineColor(kTeal-5);
   hTime5MeVp->SetLineWidth(3);
   hTime5MeVp->Draw();
   hTime0MeVp->SetLineColor(kViolet-5);
   hTime0MeVp->SetLineWidth(3);
   hTime0MeVp->Draw("SAME");
   hTime10MeVp->SetLineColor(kOrange-5);
   hTime10MeVp->SetLineWidth(3);
   hTime10MeVp->Draw("SAME");
   hTime15MeVp->SetLineColor(kRed-7);
   hTime15MeVp->SetLineWidth(3);
   hTime15MeVp->Draw("SAME");
   hTime20MeVp->SetLineColor(kSpring-9);
   hTime20MeVp->SetLineWidth(3);
   hTime20MeVp->Draw("SAME");
   auto legendp = new TLegend(0.84,0.81,0.98,0.97);
   legendp->AddEntry(hTime0MeVp,"E_{BGO} #in [0..0.5) MeV","f");
   legendp->AddEntry(hTime5MeVp,"E_{BGO} #in [0.5..10) MeV","f");
   legendp->AddEntry(hTime10MeVp,"E_{BGO} #in [10..15) MeV","f");
   legendp->AddEntry(hTime15MeVp,"E_{BGO} #in [15..20) MeV","f");
   legendp->AddEntry(hTime20MeVp,"E_{BGO} #in [20..25) MeV","f");
   legendp->Draw();
   wp->SaveAs("Veto5_B_time_part.pdf");
*/
   
}

int main() {
   TimeRes();   
   return 0;
}
