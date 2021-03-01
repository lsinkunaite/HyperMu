//////////////////////////////////////////////////////////////
/*                                                          */
/*  LS: to draw a full spectrum of mu-decay for >= 250-mm   */
/*  scintillator, SciD3, increase the number of array ele-  */
/*  ments in the location #1, modify the # of bins when     */
/*  filling the arrays in the locations #2 and change the   */
/*  range in the location #3.                               */
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

void VetoEff(){

   //Some style definitions
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

   std::string runnumber = "run530/530";
  

   std::vector<int> timemin;
   std::vector<int> timemax;

   timemin.push_back(100);
   timemax.push_back(1000);

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
   std::string fileBGOBackB = runnumber+"_BGO_Back_B_prep.txt";
   std::string fileBGOBackC = runnumber+"_BGO_Back_C_prep.txt";
   std::string fileBGOBackE = runnumber+"_BGO_Back_E_prep.txt";
   

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
   BGOfiles.push_back(fileBGOBackB);
   BGOfiles.push_back(fileBGOBackC);
   BGOfiles.push_back(fileBGOBackE);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float EventID, Instance, Energy, Time;
   float iEventID;


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
   // BGOs
//   std::vector< std::vector< double > > allIDBGOBackCluster;
//   std::vector< std::vector< double > > allEnBGOBackCluster;

   
		   
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
      //std::string astring;
      //getline(fVeto4A, astring, '*');
      //std::cout << astring << std::endl;
      fVeto4A >> EvIDV4A >> InstV4A >> EdepV4A >> TimeV4A;
      vEvIDV4A.push_back(EvIDV4A);
      vEdepV4A.push_back(EdepV4A);
      vTimeV4A.push_back(TimeV4A);
      //std::cout << "EvID = " << EvIDV4A << ", InstV4A = " << InstV4A << ", Edep = "<< EdepV4A << ", Time = " << TimeV4A << std::endl;
      }
   vEvIDV4A.pop_back();
   vEdepV4A.pop_back();
   vTimeV4A.pop_back();
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


/*
   // Veto5_A
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

*/

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


/*
   // BGO_Back_B
   std::ifstream fBGOBackB(BGOfiles[1]);
   std::vector<double> vEvIDBGOBackB;
   std::vector<double> vEdepBGOBackB;
   std::vector<double> vEkeVBGOBackB;
   std::vector<double> vTimeBGOBackB;
   double kbgobackb = 1.94;
   double bbgobackb = 10.34;
   while (!fBGOBackB.eof()) {
      double EvIDBGOBackB, InstBGOBackB, EdepBGOBackB, TimeBGOBackB;
      double EkeVBGOBackB;
      fBGOBackB >> EvIDBGOBackB >> InstBGOBackB >> EdepBGOBackB >> TimeBGOBackB;
      vEvIDBGOBackB.push_back(EvIDBGOBackB);
      vEdepBGOBackB.push_back(EdepBGOBackB);
      vTimeBGOBackB.push_back(TimeBGOBackB);
      EkeVBGOBackB = EdepBGOBackB*kbgobackb+bbgobackb;
      vEkeVBGOBackB.push_back(EkeVBGOBackB);
   }
   vEvIDBGOBackB.pop_back();
   vEdepBGOBackB.pop_back();
   vTimeBGOBackB.pop_back();
   vEkeVBGOBackB.pop_back();
   fBGOBackB.close();


   // BGO_Back_C
   std::ifstream fBGOBackC(BGOfiles[2]);
   std::vector<double> vEvIDBGOBackC;
   std::vector<double> vEdepBGOBackC;
   std::vector<double> vEkeVBGOBackC;
   std::vector<double> vTimeBGOBackC;
   double kbgobackc = 1.82;
   double bbgobackc = 11.70;
   while (!fBGOBackC.eof()) {
      double EvIDBGOBackC, InstBGOBackC, EdepBGOBackC, TimeBGOBackC;
      double EkeVBGOBackC;
      fBGOBackC >> EvIDBGOBackC >> InstBGOBackC >> EdepBGOBackC >> TimeBGOBackC;
      vEvIDBGOBackC.push_back(EvIDBGOBackC);
      vEdepBGOBackC.push_back(EdepBGOBackC);
      vTimeBGOBackC.push_back(TimeBGOBackC);
      EkeVBGOBackC = EdepBGOBackC*kbgobackc+bbgobackc;
      vEkeVBGOBackC.push_back(EkeVBGOBackC);
   }
   vEvIDBGOBackC.pop_back();
   vEdepBGOBackC.pop_back();
   vTimeBGOBackC.pop_back();
   vEkeVBGOBackC.pop_back();
   fBGOBackC.close();


   // BGO_Back_E
   std::ifstream fBGOBackE(BGOfiles[3]);
   std::vector<double> vEvIDBGOBackE;
   std::vector<double> vEdepBGOBackE;
   std::vector<double> vEkeVBGOBackE;
   std::vector<double> vTimeBGOBackE;
   double kbgobacke = 1.88;
   double bbgobacke = 20.78;
   while (!fBGOBackE.eof()) {
      double EvIDBGOBackE, InstBGOBackE, EdepBGOBackE, TimeBGOBackE;
      double EkeVBGOBackE;
      fBGOBackE >> EvIDBGOBackE >> InstBGOBackE >> EdepBGOBackE >> TimeBGOBackE;
      vEvIDBGOBackE.push_back(EvIDBGOBackE);
      vEdepBGOBackE.push_back(EdepBGOBackE);
      vTimeBGOBackE.push_back(TimeBGOBackE);
      EkeVBGOBackE = EdepBGOBackE*kbgobacke+bbgobacke;
      vEkeVBGOBackE.push_back(EkeVBGOBackE);  
   }
   vEvIDBGOBackE.pop_back();
   vEdepBGOBackE.pop_back();
   vTimeBGOBackE.pop_back();
   vEkeVBGOBackE.pop_back();
   fBGOBackE.close();
*/



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

