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
   std::string fileVeto4A = runnumber+"_Veto6_B_prep.txt";
   std::string fileVeto4B = runnumber+"_Veto6_B_prep.txt";   
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

/*
   float Edep, EventID;
   float iEventID;

   float Ethr1 = 0.5;
   float Ethr21 = 0.5;
   float Ethr22 = 8.0;
   float Ethr3 = 1;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
		   
   // Storage vectors
   // Normalisation 2 [abs = total] :: X-ray cascade
   std::vector< std::vector<double> > PXevector(Xfiles.size()/5,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector(Xfiles.size()/5,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector2(Xfiles.size()/5,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2(Xfiles.size()/5,std::vector<double>(nsamps));          


   // Normalisation 2 [abs = total] :: Mu-decay
   std::vector< std::vector<double> > Peevector(mufiles.size()/5,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector(mufiles.size()/5,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector2(mufiles.size()/5,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2(mufiles.size()/5,std::vector<double>(nsamps));      
*/

   // Elelectron vetos 
   std::vector< std::vector< double > > allEvIDVeto4A;
   std::vector< std::vector< double > > allEdepVeto4A;
   std::vector< std::vector< double > > allTimeVeto4A;
   std::vector< std::vector< double > > allEvIDVeto4B;
   std::vector< std::vector< double > > allEdepVeto4B;
   std::vector< std::vector< double > > allTimeVeto4B;
   // BGOs
   std::vector< std::vector< double > > allIDBGOBackCluster;
   std::vector< std::vector< double > > allEnBGOBackCluster;

/*

   float Ethr;
   int counterXX = 1e5;
   int counteree = 1e5;
   int XXray = 0; // X-rays i-fied as X-rays
   int Xelec = 0; // X-rays i-fied as electrons
   int XXray2 = 0;
   int Xelec2 = 0;
   int eXray = 0; // Electrons i-fied as X-rays
   int eelec = 0; // Electrons i-fied as electrons
   int eXray2 = 0;
   int eelec2 = 0;
   	   
   Ethrmu[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;

*/
   //-------------------------------------------------------------------
   //                           Reading
   //-------------------------------------------------------------------
		   
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
   std::cout << "size = " << vEvIDV4A.size() << ", " << vEdepV4A.size() << ", " << vTimeV4A.size() << std::endl;
//   for (int i=vEvIDV4A.size()-10;i<vEvIDV4A.size(); i++) { 
   for (int i=0; i<11; i++) {
   std::cout << i << " = " << vEvIDV4A[i] << " " << vEdepV4A[i] << " " << vTimeV4A[i] <<std::endl;
   }
