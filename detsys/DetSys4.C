///////////////////////////////////////////////
//                                           //
//                 DetSys4.C                 //
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

void DetSys4(){
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
   gStyle->SetPadBottomMargin(0.14);
   gStyle->SetPadLeftMargin(0.12);
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

   // Uncomment for Au-target
   std::string runnumber = "run373/373";
   // Uncomment for PE-target
   //std::string runnumber = "run383/383";

   // Time coincidence for the BGOs
   std::vector<int> timemin;
   std::vector<int> timemax;
   // Uncomment for Au-target
   timemin.push_back(-30);
   timemax.push_back(30);
   // Uncomment for PE-target
   //timemin.push_back(100);
   //timemax.push_back(1000);

   // Names of the files
   // Muon Entrance [main trigger]
   std::string fileMu = runnumber+"_muentrance_prep.txt";
   // Electron Vetos
   std::string fileVeto = runnumber+"_Electron_Vetos_prep2.txt";
   // BGO Clusters
   std::string fileBGO = runnumber+"_BGO_Clusters_prep.txt";


   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   

   //---------------------------------- Muon Entrance -------------------------------
   // Muon Entrance [trigger]
   std::ifstream fMu(fileMu);
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

   //-------------------------------- Electron Vetos --------------------------------
   std::ifstream fVeto(fileVeto);
   std::vector<double> vEvIDVeto;
   std::vector<double> vEdepVeto;
   std::vector<double> vTimeVeto;
   std::vector<double> vChanVeto;   
   // 34 = V1; 35 = V2; 36 = V3A; 37 = V3B; 38 = V4A; 39 = V4B;

   while (!fVeto.eof()) {
      double EvIDVeto, InstVeto, EdepVeto, TimeVeto, ChVeto;
      fVeto >> EvIDVeto >> InstVeto >> EdepVeto >> TimeVeto >> ChVeto;
      vEvIDVeto.push_back(EvIDVeto);
      vEdepVeto.push_back(EdepVeto);
      vTimeVeto.push_back(TimeVeto);
      vChanVeto.push_back(ChVeto);
   }
   vEvIDVeto.pop_back();
   vEdepVeto.pop_back();
   vTimeVeto.pop_back();
   vChanVeto.pop_back();
   fVeto.close();   

   //--------------------------------- BGO Clusters ---------------------------------
   std::ifstream fBGO(fileBGO);
   std::vector<double> vEvIDBGO; 
   std::vector<double> vEkeVBGO;
   std::vector<double> vTimeBGO;
   std::vector<double> vCluster;

   double kbgobacka = 1.74; double bbgobacka = 12.46;
   double kbgobackb = 1.94; double bbgobackb = 10.34;
   double kbgobackc = 1.82; double bbgobackc = 11.70;
   double kbgobackd = 1.86; double bbgobackd = 22.30;
   double kbgobacke = 1.88; double bbgobacke = 20.78;
   double kbgobackf = 2.65; double bbgobackf = 13.41;
   double kbgobackg = 1.92; double bbgobackg = 13.03;
   double kbgobackh = 2.00; double bbgobackh = 14.92;  
   double kbgobacki = 2.10; double bbgobacki = 13.37;
   double kbgobackj = 2.52; double bbgobackj = 13.16;
   double kbgofronta = 1.90; double bbgofronta = 24.51;
   double kbgofrontb = 1.81; double bbgofrontb = 34.33;
   double kbgofrontc = 1.90; double bbgofrontc = 32.27;
   double kbgofrontd = 2.00; double bbgofrontd = 50.30;
   double kbgofronte = 1.96; double bbgofronte = 82.73;
   double kbgofrontf = 1.95; double bbgofrontf = 33.43;
   double kbgofrontg = 1.80; double bbgofrontg = 32.41;
   double kbgofronth = 1.94; double bbgofronth = 27.70;
   while (!fBGO.eof()) {
      double EvIDBGO, InstBGO, EdepBGO, TimeBGO, ChBGO;
      fBGO >> EvIDBGO >> InstBGO >> EdepBGO >> TimeBGO >> ChBGO;
      if (EdepBGO < 100000) {
         vEvIDBGO.push_back(EvIDBGO);
         vTimeBGO.push_back(TimeBGO);
         if (ChBGO == 1) {
            vEkeVBGO.push_back(EdepBGO*kbgobacka+bbgobacka);
            vCluster.push_back(1);
         } else if (ChBGO == 2) {
            vEkeVBGO.push_back(EdepBGO*kbgobackb+bbgobackb);
            vCluster.push_back(1);
         } else if (ChBGO == 3) {
            vEkeVBGO.push_back(EdepBGO*kbgobackc+bbgobackc);
            vCluster.push_back(1);
         } else if (ChBGO == 4) {
            vEkeVBGO.push_back(EdepBGO*kbgobackd+bbgobackd);
            vCluster.push_back(1);
         } else if (ChBGO == 5) {
            vEkeVBGO.push_back(EdepBGO*kbgobacke+bbgobacke);
            vCluster.push_back(1);
         } else if (ChBGO == 6) {
            vEkeVBGO.push_back(EdepBGO*kbgobackf+bbgobackf);
            vCluster.push_back(1);
         } else if (ChBGO == 7) {
            vEkeVBGO.push_back(EdepBGO*kbgobackg+bbgobackg);
            vCluster.push_back(1);
         } else if (ChBGO == 8) {
            vEkeVBGO.push_back(EdepBGO*kbgobackh+bbgobackh);
            vCluster.push_back(1);
         } else if (ChBGO == 9) {
            vEkeVBGO.push_back(EdepBGO*kbgobacki+bbgobacki);
            vCluster.push_back(1);
         } else if (ChBGO == 10) {
            vEkeVBGO.push_back(EdepBGO*kbgobackj+bbgobackj);
            vCluster.push_back(1);
         } else if (ChBGO == 17) {
            vEkeVBGO.push_back(EdepBGO*kbgofronta+bbgofronta);
            vCluster.push_back(-1);
         } else if (ChBGO == 18) {
            vEkeVBGO.push_back(EdepBGO*kbgofrontb+bbgofrontb);
            vCluster.push_back(-1);
         } else if (ChBGO == 19) {
            vEkeVBGO.push_back(EdepBGO*kbgofrontc+bbgofrontc);
            vCluster.push_back(-1);
         } else if (ChBGO == 20) {
            vEkeVBGO.push_back(EdepBGO*kbgofrontd+bbgofrontd);
            vCluster.push_back(-1);
         } else if (ChBGO == 21) {
            vEkeVBGO.push_back(EdepBGO*kbgofronte+bbgofronte);
            vCluster.push_back(-1);
         } else if (ChBGO == 22) {
            vEkeVBGO.push_back(EdepBGO*kbgofrontf+bbgofrontf);
            vCluster.push_back(-1);
         } else if (ChBGO == 23) {
            vEkeVBGO.push_back(EdepBGO*kbgofrontg+bbgofrontg);
            vCluster.push_back(-1);
         } else {
            vEkeVBGO.push_back(EdepBGO*kbgofronth+bbgofronth);
            vCluster.push_back(-1);
         }
      }   
   }
   vEvIDBGO.pop_back(); 
   vTimeBGO.pop_back();
   vEkeVBGO.pop_back();
   vCluster.pop_back();
   fBGO.close();


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

   std::cout << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m---------------------- Matching --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;

   std::vector<double> BackClusterEn;
   std::vector<double> FrontClusterEn;
   std::vector<double> ClusterTm;
   std::vector<double> V1En;
   std::vector<double> V2En;
   std::vector<double> V3En;
   std::vector<double> V4En;
   std::vector<double> ElectronTm;

   double tmel = 50;

   for (int n=0; n<10000; n++) {
      double BackRunEn = 0.0;
      double FrontRunEn = 0.0;
      std::vector<double> RunTm;
      for (int k=0; k<50000; k++) {
         if (vEvIDBGO[k] == vEvIDTrig[n]) {
            if ((vTimeBGO[k] > timemin[0]) && (vTimeBGO[k] <= timemax[0])) {
               if (vEkeVBGO[k] > 100) {
                  RunTm.push_back(vTimeBGO[k]);
                  if (vCluster[k] > 0) {
                     BackRunEn += vEkeVBGO[k];
                  } else {
                     FrontRunEn += vEkeVBGO[k];
                  }
               }
            }
         }
      }
      BackClusterEn.push_back(BackRunEn);
      FrontClusterEn.push_back(FrontRunEn);
      if (RunTm.size() > 0) {
         ClusterTm.push_back(*std::min_element(RunTm.begin(),RunTm.end()));

         double V1RunEn = 0.0;
         double V2RunEn = 0.0;
         double V3RunEn = 0.0;
         double V4RunEn = 0.0;
         for (int l=0; l<30000; l++) {
            if (vEvIDVeto[l] == vEvIDTrig[n]) {
               if ((vTimeVeto[l] >= (ClusterTm[n]-tmel)) && (vTimeVeto[l] <= (ClusterTm[n]+tmel))) {
                  if (vChanVeto[l] == 34) V1RunEn += vEdepVeto[l];
                  if (vChanVeto[l] == 35) V2RunEn += vEdepVeto[l];
                  if (vChanVeto[l] == 36) V3RunEn += vEdepVeto[l];
                  if (vChanVeto[l] == 38) V4RunEn += vEdepVeto[l];
               }
            }
         }
         V1En.push_back(V1RunEn);
         V2En.push_back(V2RunEn);
         V3En.push_back(V3RunEn);
         V4En.push_back(V4RunEn);  
      }

      for (int m=0; m<30000; m++) {
         if (vEvIDVeto[m] == vEvIDTrig[n]) {
            if (vChanVeto[m] == 38) ElectronTm.push_back(vTimeVeto[m]);
         }
      }

   }


   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl; 

   TH1F *htmvetos = new TH1F("htmvetos","htmvetos",50,-100.0,200.0);
   for (int i=0; i<ElectronTm.size(); i++) htmvetos->Fill(ElectronTm[i]);
   TH1F *hclustertm = new TH1F("hclustertm","hclustertm",25,-40.0,60.0);
   for (int i=0; i<ClusterTm.size(); i++) hclustertm->Fill(ClusterTm[i]); 

   TCanvas *c = new TCanvas("c","c",800,600);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   htmvetos->SetTitle("");
   htmvetos->GetXaxis()->SetTitle("t_{Veto} [ns]");
   htmvetos->SetLineColor(kBlack);
   htmvetos->Draw();
   auto legend = new TLegend(0.8,0.8,0.96,0.96);
   legend->AddEntry(htmvetos,"Any veto","l");
   legend->Draw();


}

int main() {
   DetSys4();
   return 0;
}  
