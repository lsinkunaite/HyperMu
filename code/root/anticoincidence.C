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

void anticoincidence(){

   //Some style definitions
   //gROOT->Reset();
   //gROOT->SetStyle("Plain");
   gStyle->SetPaperSize(26,20);
   gStyle->SetOptStat(1);
   gStyle->SetTitleXOffset(1.15);
   gStyle->SetTitleYOffset(1.15);
   gStyle->SetTitleBorderSize(0.1);
   gStyle->SetLegendBorderSize(0.1);
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

   const int nsamps = 101;
   std::string phishift = "0";
   std::string zshift = "0";
   std::string path = "../../simdata/order/";
   std::string cavmaterial = "Cu";
   std::string BGOmaterial = "BGO";
   std::string dA1 = "400";
   std::string dL1 = "30";
   
   // Names of the files
   // X-ray cascade
   std::string filexSciD1 = path+cavmaterial+"_cav_"+BGOmaterial+"_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_SciD1.txt";
   std::string filexSciD2 = path+cavmaterial+"_cav_"+BGOmaterial+"_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_SciD2.txt";
   std::string filexSciD3 = path+cavmaterial+"_cav_"+BGOmaterial+"_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_SciD3.txt";
   std::string filexBGOD1 = path+cavmaterial+"_cav_"+BGOmaterial+"_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD2 = path+cavmaterial+"_cav_"+BGOmaterial+"_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_BGOD2.txt";


   // Vectors with filenames   
   std::vector<std::string> Xfiles;

   // X-ray cascade		 
   Xfiles.push_back(filexSciD1);
   Xfiles.push_back(filexSciD2);
   Xfiles.push_back(filexSciD3);
   Xfiles.push_back(filexBGOD1);
   Xfiles.push_back(filexBGOD2);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep, EventID;
   float iEventID;

   float Ethr1 = 0.6;
   float Ethr21 = 0.5;
   float Ethr22 = 10.0;
   float Ethr3 = 1;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
   float EthrmuThin[nsamps] = {};
   float EthrmuThick[nsamps] = {};
   float EstepThin = 1.5/(nsamps-1);
   float EstepThick = 4.0/(nsamps-1);
		   
   // Storage vectors
   // Normalisation 2 [abs = total] :: X-ray cascade [Cu]
   std::vector< std::vector<double> > PXevector(Xfiles.size()/5,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector(Xfiles.size()/5,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevectorThin(Xfiles.size()/5,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorThin(Xfiles.size()/5,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevectorThick(Xfiles.size()/5,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorThick(Xfiles.size()/5,std::vector<double>(nsamps));


   // X-ray cascade
   std::vector< std::vector< double > > allvEvIDSD1x;
   std::vector< std::vector< double > > allvEdepSD1x;
   std::vector< std::vector< double > > allvEvIDSD2x;
   std::vector< std::vector< double > > allvEdepSD2x;
   std::vector< std::vector< double > > allvEvIDSD3x;
   std::vector< std::vector< double > > allvEdepSD3x;
   std::vector< std::vector< double > > allvEvIDBD1x;
   std::vector< std::vector< double > > allvEdepBD1x;
   std::vector< std::vector< double > > allvEvIDBD2x;
   std::vector< std::vector< double > > allvEdepBD2x;


   float Ethr;
   float EthrThin;
   float EthrThick;
   int counterXX = 1e5;
   int XXray = 0; // X-rays i-fied as X-rays
   int Xelec = 0; // X-rays i-fied as electrons
   int XXrayThin = 0;
   int XelecThin = 0;
   int XXrayThick = 0;
   int XelecThick = 0;
   	   
   Ethrmu[0] = 0;
   EthrmuThin[0] = 0.1;
   EthrmuThick[0] = 7;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;
   for (int i=1; i<nsamps; i++) EthrmuThin[i] = EthrmuThin[i-1] + EstepThin;
   for (int i=1; i<nsamps; i++) EthrmuThick[i] = EthrmuThick[i-1] + EstepThick;


   //-------------------------------------------------------------------
   //                           Reading
   //-------------------------------------------------------------------
		   
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m------------------- X-ray cascade ------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


   for (int k=0; k<((Xfiles.size())/5); k++) {
			  
      // SciD1
	  std::ifstream xfSciD1(TString(Xfiles[k*5]));
	  std::vector<double> vEvIDSD1x;
	  std::vector<double> vEdepSD1x;
			  
	  while (!xfSciD1.eof()) {
	     double EvIDSD1, EdepSD1;
		 xfSciD1 >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1x.push_back(EvIDSD1);
		 vEdepSD1x.push_back(EdepSD1);
	  }
	  vEvIDSD1x.pop_back(); vEdepSD1x.pop_back();
	  vEvIDSD1x.pop_back(); vEdepSD1x.pop_back();
			  
	  xfSciD1.close();
	  allvEvIDSD1x.push_back(vEvIDSD1x);
	  allvEdepSD1x.push_back(vEdepSD1x);


	  // SciD2
	  std::ifstream xfSciD2(TString(Xfiles[(k*5)+1]));
	  std::vector<double> vEvIDSD2x;
	  std::vector<double> vEdepSD2x;
			  
	  while (!xfSciD2.eof()) {
	     double EvIDSD2, EdepSD2;
		 xfSciD2 >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2x.push_back(EvIDSD2);
		 vEdepSD2x.push_back(EdepSD2);
	  }
	  vEvIDSD2x.pop_back(); vEdepSD2x.pop_back();
	  vEvIDSD2x.pop_back(); vEdepSD2x.pop_back();
			  
	  xfSciD2.close();
	  allvEvIDSD2x.push_back(vEvIDSD2x);
	  allvEdepSD2x.push_back(vEdepSD2x);


	  // SciD3
	  std::ifstream xfSciD3(TString(Xfiles[(k*5)+2]));
	  std::vector<double> vEvIDSD3x;
	  std::vector<double> vEdepSD3x;
			  
	  while (!xfSciD3.eof()) {
	     double EvIDSD3, EdepSD3;
		 xfSciD3 >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3x.push_back(EvIDSD3);
		 vEdepSD3x.push_back(EdepSD3);
	  }
	  vEvIDSD3x.pop_back(); vEdepSD3x.pop_back();
	  vEvIDSD3x.pop_back(); vEdepSD3x.pop_back();
			  
	  xfSciD3.close();
	  allvEvIDSD3x.push_back(vEvIDSD3x);
	  allvEdepSD3x.push_back(vEdepSD3x);

			  
	  // BGOD1
	  std::ifstream xfBGOD1(TString(Xfiles[(k*5)+3]));
	  std::vector<double> vEvIDBD1x;
	  std::vector<double> vEdepBD1x;
			  
	  while (!xfBGOD1.eof()) {
	     double EvIDBD1, EdepBD1;
		 xfBGOD1 >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1x.push_back(EvIDBD1);
		 vEdepBD1x.push_back(EdepBD1);
	  }
	  vEvIDBD1x.pop_back(); vEdepBD1x.pop_back();
	  vEvIDBD1x.pop_back(); vEdepBD1x.pop_back();
			  
	  xfBGOD1.close();
	  allvEvIDBD1x.push_back(vEvIDBD1x);
	  allvEdepBD1x.push_back(vEdepBD1x);


	  // BGOD2
	  std::ifstream xfBGOD2(TString(Xfiles[(k*5)+4]));
	  std::vector<double> vEvIDBD2x;
	  std::vector<double> vEdepBD2x;
			  
	  while (!xfBGOD2.eof()) {
	     double EvIDBD2, EdepBD2;
		 xfBGOD2 >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2x.push_back(EvIDBD2);
		 vEdepBD2x.push_back(EdepBD2);
	  }
	  vEvIDBD2x.pop_back(); vEdepBD2x.pop_back();
	  vEvIDBD2x.pop_back(); vEdepBD2x.pop_back();
			  
	  xfBGOD2.close();
	  allvEvIDBD2x.push_back(vEvIDBD2x);
	  allvEdepBD2x.push_back(vEdepBD2x);


   }


		
   //-------------------------------------------------------------------
   //                     Bin-by-bin analysis
   //                          Mu-decay
   //-------------------------------------------------------------------     
			
   // X-ray cascade	  
   for (int i=0; i<allvEvIDBD1x.size(); i++) {
      
      std::cout << std::endl;
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m--------------------- X-ray cascade ----------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

      for (int m=0; m<nsamps; m++) {

	     Ethr = Ethrmu[m];
         EthrThin = EthrmuThin[m];
         EthrThick = EthrmuThick[m];

		 //--------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Cu Ethr21
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
		 // Normalisation 2 [absolute] :: cascade Cu Ethr1
		 //-------------------------------------------------- 
		 XXrayThin = 0; XelecThin = 0;
			  
		 for (int a=0; a<allvEvIDBD1x[0].size(); a++) {

		    if ((allvEdepSD1x[i][a] < EthrThin) && (allvEdepSD2x[i][a] < EthrThin) && (allvEdepSD3x[i][a] < EthrThin)) {
			   if (((allvEdepBD1x[i][a] > Ethr21) && (allvEdepBD1x[i][a] < Ethr22)) || ((allvEdepBD2x[i][a] > Ethr21) && (allvEdepBD2x[i][a] < Ethr22))) {
				  XXrayThin += 1;
			   } else { XelecThin += 1; }
		    } else { XelecThin += 1; }
		 }
				 
		 PXXvectorThin[i][m] = XXrayThin/(double)(counterXX);
		 PXevectorThin[i][m] = XelecThin/(double)(counterXX); 


		 //--------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Cu Ethr1
		 //-------------------------------------------------- 
		 XXrayThick = 0; XelecThick = 0;
			  
		 for (int a=0; a<allvEvIDBD1x[0].size(); a++) {

		    if ((allvEdepSD1x[i][a] < Ethr1) && (allvEdepSD2x[i][a] < Ethr1) && (allvEdepSD3x[i][a] < Ethr1)) {
			   if (((allvEdepBD1x[i][a] > Ethr21) && (allvEdepBD1x[i][a] < EthrThick)) || ((allvEdepBD2x[i][a] > Ethr21) && (allvEdepBD2x[i][a] < EthrThick))) {
				  XXrayThick += 1;
			   } else { XelecThick += 1; }
		    } else { XelecThick += 1; }
		 }
				 
		 PXXvectorThick[i][m] = XXrayThick/(double)(counterXX);
		 PXevectorThick[i][m] = XelecThick/(double)(counterXX); 

	  
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
   // Normalisation 2 [abs]
   float PXXarr[nsamps] = {}; // X-ray cascade
   float PXXThinarr[nsamps] = {};
   float PXXThickarr[nsamps] = {};
 		 	   
   for (int i=0; i<nsamps; i++) {
      // Normalisation 2 [absolute]
	  PXXarr[i] = PXXvector[0][i];
      PXXThinarr[i] = PXXvectorThin[0][i];
      PXXThickarr[i] = PXXvectorThick[0][i];
   }	   

		  
   TCanvas *f = new TCanvas("f","E_{THR}",800,600);
   f->Divide(3,1);
   f->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   //gPad->SetFixedAspectRatio();
   TGraph *grPXX = new TGraph(nsamps,Ethrmu,PXXarr);
   grPXX->SetTitle("E_{THR_{1}} = 0.6 MeV, E_{THR_{22}} = 10MeV"); 
   grPXX->GetXaxis()->SetTitle("E_{THR_{21}} [MeV]");
   grPXX->GetXaxis()->SetRangeUser(0,2.03);
   grPXX->GetXaxis()->SetNdivisions(-304);
   grPXX->GetYaxis()->SetMoreLogLabels(1);
   grPXX->GetYaxis()->SetTitle("P_{XX}");
   grPXX->GetYaxis()->SetTitleOffset(2.1);
   grPXX->GetYaxis()->SetRangeUser(6e-1,9.5e-1);
   grPXX->SetLineColor(kRed);
   grPXX->SetLineWidth(3);
   grPXX->Draw("ALP");
   
   f->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPXXThin = new TGraph(nsamps,EthrmuThin,PXXThinarr);
   grPXXThin->SetTitle("E_{THR_{21}} = 0.5 MeV, E_{THR_{22}} = 10 MeV");
   grPXXThin->GetXaxis()->SetTitle("E_{THR_{1}} [MeV]");
   grPXXThin->GetXaxis()->SetRangeUser(0.05,1.69);
   grPXXThin->GetXaxis()->SetNdivisions(-304);
   TGaxis::SetMaxDigits(2);
   grPXXThin->GetYaxis()->SetMoreLogLabels(1);
   grPXXThin->GetYaxis()->SetTitle("P_{XX}");
   grPXXThin->GetYaxis()->SetTitleOffset(2.1);
   grPXXThin->GetYaxis()->SetRangeUser(7.6e-1,9.2e-1);
   grPXXThin->SetLineColor(kRed);
   grPXXThin->SetLineWidth(3);
   grPXXThin->Draw("ALP");

   f->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPXXThick = new TGraph(nsamps,EthrmuThick,PXXThickarr);
   grPXXThick->SetTitle("E_{THR_1} = 0.6 MeV, E_{THR_{21}} = 0.5 MeV");
   grPXXThick->GetXaxis()->SetTitle("E_{THR_{22}} [MeV]");
   grPXXThick->GetXaxis()->SetRangeUser(6.7,11.2);
   grPXXThick->GetXaxis()->SetNdivisions(-304);
   TGaxis::SetMaxDigits(2);
   grPXXThick->GetYaxis()->SetMoreLogLabels(1);
   grPXXThick->GetYaxis()->SetTitle("P_{XX}");
   grPXXThick->GetYaxis()->SetTitleOffset(2.1);
   grPXXThick->GetYaxis()->SetRangeUser(7.9e-1,8.7e-1);
   grPXXThick->SetLineColor(kRed);
   grPXXThick->SetLineWidth(3);
   grPXXThick->Draw("ALP");


   f->SaveAs(TString(cavmaterial)+"_cav_"+TString(BGOmaterial)+"_dA1_"+TString(dA1)+"mm_dL1_"+TString(dL1)+"mm_Anticoincidence1.pdf");
   f->SaveAs(TString(cavmaterial)+"_cav_"+TString(BGOmaterial)+"_dA1_"+TString(dA1)+"mm_dL1_"+TString(dL1)+"mm_Anticoincidence1.png");
   f->SaveAs(TString(cavmaterial)+"_cav_"+TString(BGOmaterial)+"_dA1_"+TString(dA1)+"mm_dL1_"+TString(dL1)+"mm_Anticoincidence1.C");

} 
 
 int main() {
   anticoincidence();
   return 0;
}  
