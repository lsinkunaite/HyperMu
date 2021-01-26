//////////////////////////////////////////////////////////////
/*                                                          */
/*  LS: to draw a full spectrum of mu-decay for >= 250-mm   */
/*  scintillator, SciD3, increase the number of array ele-  */
/*  ments in the location #1, modify the # of bins when     */
/*  filling the arrays in the locations #2 and change the   */
/*  range in the location #3.                               */
/*                                                          */
//////////////////////////////////////////////////////////////

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

void VetoEff(){

   //Some style definitions
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
   gStyle->SetPadLeftMargin(0.24);
   //gStyle->SetPadTopMargin(0.32);
   gStyle->SetPadTopMargin(0.12);
   //gStyle->SetPadRightMargin(0.05);
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

   std::string runnumber = "530";
  

   std::vector<int> timemin;
   std::vector<int> timemax;

   timemin.push_back(100);
   timemax.push_back(400);

   // Names of the files
   // Electron Vetos
   std::string fileVeto4A = runnumber+"_Veto4_A_prep.txt";
   std::string fileVeto4B = runnumber+"_Veto4_B_prep.txt";   
   // BGOs
   std::string fileBGOBackA = runnumber+"_BGO_Back_A_prep.txt";
   std::string fileBGOBackB = runnumber+"_BGO_Back_B_prep.txt";
   std::string fileBGOBackC = runnumber+"_BGO_Back_C_prep.txt";
   std::string fileBGOBackE = runnumber+"_BGO_Back_E_prep.txt";
   

   // Vectors with detector names
   std::vector<std::string> BGOfiles;
   std::vector<std::string> Vetofiles;

   // Electron Vetos
   Vetofiles.push_back(fileVeto4A);
   Vetofiles.push_back(fileVeto4B);
   // BGOs
   BGOfiles.push_back(fileBGOBackA);
   BGOfiles.push_back(fileBGOBackB);
   BGOfiles.push_back(fileBGOBackC);
   BGOfiles.push_back(fileBGOBackE);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float EventID, Instance, Energy, Time;
   float iEventID;


   // Elelectron vetos 
   std::vector< std::vector< double > > allEvIDVeto4A;
   std::vector< std::vector< double > > allEdepVeto4A;
   std::vector< std::vector< double > > allTimeVeto4A;
   std::vector< std::vector< double > > allEvIDVeto4B;
   std::vector< std::vector< double > > allEdepVeto4B;
   std::vector< std::vector< double > > allTimeVeto4B;
   // BGOs
//   std::vector< std::vector< double > > allIDBGOBackCluster;
//   std::vector< std::vector< double > > allEnBGOBackCluster;

   
		   
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
      //std::string astring;
      //getline(fVeto4A, astring, '*');
      //std::cout << astring << std::endl;
      fVeto4A >> EvIDV4A >> InstV4A >> EdepV4A >> TimeV4A;
      vEvIDV4A.push_back(EvIDV4A);
      vEdepV4A.push_back(EdepV4A);
      vTimeV4A.push_back(TimeV4A);
      //std::cout << "EvID = " << EvIDV4A << ", InstV4A = " << InstV4A << ", Edep = "<< EdepV4A << ", Time = " << TimeV4A << std::endl;
      }
   vEvIDV4A.pop_back();
   vEdepV4A.pop_back();
   vTimeV4A.pop_back();
   fVeto4A.close();


/*
   // Veto4_B
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
*/


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