/*
   // Veto5_A
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

*/
   // BGO_Back_A
   std::vector<double> vEnBGOBackA;
   std::vector<double> vIDBGOBackA;
   std::vector<double> vTmBGOBackA;
   std::vector<double> vTmBGOBackA2;
   std::vector<double> vTmBGOBackA3;
   std::vector<double> vTmBGOBackA4;
   int cBackBGOA;
   for (int s=0; s<vTimeBGOBackA.size(); s++) {
      if ((vTimeBGOBackA[s] > timemin[0]) && (vTimeBGOBackA[s] <timemax[0])) {
         //if (vEkeVBGOBackA[s] < 100000) {
         if ((vEkeVBGOBackA[s] >= 5000) && (vEkeVBGOBackA[s] <= 20000)) {
            vIDBGOBackA.push_back(vEvIDBGOBackA[s]);
            vEnBGOBackA.push_back(vEkeVBGOBackA[s]);
            vTmBGOBackA.push_back(vTimeBGOBackA[s]);
         }
         /*if (vEkeVBGOBackA[s] <= 1000) {
            vTmBGOBackA2.push_back(vTimeBGOBackA[s]);
         } else if ((vEkeVBGOBackA[s] >=20000) && (vEkeVBGOBackA[s] < 100000)) {
            vTmBGOBackA3.push_back(vTimeBGOBackA[s]);
         } else if ((vEkeVBGOBackA[s] > 1000) && (vEkeVBGOBackA[s] <20000)) {
            vTmBGOBackA4.push_back(vTimeBGOBackA[s]);
         }*/
      }
   }
