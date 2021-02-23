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

void DetEff(){

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

   std::string runnumber = "run373/373";
  

   std::vector<int> timemin;
   std::vector<int> timemax;

   timemin.push_back(-200);
   timemax.push_back(200);

   // Names of the files
   // Mu-Entrance
   std::string fileMuEntrance = runnumber+"_muentrance_prep.txt";
   // Electron Vetos
   std::string fileVeto1 = runnumber+"_Veto1_prep.txt";
   std::string fileVeto2 = runnumber+"_Veto2_prep.txt";
   std::string fileVeto3A = runnumber+"_Veto3_A_prep.txt";
   std::string fileVeto3B = runnumber+"_Veto3_B_prep.txt";
   std::string fileVeto4A = runnumber+"_Veto4_A_prep.txt";
   std::string fileVeto4B = runnumber+"_Veto4_B_prep.txt";
   // Front BGOs
   std::string fileBGOFrontA = runnumber+"_BGO_Front_A_prep.txt";
   std::string fileBGOFrontB = runnumber+"_BGO_Front_B_prep.txt";
   std::string fileBGOFrontC = runnumber+"_BGO_Front_C_prep.txt";
   std::string fileBGOFrontD = runnumber+"_BGO_Front_D_prep.txt";
   std::string fileBGOFrontE = runnumber+"_BGO_Front_E_prep.txt";
   std::string fileBGOFrontF = runnumber+"_BGO_Front_F_prep.txt";
   std::string fileBGOFrontG = runnumber+"_BGO_Front_G_prep.txt";
   std::string fileBGOFrontH = runnumber+"_BGO_Front_H_prep.txt"; 
   // Back BGOs
   std::string fileBGOBackA = runnumber+"_BGO_Back_A_prep.txt";
   std::string fileBGOBackB = runnumber+"_BGO_Back_B_prep.txt";
   std::string fileBGOBackC = runnumber+"_BGO_Back_C_prep.txt";
   std::string fileBGOBackD = runnumber+"_BGO_Back_D_prep.txt";
   std::string fileBGOBackE = runnumber+"_BGO_Back_E_prep.txt";
   std::string fileBGOBackF = runnumber+"_BGO_Back_F_prep.txt";
   std::string fileBGOBackG = runnumber+"_BGO_Back_G_prep.txt";
   std::string fileBGOBackH = runnumber+"_BGO_Back_H_prep.txt";
   std::string fileBGOBackI = runnumber+"_BGO_Back_I_prep.txt";
   std::string fileBGOBackJ = runnumber+"_BGO_Back_J_prep.txt";
   

   // Vectors with detector names
   std::vector<std::string> BBGOfiles;
   std::vector<std::string> FBGOfiles;
   std::vector<std::string> Vetofiles;

   // Electron Vetos
   Vetofiles.push_back(fileVeto1);
   Vetofiles.push_back(fileVeto2);
   Vetofiles.push_back(fileVeto3A);
   Vetofiles.push_back(fileVeto3B);
   Vetofiles.push_back(fileVeto4A);
   Vetofiles.push_back(fileVeto4B);
   // Front BGOs
   FBGOfiles.push_back(fileBGOFrontA);
   FBGOfiles.push_back(fileBGOFrontB);
   FBGOfiles.push_back(fileBGOFrontC);
   FBGOfiles.push_back(fileBGOFrontD);
   FBGOfiles.push_back(fileBGOFrontE);
   FBGOfiles.push_back(fileBGOFrontF);
   FBGOfiles.push_back(fileBGOFrontG);
   FBGOfiles.push_back(fileBGOFrontH);
   // Back BGOs
   BBGOfiles.push_back(fileBGOBackA);
   BBGOfiles.push_back(fileBGOBackB);
   BBGOfiles.push_back(fileBGOBackC);
   BBGOfiles.push_back(fileBGOBackD);
   BBGOfiles.push_back(fileBGOBackE);
   BBGOfiles.push_back(fileBGOBackF);
   BBGOfiles.push_back(fileBGOBackG);
   BBGOfiles.push_back(fileBGOBackH);
   BBGOfiles.push_back(fileBGOBackI);
   BBGOfiles.push_back(fileBGOBackJ);



   /*********************************/
   /*           Analysis            */
   /*********************************/


   // Mu-Entrance
   std::vector< std::vector< double > > allEvIDMu;
   std::vector< std::vector< double > > allEdepMu;
   std::vector< std::vector< double > > allTimeMu;
   // Electron vetos
   std::vector< std::vector< double > > allEvIDVeto1;
   std::vector< std::vector< double > > allEdepVeto1;
   std::vector< std::vector< double > > allTimeVeto1;
   std::vector< std::vector< double > > allEvIDVeto2;
   std::vector< std::vector< double > > allEdepVeto2;
   std::vector< std::vector< double > > allTimeVeto2;
   std::vector< std::vector< double > > allEvIDVeto3A;
   std::vector< std::vector< double > > allEdepVeto3A;
   std::vector< std::vector< double > > allTimeVeto3A;
   std::vector< std::vector< double > > allEvIDVeto3B;
   std::vector< std::vector< double > > allEdepVeto3B;
   std::vector< std::vector< double > > allTimeVeto3B;
   std::vector< std::vector< double > > allEvIDVeto4A;
   std::vector< std::vector< double > > allEdepVeto4A;
   std::vector< std::vector< double > > allTimeVeto4A;
   std::vector< std::vector< double > > allEvIDVeto4B;
   std::vector< std::vector< double > > allEdepVeto4B;
   std::vector< std::vector< double > > allTimeVeto4B;
   // Front BGOs
   std::vector< std::vector< double > > allEvIDFBGOA;
   std::vector< std::vector< double > > allEdepFBGOA;
   std::vector< std::vector< double > > allTimeFBGOA;
   std::vector< std::vector< double > > allEvIDFBGOB;
   std::vector< std::vector< double > > allEdepFBGOB;
   std::vector< std::vector< double > > allTimeFBGOB;
   std::vector< std::vector< double > > allEvIDFBGOC;
   std::vector< std::vector< double > > allEdepFBGOC;
   std::vector< std::vector< double > > allTimeFBGOC;
   std::vector< std::vector< double > > allEvIDFBGOD;
   std::vector< std::vector< double > > allEdepFBGOD;
   std::vector< std::vector< double > > allTimeFBGOD;
   std::vector< std::vector< double > > allEvIDFBGOE;
   std::vector< std::vector< double > > allEdepFBGOE;
   std::vector< std::vector< double > > allTimeFBGOE;
   std::vector< std::vector< double > > allEvIDFBGOF;
   std::vector< std::vector< double > > allEdepFBGOF;
   std::vector< std::vector< double > > allTimeFBGOF;
   std::vector< std::vector< double > > allEvIDFBGOG;
   std::vector< std::vector< double > > allEdepFBGOG;
   std::vector< std::vector< double > > allTimeFBGOG;
   std::vector< std::vector< double > > allEvIDFBGOH;
   std::vector< std::vector< double > > allEdepFBGOH;
   std::vector< std::vector< double > > allTimeFBGOH;
   // Back BGOs
   std::vector< std::vector< double > > allEvIDBBGOA;
   std::vector< std::vector< double > > allEdepBBGOA;
   std::vector< std::vector< double > > allTimeBBGOA;
   std::vector< std::vector< double > > allEvIDBBGOB;
   std::vector< std::vector< double > > allEdepBBGOB;
   std::vector< std::vector< double > > allTimeBBGOB;
   std::vector< std::vector< double > > allEvIDBBGOC;
   std::vector< std::vector< double > > allEdepBBGOC;
   std::vector< std::vector< double > > allTimeBBGOC;
   std::vector< std::vector< double > > allEvIDBBGOD;
   std::vector< std::vector< double > > allEdepBBGOD;
   std::vector< std::vector< double > > allTimeBBGOD;
   std::vector< std::vector< double > > allEvIDBBGOE;
   std::vector< std::vector< double > > allEdepBBGOE;
   std::vector< std::vector< double > > allTimeBBGOE;
   std::vector< std::vector< double > > allEvIDBBGOF;
   std::vector< std::vector< double > > allEdepBBGOF;
   std::vector< std::vector< double > > allTimeBBGOF;
   std::vector< std::vector< double > > allEvIDBBGOG;
   std::vector< std::vector< double > > allEdepBBGOG;
   std::vector< std::vector< double > > allTimeBBGOG;
   std::vector< std::vector< double > > allEvIDBBGOH;
   std::vector< std::vector< double > > allEdepBBGOH;
   std::vector< std::vector< double > > allTimeBBGOH;
   std::vector< std::vector< double > > allEvIDBBGOI;
   std::vector< std::vector< double > > allEdepBBGOI;
   std::vector< std::vector< double > > allTimeBBGOI;
   std::vector< std::vector< double > > allEvIDBBGOJ;
   std::vector< std::vector< double > > allEdepBBGOJ;
   std::vector< std::vector< double > > allTimeBBGOJ;
		   
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
  

   // Mu-Entrance
   std::ifstream fMu(fileMuEntrance);
   std::vector<double> vEvIDMu;
   std::vector<double> vEdepMu;
   std::vector<double> vTimeMu;
   while (!fMu.eof()) {  
      double EvIDMu, InstMu, EdepMu, TimeMu;
      fMu >> EvIDMu >> InstMu >> EdepMu >> TimeMu;
      vEvIDMu.push_back(EvIDMu); 
      vEdepMu.push_back(EdepMu);  
      vTimeMu.push_back(TimeMu);
   }
   vEvIDMu.pop_back();
   vEdepMu.pop_back();
   vTimeMu.pop_back();
   fMu.close();



   // Veto 1
   std::ifstream fVeto1(Vetofiles[0]);
   std::vector<double> vEvIDV1;
   std::vector<double> vEdepV1;
   std::vector<double> vTimeV1;
   while (!fVeto1.eof()) {
      double EvIDV1, InstV1, EdepV1, TimeV1;
      fVeto1 >> EvIDV1 >> InstV1 >> EdepV1 >> TimeV1;
      vEvIDV1.push_back(EvIDV1);
      vEdepV1.push_back(EdepV1);
      vTimeV1.push_back(TimeV1);
   }
   vEvIDV1.pop_back();
   vEdepV1.pop_back();
   vTimeV1.pop_back();
   fVeto1.close();



   // Veto 2
   std::ifstream fVeto2(Vetofiles[1]);
   std::vector<double> vEvIDV2;
   std::vector<double> vEdepV2;
   std::vector<double> vTimeV2;
   while (!fVeto2.eof()) {
      double EvIDV2, InstV2, EdepV2, TimeV2;
      fVeto2 >> EvIDV2 >> InstV2 >> EdepV2 >> TimeV2;
      vEvIDV2.push_back(EvIDV2);
      vEdepV2.push_back(EdepV2);
      vTimeV2.push_back(TimeV2);
   }
   vEvIDV2.pop_back();
   vEdepV2.pop_back();
   vTimeV2.pop_back();
   fVeto2.close();



   // Veto3_A
   std::ifstream fVeto3A(Vetofiles[2]);
   std::vector<double> vEvIDV3A;
   std::vector<double> vEdepV3A;
   std::vector<double> vTimeV3A;
   while (!fVeto3A.eof()) {  
      double EvIDV3A, InstV3A, EdepV3A, TimeV3A;
      fVeto3A >> EvIDV3A >> InstV3A >> EdepV3A >> TimeV3A;
      vEvIDV3A.push_back(EvIDV3A);
      vEdepV3A.push_back(EdepV3A);
      vTimeV3A.push_back(TimeV3A);
   }
   vEvIDV3A.pop_back();
   vEdepV3A.pop_back();
   vTimeV3A.pop_back();
   fVeto3A.close(); 



   // Veto3_B
   std::ifstream fVeto3B(Vetofiles[3]);
   std::vector<double> vEvIDV3B;
   std::vector<double> vEdepV3B;
   std::vector<double> vTimeV3B;
   while (!fVeto3B.eof()) {
      double EvIDV3B, InstV3B, EdepV3B, TimeV3B;
      fVeto3B >> EvIDV3B >> InstV3B >> EdepV3B >> TimeV3B;
      vEvIDV3B.push_back(EvIDV3B);
      vEdepV3B.push_back(EdepV3B);
      vTimeV3B.push_back(TimeV3B);
   }
   vEvIDV3B.pop_back();
   vEdepV3B.pop_back();
   vTimeV3B.pop_back();
   fVeto3B.close();



   // Veto4_A
   std::ifstream fVeto4A(Vetofiles[4]);
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



   // Veto4_B
   std::ifstream fVeto4B(Vetofiles[5]); 
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



   // BGO_Back_A
   std::ifstream fBGOBackA(BBGOfiles[0]);
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


   // Mu-Entrance
   std::vector<double> vTimeTrig;
   std::vector<double> vEdepTrig;
   std::vector<double> vEvIDTrig;
   int EvIDMu;
   int tcounter = 0;
   for (int s=0; s<vEvIDMu.size(); s++) {
      if (vTimeMu[s] == 0) {
         vEvIDTrig.push_back(vEvIDMu[s]);
         vEdepTrig.push_back(vEdepMu[s]);
         vTimeTrig.push_back(vTimeMu[s]);
      } else {
         tcounter++;
      }
   }

   std::cout << "original = " << vEvIDMu.size() <<", counter = " << tcounter << " + new = " << vEvIDTrig.size() << " = " << tcounter+vEvIDTrig.size() << std::endl;

   std::cout << " last = " << vEdepTrig[vEvIDTrig.size()-1] << ", second last = " << vEdepTrig[vEvIDTrig.size()-2] << std::endl;

/*
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
    */     /*if (vEkeVBGOBackA[s] <= 1000) {
            vTmBGOBackA2.push_back(vTimeBGOBackA[s]);
         } else if ((vEkeVBGOBackA[s] >=20000) && (vEkeVBGOBackA[s] < 100000)) {
            vTmBGOBackA3.push_back(vTimeBGOBackA[s]);
         } else if ((vEkeVBGOBackA[s] > 1000) && (vEkeVBGOBackA[s] <20000)) {
            vTmBGOBackA4.push_back(vTimeBGOBackA[s]);
         }*/
/*      }
   }*/
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

/*
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
   std::vector<double> EffVeto4A;
   std::vector<double> EffVeto4A2;
   std::vector<double> EffVeto4A3;
   std::vector<double> EffVeto4B;
   std::vector<double> EffVeto4B2;
   std::vector<double> EffVeto4B3;

   std::vector<double> vMatchedEnergyV4A;
   std::vector<double> vMatchedEnergyV4A2;
   std::vector<double> vMatchedEnergyV4A3;
   std::vector<double> vMatchedEnergyV4B;
   std::vector<double> vMatchedEnergyV4B2;
   std::vector<double> vMatchedEnergyV4B3;
   
   
   //std::vector<double> vBGOMatchedV4A;
   //std::vector<double> vBGOMatchedV4B;
   

   // AND and OR loop
   std::vector<double>  Effand;
   std::vector<double>  Effor;

   std::vector<double> EffVeto;
   std::vector<double> EffVeto2;
   std::vector<double> EffVeto3;
   std::vector<double> EffVetoerr;
   std::vector<double> EffVeto2err;
   std::vector<double> EffVeto3err;

   for (int m=1; m<Ethr.size(); m++) {
      double MatchCounterV4A=0;
      double TotalCounterV4A=0;
      double MatchCounterV4A2=0;
      double MatchCounterV4A3=0;
      double TotalCounterV4B=0;
      double MatchCounterV4B=0;
      double MatchCounterV4B2=0;
      double MatchCounterV4B3=0;

      double MatchEnCount=0;
      double MatchEnCount2=0;
      double MatchEnCount3=0;
      double TotalCount=0;

      double Efferr;

      std::vector<double> vBGOMatchedV4A;
      std::vector<double> vBGOMatchedV4B;

      for (int q=0; q<Eveto.size(); q++) {
         MatchEnCount = 0;
         MatchEnCount2 = 0;
         MatchEnCount3 = 0;
         TotalCount = 0;
         std::cout << " q = " << q <<std::endl;
         for (int n=0; n<vIDBGOBackA.size(); n++) {
            int GoodCount = 0;
            for (int k=0; k<vEvIDV4A.size(); k++) {
               if (vEvIDV4A[k] == vIDBGOBackA[n]) {
                  if (vInstV4A[k] == 0) {
                     if (vEdepV4A[k] >= Eveto[q]) {
                        if ((vTimeV4A[k] >= (vTmBGOBackA[n]-250)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+65))) {
                           if ((vTimeV4A[k] >= (vTmBGOBackA[n]-60)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+30))) {
                              if ((vTimeV4A[k] >= (vTmBGOBackA[n]-30)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+30))) {
                                 MatchEnCount3++;
                              }
                              MatchEnCount2++;
                           }
                           MatchEnCount++;
                        }
                     }
                  } else {
                     GoodCount = 1;
                  }
               }
            }
            if (GoodCount == 0) {
               TotalCount++;
            }
         }
         EffVeto.push_back(MatchEnCount/TotalCount);
         //Efferr = (sqrt((1.0/MatchEnCount)+(1.0/TotalCount)))*(MatchEnCount/TotalCount);
         //Efferr = (pow(((sqrt(MatchEnCount))/TotalCount),2));
         //Efferr = (pow((MatchEnCount*(sqrt(TotalCount))/TotalCount/TotalCount),2));
         Efferr = sqrt((pow(((sqrt(MatchEnCount))/TotalCount),2)) + (pow((MatchEnCount*(sqrt(TotalCount))/TotalCount/TotalCount),2)));
         //EffVetoerr.push_back((sqrt((1.0/MatchEnCount)+(1.0/TotalCount)))*(MatchEnCount/TotalCount));
         EffVetoerr.push_back(Efferr);
         EffVeto2.push_back(MatchEnCount2/TotalCount);
         EffVeto2err.push_back((sqrt((1.0/MatchEnCount2)+(1.0/TotalCount)))*(MatchEnCount2/TotalCount));
         EffVeto3.push_back(MatchEnCount3/TotalCount);
         EffVeto3err.push_back((sqrt((1.0/MatchEnCount3)+(1.0/TotalCount)))*(MatchEnCount3/TotalCount));
         std::cout << "EffVeto = " << MatchEnCount/TotalCount << ", eff error = " << Efferr << ", Total = " << TotalCount << ", Match = " << MatchEnCount << std::endl;
      }
        

      for (int n=0; n<vIDBGOBackA.size(); n++) {
         //std::cout << "Ethr = " << Ethr[m] << " BGOEn = " << allEnBGOBackCluster[0][n] <<std::endl;
         if ((vEnBGOBackA[n] >= Ethr[m-1]) && (vEnBGOBackA[n] < Ethr[m])) {

            int UnmatchedV4A = 0;
            int GoodEventV4A = 0;
            for (int k=0; k<vEvIDV4A.size(); k++) {
               if (vEvIDV4A[k] == vIDBGOBackA[n]) {
                  if (vInstV4A[k] == 0) {
                     if ((vTimeV4A[k] >= (vTmBGOBackA[n]-250)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+65))) {
                        if ((vTimeV4A[k] >= (vTmBGOBackA[n]-200)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+35))) {
                           if ((vTimeV4A[k] >= (vTmBGOBackA[n]-150)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+35))) {
                              MatchCounterV4A++;
                              vMatchedEnergyV4A.push_back(vEdepV4A[k]);
                           }
                           MatchCounterV4A2++;
                           vMatchedEnergyV4A2.push_back(vEdepV4A[k]);
                        }
                        MatchCounterV4A3++;
                        vMatchedEnergyV4A3.push_back(vEdepV4A[k]);
                        UnmatchedV4A = 1;  
                     }
                  } else {
                     GoodEventV4A = 1;
                  }
               }
            }
            //if (m == 0) {
            if (GoodEventV4A == 0) {
               if (UnmatchedV4A == 0) {
                  vBGOMatchedV4A.push_back(0);
               } else {
                  vBGOMatchedV4A.push_back(1);
               }
               TotalCounterV4A++;
            } else {
               vBGOMatchedV4A.push_back(-1);
            }
            //}            
            //if (GoodEventV4A == 0) {
               //TotalCounterV4A++;
            //}
   
         
            int UnmatchedV4B = 0;
            int GoodEventV4B = 0;
            for (int l=0; l<vEvIDV4B.size(); l++) {
               if (vEvIDV4B[l] == vIDBGOBackA[n]) {
                  if (vInstV4B[l] == 0) {
                     if ((vTimeV4B[l] >= (vTmBGOBackA[n]-250)) && (vTimeV4B[l] <= (vTmBGOBackA[n]+65))) {
                        if ((vTimeV4B[l] >= (vTmBGOBackA[n]-200)) && (vTimeV4B[l] <= (vTmBGOBackA[n]+35))) {
                           if ((vTimeV4B[l] >= (vTmBGOBackA[n]-150)) && (vTimeV4B[l] <= (vTmBGOBackA[n]+35))) {
                              MatchCounterV4B++;
                              vMatchedEnergyV4B.push_back(vEdepV4B[l]);
                           }  
                           MatchCounterV4B2++;
                           vMatchedEnergyV4B2.push_back(vEdepV4B[l]);
                        }  
                        MatchCounterV4B3++;
                        vMatchedEnergyV4B3.push_back(vEdepV4B[l]);
                        UnmatchedV4B = 1;
                     }  
                  } else {
                     GoodEventV4B = 1;
                  }
               }  
            }
            //if (m == 0) {
            if (GoodEventV4B == 0) {
               TotalCounterV4B++;
               if (UnmatchedV4B == 0) {
                  vBGOMatchedV4B.push_back(0);
               } else {
                  vBGOMatchedV4B.push_back(1);
               }
            } else {
               vBGOMatchedV4B.push_back(-1);
            }
            //}  
            //if (GoodEventV4B == 0) {
               //TotalCounterV4B++;
            //}
         }

      }
      std::cout << "Ethr = " << Ethr[m] << ", V4A :: Eff1 = " << MatchCounterV4A/TotalCounterV4A << ", Eff2 = " << MatchCounterV4A2/TotalCounterV4A << ", Eff3 = " << MatchCounterV4A3/TotalCounterV4A << std::endl;
      EffVeto4A.push_back(MatchCounterV4A/TotalCounterV4A);
      EffVeto4A2.push_back(MatchCounterV4A2/TotalCounterV4A);
      EffVeto4A3.push_back(MatchCounterV4A3/TotalCounterV4A);

      std::cout << "Ethr = " << Ethr[m] << ", V4B :: Eff1 = " << MatchCounterV4B/TotalCounterV4B << ", Eff2 = " << MatchCounterV4B2/TotalCounterV4B << ", Eff3 = " << MatchCounterV4B3/TotalCounterV4B << std::endl;
      EffVeto4B.push_back(MatchCounterV4B/TotalCounterV4B);
      EffVeto4B2.push_back(MatchCounterV4B2/TotalCounterV4B);
      EffVeto4B3.push_back(MatchCounterV4B3/TotalCounterV4B);
      std::cout << "match counter v4a = " << MatchCounterV4A3 << ", match counter v4b = " << MatchCounterV4B3 << ", total counter v4a = " << TotalCounterV4A << ", total counter v4b = " << TotalCounterV4B << std::endl;               


      std::cout << "\033[1;36m ethr = " << Ethr[m] << ", v4a size = " << vBGOMatchedV4A.size() << ", v4b size = " << vBGOMatchedV4B.size() << "\033[0m" << std::endl;

      double ANDCounter=0;
      double ORCounter=0;
      double TotalCounter=0;
      for (int j=0; j<vBGOMatchedV4A.size(); j++) {
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
      }
      Effand.push_back(ANDCounter/TotalCounter);
      Effor.push_back(ORCounter/TotalCounter);    


   }      
*/
/*
   // AND and OR loop
   std::vector<double>  Effand;
   std::vector<double>  Effor;

   std::cout << "matched v4b = " << vBGOMatchedV4B.size() << ", matched v4a = " << vBGOMatchedV4A.size() << ", enBGO = " << vEnBGOBackA.size() << std::endl;


   std::vector<double> EnBGO;
   EnBGO.push_back(0.0);
   for (int i=1; i<nbins; i++) EnBGO.push_back(EnBGO[i-1]+Eint);

   for (int m=1; m<EnBGO.size(); m++) {
      double ANDCounter=0;
      double ORCounter=0;
      double TotalCounter=0;
 
      for (int i=0; i<vEnBGOBackA.size(); i++) {
         if ((vEnBGOBackA[i] >= EnBGO[m-1]) && (vEnBGOBackA[i] < EnBGO[m])) {
            if ((vBGOMatchedV4A[i] == 1) && (vBGOMatchedV4B[i] == 1)) {
               ANDCounter++;
               ORCounter++;
               TotalCounter++;
            } else if ((vBGOMatchedV4A[i] == 1) || (vBGOMatchedV4B[i] == 1)) {
               ORCounter++;
               TotalCounter++;
            } else if ((vBGOMatchedV4A[i] + vBGOMatchedV4B[i]) == 0) {
               TotalCounter++;
            }
         }
      }
      std::cout << "E = " << EnBGO[m] << " AND = " << ANDCounter << ", OR = " << ORCounter << ", total = " << TotalCounter << std::endl;
      Effand.push_back(ANDCounter/TotalCounter);
      Effor.push_back(ORCounter/TotalCounter);
   }           
*/


 
   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m---------------------- Plotting --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


/*
   const int nticks = 7;
   float EffVetoarr[nticks] = {};
   float EffVeto2arr[nticks] = {};
   float EffVeto3arr[nticks] = {};
   float EffVetoerrx[nticks] = {};
   float EffVetoerry[nticks] = {};
   float EffVeto2errx[nticks] = {};
   float EffVeto2erry[nticks] = {};
   float EffVeto3errx[nticks] = {};
   float EffVeto3erry[nticks] = {};
   float Evetoarr[nticks] = {};

   for (int i=0; i<nticks; i++) {
      EffVetoarr[i] = EffVeto[i];
      EffVeto2arr[i] = EffVeto2[i];
      EffVeto3arr[i] = EffVeto3[i];
      EffVetoerrx[i] = 0.0;
      EffVetoerry[i] = EffVetoerr[i];
      EffVeto2errx[i] = 0.0;
      EffVeto2erry[i] = EffVeto2err[i];
      EffVeto3errx[i] = 0.0;
      EffVeto3erry[i] = EffVeto3err[i];
      Evetoarr[i] = Eveto[i];
   }

   TCanvas *fvcut = new TCanvas("fvcut","E_{THR}",800,600);
   gPad->SetGrid(1,1);
   TGraphErrors *grv0 = new TGraphErrors(nticks,Evetoarr,EffVetoarr,EffVetoerrx,EffVetoerry);
   grv0->SetTitle("Efficiency of Veto_4_A");
   grv0->GetXaxis()->SetTitle("E_{Veto} [adc]");
   grv0->GetYaxis()->SetTitle("Eff");
   grv0->GetYaxis()->SetTitleOffset(1.9);
   grv0->GetYaxis()->SetRangeUser(0.78,1.03);
   //grv0->SetLineColor(kGray+3);
   grv0->SetLineWidth(3);
   grv0->SetLineColor(kViolet-5);
   grv0->SetMarkerColor(kViolet-5);
   grv0->SetMarkerSize(1.5);
   grv0->SetMarkerStyle(21);
   grv0->Draw("ALP");
   TGraphErrors *grv1 = new TGraphErrors(nticks,Evetoarr,EffVeto2arr,EffVeto2errx,EffVeto2erry);
   grv1->SetLineWidth(3);
   grv1->SetLineColor(kTeal-5);
   grv1->SetLineStyle(kDashed);
   grv1->SetMarkerColor(kTeal-5);
   grv1->SetMarkerSize(1.5);
   grv1->SetMarkerStyle(22);
   grv1->Draw("LP");
   TGraphErrors *grv2 = new TGraphErrors(nticks,Evetoarr,EffVeto3arr,EffVeto3errx,EffVeto3erry);
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
  // fvcut->SaveAs("EffV4_A_vcuttime_err.pdf");
*/
				

} 
 
 int main() {
   DetEff();
   return 0;
}  