/*
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
      double EkeVBGOBackB;
      fBGOBackB >> EvIDBGOBackB >> InstBGOBackB >> EdepBGOBackB >> TimeBGOBackB;
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
      double EkeVBGOBackC;
      fBGOBackC >> EvIDBGOBackC >> InstBGOBackC >> EdepBGOBackC >> TimeBGOBackC;
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


   // BGO_Back_E
   std::ifstream fBGOBackE(BGOfiles[3]);
   std::vector<double> vEvIDBGOBackE;
   std::vector<double> vEdepBGOBackE;
   std::vector<double> vEkeVBGOBackE;
   std::vector<double> vTimeBGOBackE;
   double kbgobacke = 1.88;
   double bbgobacke = 20.78;
   while (!fBGOBackE.eof()) {
      double EvIDBGOBackE, InstBGOBackE, EdepBGOBackE, TimeBGOBackE;
      double EkeVBGOBackE;
      fBGOBackE >> EvIDBGOBackE >> InstBGOBackE >> EdepBGOBackE >> TimeBGOBackE;
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
*/



   std::cout << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m---------------------- Reading II --------:----------------\033[0m" << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;

   // Veto4_A
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
   int cBackBGOA;
   for (int s=0; s<vTimeBGOBackA.size(); s++) {
      if ((vTimeBGOBackA[s] > timemin[0]) && (vTimeBGOBackA[s] <timemax[0])) {
         if (vEkeVBGOBackA[s] < 100000) {
            vIDBGOBackA.push_back(vEvIDBGOBackA[s]);
            vEnBGOBackA.push_back(vEkeVBGOBackA[s]);
            vTmBGOBackA.push_back(vTimeBGOBackA[s]);
         }
      }
   }
/*
   for (int s=0; s<vTimeBGOBackA.size(); s++) {
      if ((vTimeBGOBackA[s] > timemin[g]) && (vTimeBGOBackA[s] <timemax[g])) {
         if (vEkeVBGOBackA[s] < 100000) {    
            cBackBGOA = vPureIDBGOBackA.size();
            if (cBackBGOA == 0) {
               vPureIDBGOBackA.push_back(vEvIDBGOBackA[s]);
               vPureEnBGOBackA.push_back(vEkeVBGOBackA[s]);            
            } else if (vEvIDBGOBackA[s] == vPureIDBGOBackA[cBackBGOA-1]) {
               vPureEnBGOBackA[cBackBGOA-1] = vPureEnBGOBackA[cBackBGOA-1] + vEkeVBGOBackA[s]; 
            } else {
               vPureIDBGOBackA.push_back(vEvIDBGOBackA[s]);
               vPureEnBGOBackA.push_back(vEkeVBGOBackA[s]);
            }
         }
      }
   }
*/
/*
   // BGO_Back_B
   std::vector<double> vPureEnBGOBackB;
   std::vector<double> vPureIDBGOBackB;
   int cBackBGOB;
   for (int s=0; s<vTimeBGOBackB.size(); s++) {
      if ((vTimeBGOBackB[s] > timemin[g]) && (vTimeBGOBackB[s] <timemax[g])) {
         if (vEkeVBGOBackB[s] < 100000) {    
            cBackBGOB = vPureIDBGOBackB.size();
            if (cBackBGOB == 0) {
               vPureIDBGOBackB.push_back(vEvIDBGOBackB[s]);
               vPureEnBGOBackB.push_back(vEkeVBGOBackB[s]); 
            } else if (vEvIDBGOBackB[s] == vPureIDBGOBackB[cBackBGOB-1]) {
               vPureEnBGOBackB[cBackBGOB-1] = vPureEnBGOBackB[cBackBGOB-1] + vEkeVBGOBackB[s]; 
            } else {
               vPureIDBGOBackB.push_back(vEvIDBGOBackB[s]);
               vPureEnBGOBackB.push_back(vEkeVBGOBackB[s]);
            }
         }
      }
   }

   
   // BGO_Back_C
   std::vector<double> vPureEnBGOBackC;
   std::vector<double> vPureIDBGOBackC;
   int cBackBGOC;
   for (int s=0; s<vTimeBGOBackC.size(); s++) {
      if ((vTimeBGOBackC[s] > timemin[g]) && (vTimeBGOBackC[s] <timemax[g])) {
         if (vEkeVBGOBackC[s] < 100000) {    
            cBackBGOC = vPureIDBGOBackC.size();
            if (cBackBGOC == 0) {
               vPureIDBGOBackC.push_back(vEvIDBGOBackC[s]);
               vPureEnBGOBackC.push_back(vEkeVBGOBackC[s]); 
            } else if (vEvIDBGOBackC[s] == vPureIDBGOBackC[cBackBGOC-1]) {
               vPureEnBGOBackC[cBackBGOC-1] = vPureEnBGOBackC[cBackBGOC-1] + vEkeVBGOBackC[s]; 
            } else {
               vPureIDBGOBackC.push_back(vEvIDBGOBackC[s]);
               vPureEnBGOBackC.push_back(vEkeVBGOBackC[s]);
            }
         }
      }
   }


   // BGO_Back_E
   std::vector<double> vPureEnBGOBackE;
   std::vector<double> vPureIDBGOBackE;
   int cBackBGOE;
   for (int s=0; s<vTimeBGOBackE.size(); s++) {
      if ((vTimeBGOBackE[s] > timemin[g]) && (vTimeBGOBackE[s] <timemax[g])) {
         if (vEkeVBGOBackE[s] < 100000) {    
            cBackBGOE = vPureIDBGOBackE.size();
            if (cBackBGOE == 0) {
               vPureIDBGOBackE.push_back(vEvIDBGOBackE[s]);
               vPureEnBGOBackE.push_back(vEkeVBGOBackE[s]);
            } else if (vEvIDBGOBackE[s] == vPureIDBGOBackE[cBackBGOE-1]) {
               vPureEnBGOBackE[cBackBGOE-1] = vPureEnBGOBackE[cBackBGOE-1] + vEkeVBGOBackE[s];
            } else {
               vPureIDBGOBackE.push_back(vEvIDBGOBackE[s]);
               vPureEnBGOBackE.push_back(vEkeVBGOBackE[s]);
            }
         }  
      }
   }
 */  



   std::cout << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m---------------------- Matching --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;


   const int nsamps = 100;
   double Estep = 25000.0/(nsamps);
   std::vector<double> Ethr;
   Ethr.push_back(0.0);
   for (int i=1; i<nsamps; i++) Ethr.push_back(Ethr[i-1]+Estep);
   std::vector<double> EffVeto4A;
   std::vector<double> EffVeto4A2;
   std::vector<double> EffVeto4A3;

   for (int m=0; m<Ethr.size(); m++) {
      double MatchCounter=0;
      double TotalCounter=0;
      double MatchCounter2=0;
      double MatchCounter3=0;
      for (int n=0; n<vIDBGOBackA.size(); n++) {
         //std::cout << "Ethr = " << Ethr[m] << " BGOEn = " << allEnBGOBackCluster[0][n] <<std::endl;
         if (vEnBGOBackA[n] >= Ethr[m]) {
            int GoodEvent = 0;
            for (int k=0; k<vEvIDV4A.size(); k++) {
               if (vEvIDV4A[k] == vIDBGOBackA[n]) {
                  if (vInstV4A[k] == 0) {
                     if ((vTimeV4A[k] >= (vTmBGOBackA[n]-100)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+100))) {
                        if ((vTimeV4A[k] >= (vTmBGOBackA[n]-65)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+65))) {
                           if ((vTimeV4A[k] >= (vTmBGOBackA[n]-30)) && (vTimeV4A[k] <= (vTmBGOBackA[n]+30))) {
                              MatchCounter++;
                           }
                           MatchCounter2++;
                        }
                        MatchCounter3++;
                     }
                  } else {
                     GoodEvent = 1;
                  }
               }
            }
            if (GoodEvent == 0) {
               TotalCounter++;
            }
         }
      }
      std::cout << "Ethr = " << Ethr[m] << ", Eff1 = " << MatchCounter/TotalCounter << ", Eff2 = " << MatchCounter2/TotalCounter << ", Eff3 = " << MatchCounter3/TotalCounter << std::endl;
      EffVeto4A.push_back(MatchCounter/TotalCounter);
      EffVeto4A2.push_back(MatchCounter2/TotalCounter);
      EffVeto4A3.push_back(MatchCounter3/TotalCounter);               
   }      




 
   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


   float EffV4Aarr[nsamps] = {}; // Efficiency
   float EffV4Aarr2[nsamps] = {};
   float EffV4Aarr3[nsamps] = {};
   float EthrV4Aarr[nsamps] = {};
   for (int i=0; i<nsamps; i++) {
      EffV4Aarr[i] = EffVeto4A[i];
      EffV4Aarr2[i] = EffVeto4A2[i];
      EffV4Aarr3[i] = EffVeto4A3[i];
      EthrV4Aarr[i] = Ethr[i]/1000.0;
   }
   TCanvas *f = new TCanvas("f","E_{THR}",800,600);
   //gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grV4A3 = new TGraph(nsamps,EthrV4Aarr,EffV4Aarr3);
   grV4A3->SetTitle("Efficiency of Veto_4_A");
   grV4A3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grV4A3->GetYaxis()->SetTitle("Eff");
   grV4A3->GetYaxis()->SetTitleOffset(2.1);
   grV4A3->SetLineColor(kGray+3);
   grV4A3->SetLineWidth(2);
   grV4A3->SetFillColor(kViolet-5);
   //grV4A3->SetFillStyle(3002);
   grV4A3->Draw("ALB1");
   TGraph *grV4A2 = new TGraph(nsamps,EthrV4Aarr,EffV4Aarr2);
   grV4A2->SetLineColor(kGray+3);
   grV4A2->SetLineWidth(2);
   grV4A2->SetFillColor(kTeal-5);
   //grV4A2->SetFillStyle(3002);
   grV4A2->Draw("LB1");
   TGraph *grV4A = new TGraph(nsamps,EthrV4Aarr,EffV4Aarr);
   grV4A->SetLineColor(kGray+3);
   grV4A->SetLineWidth(2);
   grV4A->SetFillColor(kOrange-4);
   //grV4A->SetFillStyle(3002);
   grV4A->Draw("LB1");

   auto legend = new TLegend(0.71,0.71,0.87,0.87); 
   legend->AddEntry(grV4A3,"t=[-100, 100] ns","f");
   legend->AddEntry(grV4A2,"t=[-65, 65] ns","f");
   legend->AddEntry(grV4A,"t=[-30, 30] ns", "f");
   legend->Draw();
   f->SaveAs("EffV4A_new2.pdf");



   //TH1F *ht3 = new TH1F("ht3","Cluster",250,0,70.0);
   //TH1F *ht2 = new TH1F("ht2","Cluster",250,0,70.0);
   TH1F *ht1 = new TH1F("ht1","Cluster",250,0,50.0);
   TH1F *hv4a = new TH1F("hv4a","Veto 4 A",250,0,5.0);
