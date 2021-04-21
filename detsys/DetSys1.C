///////////////////////////////////////////////
//                                           //
//                 DetSys1.C                 //
//                                           //                
//  Plots Efficieny of a veto for different  //
//  energies in the BGO.                     //
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

void DetSys1(){
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

   // Uncomment for Au-target
   //std::string runnumber = "run373/373";
   // Uncomment for PE-target
   std::string runnumber = "run383/383";

   // Time coincidence for the BGOs
   std::vector<int> timemin;
   std::vector<int> timemax;
   // Uncomment for Au-target
   //timemin.push_back(-30);
   //timemax.push_back(30);
   // Uncomment for PE-target
   timemin.push_back(100);
   timemax.push_back(1000);

   // Names of the files
   // Muon Entrance [main trigger]
   std::string fileMu = runnumber+"_muentrance_prep.txt";
   // Electron Vetos
   std::string fileVeto1 = runnumber+"_Veto1_prep.txt";
   std::string fileVeto2 = runnumber+"_Veto2_prep.txt";
   std::string fileVeto3A = runnumber+"_Veto3_A_prep.txt";
   std::string fileVeto3B = runnumber+"_Veto3_B_prep.txt";
   std::string fileVeto4A = runnumber+"_Veto4_A_prep.txt";
   std::string fileVeto4B = runnumber+"_Veto4_B_prep.txt";
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
   // Front BGOs
   std::string fileBGOFrontA = runnumber+"_BGO_Front_A_prep.txt";
   std::string fileBGOFrontB = runnumber+"_BGO_Front_B_prep.txt";
   std::string fileBGOFrontC = runnumber+"_BGO_Front_C_prep.txt";
   std::string fileBGOFrontD = runnumber+"_BGO_Front_D_prep.txt";
   std::string fileBGOFrontE = runnumber+"_BGO_Front_E_prep.txt";
   std::string fileBGOFrontF = runnumber+"_BGO_Front_F_prep.txt";
   std::string fileBGOFrontG = runnumber+"_BGO_Front_G_prep.txt";
   std::string fileBGOFrontH = runnumber+"_BGO_Front_H_prep.txt";

   // Vectors with detector names
   std::vector<std::string> Mufiles;
   std::vector<std::string> Vetofiles;
   std::vector<std::string> BGOfiles;

   // Muon Entrance [main trigger]
   Mufiles.push_back(fileMu);
   // Electron Vetos
   Vetofiles.push_back(fileVeto1);
   Vetofiles.push_back(fileVeto2);
   Vetofiles.push_back(fileVeto3A);
   Vetofiles.push_back(fileVeto3B);
   Vetofiles.push_back(fileVeto4A);
   Vetofiles.push_back(fileVeto4B);  
   // Back BGOs
   BGOfiles.push_back(fileBGOBackA);
   BGOfiles.push_back(fileBGOBackB);
   BGOfiles.push_back(fileBGOBackC);
   BGOfiles.push_back(fileBGOBackD);
   BGOfiles.push_back(fileBGOBackE);
   BGOfiles.push_back(fileBGOBackF);
   BGOfiles.push_back(fileBGOBackG);
   BGOfiles.push_back(fileBGOBackH);
   BGOfiles.push_back(fileBGOBackI);
   BGOfiles.push_back(fileBGOBackJ);
   // Front BGOs
   BGOfiles.push_back(fileBGOFrontA);
   BGOfiles.push_back(fileBGOFrontB);
   BGOfiles.push_back(fileBGOFrontC);
   BGOfiles.push_back(fileBGOFrontD);
   BGOfiles.push_back(fileBGOFrontE);
   BGOfiles.push_back(fileBGOFrontF);
   BGOfiles.push_back(fileBGOFrontG);
   BGOfiles.push_back(fileBGOFrontH);


   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   

   //---------------------------------- Muon Entrance -------------------------------
   // Muon Entrance [trigger]
   std::ifstream fMu(Mufiles[0]);
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


   //--------------------------------- Electron Vetos -------------------------------
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


   //------------------------------------ Back BGOs ---------------------------------
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
      fBGOBackB >> EvIDBGOBackB >> InstBGOBackB >> EdepBGOBackB >> TimeBGOBackB;
      double EkeVBGOBackB;
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
      fBGOBackC >> EvIDBGOBackC >> InstBGOBackC >> EdepBGOBackC >> TimeBGOBackC;
      double EkeVBGOBackC;
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

   // BGO_Back_D
   std::ifstream fBGOBackD(BGOfiles[3]);
   std::vector<double> vEvIDBGOBackD;
   std::vector<double> vEdepBGOBackD;
   std::vector<double> vEkeVBGOBackD;
   std::vector<double> vTimeBGOBackD;
   double kbgobackd = 1.86;
   double bbgobackd = 22.30;
   while (!fBGOBackD.eof()) {
      double EvIDBGOBackD, InstBGOBackD, EdepBGOBackD, TimeBGOBackD;
      fBGOBackD >> EvIDBGOBackD >> InstBGOBackD >> EdepBGOBackD >> TimeBGOBackD;
      double EkeVBGOBackD;
      vEvIDBGOBackD.push_back(EvIDBGOBackD);    
      vEdepBGOBackD.push_back(EdepBGOBackD);    
      vTimeBGOBackD.push_back(TimeBGOBackD);     
      EkeVBGOBackD = EdepBGOBackD*kbgobackd+bbgobackd;
      vEkeVBGOBackD.push_back(EkeVBGOBackD);
   }
   vEvIDBGOBackD.pop_back();
   vEdepBGOBackD.pop_back();
   vTimeBGOBackD.pop_back();
   vEkeVBGOBackD.pop_back();
   fBGOBackD.close();
  
   // BGO_Back_E
   std::ifstream fBGOBackE(BGOfiles[4]);
   std::vector<double> vEvIDBGOBackE;
   std::vector<double> vEdepBGOBackE;
   std::vector<double> vEkeVBGOBackE;
   std::vector<double> vTimeBGOBackE;
   double kbgobacke = 1.88;
   double bbgobacke = 20.78;
   while (!fBGOBackE.eof()) {
      double EvIDBGOBackE, InstBGOBackE, EdepBGOBackE, TimeBGOBackE;
      fBGOBackE >> EvIDBGOBackE >> InstBGOBackE >> EdepBGOBackE >> TimeBGOBackE;
      double EkeVBGOBackE;
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

   // BGO_Back_F
   std::ifstream fBGOBackF(BGOfiles[5]);
   std::vector<double> vEvIDBGOBackF;
   std::vector<double> vEdepBGOBackF;
   std::vector<double> vEkeVBGOBackF;
   std::vector<double> vTimeBGOBackF;
   double kbgobackf = 2.65;
   double bbgobackf = 13.41;
   while (!fBGOBackF.eof()) {
      double EvIDBGOBackF, InstBGOBackF, EdepBGOBackF, TimeBGOBackF;
      fBGOBackF >> EvIDBGOBackF >> InstBGOBackF >> EdepBGOBackF >> TimeBGOBackF;
      double EkeVBGOBackF;
      vEvIDBGOBackF.push_back(EvIDBGOBackF);    
      vEdepBGOBackF.push_back(EdepBGOBackF);    
      vTimeBGOBackF.push_back(TimeBGOBackF);     
      EkeVBGOBackF = EdepBGOBackF*kbgobackf+bbgobackf;
      vEkeVBGOBackF.push_back(EkeVBGOBackF);
   }
   vEvIDBGOBackF.pop_back();
   vEdepBGOBackF.pop_back();
   vTimeBGOBackF.pop_back();
   vEkeVBGOBackF.pop_back();
   fBGOBackF.close();

   // BGO_Back_G
   std::ifstream fBGOBackG(BGOfiles[6]);
   std::vector<double> vEvIDBGOBackG;
   std::vector<double> vEdepBGOBackG;
   std::vector<double> vEkeVBGOBackG;
   std::vector<double> vTimeBGOBackG;
   double kbgobackg = 1.92;
   double bbgobackg = 13.03;
   while (!fBGOBackG.eof()) {
      double EvIDBGOBackG, InstBGOBackG, EdepBGOBackG, TimeBGOBackG;
      fBGOBackG >> EvIDBGOBackG >> InstBGOBackG >> EdepBGOBackG >> TimeBGOBackG;
      double EkeVBGOBackG;
      vEvIDBGOBackG.push_back(EvIDBGOBackG);    
      vEdepBGOBackG.push_back(EdepBGOBackG);    
      vTimeBGOBackG.push_back(TimeBGOBackG);     
      EkeVBGOBackG = EdepBGOBackG*kbgobackg+bbgobackg;
      vEkeVBGOBackG.push_back(EkeVBGOBackG);
   }
   vEvIDBGOBackG.pop_back();
   vEdepBGOBackG.pop_back();
   vTimeBGOBackG.pop_back();
   vEkeVBGOBackG.pop_back();
   fBGOBackG.close();

   // BGO_Back_H
   std::ifstream fBGOBackH(BGOfiles[7]);
   std::vector<double> vEvIDBGOBackH;
   std::vector<double> vEdepBGOBackH;
   std::vector<double> vEkeVBGOBackH;
   std::vector<double> vTimeBGOBackH;
   double kbgobackh = 2.00;
   double bbgobackh = 14.92;
   while (!fBGOBackH.eof()) {
      double EvIDBGOBackH, InstBGOBackH, EdepBGOBackH, TimeBGOBackH;
      fBGOBackH >> EvIDBGOBackH >> InstBGOBackH >> EdepBGOBackH >> TimeBGOBackH;
      double EkeVBGOBackH;
      vEvIDBGOBackH.push_back(EvIDBGOBackH);
      vEdepBGOBackH.push_back(EdepBGOBackH);
      vTimeBGOBackH.push_back(TimeBGOBackH);
      EkeVBGOBackH = EdepBGOBackH*kbgobackh+bbgobackh; 
      vEkeVBGOBackH.push_back(EkeVBGOBackH);
   }
   vEvIDBGOBackH.pop_back();
   vEdepBGOBackH.pop_back();
   vTimeBGOBackH.pop_back();
   vEkeVBGOBackH.pop_back();
   fBGOBackH.close();
   
   // BGO_Back_I
   std::ifstream fBGOBackI(BGOfiles[8]);
   std::vector<double> vEvIDBGOBackI;
   std::vector<double> vEdepBGOBackI;
   std::vector<double> vEkeVBGOBackI;
   std::vector<double> vTimeBGOBackI;
   double kbgobacki = 2.10;
   double bbgobacki = 13.37;
   while (!fBGOBackI.eof()) {
      double EvIDBGOBackI, InstBGOBackI, EdepBGOBackI, TimeBGOBackI;
      fBGOBackI >> EvIDBGOBackI >> InstBGOBackI >> EdepBGOBackI >> TimeBGOBackI;
      double EkeVBGOBackI;
      vEvIDBGOBackI.push_back(EvIDBGOBackI);
      vEdepBGOBackI.push_back(EdepBGOBackI);
      vTimeBGOBackI.push_back(TimeBGOBackI);
      EkeVBGOBackI = EdepBGOBackI*kbgobacki+bbgobacki;
      vEkeVBGOBackI.push_back(EkeVBGOBackI);
   }
   vEvIDBGOBackI.pop_back();
   vEdepBGOBackI.pop_back();
   vTimeBGOBackI.pop_back();
   vEkeVBGOBackI.pop_back();
   fBGOBackI.close();

   // BGO_Back_J
   std::ifstream fBGOBackJ(BGOfiles[9]);
   std::vector<double> vEvIDBGOBackJ;
   std::vector<double> vEdepBGOBackJ;
   std::vector<double> vEkeVBGOBackJ;
   std::vector<double> vTimeBGOBackJ;
   double kbgobackj = 2.52;
   double bbgobackj = 13.16;
   while (!fBGOBackJ.eof()) {
      double EvIDBGOBackJ, InstBGOBackJ, EdepBGOBackJ, TimeBGOBackJ;
      fBGOBackJ >> EvIDBGOBackJ >> InstBGOBackJ >> EdepBGOBackJ >> TimeBGOBackJ;
      double EkeVBGOBackJ;
      vEvIDBGOBackJ.push_back(EvIDBGOBackJ);
      vEdepBGOBackJ.push_back(EdepBGOBackJ);
      vTimeBGOBackJ.push_back(TimeBGOBackJ);
      EkeVBGOBackJ = EdepBGOBackJ*kbgobackj+bbgobackj;
      vEkeVBGOBackJ.push_back(EkeVBGOBackJ);
   }
   vEvIDBGOBackJ.pop_back();
   vEdepBGOBackJ.pop_back();
   vTimeBGOBackJ.pop_back();
   vEkeVBGOBackJ.pop_back();
   fBGOBackJ.close();

   //----------------------------------- Front BGOs ---------------------------------
   // BGO_Front_A
   std::ifstream fBGOFrontA(BGOfiles[10]);
   std::vector<double> vEvIDBGOFrontA;
   std::vector<double> vEdepBGOFrontA;
   std::vector<double> vEkeVBGOFrontA;
   std::vector<double> vTimeBGOFrontA;
   double kbgofronta = 1.90;
   double bbgofronta = 24.51;
   while (!fBGOFrontA.eof()) {
      double EvIDBGOFrontA, InstBGOFrontA, EdepBGOFrontA, TimeBGOFrontA;
      fBGOFrontA >> EvIDBGOFrontA >> InstBGOFrontA >> EdepBGOFrontA >> TimeBGOFrontA;
      double EkeVBGOFrontA;
      vEvIDBGOFrontA.push_back(EvIDBGOFrontA);
      vEdepBGOFrontA.push_back(EdepBGOFrontA);
      vTimeBGOFrontA.push_back(TimeBGOFrontA);
      EkeVBGOFrontA = EdepBGOFrontA*kbgofronta+bbgofronta;
      vEkeVBGOFrontA.push_back(EkeVBGOFrontA);
   }
   vEvIDBGOFrontA.pop_back();
   vEdepBGOFrontA.pop_back();
   vTimeBGOFrontA.pop_back();
   vEkeVBGOFrontA.pop_back();
   fBGOFrontA.close();

   // BGO_Front_B
   std::ifstream fBGOFrontB(BGOfiles[11]);
   std::vector<double> vEvIDBGOFrontB;
   std::vector<double> vEdepBGOFrontB;
   std::vector<double> vEkeVBGOFrontB;
   std::vector<double> vTimeBGOFrontB;
   double kbgofrontb = 1.81;
   double bbgofrontb = 34.33;
   while (!fBGOFrontB.eof()) {
      double EvIDBGOFrontB, InstBGOFrontB, EdepBGOFrontB, TimeBGOFrontB;
      fBGOFrontB >> EvIDBGOFrontB >> InstBGOFrontB >> EdepBGOFrontB >> TimeBGOFrontB;
      double EkeVBGOFrontB;
      vEvIDBGOFrontB.push_back(EvIDBGOFrontB);
      vEdepBGOFrontB.push_back(EdepBGOFrontB);
      vTimeBGOFrontB.push_back(TimeBGOFrontB);
      EkeVBGOFrontB = EdepBGOFrontB*kbgofrontb+bbgofrontb;
      vEkeVBGOFrontB.push_back(EkeVBGOFrontB);
   }
   vEvIDBGOFrontB.pop_back();
   vEdepBGOFrontB.pop_back();
   vTimeBGOFrontB.pop_back();
   vEkeVBGOFrontB.pop_back();
   fBGOFrontB.close();

   // BGO_Front_C
   std::ifstream fBGOFrontC(BGOfiles[12]);
   std::vector<double> vEvIDBGOFrontC;
   std::vector<double> vEdepBGOFrontC;
   std::vector<double> vEkeVBGOFrontC;
   std::vector<double> vTimeBGOFrontC;
   double kbgofrontc = 1.90;
   double bbgofrontc = 32.27;
   while (!fBGOFrontC.eof()) {
      double EvIDBGOFrontC, InstBGOFrontC, EdepBGOFrontC, TimeBGOFrontC;
      fBGOFrontC >> EvIDBGOFrontC >> InstBGOFrontC >> EdepBGOFrontC >> TimeBGOFrontC;
      double EkeVBGOFrontC;
      vEvIDBGOFrontC.push_back(EvIDBGOFrontC);
      vEdepBGOFrontC.push_back(EdepBGOFrontC);
      vTimeBGOFrontC.push_back(TimeBGOFrontC);
      EkeVBGOFrontC = EdepBGOFrontC*kbgofrontc+bbgofrontc;
      vEkeVBGOFrontC.push_back(EkeVBGOFrontC);
   }
   vEvIDBGOFrontC.pop_back();
   vEdepBGOFrontC.pop_back();
   vTimeBGOFrontC.pop_back();
   vEkeVBGOFrontC.pop_back();
   fBGOFrontC.close();

   // BGO_Front_D
   std::ifstream fBGOFrontD(BGOfiles[13]);
   std::vector<double> vEvIDBGOFrontD;
   std::vector<double> vEdepBGOFrontD;
   std::vector<double> vEkeVBGOFrontD;
   std::vector<double> vTimeBGOFrontD;
   double kbgofrontd = 2.00;
   double bbgofrontd = 50.30;
   while (!fBGOFrontD.eof()) {
      double EvIDBGOFrontD, InstBGOFrontD, EdepBGOFrontD, TimeBGOFrontD;
      fBGOFrontD >> EvIDBGOFrontD >> InstBGOFrontD >> EdepBGOFrontD >> TimeBGOFrontD;
      double EkeVBGOFrontD;
      vEvIDBGOFrontD.push_back(EvIDBGOFrontD);
      vEdepBGOFrontD.push_back(EdepBGOFrontD);
      vTimeBGOFrontD.push_back(TimeBGOFrontD);
      EkeVBGOFrontD = EdepBGOFrontD*kbgofrontd+bbgofrontd;
      vEkeVBGOFrontD.push_back(EkeVBGOFrontD);
   }
   vEvIDBGOFrontD.pop_back();
   vEdepBGOFrontD.pop_back();
   vTimeBGOFrontD.pop_back();
   vEkeVBGOFrontD.pop_back();
   fBGOFrontD.close();

   // BGO_Front_E
   std::ifstream fBGOFrontE(BGOfiles[14]);
   std::vector<double> vEvIDBGOFrontE;
   std::vector<double> vEdepBGOFrontE;
   std::vector<double> vEkeVBGOFrontE;
   std::vector<double> vTimeBGOFrontE;
   double kbgofronte = 1.96;
   double bbgofronte = 82.73;
   while (!fBGOFrontE.eof()) {
      double EvIDBGOFrontE, InstBGOFrontE, EdepBGOFrontE, TimeBGOFrontE;
      fBGOFrontE >> EvIDBGOFrontE >> InstBGOFrontE >> EdepBGOFrontE >> TimeBGOFrontE;
      double EkeVBGOFrontE;
      vEvIDBGOFrontE.push_back(EvIDBGOFrontE);
      vEdepBGOFrontE.push_back(EdepBGOFrontE);
      vTimeBGOFrontE.push_back(TimeBGOFrontE);
      EkeVBGOFrontE = EdepBGOFrontE*kbgofronte+bbgofronte;
      vEkeVBGOFrontE.push_back(EkeVBGOFrontE);
   }
   vEvIDBGOFrontE.pop_back();
   vEdepBGOFrontE.pop_back();
   vTimeBGOFrontE.pop_back();
   vEkeVBGOFrontE.pop_back();
   fBGOFrontE.close();  

   // BGO_Front_F
   std::ifstream fBGOFrontF(BGOfiles[15]);
   std::vector<double> vEvIDBGOFrontF;
   std::vector<double> vEdepBGOFrontF;
   std::vector<double> vEkeVBGOFrontF;
   std::vector<double> vTimeBGOFrontF;
   double kbgofrontf = 1.95;
   double bbgofrontf = 33.43;
   while (!fBGOFrontF.eof()) {
      double EvIDBGOFrontF, InstBGOFrontF, EdepBGOFrontF, TimeBGOFrontF;
      fBGOFrontF >> EvIDBGOFrontF >> InstBGOFrontF >> EdepBGOFrontF >> TimeBGOFrontF;
      double EkeVBGOFrontF;
      vEvIDBGOFrontF.push_back(EvIDBGOFrontF);
      vEdepBGOFrontF.push_back(EdepBGOFrontF);
      vTimeBGOFrontF.push_back(TimeBGOFrontF);
      EkeVBGOFrontF = EdepBGOFrontF*kbgofrontf+bbgofrontf;
      vEkeVBGOFrontF.push_back(EkeVBGOFrontF);
   }
   vEvIDBGOFrontF.pop_back();
   vEdepBGOFrontF.pop_back();
   vTimeBGOFrontF.pop_back();
   vEkeVBGOFrontF.pop_back();
   fBGOFrontF.close(); 

   // BGO_Front_G
   std::ifstream fBGOFrontG(BGOfiles[16]);
   std::vector<double> vEvIDBGOFrontG;
   std::vector<double> vEdepBGOFrontG;
   std::vector<double> vEkeVBGOFrontG;
   std::vector<double> vTimeBGOFrontG;
   double kbgofrontg = 1.80;
   double bbgofrontg = 32.41;
   while (!fBGOFrontG.eof()) {
      double EvIDBGOFrontG, InstBGOFrontG, EdepBGOFrontG, TimeBGOFrontG;
      fBGOFrontG >> EvIDBGOFrontG >> InstBGOFrontG >> EdepBGOFrontG >> TimeBGOFrontG;
      double EkeVBGOFrontG;
      vEvIDBGOFrontG.push_back(EvIDBGOFrontG);
      vEdepBGOFrontG.push_back(EdepBGOFrontG);
      vTimeBGOFrontG.push_back(TimeBGOFrontG);
      EkeVBGOFrontG = EdepBGOFrontG*kbgofrontg+bbgofrontg;
      vEkeVBGOFrontG.push_back(EkeVBGOFrontG);
   }
   vEvIDBGOFrontG.pop_back();
   vEdepBGOFrontG.pop_back();
   vTimeBGOFrontG.pop_back();
   vEkeVBGOFrontG.pop_back();
   fBGOFrontG.close(); 

   // BGO_Front_H
   std::ifstream fBGOFrontH(BGOfiles[17]);
   std::vector<double> vEvIDBGOFrontH;
   std::vector<double> vEdepBGOFrontH;
   std::vector<double> vEkeVBGOFrontH;
   std::vector<double> vTimeBGOFrontH;
   double kbgofronth = 1.94;
   double bbgofronth = 27.70;
   while (!fBGOFrontH.eof()) {
      double EvIDBGOFrontH, InstBGOFrontH, EdepBGOFrontH, TimeBGOFrontH;
      fBGOFrontH >> EvIDBGOFrontH >> InstBGOFrontH >> EdepBGOFrontH >> TimeBGOFrontH;
      double EkeVBGOFrontH;
      vEvIDBGOFrontH.push_back(EvIDBGOFrontH);
      vEdepBGOFrontH.push_back(EdepBGOFrontH);
      vTimeBGOFrontH.push_back(TimeBGOFrontH);
      EkeVBGOFrontH = EdepBGOFrontH*kbgofronth+bbgofronth;
      vEkeVBGOFrontH.push_back(EkeVBGOFrontH);
   }
   vEvIDBGOFrontH.pop_back();
   vEdepBGOFrontH.pop_back();
   vTimeBGOFrontH.pop_back();
   vEkeVBGOFrontH.pop_back();
   fBGOFrontH.close(); 


   std::cout << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m--------------------- Reading II -------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;


   //---------------------------------- Muon Entrance -------------------------------
   // Muon Entrance [main trigger]
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
      }
   }


   //------------------------------------ Back BGOs ---------------------------------
   // BGO_Back_A
   std::vector<double> vEnBGOBackA;
   std::vector<double> vIDBGOBackA;
   std::vector<double> vTmBGOBackA;
   for (int s=0; s<vTimeBGOBackA.size(); s++) {
      if (vEkeVBGOBackA[s] < 100000) {
         vIDBGOBackA.push_back(vEvIDBGOBackA[s]);
         vEnBGOBackA.push_back(vEkeVBGOBackA[s]);
         vTmBGOBackA.push_back(vTimeBGOBackA[s]);
      }
   }

   // BGO_Back_B
   std::vector<double> vEnBGOBackB;
   std::vector<double> vIDBGOBackB;
   std::vector<double> vTmBGOBackB;
   for (int s=0; s<vTimeBGOBackB.size(); s++) {
      if (vEkeVBGOBackB[s] < 100000) {
         vIDBGOBackB.push_back(vEvIDBGOBackB[s]);
         vEnBGOBackB.push_back(vEkeVBGOBackB[s]);
         vTmBGOBackB.push_back(vTimeBGOBackB[s]);
      }
   }

   // BGO_Back_C
   std::vector<double> vEnBGOBackC;
   std::vector<double> vIDBGOBackC;
   std::vector<double> vTmBGOBackC;
   for (int s=0; s<vTimeBGOBackC.size(); s++) {
      if (vEkeVBGOBackC[s] < 100000) {
         vIDBGOBackC.push_back(vEvIDBGOBackC[s]);
         vEnBGOBackC.push_back(vEkeVBGOBackC[s]);
         vTmBGOBackC.push_back(vTimeBGOBackC[s]);
      }
   }

   // BGO_Back_D
   std::vector<double> vEnBGOBackD;
   std::vector<double> vIDBGOBackD;
   std::vector<double> vTmBGOBackD;
   for (int s=0; s<vTimeBGOBackD.size(); s++) {
      if (vEkeVBGOBackD[s] < 100000) {
         vIDBGOBackD.push_back(vEvIDBGOBackD[s]);
         vEnBGOBackD.push_back(vEkeVBGOBackD[s]);
         vTmBGOBackD.push_back(vTimeBGOBackD[s]);
      }
   }

   // BGO_Back_E
   std::vector<double> vEnBGOBackE;
   std::vector<double> vIDBGOBackE;
   std::vector<double> vTmBGOBackE;
   for (int s=0; s<vTimeBGOBackE.size(); s++) {
      if (vEkeVBGOBackE[s] < 100000) {
         vIDBGOBackE.push_back(vEvIDBGOBackE[s]);
         vEnBGOBackE.push_back(vEkeVBGOBackE[s]);
         vTmBGOBackE.push_back(vTimeBGOBackE[s]);
      }
   }

   // BGO_Back_F
   std::vector<double> vEnBGOBackF;
   std::vector<double> vIDBGOBackF;
   std::vector<double> vTmBGOBackF;
   for (int s=0; s<vTimeBGOBackF.size(); s++) {
      if (vEkeVBGOBackF[s] < 100000) {
         vIDBGOBackF.push_back(vEvIDBGOBackF[s]);
         vEnBGOBackF.push_back(vEkeVBGOBackF[s]);
         vTmBGOBackF.push_back(vTimeBGOBackF[s]);
      }
   }

   // BGO_Back_G
   std::vector<double> vEnBGOBackG;
   std::vector<double> vIDBGOBackG;
   std::vector<double> vTmBGOBackG;
   for (int s=0; s<vTimeBGOBackG.size(); s++) {
      if (vEkeVBGOBackG[s] < 100000) {
         vIDBGOBackG.push_back(vEvIDBGOBackG[s]);
         vEnBGOBackG.push_back(vEkeVBGOBackG[s]);
         vTmBGOBackG.push_back(vTimeBGOBackG[s]);
      }
   }

   // BGO_Back_H
   std::vector<double> vEnBGOBackH;
   std::vector<double> vIDBGOBackH;
   std::vector<double> vTmBGOBackH;
   for (int s=0; s<vTimeBGOBackH.size(); s++) {
      if (vEkeVBGOBackH[s] < 100000) {
         vIDBGOBackH.push_back(vEvIDBGOBackH[s]);
         vEnBGOBackH.push_back(vEkeVBGOBackH[s]);
         vTmBGOBackH.push_back(vTimeBGOBackH[s]);
      }
   }

   // BGO_Back_I
   std::vector<double> vEnBGOBackI;
   std::vector<double> vIDBGOBackI;
   std::vector<double> vTmBGOBackI;
   for (int s=0; s<vTimeBGOBackI.size(); s++) {
      if (vEkeVBGOBackI[s] < 100000) {
         vIDBGOBackI.push_back(vEvIDBGOBackI[s]);
         vEnBGOBackI.push_back(vEkeVBGOBackI[s]);
         vTmBGOBackI.push_back(vTimeBGOBackI[s]);
      }
   }

   // BGO_Back_J
   std::vector<double> vEnBGOBackJ;
   std::vector<double> vIDBGOBackJ;
   std::vector<double> vTmBGOBackJ;
   for (int s=0; s<vTimeBGOBackJ.size(); s++) {
      if (vEkeVBGOBackJ[s] < 100000) {
         vIDBGOBackJ.push_back(vEvIDBGOBackJ[s]);
         vEnBGOBackJ.push_back(vEkeVBGOBackJ[s]);
         vTmBGOBackJ.push_back(vTimeBGOBackJ[s]);
      }
   }


   //----------------------------------- Front BGOs ---------------------------------
   // BGO_Front_A
   std::vector<double> vEnBGOFrontA;
   std::vector<double> vIDBGOFrontA;
   std::vector<double> vTmBGOFrontA;
   for (int s=0; s<vTimeBGOFrontA.size(); s++) {
      if (vEkeVBGOFrontA[s] < 100000) {
         vIDBGOFrontA.push_back(vEvIDBGOFrontA[s]);
         vEnBGOFrontA.push_back(vEkeVBGOFrontA[s]);
         vTmBGOFrontA.push_back(vTimeBGOFrontA[s]);
      } 
   }

   // BGO_Front_B
   std::vector<double> vEnBGOFrontB;
   std::vector<double> vIDBGOFrontB;
   std::vector<double> vTmBGOFrontB;
   for (int s=0; s<vTimeBGOFrontB.size(); s++) {
      if (vEkeVBGOFrontB[s] < 100000) {
         vIDBGOFrontB.push_back(vEvIDBGOFrontB[s]);
         vEnBGOFrontB.push_back(vEkeVBGOFrontB[s]);
         vTmBGOFrontB.push_back(vTimeBGOFrontB[s]);
      } 
   }

   // BGO_Front_C
   std::vector<double> vEnBGOFrontC;
   std::vector<double> vIDBGOFrontC;
   std::vector<double> vTmBGOFrontC;
   for (int s=0; s<vTimeBGOFrontC.size(); s++) {
      if (vEkeVBGOFrontC[s] < 100000) {
         vIDBGOFrontC.push_back(vEvIDBGOFrontC[s]);
         vEnBGOFrontC.push_back(vEkeVBGOFrontC[s]);
         vTmBGOFrontC.push_back(vTimeBGOFrontC[s]);
      } 
   }

   // BGO_Front_D
   std::vector<double> vEnBGOFrontD;
   std::vector<double> vIDBGOFrontD;
   std::vector<double> vTmBGOFrontD;
   for (int s=0; s<vTimeBGOFrontD.size(); s++) {
      if (vEkeVBGOFrontD[s] < 100000) {
         vIDBGOFrontD.push_back(vEvIDBGOFrontD[s]);
         vEnBGOFrontD.push_back(vEkeVBGOFrontD[s]);
         vTmBGOFrontD.push_back(vTimeBGOFrontD[s]);
      } 
   }

   // BGO_Front_E
   std::vector<double> vEnBGOFrontE;
   std::vector<double> vIDBGOFrontE;
   std::vector<double> vTmBGOFrontE;
   for (int s=0; s<vTimeBGOFrontE.size(); s++) {
      if (vEkeVBGOFrontE[s] < 100000) {
         vIDBGOFrontE.push_back(vEvIDBGOFrontE[s]);
         vEnBGOFrontE.push_back(vEkeVBGOFrontE[s]);
         vTmBGOFrontE.push_back(vTimeBGOFrontE[s]);
      } 
   }

   // BGO_Front_F
   std::vector<double> vEnBGOFrontF;
   std::vector<double> vIDBGOFrontF;
   std::vector<double> vTmBGOFrontF;
   for (int s=0; s<vTimeBGOFrontF.size(); s++) {
      if (vEkeVBGOFrontF[s] < 100000) {
         vIDBGOFrontF.push_back(vEvIDBGOFrontF[s]);
         vEnBGOFrontF.push_back(vEkeVBGOFrontF[s]);
         vTmBGOFrontF.push_back(vTimeBGOFrontF[s]);
      } 
   }

   // BGO_Front_G
   std::vector<double> vEnBGOFrontG;
   std::vector<double> vIDBGOFrontG;
   std::vector<double> vTmBGOFrontG;
   for (int s=0; s<vTimeBGOFrontG.size(); s++) {
      if (vEkeVBGOFrontG[s] < 100000) {
         vIDBGOFrontG.push_back(vEvIDBGOFrontG[s]);
         vEnBGOFrontG.push_back(vEkeVBGOFrontG[s]);
         vTmBGOFrontG.push_back(vTimeBGOFrontG[s]);
      } 
   }
   
   // BGO_Front_H
   std::vector<double> vEnBGOFrontH;
   std::vector<double> vIDBGOFrontH;
   std::vector<double> vTmBGOFrontH;
   for (int s=0; s<vTimeBGOFrontH.size(); s++) {
      if (vEkeVBGOFrontH[s] < 100000) {
         vIDBGOFrontH.push_back(vEvIDBGOFrontH[s]);
         vEnBGOFrontH.push_back(vEkeVBGOFrontH[s]);
         vTmBGOFrontH.push_back(vTimeBGOFrontH[s]);
      } 
   }


   std::cout << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m---------------------- Matching --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;

   double BackClusterEn;
   double FrontClusterEn;

   for (int n=0; n<250; n++) {
      BackClusterEn = 0;
      FrontClusterEn = 0;
      for (int k=0; k<250; k++) {
         //------------------------------------ Back BGOs ---------------------------------
         if (vIDBGOBackA[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOBackA[k]) && (vTmBGOBackA[k] <= timemax[0])) {
               BackClusterEn += vEnBGOBackA[k];
               std::cout << "Back-A :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOBackA[k] << ", E = " << vEnBGOBackA[k] << std::endl;
            }
         }
         if (vIDBGOBackB[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOBackB[k]) && (vTmBGOBackB[k] <= timemax[0])) {
               BackClusterEn += vEnBGOBackB[k];
               std::cout << "Back-B :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOBackB[k] << ", E = " << vEnBGOBackB[k] << std::endl;
            }
         }
         if (vIDBGOBackC[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOBackC[k]) && (vTmBGOBackC[k] <= timemax[0])) {
               BackClusterEn += vEnBGOBackC[k];
               std::cout << "Back-C :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOBackC[k] << ", E = " << vEnBGOBackC[k] << std::endl;
            }
         }
         if (vIDBGOBackD[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOBackD[k]) && (vTmBGOBackD[k] <= timemax[0])) {
               BackClusterEn += vEnBGOBackD[k];
               std::cout << "Back-D :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOBackD[k] << ", E = " << vEnBGOBackD[k] << std::endl;
            }
         }
         if (vIDBGOBackE[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOBackE[k]) && (vTmBGOBackE[k] <= timemax[0])) {
               BackClusterEn += vEnBGOBackE[k];
               std::cout << "Back-E :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOBackE[k] << ", E = " << vEnBGOBackE[k] << std::endl;
            }
         }
         if (vIDBGOBackF[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOBackF[k]) && (vTmBGOBackF[k] <= timemax[0])) {
               BackClusterEn += vEnBGOBackF[k];
               std::cout << "Back-F :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOBackF[k] << ", E = " << vEnBGOBackF[k] << std::endl;
            }
         }
         if (vIDBGOBackG[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOBackG[k]) && (vTmBGOBackG[k] <= timemax[0])) {
               BackClusterEn += vEnBGOBackG[k];
               std::cout << "Back-G :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOBackG[k] << ", E = " << vEnBGOBackG[k] << std::endl;
            }
         }
         if (vIDBGOBackH[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOBackH[k]) && (vTmBGOBackH[k] <= timemax[0])) {
               BackClusterEn += vEnBGOBackH[k];
               std::cout << "Back-H :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOBackH[k] << ", E = " << vEnBGOBackH[k] << std::endl;
            }
         }
         if (vIDBGOBackI[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOBackI[k]) && (vTmBGOBackI[k] <= timemax[0])) {
               BackClusterEn += vEnBGOBackI[k];
               std::cout << "Back-I :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOBackI[k] << ", E = " << vEnBGOBackI[k] << std::endl;
            }
         }
         if (vIDBGOBackJ[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOBackJ[k]) && (vTmBGOBackJ[k] <= timemax[0])) {
               BackClusterEn += vEnBGOBackJ[k];
               std::cout << "Back-J :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOBackJ[k] << ", E = " << vEnBGOBackJ[k] << std::endl;
            }
         }
         //----------------------------------- Front BGOs ---------------------------------
         if (vIDBGOFrontA[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOFrontA[k]) && (vTmBGOFrontA[k] <= timemax[0])) {
               FrontClusterEn += vEnBGOFrontA[k];
               std::cout << "Front-A :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOFrontA[k] << ", E = " << vEnBGOFrontA[k] << std::endl;
            }
         }
         if (vIDBGOFrontB[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOFrontB[k]) && (vTmBGOFrontB[k] <= timemax[0])) {
               FrontClusterEn += vEnBGOFrontB[k];
               std::cout << "Front-B :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOFrontB[k] << ", E = " << vEnBGOFrontB[k] << std::endl;
            }
         }
         if (vIDBGOFrontC[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOFrontC[k]) && (vTmBGOFrontC[k] <= timemax[0])) {
               FrontClusterEn += vEnBGOFrontC[k];
               std::cout << "Front-C :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOFrontC[k] << ", E = " << vEnBGOFrontC[k] << std::endl;
            }
         }
         if (vIDBGOFrontD[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOFrontD[k]) && (vTmBGOFrontD[k] <= timemax[0])) {
               FrontClusterEn += vEnBGOFrontD[k];
               std::cout << "Front-D :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOFrontD[k] << ", E = " << vEnBGOFrontD[k] << std::endl;
            }
         }
         if (vIDBGOFrontE[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOFrontE[k]) && (vTmBGOFrontE[k] <= timemax[0])) {
               FrontClusterEn += vEnBGOFrontE[k]; 
               std::cout << "Front-E :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOFrontE[k] << ", E = " << vEnBGOFrontE[k] << std::endl;
            }
         }
         if (vIDBGOFrontF[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOFrontF[k]) && (vTmBGOFrontF[k] <= timemax[0])) {
               FrontClusterEn += vEnBGOFrontF[k];
               std::cout << "Front-F :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOFrontF[k] << ", E = " << vEnBGOFrontF[k] << std::endl;
            }
         }
         if (vIDBGOFrontG[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOFrontG[k]) && (vTmBGOFrontG[k] <= timemax[0])) {
               FrontClusterEn += vEnBGOFrontG[k];
               std::cout << "Front-G :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOFrontG[k] << ", E = " << vEnBGOFrontG[k] << std::endl;
            }
         }
         if (vIDBGOFrontH[k] == vEvIDTrig[n]) {
            if ((timemin[0] <= vTmBGOFrontH[k]) && (vTmBGOFrontH[k] <= timemax[0])) {
               FrontClusterEn += vEnBGOFrontH[k];
               std::cout << "Front-H :: ID = " << vEvIDTrig[n] << ", t = " << vTmBGOFrontH[k] << ", E = " << vEnBGOFrontH[k] << std::endl;
            }
         }
         //--------------------------------- Electron Vetos -------------------------------
         if (vEvIDV1[k] == vEvIDTrig[n]) {
            //if ((timemin[0] <= vTmBGOFrontH[k]) && (vTmBGOFrontH[k] <= timemax[0])) {
            std::cout << "V1 :: ID = " << vEvIDTrig[n] << ", t = " << vTimeV1[k] << ", E = " << vEdepV1[k] << std::endl;
         }
         if (vEvIDV2[k] == vEvIDTrig[n]) {
            std::cout << "V2 :: ID = " << vEvIDTrig[n] << ", t = " << vTimeV2[k] << ", E = " << vEdepV2[k] << std::endl;
         }
         if (vEvIDV3A[k] == vEvIDTrig[n]) {
            std::cout << "V3A :: ID = " << vEvIDTrig[n] << ", t = " << vTimeV3A[k] << ", E = " << vEdepV3A[k] << std::endl;
         }
         if (vEvIDV3B[k] == vEvIDTrig[n]) {
            std::cout << "V3B :: ID = " << vEvIDTrig[n] << ", t = " << vTimeV3B[k] << ", E = " << vEdepV3B[k] << std::endl;
         }
         if (vEvIDV4A[k] == vEvIDTrig[n]) {
            std::cout << "V4A :: ID = " << vEvIDTrig[n] << ", t = " << vTimeV4A[k] << ", E = " << vEdepV4A[k] << std::endl;
         }
         if (vEvIDV4B[k] == vEvIDTrig[n]) {
            std::cout << "V4B :: ID = " << vEvIDTrig[n] << ", t = " << vTimeV4B[k] << ", E = " << vEdepV4B[k] << std::endl;
         }

      }
      std::cout << std::endl;
      std::cout << "ID = " << vEvIDTrig[n] << ", BackClusterEn = " << BackClusterEn << std::endl;
      std::cout << "ID = " << vEvIDTrig[n] << ", FrontClusterEn = " << FrontClusterEn << std::endl;
      std::cout << std::endl;  
   }
