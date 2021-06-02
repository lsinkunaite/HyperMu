/////////////////////////////////////////////////
//                                             //
//                 DetSys4pe.C                 //
//                                             //                
//   Plots Efficieny of a veto for different   //
//   energies in the BGO.                      //
//                                             //
/////////////////////////////////////////////////


// I/O
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <fstream>
#include <numeric>
#include <string>
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

void DetSys4pe(){
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

   // Uncomment for PE-target
   std::string runnumber = "run383/383";

   // Time coincidence for the BGOs
   std::vector<int> timemin;
   std::vector<int> timemax;
   // Uncomment for PE-target
   timemin.push_back(100);
   timemax.push_back(2000);

   // Names of the files
   // Muon Entrance [main trigger]
   std::string fileMu = runnumber+"_muentrance_prep.txt";
   // Electron Vetos
   std::string fileVeto = runnumber+"_Electron_Vetos_prep2.txt";
   // BGO Clusters
   std::string fileBGO = runnumber+"_BGO_Clusters_prep2.txt";


   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m------------------------ Reading -------------------------\033[0m" << std::endl;
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
            vCluster.push_back(2);
         } else if (ChBGO == 3) {
            vEkeVBGO.push_back(EdepBGO*kbgobackc+bbgobackc);
            vCluster.push_back(3);
         } else if (ChBGO == 4) {
            vEkeVBGO.push_back(EdepBGO*kbgobackd+bbgobackd);
            vCluster.push_back(4);
         } else if (ChBGO == 5) {
            vEkeVBGO.push_back(EdepBGO*kbgobacke+bbgobacke);
            vCluster.push_back(5);
         } else if (ChBGO == 6) {
            vEkeVBGO.push_back(EdepBGO*kbgobackf+bbgobackf);
            vCluster.push_back(6);
         } else if (ChBGO == 7) {
            vEkeVBGO.push_back(EdepBGO*kbgobackg+bbgobackg);
            vCluster.push_back(7);
         } else if (ChBGO == 8) {
            vEkeVBGO.push_back(EdepBGO*kbgobackh+bbgobackh);
            vCluster.push_back(8);
         } else if (ChBGO == 9) {
            vEkeVBGO.push_back(EdepBGO*kbgobacki+bbgobacki);
            vCluster.push_back(9);
         } else if (ChBGO == 10) {
            vEkeVBGO.push_back(EdepBGO*kbgobackj+bbgobackj);
            vCluster.push_back(10);
         } else if (ChBGO == 17) {
            vEkeVBGO.push_back(EdepBGO*kbgofronta+bbgofronta);
            vCluster.push_back(-17);
         } else if (ChBGO == 18) {
            vEkeVBGO.push_back(EdepBGO*kbgofrontb+bbgofrontb);
            vCluster.push_back(-18);
         } else if (ChBGO == 19) {
            vEkeVBGO.push_back(EdepBGO*kbgofrontc+bbgofrontc);
            vCluster.push_back(-19);
         } else if (ChBGO == 20) {
            vEkeVBGO.push_back(EdepBGO*kbgofrontd+bbgofrontd);
            vCluster.push_back(-20);
         } else if (ChBGO == 21) {
            vEkeVBGO.push_back(EdepBGO*kbgofronte+bbgofronte);
            vCluster.push_back(-21);
         } else if (ChBGO == 22) {
            vEkeVBGO.push_back(EdepBGO*kbgofrontf+bbgofrontf);
            vCluster.push_back(-22);
         } else if (ChBGO == 23) {
            vEkeVBGO.push_back(EdepBGO*kbgofrontg+bbgofrontg);
            vCluster.push_back(-23);
         } else {
            vEkeVBGO.push_back(EdepBGO*kbgofronth+bbgofronth);
            vCluster.push_back(-24);
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
   std::cout << "\033[1;35m----------------------- Reading II -----------------------\033[0m" << std::endl;
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
   std::cout << "\033[1;32m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;32m------------------------ Sorting -------------------------\033[0m" << std::endl;
   std::cout << "\033[1;32m----------------------------------------------------------\033[0m" << std::endl;

   std::vector<double> BackClusterEn;
   std::vector<double> FrontClusterEn;
   std::vector<double> ClusterTm;
   std::vector<double> ClusterMu;
   std::vector<double> V1En;
   std::vector<double> V2En;
   std::vector<double> V3En;
   std::vector<double> V4En;
   std::vector<double> ElectronTm;
   std::vector<double> BackClusterTm;
   std::vector<double> FrontClusterTm;
   std::vector<double> BGO_side;
   std::vector<double> Veto_side;
   std::vector<double> Same_side;

   double tmelmin = -25; // -40 // veto time window
   double tmelmax = 25; // 400

   double tbwindow = 60; // time window BGO
   int nmuons = 10000;
   double muon_tau = 2197.0;
   double norm = nmuons*((exp(-timemin[0]/muon_tau)) - (exp(-timemax[0]/muon_tau)));

   TH1F *hfronttm = new TH1F("hfronttm","hfronttm",15,0,60);
   TH1F *hbacktm = new TH1F("hbacktm","hbacktm",15,0,60);

   for (int n=0; n<nmuons; n++) {
      std::vector<double> RunTm;
      std::vector<double> RunEn;
      std::vector<double> RunCh;
      for (int k=0; k<(5*nmuons); k++) {
         if (vEvIDBGO[k] == vEvIDTrig[n]) {
            if ((vTimeBGO[k] > timemin[0]) && (vTimeBGO[k] <= timemax[0])) {
               if (vEkeVBGO[k] > 100) {
                  RunTm.push_back(vTimeBGO[k]);
                  RunEn.push_back(vEkeVBGO[k]);
                  RunCh.push_back(vCluster[k]);
               }
            }
         }
      }

      // Sorting by order
      std::vector<double> SortedRunTm = RunTm;
      std::vector<double> SortedIndex;
      std::vector<double> SortedRunEn;
      std::vector<double> SortedRunCh;
      std::sort(SortedRunTm.begin(),SortedRunTm.end());      

      std::vector<double> FrontRunTm;
      std::vector<double> BackRunTm;

      std::vector<double> UsedIndex;

      for (int i=0; i<SortedRunTm.size(); i++) {
         std::vector<double> Indices;
         std::vector<double>::iterator it = RunTm.begin();
         while ((it = find(it,RunTm.end(),SortedRunTm[i])) != RunTm.end()) {
            Indices.push_back(std::distance(RunTm.begin(),it));
            it++;
         }
         if (Indices.size() == 1) {
            SortedIndex.push_back(Indices[0]);
         } else {
            SortedIndex.push_back(Indices[UsedIndex.size()]);
            UsedIndex.push_back(Indices[UsedIndex.size()]);
            if (UsedIndex.size() == Indices.size()) UsedIndex.clear();
         } 
         SortedRunEn.push_back(RunEn[SortedIndex[i]]);
         SortedRunCh.push_back(RunCh[SortedIndex[i]]);  
      }

      double BackRunEn = 0.0;
      double FrontRunEn = 0.0;
      double runclustertm; 

      bool assignedf = false;
      bool assignedb = false;

      if (SortedRunTm.size() > 0) {
      //if ((SortedRunTm.size() > 0) && (SortedRunCh[0] >= 0)) {
         runclustertm = SortedRunTm[0]; 
         //if (SortedRunCh[0] >= 0) {
            //BackClusterTm.push_back(runclustertm);
         //} else {
            //FrontClusterTm.push_back(runclustertm);
         //}
         //std::cout << "muon no. = " << vEvIDTrig[n] << std::endl;
         //for (int i=0; i<RunTm.size(); i++) std::cout << "Tm = " << RunTm[i] << ", En = " << RunEn[i] << ", Ch = " << RunCh[i] << std::endl;
         //for (int i=0; i<SortedRunTm.size(); i++) std::cout << "\033[1;32m Tm = " << SortedRunTm[i] << ", En = " << SortedRunEn[i] << ", Ch = " << SortedRunCh[i] << "\033[0m" << std::endl;
         for (int i=0; i<SortedRunTm.size(); i++) {
            if ((SortedRunTm[i] - runclustertm) < tbwindow) {
               if (SortedRunCh[i] > 0) {
                  BackRunEn += SortedRunEn[i];
                  if ((SortedRunCh[0] <= 0) && (!assignedb)) {
                     BackRunTm.push_back(SortedRunTm[i]-runclustertm);
                     assignedb = true;
                  }
               } else {
                  FrontRunEn += SortedRunEn[i];
                  if ((SortedRunCh[0] > 0) && (!assignedf)) {
                     FrontRunTm.push_back(SortedRunTm[i]-runclustertm);
                     assignedf = true;
                  }
               }
            } else {
               BackClusterEn.push_back(BackRunEn);
               FrontClusterEn.push_back(FrontRunEn);
               ClusterTm.push_back(runclustertm);
               ClusterMu.push_back(vEvIDTrig[n]);
               BackRunEn = 0.0;
               FrontRunEn = 0.0;
               runclustertm = SortedRunTm[i];
               if (SortedRunCh[i] > 0) {
                  BackRunEn += SortedRunEn[i];
               } else {
                  FrontRunEn += SortedRunEn[i];
               }
                 
            }
            //std::cout << "cl.time = " << runclustertm << ", back en = " << BackRunEn << ", front en = " << FrontRunEn << std::endl; 
         }
         BackClusterEn.push_back(BackRunEn);
         FrontClusterEn.push_back(FrontRunEn);
         ClusterTm.push_back(runclustertm);
         ClusterMu.push_back(vEvIDTrig[n]);
         //std::cout << "cluster length = " <<ClusterTm.size() << ", cluster last = " << ClusterTm[ClusterTm.size()-1] << ", cluster back = " << ClusterTm.back() << ", muon = " << ClusterMu.back() << std::endl;
         //std::cout << std::endl;
 
         for (int i=0; i<FrontRunTm.size(); i++) hfronttm->Fill(FrontRunTm[i]);
         for (int i=0; i<BackRunTm.size(); i++) hbacktm->Fill(BackRunTm[i]);
         
      }

   }

   std::cout << FrontClusterTm.size() << " <= front, back => " << BackClusterTm.size() << std::endl; 

   std::cout << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m---------------------- Matching --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << std::endl;


   for (int n=0; n<ClusterMu.size(); n++) {
      double V1RunEn = 0.0;
      double V2RunEn = 0.0;
      double V3RunEn = 0.0;
      double V4RunEn = 0.0;   
      for (int l=0; l<(3*nmuons); l++) {
         if ((vEvIDVeto[l] == ClusterMu[n]) && (vEdepVeto[l] > 100)) {
            if (((vTimeVeto[l] - ClusterTm[n]) >= tmelmin) && ((vTimeVeto[l] - ClusterTm[n]) <= tmelmax)) {
               if (vChanVeto[l] == 34) V1RunEn += vEdepVeto[l];
               if (vChanVeto[l] == 35) V2RunEn += vEdepVeto[l];
               if (vChanVeto[l] == 36) V3RunEn += vEdepVeto[l];
               if (vChanVeto[l] == 38) {
                  V4RunEn += vEdepVeto[l];
                  ElectronTm.push_back(vTimeVeto[l] - ClusterTm[n]);
               }
            }
         }
      }
      V1En.push_back(V1RunEn);
      V2En.push_back(V2RunEn);
      V3En.push_back(V3RunEn);
      V4En.push_back(V4RunEn);

      double bgoside = 0;
      double vetoside = 0;
      double sameside = 0;
      bgoside = ((BackClusterEn[n]-FrontClusterEn[n])/(BackClusterEn[n]+FrontClusterEn[n]));
      vetoside = ((V4RunEn-V3RunEn)/(V4RunEn+V3RunEn));
      sameside = abs(bgoside+vetoside);
      if ((V4RunEn == 0) && (V3RunEn == 0)) {
         Same_side.push_back(abs(bgoside));
      } else {
         Same_side.push_back(abs(bgoside+vetoside));
      }
      BGO_side.push_back((BackClusterEn[n]-FrontClusterEn[n])/(BackClusterEn[n]+FrontClusterEn[n]));
      Veto_side.push_back((V4RunEn-V3RunEn)/(V4RunEn+V3RunEn));

      std::cout << "bgoside = " << bgoside << ", vetoside = " << vetoside << ", sameside = " << sameside << std::endl;

   }

/*
   int sampcount = 0;
   for (int i=0; i<BackClusterEn.size(); i++) {
      if ((FrontClusterEn[i] != 0) && (BackClusterEn[i] == 0) && (V3En[i] == 0) && (V4En[i] == 0)) {
         if ((FrontClusterEn[i] >= 800) && (FrontClusterEn[i] <= 10000)) {
            sampcount++;
            std::cout << FrontClusterEn[i] << std::endl;
         }
      }
   }

   std::cout << "sampcount = " << sampcount << std::endl;
*/
//   std::cout << "Sizes :: V1 = " << V1En.size() <<", V2 = " << V2En.size() << ", V3 = " << V3En.size() << ", V4 = " << V4En.size() << std::endl;
//   for (int i=0; i<V1En.size(); i++) {
//      std::cout << "V1 = " << V1En[i] << ", V2 = " << V2En[i] << ", V3 = " << V3En[i] << ", V4 = " << V4En[i] << std::endl;
//   }


   std::cout << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m-------------------- Real Matching -----------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << std::endl;

   std::vector<std::vector<double>> AllPex;
   std::vector<std::vector<double>> AllPee; 

   std::vector<std::vector<double>> AllPex2;
   std::vector<std::vector<double>> AllPee2;

   double Ethr3 = 10000; // keV [BGO upper]
   double Ethr4 = 1000; // adc [Veto 2]
   double Ethr5 = 700; // adc [Veto 1]

   double Ethr1[] = {0,500,1000,1500,2000,2500,3000}; // adc [Veto]
   double Ethr2[] = {500,750,1000,1250,1500,1750,2000}; // keV [BGO lower]

   int nvar = 7; 

   std::cout << Same_side.size() << " <== same side, BackCluster ==> " << BackClusterEn.size() << std::endl;

   // Standard method + Carlos' sideness
   for (int p=0; p<nvar; p++) {
      std::vector<double> RunPex;
      std::vector<double> RunPee;
      for (int q=0; q<nvar; q++) { 
         double XrayCounter = 0;
         double elecCounter = 0;
         double TotalCounter = 0;
         for (int i=0; i < BackClusterEn.size(); i++) {
            if ((((V3En[i] <= Ethr1[p]) && (V2En[i] <= Ethr4) && (FrontClusterEn[i] >= Ethr2[q]) && (FrontClusterEn[i] <= Ethr3)) || ((V4En[i] <= Ethr1[p]) && (BackClusterEn[i] >= Ethr2[q]) && (BackClusterEn[i] <= Ethr3))) && (Same_side[i] < 1.6)) {
               XrayCounter++;
               TotalCounter++;
            } else {
               elecCounter++;
               TotalCounter++;
            }
         } 
         RunPex.push_back(XrayCounter/norm);
         RunPee.push_back(elecCounter/norm);
         //std::cout << "Pex = " << XrayCounter/TotalCounter <<", Pee = "<< elecCounter/TotalCounter << std::endl;
      }
      AllPex.push_back(RunPex);
      AllPee.push_back(RunPee);
   }


   // Standard method + Carlos' sideness + Aldo's recuperation 
   for (int p=0; p<nvar; p++) {
      std::vector<double> RunPex2;
      std::vector<double> RunPee2;
      for (int q=0; q<nvar; q++) {
         double XrayCounter = 0;
         double Xray2Counter = 0;
         double elecCounter = 0;
         double TotalCounter = 0;
         for (int i=0; i < BackClusterEn.size(); i++) {
            if ((((V3En[i] <= Ethr1[p]) && (V2En[i] <= Ethr4) && (FrontClusterEn[i] >= Ethr2[q]) && (FrontClusterEn[i] <= Ethr3)) || ((V4En[i] <= Ethr1[p]) && (BackClusterEn[i] >= Ethr2[q]) && (BackClusterEn[i] <= Ethr3))) && (Same_side[i] < 1.6)) {
               XrayCounter++;
               TotalCounter++;
            } else if ((FrontClusterEn[i] >= Ethr2[q]) && (FrontClusterEn[i] <= Ethr3) && (BackClusterEn[i] >= Ethr2[q]) && (BackClusterEn[i] <= Ethr3)) {
               Xray2Counter++;
               TotalCounter++;
            } else {
               elecCounter++;
               TotalCounter++;
            }
         }
         RunPex2.push_back((XrayCounter+Xray2Counter)/norm);
         RunPee2.push_back(elecCounter/norm);
         std::cout << "Xrays = " << XrayCounter << ", X*-rays = " << Xray2Counter << ", elecs = " << elecCounter << ", Total = " << TotalCounter << std::endl;
         //std::cout << "Pex = " << XrayCounter/TotalCounter <<", Pee = "<< elecCounter/TotalCounter << std::endl;
      }
      AllPex2.push_back(RunPex2);
      AllPee2.push_back(RunPee2);
   }


   TGraph2D *gpex = new TGraph2D(); // Standard + Carlos
   TGraph2D *gpex2 = new TGraph2D(); // Standard + Carlos + Aldo
   
   for (int p=0; p<nvar;p++) {
      for (int q=0; q<nvar;q++) {
         gpex->SetPoint(p*nvar+q,Ethr1[p],Ethr2[q],AllPex[p][q]);
         gpex2->SetPoint(p*nvar+q,Ethr1[p],Ethr2[q],AllPex2[p][q]);
      }
   }


   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------- Plotting -------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl; 


   TH1F *hsameside = new TH1F("hsameside","hsameside",50,0,2);
   for (int i=0; i<Same_side.size(); i++) hsameside->Fill(Same_side[i]);

   TCanvas *csameside = new TCanvas("csameside","csameside",800,600);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   hsameside->SetTitle("");
   hsameside->Draw();
   csameside->SaveAs("same_side_pe.C");

   TH1F *heltimes = new TH1F("heltimes","heltimes",100,-200,200);
   for (int i=0; i<ElectronTm.size(); i++) heltimes->Fill(ElectronTm[i]);

   TCanvas *celtimes = new TCanvas("celtimes","celtimes",800,600);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   heltimes->SetTitle("");
   heltimes->GetXaxis()->SetTitle("t_{V4} - t_{Cluster}");
   heltimes->Draw();

/*
   TH1F *htmvetos = new TH1F("htmvetos","htmvetos",110,-40.0,400.0);
   for (int i=0; i<ElectronTm.size(); i++) htmvetos->Fill(ElectronTm[i]);
   TH1F *hclustertm = new TH1F("hclustertm","hclustertm",25,-40.0,60.0);
   for (int i=0; i<ClusterTm.size(); i++) hclustertm->Fill(ClusterTm[i]); 

   TCanvas *c = new TCanvas("c","c",800,600);
   gPad->SetGrid(1,1);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   htmvetos->SetTitle("");
   htmvetos->GetXaxis()->SetTitle("t_{Veto_4_A} - t_{Cluster} [ns]");
   htmvetos->SetLineColor(kBlack);
   htmvetos->Draw();
   //auto legend = new TLegend(0.8,0.8,0.96,0.96);
   //legend->AddEntry(htmvetos,"Any veto","l");
   //legend->Draw();
*/

   TCanvas *d = new TCanvas("d","d",800,600);
   gPad->SetGrid(1,1);
   gStyle->SetOptStat(0);
   //gStyle->SetPalette(kCMYK);
   //TColor::InvertPalette();
   gpex->SetTitle("; E_{THR 1} [adc]; E_{THR 2} [keV]; P_{eX}");
   gpex->Draw("colz");
   d->SaveAs("Pex_run383_side.pdf");   

   TCanvas *caldo = new TCanvas("caldo","caldo",800,600);
   gPad->SetGrid(1,1);
   gStyle->SetOptStat(0);
   gpex2->SetTitle("; E_{THR 1} [adc]; E_{THR 2} [keV]; P_{eX}");
   gpex2->Draw("colz");
 

   TCanvas *f = new TCanvas("f","f",800,600);
   gPad->SetGrid(1,1);
   gStyle->SetOptStat(0);
   hfronttm->SetTitle("");
   //hfronttm->GetXaxis()->SetTitle("t_{Front, i} - t_{Cluster}");
   hfronttm->GetXaxis()->SetTitle("t_{Front, cluster} - t_{Cluster}");
   hfronttm->SetLineColor(kTeal);
   hfronttm->SetFillColor(kTeal-5);
   hfronttm->Draw();
 
   TCanvas *g = new TCanvas("g","g",800,600);
   gPad->SetGrid(1,1);
   gStyle->SetOptStat(0);
   hbacktm->SetTitle("");
   //hbacktm->GetXaxis()->SetTitle("t_{Back, i} - t_{Cluster}");
   hbacktm->GetXaxis()->SetTitle("t_{Back, cluster} - t_{Cluster}");
   hbacktm->SetLineColor(kViolet);
   hbacktm->SetFillColor(kViolet-4);
   hbacktm->Draw(); 

}

int main() {
   DetSys4pe();
   return 0;
}  
