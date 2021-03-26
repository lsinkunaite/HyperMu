///////////////////////////////////////////////
//                                           //
//               VetoEff7.C                  //
//                                           //                
//  Compares the energy difference in the    //
//  sandwich detectors.                      //
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

void VetoEff7(){
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
   gStyle->SetPadBottomMargin(0.24);
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

   std::string runnumberPE = "run530/530";
   std::string runnumberAu = "run549/549";  

   std::vector<int> timemin;
   std::vector<int> timemax;

   timemin.push_back(100); // PE
   timemax.push_back(1000);
   timemin.push_back(-30); // Au
   timemax.push_back(30);
   double toffsetV4 = 3.0;
   double toffsetV5 = -3.0;   

   // Names of the files
   // Electron Vetos - PE
   std::string fileVeto4APE = runnumberPE+"_Veto4_A_prep.txt";
   std::string fileVeto4BPE = runnumberPE+"_Veto4_B_prep.txt";
   std::string fileVeto5APE = runnumberPE+"_Veto5_A_prep.txt";
   std::string fileVeto5BPE = runnumberPE+"_Veto5_B_prep.txt";
   // Electron Vetos - Au
   std::string fileVeto4AAu = runnumberAu+"_Veto4_A_prep.txt";
   std::string fileVeto4BAu = runnumberAu+"_Veto4_B_prep.txt";
   std::string fileVeto5AAu = runnumberAu+"_Veto5_A_prep.txt";
   std::string fileVeto5BAu = runnumberAu+"_Veto5_B_prep.txt";
   // BGOs - PE
   std::string fileBGOBackAPE = runnumberPE+"_BGO_Back_A_prep.txt";
   // BGOs - Au
   std::string fileBGOBackAAu = runnumberAu+"_BGO_Back_A_prep.txt";

   // Vectors with detector names
   std::vector<std::string> BGOfiles;
   std::vector<std::string> Vetofiles;

   // Electron Vetos
   Vetofiles.push_back(fileVeto4APE);
   Vetofiles.push_back(fileVeto4BPE);
   Vetofiles.push_back(fileVeto5APE);
   Vetofiles.push_back(fileVeto5BPE);
   Vetofiles.push_back(fileVeto4AAu);
   Vetofiles.push_back(fileVeto4BAu);
   Vetofiles.push_back(fileVeto5AAu);
   Vetofiles.push_back(fileVeto5BAu);
   // BGOs
   BGOfiles.push_back(fileBGOBackAPE);
   BGOfiles.push_back(fileBGOBackAAu);


   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   

   // Veto4_A - PE-target
   std::ifstream fVeto4Ape(Vetofiles[0]);
   std::vector<double> vEvIDV4Ape;
   std::vector<double> vEdepV4Ape;
   std::vector<double> vTimeV4Ape;
   while (!fVeto4Ape.eof()) {  
      double EvIDV4Ape, InstV4Ape, EdepV4Ape, TimeV4Ape;
      fVeto4Ape >> EvIDV4Ape >> InstV4Ape >> EdepV4Ape >> TimeV4Ape;
      vEvIDV4Ape.push_back(EvIDV4Ape);
      vEdepV4Ape.push_back(EdepV4Ape);
      vTimeV4Ape.push_back(TimeV4Ape+toffsetV4);
   }
   vEvIDV4Ape.pop_back();
   vEdepV4Ape.pop_back();
   vTimeV4Ape.pop_back();
   fVeto4Ape.close();


   // Veto4_B - PE-target
   std::ifstream fVeto4Bpe(Vetofiles[1]);
   std::vector<double> vEvIDV4Bpe;
   std::vector<double> vEdepV4Bpe;
   std::vector<double> vTimeV4Bpe;
   while (!fVeto4Bpe.eof()) {
      double EvIDV4Bpe, InstV4Bpe, EdepV4Bpe, TimeV4Bpe;
      fVeto4Bpe >> EvIDV4Bpe >> InstV4Bpe >> EdepV4Bpe >> TimeV4Bpe;
      vEvIDV4Bpe.push_back(EvIDV4Bpe);
      vEdepV4Bpe.push_back(EdepV4Bpe);
      vTimeV4Bpe.push_back(TimeV4Bpe+toffsetV4);
   }
   vEvIDV4Bpe.pop_back();
   vEdepV4Bpe.pop_back();
   vTimeV4Bpe.pop_back();
   fVeto4Bpe.close();


   // Veto5_A - PE-target
   std::ifstream fVeto5Ape(Vetofiles[2]);
   std::vector<double> vEvIDV5Ape;
   std::vector<double> vEdepV5Ape;
   std::vector<double> vTimeV5Ape;
   while (!fVeto5Ape.eof()) {
      double EvIDV5Ape, InstV5Ape, EdepV5Ape, TimeV5Ape;
      fVeto5Ape >> EvIDV5Ape >> InstV5Ape >> EdepV5Ape >> TimeV5Ape;
      vEvIDV5Ape.push_back(EvIDV5Ape);
      vEdepV5Ape.push_back(EdepV5Ape);
      vTimeV5Ape.push_back(TimeV5Ape+toffsetV5);
   }
   vEvIDV5Ape.pop_back();
   vEdepV5Ape.pop_back();
   vTimeV5Ape.pop_back();
   fVeto5Ape.close();


   // Veto5_B - PE-target
   std::ifstream fVeto5Bpe(Vetofiles[3]);
   std::vector<double> vEvIDV5Bpe;
   std::vector<double> vEdepV5Bpe;
   std::vector<double> vTimeV5Bpe;
   while (!fVeto5Bpe.eof()) {
      double EvIDV5Bpe, InstV5Bpe, EdepV5Bpe, TimeV5Bpe;
      fVeto5Bpe >> EvIDV5Bpe >> InstV5Bpe >> EdepV5Bpe >> TimeV5Bpe;
      vEvIDV5Bpe.push_back(EvIDV5Bpe);
      vEdepV5Bpe.push_back(EdepV5Bpe);
      vTimeV5Bpe.push_back(TimeV5Bpe+toffsetV5);
   }
   vEvIDV5Bpe.pop_back();
   vEdepV5Bpe.pop_back();
   vTimeV5Bpe.pop_back();
   fVeto5Bpe.close();


   // Veto4_A - Au-target
   std::ifstream fVeto4Aau(Vetofiles[4]);
   std::vector<double> vEvIDV4Aau;
   std::vector<double> vEdepV4Aau;
   std::vector<double> vTimeV4Aau;
   while (!fVeto4Aau.eof()) {
      double EvIDV4Aau, InstV4Aau, EdepV4Aau, TimeV4Aau;
      fVeto4Aau >> EvIDV4Aau >> InstV4Aau >> EdepV4Aau >> TimeV4Aau;
      vEvIDV4Aau.push_back(EvIDV4Aau);
      vEdepV4Aau.push_back(EdepV4Aau);
      vTimeV4Aau.push_back(TimeV4Aau+toffsetV4); 
   }
   vEvIDV4Aau.pop_back();
   vEdepV4Aau.pop_back();
   vTimeV4Aau.pop_back();
   fVeto4Aau.close();


   // Veto4_B - Au_target
   std::ifstream fVeto4Bau(Vetofiles[5]);
   std::vector<double> vEvIDV4Bau;
   std::vector<double> vEdepV4Bau;
   std::vector<double> vTimeV4Bau;
   while (!fVeto4Bau.eof()) {
      double EvIDV4Bau, InstV4Bau, EdepV4Bau, TimeV4Bau;
      fVeto4Bau >> EvIDV4Bau >> InstV4Bau >> EdepV4Bau >> TimeV4Bau;
      vEvIDV4Bau.push_back(EvIDV4Bau);
      vEdepV4Bau.push_back(EdepV4Bau);
      vTimeV4Bau.push_back(TimeV4Bau+toffsetV4);
   }
   vEvIDV4Bau.pop_back();
   vEdepV4Bau.pop_back();
   vTimeV4Bau.pop_back();  
   fVeto4Bau.close();


   // Veto5_A - Au-target
   std::ifstream fVeto5Aau(Vetofiles[6]);
   std::vector<double> vEvIDV5Aau;
   std::vector<double> vEdepV5Aau;
   std::vector<double> vTimeV5Aau;
   while (!fVeto5Aau.eof()) {
      double EvIDV5Aau, InstV5Aau, EdepV5Aau, TimeV5Aau;
      fVeto5Aau >> EvIDV5Aau >> InstV5Aau >> EdepV5Aau >> TimeV5Aau;
      vEvIDV5Aau.push_back(EvIDV5Aau);
      vEdepV5Aau.push_back(EdepV5Aau);
      vTimeV5Aau.push_back(TimeV5Aau+toffsetV5);
   }
   vEvIDV5Aau.pop_back();
   vEdepV5Aau.pop_back();
   vTimeV5Aau.pop_back();
   fVeto5Aau.close();


   // Veto5_B - Au-target
   std::ifstream fVeto5Bau(Vetofiles[7]);
   std::vector<double> vEvIDV5Bau;
   std::vector<double> vEdepV5Bau;
   std::vector<double> vTimeV5Bau;
   while (!fVeto5Bau.eof()) {
      double EvIDV5Bau, InstV5Bau, EdepV5Bau, TimeV5Bau;
      fVeto5Bau >> EvIDV5Bau >> InstV5Bau >> EdepV5Bau >> TimeV5Bau;
      vEvIDV5Bau.push_back(EvIDV5Bau);
      vEdepV5Bau.push_back(EdepV5Bau);
      vTimeV5Bau.push_back(TimeV5Bau+toffsetV5);
   }
   vEvIDV5Bau.pop_back();
   vEdepV5Bau.pop_back();
   vTimeV5Bau.pop_back();
   fVeto5Bau.close();


   // BGO_Back_A - PE-target
   std::ifstream fBGOBackApe(BGOfiles[0]);
   std::vector<double> vEvIDBGOBackApe;
   std::vector<double> vEdepBGOBackApe;
   std::vector<double> vEkeVBGOBackApe;
   std::vector<double> vTimeBGOBackApe;
   double kbgobacka = 1.74;
   double bbgobacka = 12.46;
   while (!fBGOBackApe.eof()) {
      double EvIDBGOBackApe, InstBGOBackApe, EdepBGOBackApe, TimeBGOBackApe;
      fBGOBackApe >> EvIDBGOBackApe >> InstBGOBackApe >> EdepBGOBackApe >> TimeBGOBackApe;
      double EkeVBGOBackApe;
      vEvIDBGOBackApe.push_back(EvIDBGOBackApe);
      vEdepBGOBackApe.push_back(EdepBGOBackApe);
      vTimeBGOBackApe.push_back(TimeBGOBackApe); 
      EkeVBGOBackApe = EdepBGOBackApe*kbgobacka+bbgobacka;
      vEkeVBGOBackApe.push_back(EkeVBGOBackApe);     
   }
   vEvIDBGOBackApe.pop_back();
   vEdepBGOBackApe.pop_back();
   vTimeBGOBackApe.pop_back();
   vEkeVBGOBackApe.pop_back();
   fBGOBackApe.close();


   // BGO_Back_A - Au-target
   std::ifstream fBGOBackAau(BGOfiles[1]);
   std::vector<double> vEvIDBGOBackAau;
   std::vector<double> vEdepBGOBackAau;
   std::vector<double> vEkeVBGOBackAau;
   std::vector<double> vTimeBGOBackAau;
   while (!fBGOBackAau.eof()) {
      double EvIDBGOBackAau, InstBGOBackAau, EdepBGOBackAau, TimeBGOBackAau;
      fBGOBackAau >> EvIDBGOBackAau >> InstBGOBackAau >> EdepBGOBackAau >> TimeBGOBackAau;
      double EkeVBGOBackAau;
      vEvIDBGOBackAau.push_back(EvIDBGOBackAau);
      vEdepBGOBackAau.push_back(EdepBGOBackAau);
      vTimeBGOBackAau.push_back(TimeBGOBackAau);
      EkeVBGOBackAau = EdepBGOBackAau*kbgobacka+bbgobacka;
      vEkeVBGOBackAau.push_back(EkeVBGOBackAau);
   }
   vEvIDBGOBackAau.pop_back();
   vEdepBGOBackAau.pop_back();
   vTimeBGOBackAau.pop_back();
   vEkeVBGOBackAau.pop_back();
   fBGOBackAau.close();


   std::cout << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m--------------------- Reading II -------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;

   // Veto_4_A - PE-target
   std::vector<double> vInstV4Ape; // Vector of repeating instances
   int EvIDV4Ape;
   for (int s=0; s<vEvIDV4Ape.size(); s++) {
      if ((s > 0) && (s < (vEvIDV4Ape.size()-1))) {
         if ((vEvIDV4Ape[s] == vEvIDV4Ape[s+1]) || (vEvIDV4Ape[s] == vEvIDV4Ape[s-1])) {
            vInstV4Ape.push_back(1);
         } else {
            vInstV4Ape.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDV4Ape[s] == vEvIDV4Ape[s+1]) {
            vInstV4Ape.push_back(1);
         } else {
            vInstV4Ape.push_back(0);
         }
      } else if (vEvIDV4Ape[s] == vEvIDV4Ape[s-1]) {
         vInstV4Ape.push_back(1);
      } else {
         vInstV4Ape.push_back(0);
      }
   }


   // Veto_4_B - PE-target
   std::vector<double> vInstV4Bpe; // Vector of repeating instances
   int EvIDV4Bpe;
   for (int s=0; s<vEvIDV4Bpe.size(); s++) {
      if ((s > 0) && (s < (vEvIDV4Bpe.size()-1))) {
         if ((vEvIDV4Bpe[s] == vEvIDV4Bpe[s+1]) || (vEvIDV4Bpe[s] == vEvIDV4Bpe[s-1])) {
            vInstV4Bpe.push_back(1);
         } else {
            vInstV4Bpe.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDV4Bpe[s] == vEvIDV4Bpe[s+1]) {
            vInstV4Bpe.push_back(1);
         } else {
            vInstV4Bpe.push_back(0);
         }
      } else if (vEvIDV4Bpe[s] == vEvIDV4Bpe[s-1]) {
         vInstV4Bpe.push_back(1);
      } else {
         vInstV4Bpe.push_back(0);
      }
   }


   // Veto_5_A - PE-target
   std::vector<double> vInstV5Ape; // Vector of repeating instances
   int EvIDV5Ape;
   for (int s=0; s<vEvIDV5Ape.size(); s++) {
      if ((s > 0) && (s < (vEvIDV5Ape.size()-1))) {
         if ((vEvIDV5Ape[s] == vEvIDV5Ape[s+1]) || (vEvIDV5Ape[s] == vEvIDV5Ape[s-1])) {
            vInstV5Ape.push_back(1);
         } else {
            vInstV5Ape.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDV5Ape[s] == vEvIDV5Ape[s+1]) {
            vInstV5Ape.push_back(1);
         } else {
            vInstV5Ape.push_back(0);
         }
      } else if (vEvIDV5Ape[s] == vEvIDV5Ape[s-1]) {
         vInstV5Ape.push_back(1);
      } else {
         vInstV5Ape.push_back(0);
      }
   }


   // Veto_5_B - PE-target
   std::vector<double> vInstV5Bpe; // Vector of repeating instances
   int EvIDV5Bpe;
   for (int s=0; s<vEvIDV5Bpe.size(); s++) {
      if ((s > 0) && (s < (vEvIDV5Bpe.size()-1))) {
         if ((vEvIDV5Bpe[s] == vEvIDV5Bpe[s+1]) || (vEvIDV5Bpe[s] == vEvIDV5Bpe[s-1])) {
            vInstV5Bpe.push_back(1);
         } else {
            vInstV5Bpe.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDV5Bpe[s] == vEvIDV5Bpe[s+1]) {
            vInstV5Bpe.push_back(1);
         } else {
            vInstV5Bpe.push_back(0);
         }
      } else if (vEvIDV5Bpe[s] == vEvIDV5Bpe[s-1]) { 
         vInstV5Bpe.push_back(1);
      } else {
         vInstV5Bpe.push_back(0);
      }
   }


   // Veto4_A - Au-target
   std::vector<double> vInstV4Aau; // Vector of repeating instances
   int EvIDV4Aau;
   for (int s=0; s<vEvIDV4Aau.size(); s++) {
      if ((s > 0) && (s < (vEvIDV4Aau.size()-1))) {
         if ((vEvIDV4Aau[s] == vEvIDV4Aau[s+1]) || (vEvIDV4Aau[s] == vEvIDV4Aau[s-1])) {
            vInstV4Aau.push_back(1);
         } else {
            vInstV4Aau.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDV4Aau[s] == vEvIDV4Aau[s+1]) {
            vInstV4Aau.push_back(1);
         } else {
            vInstV4Aau.push_back(0);
         }
      } else if (vEvIDV4Aau[s] == vEvIDV4Aau[s-1]) {
         vInstV4Aau.push_back(1);
      } else {
         vInstV4Aau.push_back(0);
      }
   }


   // Veto4_B - Au-target
   std::vector<double> vInstV4Bau; // Vector of repeating instances
   int EvIDV4Bau;
   for (int s=0; s<vEvIDV4Bau.size(); s++) {
      if ((s > 0) && (s < (vEvIDV4Bau.size()-1))) {
         if ((vEvIDV4Bau[s] == vEvIDV4Bau[s+1]) || (vEvIDV4Bau[s] == vEvIDV4Bau[s-1])) {
            vInstV4Bau.push_back(1);
         } else {
            vInstV4Bau.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDV4Bau[s] == vEvIDV4Bau[s+1]) {
            vInstV4Bau.push_back(1);
         } else {
            vInstV4Bau.push_back(0);
         }
      } else if (vEvIDV4Bau[s] == vEvIDV4Bau[s-1]) {
         vInstV4Bau.push_back(1);
      } else {
         vInstV4Bau.push_back(0);
      }
   }


   // Veto5_A - Au-target
   std::vector<double> vInstV5Aau; // Vector of repeating instances
   int EvIDV5Aau;
   for (int s=0; s<vEvIDV5Aau.size(); s++) {
      if ((s > 0) && (s < (vEvIDV5Aau.size()-1))) {
         if ((vEvIDV5Aau[s] == vEvIDV5Aau[s+1]) || (vEvIDV5Aau[s] == vEvIDV5Aau[s-1])) {
            vInstV5Aau.push_back(1);
         } else {
            vInstV5Aau.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDV5Aau[s] == vEvIDV5Aau[s+1]) {
            vInstV5Aau.push_back(1);
         } else {
            vInstV5Aau.push_back(0);
         }
      } else if (vEvIDV5Aau[s] == vEvIDV5Aau[s-1]) {
         vInstV5Aau.push_back(1);
      } else {
         vInstV5Aau.push_back(0);
      }
   }


   // Veto5_B - Au-target
   std::vector<double> vInstV5Bau; // Vector of repeating instances
   int EvIDV5Bau;
   for (int s=0; s<vEvIDV5Bau.size(); s++) {
      if ((s > 0) && (s < (vEvIDV5Bau.size()-1))) {
         if ((vEvIDV5Bau[s] == vEvIDV5Bau[s+1]) || (vEvIDV5Bau[s] == vEvIDV5Bau[s-1])) {
            vInstV5Bau.push_back(1);
         } else {
            vInstV5Bau.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDV5Bau[s] == vEvIDV5Bau[s+1]) {
            vInstV5Bau.push_back(1);
         } else {
            vInstV5Bau.push_back(0);
         }
      } else if (vEvIDV5Bau[s] == vEvIDV5Bau[s-1]) {
         vInstV5Bau.push_back(1);
      } else {
         vInstV5Bau.push_back(0);
      }
   }


   // BGO_Back_A - PE-target
   std::vector<double> vEnBGOBackApe;
   std::vector<double> vIDBGOBackApe;
   std::vector<double> vTmBGOBackApe;
   for (int s=0; s<vTimeBGOBackApe.size(); s++) {
      if ((vTimeBGOBackApe[s] > timemin[0]) && (vTimeBGOBackApe[s] <timemax[0])) {
         if ((vEkeVBGOBackApe[s] >= 2000) && (vEkeVBGOBackApe[s] < 100000)) {
            vIDBGOBackApe.push_back(vEvIDBGOBackApe[s]);
            vEnBGOBackApe.push_back(vEkeVBGOBackApe[s]);
            vTmBGOBackApe.push_back(vTimeBGOBackApe[s]);
         }
      }
   }


   // BGO_Back_B - Au-target
   std::vector<double> vEnBGOBackAau;
   std::vector<double> vIDBGOBackAau;
   std::vector<double> vTmBGOBackAau;
   for (int s=0; s<vTimeBGOBackAau.size(); s++) {
      if ((vTimeBGOBackAau[s] > timemin[1]) && (vTimeBGOBackAau[s] <timemax[1])) {
         if ((vEkeVBGOBackAau[s] >= 500) && (vEkeVBGOBackAau[s] < 10000)) {
            vIDBGOBackAau.push_back(vEvIDBGOBackAau[s]);
            vEnBGOBackAau.push_back(vEkeVBGOBackAau[s]);
            vTmBGOBackAau.push_back(vTimeBGOBackAau[s]);
         }
      }
   }


   std::cout << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m---------------------- Matching --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;


   std::vector<double> EnVeto4Ape;
   std::vector<double> EnVeto4Aau;
   std::vector<double> EnVeto5Ape;
   std::vector<double> EnVeto5Aau; 
   
   for (int n=0; n<vIDBGOBackApe.size(); n++) {
      // Veto_4_A - PE-target
      int MatchV4Ape = 0;
      for (int k=0; k<vEvIDV4Ape.size(); k++) {
         if (vEvIDV4Ape[k] == vIDBGOBackApe[n]) {
            if ((vTimeV4Ape[k] >= (vTmBGOBackApe[n]-250)) && (vTimeV4Ape[k] <= (vTmBGOBackApe[n]+65))) { 
               if (vEdepV4Ape[k] >= 0) {
                  EnVeto4Ape.push_back(vEdepV4Ape[k]);
                  MatchV4Ape = 1;
               }
            }
         }
      }   
      if (MatchV4Ape == 0) {
         EnVeto4Ape.push_back(0.0);
      }
   }
 
   for (int n=0; n<vIDBGOBackAau.size(); n++) {
      // Veto_4_A - Au-target
      int MatchV4Aau = 0;
      for (int k=0; k<vEvIDV4Aau.size(); k++) {
         if (vEvIDV4Aau[k] == vIDBGOBackAau[n]) {
            if ((vTimeV4Aau[k] >= (vTmBGOBackAau[n]-50)) && (vTimeV4Aau[k] <= (vTmBGOBackAau[n]+450))) { 
               if (vEdepV4Aau[k] >= 0) { 
                  EnVeto4Aau.push_back(vEdepV4Aau[k]);
                  MatchV4Aau = 1;
               }
            }
         }
      }
      if (MatchV4Aau == 0) {
         EnVeto4Aau.push_back(0.0);
      }
   }
  
   for (int n=0; n<vIDBGOBackApe.size(); n++) {
      // Veto_5_A - PE-target
      int MatchV5Ape = 0;
      for (int l=0; l<vEvIDV5Ape.size(); l++) {
         if (vEvIDV5Ape[l] == vIDBGOBackApe[n]) {
            if ((vTimeV5Ape[l] >= (vTmBGOBackApe[n]-250)) && (vTimeV5Ape[l] <= (vTmBGOBackApe[n]+65))) {
               if (vEdepV5Ape[l] >= 0) {
                  EnVeto5Ape.push_back(vEdepV5Ape[l]);
                  MatchV5Ape = 1;
               }
            }
         }
      }
      if (MatchV5Ape == 0) {
         EnVeto5Ape.push_back(0.0);
      }
   }

   for (int n=0; n<vIDBGOBackAau.size(); n++) {
      // Veto_5_A - Au-target
      int MatchV5Aau = 0;
      for (int l=0; l<vEvIDV5Aau.size(); l++) {
         if (vEvIDV5Aau[l] == vIDBGOBackAau[n]) {
            if ((vTimeV5Aau[l] >= (vTmBGOBackAau[n]-50)) && (vTimeV5Aau[l] <= (vTmBGOBackAau[n]+450))) {
               if (vEdepV5Aau[l] >= 0) {
                  EnVeto5Aau.push_back(vEdepV5Aau[l]);
                  MatchV5Aau = 1;
               }
            }  
         }
      } 
      if (MatchV5Aau == 0) {
         EnVeto5Aau.push_back(0.0);         
      }
   }

   std::cout << "Length PE : BGO = " << vIDBGOBackApe.size() << ", V4A = " << EnVeto4Ape.size() << ", V5A = " << EnVeto5Ape.size() << std::endl; 
   std::cout << "Length Au : BGO = " << vIDBGOBackAau.size() << ", V4A = " << EnVeto4Aau.size() << ", V5A = " << EnVeto5Aau.size() << std::endl;

   std::vector<double> EnDiff1pe;
   std::vector<double> EnDiff2pe;
   std::vector<double> EnDiff3pe;
   std::vector<double> EnDiff1au;
   std::vector<double> EnDiff2au;
   std::vector<double> EnDiff3au;
   double auxx = 0;
   double auxe = 0;
   double peee = 0;
   double peex = 0;
   for (int i=0; i<vIDBGOBackApe.size(); i++) {
      EnDiff1pe.push_back(EnVeto4Ape[i]-EnVeto5Ape[i]);
      EnDiff2pe.push_back((EnVeto4Ape[i]-EnVeto5Ape[i])/(EnVeto4Ape[i]+EnVeto5Ape[i]));
      if (EnVeto5Ape[i] >= EnVeto4Ape[i]) {
         EnDiff3pe.push_back((EnVeto5Ape[i]-EnVeto4Ape[i])/(EnVeto5Ape[i]));
      } else {
         EnDiff3pe.push_back((EnVeto4Ape[i]-EnVeto5Ape[i])/(EnVeto4Ape[i]));
      }
      //EnDiff3pe.push_back((EnVeto4Ape[i]-EnVeto5Ape[i])*(EnVeto4Ape[i]+EnVeto5Ape[i]));
      //if (EnDiff3pe[i] <= 0.5) {
      if ((EnVeto4Ape[i] >= 500) && (EnVeto5Ape[i] >= 500)) {
         peee++;
      } else {
         peex++;
      }
   }
   for (int i=0; i<vIDBGOBackAau.size(); i++) {
      EnDiff1au.push_back(EnVeto4Aau[i]-EnVeto5Aau[i]);
      EnDiff2au.push_back((EnVeto4Aau[i]-EnVeto5Aau[i])/(EnVeto4Aau[i]+EnVeto5Aau[i]));
      if (EnVeto5Aau[i] >= EnVeto4Aau[i]) {
         EnDiff3au.push_back((EnVeto5Aau[i]-EnVeto4Aau[i])/(EnVeto5Aau[i]));
      } else {
         EnDiff3au.push_back((EnVeto4Aau[i]-EnVeto5Aau[i])/(EnVeto4Aau[i]));
      }
      //EnDiff3au.push_back((EnVeto4Aau[i]-EnVeto5Aau[i])*(EnVeto4Aau[i]+EnVeto5Aau[i]));
      //if (EnDiff3au[i] <= 0.5) {
      if ((EnVeto4Aau[i] >= 500) && (EnVeto5Aau[i] >= 500)) {
         auxe++;
      } else {
         auxx++;
      }
   }   

   std::cout << " Au :: x-eff = " << auxx/(vIDBGOBackAau.size()) << ", misid = " << auxe/(vIDBGOBackAau.size()) << std::endl;
   std::cout << " PE :: el-eff = " << peee/(vIDBGOBackApe.size()) << ", e misid = " << peex/(vIDBGOBackApe.size()) << std::endl;

   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

   TH1F *hEnDiff1pe = new TH1F("hDiff1pe","hDiff1pe",50,-1000.0,1000.0); // EnDiff1-pe
   TH1F *hEnDiff1au = new TH1F("hDiffau","hDiff1au",50,-1000.0,1000.0); // EnDiff1-au
   TH1F *hEnDiff2pe = new TH1F("hDiff2pe","hDiff2pe",50,-1.2,1.2); // EnDiff2-pe
   TH1F *hEnDiff2au = new TH1F("hDiff2au","hDiff2au",50,-1.2,1.2); // EnDiff2-au
   TH1F *hEnDiff3pe = new TH1F("hDiff3pe","hDiff3pe",50,0.0,1.01); // EnDiff3-pe
   TH1F *hEnDiff3au = new TH1F("hDiff3au","hDiff3au",50,0.0,1.01); // EnDiff3-au

   TH1F *hEnV4A = new TH1F("hEnV4A","hEnV4A",100,0.0,10.0);
   TH1F *hEnV5A = new TH1F("hEnV5A","hEnV5A",100,0.0,10.0);

   for (int i=0; i<EnDiff1pe.size(); i++) hEnDiff1pe->Fill(EnDiff1pe[i]);
   for (int i=0; i<EnDiff2pe.size(); i++) hEnDiff2pe->Fill(EnDiff2pe[i]);
   for (int i=0; i<EnDiff3pe.size(); i++) hEnDiff3pe->Fill(EnDiff3pe[i]);
   for (int i=0; i<EnDiff1au.size(); i++) hEnDiff1au->Fill(EnDiff1au[i]);
   for (int i=0; i<EnDiff2au.size(); i++) hEnDiff2au->Fill(EnDiff2au[i]);
   for (int i=0; i<EnDiff3au.size(); i++) hEnDiff3au->Fill(EnDiff3au[i]);

   for (int i=0; i<EnVeto4Aau.size(); i++) hEnV4A->Fill(EnVeto4Aau[i]/1000.0);
   for (int i=0; i<EnVeto5Aau.size(); i++) hEnV5A->Fill(EnVeto5Aau[i]/1000.0);
/*
   TCanvas *c = new TCanvas("c","c",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hEnV4A->SetTitle("");
   hEnV4A->GetXaxis()->SetTitle("E_{Veto} [kadc]");
   hEnV4A->SetLineColor(kBlue);
   hEnV4A->Draw("");
   hEnV5A->SetLineColor(kRed);
   hEnV5A->Draw("SAME");
   auto l = new TLegend(0.82, 0.71,0.94,0.87);
   l->AddEntry(hEnV4A,"V4A","l");
   l->AddEntry(hEnV5A,"V5A","l");
   l->Draw();
*/
/*
   TCanvas *c1 = new TCanvas("c1","c1",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hEnDiff1au->SetTitle("");
   hEnDiff1au->GetXaxis()->SetTitle("E_{V4_A} - E_{V5_A} [adc]");
   hEnDiff1au->SetLineWidth(3);
   hEnDiff1au->SetLineColor(kGray+3);
   hEnDiff1au->SetFillColorAlpha(kTeal-5,0.7);
   hEnDiff1au->Draw();
   hEnDiff1pe->SetLineWidth(3);
   hEnDiff1pe->SetLineColor(kGray+3);
   hEnDiff1pe->SetFillColorAlpha(kPink+4,0.5);
   //hEnDiff1pe->Draw("same");
   auto legend1 = new TLegend(0.82,0.71,0.94,0.87);
   legend1->AddEntry(hEnDiff1pe,"PE","f");
   legend1->AddEntry(hEnDiff1au,"Au","f");
   legend1->Draw();
   c1->SaveAs("Eff_Sand_Smart1_encut.pdf");
   
   TCanvas *c2 = new TCanvas("c2","c2",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hEnDiff2au->SetTitle("");
   hEnDiff2au->GetXaxis()->SetTitle("#frac{E_{V4_A} - E_{V5_A}}{E_{V4_A} + E_{V5_A}}");
   hEnDiff2au->SetLineWidth(3);
   hEnDiff2au->SetLineColor(kGray+3);
   hEnDiff2au->SetFillColorAlpha(kViolet-5,0.7);
   hEnDiff2au->Draw();
   hEnDiff2pe->SetLineWidth(3);
   hEnDiff2pe->SetLineColor(kGray+3);
   hEnDiff2pe->SetFillColorAlpha(kSpring-1,0.5);  
   hEnDiff2pe->Draw("same");
   auto legend2 = new TLegend(0.82,0.71,0.94,0.87);
   legend2->AddEntry(hEnDiff2pe,"PE","f");
   legend2->AddEntry(hEnDiff2au,"Au","f");
   legend2->Draw();
   c2->SaveAs("Eff_Sand_Smart2_encut.pdf");
*/
   TCanvas *c3 = new TCanvas("c3","c3",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hEnDiff3au->SetTitle("");
   hEnDiff3au->GetXaxis()->SetTitleOffset(1.6);
   hEnDiff3au->GetXaxis()->SetTitle("#frac{|E_{V4_A} - E_{V5_A}|}{max.(E_{V4_A}, E_{V5_A})}");
   hEnDiff3au->SetLineWidth(3);
   hEnDiff3au->SetLineColor(kGray+3);
   hEnDiff3au->SetFillColorAlpha(kOrange-5,0.7);
   hEnDiff3au->Draw();
   hEnDiff3pe->SetLineWidth(3);
   hEnDiff3pe->SetLineColor(kGray+3);
   hEnDiff3pe->SetFillColorAlpha(kAzure+8,0.5);
   hEnDiff3pe->Draw("same");
   auto legend3 = new TLegend(0.8,0.81,0.88,0.96);
   legend3->AddEntry(hEnDiff3pe,"PE","f");
   legend3->AddEntry(hEnDiff3au,"Au","f");
   legend3->Draw();
   c3->SaveAs("Eff_Sand_Smart3_encut.pdf");

}

int main() {
   VetoEff7();
   return 0;
} 
 
