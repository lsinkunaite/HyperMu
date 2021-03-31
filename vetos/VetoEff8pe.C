//////////////////////////////////////////////
//                                          //
//               VetoEff8pe.C               //
//                                          //                
//  Plots 2D histograms in energy and time  //
//  for the matched veto and BGO.           //
//                                          //
//////////////////////////////////////////////


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

void VetoEff8pe(){
   // Some style definitions
   //gROOT->Reset();
   //gROOT->SetStyle("Plain");
   gStyle->SetPaperSize(26,20);
   gStyle->SetOptStat(1);
   gStyle->SetTitleXOffset(1.15);
   gStyle->SetTitleYOffset(1.30);
   gStyle->SetTitleBorderSize(1);
   gStyle->SetLegendBorderSize(1);
   //gStyle->SetPadBottomMargin(0.32);
   gStyle->SetPadBottomMargin(0.12);
   gStyle->SetPadLeftMargin(0.18);
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

   std::string runnumber = "run530/530";
  
   std::vector<int> timemin;
   std::vector<int> timemax;

   timemin.push_back(100);
   timemax.push_back(1000);
   double toffsetV4A = 3.0;   

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
      vTimeV4A.push_back(TimeV4A+toffsetV4A);
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


   std::vector<double> EnVetoMatched;
   std::vector<double> EnBGOMatched; 
   std::vector<double> Eveto02;
   std::vector<double> Eveto24;
   std::vector<double> Eveto46;
   std::vector<double> Eveto68;
   std::vector<double> Eveto810;
   std::vector<double> Eveto1012;
   std::vector<double> Eveto1214;
   std::vector<double> Eveto1416;
   std::vector<double> Eveto1618;
   std::vector<double> Eveto1820; 
   std::vector<double> Ebgo02;
   std::vector<double> Ebgo24;
   std::vector<double> Ebgo46;
   std::vector<double> Ebgo68;
   std::vector<double> Ebgo810;
   std::vector<double> Ebgo1012;
   std::vector<double> Ebgo1214;
   std::vector<double> Ebgo1416;
   std::vector<double> Ebgo1618;
   std::vector<double> Ebgo1820;
   
   for (int n=0; n<vIDBGOBackA.size(); n++) {
      for (int k=0; k<vEvIDV4A.size(); k++) {
         if (vEvIDV4A[k] == vIDBGOBackA[n]) {
            if (vInstV4A[k] == 0) {
               if ((vTimeV4A[k] >= (vTmBGOBackA[n]-50)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+450))) {
                  EnVetoMatched.push_back(vEdepV4A[k]);
                  EnBGOMatched.push_back(vEnBGOBackA[n]);
                  if (vEnBGOBackA[n] < 2000) {
                     Eveto02.push_back(vEdepV4A[k]);
                     Ebgo02.push_back(vEnBGOBackA[n]);
                  } else if ((vEnBGOBackA[n] >= 2000) && (vEnBGOBackA[n] < 4000)) {
                     Eveto24.push_back(vEdepV4A[k]);
                     Ebgo24.push_back(vEnBGOBackA[n]);
                  } else if ((vEnBGOBackA[n] >= 4000) && (vEnBGOBackA[n] < 6000)) {
                     Eveto46.push_back(vEdepV4A[k]);
                     Ebgo46.push_back(vEnBGOBackA[n]);
                  } else if ((vEnBGOBackA[n] >= 6000) && (vEnBGOBackA[n] < 8000)) {
                     Eveto68.push_back(vEdepV4A[k]);
                     Ebgo68.push_back(vEnBGOBackA[n]);
                  } else if ((vEnBGOBackA[n] >= 8000) && (vEnBGOBackA[n] < 10000)) {
                     Eveto810.push_back(vEdepV4A[k]);
                     Ebgo810.push_back(vEnBGOBackA[n]);
                  } else if ((vEnBGOBackA[n] >= 10000) && (vEnBGOBackA[n] < 12000)) {
                     Eveto1012.push_back(vEdepV4A[k]);
                     Ebgo1012.push_back(vEnBGOBackA[n]);
                  } else if ((vEnBGOBackA[n] >= 12000) && (vEnBGOBackA[n] < 14000)) {
                     Eveto1214.push_back(vEdepV4A[k]);
                     Ebgo1214.push_back(vEnBGOBackA[n]);
                  } else if ((vEnBGOBackA[n] >= 14000) && (vEnBGOBackA[n] < 16000)) {
                     Eveto1416.push_back(vEdepV4A[k]);
                     Ebgo1416.push_back(vEnBGOBackA[n]);
                  } else if ((vEnBGOBackA[n] >= 16000) && (vEnBGOBackA[n] < 18000)) {
                     Eveto1618.push_back(vEdepV4A[k]);
                     Ebgo1618.push_back(vEnBGOBackA[n]);
                  } else if ((vEnBGOBackA[n] >= 18000) && (vEnBGOBackA[n] < 20000)) {
                     Eveto1820.push_back(vEdepV4A[k]);
                     Ebgo1820.push_back(vEnBGOBackA[n]);
                  }
               }
            }
         }
      }
   }


   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

   TH1F *hveto02 = new TH1F("hveto02","hveto02",20,0,9.0);
   TH1F *hveto24 = new TH1F("hveto24","hveto24",20,0,9.0);
   TH1F *hveto46 = new TH1F("hveto46","hveto46",20,0,9.0);
   TH1F *hveto68 = new TH1F("hveto68","hveto68",20,0,9.0);
   TH1F *hveto810 = new TH1F("hveto810","hveto810",20,0,9.0);
   TH1F *hveto1012 = new TH1F("hveto1012","hveto1012",20,0,9.0);
   TH1F *hveto1214 = new TH1F("hveto1214","hveto1214",20,0,9.0);
   TH1F *hveto1416 = new TH1F("hveto1416","hveto1416",20,0,9.0);
   TH1F *hveto1618 = new TH1F("hveto1618","hveto1618",20,0,9.0);
   TH1F *hveto1820 = new TH1F("hveto1820","hveto1820",20,0,9.0);
   for (int i=0; i<Eveto02.size(); i++) hveto02->Fill(Eveto02[i]/1000.0);
   for (int i=0; i<Eveto24.size(); i++) hveto24->Fill(Eveto24[i]/1000.0);
   for (int i=0; i<Eveto46.size(); i++) hveto46->Fill(Eveto46[i]/1000.0);
   for (int i=0; i<Eveto68.size(); i++) hveto68->Fill(Eveto68[i]/1000.0);
   for (int i=0; i<Eveto810.size(); i++) hveto810->Fill(Eveto810[i]/1000.0);
   for (int i=0; i<Eveto1012.size(); i++) hveto1012->Fill(Eveto1012[i]/1000.0);
   for (int i=0; i<Eveto1214.size(); i++) hveto1214->Fill(Eveto1214[i]/1000.0);
   for (int i=0; i<Eveto1416.size(); i++) hveto1416->Fill(Eveto1416[i]/1000.0);
   for (int i=0; i<Eveto1618.size(); i++) hveto1618->Fill(Eveto1618[i]/1000.0);
   for (int i=0; i<Eveto1820.size(); i++) hveto1820->Fill(Eveto1820[i]/1000.0);
   
   TH1F *hbgo02 = new TH1F("hbgo02","hbgo02",20,0,22.0);
   TH1F *hbgo24 = new TH1F("hbgo24","hbgo24",20,0,22.0);
   TH1F *hbgo46 = new TH1F("hbgo46","hbgo46",20,0,22.0);
   TH1F *hbgo68 = new TH1F("hbgo68","hbgo68",20,0,22.0);
   TH1F *hbgo810 = new TH1F("hbgo810","hbgo810",20,0,22.0);
   TH1F *hbgo1012 = new TH1F("hbgo1012","hbgo1012",20,0,22.0);
   TH1F *hbgo1214 = new TH1F("hbgo1214","hbgo1214",20,0,22.0);
   TH1F *hbgo1416 = new TH1F("hbgo1416","hbgo1416",20,0,22.0);
   TH1F *hbgo1618 = new TH1F("hbgo1618","hbgo1618",20,0,22.0);
   TH1F *hbgo1820 = new TH1F("hbgo1820","hbgo1820",20,0,22.0);
   for (int i=0; i<Ebgo02.size(); i++) hbgo02->Fill(Ebgo02[i]/1000.0);
   for (int i=0; i<Ebgo24.size(); i++) hbgo24->Fill(Ebgo24[i]/1000.0);
   for (int i=0; i<Ebgo46.size(); i++) hbgo46->Fill(Ebgo46[i]/1000.0);
   for (int i=0; i<Ebgo68.size(); i++) hbgo68->Fill(Ebgo68[i]/1000.0);
   for (int i=0; i<Ebgo810.size(); i++) hbgo810->Fill(Ebgo810[i]/1000.0); 
   for (int i=0; i<Ebgo1012.size(); i++) hbgo1012->Fill(Ebgo1012[i]/1000.0);
   for (int i=0; i<Ebgo1214.size(); i++) hbgo1214->Fill(Ebgo1214[i]/1000.0);
   for (int i=0; i<Ebgo1416.size(); i++) hbgo1416->Fill(Ebgo1416[i]/1000.0);
   for (int i=0; i<Ebgo1618.size(); i++) hbgo1618->Fill(Ebgo1618[i]/1000.0);
   for (int i=0; i<Ebgo1820.size(); i++) hbgo1820->Fill(Ebgo1820[i]/1000.0);   

   double wintv02=0, wintv24=0, wintv46=0, wintv68=0, wintv810=0, wintv1012=0, wintv1214=0, wintv1416=0, wintv1618=0, wintv1820=0;
   double wintb02=0, wintb24=0, wintb46=0, wintb68=0, wintb810=0, wintb1012=0, wintb1214=0, wintb1416=0, wintb1618=0, wintb1820=0;

   for (int i=0; i<=20; i++) {
      wintv02 = wintv02 + ((hveto02->GetBinCenter(i))*(hveto02->GetBinContent(i)));
      wintb02 = wintb02 + ((hbgo02->GetBinCenter(i))*(hbgo02->GetBinContent(i)));
      wintv24 = wintv24 + ((hveto24->GetBinCenter(i))*(hveto24->GetBinContent(i)));
      wintb24 = wintb24 + ((hbgo24->GetBinCenter(i))*(hbgo24->GetBinContent(i)));
      wintv46 = wintv46 + ((hveto46->GetBinCenter(i))*(hveto46->GetBinContent(i)));
      wintb46 = wintb46 + ((hbgo46->GetBinCenter(i))*(hbgo46->GetBinContent(i)));
      wintv68 = wintv68 + ((hveto68->GetBinCenter(i))*(hveto68->GetBinContent(i)));
      wintb68 = wintb68 + ((hbgo68->GetBinCenter(i))*(hbgo68->GetBinContent(i)));
      wintv810 = wintv810 + ((hveto810->GetBinCenter(i))*(hveto810->GetBinContent(i)));
      wintb810 = wintb810 + ((hbgo810->GetBinCenter(i))*(hbgo810->GetBinContent(i)));
      wintv1012 = wintv1012 + ((hveto1012->GetBinCenter(i))*(hveto1012->GetBinContent(i)));
      wintb1012 = wintb1012 + ((hbgo1012->GetBinCenter(i))*(hbgo1012->GetBinContent(i)));
      wintv1214 = wintv1214 + ((hveto1214->GetBinCenter(i))*(hveto1214->GetBinContent(i)));
      wintb1214 = wintb1214 + ((hbgo1214->GetBinCenter(i))*(hbgo1214->GetBinContent(i)));
      wintv1416 = wintv1416 + ((hveto1416->GetBinCenter(i))*(hveto1416->GetBinContent(i)));
      wintb1416 = wintb1416 + ((hbgo1416->GetBinCenter(i))*(hbgo1416->GetBinContent(i)));
      wintv1618 = wintv1618 + ((hveto1618->GetBinCenter(i))*(hveto1618->GetBinContent(i)));
      wintb1618 = wintb1618 + ((hbgo1618->GetBinCenter(i))*(hbgo1618->GetBinContent(i)));
      wintv1820 = wintv1820 + ((hveto1820->GetBinCenter(i))*(hveto1820->GetBinContent(i)));
      wintb1820 = wintb1820 + ((hbgo1820->GetBinCenter(i))*(hbgo1820->GetBinContent(i)));
   }

   float IntRatio[10] = {};
   float EnBGO[10] = {};
   IntRatio[0] = wintv02/wintb02;
   IntRatio[1] = wintv24/wintb24;
   IntRatio[2] = wintv46/wintb46;
   IntRatio[3] = wintv68/wintb68;
   IntRatio[4] = wintv810/wintb810;
   IntRatio[5] = wintv1012/wintb1012;
   IntRatio[6] = wintv1214/wintb1214;
   IntRatio[7] = wintv1416/wintb1416;
   IntRatio[8] = wintv1618/wintb1618;
   IntRatio[9] = wintv1820/wintb1820;
   EnBGO[0] = 1.0;
   EnBGO[1] = 3.0;
   EnBGO[2] = 5.0;
   EnBGO[3] = 7.0;
   EnBGO[4] = 9.0;
   EnBGO[5] = 11.0;
   EnBGO[6] = 13.0;
   EnBGO[7] = 15.0;
   EnBGO[8] = 17.0;
   EnBGO[9] = 19.0;


   TCanvas *cgraph = new TCanvas("cgraph","cgraph",800,600);
   gPad->SetGrid(1,1);
   TGraph *grate = new TGraph(10,EnBGO,IntRatio);
   grate->SetTitle("");
   grate->GetXaxis()->SetTitle("E_{BGO} [MeV]");
   grate->GetYaxis()->SetTitle("N_{Veto}/N_{BGO}");
   grate->SetMarkerColor(kTeal-5);
   grate->SetMarkerSize(1.5);
   grate->SetMarkerStyle(22);
   grate->SetLineColor(kTeal-7);
   grate->Draw("ALP");


   hveto02->Scale(1/(hveto02->GetBinContent(hveto02->GetMaximumBin())),"nosw2");
   hveto24->Scale(1/(hveto24->GetBinContent(hveto24->GetMaximumBin())),"nosw2");
   hveto46->Scale(1/(hveto46->GetBinContent(hveto46->GetMaximumBin())),"nosw2");
   hveto68->Scale(1/(hveto68->GetBinContent(hveto68->GetMaximumBin())),"nosw2");
   hveto810->Scale(1/(hveto810->GetBinContent(hveto810->GetMaximumBin())),"nosw2");
   hveto1012->Scale(1/(hveto1012->GetBinContent(hveto1012->GetMaximumBin())),"nosw2");
   hveto1214->Scale(1/(hveto1214->GetBinContent(hveto1214->GetMaximumBin())),"nosw2");
   hveto1416->Scale(1/(hveto1416->GetBinContent(hveto1416->GetMaximumBin())),"nosw2");
   hveto1618->Scale(1/(hveto1618->GetBinContent(hveto1618->GetMaximumBin())),"nosw2");
   hveto1820->Scale(1/(hveto1820->GetBinContent(hveto1820->GetMaximumBin())),"nosw2");


   TCanvas *c = new TCanvas("c","c",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hveto02->SetTitle("");
   hveto02->GetXaxis()->SetTitle("E_{Veto} [kadc]");
   hveto02->SetLineColor(kRed);
   hveto02->Draw();
   hveto24->SetLineColor(kGreen-2);
   hveto24->Draw("same");
   hveto46->SetLineColor(kAzure-5);
   hveto46->Draw("same");
   hveto68->SetLineColor(kOrange+3);
   hveto68->Draw("same");
   hveto810->SetLineColor(kViolet-5);
   hveto810->Draw("same");
   hveto1012->SetLineColor(kBlack);
   hveto1012->Draw("same");
   hveto1214->SetLineColor(kSpring+7);
   hveto1214->Draw("same");
   hveto1416->SetLineColor(kPink+3);
   hveto1416->Draw("same");
   hveto1618->SetLineColor(kYellow-4);
   hveto1618->Draw("same");
   hveto1820->SetLineColor(kBlue-3);
   hveto1820->Draw("same");
   auto legend = new TLegend(0.67,0.75,0.87,0.95);
   legend->AddEntry(hveto02,"E_{BGO} #in [0, 2) MeV","l");
   legend->AddEntry(hveto24,"E_{BGO} #in [2, 4) MeV","l");
   legend->AddEntry(hveto46,"E_{BGO} #in [4, 6) MeV","l");
   legend->AddEntry(hveto68,"E_{BGO} #in [6, 8) MeV","l");
   legend->AddEntry(hveto810,"E_{BGO} #in [8, 10) MeV","l");
   legend->AddEntry(hveto1012,"E_{BGO} #in [10, 12) MeV","l");
   legend->AddEntry(hveto1214,"E_{BGO} #in [12, 14) MeV","l");
   legend->AddEntry(hveto1416,"E_{BGO} #in [14, 16) MeV","l");
   legend->AddEntry(hveto1618,"E_{BGO} #in [16, 18) MeV","l");
   legend->AddEntry(hveto1820,"E_{BGO} #in [18, 20) MeV","l");
   legend->Draw();


/*
   TH1F *hRatioMatchedVeto = new TH1F("hRatioMatchedVeto","hRatioMatchedVeto",100,0.0,30.0);
   TH1F *hRatioMatchedBGO = new TH1F("hRatioMatchedBGO","hRatioMatchedBGO",100,0.0,21.0);
   for (int i=0; i<EnVetoMatched.size(); i++) {
      hRatioMatchedVeto->Fill(EnVetoMatched[i]/EnBGOMatched[i]);
      hRatioMatchedBGO->Fill(EnBGOMatched[i]/EnVetoMatched[i]);
   }

   TCanvas *cvratio = new TCanvas("cvratio","cvratio",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hRatioMatchedVeto->SetTitle("");
   hRatioMatchedVeto->GetXaxis()->SetTitle("E_{Veto}/E_{BGO}");
   hRatioMatchedVeto->Draw();
  
   TCanvas *cbratio = new TCanvas("cbratio","cbratio",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   hRatioMatchedBGO->SetTitle("");
   hRatioMatchedBGO->GetXaxis()->SetTitle("E_{BGO}/E_{Veto}");
   hRatioMatchedBGO->Draw();
*/
/*
   TH2F *hRatioMatched2Veto = new TH2F("hRatioMatched2Veto","hRatioMatched2Veto",25,0,10.0,25,0,35.0);
   TH2F *hRatioMatched2BGO = new TH2F("hRatioMatched2BGO","hRatioMatched2BGO",25,0.0,22.0,25,0,21.0);
   for (int i=0; i <EnVetoMatched.size(); i++) {
      hRatioMatched2Veto->Fill((EnVetoMatched[i]/1000.0),EnVetoMatched[i]/EnBGOMatched[i]);
      hRatioMatched2BGO->Fill((EnBGOMatched[i]/1000.0),EnBGOMatched[i]/EnVetoMatched[i]);
   }

   TCanvas *cvratio2 = new TCanvas("cvratio2","cvratio2",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogz();
   hRatioMatched2Veto->SetTitle("");
   hRatioMatched2Veto->GetXaxis()->SetTitle("E_{Veto} [kadc]");
   hRatioMatched2Veto->GetYaxis()->SetTitle("E_{Veto}/E_{BGO}");
   hRatioMatched2Veto->Draw("COLZ");

   TCanvas *cbratio2 = new TCanvas("cbratio2","cbratio2",800,600);
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   gPad->SetLogz();
   hRatioMatched2BGO->SetTitle("");
   hRatioMatched2BGO->GetXaxis()->SetTitle("E_{BGO} [MeV]");
   hRatioMatched2BGO->GetYaxis()->SetTitle("E_{BGO}/E_{Veto}");
   hRatioMatched2BGO->Draw("COLZ");
*/

}

int main() {
   VetoEff8pe();
   return 0;
} 
 
