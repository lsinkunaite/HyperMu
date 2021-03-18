/////////////////////////////////////////////
//                                         //
//               VetoEff6.C                //
//                                         //         
//  Plots Efficiency of a veto versus the  //
//  threshold in the BGO.                  //
//                                         //
/////////////////////////////////////////////


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

void VetoEff6(){
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
   gStyle->SetPadLeftMargin(0.);
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
   std::string runnumber = "run549/549";
  
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
   // BGOs
   std::string fileBGOBackA = runnumber+"_BGO_Back_A_prep.txt";

   // Vectors with detector names
   std::vector<std::string> BGOfiles;
   std::vector<std::string> Vetofiles;

   // Electron Vetos
   Vetofiles.push_back(fileVeto4A);
   Vetofiles.push_back(fileVeto4B);
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
   
   for (int m=0; m<Ethr.size(); m++) {
      double MCountA1=0;
      double MCountA2=0;
      double MCountA3=0;
      double TCountA=0;
      double MCountB1=0;
      double MCountB2=0;
      double MCountB3=0;
      double TCountB=0;

      std::vector<double> vMBGOA1;
      std::vector<double> vMBGOA2;
      std::vector<double> vMBGOA3;
      std::vector<double> vMBGOB1;
      std::vector<double> vMBGOB2;
      std::vector<double> vMBGOB3;

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
                     //if ((vTimeV4A[k] >= (vTmBGOBackA[n]-50)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+450))) {
                     if ((vTimeV4A[k] >= (vTmBGOBackA[n]-40)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+160))) {
                        if ((vTimeV4A[k] >= (vTmBGOBackA[n]-40)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+160))) {
                           if ((vTimeV4A[k] >= (vTmBGOBackA[n]-25)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+25))) {
                              MCountA1++;
                              UnmatchedV4A1 = 1;
                           }
                           MCountA2++;
                           UnmatchedV4A2 = 1;
                        }
                        MCountA3++;
                        UnmatchedV4A3 = 1;
                     }
                  }
               } else {
                  GoodEventV4A = 1;
               }
            }
         }
         if (GoodEventV4A == 0) {
            TCountA++;
            if (UnmatchedV4A3 == 0) {
               vMBGOA3.push_back(0);
               vMBGOA2.push_back(0);
               vMBGOA1.push_back(0);
            } else {
               vMBGOA3.push_back(1);
               if (UnmatchedV4A2 == 0) {
                  vMBGOA2.push_back(0);
                  vMBGOA1.push_back(0);
               } else {
                  if (UnmatchedV4A1 == 0) {
                     vMBGOA1.push_back(0);
                  } else {
                     vMBGOA1.push_back(1);
                  }
               }
            } 
         } else {
            vMBGOA1.push_back(-1);
            vMBGOA2.push_back(-1);
            vMBGOA3.push_back(-1);
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
                     if ((vTimeV4B[k] >= (vTmBGOBackA[n]-40)) && (vTimeV4B[k] <= (vTmBGOBackA[n]+160))) {
                        if ((vTimeV4B[k] >= (vTmBGOBackA[n]-40)) && (vTimeV4B[k] <= (vTmBGOBackA[n]+160))) {
                           if ((vTimeV4B[k] >= (vTmBGOBackA[n]-25)) && (vTimeV4B[k] <= (vTmBGOBackA[n]+25))) {
                              MCountB1++;
                              UnmatchedV4B1 = 1;
                           }
                           MCountB2++;
                           UnmatchedV4B2 = 1;
                        }
                        MCountB3++;
                        UnmatchedV4B3 = 1;
                     }
                  }
               } else {
                  GoodEventV4B = 1;
               }
            }
         } 
         if (GoodEventV4B == 0) {
            TCountB++;
            if (UnmatchedV4B3 == 0) {
               vMBGOB3.push_back(0);
               vMBGOB2.push_back(0);
               vMBGOB1.push_back(0);
            } else {
               vMBGOB3.push_back(1);
               if (UnmatchedV4B2 == 0) {
                  vMBGOB2.push_back(0);
                  vMBGOB1.push_back(0);
               } else {
                  vMBGOB2.push_back(1);
                  if (UnmatchedV4B1 == 0) {
                     vMBGOB1.push_back(0);
                  } else {
                     vMBGOB1.push_back(1);
                  }
               }
            }
         } else {
            vMBGOB1.push_back(-1);
            vMBGOB2.push_back(-1);
            vMBGOB3.push_back(-1);
         }
      }
      std::cout << "Ethr = " << Ethr[m] << ", V4A :: Eff1 = " << MCountA1/TCountA << ", Eff2 = " << MCountA2/TCountA << ", Eff3 = " << MCountA3/TCountA << std::endl;
      std::cout << "Ethr = " << Ethr[m] << ", V4B :: Eff1 = " << MCountB1/TCountB << ", Eff2 =  " << MCountB2/TCountB << ", Eff3 = " << MCountB3/TCountB << std::endl;
      std::cout << std::endl;
      EffVetoA1.push_back(MCountA1/TCountA);
      EffVetoA2.push_back(MCountA2/TCountA);
      EffVetoA3.push_back(MCountA3/TCountA);
      EffVetoB1.push_back(MCountB1/TCountB);
      EffVetoB2.push_back(MCountB2/TCountB);
      EffVetoB3.push_back(MCountB3/TCountB);

      
      // Veto_4_A && Veto_4_B
      double ANDCount1 = 0;
      double ANDCount2 = 0;
      double ANDCount3 = 0;
      double ORCount1 = 0;
      double ORCount2 = 0;
      double ORCount3 = 0;
      double TotCount1 = 0;
      double TotCount2 = 0;
      double TotCount3 = 0;

      for (int j=0; j<vMBGOB1.size(); j++) {
         // Large time selection
         if ((vMBGOA3[j] == 1) && (vMBGOB3[j] == 1)) {
            ANDCount3++;
            ORCount3++;
            TotCount3++;
         } else if ((vMBGOA3[j] == 1) || (vMBGOB3[j] == 1)) {
            ORCount3++;
            TotCount3++;
         } else if ((vMBGOA3[j] + vMBGOB3[j]) == 0) {
            TotCount3++;
         }
         // Intermediate time selection
         if ((vMBGOA2[j] == 1) && (vMBGOB2[j] == 1)) {
            ANDCount2++;
            ORCount2++;
            TotCount2++;
         } else if ((vMBGOA2[j] == 1) || (vMBGOB2[j] == 1)) {
            ORCount2++;
            TotCount2++;
         } else if ((vMBGOA2[j] + vMBGOB2[j]) == 0) {
            TotCount2++;
         }
         // Small time selection
         if ((vMBGOA1[j] == 1) && (vMBGOB1[j] == 1)) {
            ANDCount1++;
            ORCount1++;
            TotCount1++;
         } else if ((vMBGOA1[j] == 1) || (vMBGOB1[j] == 1)) {
            ORCount1++;
            TotCount1++;
         } else if ((vMBGOA1[j] + vMBGOB1[j]) == 0) {
            TotCount1++;
         }
      }
      Effand1.push_back(ANDCount1/TotCount1);
      Effor1.push_back(ORCount1/TotCount1);
      Effand2.push_back(ANDCount2/TotCount2);
      Effor2.push_back(ORCount2/TotCount2);
      Effand3.push_back(ANDCount3/TotCount3);
      Effor3.push_back(ORCount3/TotCount3);

      std::cout << "Ethr = " << Ethr[m] << ", Eff1 = " << Effor1[m] << ", Eff2 = " << Effor2[m] << " Effor3 = " << Effor3[m] << std::endl;

   }


   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

   // Efficiency V4_A
   float EffV4A1arr[nbins+1] = {};
   float EffV4A2arr[nbins+1] = {};
   float EffV4A3arr[nbins+1] = {};
   float EffV4B1arr[nbins+1] = {};
   float EffV4B2arr[nbins+1] = {};
   float EffV4B3arr[nbins+1] = {};
   float Effand1arr[nbins+1] = {};
   float Effand2arr[nbins+1] = {};
   float Effand3arr[nbins+1] = {};
   float Effor1arr[nbins+1] = {};
   float Effor2arr[nbins+1] = {};  
   float Effor3arr[nbins+1] = {};
   float Ethrarr[nbins+1] = {};

   for (int i=0; i<(nbins+1); i++) {
      EffV4A1arr[i] = EffVetoA1[i];
      EffV4A2arr[i] = EffVetoA2[i];
      EffV4A3arr[i] = EffVetoA3[i];
      EffV4B1arr[i] = EffVetoB1[i];
      EffV4B2arr[i] = EffVetoB2[i];
      EffV4B3arr[i] = EffVetoB3[i];
      Effand1arr[i] = Effand1[i];
      Effand2arr[i] = Effand2[i];
      Effand3arr[i] = Effand3[i];
      Effor1arr[i] = Effor1[i];
      Effor2arr[i] = Effor2[i];
      Effor3arr[i] = Effor3[i];
      Ethrarr[i] = Ethr[i];
   }


   TCanvas *c = new TCanvas("c","c",800,600);
   gPad->SetGrid(1,1);
   TGraph *grV4A3 = new TGraph(nbins+1,Ethrarr,EffV4A3arr);
   grV4A3->SetTitle("");
   grV4A3->GetXaxis()->SetTitle("E_{Veto} > E_{THR} [adc]");
   grV4A3->GetYaxis()->SetTitle("Eff");
   grV4A3->GetYaxis()->SetTitleOffset(1.1);
   //grV4A3->GetYaxis()->SetRangeUser(0.975,0.99); // PE-target
   grV4A3->GetYaxis()->SetRangeUser(0.05,0.36); // Au-target
   grV4A3->GetXaxis()->SetRangeUser(0,1100.00);
   grV4A3->SetLineWidth(3);
   grV4A3->SetLineColor(kViolet-5);
   grV4A3->Draw("ALP");
   TGraph *grV4B3 = new TGraph(nbins+1,Ethrarr,EffV4B3arr);
   grV4B3->SetLineWidth(3);
   grV4B3->SetLineColor(kTeal-5);
   grV4B3->Draw("LP");
   TGraph *grand3 = new TGraph(nbins+1,Ethrarr,Effand3arr);
   grand3->SetLineWidth(3);
   grand3->SetLineColor(kOrange-3);
   grand3->Draw("LP");
   TGraph *gror3 = new TGraph(nbins+1,Ethrarr,Effor3arr);
   gror3->SetLineWidth(3);
   gror3->SetLineColor(kRed-7);
   gror3->Draw("LP");
   auto legend = new TLegend(0.84,0.71,0.92,0.87); 
   legend->AddEntry(grV4A3,"A","l");
   legend->AddEntry(grV4B3,"B","l");
   legend->AddEntry(grand3,"AND","l");
   legend->AddEntry(gror3,"OR","l");
   legend->Draw();
   //c->SaveAs("EffV4_conditions_run549.pdf");




}

int main() {
   VetoEff6();
   return 0;
}  
