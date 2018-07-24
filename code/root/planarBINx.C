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

void planarBINx(){

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
   // X-ray cascade 3-mm
   std::string file3Alx250SciD1D = "../../simdata/planar/planar_2x5mm_250mm_SciD_3mm_Al_1e6goldcascade_SciD1D.txt";
   std::string file3Alx250SciD2D = "../../simdata/planar/planar_2x5mm_250mm_SciD_3mm_Al_1e6goldcascade_SciD2D.txt";
   std::string file3Alx250SciD3D = "../../simdata/planar/planar_2x5mm_250mm_SciD_3mm_Al_1e6goldcascade_SciD3D.txt";
   std::string file3Alx250SciD1U = "../../simdata/planar/planar_2x5mm_250mm_SciD_3mm_Al_1e6goldcascade_SciD1U.txt";
   std::string file3Alx250SciD2U = "../../simdata/planar/planar_2x5mm_250mm_SciD_3mm_Al_1e6goldcascade_SciD2U.txt";
   std::string file3Alx250SciD3U = "../../simdata/planar/planar_2x5mm_250mm_SciD_3mm_Al_1e6goldcascade_SciD3U.txt";
   std::string file3Alx500SciD1D = "../../simdata/planar/planar_2x5mm_500mm_SciD_3mm_Al_1e6goldcascade_SciD1D.txt";
   std::string file3Alx500SciD2D = "../../simdata/planar/planar_2x5mm_500mm_SciD_3mm_Al_1e6goldcascade_SciD2D.txt";
   std::string file3Alx500SciD3D = "../../simdata/planar/planar_2x5mm_500mm_SciD_3mm_Al_1e6goldcascade_SciD3D.txt";
   std::string file3Alx500SciD1U = "../../simdata/planar/planar_2x5mm_500mm_SciD_3mm_Al_1e6goldcascade_SciD1U.txt";
   std::string file3Alx500SciD2U = "../../simdata/planar/planar_2x5mm_500mm_SciD_3mm_Al_1e6goldcascade_SciD2U.txt";
   std::string file3Alx500SciD3U = "../../simdata/planar/planar_2x5mm_500mm_SciD_3mm_Al_1e6goldcascade_SciD3U.txt";
   std::string file3Alx750SciD1D = "../../simdata/planar/planar_2x5mm_750mm_SciD_3mm_Al_1e6goldcascade_SciD1D.txt";
   std::string file3Alx750SciD2D = "../../simdata/planar/planar_2x5mm_750mm_SciD_3mm_Al_1e6goldcascade_SciD2D.txt";
   std::string file3Alx750SciD3D = "../../simdata/planar/planar_2x5mm_750mm_SciD_3mm_Al_1e6goldcascade_SciD3D.txt";
   std::string file3Alx750SciD1U = "../../simdata/planar/planar_2x5mm_750mm_SciD_3mm_Al_1e6goldcascade_SciD1U.txt";
   std::string file3Alx750SciD2U = "../../simdata/planar/planar_2x5mm_750mm_SciD_3mm_Al_1e6goldcascade_SciD2U.txt";
   std::string file3Alx750SciD3U = "../../simdata/planar/planar_2x5mm_750mm_SciD_3mm_Al_1e6goldcascade_SciD3U.txt";
   // X-ray cascade 6-mm
   std::string file6Alx250SciD1D = "../../simdata/planar/planar_2x5mm_250mm_SciD_6mm_Al_1e6goldcascade_SciD1D.txt";
   std::string file6Alx250SciD2D = "../../simdata/planar/planar_2x5mm_250mm_SciD_6mm_Al_1e6goldcascade_SciD2D.txt";
   std::string file6Alx250SciD3D = "../../simdata/planar/planar_2x5mm_250mm_SciD_6mm_Al_1e6goldcascade_SciD3D.txt";
   std::string file6Alx250SciD1U = "../../simdata/planar/planar_2x5mm_250mm_SciD_6mm_Al_1e6goldcascade_SciD1U.txt";
   std::string file6Alx250SciD2U = "../../simdata/planar/planar_2x5mm_250mm_SciD_6mm_Al_1e6goldcascade_SciD2U.txt";
   std::string file6Alx250SciD3U = "../../simdata/planar/planar_2x5mm_250mm_SciD_6mm_Al_1e6goldcascade_SciD3U.txt";
   std::string file6Alx500SciD1D = "../../simdata/planar/planar_2x5mm_500mm_SciD_6mm_Al_1e6goldcascade_SciD1D.txt";
   std::string file6Alx500SciD2D = "../../simdata/planar/planar_2x5mm_500mm_SciD_6mm_Al_1e6goldcascade_SciD2D.txt";
   std::string file6Alx500SciD3D = "../../simdata/planar/planar_2x5mm_500mm_SciD_6mm_Al_1e6goldcascade_SciD3D.txt";
   std::string file6Alx500SciD1U = "../../simdata/planar/planar_2x5mm_500mm_SciD_6mm_Al_1e6goldcascade_SciD1U.txt";
   std::string file6Alx500SciD2U = "../../simdata/planar/planar_2x5mm_500mm_SciD_6mm_Al_1e6goldcascade_SciD2U.txt";
   std::string file6Alx500SciD3U = "../../simdata/planar/planar_2x5mm_500mm_SciD_6mm_Al_1e6goldcascade_SciD3U.txt";
   std::string file6Alx750SciD1D = "../../simdata/planar/planar_2x5mm_750mm_SciD_6mm_Al_1e6goldcascade_SciD1D.txt";
   std::string file6Alx750SciD2D = "../../simdata/planar/planar_2x5mm_750mm_SciD_6mm_Al_1e6goldcascade_SciD2D.txt";
   std::string file6Alx750SciD3D = "../../simdata/planar/planar_2x5mm_750mm_SciD_6mm_Al_1e6goldcascade_SciD3D.txt";
   std::string file6Alx750SciD1U = "../../simdata/planar/planar_2x5mm_750mm_SciD_6mm_Al_1e6goldcascade_SciD1U.txt";
   std::string file6Alx750SciD2U = "../../simdata/planar/planar_2x5mm_750mm_SciD_6mm_Al_1e6goldcascade_SciD2U.txt";
   std::string file6Alx750SciD3U = "../../simdata/planar/planar_2x5mm_750mm_SciD_6mm_Al_1e6goldcascade_SciD3U.txt";
   
 
   std::vector<std::string> Xfiles;

   // X-ray cascade 3-mm
   Xfiles.push_back(file3Alx250SciD1D);
   Xfiles.push_back(file3Alx250SciD2D);
   Xfiles.push_back(file3Alx250SciD3D);
   Xfiles.push_back(file3Alx250SciD1U);
   Xfiles.push_back(file3Alx250SciD2U);
   Xfiles.push_back(file3Alx250SciD3U);
   Xfiles.push_back(file3Alx500SciD1D);
   Xfiles.push_back(file3Alx500SciD2D);
   Xfiles.push_back(file3Alx500SciD3D);
   Xfiles.push_back(file3Alx500SciD1U);
   Xfiles.push_back(file3Alx500SciD2U);
   Xfiles.push_back(file3Alx500SciD3U);
   Xfiles.push_back(file3Alx750SciD1D);
   Xfiles.push_back(file3Alx750SciD2D);
   Xfiles.push_back(file3Alx750SciD3D);
   Xfiles.push_back(file3Alx750SciD1U);
   Xfiles.push_back(file3Alx750SciD2U);
   Xfiles.push_back(file3Alx750SciD3U);
   // Mu-decay 6-mm
   Xfiles.push_back(file6Alx250SciD1D);
   Xfiles.push_back(file6Alx250SciD2D);
   Xfiles.push_back(file6Alx250SciD3D);
   Xfiles.push_back(file6Alx250SciD1U);
   Xfiles.push_back(file6Alx250SciD2U);
   Xfiles.push_back(file6Alx250SciD3U);
   Xfiles.push_back(file6Alx500SciD1D);
   Xfiles.push_back(file6Alx500SciD2D);
   Xfiles.push_back(file6Alx500SciD3D);
   Xfiles.push_back(file6Alx500SciD1U);
   Xfiles.push_back(file6Alx500SciD2U);
   Xfiles.push_back(file6Alx500SciD3U);
   Xfiles.push_back(file6Alx750SciD1D);
   Xfiles.push_back(file6Alx750SciD2D);
   Xfiles.push_back(file6Alx750SciD3D);
   Xfiles.push_back(file6Alx750SciD1U);
   Xfiles.push_back(file6Alx750SciD2U);
   Xfiles.push_back(file6Alx750SciD3U);



   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep, EventID;
   float iEventID;

   const int nsamps = 101;
   float Ethr3 = 0.5;
   float Estep = 2.0/(nsamps-1);
   float Ethrx[nsamps] = {};
   
   // X-ray cascade storage vectors
   std::vector< std::vector<double> > PXevectorD((Xfiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorD((Xfiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXevectorU((Xfiles.size())/6,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorU((Xfiles.size())/6,std::vector<double>(nsamps));

   
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
   float tPxx;
   int counterD, counterU; 
   int Xray = 0;
   int elec = 0;
   
   Ethrx[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrx[i] = Ethrx[i-1] + Estep;


   //-------------------------------------------------------------------
   //                           Reading
   //-------------------------------------------------------------------


   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m------------------- X-ray cascade ------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


   for (int k=0; k<((Xfiles.size())/6); k++) {
	  // SciD1D
      std::ifstream xfSciD1D(TString(Xfiles[k*6]));
      std::vector<double> vEvID1D;
      std::vector<double> vEdep1D;
     
      while (!xfSciD1D.eof()) {
         double EvID1, Edep1;
	     xfSciD1D >> EvID1 >> Edep1;
	     vEvID1D.push_back(EvID1);
	     vEdep1D.push_back(Edep1);
	  }
	  vEvID1D.pop_back(); vEdep1D.pop_back();    
      vEvID1D.pop_back(); vEdep1D.pop_back();    
      
      xfSciD1D.close();
      allvEvID1Dx.push_back(vEvID1D);
      allvEdep1Dx.push_back(vEdep1D);


      // SciD2D
      std::ifstream xfSciD2D(TString(Xfiles[(k*6)+1]));
      std::vector<double> vEvID2D;
      std::vector<double> vEdep2D;
     
      while (!xfSciD2D.eof()) {
         double EvID2, Edep2;
	     xfSciD2D >> EvID2 >> Edep2;
	     vEvID2D.push_back(EvID2);
	     vEdep2D.push_back(Edep2);
	  }
	  vEvID2D.pop_back(); vEdep2D.pop_back();    
      vEvID2D.pop_back(); vEdep2D.pop_back();    
      
      xfSciD2D.close();
      allvEvID2Dx.push_back(vEvID2D);
      allvEdep2Dx.push_back(vEdep2D);


      // SciD3D
      std::ifstream xfSciD3D(TString(Xfiles[(k*6)+2]));
      std::vector<double> vEvID3D;
      std::vector<double> vEdep3D;
     
      while (!xfSciD3D.eof()) {
         double EvID3, Edep3;
	     xfSciD3D >> EvID3 >> Edep3;
	     vEvID3D.push_back(EvID3);
	     vEdep3D.push_back(Edep3);
	  }
	  vEvID3D.pop_back(); vEdep3D.pop_back();    
      vEvID3D.pop_back(); vEdep3D.pop_back();    
      
      xfSciD3D.close();
      allvEvID3Dx.push_back(vEvID3D);
      allvEdep3Dx.push_back(vEdep3D);


      // SciD1U
      std::ifstream xfSciD1U(TString(Xfiles[(k*6)+3]));
      std::vector<double> vEvID1U;
      std::vector<double> vEdep1U;
     
      while (!xfSciD1U.eof()) {
         double EvID1, Edep1;
	     xfSciD1U >> EvID1 >> Edep1;
	     vEvID1U.push_back(EvID1);
	     vEdep1U.push_back(Edep1);
	  }
	  vEvID1U.pop_back(); vEdep1U.pop_back();    
      vEvID1U.pop_back(); vEdep1U.pop_back();    
      
      xfSciD1U.close();
      allvEvID1Ux.push_back(vEvID1U);
      allvEdep1Ux.push_back(vEdep1U);


      // SciD2U
      std::ifstream xfSciD2U(TString(Xfiles[(k*6)+4]));
      std::vector<double> vEvID2U;
      std::vector<double> vEdep2U;
     
      while (!xfSciD2U.eof()) {
         double EvID2, Edep2;
	     xfSciD2U >> EvID2 >> Edep2;
	     vEvID2U.push_back(EvID2);
	     vEdep2U.push_back(Edep2);
	  }
	  vEvID2U.pop_back(); vEdep2U.pop_back();    
      vEvID2U.pop_back(); vEdep2U.pop_back();    
      
      xfSciD2U.close();
      allvEvID2Ux.push_back(vEvID2U);
      allvEdep2Ux.push_back(vEdep2U);


      // SciD3U
      std::ifstream xfSciD3U(TString(Xfiles[(k*6)+5]));
      std::vector<double> vEvID3U;
      std::vector<double> vEdep3U;
     
      while (!xfSciD3U.eof()) {
         double EvID3, Edep3;
	     xfSciD3U >> EvID3 >> Edep3;
	     vEvID3U.push_back(EvID3);
	     vEdep3U.push_back(Edep3);
	  }
	  vEvID3U.pop_back(); vEdep3U.pop_back();    
      vEvID3U.pop_back(); vEdep3U.pop_back();    
      
      xfSciD3U.close();
      allvEvID3Ux.push_back(vEvID3U);
      allvEdep3Ux.push_back(vEdep3U);

   }

    
   //-------------------------------------------------------------------
   //                     Bin-by-bin analysis
   //                        X-ray cascade
   //-------------------------------------------------------------------     
     
    
	  
   for (int i=0; i<allvEvID1Dx.size(); i++) {

      std::cout << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- X-ray cascade -----------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


      // X-ray cascade D-stream 	
      counterD = 0;
      for (int a=0; a<allvEvID3Dx[0].size(); a++) {
         if (allvEdep3Dx[i][a] >= Ethr3) {
			counterD++;
	     }
	  }
	  
      for (int m=0; m < nsamps; m++) {
	     Ethr = Ethrx[m];
         Xray = 0; elec = 0;

		 for (int j=0; j<allvEvID1Dx[0].size(); j++) {
		    if (allvEdep3Dx[i][j] >= Ethr3) {	  		  
			   tPxx = 0;
			   
			   if (allvEdep1Dx[i][j] < Ethr) {
			      tPxx += 1;   
			      if (allvEdep2Dx[i][j] < Ethr) {
				     tPxx += 1;			
					 if ((allvEdep3Dx[i][j] >= Ethr3) && (allvEdep3Dx[i][j] < 10) && (tPxx == 2)) {
						Xray += 1;
					 } else {
						elec += 1;
					 }
				  } else {
					 elec += 1;
				  }
			   } else {
				  elec += 1;
			   }
			}
		 }      


         PXXvectorD[i][m] = Xray/(double)(counterD);
         PXevectorD[i][m] = elec/(double)(counterD); 
       
         //std::cout << " PXXD[" << i << "][" << m << "] = " << PXXvectorD[i][m] << " PXeD[" << i << "][" << m << "] = " << PXevectorD[i][m] << " PXX + PXe = " << PXXvectorD[i][m] + PXevectorD[i][m] << " counterD = " << counterD << std::endl;
     

      }   
       
      
      // X-ray cascade U-stream 	
      counterU = 0;
      for (int a=0; a<allvEvID3Ux[0].size(); a++) {
	     if (allvEdep3Ux[i][a] >= Ethr3) {
			counterU++;
	     }
	  }
	  
      for (int m=0; m < nsamps; m++) {
	     Ethr = Ethrx[m];
         Xray = 0; elec = 0;

		 for (int j=0; j<allvEvID1Ux[0].size(); j++) {
			if (allvEdep3Ux[i][j] >= Ethr3) {  
			   tPxx = 0;
			   
			   if (allvEdep1Ux[i][j] < Ethr) {
				  tPxx += 1;   
				  if (allvEdep2Ux[i][j] < Ethr) {
					 tPxx += 1;
					 if ((allvEdep3Ux[i][j] >= Ethr3) && (allvEdep3Ux[i][j] < 10) && (tPxx == 2)) {
						Xray += 1;
					 } else {
						elec += 1;
					 }
				  } else {
					 elec += 1;
				  }
			   } else {
				  elec += 1;
			   }	
		    }
		 }   

         //std::cout << " UXray = " << Xray << " elec = " << elec << std::endl;

         PXXvectorU[i][m] = Xray/(double)(counterU);
         PXevectorU[i][m] = elec/(double)(counterU);
       
         //std::cout << " PXXU[" << i << "][" << m << "] = " << PXXvectorU[i][m] << " PXeU[" << i << "][" << m << "] = " << PXevectorU[i][m] << " PXX+PXe = " << PXXvectorU[i][m] + PXevectorU[i][m] << " counterU = " << counterU << std::endl;
     
     
      } 
       
        
   }




   //-------------------------------------------------------------------
   //                     Plotting business
   //-------------------------------------------------------------------     
    
    
   std::cout << std::endl;
   std::cout << "\033[1;33m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;33m-------------------- Plotting business -------------------\033[0m" << std::endl;
   std::cout << "\033[1;33m----------------------------------------------------------\033[0m" << std::endl;

  
   // X-ray cascade 3-mm
   float PXXarr250x3AlD[nsamps] = {};
   float PXearr250x3AlD[nsamps] = {};
   float PXXarr500x3AlD[nsamps] = {};
   float PXearr500x3AlD[nsamps] = {};
   float PXXarr750x3AlD[nsamps] = {};
   float PXearr750x3AlD[nsamps] = {};
   float PXXarr250x3AlU[nsamps] = {};
   float PXearr250x3AlU[nsamps] = {};
   float PXXarr500x3AlU[nsamps] = {};
   float PXearr500x3AlU[nsamps] = {};
   float PXXarr750x3AlU[nsamps] = {};
   float PXearr750x3AlU[nsamps] = {};
   // X-ray cascade 6-mm
   float PXXarr250x6AlD[nsamps] = {};
   float PXearr250x6AlD[nsamps] = {};
   float PXXarr500x6AlD[nsamps] = {};
   float PXearr500x6AlD[nsamps] = {};
   float PXXarr750x6AlD[nsamps] = {};
   float PXearr750x6AlD[nsamps] = {};
   float PXXarr250x6AlU[nsamps] = {};
   float PXearr250x6AlU[nsamps] = {};
   float PXXarr500x6AlU[nsamps] = {};
   float PXearr500x6AlU[nsamps] = {};
   float PXXarr750x6AlU[nsamps] = {};
   float PXearr750x6AlU[nsamps] = {};

     
   for (int i=0; i<nsamps; i++) {
      PXXarr250x3AlD[i] = PXXvectorD[0][i];
      PXearr250x3AlD[i] = PXevectorD[0][i];
      PXXarr500x3AlD[i] = PXXvectorD[1][i];
      PXearr500x3AlD[i] = PXevectorD[1][i];
      PXXarr750x3AlD[i] = PXXvectorD[2][i];
      PXearr750x3AlD[i] = PXevectorD[2][i];
      PXXarr250x3AlU[i] = PXXvectorU[0][i];
      PXearr250x3AlU[i] = PXevectorU[0][i];
      PXXarr500x3AlU[i] = PXXvectorU[1][i];
      PXearr500x3AlU[i] = PXevectorU[1][i];
      PXXarr750x3AlU[i] = PXXvectorU[2][i];
      PXearr750x3AlU[i] = PXevectorU[2][i];

      PXXarr250x6AlD[i] = PXXvectorD[3][i];
      PXearr250x6AlD[i] = PXevectorD[3][i];
      PXXarr500x6AlD[i] = PXXvectorD[4][i];
      PXearr500x6AlD[i] = PXevectorD[4][i];
      PXXarr750x6AlD[i] = PXXvectorD[5][i];
      PXearr750x6AlD[i] = PXevectorD[5][i];
      PXXarr250x6AlU[i] = PXXvectorU[3][i];
      PXearr250x6AlU[i] = PXevectorU[3][i];
      PXXarr500x6AlU[i] = PXXvectorU[4][i];
      PXearr500x6AlU[i] = PXevectorU[4][i];
      PXXarr750x6AlU[i] = PXXvectorU[5][i];
      PXearr750x6AlU[i] = PXevectorU[5][i];
  
   }
  
  
   
   TCanvas *c = new TCanvas("c","E_{THR}",800,600);
   c->Divide(3,2);
   c->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr250x3AlSciDet1PXXD = new TGraph(nsamps,Ethrx,PXXarr250x3AlD);
   gr250x3AlSciDet1PXXD->SetTitle("10 MeV: 3-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3} D-stream [10^6 events]");
   gr250x3AlSciDet1PXXD->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr250x3AlSciDet1PXXD->GetXaxis()->SetRangeUser(0,2.05);
   gr250x3AlSciDet1PXXD->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr250x3AlSciDet1PXXD->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
   gr250x3AlSciDet1PXXD->GetYaxis()->SetTitleOffset(1.8);
   gr250x3AlSciDet1PXXD->SetMarkerColor(kBlack);
   gr250x3AlSciDet1PXXD->SetMarkerStyle(33);
   gr250x3AlSciDet1PXXD->SetLineColor(kBlack);
   gr250x3AlSciDet1PXXD->Draw("ALP");
   TGraph *gr250x3AlSciDet1PXeD = new TGraph(nsamps,Ethrx,PXearr250x3AlD); 
   gr250x3AlSciDet1PXeD->SetMarkerColor(kRed);
   gr250x3AlSciDet1PXeD->SetMarkerStyle(31);
   gr250x3AlSciDet1PXeD->SetLineColor(kRed);
   gr250x3AlSciDet1PXeD->Draw("LP");
   leg250x3AlSciDet1PXXPXeD = new TLegend(0.2,-0.005,0.4,0.08);
   leg250x3AlSciDet1PXXPXeD->AddEntry(gr250x3AlSciDet1PXXD,"P_{X->X}","lp");
   leg250x3AlSciDet1PXXPXeD->AddEntry(gr250x3AlSciDet1PXeD,"P_{X->e}","lp");
   leg250x3AlSciDet1PXXPXeD->Draw();
  
   c->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr500x3AlSciDet1PXXD = new TGraph(nsamps,Ethrx,PXXarr500x3AlD);  
   gr500x3AlSciDet1PXXD->SetTitle("10 MeV: 3-mm Al + 2x5-mm SCiD_{1,2} + 500-mm SciD_{3} D-stream [10^6 events]");
   gr500x3AlSciDet1PXXD->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr500x3AlSciDet1PXXD->GetXaxis()->SetRangeUser(0,2.05);
   gr500x3AlSciDet1PXXD->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr500x3AlSciDet1PXXD->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
   gr500x3AlSciDet1PXXD->GetYaxis()->SetTitleOffset(1.8);
   gr500x3AlSciDet1PXXD->SetMarkerColor(kBlack);
   gr500x3AlSciDet1PXXD->SetMarkerStyle(33);
   gr500x3AlSciDet1PXXD->SetLineColor(kBlack);
   gr500x3AlSciDet1PXXD->Draw("ALP");
   TGraph *gr500x3AlSciDet1PXeD = new TGraph(nsamps,Ethrx,PXearr500x3AlD); 
   gr500x3AlSciDet1PXeD->SetMarkerColor(kRed);
   gr500x3AlSciDet1PXeD->SetMarkerStyle(31);
   gr500x3AlSciDet1PXeD->SetLineColor(kRed);
   gr500x3AlSciDet1PXeD->Draw("LP");
   leg500x3AlSciDet1PXXPXeD = new TLegend(0.2,-0.005,0.4,0.08);
   leg500x3AlSciDet1PXXPXeD->AddEntry(gr500x3AlSciDet1PXXD,"P_{X->X}","lp");
   leg500x3AlSciDet1PXXPXeD->AddEntry(gr500x3AlSciDet1PXeD,"P_{X->e}","lp");
   leg500x3AlSciDet1PXXPXeD->Draw();

   c->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr750x3AlSciDet1PXXD = new TGraph(nsamps,Ethrx,PXXarr750x3AlD); 
   gr750x3AlSciDet1PXXD->SetTitle("10 MeV: 3-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3} D-stream [10^6 events]");
   gr750x3AlSciDet1PXXD->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr750x3AlSciDet1PXXD->GetXaxis()->SetRangeUser(0,2.05);
   gr750x3AlSciDet1PXXD->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr750x3AlSciDet1PXXD->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
   gr750x3AlSciDet1PXXD->GetYaxis()->SetTitleOffset(1.8);
   gr750x3AlSciDet1PXXD->SetMarkerColor(kBlack);
   gr750x3AlSciDet1PXXD->SetMarkerStyle(33);
   gr750x3AlSciDet1PXXD->SetLineColor(kBlack);
   gr750x3AlSciDet1PXXD->Draw("ALP");
   TGraph *gr750x3AlSciDet1PXeD = new TGraph(nsamps,Ethrx,PXearr750x3AlD); 
   gr750x3AlSciDet1PXeD->SetMarkerColor(kRed);
   gr750x3AlSciDet1PXeD->SetMarkerStyle(31);
   gr750x3AlSciDet1PXeD->SetLineColor(kRed);
   gr750x3AlSciDet1PXeD->Draw("LP");
   leg750x3AlSciDet1PXXPXeD = new TLegend(0.2,-0.005,0.4,0.08);
   leg750x3AlSciDet1PXXPXeD->AddEntry(gr750x3AlSciDet1PXXD,"P_{X->X}","lp");
   leg750x3AlSciDet1PXXPXeD->AddEntry(gr750x3AlSciDet1PXeD,"P_{X->e}","lp");
   leg750x3AlSciDet1PXXPXeD->Draw();
  
   c->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr250x6AlSciDet1PXXD = new TGraph(nsamps,Ethrx,PXXarr250x6AlD);
   gr250x6AlSciDet1PXXD->SetTitle("10 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3} D-stream [10^6 events]");
   gr250x6AlSciDet1PXXD->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr250x6AlSciDet1PXXD->GetXaxis()->SetRangeUser(0,2.05);
   gr250x6AlSciDet1PXXD->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr250x6AlSciDet1PXXD->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
   gr250x6AlSciDet1PXXD->GetYaxis()->SetTitleOffset(1.8);
   gr250x6AlSciDet1PXXD->SetMarkerColor(kBlack);
   gr250x6AlSciDet1PXXD->SetMarkerStyle(33);
   gr250x6AlSciDet1PXXD->SetLineColor(kBlack);
   gr250x6AlSciDet1PXXD->Draw("ALP");
   TGraph *gr250x6AlSciDet1PXeD = new TGraph(nsamps,Ethrx,PXearr250x6AlD); 
   gr250x6AlSciDet1PXeD->SetMarkerColor(kRed);
   gr250x6AlSciDet1PXeD->SetMarkerStyle(31);
   gr250x6AlSciDet1PXeD->SetLineColor(kRed);
   gr250x6AlSciDet1PXeD->Draw("LP");
   leg250x6AlSciDet1PXXPXeD = new TLegend(0.2,-0.005,0.4,0.08);
   leg250x6AlSciDet1PXXPXeD->AddEntry(gr250x6AlSciDet1PXXD,"P_{X->X}","lp");
   leg250x6AlSciDet1PXXPXeD->AddEntry(gr250x6AlSciDet1PXeD,"P_{X->e}","lp");
   leg250x6AlSciDet1PXXPXeD->Draw();
    
   c->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr500x6AlSciDet1PXXD = new TGraph(nsamps,Ethrx,PXXarr500x6AlD);
   gr500x6AlSciDet1PXXD->SetTitle("10 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3} D-stream [10^6 events]");
   gr500x6AlSciDet1PXXD->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr500x6AlSciDet1PXXD->GetXaxis()->SetRangeUser(0,2.05);
   gr500x6AlSciDet1PXXD->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr500x6AlSciDet1PXXD->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr500x6AlSciDet1PXXD->GetYaxis()->SetTitleOffset(1.8);
   gr500x6AlSciDet1PXXD->SetMarkerColor(kBlack);
   gr500x6AlSciDet1PXXD->SetMarkerStyle(33);
   gr500x6AlSciDet1PXXD->SetLineColor(kBlack);
   gr500x6AlSciDet1PXXD->Draw("ALP");
   TGraph *gr500x6AlSciDet1PXeD = new TGraph(nsamps,Ethrx,PXearr500x6AlD); 
   gr500x6AlSciDet1PXeD->SetMarkerColor(kRed);
   gr500x6AlSciDet1PXeD->SetMarkerStyle(31);
   gr500x6AlSciDet1PXeD->SetLineColor(kRed);
   gr500x6AlSciDet1PXeD->Draw("LP");
   leg500x6AlSciDet1PXXPXeD = new TLegend(0.2,-0.005,0.4,0.08);
   leg500x6AlSciDet1PXXPXeD->AddEntry(gr500x6AlSciDet1PXXD,"P_{X->X}","lp");
   leg500x6AlSciDet1PXXPXeD->AddEntry(gr500x6AlSciDet1PXeD,"P_{X->e}","lp");
   leg500x6AlSciDet1PXXPXeD->Draw();
    
   c->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr750x6AlSciDet1PXXD = new TGraph(nsamps,Ethrx,PXXarr750x6AlD);
   gr750x6AlSciDet1PXXD->SetTitle("10 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3} D-stream [10^6 events]");
   gr750x6AlSciDet1PXXD->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr750x6AlSciDet1PXXD->GetXaxis()->SetRangeUser(0,2.05);
   gr750x6AlSciDet1PXXD->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr750x6AlSciDet1PXXD->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
   gr750x6AlSciDet1PXXD->GetYaxis()->SetTitleOffset(1.8);
   gr750x6AlSciDet1PXXD->SetMarkerColor(kBlack);
   gr750x6AlSciDet1PXXD->SetMarkerStyle(33);
   gr750x6AlSciDet1PXXD->SetLineColor(kBlack);
   gr750x6AlSciDet1PXXD->Draw("ALP");
   TGraph *gr750x6AlSciDet1PXeD = new TGraph(nsamps,Ethrx,PXearr750x6AlD); 
   gr750x6AlSciDet1PXeD->SetMarkerColor(kRed);
   gr750x6AlSciDet1PXeD->SetMarkerStyle(31);
   gr750x6AlSciDet1PXeD->SetLineColor(kRed);
   gr750x6AlSciDet1PXeD->Draw("LP");
   leg750x6AlSciDet1PXXPXeD = new TLegend(0.2,-0.005,0.4,0.08);
   leg750x6AlSciDet1PXXPXeD->AddEntry(gr750x6AlSciDet1PXXD,"P_{X->X}","lp");
   leg750x6AlSciDet1PXXPXeD->AddEntry(gr750x6AlSciDet1PXeD,"P_{X->e}","lp");
   leg750x6AlSciDet1PXXPXeD->Draw();

   c->SaveAs("Bubble4BinPlot_PXX_PXe_3mm_6mm_10_MeV_D_stream.pdf");
   c->SaveAs("Bubble4BinPlot_PXX_PXe_3mm_6mm_10_MeV_D_stream.png");
   c->SaveAs("Bubble4BinPlot_PXX_PXe_3mm_6mm_10_MeV_D_stream.C");
 
  
  
   TCanvas *d = new TCanvas("d","E_{THR}",800,600);
   d->Divide(3,2);
   d->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr250x3AlSciDet1PXXU = new TGraph(nsamps,Ethrx,PXXarr250x3AlU);
   gr250x3AlSciDet1PXXU->SetTitle("10 MeV: 3-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3} U-stream [10^6 events]");
   gr250x3AlSciDet1PXXU->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr250x3AlSciDet1PXXU->GetXaxis()->SetRangeUser(0,2.05);
   gr250x3AlSciDet1PXXU->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr250x3AlSciDet1PXXU->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
   gr250x3AlSciDet1PXXU->GetYaxis()->SetTitleOffset(1.8);
   gr250x3AlSciDet1PXXU->SetMarkerColor(kBlack);
   gr250x3AlSciDet1PXXU->SetMarkerStyle(33);
   gr250x3AlSciDet1PXXU->SetLineColor(kBlack);
   gr250x3AlSciDet1PXXU->Draw("ALP");
   TGraph *gr250x3AlSciDet1PXeU = new TGraph(nsamps,Ethrx,PXearr250x3AlU); 
   gr250x3AlSciDet1PXeU->SetMarkerColor(kRed);
   gr250x3AlSciDet1PXeU->SetMarkerStyle(31);
   gr250x3AlSciDet1PXeU->SetLineColor(kRed);
   gr250x3AlSciDet1PXeU->Draw("LP");
   leg250x3AlSciDet1PXXPXeU = new TLegend(0.2,-0.005,0.4,0.08);
   leg250x3AlSciDet1PXXPXeU->AddEntry(gr250x3AlSciDet1PXXU,"P_{X->X}","lp");
   leg250x3AlSciDet1PeXPXeU->AddEntry(gr250x3AlSciDet1PXeU,"P_{X->e}","lp");
   leg250x3AlSciDet1PXXPXeU->Draw();
  
   d->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr500x3AlSciDet1PXXU = new TGraph(nsamps,Ethrx,PXXarr500x3AlU);  
   gr500x3AlSciDet1PXXU->SetTitle("10 MeV: 3-mm Al + 2x5-mm SCiD_{1,2} + 500-mm SciD_{3} U-stream [10^6 events]");
   gr500x3AlSciDet1PXXU->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr500x3AlSciDet1PXXU->GetXaxis()->SetRangeUser(0,2.05);
   gr500x3AlSciDet1PXXU->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr500x3AlSciDet1PXXU->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
   gr500x3AlSciDet1PXXU->GetYaxis()->SetTitleOffset(1.8);
   gr500x3AlSciDet1PXXU->SetMarkerColor(kBlack);
   gr500x3AlSciDet1PXXU->SetMarkerStyle(33);
   gr500x3AlSciDet1PXXU->SetLineColor(kBlack);
   gr500x3AlSciDet1PXXU->Draw("ALP");
   TGraph *gr500x3AlSciDet1PXeU = new TGraph(nsamps,Ethrx,PXearr500x3AlU); 
   gr500x3AlSciDet1PXeU->SetMarkerColor(kRed);
   gr500x3AlSciDet1PXeU->SetMarkerStyle(31);
   gr500x3AlSciDet1PXeU->SetLineColor(kRed);
   gr500x3AlSciDet1PXeU->Draw("LP");
   leg500x3AlSciDet1PXXPXeU = new TLegend(0.2,-0.005,0.4,0.08);
   leg500x3AlSciDet1PXXPXeU->AddEntry(gr500x3AlSciDet1PXXU,"P_{X->X}","lp");
   leg500x3AlSciDet1PXXPXeU->AddEntry(gr500x3AlSciDet1PXeU,"P_{X->e}","lp");
   leg500x3AlSciDet1PXXPXeU->Draw();

   d->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr750x3AlSciDet1PXXU = new TGraph(nsamps,Ethrx,PXXarr750x3AlU); 
   gr750x3AlSciDet1PXXU->SetTitle("10 MeV: 3-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3} U-stream [10^6 events]");
   gr750x3AlSciDet1PXXU->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr750x3AlSciDet1PXXU->GetXaxis()->SetRangeUser(0,2.05);
   gr750x3AlSciDet1PXXU->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr750x3AlSciDet1PXXU->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr750x3AlSciDet1PXXU->GetYaxis()->SetTitleOffset(1.8);
   gr750x3AlSciDet1PXXU->SetMarkerColor(kBlack);
   gr750x3AlSciDet1PXXU->SetMarkerStyle(33);
   gr750x3AlSciDet1PXXU->SetLineColor(kBlack);
   gr750x3AlSciDet1PXXU->Draw("ALP");
   TGraph *gr750x3AlSciDet1PXeU = new TGraph(nsamps,Ethrx,PXearr750x3AlU); 
   gr750x3AlSciDet1PXeU->SetMarkerColor(kRed);
   gr750x3AlSciDet1PXeU->SetMarkerStyle(31);
   gr750x3AlSciDet1PXeU->SetLineColor(kRed);
   gr750x3AlSciDet1PXeU->Draw("LP");
   leg750x3AlSciDet1PXXPXeU = new TLegend(0.2,-0.005,0.4,0.08);
   leg750x3AlSciDet1PXXPXeU->AddEntry(gr750x3AlSciDet1PXXU,"P_{X->X}","lp");
   leg750x3AlSciDet1PeXPXeU->AddEntry(gr750x3AlSciDet1PXeU,"P_{X->e}","lp");
   leg750x3AlSciDet1PeXPXeU->Draw();
  
   d->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr250x6AlSciDet1PXXU = new TGraph(nsamps,Ethrx,PXXarr250x6AlU);
   gr250x6AlSciDet1PXXU->SetTitle("10 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3} U-stream [10^6 events]");
   gr250x6AlSciDet1PXXU->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr250x6AlSciDet1PXXU->GetXaxis()->SetRangeUser(0,2.05);
   gr250x6AlSciDet1PXXU->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr250x6AlSciDet1PXXU->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr250x6AlSciDet1PXXU->GetYaxis()->SetTitleOffset(1.8);
   gr250x6AlSciDet1PXXU->SetMarkerColor(kBlack);
   gr250x6AlSciDet1PXXU->SetMarkerStyle(33);
   gr250x6AlSciDet1PXXU->SetLineColor(kBlack);
   gr250x6AlSciDet1PXXU->Draw("ALP");
   TGraph *gr250x6AlSciDet1PXeU = new TGraph(nsamps,Ethrx,PXearr250x6AlU); 
   gr250x6AlSciDet1PXeU->SetMarkerColor(kRed);
   gr250x6AlSciDet1PXeU->SetMarkerStyle(31);
   gr250x6AlSciDet1PXeU->SetLineColor(kRed);
   gr250x6AlSciDet1PXeU->Draw("LP");
   leg250x6AlSciDet1PXXPXeU = new TLegend(0.2,-0.005,0.4,0.08);
   leg250x6AlSciDet1PXXPXeU->AddEntry(gr250x6AlSciDet1PXXU,"P_{X->X}","lp");
   leg250x6AlSciDet1PXXPXeU->AddEntry(gr250x6AlSciDet1PXeU,"P_{X->e}","lp");
   leg250x6AlSciDet1PXXPXeU->Draw();
    
   d->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr500x6AlSciDet1PXXU = new TGraph(nsamps,Ethrx,PXXarr500x6AlU);
   gr500x6AlSciDet1PXXU->SetTitle("10 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3} U-stream [10^6 events]");
   gr500x6AlSciDet1PXXU->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr500x6AlSciDet1PXXU->GetXaxis()->SetRangeUser(0,2.05);
   gr500x6AlSciDet1PXXU->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr500x6AlSciDet1PXXU->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
   gr500x6AlSciDet1PXXU->GetYaxis()->SetTitleOffset(1.8);
   gr500x6AlSciDet1PXXU->SetMarkerColor(kBlack);
   gr500x6AlSciDet1PXXU->SetMarkerStyle(33);
   gr500x6AlSciDet1PXXU->SetLineColor(kBlack);
   gr500x6AlSciDet1PXXU->Draw("ALP");
   TGraph *gr500x6AlSciDet1PXeU = new TGraph(nsamps,Ethrx,PXearr500x6AlU); 
   gr500x6AlSciDet1PXeU->SetMarkerColor(kRed);
   gr500x6AlSciDet1PXeU->SetMarkerStyle(31);
   gr500x6AlSciDet1PXeU->SetLineColor(kRed);
   gr500x6AlSciDet1PXeU->Draw("LP");
   leg500x6AlSciDet1PXXPXeU = new TLegend(0.2,-0.005,0.4,0.08);
   leg500x6AlSciDet1PXXPXeU->AddEntry(gr500x6AlSciDet1PXXU,"P_{X->X}","lp");
   leg500x6AlSciDet1PXXPXeU->AddEntry(gr500x6AlSciDet1PXeU,"P_{X->e}","lp");
   leg500x6AlSciDet1PXXPXeU->Draw();
    
   d->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr750x6AlSciDet1PXXU = new TGraph(nsamps,Ethrx,PXXarr750x6AlU);
   gr750x6AlSciDet1PXXU->SetTitle("10 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3} U-stream [10^6 events]");
   gr750x6AlSciDet1PXXU->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr750x6AlSciDet1PXXU->GetXaxis()->SetRangeUser(0,2.05);
   gr750x6AlSciDet1PXXU->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr750x6AlSciDet1PXXU->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr750x6AlSciDet1PXXU->GetYaxis()->SetTitleOffset(1.8);
   gr750x6AlSciDet1PXXU->SetMarkerColor(kBlack);
   gr750x6AlSciDet1PXXU->SetMarkerStyle(33);
   gr750x6AlSciDet1PXXU->SetLineColor(kBlack);
   gr750x6AlSciDet1PXXU->Draw("ALP");
   TGraph *gr750x6AlSciDet1PXeU = new TGraph(nsamps,Ethrx,PXearr750x6AlU); 
   gr750x6AlSciDet1PXeU->SetMarkerColor(kRed);
   gr750x6AlSciDet1PXeU->SetMarkerStyle(31);
   gr750x6AlSciDet1PXeU->SetLineColor(kRed);
   gr750x6AlSciDet1PXeU->Draw("LP");
   leg750x6AlSciDet1PXXPXeU = new TLegend(0.2,-0.005,0.4,0.08);
   leg750x6AlSciDet1PXXPXeU->AddEntry(gr750x6AlSciDet1PXXU,"P_{X->X}","lp");
   leg750x6AlSciDet1PXXPXeU->AddEntry(gr750x6AlSciDet1PXeU,"P_{X->e}","lp");
   leg750x6AlSciDet1PXXPXeU->Draw();

   d->SaveAs("Bubble4BinPlot_PXX_PXe_3mm_6mm_10_MeV_U_stream.pdf");
   d->SaveAs("Bubble4BinPlot_PXX_PXe_3mm_6mm_10_MeV_U_stream.png");
   d->SaveAs("Bubble4BinPlot_PXX_PXe_3mm_6mm_10_MeV_U_stream.C");
 

  
  
 }
 
 
 int main() {
   planarBINx();
   return 0;
}  
