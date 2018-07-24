/*//////////////////////////////////////////////////////////*/
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
#include <string>
#include <cstring>
#include <sstream>
#include <stdio>
#include <stdlib>
#include <vector>
using namespace std;

// ROOT
#include "TAttMarker.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TList.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveStats.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TText.h"

void planarBINmu(){

   //Some style definitions
   //gROOT->Reset();
   //gROOT->SetStyle("Plain");
   gStyle->SetPaperSize(26,20);
   gStyle->SetOptStat(1);
   gStyle->SetTitleXOffset(1.15);
   gStyle->SetTitleYOffset(1.15);
   gStyle->SetTitleBorderSize(0.1);
   gStyle->SetLegendBorderSize(0.1);
   gStyle->SetPadBottomMargin(0.12);
   gStyle->SetPadLeftMargin(0.18);
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

   // Names of the files
   // Mu-decay 3-mm
   std::string file3Almu250SciD1D = "../../simdata/planar/planar_2x5mm_250mm_SciD_3mm_Al_1e6mudecay_SciD1D.txt";
   std::string file3Almu250SciD2D = "../../simdata/planar/planar_2x5mm_250mm_SciD_3mm_Al_1e6mudecay_SciD2D.txt";
   std::string file3Almu250SciD3D = "../../simdata/planar/planar_2x5mm_250mm_SciD_3mm_Al_1e6mudecay_SciD3D.txt";
   std::string file3Almu250SciD1U = "../../simdata/planar/planar_2x5mm_250mm_SciD_3mm_Al_1e6mudecay_SciD1U.txt";
   std::string file3Almu250SciD2U = "../../simdata/planar/planar_2x5mm_250mm_SciD_3mm_Al_1e6mudecay_SciD2U.txt";
   std::string file3Almu250SciD3U = "../../simdata/planar/planar_2x5mm_250mm_SciD_3mm_Al_1e6mudecay_SciD3U.txt";
   std::string file3Almu500SciD1D = "../../simdata/planar/planar_2x5mm_500mm_SciD_3mm_Al_1e6mudecay_SciD1D.txt";
   std::string file3Almu500SciD2D = "../../simdata/planar/planar_2x5mm_500mm_SciD_3mm_Al_1e6mudecay_SciD2D.txt";
   std::string file3Almu500SciD3D = "../../simdata/planar/planar_2x5mm_500mm_SciD_3mm_Al_1e6mudecay_SciD3D.txt";
   std::string file3Almu500SciD1U = "../../simdata/planar/planar_2x5mm_500mm_SciD_3mm_Al_1e6mudecay_SciD1U.txt";
   std::string file3Almu500SciD2U = "../../simdata/planar/planar_2x5mm_500mm_SciD_3mm_Al_1e6mudecay_SciD2U.txt";
   std::string file3Almu500SciD3U = "../../simdata/planar/planar_2x5mm_500mm_SciD_3mm_Al_1e6mudecay_SciD3U.txt";
   std::string file3Almu750SciD1D = "../../simdata/planar/planar_2x5mm_750mm_SciD_3mm_Al_1e6mudecay_SciD1D.txt";
   std::string file3Almu750SciD2D = "../../simdata/planar/planar_2x5mm_750mm_SciD_3mm_Al_1e6mudecay_SciD2D.txt";
   std::string file3Almu750SciD3D = "../../simdata/planar/planar_2x5mm_750mm_SciD_3mm_Al_1e6mudecay_SciD3D.txt";
   std::string file3Almu750SciD1U = "../../simdata/planar/planar_2x5mm_750mm_SciD_3mm_Al_1e6mudecay_SciD1U.txt";
   std::string file3Almu750SciD2U = "../../simdata/planar/planar_2x5mm_750mm_SciD_3mm_Al_1e6mudecay_SciD2U.txt";
   std::string file3Almu750SciD3U = "../../simdata/planar/planar_2x5mm_750mm_SciD_3mm_Al_1e6mudecay_SciD3U.txt";
   // Mu-decay 6-mm
   std::string file6Almu250SciD1D = "../../simdata/planar/planar_2x5mm_250mm_SciD_6mm_Al_1e6mudecay_SciD1D.txt";
   std::string file6Almu250SciD2D = "../../simdata/planar/planar_2x5mm_250mm_SciD_6mm_Al_1e6mudecay_SciD2D.txt";
   std::string file6Almu250SciD3D = "../../simdata/planar/planar_2x5mm_250mm_SciD_6mm_Al_1e6mudecay_SciD3D.txt";
   std::string file6Almu250SciD1U = "../../simdata/planar/planar_2x5mm_250mm_SciD_6mm_Al_1e6mudecay_SciD1U.txt";
   std::string file6Almu250SciD2U = "../../simdata/planar/planar_2x5mm_250mm_SciD_6mm_Al_1e6mudecay_SciD2U.txt";
   std::string file6Almu250SciD3U = "../../simdata/planar/planar_2x5mm_250mm_SciD_6mm_Al_1e6mudecay_SciD3U.txt";
   std::string file6Almu500SciD1D = "../../simdata/planar/planar_2x5mm_500mm_SciD_6mm_Al_1e6mudecay_SciD1D.txt";
   std::string file6Almu500SciD2D = "../../simdata/planar/planar_2x5mm_500mm_SciD_6mm_Al_1e6mudecay_SciD2D.txt";
   std::string file6Almu500SciD3D = "../../simdata/planar/planar_2x5mm_500mm_SciD_6mm_Al_1e6mudecay_SciD3D.txt";
   std::string file6Almu500SciD1U = "../../simdata/planar/planar_2x5mm_500mm_SciD_6mm_Al_1e6mudecay_SciD1U.txt";
   std::string file6Almu500SciD2U = "../../simdata/planar/planar_2x5mm_500mm_SciD_6mm_Al_1e6mudecay_SciD2U.txt";
   std::string file6Almu500SciD3U = "../../simdata/planar/planar_2x5mm_500mm_SciD_6mm_Al_1e6mudecay_SciD3U.txt";
   std::string file6Almu750SciD1D = "../../simdata/planar/planar_2x5mm_750mm_SciD_6mm_Al_1e6mudecay_SciD1D.txt";
   std::string file6Almu750SciD2D = "../../simdata/planar/planar_2x5mm_750mm_SciD_6mm_Al_1e6mudecay_SciD2D.txt";
   std::string file6Almu750SciD3D = "../../simdata/planar/planar_2x5mm_750mm_SciD_6mm_Al_1e6mudecay_SciD3D.txt";
   std::string file6Almu750SciD1U = "../../simdata/planar/planar_2x5mm_750mm_SciD_6mm_Al_1e6mudecay_SciD1U.txt";
   std::string file6Almu750SciD2U = "../../simdata/planar/planar_2x5mm_750mm_SciD_6mm_Al_1e6mudecay_SciD2U.txt";
   std::string file6Almu750SciD3U = "../../simdata/planar/planar_2x5mm_750mm_SciD_6mm_Al_1e6mudecay_SciD3U.txt";
   
 
   std::vector<std::string> mufiles;

   // Mu-decay 3-mm
   mufiles.push_back(file3Almu250SciD1D);
   mufiles.push_back(file3Almu250SciD2D);
   mufiles.push_back(file3Almu250SciD3D);
   mufiles.push_back(file3Almu250SciD1U);
   mufiles.push_back(file3Almu250SciD2U);
   mufiles.push_back(file3Almu250SciD3U);
   mufiles.push_back(file3Almu500SciD1D);
   mufiles.push_back(file3Almu500SciD2D);
   mufiles.push_back(file3Almu500SciD3D);
   mufiles.push_back(file3Almu500SciD1U);
   mufiles.push_back(file3Almu500SciD2U);
   mufiles.push_back(file3Almu500SciD3U);
   mufiles.push_back(file3Almu750SciD1D);
   mufiles.push_back(file3Almu750SciD2D);
   mufiles.push_back(file3Almu750SciD3D);
   mufiles.push_back(file3Almu750SciD1U);
   mufiles.push_back(file3Almu750SciD2U);
   mufiles.push_back(file3Almu750SciD3U);
   // Mu-decay 6-mm
   mufiles.push_back(file6Almu250SciD1D);
   mufiles.push_back(file6Almu250SciD2D);
   mufiles.push_back(file6Almu250SciD3D);
   mufiles.push_back(file6Almu250SciD1U);
   mufiles.push_back(file6Almu250SciD2U);
   mufiles.push_back(file6Almu250SciD3U);
   mufiles.push_back(file6Almu500SciD1D);
   mufiles.push_back(file6Almu500SciD2D);
   mufiles.push_back(file6Almu500SciD3D);
   mufiles.push_back(file6Almu500SciD1U);
   mufiles.push_back(file6Almu500SciD2U);
   mufiles.push_back(file6Almu500SciD3U);
   mufiles.push_back(file6Almu750SciD1D);
   mufiles.push_back(file6Almu750SciD2D);
   mufiles.push_back(file6Almu750SciD3D);
   mufiles.push_back(file6Almu750SciD1U);
   mufiles.push_back(file6Almu750SciD2U);
   mufiles.push_back(file6Almu750SciD3U);





   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep, EventID;
   float iEventID;

   const int nsamps = 101;
   float Ethr3 = 0.5;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
   
   // Mu-decay storage vectors
   std::vector< std::vector<double> > PeevectorD((mufiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorD((mufiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeevectorU((mufiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorU((mufiles.size())/6,std::vector<double>(nsamps));

   
   // Mu-decay
   std::vector< std::vector< double > > allvEvID1Dmu;
   std::vector< std::vector< double > > allvEvID2Dmu;
   std::vector< std::vector< double > > allvEvID3Dmu;
   std::vector< std::vector< double > > allvEvID1Umu;
   std::vector< std::vector< double > > allvEvID2Umu;
   std::vector< std::vector< double > > allvEvID3Umu;
 
   std::vector< std::vector< double > > allvEdep1Dmu;
   std::vector< std::vector< double > > allvEdep2Dmu;
   std::vector< std::vector< double > > allvEdep3Dmu;
   std::vector< std::vector< double > > allvEdep1Umu;
   std::vector< std::vector< double > > allvEdep2Umu;
   std::vector< std::vector< double > > allvEdep3Umu;


   float Ethr;
   float tPex;
   int counterD, counterU; 
   int Xray = 0;
   int elec = 0;
   
   Ethrmu[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;


   //-------------------------------------------------------------------
   //                           Reading
   //-------------------------------------------------------------------


   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Mu-decay --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


   for (int k=0; k<((mufiles.size())/6); k++) {
	  // SciD1D
      std::ifstream mufSciD1D(TString(mufiles[k*6]));
      std::vector<double> vEvID1D;
      std::vector<double> vEdep1D;
     
      while (!mufSciD1D.eof()) {
         double EvID1, Edep1;
	     mufSciD1D >> EvID1 >> Edep1;
	     vEvID1D.push_back(EvID1);
	     vEdep1D.push_back(Edep1);
	  }
	  vEvID1D.pop_back(); vEdep1D.pop_back();    
      vEvID1D.pop_back(); vEdep1D.pop_back();    
      
      mufSciD1D.close();
      allvEvID1Dmu.push_back(vEvID1D);
      allvEdep1Dmu.push_back(vEdep1D);


      // SciD2D
      std::ifstream mufSciD2D(TString(mufiles[(k*6)+1]));
      std::vector<double> vEvID2D;
      std::vector<double> vEdep2D;
     
      while (!mufSciD2D.eof()) {
         double EvID2, Edep2;
	     mufSciD2D >> EvID2 >> Edep2;
	     vEvID2D.push_back(EvID2);
	     vEdep2D.push_back(Edep2);
	  }
	  vEvID2D.pop_back(); vEdep2D.pop_back();    
      vEvID2D.pop_back(); vEdep2D.pop_back();    
      
      mufSciD2D.close();
      allvEvID2Dmu.push_back(vEvID2D);
      allvEdep2Dmu.push_back(vEdep2D);


      // SciD3D
      std::ifstream mufSciD3D(TString(mufiles[(k*6)+2]));
      std::vector<double> vEvID3D;
      std::vector<double> vEdep3D;
     
      while (!mufSciD3D.eof()) {
         double EvID3, Edep3;
	     mufSciD3D >> EvID3 >> Edep3;
	     vEvID3D.push_back(EvID3);
	     vEdep3D.push_back(Edep3);
	  }
	  vEvID3D.pop_back(); vEdep3D.pop_back();    
      vEvID3D.pop_back(); vEdep3D.pop_back();    
      
      mufSciD3D.close();
      allvEvID3Dmu.push_back(vEvID3D);
      allvEdep3Dmu.push_back(vEdep3D);


      // SciD1U
      std::ifstream mufSciD1U(TString(mufiles[(k*6)+3]));
      std::vector<double> vEvID1U;
      std::vector<double> vEdep1U;
     
      while (!mufSciD1U.eof()) {
         double EvID1, Edep1;
	     mufSciD1U >> EvID1 >> Edep1;
	     vEvID1U.push_back(EvID1);
	     vEdep1U.push_back(Edep1);
	  }
	  vEvID1U.pop_back(); vEdep1U.pop_back();    
      vEvID1U.pop_back(); vEdep1U.pop_back();    
      
      mufSciD1U.close();
      allvEvID1Umu.push_back(vEvID1U);
      allvEdep1Umu.push_back(vEdep1U);


      // SciD2U
      std::ifstream mufSciD2U(TString(mufiles[(k*6)+4]));
      std::vector<double> vEvID2U;
      std::vector<double> vEdep2U;
     
      while (!mufSciD2U.eof()) {
         double EvID2, Edep2;
	     mufSciD2U >> EvID2 >> Edep2;
	     vEvID2U.push_back(EvID2);
	     vEdep2U.push_back(Edep2);
	  }
	  vEvID2U.pop_back(); vEdep2U.pop_back();    
      vEvID2U.pop_back(); vEdep2U.pop_back();    
      
      mufSciD2U.close();
      allvEvID2Umu.push_back(vEvID2U);
      allvEdep2Umu.push_back(vEdep2U);


      // SciD3U
      std::ifstream mufSciD3U(TString(mufiles[(k*6)+5]));
      std::vector<double> vEvID3U;
      std::vector<double> vEdep3U;
     
      while (!mufSciD3U.eof()) {
         double EvID3, Edep3;
	     mufSciD3U >> EvID3 >> Edep3;
	     vEvID3U.push_back(EvID3);
	     vEdep3U.push_back(Edep3);
	  }
	  vEvID3U.pop_back(); vEdep3U.pop_back();    
      vEvID3U.pop_back(); vEdep3U.pop_back();    
      
      mufSciD3U.close();
      allvEvID3Umu.push_back(vEvID3U);
      allvEdep3Umu.push_back(vEdep3U);

   }

    
   //-------------------------------------------------------------------
   //                     Bin-by-bin analysis
   //                          Mu-decay
   //-------------------------------------------------------------------     
     
    
	  
   for (int i=0; i<allvEvID1Dmu.size(); i++) {

      std::cout << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------- Mu-decay -------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


      // Mu-decay D-stream 	
      counterD = 0;
      for (int a=0; a<allvEvID3Dmu[0].size(); a++) {
         if (allvEdep3Dmu[i][a] >= Ethr3) {
			counterD++;
	     }
	  }
	  
      for (int m=0; m < nsamps; m++) {
	     Ethr = Ethrmu[m];
         Xray = 0; elec = 0;

		 for (int j=0; j<allvEvID1Dmu[0].size(); j++) {
		    if (allvEdep3Dmu[i][j] >= Ethr3) {	
			   tPex = 0;
			   if (allvEdep1Dmu[i][j] < Ethr) {
				  tPex += 1;   
			   }
				
			   if (allvEdep2Dmu[i][j] < Ethr) {
				  tPex += 1;
			   }
				
			   if ((allvEdep3Dmu[i][j] >= Ethr3) && (allvEdep3Dmu[i][j] < 10) && ((tPex == 2) || (tPex == 1))) {
				  Xray += 1;
			   } else {
				  elec += 1;
			   }	
		    }   
         }

         PeXvectorD[i][m] = Xray/(double)(counterD);
         PeevectorD[i][m] = elec/(double)(counterD); 
       
         std::cout << "counterD = " << counterD << std::endl;
       
         //std::cout << " PeXD[" << i << "][" << m << "] = " << PeXvectorD[i][m] << " PeeD[" << i << "][" << m << "] = " << PeevectorD[i][m] << std::endl;
     

      }   
       
      
      // Mu-decay U-stream 	
      counterU = 0;
      for (int a=0; a<allvEvID3Umu[0].size(); a++) {
         if (allvEdep3Umu[i][a] >= Ethr3) {
			counterU++;
	     }
	  }
	  
      for (int m=0; m < nsamps; m++) {
	     Ethr = Ethrmu[m];
         Xray = 0; elec = 0;

		 for (int j=0; j<allvEvID1Umu[0].size(); j++) {
			if (allvEdep3Umu[i][j] >= Ethr3) {	  				  
			   tPex = 0;
			   if (allvEdep1Umu[i][j] < Ethr) {
				  tPex += 1;   
			   }
				
			   if (allvEdep2Umu[i][j] < Ethr) {
				  tPex += 1;
			   }
				
			   if ((allvEdep3Umu[i][j] >= Ethr3) && (allvEdep3Umu[i][j] < 10) && ((tPex == 2) || (tPex == 1))) {
				  Xray += 1;
			   } else {
				  elec += 1;
			   }	
			}   
		 }

         PeXvectorU[i][m] = Xray/(double)(counterU);
         PeevectorU[i][m] = elec/(double)(counterU); 
        
         std::cout << "counterU = " << counterU << std::endl;
       
         //std::cout << " PeXU[" << i << "][" << m << "] = " << PeXvectorU[i][m] << " PeeU[" << i << "][" << m << "] = " << PeevectorU[i][m] << std::endl;
     

      } 
       
        
   }




   //-------------------------------------------------------------------
   //                     Plotting business
   //-------------------------------------------------------------------     
    
    
   std::cout << std::endl;
   std::cout << "\033[1;33m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;33m-------------------- Plotting business -------------------\033[0m" << std::endl;
   std::cout << "\033[1;33m----------------------------------------------------------\033[0m" << std::endl;

  
   // Mu-decay 3-mm
   float PeXarr250mu3AlD[nsamps] = {};
   float Peearr250mu3AlD[nsamps] = {};
   float PeXarr500mu3AlD[nsamps] = {};
   float Peearr500mu3AlD[nsamps] = {};
   float PeXarr750mu3AlD[nsamps] = {};
   float Peearr750mu3AlD[nsamps] = {};
   float PeXarr250mu3AlU[nsamps] = {};
   float Peearr250mu3AlU[nsamps] = {};
   float PeXarr500mu3AlU[nsamps] = {};
   float Peearr500mu3AlU[nsamps] = {};
   float PeXarr750mu3AlU[nsamps] = {};
   float Peearr750mu3AlU[nsamps] = {};
   // Mu-decay 6-mm
   float PeXarr250mu6AlD[nsamps] = {};
   float Peearr250mu6AlD[nsamps] = {};
   float PeXarr500mu6AlD[nsamps] = {};
   float Peearr500mu6AlD[nsamps] = {};
   float PeXarr750mu6AlD[nsamps] = {};
   float Peearr750mu6AlD[nsamps] = {};
   float PeXarr250mu6AlU[nsamps] = {};
   float Peearr250mu6AlU[nsamps] = {};
   float PeXarr500mu6AlU[nsamps] = {};
   float Peearr500mu6AlU[nsamps] = {};
   float PeXarr750mu6AlU[nsamps] = {};
   float Peearr750mu6AlU[nsamps] = {};

     
   for (int i=0; i<nsamps; i++) {
      PeXarr250mu3AlD[i] = PeXvectorD[0][i];
      Peearr250mu3AlD[i] = PeevectorD[0][i];
      PeXarr500mu3AlD[i] = PeXvectorD[1][i];
      Peearr500mu3AlD[i] = PeevectorD[1][i];
      PeXarr750mu3AlD[i] = PeXvectorD[2][i];
      Peearr750mu3AlD[i] = PeevectorD[2][i];
      PeXarr250mu3AlU[i] = PeXvectorU[0][i];
      Peearr250mu3AlU[i] = PeevectorU[0][i];
      PeXarr500mu3AlU[i] = PeXvectorU[1][i];
      Peearr500mu3AlU[i] = PeevectorU[1][i];
      PeXarr750mu3AlU[i] = PeXvectorU[2][i];
      Peearr750mu3AlU[i] = PeevectorU[2][i];

      PeXarr250mu6AlD[i] = PeXvectorD[3][i];
      Peearr250mu6AlD[i] = PeevectorD[3][i];
      PeXarr500mu6AlD[i] = PeXvectorD[4][i];
      Peearr500mu6AlD[i] = PeevectorD[4][i];
      PeXarr750mu6AlD[i] = PeXvectorD[5][i];
      Peearr750mu6AlD[i] = PeevectorD[5][i];
      PeXarr250mu6AlU[i] = PeXvectorU[3][i];
      Peearr250mu6AlU[i] = PeevectorU[3][i];
      PeXarr500mu6AlU[i] = PeXvectorU[4][i];
      Peearr500mu6AlU[i] = PeevectorU[4][i];
      PeXarr750mu6AlU[i] = PeXvectorU[5][i];
      Peearr750mu6AlU[i] = PeevectorU[5][i];
  
   }
  
  
   
   TCanvas *c = new TCanvas("c","E_{THR}",800,600);
   c->Divide(3,2);
   c->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr250mu3AlSciDet1PeXD = new TGraph(nsamps,Ethrmu,PeXarr250mu3AlD);
   gr250mu3AlSciDet1PeXD->SetTitle("10 MeV: 3-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3} D-stream [10^6 events]");
   gr250mu3AlSciDet1PeXD->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr250mu3AlSciDet1PeXD->GetXaxis()->SetRangeUser(0,2.05);
   gr250mu3AlSciDet1PeXD->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr250mu3AlSciDet1PeXD->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr250mu3AlSciDet1PeXD->GetYaxis()->SetTitleOffset(1.8);
   gr250mu3AlSciDet1PeXD->SetMarkerColor(kBlack);
   gr250mu3AlSciDet1PeXD->SetMarkerStyle(33);
   gr250mu3AlSciDet1PeXD->SetLineColor(kBlack);
   gr250mu3AlSciDet1PeXD->Draw("ALP");
   TGraph *gr250mu3AlSciDet1PeeD = new TGraph(nsamps,Ethrmu,Peearr250mu3AlD); 
   gr250mu3AlSciDet1PeeD->SetMarkerColor(kRed);
   gr250mu3AlSciDet1PeeD->SetMarkerStyle(31);
   gr250mu3AlSciDet1PeeD->SetLineColor(kRed);
   gr250mu3AlSciDet1PeeD->Draw("LP");
   leg250mu3AlSciDet1PeXPeeD = new TLegend(0.2,-0.005,0.4,0.08);
   leg250mu3AlSciDet1PeXPeeD->AddEntry(gr250mu3AlSciDet1PeXD,"P_{e->X}","lp");
   leg250mu3AlSciDet1PeXPeeD->AddEntry(gr250mu3AlSciDet1PeeD,"P_{e->e}","lp");
   leg250mu3AlSciDet1PeXPeeD->Draw();
  
   c->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr500mu3AlSciDet1PeXD = new TGraph(nsamps,Ethrmu,PeXarr500mu3AlD);  
   gr500mu3AlSciDet1PeXD->SetTitle("10 MeV: 3-mm Al + 2x5-mm SCiD_{1,2} + 500-mm SciD_{3} D-stream [10^6 events]");
   gr500mu3AlSciDet1PeXD->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr500mu3AlSciDet1PeXD->GetXaxis()->SetRangeUser(0,2.05);
   gr500mu3AlSciDet1PeXD->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr500mu3AlSciDet1PeXD->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr500mu3AlSciDet1PeXD->GetYaxis()->SetTitleOffset(1.8);
   gr500mu3AlSciDet1PeXD->SetMarkerColor(kBlack);
   gr500mu3AlSciDet1PeXD->SetMarkerStyle(33);
   gr500mu3AlSciDet1PeXD->SetLineColor(kBlack);
   gr500mu3AlSciDet1PeXD->Draw("ALP");
   TGraph *gr500mu3AlSciDet1PeeD = new TGraph(nsamps,Ethrmu,Peearr500mu3AlD); 
   gr500mu3AlSciDet1PeeD->SetMarkerColor(kRed);
   gr500mu3AlSciDet1PeeD->SetMarkerStyle(31);
   gr500mu3AlSciDet1PeeD->SetLineColor(kRed);
   gr500mu3AlSciDet1PeeD->Draw("LP");
   leg500mu3AlSciDet1PeXPeeD = new TLegend(0.2,-0.005,0.4,0.08);
   leg500mu3AlSciDet1PeXPeeD->AddEntry(gr500mu3AlSciDet1PeXD,"P_{e->X}","lp");
   leg500mu3AlSciDet1PeXPeeD->AddEntry(gr500mu3AlSciDet1PeeD,"P_{e->e}","lp");
   leg500mu3AlSciDet1PeXPeeD->Draw();

   c->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr750mu3AlSciDet1PeXD = new TGraph(nsamps,Ethrmu,PeXarr750mu3AlD); 
   gr750mu3AlSciDet1PeXD->SetTitle("10 MeV: 3-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3} D-stream [10^6 events]");
   gr750mu3AlSciDet1PeXD->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr750mu3AlSciDet1PeXD->GetXaxis()->SetRangeUser(0,2.05);
   gr750mu3AlSciDet1PeXD->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr750mu3AlSciDet1PeXD->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr750mu3AlSciDet1PeXD->GetYaxis()->SetTitleOffset(1.8);
   gr750mu3AlSciDet1PeXD->SetMarkerColor(kBlack);
   gr750mu3AlSciDet1PeXD->SetMarkerStyle(33);
   gr750mu3AlSciDet1PeXD->SetLineColor(kBlack);
   gr750mu3AlSciDet1PeXD->Draw("ALP");
   TGraph *gr750mu3AlSciDet1PeeD = new TGraph(nsamps,Ethrmu,Peearr750mu3AlD); 
   gr750mu3AlSciDet1PeeD->SetMarkerColor(kRed);
   gr750mu3AlSciDet1PeeD->SetMarkerStyle(31);
   gr750mu3AlSciDet1PeeD->SetLineColor(kRed);
   gr750mu3AlSciDet1PeeD->Draw("LP");
   leg750mu3AlSciDet1PeXPeeD = new TLegend(0.2,-0.005,0.4,0.08);
   leg750mu3AlSciDet1PeXPeeD->AddEntry(gr750mu3AlSciDet1PeXD,"P_{e->X}","lp");
   leg750mu3AlSciDet1PeXPeeD->AddEntry(gr750mu3AlSciDet1PeeD,"P_{e->e}","lp");
   leg750mu3AlSciDet1PeXPeeD->Draw();
  
   c->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr250mu6AlSciDet1PeXD = new TGraph(nsamps,Ethrmu,PeXarr250mu6AlD);
   gr250mu6AlSciDet1PeXD->SetTitle("10 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3} D-stream [10^6 events]");
   gr250mu6AlSciDet1PeXD->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr250mu6AlSciDet1PeXD->GetXaxis()->SetRangeUser(0,2.05);
   gr250mu6AlSciDet1PeXD->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr250mu6AlSciDet1PeXD->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr250mu6AlSciDet1PeXD->GetYaxis()->SetTitleOffset(1.8);
   gr250mu6AlSciDet1PeXD->SetMarkerColor(kBlack);
   gr250mu6AlSciDet1PeXD->SetMarkerStyle(33);
   gr250mu6AlSciDet1PeXD->SetLineColor(kBlack);
   gr250mu6AlSciDet1PeXD->Draw("ALP");
   TGraph *gr250mu6AlSciDet1PeeD = new TGraph(nsamps,Ethrmu,Peearr250mu6AlD); 
   gr250mu6AlSciDet1PeeD->SetMarkerColor(kRed);
   gr250mu6AlSciDet1PeeD->SetMarkerStyle(31);
   gr250mu6AlSciDet1PeeD->SetLineColor(kRed);
   gr250mu6AlSciDet1PeeD->Draw("LP");
   leg250mu6AlSciDet1PeXPeeD = new TLegend(0.2,-0.005,0.4,0.08);
   leg250mu6AlSciDet1PeXPeeD->AddEntry(gr250mu6AlSciDet1PeXD,"P_{e->X}","lp");
   leg250mu6AlSciDet1PeXPeeD->AddEntry(gr250mu6AlSciDet1PeeD,"P_{e->e}","lp");
   leg250mu6AlSciDet1PeXPeeD->Draw();
    
   c->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr500mu6AlSciDet1PeXD = new TGraph(nsamps,Ethrmu,PeXarr500mu6AlD);
   gr500mu6AlSciDet1PeXD->SetTitle("10 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3} D-stream [10^6 events]");
   gr500mu6AlSciDet1PeXD->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr500mu6AlSciDet1PeXD->GetXaxis()->SetRangeUser(0,2.05);
   gr500mu6AlSciDet1PeXD->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr500mu6AlSciDet1PeXD->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr500mu6AlSciDet1PeXD->GetYaxis()->SetTitleOffset(1.8);
   gr500mu6AlSciDet1PeXD->SetMarkerColor(kBlack);
   gr500mu6AlSciDet1PeXD->SetMarkerStyle(33);
   gr500mu6AlSciDet1PeXD->SetLineColor(kBlack);
   gr500mu6AlSciDet1PeXD->Draw("ALP");
   TGraph *gr500mu6AlSciDet1PeeD = new TGraph(nsamps,Ethrmu,Peearr500mu6AlD); 
   gr500mu6AlSciDet1PeeD->SetMarkerColor(kRed);
   gr500mu6AlSciDet1PeeD->SetMarkerStyle(31);
   gr500mu6AlSciDet1PeeD->SetLineColor(kRed);
   gr500mu6AlSciDet1PeeD->Draw("LP");
   leg500mu6AlSciDet1PeXPeeD = new TLegend(0.2,-0.005,0.4,0.08);
   leg500mu6AlSciDet1PeXPeeD->AddEntry(gr500mu6AlSciDet1PeXD,"P_{e->X}","lp");
   leg500mu6AlSciDet1PeXPeeD->AddEntry(gr500mu6AlSciDet1PeeD,"P_{e->e}","lp");
   leg500mu6AlSciDet1PeXPeeD->Draw();
    
   c->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr750mu6AlSciDet1PeXD = new TGraph(nsamps,Ethrmu,PeXarr750mu6AlD);
   gr750mu6AlSciDet1PeXD->SetTitle("10 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3} D-stream [10^6 events]");
   gr750mu6AlSciDet1PeXD->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr750mu6AlSciDet1PeXD->GetXaxis()->SetRangeUser(0,2.05);
   gr750mu6AlSciDet1PeXD->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr750mu6AlSciDet1PeXD->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr750mu6AlSciDet1PeXD->GetYaxis()->SetTitleOffset(1.8);
   gr750mu6AlSciDet1PeXD->SetMarkerColor(kBlack);
   gr750mu6AlSciDet1PeXD->SetMarkerStyle(33);
   gr750mu6AlSciDet1PeXD->SetLineColor(kBlack);
   gr750mu6AlSciDet1PeXD->Draw("ALP");
   TGraph *gr750mu6AlSciDet1PeeD = new TGraph(nsamps,Ethrmu,Peearr750mu6AlD); 
   gr750mu6AlSciDet1PeeD->SetMarkerColor(kRed);
   gr750mu6AlSciDet1PeeD->SetMarkerStyle(31);
   gr750mu6AlSciDet1PeeD->SetLineColor(kRed);
   gr750mu6AlSciDet1PeeD->Draw("LP");
   leg750mu6AlSciDet1PeXPeeD = new TLegend(0.2,-0.005,0.4,0.08);
   leg750mu6AlSciDet1PeXPeeD->AddEntry(gr750mu6AlSciDet1PeXD,"P_{e->X}","lp");
   leg750mu6AlSciDet1PeXPeeD->AddEntry(gr750mu6AlSciDet1PeeD,"P_{e->e}","lp");
   leg750mu6AlSciDet1PeXPeeD->Draw();

   c->SaveAs("Bubble4BinPlot_PeX_Pee_3mm_6mm_10_MeV_D_stream.pdf");
   c->SaveAs("Bubble4BinPlot_PeX_Pee_3mm_6mm_10_MeV_D_stream.png");
   c->SaveAs("Bubble4BinPlot_PeX_Pee_3mm_6mm_10_MeV_D_stream.C");
 
  
  
   TCanvas *d = new TCanvas("d","E_{THR}",800,600);
   d->Divide(3,2);
   d->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr250mu3AlSciDet1PeXU = new TGraph(nsamps,Ethrmu,PeXarr250mu3AlU);
   gr250mu3AlSciDet1PeXU->SetTitle("10 MeV: 3-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3} U-stream [10^6 events]");
   gr250mu3AlSciDet1PeXU->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr250mu3AlSciDet1PeXU->GetXaxis()->SetRangeUser(0,2.05);
   gr250mu3AlSciDet1PeXU->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr250mu3AlSciDet1PeXU->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr250mu3AlSciDet1PeXU->GetYaxis()->SetTitleOffset(1.8);
   gr250mu3AlSciDet1PeXU->SetMarkerColor(kBlack);
   gr250mu3AlSciDet1PeXU->SetMarkerStyle(33);
   gr250mu3AlSciDet1PeXU->SetLineColor(kBlack);
   gr250mu3AlSciDet1PeXU->Draw("ALP");
   TGraph *gr250mu3AlSciDet1PeeU = new TGraph(nsamps,Ethrmu,Peearr250mu3AlU); 
   gr250mu3AlSciDet1PeeU->SetMarkerColor(kRed);
   gr250mu3AlSciDet1PeeU->SetMarkerStyle(31);
   gr250mu3AlSciDet1PeeU->SetLineColor(kRed);
   gr250mu3AlSciDet1PeeU->Draw("LP");
   leg250mu3AlSciDet1PeXPeeU = new TLegend(0.2,-0.005,0.4,0.08);
   leg250mu3AlSciDet1PeXPeeU->AddEntry(gr250mu3AlSciDet1PeXU,"P_{e->X}","lp");
   leg250mu3AlSciDet1PeXPeeU->AddEntry(gr250mu3AlSciDet1PeeU,"P_{e->e}","lp");
   leg250mu3AlSciDet1PeXPeeU->Draw();
  
   d->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr500mu3AlSciDet1PeXU = new TGraph(nsamps,Ethrmu,PeXarr500mu3AlU);  
   gr500mu3AlSciDet1PeXU->SetTitle("10 MeV: 3-mm Al + 2x5-mm SCiD_{1,2} + 500-mm SciD_{3} U-stream [10^6 events]");
   gr500mu3AlSciDet1PeXU->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr500mu3AlSciDet1PeXU->GetXaxis()->SetRangeUser(0,2.05);
   gr500mu3AlSciDet1PeXU->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr500mu3AlSciDet1PeXU->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr500mu3AlSciDet1PeXU->GetYaxis()->SetTitleOffset(1.8);
   gr500mu3AlSciDet1PeXU->SetMarkerColor(kBlack);
   gr500mu3AlSciDet1PeXU->SetMarkerStyle(33);
   gr500mu3AlSciDet1PeXU->SetLineColor(kBlack);
   gr500mu3AlSciDet1PeXU->Draw("ALP");
   TGraph *gr500mu3AlSciDet1PeeU = new TGraph(nsamps,Ethrmu,Peearr500mu3AlU); 
   gr500mu3AlSciDet1PeeU->SetMarkerColor(kRed);
   gr500mu3AlSciDet1PeeU->SetMarkerStyle(31);
   gr500mu3AlSciDet1PeeU->SetLineColor(kRed);
   gr500mu3AlSciDet1PeeU->Draw("LP");
   leg500mu3AlSciDet1PeXPeeU = new TLegend(0.2,-0.005,0.4,0.08);
   leg500mu3AlSciDet1PeXPeeU->AddEntry(gr500mu3AlSciDet1PeXU,"P_{e->X}","lp");
   leg500mu3AlSciDet1PeXPeeU->AddEntry(gr500mu3AlSciDet1PeeU,"P_{e->e}","lp");
   leg500mu3AlSciDet1PeXPeeU->Draw();

   d->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr750mu3AlSciDet1PeXU = new TGraph(nsamps,Ethrmu,PeXarr750mu3AlU); 
   gr750mu3AlSciDet1PeXU->SetTitle("10 MeV: 3-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3} U-stream [10^6 events]");
   gr750mu3AlSciDet1PeXU->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr750mu3AlSciDet1PeXU->GetXaxis()->SetRangeUser(0,2.05);
   gr750mu3AlSciDet1PeXU->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr750mu3AlSciDet1PeXU->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr750mu3AlSciDet1PeXU->GetYaxis()->SetTitleOffset(1.8);
   gr750mu3AlSciDet1PeXU->SetMarkerColor(kBlack);
   gr750mu3AlSciDet1PeXU->SetMarkerStyle(33);
   gr750mu3AlSciDet1PeXU->SetLineColor(kBlack);
   gr750mu3AlSciDet1PeXU->Draw("ALP");
   TGraph *gr750mu3AlSciDet1PeeU = new TGraph(nsamps,Ethrmu,Peearr750mu3AlU); 
   gr750mu3AlSciDet1PeeU->SetMarkerColor(kRed);
   gr750mu3AlSciDet1PeeU->SetMarkerStyle(31);
   gr750mu3AlSciDet1PeeU->SetLineColor(kRed);
   gr750mu3AlSciDet1PeeU->Draw("LP");
   leg750mu3AlSciDet1PeXPeeU = new TLegend(0.2,-0.005,0.4,0.08);
   leg750mu3AlSciDet1PeXPeeU->AddEntry(gr750mu3AlSciDet1PeXU,"P_{e->X}","lp");
   leg750mu3AlSciDet1PeXPeeU->AddEntry(gr750mu3AlSciDet1PeeU,"P_{e->e}","lp");
   leg750mu3AlSciDet1PeXPeeU->Draw();
  
   d->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr250mu6AlSciDet1PeXU = new TGraph(nsamps,Ethrmu,PeXarr250mu6AlU);
   gr250mu6AlSciDet1PeXU->SetTitle("10 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3} U-stream [10^6 events]");
   gr250mu6AlSciDet1PeXU->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr250mu6AlSciDet1PeXU->GetXaxis()->SetRangeUser(0,2.05);
   gr250mu6AlSciDet1PeXU->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr250mu6AlSciDet1PeXU->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr250mu6AlSciDet1PeXU->GetYaxis()->SetTitleOffset(1.8);
   gr250mu6AlSciDet1PeXU->SetMarkerColor(kBlack);
   gr250mu6AlSciDet1PeXU->SetMarkerStyle(33);
   gr250mu6AlSciDet1PeXU->SetLineColor(kBlack);
   gr250mu6AlSciDet1PeXU->Draw("ALP");
   TGraph *gr250mu6AlSciDet1PeeU = new TGraph(nsamps,Ethrmu,Peearr250mu6AlU); 
   gr250mu6AlSciDet1PeeU->SetMarkerColor(kRed);
   gr250mu6AlSciDet1PeeU->SetMarkerStyle(31);
   gr250mu6AlSciDet1PeeU->SetLineColor(kRed);
   gr250mu6AlSciDet1PeeU->Draw("LP");
   leg250mu6AlSciDet1PeXPeeU = new TLegend(0.2,-0.005,0.4,0.08);
   leg250mu6AlSciDet1PeXPeeU->AddEntry(gr250mu6AlSciDet1PeXU,"P_{e->X}","lp");
   leg250mu6AlSciDet1PeXPeeU->AddEntry(gr250mu6AlSciDet1PeeU,"P_{e->e}","lp");
   leg250mu6AlSciDet1PeXPeeU->Draw();
    
   d->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr500mu6AlSciDet1PeXU = new TGraph(nsamps,Ethrmu,PeXarr500mu6AlU);
   gr500mu6AlSciDet1PeXU->SetTitle("10 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3} U-stream [10^6 events]");
   gr500mu6AlSciDet1PeXU->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr500mu6AlSciDet1PeXU->GetXaxis()->SetRangeUser(0,2.05);
   gr500mu6AlSciDet1PeXU->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr500mu6AlSciDet1PeXU->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr500mu6AlSciDet1PeXU->GetYaxis()->SetTitleOffset(1.8);
   gr500mu6AlSciDet1PeXU->SetMarkerColor(kBlack);
   gr500mu6AlSciDet1PeXU->SetMarkerStyle(33);
   gr500mu6AlSciDet1PeXU->SetLineColor(kBlack);
   gr500mu6AlSciDet1PeXU->Draw("ALP");
   TGraph *gr500mu6AlSciDet1PeeU = new TGraph(nsamps,Ethrmu,Peearr500mu6AlU); 
   gr500mu6AlSciDet1PeeU->SetMarkerColor(kRed);
   gr500mu6AlSciDet1PeeU->SetMarkerStyle(31);
   gr500mu6AlSciDet1PeeU->SetLineColor(kRed);
   gr500mu6AlSciDet1PeeU->Draw("LP");
   leg500mu6AlSciDet1PeXPeeU = new TLegend(0.2,-0.005,0.4,0.08);
   leg500mu6AlSciDet1PeXPeeU->AddEntry(gr500mu6AlSciDet1PeXU,"P_{e->X}","lp");
   leg500mu6AlSciDet1PeXPeeU->AddEntry(gr500mu6AlSciDet1PeeU,"P_{e->e}","lp");
   leg500mu6AlSciDet1PeXPeeU->Draw();
    
   d->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr750mu6AlSciDet1PeXU = new TGraph(nsamps,Ethrmu,PeXarr750mu6AlU);
   gr750mu6AlSciDet1PeXU->SetTitle("10 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3} U-stream [10^6 events]");
   gr750mu6AlSciDet1PeXU->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr750mu6AlSciDet1PeXU->GetXaxis()->SetRangeUser(0,2.05);
   gr750mu6AlSciDet1PeXU->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr750mu6AlSciDet1PeXU->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr750mu6AlSciDet1PeXU->GetYaxis()->SetTitleOffset(1.8);
   gr750mu6AlSciDet1PeXU->SetMarkerColor(kBlack);
   gr750mu6AlSciDet1PeXU->SetMarkerStyle(33);
   gr750mu6AlSciDet1PeXU->SetLineColor(kBlack);
   gr750mu6AlSciDet1PeXU->Draw("ALP");
   TGraph *gr750mu6AlSciDet1PeeU = new TGraph(nsamps,Ethrmu,Peearr750mu6AlU); 
   gr750mu6AlSciDet1PeeU->SetMarkerColor(kRed);
   gr750mu6AlSciDet1PeeU->SetMarkerStyle(31);
   gr750mu6AlSciDet1PeeU->SetLineColor(kRed);
   gr750mu6AlSciDet1PeeU->Draw("LP");
   leg750mu6AlSciDet1PeXPeeU = new TLegend(0.2,-0.005,0.4,0.08);
   leg750mu6AlSciDet1PeXPeeU->AddEntry(gr750mu6AlSciDet1PeXU,"P_{e->X}","lp");
   leg750mu6AlSciDet1PeXPeeU->AddEntry(gr750mu6AlSciDet1PeeU,"P_{e->e}","lp");
   leg750mu6AlSciDet1PeXPeeU->Draw();

   d->SaveAs("Bubble4BinPlot_PeX_Pee_3mm_6mm_10_MeV_U_stream.pdf");
   d->SaveAs("Bubble4BinPlot_PeX_Pee_3mm_6mm_10_MeV_U_stream.png");
   d->SaveAs("Bubble4BinPlot_PeX_Pee_3mm_6mm_10_MeV_U_stream.C");
 
  
  
  
 }
 
 
 int main() {
   planarBINmu();
   return 0;
}  
