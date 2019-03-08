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

void gascavCuGlasseff(){

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

   // Names of the files
   // X-ray cascade
   std::string filexSciD1 = "../../simdata/gas/Cu_cav_dB_10mm_dA1_400mm_no_wires_1e5goldcascade_SciD1.txt";
   std::string filexSciD2 = "../../simdata/gas/Cu_cav_dB_10mm_dA1_400mm_no_wires_1e5goldcascade_SciD2.txt";
   std::string filexSciD3 = "../../simdata/gas/Cu_cav_dB_10mm_dA1_400mm_no_wires_1e5goldcascade_SciD3.txt";
   std::string filexBGOD1 = "../../simdata/gas/Cu_cav_dB_10mm_dA1_400mm_no_wires_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD2 = "../../simdata/gas/Cu_cav_dB_10mm_dA1_400mm_no_wires_1e5goldcascade_BGOD2.txt";
   
   // X-ray cascade
   std::string filex2SciD1 = "../../simdata/gas/Glass_cav_dB_10mm_dA1_400mm_no_wires_1e5goldcascade_SciD1.txt";
   std::string filex2SciD2 = "../../simdata/gas/Glass_cav_dB_10mm_dA1_400mm_no_wires_1e5goldcascade_SciD2.txt";
   std::string filex2SciD3 = "../../simdata/gas/Glass_cav_dB_10mm_dA1_400mm_no_wires_1e5goldcascade_SciD3.txt";
   std::string filex2BGOD1 = "../../simdata/gas/Glass_cav_dB_10mm_dA1_400mm_no_wires_1e5goldcascade_BGOD1.txt";
   std::string filex2BGOD2 = "../../simdata/gas/Glass_cav_dB_10mm_dA1_400mm_no_wires_1e5goldcascade_BGOD2.txt";


   // Mu-decay
   std::string filemuSciD1 = "../../simdata/gas/Cu_cav_dB_10mm_dA1_400mm_no_wires_1e5mudecay_SciD1.txt";
   std::string filemuSciD2 = "../../simdata/gas/Cu_cav_dB_10mm_dA1_400mm_no_wires_1e5mudecay_SciD2.txt";
   std::string filemuSciD3 = "../../simdata/gas/Cu_cav_dB_10mm_dA1_400mm_no_wires_1e5mudecay_SciD3.txt";
   std::string filemuBGOD1 = "../../simdata/gas/Cu_cav_dB_10mm_dA1_400mm_no_wires_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD2 = "../../simdata/gas/Cu_cav_dB_10mm_dA1_400mm_no_wires_1e5mudecay_BGOD2.txt";

   std::string filemu2SciD1 = "../../simdata/gas/Glass_cav_dB_10mm_dA1_400mm_no_wires_1e5mudecay_SciD1.txt";
   std::string filemu2SciD2 = "../../simdata/gas/Glass_cav_dB_10mm_dA1_400mm_no_wires_1e5mudecay_SciD2.txt";
   std::string filemu2SciD3 = "../../simdata/gas/Glass_cav_dB_10mm_dA1_400mm_no_wires_1e5mudecay_SciD3.txt";
   std::string filemu2BGOD1 = "../../simdata/gas/Glass_cav_dB_10mm_dA1_400mm_no_wires_1e5mudecay_BGOD1.txt";
   std::string filemu2BGOD2 = "../../simdata/gas/Glass_cav_dB_10mm_dA1_400mm_no_wires_1e5mudecay_BGOD2.txt";



   // Vectors with filenames   
   std::vector<std::string> Xfiles;
   std::vector<std::string> mufiles;

   // X-ray cascade		 
   Xfiles.push_back(filexSciD1);
   Xfiles.push_back(filexSciD2);
   Xfiles.push_back(filexSciD3);
   Xfiles.push_back(filexBGOD1);
   Xfiles.push_back(filexBGOD2);

   Xfiles.push_back(filex2SciD1);
   Xfiles.push_back(filex2SciD2);
   Xfiles.push_back(filex2SciD3);
   Xfiles.push_back(filex2BGOD1);
   Xfiles.push_back(filex2BGOD2);

   // Mu-decay
   mufiles.push_back(filemuSciD1);
   mufiles.push_back(filemuSciD2);
   mufiles.push_back(filemuSciD3);
   mufiles.push_back(filemuBGOD1);
   mufiles.push_back(filemuBGOD2);

   mufiles.push_back(filemu2SciD1);
   mufiles.push_back(filemu2SciD2);
   mufiles.push_back(filemu2SciD3);
   mufiles.push_back(filemu2BGOD1);
   mufiles.push_back(filemu2BGOD2);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep, EventID;
   float iEventID;

   float Ethr1 = 0.001;
   float Ethr21 = 0.5;
   float Ethr22 = 10;
   float Ethr3 = 1;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
		   
   // Storage vectors
   // Normalisation 2 [abs = total] :: X-ray cascade [Cu]
   std::vector< std::vector<double> > PXevector(Xfiles.size()/10,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector(Xfiles.size()/10,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector(Xfiles.size()/10,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector(Xfiles.size()/10,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [glass]
   std::vector< std::vector<double> > PXevector2(Xfiles.size()/10,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2(Xfiles.size()/10,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector2(Xfiles.size()/10,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2(Xfiles.size()/10,std::vector<double>(nsamps));      

   // Normalisation 2 [abs = total] :: Mu-decay [Cu]
   std::vector< std::vector<double> > Peevector(mufiles.size()/10,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector(mufiles.size()/10,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector(mufiles.size()/10,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector(mufiles.size()/10,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [glass]
   std::vector< std::vector<double> > Peevector2(mufiles.size()/10,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2(mufiles.size()/10,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector2(mufiles.size()/10,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2(mufiles.size()/10,std::vector<double>(nsamps));      


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

   std::vector< std::vector< double > > allvEvIDSD1x2;
   std::vector< std::vector< double > > allvEdepSD1x2;
   std::vector< std::vector< double > > allvEvIDSD2x2;
   std::vector< std::vector< double > > allvEdepSD2x2;
   std::vector< std::vector< double > > allvEvIDSD3x2;
   std::vector< std::vector< double > > allvEdepSD3x2;
   std::vector< std::vector< double > > allvEvIDBD1x2;
   std::vector< std::vector< double > > allvEdepBD1x2;
   std::vector< std::vector< double > > allvEvIDBD2x2;
   std::vector< std::vector< double > > allvEdepBD2x2;


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

   std::vector< std::vector< double > > allvEvIDSD1mu2;
   std::vector< std::vector< double > > allvEdepSD1mu2;
   std::vector< std::vector< double > > allvEvIDSD2mu2;
   std::vector< std::vector< double > > allvEdepSD2mu2;
   std::vector< std::vector< double > > allvEvIDSD3mu2;
   std::vector< std::vector< double > > allvEdepSD3mu2;
   std::vector< std::vector< double > > allvEvIDBD1mu2;
   std::vector< std::vector< double > > allvEdepBD1mu2;
   std::vector< std::vector< double > > allvEvIDBD2mu2;
   std::vector< std::vector< double > > allvEdepBD2mu2;



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
			  
      // SciD1
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


	  // SciD2
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


	  // SciD3
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

			  
	  // BGOD1
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


	  // BGOD2
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


      // SciD1
	  std::ifstream x2fSciD1(TString(Xfiles[(k*10)+5]));
	  std::vector<double> vEvIDSD1x2;
	  std::vector<double> vEdepSD1x2;
			  
	  while (!x2fSciD1.eof()) {
	     double EvIDSD1, EdepSD1;
		 x2fSciD1 >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1x2.push_back(EvIDSD1);
		 vEdepSD1x2.push_back(EdepSD1);
	  }
	  vEvIDSD1x2.pop_back(); vEdepSD1x2.pop_back();
	  vEvIDSD1x2.pop_back(); vEdepSD1x2.pop_back();
			  
	  x2fSciD1.close();
	  allvEvIDSD1x2.push_back(vEvIDSD1x2);
	  allvEdepSD1x2.push_back(vEdepSD1x2);


	  // SciD2
	  std::ifstream x2fSciD2(TString(Xfiles[(k*10)+6]));
	  std::vector<double> vEvIDSD2x2;
	  std::vector<double> vEdepSD2x2;
			  
	  while (!x2fSciD2.eof()) {
	     double EvIDSD2, EdepSD2;
		 x2fSciD2 >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2x2.push_back(EvIDSD2);
		 vEdepSD2x2.push_back(EdepSD2);
	  }
	  vEvIDSD2x2.pop_back(); vEdepSD2x2.pop_back();
	  vEvIDSD2x2.pop_back(); vEdepSD2x2.pop_back();
			  
	  x2fSciD2.close();
	  allvEvIDSD2x2.push_back(vEvIDSD2x2);
	  allvEdepSD2x2.push_back(vEdepSD2x2);


	  // SciD3
	  std::ifstream x2fSciD3(TString(Xfiles[(k*10)+7]));
	  std::vector<double> vEvIDSD3x2;
	  std::vector<double> vEdepSD3x2;
			  
	  while (!x2fSciD3.eof()) {
	     double EvIDSD3, EdepSD3;
		 x2fSciD3 >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3x2.push_back(EvIDSD3);
		 vEdepSD3x2.push_back(EdepSD3);
	  }
	  vEvIDSD3x2.pop_back(); vEdepSD3x2.pop_back();
	  vEvIDSD3x2.pop_back(); vEdepSD3x2.pop_back();
			  
	  x2fSciD3.close();
	  allvEvIDSD3x2.push_back(vEvIDSD3x2);
	  allvEdepSD3x2.push_back(vEdepSD3x2);
			  

	  // BGOD1
	  std::ifstream x2fBGOD1(TString(Xfiles[(k*10)+8]));
	  std::vector<double> vEvIDBD1x2;
	  std::vector<double> vEdepBD1x2;
			  
	  while (!x2fBGOD1.eof()) {
	     double EvIDBD1, EdepBD1;
		 x2fBGOD1 >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1x2.push_back(EvIDBD1);
		 vEdepBD1x2.push_back(EdepBD1);
	  }
	  vEvIDBD1x2.pop_back(); vEdepBD1x2.pop_back();
	  vEvIDBD1x2.pop_back(); vEdepBD1x2.pop_back();
			  
	  x2fBGOD1.close();
	  allvEvIDBD1x2.push_back(vEvIDBD1x2);
	  allvEdepBD1x2.push_back(vEdepBD1x2);


	  // BGOD2
	  std::ifstream x2fBGOD2(TString(Xfiles[(k*10)+9]));
	  std::vector<double> vEvIDBD2x2;
	  std::vector<double> vEdepBD2x2;
			  
	  while (!x2fBGOD2.eof()) {
	     double EvIDBD2, EdepBD2;
		 x2fBGOD2 >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2x2.push_back(EvIDBD2);
		 vEdepBD2x2.push_back(EdepBD2);
	  }
	  vEvIDBD2x2.pop_back(); vEdepBD2x2.pop_back();
	  vEvIDBD2x2.pop_back(); vEdepBD2x2.pop_back();
			  
	  x2fBGOD2.close();
	  allvEvIDBD2x2.push_back(vEvIDBD2x2);
	  allvEdepBD2x2.push_back(vEdepBD2x2);


   }



   for (int k=0; k<((mufiles.size())/10); k++) {
   
      // SciD1mu
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


	  // SciD2mu
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


	  // SciD3mu
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
			 

	  // BGOD1mu
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


	  // BGOD2mu
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


      // SciD1mu2
	  std::ifstream mu2fSciD1(TString(mufiles[(k*10)+5]));
	  std::vector<double> vEvIDSD1mu2;
	  std::vector<double> vEdepSD1mu2;
			  
	  while (!mu2fSciD1.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mu2fSciD1 >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1mu2.push_back(EvIDSD1mu);
		 vEdepSD1mu2.push_back(EdepSD1mu);
	  }
	  vEvIDSD1mu2.pop_back(); vEdepSD1mu2.pop_back();
	  vEvIDSD1mu2.pop_back(); vEdepSD1mu2.pop_back();
			  
	  mu2fSciD1.close();
	  allvEvIDSD1mu2.push_back(vEvIDSD1mu2);
	  allvEdepSD1mu2.push_back(vEdepSD1mu2);


	  // SciD2mu
	  std::ifstream mu2fSciD2(TString(mufiles[(k*10)+6]));
	  std::vector<double> vEvIDSD2mu2;
	  std::vector<double> vEdepSD2mu2;
			  
	  while (!mu2fSciD2.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mu2fSciD2 >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2mu2.push_back(EvIDSD2mu);
		 vEdepSD2mu2.push_back(EdepSD2mu);
	  }
	  vEvIDSD2mu2.pop_back(); vEdepSD2mu2.pop_back();
	  vEvIDSD2mu2.pop_back(); vEdepSD2mu2.pop_back();
			  
	  mu2fSciD2.close();
	  allvEvIDSD2mu2.push_back(vEvIDSD2mu2);
	  allvEdepSD2mu2.push_back(vEdepSD2mu2);


	  // SciD3mu
	  std::ifstream mu2fSciD3(TString(mufiles[(k*10)+7]));
	  std::vector<double> vEvIDSD3mu2;
	  std::vector<double> vEdepSD3mu2;
			  
	  while (!mu2fSciD3.eof()) {
	     double EvIDSD3mu, EdepSD3mu;
		 mu2fSciD3 >> EvIDSD3mu >> EdepSD3mu;
		 vEvIDSD3mu2.push_back(EvIDSD3mu);
		 vEdepSD3mu2.push_back(EdepSD3mu);
	  }
	  vEvIDSD3mu2.pop_back(); vEdepSD3mu2.pop_back();
	  vEvIDSD3mu2.pop_back(); vEdepSD3mu2.pop_back();
			  
	  mu2fSciD3.close();
	  allvEvIDSD3mu2.push_back(vEvIDSD3mu2);
	  allvEdepSD3mu2.push_back(vEdepSD3mu2);
			  

	  // BGOD1mu
	  std::ifstream mu2fBGOD1(TString(mufiles[(k*10)+8]));
	  std::vector<double> vEvIDBD1mu2;
	  std::vector<double> vEdepBD1mu2;
			  
	  while (!mu2fBGOD1.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mu2fBGOD1 >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1mu2.push_back(EvIDBD1mu);
		 vEdepBD1mu2.push_back(EdepBD1mu);
	  }
	  vEvIDBD1mu2.pop_back(); vEdepBD1mu2.pop_back();
	  vEvIDBD1mu2.pop_back(); vEdepBD1mu2.pop_back();
			  
	  mu2fBGOD1.close();
	  allvEvIDBD1mu2.push_back(vEvIDBD1mu2);
	  allvEdepBD1mu2.push_back(vEdepBD1mu2);


	  // BGOD2mu
	  std::ifstream mu2fBGOD2(TString(mufiles[(k*10)+9]));
	  std::vector<double> vEvIDBD2mu2;
	  std::vector<double> vEdepBD2mu2;
			  
	  while (!mu2fBGOD2.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mu2fBGOD2 >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2mu2.push_back(EvIDBD2mu);
		 vEdepBD2mu2.push_back(EdepBD2mu);
	  }
	  vEvIDBD2mu2.pop_back(); vEdepBD2mu2.pop_back();
	  vEvIDBD2mu2.pop_back(); vEdepBD2mu2.pop_back();
			  
	  mu2fBGOD2.close();
	  allvEvIDBD2mu2.push_back(vEvIDBD2mu2);
	  allvEdepBD2mu2.push_back(vEdepBD2mu2);


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
		 // Normalisation 2 [absolute] :: cascade Cu
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
		 // Normalisation 2 [absolute] :: cascade Glass
		 //-------------------------------------------------- 
		 XXray2 = 0; Xelec2 = 0;
			  
		 for (int a=0; a<allvEvIDBD1x2[0].size(); a++) {

		    if ((allvEdepSD1x2[i][a] < Ethr1) && (allvEdepSD2x2[i][a] < Ethr1) && (allvEdepSD3x2[i][a] < Ethr1)) {
			   if (((allvEdepBD1x2[i][a] > Ethr) && (allvEdepBD1x2[i][a] < Ethr22)) || ((allvEdepBD2x2[i][a] > Ethr) && (allvEdepBD2x2[i][a] < Ethr22))) {
				  XXray2 += 1;
			   } else { Xelec2 += 1; }
		    } else { Xelec2 += 1; }
		 }
				 
		 PXXvector2[i][m] = XXray2/(double)(counterXX);
		 PXevector2[i][m] = Xelec2/(double)(counterXX); 


		 //--------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Cu
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


		 //--------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Glass
		 //-------------------------------------------------- 
		 eXray2 = 0; eelec2 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu2[0].size(); a++) {

		    if ((allvEdepSD1mu2[i][a] < Ethr1) && (allvEdepSD2mu2[i][a] < Ethr1) && (allvEdepSD3mu2[i][a] < Ethr1)) {
		       if (((allvEdepBD1mu2[i][a] > Ethr) && (allvEdepBD1mu2[i][a] < Ethr22)) || ((allvEdepBD2mu2[i][a] > Ethr) && (allvEdepBD2mu2[i][a] < Ethr22))) { 
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
   f->Divide(2,2);
   f->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   //gPad->SetFixedAspectRatio();
   TGraph *grPXX = new TGraph(nsamps,Ethrmu,PXXarr);
   grPXX->SetTitle("E_{THR1} = 0.001 MeV"); 
   grPXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXX->GetXaxis()->SetRangeUser(0,2.04);
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
   grPeX->SetTitle("black - copper, red - glass, no wires");
   grPeX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeX->GetXaxis()->SetRangeUser(0,2.04);
   grPeX->GetXaxis()->SetNdivisions(-314);
   TGaxis::SetMaxDigits(2);
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
   grPeXXX->GetXaxis()->SetRangeUser(0,2.04);
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

   f->SaveAs("Cu_glass_Sci_no_wires.pdf");
   f->SaveAs("Cu_glass_Sci_no_wires.png");
   f->SaveAs("Cu_glass_Sci_no_wires.C");


 
} 
 
 int main() {
   gascavCuGlasseff();
   return 0;
}  