/*
   for (int s=0; s<vTimeBGOBackA.size(); s++) {
      if ((vTimeBGOBackA[s] > timemin[g]) && (vTimeBGOBackA[s] <timemax[g])) {
         if (vEkeVBGOBackA[s] < 100000) {    
            cBackBGOA = vPureIDBGOBackA.size();
            if (cBackBGOA == 0) {
               vPureIDBGOBackA.push_back(vEvIDBGOBackA[s]);
               vPureEnBGOBackA.push_back(vEkeVBGOBackA[s]);            
            } else if (vEvIDBGOBackA[s] == vPureIDBGOBackA[cBackBGOA-1]) {
               vPureEnBGOBackA[cBackBGOA-1] = vPureEnBGOBackA[cBackBGOA-1] + vEkeVBGOBackA[s]; 
            } else {
               vPureIDBGOBackA.push_back(vEvIDBGOBackA[s]);
               vPureEnBGOBackA.push_back(vEkeVBGOBackA[s]);
            }
         }
      }
   }
*/
/*
   // BGO_Back_B
   std::vector<double> vPureEnBGOBackB;
   std::vector<double> vPureIDBGOBackB;
   int cBackBGOB;
   for (int s=0; s<vTimeBGOBackB.size(); s++) {
      if ((vTimeBGOBackB[s] > timemin[g]) && (vTimeBGOBackB[s] <timemax[g])) {
         if (vEkeVBGOBackB[s] < 100000) {    
            cBackBGOB = vPureIDBGOBackB.size();
            if (cBackBGOB == 0) {
               vPureIDBGOBackB.push_back(vEvIDBGOBackB[s]);
               vPureEnBGOBackB.push_back(vEkeVBGOBackB[s]); 
            } else if (vEvIDBGOBackB[s] == vPureIDBGOBackB[cBackBGOB-1]) {
               vPureEnBGOBackB[cBackBGOB-1] = vPureEnBGOBackB[cBackBGOB-1] + vEkeVBGOBackB[s]; 
            } else {
               vPureIDBGOBackB.push_back(vEvIDBGOBackB[s]);
               vPureEnBGOBackB.push_back(vEkeVBGOBackB[s]);
            }
         }
      }
   }

   
   // BGO_Back_C
   std::vector<double> vPureEnBGOBackC;
   std::vector<double> vPureIDBGOBackC;
   int cBackBGOC;
   for (int s=0; s<vTimeBGOBackC.size(); s++) {
      if ((vTimeBGOBackC[s] > timemin[g]) && (vTimeBGOBackC[s] <timemax[g])) {
         if (vEkeVBGOBackC[s] < 100000) {    
            cBackBGOC = vPureIDBGOBackC.size();
            if (cBackBGOC == 0) {
               vPureIDBGOBackC.push_back(vEvIDBGOBackC[s]);
               vPureEnBGOBackC.push_back(vEkeVBGOBackC[s]); 
            } else if (vEvIDBGOBackC[s] == vPureIDBGOBackC[cBackBGOC-1]) {
               vPureEnBGOBackC[cBackBGOC-1] = vPureEnBGOBackC[cBackBGOC-1] + vEkeVBGOBackC[s]; 
            } else {
               vPureIDBGOBackC.push_back(vEvIDBGOBackC[s]);
               vPureEnBGOBackC.push_back(vEkeVBGOBackC[s]);
            }
         }
      }
   }


   // BGO_Back_E
   std::vector<double> vPureEnBGOBackE;
   std::vector<double> vPureIDBGOBackE;
   int cBackBGOE;
   for (int s=0; s<vTimeBGOBackE.size(); s++) {
      if ((vTimeBGOBackE[s] > timemin[g]) && (vTimeBGOBackE[s] <timemax[g])) {
         if (vEkeVBGOBackE[s] < 100000) {    
            cBackBGOE = vPureIDBGOBackE.size();
            if (cBackBGOE == 0) {
               vPureIDBGOBackE.push_back(vEvIDBGOBackE[s]);
               vPureEnBGOBackE.push_back(vEkeVBGOBackE[s]);
            } else if (vEvIDBGOBackE[s] == vPureIDBGOBackE[cBackBGOE-1]) {
               vPureEnBGOBackE[cBackBGOE-1] = vPureEnBGOBackE[cBackBGOE-1] + vEkeVBGOBackE[s];
            } else {
               vPureIDBGOBackE.push_back(vEvIDBGOBackE[s]);
               vPureEnBGOBackE.push_back(vEkeVBGOBackE[s]);
            }
         }  
      }
   }
 */  



   std::cout << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m---------------------- Matching --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;


   //const int nbins = 26;
   //double Eint = 26000.0/(nbins);
   //const int nsamps = 26;
   //double Estep = 26000.0/(nsamps);
   const int nbins = 2;
   const int nsamps = 2;
   double Eint=15000.0/(nbins);
   double Estep = 15000.0/(nbins);
   std::vector<double> Ethr;
   //Ethr.push_back(0.0);
   Ethr.push_back(-10000.0);
   for (int i=1; i<nsamps; i++) Ethr.push_back(Ethr[i-1]+Estep);
   std::vector<double> Eveto = {0, 250, 500, 750, 1000, 1250, 1500};
   //std::vector<double> EffVeto4A;
   //std::vector<double> EffVeto4A2;
   //std::vector<double> EffVeto4A3;
   //std::vector<double> EffVeto4B;
   //std::vector<double> EffVeto4B2;
   //std::vector<double> EffVeto4B3;

   //std::vector<double> vMatchedEnergyV4A;
   //std::vector<double> vMatchedEnergyV4A2;
   //std::vector<double> vMatchedEnergyV4A3;
   //std::vector<double> vMatchedEnergyV4B;
   //std::vector<double> vMatchedEnergyV4B2;
   //std::vector<double> vMatchedEnergyV4B3;
   

   // AND and OR loop
   std::vector<double> Effand;
   std::vector<double> Effand2;
   std::vector<double> Effand3;
   std::vector<double> Effor;
   std::vector<double> Effor2;
   std::vector<double> Effor3;

   std::vector<double> EffVetoV4A;
   std::vector<double> EffVeto2V4A;
   std::vector<double> EffVeto3V4A;
   std::vector<double> EffVetoV4B;
   std::vector<double> EffVeto2V4B;
   std::vector<double> EffVeto3V4B;

   for (int m=1; m<Ethr.size(); m++) {
//      double MatchCounterV4A=0;
//      double TotalCounterV4A=0;
//      double MatchCounterV4A2=0;
//      double MatchCounterV4A3=0;
//      double TotalCounterV4B=0;
//      double MatchCounterV4B=0;
//      double MatchCounterV4B2=0;
//      double MatchCounterV4B3=0;

      double MatchEnCountV4A=0;
      double MatchEnCount2V4A=0;
      double MatchEnCount3V4A=0;
      double TotalCountV4A=0;
      double MatchEnCountV4B=0;
      double MatchEnCount2V4B=0;
      double MatchEnCount3V4B=0;
      double TotalCountV4B=0;


      for (int q=0; q<Eveto.size(); q++) {
         MatchEnCountV4A = 0;
         MatchEnCount2V4A = 0;
         MatchEnCount3V4A = 0;
         TotalCountV4A = 0;
         MatchEnCountV4B = 0;
         MatchEnCount2V4B = 0;
         MatchEnCount3V4B = 0;
         TotalCountV4B = 0;
         std::cout << " q = " << q << ", Eveto THR = " << Eveto[q] << std::endl;

         std::vector<double> vBGOMatchedV4A;
         std::vector<double> vBGOMatched2V4A;
         std::vector<double> vBGOMatched3V4A;
         std::vector<double> vBGOMatchedV4B;
         std::vector<double> vBGOMatched2V4B;
         std::vector<double> vBGOMatched3V4B;

         for (int n=0; n<vIDBGOBackA.size(); n++) {
            // Veto_4_A
            int UnmatchedV4A = 0;
            int Unmatched2V4A = 0;
            int Unmatched3V4A = 0;
            int GoodCountV4A = 0;
            for (int k=0; k<vEvIDV4A.size(); k++) {
               if (vEvIDV4A[k] == vIDBGOBackA[n]) {
                  if (vInstV4A[k] == 0) {
                     if (vEdepV4A[k] >= Eveto[q]) {
                        if ((vTimeV4A[k] >= (vTmBGOBackA[n]-250)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+65))) {
                           if ((vTimeV4A[k] >= (vTmBGOBackA[n]-60)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+30))) {
                              if ((vTimeV4A[k] >= (vTmBGOBackA[n]-30)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+30))) {
                                 MatchEnCount3V4A++;
                                 Unmatched3V4A = 1;
                              }
                              MatchEnCount2V4A++;
                              Unmatched2V4A = 1;
                           }
                           MatchEnCountV4A++;
                           UnmatchedV4A = 1;
                        }
                     }
                  } else {
                     GoodCountV4A = 1;
                  }
               }
            }
            if (GoodCountV4A == 0) {
               TotalCountV4A++;
               if (UnmatchedV4A == 0) {
                  vBGOMatchedV4A.push_back(0);
               } else {
                  vBGOMatchedV4A.push_back(1);
               }
               if (Unmatched2V4A == 0) {
                  vBGOMatched2V4A.push_back(0);
               } else {
                  vBGOMatched2V4A.push_back(1);
               }
               if (Unmatched3V4A == 0) {
                  vBGOMatched3V4A.push_back(0);
               } else {
                  vBGOMatched3V4A.push_back(1);
               }
            } else {
               vBGOMatchedV4A.push_back(-1);
               vBGOMatched2V4A.push_back(-1);
               vBGOMatched3V4A.push_back(-1);
            }

            // Veto_4_B
            int UnmatchedV4B = 0;
            int Unmatched2V4B = 0;
            int Unmatched3V4B = 0;
            int GoodCountV4B = 0;
            for (int l=0; l<vEvIDV4B.size(); l++) {
               if (vEvIDV4B[l] == vIDBGOBackA[n]) {
                  if (vInstV4B[l] == 0) {
                     if (vEdepV4B[l] >= Eveto[q]) {
                        if ((vTimeV4B[l] >= (vTmBGOBackA[n]-250)) && (vTimeV4B[l] <= (vTmBGOBackA[n]+65))) {
                           if ((vTimeV4B[l] >= (vTmBGOBackA[n]-60)) && (vTimeV4B[l] <= (vTmBGOBackA[n]+30))) {
                              if ((vTimeV4B[l] >= (vTmBGOBackA[n]-30)) && (vTimeV4B[l] <= (vTmBGOBackA[n]+30))) {
                                 MatchEnCount3V4B++;
                                 Unmatched3V4B = 1;
                              }
                              MatchEnCount2V4B++;
                              Unmatched2V4B = 1;
                           }
                           MatchEnCountV4B++;
                           UnmatchedV4B = 1;
                        }
                     }
                  } else {
                     GoodCountV4B = 1;
                  }
               }
            }
            if (GoodCountV4B == 0) {
               TotalCountV4B++;
               if (UnmatchedV4B == 0) {
                  vBGOMatchedV4B.push_back(0);
               } else {
                  vBGOMatchedV4B.push_back(1);
               }
               if (Unmatched2V4B == 0) {
                  vBGOMatched2V4B.push_back(0);
               } else {
                  vBGOMatched2V4B.push_back(1);
               }
               if (Unmatched3V4B == 0) {
                  vBGOMatched3V4B.push_back(0);
               } else {
                  vBGOMatched3V4B.push_back(1);
               }
            } else {
               vBGOMatchedV4B.push_back(-1);
               vBGOMatched2V4B.push_back(-1);
               vBGOMatched3V4B.push_back(-1);
            }


         }

         EffVetoV4A.push_back(MatchEnCountV4A/TotalCountV4A);
         EffVeto2V4A.push_back(MatchEnCount2V4A/TotalCountV4A);
         EffVeto3V4A.push_back(MatchEnCount3V4A/TotalCountV4A);
         //std::cout << "A :: EffVeto = " << MatchEnCountV4A/TotalCountV4A << ", Total = " << TotalCountV4A << ", Match = " << MatchEnCountV4A << std::endl;

         EffVetoV4B.push_back(MatchEnCountV4B/TotalCountV4B);
         EffVeto2V4B.push_back(MatchEnCount2V4B/TotalCountV4B);
         EffVeto3V4B.push_back(MatchEnCount3V4B/TotalCountV4B);
         //std::cout << "B :: EffVEto = " << MatchEnCountV4B/TotalCountV4B << ", Total = " << TotalCountV4B << ", Match = " << MatchEnCountV4B << std::endl;
       


         // Veto_4_A && Veto_4_B
         double ANDCounter=0;
         double ANDCounter2=0;
         double ANDCounter3=0;
         double ORCounter=0;
         double ORCounter2=0;
         double ORCounter3=0;
         double TotalCounter=0;
         double TotalCounter2=0;
         double TotalCounter3=0;
         for (int j=0; j<vBGOMatchedV4A.size(); j++) {
            // Time window 1
            if ((vBGOMatchedV4A[j] == 1) && (vBGOMatchedV4B[j] == 1)) {
               ANDCounter++;
               ORCounter++;
               TotalCounter++;
            } else if ((vBGOMatchedV4A[j] == 1) || (vBGOMatchedV4B[j] == 1)) {
               ORCounter++;
               TotalCounter++;
            } else if ((vBGOMatchedV4A[j] + vBGOMatchedV4B[j]) == 0) {
               TotalCounter++;
            }
            // Time window 2
            if ((vBGOMatched2V4A[j] == 1) && (vBGOMatched2V4B[j] == 1)) {
               ANDCounter2++;
               ORCounter2++;
               TotalCounter2++;
            } else if ((vBGOMatched2V4A[j] == 1) || (vBGOMatched2V4B[j] == 1)) {
               ORCounter2++;
               TotalCounter2++;
            } else if ((vBGOMatched2V4A[j] + vBGOMatched2V4B[j]) == 0) {
               TotalCounter2++;
            }
            // Time window 3
            if ((vBGOMatched3V4A[j] == 1) && (vBGOMatched3V4B[j] == 1)) {
               ANDCounter3++;
               ORCounter3++;
               TotalCounter3++;
            } else if ((vBGOMatched3V4A[j] == 1) || (vBGOMatched3V4B[j] == 1)) {
               ORCounter3++;
               TotalCounter3++;
            } else if ((vBGOMatched3V4A[j] + vBGOMatched3V4B[j]) == 0) {
               TotalCounter3++;
            }
         }
         Effand.push_back(ANDCounter/TotalCounter);
         Effand2.push_back(ANDCounter2/TotalCounter2);
         Effand3.push_back(ANDCounter3/TotalCounter3);
         Effor.push_back(ORCounter/TotalCounter);
         Effor2.push_back(ORCounter2/TotalCounter2);
         Effor3.push_back(ORCounter3/TotalCounter3);
 
         std::cout << "1 :: OR = " << ORCounter/TotalCounter << std::endl;
         std::cout << "2 :: OR = " << ORCounter2/TotalCounter2 << std::endl;
         std::cout << "3 :: OR = " << ORCounter3/TotalCounter3 << std::endl;
      }  
        
   }



 
   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;



   const int nticks = 7;
   float EffVetoarr[nticks] = {};
   float EffVeto2arr[nticks] = {};
   float EffVeto3arr[nticks] = {};
   float Evetoarr[nticks] = {};

   for (int i=0; i<nticks; i++) {
      //EffVetoarr[i] = EffVetoV4A[i];
      EffVetoarr[i] = Effor[i];
      //EffVeto2arr[i] = EffVeto2V4A[i];
      EffVeto2arr[i] = Effor2[i];
      //EffVeto3arr[i] = EffVeto3V4A[i];
      EffVeto3arr[i] = Effor3[i];
      Evetoarr[i] = Eveto[i];
   }

   TCanvas *fvcut = new TCanvas("fvcut","E_{THR}",800,600);
   gPad->SetGrid(1,1);
   TGraph *grv0 = new TGraph(nticks,Evetoarr,EffVetoarr);
   grv0->SetTitle("Efficiency of Veto_4 (OR)");
   grv0->GetXaxis()->SetTitle("E_{Veto} [adc]");
   grv0->GetYaxis()->SetTitle("Eff");
   grv0->GetYaxis()->SetTitleOffset(1.9);
   grv0->GetYaxis()->SetRangeUser(0.62,1.01);
   grv0->GetXaxis()->SetRangeUser(0.0,1500.0);
   //grv0->SetLineColor(kGray+3);
   grv0->SetLineWidth(3);
   grv0->SetLineColor(kViolet-5);
   grv0->SetMarkerColor(kViolet-5);
   grv0->SetMarkerSize(1.5);
   grv0->SetMarkerStyle(21);
   grv0->Draw("ALP");
   TGraph *grv1 = new TGraph(nticks,Evetoarr,EffVeto2arr);
   grv1->SetLineWidth(3);
   grv1->SetLineColor(kTeal-5);
   //grv1->SetLineStyle(kDashed);
   grv1->SetMarkerColor(kTeal-5);
   grv1->SetMarkerSize(1.5);
   grv1->SetMarkerStyle(22);
   grv1->Draw("LP");
   TGraph *grv2 = new TGraph(nticks,Evetoarr,EffVeto3arr);
   grv2->SetLineWidth(3);
   grv2->SetLineColorAlpha(kOrange-5,0.1);
   grv2->SetMarkerColor(kOrange-5);
   grv2->SetMarkerSize(1.5);
   grv2->SetMarkerStyle(23);
   grv2->Draw("LP");
   auto legendvcut = new TLegend(0.82,0.71,0.94,0.87);
   legendvcut->AddEntry(grv0,"t = [-250..65] ns","f");
   legendvcut->AddEntry(grv1,"t = [-60..30] ns","f");
   legendvcut->AddEntry(grv2,"t = [-30..30] ns","f");
   legendvcut->Draw();
   fvcut->SaveAs("530_EffV4_OR_vcuttime.pdf");

   
   double q0v41[] = {0.989055};
   double q0v42[] = {0.966436};
   double q0v43[] = {0.915359};
   double q1v41[] = {0.988325};
   double q1v42[] = {0.965706};
   double q1v43[] = {0.91463};
   double q2v41[] = {0.987961};
   double q2v42[] = {0.965341};
   double q2v43[] = {0.91463};
   double q3v41[] = {0.987961};
   double q3v42[] = {0.965341};
   double q3v43[] = {0.91463};
   double q4v41[] = {0.980664};
   double q4v42[] = {0.958045};
   double q4v43[] = {0.907333};
   double q5v41[] = {0.896275};
   double q5v42[] = {0.876187};
   double q5v43[] = {0.829803};
   double q6v41[] = {0.678127};
   double q6v42[] = {0.663497};
   double q6v43[] = {0.632041};

   auto c42 = new TCanvas("c42","c42",800,600);
   gPad->SetGrid(1,1);
   double x[] = {0.0, 250.0, 500.0, 750.0, 1000.0, 1250.0, 1500.0};
   double y[] = {0.987763, 0.9870535, 0.9868755, 0.986343, 0.9783565, 0.888993, 0.673808};
   double ex[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
   double ey[] = {0.001291, 0.0012935, 0.0014715, 0.001651, 0.0014965, 0.008253, 0.002039};
   auto ge = new TGraphErrors(7, x, y, ex, ey);
   ge->SetFillColor(4);
   ge->SetFillStyle(3010);
   ge->Draw("a3");
   ge->GetYaxis()->SetRangeUser(0.8,1.01);
   ge->GetXaxis()->SetTitle("E_{Veto} [adc]");


/* 
  
   TH1F *hTimeV4A = new TH1F("hTimeV4A","Veto4A",200,-500.0,10000.0); 
   for (int i=0; i<vTimeV4A.size(); i++) {
      hTimeV4A->Fill(vTimeV4A[i]);
   }
 
   TCanvas *newc = new TCanvas("newc","V4A",800,600);
   gPad->SetLogy();
   hTimeV4A->SetTitle("Veto_4_A");
   hTimeV4A->GetXaxis()->SetTitle("Time [ns]");
   hTimeV4A->Draw();
*/   


/*
   float EffV4ANDarr[nbins-1] = {};
   float EffV4ORarr[nbins-1] = {};
   float EBGOarr[nbins-1] = {};

   for (int i=0; i<(nbins-1); i++) {
      EffV4ANDarr[i] = Effand[i];
      EffV4ORarr[i] = Effor[i];
      //EBGOarr[i] = EnBGO[i]/1000.0;
   }
  
   float EffV4Aarr[nsamps-1] = {}; // Efficiency V4_A
   float EffV4Aarr2[nsamps-1] = {};
   float EffV4Aarr3[nsamps-1] = {};
  // float Ethrarr[nsamps-1] = {};
   float EffV4Barr[nsamps-1] = {}; // Efficiency V4_B
   float EffV4Barr2[nsamps-1] = {};
   float EffV4Barr3[nsamps-1] = {};

   for (int i=0; i<(nsamps-1); i++) {
      EffV4Aarr[i] = EffVeto4A[i];
      EffV4Aarr2[i] = EffVeto4A2[i];
      EffV4Aarr3[i] = EffVeto4A3[i];
      EffV4Barr[i] = EffVeto4B[i];
      EffV4Barr2[i] = EffVeto4B2[i];
      EffV4Barr3[i] = EffVeto4B3[i];
      //Ethrarr[i] = Ethr[i]/1000.0;
   }


 
   TCanvas *fcomp = new TCanvas("fcomp","E_{THR}",800,600);
   gPad->SetGrid(1,1);
   //TGraph *grV4OR = new TGraph(nbins-1,EBGOarr,EffV4ORarr);
   TGraph *grV4OR = new TGraph(nbins-1,Ethrarr,EffV4ORarr);
   grV4OR->SetTitle("Efficiency of Veto_4");
   grV4OR->GetXaxis()->SetTitle("E_{BGO} [MeV]");
   grV4OR->GetYaxis()->SetTitle("Eff");
   grV4OR->GetYaxis()->SetTitleOffset(2.1);
   grV4OR->GetYaxis()->SetRangeUser(0.6,1.01);
   //grV4OR->SetLineColor(kGray+3);
   grV4OR->SetLineWidth(3);
   grV4OR->SetLineColor(kViolet-5);
   //grV4OR->SetMarkerColor(kViolet-5);
   //grV4OR->SetMarkerSize(1.5);
   //grV4OR->SetMarkerStyle(21);
   grV4OR->Draw("ALP");
   //TGraph *grV4AND = new TGraph(nbins-1,EBGOarr,EffV4ANDarr);
   TGraph *grV4AND = new TGraph(nbins-1,Ethrarr,EffV4ANDarr);
   //grV4AND->SetLineColor(kGray+3);
   grV4AND->SetLineWidth(3);
   grV4AND->SetLineColor(kTeal-5);
   //grV4AND->SetMarkerColor(kTeal-5);
   //grV4AND->SetMarkerSize(1.5);
   //grV4AND->SetMarkerStyle(22);
   //grV4AND->Draw("CP");
   grV4AND->Draw("LP");
   TGraph *grV4a = new TGraph(nsamps-1,Ethrarr,EffV4Aarr3);
   grV4a->SetLineWidth(3);
   grV4a->SetLineColor(kOrange-3);
   grV4a->Draw("LP");
   TGraph *grV4b = new TGraph(nsamps-1,Ethrarr,EffV4Barr3);
   grV4b->SetLineWidth(3);
   grV4b->SetLineColor(kRed-7);
   grV4b->Draw("LP");
   auto legendV4comp = new TLegend(0.82,0.71,0.94,0.87); 
   legendV4comp->AddEntry(grV4AND,"V4_A && V4_B ","f");
   legendV4comp->AddEntry(grV4OR,"V4_A || V4_B","f");
   legendV4comp->AddEntry(grV4a,"V4_A","f");
   legendV4comp->AddEntry(grV4b,"V4_B","f");
   legendV4comp->Draw();
   //fcomp->SaveAs("EffV4_comp_all.pdf");
*/

/*
   TH1F *hTime = new TH1F("hTime","Veto4A",33,0,1100.0);
   TH1F *hTimeLow = new TH1F("hTimeLow","Veto4A",33,0,1100.0);
   TH1F *hTimeHigh = new TH1F("hTimeHigh","Veto4A",33,0,1100.0); 
   TH1F *hTimeMid = new TH1F("hTimeMid","Veto4A",33,0,1100.0);
   for (int i=0; i<vTmBGOBackA.size(); i++) {
      hTime->Fill(vTmBGOBackA[i]);
   }
   for (int i=0; i<vTmBGOBackA2.size(); i++) {
      hTimeLow->Fill(vTmBGOBackA2[i]);
   }
   for (int i=0; i<vTmBGOBackA3.size(); i++) {
      hTimeHigh->Fill(vTmBGOBackA3[i]);
   }
   for (int i=0; i<vTmBGOBackA4.size(); i++) {
      hTimeMid->Fill(vTmBGOBackA4[i]);
   }

   TCanvas *ctime = new TCanvas("ctime","ctime",800,600);
   hTime->Draw();
   hTimeLow->SetLineColor(kRed);
   hTimeLow->Draw("SAME");
   hTimeHigh->SetLineColor(kGreen-2);
   hTimeHigh->Draw("SAME");
   hTimeMid->SetLineColor(kOrange);
   hTimeMid->Draw("SAME");
   auto lt = new TLegend(0.82,0.71,0.94,0.87);
   lt->AddEntry(hTime,"All","f"); 
   lt->AddEntry(hTimeLow,"E <= 1 MeV","f");
   lt->AddEntry(hTimeHigh,"E >= 20 MeV","f");
   lt->AddEntry(hTimeMid,"E = (1..20) MeV","f");
   lt->Draw();
   //ctime->SaveAs("test0007.pdf");
*/


/*
   TCanvas *f = new TCanvas("f","E_{THR}",800,600);
   //gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grV4A3 = new TGraph(nsamps-1,Ethrarr,EffV4Aarr3);
   grV4A3->SetTitle("Efficiency of Veto_4_A");
   grV4A3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grV4A3->GetYaxis()->SetTitle("Eff");
   grV4A3->GetYaxis()->SetTitleOffset(2.1);
   grV4A3->SetLineColor(kGray+3);
   grV4A3->SetLineWidth(2);
   grV4A3->SetFillColor(kViolet-5);
   //grV4A3->SetFillStyle(3002);
   grV4A3->Draw("ALB1");
   TGraph *grV4A2 = new TGraph(nsamps-1,Ethrarr,EffV4Aarr2);
   grV4A2->SetLineColor(kGray+3);
   grV4A2->SetLineWidth(2);
   grV4A2->SetFillColor(kTeal-5);
   //grV4A2->SetFillStyle(3002);
   grV4A2->Draw("LB1");
   TGraph *grV4A = new TGraph(nsamps-1,Ethrarr,EffV4Aarr);
   grV4A->SetLineColor(kGray+3);
   grV4A->SetLineWidth(2);
   grV4A->SetFillColor(kOrange-4);
   //grV4A->SetFillStyle(3002);
   grV4A->Draw("LB1");
   auto legendV4A = new TLegend(0.82,0.71,0.94,0.87); 
   legendV4A->AddEntry(grV4A3,"t=[-250, 65] ns","f");
   legendV4A->AddEntry(grV4A2,"t=[-200, 35] ns","f");
   legendV4A->AddEntry(grV4A,"t=[-150, 35] ns", "f");
   legendV4A->Draw();
   f->SaveAs("EffV4A_indiv_en.pdf");
   
   TCanvas *f2 = new TCanvas("f2","E_{THR}",800,600);
   gPad->SetGrid(1,1);
   TGraph *grV4B3 = new TGraph(nsamps-1,Ethrarr,EffV4Barr3);
   grV4B3->SetTitle("Efficiency of Veto_4_B");
   grV4B3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grV4B3->GetYaxis()->SetTitle("Eff");
   grV4B3->GetYaxis()->SetTitleOffset(2.1);
   grV4B3->SetLineColor(kGray+3);
   grV4B3->SetLineWidth(2);
   grV4B3->SetFillColor(kViolet-5);
   grV4B3->Draw("ALB1");
   TGraph *grV4B2 = new TGraph(nsamps-1,Ethrarr,EffV4Barr2);
   grV4B2->SetLineColor(kGray+3);
   grV4B2->SetLineWidth(2);
   grV4B2->SetFillColor(kTeal-5);
   grV4B2->Draw("LB1");
   TGraph *grV4B = new TGraph(nsamps-1,Ethrarr,EffV4Barr);
   grV4B->SetLineColor(kGray+3);
   grV4B->SetLineWidth(2);
   grV4B->SetFillColor(kOrange-4);
   grV4B->Draw("LB1");
   auto legendV4B = new TLegend(0.82,0.71,0.94,0.87); 
   legendV4B->AddEntry(grV4B3,"t=[-250, 65] ns","f");
   legendV4B->AddEntry(grV4B2,"t=[-200, 35] ns","f");
   legendV4B->AddEntry(grV4B,"t=[-150, 35] ns", "f");
   legendV4B->Draw();
   f2->SaveAs("EffV4B_indiv_en.pdf");
*/

/*
   TH1F *hMatched = new TH1F("hMatched","Veto4A",100,0,10.0);
   TH1F *hMatched2 = new TH1F("hMatched2","Veto4A",100,0,10.0);
   TH1F *hMatched3 = new TH1F("hMatched3","Veto4A",100,0,10.0); 

   for (int i=0; i<vMatchedEnergyV4A.size(); i++) {
      hMatched->Fill((vMatchedEnergyV4A[i])/(1000.0));
   }
   for (int i=0; i<vMatchedEnergyV4A2.size(); i++) {
      hMatched2->Fill((vMatchedEnergyV4A2[i])/(1000.0));
   }
   for (int i=0; i<vMatchedEnergyV4A3.size(); i++) {
      hMatched3->Fill((vMatchedEnergyV4A3[i])/(1000.0));
   }

   TH1F *hTime5MeV = new TH1F("hTime5MeV","Veto4A",50,-250.0,50.0);
   TH1F *hTime10MeV = new TH1F("hTime10MeV","Veto4A",50,-250.0,50.0);
   TH1F *hTime15MeV = new TH1F("hTime15MeV","Veto4A",50,-250.0,50.0);

   for (int i=0; i<vMatchedTimeV4A5MeV.size(); i++) {
      hTime5MeV->Fill(vMatchedTimeV4A5MeV[i]);
   }
   for (int i=0; i<vMatchedTimeV4A10MeV.size(); i++) {
      hTime10MeV->Fill(vMatchedTimeV4A10MeV[i]);
   }
   for (int i=0; i<vMatchedTimeV4A15MeV.size(); i++) {
      hTime15MeV->Fill(vMatchedTimeV4A15MeV[i]);
   }
   TH2F *hMatchedBGOEnTm = new TH2F("hMatchedBGOEnTm","En-Time",50,-250.0,65.0,50,0,25.0);
   for (int i=0; i<vMatchedBGOTm0.size(); i++) {
      for (int j=0; j<vMatchedBGOEn0.size(); j++) {
         hMatchedBGOEnTm->Fill(vMatchedBGOTm0[i],(vMatchedBGOEn0[j]/1000.0));
      }
   }
*/

/*
   TCanvas *w = new TCanvas("w","Veto4A",800,600);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   hTime5MeV->GetXaxis()->SetTitle("t_{Veto} - t_{BGO}");
   hTime5MeV->SetTitle("Veto_4_A");
   hTime5MeV->SetLineColor(kViolet-5);
   hTime5MeV->SetLineWidth(3);
   hTime5MeV->Draw();
   hTime10MeV->SetLineColor(kTeal-5);
   hTime10MeV->SetLineWidth(3);
   hTime10MeV->Draw("SAME");
   hTime15MeV->SetLineColor(kOrange-5);
   hTime15MeV->SetLineWidth(3);
   hTime15MeV->Draw("SAME");
   auto legend3 = new TLegend(0.83,0.61,0.97,0.77);
   legend3->AddEntry(hTime5MeV,"E_{BGO} >= 5 MeV","f");
   legend3->AddEntry(hTime10MeV,"E_{BGO} >= 10 MeV","f");
   legend3->AddEntry(hTime15MeV,"E_{BGO} >= 15 MeV","f");
   legend3->Draw();
   w->SaveAs("Veto4_A_time_exp.pdf");
*/

/*
   TCanvas *u = new TCanvas("u","En-Tm BGO Veto4B",800,600);
   //gPad->SetLogy();
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   hMatchedBGOEnTm->GetXaxis()->SetTitle("t_{Veto}-t_{BGP}");
   hMatchedBGOEnTm->GetYaxis()->SetTitle("E_{BGO}");
   hMatchedBGOEnTm->SetTitle("En Tm BGO");
   hMatchedBGOEnTm->Draw("COLZ");
   u->SaveAs("BGOBackA2D.pdf");
*/
/*
   TCanvas *u = new TCanvas("u","Veto4A",800,600);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   hTime2500->GetXaxis()->SetTitle("t_{Veto} - t_{BGO}");
   hTime2500->SetTitle("Veto_4_A");
   hTime2500->SetLineColor(kViolet-5);
   hTime2500->SetLineWidth(3);
   hTime2500->Draw();
   hTime5000->SetLineColor(kTeal-5);
   hTime5000->SetLineWidth(3);
   hTime5000->Draw("SAME");
   hTime7500->SetLineColor(kOrange-5);
   hTime7500->SetLineWidth(3);
   hTime7500->Draw("SAME");
   auto legend4 = new TLegend(0.83,0.61,0.97,0.77);
   legend4->AddEntry(hTime2500,"E_{V4_A} = 2500 adc","f");
   legend4->AddEntry(hTime5000,"E_{V4_A} = 5000 adc","f");
   legend4->AddEntry(hTime7500,"E_{V4_A} = 7500 adc","f");
   legend4->Draw();
   u->SaveAs("Veto4_A_time_indiv.pdf");
*/
/*
   TCanvas *z = new TCanvas("z","Veto4A",800,600);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   hMatched3->GetXaxis()->SetTitle("E [adc #times 10^3]");
   hMatched3->SetTitle("Veto_4_A");
   hMatched3->SetLineColor(kGray+3);
   hMatched3->SetLineWidth(3);
   hMatched3->SetFillColor(kViolet-5);
   hMatched3->Draw();
   hMatched2->SetLineColor(kGray+2);
   hMatched2->SetLineWidth(3);
   hMatched2->SetFillColor(kTeal-5);
   hMatched2->Draw("same");
   hMatched2->SetLineColor(kGray+3);
   hMatched2->SetLineWidth(3);
   hMatched->SetFillColor(kOrange-5);
   hMatched->Draw("same");
   auto legend2 = new TLegend(0.75,0.61,0.91,0.77);
   legend2->AddEntry(hMatched3, "t = [-100, 100] ns","f");
   legend2->AddEntry(hMatched2, "t = [-65, 65] ns", "f");
   legend2->AddEntry(hMatched, " t = [-30, 30] ns","f");
   legend2->Draw();
   z->SaveAs("Veto4_A_energy.pdf");
*/

   TH1F *hbgoaadc = new TH1F("hbgoaadc","BGO-A adc",250,0,16.0);
   TH1F *hbgoakev = new TH1F("hbgoakev","BGO-A keV",250,0,30.0);
   //TH1F *hv4a = new TH1F("hv4a","Veto 4 A",250,0,5.0);
/*
   TH1F *h3 = new TH1F("h3","E keV",250,0,55.0);
   TH1F *hbgoa = new TH1F("hbgoa","BGO A",100,0,28.0);
   TH1F *hbgob = new TH1F("hbgob","B",100,0,28.0);
   TH1F *hbgoc = new TH1F("hbgoc","C",100,0,28.0);
   TH1F *hbgoe = new TH1F("hbgoe","E",100,0,28.0);   
*/
/*
   for (int i=0; i<vEdepBGOBackA.size(); i++) {
      hbgoaadc->Fill((vEdepBGOBackA[i])/(1000.0));
      hbgoakev->Fill((vEkeVBGOBackA[i])/(1000.0));
   }


   TCanvas *d = new TCanvas("d","BGO-A",800,600);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   hbgoaadc->GetXaxis()->SetTitle("E [adc #times 10^3]");
   hbgoaadc->SetTitle("BGO Back A");
   hbgoaadc->SetLineColor(kBlack);
   hbgoaadc->Draw();
   d->SaveAs("BGO_Back_A_adc.pdf");
   
   TCanvas *l = new TCanvas("l","BGO-A",800,600);
   gPad->SetLogy();
   gPad->SetGrid();
   hbgoakev->GetXaxis()->SetTitle("E [MeV]");
   hbgoakev->SetTitle("BGO Back A");
   hbgoakev->SetLineColor(kGreen-2);
   hbgoakev->Draw();
   l->SaveAs("BGO_Back_A_keV.pdf");
*/

   //for (int i=0; i<allEnBGOBackCluster[1].size(); i++) {
   //   ht2->Fill((allEnBGOBackCluster[1][i])/(1000.0));
   //}
   //for (int i=0; i<allEnBGOBackCluster[2].size(); i++) {
   //   ht3->Fill((allEnBGOBackCluster[2][i])/(1000.0));
   //}


/*
   TCanvas *c = new TCanvas("c", "BGO Back Cluster",800,600);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   ht1->SetTitle("BGO_Back_Cluster");
   ht1->GetXaxis()->SetTitle("MeV");
   ht1->GetYaxis()->SetRangeUser(1e0,1e4);
   ht1->SetLineColor(kBlack);
   ht1->SetLineWidth(1);
   ht1->SetFillColorAlpha(kTeal-9,1);
   ht1->Draw();
   hv4a->SetLineColor(kBlack);
   hv4a->SetLineWidth(1);
   hv4a->SetFillColorAlpha(kOrange+1,0.5);
   hv4a->Draw("SAME");
   //ht2->SetLineColor(kBlack);
   //ht2->SetLineWidth(1);
   //ht2->SetFillColorAlpha(kPink+1,1);
   //ht2->Draw("SAME");
   //ht1->SetLineColor(kBlack);
   //ht1->SetLineWidth(1);
   //ht1->SetFillColorAlpha(kYellow-7,1);
   //ht1->Draw("SAME");

   auto legend = new TLegend(0.71,0.71,0.87,0.87);
   //legend->AddEntry(ht3, TString::Format("t=[%d, %d] ns", timemin[2],timemax[2]),"f");
   //legend->AddEntry(ht2, TString::Format("t=[%d, %d] ns", timemin[1],timemax[1]),"f");
   legend->AddEntry(ht1, TString::Format("t=[%d, %d] ns", timemin[0], timemax[0]),"f");
   legend->AddEntry(hv4a,"Veto_4_A","f");
   legend->Draw();

   c->SaveAs("BGOCluster_v4a.pdf");
   //c->SaveAs("BackCluster_times.pdf");
*/

/* 

   TCanvas *c = new TCanvas("c", "BGO Back E",800,600);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   h3->SetTitle("BGO_Back_Cluster "+TString::Format("t=[%d, %d] ns",timemin,timemax));
   h3->GetXaxis()->SetTitle("MeV");
   h3->SetLineColor(kBlack);
   h3->SetLineWidth(3);
   h3->Draw();
   //hbgoa->SetFillColorAlpha(kRed-7, 0.9);
   //hbgoa->SetLineColorAlpha(kRed, 0.464);
   //hbgoa->SetLineWidth(2);
   //hbgoa->Draw("SAME");
   //hbgob->SetFillColorAlpha(kGreen-6,0.7);
   //hbgob->SetLineColor(kGreen-2);
   //hbgob->SetLineWidth(2);
   //hbgob->Draw("SAME");
   //hbgoc->SetFillColorAlpha(kOrange-4, 0.5);
   //hbgoc->SetLineColor(kOrange);
   //hbgoc->SetLineWidth(2);
   //hbgoc->Draw("SAME");
   //hbgoe->SetFillColorAlpha(kBlue,0.3);
   //hbgoe->SetLineColor(kBlue-2);
   //hbgoe->SetLineWidth(2);
   //hbgoe->Draw("SAME");   

   auto legend = new TLegend(0.71,0.71,0.87,0.87);
   legend->AddEntry(h3, "Cluster","f");
   legend->AddEntry(hbgoa, "Back_A","f");
   legend->AddEntry(hbgob, "Back_B","f");
   legend->AddEntry(hbgoc,"Back_C","f");
   legend->AddEntry(hbgoe,"Back_E","f");
   legend->Draw();
*/
   //c->SaveAs("BackCluster_100_400ns.pdf");

				

} 
 
 int main() {
   VetoEff();
   return 0;
}  
