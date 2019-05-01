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

void thesiseff(){

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
   std::string path = "../../simdata/thesis/";
   std::string dA1 = "400";
   std::string dL1 = "100";
   
   // Names of the files
   // X-ray cascade
   std::string filexSciD1 = path+"Cu_cav_Al_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_SciD1.txt";
   std::string filexSciD2 = path+"Cu_cav_Al_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_SciD2.txt";
   std::string filexSciD3 = path+"Cu_cav_Al_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_SciD3.txt";
   std::string filexBGOD1 = path+"Cu_cav_Al_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD2 = path+"Cu_cav_Al_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_BGOD2.txt";

   std::string filexSciD12 = path+"Glass_cav_Al2_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_SciD1.txt";
   std::string filexSciD22 = path+"Glass_cav_Al2_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_SciD2.txt";
   std::string filexSciD32 = path+"Glass_cav_Al2_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_SciD3.txt";
   std::string filexBGOD12 = path+"Glass_cav_Al2_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD22 = path+"Glass_cav_Al2_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade_BGOD2.txt";


   // Mu-decay
   std::string filemuSciD1 = path+"Cu_cav_Al_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5mudecay_SciD1.txt";
   std::string filemuSciD2 = path+"Cu_cav_Al_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5mudecay_SciD2.txt";
   std::string filemuSciD3 = path+"Cu_cav_Al_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5mudecay_SciD3.txt";
   std::string filemuBGOD1 = path+"Cu_cav_Al_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD2 = path+"Cu_cav_Al_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5mudecay_BGOD2.txt";

   std::string filemuSciD12 = path+"Glass_cav_Al2_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5mudecay_SciD1.txt";
   std::string filemuSciD22 = path+"Glass_cav_Al2_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5mudecay_SciD2.txt";
   std::string filemuSciD32 = path+"Glass_cav_Al2_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5mudecay_SciD3.txt";
   std::string filemuBGOD12 = path+"Glass_cav_Al2_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD22 = path+"Glass_cav_Al2_NaI_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5mudecay_BGOD2.txt";


   // Vectors with filenames   
   std::vector<std::string> Xfiles;
   std::vector<std::string> mufiles;

   // X-ray cascade		 
   Xfiles.push_back(filexSciD1);
   Xfiles.push_back(filexSciD2);
   Xfiles.push_back(filexSciD3);
   Xfiles.push_back(filexBGOD1);
   Xfiles.push_back(filexBGOD2);

   Xfiles.push_back(filexSciD12);
   Xfiles.push_back(filexSciD22);
   Xfiles.push_back(filexSciD32);
   Xfiles.push_back(filexBGOD12);
   Xfiles.push_back(filexBGOD22);


   // Mu-decay
   mufiles.push_back(filemuSciD1);
   mufiles.push_back(filemuSciD2);
   mufiles.push_back(filemuSciD3);
   mufiles.push_back(filemuBGOD1);
   mufiles.push_back(filemuBGOD2);

   mufiles.push_back(filemuSciD12);
   mufiles.push_back(filemuSciD22);
   mufiles.push_back(filemuSciD32);
   mufiles.push_back(filemuBGOD12);
   mufiles.push_back(filemuBGOD22);


   /*********************************/
   /*           Analysis            */
   /*********************************/

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

   std::vector< std::vector< double > > allvEvIDSD12x;
   std::vector< std::vector< double > > allvEdepSD12x;
   std::vector< std::vector< double > > allvEvIDSD22x;
   std::vector< std::vector< double > > allvEdepSD22x;
   std::vector< std::vector< double > > allvEvIDSD32x;
   std::vector< std::vector< double > > allvEdepSD32x;
   std::vector< std::vector< double > > allvEvIDBD12x;
   std::vector< std::vector< double > > allvEdepBD12x;
   std::vector< std::vector< double > > allvEvIDBD22x;
   std::vector< std::vector< double > > allvEdepBD22x;


   // Mu-decay
   std::vector< std::vector< double > > allvEvIDSD1mu;
   std::vector< std::vector< double > > allvEdepSD1mu;
   std::vector< std::vector< double > > allvEvIDSD2mu;
   std::vector< std::vector< double > > allvEdepSD2mu;
   std::vector< std::vector< double > > allvEvIDSD3mu;
   std::vector< std::vector< double > > allvEdepSD3mu;
   std::vector< std::vector< double > > allvEvIDBD1mu;
   std::vector< std::vector< double > > allvEdepBD1mu;
   std::vector< std::vector< double > > allvEvIDBD2mu;
   std::vector< std::vector< double > > allvEdepBD2mu;

   std::vector< std::vector< double > > allvEvIDSD12mu;
   std::vector< std::vector< double > > allvEdepSD12mu;
   std::vector< std::vector< double > > allvEvIDSD22mu;
   std::vector< std::vector< double > > allvEdepSD22mu;
   std::vector< std::vector< double > > allvEvIDSD32mu;
   std::vector< std::vector< double > > allvEdepSD32mu;
   std::vector< std::vector< double > > allvEvIDBD12mu;
   std::vector< std::vector< double > > allvEdepBD12mu;
   std::vector< std::vector< double > > allvEvIDBD22mu;
   std::vector< std::vector< double > > allvEdepBD22mu;


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


   //-------------------------------------------------------------------
   //                           Reading
   //-------------------------------------------------------------------
		   
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m------------------- X-ray cascade ------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


   for (int k=0; k<((Xfiles.size())/10); k++) {
			  
      // SciD1 Cu - Al
	  std::ifstream xfSciD1(TString(Xfiles[k*10]));
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


	  // SciD2 Cu - Al
	  std::ifstream xfSciD2(TString(Xfiles[(k*10)+1]));
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


	  // SciD3 Cu - Al
	  std::ifstream xfSciD3(TString(Xfiles[(k*10)+2]));
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

			  
	  // BGOD1 Cu - Al
	  std::ifstream xfBGOD1(TString(Xfiles[(k*10)+3]));
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


	  // BGOD2 Cu - Al
	  std::ifstream xfBGOD2(TString(Xfiles[(k*10)+4]));
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


      // SciD1 Glass - Al2
	  std::ifstream xfSciD12(TString(Xfiles[(k*10)+5]));
	  std::vector<double> vEvIDSD12x;
	  std::vector<double> vEdepSD12x;
			  
	  while (!xfSciD12.eof()) {
	     double EvIDSD1, EdepSD1;
		 xfSciD12 >> EvIDSD1 >> EdepSD1;
		 vEvIDSD12x.push_back(EvIDSD1);
		 vEdepSD12x.push_back(EdepSD1);
	  }
	  vEvIDSD12x.pop_back(); vEdepSD12x.pop_back();
	  vEvIDSD12x.pop_back(); vEdepSD12x.pop_back();
			  
	  xfSciD12.close();
	  allvEvIDSD12x.push_back(vEvIDSD12x);
	  allvEdepSD12x.push_back(vEdepSD12x);


	  // SciD2 Glass - Al2
	  std::ifstream xfSciD22(TString(Xfiles[(k*10)+6]));
	  std::vector<double> vEvIDSD22x;
	  std::vector<double> vEdepSD22x;
			  
	  while (!xfSciD22.eof()) {
	     double EvIDSD2, EdepSD2;
		 xfSciD22 >> EvIDSD2 >> EdepSD2;
		 vEvIDSD22x.push_back(EvIDSD2);
		 vEdepSD22x.push_back(EdepSD2);
	  }
	  vEvIDSD22x.pop_back(); vEdepSD22x.pop_back();
	  vEvIDSD22x.pop_back(); vEdepSD22x.pop_back();
			  
	  xfSciD22.close();
	  allvEvIDSD22x.push_back(vEvIDSD22x);
	  allvEdepSD22x.push_back(vEdepSD22x);


	  // SciD3 Glass - Al2
	  std::ifstream xfSciD32(TString(Xfiles[(k*10)+7]));
	  std::vector<double> vEvIDSD32x;
	  std::vector<double> vEdepSD32x;
			  
	  while (!xfSciD32.eof()) {
	     double EvIDSD3, EdepSD3;
		 xfSciD32 >> EvIDSD3 >> EdepSD3;
		 vEvIDSD32x.push_back(EvIDSD3);
		 vEdepSD32x.push_back(EdepSD3);
	  }
	  vEvIDSD32x.pop_back(); vEdepSD32x.pop_back();
	  vEvIDSD32x.pop_back(); vEdepSD32x.pop_back();
			  
	  xfSciD32.close();
	  allvEvIDSD32x.push_back(vEvIDSD32x);
	  allvEdepSD32x.push_back(vEdepSD32x);

			  
	  // BGOD1 Glass - Al2
	  std::ifstream xfBGOD12(TString(Xfiles[(k*10)+8]));
	  std::vector<double> vEvIDBD12x;
	  std::vector<double> vEdepBD12x;
			  
	  while (!xfBGOD12.eof()) {
	     double EvIDBD1, EdepBD1;
		 xfBGOD12 >> EvIDBD1 >> EdepBD1;
		 vEvIDBD12x.push_back(EvIDBD1);
		 vEdepBD12x.push_back(EdepBD1);
	  }
	  vEvIDBD12x.pop_back(); vEdepBD12x.pop_back();
	  vEvIDBD12x.pop_back(); vEdepBD12x.pop_back();
			  
	  xfBGOD12.close();
	  allvEvIDBD12x.push_back(vEvIDBD12x);
	  allvEdepBD12x.push_back(vEdepBD12x);


	  // BGOD2 Glass - Al2
	  std::ifstream xfBGOD22(TString(Xfiles[(k*10)+9]));
	  std::vector<double> vEvIDBD22x;
	  std::vector<double> vEdepBD22x;
			  
	  while (!xfBGOD22.eof()) {
	     double EvIDBD2, EdepBD2;
		 xfBGOD22 >> EvIDBD2 >> EdepBD2;
		 vEvIDBD22x.push_back(EvIDBD2);
		 vEdepBD22x.push_back(EdepBD2);
	  }
	  vEvIDBD22x.pop_back(); vEdepBD22x.pop_back();
	  vEvIDBD22x.pop_back(); vEdepBD22x.pop_back();
			  
	  xfBGOD22.close();
	  allvEvIDBD22x.push_back(vEvIDBD22x);
	  allvEdepBD22x.push_back(vEdepBD22x);

   }


   for (int k=0; k<((mufiles.size())/10); k++) {
   
      // SciD1mu Cu - Al
	  std::ifstream mufSciD1(TString(mufiles[k*10]));
	  std::vector<double> vEvIDSD1mu;
	  std::vector<double> vEdepSD1mu;
			  
	  while (!mufSciD1.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mufSciD1 >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1mu.push_back(EvIDSD1mu);
		 vEdepSD1mu.push_back(EdepSD1mu);
	  }
	  vEvIDSD1mu.pop_back(); vEdepSD1mu.pop_back();
	  vEvIDSD1mu.pop_back(); vEdepSD1mu.pop_back();
			  
	  mufSciD1.close();
	  allvEvIDSD1mu.push_back(vEvIDSD1mu);
	  allvEdepSD1mu.push_back(vEdepSD1mu);


	  // SciD2mu Cu - Al
	  std::ifstream mufSciD2(TString(mufiles[(k*10)+1]));
	  std::vector<double> vEvIDSD2mu;
	  std::vector<double> vEdepSD2mu;
			  
	  while (!mufSciD2.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mufSciD2 >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2mu.push_back(EvIDSD2mu);
		 vEdepSD2mu.push_back(EdepSD2mu);
	  }
	  vEvIDSD2mu.pop_back(); vEdepSD2mu.pop_back();
	  vEvIDSD2mu.pop_back(); vEdepSD2mu.pop_back();
			  
	  mufSciD2.close();
	  allvEvIDSD2mu.push_back(vEvIDSD2mu);
	  allvEdepSD2mu.push_back(vEdepSD2mu);


	  // SciD3mu Cu - Al
	  std::ifstream mufSciD3(TString(mufiles[(k*10)+2]));
	  std::vector<double> vEvIDSD3mu;
	  std::vector<double> vEdepSD3mu;
			  
	  while (!mufSciD3.eof()) {
	     double EvIDSD3mu, EdepSD3mu;
		 mufSciD3 >> EvIDSD3mu >> EdepSD3mu;
		 vEvIDSD3mu.push_back(EvIDSD3mu);
		 vEdepSD3mu.push_back(EdepSD3mu);
	  }
	  vEvIDSD3mu.pop_back(); vEdepSD3mu.pop_back();
	  vEvIDSD3mu.pop_back(); vEdepSD3mu.pop_back();
			  
	  mufSciD3.close();
	  allvEvIDSD3mu.push_back(vEvIDSD3mu);
	  allvEdepSD3mu.push_back(vEdepSD3mu);
			 

	  // BGOD1mu Cu - Al
	  std::ifstream mufBGOD1(TString(mufiles[(k*10)+3]));
	  std::vector<double> vEvIDBD1mu;
	  std::vector<double> vEdepBD1mu;
			  
	  while (!mufBGOD1.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mufBGOD1 >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1mu.push_back(EvIDBD1mu);
		 vEdepBD1mu.push_back(EdepBD1mu);
	  }
	  vEvIDBD1mu.pop_back(); vEdepBD1mu.pop_back();
	  vEvIDBD1mu.pop_back(); vEdepBD1mu.pop_back();
			  
	  mufBGOD1.close();
	  allvEvIDBD1mu.push_back(vEvIDBD1mu);
	  allvEdepBD1mu.push_back(vEdepBD1mu);


	  // BGOD2mu Cu - Al
	  std::ifstream mufBGOD2(TString(mufiles[(k*10)+4]));
	  std::vector<double> vEvIDBD2mu;
	  std::vector<double> vEdepBD2mu;
			  
	  while (!mufBGOD2.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mufBGOD2 >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2mu.push_back(EvIDBD2mu);
		 vEdepBD2mu.push_back(EdepBD2mu);
	  }
	  vEvIDBD2mu.pop_back(); vEdepBD2mu.pop_back();
	  vEvIDBD2mu.pop_back(); vEdepBD2mu.pop_back();
			  
	  mufBGOD2.close();
	  allvEvIDBD2mu.push_back(vEvIDBD2mu);
	  allvEdepBD2mu.push_back(vEdepBD2mu);


      // SciD1mu Glass - Al2
	  std::ifstream mufSciD12(TString(mufiles[(k*10)+5]));
	  std::vector<double> vEvIDSD12mu;
	  std::vector<double> vEdepSD12mu;
			  
	  while (!mufSciD12.eof()) {
	     double EvIDSD12mu, EdepSD12mu;
		 mufSciD12 >> EvIDSD12mu >> EdepSD12mu;
		 vEvIDSD12mu.push_back(EvIDSD12mu);
		 vEdepSD12mu.push_back(EdepSD12mu);
	  }
	  vEvIDSD12mu.pop_back(); vEdepSD12mu.pop_back();
	  vEvIDSD12mu.pop_back(); vEdepSD12mu.pop_back();
			  
	  mufSciD12.close();
	  allvEvIDSD12mu.push_back(vEvIDSD12mu);
	  allvEdepSD12mu.push_back(vEdepSD12mu);


	  // SciD2mu Glass - Al2
	  std::ifstream mufSciD22(TString(mufiles[(k*10)+6]));
	  std::vector<double> vEvIDSD22mu;
	  std::vector<double> vEdepSD22mu;
			  
	  while (!mufSciD22.eof()) {
	     double EvIDSD22mu, EdepSD22mu;
		 mufSciD22 >> EvIDSD22mu >> EdepSD22mu;
		 vEvIDSD22mu.push_back(EvIDSD22mu);
		 vEdepSD22mu.push_back(EdepSD22mu);
	  }
	  vEvIDSD22mu.pop_back(); vEdepSD22mu.pop_back();
	  vEvIDSD22mu.pop_back(); vEdepSD22mu.pop_back();
			  
	  mufSciD22.close();
	  allvEvIDSD22mu.push_back(vEvIDSD22mu);
	  allvEdepSD22mu.push_back(vEdepSD22mu);


	  // SciD3mu Glass - Al2
	  std::ifstream mufSciD32(TString(mufiles[(k*10)+7]));
	  std::vector<double> vEvIDSD32mu;
	  std::vector<double> vEdepSD32mu;
			  
	  while (!mufSciD32.eof()) {
	     double EvIDSD32mu, EdepSD32mu;
		 mufSciD32 >> EvIDSD32mu >> EdepSD32mu;
		 vEvIDSD32mu.push_back(EvIDSD32mu);
		 vEdepSD32mu.push_back(EdepSD32mu);
	  }
	  vEvIDSD32mu.pop_back(); vEdepSD32mu.pop_back();
	  vEvIDSD32mu.pop_back(); vEdepSD32mu.pop_back();
			  
	  mufSciD32.close();
	  allvEvIDSD32mu.push_back(vEvIDSD32mu);
	  allvEdepSD32mu.push_back(vEdepSD32mu);
			 

	  // BGOD1mu Glass - Al2
	  std::ifstream mufBGOD12(TString(mufiles[(k*10)+8]));
	  std::vector<double> vEvIDBD12mu;
	  std::vector<double> vEdepBD12mu;
			  
	  while (!mufBGOD12.eof()) {
	     double EvIDBD12mu, EdepBD12mu;
		 mufBGOD12 >> EvIDBD12mu >> EdepBD12mu;
		 vEvIDBD12mu.push_back(EvIDBD12mu);
		 vEdepBD12mu.push_back(EdepBD12mu);
	  }
	  vEvIDBD12mu.pop_back(); vEdepBD12mu.pop_back();
	  vEvIDBD12mu.pop_back(); vEdepBD12mu.pop_back();
			  
	  mufBGOD12.close();
	  allvEvIDBD12mu.push_back(vEvIDBD12mu);
	  allvEdepBD12mu.push_back(vEdepBD12mu);


	  // BGOD2mu Glass - Al2
	  std::ifstream mufBGOD22(TString(mufiles[(k*10)+9]));
	  std::vector<double> vEvIDBD22mu;
	  std::vector<double> vEdepBD22mu;
			  
	  while (!mufBGOD22.eof()) {
	     double EvIDBD22mu, EdepBD22mu;
		 mufBGOD22 >> EvIDBD22mu >> EdepBD22mu;
		 vEvIDBD22mu.push_back(EvIDBD22mu);
		 vEdepBD22mu.push_back(EdepBD22mu);
	  }
	  vEvIDBD22mu.pop_back(); vEdepBD22mu.pop_back();
	  vEvIDBD22mu.pop_back(); vEdepBD22mu.pop_back();
			  
	  mufBGOD22.close();
	  allvEvIDBD22mu.push_back(vEvIDBD22mu);
	  allvEdepBD22mu.push_back(vEdepBD22mu);

   }  

		
   //-------------------------------------------------------------------
   //                     Bin-by-bin analysis
   //                          Mu-decay
   //-------------------------------------------------------------------     
			
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


} 
 
 int main() {
   thesiseff();
   return 0;
}  
