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

void modbeamMULTIeff(){

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
   const int length = 1;
   float phiArray[length] = {50};
   float zArray[length] = {30};


   int phishift, zshift;
      
   for (int phi=0; phi<length; phi++) {

      for (int z=0; z<length; z++) {
	     phishift = phiArray[phi];
	     zshift = zArray[z];

   
		 std::stringstream phishiftss;
		 std::stringstream zshiftss;
		 phishiftss << phishift;
		 zshiftss << zshift;


		 // Names of the files
         // X-ray cascade 0
		 std::string filexSciD1c0 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade0_1e5goldcascade_SciD1.txt";
		 std::string filexSciD2c0 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade0_1e5goldcascade_SciD2.txt";
		 std::string filexSciDTc0 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade0_1e5goldcascade_SciDT.txt";
		 std::string filexSciDBc0 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade0_1e5goldcascade_SciDB.txt";
		 std::string filexSciDLc0 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade0_1e5goldcascade_SciDL.txt";
		 std::string filexSciDRc0 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade0_1e5goldcascade_SciDR.txt";
		 std::string filexBGOD1c0 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade0_1e5goldcascade_BGOD1.txt";
		 
         // X-ray cascade 1
		 std::string filexSciD1c1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade1_1e5goldcascade_SciD1.txt";
		 std::string filexSciD2c1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade1_1e5goldcascade_SciD2.txt";
		 std::string filexSciDTc1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade1_1e5goldcascade_SciDT.txt";
		 std::string filexSciDBc1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade1_1e5goldcascade_SciDB.txt";
		 std::string filexSciDLc1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade1_1e5goldcascade_SciDL.txt";
		 std::string filexSciDRc1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade1_1e5goldcascade_SciDR.txt";
		 std::string filexBGOD1c1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade1_1e5goldcascade_BGOD1.txt";

         // X-ray cascade 2
		 std::string filexSciD1c2 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade2_1e5goldcascade_SciD1.txt";
		 std::string filexSciD2c2 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade2_1e5goldcascade_SciD2.txt";
		 std::string filexSciDTc2 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade2_1e5goldcascade_SciDT.txt";
		 std::string filexSciDBc2 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade2_1e5goldcascade_SciDB.txt";
		 std::string filexSciDLc2 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade2_1e5goldcascade_SciDL.txt";
		 std::string filexSciDRc2 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade2_1e5goldcascade_SciDR.txt";
		 std::string filexBGOD1c2 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade2_1e5goldcascade_BGOD1.txt";

         // X-ray cascade 3
		 std::string filexSciD1c3 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade3_1e5goldcascade_SciD1.txt";
		 std::string filexSciD2c3 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade3_1e5goldcascade_SciD2.txt";
		 std::string filexSciDTc3 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade3_1e5goldcascade_SciDT.txt";
		 std::string filexSciDBc3 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade3_1e5goldcascade_SciDB.txt";
		 std::string filexSciDLc3 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade3_1e5goldcascade_SciDL.txt";
		 std::string filexSciDRc3 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade3_1e5goldcascade_SciDR.txt";
		 std::string filexBGOD1c3 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade3_1e5goldcascade_BGOD1.txt";

         // mu-decay
		 std::string filemuSciD1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_fixed_1e5mudecay_SciD1.txt";
		 std::string filemuSciD2 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_fixed_1e5mudecay_SciD2.txt";
		 std::string filemuSciDT = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_fixed_1e5mudecay_SciDT.txt";
		 std::string filemuSciDB = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_fixed_1e5mudecay_SciDB.txt";
		 std::string filemuSciDL = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_fixed_1e5mudecay_SciDL.txt";
		 std::string filemuSciDR = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_fixed_1e5mudecay_SciDR.txt";
		 std::string filemuBGOD1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_fixed_1e5mudecay_BGOD1.txt";
         

		 // Vectors with filenames   
		 std::vector<std::string> Xfiles;
		 std::vector<std::string> mufiles;

		 // X-ray cascade
		 Xfiles.push_back(filexSciD1c0);
		 Xfiles.push_back(filexSciD2c0);
		 Xfiles.push_back(filexSciDTc0);
		 Xfiles.push_back(filexSciDBc0);
		 Xfiles.push_back(filexSciDLc0);
		 Xfiles.push_back(filexSciDRc0);
		 Xfiles.push_back(filexBGOD1c0);

		 Xfiles.push_back(filexSciD1c1);
		 Xfiles.push_back(filexSciD2c1);
		 Xfiles.push_back(filexSciDTc1);
		 Xfiles.push_back(filexSciDBc1);
		 Xfiles.push_back(filexSciDLc1);
		 Xfiles.push_back(filexSciDRc1);
		 Xfiles.push_back(filexBGOD1c1);

		 Xfiles.push_back(filexSciD1c2);
		 Xfiles.push_back(filexSciD2c2);
		 Xfiles.push_back(filexSciDTc2);
		 Xfiles.push_back(filexSciDBc2);
		 Xfiles.push_back(filexSciDLc2);
		 Xfiles.push_back(filexSciDRc2);
		 Xfiles.push_back(filexBGOD1c2);
		 
		 Xfiles.push_back(filexSciD1c3);
		 Xfiles.push_back(filexSciD2c3);
		 Xfiles.push_back(filexSciDTc3);
		 Xfiles.push_back(filexSciDBc3);
		 Xfiles.push_back(filexSciDLc3);
		 Xfiles.push_back(filexSciDRc3);
		 Xfiles.push_back(filexBGOD1c3);

         // Mu-decay
         mufiles.push_back(filemuSciD1);
         mufiles.push_back(filemuSciD2);
         mufiles.push_back(filemuSciDT);
         mufiles.push_back(filemuSciDB);
         mufiles.push_back(filemuSciDL);
         mufiles.push_back(filemuSciDR);
         mufiles.push_back(filemuBGOD1);


		 /*********************************/
		 /*           Analysis            */
		 /*********************************/

		 float Edep, EventID;
		 float iEventID;

		 float Ethr1 = 0.5;
		 float Ethr21 = 0.5;
		 float Ethr22 = 8;
		 float Ethr3 = 1;
		 float Estep = 2.0/(nsamps-1);
		 float Ethrmu[nsamps] = {};
		   
		 // Storage vectors
		 // Normalisation 2 [abs = total] :: X-ray cascade
		 std::vector< std::vector<double> > PXevectorN2c0(Xfiles.size()/28,std::vector<double>(nsamps));
		 std::vector< std::vector<double> > PXXvectorN2c0(Xfiles.size()/28,std::vector<double>(nsamps));          
		 std::vector< std::vector<double> > PXevectorN2c1(Xfiles.size()/28,std::vector<double>(nsamps));
		 std::vector< std::vector<double> > PXXvectorN2c1(Xfiles.size()/28,std::vector<double>(nsamps));      
		 std::vector< std::vector<double> > PXevectorN2c2(Xfiles.size()/28,std::vector<double>(nsamps));
		 std::vector< std::vector<double> > PXXvectorN2c2(Xfiles.size()/28,std::vector<double>(nsamps));      
		 std::vector< std::vector<double> > PXevectorN2c3(Xfiles.size()/28,std::vector<double>(nsamps));
		 std::vector< std::vector<double> > PXXvectorN2c3(Xfiles.size()/28,std::vector<double>(nsamps));      
         // Normalisation 2 [abs = total] :: Mu-decay
         std::vector< std::vector<double> > PeevectorN2(mufiles.size()/7,std::vector<double>(nsamps));
		 std::vector< std::vector<double> > PeXvectorN2(mufiles.size()/7,std::vector<double>(nsamps));      


		 // X-ray cascade
		 std::vector< std::vector< double > > allvEvIDSD1xc0;
		 std::vector< std::vector< double > > allvEdepSD1xc0;
		 std::vector< std::vector< double > > allvEvIDSD2xc0;
		 std::vector< std::vector< double > > allvEdepSD2xc0;
		 std::vector< std::vector< double > > allvEvIDSDTxc0;
		 std::vector< std::vector< double > > allvEdepSDTxc0;
		 std::vector< std::vector< double > > allvEvIDSDBxc0;
		 std::vector< std::vector< double > > allvEdepSDBxc0;
		 std::vector< std::vector< double > > allvEvIDSDLxc0;
		 std::vector< std::vector< double > > allvEdepSDLxc0;
		 std::vector< std::vector< double > > allvEvIDSDRxc0;
		 std::vector< std::vector< double > > allvEdepSDRxc0;
		 std::vector< std::vector< double > > allvEvIDBD1xc0;
		 std::vector< std::vector< double > > allvEdepBD1xc0;

		 std::vector< std::vector< double > > allvEvIDSD1xc1;
		 std::vector< std::vector< double > > allvEdepSD1xc1;
		 std::vector< std::vector< double > > allvEvIDSD2xc1;
		 std::vector< std::vector< double > > allvEdepSD2xc1;
		 std::vector< std::vector< double > > allvEvIDSDTxc1;
		 std::vector< std::vector< double > > allvEdepSDTxc1;
		 std::vector< std::vector< double > > allvEvIDSDBxc1;
		 std::vector< std::vector< double > > allvEdepSDBxc1;
		 std::vector< std::vector< double > > allvEvIDSDLxc1;
		 std::vector< std::vector< double > > allvEdepSDLxc1;
		 std::vector< std::vector< double > > allvEvIDSDRxc1;
		 std::vector< std::vector< double > > allvEdepSDRxc1;
		 std::vector< std::vector< double > > allvEvIDBD1xc1;
		 std::vector< std::vector< double > > allvEdepBD1xc1;
		   
		 std::vector< std::vector< double > > allvEvIDSD1xc2;
		 std::vector< std::vector< double > > allvEdepSD1xc2;
		 std::vector< std::vector< double > > allvEvIDSD2xc2;
		 std::vector< std::vector< double > > allvEdepSD2xc2;
		 std::vector< std::vector< double > > allvEvIDSDTxc2;
		 std::vector< std::vector< double > > allvEdepSDTxc2;
		 std::vector< std::vector< double > > allvEvIDSDBxc2;
		 std::vector< std::vector< double > > allvEdepSDBxc2;
		 std::vector< std::vector< double > > allvEvIDSDLxc2;
		 std::vector< std::vector< double > > allvEdepSDLxc2;
		 std::vector< std::vector< double > > allvEvIDSDRxc2;
		 std::vector< std::vector< double > > allvEdepSDRxc2;
		 std::vector< std::vector< double > > allvEvIDBD1xc2;
		 std::vector< std::vector< double > > allvEdepBD1xc2;

		 std::vector< std::vector< double > > allvEvIDSD1xc3;
		 std::vector< std::vector< double > > allvEdepSD1xc3;
		 std::vector< std::vector< double > > allvEvIDSD2xc3;
		 std::vector< std::vector< double > > allvEdepSD2xc3;
		 std::vector< std::vector< double > > allvEvIDSDTxc3;
		 std::vector< std::vector< double > > allvEdepSDTxc3;
		 std::vector< std::vector< double > > allvEvIDSDBxc3;
		 std::vector< std::vector< double > > allvEdepSDBxc3;
		 std::vector< std::vector< double > > allvEvIDSDLxc3;
		 std::vector< std::vector< double > > allvEdepSDLxc3;
		 std::vector< std::vector< double > > allvEvIDSDRxc3;
		 std::vector< std::vector< double > > allvEdepSDRxc3;
		 std::vector< std::vector< double > > allvEvIDBD1xc3;
		 std::vector< std::vector< double > > allvEdepBD1xc3;

         // Mu-decay
         std::vector< std::vector< double > > allvEvIDSD1mu;
		 std::vector< std::vector< double > > allvEdepSD1mu;
		 std::vector< std::vector< double > > allvEvIDSD2mu;
		 std::vector< std::vector< double > > allvEdepSD2mu;
		 std::vector< std::vector< double > > allvEvIDSDTmu;
		 std::vector< std::vector< double > > allvEdepSDTmu;
		 std::vector< std::vector< double > > allvEvIDSDBmu;
		 std::vector< std::vector< double > > allvEdepSDBmu;
		 std::vector< std::vector< double > > allvEvIDSDLmu;
		 std::vector< std::vector< double > > allvEdepSDLmu;
		 std::vector< std::vector< double > > allvEvIDSDRmu;
		 std::vector< std::vector< double > > allvEdepSDRmu;
		 std::vector< std::vector< double > > allvEvIDBD1mu;
		 std::vector< std::vector< double > > allvEdepBD1mu;


		 float Ethr;
		 int counterXXN2 = 1e5;
		 int countereeN2 = 1e5;
		 int XXrayN2c0 = 0; // X-rays i-fied as X-rays
		 int XelecN2c0 = 0; // X-rays i-fied as electrons
		 int XXrayN2c1 = 0;
		 int XelecN2c1 = 0;
		 int XXrayN2c2 = 0;
		 int XelecN2c2 = 0;
		 int XXrayN2c3 = 0;
		 int XelecN2c3 = 0;
		 int eXrayN2 = 0; // Electrons i-fied as X-rays
		 int eelecN2 = 0; // Electrons i-fied as electrons
		   
		 Ethrmu[0] = 0;
		 for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;


		 //-------------------------------------------------------------------
		 //                           Reading
		 //-------------------------------------------------------------------
		   
		 std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
		 std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
		 std::cout << "\033[1;34m------------------- X-ray cascade ------------------------\033[0m" << std::endl;
		 std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


		 for (int k=0; k<((Xfiles.size())/28); k++) {
			  
		    // SciD1c0
			std::ifstream xfSciD1c0(TString(Xfiles[k*28]));
			std::vector<double> vEvIDSD1xc0;
			std::vector<double> vEdepSD1xc0;
			  
			while (!xfSciD1c0.eof()) {
			   double EvIDSD1c0, EdepSD1c0;
			   xfSciD1c0 >> EvIDSD1c0 >> EdepSD1c0;
			   vEvIDSD1xc0.push_back(EvIDSD1c0);
			   vEdepSD1xc0.push_back(EdepSD1c0);
			}
			vEvIDSD1xc0.pop_back(); vEdepSD1xc0.pop_back();
			vEvIDSD1xc0.pop_back(); vEdepSD1xc0.pop_back();
			  
			xfSciD1c0.close();
			allvEvIDSD1xc0.push_back(vEvIDSD1xc0);
			allvEdepSD1xc0.push_back(vEdepSD1xc0);


			// SciD2c0
			std::ifstream xfSciD2c0(TString(Xfiles[(k*28)+1]));
			std::vector<double> vEvIDSD2xc0;
			std::vector<double> vEdepSD2xc0;
			  
			while (!xfSciD2c0.eof()) {
			   double EvIDSD2c0, EdepSD2c0;
			   xfSciD2c0 >> EvIDSD2c0 >> EdepSD2c0;
			   vEvIDSD2xc0.push_back(EvIDSD2c0);
			   vEdepSD2xc0.push_back(EdepSD2c0);
			}
			vEvIDSD2xc0.pop_back(); vEdepSD2xc0.pop_back();
			vEvIDSD2xc0.pop_back(); vEdepSD2xc0.pop_back();
			  
			xfSciD2c0.close();
			allvEvIDSD2xc0.push_back(vEvIDSD2xc0);
			allvEdepSD2xc0.push_back(vEdepSD2xc0);
			  
			  
			// SciDTc0
			std::ifstream xfSciDTc0(TString(Xfiles[(k*28)+2]));
			std::vector<double> vEvIDSDTxc0;
			std::vector<double> vEdepSDTxc0;
			  
			while (!xfSciDTc0.eof()) {
			   double EvIDSDTc0, EdepSDTc0;
			   xfSciDTc0 >> EvIDSDTc0 >> EdepSDTc0;
			   vEvIDSDTxc0.push_back(EvIDSDTc0);
			   vEdepSDTxc0.push_back(EdepSDTc0);
			}
			vEvIDSDTxc0.pop_back(); vEdepSDTxc0.pop_back();
			vEvIDSDTxc0.pop_back(); vEdepSDTxc0.pop_back();
			  
			xfSciDTc0.close();
			allvEvIDSDTxc0.push_back(vEvIDSDTxc0);
			allvEdepSDTxc0.push_back(vEdepSDTxc0);


			// SciDBc0
			std::ifstream xfSciDBc0(TString(Xfiles[(k*28)+3]));
			std::vector<double> vEvIDSDBxc0;
			std::vector<double> vEdepSDBxc0;
			  
			while (!xfSciDBc0.eof()) {
			   double EvIDSDBc0, EdepSDBc0;
			   xfSciDBc0 >> EvIDSDBc0 >> EdepSDBc0;
			   vEvIDSDBxc0.push_back(EvIDSDBc0);
			   vEdepSDBxc0.push_back(EdepSDBc0);
			}
			vEvIDSDBxc0.pop_back(); vEdepSDBxc0.pop_back();
			vEvIDSDBxc0.pop_back(); vEdepSDBxc0.pop_back();
			  
			xfSciDBc0.close();
			allvEvIDSDBxc0.push_back(vEvIDSDBxc0);
			allvEdepSDBxc0.push_back(vEdepSDBxc0);


			// SciDLc0
			std::ifstream xfSciDLc0(TString(Xfiles[(k*28)+4]));
			std::vector<double> vEvIDSDLxc0;
			std::vector<double> vEdepSDLxc0;
			  
			while (!xfSciDLc0.eof()) {
			   double EvIDSDLc0, EdepSDLc0;
			   xfSciDLc0 >> EvIDSDLc0 >> EdepSDLc0;
			   vEvIDSDLxc0.push_back(EvIDSDLc0);
			   vEdepSDLxc0.push_back(EdepSDLc0);
			}
			vEvIDSDLxc0.pop_back(); vEdepSDLxc0.pop_back();
			vEvIDSDLxc0.pop_back(); vEdepSDLxc0.pop_back();
			  
			xfSciDLc0.close();
			allvEvIDSDLxc0.push_back(vEvIDSDLxc0);
			allvEdepSDLxc0.push_back(vEdepSDLxc0);


			// SciDRc0
			std::ifstream xfSciDRc0(TString(Xfiles[(k*28)+5]));
			std::vector<double> vEvIDSDRxc0;
			std::vector<double> vEdepSDRxc0;
			  
			while (!xfSciDRc0.eof()) {
			   double EvIDSDRc0, EdepSDRc0;
			   xfSciDRc0 >> EvIDSDRc0 >> EdepSDRc0;
			   vEvIDSDRxc0.push_back(EvIDSDRc0);
			   vEdepSDRxc0.push_back(EdepSDRc0);
			}
			vEvIDSDRxc0.pop_back(); vEdepSDRxc0.pop_back();
			vEvIDSDRxc0.pop_back(); vEdepSDRxc0.pop_back();
			  
			xfSciDRc0.close();
			allvEvIDSDRxc0.push_back(vEvIDSDRxc0);
			allvEdepSDRxc0.push_back(vEdepSDRxc0);


			// BGOD1c0
			std::ifstream xfBGOD1c0(TString(Xfiles[(k*28)+6]));
			std::vector<double> vEvIDBD1xc0;
			std::vector<double> vEdepBD1xc0;
			  
			while (!xfBGOD1c0.eof()) {
			   double EvIDBD1c0, EdepBD1c0;
			   xfBGOD1c0 >> EvIDBD1c0 >> EdepBD1c0;
			   vEvIDBD1xc0.push_back(EvIDBD1c0);
			   vEdepBD1xc0.push_back(EdepBD1c0);
			}
			vEvIDBD1xc0.pop_back(); vEdepBD1xc0.pop_back();
			vEvIDBD1xc0.pop_back(); vEdepBD1xc0.pop_back();
			  
			xfBGOD1c0.close();
			allvEvIDBD1xc0.push_back(vEvIDBD1xc0);
			allvEdepBD1xc0.push_back(vEdepBD1xc0);


		    // SciD1c1
			std::ifstream xfSciD1c1(TString(Xfiles[(k*28)+7]));
			std::vector<double> vEvIDSD1xc1;
			std::vector<double> vEdepSD1xc1;
			  
			while (!xfSciD1c1.eof()) {
			   double EvIDSD1c1, EdepSD1c1;
			   xfSciD1c1 >> EvIDSD1c1 >> EdepSD1c1;
			   vEvIDSD1xc1.push_back(EvIDSD1c1);
			   vEdepSD1xc1.push_back(EdepSD1c1);
			}
			vEvIDSD1xc1.pop_back(); vEdepSD1xc1.pop_back();
			vEvIDSD1xc1.pop_back(); vEdepSD1xc1.pop_back();
			  
			xfSciD1c1.close();
			allvEvIDSD1xc1.push_back(vEvIDSD1xc1);
			allvEdepSD1xc1.push_back(vEdepSD1xc1);


			// SciD2c1
			std::ifstream xfSciD2c1(TString(Xfiles[(k*28)+8]));
			std::vector<double> vEvIDSD2xc1;
			std::vector<double> vEdepSD2xc1;
			  
			while (!xfSciD2c1.eof()) {
			   double EvIDSD2c1, EdepSD2c1;
			   xfSciD2c1 >> EvIDSD2c1 >> EdepSD2c1;
			   vEvIDSD2xc1.push_back(EvIDSD2c1);
			   vEdepSD2xc1.push_back(EdepSD2c1);
			}
			vEvIDSD2xc1.pop_back(); vEdepSD2xc1.pop_back();
			vEvIDSD2xc1.pop_back(); vEdepSD2xc1.pop_back();
			  
			xfSciD2c1.close();
			allvEvIDSD2xc1.push_back(vEvIDSD2xc1);
			allvEdepSD2xc1.push_back(vEdepSD2xc1);
			  
			  
			// SciDTc1
			std::ifstream xfSciDTc1(TString(Xfiles[(k*28)+9]));
			std::vector<double> vEvIDSDTxc1;
			std::vector<double> vEdepSDTxc1;
			  
			while (!xfSciDTc1.eof()) {
			   double EvIDSDTc1, EdepSDTc1;
			   xfSciDTc1 >> EvIDSDTc1 >> EdepSDTc1;
			   vEvIDSDTxc1.push_back(EvIDSDTc1);
			   vEdepSDTxc1.push_back(EdepSDTc1);
			}
			vEvIDSDTxc1.pop_back(); vEdepSDTxc1.pop_back();
			vEvIDSDTxc1.pop_back(); vEdepSDTxc1.pop_back();
			  
			xfSciDTc1.close();
			allvEvIDSDTxc1.push_back(vEvIDSDTxc1);
			allvEdepSDTxc1.push_back(vEdepSDTxc1);


			// SciDBc1
			std::ifstream xfSciDBc1(TString(Xfiles[(k*28)+10]));
			std::vector<double> vEvIDSDBxc1;
			std::vector<double> vEdepSDBxc1;
			  
			while (!xfSciDBc1.eof()) {
			   double EvIDSDBc1, EdepSDBc1;
			   xfSciDBc1 >> EvIDSDBc1 >> EdepSDBc1;
			   vEvIDSDBxc1.push_back(EvIDSDBc1);
			   vEdepSDBxc1.push_back(EdepSDBc1);
			}
			vEvIDSDBxc1.pop_back(); vEdepSDBxc1.pop_back();
			vEvIDSDBxc1.pop_back(); vEdepSDBxc1.pop_back();
			  
			xfSciDBc1.close();
			allvEvIDSDBxc1.push_back(vEvIDSDBxc1);
			allvEdepSDBxc1.push_back(vEdepSDBxc1);


			// SciDLc1
			std::ifstream xfSciDLc1(TString(Xfiles[(k*28)+11]));
			std::vector<double> vEvIDSDLxc1;
			std::vector<double> vEdepSDLxc1;
			  
			while (!xfSciDLc1.eof()) {
			   double EvIDSDLc1, EdepSDLc1;
			   xfSciDLc1 >> EvIDSDLc1 >> EdepSDLc1;
			   vEvIDSDLxc1.push_back(EvIDSDLc1);
			   vEdepSDLxc1.push_back(EdepSDLc1);
			}
			vEvIDSDLxc1.pop_back(); vEdepSDLxc1.pop_back();
			vEvIDSDLxc1.pop_back(); vEdepSDLxc1.pop_back();
			  
			xfSciDLc1.close();
			allvEvIDSDLxc1.push_back(vEvIDSDLxc1);
			allvEdepSDLxc1.push_back(vEdepSDLxc1);


			// SciDRc1
			std::ifstream xfSciDRc1(TString(Xfiles[(k*28)+12]));
			std::vector<double> vEvIDSDRxc1;
			std::vector<double> vEdepSDRxc1;
			  
			while (!xfSciDRc1.eof()) {
			   double EvIDSDRc1, EdepSDRc1;
			   xfSciDRc1 >> EvIDSDRc1 >> EdepSDRc1;
			   vEvIDSDRxc1.push_back(EvIDSDRc1);
			   vEdepSDRxc1.push_back(EdepSDRc1);
			}
			vEvIDSDRxc1.pop_back(); vEdepSDRxc1.pop_back();
			vEvIDSDRxc1.pop_back(); vEdepSDRxc1.pop_back();
			  
			xfSciDRc1.close();
			allvEvIDSDRxc1.push_back(vEvIDSDRxc1);
			allvEdepSDRxc1.push_back(vEdepSDRxc1);


			// BGOD1c1
			std::ifstream xfBGOD1c1(TString(Xfiles[(k*28)+13]));
			std::vector<double> vEvIDBD1xc1;
			std::vector<double> vEdepBD1xc1;
			  
			while (!xfBGOD1c1.eof()) {
			   double EvIDBD1c1, EdepBD1c1;
			   xfBGOD1c1 >> EvIDBD1c1 >> EdepBD1c1;
			   vEvIDBD1xc1.push_back(EvIDBD1c1);
			   vEdepBD1xc1.push_back(EdepBD1c1);
			}
			vEvIDBD1xc1.pop_back(); vEdepBD1xc1.pop_back();
			vEvIDBD1xc1.pop_back(); vEdepBD1xc1.pop_back();
			  
			xfBGOD1c1.close();
			allvEvIDBD1xc1.push_back(vEvIDBD1xc1);
			allvEdepBD1xc1.push_back(vEdepBD1xc1);


            // SciD1c2
			std::ifstream xfSciD1c2(TString(Xfiles[(k*28)+14]));
			std::vector<double> vEvIDSD1xc2;
			std::vector<double> vEdepSD1xc2;
			  
			while (!xfSciD1c2.eof()) {
			   double EvIDSD1c2, EdepSD1c2;
			   xfSciD1c2 >> EvIDSD1c2 >> EdepSD1c2;
			   vEvIDSD1xc2.push_back(EvIDSD1c2);
			   vEdepSD1xc2.push_back(EdepSD1c2);
			}
			vEvIDSD1xc2.pop_back(); vEdepSD1xc2.pop_back();
			vEvIDSD1xc2.pop_back(); vEdepSD1xc2.pop_back();
			  
			xfSciD1c2.close();
			allvEvIDSD1xc2.push_back(vEvIDSD1xc2);
			allvEdepSD1xc2.push_back(vEdepSD1xc2);


			// SciD2c2
			std::ifstream xfSciD2c2(TString(Xfiles[(k*28)+15]));
			std::vector<double> vEvIDSD2xc2;
			std::vector<double> vEdepSD2xc2;
			  
			while (!xfSciD2c2.eof()) {
			   double EvIDSD2c2, EdepSD2c2;
			   xfSciD2c2 >> EvIDSD2c2 >> EdepSD2c2;
			   vEvIDSD2xc2.push_back(EvIDSD2c2);
			   vEdepSD2xc2.push_back(EdepSD2c2);
			}
			vEvIDSD2xc2.pop_back(); vEdepSD2xc2.pop_back();
			vEvIDSD2xc2.pop_back(); vEdepSD2xc2.pop_back();
			  
			xfSciD2c2.close();
			allvEvIDSD2xc2.push_back(vEvIDSD2xc2);
			allvEdepSD2xc2.push_back(vEdepSD2xc2);
			  
			  
			// SciDTc2
			std::ifstream xfSciDTc2(TString(Xfiles[(k*28)+16]));
			std::vector<double> vEvIDSDTxc2;
			std::vector<double> vEdepSDTxc2;
			  
			while (!xfSciDTc2.eof()) {
			   double EvIDSDTc2, EdepSDTc2;
			   xfSciDTc2 >> EvIDSDTc2 >> EdepSDTc2;
			   vEvIDSDTxc2.push_back(EvIDSDTc2);
			   vEdepSDTxc2.push_back(EdepSDTc2);
			}
			vEvIDSDTxc2.pop_back(); vEdepSDTxc2.pop_back();
			vEvIDSDTxc2.pop_back(); vEdepSDTxc2.pop_back();
			  
			xfSciDTc2.close();
			allvEvIDSDTxc2.push_back(vEvIDSDTxc2);
			allvEdepSDTxc2.push_back(vEdepSDTxc2);


			// SciDBc2
			std::ifstream xfSciDBc2(TString(Xfiles[(k*28)+17]));
			std::vector<double> vEvIDSDBxc2;
			std::vector<double> vEdepSDBxc2;
			  
			while (!xfSciDBc2.eof()) {
			   double EvIDSDBc2, EdepSDBc2;
			   xfSciDBc2 >> EvIDSDBc2 >> EdepSDBc2;
			   vEvIDSDBxc2.push_back(EvIDSDBc2);
			   vEdepSDBxc2.push_back(EdepSDBc2);
			}
			vEvIDSDBxc2.pop_back(); vEdepSDBxc2.pop_back();
			vEvIDSDBxc2.pop_back(); vEdepSDBxc2.pop_back();
			  
			xfSciDBc2.close();
			allvEvIDSDBxc2.push_back(vEvIDSDBxc2);
			allvEdepSDBxc2.push_back(vEdepSDBxc2);


			// SciDLc2
			std::ifstream xfSciDLc2(TString(Xfiles[(k*28)+18]));
			std::vector<double> vEvIDSDLxc2;
			std::vector<double> vEdepSDLxc2;
			  
			while (!xfSciDLc2.eof()) {
			   double EvIDSDLc2, EdepSDLc2;
			   xfSciDLc2 >> EvIDSDLc2 >> EdepSDLc2;
			   vEvIDSDLxc2.push_back(EvIDSDLc2);
			   vEdepSDLxc2.push_back(EdepSDLc2);
			}
			vEvIDSDLxc2.pop_back(); vEdepSDLxc2.pop_back();
			vEvIDSDLxc2.pop_back(); vEdepSDLxc2.pop_back();
			  
			xfSciDLc2.close();
			allvEvIDSDLxc2.push_back(vEvIDSDLxc2);
			allvEdepSDLxc2.push_back(vEdepSDLxc2);


			// SciDRc2
			std::ifstream xfSciDRc2(TString(Xfiles[(k*28)+19]));
			std::vector<double> vEvIDSDRxc2;
			std::vector<double> vEdepSDRxc2;
			  
			while (!xfSciDRc2.eof()) {
			   double EvIDSDRc2, EdepSDRc2;
			   xfSciDRc2 >> EvIDSDRc2 >> EdepSDRc2;
			   vEvIDSDRxc2.push_back(EvIDSDRc2);
			   vEdepSDRxc2.push_back(EdepSDRc2);
			}
			vEvIDSDRxc2.pop_back(); vEdepSDRxc2.pop_back();
			vEvIDSDRxc2.pop_back(); vEdepSDRxc2.pop_back();
			  
			xfSciDRc2.close();
			allvEvIDSDRxc2.push_back(vEvIDSDRxc2);
			allvEdepSDRxc2.push_back(vEdepSDRxc2);


			// BGOD1c2
			std::ifstream xfBGOD1c2(TString(Xfiles[(k*28)+20]));
			std::vector<double> vEvIDBD1xc2;
			std::vector<double> vEdepBD1xc2;
			  
			while (!xfBGOD1c2.eof()) {
			   double EvIDBD1c2, EdepBD1c2;
			   xfBGOD1c2 >> EvIDBD1c2 >> EdepBD1c2;
			   vEvIDBD1xc2.push_back(EvIDBD1c2);
			   vEdepBD1xc2.push_back(EdepBD1c2);
			}
			vEvIDBD1xc2.pop_back(); vEdepBD1xc2.pop_back();
			vEvIDBD1xc2.pop_back(); vEdepBD1xc2.pop_back();
			  
			xfBGOD1c2.close();
			allvEvIDBD1xc2.push_back(vEvIDBD1xc2);
			allvEdepBD1xc2.push_back(vEdepBD1xc2);


			// SciD1c3
			std::ifstream xfSciD1c3(TString(Xfiles[(k*28)+21]));
			std::vector<double> vEvIDSD1xc3;
			std::vector<double> vEdepSD1xc3;
			  
			while (!xfSciD1c3.eof()) {
			   double EvIDSD1c3, EdepSD1c3;
			   xfSciD1c3 >> EvIDSD1c3 >> EdepSD1c3;
			   vEvIDSD1xc3.push_back(EvIDSD1c3);
			   vEdepSD1xc3.push_back(EdepSD1c3);
			}
			vEvIDSD1xc3.pop_back(); vEdepSD1xc3.pop_back();
			vEvIDSD1xc3.pop_back(); vEdepSD1xc3.pop_back();
			  
			xfSciD1c3.close();
			allvEvIDSD1xc3.push_back(vEvIDSD1xc3);
			allvEdepSD1xc3.push_back(vEdepSD1xc3);


			// SciD2c3
			std::ifstream xfSciD2c3(TString(Xfiles[(k*28)+22]));
			std::vector<double> vEvIDSD2xc3;
			std::vector<double> vEdepSD2xc3;
			  
			while (!xfSciD2c3.eof()) {
			   double EvIDSD2c3, EdepSD2c3;
			   xfSciD2c3 >> EvIDSD2c3 >> EdepSD2c3;
			   vEvIDSD2xc3.push_back(EvIDSD2c3);
			   vEdepSD2xc3.push_back(EdepSD2c3);
			}
			vEvIDSD2xc3.pop_back(); vEdepSD2xc3.pop_back();
			vEvIDSD2xc3.pop_back(); vEdepSD2xc3.pop_back();
			  
			xfSciD2c3.close();
			allvEvIDSD2xc3.push_back(vEvIDSD2xc3);
			allvEdepSD2xc3.push_back(vEdepSD2xc3);
			  
			  
			// SciDTc3
			std::ifstream xfSciDTc3(TString(Xfiles[(k*28)+23]));
			std::vector<double> vEvIDSDTxc3;
			std::vector<double> vEdepSDTxc3;
			  
			while (!xfSciDTc3.eof()) {
			   double EvIDSDTc3, EdepSDTc3;
			   xfSciDTc3 >> EvIDSDTc3 >> EdepSDTc3;
			   vEvIDSDTxc3.push_back(EvIDSDTc3);
			   vEdepSDTxc3.push_back(EdepSDTc3);
			}
			vEvIDSDTxc3.pop_back(); vEdepSDTxc3.pop_back();
			vEvIDSDTxc3.pop_back(); vEdepSDTxc3.pop_back();
			  
			xfSciDTc3.close();
			allvEvIDSDTxc3.push_back(vEvIDSDTxc3);
			allvEdepSDTxc3.push_back(vEdepSDTxc3);


			// SciDBc3
			std::ifstream xfSciDBc3(TString(Xfiles[(k*28)+24]));
			std::vector<double> vEvIDSDBxc3;
			std::vector<double> vEdepSDBxc3;
			  
			while (!xfSciDBc3.eof()) {
			   double EvIDSDBc3, EdepSDBc3;
			   xfSciDBc3 >> EvIDSDBc3 >> EdepSDBc3;
			   vEvIDSDBxc3.push_back(EvIDSDBc3);
			   vEdepSDBxc3.push_back(EdepSDBc3);
			}
			vEvIDSDBxc3.pop_back(); vEdepSDBxc3.pop_back();
			vEvIDSDBxc3.pop_back(); vEdepSDBxc3.pop_back();
			  
			xfSciDBc3.close();
			allvEvIDSDBxc3.push_back(vEvIDSDBxc3);
			allvEdepSDBxc3.push_back(vEdepSDBxc3);


			// SciDLc3
			std::ifstream xfSciDLc3(TString(Xfiles[(k*28)+25]));
			std::vector<double> vEvIDSDLxc3;
			std::vector<double> vEdepSDLxc3;
			  
			while (!xfSciDLc3.eof()) {
			   double EvIDSDLc3, EdepSDLc3;
			   xfSciDLc3 >> EvIDSDLc3 >> EdepSDLc3;
			   vEvIDSDLxc3.push_back(EvIDSDLc3);
			   vEdepSDLxc3.push_back(EdepSDLc3);
			}
			vEvIDSDLxc3.pop_back(); vEdepSDLxc3.pop_back();
			vEvIDSDLxc3.pop_back(); vEdepSDLxc3.pop_back();
			  
			xfSciDLc3.close();
			allvEvIDSDLxc3.push_back(vEvIDSDLxc3);
			allvEdepSDLxc3.push_back(vEdepSDLxc3);


			// SciDRc3
			std::ifstream xfSciDRc3(TString(Xfiles[(k*28)+26]));
			std::vector<double> vEvIDSDRxc3;
			std::vector<double> vEdepSDRxc3;
			  
			while (!xfSciDRc3.eof()) {
			   double EvIDSDRc3, EdepSDRc3;
			   xfSciDRc3 >> EvIDSDRc3 >> EdepSDRc3;
			   vEvIDSDRxc3.push_back(EvIDSDRc3);
			   vEdepSDRxc3.push_back(EdepSDRc3);
			}
			vEvIDSDRxc3.pop_back(); vEdepSDRxc3.pop_back();
			vEvIDSDRxc3.pop_back(); vEdepSDRxc3.pop_back();
			  
			xfSciDRc3.close();
			allvEvIDSDRxc3.push_back(vEvIDSDRxc3);
			allvEdepSDRxc3.push_back(vEdepSDRxc3);


			// BGOD1c3
			std::ifstream xfBGOD1c3(TString(Xfiles[(k*28)+27]));
			std::vector<double> vEvIDBD1xc3;
			std::vector<double> vEdepBD1xc3;
			  
			while (!xfBGOD1c3.eof()) {
			   double EvIDBD1c3, EdepBD1c3;
			   xfBGOD1c3 >> EvIDBD1c3 >> EdepBD1c3;
			   vEvIDBD1xc3.push_back(EvIDBD1c3);
			   vEdepBD1xc3.push_back(EdepBD1c3);
			}
			vEvIDBD1xc3.pop_back(); vEdepBD1xc3.pop_back();
			vEvIDBD1xc3.pop_back(); vEdepBD1xc3.pop_back();
			  
			xfBGOD1c3.close();
			allvEvIDBD1xc3.push_back(vEvIDBD1xc3);
			allvEdepBD1xc3.push_back(vEdepBD1xc3);


		 }



		 for (int k=0; k<((mufiles.size())/7); k++) {
            
			// SciD1mu
			std::ifstream mufSciD1(TString(mufiles[k*7]));
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
			std::ifstream mufSciD2(TString(mufiles[(k*7)+1]));
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
			  
			  
			// SciDTmu
			std::ifstream mufSciDT(TString(mufiles[(k*7)+2]));
			std::vector<double> vEvIDSDTmu;
			std::vector<double> vEdepSDTmu;
			  
			while (!mufSciDT.eof()) {
			   double EvIDSDTmu, EdepSDTmu;
			   mufSciDT >> EvIDSDTmu >> EdepSDTmu;
			   vEvIDSDTmu.push_back(EvIDSDTmu);
			   vEdepSDTmu.push_back(EdepSDTmu);
			}
			vEvIDSDTmu.pop_back(); vEdepSDTmu.pop_back();
			vEvIDSDTmu.pop_back(); vEdepSDTmu.pop_back();
			  
			mufSciDT.close();
			allvEvIDSDTmu.push_back(vEvIDSDTmu);
			allvEdepSDTmu.push_back(vEdepSDTmu);


			// SciDBmu
			std::ifstream mufSciDB(TString(mufiles[(k*7)+3]));
			std::vector<double> vEvIDSDBmu;
			std::vector<double> vEdepSDBmu;
			  
			while (!mufSciDB.eof()) {
			   double EvIDSDBmu, EdepSDBmu;
			   mufSciDB >> EvIDSDBmu >> EdepSDBmu;
			   vEvIDSDBmu.push_back(EvIDSDBmu);
			   vEdepSDBmu.push_back(EdepSDBmu);
			}
			vEvIDSDBmu.pop_back(); vEdepSDBmu.pop_back();
			vEvIDSDBmu.pop_back(); vEdepSDBmu.pop_back();
			  
			mufSciDB.close();
			allvEvIDSDBmu.push_back(vEvIDSDBmu);
			allvEdepSDBmu.push_back(vEdepSDBmu);


			// SciDLmu
			std::ifstream mufSciDL(TString(mufiles[(k*7)+4]));
			std::vector<double> vEvIDSDLmu;
			std::vector<double> vEdepSDLmu;
			  
			while (!mufSciDL.eof()) {
			   double EvIDSDLmu, EdepSDLmu;
			   mufSciDL >> EvIDSDLmu >> EdepSDLmu;
			   vEvIDSDLmu.push_back(EvIDSDLmu);
			   vEdepSDLmu.push_back(EdepSDLmu);
			}
			vEvIDSDLmu.pop_back(); vEdepSDLmu.pop_back();
			vEvIDSDLmu.pop_back(); vEdepSDLmu.pop_back();
			  
			mufSciDL.close();
			allvEvIDSDLmu.push_back(vEvIDSDLmu);
			allvEdepSDLmu.push_back(vEdepSDLmu);


			// SciDRmu
			std::ifstream mufSciDR(TString(mufiles[(k*7)+5]));
			std::vector<double> vEvIDSDRmu;
			std::vector<double> vEdepSDRmu;
			  
			while (!mufSciDR.eof()) {
			   double EvIDSDRmu, EdepSDRmu;
			   mufSciDR >> EvIDSDRmu >> EdepSDRmu;
			   vEvIDSDRmu.push_back(EvIDSDRmu);
			   vEdepSDRmu.push_back(EdepSDRmu);
			}
			vEvIDSDRmu.pop_back(); vEdepSDRmu.pop_back();
			vEvIDSDRmu.pop_back(); vEdepSDRmu.pop_back();
			  
			mufSciDR.close();
			allvEvIDSDRmu.push_back(vEvIDSDRmu);
			allvEdepSDRmu.push_back(vEdepSDRmu);


			// BGOD1mu
			std::ifstream mufBGOD1(TString(mufiles[(k*7)+6]));
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

         }  



			  

			
		 //-------------------------------------------------------------------
		 //                     Bin-by-bin analysis
		 //                          Mu-decay
		 //-------------------------------------------------------------------     

			
		 // X-ray cascade	  
		 for (int i=0; i<allvEvIDBD1xc1.size(); i++) {
      
			std::cout << std::endl;
			std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
			std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
			std::cout << "\033[1;31m--------------------- X-ray cascade ----------------------\033[0m" << std::endl;
			std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


            for (int m=0; m<nsamps; m++) {

			   Ethr = Ethrmu[m];

			   //--------------------------------------------------
			   // Normalisation 2 [absolute] :: cascade 0
			   //-------------------------------------------------- 
			   XXrayN2c0 = 0; XelecN2c0 = 0;
			  
			   for (int a=0; a<allvEvIDBD1xc0[0].size(); a++) {

			      if ((allvEdepSD1xc0[i][a] < Ethr1) && (allvEdepSD2xc0[i][a] < Ethr1)) {
				     if ((allvEdepBD1xc0[i][a] > Ethr) && (allvEdepBD1xc0[i][a] < Ethr22)) {
					    if ((allvEdepSDTxc0[i][a] < Ethr3) || (allvEdepSDTxc0[i][a] < Ethr3) || (allvEdepSDLxc0[i][a] < Ethr3) || (allvEdepSDRxc0[i][a] < Ethr3)) {
						   XXrayN2c0 += 1;
						} else { XelecN2c0 += 1; }
					 } else { XelecN2c0 += 1; }
				  } else { XelecN2c0 += 1; }
			   }
				 
			   PXXvectorN2c0[i][m] = XXrayN2c0/(double)(counterXXN2);
			   PXevectorN2c0[i][m] = XelecN2c0/(double)(counterXXN2); 
				

			   //--------------------------------------------------
			   // Normalisation 2 [absolute] :: cascade 1
			   //-------------------------------------------------- 
			   XXrayN2c1 = 0; XelecN2c1 = 0;
			  
			   for (int a=0; a<allvEvIDBD1xc1[0].size(); a++) {

			      if ((allvEdepSD1xc1[i][a] < Ethr1) && (allvEdepSD2xc1[i][a] < Ethr1)) {
				     if ((allvEdepBD1xc1[i][a] > Ethr) && (allvEdepBD1xc1[i][a] < Ethr22)) {
					    if ((allvEdepSDTxc1[i][a] < Ethr3) || (allvEdepSDTxc1[i][a] < Ethr3) || (allvEdepSDLxc1[i][a] < Ethr3) || (allvEdepSDRxc1[i][a] < Ethr3)) {
						   XXrayN2c1 += 1;
						} else { XelecN2c1 += 1; }
					 } else { XelecN2c1 += 1; }
				  } else { XelecN2c1 += 1; }
			   }
				 
			   PXXvectorN2c1[i][m] = XXrayN2c1/(double)(counterXXN2);
			   PXevectorN2c1[i][m] = XelecN2c1/(double)(counterXXN2); 
				
			  
			   //--------------------------------------------------
			   // Normalisation 2 [absolute] :: cascade 2
			   //-------------------------------------------------- 
			   XXrayN2c2 = 0; XelecN2c2 = 0;
			  
			   for (int a=0; a<allvEvIDBD1xc2[0].size(); a++) {

			      if ((allvEdepSD1xc2[i][a] < Ethr1) && (allvEdepSD2xc2[i][a] < Ethr1)) {
				     if ((allvEdepBD1xc2[i][a] > Ethr) && (allvEdepBD1xc2[i][a] < Ethr22)) {
					    if ((allvEdepSDTxc2[i][a] < Ethr3) || (allvEdepSDTxc2[i][a] < Ethr3) || (allvEdepSDLxc2[i][a] < Ethr3) || (allvEdepSDRxc2[i][a] < Ethr3)) {
						   XXrayN2c2 += 1;
						} else { XelecN2c2 += 1; }
					 } else { XelecN2c2 += 1; }
				  } else { XelecN2c2 += 1; }
			   }
				 
			   PXXvectorN2c2[i][m] = XXrayN2c2/(double)(counterXXN2);
			   PXevectorN2c2[i][m] = XelecN2c2/(double)(counterXXN2); 
							   
			   
			   //--------------------------------------------------
			   // Normalisation 2 [absolute] :: cascade 3
			   //-------------------------------------------------- 
			   XXrayN2c3 = 0; XelecN2c3 = 0;
			  
			   for (int a=0; a<allvEvIDBD1xc3[0].size(); a++) {

			      if ((allvEdepSD1xc3[i][a] < Ethr1) && (allvEdepSD2xc3[i][a] < Ethr1)) {
				     if ((allvEdepBD1xc3[i][a] > Ethr) && (allvEdepBD1xc3[i][a] < Ethr22)) {
					    if ((allvEdepSDTxc3[i][a] < Ethr3) || (allvEdepSDTxc3[i][a] < Ethr3) || (allvEdepSDLxc3[i][a] < Ethr3) || (allvEdepSDRxc3[i][a] < Ethr3)) {
						   XXrayN2c3 += 1;
						} else { XelecN2c3 += 1; }
					 } else { XelecN2c3 += 1; }
				  } else { XelecN2c3 += 1; }
			   }
				 
			   PXXvectorN2c3[i][m] = XXrayN2c3/(double)(counterXXN2);
			   PXevectorN2c3[i][m] = XelecN2c3/(double)(counterXXN2); 
				

			   //--------------------------------------------------
			   // Normalisation 2 [absolute] :: mu-decay
			   //-------------------------------------------------- 
			   eXrayN2 = 0; eelecN2 = 0;
			  
			   for (int a=0; a<allvEvIDBD1mu[0].size(); a++) {

			      if ((allvEdepSD1mu[i][a] < Ethr1) && (allvEdepSD2mu[i][a] < Ethr1)) {
				     if ((allvEdepBD1mu[i][a] > Ethr) && (allvEdepBD1mu[i][a] < Ethr22)) {
					    if ((allvEdepSDTmu[i][a] < Ethr3) || (allvEdepSDTmu[i][a] < Ethr3) || (allvEdepSDLmu[i][a] < Ethr3) || (allvEdepSDRmu[i][a] < Ethr3)) {
						   eXrayN2 += 1;
						} else { eelecN2 += 1; }
					 } else { eelecN2 += 1; }
				  } else { eelecN2 += 1; }
			   }
				 
			   PeXvectorN2[i][m] = eXrayN2/(double)(countereeN2);
			   PeevectorN2[i][m] = eelecN2/(double)(countereeN2); 



			  
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
		 float PXXarrN2c0[nsamps] = {}; // X-ray cascade
		 float PXXarrN2c1[nsamps] = {};
         float PXXarrN2c2[nsamps] = {};
         float PXXarrN2c3[nsamps] = {};
         float PeXarrN2[nsamps] = {};
         float PeXXXarrN2c0r[nsamps] = {};
         float PeXXXarrN2c1r[nsamps] = {};
         float PeXXXarrN2c2r[nsamps] = {};
         float PeXXXarrN2c3r[nsamps] = {};

		 	   
		 for (int i=0; i<nsamps; i++) {
			// Normalisation 2 [absolute]
			PXXarrN2c0[i] = PXXvectorN2c0[0][i];
			PXXarrN2c1[i] = PXXvectorN2c1[0][i];
			PXXarrN2c2[i] = PXXvectorN2c2[0][i];
			PXXarrN2c3[i] = PXXvectorN2c3[0][i];
			PeXarrN2[i] = PeXvectorN2[0][i];
			PeXXXarrN2c0r[i] = (PeXvectorN2[0][i])/(double)(PXXvectorN2c0[0][i]);
			PeXXXarrN2c1r[i] = (PeXvectorN2[0][i])/(double)(PXXvectorN2c1[0][i]);
			PeXXXarrN2c2r[i] = (PeXvectorN2[0][i])/(double)(PXXvectorN2c2[0][i]);
			PeXXXarrN2c3r[i] = (PeXvectorN2[0][i])/(double)(PXXvectorN2c3[0][i]);
		 }	   

		  
		 TCanvas *d = new TCanvas("d","E_{THR}",800,600);
		 d->Divide(2,1);
		 d->cd(1);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPXXN2c0 = new TGraph(nsamps,Ethrmu,PXXarrN2c0);
		 grPXXN2c0->SetTitle("X-ray cascades: 0, 1, 2, 3 :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]"); 
		 grPXXN2c0->GetXaxis()->SetTitle("E_{THR} [MeV]");
		 grPXXN2c0->GetXaxis()->SetRangeUser(0,2.05);
		 grPXXN2c0->GetYaxis()->SetRangeUser(3e-1,1.1);
		 grPXXN2c0->GetYaxis()->SetMoreLogLabels(1);
		 grPXXN2c0->GetYaxis()->SetTitle("P_{X->X}(E_{THR})");
		 grPXXN2c0->GetYaxis()->SetTitleOffset(1.8);
		 //grPXXN2c0->SetMarkerColor(kRed);
		 //grPXXN2c0->SetMarkerStyle(31);
		 grPXXN2c0->SetLineColor(kRed);
		 grPXXN2c0->SetLineWidth(3);
		 grPXXN2c0->Draw("ALP");
		 TGraph *grPXXN2c1 = new TGraph(nsamps,Ethrmu,PXXarrN2c1); 
		 grPXXN2c1->SetLineColor(kBlack);
		 grPXXN2c1->SetLineWidth(3);
		 grPXXN2c1->Draw("LP");
		 TGraph *grPXXN2c2 = new TGraph(nsamps,Ethrmu,PXXarrN2c2); 
		 grPXXN2c2->SetLineColor(kGreen-2);
		 grPXXN2c2->SetLineWidth(3);
		 grPXXN2c2->Draw("LP");  		   
		 TGraph *grPXXN2c3 = new TGraph(nsamps,Ethrmu,PXXarrN2c3); 
		 grPXXN2c3->SetLineColor(kMagenta+2);
		 grPXXN2c3->SetLineWidth(3);
		 grPXXN2c3->Draw("LP");  		   
         legPXXN2 = new TLegend(0.2,-0.005,0.4,0.08);
         legPXXN2->AddEntry(grPXXN2c0,"Cascade 0","lp");
		 legPXXN2->AddEntry(grPXXN2c1,"Cascade 1","lp");
		 legPXXN2->AddEntry(grPXXN2c2,"Cascade 2","lp");
		 legPXXN2->AddEntry(grPXXN2c3,"Cascade 3","lp");
		 legPXXN2->Draw();

         d->cd(2);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPeXXXN2c3r = new TGraph(nsamps,Ethrmu,PeXXXarrN2c3r);
		 grPeXXXN2c3r->SetTitle("X-ray cascades: 0, 1, 2, 3 :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]");
		 grPeXXXN2c3r->GetXaxis()->SetTitle("E_{THR} [MeV]");
		 grPeXXXN2c3r->GetXaxis()->SetRangeUser(0,2.05);
		 grPeXXXN2c3r->GetYaxis()->SetMoreLogLabels(1);
		 grPeXXXN2c3r->GetYaxis()->SetTitle("#frac{P_{e->X}}{P_{X->X}}(E_{THR})");
		 grPeXXXN2c3r->GetYaxis()->SetTitleOffset(1.7);
		 grPeXXXN2c3r->SetLineColor(kMagenta+2);
		 grPeXXXN2c3r->SetLineWidth(3);
		 grPeXXXN2c3r->Draw("ALP");
		 TGraph *grPeXXXN2c0r = new TGraph(nsamps,Ethrmu,PeXXXarrN2c0r);
		 grPeXXXN2c0r->SetLineColor(kRed);
		 grPeXXXN2c0r->SetLineWidth(3);
		 grPeXXXN2c0r->Draw("LP");
		 TGraph *grPeXXXN2c1r = new TGraph(nsamps,Ethrmu,PeXXXarrN2c1r);
		 grPeXXXN2c1r->SetLineColor(kBlack);
		 grPeXXXN2c1r->SetLineWidth(3);
		 grPeXXXN2c1r->Draw("LP");
		 TGraph *grPeXXXN2c2r = new TGraph(nsamps,Ethrmu,PeXXXarrN2c2r);
		 grPeXXXN2c2r->SetLineColor(kGreen-2);
		 grPeXXXN2c2r->SetLineWidth(3);
		 grPeXXXN2c2r->Draw("LP");
		 legPeXXXN2r = new TLegend(0.2,-0.005,0.4,0.08);
		 legPeXXXN2r->AddEntry(grPeXXXN2c0r,"Cascade 0","lp");
		 legPeXXXN2r->AddEntry(grPeXXXN2c1r,"Cascade 1","lp");
		 legPeXXXN2r->AddEntry(grPeXXXN2c2r,"Cascade 2","lp");
		 legPeXXXN2r->AddEntry(grPeXXXN2c3r,"Cascade 3","lp");
		 legPeXXXN2r->Draw();

		 d->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shift_cascades_comb_MULTIplicities_eff.pdf");
		 d->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shift_cascades_comb_MULTIplicities_eff.png");
		 d->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shift_cascades_comb_MULTIplicities_eff.C");


/*		   		   
		 TCanvas *c = new TCanvas("c","E_{THR}",800,600);
		 c->Divide(2,2);
		 c->cd(1);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPeXXXN2c0r = new TGraph(nsamps,Ethrmu,PeXXXarrN2c0r);
		 grPeXXXN2c0r->SetTitle("Cascade 0 :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]");
		 grPeXXXN2c0r->GetXaxis()->SetTitle("E_{THR} [MeV]");
		 grPeXXXN2c0r->GetXaxis()->SetRangeUser(0,2.05);
		 grPeXXXN2c0r->GetYaxis()->SetMoreLogLabels(1);
		 grPeXXXN2c0r->GetYaxis()->SetTitle("#frac{P_{e->X}}{P_{X->X}}(E_{THR})");
		 grPeXXXN2c0r->GetYaxis()->SetTitleOffset(1.7);
		 grPeXXXN2c0r->SetLineColor(kRed);
		 grPeXXXN2c0r->SetLineWidth(3);
		 grPeXXXN2c0r->Draw("ALP");
		 legPeXXXN2c0r = new TLegend(0.2,-0.005,0.4,0.08);
		 legPeXXXN2c0r->AddEntry(grPeXXXN2c0r,"Cascade 0","lp");
		 legPeXXXN2c0r->Draw();

         c->cd(2);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPeXXXN2c1r = new TGraph(nsamps,Ethrmu,PeXXXarrN2c1r);
		 grPeXXXN2c1r->SetTitle("Cascade 1 :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]");
		 grPeXXXN2c1r->GetXaxis()->SetTitle("E_{THR} [MeV]");
		 grPeXXXN2c1r->GetXaxis()->SetRangeUser(0,2.05);
		 grPeXXXN2c1r->GetYaxis()->SetMoreLogLabels(1);
		 grPeXXXN2c1r->GetYaxis()->SetTitle("#frac{P_{e->X}}{P_{X->X}}(E_{THR})");
		 grPeXXXN2c1r->GetYaxis()->SetTitleOffset(1.7);
		 grPeXXXN2c1r->SetLineColor(kBlack);
		 grPeXXXN2c1r->SetLineWidth(3);
		 grPeXXXN2c1r->Draw("ALP");
		 legPeXXXN2c1r = new TLegend(0.2,-0.005,0.4,0.08);
		 legPeXXXN2c1r->AddEntry(grPeXXXN2c1r,"Cascade 1","lp");
		 legPeXXXN2c1r->Draw();

         c->cd(3);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPeXXXN2c2r = new TGraph(nsamps,Ethrmu,PeXXXarrN2c2r);
		 grPeXXXN2c2r->SetTitle("Cascade 2 :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]");
		 grPeXXXN2c2r->GetXaxis()->SetTitle("E_{THR} [MeV]");
		 grPeXXXN2c2r->GetXaxis()->SetRangeUser(0,2.05);
		 grPeXXXN2c2r->GetYaxis()->SetMoreLogLabels(1);
		 grPeXXXN2c2r->GetYaxis()->SetTitle("#frac{P_{e->X}}{P_{X->X}}(E_{THR})");
		 grPeXXXN2c2r->GetYaxis()->SetTitleOffset(1.7);
		 grPeXXXN2c2r->SetLineColor(kGreen-2);
		 grPeXXXN2c2r->SetLineWidth(3);
		 grPeXXXN2c2r->Draw("ALP");
		 legPeXXXN2c2r = new TLegend(0.2,-0.005,0.4,0.08);
		 legPeXXXN2c2r->AddEntry(grPeXXXN2c2r,"Cascade 2","lp");
		 legPeXXXN2c2r->Draw();

		 c->cd(4);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPeXXXN2c3r = new TGraph(nsamps,Ethrmu,PeXXXarrN2c3r);
		 grPeXXXN2c3r->SetTitle("Cascade 3 :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]");
		 grPeXXXN2c3r->GetXaxis()->SetTitle("E_{THR} [MeV]");
		 grPeXXXN2c3r->GetXaxis()->SetRangeUser(0,2.05);
		 grPeXXXN2c3r->GetYaxis()->SetMoreLogLabels(1);
		 grPeXXXN2c3r->GetYaxis()->SetTitle("#frac{P_{e->X}}{P_{X->X}}(E_{THR})");
		 grPeXXXN2c3r->GetYaxis()->SetTitleOffset(1.7);
		 grPeXXXN2c3r->SetLineColor(kMagenta+2);
		 grPeXXXN2c3r->SetLineWidth(3);
		 grPeXXXN2c3r->Draw("ALP");
		 legPeXXXN2c3r = new TLegend(0.2,-0.005,0.4,0.08);
		 legPeXXXN2c3r->AddEntry(grPeXXXN2c3r,"Cascade 3","lp");
		 legPeXXXN2c3r->Draw();
		 
		 c->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shift_cascades_MULTIplicities_eff.pdf");
		 c->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shift_cascades_MULTIplicities_eff.png");
		 c->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shift_cascades_MULTIplicities_eff.C");
*/		  

      }

  
   }  


 }
 
 
 int main() {
   modbeamMULTIeff();
   return 0;
}  
