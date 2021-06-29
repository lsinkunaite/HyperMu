/////////////////////////////////////////////////
//                                             //
//                  AntiCoin.C                 //
//                                             //                
//   Plots Efficieny of a veto for different   //
//   energies in the BGO.                      //
//                                             //
/////////////////////////////////////////////////


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
#include "TColor.h"
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TGraph2D.h"
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

void AntiCoin(){
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

   // Uncomment for Au-target
   std::string runnumber = "run373/373";

   // Time coincidence for the BGOs
   std::vector<int> timemin;
   std::vector<int> timemax;
   // Uncomment for Au-target
   timemin.push_back(-50);
   timemax.push_back(100);

   // Names of the files
   // Muon Entrance [main trigger]
   std::string fileMu = runnumber+"_muentrance_prep.txt";
   // Electron Vetos
   std::string fileVeto = runnumber+"_Electron_Vetos_prep2.txt";
   // BGO Clusters
   std::string fileBGO = runnumber+"_BGO_Clusters_prep2.txt";


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


   // Time window between veto and the cluster
   double tmelmin = -25; 
   double tmelmax = 25;

   int nmuons = 10000;

   int AntiCounter=0;
   int VetoCounter=0;
   int VBORCounter=0;
   int BackCounter=0;
   int FrontCounter=0;
   // BGOs
   std::vector<double> EvTm0;
   std::vector<double> EvTm400;
   std::vector<double> EvTm800;
   std::vector<double> EvTm1200;
   std::vector<double> EvTm1600;
   std::vector<double> EvTm2000;
   // Veto 3 && 4
   std::vector<double> VTm0;
   std::vector<double> VTm100;
   std::vector<double> VTm200;
   std::vector<double> VTm300;
   std::vector<double> VTm400;
   std::vector<double> VTm500;


   for (int n=0; n<nmuons; n++) {
      double BackRunEn = 0.0;
      double FrontRunEn = 0.0;
      double V34En = 0.0;
      std::vector<double> RunTm;
      std::vector<double> RunEn;
      std::vector<double> VetoTm;
      std::vector<double> VetoEn;
      for (int k=0; k<50000; k++) {
         if (vEvIDBGO[k] == vEvIDTrig[n]) {
            if ((vTimeBGO[k] > timemin[0]) && (vTimeBGO[k] <= timemax[0])) {
               //if (vEkeVBGO[k] > 100) {
               if (vEkeVBGO[k] > 0) {
                  RunTm.push_back(vTimeBGO[k]);
                  RunEn.push_back(vEkeVBGO[k]);
                  if (vCluster[k] > 0) {
                     BackRunEn += vEkeVBGO[k];
                  } else {
                     FrontRunEn += vEkeVBGO[k];
                  }
               }
            }
         }
 
         if ((vEvIDVeto[k] == vEvIDTrig[n]) && (vTimeVeto[k] > timemin[0]) && (vTimeVeto[k] <= timemax[0]) && ((vChanVeto[k] == 36) || (vChanVeto[k] == 38))) {
            VetoTm.push_back(vTimeVeto[k]);
            VetoEn.push_back(vEdepVeto[k]);
            V34En += vEdepVeto[k];
            //std::cout << "ID = " << vEvIDVeto[k] << ", Edep = " << vEdepVeto[k] << std::endl;
         }     
      }

      if (VetoTm.size() > 0) {
         double vttime = *std::min_element(VetoTm.begin(),VetoTm.end());
         if (V34En > 0) {
            VetoCounter++;
            VTm0.push_back(vttime);
         }
         if (V34En > 100) VTm100.push_back(vttime);
         if (V34En > 200) VTm200.push_back(vttime);
         if (V34En > 300) VTm300.push_back(vttime);
         if (V34En > 400) VTm400.push_back(vttime);
         if (V34En > 500) VTm500.push_back(vttime);
         
      }      


      if (RunTm.size() > 0) {
         BackClusterEn.push_back(BackRunEn);
         FrontClusterEn.push_back(FrontRunEn);        
         ClusterTm.push_back(*std::min_element(RunTm.begin(),RunTm.end()));
         double tttime = *std::min_element(RunTm.begin(),RunTm.end());

         if ((BackRunEn+FrontRunEn) > 100) {
            AntiCounter++; 
            EvTm0.push_back(tttime);
         }

         if ((BackRunEn+FrontRunEn) > 400) EvTm400.push_back(tttime);
         if ((BackRunEn+FrontRunEn) > 800) {
            //AntiCounter++;
            EvTm800.push_back(tttime);
            //std::cout << "t = " << tttime << ", E = " << BackRunEn+FrontRunEn << std::endl;
         }
         if ((BackRunEn+FrontRunEn) > 1200) EvTm1200.push_back(tttime);
         if ((BackRunEn+FrontRunEn) > 1600) EvTm1600.push_back(tttime);
         if ((BackRunEn+FrontRunEn) > 2000) EvTm2000.push_back(tttime);


      } else if (VetoTm.size() > 0) {
         double vbtime = *std::min_element(VetoTm.begin(),VetoTm.end());
         if (V34En > 50) VBORCounter++;
      }

   }
   std::cout << "Anticounter = " << AntiCounter << std::endl;
   std::cout << "Vetocounter = " << VetoCounter << std::endl;
   std::cout << "VBORcounter = " << VBORCounter << std::endl;


   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl; 

   // BGOs
   TH1F *hevtime0 = new TH1F("hevtime0","hevtime0",50,-80,120);
   TH1F *hevtime400 = new TH1F("hevtime400","hevtime400",50,-80,120);
   TH1F *hevtime800 = new TH1F("hevtime800","hevtime800",50,-80,120);
   TH1F *hevtime1200 = new TH1F("hevtime1200","hevtime1200",50,-80,120);
   TH1F *hevtime1600 = new TH1F("hevtime1600","hevtime1600",50,-80,120);
   TH1F *hevtime2000 = new TH1F("hevtime2000","hevtime2000",50,-80,120);
   for (int i=0; i<EvTm0.size(); i++) hevtime0->Fill(EvTm0[i]);
   for (int i=0; i<EvTm400.size(); i++) hevtime400->Fill(EvTm400[i]);
   for (int i=0; i<EvTm800.size(); i++) hevtime800->Fill(EvTm800[i]);
   for (int i=0; i<EvTm1200.size(); i++) hevtime1200->Fill(EvTm1200[i]);
   for (int i=0; i<EvTm1600.size(); i++) hevtime1600->Fill(EvTm1600[i]);
   for (int i=0; i<EvTm2000.size(); i++) hevtime2000->Fill(EvTm2000[i]);
   
   // Vetos
   TH1F *hvtime0 = new TH1F("hvtime0","hvtime0",50,-80,120);
   TH1F *hvtime100 = new TH1F("hvtime100","hvtime100",50,-80,120);
   TH1F *hvtime200 = new TH1F("hvtime200","hvtime200",50,-80,120);
   TH1F *hvtime300 = new TH1F("hvtime300","hvtime300",50,-80,120);
   TH1F *hvtime400 = new TH1F("hvtime400","hvtime400",50,-80,120);
   TH1F *hvtime500 = new TH1F("hvtime500","hvtime500",50,-80,120);
   for (int i=0; i<VTm0.size(); i++) hvtime0->Fill(VTm0[i]);
   for (int i=0; i<VTm100.size(); i++) hvtime100->Fill(VTm100[i]);
   for (int i=0; i<VTm200.size(); i++) hvtime200->Fill(VTm200[i]);
   for (int i=0; i<VTm300.size(); i++) hvtime300->Fill(VTm300[i]);
   for (int i=0; i<VTm400.size(); i++) hvtime400->Fill(VTm400[i]);
   for (int i=0; i<VTm500.size(); i++) hvtime500->Fill(VTm500[i]);

   // BGOs
   TCanvas *cevtime = new TCanvas("cevtime","cevtime",800,600);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   hevtime0->SetTitle("");
   hevtime0->GetXaxis()->SetTitle("t [ns]");
   hevtime0->SetLineColor(kBlack);
   hevtime0->Draw();
   hevtime400->SetLineColor(kTeal-5);
   hevtime400->Draw("same");
   hevtime800->SetLineColor(kRed-5);
   hevtime800->Draw("same");
   hevtime1200->SetLineColor(kOrange-3);
   hevtime1200->Draw("same");
   hevtime1600->SetLineColor(kViolet-5);
   hevtime1600->Draw("same");
   hevtime2000->SetLineColor(kAzure+1);
   hevtime2000->Draw("same");
   auto legend = new TLegend(0.7,0.72,0.94,0.94);
   legend->AddEntry(hevtime2000,"E_{Cluster} > 2000 keV","l");
   legend->AddEntry(hevtime1600,"E_{Cluster} > 1600 keV","l");
   legend->AddEntry(hevtime1200,"E_{Cluster} > 1200 keV","l");
   legend->AddEntry(hevtime800,"E_{Cluster} > 800 keV","l");
   legend->AddEntry(hevtime400,"E_{Cluster} > 400 keV","l");
   legend->AddEntry(hevtime0,"E_{Cluster} > 0 keV","l");
   legend->Draw();
   cevtime->SaveAs("AnticoincidenceBGOs.pdf");

   // Vetos
   TCanvas *cvtime = new TCanvas("cvtime","cvtime",800,600);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   hvtime0->SetTitle("");
   hvtime0->GetXaxis()->SetTitle("t [ns]");
   hvtime0->SetLineColor(kBlack);
   hvtime0->Draw();
   hvtime100->SetLineColor(kTeal-5);
   hvtime100->Draw("same");
   hvtime200->SetLineColor(kRed-5);
   hvtime200->Draw("same");
   hvtime300->SetLineColor(kOrange-3);
   hvtime300->Draw("same");
   hvtime400->SetLineColor(kViolet-5);
   hvtime400->Draw("same");
   hvtime500->SetLineColor(kAzure+1);
   hvtime500->Draw("same");
   auto vlegend = new TLegend(0.7,0.72,0.94,0.94);
   vlegend->AddEntry(hvtime500,"E_{V3 + V4} > 500 adc","l"); 
   vlegend->AddEntry(hvtime400,"E_{V3 + V4} > 400 adc","l");
   vlegend->AddEntry(hvtime300,"E_{V3 + V4} > 300 adc","l");
   vlegend->AddEntry(hvtime200,"E_{V3 + V4} > 200 adc","l");
   vlegend->AddEntry(hvtime100,"E_{V3 + V4} > 100 adc","l");
   vlegend->AddEntry(hvtime0,"E_{V3 + V4} > 0 adc","l");
   vlegend->Draw();
   cvtime->SaveAs("AnticoincidenceVetos.pdf");



}

int main() {
   AntiCoin();
   return 0;
}  
