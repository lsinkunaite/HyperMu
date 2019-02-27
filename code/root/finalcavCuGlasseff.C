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
#include "TPaveStats.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TText.h"

void finalcavCuGlasseff(){

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
   std::string dB = "10";

   // Names of the files
   // X-ray cascade
   std::string filexSciD1 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_SciD1.txt";
   std::string filexSciD2 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_SciD2.txt";
   std::string filexSciD3 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_SciD3.txt";
   std::string filexSciDS1 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_SciDS1.txt";
   std::string filexSciDS2 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_SciDS2.txt";
   std::string filexBGOD1 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD2 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_BGOD2.txt";
   std::string filexSciVeto = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_SciVeto.txt";

   // X-ray cascade
   std::string filex2SciD1 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_SciD1.txt";
   std::string filex2SciD2 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_SciD2.txt";
   std::string filex2SciD3 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_SciD3.txt";
   std::string filex2SciDS1 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_SciDS1.txt";
   std::string filex2SciDS2 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_SciDS2.txt";
   std::string filex2BGOD1 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_BGOD1.txt";
   std::string filex2BGOD2 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_BGOD2.txt";
   std::string filex2SciVeto = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5goldcascade_SciVeto.txt";


   // Mu-decay
   std::string filemuSciD1 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_SciD1.txt";
   std::string filemuSciD2 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_SciD2.txt";
   std::string filemuSciD3 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_SciD3.txt";
   std::string filemuSciDS1 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_SciDS1.txt";
   std::string filemuSciDS2 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_SciDS2.txt";
   std::string filemuBGOD1 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD2 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_BGOD2.txt";
   std::string filemuSciVeto = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_SciVeto.txt";

   std::string filemu2SciD1 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_SciD1.txt";
   std::string filemu2SciD2 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_SciD2.txt";
   std::string filemu2SciD3 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_SciD3.txt";
   std::string filemu2SciDS1 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_SciDS1.txt";
   std::string filemu2SciDS2 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_SciDS2.txt";
   std::string filemu2BGOD1 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_BGOD1.txt";
   std::string filemu2BGOD2 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_BGOD2.txt";
   std::string filemu2SciVeto = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_1e5mudecay_SciVeto.txt";



   // Vectors with filenames   
   std::vector<std::string> Xfiles;
   std::vector<std::string> mufiles;

   // X-ray cascade		 
   Xfiles.push_back(filexSciD1);
   Xfiles.push_back(filexSciD2);
   Xfiles.push_back(filexSciD3);
   Xfiles.push_back(filexSciDS1);
   Xfiles.push_back(filexSciDS2);
   Xfiles.push_back(filexBGOD1);
   Xfiles.push_back(filexBGOD2);
   Xfiles.push_back(filexSciVeto);

   Xfiles.push_back(filex2SciD1);
   Xfiles.push_back(filex2SciD2);
   Xfiles.push_back(filex2SciD3);
   Xfiles.push_back(filex2SciDS1);
   Xfiles.push_back(filex2SciDS2);
   Xfiles.push_back(filex2BGOD1);
   Xfiles.push_back(filex2BGOD2);
   Xfiles.push_back(filex2SciVeto);

   // Mu-decay
   mufiles.push_back(filemuSciD1);
   mufiles.push_back(filemuSciD2);
   mufiles.push_back(filemuSciD3);
   mufiles.push_back(filemuSciDS1);
   mufiles.push_back(filemuSciDS2);
   mufiles.push_back(filemuBGOD1);
   mufiles.push_back(filemuBGOD2);
   mufiles.push_back(filemuSciVeto);

   mufiles.push_back(filemu2SciD1);
   mufiles.push_back(filemu2SciD2);
   mufiles.push_back(filemu2SciD3);
   mufiles.push_back(filemu2SciDS1);
   mufiles.push_back(filemu2SciDS2);
   mufiles.push_back(filemu2BGOD1);
   mufiles.push_back(filemu2BGOD2);
   mufiles.push_back(filemu2SciVeto);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep, EventID;
   float iEventID;

   float Ethr1 = 1.65;
   float Ethr12 = 1.6;
   float Ethr13 = 1.55;
   float Ethr21 = 0.5;
   float Ethr22 = 10;
   float Ethr3 = 1;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
   
   std::stringstream Ethr1str;
   std::stringstream Ethr12str;
   std::stringstream Ethr13str;
   
   Ethr1str << Ethr1;
   Ethr12str << Ethr12;
   Ethr13str << Ethr13;
		   
   // Storage vectors
   // Normalisation 2 [abs = total] :: X-ray cascade [Cu] Ethr1=0.5 MeV
   std::vector< std::vector<double> > PXevector(Xfiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector(Xfiles.size()/16,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector(Xfiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector(Xfiles.size()/16,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [glass] Ethr1=0.5 MeV
   std::vector< std::vector<double> > PXevector2(Xfiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2(Xfiles.size()/16,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector2(Xfiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2(Xfiles.size()/16,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [Cu] Ethr1=0.7 MeV
   std::vector< std::vector<double> > PXevector3(Xfiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector3(Xfiles.size()/16,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector3(Xfiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector3(Xfiles.size()/16,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [glass] Ethr1=0.7 MeV
   std::vector< std::vector<double> > PXevector4(Xfiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector4(Xfiles.size()/16,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector4(Xfiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector4(Xfiles.size()/16,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [Cu] Ethr1=0.3 MeV
   std::vector< std::vector<double> > PXevector5(Xfiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector5(Xfiles.size()/16,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector5(Xfiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector5(Xfiles.size()/16,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [glass] Ethr1=0.3 MeV
   std::vector< std::vector<double> > PXevector6(Xfiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector6(Xfiles.size()/16,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector6(Xfiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector6(Xfiles.size()/16,std::vector<double>(nsamps));      



   // Normalisation 2 [abs = total] :: Mu-decay [Cu] Ethr1=0.5 MeV
   std::vector< std::vector<double> > Peevector(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector(mufiles.size()/16,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector(mufiles.size()/16,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [glass] Ethr1=0.5 MeV
   std::vector< std::vector<double> > Peevector2(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2(mufiles.size()/16,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector2(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2(mufiles.size()/16,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [Cu] Ethr1=0.7 MeV
   std::vector< std::vector<double> > Peevector3(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector3(mufiles.size()/16,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector3(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector3(mufiles.size()/16,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [glass] Ethr1=0.7 MeV
   std::vector< std::vector<double> > Peevector4(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector4(mufiles.size()/16,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector4(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector4(mufiles.size()/16,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [Cu] Ethr1=0.3 MeV
   std::vector< std::vector<double> > Peevector5(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector5(mufiles.size()/16,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector5(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector5(mufiles.size()/16,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [glass] Ethr1=0.3 MeV
   std::vector< std::vector<double> > Peevector6(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector6(mufiles.size()/16,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector6(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector6(mufiles.size()/16,std::vector<double>(nsamps));      


   // X-ray cascade
   std::vector< std::vector< double > > allvEvIDSD1x;
   std::vector< std::vector< double > > allvEdepSD1x;
   std::vector< std::vector< double > > allvEvIDSD2x;
   std::vector< std::vector< double > > allvEdepSD2x;
   std::vector< std::vector< double > > allvEvIDSD3x;
   std::vector< std::vector< double > > allvEdepSD3x;
   std::vector< std::vector< double > > allvEvIDSDS1x;
   std::vector< std::vector< double > > allvEdepSDS1x;
   std::vector< std::vector< double > > allvEvIDSDS2x;
   std::vector< std::vector< double > > allvEdepSDS2x;
   std::vector< std::vector< double > > allvEvIDBD1x;
   std::vector< std::vector< double > > allvEdepBD1x;
   std::vector< std::vector< double > > allvEvIDBD2x;
   std::vector< std::vector< double > > allvEdepBD2x;
   std::vector< std::vector< double > > allvEvIDSVx;
   std::vector< std::vector< double > > allvEdepSVx;

   std::vector< std::vector< double > > allvEvIDSD1x2;
   std::vector< std::vector< double > > allvEdepSD1x2;
   std::vector< std::vector< double > > allvEvIDSD2x2;
   std::vector< std::vector< double > > allvEdepSD2x2;
   std::vector< std::vector< double > > allvEvIDSD3x2;
   std::vector< std::vector< double > > allvEdepSD3x2;
   std::vector< std::vector< double > > allvEvIDSDS1x2;
   std::vector< std::vector< double > > allvEdepSDS1x2;
   std::vector< std::vector< double > > allvEvIDSDS2x2;
   std::vector< std::vector< double > > allvEdepSDS2x2;
   std::vector< std::vector< double > > allvEvIDBD1x2;
   std::vector< std::vector< double > > allvEdepBD1x2;
   std::vector< std::vector< double > > allvEvIDBD2x2;
   std::vector< std::vector< double > > allvEdepBD2x2;
   std::vector< std::vector< double > > allvEvIDSVx2;
   std::vector< std::vector< double > > allvEdepSVx2;


   // Mu-decay
   std::vector< std::vector< double > > allvEvIDSD1mu;
   std::vector< std::vector< double > > allvEdepSD1mu;
   std::vector< std::vector< double > > allvEvIDSD2mu;
   std::vector< std::vector< double > > allvEdepSD2mu;
   std::vector< std::vector< double > > allvEvIDSD3mu;
   std::vector< std::vector< double > > allvEdepSD3mu;
   std::vector< std::vector< double > > allvEvIDSDS1mu;
   std::vector< std::vector< double > > allvEdepSDS1mu;
   std::vector< std::vector< double > > allvEvIDSDS2mu;
   std::vector< std::vector< double > > allvEdepSDS2mu;
   std::vector< std::vector< double > > allvEvIDBD1mu;
   std::vector< std::vector< double > > allvEdepBD1mu;
   std::vector< std::vector< double > > allvEvIDBD2mu;
   std::vector< std::vector< double > > allvEdepBD2mu;
   std::vector< std::vector< double > > allvEvIDSVmu;
   std::vector< std::vector< double > > allvEdepSVmu;

   std::vector< std::vector< double > > allvEvIDSD1mu2;
   std::vector< std::vector< double > > allvEdepSD1mu2;
   std::vector< std::vector< double > > allvEvIDSD2mu2;
   std::vector< std::vector< double > > allvEdepSD2mu2;
   std::vector< std::vector< double > > allvEvIDSD3mu2;
   std::vector< std::vector< double > > allvEdepSD3mu2;
   std::vector< std::vector< double > > allvEvIDSDS1mu2;
   std::vector< std::vector< double > > allvEdepSDS1mu2;
   std::vector< std::vector< double > > allvEvIDSDS2mu2;
   std::vector< std::vector< double > > allvEdepSDS2mu2;
   std::vector< std::vector< double > > allvEvIDBD1mu2;
   std::vector< std::vector< double > > allvEdepBD1mu2;
   std::vector< std::vector< double > > allvEvIDBD2mu2;
   std::vector< std::vector< double > > allvEdepBD2mu2;
   std::vector< std::vector< double > > allvEvIDSVmu2;
   std::vector< std::vector< double > > allvEdepSVmu2;



   float Ethr;
   int counterXX = 1e5;
   int counteree = 1e5;
   int XXray = 0; // X-rays i-fied as X-rays
   int Xelec = 0; // X-rays i-fied as electrons
   int XXray2 = 0;
   int Xelec2 = 0;
   int XXray3 = 0;
   int Xelec3 = 0;
   int XXray4 = 0;
   int Xelec4 = 0;
   int XXray5 = 0;
   int Xelec5 = 0;
   int XXray6 = 0;
   int Xelec6 = 0;
   int eXray = 0; // Electrons i-fied as X-rays
   int eelec = 0; // Electrons i-fied as electrons
   int eXray2 = 0;
   int eelec2 = 0;	   
   int eXray3 = 0;
   int eelec3 = 0;	   
   int eXray4 = 0;
   int eelec4 = 0;	   
   int eXray5 = 0;
   int eelec5 = 0;	   
   int eXray6 = 0;
   int eelec6 = 0;	   
   	   
   Ethrmu[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;


   //-------------------------------------------------------------------
   //                           Reading
   //-------------------------------------------------------------------
		   
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m------------------- X-ray cascade ------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


   for (int k=0; k<((Xfiles.size())/16); k++) {
			  
      // SciD1
	  std::ifstream xfSciD1(TString(Xfiles[k*16]));
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
	  std::ifstream xfSciD2(TString(Xfiles[(k*16)+1]));
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
	  std::ifstream xfSciD3(TString(Xfiles[(k*16)+2]));
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
			  
			  
	  // SciDS1
	  std::ifstream xfSciDS1(TString(Xfiles[(k*16)+3]));
	  std::vector<double> vEvIDSDS1x;
	  std::vector<double> vEdepSDS1x;
			  
	  while (!xfSciDS1.eof()) {
	     double EvIDSDS1, EdepSDS1;
		 xfSciDS1 >> EvIDSDS1 >> EdepSDS1;
		 vEvIDSDS1x.push_back(EvIDSDS1);
		 vEdepSDS1x.push_back(EdepSDS1);
	  }
	  vEvIDSDS1x.pop_back(); vEdepSDS1x.pop_back();
	  vEvIDSDS1x.pop_back(); vEdepSDS1x.pop_back();
			  
	  xfSciDS1.close();
	  allvEvIDSDS1x.push_back(vEvIDSDS1x);
	  allvEdepSDS1x.push_back(vEdepSDS1x);


	  // SciDS2
	  std::ifstream xfSciDS2(TString(Xfiles[(k*16)+4]));
	  std::vector<double> vEvIDSDS2x;
	  std::vector<double> vEdepSDS2x;
			  
	  while (!xfSciDS2.eof()) {
	     double EvIDSDS2, EdepSDS2;
		 xfSciDS2 >> EvIDSDS2 >> EdepSDS2;
		 vEvIDSDS2x.push_back(EvIDSDS2);
		 vEdepSDS2x.push_back(EdepSDS2);
	  }
	  vEvIDSDS2x.pop_back(); vEdepSDS2x.pop_back();
	  vEvIDSDS2x.pop_back(); vEdepSDS2x.pop_back();
			  
	  xfSciDS2.close();
	  allvEvIDSDS2x.push_back(vEvIDSDS2x);
	  allvEdepSDS2x.push_back(vEdepSDS2x);


	  // BGOD1
	  std::ifstream xfBGOD1(TString(Xfiles[(k*16)+5]));
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
	  std::ifstream xfBGOD2(TString(Xfiles[(k*16)+6]));
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


	  // SciVeto
	  std::ifstream xfSciVeto(TString(Xfiles[(k*16)+7]));
	  std::vector<double> vEvIDSVx;
	  std::vector<double> vEdepSVx;
			  
	  while (!xfSciVeto.eof()) {
	     double EvIDSV, EdepSV;
		 xfSciVeto >> EvIDSV >> EdepSV;
		 vEvIDSVx.push_back(EvIDSV);
		 vEdepSVx.push_back(EdepSV);
	  }
	  vEvIDSVx.pop_back(); vEdepSVx.pop_back();
	  vEvIDSVx.pop_back(); vEdepSVx.pop_back();
			  
	  xfSciVeto.close();
	  allvEvIDSVx.push_back(vEvIDSVx);
	  allvEdepSVx.push_back(vEdepSVx);


      // SciD1
	  std::ifstream x2fSciD1(TString(Xfiles[(k*16)+8]));
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
	  std::ifstream x2fSciD2(TString(Xfiles[(k*16)+9]));
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
	  std::ifstream x2fSciD3(TString(Xfiles[(k*16)+10]));
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
			  
			  
	  // SciDS1
	  std::ifstream x2fSciDS1(TString(Xfiles[(k*16)+11]));
	  std::vector<double> vEvIDSDS1x2;
	  std::vector<double> vEdepSDS1x2;
			  
	  while (!x2fSciDS1.eof()) {
	     double EvIDSDS1, EdepSDS1;
		 x2fSciDS1 >> EvIDSDS1 >> EdepSDS1;
		 vEvIDSDS1x2.push_back(EvIDSDS1);
		 vEdepSDS1x2.push_back(EdepSDS1);
	  }
	  vEvIDSDS1x2.pop_back(); vEdepSDS1x2.pop_back();
	  vEvIDSDS1x2.pop_back(); vEdepSDS1x2.pop_back();
			  
	  x2fSciDS1.close();
	  allvEvIDSDS1x2.push_back(vEvIDSDS1x2);
	  allvEdepSDS1x2.push_back(vEdepSDS1x2);


	  // SciDS2
	  std::ifstream x2fSciDS2(TString(Xfiles[(k*16)+12]));
	  std::vector<double> vEvIDSDS2x2;
	  std::vector<double> vEdepSDS2x2;
			  
	  while (!x2fSciDS2.eof()) {
	     double EvIDSDS2, EdepSDS2;
		 x2fSciDS2 >> EvIDSDS2 >> EdepSDS2;
		 vEvIDSDS2x2.push_back(EvIDSDS2);
		 vEdepSDS2x2.push_back(EdepSDS2);
	  }
	  vEvIDSDS2x2.pop_back(); vEdepSDS2x2.pop_back();
	  vEvIDSDS2x2.pop_back(); vEdepSDS2x2.pop_back();
			  
	  x2fSciDS2.close();
	  allvEvIDSDS2x2.push_back(vEvIDSDS2x2);
	  allvEdepSDS2x2.push_back(vEdepSDS2x2);


	  // BGOD1
	  std::ifstream x2fBGOD1(TString(Xfiles[(k*16)+13]));
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
	  std::ifstream x2fBGOD2(TString(Xfiles[(k*16)+14]));
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


	  // SciVeto
	  std::ifstream x2fSciVeto(TString(Xfiles[(k*16)+15]));
	  std::vector<double> vEvIDSVx2;
	  std::vector<double> vEdepSVx2;
			  
	  while (!x2fSciVeto.eof()) {
	     double EvIDSV, EdepSV;
		 x2fSciVeto >> EvIDSV >> EdepSV;
		 vEvIDSVx2.push_back(EvIDSV);
		 vEdepSVx2.push_back(EdepSV);
	  }
	  vEvIDSVx2.pop_back(); vEdepSVx2.pop_back();
	  vEvIDSVx2.pop_back(); vEdepSVx2.pop_back();
			  
	  x2fSciVeto.close();
	  allvEvIDSVx2.push_back(vEvIDSVx2);
	  allvEdepSVx2.push_back(vEdepSVx2);


   }



   for (int k=0; k<((mufiles.size())/16); k++) {
   
      // SciD1mu
	  std::ifstream mufSciD1(TString(mufiles[k*16]));
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
	  std::ifstream mufSciD2(TString(mufiles[(k*16)+1]));
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
	  std::ifstream mufSciD3(TString(mufiles[(k*16)+2]));
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
			  
			  
	  // SciDS1mu
	  std::ifstream mufSciDS1(TString(mufiles[(k*16)+3]));
	  std::vector<double> vEvIDSDS1mu;
	  std::vector<double> vEdepSDS1mu;
			  
	  while (!mufSciDS1.eof()) {
	     double EvIDSDS1mu, EdepSDS1mu;
		 mufSciDS1 >> EvIDSDS1mu >> EdepSDS1mu;
		 vEvIDSDS1mu.push_back(EvIDSDS1mu);
		 vEdepSDS1mu.push_back(EdepSDS1mu);
	  }
	  vEvIDSDS1mu.pop_back(); vEdepSDS1mu.pop_back();
	  vEvIDSDS1mu.pop_back(); vEdepSDS1mu.pop_back();
			  
	  mufSciDS1.close();
	  allvEvIDSDS1mu.push_back(vEvIDSDS1mu);
	  allvEdepSDS1mu.push_back(vEdepSDS1mu);


	  // SciDS2mu
	  std::ifstream mufSciDS2(TString(mufiles[(k*16)+4]));
	  std::vector<double> vEvIDSDS2mu;
	  std::vector<double> vEdepSDS2mu;
			  
	  while (!mufSciDS2.eof()) {
	     double EvIDSDS2mu, EdepSDS2mu;
		 mufSciDS2 >> EvIDSDS2mu >> EdepSDS2mu;
		 vEvIDSDS2mu.push_back(EvIDSDS2mu);
		 vEdepSDS2mu.push_back(EdepSDS2mu);
	  }
	  vEvIDSDS2mu.pop_back(); vEdepSDS2mu.pop_back();
	  vEvIDSDS2mu.pop_back(); vEdepSDS2mu.pop_back();
			  
	  mufSciDS2.close();
	  allvEvIDSDS2mu.push_back(vEvIDSDS2mu);
	  allvEdepSDS2mu.push_back(vEdepSDS2mu);


	  // BGOD1mu
	  std::ifstream mufBGOD1(TString(mufiles[(k*16)+5]));
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
	  std::ifstream mufBGOD2(TString(mufiles[(k*16)+6]));
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


	  // SciVetomu
	  std::ifstream mufSciVeto(TString(mufiles[(k*16)+7]));
	  std::vector<double> vEvIDSVmu;
	  std::vector<double> vEdepSVmu;
			  
	  while (!mufSciVeto.eof()) {
	     double EvIDSVmu, EdepSVmu;
		 mufSciVeto >> EvIDSVmu >> EdepSVmu;
		 vEvIDSVmu.push_back(EvIDSVmu);
		 vEdepSVmu.push_back(EdepSVmu);
	  }
	  vEvIDSVmu.pop_back(); vEdepSVmu.pop_back();
	  vEvIDSVmu.pop_back(); vEdepSVmu.pop_back();
			  
	  mufSciVeto.close();
	  allvEvIDSVmu.push_back(vEvIDSVmu);
	  allvEdepSVmu.push_back(vEdepSVmu);


      // SciD1mu2
	  std::ifstream mu2fSciD1(TString(mufiles[(k*16)+8]));
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
	  std::ifstream mu2fSciD2(TString(mufiles[(k*16)+9]));
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
	  std::ifstream mu2fSciD3(TString(mufiles[(k*16)+10]));
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
			  
			  
	  // SciDS1mu
	  std::ifstream mu2fSciDS1(TString(mufiles[(k*16)+11]));
	  std::vector<double> vEvIDSDS1mu2;
	  std::vector<double> vEdepSDS1mu2;
			  
	  while (!mu2fSciDS1.eof()) {
	     double EvIDSDS1mu, EdepSDS1mu;
		 mu2fSciDS1 >> EvIDSDS1mu >> EdepSDS1mu;
		 vEvIDSDS1mu2.push_back(EvIDSDS1mu);
		 vEdepSDS1mu2.push_back(EdepSDS1mu);
	  }
	  vEvIDSDS1mu2.pop_back(); vEdepSDS1mu2.pop_back();
	  vEvIDSDS1mu2.pop_back(); vEdepSDS1mu2.pop_back();
			  
	  mu2fSciDS1.close();
	  allvEvIDSDS1mu2.push_back(vEvIDSDS1mu2);
	  allvEdepSDS1mu2.push_back(vEdepSDS1mu2);


	  // SciDS2mu
	  std::ifstream mu2fSciDS2(TString(mufiles[(k*16)+12]));
	  std::vector<double> vEvIDSDS2mu2;
	  std::vector<double> vEdepSDS2mu2;
			  
	  while (!mu2fSciDS2.eof()) {
	     double EvIDSDS2mu, EdepSDS2mu;
		 mu2fSciDS2 >> EvIDSDS2mu >> EdepSDS2mu;
		 vEvIDSDS2mu2.push_back(EvIDSDS2mu);
		 vEdepSDS2mu2.push_back(EdepSDS2mu);
	  }
	  vEvIDSDS2mu2.pop_back(); vEdepSDS2mu2.pop_back();
	  vEvIDSDS2mu2.pop_back(); vEdepSDS2mu2.pop_back();
			  
	  mu2fSciDS2.close();
	  allvEvIDSDS2mu2.push_back(vEvIDSDS2mu2);
	  allvEdepSDS2mu2.push_back(vEdepSDS2mu2);


	  // BGOD1mu
	  std::ifstream mu2fBGOD1(TString(mufiles[(k*16)+13]));
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
	  std::ifstream mu2fBGOD2(TString(mufiles[(k*16)+14]));
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


	  // SciVetomu
	  std::ifstream mu2fSciVeto(TString(mufiles[(k*16)+15]));
	  std::vector<double> vEvIDSVmu2;
	  std::vector<double> vEdepSVmu2;
			  
	  while (!mu2fSciVeto.eof()) {
	     double EvIDSVmu, EdepSVmu;
		 mu2fSciVeto >> EvIDSVmu >> EdepSVmu;
		 vEvIDSVmu2.push_back(EvIDSVmu);
		 vEdepSVmu2.push_back(EdepSVmu);
	  }
	  vEvIDSVmu2.pop_back(); vEdepSVmu2.pop_back();
	  vEvIDSVmu2.pop_back(); vEdepSVmu2.pop_back();
			  
	  mu2fSciVeto.close();
	  allvEvIDSVmu2.push_back(vEvIDSVmu2);
	  allvEdepSVmu2.push_back(vEdepSVmu2);

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

		 //--------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Cu Ethr1=0.5 MeV
		 //-------------------------------------------------------- 
		 XXray = 0; Xelec = 0;
			  
		 for (int a=0; a<allvEvIDBD1x[0].size(); a++) {

		    if ((allvEdepSD1x[i][a] < Ethr1) && (allvEdepSD2x[i][a] < Ethr1) && (allvEdepSD3x[i][a] < Ethr1)) {
			   if ((allvEdepBD1x[i][a] > Ethr) || (allvEdepBD1x[i][a] < Ethr22) && (allvEdepBD2x[i][a] > Ethr) && (allvEdepBD2x[i][a] < Ethr22)) {
			      if ((allvEdepSDS1x[i][a] < Ethr3) && (allvEdepSDS2x[i][a] < Ethr3) && (allvEdepSVx[i][a] < Ethr3)) {
				     XXray += 1;
				  } else { Xelec += 1; }
			   } else { Xelec += 1; }
		    } else { Xelec += 1; }
		 }
				 
		 PXXvector[i][m] = XXray/(double)(counterXX);
		 PXevector[i][m] = Xelec/(double)(counterXX); 


		 //-----------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Glass Ethr1=0.5 MeV
		 //----------------------------------------------------------- 
		 XXray2 = 0; Xelec2 = 0;
			  
		 for (int a=0; a<allvEvIDBD1x2[0].size(); a++) {

		    if ((allvEdepSD1x2[i][a] < Ethr1) && (allvEdepSD2x2[i][a] < Ethr1) && (allvEdepSD3x2[i][a] < Ethr1)) {
			   if ((allvEdepBD1x2[i][a] > Ethr) || (allvEdepBD1x2[i][a] < Ethr22) && (allvEdepBD2x2[i][a] > Ethr) && (allvEdepBD2x2[i][a] < Ethr22)) {
			      if ((allvEdepSDS1x2[i][a] < Ethr3) && (allvEdepSDS2x2[i][a] < Ethr3) && (allvEdepSVx2[i][a] < Ethr3)) {
				     XXray2 += 1;
				  } else { Xelec2 += 1; }
			   } else { Xelec2 += 1; }
		    } else { Xelec2 += 1; }
		 }
				 
		 PXXvector2[i][m] = XXray2/(double)(counterXX);
		 PXevector2[i][m] = Xelec2/(double)(counterXX); 


         //--------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Cu Ethr1=0.7 MeV
		 //-------------------------------------------------------- 
		 XXray3 = 0; Xelec3 = 0;
			  
		 for (int a=0; a<allvEvIDBD1x[0].size(); a++) {

		    if ((allvEdepSD1x[i][a] < Ethr12) && (allvEdepSD2x[i][a] < Ethr12) && (allvEdepSD3x[i][a] < Ethr12)) {
			   if ((allvEdepBD1x[i][a] > Ethr) || (allvEdepBD1x[i][a] < Ethr22) && (allvEdepBD2x[i][a] > Ethr) && (allvEdepBD2x[i][a] < Ethr22)) {
			      if ((allvEdepSDS1x[i][a] < Ethr3) && (allvEdepSDS2x[i][a] < Ethr3) && (allvEdepSVx[i][a] < Ethr3)) {
				     XXray3 += 1;
				  } else { Xelec3 += 1; }
			   } else { Xelec3 += 1; }
		    } else { Xelec3 += 1; }
		 }
				 
		 PXXvector3[i][m] = XXray3/(double)(counterXX);
		 PXevector3[i][m] = Xelec3/(double)(counterXX); 


		 //-----------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Glass Ethr1=0.7 MeV
		 //----------------------------------------------------------- 
		 XXray4 = 0; Xelec4 = 0;
			  
		 for (int a=0; a<allvEvIDBD1x2[0].size(); a++) {

		    if ((allvEdepSD1x2[i][a] < Ethr12) && (allvEdepSD2x2[i][a] < Ethr12) && (allvEdepSD3x2[i][a] < Ethr12)) {
			   if ((allvEdepBD1x2[i][a] > Ethr) || (allvEdepBD1x2[i][a] < Ethr22) && (allvEdepBD2x2[i][a] > Ethr) && (allvEdepBD2x2[i][a] < Ethr22)) {
			      if ((allvEdepSDS1x2[i][a] < Ethr3) && (allvEdepSDS2x2[i][a] < Ethr3) && (allvEdepSVx2[i][a] < Ethr3)) {
				     XXray4 += 1;
				  } else { Xelec4 += 1; }
			   } else { Xelec4 += 1; }
		    } else { Xelec4 += 1; }
		 }
				 
		 PXXvector4[i][m] = XXray4/(double)(counterXX);
		 PXevector4[i][m] = Xelec4/(double)(counterXX); 


         //--------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Cu Ethr1=0.3 MeV
		 //-------------------------------------------------------- 
		 XXray5 = 0; Xelec5 = 0;
			  
		 for (int a=0; a<allvEvIDBD1x[0].size(); a++) {

		    if ((allvEdepSD1x[i][a] < Ethr13) && (allvEdepSD2x[i][a] < Ethr13) && (allvEdepSD3x[i][a] < Ethr13)) {
			   if ((allvEdepBD1x[i][a] > Ethr) || (allvEdepBD1x[i][a] < Ethr22) && (allvEdepBD2x[i][a] > Ethr) && (allvEdepBD2x[i][a] < Ethr22)) {
			      if ((allvEdepSDS1x[i][a] < Ethr3) && (allvEdepSDS2x[i][a] < Ethr3) && (allvEdepSVx[i][a] < Ethr3)) {
				     XXray5 += 1;
				  } else { Xelec5 += 1; }
			   } else { Xelec5 += 1; }
		    } else { Xelec5 += 1; }
		 }
				 
		 PXXvector5[i][m] = XXray5/(double)(counterXX);
		 PXevector5[i][m] = Xelec5/(double)(counterXX); 


		 //-----------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Glass Ethr1=0.3 MeV
		 //----------------------------------------------------------- 
		 XXray6 = 0; Xelec6 = 0;
			  
		 for (int a=0; a<allvEvIDBD1x2[0].size(); a++) {

		    if ((allvEdepSD1x2[i][a] < Ethr13) && (allvEdepSD2x2[i][a] < Ethr13) && (allvEdepSD3x2[i][a] < Ethr13)) {
			   if ((allvEdepBD1x2[i][a] > Ethr) || (allvEdepBD1x2[i][a] < Ethr22) && (allvEdepBD2x2[i][a] > Ethr) && (allvEdepBD2x2[i][a] < Ethr22)) {
			      if ((allvEdepSDS1x2[i][a] < Ethr3) && (allvEdepSDS2x2[i][a] < Ethr3) && (allvEdepSVx2[i][a] < Ethr3)) {
				     XXray6 += 1;
				  } else { Xelec6 += 1; }
			   } else { Xelec6 += 1; }
		    } else { Xelec6 += 1; }
		 }
				 
		 PXXvector6[i][m] = XXray6/(double)(counterXX);
		 PXevector6[i][m] = Xelec6/(double)(counterXX);


		 //---------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Cu Ethr1=0.5 MeV
		 //--------------------------------------------------------- 
		 eXray = 0; eelec = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu[0].size(); a++) {

		    if ((allvEdepSD1mu[i][a] < Ethr1) && (allvEdepSD2mu[i][a] < Ethr1) && (allvEdepSD3mu[i][a] < Ethr1)) {
		       if ((allvEdepBD1mu[i][a] > Ethr) || (allvEdepBD1mu[i][a] < Ethr22) && (allvEdepBD2mu[i][a] > Ethr) && (allvEdepBD2mu[i][a] < Ethr22)) {
			      if ((allvEdepSDS1mu[i][a] < Ethr3) && (allvEdepSDS2mu[i][a] < Ethr3) && (allvEdepSVmu[i][a] < Ethr3)) {
				     eXray += 1;
				  } else { eelec += 1; }
			   } else { eelec += 1; }
		    } else { eelec += 1; }
		 }
				 
		 PeXvector[i][m] = eXray/(double)(counteree);
		 Peevector[i][m] = eelec/(double)(counteree); 


		 //------------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Glass Ethr1=0.5 MeV
		 //------------------------------------------------------------ 
		 eXray2 = 0; eelec2 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu2[0].size(); a++) {

		    if ((allvEdepSD1mu2[i][a] < Ethr1) && (allvEdepSD2mu2[i][a] < Ethr1) && (allvEdepSD3mu2[i][a] < Ethr1)) {
		       if ((allvEdepBD1mu2[i][a] > Ethr) || (allvEdepBD1mu2[i][a] < Ethr22) && (allvEdepBD2mu2[i][a] > Ethr) && (allvEdepBD2mu2[i][a] < Ethr22)) {
			      if ((allvEdepSDS1mu2[i][a] < Ethr3) && (allvEdepSDS2mu2[i][a] < Ethr3) && (allvEdepSVmu2[i][a] < Ethr3)) {
				     eXray2 += 1;
				  } else { eelec2 += 1; }
			   } else { eelec2 += 1; }
		    } else { eelec2 += 1; }
		 }
				 
		 PeXvector2[i][m] = eXray2/(double)(counteree);
		 Peevector2[i][m] = eelec2/(double)(counteree); 


		 //---------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Cu Ethr1=0.7 MeV
		 //--------------------------------------------------------- 
		 eXray3 = 0; eelec3 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu[0].size(); a++) {

		    if ((allvEdepSD1mu[i][a] < Ethr12) && (allvEdepSD2mu[i][a] < Ethr12) && (allvEdepSD3mu[i][a] < Ethr12)) {
		       if ((allvEdepBD1mu[i][a] > Ethr) || (allvEdepBD1mu[i][a] < Ethr22) && (allvEdepBD2mu[i][a] > Ethr) && (allvEdepBD2mu[i][a] < Ethr22)) {
			      if ((allvEdepSDS1mu[i][a] < Ethr3) && (allvEdepSDS2mu[i][a] < Ethr3) && (allvEdepSVmu[i][a] < Ethr3)) {
				     eXray3 += 1;
				  } else { eelec3 += 1; }
			   } else { eelec3 += 1; }
		    } else { eelec3 += 1; }
		 }
				 
		 PeXvector3[i][m] = eXray3/(double)(counteree);
		 Peevector3[i][m] = eelec3/(double)(counteree); 


		 //------------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Glass Ethr1=0.7 MeV
		 //------------------------------------------------------------ 
		 eXray4 = 0; eelec4 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu2[0].size(); a++) {

		    if ((allvEdepSD1mu2[i][a] < Ethr12) && (allvEdepSD2mu2[i][a] < Ethr12) && (allvEdepSD3mu2[i][a] < Ethr12)) {
		       if ((allvEdepBD1mu2[i][a] > Ethr) || (allvEdepBD1mu2[i][a] < Ethr22) && (allvEdepBD2mu2[i][a] > Ethr) && (allvEdepBD2mu2[i][a] < Ethr22)) {
			      if ((allvEdepSDS1mu2[i][a] < Ethr3) && (allvEdepSDS2mu2[i][a] < Ethr3) && (allvEdepSVmu2[i][a] < Ethr3)) {
				     eXray4 += 1;
				  } else { eelec4 += 1; }
			   } else { eelec4 += 1; }
		    } else { eelec4 += 1; }
		 }
				 
		 PeXvector4[i][m] = eXray4/(double)(counteree);
		 Peevector4[i][m] = eelec4/(double)(counteree); 


		 //---------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Cu Ethr1=0.3 MeV
		 //--------------------------------------------------------- 
		 eXray5 = 0; eelec5 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu[0].size(); a++) {

		    if ((allvEdepSD1mu[i][a] < Ethr13) && (allvEdepSD2mu[i][a] < Ethr13) && (allvEdepSD3mu[i][a] < Ethr13)) {
		       if ((allvEdepBD1mu[i][a] > Ethr) || (allvEdepBD1mu[i][a] < Ethr22) && (allvEdepBD2mu[i][a] > Ethr) && (allvEdepBD2mu[i][a] < Ethr22)) {
			      if ((allvEdepSDS1mu[i][a] < Ethr3) && (allvEdepSDS2mu[i][a] < Ethr3) && (allvEdepSVmu[i][a] < Ethr3)) {
				     eXray5 += 1;
				  } else { eelec5 += 1; }
			   } else { eelec5 += 1; }
		    } else { eelec5 += 1; }
		 }
				 
		 PeXvector5[i][m] = eXray5/(double)(counteree);
		 Peevector5[i][m] = eelec5/(double)(counteree); 


		 //------------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Glass Ethr1=0.3 MeV
		 //------------------------------------------------------------ 
		 eXray6 = 0; eelec6 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu2[0].size(); a++) {

		    if ((allvEdepSD1mu2[i][a] < Ethr13) && (allvEdepSD2mu2[i][a] < Ethr13) && (allvEdepSD3mu2[i][a] < Ethr13)) {
		       if ((allvEdepBD1mu2[i][a] > Ethr) || (allvEdepBD1mu2[i][a] < Ethr22) && (allvEdepBD2mu2[i][a] > Ethr) && (allvEdepBD2mu2[i][a] < Ethr22)) {
			      if ((allvEdepSDS1mu2[i][a] < Ethr3) && (allvEdepSDS2mu2[i][a] < Ethr3) && (allvEdepSVmu2[i][a] < Ethr3)) {
				     eXray6 += 1;
				  } else { eelec6 += 1; }
			   } else { eelec6 += 1; }
		    } else { eelec6 += 1; }
		 }
				 
		 PeXvector6[i][m] = eXray6/(double)(counteree);
		 Peevector6[i][m] = eelec6/(double)(counteree); 

	  
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
   float PXXarr3[nsamps] = {};
   float PXXarr4[nsamps] = {};
   float PXXarr5[nsamps] = {};
   float PXXarr6[nsamps] = {};
   float PeXarr[nsamps] = {};
   float PeXarr2[nsamps] = {};
   float PeXarr3[nsamps] = {};
   float PeXarr4[nsamps] = {};
   float PeXarr5[nsamps] = {};
   float PeXarr6[nsamps] = {};
   float PeXXXarr[nsamps] = {};
   float PeXXXarr2[nsamps] = {};
 		 	   
   for (int i=0; i<nsamps; i++) {
      // Normalisation 2 [absolute]
	  PXXarr[i] = PXXvector[0][i];
	  PXXarr2[i] = PXXvector2[0][i];
	  PXXarr3[i] = PXXvector3[0][i];
	  PXXarr4[i] = PXXvector4[0][i];
	  PXXarr5[i] = PXXvector5[0][i];
	  PXXarr6[i] = PXXvector6[0][i];
	  PeXarr[i] = PeXvector[0][i];
	  PeXarr2[i] = PeXvector2[0][i];
	  PeXarr3[i] = PeXvector3[0][i];
	  PeXarr4[i] = PeXvector4[0][i];
	  PeXarr5[i] = PeXvector5[0][i];
	  PeXarr6[i] = PeXvector6[0][i];
	  PeXXXarr[i] = (PeXvector[0][i])/(double)(PXXvector[0][i]);
	  PeXXXarr2[i] = (PeXvector2[0][i])/(double)(PXXvector2[0][i]);
   }	   

		  
   TCanvas *f = new TCanvas("f","E_{THR}",800,600);
   f->Divide(2,1);
   f->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   //gPad->SetFixedAspectRatio();
   TGraph *grPXX = new TGraph(nsamps,Ethrmu,PXXarr);
   grPXX->SetTitle(""); 
   grPXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXX->GetXaxis()->SetRangeUser(0,2.04);
   //grPXX->GetXaxis()->SetNdivisions(-304);
   grPXX->GetYaxis()->SetMoreLogLabels(1);
   grPXX->GetYaxis()->SetTitle("P_{XX}");
   grPXX->GetYaxis()->SetTitleOffset(2.1);
   grPXX->SetLineColor(kRed);
   grPXX->SetLineWidth(3);
   grPXX->Draw("ALP");
   TGraph *grPXX3 = new TGraph(nsamps,Ethrmu,PXXarr3);
   grPXX3->SetLineColor(kRed);
   grPXX3->SetLineStyle(7);
   grPXX3->SetLineWidth(3);
   grPXX3->Draw("LP");
   TGraph *grPXX5 = new TGraph(nsamps,Ethrmu,PXXarr5);
   grPXX5->SetLineColor(kRed);
   grPXX5->SetLineStyle(9);
   grPXX5->SetLineWidth(3);
   grPXX5->Draw("LP");
   TGraph *grPXX2 = new TGraph(nsamps,Ethrmu,PXXarr2);
   grPXX2->SetLineColor(kBlack);
   grPXX2->SetLineWidth(3);
   grPXX2->Draw("LP");
   TGraph *grPXX4 = new TGraph(nsamps,Ethrmu,PXXarr4);
   grPXX4->SetLineColor(kBlack);
   grPXX4->SetLineStyle(7);
   grPXX4->SetLineWidth(3);
   grPXX4->Draw("LP");
   TGraph *grPXX6 = new TGraph(nsamps,Ethrmu,PXXarr6);
   grPXX6->SetLineColor(kBlack);
   grPXX6->SetLineStyle(9);
   grPXX6->SetLineWidth(3);
   grPXX6->Draw("LP");
   legPXX4mm = new TLegend(0.35,0.8,1.0,1.0);
   //legPXX4mm->SetNColumns(2);
   legPXX4mm->SetTextSize(0.03);
   legPXX4mm->AddEntry(grPXX3,"Copper, d_{B}="+TString(dB)+"mm, E_{THR1} = "+TString(Ethr1str.str())+" MeV","lp");
   legPXX4mm->AddEntry(grPXX5,"Copper, d_{B}="+TString(dB)+"mm, E_{THR1} = "+TString(Ethr12str.str())+" MeV","lp");
   legPXX4mm->AddEntry(grPXX,"Copper, d_{B}="+TString(dB)+"mm, E_{THR1} = "+TString(Ethr13str.str())+" MeV","lp");
   legPXX4mm->AddEntry(grPXX4,"Glass, d_{B}="+TString(dB)+"mm, E_{THR1} = "+TString(Ethr1str.str())+" MeV","lp");
   legPXX4mm->AddEntry(grPXX6,"Glass, d_{B}="+TString(dB)+"mm, E_{THR1} = "+TString(Ethr12str.str())+" MeV","lp");
   legPXX4mm->AddEntry(grPXX2,"Glass, d_{B}="+TString(dB)+"mm, E_{THR1} = "+TString(Ethr13str.str())+" MeV","lp");
   legPXX4mm->Draw();
   
   f->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeX = new TGraph(nsamps,Ethrmu,PeXarr);
   grPeX->SetTitle("");
   grPeX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeX->GetXaxis()->SetRangeUser(0,2.04);
   //grPeX->GetXaxis()->SetNdivisions(-304);
   //TGaxis::SetMaxDigits(2);
   grPeX->GetYaxis()->SetMoreLogLabels(1);
   grPeX->GetYaxis()->SetTitle("P_{eX}");
   grPeX->GetYaxis()->SetTitleOffset(2.1);
   grPeX->SetLineColor(kRed);
   grPeX->SetLineWidth(3);
   grPeX->Draw("ALP");
   TGraph *grPeX3 = new TGraph(nsamps,Ethrmu,PeXarr3);
   grPeX3->SetLineColor(kRed);
   grPeX3->SetLineStyle(7);
   grPeX3->SetLineWidth(3);
   grPeX3->Draw("LP");
   TGraph *grPeX5 = new TGraph(nsamps,Ethrmu,PeXarr5);
   grPeX5->SetLineColor(kRed);
   grPeX5->SetLineStyle(9);
   grPeX5->SetLineWidth(3);
   grPeX5->Draw("LP");
   TGraph *grPeX2 = new TGraph(nsamps,Ethrmu,PeXarr2);
   grPeX2->SetLineColor(kBlack);
   grPeX2->SetLineWidth(3);
   grPeX2->Draw("LP");
   TGraph *grPeX4 = new TGraph(nsamps,Ethrmu,PeXarr4);
   grPeX4->SetLineColor(kBlack);
   grPeX4->SetLineStyle(7);
   grPeX4->SetLineWidth(3);
   grPeX4->Draw("LP");
   TGraph *grPeX6 = new TGraph(nsamps,Ethrmu,PeXarr6);
   grPeX6->SetLineColor(kBlack);
   grPeX6->SetLineStyle(9);
   grPeX6->SetLineWidth(3);
   grPeX6->Draw("LP");
   legPeX4mm = new TLegend(0.35,0.8,1.0,1.0);
   //legPeX4mm->SetNColumns(2);
   legPeX4mm->SetTextSize(0.03);
   legPeX4mm->AddEntry(grPeX3,"Copper, d_{B}="+TString(dB)+"mm, E_{THR1} = "+TString(Ethr1str.str())+" MeV","lp");
   legPeX4mm->AddEntry(grPeX5,"Copper, d_{B}="+TString(dB)+"mm, E_{THR1} = "+TString(Ethr12str.str())+" MeV","lp");
   legPeX4mm->AddEntry(grPeX,"Copper, d_{B}="+TString(dB)+"mm, E_{THR1} = "+TString(Ethr13str.str())+" MeV","lp");
   legPeX4mm->AddEntry(grPeX4,"Glass, d_{B}="+TString(dB)+"mm, E_{THR1} = "+TString(Ethr1str.str())+" MeV","lp");
   legPeX4mm->AddEntry(grPeX6,"Glass, d_{B}="+TString(dB)+"mm, E_{THR1} = "+TString(Ethr12str.str())+" MeV","lp");
   legPeX4mm->AddEntry(grPeX2,"Glass, d_{B}="+TString(dB)+"mm, E_{THR1} = "+TString(Ethr13str.str())+" MeV","lp");
   legPeX4mm->Draw();



/*   f->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeXXX = new TGraph(nsamps,Ethrmu,PeXXXarr);
   grPeXXX->SetTitle(""); 
   grPeXXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeXXX->GetXaxis()->SetRangeUser(0,2.04);
   grPeXXX->GetYaxis()->SetMoreLogLabels(1);
   grPeXXX->GetYaxis()->SetTitle("#frac{P_{eX}}{P_{XX}}");
   grPeXXX->GetYaxis()->SetTitleOffset(1.8);
   grPeXXX->SetLineColor(kRed);
   grPeXXX->SetLineWidth(3);
   grPeXXX->Draw("ALP");
   TGraph *grPeXXX2 = new TGraph(nsamps,Ethrmu,PeXXXarr2);
   grPeXXX2->SetLineColor(kBlack);
   grPeXXX2->SetLineWidth(3);
   grPeXXX2->Draw("LP");
*/
/*
   f->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeX2 = new TGraph(nsamps,Ethrmu,PeXarr2);
   grPeX2->SetTitle("");
   grPeX2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeX2->GetXaxis()->SetRangeUser(0,2.05);
   grPeX2->GetYaxis()->SetMoreLogLabels(1);
   grPeX2->GetYaxis()->SetTitle("P_{eX}");
   grPeX2->GetYaxis()->SetTitleOffset(1.8);
   grPeX2->SetLineColor(kBlack);
   grPeX2->SetLineWidth(3);
   grPeX2->Draw("ALP");*/
    

   f->SaveAs("Cu_glass_Sci_eff_dB_"+TString(dB)+"mm_THR3.pdf");
   f->SaveAs("Cu_glass_Sci_eff_dB_"+TString(dB)+"mm_THR3.png");
   f->SaveAs("Cu_glass_Sci_eff_dB_"+TString(dB)+"mm_THR3.C");

 
} 
 
 int main() {
   finalcavCuGlasseff();
   return 0;
}  
