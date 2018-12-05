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

void finalsquareMULTIeff(){

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

   const int nsamps = 101;

   // Names of the files
   // X-ray cascade with NaI
   std::string filexSciD1NaI = "../../simdata/final/square_both_sides_NaI_1e5goldcascade_SciD1.txt";
   std::string filexSciD2NaI = "../../simdata/final/square_both_sides_NaI_1e5goldcascade_SciD2.txt";
   std::string filexSciD3NaI = "../../simdata/final/square_both_sides_NaI_1e5goldcascade_SciD3.txt";
   std::string filexSciDT1NaI = "../../simdata/final/square_both_sides_NaI_1e5goldcascade_SciDT1.txt";
   std::string filexSciDB1NaI = "../../simdata/final/square_both_sides_NaI_1e5goldcascade_SciDB1.txt";
   std::string filexSciDL1NaI = "../../simdata/final/square_both_sides_NaI_1e5goldcascade_SciDL1.txt";
   std::string filexSciDR1NaI = "../../simdata/final/square_both_sides_NaI_1e5goldcascade_SciDR1.txt";
   std::string filexSciDT2NaI = "../../simdata/final/square_both_sides_NaI_1e5goldcascade_SciDT2.txt";
   std::string filexSciDB2NaI = "../../simdata/final/square_both_sides_NaI_1e5goldcascade_SciDB2.txt";
   std::string filexSciDL2NaI = "../../simdata/final/square_both_sides_NaI_1e5goldcascade_SciDL2.txt";
   std::string filexSciDR2NaI = "../../simdata/final/square_both_sides_NaI_1e5goldcascade_SciDR2.txt";
   std::string filexBGOD1NaI = "../../simdata/final/square_both_sides_NaI_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD2NaI = "../../simdata/final/square_both_sides_NaI_1e5goldcascade_BGOD2.txt";

   // X-ray cascade with Sci
   std::string filexSciD1Sci = "../../simdata/final/square_both_sides_Sci_1e5goldcascade_SciD1.txt";
   std::string filexSciD2Sci = "../../simdata/final/square_both_sides_Sci_1e5goldcascade_SciD2.txt";
   std::string filexSciD3Sci = "../../simdata/final/square_both_sides_Sci_1e5goldcascade_SciD3.txt";
   std::string filexSciDT1Sci = "../../simdata/final/square_both_sides_Sci_1e5goldcascade_SciDT1.txt";
   std::string filexSciDB1Sci = "../../simdata/final/square_both_sides_Sci_1e5goldcascade_SciDB1.txt";
   std::string filexSciDL1Sci = "../../simdata/final/square_both_sides_Sci_1e5goldcascade_SciDL1.txt";
   std::string filexSciDR1Sci = "../../simdata/final/square_both_sides_Sci_1e5goldcascade_SciDR1.txt";
   std::string filexSciDT2Sci = "../../simdata/final/square_both_sides_Sci_1e5goldcascade_SciDT2.txt";
   std::string filexSciDB2Sci = "../../simdata/final/square_both_sides_Sci_1e5goldcascade_SciDB2.txt";
   std::string filexSciDL2Sci = "../../simdata/final/square_both_sides_Sci_1e5goldcascade_SciDL2.txt";
   std::string filexSciDR2Sci = "../../simdata/final/square_both_sides_Sci_1e5goldcascade_SciDR2.txt";
   std::string filexBGOD1Sci = "../../simdata/final/square_both_sides_Sci_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD2Sci = "../../simdata/final/square_both_sides_Sci_1e5goldcascade_BGOD2.txt";

   // Mu-decay with NaI
   std::string filemuSciD1NaI = "../../simdata/final/square_both_sides_NaI_1e5mudecay_SciD1.txt";
   std::string filemuSciD2NaI = "../../simdata/final/square_both_sides_NaI_1e5mudecay_SciD2.txt";
   std::string filemuSciD3NaI = "../../simdata/final/square_both_sides_NaI_1e5mudecay_SciD3.txt";
   std::string filemuSciDT1NaI = "../../simdata/final/square_both_sides_NaI_1e5mudecay_SciDT1.txt";
   std::string filemuSciDB1NaI = "../../simdata/final/square_both_sides_NaI_1e5mudecay_SciDB1.txt";
   std::string filemuSciDL1NaI = "../../simdata/final/square_both_sides_NaI_1e5mudecay_SciDL1.txt";
   std::string filemuSciDR1NaI = "../../simdata/final/square_both_sides_NaI_1e5mudecay_SciDR1.txt";
   std::string filemuSciDT2NaI = "../../simdata/final/square_both_sides_NaI_1e5mudecay_SciDT2.txt";
   std::string filemuSciDB2NaI = "../../simdata/final/square_both_sides_NaI_1e5mudecay_SciDB2.txt";
   std::string filemuSciDL2NaI = "../../simdata/final/square_both_sides_NaI_1e5mudecay_SciDL2.txt";
   std::string filemuSciDR2NaI = "../../simdata/final/square_both_sides_NaI_1e5mudecay_SciDR2.txt";
   std::string filemuBGOD1NaI = "../../simdata/final/square_both_sides_NaI_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD2NaI = "../../simdata/final/square_both_sides_NaI_1e5mudecay_BGOD2.txt";

   // Mu-decay with Sci
   std::string filemuSciD1Sci = "../../simdata/final/square_both_sides_Sci_1e5mudecay_SciD1.txt";
   std::string filemuSciD2Sci = "../../simdata/final/square_both_sides_Sci_1e5mudecay_SciD2.txt";
   std::string filemuSciD3Sci = "../../simdata/final/square_both_sides_Sci_1e5mudecay_SciD3.txt";
   std::string filemuSciDT1Sci = "../../simdata/final/square_both_sides_Sci_1e5mudecay_SciDT1.txt";
   std::string filemuSciDB1Sci = "../../simdata/final/square_both_sides_Sci_1e5mudecay_SciDB1.txt";
   std::string filemuSciDL1Sci = "../../simdata/final/square_both_sides_Sci_1e5mudecay_SciDL1.txt";
   std::string filemuSciDR1Sci = "../../simdata/final/square_both_sides_Sci_1e5mudecay_SciDR1.txt";
   std::string filemuSciDT2Sci = "../../simdata/final/square_both_sides_Sci_1e5mudecay_SciDT2.txt";
   std::string filemuSciDB2Sci = "../../simdata/final/square_both_sides_Sci_1e5mudecay_SciDB2.txt";
   std::string filemuSciDL2Sci = "../../simdata/final/square_both_sides_Sci_1e5mudecay_SciDL2.txt";
   std::string filemuSciDR2Sci = "../../simdata/final/square_both_sides_Sci_1e5mudecay_SciDR2.txt";
   std::string filemuBGOD1Sci = "../../simdata/final/square_both_sides_Sci_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD2Sci = "../../simdata/final/square_both_sides_Sci_1e5mudecay_BGOD2.txt";


   // Vectors with filenames   
   std::vector<std::string> Xfiles;
   std::vector<std::string> mufiles;

   // X-ray cascade
   Xfiles.push_back(filexSciD1NaI);
   Xfiles.push_back(filexSciD2NaI);
   Xfiles.push_back(filexSciD3NaI);
   Xfiles.push_back(filexSciDT1NaI);
   Xfiles.push_back(filexSciDB1NaI);
   Xfiles.push_back(filexSciDL1NaI);
   Xfiles.push_back(filexSciDR1NaI);
   Xfiles.push_back(filexSciDT2NaI);
   Xfiles.push_back(filexSciDB2NaI);
   Xfiles.push_back(filexSciDL2NaI);
   Xfiles.push_back(filexSciDR2NaI);
   Xfiles.push_back(filexBGOD1NaI);
   Xfiles.push_back(filexBGOD2NaI);

   Xfiles.push_back(filexSciD1Sci);
   Xfiles.push_back(filexSciD2Sci);
   Xfiles.push_back(filexSciD3Sci);
   Xfiles.push_back(filexSciDT1Sci);
   Xfiles.push_back(filexSciDB1Sci);
   Xfiles.push_back(filexSciDL1Sci);
   Xfiles.push_back(filexSciDR1Sci);
   Xfiles.push_back(filexSciDT2Sci);
   Xfiles.push_back(filexSciDB2Sci);
   Xfiles.push_back(filexSciDL2Sci);
   Xfiles.push_back(filexSciDR2Sci);
   Xfiles.push_back(filexBGOD1Sci);
   Xfiles.push_back(filexBGOD2Sci);
		 

   // Mu-decay
   mufiles.push_back(filemuSciD1NaI);
   mufiles.push_back(filemuSciD2NaI);
   mufiles.push_back(filemuSciD3NaI);
   mufiles.push_back(filemuSciDT1NaI);
   mufiles.push_back(filemuSciDB1NaI);
   mufiles.push_back(filemuSciDL1NaI);
   mufiles.push_back(filemuSciDR1NaI);
   mufiles.push_back(filemuSciDT2NaI);
   mufiles.push_back(filemuSciDB2NaI);
   mufiles.push_back(filemuSciDL2NaI);
   mufiles.push_back(filemuSciDR2NaI);
   mufiles.push_back(filemuBGOD1NaI);
   mufiles.push_back(filemuBGOD2NaI);

   mufiles.push_back(filemuSciD1Sci);
   mufiles.push_back(filemuSciD2Sci);
   mufiles.push_back(filemuSciD3Sci);
   mufiles.push_back(filemuSciDT1Sci);
   mufiles.push_back(filemuSciDB1Sci);
   mufiles.push_back(filemuSciDL1Sci);
   mufiles.push_back(filemuSciDR1Sci);
   mufiles.push_back(filemuSciDT2Sci);
   mufiles.push_back(filemuSciDB2Sci);
   mufiles.push_back(filemuSciDL2Sci);
   mufiles.push_back(filemuSciDR2Sci);
   mufiles.push_back(filemuBGOD1Sci);
   mufiles.push_back(filemuBGOD2Sci);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep, EventID;
   float iEventID;

   float Ethr1 = 0.5;
   float Ethr21 = 0.5;
   float Ethr22 = 10;
   float Ethr3 = 1;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
		   
   // Storage vectors
   // Normalisation 2 [abs = total] :: X-ray cascade
   std::vector< std::vector<double> > PXevectorN2NaI(Xfiles.size()/26,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorN2NaI(Xfiles.size()/26,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevectorN2Sci(Xfiles.size()/26,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorN2Sci(Xfiles.size()/26,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay
   std::vector< std::vector<double> > PeevectorN2NaI(mufiles.size()/26,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorN2NaI(mufiles.size()/26,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > PeevectorN2Sci(mufiles.size()/26,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorN2Sci(mufiles.size()/26,std::vector<double>(nsamps));      


   // X-ray cascade
   std::vector< std::vector< double > > allvEvIDSD1xNaI;
   std::vector< std::vector< double > > allvEdepSD1xNaI;
   std::vector< std::vector< double > > allvEvIDSD2xNaI;
   std::vector< std::vector< double > > allvEdepSD2xNaI;
   std::vector< std::vector< double > > allvEvIDSD3xNaI;
   std::vector< std::vector< double > > allvEdepSD3xNaI;
   std::vector< std::vector< double > > allvEvIDSDT1xNaI;
   std::vector< std::vector< double > > allvEdepSDT1xNaI;
   std::vector< std::vector< double > > allvEvIDSDB1xNaI;
   std::vector< std::vector< double > > allvEdepSDB1xNaI;
   std::vector< std::vector< double > > allvEvIDSDL1xNaI;
   std::vector< std::vector< double > > allvEdepSDL1xNaI;
   std::vector< std::vector< double > > allvEvIDSDR1xNaI;
   std::vector< std::vector< double > > allvEdepSDR1xNaI;
   std::vector< std::vector< double > > allvEvIDSDT2xNaI;
   std::vector< std::vector< double > > allvEdepSDT2xNaI;
   std::vector< std::vector< double > > allvEvIDSDB2xNaI;
   std::vector< std::vector< double > > allvEdepSDB2xNaI;
   std::vector< std::vector< double > > allvEvIDSDL2xNaI;
   std::vector< std::vector< double > > allvEdepSDL2xNaI;
   std::vector< std::vector< double > > allvEvIDSDR2xNaI;
   std::vector< std::vector< double > > allvEdepSDR2xNaI;
   std::vector< std::vector< double > > allvEvIDBD1xNaI;
   std::vector< std::vector< double > > allvEdepBD1xNaI;
   std::vector< std::vector< double > > allvEvIDBD2xNaI;
   std::vector< std::vector< double > > allvEdepBD2xNaI;

   std::vector< std::vector< double > > allvEvIDSD1xSci;
   std::vector< std::vector< double > > allvEdepSD1xSci;
   std::vector< std::vector< double > > allvEvIDSD2xSci;
   std::vector< std::vector< double > > allvEdepSD2xSci;
   std::vector< std::vector< double > > allvEvIDSD3xSci;
   std::vector< std::vector< double > > allvEdepSD3xSci;
   std::vector< std::vector< double > > allvEvIDSDT1xSci;
   std::vector< std::vector< double > > allvEdepSDT1xSci;
   std::vector< std::vector< double > > allvEvIDSDB1xSci;
   std::vector< std::vector< double > > allvEdepSDB1xSci;
   std::vector< std::vector< double > > allvEvIDSDL1xSci;
   std::vector< std::vector< double > > allvEdepSDL1xSci;
   std::vector< std::vector< double > > allvEvIDSDR1xSci;
   std::vector< std::vector< double > > allvEdepSDR1xSci;
   std::vector< std::vector< double > > allvEvIDSDT2xSci;
   std::vector< std::vector< double > > allvEdepSDT2xSci;
   std::vector< std::vector< double > > allvEvIDSDB2xSci;
   std::vector< std::vector< double > > allvEdepSDB2xSci;
   std::vector< std::vector< double > > allvEvIDSDL2xSci;
   std::vector< std::vector< double > > allvEdepSDL2xSci;
   std::vector< std::vector< double > > allvEvIDSDR2xSci;
   std::vector< std::vector< double > > allvEdepSDR2xSci;
   std::vector< std::vector< double > > allvEvIDBD1xSci;
   std::vector< std::vector< double > > allvEdepBD1xSci;
   std::vector< std::vector< double > > allvEvIDBD2xSci;
   std::vector< std::vector< double > > allvEdepBD2xSci;


   // Mu-decay
   std::vector< std::vector< double > > allvEvIDSD1muNaI;
   std::vector< std::vector< double > > allvEdepSD1muNaI;
   std::vector< std::vector< double > > allvEvIDSD2muNaI;
   std::vector< std::vector< double > > allvEdepSD2muNaI;
   std::vector< std::vector< double > > allvEvIDSD3muNaI;
   std::vector< std::vector< double > > allvEdepSD3muNaI;
   std::vector< std::vector< double > > allvEvIDSDT1muNaI;
   std::vector< std::vector< double > > allvEdepSDT1muNaI;
   std::vector< std::vector< double > > allvEvIDSDB1muNaI;
   std::vector< std::vector< double > > allvEdepSDB1muNaI;
   std::vector< std::vector< double > > allvEvIDSDL1muNaI;
   std::vector< std::vector< double > > allvEdepSDL1muNaI;
   std::vector< std::vector< double > > allvEvIDSDR1muNaI;
   std::vector< std::vector< double > > allvEdepSDR1muNaI;
   std::vector< std::vector< double > > allvEvIDSDT2muNaI;
   std::vector< std::vector< double > > allvEdepSDT2muNaI;
   std::vector< std::vector< double > > allvEvIDSDB2muNaI;
   std::vector< std::vector< double > > allvEdepSDB2muNaI;
   std::vector< std::vector< double > > allvEvIDSDL2muNaI;
   std::vector< std::vector< double > > allvEdepSDL2muNaI;
   std::vector< std::vector< double > > allvEvIDSDR2muNaI;
   std::vector< std::vector< double > > allvEdepSDR2muNaI;
   std::vector< std::vector< double > > allvEvIDBD1muNaI;
   std::vector< std::vector< double > > allvEdepBD1muNaI;
   std::vector< std::vector< double > > allvEvIDBD2muNaI;
   std::vector< std::vector< double > > allvEdepBD2muNaI;

   std::vector< std::vector< double > > allvEvIDSD1muSci;
   std::vector< std::vector< double > > allvEdepSD1muSci;
   std::vector< std::vector< double > > allvEvIDSD2muSci;
   std::vector< std::vector< double > > allvEdepSD2muSci;
   std::vector< std::vector< double > > allvEvIDSD3muSci;
   std::vector< std::vector< double > > allvEdepSD3muSci;
   std::vector< std::vector< double > > allvEvIDSDT1muSci;
   std::vector< std::vector< double > > allvEdepSDT1muSci;
   std::vector< std::vector< double > > allvEvIDSDB1muSci;
   std::vector< std::vector< double > > allvEdepSDB1muSci;
   std::vector< std::vector< double > > allvEvIDSDL1muSci;
   std::vector< std::vector< double > > allvEdepSDL1muSci;
   std::vector< std::vector< double > > allvEvIDSDR1muSci;
   std::vector< std::vector< double > > allvEdepSDR1muSci;
   std::vector< std::vector< double > > allvEvIDSDT2muSci;
   std::vector< std::vector< double > > allvEdepSDT2muSci;
   std::vector< std::vector< double > > allvEvIDSDB2muSci;
   std::vector< std::vector< double > > allvEdepSDB2muSci;
   std::vector< std::vector< double > > allvEvIDSDL2muSci;
   std::vector< std::vector< double > > allvEdepSDL2muSci;
   std::vector< std::vector< double > > allvEvIDSDR2muSci;
   std::vector< std::vector< double > > allvEdepSDR2muSci;
   std::vector< std::vector< double > > allvEvIDBD1muSci;
   std::vector< std::vector< double > > allvEdepBD1muSci;
   std::vector< std::vector< double > > allvEvIDBD2muSci;
   std::vector< std::vector< double > > allvEdepBD2muSci;


   float Ethr;
   int counterXXN2 = 1e5;
   int countereeN2 = 1e5;
   int XXrayN2NaI = 0; // X-rays i-fied as X-rays
   int XelecN2NaI = 0; // X-rays i-fied as electrons
   int XXrayN2Sci = 0;
   int XelecN2Sci = 0;
   int eXrayN2NaI = 0; // Electrons i-fied as X-rays
   int eelecN2NaI = 0; // Electrons i-fied as electrons
   int eXrayN2Sci = 0;
   int eelecN2Sci = 0;
		   
   Ethrmu[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;


   //-------------------------------------------------------------------
   //                           Reading
   //-------------------------------------------------------------------
		   
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m------------------- X-ray cascade ------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


   for (int k=0; k<((Xfiles.size())/26); k++) {
			  
      // SciD1NaI
	  std::ifstream xfSciD1NaI(TString(Xfiles[k*26]));
	  std::vector<double> vEvIDSD1xNaI;
	  std::vector<double> vEdepSD1xNaI;
			  
	  while (!xfSciD1NaI.eof()) {
	     double EvIDSD1NaI, EdepSD1NaI;
		 xfSciD1NaI >> EvIDSD1NaI >> EdepSD1NaI;
		 vEvIDSD1xNaI.push_back(EvIDSD1NaI);
		 vEdepSD1xNaI.push_back(EdepSD1NaI);
	  }
	  vEvIDSD1xNaI.pop_back(); vEdepSD1xNaI.pop_back();
	  vEvIDSD1xNaI.pop_back(); vEdepSD1xNaI.pop_back();
			  
	  xfSciD1NaI.close();
	  allvEvIDSD1xNaI.push_back(vEvIDSD1xNaI);
	  allvEdepSD1xNaI.push_back(vEdepSD1xNaI);


	  // SciD2NaI
	  std::ifstream xfSciD2NaI(TString(Xfiles[(k*26)+1]));
	  std::vector<double> vEvIDSD2xNaI;
	  std::vector<double> vEdepSD2xNaI;
			  
	  while (!xfSciD2NaI.eof()) {
	     double EvIDSD2NaI, EdepSD2NaI;
		 xfSciD2NaI >> EvIDSD2NaI >> EdepSD2NaI;
		 vEvIDSD2xNaI.push_back(EvIDSD2NaI);
		 vEdepSD2xNaI.push_back(EdepSD2NaI);
	  }
	  vEvIDSD2xNaI.pop_back(); vEdepSD2xNaI.pop_back();
	  vEvIDSD2xNaI.pop_back(); vEdepSD2xNaI.pop_back();
			  
	  xfSciD2NaI.close();
	  allvEvIDSD2xNaI.push_back(vEvIDSD2xNaI);
	  allvEdepSD2xNaI.push_back(vEdepSD2xNaI);


	  // SciD3NaI
	  std::ifstream xfSciD3NaI(TString(Xfiles[(k*26)+2]));
	  std::vector<double> vEvIDSD3xNaI;
	  std::vector<double> vEdepSD3xNaI;
			  
	  while (!xfSciD3NaI.eof()) {
	     double EvIDSD3NaI, EdepSD3NaI;
		 xfSciD3NaI >> EvIDSD3NaI >> EdepSD3NaI;
		 vEvIDSD3xNaI.push_back(EvIDSD3NaI);
		 vEdepSD3xNaI.push_back(EdepSD3NaI);
	  }
	  vEvIDSD3xNaI.pop_back(); vEdepSD3xNaI.pop_back();
	  vEvIDSD3xNaI.pop_back(); vEdepSD3xNaI.pop_back();
			  
	  xfSciD3NaI.close();
	  allvEvIDSD3xNaI.push_back(vEvIDSD3xNaI);
	  allvEdepSD3xNaI.push_back(vEdepSD3xNaI);
			  
			  
	  // SciDT1NaI
	  std::ifstream xfSciDT1NaI(TString(Xfiles[(k*26)+3]));
	  std::vector<double> vEvIDSDT1xNaI;
	  std::vector<double> vEdepSDT1xNaI;
			  
	  while (!xfSciDT1NaI.eof()) {
	     double EvIDSDT1NaI, EdepSDT1NaI;
		 xfSciDT1NaI >> EvIDSDT1NaI >> EdepSDT1NaI;
		 vEvIDSDT1xNaI.push_back(EvIDSDT1NaI);
		 vEdepSDT1xNaI.push_back(EdepSDT1NaI);
	  }
	  vEvIDSDT1xNaI.pop_back(); vEdepSDT1xNaI.pop_back();
	  vEvIDSDT1xNaI.pop_back(); vEdepSDT1xNaI.pop_back();
			  
	  xfSciDT1NaI.close();
	  allvEvIDSDT1xNaI.push_back(vEvIDSDT1xNaI);
	  allvEdepSDT1xNaI.push_back(vEdepSDT1xNaI);


	  // SciDB1NaI
	  std::ifstream xfSciDB1NaI(TString(Xfiles[(k*26)+4]));
	  std::vector<double> vEvIDSDB1xNaI;
	  std::vector<double> vEdepSDB1xNaI;
			  
	  while (!xfSciDB1NaI.eof()) {
	     double EvIDSDB1NaI, EdepSDB1NaI;
		 xfSciDB1NaI >> EvIDSDB1NaI >> EdepSDB1NaI;
		 vEvIDSDB1xNaI.push_back(EvIDSDB1NaI);
		 vEdepSDB1xNaI.push_back(EdepSDB1NaI);
	  }
	  vEvIDSDB1xNaI.pop_back(); vEdepSDB1xNaI.pop_back();
	  vEvIDSDB1xNaI.pop_back(); vEdepSDB1xNaI.pop_back();
			  
	  xfSciDB1NaI.close();
	  allvEvIDSDB1xNaI.push_back(vEvIDSDB1xNaI);
	  allvEdepSDB1xNaI.push_back(vEdepSDB1xNaI);


	  // SciDL1NaI
	  std::ifstream xfSciDL1NaI(TString(Xfiles[(k*26)+5]));
	  std::vector<double> vEvIDSDL1xNaI;
	  std::vector<double> vEdepSDL1xNaI;
			  
	  while (!xfSciDL1NaI.eof()) {
	     double EvIDSDL1NaI, EdepSDL1NaI;
		 xfSciDL1NaI >> EvIDSDL1NaI >> EdepSDL1NaI;
		 vEvIDSDL1xNaI.push_back(EvIDSDL1NaI);
		 vEdepSDL1xNaI.push_back(EdepSDL1NaI);
	  }
	  vEvIDSDL1xNaI.pop_back(); vEdepSDL1xNaI.pop_back();
	  vEvIDSDL1xNaI.pop_back(); vEdepSDL1xNaI.pop_back();
			  
	  xfSciDL1NaI.close();
	  allvEvIDSDL1xNaI.push_back(vEvIDSDL1xNaI);
	  allvEdepSDL1xNaI.push_back(vEdepSDL1xNaI);


	  // SciDR1NaI
	  std::ifstream xfSciDR1NaI(TString(Xfiles[(k*26)+6]));
	  std::vector<double> vEvIDSDR1xNaI;
	  std::vector<double> vEdepSDR1xNaI;
			  
	  while (!xfSciDR1NaI.eof()) {
	     double EvIDSDR1NaI, EdepSDR1NaI;
		 xfSciDR1NaI >> EvIDSDR1NaI >> EdepSDR1NaI;
		 vEvIDSDR1xNaI.push_back(EvIDSDR1NaI);
		 vEdepSDR1xNaI.push_back(EdepSDR1NaI);
	  }
	  vEvIDSDR1xNaI.pop_back(); vEdepSDR1xNaI.pop_back();
	  vEvIDSDR1xNaI.pop_back(); vEdepSDR1xNaI.pop_back();
			  
	  xfSciDR1NaI.close();
	  allvEvIDSDR1xNaI.push_back(vEvIDSDR1xNaI);
	  allvEdepSDR1xNaI.push_back(vEdepSDR1xNaI);


	  // SciDT2NaI
	  std::ifstream xfSciDT2NaI(TString(Xfiles[(k*26)+7]));
	  std::vector<double> vEvIDSDT2xNaI;
	  std::vector<double> vEdepSDT2xNaI;
			  
	  while (!xfSciDT2NaI.eof()) {
	     double EvIDSDT2NaI, EdepSDT2NaI;
		 xfSciDT2NaI >> EvIDSDT2NaI >> EdepSDT2NaI;
		 vEvIDSDT2xNaI.push_back(EvIDSDT2NaI);
		 vEdepSDT2xNaI.push_back(EdepSDT2NaI);
	  }
	  vEvIDSDT2xNaI.pop_back(); vEdepSDT2xNaI.pop_back();
	  vEvIDSDT2xNaI.pop_back(); vEdepSDT2xNaI.pop_back();
			  
	  xfSciDT2NaI.close();
	  allvEvIDSDT2xNaI.push_back(vEvIDSDT2xNaI);
	  allvEdepSDT2xNaI.push_back(vEdepSDT2xNaI);


	  // SciDB2NaI
	  std::ifstream xfSciDB2NaI(TString(Xfiles[(k*26)+8]));
	  std::vector<double> vEvIDSDB2xNaI;
	  std::vector<double> vEdepSDB2xNaI;
			  
	  while (!xfSciDB2NaI.eof()) {
	     double EvIDSDB2NaI, EdepSDB2NaI;
		 xfSciDB2NaI >> EvIDSDB2NaI >> EdepSDB2NaI;
		 vEvIDSDB2xNaI.push_back(EvIDSDB2NaI);
		 vEdepSDB2xNaI.push_back(EdepSDB2NaI);
	  }
	  vEvIDSDB2xNaI.pop_back(); vEdepSDB2xNaI.pop_back();
	  vEvIDSDB2xNaI.pop_back(); vEdepSDB2xNaI.pop_back();
			  
	  xfSciDB2NaI.close();
	  allvEvIDSDB2xNaI.push_back(vEvIDSDB2xNaI);
	  allvEdepSDB2xNaI.push_back(vEdepSDB2xNaI);


	  // SciDL2NaI
	  std::ifstream xfSciDL2NaI(TString(Xfiles[(k*26)+9]));
	  std::vector<double> vEvIDSDL2xNaI;
	  std::vector<double> vEdepSDL2xNaI;
			  
	  while (!xfSciDL2NaI.eof()) {
	     double EvIDSDL2NaI, EdepSDL2NaI;
		 xfSciDL2NaI >> EvIDSDL2NaI >> EdepSDL2NaI;
		 vEvIDSDL2xNaI.push_back(EvIDSDL2NaI);
		 vEdepSDL2xNaI.push_back(EdepSDL2NaI);
	  }
	  vEvIDSDL2xNaI.pop_back(); vEdepSDL2xNaI.pop_back();
	  vEvIDSDL2xNaI.pop_back(); vEdepSDL2xNaI.pop_back();
			  
	  xfSciDL2NaI.close();
	  allvEvIDSDL2xNaI.push_back(vEvIDSDL2xNaI);
	  allvEdepSDL2xNaI.push_back(vEdepSDL2xNaI);


	  // SciDR2NaI
	  std::ifstream xfSciDR2NaI(TString(Xfiles[(k*26)+10]));
	  std::vector<double> vEvIDSDR2xNaI;
	  std::vector<double> vEdepSDR2xNaI;
			  
	  while (!xfSciDR2NaI.eof()) {
	     double EvIDSDR2NaI, EdepSDR2NaI;
		 xfSciDR2NaI >> EvIDSDR2NaI >> EdepSDR2NaI;
		 vEvIDSDR2xNaI.push_back(EvIDSDR2NaI);
		 vEdepSDR2xNaI.push_back(EdepSDR2NaI);
	  }
	  vEvIDSDR2xNaI.pop_back(); vEdepSDR2xNaI.pop_back();
	  vEvIDSDR2xNaI.pop_back(); vEdepSDR2xNaI.pop_back();
			  
	  xfSciDR2NaI.close();
	  allvEvIDSDR2xNaI.push_back(vEvIDSDR2xNaI);
	  allvEdepSDR2xNaI.push_back(vEdepSDR2xNaI);


	  // BGOD1NaI
	  std::ifstream xfBGOD1NaI(TString(Xfiles[(k*26)+11]));
	  std::vector<double> vEvIDBD1xNaI;
	  std::vector<double> vEdepBD1xNaI;
			  
	  while (!xfBGOD1NaI.eof()) {
	     double EvIDBD1NaI, EdepBD1NaI;
		 xfBGOD1NaI >> EvIDBD1NaI >> EdepBD1NaI;
		 vEvIDBD1xNaI.push_back(EvIDBD1NaI);
		 vEdepBD1xNaI.push_back(EdepBD1NaI);
	  }
	  vEvIDBD1xNaI.pop_back(); vEdepBD1xNaI.pop_back();
	  vEvIDBD1xNaI.pop_back(); vEdepBD1xNaI.pop_back();
			  
	  xfBGOD1NaI.close();
	  allvEvIDBD1xNaI.push_back(vEvIDBD1xNaI);
	  allvEdepBD1xNaI.push_back(vEdepBD1xNaI);


	  // BGOD2NaI
	  std::ifstream xfBGOD2NaI(TString(Xfiles[(k*26)+12]));
	  std::vector<double> vEvIDBD2xNaI;
	  std::vector<double> vEdepBD2xNaI;
			  
	  while (!xfBGOD2NaI.eof()) {
	     double EvIDBD2NaI, EdepBD2NaI;
		 xfBGOD2NaI >> EvIDBD2NaI >> EdepBD2NaI;
		 vEvIDBD2xNaI.push_back(EvIDBD2NaI);
		 vEdepBD2xNaI.push_back(EdepBD2NaI);
	  }
	  vEvIDBD2xNaI.pop_back(); vEdepBD2xNaI.pop_back();
	  vEvIDBD2xNaI.pop_back(); vEdepBD2xNaI.pop_back();
			  
	  xfBGOD2NaI.close();
	  allvEvIDBD2xNaI.push_back(vEvIDBD2xNaI);
	  allvEdepBD2xNaI.push_back(vEdepBD2xNaI);


      // SciD1Sci
	  std::ifstream xfSciD1Sci(TString(Xfiles[(k*26)+13]));
	  std::vector<double> vEvIDSD1xSci;
	  std::vector<double> vEdepSD1xSci;
			  
	  while (!xfSciD1Sci.eof()) {
	     double EvIDSD1Sci, EdepSD1Sci;
		 xfSciD1Sci >> EvIDSD1Sci >> EdepSD1Sci;
		 vEvIDSD1xSci.push_back(EvIDSD1Sci);
		 vEdepSD1xSci.push_back(EdepSD1Sci);
	  }
	  vEvIDSD1xSci.pop_back(); vEdepSD1xSci.pop_back();
	  vEvIDSD1xSci.pop_back(); vEdepSD1xSci.pop_back();
			  
	  xfSciD1Sci.close();
	  allvEvIDSD1xSci.push_back(vEvIDSD1xSci);
	  allvEdepSD1xSci.push_back(vEdepSD1xSci);


	  // SciD2Sci
	  std::ifstream xfSciD2Sci(TString(Xfiles[(k*26)+14]));
	  std::vector<double> vEvIDSD2xSci;
	  std::vector<double> vEdepSD2xSci;
			  
	  while (!xfSciD2Sci.eof()) {
	     double EvIDSD2Sci, EdepSD2Sci;
		 xfSciD2Sci >> EvIDSD2Sci >> EdepSD2Sci;
		 vEvIDSD2xSci.push_back(EvIDSD2Sci);
		 vEdepSD2xSci.push_back(EdepSD2Sci);
	  }
	  vEvIDSD2xSci.pop_back(); vEdepSD2xSci.pop_back();
	  vEvIDSD2xSci.pop_back(); vEdepSD2xSci.pop_back();
			  
	  xfSciD2Sci.close();
	  allvEvIDSD2xSci.push_back(vEvIDSD2xSci);
	  allvEdepSD2xSci.push_back(vEdepSD2xSci);


	  // SciD3Sci
	  std::ifstream xfSciD3Sci(TString(Xfiles[(k*26)+15]));
	  std::vector<double> vEvIDSD3xSci;
	  std::vector<double> vEdepSD3xSci;
			  
	  while (!xfSciD3Sci.eof()) {
	     double EvIDSD3Sci, EdepSD3Sci;
		 xfSciD3Sci >> EvIDSD3Sci >> EdepSD3Sci;
		 vEvIDSD3xSci.push_back(EvIDSD3Sci);
		 vEdepSD3xSci.push_back(EdepSD3Sci);
	  }
	  vEvIDSD3xSci.pop_back(); vEdepSD3xSci.pop_back();
	  vEvIDSD3xSci.pop_back(); vEdepSD3xSci.pop_back();
			  
	  xfSciD3Sci.close();
	  allvEvIDSD3xSci.push_back(vEvIDSD3xSci);
	  allvEdepSD3xSci.push_back(vEdepSD3xSci);
			  
			  
	  // SciDT1Sci
	  std::ifstream xfSciDT1Sci(TString(Xfiles[(k*26)+16]));
	  std::vector<double> vEvIDSDT1xSci;
	  std::vector<double> vEdepSDT1xSci;
			  
	  while (!xfSciDT1Sci.eof()) {
	     double EvIDSDT1Sci, EdepSDT1Sci;
		 xfSciDT1Sci >> EvIDSDT1Sci >> EdepSDT1Sci;
		 vEvIDSDT1xSci.push_back(EvIDSDT1Sci);
		 vEdepSDT1xSci.push_back(EdepSDT1Sci);
	  }
	  vEvIDSDT1xSci.pop_back(); vEdepSDT1xSci.pop_back();
	  vEvIDSDT1xSci.pop_back(); vEdepSDT1xSci.pop_back();
			  
	  xfSciDT1Sci.close();
	  allvEvIDSDT1xSci.push_back(vEvIDSDT1xSci);
	  allvEdepSDT1xSci.push_back(vEdepSDT1xSci);


	  // SciDB1Sci
	  std::ifstream xfSciDB1Sci(TString(Xfiles[(k*26)+17]));
	  std::vector<double> vEvIDSDB1xSci;
	  std::vector<double> vEdepSDB1xSci;
			  
	  while (!xfSciDB1Sci.eof()) {
	     double EvIDSDB1Sci, EdepSDB1Sci;
		 xfSciDB1Sci >> EvIDSDB1Sci >> EdepSDB1Sci;
		 vEvIDSDB1xSci.push_back(EvIDSDB1Sci);
		 vEdepSDB1xSci.push_back(EdepSDB1Sci);
	  }
	  vEvIDSDB1xSci.pop_back(); vEdepSDB1xSci.pop_back();
	  vEvIDSDB1xSci.pop_back(); vEdepSDB1xSci.pop_back();
			  
	  xfSciDB1Sci.close();
	  allvEvIDSDB1xSci.push_back(vEvIDSDB1xSci);
	  allvEdepSDB1xSci.push_back(vEdepSDB1xSci);


	  // SciDL1Sci
	  std::ifstream xfSciDL1Sci(TString(Xfiles[(k*26)+18]));
	  std::vector<double> vEvIDSDL1xSci;
	  std::vector<double> vEdepSDL1xSci;
			  
	  while (!xfSciDL1Sci.eof()) {
	     double EvIDSDL1Sci, EdepSDL1Sci;
		 xfSciDL1Sci >> EvIDSDL1Sci >> EdepSDL1Sci;
		 vEvIDSDL1xSci.push_back(EvIDSDL1Sci);
		 vEdepSDL1xSci.push_back(EdepSDL1Sci);
	  }
	  vEvIDSDL1xSci.pop_back(); vEdepSDL1xSci.pop_back();
	  vEvIDSDL1xSci.pop_back(); vEdepSDL1xSci.pop_back();
			  
	  xfSciDL1Sci.close();
	  allvEvIDSDL1xSci.push_back(vEvIDSDL1xSci);
	  allvEdepSDL1xSci.push_back(vEdepSDL1xSci);


	  // SciDR1Sci
	  std::ifstream xfSciDR1Sci(TString(Xfiles[(k*26)+19]));
	  std::vector<double> vEvIDSDR1xSci;
	  std::vector<double> vEdepSDR1xSci;
			  
	  while (!xfSciDR1Sci.eof()) {
	     double EvIDSDR1Sci, EdepSDR1Sci;
		 xfSciDR1Sci >> EvIDSDR1Sci >> EdepSDR1Sci;
		 vEvIDSDR1xSci.push_back(EvIDSDR1Sci);
		 vEdepSDR1xSci.push_back(EdepSDR1Sci);
	  }
	  vEvIDSDR1xSci.pop_back(); vEdepSDR1xSci.pop_back();
	  vEvIDSDR1xSci.pop_back(); vEdepSDR1xSci.pop_back();
			  
	  xfSciDR1Sci.close();
	  allvEvIDSDR1xSci.push_back(vEvIDSDR1xSci);
	  allvEdepSDR1xSci.push_back(vEdepSDR1xSci);


	  // SciDT2Sci
	  std::ifstream xfSciDT2Sci(TString(Xfiles[(k*26)+20]));
	  std::vector<double> vEvIDSDT2xSci;
	  std::vector<double> vEdepSDT2xSci;
			  
	  while (!xfSciDT2Sci.eof()) {
	     double EvIDSDT2Sci, EdepSDT2Sci;
		 xfSciDT2Sci >> EvIDSDT2Sci >> EdepSDT2Sci;
		 vEvIDSDT2xSci.push_back(EvIDSDT2Sci);
		 vEdepSDT2xSci.push_back(EdepSDT2Sci);
	  }
	  vEvIDSDT2xSci.pop_back(); vEdepSDT2xSci.pop_back();
	  vEvIDSDT2xSci.pop_back(); vEdepSDT2xSci.pop_back();
			  
	  xfSciDT2Sci.close();
	  allvEvIDSDT2xSci.push_back(vEvIDSDT2xSci);
	  allvEdepSDT2xSci.push_back(vEdepSDT2xSci);


	  // SciDB2Sci
	  std::ifstream xfSciDB2Sci(TString(Xfiles[(k*26)+21]));
	  std::vector<double> vEvIDSDB2xSci;
	  std::vector<double> vEdepSDB2xSci;
			  
	  while (!xfSciDB2Sci.eof()) {
	     double EvIDSDB2Sci, EdepSDB2Sci;
		 xfSciDB2Sci >> EvIDSDB2Sci >> EdepSDB2Sci;
		 vEvIDSDB2xSci.push_back(EvIDSDB2Sci);
		 vEdepSDB2xSci.push_back(EdepSDB2Sci);
	  }
	  vEvIDSDB2xSci.pop_back(); vEdepSDB2xSci.pop_back();
	  vEvIDSDB2xSci.pop_back(); vEdepSDB2xSci.pop_back();
			  
	  xfSciDB2Sci.close();
	  allvEvIDSDB2xSci.push_back(vEvIDSDB2xSci);
	  allvEdepSDB2xSci.push_back(vEdepSDB2xSci);


	  // SciDL2Sci
	  std::ifstream xfSciDL2Sci(TString(Xfiles[(k*26)+22]));
	  std::vector<double> vEvIDSDL2xSci;
	  std::vector<double> vEdepSDL2xSci;
			  
	  while (!xfSciDL2Sci.eof()) {
	     double EvIDSDL2Sci, EdepSDL2Sci;
		 xfSciDL2Sci >> EvIDSDL2Sci >> EdepSDL2Sci;
		 vEvIDSDL2xSci.push_back(EvIDSDL2Sci);
		 vEdepSDL2xSci.push_back(EdepSDL2Sci);
	  }
	  vEvIDSDL2xSci.pop_back(); vEdepSDL2xSci.pop_back();
	  vEvIDSDL2xSci.pop_back(); vEdepSDL2xSci.pop_back();
			  
	  xfSciDL2Sci.close();
	  allvEvIDSDL2xSci.push_back(vEvIDSDL2xSci);
	  allvEdepSDL2xSci.push_back(vEdepSDL2xSci);


	  // SciDR2Sci
	  std::ifstream xfSciDR2Sci(TString(Xfiles[(k*26)+23]));
	  std::vector<double> vEvIDSDR2xSci;
	  std::vector<double> vEdepSDR2xSci;
			  
	  while (!xfSciDR2Sci.eof()) {
	     double EvIDSDR2Sci, EdepSDR2Sci;
		 xfSciDR2Sci >> EvIDSDR2Sci >> EdepSDR2Sci;
		 vEvIDSDR2xSci.push_back(EvIDSDR2Sci);
		 vEdepSDR2xSci.push_back(EdepSDR2Sci);
	  }
	  vEvIDSDR2xSci.pop_back(); vEdepSDR2xSci.pop_back();
	  vEvIDSDR2xSci.pop_back(); vEdepSDR2xSci.pop_back();
			  
	  xfSciDR2Sci.close();
	  allvEvIDSDR2xSci.push_back(vEvIDSDR2xSci);
	  allvEdepSDR2xSci.push_back(vEdepSDR2xSci);


	  // BGOD1Sci
	  std::ifstream xfBGOD1Sci(TString(Xfiles[(k*26)+24]));
	  std::vector<double> vEvIDBD1xSci;
	  std::vector<double> vEdepBD1xSci;
			  
	  while (!xfBGOD1Sci.eof()) {
	     double EvIDBD1Sci, EdepBD1Sci;
		 xfBGOD1Sci >> EvIDBD1Sci >> EdepBD1Sci;
		 vEvIDBD1xSci.push_back(EvIDBD1Sci);
		 vEdepBD1xSci.push_back(EdepBD1Sci);
	  }
	  vEvIDBD1xSci.pop_back(); vEdepBD1xSci.pop_back();
	  vEvIDBD1xSci.pop_back(); vEdepBD1xSci.pop_back();
			  
	  xfBGOD1Sci.close();
	  allvEvIDBD1xSci.push_back(vEvIDBD1xSci);
	  allvEdepBD1xSci.push_back(vEdepBD1xSci);


	  // BGOD2Sci
	  std::ifstream xfBGOD2Sci(TString(Xfiles[(k*26)+25]));
	  std::vector<double> vEvIDBD2xSci;
	  std::vector<double> vEdepBD2xSci;
			  
	  while (!xfBGOD2Sci.eof()) {
	     double EvIDBD2Sci, EdepBD2Sci;
		 xfBGOD2Sci >> EvIDBD2Sci >> EdepBD2Sci;
		 vEvIDBD2xSci.push_back(EvIDBD2Sci);
		 vEdepBD2xSci.push_back(EdepBD2Sci);
	  }
	  vEvIDBD2xSci.pop_back(); vEdepBD2xSci.pop_back();
	  vEvIDBD2xSci.pop_back(); vEdepBD2xSci.pop_back();
			  
	  xfBGOD2Sci.close();
	  allvEvIDBD2xSci.push_back(vEvIDBD2xSci);
	  allvEdepBD2xSci.push_back(vEdepBD2xSci);

   }



   for (int k=0; k<((mufiles.size())/26); k++) {
   
      // SciD1muNaI
	  std::ifstream mufSciD1NaI(TString(mufiles[k*26]));
	  std::vector<double> vEvIDSD1muNaI;
	  std::vector<double> vEdepSD1muNaI;
			  
	  while (!mufSciD1NaI.eof()) {
	     double EvIDSD1muNaI, EdepSD1muNaI;
		 mufSciD1NaI >> EvIDSD1muNaI >> EdepSD1muNaI;
		 vEvIDSD1muNaI.push_back(EvIDSD1muNaI);
		 vEdepSD1muNaI.push_back(EdepSD1muNaI);
	  }
	  vEvIDSD1muNaI.pop_back(); vEdepSD1muNaI.pop_back();
	  vEvIDSD1muNaI.pop_back(); vEdepSD1muNaI.pop_back();
			  
	  mufSciD1NaI.close();
	  allvEvIDSD1muNaI.push_back(vEvIDSD1muNaI);
	  allvEdepSD1muNaI.push_back(vEdepSD1muNaI);


	  // SciD2muNaI
	  std::ifstream mufSciD2NaI(TString(mufiles[(k*26)+1]));
	  std::vector<double> vEvIDSD2muNaI;
	  std::vector<double> vEdepSD2muNaI;
			  
	  while (!mufSciD2NaI.eof()) {
	     double EvIDSD2muNaI, EdepSD2muNaI;
		 mufSciD2NaI >> EvIDSD2muNaI >> EdepSD2muNaI;
		 vEvIDSD2muNaI.push_back(EvIDSD2muNaI);
		 vEdepSD2muNaI.push_back(EdepSD2muNaI);
	  }
	  vEvIDSD2muNaI.pop_back(); vEdepSD2muNaI.pop_back();
	  vEvIDSD2muNaI.pop_back(); vEdepSD2muNaI.pop_back();
			  
	  mufSciD2NaI.close();
	  allvEvIDSD2muNaI.push_back(vEvIDSD2muNaI);
	  allvEdepSD2muNaI.push_back(vEdepSD2muNaI);


	  // SciD3muNaI
	  std::ifstream mufSciD3NaI(TString(mufiles[(k*26)+2]));
	  std::vector<double> vEvIDSD3muNaI;
	  std::vector<double> vEdepSD3muNaI;
			  
	  while (!mufSciD3NaI.eof()) {
	     double EvIDSD3muNaI, EdepSD3muNaI;
		 mufSciD3NaI >> EvIDSD3muNaI >> EdepSD3muNaI;
		 vEvIDSD3muNaI.push_back(EvIDSD3muNaI);
		 vEdepSD3muNaI.push_back(EdepSD3muNaI);
	  }
	  vEvIDSD3muNaI.pop_back(); vEdepSD3muNaI.pop_back();
	  vEvIDSD3muNaI.pop_back(); vEdepSD3muNaI.pop_back();
			  
	  mufSciD3NaI.close();
	  allvEvIDSD3muNaI.push_back(vEvIDSD3muNaI);
	  allvEdepSD3muNaI.push_back(vEdepSD3muNaI);
			  
			  
	  // SciDT1muNaI
	  std::ifstream mufSciDT1NaI(TString(mufiles[(k*26)+3]));
	  std::vector<double> vEvIDSDT1muNaI;
	  std::vector<double> vEdepSDT1muNaI;
			  
	  while (!mufSciDT1NaI.eof()) {
	     double EvIDSDT1muNaI, EdepSDT1muNaI;
		 mufSciDT1NaI >> EvIDSDT1muNaI >> EdepSDT1muNaI;
		 vEvIDSDT1muNaI.push_back(EvIDSDT1muNaI);
		 vEdepSDT1muNaI.push_back(EdepSDT1muNaI);
	  }
	  vEvIDSDT1muNaI.pop_back(); vEdepSDT1muNaI.pop_back();
	  vEvIDSDT1muNaI.pop_back(); vEdepSDT1muNaI.pop_back();
			  
	  mufSciDT1NaI.close();
	  allvEvIDSDT1muNaI.push_back(vEvIDSDT1muNaI);
	  allvEdepSDT1muNaI.push_back(vEdepSDT1muNaI);


	  // SciDB1muNaI
	  std::ifstream mufSciDB1NaI(TString(mufiles[(k*26)+4]));
	  std::vector<double> vEvIDSDB1muNaI;
	  std::vector<double> vEdepSDB1muNaI;
			  
	  while (!mufSciDB1NaI.eof()) {
	     double EvIDSDB1muNaI, EdepSDB1muNaI;
		 mufSciDB1NaI >> EvIDSDB1muNaI >> EdepSDB1muNaI;
		 vEvIDSDB1muNaI.push_back(EvIDSDB1muNaI);
		 vEdepSDB1muNaI.push_back(EdepSDB1muNaI);
	  }
	  vEvIDSDB1muNaI.pop_back(); vEdepSDB1muNaI.pop_back();
	  vEvIDSDB1muNaI.pop_back(); vEdepSDB1muNaI.pop_back();
			  
	  mufSciDB1NaI.close();
	  allvEvIDSDB1muNaI.push_back(vEvIDSDB1muNaI);
	  allvEdepSDB1muNaI.push_back(vEdepSDB1muNaI);


	  // SciDL1muNaI
	  std::ifstream mufSciDL1NaI(TString(mufiles[(k*26)+5]));
	  std::vector<double> vEvIDSDL1muNaI;
	  std::vector<double> vEdepSDL1muNaI;
			  
	  while (!mufSciDL1NaI.eof()) {
	     double EvIDSDL1muNaI, EdepSDL1muNaI;
		 mufSciDL1NaI >> EvIDSDL1muNaI >> EdepSDL1muNaI;
		 vEvIDSDL1muNaI.push_back(EvIDSDL1muNaI);
		 vEdepSDL1muNaI.push_back(EdepSDL1muNaI);
	  }
	  vEvIDSDL1muNaI.pop_back(); vEdepSDL1muNaI.pop_back();
	  vEvIDSDL1muNaI.pop_back(); vEdepSDL1muNaI.pop_back();
			  
	  mufSciDL1NaI.close();
	  allvEvIDSDL1muNaI.push_back(vEvIDSDL1muNaI);
	  allvEdepSDL1muNaI.push_back(vEdepSDL1muNaI);


	  // SciDR1muNaI
	  std::ifstream mufSciDR1NaI(TString(mufiles[(k*26)+6]));
	  std::vector<double> vEvIDSDR1muNaI;
	  std::vector<double> vEdepSDR1muNaI;
			  
	  while (!mufSciDR1NaI.eof()) {
	     double EvIDSDR1muNaI, EdepSDR1muNaI;
		 mufSciDR1NaI >> EvIDSDR1muNaI >> EdepSDR1muNaI;
		 vEvIDSDR1muNaI.push_back(EvIDSDR1muNaI);
		 vEdepSDR1muNaI.push_back(EdepSDR1muNaI);
	  }
	  vEvIDSDR1muNaI.pop_back(); vEdepSDR1muNaI.pop_back();
	  vEvIDSDR1muNaI.pop_back(); vEdepSDR1muNaI.pop_back();
			  
	  mufSciDR1NaI.close();
	  allvEvIDSDR1muNaI.push_back(vEvIDSDR1muNaI);
	  allvEdepSDR1muNaI.push_back(vEdepSDR1muNaI);


	  // SciDT2muNaI
	  std::ifstream mufSciDT2NaI(TString(mufiles[(k*26)+7]));
	  std::vector<double> vEvIDSDT2muNaI;
	  std::vector<double> vEdepSDT2muNaI;
			  
	  while (!mufSciDT2NaI.eof()) {
	     double EvIDSDT2muNaI, EdepSDT2muNaI;
		 mufSciDT2NaI >> EvIDSDT2muNaI >> EdepSDT2muNaI;
		 vEvIDSDT2muNaI.push_back(EvIDSDT2muNaI);
		 vEdepSDT2muNaI.push_back(EdepSDT2muNaI);
	  }
	  vEvIDSDT2muNaI.pop_back(); vEdepSDT2muNaI.pop_back();
	  vEvIDSDT2muNaI.pop_back(); vEdepSDT2muNaI.pop_back();
			  
	  mufSciDT2NaI.close();
	  allvEvIDSDT2muNaI.push_back(vEvIDSDT2muNaI);
	  allvEdepSDT2muNaI.push_back(vEdepSDT2muNaI);


	  // SciDB2muNaI
	  std::ifstream mufSciDB2NaI(TString(mufiles[(k*26)+8]));
	  std::vector<double> vEvIDSDB2muNaI;
	  std::vector<double> vEdepSDB2muNaI;
			  
	  while (!mufSciDB2NaI.eof()) {
	     double EvIDSDB2muNaI, EdepSDB2muNaI;
		 mufSciDB2NaI >> EvIDSDB2muNaI >> EdepSDB2muNaI;
		 vEvIDSDB2muNaI.push_back(EvIDSDB2muNaI);
		 vEdepSDB2muNaI.push_back(EdepSDB2muNaI);
	  }
	  vEvIDSDB2muNaI.pop_back(); vEdepSDB2muNaI.pop_back();
	  vEvIDSDB2muNaI.pop_back(); vEdepSDB2muNaI.pop_back();
			  
	  mufSciDB2NaI.close();
	  allvEvIDSDB2muNaI.push_back(vEvIDSDB2muNaI);
	  allvEdepSDB2muNaI.push_back(vEdepSDB2muNaI);


	  // SciDL2muNaI
	  std::ifstream mufSciDL2NaI(TString(mufiles[(k*26)+9]));
	  std::vector<double> vEvIDSDL2muNaI;
	  std::vector<double> vEdepSDL2muNaI;
			  
	  while (!mufSciDL2NaI.eof()) {
	     double EvIDSDL2muNaI, EdepSDL2muNaI;
		 mufSciDL2NaI >> EvIDSDL2muNaI >> EdepSDL2muNaI;
		 vEvIDSDL2muNaI.push_back(EvIDSDL2muNaI);
		 vEdepSDL2muNaI.push_back(EdepSDL2muNaI);
	  }
	  vEvIDSDL2muNaI.pop_back(); vEdepSDL2muNaI.pop_back();
	  vEvIDSDL2muNaI.pop_back(); vEdepSDL2muNaI.pop_back();
			  
	  mufSciDL2NaI.close();
	  allvEvIDSDL2muNaI.push_back(vEvIDSDL2muNaI);
	  allvEdepSDL2muNaI.push_back(vEdepSDL2muNaI);


	  // SciDR2muNaI
	  std::ifstream mufSciDR2NaI(TString(mufiles[(k*26)+10]));
	  std::vector<double> vEvIDSDR2muNaI;
	  std::vector<double> vEdepSDR2muNaI;
			  
	  while (!mufSciDR2NaI.eof()) {
	     double EvIDSDR2muNaI, EdepSDR2muNaI;
		 mufSciDR2NaI >> EvIDSDR2muNaI >> EdepSDR2muNaI;
		 vEvIDSDR2muNaI.push_back(EvIDSDR2muNaI);
		 vEdepSDR2muNaI.push_back(EdepSDR2muNaI);
	  }
	  vEvIDSDR2muNaI.pop_back(); vEdepSDR2muNaI.pop_back();
	  vEvIDSDR2muNaI.pop_back(); vEdepSDR2muNaI.pop_back();
			  
	  mufSciDR2NaI.close();
	  allvEvIDSDR2muNaI.push_back(vEvIDSDR2muNaI);
	  allvEdepSDR2muNaI.push_back(vEdepSDR2muNaI);


	  // BGOD1muNaI
	  std::ifstream mufBGOD1NaI(TString(mufiles[(k*26)+11]));
	  std::vector<double> vEvIDBD1muNaI;
	  std::vector<double> vEdepBD1muNaI;
			  
	  while (!mufBGOD1NaI.eof()) {
	     double EvIDBD1muNaI, EdepBD1muNaI;
		 mufBGOD1NaI >> EvIDBD1muNaI >> EdepBD1muNaI;
		 vEvIDBD1muNaI.push_back(EvIDBD1muNaI);
		 vEdepBD1muNaI.push_back(EdepBD1muNaI);
	  }
	  vEvIDBD1muNaI.pop_back(); vEdepBD1muNaI.pop_back();
	  vEvIDBD1muNaI.pop_back(); vEdepBD1muNaI.pop_back();
			  
	  mufBGOD1NaI.close();
	  allvEvIDBD1muNaI.push_back(vEvIDBD1muNaI);
	  allvEdepBD1muNaI.push_back(vEdepBD1muNaI);


	  // BGOD2muNaI
	  std::ifstream mufBGOD2NaI(TString(mufiles[(k*26)+12]));
	  std::vector<double> vEvIDBD2muNaI;
	  std::vector<double> vEdepBD2muNaI;
			  
	  while (!mufBGOD2NaI.eof()) {
	     double EvIDBD2muNaI, EdepBD2muNaI;
		 mufBGOD2NaI >> EvIDBD2muNaI >> EdepBD2muNaI;
		 vEvIDBD2muNaI.push_back(EvIDBD2muNaI);
		 vEdepBD2muNaI.push_back(EdepBD2muNaI);
	  }
	  vEvIDBD2muNaI.pop_back(); vEdepBD2muNaI.pop_back();
	  vEvIDBD2muNaI.pop_back(); vEdepBD2muNaI.pop_back();
			  
	  mufBGOD2NaI.close();
	  allvEvIDBD2muNaI.push_back(vEvIDBD2muNaI);
	  allvEdepBD2muNaI.push_back(vEdepBD2muNaI);


      // SciD1muSci
	  std::ifstream mufSciD1Sci(TString(mufiles[(k*26)+13]));
	  std::vector<double> vEvIDSD1muSci;
	  std::vector<double> vEdepSD1muSci;
			  
	  while (!mufSciD1Sci.eof()) {
	     double EvIDSD1muSci, EdepSD1muSci;
		 mufSciD1Sci >> EvIDSD1muSci >> EdepSD1muSci;
		 vEvIDSD1muSci.push_back(EvIDSD1muSci);
		 vEdepSD1muSci.push_back(EdepSD1muSci);
	  }
	  vEvIDSD1muSci.pop_back(); vEdepSD1muSci.pop_back();
	  vEvIDSD1muSci.pop_back(); vEdepSD1muSci.pop_back();
			  
	  mufSciD1Sci.close();
	  allvEvIDSD1muSci.push_back(vEvIDSD1muSci);
	  allvEdepSD1muSci.push_back(vEdepSD1muSci);


	  // SciD2muSci
	  std::ifstream mufSciD2Sci(TString(mufiles[(k*26)+14]));
	  std::vector<double> vEvIDSD2muSci;
	  std::vector<double> vEdepSD2muSci;
			  
	  while (!mufSciD2Sci.eof()) {
	     double EvIDSD2muSci, EdepSD2muSci;
		 mufSciD2Sci >> EvIDSD2muSci >> EdepSD2muSci;
		 vEvIDSD2muSci.push_back(EvIDSD2muSci);
		 vEdepSD2muSci.push_back(EdepSD2muSci);
	  }
	  vEvIDSD2muSci.pop_back(); vEdepSD2muSci.pop_back();
	  vEvIDSD2muSci.pop_back(); vEdepSD2muSci.pop_back();
			  
	  mufSciD2Sci.close();
	  allvEvIDSD2muSci.push_back(vEvIDSD2muSci);
	  allvEdepSD2muSci.push_back(vEdepSD2muSci);


	  // SciD3muSci
	  std::ifstream mufSciD3Sci(TString(mufiles[(k*26)+15]));
	  std::vector<double> vEvIDSD3muSci;
	  std::vector<double> vEdepSD3muSci;
			  
	  while (!mufSciD3Sci.eof()) {
	     double EvIDSD3muSci, EdepSD3muSci;
		 mufSciD3Sci >> EvIDSD3muSci >> EdepSD3muSci;
		 vEvIDSD3muSci.push_back(EvIDSD3muSci);
		 vEdepSD3muSci.push_back(EdepSD3muSci);
	  }
	  vEvIDSD3muSci.pop_back(); vEdepSD3muSci.pop_back();
	  vEvIDSD3muSci.pop_back(); vEdepSD3muSci.pop_back();
			  
	  mufSciD3Sci.close();
	  allvEvIDSD3muSci.push_back(vEvIDSD3muSci);
	  allvEdepSD3muSci.push_back(vEdepSD3muSci);
			  
	 		  
	  // SciDT1muSci
	  std::ifstream mufSciDT1Sci(TString(mufiles[(k*26)+16]));
	  std::vector<double> vEvIDSDT1muSci;
	  std::vector<double> vEdepSDT1muSci;
			  
	  while (!mufSciDT1Sci.eof()) {
	     double EvIDSDT1muSci, EdepSDT1muSci;
		 mufSciDT1Sci >> EvIDSDT1muSci >> EdepSDT1muSci;
		 vEvIDSDT1muSci.push_back(EvIDSDT1muSci);
		 vEdepSDT1muSci.push_back(EdepSDT1muSci);
	  }
	  vEvIDSDT1muSci.pop_back(); vEdepSDT1muSci.pop_back();
	  vEvIDSDT1muSci.pop_back(); vEdepSDT1muSci.pop_back();
			  
	  mufSciDT1Sci.close();
	  allvEvIDSDT1muSci.push_back(vEvIDSDT1muSci);
	  allvEdepSDT1muSci.push_back(vEdepSDT1muSci);


	  // SciDB1muSci
	  std::ifstream mufSciDB1Sci(TString(mufiles[(k*26)+17]));
	  std::vector<double> vEvIDSDB1muSci;
	  std::vector<double> vEdepSDB1muSci;
			  
	  while (!mufSciDB1Sci.eof()) {
	     double EvIDSDB1muSci, EdepSDB1muSci;
		 mufSciDB1Sci >> EvIDSDB1muSci >> EdepSDB1muSci;
		 vEvIDSDB1muSci.push_back(EvIDSDB1muSci);
		 vEdepSDB1muSci.push_back(EdepSDB1muSci);
	  }
	  vEvIDSDB1muSci.pop_back(); vEdepSDB1muSci.pop_back();
	  vEvIDSDB1muSci.pop_back(); vEdepSDB1muSci.pop_back();
			  
	  mufSciDB1Sci.close();
	  allvEvIDSDB1muSci.push_back(vEvIDSDB1muSci);
	  allvEdepSDB1muSci.push_back(vEdepSDB1muSci);


	  // SciDL1muSci
	  std::ifstream mufSciDL1Sci(TString(mufiles[(k*26)+18]));
	  std::vector<double> vEvIDSDL1muSci;
	  std::vector<double> vEdepSDL1muSci;
			  
	  while (!mufSciDL1Sci.eof()) {
	     double EvIDSDL1muSci, EdepSDL1muSci;
		 mufSciDL1Sci >> EvIDSDL1muSci >> EdepSDL1muSci;
		 vEvIDSDL1muSci.push_back(EvIDSDL1muSci);
		 vEdepSDL1muSci.push_back(EdepSDL1muSci);
	  }
	  vEvIDSDL1muSci.pop_back(); vEdepSDL1muSci.pop_back();
	  vEvIDSDL1muSci.pop_back(); vEdepSDL1muSci.pop_back();
			  
	  mufSciDL1Sci.close();
	  allvEvIDSDL1muSci.push_back(vEvIDSDL1muSci);
	  allvEdepSDL1muSci.push_back(vEdepSDL1muSci);


	  // SciDR1muSci
	  std::ifstream mufSciDR1Sci(TString(mufiles[(k*26)+19]));
	  std::vector<double> vEvIDSDR1muSci;
	  std::vector<double> vEdepSDR1muSci;
			  
	  while (!mufSciDR1Sci.eof()) {
	     double EvIDSDR1muSci, EdepSDR1muSci;
		 mufSciDR1Sci >> EvIDSDR1muSci >> EdepSDR1muSci;
		 vEvIDSDR1muSci.push_back(EvIDSDR1muSci);
		 vEdepSDR1muSci.push_back(EdepSDR1muSci);
	  }
	  vEvIDSDR1muSci.pop_back(); vEdepSDR1muSci.pop_back();
	  vEvIDSDR1muSci.pop_back(); vEdepSDR1muSci.pop_back();
			  
	  mufSciDR1Sci.close();
	  allvEvIDSDR1muSci.push_back(vEvIDSDR1muSci);
	  allvEdepSDR1muSci.push_back(vEdepSDR1muSci);


	  // SciDT2muSci
	  std::ifstream mufSciDT2Sci(TString(mufiles[(k*26)+20]));
	  std::vector<double> vEvIDSDT2muSci;
	  std::vector<double> vEdepSDT2muSci;
			  
	  while (!mufSciDT2Sci.eof()) {
	     double EvIDSDT2muSci, EdepSDT2muSci;
		 mufSciDT2Sci >> EvIDSDT2muSci >> EdepSDT2muSci;
		 vEvIDSDT2muSci.push_back(EvIDSDT2muSci);
		 vEdepSDT2muSci.push_back(EdepSDT2muSci);
	  }
	  vEvIDSDT2muSci.pop_back(); vEdepSDT2muSci.pop_back();
	  vEvIDSDT2muSci.pop_back(); vEdepSDT2muSci.pop_back();
			  
	  mufSciDT2Sci.close();
	  allvEvIDSDT2muSci.push_back(vEvIDSDT2muSci);
	  allvEdepSDT2muSci.push_back(vEdepSDT2muSci);


	  // SciDB2muSci
	  std::ifstream mufSciDB2Sci(TString(mufiles[(k*26)+21]));
	  std::vector<double> vEvIDSDB2muSci;
	  std::vector<double> vEdepSDB2muSci;
			  
	  while (!mufSciDB2Sci.eof()) {
	     double EvIDSDB2muSci, EdepSDB2muSci;
		 mufSciDB2Sci >> EvIDSDB2muSci >> EdepSDB2muSci;
		 vEvIDSDB2muSci.push_back(EvIDSDB2muSci);
		 vEdepSDB2muSci.push_back(EdepSDB2muSci);
	  }
	  vEvIDSDB2muSci.pop_back(); vEdepSDB2muSci.pop_back();
	  vEvIDSDB2muSci.pop_back(); vEdepSDB2muSci.pop_back();
			  
	  mufSciDB2Sci.close();
	  allvEvIDSDB2muSci.push_back(vEvIDSDB2muSci);
	  allvEdepSDB2muSci.push_back(vEdepSDB2muSci);


	  // SciDL2muSci
	  std::ifstream mufSciDL2Sci(TString(mufiles[(k*26)+22]));
	  std::vector<double> vEvIDSDL2muSci;
	  std::vector<double> vEdepSDL2muSci;
			  
	  while (!mufSciDL2Sci.eof()) {
	     double EvIDSDL2muSci, EdepSDL2muSci;
		 mufSciDL2Sci >> EvIDSDL2muSci >> EdepSDL2muSci;
		 vEvIDSDL2muSci.push_back(EvIDSDL2muSci);
		 vEdepSDL2muSci.push_back(EdepSDL2muSci);
	  }
	  vEvIDSDL2muSci.pop_back(); vEdepSDL2muSci.pop_back();
	  vEvIDSDL2muSci.pop_back(); vEdepSDL2muSci.pop_back();
			  
	  mufSciDL2Sci.close();
	  allvEvIDSDL2muSci.push_back(vEvIDSDL2muSci);
	  allvEdepSDL2muSci.push_back(vEdepSDL2muSci);


	  // SciDR2muSci
	  std::ifstream mufSciDR2Sci(TString(mufiles[(k*26)+23]));
	  std::vector<double> vEvIDSDR2muSci;
	  std::vector<double> vEdepSDR2muSci;
			  
	  while (!mufSciDR2Sci.eof()) {
	     double EvIDSDR2muSci, EdepSDR2muSci;
		 mufSciDR2Sci >> EvIDSDR2muSci >> EdepSDR2muSci;
		 vEvIDSDR2muSci.push_back(EvIDSDR2muSci);
		 vEdepSDR2muSci.push_back(EdepSDR2muSci);
	  }
	  vEvIDSDR2muSci.pop_back(); vEdepSDR2muSci.pop_back();
	  vEvIDSDR2muSci.pop_back(); vEdepSDR2muSci.pop_back();
			  
	  mufSciDR2Sci.close();
	  allvEvIDSDR2muSci.push_back(vEvIDSDR2muSci);
	  allvEdepSDR2muSci.push_back(vEdepSDR2muSci);


	  // BGOD1muSci
	  std::ifstream mufBGOD1Sci(TString(mufiles[(k*26)+24]));
	  std::vector<double> vEvIDBD1muSci;
	  std::vector<double> vEdepBD1muSci;
			  
	  while (!mufBGOD1Sci.eof()) {
	     double EvIDBD1muSci, EdepBD1muSci;
		 mufBGOD1Sci >> EvIDBD1muSci >> EdepBD1muSci;
		 vEvIDBD1muSci.push_back(EvIDBD1muSci);
		 vEdepBD1muSci.push_back(EdepBD1muSci);
	  }
	  vEvIDBD1muSci.pop_back(); vEdepBD1muSci.pop_back();
	  vEvIDBD1muSci.pop_back(); vEdepBD1muSci.pop_back();
			  
	  mufBGOD1Sci.close();
	  allvEvIDBD1muSci.push_back(vEvIDBD1muSci);
	  allvEdepBD1muSci.push_back(vEdepBD1muSci);


	  // BGOD2muSci
	  std::ifstream mufBGOD2Sci(TString(mufiles[(k*26)+25]));
	  std::vector<double> vEvIDBD2muSci;
	  std::vector<double> vEdepBD2muSci;
			  
	  while (!mufBGOD2Sci.eof()) {
	     double EvIDBD2muSci, EdepBD2muSci;
		 mufBGOD2Sci >> EvIDBD2muSci >> EdepBD2muSci;
		 vEvIDBD2muSci.push_back(EvIDBD2muSci);
		 vEdepBD2muSci.push_back(EdepBD2muSci);
	  }
	  vEvIDBD2muSci.pop_back(); vEdepBD2muSci.pop_back();
	  vEvIDBD2muSci.pop_back(); vEdepBD2muSci.pop_back();
			  
	  mufBGOD2Sci.close();
	  allvEvIDBD2muSci.push_back(vEvIDBD2muSci);
	  allvEdepBD2muSci.push_back(vEdepBD2muSci);

   }  

		
   //-------------------------------------------------------------------
   //                     Bin-by-bin analysis
   //                          Mu-decay
   //-------------------------------------------------------------------     
			
   // X-ray cascade	  
   for (int i=0; i<allvEvIDBD1muNaI.size(); i++) {
      
      std::cout << std::endl;
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m--------------------- X-ray cascade ----------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

      for (int m=0; m<nsamps; m++) {

	     Ethr = Ethrmu[m];

		 //--------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade with NaI
		 //-------------------------------------------------- 
		 XXrayN2NaI = 0; XelecN2NaI = 0;
			  
		 for (int a=0; a<allvEvIDBD1xNaI[0].size(); a++) {

		    if ((allvEdepSD1xNaI[i][a] < Ethr1) && (allvEdepSD2xNaI[i][a] < Ethr1) && (allvEdepSD3xNaI[i][a] < Ethr1)) {
		       if ((allvEdepBD1xNaI[i][a] > Ethr) && (allvEdepBD1xNaI[i][a] < Ethr22) && (allvEdepBD2xNaI[i][a] > Ethr) && (allvEdepBD2xNaI[i][a] < Ethr22)) {
//			      if (((allvEdepSDT1xNaI[i][a] < Ethr3) || (allvEdepSDB1xNaI[i][a] < Ethr3) || (allvEdepSDL1xNaI[i][a] < Ethr3) || (allvEdepSDR1xNaI[i][a] < Ethr3)) && ((allvEdepSDT2xNaI[i][a] < Ethr3) || (allvEdepSDB2xNaI[i][a] < Ethr3) || (allvEdepSDL2xNaI[i][a] < Ethr3) || (allvEdepSDR2xNaI[i][a] < Ethr3))) {
                  if (((allvEdepSDT1xNaI[i][a] < Ethr3) && (allvEdepSDB1xNaI[i][a] < Ethr3) && (allvEdepSDL1xNaI[i][a] < Ethr3) && (allvEdepSDR1xNaI[i][a] < Ethr3)) && ((allvEdepSDT2xNaI[i][a] < Ethr3) && (allvEdepSDB2xNaI[i][a] < Ethr3) && (allvEdepSDL2xNaI[i][a] < Ethr3) && (allvEdepSDR2xNaI[i][a] < Ethr3))) {
				     XXrayN2NaI += 1;
				  } else { XelecN2NaI += 1; }
			   } else { XelecN2NaI += 1; }
			} else { XelecN2NaI += 1; }
		 }
				 
		 PXXvectorN2NaI[i][m] = XXrayN2NaI/(double)(counterXXN2);
		 PXevectorN2NaI[i][m] = XelecN2NaI/(double)(counterXXN2); 
				

		 //--------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade with Sci
		 //-------------------------------------------------- 
		 XXrayN2Sci = 0; XelecN2Sci = 0;
			  
		 for (int a=0; a<allvEvIDBD1xSci[0].size(); a++) {

		    if ((allvEdepSD1xSci[i][a] < Ethr1) && (allvEdepSD2xSci[i][a] < Ethr1) && (allvEdepSD3xSci[i][a] < Ethr1)) {
			   if ((allvEdepBD1xSci[i][a] > Ethr) && (allvEdepBD1xSci[i][a] < Ethr22) && (allvEdepBD2xSci[i][a] > Ethr) && (allvEdepBD2xSci[i][a] < Ethr22)) {
//			      if (((allvEdepSDT1xSci[i][a] < Ethr3) || (allvEdepSDB1xSci[i][a] < Ethr3) || (allvEdepSDL1xSci[i][a] < Ethr3) || (allvEdepSDR1xSci[i][a] < Ethr3)) && ((allvEdepSDT2xSci[i][a] < Ethr3) || (allvEdepSDB2xSci[i][a] < Ethr3) || (allvEdepSDL2xSci[i][a] < Ethr3) || (allvEdepSDR2xSci[i][a] < Ethr3))) {
			      if (((allvEdepSDT1xSci[i][a] < Ethr3) && (allvEdepSDB1xSci[i][a] < Ethr3) && (allvEdepSDL1xSci[i][a] < Ethr3) && (allvEdepSDR1xSci[i][a] < Ethr3)) && ((allvEdepSDT2xSci[i][a] < Ethr3) && (allvEdepSDB2xSci[i][a] < Ethr3) && (allvEdepSDL2xSci[i][a] < Ethr3) && (allvEdepSDR2xSci[i][a] < Ethr3))) {
				     XXrayN2Sci += 1;
				  } else { XelecN2Sci += 1; }
			   } else { XelecN2Sci += 1; }
		    } else { XelecN2Sci += 1; }
		 }
				 
		 PXXvectorN2Sci[i][m] = XXrayN2Sci/(double)(counterXXN2);
		 PXevectorN2Sci[i][m] = XelecN2Sci/(double)(counterXXN2); 
				

		 //--------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay with NaI
		 //-------------------------------------------------- 
		 eXrayN2NaI = 0; eelecN2NaI = 0;
			  
		 for (int a=0; a<allvEvIDBD1muNaI[0].size(); a++) {

		    if ((allvEdepSD1muNaI[i][a] < Ethr1) && (allvEdepSD2muNaI[i][a] < Ethr1) && (allvEdepSD3muNaI[i][a] < Ethr1)) {
		       if ((allvEdepBD1muNaI[i][a] > Ethr) && (allvEdepBD1muNaI[i][a] < Ethr22) && (allvEdepBD2muNaI[i][a] > Ethr) && (allvEdepBD2muNaI[i][a] < Ethr22)) {
//			      if (((allvEdepSDT1muNaI[i][a] < Ethr3) || (allvEdepSDB1muNaI[i][a] < Ethr3) || (allvEdepSDL1muNaI[i][a] < Ethr3) || (allvEdepSDR1muNaI[i][a] < Ethr3)) && ((allvEdepSDT2muNaI[i][a] < Ethr3) || (allvEdepSDB2muNaI[i][a] < Ethr3) || (allvEdepSDL2muNaI[i][a] < Ethr3) || (allvEdepSDR2muNaI[i][a] < Ethr3))) {
			      if (((allvEdepSDT1muNaI[i][a] < Ethr3) && (allvEdepSDB1muNaI[i][a] < Ethr3) && (allvEdepSDL1muNaI[i][a] < Ethr3) && (allvEdepSDR1muNaI[i][a] < Ethr3)) && ((allvEdepSDT2muNaI[i][a] < Ethr3) && (allvEdepSDB2muNaI[i][a] < Ethr3) && (allvEdepSDL2muNaI[i][a] < Ethr3) && (allvEdepSDR2muNaI[i][a] < Ethr3))) {
				     eXrayN2NaI += 1;
				  } else { eelecN2NaI += 1; }
			   } else { eelecN2NaI += 1; }
		    } else { eelecN2NaI += 1; }
		 }
				 
		 PeXvectorN2NaI[i][m] = eXrayN2NaI/(double)(countereeN2);
		 PeevectorN2NaI[i][m] = eelecN2NaI/(double)(countereeN2); 


		 //--------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay with Sci
		 //-------------------------------------------------- 
		 eXrayN2Sci = 0; eelecN2Sci = 0;
			  
		 for (int a=0; a<allvEvIDBD1muSci[0].size(); a++) {

		    if ((allvEdepSD1muSci[i][a] < Ethr1) && (allvEdepSD2muSci[i][a] < Ethr1) && (allvEdepSD3muSci[i][a] < Ethr1)) {
		       if ((allvEdepBD1muSci[i][a] > Ethr) && (allvEdepBD1muSci[i][a] < Ethr22) && (allvEdepBD2muSci[i][a] > Ethr) && (allvEdepBD2muSci[i][a] < Ethr22)) {
//			      if (((allvEdepSDT1muSci[i][a] < Ethr3) || (allvEdepSDB1muSci[i][a] < Ethr3) || (allvEdepSDL1muSci[i][a] < Ethr3) || (allvEdepSDR1muSci[i][a] < Ethr3)) && ((allvEdepSDT2muSci[i][a] < Ethr3) || (allvEdepSDB2muSci[i][a] < Ethr3) || (allvEdepSDL2muSci[i][a] < Ethr3) || (allvEdepSDR2muSci[i][a] < Ethr3))) {
			      if (((allvEdepSDT1muSci[i][a] < Ethr3) && (allvEdepSDB1muSci[i][a] < Ethr3) && (allvEdepSDL1muSci[i][a] < Ethr3) && (allvEdepSDR1muSci[i][a] < Ethr3)) && ((allvEdepSDT2muSci[i][a] < Ethr3) && (allvEdepSDB2muSci[i][a] < Ethr3) && (allvEdepSDL2muSci[i][a] < Ethr3) && (allvEdepSDR2muSci[i][a] < Ethr3))) {
				     eXrayN2Sci += 1;
				  } else { eelecN2Sci += 1; }
			   } else { eelecN2Sci += 1; }
		    } else { eelecN2Sci += 1; }
		 }
				 
		 PeXvectorN2Sci[i][m] = eXrayN2Sci/(double)(countereeN2);
		 PeevectorN2Sci[i][m] = eelecN2Sci/(double)(countereeN2); 
	  
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
   float PXXarrN2NaI[nsamps] = {}; // X-ray cascade
   float PXXarrN2Sci[nsamps] = {};
   float PeXarrN2NaI[nsamps] = {};
   float PeXarrN2Sci[nsamps] = {};
   float PeXXXarrN2NaIr[nsamps] = {};
   float PeXXXarrN2Scir[nsamps] = {};
		 	   
   for (int i=0; i<nsamps; i++) {
      // Normalisation 2 [absolute]
	  PXXarrN2NaI[i] = PXXvectorN2NaI[0][i];
	  PXXarrN2Sci[i] = PXXvectorN2Sci[0][i];
	  PeXarrN2NaI[i] = PeXvectorN2NaI[0][i];
	  PeXarrN2Sci[i] = PeXvectorN2Sci[0][i];
	  PeXXXarrN2NaIr[i] = (PeXvectorN2NaI[0][i])/(double)(PXXvectorN2NaI[0][i]);
	  PeXXXarrN2Scir[i] = (PeXvectorN2Sci[0][i])/(double)(PXXvectorN2Sci[0][i]);
   }	   

		  
   TCanvas *d = new TCanvas("d","E_{THR}",800,600);
   d->Divide(3,1);
   d->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPXXN2NaI = new TGraph(nsamps,Ethrmu,PXXarrN2NaI);
   grPXXN2NaI->SetTitle("Square final setup [AND] with NaI and Sci [10^5 events]"); 
   grPXXN2NaI->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXXN2NaI->GetXaxis()->SetRangeUser(0,2.05);
   //grPXXN2NaI->GetYaxis()->SetRangeUser(3e-1,1.1);
   grPXXN2NaI->GetYaxis()->SetMoreLogLabels(1);
   grPXXN2NaI->GetYaxis()->SetTitle("P_{X->X}(E_{THR})");
   grPXXN2NaI->GetYaxis()->SetTitleOffset(1.8);
   //grPXXN2NaI->SetMarkerColor(kRed);
   //grPXXN2NaI->SetMarkerStyle(31);
   grPXXN2NaI->SetLineColor(kRed);
   grPXXN2NaI->SetLineWidth(3);
   grPXXN2NaI->Draw("ALP");
   TGraph *grPXXN2Sci = new TGraph(nsamps,Ethrmu,PXXarrN2Sci); 
   grPXXN2Sci->SetLineColor(kBlack);
   grPXXN2Sci->SetLineWidth(3);
   grPXXN2Sci->Draw("LP");
   legPXXN2 = new TLegend(0.2,-0.005,0.4,0.08);
   legPXXN2->AddEntry(grPXXN2NaI,"NaI","lp");
   legPXXN2->AddEntry(grPXXN2Sci,"Sci","lp");
   legPXXN2->Draw();

   d->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeXN2NaI = new TGraph(nsamps,Ethrmu,PeXarrN2NaI);
   grPeXN2NaI->SetTitle("Square final setup [AND] with NaI and Sci [10^5 events]");
   grPeXN2NaI->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeXN2NaI->GetXaxis()->SetRangeUser(0,2.05);
   //grPeXN2NaI->GetYaxis()->SetRangeUser(3e-1,1.1);
   grPeXN2NaI->GetYaxis()->SetMoreLogLabels(1);
   grPeXN2NaI->GetYaxis()->SetTitle("P_{X->X}(E_{THR})");
   grPeXN2NaI->GetYaxis()->SetTitleOffset(1.8);
   grPeXN2NaI->SetLineColor(kRed);
   grPeXN2NaI->SetLineWidth(3);
   grPeXN2NaI->Draw("ALP");
   TGraph *grPeXN2Sci = new TGraph(nsamps,Ethrmu,PeXarrN2Sci);
   grPeXN2Sci->SetLineColor(kBlack);
   grPeXN2Sci->SetLineWidth(3);
   grPeXN2Sci->Draw("LP");
   legPeXN2 = new TLegend(0.2,-0.005,0.4,0.08);
   legPeXN2->AddEntry(grPeXN2NaI,"NaI","lp");
   legPeXN2->AddEntry(grPeXN2Sci,"Sci","lp");
   legPeXN2->Draw(); 
    
   d->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeXXXN2NaIr = new TGraph(nsamps,Ethrmu,PeXXXarrN2NaIr);
   grPeXXXN2NaIr->SetTitle("Square final setup [AND] with NaI and Sci [10^5 events]");
   grPeXXXN2NaIr->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeXXXN2NaIr->GetXaxis()->SetRangeUser(0,2.05);
   grPeXXXN2NaIr->GetYaxis()->SetMoreLogLabels(1);
   grPeXXXN2NaIr->GetYaxis()->SetTitle("#frac{P_{e->X}}{P_{X->X}}(E_{THR})");
   grPeXXXN2NaIr->GetYaxis()->SetTitleOffset(1.7);
   grPeXXXN2NaIr->SetLineColor(kRed);
   grPeXXXN2NaIr->SetLineWidth(3);
   grPeXXXN2NaIr->Draw("ALP");
   TGraph *grPeXXXN2Scir = new TGraph(nsamps,Ethrmu,PeXXXarrN2Scir);
   grPeXXXN2Scir->SetLineColor(kBlack);
   grPeXXXN2Scir->SetLineWidth(3);
   grPeXXXN2Scir->Draw("LP");
   legPeXXXN2r = new TLegend(0.2,-0.005,0.4,0.08);
   legPeXXXN2r->AddEntry(grPeXXXN2NaIr,"NaI","lp");
   legPeXXXN2r->AddEntry(grPeXXXN2Scir,"Sci","lp");
   legPeXXXN2r->Draw();

   d->SaveAs("FinalSquare_NaI_vs_Sci_AND_MULTIplicities_eff.pdf");
   d->SaveAs("FinalSquare_NaI_vs_Sci_AND_MULTIplicities_eff.png");
   d->SaveAs("FinalSquare_NaI_vs_Sci_AND_MULTIplicities_eff.C");



 
} 
 
 int main() {
   finalsquareMULTIeff();
   return 0;
}  