/*
   TH1F *h3 = new TH1F("h3","E keV",250,0,55.0);
   TH1F *hbgoa = new TH1F("hbgoa","BGO A",100,0,28.0);
   TH1F *hbgob = new TH1F("hbgob","B",100,0,28.0);
   TH1F *hbgoc = new TH1F("hbgoc","C",100,0,28.0);
   TH1F *hbgoe = new TH1F("hbgoe","E",100,0,28.0);   
*/

   //for (int i=0; i<allEnBGOBackCluster[1].size(); i++) {
   //   ht2->Fill((allEnBGOBackCluster[1][i])/(1000.0));
   //}
   //for (int i=0; i<allEnBGOBackCluster[2].size(); i++) {
   //   ht3->Fill((allEnBGOBackCluster[2][i])/(1000.0));
   //}

/*
   for (int i=0; i<SortedClusterEn.size(); i++) {
      h3->Fill((SortedClusterEn[i])/(1000.0));
   }
   for (int i=0; i<vPureEnBGOBackA.size(); i++) {
      hbgoa->Fill((vPureEnBGOBackA[i])/(1000.0));
   }
   for (int i=0; i<vPureEnBGOBackB.size(); i++) {
      hbgob->Fill((vPureEnBGOBackB[i])/(1000.0));
   }
   for (int i=0; i<vPureEnBGOBackC.size(); i++) {
      hbgoc->Fill((vPureEnBGOBackC[i])/(1000.0));
   } 
   for (int i=0; i<vPureEnBGOBackE.size(); i++) {
      hbgoe->Fill((vPureEnBGOBackE[i])/(1000.0));
   }
*/