*/

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




   for (int g=0; g<timemin.size(); g++) {

   std::cout << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m-------------------- Reading II --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;

   
   // BGO_Back_A
   std::vector<double> vPureEnBGOBackA;
   std::vector<double> vPureIDBGOBackA;
   int cBackBGOA;
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
   

   std::cout << std::endl; 
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m-------------------- Clustering --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;36m----------------------------------------------------------\033[0m" << std::endl;



   // BGO_Back_Cluster: A
   std::vector<double> vPureEnBGOBackCluster = vPureEnBGOBackA;
   std::vector<double> vPureIDBGOBackCluster = vPureIDBGOBackA;
   std::cout << "Cluster contains: A" << std::endl;   

   // BGO_Back_Cluster: A + B
   for (int s=0; s <vPureIDBGOBackB.size(); s++) {
      auto it = find(vPureIDBGOBackCluster.begin(), vPureIDBGOBackCluster.end(), vPureIDBGOBackB[s]);
      if (it != vPureIDBGOBackCluster.end()) {
         int index = it - vPureIDBGOBackCluster.begin();
         vPureEnBGOBackCluster[index] = vPureEnBGOBackCluster[index] + vPureEnBGOBackB[s];
      } else {
         vPureIDBGOBackCluster.push_back(vPureIDBGOBackB[s]);
         vPureEnBGOBackCluster.push_back(vPureEnBGOBackB[s]);
      }
   }      
   std::cout << "Cluster contains: A, B" << std::endl;

   // BGO_Back_Cluster: A + B + C
   for (int s=0; s <vPureIDBGOBackC.size(); s++) {
      auto it = find(vPureIDBGOBackCluster.begin(), vPureIDBGOBackCluster.end(), vPureIDBGOBackC[s]);
      if (it != vPureIDBGOBackCluster.end()) {
         int index = it - vPureIDBGOBackCluster.begin();
         vPureEnBGOBackCluster[index] = vPureEnBGOBackCluster[index] + vPureEnBGOBackC[s];
      } else {
         vPureIDBGOBackCluster.push_back(vPureIDBGOBackC[s]);
         vPureEnBGOBackCluster.push_back(vPureEnBGOBackC[s]);
      }
   }
   std::cout << "Cluster contains: A, B, C" << std::endl;

   // BGO_Back_Cluster: A + B + C + E 
   for (int s=0; s <vPureIDBGOBackE.size(); s++) {
      auto it = find(vPureIDBGOBackCluster.begin(), vPureIDBGOBackCluster.end(), vPureIDBGOBackC[s]);
      if (it != vPureIDBGOBackCluster.end()) {
         int index = it - vPureIDBGOBackCluster.begin();
         vPureEnBGOBackCluster[index] = vPureEnBGOBackCluster[index] + vPureEnBGOBackE[s];
      } else {
         vPureIDBGOBackCluster.push_back(vPureIDBGOBackE[s]);
         vPureEnBGOBackCluster.push_back(vPureEnBGOBackE[s]);
      }
   }
   std::cout << "Cluster contains: A, B, C, E" << std::endl; 
 

      
/* 
   std::vector<int> avector;
   std::vector<int> bvector;

   avector.push_back(14); bvector.push_back(0);
   avector.push_back(11); bvector.push_back(1);
   avector.push_back(16); bvector.push_back(2);
   avector.push_back(8); bvector.push_back(3);
   avector.push_back(1); bvector.push_back(4);


   for (int i=0; i<avector.size(); i++) {
      std::cout << avector[i] << " " <<bvector[i] << std::endl;
   }


   std::vector<int> cvector = avector;
   std::vector<int> newindex;
   std::vector<int> dvector;
   std::sort(avector.begin(), avector.end());  
   for (int i =0; i<cvector.size(); i++) {
      auto itt = find(cvector.begin(), cvector.end(), avector[i]);
      newindex.push_back(itt-cvector.begin());
      std::cout <<" new index= "<< newindex[i] <<" c = " << cvector[i]<< std::endl;
   }
   
   for (int i=0; i<newindex.size(); i++) {
      dvector.push_back(bvector[newindex[i]]);
   }

   std::cout << std::endl;
   for (int i=0; i<avector.size(); i++) {
      std::cout << "a = " << avector[i] << ", b = " << dvector[i] << std::endl;
   }    
*/


   std::cout << std::endl;
   std::cout << "\033[1;32m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;32m---------------------- Sorting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;32m----------------------------------------------------------\033[0m" << std::endl;


   std::vector<double> SortedIndex;
   std::vector<double> SortedClusterID = vPureIDBGOBackCluster;
   std::vector<double> SortedClusterEn;

   std::sort(SortedClusterID.begin(),SortedClusterID.end());
   for (int i=0; i<SortedClusterID.size(); i++) {
      auto it = find(vPureIDBGOBackCluster.begin(), vPureIDBGOBackCluster.end(),SortedClusterID[i]);
      SortedIndex.push_back(it-vPureIDBGOBackCluster.begin());
      SortedClusterEn.push_back(vPureEnBGOBackCluster[SortedIndex[i]]);
   }

   std::cout << "The cluster is sorted! " <<std::endl;

   allEnBGOBackCluster.push_back(SortedClusterEn);
   allIDBGOBackCluster.push_back(SortedClusterID);
   }



   const int nsamps = 100;
   double Estep = 25000.0/(nsamps);
   std::vector<double> Ethr;
   Ethr.push_back(0.0);
   for (int i=1; i<nsamps; i++) Ethr.push_back(Ethr[i-1]+Estep);
   std::vector<double> EffVeto4A;

   for (int m=0; m<Ethr.size(); m++) {
      double MatchCounter=0;
      double TotalCounter=0;
      for (int n=0; n<allIDBGOBackCluster[0].size(); n++) {
         //std::cout << "Ethr = " << Ethr[m] << " BGOEn = " << allEnBGOBackCluster[0][n] <<std::endl;
         if (allEnBGOBackCluster[0][n] >= Ethr[m]) {
            auto it = find(vEvIDV4A.begin(), vEvIDV4A.end(), allIDBGOBackCluster[0][n]);
            int index = it-vEvIDV4A.begin();
            if (index < vEvIDV4A.size()) {
               if ((vTimeV4A[index] > (timemin[0]-30)) && (vTimeV4A[index] < (timemax[0]+30))) {
                  MatchCounter++;
               }
            }
            TotalCounter++;
         }
      }
      //std::cout << "Ethr = " << Ethr[m] << ", Efficiency = " << MatchCounter/TotalCounter << std::endl;
      EffVeto4A.push_back(MatchCounter/TotalCounter);               
   }      




 
   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- Plotting ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


   float EffV4Aarr[nsamps] = {}; // Efficiency
   float EthrV4Aarr[nsamps] = {};
   for (int i=0; i<nsamps; i++) {
      EffV4Aarr[i] = EffVeto4A[i];
      EthrV4Aarr[i] = Ethr[i]/1000.0;
   }
   TCanvas *f = new TCanvas("f","E_{THR}",800,600);
   //gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grV4A = new TGraph(nsamps,EthrV4Aarr,EffV4Aarr);
   grV4A->SetTitle("Efficiency of Veto_6_B");
   grV4A->GetXaxis()->SetTitle("E_{THR} [MeV]");
   //grV4A->GetXaxis()->SetRangeUser(0,2.03);
//487    grPXX->GetXaxis()->SetNdivisions(-304);
   //grV4A->GetYaxis()->SetMoreLogLabels(1);
   grV4A->GetYaxis()->SetTitle("Eff");
   grV4A->GetYaxis()->SetTitleOffset(2.1);
   grV4A->SetLineColor(kGray+3);
   grV4A->SetLineWidth(2);
   grV4A->SetFillColor(kViolet-5);
   grV4A->SetFillStyle(3002);
   grV4A->Draw("ALB1");

   f->SaveAs("EffV6B_100_400_ns.pdf");



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

   for (int i=0; i<allEnBGOBackCluster[0].size(); i++) {
      ht1->Fill((allEnBGOBackCluster[0][i])/(1000.0));
   }
  
   for (int i=0; i<vEvIDV4A.size(); i++) {
      hv4a->Fill((vEdepV4A[i])/(2000.0));
   }

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






		  		 
		
   //-------------------------------------------------------------------
   //                     Bin-by-bin analysis
   //                          Mu-decay
   //-------------------------------------------------------------------     
/*			
   // X-ray cascade	  
   for (int i=0; i<allvEvIDBD1mu.size(); i++) {
      
      std::cout << std::endl;
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m--------------------- X-ray cascade ----------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

      for (int m=0; m<nsamps; m++) {

	     Ethr = Ethrmu[m];

		 //--------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Cu - Al
		 //-------------------------------------------------- 
		 XXray = 0; Xelec = 0;
			  
		 for (int a=0; a<allvEvIDBD1x[0].size(); a++) {

		    if ((allvEdepSD1x[i][a] < Ethr1) && (allvEdepSD2x[i][a] < Ethr1) && (allvEdepSD3x[i][a] < Ethr1)) {
			   if (((allvEdepBD1x[i][a] > Ethr) && (allvEdepBD1x[i][a] < Ethr22)) || ((allvEdepBD2x[i][a] > Ethr) && (allvEdepBD2x[i][a] < Ethr22))) {
				  XXray += 1;
			   } else { Xelec += 1; }
		    } else { Xelec += 1; }
		 }
				 
		 PXXvector[i][m] = XXray/(double)(counterXX);
		 PXevector[i][m] = Xelec/(double)(counterXX); 


		 //--------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Cu - Al
		 //-------------------------------------------------- 
		 eXray = 0; eelec = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu[0].size(); a++) {

		    if ((allvEdepSD1mu[i][a] < Ethr1) && (allvEdepSD2mu[i][a] < Ethr1) && (allvEdepSD3mu[i][a] < Ethr1)) {
		       if (((allvEdepBD1mu[i][a] > Ethr) && (allvEdepBD1mu[i][a] < Ethr22))) || ((allvEdepBD2mu[i][a] > Ethr) && (allvEdepBD2mu[i][a] < Ethr22))) {
				  eXray += 1;
			   } else { eelec += 1; }
		    } else { eelec += 1; }
		 }
				 
		 PeXvector[i][m] = eXray/(double)(counteree);
		 Peevector[i][m] = eelec/(double)(counteree); 

	  
	     //----------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Glass - Al2
		 //---------------------------------------------------- 
		 XXray2 = 0; Xelec2 = 0;
			  
		 for (int a=0; a<allvEvIDBD12x[0].size(); a++) {

		    if ((allvEdepSD12x[i][a] < Ethr1) && (allvEdepSD22x[i][a] < Ethr1) && (allvEdepSD32x[i][a] < Ethr1)) {
			   if (((allvEdepBD12x[i][a] > Ethr) && (allvEdepBD12x[i][a] < Ethr22)) || ((allvEdepBD22x[i][a] > Ethr) && (allvEdepBD22x[i][a] < Ethr22))) {
				  XXray2 += 1;
			   } else { Xelec2 += 1; }
		    } else { Xelec2 += 1; }
		 }
				 
		 PXXvector2[i][m] = XXray2/(double)(counterXX);
		 PXevector2[i][m] = Xelec2/(double)(counterXX); 


		 //----------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Glass - Al2
		 //---------------------------------------------------- 
		 eXray2 = 0; eelec2 = 0;
			  
		 for (int a=0; a<allvEvIDBD12mu[0].size(); a++) {

		    if ((allvEdepSD12mu[i][a] < Ethr1) && (allvEdepSD22mu[i][a] < Ethr1) && (allvEdepSD32mu[i][a] < Ethr1)) {
		       if (((allvEdepBD12mu[i][a] > Ethr) && (allvEdepBD12mu[i][a] < Ethr22))) || ((allvEdepBD22mu[i][a] > Ethr) && (allvEdepBD22mu[i][a] < Ethr22))) {
				  eXray2 += 1;
			   } else { eelec2 += 1; }
		    } else { eelec2 += 1; }
		 }
				 
		 PeXvector2[i][m] = eXray2/(double)(counteree);
		 Peevector2[i][m] = eelec2/(double)(counteree); 

	  
	  } 

				
   }  
*/
   //-------------------------------------------------------------------
   //                     Plotting business
   //-------------------------------------------------------------------     
/*						
   std::cout << std::endl;
   std::cout << "\033[1;33m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;33m-------------------- Plotting business -------------------\033[0m" << std::endl;
   std::cout << "\033[1;33m----------------------------------------------------------\033[0m" << std::endl;

   // Array declarations
   // Normalisation 2 [abs]
   float PXXarr[nsamps] = {}; // X-ray cascade
   float PXXarr2[nsamps] = {};
   float PeXarr[nsamps] = {};
   float PeXarr2[nsamps] = {};
   float PeXXXarr[nsamps] = {};
   float PeXXXarr2[nsamps] = {};
 		 	   
   for (int i=0; i<nsamps; i++) {
      // Normalisation 2 [absolute]
	  PXXarr[i] = PXXvector[0][i];
	  PXXarr2[i] = PXXvector2[0][i];
	  PeXarr[i] = PeXvector[0][i];
	  PeXarr2[i] = PeXvector2[0][i];
	  PeXXXarr[i] = (PeXvector[0][i])/(double)(PXXvector[0][i]);
	  PeXXXarr2[i] = (PeXvector2[0][i])/(double)(PXXvector2[0][i]);
   }	   


   TCanvas *c = new TCanvas("c","test",800,600);
   TH2F *h3 = new TH2F("h3","",nsamps,0.001,0.04,nsamps,0.45,0.8);
   for (int i=0; i < nsamps; i++) {
      h3->Fill(PeXarr[i],PXXarr[i]);
   }
   h3->Draw("COLZ");	
*/
/*		  
   TCanvas *f = new TCanvas("f","E_{THR}",800,600);
   f->Divide(3,1);
   f->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   //gPad->SetFixedAspectRatio();
   TGraph *grPXX = new TGraph(nsamps,Ethrmu,PXXarr);
   grPXX->SetTitle(""); 
   grPXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXX->GetXaxis()->SetRangeUser(0,2.01);
   grPXX->GetXaxis()->SetNdivisions(-304);
   grPXX->GetYaxis()->SetMoreLogLabels(1);
   grPXX->GetYaxis()->SetTitle("P_{XX}");
   grPXX->GetYaxis()->SetTitleOffset(2.1);
   grPXX->SetLineColor(kRed);
   grPXX->SetLineWidth(3);
   grPXX->Draw("ALP");
   TGraph *grPXX2 = new TGraph(nsamps,Ethrmu,PXXarr2);
   grPXX2->SetLineColor(kBlack);
   grPXX2->SetLineWidth(3);
   grPXX2->Draw("LP");

   f->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeX = new TGraph(nsamps,Ethrmu,PeXarr);
   grPeX->SetTitle("");
   grPeX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeX->GetXaxis()->SetRangeUser(0,2.01);
   grPeX->GetYaxis()->SetRangeUser(9.5e-4,3.5e-2);
   grPeX->GetXaxis()->SetNdivisions(-304);
   //TGaxis::SetMaxDigits(2);
   grPeX->GetYaxis()->SetMoreLogLabels(1);
   grPeX->GetYaxis()->SetTitle("P_{eX}");
   grPeX->GetYaxis()->SetTitleOffset(2.1);
   grPeX->SetLineColor(kRed);
   grPeX->SetLineWidth(3);
   grPeX->Draw("ALP");
   TGraph *grPeX2 = new TGraph(nsamps,Ethrmu,PeXarr2);
   grPeX2->SetLineColor(kBlack);
   grPeX2->SetLineWidth(3);
   grPeX2->Draw("LP");
   
   f->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeXXX = new TGraph(nsamps,Ethrmu,PeXXXarr);
   grPeXXX->SetTitle("");
   grPeXXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeXXX->GetXaxis()->SetRangeUser(0,2.01);
   grPeXXX->GetYaxis()->SetRangeUser(1.9e-3,4.7e-2);
   grPeXXX->GetXaxis()->SetNdivisions(-304);
   TGaxis::SetMaxDigits(2);
   grPeXXX->GetYaxis()->SetMoreLogLabels(1);
   grPeXXX->GetYaxis()->SetTitle("#frac{P_{eX}}{P_{XX}}");
   grPeXXX->GetYaxis()->SetTitleOffset(2.1);
   grPeXXX->SetLineColor(kRed);
   grPeXXX->SetLineWidth(3);
   grPeXXX->Draw("ALP");
   TGraph *grPeXXX2 = new TGraph(nsamps,Ethrmu,PeXXXarr2);
   grPeXXX2->SetLineColor(kBlack);
   grPeXXX2->SetLineWidth(3);
   grPeXXX2->Draw("LP");

   f->SaveAs("Cu_Al_vs_Glass_Al2_dA1_"+TString(dA1)+"mm_dL1_"+TString(dL1)+"mm.pdf");
   f->SaveAs("Cu_Al_vs_Glass_Al2_dA1_"+TString(dA1)+"mm_dL1_"+TString(dL1)+"mm.png");
   f->SaveAs("Cu_Al_vs_Glass_Al2_dA1_"+TString(dA1)+"mm_dL1_"+TString(dL1)+"mm.C");
*/

} 
 
 int main() {
   VetoEff();
   return 0;
}  
