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

void planarMULTIeff(){

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
   // Mu-decay
   std::string filemuSciD1D = "../../simdata/planar/planar_MULTI_2x5mm_500mm_SciD_1mm_Al_5mm_Al_1e6mudecay_SciD1D.txt";
   std::string filemuSciD2D = "../../simdata/planar/planar_MULTI_2x5mm_500mm_SciD_1mm_Al_5mm_Al_1e6mudecay_SciD2D.txt";
   std::string filemuSciD3D = "../../simdata/planar/planar_MULTI_2x5mm_500mm_SciD_1mm_Al_5mm_Al_1e6mudecay_SciD3D.txt"; 
   std::string filemuSciD1U = "../../simdata/planar/planar_MULTI_2x5mm_500mm_SciD_1mm_Al_5mm_Al_1e6mudecay_SciD1U.txt";
   std::string filemuSciD2U = "../../simdata/planar/planar_MULTI_2x5mm_500mm_SciD_1mm_Al_5mm_Al_1e6mudecay_SciD2U.txt";
   std::string filemuSciD3U = "../../simdata/planar/planar_MULTI_2x5mm_500mm_SciD_1mm_Al_5mm_Al_1e6mudecay_SciD3U.txt"; 
   // X-ray cascade
   std::string filexSciD1D = "../../simdata/planar/planar_MULTI_2x5mm_500mm_SciD_1mm_Al_5mm_Al_1e6goldcascade_SciD1D.txt";
   std::string filexSciD2D = "../../simdata/planar/planar_MULTI_2x5mm_500mm_SciD_1mm_Al_5mm_Al_1e6goldcascade_SciD2D.txt";
   std::string filexSciD3D = "../../simdata/planar/planar_MULTI_2x5mm_500mm_SciD_1mm_Al_5mm_Al_1e6goldcascade_SciD3D.txt";
   std::string filexSciD1U = "../../simdata/planar/planar_MULTI_2x5mm_500mm_SciD_1mm_Al_5mm_Al_1e6goldcascade_SciD1U.txt";
   std::string filexSciD2U = "../../simdata/planar/planar_MULTI_2x5mm_500mm_SciD_1mm_Al_5mm_Al_1e6goldcascade_SciD2U.txt";
   std::string filexSciD3U = "../../simdata/planar/planar_MULTI_2x5mm_500mm_SciD_1mm_Al_5mm_Al_1e6goldcascade_SciD3U.txt";



   // Vectors with filenames   
   std::vector<std::string> mufiles;
   std::vector<std::string> Xfiles;

   // Mu-decay
   mufiles.push_back(filemuSciD1D);
   mufiles.push_back(filemuSciD2D);
   mufiles.push_back(filemuSciD3D);
   mufiles.push_back(filemuSciD1U);
   mufiles.push_back(filemuSciD2U);
   mufiles.push_back(filemuSciD3U);
   // X-ray cascade
   Xfiles.push_back(filexSciD1D);
   Xfiles.push_back(filexSciD2D);
   Xfiles.push_back(filexSciD3D);
   Xfiles.push_back(filexSciD1U);
   Xfiles.push_back(filexSciD2U);
   Xfiles.push_back(filexSciD3U);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep, EventID;
   float iEventID;

   const int nsamps = 101;
   float Ethr1 = 0.5;
   float Ethr2 = 0.5;
   float Ethr31 = 0.8;
   float Ethr32 = 8;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
   
   // Storage vectors
   // Normalisation 1 [rel], D && U
   std::vector< std::vector<double> > PeevectorANDN1((mufiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorANDN1((mufiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXevectorANDN1((Xfiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorANDN1((Xfiles.size())/6,std::vector<double>(nsamps));
   // Normalisation 2 [abs], D && U
   std::vector< std::vector<double> > PeevectorANDN2((mufiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorANDN2((mufiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXevectorANDN2((Xfiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorANDN2((Xfiles.size())/6,std::vector<double>(nsamps));
   // Normalisation 1 [rel], D || U
   std::vector< std::vector<double> > PeevectorORN1((mufiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorORN1((mufiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXevectorORN1((Xfiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorORN1((Xfiles.size())/6,std::vector<double>(nsamps));
   // Normalisation 2 abs], D || U
   std::vector< std::vector<double> > PeevectorORN2((mufiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorORN2((mufiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXevectorORN2((Xfiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorORN2((Xfiles.size())/6,std::vector<double>(nsamps));



   
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

   // X-ray cascade
   std::vector< std::vector< double > > allvEvID1Dx;
   std::vector< std::vector< double > > allvEvID2Dx;
   std::vector< std::vector< double > > allvEvID3Dx;
   std::vector< std::vector< double > > allvEvID1Ux;
   std::vector< std::vector< double > > allvEvID2Ux;
   std::vector< std::vector< double > > allvEvID3Ux;
   std::vector< std::vector< double > > allvEdep1Dx;
   std::vector< std::vector< double > > allvEdep2Dx;
   std::vector< std::vector< double > > allvEdep3Dx;
   std::vector< std::vector< double > > allvEdep1Ux;
   std::vector< std::vector< double > > allvEdep2Ux;
   std::vector< std::vector< double > > allvEdep3Ux;


   float Ethr;
   int counterDX, counterUX, counterDmu, counterUmu, counterXX, counteree;
   int counterXXN2 = 1e6; int countereeN2 = 1e6; 
   int XXrayANDN1 = 0; // X-rays i-fied as X-rays
   int XXrayANDN2 = 0;
   int XXrayORN1 = 0;
   int XXrayORN2 = 0;
   int XelecANDN1 = 0; // X-rays i-fied as electrons
   int XelecANDN2 = 0;
   int XelecORN1 = 0;
   int XelecORN2 = 0;
   int eXrayANDN1 = 0; // electrons i-fied as X-rays
   int eXrayANDN2 = 0;
   int eXrayORN1 = 0;
   int eXrayORN2 = 0;
   int eelecANDN1 = 0; // electrons i-fied as electrons
   int eelecANDN2 = 0;
   int eelecORN1 = 0;
   int eelecORN2 = 0;
   
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
      std::vector<double> vEvID1Dmu;
      std::vector<double> vEdep1Dmu;
     
      while (!mufSciD1D.eof()) {
         double EvID1, Edep1;
	     mufSciD1D >> EvID1 >> Edep1;
	     vEvID1Dmu.push_back(EvID1);
	     vEdep1Dmu.push_back(Edep1);
	  }
	  vEvID1Dmu.pop_back(); vEdep1Dmu.pop_back();    
      vEvID1Dmu.pop_back(); vEdep1Dmu.pop_back();    
      
      mufSciD1D.close();
      allvEvID1Dmu.push_back(vEvID1Dmu);
      allvEdep1Dmu.push_back(vEdep1Dmu);


      // SciD2D
      std::ifstream mufSciD2D(TString(mufiles[(k*6)+1]));
      std::vector<double> vEvID2Dmu;
      std::vector<double> vEdep2Dmu;
     
      while (!mufSciD2D.eof()) {
         double EvID2, Edep2;
	     mufSciD2D >> EvID2 >> Edep2;
	     vEvID2Dmu.push_back(EvID2);
	     vEdep2Dmu.push_back(Edep2);
	  }
	  vEvID2Dmu.pop_back(); vEdep2Dmu.pop_back();    
      vEvID2Dmu.pop_back(); vEdep2Dmu.pop_back();    
      
      mufSciD2D.close();
      allvEvID2Dmu.push_back(vEvID2Dmu);
      allvEdep2Dmu.push_back(vEdep2Dmu);


      // SciD3D
      std::ifstream mufSciD3D(TString(mufiles[(k*6)+2]));
      std::vector<double> vEvID3Dmu;
      std::vector<double> vEdep3Dmu;
     
      while (!mufSciD3D.eof()) {
         double EvID3, Edep3;
	     mufSciD3D >> EvID3 >> Edep3;
	     vEvID3Dmu.push_back(EvID3);
	     vEdep3Dmu.push_back(Edep3);
	  }
	  vEvID3Dmu.pop_back(); vEdep3Dmu.pop_back();    
      vEvID3Dmu.pop_back(); vEdep3Dmu.pop_back();    
      
      mufSciD3D.close();
      allvEvID3Dmu.push_back(vEvID3Dmu);
      allvEdep3Dmu.push_back(vEdep3Dmu);


      // SciD1U
      std::ifstream mufSciD1U(TString(mufiles[(k*6)+3]));
      std::vector<double> vEvID1Umu;
      std::vector<double> vEdep1Umu;
     
      while (!mufSciD1U.eof()) {
         double EvID1, Edep1;
	     mufSciD1U >> EvID1 >> Edep1;
	     vEvID1Umu.push_back(EvID1);
	     vEdep1Umu.push_back(Edep1);
	  }
	  vEvID1Umu.pop_back(); vEdep1Umu.pop_back();    
      vEvID1Umu.pop_back(); vEdep1Umu.pop_back();    
      
      mufSciD1U.close();
      allvEvID1Umu.push_back(vEvID1Umu);
      allvEdep1Umu.push_back(vEdep1Umu);


      // SciD2U
      std::ifstream mufSciD2U(TString(mufiles[(k*6)+4]));
      std::vector<double> vEvID2Umu;
      std::vector<double> vEdep2Umu;
     
      while (!mufSciD2U.eof()) {
         double EvID2, Edep2;
	     mufSciD2U >> EvID2 >> Edep2;
	     vEvID2Umu.push_back(EvID2);
	     vEdep2Umu.push_back(Edep2);
	  }
	  vEvID2Umu.pop_back(); vEdep2Umu.pop_back();    
      vEvID2Umu.pop_back(); vEdep2Umu.pop_back();    
      
      mufSciD2U.close();
      allvEvID2Umu.push_back(vEvID2Umu);
      allvEdep2Umu.push_back(vEdep2Umu);


      // SciD3U
      std::ifstream mufSciD3U(TString(mufiles[(k*6)+5]));
      std::vector<double> vEvID3Umu;
      std::vector<double> vEdep3Umu;
     
      while (!mufSciD3U.eof()) {
         double EvID3, Edep3;
	     mufSciD3U >> EvID3 >> Edep3;
	     vEvID3Umu.push_back(EvID3);
	     vEdep3Umu.push_back(Edep3);
	  }
	  vEvID3Umu.pop_back(); vEdep3Umu.pop_back();    
      vEvID3Umu.pop_back(); vEdep3Umu.pop_back();    
      
      mufSciD3U.close();
      allvEvID3Umu.push_back(vEvID3Umu);
      allvEdep3Umu.push_back(vEdep3Umu);

   }
   
   
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m------------------- X-ray cascade ------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


   for (int k=0; k<((Xfiles.size())/6); k++) {
	  // SciD1D
      std::ifstream xfSciD1D(TString(Xfiles[k*6]));
      std::vector<double> vEvID1Dx;
      std::vector<double> vEdep1Dx;
     
      while (!xfSciD1D.eof()) {
         double EvID1, Edep1;
	     xfSciD1D >> EvID1 >> Edep1;
	     vEvID1Dx.push_back(EvID1);
	     vEdep1Dx.push_back(Edep1);
	  }
	  vEvID1Dx.pop_back(); vEdep1Dx.pop_back();    
      vEvID1Dx.pop_back(); vEdep1Dx.pop_back();    
      
      xfSciD1D.close();
      allvEvID1Dx.push_back(vEvID1Dx);
      allvEdep1Dx.push_back(vEdep1Dx);


      // SciD2D
      std::ifstream xfSciD2D(TString(Xfiles[(k*6)+1]));
      std::vector<double> vEvID2Dx;
      std::vector<double> vEdep2Dx;
     
      while (!xfSciD2D.eof()) {
         double EvID2, Edep2;
	     xfSciD2D >> EvID2 >> Edep2;
	     vEvID2Dx.push_back(EvID2);
	     vEdep2Dx.push_back(Edep2);
	  }
	  vEvID2Dx.pop_back(); vEdep2Dx.pop_back();    
      vEvID2Dx.pop_back(); vEdep2Dx.pop_back();    
      
      xfSciD2D.close();
      allvEvID2Dx.push_back(vEvID2Dx);
      allvEdep2Dx.push_back(vEdep2Dx);


      // SciD3D
      std::ifstream xfSciD3D(TString(Xfiles[(k*6)+2]));
      std::vector<double> vEvID3Dx;
      std::vector<double> vEdep3Dx;
     
      while (!xfSciD3D.eof()) {
         double EvID3, Edep3;
	     xfSciD3D >> EvID3 >> Edep3;
	     vEvID3Dx.push_back(EvID3);
	     vEdep3Dx.push_back(Edep3);
	  }
	  vEvID3Dx.pop_back(); vEdep3Dx.pop_back();    
      vEvID3Dx.pop_back(); vEdep3Dx.pop_back();    
      
      xfSciD3D.close();
      allvEvID3Dx.push_back(vEvID3Dx);
      allvEdep3Dx.push_back(vEdep3Dx);


      // SciD1U
      std::ifstream xfSciD1U(TString(Xfiles[(k*6)+3]));
      std::vector<double> vEvID1Ux;
      std::vector<double> vEdep1Ux;
     
      while (!xfSciD1U.eof()) {
         double EvID1, Edep1;
	     xfSciD1U >> EvID1 >> Edep1;
	     vEvID1Ux.push_back(EvID1);
	     vEdep1Ux.push_back(Edep1);
	  }
	  vEvID1Ux.pop_back(); vEdep1Ux.pop_back();    
      vEvID1Ux.pop_back(); vEdep1Ux.pop_back();    
      
      xfSciD1U.close();
      allvEvID1Ux.push_back(vEvID1Ux);
      allvEdep1Ux.push_back(vEdep1Ux);


      // SciD2U
      std::ifstream xfSciD2U(TString(Xfiles[(k*6)+4]));
      std::vector<double> vEvID2Ux;
      std::vector<double> vEdep2Ux;
     
      while (!xfSciD2U.eof()) {
         double EvID2, Edep2;
	     xfSciD2U >> EvID2 >> Edep2;
	     vEvID2Ux.push_back(EvID2);
	     vEdep2Ux.push_back(Edep2);
	  }
	  vEvID2Ux.pop_back(); vEdep2Ux.pop_back();    
      vEvID2Ux.pop_back(); vEdep2Ux.pop_back();    
      
      xfSciD2U.close();
      allvEvID2Ux.push_back(vEvID2Ux);
      allvEdep2Ux.push_back(vEdep2Ux);


      // SciD3U
      std::ifstream xfSciD3U(TString(Xfiles[(k*6)+5]));
      std::vector<double> vEvID3Ux;
      std::vector<double> vEdep3Ux;
     
      while (!xfSciD3U.eof()) {
         double EvID3, Edep3;
	     xfSciD3U >> EvID3 >> Edep3;
	     vEvID3Ux.push_back(EvID3);
	     vEdep3Ux.push_back(Edep3);
	  }
	  vEvID3Ux.pop_back(); vEdep3Ux.pop_back();    
      vEvID3Ux.pop_back(); vEdep3Ux.pop_back();    
      
      xfSciD3U.close();
      allvEvID3Ux.push_back(vEvID3Ux);
      allvEdep3Ux.push_back(vEdep3Ux);

   }

   
   

    
   //-------------------------------------------------------------------
   //                     Bin-by-bin analysis
   //                          Mu-decay
   //-------------------------------------------------------------------     
     
    
   // Mu-decay  
   for (int i=0; i<allvEvID1Dmu.size(); i++) {

      std::cout << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------- Mu-decay -------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


      for (int m=0; m < nsamps; m++) {

         Ethr = Ethrmu[m];

         counteree = 0; 	
         for (int a=0; a<allvEvID3Dmu[0].size(); a++) {
            if ((allvEdep3Dmu[i][a] > Ethr31) || (allvEdep3Umu[i][a] > Ethr31)) {
			   counteree++;
	        }
	     }
         
         Ethr1 = Ethr;
         Ethr2 = Ethr;


         //--------------------------------------------------
         // Algorithm with D && U, Normalisation 1 [relative]
         //--------------------------------------------------         
         eXrayANDN1 = 0; eelecANDN1 = 0;
      
		 for (int a=0; a<allvEvID3Dmu[0].size(); a++) {
            
            if ((allvEdep3Dmu[i][a] > Ethr31) || (allvEdep3Umu[i][a] > Ethr31)) {
            
				counterDmu = 0; counterUmu = 0;
				if (allvEdep1Dmu[i][a] < Ethr1) {
				   if (allvEdep2Dmu[i][a] < Ethr2) {
					  if ((allvEdep3Dmu[i][a] > Ethr31) && (allvEdep3Dmu[i][a] < Ethr32)) {
						 counterDmu++;
					  }
				   }
				}
				 
				if (allvEdep1Umu[i][a] < Ethr1) {
				   if (allvEdep2Umu[i][a] < Ethr2) {
					  if ((allvEdep3Umu[i][a] > Ethr31) && (allvEdep3Umu[i][a] < Ethr32)) {
						 if ((allvEdep3Dmu[i][a] + allvEdep3Umu[i][a]) < 10) {
							counterUmu++;
						 }
					  }
				   }
				}
				 
				if ((counterDmu + counterUmu) == 2) {
				   eXrayANDN1 += 1;
				} else {
				   eelecANDN1 += 1;
				}
            
            }
			
		 }

         PeXvectorANDN1[i][m] = eXrayANDN1/(double)(counteree);
         PeevectorANDN1[i][m] = eelecANDN1/(double)(counteree); 


         //--------------------------------------------------
         // Algorithm with D && U, Normalisation 2 [absolute]
         //--------------------------------------------------         
         eXrayANDN2 = 0; eelecANDN2 = 0;
      
		 for (int a=0; a<allvEvID3Dmu[0].size(); a++) {
            
            if ((allvEdep3Dmu[i][a] > Ethr31) || (allvEdep3Umu[i][a] > Ethr31)) {
            
				counterDmu = 0; counterUmu = 0;
				if (allvEdep1Dmu[i][a] < Ethr1) {
				   if (allvEdep2Dmu[i][a] < Ethr2) {
					  if ((allvEdep3Dmu[i][a] > Ethr31) && (allvEdep3Dmu[i][a] < Ethr32)) {
						 counterDmu++;
					  }
				   }
				}
				 
				if (allvEdep1Umu[i][a] < Ethr1) {
				   if (allvEdep2Umu[i][a] < Ethr2) {
					  if ((allvEdep3Umu[i][a] > Ethr31) && (allvEdep3Umu[i][a] < Ethr32)) {
						 if ((allvEdep3Dmu[i][a] + allvEdep3Umu[i][a]) < 10) {
							counterUmu++;
						 }
					  }
				   }
				}
				 
				if ((counterDmu + counterUmu) == 2) {
				   eXrayANDN2 += 1;
				} else {
				   eelecANDN2 += 1;
				}
            
            }
			
		 }
	  
         PeXvectorANDN2[i][m] = eXrayANDN2/(double)(countereeN2);
         PeevectorANDN2[i][m] = eelecANDN2/(double)(countereeN2); 
      

         //--------------------------------------------------
         // Algorithm with D || U, Normalisation 1 [relative]
         //--------------------------------------------------         
         eXrayORN1 = 0; eelecORN1 = 0;
      
		 for (int a=0; a<allvEvID3Dmu[0].size(); a++) {
            
            if ((allvEdep3Dmu[i][a] > Ethr31) || (allvEdep3Umu[i][a] > Ethr31)) {
            
				counterDmu = 0; counterUmu = 0;
				if (allvEdep1Dmu[i][a] < Ethr1) {
				   if (allvEdep2Dmu[i][a] < Ethr2) {
					  if ((allvEdep3Dmu[i][a] > Ethr31) && (allvEdep3Dmu[i][a] < Ethr32)) {
						 counterDmu++;
					  }
				   }
				}
				 
				if (allvEdep1Umu[i][a] < Ethr1) {
				   if (allvEdep2Umu[i][a] < Ethr2) {
					  if ((allvEdep3Umu[i][a] > Ethr31) && (allvEdep3Umu[i][a] < Ethr32)) {
						 if ((allvEdep3Dmu[i][a] + allvEdep3Umu[i][a]) < 10) {
							counterUmu++;
						 }
					  }
				   }
				}
				 
				if ((counterDmu == 1) || (counterUmu == 1)) {
				   eXrayORN1 += 1;
				} else {
				   eelecORN1 += 1;
				}
            
            }
			
		 }
	  
         PeXvectorORN1[i][m] = eXrayORN1/(double)(counteree);
         PeevectorORN1[i][m] = eelecORN1/(double)(counteree); 


         //--------------------------------------------------
         // Algorithm with D || U, Normalisation 2 [absolute]
         //--------------------------------------------------         
         eXrayORN2 = 0; eelecORN2 = 0;
      
		 for (int a=0; a<allvEvID3Dmu[0].size(); a++) {
            
            if ((allvEdep3Dmu[i][a] > Ethr31) || (allvEdep3Umu[i][a] > Ethr31)) {
            
				counterDmu = 0; counterUmu = 0;
				if (allvEdep1Dmu[i][a] < Ethr1) {
				   if (allvEdep2Dmu[i][a] < Ethr2) {
					  if ((allvEdep3Dmu[i][a] > Ethr31) && (allvEdep3Dmu[i][a] < Ethr32)) {
						 counterDmu++;
					  }
				   }
				}
				 
				if (allvEdep1Umu[i][a] < Ethr1) {
				   if (allvEdep2Umu[i][a] < Ethr2) {
					  if ((allvEdep3Umu[i][a] > Ethr31) && (allvEdep3Umu[i][a] < Ethr32)) {
						 if ((allvEdep3Dmu[i][a] + allvEdep3Umu[i][a]) < 10) {
							counterUmu++;
						 }
					  }
				   }
				}
				 
				if ((counterDmu == 1) || (counterUmu == 1)) {
				   eXrayORN2 += 1;
				} else {
				   eelecORN2 += 1;
				}
            
            }
			
		 }
	  
         PeXvectorORN2[i][m] = eXrayORN2/(double)(countereeN2);
         PeevectorORN2[i][m] = eelecORN2/(double)(countereeN2); 


      
      
      
      }   
        
   }

    
   // X-ray cascade	  
   for (int i=0; i<allvEvID1Dx.size(); i++) {

      std::cout << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m--------------------- X-ray cascade ----------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


      for (int m=0; m < nsamps; m++) {

         Ethr = Ethrmu[m];

         counterXX = 0; 	
         for (int a=0; a<allvEvID3Dx[0].size(); a++) {
            if ((allvEdep3Dx[i][a] > Ethr31) || (allvEdep3Ux[i][a] > Ethr31)) {
			   counterXX++;
	        }
	     }
         
         Ethr1 = Ethr;
         Ethr2 = Ethr;
         

         //--------------------------------------------------
         // Algorithm with D && U, Normalisation 1 [relative]
         //-------------------------------------------------- 
         XXrayANDN1 = 0; XelecANDN1 = 0;
      
		 for (int a=0; a<allvEvID3Dx[0].size(); a++) {
            
            if ((allvEdep3Dx[i][a] > Ethr31) || (allvEdep3Ux[i][a] > Ethr31)) {
            
				counterDX = 0; counterUX = 0;
				if (allvEdep1Dx[i][a] < Ethr1) {
				   if (allvEdep2Dx[i][a] < Ethr2) {
					  if ((allvEdep3Dx[i][a] > Ethr31) && (allvEdep3Dx[i][a] < Ethr32)) {
						 counterDX++;
					  }
				   }
				}
				 
				if (allvEdep1Ux[i][a] < Ethr1) {
				   if (allvEdep2Ux[i][a] < Ethr2) {
					  if ((allvEdep3Ux[i][a] > Ethr31) && (allvEdep3Ux[i][a] < Ethr32)) {
						 if ((allvEdep3Dx[i][a] + allvEdep3Ux[i][a]) < 10) {
							counterUX++;
						 }
					  }
				   }
				}
				 
				if ((counterDX + counterUX) == 2) {
				   XXrayANDN1 += 1;
				} else {
				   XelecANDN1 += 1;
				}
            
            }
			
		 }
	  
         PXXvectorANDN1[i][m] = XXrayANDN1/(double)(counterXX);
         PXevectorANDN1[i][m] = XelecANDN1/(double)(counterXX); 


         //--------------------------------------------------
         // Algorithm with D && U, Normalisation 2 [absolute]
         //-------------------------------------------------- 
         XXrayANDN2 = 0; XelecANDN2 = 0;
      
		 for (int a=0; a<allvEvID3Dx[0].size(); a++) {
            
            if ((allvEdep3Dx[i][a] > Ethr31) || (allvEdep3Ux[i][a] > Ethr31)) {
            
				counterDX = 0; counterUX = 0;
				if (allvEdep1Dx[i][a] < Ethr1) {
				   if (allvEdep2Dx[i][a] < Ethr2) {
					  if ((allvEdep3Dx[i][a] > Ethr31) && (allvEdep3Dx[i][a] < Ethr32)) {
						 counterDX++;
					  }
				   }
				}
				 
				if (allvEdep1Ux[i][a] < Ethr1) {
				   if (allvEdep2Ux[i][a] < Ethr2) {
					  if ((allvEdep3Ux[i][a] > Ethr31) && (allvEdep3Ux[i][a] < Ethr32)) {
						 if ((allvEdep3Dx[i][a] + allvEdep3Ux[i][a]) < 10) {
							counterUX++;
						 }
					  }
				   }
				}
				 
				if ((counterDX + counterUX) == 2) {
				   XXrayANDN2 += 1;
				} else {
				   XelecANDN2 += 1;
				}
            
            }
			
		 }
	  
         PXXvectorANDN2[i][m] = XXrayANDN2/(double)(counterXXN2);
         PXevectorANDN2[i][m] = XelecANDN2/(double)(counterXXN2); 


         //--------------------------------------------------
         // Algorithm with D || U, Normalisation 1 [relative]
         //-------------------------------------------------- 
         XXrayORN1 = 0; XelecORN1 = 0;
      
		 for (int a=0; a<allvEvID3Dx[0].size(); a++) {
            
            if ((allvEdep3Dx[i][a] > Ethr31) || (allvEdep3Ux[i][a] > Ethr31)) {
            
				counterDX = 0; counterUX = 0;
				if (allvEdep1Dx[i][a] < Ethr1) {
				   if (allvEdep2Dx[i][a] < Ethr2) {
					  if ((allvEdep3Dx[i][a] > Ethr31) && (allvEdep3Dx[i][a] < Ethr32)) {
						 counterDX++;
					  }
				   }
				}
				 
				if (allvEdep1Ux[i][a] < Ethr1) {
				   if (allvEdep2Ux[i][a] < Ethr2) {
					  if ((allvEdep3Ux[i][a] > Ethr31) && (allvEdep3Ux[i][a] < Ethr32)) {
						 if ((allvEdep3Dx[i][a] + allvEdep3Ux[i][a]) < 10) {
							counterUX++;
						 }
					  }
				   }
				}
				 
				if ((counterDX == 1) || (counterUX == 1)) {
				   XXrayORN1 += 1;
				} else {
				   XelecORN1 += 1;
				}
            
            }
			
		 }
	  
         PXXvectorORN1[i][m] = XXrayORN1/(double)(counterXX);
         PXevectorORN1[i][m] = XelecORN1/(double)(counterXX); 

      
         //--------------------------------------------------
         // Algorithm with D || U, Normalisation 2 [absolute]
         //-------------------------------------------------- 
         XXrayORN2 = 0; XelecORN2 = 0;
      
		 for (int a=0; a<allvEvID3Dx[0].size(); a++) {
            
            if ((allvEdep3Dx[i][a] > Ethr31) || (allvEdep3Ux[i][a] > Ethr31)) {
            
				counterDX = 0; counterUX = 0;
				if (allvEdep1Dx[i][a] < Ethr1) {
				   if (allvEdep2Dx[i][a] < Ethr2) {
					  if ((allvEdep3Dx[i][a] > Ethr31) && (allvEdep3Dx[i][a] < Ethr32)) {
						 counterDX++;
					  }
				   }
				}
				 
				if (allvEdep1Ux[i][a] < Ethr1) {
				   if (allvEdep2Ux[i][a] < Ethr2) {
					  if ((allvEdep3Ux[i][a] > Ethr31) && (allvEdep3Ux[i][a] < Ethr32)) {
						 if ((allvEdep3Dx[i][a] + allvEdep3Ux[i][a]) < 10) {
							counterUX++;
						 }
					  }
				   }
				}
				 
				if ((counterDX == 1) || (counterUX == 1)) {
				   XXrayORN2 += 1;
				} else {
				   XelecORN2 += 1;
				}
            
            }
			
		 }
	  
         PXXvectorORN2[i][m] = XXrayORN2/(double)(counterXXN2);
         PXevectorORN2[i][m] = XelecORN2/(double)(counterXXN2); 
      
      
      }   
        
   }



   //-------------------------------------------------------------------
   //                     Plotting business
   //-------------------------------------------------------------------     
    
    
   std::cout << std::endl;
   std::cout << "\033[1;33m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;33m-------------------- Plotting business -------------------\033[0m" << std::endl;
   std::cout << "\033[1;33m----------------------------------------------------------\033[0m" << std::endl;

  
   // Array declarations
   // Normalisation 1 [rel], D && U
   float PeXarrANDN1[nsamps] = {}; // Mu-decay
   float PeearrANDN1[nsamps] = {};
   float PXXarrANDN1[nsamps] = {}; // X-ray cascade
   float PXearrANDN1[nsamps] = {};
   // Normalisation 2 [abs], D && U
   float PeXarrANDN2[nsamps] = {}; 
   float PeearrANDN2[nsamps] = {};
   float PXXarrANDN2[nsamps] = {}; 
   float PXearrANDN2[nsamps] = {};
   // Normalisation 1 [rel], D || U
   float PeXarrORN1[nsamps] = {}; 
   float PeearrORN1[nsamps] = {};
   float PXXarrORN1[nsamps] = {}; 
   float PXearrORN1[nsamps] = {};
   // Normalisation 2 [abs], D || U
   float PeXarrORN2[nsamps] = {}; 
   float PeearrORN2[nsamps] = {};
   float PXXarrORN2[nsamps] = {}; 
   float PXearrORN2[nsamps] = {};
   
       
   for (int i=0; i<nsamps; i++) {
      // Normalisation 1 [relative], D && U
      PeXarrANDN1[i] = PeXvectorANDN1[0][i];
      PeearrANDN1[i] = PeevectorANDN1[0][i];
      PXXarrANDN1[i] = PXXvectorANDN1[0][i];
      PXearrANDN1[i] = PXevectorANDN1[0][i];
      // Normalisation 2 [absolute], D && U
      PeXarrANDN2[i] = PeXvectorANDN2[0][i];
      PeearrANDN2[i] = PeevectorANDN2[0][i];
      PXXarrANDN2[i] = PXXvectorANDN2[0][i];
      PXearrANDN2[i] = PXevectorANDN2[0][i];
      // Normalisation 1 [relative], D || U
      PeXarrORN1[i] = PeXvectorORN1[0][i];
      PeearrORN1[i] = PeevectorORN1[0][i];
      PXXarrORN1[i] = PXXvectorORN1[0][i];
      PXearrORN1[i] = PXevectorORN1[0][i];
      // Normalisation 2 [absolute], D || U
      PeXarrORN2[i] = PeXvectorORN2[0][i];
      PeearrORN2[i] = PeevectorORN2[0][i];
      PXXarrORN2[i] = PXXvectorORN2[0][i];
      PXearrORN2[i] = PXevectorORN2[0][i];

      
      std::cout << "AND--N1 PeX = " << PeXvectorANDN1[0][i] << " Peev = " << PeevectorANDN1[0][i] << " PXX = " << PXXvectorANDN1[0][i] << " PXe = " << PXevectorORN1[0][i] << std::endl;
      std::cout << "AND--N2 PeX = " << PeXvectorANDN2[0][i] << " Peev = " << PeevectorANDN2[0][i] << " PXX = " << PXXvectorANDN2[0][i] << " PXe = " << PXevectorORN1[0][i] << std::endl;
      std::cout << "OR---N1 PeX = " << PeXvectorORN1[0][i] << " Peev = " << PeevectorORN1[0][i] << " PXX = " << PXXvectorORN1[0][i] << " PXe = " << PXevectorORN1[0][i] << std::endl;
      std::cout << "OR---N2 PeX = " << PeXvectorORN2[0][i] << " Peev = " << PeevectorORN1[0][i] << " PXX = " << PXXvectorORN1[0][i] << " PXe = " << PXevectorORN1[0][i] << std::endl;
      std::cout << std::endl;
      
      
   }	   
	   
  
   
   TCanvas *c = new TCanvas("c","E_{THR}",800,600);
   c->Divide(2,2);
   c->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPXXANDN1 = new TGraph(nsamps,Ethrmu,PXXarrANDN1);
   grPXXANDN1->SetTitle("AND - N1_{rel}: 1-mm Al + 2x5-mm SciD_{1,2} + 5-mm Al + 500-mm SciD_{3} D-stream [10^6 events]");
   grPXXANDN1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXXANDN1->GetXaxis()->SetRangeUser(0,2.05);
   grPXXANDN1->GetYaxis()->SetRangeUser(1e-6,1.1);
   grPXXANDN1->GetYaxis()->SetTitle("P_{e/X->X}(E_{THR})");
   grPXXANDN1->GetYaxis()->SetTitleOffset(1.8);
   grPXXANDN1->SetMarkerColor(kRed);
   grPXXANDN1->SetMarkerStyle(31);
   grPXXANDN1->SetLineColor(kRed);
   grPXXANDN1->Draw("ALP");
   TGraph *grPeXANDN1 = new TGraph(nsamps,Ethrmu,PeXarrANDN1); 
   grPeXANDN1->SetMarkerColor(kBlack);
   grPeXANDN1->SetMarkerStyle(33);
   grPeXANDN1->SetLineColor(kBlack);
   grPeXANDN1->Draw("LP");
   legPXXPeXANDN1 = new TLegend(0.2,-0.005,0.4,0.08);
   legPXXPeXANDN1->AddEntry(grPXXANDN1,"P_{X->X}","lp");
   legPXXPeXANDN1->AddEntry(grPeXANDN1,"P_{e->X}","lp");
   legPXXPeXANDN1->Draw();

   c->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPXXORN1 = new TGraph(nsamps,Ethrmu,PXXarrORN1);
   grPXXORN1->SetTitle("OR - N1_{rel}: 1-mm Al + 2x5-mm SciD_{1,2} + 5-mm Al + 500-mm SciD_{3} D-stream [10^6 events]");
   grPXXORN1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXXORN1->GetXaxis()->SetRangeUser(0,2.05);
   grPXXORN1->GetYaxis()->SetRangeUser(1e-6,1.1);
   grPXXORN1->GetYaxis()->SetTitle("P_{e/X->X}(E_{THR})");
   grPXXORN1->GetYaxis()->SetTitleOffset(1.8);
   grPXXORN1->SetMarkerColor(kRed);
   grPXXORN1->SetMarkerStyle(31);
   grPXXORN1->SetLineColor(kRed);
   grPXXORN1->Draw("ALP");
   TGraph *grPeXORN1 = new TGraph(nsamps,Ethrmu,PeXarrORN1); 
   grPeXORN1->SetMarkerColor(kBlack);
   grPeXORN1->SetMarkerStyle(33);
   grPeXORN1->SetLineColor(kBlack);
   grPeXORN1->Draw("LP");
   legPXXPeXORN1 = new TLegend(0.2,-0.005,0.4,0.08);
   legPXXPeXORN1->AddEntry(grPXXORN1,"P_{X->X}","lp");
   legPXXPeXORN1->AddEntry(grPeXORN1,"P_{e->X}","lp");
   legPXXPeXORN1->Draw();

   c->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPXXANDN2 = new TGraph(nsamps,Ethrmu,PXXarrANDN2);
   grPXXANDN2->SetTitle("AND - N2_{abs}: 1-mm Al + 2x5-mm SciD_{1,2} + 5-mm Al + 500-mm SciD_{3} D-stream [10^6 events]");
   grPXXANDN2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXXANDN2->GetXaxis()->SetRangeUser(0,2.05);
   grPXXANDN2->GetYaxis()->SetRangeUser(1e-6,1.1);
   grPXXANDN2->GetYaxis()->SetTitle("P_{e/X->X}(E_{THR})");
   grPXXANDN2->GetYaxis()->SetTitleOffset(1.8);
   grPXXANDN2->SetMarkerColor(kRed);
   grPXXANDN2->SetMarkerStyle(31);
   grPXXANDN2->SetLineColor(kRed);
   grPXXANDN2->Draw("ALP");
   TGraph *grPeXANDN2 = new TGraph(nsamps,Ethrmu,PeXarrANDN2); 
   grPeXANDN2->SetMarkerColor(kBlack);
   grPeXANDN2->SetMarkerStyle(33);
   grPeXANDN2->SetLineColor(kBlack);
   grPeXANDN2->Draw("LP");
   legPXXPeXANDN2 = new TLegend(0.2,-0.005,0.4,0.08);
   legPXXPeXANDN2->AddEntry(grPXXANDN2,"P_{X->X}","lp");
   legPXXPeXANDN2->AddEntry(grPeXANDN2,"P_{e->X}","lp");
   legPXXPeXANDN2->Draw();

   c->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPXXORN2 = new TGraph(nsamps,Ethrmu,PXXarrORN2);
   grPXXORN2->SetTitle("OR - N2_{abs}: 1-mm Al + 2x5-mm SciD_{1,2} + 5-mm Al + 500-mm SciD_{3} D-stream [10^6 events]");
   grPXXORN2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXXORN2->GetXaxis()->SetRangeUser(0,2.05);
   grPXXORN2->GetYaxis()->SetRangeUser(1e-6,1.1);
   grPXXORN2->GetYaxis()->SetTitle("P_{e/X->X}(E_{THR})");
   grPXXORN2->GetYaxis()->SetTitleOffset(1.8);
   grPXXORN2->SetMarkerColor(kRed);
   grPXXORN2->SetMarkerStyle(31);
   grPXXORN2->SetLineColor(kRed);
   grPXXORN2->Draw("ALP");
   TGraph *grPeXORN2 = new TGraph(nsamps,Ethrmu,PeXarrORN2); 
   grPeXORN2->SetMarkerColor(kBlack);
   grPeXORN2->SetMarkerStyle(33);
   grPeXORN2->SetLineColor(kBlack);
   grPeXORN2->Draw("LP");
   legPXXPeXORN2 = new TLegend(0.2,-0.005,0.4,0.08);
   legPXXPeXORN2->AddEntry(grPXXORN2,"P_{X->X}","lp");
   legPXXPeXORN2->AddEntry(grPeXORN2,"P_{e->X}","lp");
   legPXXPeXORN2->Draw();


   c->SaveAs("Planar_MULTIplicities_eff.pdf");
   c->SaveAs("Planar_MULTIplicities_eff.png");
   c->SaveAs("Planar_MULTIplicities_eff.C");

  
  
 }
 
 
 int main() {
   planarMULTIeff();
   return 0;
}  
