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

void DetSys5() {
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
   gStyle->SetPadRightMargin(0.18);
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
   
   // Au-target
   std::string runnumberau = "run373/373";
   // PE-target
   std::string runnumberpe = "run383/383";

   std::string fileVetoau = runnumberau+"_Electron_Vetos_prep.txt";
   std::string fileVetope = runnumberpe+"_Veto2_prep.txt";
   std::string fileMuau = runnumberau+"_muentrance_prep.txt";
   std::string fileMupe = runnumberpe+"_muentrance_prep.txt";

   std::vector<int> timemin;
   std::vector<int> timemax;
   timemin.push_back(400);
   timemax.push_back(1000);
   timemin.push_back(-5000);
   timemax.push_back(-3000);


   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m------------------------ Reading -------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;

   // Muon Entrance [trigger] - Au
   std::ifstream fMuau(fileMuau);
   std::vector<double> vEvIDMuau;
   std::vector<double> vEdepMuau;
   std::vector<double> vTimeMuau;
   while (!fMuau.eof()) {
      double EvIDMuau, InstMuau, EdepMuau, TimeMuau;
      fMuau >> EvIDMuau >> InstMuau >> EdepMuau >> TimeMuau;
      vEvIDMuau.push_back(EvIDMuau);
      vEdepMuau.push_back(EdepMuau);
      vTimeMuau.push_back(TimeMuau);
   }
   vEvIDMuau.pop_back();
   vEdepMuau.pop_back();
   vTimeMuau.pop_back();
   fMuau.close();

   // Muon Entrance [trigger] - PE
   std::ifstream fMupe(fileMupe);
   std::vector<double> vEvIDMupe;
   std::vector<double> vEdepMupe;
   std::vector<double> vTimeMupe;
   while (!fMupe.eof()) {
      double EvIDMupe, InstMupe, EdepMupe, TimeMupe;
      fMupe >> EvIDMupe >> InstMupe >> EdepMupe >> TimeMupe;
      vEvIDMupe.push_back(EvIDMupe);
      vEdepMupe.push_back(EdepMupe);
      vTimeMupe.push_back(TimeMupe);
   }  
   vEvIDMupe.pop_back();
   vEdepMupe.pop_back();
   vTimeMupe.pop_back();
   fMupe.close();

   // Electron Vetos - Au
   std::ifstream fVetoau(fileVetoau);
   std::vector<double> vEvIDVetoau;
   std::vector<double> vEdepVetoau;
   std::vector<double> vTimeVetoau;
   std::vector<double> vChanVetoau;
   while (!fVetoau.eof()) {
      double EvIDVetoau, InstVetoau, EdepVetoau, TimeVetoau, ChVetoau;
      fVetoau >> EvIDVetoau >> InstVetoau >> EdepVetoau >> TimeVetoau >> ChVetoau;
      vEvIDVetoau.push_back(EvIDVetoau);
      vEdepVetoau.push_back(EdepVetoau);
      vTimeVetoau.push_back(TimeVetoau);
      vChanVetoau.push_back(ChVetoau);
   }
   vEvIDVetoau.pop_back();
   vEdepVetoau.pop_back();
   vTimeVetoau.pop_back();
   vChanVetoau.pop_back();
   fVetoau.close();

   // Electron Vetos - PE
   std::ifstream fVetope(fileVetope);
   std::vector<double> vEvIDVetope;
   std::vector<double> vEdepVetope;
   std::vector<double> vTimeVetope;
   std::vector<double> vChanVetope;
   while (!fVetope.eof()) {
      //double EvIDVetope, InstVetope, EdepVetope, TimeVetope, ChVetope;
      //fVetope >> EvIDVetope >> InstVetope >> EdepVetope >> TimeVetope >> ChVetope;
      double EvIDVetope, InstVetope, EdepVetope, TimeVetope;
      fVetope >> EvIDVetope >> InstVetope >> EdepVetope >> TimeVetope;
      vEvIDVetope.push_back(EvIDVetope);
      vEdepVetope.push_back(EdepVetope);
      vTimeVetope.push_back(TimeVetope);
      //vChanVetope.push_back(ChVetope);
   }
   vEvIDVetope.pop_back();
   vEdepVetope.pop_back();
   vTimeVetope.pop_back();
   //vChanVetope.pop_back();
   fVetope.close(); 


   std::cout << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m----------------------- Reading II -----------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;

   // Muon Entrance [trigger] - Au
   std::vector<double> vTimeTrigau;
   std::vector<double> vEdepTrigau;
   std::vector<double> vEvIDTrigau;
   int EvIDMuau;
   for (int s=0; s<vEvIDMuau.size(); s++) {
      if (vTimeMuau[s] == 0) {
         vEvIDTrigau.push_back(vEvIDMuau[s]);
         vEdepTrigau.push_back(vEdepMuau[s]);
         vTimeTrigau.push_back(vTimeMuau[s]);
      }
   }

   // Muon Entrance [trigger] - PE
   std::vector<double> vTimeTrigpe;
   std::vector<double> vEdepTrigpe;
   std::vector<double> vEvIDTrigpe;
   int EvIDMupe;
   for (int s=0; s<vEvIDMupe.size(); s++) {
      if (vTimeMupe[s] == 0) {
         vEvIDTrigpe.push_back(vEvIDMupe[s]);
         vEdepTrigpe.push_back(vEdepMupe[s]);
         vTimeTrigpe.push_back(vTimeMupe[s]);
      }  
   }  

   // Veto 1 studies
   TH1F *hveto1au = new TH1F("hveto1au","hveto1au",100,0,5);
   TH1F *hveto1pe = new TH1F("hveto1pe","hveto1pe",100,0,5);

   // Veto 2 studies
   TH1F *hveto2au = new TH1F("hveto2au","hveto2au",100,0,8);
   TH1F *hveto2pe = new TH1F("hveto2pe","hveto2pe",100,0,8);

   for (int i=0; i<100000; i++) { // muon loop
      for (int j=0; j<200000; j++) { // el-veto loop
         if (vEvIDVetoau[j] == vEvIDTrigau[i]) {
     /*       // Au-loop
            if ((vChanVetoau[j] == 35) && (vTimeVetoau[j] >= timemin[0]) && (vTimeVetoau[j] <= timemax[0])) {
               hveto2au->Fill(vEdepVetoau[j]/1000.0);
            }
            if ((vChanVetoau[j] == 34) && (vTimeVetoau[j] >= timemin[0]) && (vTimeVetoau[j] <= timemax[0])) {
               hveto1au->Fill(vEdepVetoau[j]/1000.0);
            }*/
            // PE-loop
            //if ((vChanVetope[j] == 35) && (vTimeVetope[j] >= timemin[1]) && (vTimeVetope[j] <= timemax[1])) {
               //hveto2pe->Fill(vEdepVetope[j]/1000.0);
            //}
            if ((vTimeVetope[j] >= timemin[1]) && (vTimeVetope[j] <= timemax[1])) {
               hveto2au->Fill(vEdepVetope[j]/1000.0);
            }
            if ((vTimeVetope[j] >= timemin[0]) && (vTimeVetope[j] <= timemax[0])) {
               hveto2pe->Fill(vEdepVetope[j]/1000.0);
            }
         }
      }
   }


   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------- Plotting -------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

   TCanvas *cv1 = new TCanvas("cv1","cv1",800,600);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   hveto1pe->SetTitle("Veto 1");
   hveto1pe->GetXaxis()->SetTitle("E_{Veto} [kadc]");
   hveto1pe->SetLineColor(kMagenta+3);
   hveto1pe->SetFillColorAlpha(kViolet-4,0.8);
   hveto1pe->Draw();
   hveto1au->SetLineColor(kOrange);
   hveto1au->SetFillColorAlpha(kYellow,0.9);
   hveto1au->Draw("same");
   //hveto1au->SetLineColor(kGreen-2);
   //hveto1au->SetFillColorAlpha(kTeal-5,0.6);
   //hveto1au->Draw("same");
   auto lv1 = new TLegend(0.8,0.8,0.96,0.96);
   lv1->AddEntry(hveto1pe,"PE","l");
   //lv1->AddEntry(hveto1au,"Au","l");
   lv1->AddEntry(hveto1au,"Beam","l");
   lv1->Draw();
   cv1->SaveAs("Veto1_beam_electrons.pdf");

   TCanvas *cv2 = new TCanvas("cv2","cv2",800,600);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   gStyle->SetCanvasPreferGL(1);
   hveto2pe->SetTitle("Veto 2");
   hveto2pe->GetXaxis()->SetTitle("E_{Veto} [kadc]");
   hveto2pe->SetLineColor(kMagenta+3);
   hveto2pe->SetFillColorAlpha(kViolet-4,0.8);
   hveto2pe->Draw();
   hveto2au->SetLineColor(kOrange);
   hveto2au->SetFillColorAlpha(kYellow,0.9);
   hveto2au->Draw("same");
   //hveto2au->SetLineColor(kGreen-2);
   //hveto2au->SetFillColorAlpha(kTeal-5,0.6);
   //hveto2au->Draw("same");
   auto lv2 = new TLegend(0.8,0.8,0.96,0.96);
   lv2->AddEntry(hveto2pe,"PE","l");
   //lv2->AddEntry(hveto2au,"Au","l");
   lv2->AddEntry(hveto2au,"Beam","l");
   lv2->Draw();
   cv2->SaveAs("Veto2_beam_electrons.pdf");

}

int main() {
   DetSys5();
   return 0;
}
