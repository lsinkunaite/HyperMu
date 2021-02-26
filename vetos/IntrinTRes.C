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

void IntrinTRes(){

   // Some style definitions
   //gROOT->Reset();
   //gROOT->SetStyle("Plain");
   gStyle->SetPaperSize(26,20);
   gStyle->SetOptStat(1);
   gStyle->SetTitleXOffset(1.15);
   gStyle->SetTitleYOffset(1.15);
   gStyle->SetTitleBorderSize(0);
   gStyle->SetLegendBorderSize(1);
   //gStyle->SetPadBottomMargin(0.32);
   gStyle->SetPadBottomMargin(0.12);
   gStyle->SetPadLeftMargin(0.16);
   //gStyle->SetPadTopMargin(0.32);
   gStyle->SetPadTopMargin(0.06);
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
   
   std::string runnumber = "run530/530";                                                 
   std::vector<int> timemin;
   std::vector<int> timemax;                                                     
   timemin.push_back(100);  // Min time for BGOs                       
   timemax.push_back(1000); // Max time for BGOs

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

   double TOffsetV4A = 3.0;
   double TOffsetV5A = -3.0;
   
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
      vTimeV4A.push_back(TimeV4A);
      vTOffV4A.push_back(TimeV4A+TOffsetV4A);
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
      vTOffV5A.push_back(TimeV5A+TOffsetV5A);
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
   double Estep = 10000.0/(nsamps);
   std::vector<double> Ethr;
   Ethr.push_back(0.0);
   for (int i=1; i<nsamps; i++) Ethr.push_back(Ethr[i-1]+Estep);

   // 2-D Plot
   std::vector<double> vEdepSandwich;
   std::vector<double> vTimeSandwich;
   std::vector<double> vTOffSandwich;

   for (int n=0; n<25000; n++) {
      if (vInstV4A[n] == 0) {
         for (int k=0; k<35000; k++) {
            if (vEvIDV5A[k] == vEvIDV4A[n]) {
               if (vInstV5A[k] == 0) {
                  vEdepSandwich.push_back(vEdepV4A[n]);
                  vTimeSandwich.push_back(vTimeV5A[k]-vTimeV4A[n]);
                  vTOffSandwich.push_back(vTOffV5A[k]-vTOffV4A[n]);
               } 
            }
         }
      }
   }

   std::cout << "Round [0 .. 25000] finished!" << std::endl;
   std::cout << " time = " << vTimeSandwich.size() << ", edep = " << vEdepSandwich.size() << std::endl;

   for (int n=25000; n<50000; n++) { 
      if (vInstV4A[n] == 0) {
         for (int k=18000; k<65000; k++) {
            if (vEvIDV5A[k] == vEvIDV4A[n]) {
               if (vInstV5A[k] == 0) {
                  vEdepSandwich.push_back(vEdepV4A[n]);
                  vTimeSandwich.push_back(vTimeV5A[k]-vTimeV4A[n]);
                  vTOffSandwich.push_back(vTOffV5A[k]-vTOffV4A[n]);
               }
            }
         }
      }
   }     

   std::cout << "Round [25000 .. 50000] finished!" << std::endl;
   std::cout << " time = " << vTimeSandwich.size() << ", edep = " << vEdepSandwich.size() << std::endl;

   for (int n=50000; n<75000; n++) {
      if (vInstV4A[n] == 0) {
         for (int k=40000; k<85000; k++) {
            if (vEvIDV5A[k] == vEvIDV4A[n]) {
               if (vInstV5A[k] == 0) {
                  vEdepSandwich.push_back(vEdepV4A[n]);
                  vTimeSandwich.push_back(vTimeV5A[k]-vTimeV4A[n]);
                  vTOffSandwich.push_back(vTOffV5A[k]-vTOffV4A[n]);
               }
            }
         }
      }
   }
 
   std::cout << "Round [50000 .. 75000] finished!" << std::endl;
   std::cout << " time = " << vTimeSandwich.size() << ", edep = " << vEdepSandwich.size() << std::endl;

   for (int n=75000; n<100000; n++) {
      if (vInstV4A[n] == 0) {
         for (int k=65000; k<115000; k++) {
            if (vEvIDV5A[k] == vEvIDV4A[n]) {
               if (vInstV5A[k] == 0) {
                  vEdepSandwich.push_back(vEdepV4A[n]);
                  vTimeSandwich.push_back(vTimeV5A[k]-vTimeV4A[n]);
                  vTOffSandwich.push_back(vTOffV5A[k]-vTOffV4A[n]);
               }
            }
         }
      }
   }

   std::cout << "Round [75000 .. 100000] finished!" << std::endl;
   std::cout << " time = " << vTimeSandwich.size() << ", edep = " << vEdepSandwich.size() << std::endl;

   for (int n=100000; n<125000; n++) {
      if (vInstV4A[n] == 0) {
         for (int k=85000; k<140000; k++) { 
            if (vEvIDV5A[k] == vEvIDV4A[n]) {
               if (vInstV5A[k] == 0) {
                  vEdepSandwich.push_back(vEdepV4A[n]);
                  vTimeSandwich.push_back(vTimeV5A[k]-vTimeV4A[n]);
                  vTOffSandwich.push_back(vTOffV5A[k]-vTOffV4A[n]);
               }
            }
         }
      }
   }
 
   std::cout << "Round [100000 .. 125000] finished!" << std::endl;
   std::cout << " time = " << vTimeSandwich.size() << ", edep = " << vEdepSandwich.size() << std::endl;

   for (int n=125000; n<150000; n++) {
      if (vInstV4A[n] == 0) {
         for (int k=110000; k<165000; k++) { 
            if (vEvIDV5A[k] == vEvIDV4A[n]) {
               if (vInstV5A[k] == 0) {
                  vEdepSandwich.push_back(vEdepV4A[n]);
                  vTimeSandwich.push_back(vTimeV5A[k]-vTimeV4A[n]);
                  vTOffSandwich.push_back(vTOffV5A[k]-vTOffV4A[n]);
               }
            }
         }
      }
   }
 
   std::cout << "Round [125000 .. 150000] finished!" << std::endl;
   std::cout << " time = " << vTimeSandwich.size() << ", edep = " << vEdepSandwich.size() << std::endl;

   for (int n=150000; n<175000; n++) {
      if (vInstV4A[n] == 0) {
         for (int k=135000; k<190000; k++) {
            if (vEvIDV5A[k] == vEvIDV4A[n]) {
               if (vInstV5A[k] == 0) {
                  vEdepSandwich.push_back(vEdepV4A[n]);
                  vTimeSandwich.push_back(vTimeV5A[k]-vTimeV4A[n]);
                  vTOffSandwich.push_back(vTOffV5A[k]-vTOffV4A[n]);
               }
            }
         }
      }
   }
 
   std::cout << "Round [150000 .. 175000] finished!" << std::endl;
   std::cout << " time = " << vTimeSandwich.size() << ", edep = " << vEdepSandwich.size() << std::endl;

   for (int n=175000; n<vEvIDV4A.size(); n++) {
      if (vInstV4A[n] == 0) {
         for (int k=160000; k<vEvIDV5A.size(); k++) {
            if (vEvIDV5A[k] == vEvIDV4A[n]) {
               if (vInstV5A[k] == 0) {
                  vEdepSandwich.push_back(vEdepV4A[n]);
                  vTimeSandwich.push_back(vTimeV5A[k]-vTimeV4A[n]);
                  vTOffSandwich.push_back(vTOffV5A[k]-vTOffV4A[n]);
               }
            }
         }
      }
   }
 
   std::cout << "Round [125000 .. " << vEvIDV4A.size() << "] finished!" << std::endl;
   std::cout << " time = " << vTimeSandwich.size() << ", edep = " << vEdepSandwich.size(    ) << std::endl;


   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m---------------------- Plotting --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl; 

/*
   // 2D plots of Energy-Time of matched Sandwich
   TH2F *hSandwich = new TH2F("hSandwich","Sandwich",12,-22.0,26.0,55,0,11500.0);
   //TH1F *hSandwich = new TH1F("hSandwich","Sandwich",50,-200.0,200.0);
   for (int i=0; i<vTimeSandwich.size(); i++) {
      for (int j=0; j<vEdepSandwich.size(); j++) {
         hSandwich->Fill(vTimeSandwich[i],vEdepSandwich[j]);
      //hSandwich->Fill(vTimeSandwich[i]);
      }
   }


   TCanvas *u = new TCanvas("u","Sandwich",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogz();
   hSandwich->GetXaxis()->SetTitle("t_{V5A}-t_{V4A}");
   hSandwich->GetYaxis()->SetTitle("E_{Veto4_A}");
   hSandwich->GetYaxis()->SetTitleOffset(1.5);
   //hSandwich->SetTitle("Sandwich");
   hSandwich->SetTitle("");
   hSandwich->Draw("COLZ");
   u->SaveAs("EnTime_Sandwich.pdf");
*/

   TH1F *hSandTime = new TH1F("hSandTime","SandTime",15,-30.0,30.0);
   TH1F *hSandTOff = new TH1F("hSandTOff","SandTOff",15,-30.0,30.0);
   for (int i=0; i<vTimeSandwich.size(); i++) {
      hSandTime->Fill(vTimeSandwich[i]);
      hSandTOff->Fill(vTOffSandwich[i]);
   }
  
   TF1  *f1 = new TF1("f1","gaus",-20.0,20.0);
 
   TCanvas *w = new TCanvas("w","Sandwich",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hSandTime->GetXaxis()->SetTitle("t_{V5A} - t_{V4A}");
   //hSandTime->SetTitle("Intrinsic time resolution");
   hSandTime->SetTitle("");
   hSandTime->SetLineColor(kBlue+1);
   hSandTime->Draw();
   hSandTOff->SetLineColor(kRed);
   hSandTOff->SetLineStyle(kDashed);
   hSandTOff->Draw("same");
   hSandTOff->Fit(f1,"R");
   f1->SetLineColor(kGreen-2);
   f1->Draw("same");
   w->SaveAs("TimeRes_Sandwich_Offset.pdf");

/*
   TCanvas *ul = new TCanvas("ul","Veto4_B",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogz();
   hMatchedBGOEnTm->GetXaxis()->SetTitle("t_{Veto}-t_{BGO}");
   hMatchedBGOEnTm->GetYaxis()->SetTitle("E_{BGO}");
   hMatchedBGOEnTm->SetTitle("Veto_4_B");
   hMatchedBGOEnTm->Draw("COLZ");
   ul->SaveAs("EnTm_V4_B_log.pdf");
*/

   // 2D plots of Energy-Time of matched and timedVeto
/*   TH2F *hTimedBGOEnTm = new TH2F("hTimedBGOEnTm","En-Time",25,-200.0,200.0,20,0,10.0);
   for (int i=0; i<vTimedBGOTm0.size(); i++) {
      for (int j=0; j<vTimedBGOEn0.size(); j++) {
         hTimedBGOEnTm->Fill(vTimedBGOTm0[i],(vTimedBGOEn0[j]/1000.0));
      }
   } */

   
}

int main() {
   IntrinTRes();   
   return 0;
}
