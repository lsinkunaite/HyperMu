////////////////////////////////////////////////
//                                            //
//               VetoEff2.C                   //
//                                            //         
//  Plots Efficiency of a veto for different  //
//  energies in the E_veto.                   //
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

void VetoEff2(){
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

   std::string runnumber = "run549/549";
  
   std::vector<int> timemin;
   std::vector<int> timemax;

   timemin.push_back(100);
   timemax.push_back(300);

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
      vTimeV4A.push_back(TimeV4A);
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




}

int main() {
   VetoEff2();
   return 0;
}  
