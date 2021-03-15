///////////////////////////////////////////////
//                                           //
//               VetoEff4.C                  //
//                                           //                
//  Compares the energy and the time of the  //
//  matched electron veto and BGO for the    //
//  runs with the gold and with the plastic  //
//  target.                                  //
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

void VetoEff4(){
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

   std::string runnumberpe = "run530/530";
   std::string runnumberau = "run549/549";
  
   std::vector<int> timemin;
   std::vector<int> timemax;

   timemin.push_back(100);
   timemax.push_back(1000);
   timemin.push_back(-30);
   timemax.push_back(30);
   double toffsetV4A = 3.0;   

   // Names of the files
   // Electron Vetos
   std::string fileVetoPe = runnumberpe+"_Veto4_A_prep.txt";
   std::string fileVetoAu = runnumberau+"_Veto4_A_prep.txt";
   // BGOs
   std::string fileBGOPe = runnumberpe+"_BGO_Back_A_prep.txt";
   std::string fileBGOAu = runnumberau+"_BGO_Back_A_prep.txt";

   // Vectors with detector names
   std::vector<std::string> BGOfiles;
   std::vector<std::string> Vetofiles;

   // Electron Vetos
   Vetofiles.push_back(fileVetoPe);
   Vetofiles.push_back(fileVetoAu);
   // BGOs
   BGOfiles.push_back(fileBGOPe);
   BGOfiles.push_back(fileBGOAu);


   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   

   // Veto4_A PE-target
   std::ifstream fVetoPe(Vetofiles[0]);
   std::vector<double> vEvIDVPe;
   std::vector<double> vEdepVPe;
   std::vector<double> vTimeVPe;
   while (!fVetoPe.eof()) {  
      double EvIDVPe, InstVPe, EdepVPe, TimeVPe;
      fVetoPe >> EvIDVPe >> InstVPe >> EdepVPe >> TimeVPe;
      vEvIDVPe.push_back(EvIDVPe);
      vEdepVPe.push_back(EdepVPe);
      vTimeVPe.push_back(TimeVPe+toffsetV4A);
   }
   vEvIDVPe.pop_back();
   vEdepVPe.pop_back();
   vTimeVPe.pop_back();
   fVetoPe.close();


   // Veto4_A Au-target
   std::ifstream fVetoAu(Vetofiles[1]);
   std::vector<double> vEvIDVAu;
   std::vector<double> vEdepVAu;
   std::vector<double> vTimeVAu;
   while (!fVetoAu.eof()) {
      double EvIDVAu, InstVAu, EdepVAu, TimeVAu;
      fVetoAu >> EvIDVAu >> InstVAu >> EdepVAu >> TimeVAu;
      vEvIDVAu.push_back(EvIDVAu);
      vEdepVAu.push_back(EdepVAu);
      vTimeVAu.push_back(TimeVAu+toffsetV4A);
   }
   vEvIDVAu.pop_back();
   vEdepVAu.pop_back();
   vTimeVAu.pop_back();
   fVetoAu.close();


   // BGO_Back_A PE-target
   std::ifstream fBGOPe(BGOfiles[0]);
   std::vector<double> vEvIDBGOPe;
   std::vector<double> vEdepBGOPe;
   std::vector<double> vEkeVBGOPe;
   std::vector<double> vTimeBGOPe;
   double kbgobacka = 1.74;
   double bbgobacka = 12.46;
   while (!fBGOPe.eof()) {
      double EvIDBGOPe, InstBGOPe, EdepBGOPe, TimeBGOPe;
      fBGOPe >> EvIDBGOPe >> InstBGOPe >> EdepBGOPe >> TimeBGOPe;
      double EkeVBGOPe;
      vEvIDBGOPe.push_back(EvIDBGOPe);
      vEdepBGOPe.push_back(EdepBGOPe);
      vTimeBGOPe.push_back(TimeBGOPe); 
      EkeVBGOPe = EdepBGOPe*kbgobacka+bbgobacka;
      vEkeVBGOPe.push_back(EkeVBGOPe);     
   }
   vEvIDBGOPe.pop_back();
   vEdepBGOPe.pop_back();
   vTimeBGOPe.pop_back();
   vEkeVBGOPe.pop_back();
   fBGOPe.close();


   // BGO_Back_A Au-target
   std::ifstream fBGOAu(BGOfiles[1]);
   std::vector<double> vEvIDBGOAu;
   std::vector<double> vEdepBGOAu;
   std::vector<double> vEkeVBGOAu;
   std::vector<double> vTimeBGOAu;
   while (!fBGOAu.eof()) {
      double EvIDBGOAu, InstBGOAu, EdepBGOAu, TimeBGOAu;
      fBGOAu >> EvIDBGOAu >> InstBGOAu >> EdepBGOAu >> TimeBGOAu;
      double EkeVBGOAu;
      vEvIDBGOAu.push_back(EvIDBGOAu);
      vEdepBGOAu.push_back(EdepBGOAu);
      vTimeBGOAu.push_back(TimeBGOAu);      
      EkeVBGOAu = EdepBGOAu*kbgobacka+bbgobacka;
      vEkeVBGOAu.push_back(EkeVBGOAu);      
   }
   vEvIDBGOAu.pop_back();
   vEdepBGOAu.pop_back(); 
   vTimeBGOAu.pop_back();
   vEkeVBGOAu.pop_back();
   fBGOAu.close();


   std::cout << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m--------------------- Reading II -------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;

   // Veto_4_A PE-target
   std::vector<double> vInstVPe; // Vector of repeating instances
   int EvIDVPe;
   for (int s=0; s<vEvIDVPe.size(); s++) {
      if ((s > 0) && (s < (vEvIDVPe.size()-1))) {
         if ((vEvIDVPe[s] == vEvIDVPe[s+1]) || (vEvIDVPe[s] == vEvIDVPe[s-1])) {
            vInstVPe.push_back(1);
         } else {
            vInstVPe.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDVPe[s] == vEvIDVPe[s+1]) {
            vInstVPe.push_back(1);
         } else {
            vInstVPe.push_back(0);
         }
      } else if (vEvIDVPe[s] == vEvIDVPe[s-1]) {
         vInstVPe.push_back(1);
      } else {
         vInstVPe.push_back(0);
      }
   }


   // Veto_4_A Au-target
   std::vector<double> vInstVAu; // Vector of repeating instances
   int EvIDVAu;
   for (int s=0; s<vEvIDVAu.size(); s++) {
      if ((s > 0) && (s < (vEvIDVAu.size()-1))) {
         if ((vEvIDVAu[s] == vEvIDVAu[s+1]) || (vEvIDVAu[s] == vEvIDVAu[s-1])) {
            vInstVAu.push_back(1);
         } else {
            vInstVAu.push_back(0);
         }
      } else if (s == 0) {
         if (vEvIDVAu[s] == vEvIDVAu[s+1]) {
            vInstVAu.push_back(1);
         } else {
            vInstVAu.push_back(0);
         }
      } else if (vEvIDVAu[s] == vEvIDVAu[s-1]) {
         vInstVAu.push_back(1);
      } else {
         vInstVAu.push_back(0);
      }
   }


   // BGO_Back_A PE-target
   std::vector<double> vEnBGOPe;
   std::vector<double> vIDBGOPe;
   std::vector<double> vTmBGOPe;
   for (int s=0; s<vTimeBGOPe.size(); s++) {
    //  if ((vTimeBGOPe[s] > timemin[0]) && (vTimeBGOPe[s] <timemax[0])) {
         if (vEkeVBGOPe[s] < 100000) {
            vIDBGOPe.push_back(vEvIDBGOPe[s]);
            vEnBGOPe.push_back(vEkeVBGOPe[s]);
            vTmBGOPe.push_back(vTimeBGOPe[s]);
         }
     // }
   }


   // BGO_Back_A Au-target
   std::vector<double> vEnBGOAu;
   std::vector<double> vIDBGOAu;
   std::vector<double> vTmBGOAu;
   for (int s=0; s<vTimeBGOAu.size(); s++) {
      //if ((vTimeBGOAu[s] > timemin[1]) && (vTimeBGOAu[s] <timemax[1])) {
         if (vEkeVBGOAu[s] < 100000) {
            vIDBGOAu.push_back(vEvIDBGOAu[s]);
            vEnBGOAu.push_back(vEkeVBGOAu[s]);
            vTmBGOAu.push_back(vTimeBGOAu[s]);
         }
     // }
   }


   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

   TH1F *hVetoTmPe = new TH1F("hVetoTmPe","hVetoTmPe",50,-100.0,1500.0); // Time of Veto PE-target
   TH1F *hVetoTmAu = new TH1F("hVetoTmAu","hVetoTmAu",50,-100.0,1500.0); // Time of Veto Au-target
   TH1F *hVetoEnPe = new TH1F("hVetoEnPe","hVetoEnPe",50,0.0,12.0); // Energy of Veto PE-target
   TH1F *hVetoEnAu = new TH1F("hVetoEnAu","hVetoEnAu",50,0.0,12.0); // Energy of Veto Au-target
   TH1F *hBGOTmPe = new TH1F("hBGOTmPe","hBGOTmPe",50,-100.0,1500.0); // Time of BGO PE-target
   TH1F *hBGOTmAu = new TH1F("hBGOTmAu","hBGOTmAu",50,-100.0,1500.0); // Time of BGO Au-target
   TH1F *hBGOEnPe = new TH1F("hBGOEnPe","hBGOEnPe",50,0.0,26.0); // Energy of BGO PE-target
   TH1F *hBGOEnAu = new TH1F("hBGOEnAu","hBGOEnAu",50,0.0,26.0); // Energy of BGO Au-target


   for (int i=0; i<vTimeVPe.size(); i++) hVetoTmPe->Fill(vTimeVPe[i]);
   for (int i=0; i<vTimeVAu.size(); i++) hVetoTmAu->Fill(vTimeVAu[i]);
   for (int i=0; i<vEdepVPe.size(); i++) hVetoEnPe->Fill(vEdepVPe[i]/1000.0);
   for (int i=0; i<vEdepVAu.size(); i++) hVetoEnAu->Fill(vEdepVAu[i]/1000.0);
   for (int i=0; i<vTmBGOPe.size(); i++) hBGOTmPe->Fill(vTmBGOPe[i]);
   for (int i=0; i<vTmBGOAu.size(); i++) hBGOTmAu->Fill(vTmBGOAu[i]);
   for (int i=0; i<vEnBGOPe.size(); i++) hBGOEnPe->Fill(vEnBGOPe[i]/1000.0);
   for (int i=0; i<vEnBGOAu.size(); i++) hBGOEnAu->Fill(vEnBGOAu[i]/1000.0);

/*
   // Exponential fit to extract the lifetimes
   // PE-target Veto
   TF1 *g1 = new TF1("g1","expo",100,1400);
   hVetoTmPe->Fit(g1,"R");
   std::cout << "PE: tau = " << -1/(g1->GetParameter(1)) << std::endl;
   // Au-target Veto
   TF1 *g2 = new TF1("g2","expo",50,450);
   hVetoTmAu->Fit(g2,"R");
   std::cout << "Au: tau = " << -1/(g2->GetParameter(1)) << std::endl;
   // PE-target BGO
   TF1 *g3 = new TF1("g3","expo",150,1400);
   hBGOTmPe->Fit(g3,"R");
   std::cout << "PE: tau = " << -1/(g3->GetParameter(1)) << std::endl;
   // Au-target BGO
   TF1 *g4 = new TF1("g4","expo",40,350);
   hBGOTmAu->Fit(g4,"R");
   std::cout << "Au: tau = " << -1/(g4->GetParameter(1)) << std::endl;
*/
/*
   // Time comparison for PE, Au for Veto_4_A
   TCanvas *c = new TCanvas("c","c",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hVetoTmAu->SetTitle("");
   hVetoTmAu->GetXaxis()->SetTitle("t [ns]");
   hVetoTmAu->SetLineWidth(3);
   hVetoTmAu->SetLineColor(kGray+3);
   hVetoTmAu->SetFillStyle(3003);
   hVetoTmAu->SetFillColorAlpha(kViolet-5,0.7);
   hVetoTmAu->Draw();
   hVetoTmPe->SetLineWidth(3);
   hVetoTmPe->SetLineColor(kGray+3);
   hVetoTmPe->SetFillStyle(3013);
   hVetoTmPe->SetFillColorAlpha(kTeal-5,0.5);
   hVetoTmPe->Draw("same");
   auto lVetoTm = new TLegend(0.8,0.76,0.92,0.93); 
   lVetoTm->AddEntry(hVetoTmPe,"PE","f");
   lVetoTm->AddEntry(hVetoTmAu,"Au", "f");
   lVetoTm->Draw();
   c->SaveAs("TmV4A_Au_PE.pdf");

   // Energy comparison for PE, Au for Veto_4_A
   TCanvas *d = new TCanvas("d","d",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hVetoEnAu->SetTitle("");
   hVetoEnAu->GetXaxis()->SetTitle("E [kadc]");
   hVetoEnAu->SetLineWidth(3);
   hVetoEnAu->SetLineColor(kGray+3);
   //hVetoEnAu->SetFillStyle(3003);
   hVetoEnAu->SetFillColorAlpha(kViolet-5,0.7);
   hVetoEnAu->Draw();
   hVetoEnPe->SetLineWidth(3);
   hVetoEnPe->SetLineColor(kGray+3);
   //hVetoEnPe->SetFillStyle(3013);
   hVetoEnPe->SetFillColorAlpha(kTeal-5,0.5);
   hVetoEnPe->Draw("same");
   auto lVetoEn = new TLegend(0.80,0.76,0.92,0.93);
   lVetoEn->AddEntry(hVetoEnPe,"PE","f");
   lVetoEn->AddEntry(hVetoEnAu,"Au", "f");
   lVetoEn->Draw();
   d->SaveAs("EnV4A_Au_PE.pdf");
*/
   // Time comparison for PE, Au for BGO
   TCanvas *e = new TCanvas("e","e",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hBGOTmAu->SetTitle("");
   hBGOTmAu->GetXaxis()->SetTitle("t [ns]");
   hBGOTmAu->GetYaxis()->SetRangeUser(1,2e4);
   hBGOTmAu->SetLineWidth(3);
   hBGOTmAu->SetLineColor(kGray+3);
   //hBGOTmAu->SetFillStyle(3003);
   hBGOTmAu->SetFillColorAlpha(kViolet-5,0.7);
   hBGOTmAu->Draw();
   hBGOTmPe->SetLineWidth(3);
   hBGOTmPe->SetLineColor(kGray+3);
   //hBGOTmPe->SetFillStyle(3013);
   hBGOTmPe->SetFillColorAlpha(kTeal-5,0.5);
   hBGOTmPe->Draw("same");
   auto lBGOTm = new TLegend(0.8,0.76,0.92,0.93);
   lBGOTm->AddEntry(hBGOTmPe,"PE","f");
   lBGOTm->AddEntry(hBGOTmAu,"Au", "f");
   lBGOTm->Draw();
   e->SaveAs("TmBGO_Au_PE.pdf");

   // Energy comparison for PE, Au for BGO
   TCanvas *f = new TCanvas("f","f",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hBGOEnAu->SetTitle("");
   hBGOEnAu->GetXaxis()->SetTitle("E [MeV]");
   hBGOEnAu->SetLineWidth(3);
   hBGOEnAu->SetLineColor(kGray+3);
   //hBGOEnAu->SetFillStyle(3003);
   hBGOEnAu->SetFillColorAlpha(kViolet-5,0.7);
   hBGOEnAu->Draw();
   hBGOEnPe->SetLineWidth(3);
   hBGOEnPe->SetLineColor(kGray+3);
   //hBGOEnPe->SetFillStyle(3013);
   hBGOEnPe->SetFillColorAlpha(kTeal-5,0.5);
   hBGOEnPe->Draw("same");
   auto lBGOEn = new TLegend(0.80,0.76,0.92,0.93);
   lBGOEn->AddEntry(hBGOEnPe,"PE","f");
   lBGOEn->AddEntry(hBGOEnAu,"Au", "f");
   lBGOEn->Draw();
   f->SaveAs("EnBGO_Au_PE.pdf");



}

int main() {
   VetoEff4();
   return 0;
} 
 
