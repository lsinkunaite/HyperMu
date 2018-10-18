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

void recoverMULTIeff(){

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
   std::string filemuSciD1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_shifted_1e5mudecay_SciD1.txt";
   std::string filemuSciD2 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_shifted_1e5mudecay_SciD2.txt";
   std::string filemuSciDT = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_shifted_1e5mudecay_SciDT.txt";
   std::string filemuSciDB = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_shifted_1e5mudecay_SciDB.txt";
   std::string filemuSciDL = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_shifted_1e5mudecay_SciDL.txt";
   std::string filemuSciDR = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_shifted_1e5mudecay_SciDR.txt";
   std::string filemuBGOD1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_shifted_1e5mudecay_BGOD1.txt";
   // X-ray cascade
   std::string filexSciD1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_shifted_1e5goldcascade_SciD1.txt";
   std::string filexSciD2 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_shifted_1e5goldcascade_SciD2.txt";
   std::string filexSciDT = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_shifted_1e5goldcascade_SciDT.txt";
   std::string filexSciDB = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_shifted_1e5goldcascade_SciDB.txt";
   std::string filexSciDL = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_shifted_1e5goldcascade_SciDL.txt";
   std::string filexSciDR = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_shifted_1e5goldcascade_SciDR.txt";
   std::string filexBGOD1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_shifted_1e5goldcascade_BGOD1.txt";


   // Vectors with filenames   
   std::vector<std::string> mufiles;
   std::vector<std::string> Xfiles;

   // Mu-decay
   mufiles.push_back(filemuSciD1);
   mufiles.push_back(filemuSciD2);
   mufiles.push_back(filemuSciDT);
   mufiles.push_back(filemuSciDB);
   mufiles.push_back(filemuSciDL);
   mufiles.push_back(filemuSciDR);
   mufiles.push_back(filemuBGOD1);
   // X-ray cascade
   Xfiles.push_back(filexSciD1);
   Xfiles.push_back(filexSciD2);
   Xfiles.push_back(filexSciDT);
   Xfiles.push_back(filexSciDB);
   Xfiles.push_back(filexSciDL);
   Xfiles.push_back(filexSciDR);
   Xfiles.push_back(filexBGOD1);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep, EventID;
   float iEventID;

   const int nsamps = 101;
   float Ethr1 = 0.5;
   float Ethr21 = 0.5;
   float Ethr22 = 8;
   float Ethr3 = 1;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
   
   // Storage vectors
   // Normalisation 2 [abs = total]
   std::vector< std::vector<double> > PeevectorN2(mufiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorN2(mufiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXevectorN2(Xfiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorN2(Xfiles.size()/7,std::vector<double>(nsamps));      

   // Normalisation 3 [abs = total modified (w\o SD1)]
   std::vector< std::vector<double> > PeevectorN3(mufiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorN3(mufiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXevectorN3(Xfiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorN3(Xfiles.size()/7,std::vector<double>(nsamps));      



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

   // X-ray cascade
   std::vector< std::vector< double > > allvEvIDSD1x;
   std::vector< std::vector< double > > allvEdepSD1x;
   std::vector< std::vector< double > > allvEvIDSD2x;
   std::vector< std::vector< double > > allvEdepSD2x;
   std::vector< std::vector< double > > allvEvIDSDTx;
   std::vector< std::vector< double > > allvEdepSDTx;
   std::vector< std::vector< double > > allvEvIDSDBx;
   std::vector< std::vector< double > > allvEdepSDBx;
   std::vector< std::vector< double > > allvEvIDSDLx;
   std::vector< std::vector< double > > allvEdepSDLx;
   std::vector< std::vector< double > > allvEvIDSDRx;
   std::vector< std::vector< double > > allvEdepSDRx;
   std::vector< std::vector< double > > allvEvIDBD1x;
   std::vector< std::vector< double > > allvEdepBD1x;
   

   float Ethr;
   int counterXXN2 = 1e5; int countereeN2 = 1e5; 
   int XXrayN2 = 0; // X-rays i-fied as X-rays
   int XelecN2 = 0; // X-rays i-fied as electrons
   int eXrayN2 = 0; // electrons i-fied as X-rays
   int eelecN2 = 0; // electrons i-fied as electrons

   int XXrayN3 = 0;
   int XelecN3 = 0;
   int eXrayN3 = 0;
   int eelecN3 = 0;
   
   Ethrmu[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;


   //-------------------------------------------------------------------
   //                           Reading
   //-------------------------------------------------------------------


   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Mu-decay --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;



   for (int k=0; k<((mufiles.size())/7); k++) {
   
      // SciD1
      std::ifstream mufSciD1(TString(mufiles[k*7]));
      std::vector<double> vEvIDSD1mu;
      std::vector<double> vEdepSD1mu;
      
      while (!mufSciD1.eof()) {
	     double EvIDSD1, EdepSD1;
	     mufSciD1 >> EvIDSD1 >> EdepSD1;
	     vEvIDSD1mu.push_back(EvIDSD1);
	     vEdepSD1mu.push_back(EdepSD1);
	  }
	  vEvIDSD1mu.pop_back(); vEdepSD1mu.pop_back();
	  vEvIDSD1mu.pop_back(); vEdepSD1mu.pop_back();
	  
	  mufSciD1.close();
	  allvEvIDSD1mu.push_back(vEvIDSD1mu);
	  allvEdepSD1mu.push_back(vEdepSD1mu);


      // SciD2
      std::ifstream mufSciD2(TString(mufiles[(k*7)+1]));
      std::vector<double> vEvIDSD2mu;
      std::vector<double> vEdepSD2mu;
      
      while (!mufSciD2.eof()) {
	     double EvIDSD2, EdepSD2;
	     mufSciD2 >> EvIDSD2 >> EdepSD2;
	     vEvIDSD2mu.push_back(EvIDSD2);
	     vEdepSD2mu.push_back(EdepSD2);
	  }
	  vEvIDSD2mu.pop_back(); vEdepSD2mu.pop_back();
	  vEvIDSD2mu.pop_back(); vEdepSD2mu.pop_back();
	  
	  mufSciD2.close();
	  allvEvIDSD2mu.push_back(vEvIDSD2mu);
	  allvEdepSD2mu.push_back(vEdepSD2mu);
	  
	  
	  // SciDT
      std::ifstream mufSciDT(TString(mufiles[(k*7)+2]));
      std::vector<double> vEvIDSDTmu;
      std::vector<double> vEdepSDTmu;
      
      while (!mufSciDT.eof()) {
	     double EvIDSDT, EdepSDT;
	     mufSciDT >> EvIDSDT >> EdepSDT;
	     vEvIDSDTmu.push_back(EvIDSDT);
	     vEdepSDTmu.push_back(EdepSDT);
	  }
	  vEvIDSDTmu.pop_back(); vEdepSDTmu.pop_back();
	  vEvIDSDTmu.pop_back(); vEdepSDTmu.pop_back();
	  
	  mufSciDT.close();
	  allvEvIDSDTmu.push_back(vEvIDSDTmu);
	  allvEdepSDTmu.push_back(vEdepSDTmu);
	  
	  
	  // SciDB
      std::ifstream mufSciDB(TString(mufiles[(k*7)+3]));
      std::vector<double> vEvIDSDBmu;
      std::vector<double> vEdepSDBmu;
      
      while (!mufSciDB.eof()) {
	     double EvIDSDB, EdepSDB;
	     mufSciDB >> EvIDSDB >> EdepSDB;
	     vEvIDSDBmu.push_back(EvIDSDB);
	     vEdepSDBmu.push_back(EdepSDB);
	  }
	  vEvIDSDBmu.pop_back(); vEdepSDBmu.pop_back();
	  vEvIDSDBmu.pop_back(); vEdepSDBmu.pop_back();
	  
	  mufSciDB.close();
	  allvEvIDSDBmu.push_back(vEvIDSDBmu);
	  allvEdepSDBmu.push_back(vEdepSDBmu);
	  
	  
	  // SciDL
      std::ifstream mufSciDL(TString(mufiles[(k*7)+4]));
      std::vector<double> vEvIDSDLmu;
      std::vector<double> vEdepSDLmu;
      
      while (!mufSciDL.eof()) {
	     double EvIDSDL, EdepSDL;
	     mufSciDL >> EvIDSDL >> EdepSDL;
	     vEvIDSDLmu.push_back(EvIDSDL);
	     vEdepSDLmu.push_back(EdepSDL);
	  }
	  vEvIDSDLmu.pop_back(); vEdepSDLmu.pop_back();
	  vEvIDSDLmu.pop_back(); vEdepSDLmu.pop_back();
	  
	  mufSciDL.close();
	  allvEvIDSDLmu.push_back(vEvIDSDLmu);
	  allvEdepSDLmu.push_back(vEdepSDLmu);
	  
	  
	  // SciDR
      std::ifstream mufSciDR(TString(mufiles[(k*7)+5]));
      std::vector<double> vEvIDSDRmu;
      std::vector<double> vEdepSDRmu;
      
      while (!mufSciDR.eof()) {
	     double EvIDSDR, EdepSDR;
	     mufSciDR >> EvIDSDR >> EdepSDR;
	     vEvIDSDRmu.push_back(EvIDSDR);
	     vEdepSDRmu.push_back(EdepSDR);
	  }
	  vEvIDSDRmu.pop_back(); vEdepSDRmu.pop_back();
	  vEvIDSDRmu.pop_back(); vEdepSDRmu.pop_back();
	  
	  mufSciDR.close();
	  allvEvIDSDRmu.push_back(vEvIDSDRmu);
	  allvEdepSDRmu.push_back(vEdepSDRmu);
	  
	  
	  // BGOD1
      std::ifstream mufBGOD1(TString(mufiles[(k*7)+6]));
      std::vector<double> vEvIDBD1mu;
      std::vector<double> vEdepBD1mu;
      
      while (!mufBGOD1.eof()) {
	     double EvIDBD1, EdepBD1;
	     mufBGOD1 >> EvIDBD1 >> EdepBD1;
	     vEvIDBD1mu.push_back(EvIDBD1);
	     vEdepBD1mu.push_back(EdepBD1);
	  }
	  vEvIDBD1mu.pop_back(); vEdepBD1mu.pop_back();
	  vEvIDBD1mu.pop_back(); vEdepBD1mu.pop_back();
	  
	  mufBGOD1.close();
	  allvEvIDBD1mu.push_back(vEvIDBD1mu);
	  allvEdepBD1mu.push_back(vEdepBD1mu);

   }
   
   
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m------------------- X-ray cascade ------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


   for (int k=0; k<((Xfiles.size())/7); k++) {
      
      // SciD1
      std::ifstream xfSciD1(TString(Xfiles[k*7]));
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
      std::ifstream xfSciD2(TString(Xfiles[(k*7)+1]));
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
	  
	  
	  // SciDT
      std::ifstream xfSciDT(TString(Xfiles[(k*7)+2]));
      std::vector<double> vEvIDSDTx;
      std::vector<double> vEdepSDTx;
      
      while (!xfSciDT.eof()) {
	     double EvIDSDT, EdepSDT;
	     xfSciDT >> EvIDSDT >> EdepSDT;
	     vEvIDSDTx.push_back(EvIDSDT);
	     vEdepSDTx.push_back(EdepSDT);
	  }
	  vEvIDSDTx.pop_back(); vEdepSDTx.pop_back();
	  vEvIDSDTx.pop_back(); vEdepSDTx.pop_back();
	  
	  xfSciDT.close();
	  allvEvIDSDTx.push_back(vEvIDSDTx);
	  allvEdepSDTx.push_back(vEdepSDTx);


      // SciDB
      std::ifstream xfSciDB(TString(Xfiles[(k*7)+3]));
      std::vector<double> vEvIDSDBx;
      std::vector<double> vEdepSDBx;
      
      while (!xfSciDB.eof()) {
	     double EvIDSDB, EdepSDB;
	     xfSciDB >> EvIDSDB >> EdepSDB;
	     vEvIDSDBx.push_back(EvIDSDB);
	     vEdepSDBx.push_back(EdepSDB);
	  }
	  vEvIDSDBx.pop_back(); vEdepSDBx.pop_back();
	  vEvIDSDBx.pop_back(); vEdepSDBx.pop_back();
	  
	  xfSciDB.close();
	  allvEvIDSDBx.push_back(vEvIDSDBx);
	  allvEdepSDBx.push_back(vEdepSDBx);


      // SciDL
      std::ifstream xfSciDL(TString(Xfiles[(k*7)+4]));
      std::vector<double> vEvIDSDLx;
      std::vector<double> vEdepSDLx;
      
      while (!xfSciDL.eof()) {
	     double EvIDSDL, EdepSDL;
	     xfSciDL >> EvIDSDL >> EdepSDL;
	     vEvIDSDLx.push_back(EvIDSDL);
	     vEdepSDLx.push_back(EdepSDL);
	  }
	  vEvIDSDLx.pop_back(); vEdepSDLx.pop_back();
	  vEvIDSDLx.pop_back(); vEdepSDLx.pop_back();
	  
	  xfSciDL.close();
	  allvEvIDSDLx.push_back(vEvIDSDLx);
	  allvEdepSDLx.push_back(vEdepSDLx);


      // SciDR
      std::ifstream xfSciDR(TString(Xfiles[(k*7)+5]));
      std::vector<double> vEvIDSDRx;
      std::vector<double> vEdepSDRx;
      
      while (!xfSciDR.eof()) {
	     double EvIDSDR, EdepSDR;
	     xfSciDR >> EvIDSDR >> EdepSDR;
	     vEvIDSDRx.push_back(EvIDSDR);
	     vEdepSDRx.push_back(EdepSDR);
	  }
	  vEvIDSDRx.pop_back(); vEdepSDRx.pop_back();
	  vEvIDSDRx.pop_back(); vEdepSDRx.pop_back();
	  
	  xfSciDR.close();
	  allvEvIDSDRx.push_back(vEvIDSDRx);
	  allvEdepSDRx.push_back(vEdepSDRx);


      // BGOD1
      std::ifstream xfBGOD1(TString(Xfiles[(k*6)+6]));
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


   }
      

    
   //-------------------------------------------------------------------
   //                     Bin-by-bin analysis
   //                          Mu-decay
   //-------------------------------------------------------------------     
     
    
   // Mu-decay  
   for (int i=0; i<allvEvIDBD1mu.size(); i++) {

      std::cout << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------- Mu-decay -------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


      for (int m=0; m < nsamps; m++) {

         Ethr = Ethrmu[m];

         //--------------------------------------------------
         // Normalisation 2 [absolute]
         //--------------------------------------------------         
         eXrayN2 = 0; eelecN2 = 0;
      
         for (int a=0; a<allvEvIDBD1mu[0].size(); a++) {

//            if (allvEdepSD1mu[i][a] < Ethr1) {
            if ((allvEdepSD1mu[i][a] < Ethr1) && (allvEdepSD2mu[i][a] < Ethr1)) {
		       if ((allvEdepBD1mu[i][a] > Ethr) && (allvEdepBD1mu[i][a] < Ethr22)) {
			      if ((allvEdepSDTmu[i][a] < Ethr3) || (allvEdepSDBmu[i][a] < Ethr3) || (allvEdepSDLmu[i][a] < Ethr3) || (allvEdepSDRmu[i][a] < Ethr3)) {
				     eXrayN2 += 1;
				  } else {
				     eelecN2 += 1;
	        	  }
			   } else { eelecN2 += 1; }
			} else { eelecN2 += 1; }
	     }

			   
         PeXvectorN2[i][m] = eXrayN2/(double)(countereeN2);
         PeevectorN2[i][m] = eelecN2/(double)(countereeN2); 
        
         //std::cout << "TEST: eX + ee = " << eXrayN2 << " + " << eelecN2 << " and total = " << eXrayN2+eelecN2 << " / " << countereeN2 << " = " << (eXrayN2+eelecN2)/((double)(countereeN2)) << std::endl;
         std::cout << "PeXvectorN2[" << i << "][" << m << "] = " << PeXvectorN2[i][m] << std::endl;
        


         //--------------------------------------------------
         // Normalisation 3 [absolute modified]
         //--------------------------------------------------         
         eXrayN3 = 0; eelecN3 = 0;

         for (int a=0; a<allvEvIDBD1mu[0].size(); a++) {
            if (allvEdepSD2mu[i][a] < Ethr1) {
		       if ((allvEdepBD1mu[i][a] > Ethr) && (allvEdepBD1mu[i][a] < Ethr22)) {
			      if ((allvEdepSDTmu[i][a] < Ethr3) || (allvEdepSDBmu[i][a] < Ethr3) || (allvEdepSDLmu[i][a] < Ethr3) || (allvEdepSDRmu[i][a] < Ethr3)) {
				     eXrayN3 += 1;
				  } else {
				     eelecN3 += 1;
	        	  }
			   } else { eelecN3 += 1; }
			} else { eelecN3 += 1; }
	     }


         PeXvectorN3[i][m] = eXrayN3/(double)(countereeN2);
         PeevectorN3[i][m] = eelecN3/(double)(countereeN2); 
        
         //std::cout << "TEST: eX + ee = " << eXrayN2 << " + " << eelecN2 << " and total = " << eXrayN2+eelecN2 << " / " << countereeN2 << " = " << (eXrayN2+eelecN2)/((double)(countereeN2)) << std::endl;
         std::cout << "PeXvectorN3[" << i << "][" << m << "] = " << PeXvectorN3[i][m] << std::endl;


      
      }   


        
   }

    
   // X-ray cascade	  
   for (int i=0; i<allvEvIDBD1x.size(); i++) {

      std::cout << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m--------------------- X-ray cascade ----------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


      for (int m=0; m < nsamps; m++) {

         Ethr = Ethrmu[m];

         //--------------------------------------------------
         // Normalisation 2 [absolute]
         //-------------------------------------------------- 
         XXrayN2 = 0; XelecN2 = 0;
      
         for (int a=0; a<allvEvIDBD1x[0].size(); a++) {

//            if (allvEdepSD1x[i][a] < Ethr1) {
            if ((allvEdepSD1x[i][a] < Ethr1) && (allvEdepSD2x[i][a] < Ethr1)) {
		       if ((allvEdepBD1x[i][a] > Ethr) && (allvEdepBD1x[i][a] < Ethr22)) {
			      if ((allvEdepSDTx[i][a] < Ethr3) || (allvEdepSDTx[i][a] < Ethr3) || (allvEdepSDLx[i][a] < Ethr3) || (allvEdepSDRx[i][a] < Ethr3)) {
				     XXrayN2 += 1;
				  } else {
				     XelecN2 += 1;
				  } else { XelecN2 += 1; }
			   } else {XelecN2 += 1; }
			} else {XelecN2 += 1; }
		 }
		 
         PXXvectorN2[i][m] = XXrayN2/(double)(counterXXN2);
         PXevectorN2[i][m] = XelecN2/(double)(counterXXN2); 

         //std::cout << "TEST: XX + Xe = " << XXrayN2 << " + " << XelecN2 << " and total = " << XXrayN2+XelecN2 << " / " << counterXXN2 << " = " << (XXrayN2+XelecN2)/((double)(counterXXN2)) << std::endl;
         std::cout << "PXXvectorN2[" << i << "][" << m << "] = " << PXXvectorN2[i][m] << std::endl;



         //--------------------------------------------------
         // Normalisation 3 [absolute modified]
         //-------------------------------------------------- 
         XXrayN3 = 0; XelecN3 = 0;
      
         for (int a=0; a<allvEvIDBD1x[0].size(); a++) {
            if (allvEdepSD2x[i][a] < Ethr1) {
		       if ((allvEdepBD1x[i][a] > Ethr) && (allvEdepBD1x[i][a] < Ethr22)) {
			      if ((allvEdepSDTx[i][a] < Ethr3) || (allvEdepSDTx[i][a] < Ethr3) || (allvEdepSDLx[i][a] < Ethr3) || (allvEdepSDRx[i][a] < Ethr3)) {
				     XXrayN3 += 1;
				  } else {
				     XelecN3 += 1;
				  } else { XelecN3 += 1; }
			   } else {XelecN3 += 1; }
			} else {XelecN3 += 1; }
		 }
		 
         PXXvectorN3[i][m] = XXrayN3/(double)(counterXXN2);
         PXevectorN3[i][m] = XelecN3/(double)(counterXXN2); 

         //std::cout << "TEST: XX + Xe = " << XXrayN2 << " + " << XelecN2 << " and total = " << XXrayN2+XelecN2 << " / " << counterXXN2 << " = " << (XXrayN2+XelecN2)/((double)(counterXXN2)) << std::endl;
         std::cout << "PXXvectorN3[" << i << "][" << m << "] = " << PXXvectorN3[i][m] << std::endl;

        
      
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
   float PeXarrN2[nsamps] = {}; // Mu-decay 
   float PeearrN2[nsamps] = {};
   float PXXarrN2[nsamps] = {}; // X-ray cascade
   float PXearrN2[nsamps] = {};
   // Ratio of N2 [absolute]
   float PeXXXarrN2r[nsamps] = {};
   
   // Normalisation 3 [abs modified]
   float PeXarrN3[nsamps] = {}; // Mu-decay 
   float PeearrN3[nsamps] = {};
   float PXXarrN3[nsamps] = {}; // X-ray cascade
   float PXearrN3[nsamps] = {};
   // Ratio of N3 [absolute]
   float PeXXXarrN3r[nsamps] = {};


       
   for (int i=0; i<nsamps; i++) {
      // Normalisation 2 [absolute]
      PeXarrN2[i] = PeXvectorN2[0][i];
      PeearrN2[i] = PeevectorN2[0][i];
      PXXarrN2[i] = PXXvectorN2[0][i];
      PXearrN2[i] = PXevectorN2[0][i];
      // Ratio of N2 [absolute]
      PeXXXarrN2r[i] = (PeXvectorN2[0][i])/(double)(PXXvectorN2[0][i]);
      
      // Normalisation 3 [absolute modified]
      PeXarrN3[i] = PeXvectorN3[0][i];
      PeearrN3[i] = PeevectorN3[0][i];
      PXXarrN3[i] = PXXvectorN3[0][i];
      PXearrN3[i] = PXevectorN3[0][i];
      // Ratio of N3 [absolute modified]
      PeXXXarrN3r[i] = (PeXvectorN3[0][i])/(double)(PXXvectorN3[0][i]);
      
      
      
      
   }	   
	   

   
   
   TCanvas *c = new TCanvas("c","E_{THR}",800,600);
   c->Divide(2,2);
   c->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPXXN2 = new TGraph(nsamps,Ethrmu,PXXarrN2);
   grPXXN2->SetTitle("N2 normalisation {absolute} OR: 4-mm Al, 4-mm Al, 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity Ring, 50-mm #Phi-shift [10^5 events]");
   grPXXN2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXXN2->GetXaxis()->SetRangeUser(0,2.05);
   grPXXN2->GetYaxis()->SetRangeUser(1e-4,1.1);
   grPXXN2->GetYaxis()->SetTitle("P_{e/X->X}(E_{THR})");
   grPXXN2->GetYaxis()->SetTitleOffset(1.8);
   //grPXXN2->SetMarkerColor(kRed);
   //grPXXN2->SetMarkerStyle(31);
   grPXXN2->SetLineColor(kRed);
   grPXXN2->SetLineWidth(3);
   grPXXN2->Draw("ALP");
   TGraph *grPeXN2 = new TGraph(nsamps,Ethrmu,PeXarrN2); 
   //grPeXN2->SetMarkerColor(kBlack);
   //grPeXN2->SetMarkerStyle(33);
   grPeXN2->SetLineColor(kBlack);
   grPeXN2->SetLineWidth(3);
   grPeXN2->Draw("LP");
   legPXXPeXN2 = new TLegend(0.2,-0.005,0.4,0.08);
   legPXXPeXN2->AddEntry(grPXXN2,"P_{X->X}","lp");
   legPXXPeXN2->AddEntry(grPeXN2,"P_{e->X}","lp");
   legPXXPeXN2->Draw();

   c->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeXXXN2r = new TGraph(nsamps,Ethrmu,PeXXXarrN2r);
   grPeXXXN2r->SetTitle("Ratio of P_{e->X} / P_{X->X} vs (E_{THR})");
   grPeXXXN2r->GetXaxis()->SetRangeUser(0,2.05);
   //grPeXXXN2r->GetYaxis()->SetRangeUser(1e-2,3e-2);
   grPeXXXN2r->GetYaxis()->SetTitle("#frac{P_{e->X}}{P_{X->X}}(E_{THR})");
   grPeXXXN2r->GetYaxis()->SetTitleOffset(1.6);
   grPeXXXN2r->GetYaxis()->SetMoreLogLabels(1);
   grPeXXXN2r->SetLineColor(kBlue+1);
   grPeXXXN2r->SetLineWidth(3);
   grPeXXXN2r->Draw("ALP");
   legPeXXXN2r = new TLegend(0.2,-0.005,0.4,0.08);
   legPeXXXN2r->AddEntry(grPeXXXN2r,"P_{e->X} / P_{X->X}","lp");
   legPeXXXN2r->Draw();

   c->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPXXN3 = new TGraph(nsamps,Ethrmu,PXXarrN3);
   grPXXN3->SetTitle("N2 normalisation {no SD_{1}} OR: 4-mm Al, 4-mm Al, 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity Ring, 50-mm #Phi-shift [10^5 events]");
   grPXXN3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXXN3->GetXaxis()->SetRangeUser(0,2.05);
   grPXXN3->GetYaxis()->SetRangeUser(1e-4,1.1);
   grPXXN3->GetYaxis()->SetTitle("P_{e/X->X}(E_{THR})");
   grPXXN3->GetYaxis()->SetTitleOffset(1.8);
   grPXXN3->SetLineColor(kRed);
   grPXXN3->SetLineWidth(3);
   grPXXN3->Draw("ALP");
   TGraph *grPeXN3 = new TGraph(nsamps,Ethrmu,PeXarrN3); 
   grPeXN3->SetLineColor(kBlack);
   grPeXN3->SetLineWidth(3);
   grPeXN3->Draw("LP");
   legPXXPeXN3 = new TLegend(0.2,-0.005,0.4,0.08);
   legPXXPeXN3->AddEntry(grPXXN3,"P_{X->X}","lp");
   legPXXPeXN3->AddEntry(grPeXN3,"P_{e->X}","lp");
   legPXXPeXN3->Draw();

   c->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeXXXN3r = new TGraph(nsamps,Ethrmu,PeXXXarrN3r);
   grPeXXXN3r->SetTitle("Ratio of P_{e->X} / P_{X->X} vs (E_{THR})");
   grPeXXXN3r->GetXaxis()->SetRangeUser(0,2.05);
   grPeXXXN3r->GetYaxis()->SetTitle("#frac{P_{e->X}}{P_{X->X}}(E_{THR})");
   grPeXXXN3r->GetYaxis()->SetTitleOffset(1.6);
   grPeXXXN3r->GetYaxis()->SetMoreLogLabels(1);
   grPeXXXN3r->SetLineColor(kBlue+1);
   grPeXXXN3r->SetLineWidth(3);
   grPeXXXN3r->Draw("ALP");
   legPeXXXN3r = new TLegend(0.2,-0.005,0.4,0.08);
   legPeXXXN3r->AddEntry(grPeXXXN3r,"P_{e->X} / P_{X->X}","lp");
   legPeXXXN3r->Draw();

   c->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_50mm_phi_shift_MULTIplicities_eff.pdf");
   c->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_50mm_phi_shift_MULTIplicities_eff.png");
   c->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_50mm_phi_shift_MULTIplicities_eff.C");
  

 }
 
 
 int main() {
   recoverMULTIeff();
   return 0;
}  