/*
   const int nbins = 10;
   double Estep = 10000.0/(nbins);
   std::vector<double> Ethr;
   Ethr.push_back(0.0);
   for (int i=1; i<=nbins; i++) Ethr.push_back(Ethr[i-1]+Estep);

   std::vector<double> EffVeto1;
   std::vector<double> EffVeto2;
   std::vector<double> EffVeto3;
   std::vector<double> vMatchedEnVeto1;
   std::vector<double> vMatchedEnVeto2;
   std::vector<double> vMatchedEnVeto3;  
   
   for (int m=1; m<Ethr.size(); m++) {
      double MatchCounterVeto1=0;
      double MatchCounterVeto2=0;
      double MatchCounterVeto3=0;
      double TotalCounterVeto=0;

      for (int n=0; n<vIDBGOBackA.size(); n++) {
         if ((vEnBGOBackA[n] >= Ethr[m-1]) && (vEnBGOBackA[n] < Ethr[m])) {
            int UnmatchedV4A = 0;
            int GoodEventV4A = 0;
            for (int k=0; k<vEvIDV4A.size(); k++) {
               if (vEvIDV4A[k] == vIDBGOBackA[n]) {
                  if (vInstV4A[k] == 0) {
                     //if ((vTimeV4A[k] >= (vTmBGOBackA[n]-50)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+450))) {
                     if ((vTimeV4A[k] >= (vTmBGOBackA[n]-300)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+100))) {
                        //if ((vTimeV4A[k] >= (vTmBGOBackA[n]-40)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+160))) {
                        if ((vTimeV4A[k] >= (vTmBGOBackA[n]-300)) && (vTimeV4A[k] <= (vTmBGOBackA[n]-100))) {
                           MatchCounterVeto1++;
                           vMatchedEnVeto1.push_back(vEdepV4A[k]);
                        }
                        if ((vTimeV4A[k] >= (vTmBGOBackA[n]-50)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+50))) {
                           MatchCounterVeto2++;
                           vMatchedEnVeto2.push_back(vEdepV4A[k]);
                        }
                           //if ((vTimeV4A[k] >= (vTmBGOBackA[n]-25)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+25))) {
                              //MatchCounterVeto1++;
                              //vMatchedEnVeto1.push_back(vEdepV4A[k]);
                           //}
                           //MatchCounterVeto2++;
                           //vMatchedEnVeto2.push_back(vEdepV4A[k]);
                        //}
                        MatchCounterVeto3++;
                        vMatchedEnVeto3.push_back(vEdepV4A[k]);
                        UnmatchedV4A = 1;  
                     }
                  } else {
                     GoodEventV4A = 1;
                  }
               }
            }
            
            if (GoodEventV4A == 0) {
               TotalCounterVeto++;
            }
         }
      }
      std::cout << "Ethr = " << Ethr[m] << ", V4A :: Eff1 = " << MatchCounterVeto1/TotalCounterVeto << ", Eff2 = " << MatchCounterVeto2/TotalCounterVeto << ", Eff3 = " << MatchCounterVeto3/TotalCounterVeto << std::endl;
      EffVeto1.push_back(MatchCounterVeto1/TotalCounterVeto);
      EffVeto2.push_back(MatchCounterVeto2/TotalCounterVeto);
      EffVeto3.push_back(MatchCounterVeto3/TotalCounterVeto);

   }
*/
/*
   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

   float EffVeto1arr[nbins-1] = {}; // Efficiency V4_A
   float EffVeto2arr[nbins-1] = {};
   float EffVeto3arr[nbins-1] = {};
   float Ethrarr[nbins-1] = {};

   for (int i=0; i<(nbins-1); i++) {
      EffVeto1arr[i] = EffVeto1[i];
      EffVeto2arr[i] = EffVeto2[i];
      EffVeto3arr[i] = EffVeto3[i];
      Ethrarr[i] = (Ethr[i]/1000.0)+0.5;
   }


   TCanvas *c = new TCanvas("c","c",800,600);
   gPad->SetGrid(1,1);
   TGraph *grVeto1 = new TGraph(nbins-1,Ethrarr,EffVeto1arr);
   grVeto1->SetTitle("Efficiency of Veto_4_A");
   grVeto1->GetXaxis()->SetTitle("E_{BGO} [MeV]");
   grVeto1->GetYaxis()->SetTitle("Eff");
   grVeto1->GetYaxis()->SetTitleOffset(1.1);
   grVeto1->GetYaxis()->SetRangeUser(0.0,0.7);
   grVeto1->SetLineWidth(3);
   grVeto1->SetLineColor(kViolet-5);
   grVeto1->Draw("ALP");
   TGraph *grVeto2 = new TGraph(nbins-1,Ethrarr,EffVeto2arr);
   grVeto2->SetLineWidth(3);
   grVeto2->SetLineColor(kTeal-5);
   grVeto2->Draw("LP");
   TGraph *grVeto3 = new TGraph(nbins-1,Ethrarr,EffVeto3arr);
   grVeto3->SetLineWidth(3);
   grVeto3->SetLineColor(kOrange-3);
   grVeto3->Draw("LP");
   auto legend = new TLegend(0.84,0.71,0.96,0.87); 
   //legend->AddEntry(grVeto1,"t=[-25, 25] ns","f");
   //legend->AddEntry(grVeto2,"t=[-40, 160] ns","f");
   //legend->AddEntry(grVeto3,"t=[-50, 450] ns","f");
   legend->AddEntry(grVeto1,"t=[-300, -100] ns","f");
   legend->AddEntry(grVeto2,"t=[-50, 50] ns", "f");
   legend->AddEntry(grVeto3,"t=[-300, 100] ns","f");
   legend->Draw();
   //c->SaveAs("EffV4A_run549.pdf");

*/


}

int main() {
   DetSys1();
   return 0;
}  
