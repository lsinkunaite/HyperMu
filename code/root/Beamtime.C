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

void Beamtime(){

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
   std::string path = "../../simdata/beamtime/";
   std::string cavmaterial = "No";
   
   // Names of the files
   // X-ray cascade
   std::string filexSciD1b = path+cavmaterial+"_cav_black_BGOwide_1e5goldcascade_SciD1.txt";
   std::string filexSciD2b = path+cavmaterial+"_cav_black_BGOwide_1e5goldcascade_SciD2.txt";
   std::string filexBGOD1b = path+cavmaterial+"_cav_black_BGOwide_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD2b = path+cavmaterial+"_cav_black_BGOwide_1e5goldcascade_BGOD2.txt";
   std::string filexSciD1p = path+cavmaterial+"_cav_pink_BGOwide_1e5goldcascade_SciD1.txt";
   std::string filexSciD2p = path+cavmaterial+"_cav_pink_BGOwide_1e5goldcascade_SciD2.txt";
   std::string filexBGOD1p = path+cavmaterial+"_cav_pink_BGOwide_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD2p = path+cavmaterial+"_cav_pink_BGOwide_1e5goldcascade_BGOD2.txt";

   // Mu-decay
   std::string filemuSciD1b = path+cavmaterial+"_cav_black_BGOwide_1e5mudecay_SciD1.txt";
   std::string filemuSciD2b = path+cavmaterial+"_cav_black_BGOwide_1e5mudecay_SciD2.txt";
   std::string filemuBGOD1b = path+cavmaterial+"_cav_black_BGOwide_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD2b = path+cavmaterial+"_cav_black_BGOwide_1e5mudecay_BGOD2.txt";
   std::string filemuSciD1p = path+cavmaterial+"_cav_pink_BGOwide_1e5mudecay_SciD1.txt";
   std::string filemuSciD2p = path+cavmaterial+"_cav_pink_BGOwide_1e5mudecay_SciD2.txt";
   std::string filemuBGOD1p = path+cavmaterial+"_cav_pink_BGOwide_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD2p = path+cavmaterial+"_cav_pink_BGOwide_1e5mudecay_BGOD2.txt";


   // Vectors with filenames   
   std::vector<std::string> Xfiles;
   std::vector<std::string> mufiles;

   // X-ray cascade		 
   Xfiles.push_back(filexSciD1b);
   Xfiles.push_back(filexSciD2b);
   Xfiles.push_back(filexBGOD1b);
   Xfiles.push_back(filexBGOD2b);
   Xfiles.push_back(filexSciD1p);
   Xfiles.push_back(filexSciD2p);
   Xfiles.push_back(filexBGOD1p);
   Xfiles.push_back(filexBGOD2p);

   // Mu-decay
   mufiles.push_back(filemuSciD1b);
   mufiles.push_back(filemuSciD2b);
   mufiles.push_back(filemuBGOD1b);
   mufiles.push_back(filemuBGOD2b);
   mufiles.push_back(filemuSciD1p);
   mufiles.push_back(filemuSciD2p);
   mufiles.push_back(filemuBGOD1p);
   mufiles.push_back(filemuBGOD2p);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep, EventID;
   float iEventID;

   float Ethr1 = 0.7;
   float Ethr21 = 0.5;
   float Ethr22 = 6.5;
   float Ethr3 = 1;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
		   
   // Storage vectors
   // Normalisation 2 [abs = total] :: X-ray cascade [Cu]
   std::vector< std::vector<double> > PXevectorb(Xfiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorb(Xfiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXevectorp(Xfiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorp(Xfiles.size()/4,std::vector<double>(nsamps));          

   // Normalisation 2 [abs = total] :: Mu-decay [Cu]
   std::vector< std::vector<double> > Peevectorb(mufiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorb(mufiles.size()/4,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevectorp(mufiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorp(mufiles.size()/4,std::vector<double>(nsamps));      


   // X-ray cascade
   std::vector< std::vector< double > > allvEvIDSD1bx;
   std::vector< std::vector< double > > allvEdepSD1bx;
   std::vector< std::vector< double > > allvEvIDSD2bx;
   std::vector< std::vector< double > > allvEdepSD2bx;
   std::vector< std::vector< double > > allvEvIDBD1bx;
   std::vector< std::vector< double > > allvEdepBD1bx;
   std::vector< std::vector< double > > allvEvIDBD2bx;
   std::vector< std::vector< double > > allvEdepBD2bx;

   std::vector< std::vector< double > > allvEvIDSD1px;
   std::vector< std::vector< double > > allvEdepSD1px;
   std::vector< std::vector< double > > allvEvIDSD2px;
   std::vector< std::vector< double > > allvEdepSD2px;
   std::vector< std::vector< double > > allvEvIDBD1px;
   std::vector< std::vector< double > > allvEdepBD1px;
   std::vector< std::vector< double > > allvEvIDBD2px;
   std::vector< std::vector< double > > allvEdepBD2px;

   // Mu-decay
   std::vector< std::vector< double > > allvEvIDSD1bmu;
   std::vector< std::vector< double > > allvEdepSD1bmu;
   std::vector< std::vector< double > > allvEvIDSD2bmu;
   std::vector< std::vector< double > > allvEdepSD2bmu;
   std::vector< std::vector< double > > allvEvIDBD1bmu;
   std::vector< std::vector< double > > allvEdepBD1bmu;
   std::vector< std::vector< double > > allvEvIDBD2bmu;
   std::vector< std::vector< double > > allvEdepBD2bmu;

   std::vector< std::vector< double > > allvEvIDSD1pmu;
   std::vector< std::vector< double > > allvEdepSD1pmu;
   std::vector< std::vector< double > > allvEvIDSD2pmu;
   std::vector< std::vector< double > > allvEdepSD2pmu;
   std::vector< std::vector< double > > allvEvIDBD1pmu;
   std::vector< std::vector< double > > allvEdepBD1pmu;
   std::vector< std::vector< double > > allvEvIDBD2pmu;
   std::vector< std::vector< double > > allvEdepBD2pmu;


   float Ethr;
   int counterXX = 1e5;
   int counteree = 1e5;
   int XXrayb = 0; // X-rays i-fied as X-rays
   int Xelecb = 0; // X-rays i-fied as electrons
   int XXrayp = 0;
   int Xelecp = 0;
   int eXrayb = 0; // Electrons i-fied as X-rays
   int eelecb = 0; // Electrons i-fied as electrons
   int eXrayp = 0;
   int eelecp = 0;
   	   
   Ethrmu[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;


   //-------------------------------------------------------------------
   //                           Reading
   //-------------------------------------------------------------------
		   
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m------------------- X-ray cascade ------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


   for (int k=0; k<1; k++) {
			  
      // SciD1 - black
	  std::ifstream xfSciD1b(TString(Xfiles[k*8]));
	  std::vector<double> vEvIDSD1bx;
	  std::vector<double> vEdepSD1bx;
			  
	  while (!xfSciD1b.eof()) {
	     double EvIDSD1, EdepSD1;
		 xfSciD1b >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1bx.push_back(EvIDSD1);
		 vEdepSD1bx.push_back(EdepSD1);
	  }
	  vEvIDSD1bx.pop_back(); vEdepSD1bx.pop_back();
	  vEvIDSD1bx.pop_back(); vEdepSD1bx.pop_back();
			  
	  xfSciD1b.close();
	  allvEvIDSD1bx.push_back(vEvIDSD1bx);
	  allvEdepSD1bx.push_back(vEdepSD1bx);


	  // SciD2 - black
	  std::ifstream xfSciD2b(TString(Xfiles[(k*8)+1]));
	  std::vector<double> vEvIDSD2bx;
	  std::vector<double> vEdepSD2bx;
			  
	  while (!xfSciD2b.eof()) {
	     double EvIDSD2, EdepSD2;
		 xfSciD2b >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2bx.push_back(EvIDSD2);
		 vEdepSD2bx.push_back(EdepSD2);
	  }
	  vEvIDSD2bx.pop_back(); vEdepSD2bx.pop_back();
	  vEvIDSD2bx.pop_back(); vEdepSD2bx.pop_back();
			  
	  xfSciD2b.close();
	  allvEvIDSD2bx.push_back(vEvIDSD2bx);
	  allvEdepSD2bx.push_back(vEdepSD2bx);

			  
	  // BGOD1 - black
	  std::ifstream xfBGOD1b(TString(Xfiles[(k*8)+2]));
	  std::vector<double> vEvIDBD1bx;
	  std::vector<double> vEdepBD1bx;
			  
	  while (!xfBGOD1b.eof()) {
	     double EvIDBD1, EdepBD1;
		 xfBGOD1b >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1bx.push_back(EvIDBD1);
		 vEdepBD1bx.push_back(EdepBD1);
	  }
	  vEvIDBD1bx.pop_back(); vEdepBD1bx.pop_back();
	  vEvIDBD1bx.pop_back(); vEdepBD1bx.pop_back();
			  
	  xfBGOD1b.close();
	  allvEvIDBD1bx.push_back(vEvIDBD1bx);
	  allvEdepBD1bx.push_back(vEdepBD1bx);


	  // BGOD2 - black
	  std::ifstream xfBGOD2b(TString(Xfiles[(k*8)+3]));
	  std::vector<double> vEvIDBD2bx;
	  std::vector<double> vEdepBD2bx;
			  
	  while (!xfBGOD2b.eof()) {
	     double EvIDBD2, EdepBD2;
		 xfBGOD2b >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2bx.push_back(EvIDBD2);
		 vEdepBD2bx.push_back(EdepBD2);
	  }
	  vEvIDBD2bx.pop_back(); vEdepBD2bx.pop_back();
	  vEvIDBD2bx.pop_back(); vEdepBD2bx.pop_back();
			  
	  xfBGOD2b.close();
	  allvEvIDBD2bx.push_back(vEvIDBD2bx);
	  allvEdepBD2bx.push_back(vEdepBD2bx);


      // SciD1 - pink
	  std::ifstream xfSciD1p(TString(Xfiles[(k*8)+4]));
	  std::vector<double> vEvIDSD1px;
	  std::vector<double> vEdepSD1px;
			  
	  while (!xfSciD1p.eof()) {
	     double EvIDSD1, EdepSD1;
		 xfSciD1p >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1px.push_back(EvIDSD1);
		 vEdepSD1px.push_back(EdepSD1);
	  }
	  vEvIDSD1px.pop_back(); vEdepSD1px.pop_back();
	  vEvIDSD1px.pop_back(); vEdepSD1px.pop_back();
			  
	  xfSciD1p.close();
	  allvEvIDSD1px.push_back(vEvIDSD1px);
	  allvEdepSD1px.push_back(vEdepSD1px);


	  // SciD2 - pink
	  std::ifstream xfSciD2p(TString(Xfiles[(k*8)+5]));
	  std::vector<double> vEvIDSD2px;
	  std::vector<double> vEdepSD2px;
			  
	  while (!xfSciD2p.eof()) {
	     double EvIDSD2, EdepSD2;
		 xfSciD2p >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2px.push_back(EvIDSD2);
		 vEdepSD2px.push_back(EdepSD2);
	  }
	  vEvIDSD2px.pop_back(); vEdepSD2px.pop_back();
	  vEvIDSD2px.pop_back(); vEdepSD2px.pop_back();
			  
	  xfSciD2p.close();
	  allvEvIDSD2px.push_back(vEvIDSD2px);
	  allvEdepSD2px.push_back(vEdepSD2px);

			  
	  // BGOD1 - pink
	  std::ifstream xfBGOD1p(TString(Xfiles[(k*8)+6]));
	  std::vector<double> vEvIDBD1px;
	  std::vector<double> vEdepBD1px;
			  
	  while (!xfBGOD1p.eof()) {
	     double EvIDBD1, EdepBD1;
		 xfBGOD1p >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1px.push_back(EvIDBD1);
		 vEdepBD1px.push_back(EdepBD1);
	  }
	  vEvIDBD1px.pop_back(); vEdepBD1px.pop_back();
	  vEvIDBD1px.pop_back(); vEdepBD1px.pop_back();
			  
	  xfBGOD1p.close();
	  allvEvIDBD1px.push_back(vEvIDBD1px);
	  allvEdepBD1px.push_back(vEdepBD1px);


	  // BGOD2 - pink
	  std::ifstream xfBGOD2p(TString(Xfiles[(k*8)+7]));
	  std::vector<double> vEvIDBD2px;
	  std::vector<double> vEdepBD2px;
			  
	  while (!xfBGOD2p.eof()) {
	     double EvIDBD2, EdepBD2;
		 xfBGOD2p >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2px.push_back(EvIDBD2);
		 vEdepBD2px.push_back(EdepBD2);
	  }
	  vEvIDBD2px.pop_back(); vEdepBD2px.pop_back();
	  vEvIDBD2px.pop_back(); vEdepBD2px.pop_back();
			  
	  xfBGOD2p.close();
	  allvEvIDBD2px.push_back(vEvIDBD2px);
	  allvEdepBD2px.push_back(vEdepBD2px);


   }


   for (int k=0; k<1; k++) {
   
      // SciD1mu - black
	  std::ifstream mufSciD1b(TString(mufiles[k*8]));
	  std::vector<double> vEvIDSD1bmu;
	  std::vector<double> vEdepSD1bmu;
			  
	  while (!mufSciD1b.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mufSciD1b >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1bmu.push_back(EvIDSD1mu);
		 vEdepSD1bmu.push_back(EdepSD1mu);
	  }
	  vEvIDSD1bmu.pop_back(); vEdepSD1bmu.pop_back();
	  vEvIDSD1bmu.pop_back(); vEdepSD1bmu.pop_back();
			  
	  mufSciD1b.close();
	  allvEvIDSD1bmu.push_back(vEvIDSD1bmu);
	  allvEdepSD1bmu.push_back(vEdepSD1bmu);


	  // SciD2mu - black
	  std::ifstream mufSciD2b(TString(mufiles[(k*8)+1]));
	  std::vector<double> vEvIDSD2bmu;
	  std::vector<double> vEdepSD2bmu;
			  
	  while (!mufSciD2b.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mufSciD2b >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2bmu.push_back(EvIDSD2mu);
		 vEdepSD2bmu.push_back(EdepSD2mu);
	  }
	  vEvIDSD2bmu.pop_back(); vEdepSD2bmu.pop_back();
	  vEvIDSD2bmu.pop_back(); vEdepSD2bmu.pop_back();
			  
	  mufSciD2b.close();
	  allvEvIDSD2bmu.push_back(vEvIDSD2bmu);
	  allvEdepSD2bmu.push_back(vEdepSD2bmu);


	  // BGOD1mu - black
	  std::ifstream mufBGOD1b(TString(mufiles[(k*8)+2]));
	  std::vector<double> vEvIDBD1bmu;
	  std::vector<double> vEdepBD1bmu;
			  
	  while (!mufBGOD1b.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mufBGOD1b >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1bmu.push_back(EvIDBD1mu);
		 vEdepBD1bmu.push_back(EdepBD1mu);
	  }
	  vEvIDBD1bmu.pop_back(); vEdepBD1bmu.pop_back();
	  vEvIDBD1bmu.pop_back(); vEdepBD1bmu.pop_back();
			  
	  mufBGOD1b.close();
	  allvEvIDBD1bmu.push_back(vEvIDBD1bmu);
	  allvEdepBD1bmu.push_back(vEdepBD1bmu);


	  // BGOD2mu - black
	  std::ifstream mufBGOD2b(TString(mufiles[(k*8)+3]));
	  std::vector<double> vEvIDBD2bmu;
	  std::vector<double> vEdepBD2bmu;
			  
	  while (!mufBGOD2b.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mufBGOD2b >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2bmu.push_back(EvIDBD2mu);
		 vEdepBD2bmu.push_back(EdepBD2mu);
	  }
	  vEvIDBD2bmu.pop_back(); vEdepBD2bmu.pop_back();
	  vEvIDBD2bmu.pop_back(); vEdepBD2bmu.pop_back();
			  
	  mufBGOD2b.close();
	  allvEvIDBD2bmu.push_back(vEvIDBD2bmu);
	  allvEdepBD2bmu.push_back(vEdepBD2bmu);


      // SciD1mu - pink
	  std::ifstream mufSciD1p(TString(mufiles[(k*8)+4]));
	  std::vector<double> vEvIDSD1pmu;
	  std::vector<double> vEdepSD1pmu;
			  
	  while (!mufSciD1p.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mufSciD1p >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1pmu.push_back(EvIDSD1mu);
		 vEdepSD1pmu.push_back(EdepSD1mu);
	  }
	  vEvIDSD1pmu.pop_back(); vEdepSD1pmu.pop_back();
	  vEvIDSD1pmu.pop_back(); vEdepSD1pmu.pop_back();
			  
	  mufSciD1p.close();
	  allvEvIDSD1pmu.push_back(vEvIDSD1pmu);
	  allvEdepSD1pmu.push_back(vEdepSD1pmu);


	  // SciD2mu - pink
	  std::ifstream mufSciD2p(TString(mufiles[(k*8)+5]));
	  std::vector<double> vEvIDSD2pmu;
	  std::vector<double> vEdepSD2pmu;
			  
	  while (!mufSciD2p.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mufSciD2p >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2pmu.push_back(EvIDSD2mu);
		 vEdepSD2pmu.push_back(EdepSD2mu);
	  }
	  vEvIDSD2pmu.pop_back(); vEdepSD2pmu.pop_back();
	  vEvIDSD2pmu.pop_back(); vEdepSD2pmu.pop_back();
			  
	  mufSciD2p.close();
	  allvEvIDSD2pmu.push_back(vEvIDSD2pmu);
	  allvEdepSD2pmu.push_back(vEdepSD2pmu);


	  // BGOD1mu - pink
	  std::ifstream mufBGOD1p(TString(mufiles[(k*8)+6]));
	  std::vector<double> vEvIDBD1pmu;
	  std::vector<double> vEdepBD1pmu;
			  
	  while (!mufBGOD1p.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mufBGOD1p >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1pmu.push_back(EvIDBD1mu);
		 vEdepBD1pmu.push_back(EdepBD1mu);
	  }
	  vEvIDBD1pmu.pop_back(); vEdepBD1pmu.pop_back();
	  vEvIDBD1pmu.pop_back(); vEdepBD1pmu.pop_back();
			  
	  mufBGOD1p.close();
	  allvEvIDBD1pmu.push_back(vEvIDBD1pmu);
	  allvEdepBD1pmu.push_back(vEdepBD1pmu);


	  // BGOD2mu - pink
	  std::ifstream mufBGOD2p(TString(mufiles[(k*8)+7]));
	  std::vector<double> vEvIDBD2pmu;
	  std::vector<double> vEdepBD2pmu;
			  
	  while (!mufBGOD2p.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mufBGOD2p >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2pmu.push_back(EvIDBD2mu);
		 vEdepBD2pmu.push_back(EdepBD2mu);
	  }
	  vEvIDBD2pmu.pop_back(); vEdepBD2pmu.pop_back();
	  vEvIDBD2pmu.pop_back(); vEdepBD2pmu.pop_back();
			  
	  mufBGOD2p.close();
	  allvEvIDBD2pmu.push_back(vEvIDBD2pmu);
	  allvEdepBD2pmu.push_back(vEdepBD2pmu);


   }  

		
   //-------------------------------------------------------------------
   //                     Bin-by-bin analysis
   //                          Mu-decay
   //-------------------------------------------------------------------     
			
   // X-ray cascade	  
   std::cout << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m-------------------- Analysis Loop  " << 1 << " --------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m--------------------- X-ray cascade ----------------------\033[0m" << std::endl;
   std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

   for (int m=0; m<nsamps; m++) {

      Ethr = Ethrmu[m];

	  //--------------------------------------------------
      // X-ray cascade: black case
	  //-------------------------------------------------- 
	  XXrayb = 0; Xelecb = 0;

			  
	  for (int a=0; a<allvEvIDBD1bx[0].size(); a++) {

         if ((allvEdepSD1bx[0][a] < Ethr1) && (allvEdepSD2bx[0][a] < Ethr1)) {
		    if (((allvEdepBD1bx[0][a] > Ethr) && (allvEdepBD1bx[0][a] < Ethr22)) || ((allvEdepBD2bx[0][a] > Ethr) && (allvEdepBD2bx[0][a] < Ethr22))) {
               XXrayb += 1;
			} else { Xelecb += 1; }
		 } else { Xelecb += 1; }
      }
				 
      PXXvectorb[0][m] = XXrayb/(double)(counterXX);
      PXevectorb[0][m] = Xelecb/(double)(counterXX); 


      //--------------------------------------------------
      // X-ray cascade: pink case
      //-------------------------------------------------- 
      XXrayp = 0; Xelecp = 0;
			  
      for (int a=0; a<allvEvIDBD1px[0].size(); a++) {

         if ((allvEdepSD1px[0][a] < Ethr1) && (allvEdepSD2px[0][a] < Ethr1)) {
            if (((allvEdepBD1px[0][a] > Ethr) && (allvEdepBD1px[0][a] < Ethr22)) || ((allvEdepBD2px[0][a] > Ethr) && (allvEdepBD2px[0][a] < Ethr22))) {
               XXrayp += 1;
            } else { Xelecp += 1; }
         } else { Xelecp += 1; }
      }
				 
      PXXvectorp[0][m] = XXrayp/(double)(counterXX);
      PXevectorp[0][m] = Xelecp/(double)(counterXX); 


      //--------------------------------------------------
      // Mu-decay: black case
      //-------------------------------------------------- 
      eXrayb = 0; eelecb = 0;
			  
      for (int a=0; a<allvEvIDBD1bmu[0].size(); a++) {

         if ((allvEdepSD1bmu[0][a] < Ethr1) && (allvEdepSD2bmu[0][a] < Ethr1)) {
            if (((allvEdepBD1bmu[0][a] > Ethr) && (allvEdepBD1bmu[0][a] < Ethr22))) || ((allvEdepBD2bmu[0][a] > Ethr) && (allvEdepBD2bmu[0][a] < Ethr22))) {
               eXrayb += 1;
            } else { eelecb += 1; }
         } else { eelecb += 1; }
      }
				 
      PeXvectorb[0][m] = eXrayb/(double)(counteree);
      Peevectorb[0][m] = eelecb/(double)(counteree); 


      //--------------------------------------------------
      // Mu-decay: pink case
      //-------------------------------------------------- 
      eXrayp = 0; eelecp = 0;
			  
      for (int a=0; a<allvEvIDBD1pmu[0].size(); a++) {

         if ((allvEdepSD1pmu[0][a] < Ethr1) && (allvEdepSD2pmu[0][a] < Ethr1)) {
            if (((allvEdepBD1pmu[0][a] > Ethr) && (allvEdepBD1pmu[0][a] < Ethr22))) || ((allvEdepBD2pmu[0][a] > Ethr) && (allvEdepBD2pmu[0][a] < Ethr22))) {
               eXrayp += 1;
            } else { eelecp += 1; }
		 } else { eelecp += 1; }
      }
				 
      PeXvectorp[0][m] = eXrayp/(double)(counteree);
      Peevectorp[0][m] = eelecp/(double)(counteree); 
	  
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
   float PXXarrb[nsamps] = {}; // X-ray cascade
   float PXXarrp[nsamps] = {};
   float PeXarrb[nsamps] = {};
   float PeXarrp[nsamps] = {};
   float PeXXXarrb[nsamps] = {};
   float PeXXXarrp[nsamps] = {};
   float SNRarrb[nsamps] = {};
   float SNRarrp[nsamps] = {};
 		 	   
   for (int i=0; i<nsamps; i++) {
      // Normalisation 2 [absolute]
	  PXXarrb[i] = PXXvectorb[0][i];
	  PXXarrp[i] = PXXvectorp[0][i];
	  PeXarrb[i] = PeXvectorb[0][i];
	  PeXarrp[i] = PeXvectorp[0][i];
	  PeXXXarrb[i] = (PeXvectorb[0][i])/(double)(PXXvectorb[0][i]);
	  PeXXXarrp[i] = (PeXvectorp[0][i])/(double)(PXXvectorp[0][i]);
	  SNRarrb[i] = (PXXvectorb[0][i])/(double)(sqrt(PeXvectorb[0][i]));
	  SNRarrp[i] = (PXXvectorp[0][i])/(double)(sqrt(PeXvectorp[0][i]));
   }	   

		  
   TCanvas *f = new TCanvas("f","E_{THR}",800,600);
   f->Divide(4,1);
   f->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   //gPad->SetFixedAspectRatio();
   TGraph *grPXXb = new TGraph(nsamps,Ethrmu,PXXarrb);
   grPXXb->SetTitle(""); 
   grPXXb->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXXb->GetXaxis()->SetRangeUser(0,2.03);
   grPXXb->GetXaxis()->SetNdivisions(-304);
   TGaxis::SetMaxDigits(2);
   grPXXb->GetYaxis()->SetMoreLogLabels(1);
   grPXXb->GetYaxis()->SetTitle("P_{XX}");
   grPXXb->GetYaxis()->SetTitleOffset(2.1);
   grPXXb->SetLineColor(kBlue);
   grPXXb->SetLineWidth(3);
   grPXXb->Draw("ALP");
   TGraph *grPXXp = new TGraph(nsamps,Ethrmu,PXXarrp);
   grPXXp->SetLineColor(kRed);
   grPXXp->SetLineWidth(3);
   grPXXp->Draw("LP");
   
   f->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeXb = new TGraph(nsamps,Ethrmu,PeXarrb);
   grPeXb->SetTitle("");
   grPeXb->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeXb->GetXaxis()->SetRangeUser(0,2.04);
   grPeXb->GetXaxis()->SetNdivisions(-304);
   TGaxis::SetMaxDigits(2);
   grPeXb->GetYaxis()->SetMoreLogLabels(1);
   grPeXb->GetYaxis()->SetTitle("P_{eX}");
   grPeXb->GetYaxis()->SetTitleOffset(2.1);
   grPeXb->SetLineColor(kBlue);
   grPeXb->SetLineWidth(3);
   grPeXb->Draw("ALP");
   TGraph *grPeXp = new TGraph(nsamps,Ethrmu,PeXarrp);
   grPeXp->SetLineColor(kRed);
   grPeXp->SetLineWidth(3);
   grPeXp->Draw("LP");

   f->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeXXXb = new TGraph(nsamps,Ethrmu,PeXXXarrb);
   grPeXXXb->SetTitle("");
   grPeXXXb->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeXXXb->GetXaxis()->SetRangeUser(0,2.04);
   grPeXXXb->GetXaxis()->SetNdivisions(-304);
   TGaxis::SetMaxDigits(3);
   grPeXXXb->GetYaxis()->SetMoreLogLabels(1);
   grPeXXXb->GetYaxis()->SetTitle("#frac{P_{eX}}{P_{XX}}");
   grPeXXXb->GetYaxis()->SetTitleOffset(2.1);
   grPeXXXb->SetLineColor(kBlue);
   grPeXXXb->SetLineWidth(3);
   grPeXXXb->Draw("ALP");
   TGraph *grPeXXXp = new TGraph(nsamps,Ethrmu,PeXXXarrp);
   grPeXXXp->SetLineColor(kRed);
   grPeXXXp->SetLineWidth(3);
   grPeXXXp->Draw("LP");

   f->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grSNRb = new TGraph(nsamps,Ethrmu,SNRarrb);
   grSNRb->SetTitle("");
   grSNRb->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grSNRb->GetXaxis()->SetRangeUser(0,2.04);
   grSNRb->GetXaxis()->SetNdivisions(-304);
   TGaxis::SetMaxDigits(3);
   grSNRb->GetYaxis()->SetMoreLogLabels(1);
   grSNRb->GetYaxis()->SetTitle("#frac{P_{XX}}{#sqrt{P_{eX}}}");
   grSNRb->GetYaxis()->SetTitleOffset(2.1);
   grSNRb->SetLineColor(kBlue);
   grSNRb->SetLineWidth(3);
   grSNRb->Draw("ALP");
   TGraph *grSNRp = new TGraph(nsamps,Ethrmu,SNRarrp);
   grSNRp->SetLineColor(kRed);
   grSNRp->SetLineWidth(3);
   grSNRp->Draw("LP");
   f->SaveAs(TString(cavmaterial)+"_cav_BGOwide_beamtime.pdf");
   f->SaveAs(TString(cavmaterial)+"_cav_BGOwide_beamtime.png");
   f->SaveAs(TString(cavmaterial)+"_cav_BGOwide_beamtime.C");

} 
 
 int main() {
   Beamtime();
   return 0;
}  