/*
   TCanvas *c = new TCanvas("c", "BGO Back Cluster",800,600);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   ht1->SetTitle("BGO_Back_Cluster");
   ht1->GetXaxis()->SetTitle("MeV");
   ht1->GetYaxis()->SetRangeUser(1e0,1e4);
   ht1->SetLineColor(kBlack);
   ht1->SetLineWidth(1);
   ht1->SetFillColorAlpha(kTeal-9,1);
   ht1->Draw();
   hv4a->SetLineColor(kBlack);
   hv4a->SetLineWidth(1);
   hv4a->SetFillColorAlpha(kOrange+1,0.5);
   hv4a->Draw("SAME");
   //ht2->SetLineColor(kBlack);
   //ht2->SetLineWidth(1);
   //ht2->SetFillColorAlpha(kPink+1,1);
   //ht2->Draw("SAME");
   //ht1->SetLineColor(kBlack);
   //ht1->SetLineWidth(1);
   //ht1->SetFillColorAlpha(kYellow-7,1);
   //ht1->Draw("SAME");

   auto legend = new TLegend(0.71,0.71,0.87,0.87);
   //legend->AddEntry(ht3, TString::Format("t=[%d, %d] ns", timemin[2],timemax[2]),"f");
   //legend->AddEntry(ht2, TString::Format("t=[%d, %d] ns", timemin[1],timemax[1]),"f");
   legend->AddEntry(ht1, TString::Format("t=[%d, %d] ns", timemin[0], timemax[0]),"f");
   legend->AddEntry(hv4a,"Veto_4_A","f");
   legend->Draw();

   c->SaveAs("BGOCluster_v4a.pdf");
   //c->SaveAs("BackCluster_times.pdf");
*/

/* 

   TCanvas *c = new TCanvas("c", "BGO Back E",800,600);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   gPad->SetGrid(1,1);
   h3->SetTitle("BGO_Back_Cluster "+TString::Format("t=[%d, %d] ns",timemin,timemax));
   h3->GetXaxis()->SetTitle("MeV");
   h3->SetLineColor(kBlack);
   h3->SetLineWidth(3);
   h3->Draw();
   //hbgoa->SetFillColorAlpha(kRed-7, 0.9);
   //hbgoa->SetLineColorAlpha(kRed, 0.464);
   //hbgoa->SetLineWidth(2);
   //hbgoa->Draw("SAME");
   //hbgob->SetFillColorAlpha(kGreen-6,0.7);
   //hbgob->SetLineColor(kGreen-2);
   //hbgob->SetLineWidth(2);
   //hbgob->Draw("SAME");
   //hbgoc->SetFillColorAlpha(kOrange-4, 0.5);
   //hbgoc->SetLineColor(kOrange);
   //hbgoc->SetLineWidth(2);
   //hbgoc->Draw("SAME");
   //hbgoe->SetFillColorAlpha(kBlue,0.3);
   //hbgoe->SetLineColor(kBlue-2);
   //hbgoe->SetLineWidth(2);
   //hbgoe->Draw("SAME");   

   auto legend = new TLegend(0.71,0.71,0.87,0.87);
   legend->AddEntry(h3, "Cluster","f");
   legend->AddEntry(hbgoa, "Back_A","f");
   legend->AddEntry(hbgob, "Back_B","f");
   legend->AddEntry(hbgoc,"Back_C","f");
   legend->AddEntry(hbgoe,"Back_E","f");
   legend->Draw();
*/
   //c->SaveAs("BackCluster_100_400ns.pdf");

   //h1->SetTitle("BGO_Back_E");
   //h1->GetXaxis()->SetTitle("MeV");
   //h1->SetLineColor(kGreen-2);
   //h1->SetLineWidth(2);
   //h1->Draw();
   //h2->SetLineColor(kBlack);
   //h2->SetLineWidth(2);
   //h2->Draw("SAME");

   //auto legend = new TLegend(0.68,0.71,0.85,0.87);
   //legend->AddEntry(h1,"keV","l");
   //legend->AddEntry(h2,"adc","l");
   //legend->Draw();

				

} 
 
 int main() {
   VetoEff();
   return 0;
}  
