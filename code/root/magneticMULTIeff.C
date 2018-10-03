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

void magneticMULTIeff(){

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
   //std::string filemuSciDF = "../../simdata/magnetic/adBfield_5T_wider_4mm_Al_det_BGO1e5mudecay_SciDF.txt";
   std::string filemuTubeD = "../../simdata/magnetic/adBfield_5T_wider_noSDF_4mm_Al_det_BGO1e5mudecay_TubeD.txt";
   std::string filemuSciDE = "../../simdata/magnetic/adBfield_5T_wider_noSDF_4mm_Al_det_BGO1e5mudecay_SciDE.txt";
   // X-ray cascade
   //std::string filexSciDF = "../../simdata/magnetic/adBfield_5T_wider_4mm_Al_det_BGO1e5goldcascade_SciDF.txt";
   std::string filexTubeD = "../../simdata/magnetic/adBfield_5T_wider_noSDF_4mm_Al_det_BGO1e5goldcascade_TubeD.txt";
   std::string filexSciDE = "../../simdata/magnetic/adBfield_5T_wider_noSDF_4mm_Al_det_BGO1e5goldcascade_SciDE.txt";


   // Vectors with filenames   
   std::vector<std::string> mufiles;
   std::vector<std::string> Xfiles;

   // Mu-decay
   //mufiles.push_back(filemuSciDF);
   mufiles.push_back(filemuTubeD);
   mufiles.push_back(filemuSciDE);
   // X-ray cascade
   //Xfiles.push_back(filexSciDF);
   Xfiles.push_back(filexTubeD);
   Xfiles.push_back(filexSciDE);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep, EventID;
   float iEventID;

   const int nsamps = 101;
   float Ethr1 = 0.5;
   float Ethr21 = 0.5;
   float Ethr22 = 8;
   float Ethr3 = 0.5;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
   
   // Storage vectors
   // Normalisation 1 [rel = intrinsic]
   std::vector< std::vector<double> > PeevectorN1(mufiles.size()/2,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorN1(mufiles.size()/2,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXevectorN1(Xfiles.size()/2,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorN1(Xfiles.size()/2,std::vector<double>(nsamps));
   // Normalisation 2 [abs = total]
   std::vector< std::vector<double> > PeevectorN2(mufiles.size()/2,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorN2(mufiles.size()/2,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXevectorN2(Xfiles.size()/2,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorN2(Xfiles.size()/2,std::vector<double>(nsamps));      


   // Mu-decay
   //std::vector< std::vector< double > > allvEvIDSDFmu;
   //std::vector< std::vector< double > > allvEdepSDFmu;
   std::vector< std::vector< double > > allvEvIDTDmu;
   std::vector< std::vector< double > > allvEdepTDmu;
   std::vector< std::vector< double > > allvEvIDSDEmu;
   std::vector< std::vector< double > > allvEdepSDEmu;

   // X-ray cascade
   //std::vector< std::vector< double > > allvEvIDSDFx;
   //std::vector< std::vector< double > > allvEdepSDFx;
   std::vector< std::vector< double > > allvEvIDTDx;
   std::vector< std::vector< double > > allvEdepTDx;
   std::vector< std::vector< double > > allvEvIDSDEx;
   std::vector< std::vector< double > > allvEdepSDEx;
   

   float Ethr;
   int counterXX, counteree;
   int counterXXN2 = 1e5; int countereeN2 = 1e5; 
   int XXrayN1 = 0; // X-rays i-fied as X-rays
   int XXrayN2 = 0;
   int XelecN1 = 0; // X-rays i-fied as electrons
   int XelecN2 = 0;
   int eXrayN1 = 0; // electrons i-fied as X-rays
   int eXrayN2 = 0;
   int eelecN1 = 0; // electrons i-fied as electrons
   int eelecN2 = 0;
   
   Ethrmu[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;


   //-------------------------------------------------------------------
   //                           Reading
   //-------------------------------------------------------------------


   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Mu-decay --------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


   for (int k=0; k<((mufiles.size())/2); k++) {
/*      
      // SciDF
      std::ifstream mufSciDF(TString(mufiles[k*3]));
      std::vector<double> vEvIDSDFmu;
      std::vector<double> vEdepSDFmu;
      
      while (!mufSciDF.eof()) {
	     double EvIDSDF, EdepSDF;
	     mufSciDF >> EvIDSDF >> EdepSDF;
	     vEvIDSDFmu.push_back(EvIDSDF);
	     vEdepSDFmu.push_back(EdepSDF);
	  }
	  vEvIDSDFmu.pop_back(); vEdepSDFmu.pop_back();
	  vEvIDSDFmu.pop_back(); vEdepSDFmu.pop_back();
      
      mufSciDF.close();
      allvEvIDSDFmu.push_back(vEvIDSDFmu);
      allvEdepSDFmu.push_back(vEdepSDFmu);
*/      
       
      // TubeD
      std::ifstream mufTubeD(TString(mufiles[k*2]));      
      std::vector<double> vEvIDTDmu;
      std::vector<double> vEdepTDmu;
      
      while (!mufTubeD.eof()) {
	     double EvIDTD, EdepTD;
	     mufTubeD >> EvIDTD >> EdepTD;
	     vEvIDTDmu.push_back(EvIDTD);
	     vEdepTDmu.push_back(EdepTD);
	  }
	  vEvIDTDmu.pop_back(); vEdepTDmu.pop_back();
	  vEvIDTDmu.pop_back(); vEdepTDmu.pop_back();
	     
	  mufTubeD.close();
	  allvEvIDTDmu.push_back(vEvIDTDmu);
	  allvEdepTDmu.push_back(vEdepTDmu);   
      

      // SciDE
      std::ifstream mufSciDE(TString(mufiles[(k*2)+1]));
      std::vector<double> vEvIDSDEmu;
      std::vector<double> vEdepSDEmu;
      
      while (!mufSciDE.eof()) {
	     double EvIDSDE, EdepSDE;
	     mufSciDE >> EvIDSDE >> EdepSDE;
	     vEvIDSDEmu.push_back(EvIDSDE);
	     vEdepSDEmu.push_back(EdepSDE);
	  }
	  vEvIDSDEmu.pop_back(); vEdepSDEmu.pop_back();
	  vEvIDSDEmu.pop_back(); vEdepSDEmu.pop_back();
      
      mufSciDE.close();
      allvEvIDSDEmu.push_back(vEvIDSDEmu);
      allvEdepSDEmu.push_back(vEdepSDEmu);
	     

   }
   
   
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m------------------- X-ray cascade ------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


   for (int k=0; k<((Xfiles.size())/2); k++) {
/*
	  // SciDF
      std::ifstream xfSciDF(TString(Xfiles[k*3]));
      std::vector<double> vEvIDSDFx;
      std::vector<double> vEdepSDFx;	   
	   
	  while (!xfSciDF.eof()) {
	     double EvIDSDF, EdepSDF;
	     xfSciDF >> EvIDSDF >> EdepSDF;
	     vEvIDSDFx.push_back(EvIDSDF);
	     vEdepSDFx.push_back(EdepSDF);
	  }
	  vEvIDSDFx.pop_back(); vEdepSDFx.pop_back();
	  vEvIDSDFx.pop_back(); vEdepSDFx.pop_back();
	  
	  xfSciDF.close();
	  allvEvIDSDFx.push_back(vEvIDSDFx);
	  allvEdepSDFx.push_back(vEdepSDFx); 
*/ 
	   
      // TubeD
      std::ifstream xfTubeD(TString(Xfiles[k*2]));
      std::vector<double> vEvIDTDx;
      std::vector<double> vEdepTDx;	   
	   
	  while (!xfTubeD.eof()) {
	     double EvIDTD, EdepTD;
	     xfTubeD >> EvIDTD >> EdepTD;
	     vEvIDTDx.push_back(EvIDTD);
	     vEdepTDx.push_back(EdepTD);
	  }
	  vEvIDTDx.pop_back(); vEdepTDx.pop_back();
	  vEvIDTDx.pop_back(); vEdepTDx.pop_back();
	  
	  xfTubeD.close();
	  allvEvIDTDx.push_back(vEvIDTDx);
	  allvEdepTDx.push_back(vEdepTDx); 


      // SciDE
      std::ifstream xfSciDE(TString(Xfiles[(k*2)+1]));   
      std::vector<double> vEvIDSDEx;
      std::vector<double> vEdepSDEx;	   
	   
	  while (!xfSciDE.eof()) {
	     double EvIDSDE, EdepSDE;
	     xfSciDE >> EvIDSDE >> EdepSDE;
	     vEvIDSDEx.push_back(EvIDSDE);
	     vEdepSDEx.push_back(EdepSDE);
	  }
	  vEvIDSDEx.pop_back(); vEdepSDEx.pop_back();
	  vEvIDSDEx.pop_back(); vEdepSDEx.pop_back();
	  
	  xfSciDE.close();
	  allvEvIDSDEx.push_back(vEvIDSDEx);
	  allvEdepSDEx.push_back(vEdepSDEx); 


   }
      

    
   //-------------------------------------------------------------------
   //                     Bin-by-bin analysis
   //                          Mu-decay
   //-------------------------------------------------------------------     
     
    
   // Mu-decay  
   for (int i=0; i<allvEvIDTDmu.size(); i++) {

      std::cout << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------- Mu-decay -------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


      for (int m=0; m < nsamps; m++) {

         Ethr = Ethrmu[m];

         counteree = 0;
         for (int a=0; a<allvEvIDSDEmu[0].size(); a++) {
	        if (allvEdepSDEmu[i][a] > Ethr3) {
			   counteree++;
			}
	     }
	     


         //--------------------------------------------------
         // Normalisation 1 [relative]
         //--------------------------------------------------         
         eXrayN1 = 0; eelecN1 = 0;
      
         for (int a=0; a<allvEvIDSDEmu[0].size(); a++) {
         
//            if (allvEdepSDFmu[i][a] < Ethr1) {					
			   if (((allvEdepTDmu[i][a]) > Ethr) && (allvEdepTDmu[i][a] < Ethr22)) {
			      if (allvEdepSDEmu[i][a] < Ethr3) {
				     eXrayN1 += 1;
				  } else {
				     eelecN1 += 1;
				  }
			   } else { eelecN1 += 1; }
//			} else { eelecN1 += 1; }
		 }
		 
         PeXvectorN1[i][m] = eXrayN1/(double)(counteree);
         PeevectorN1[i][m] = eelecN1/(double)(counteree); 
         
         std::cout << std::endl;
         //std::cout << "TEST: eX + ee = " << eXrayN1 << " + " << eelecN1 << " and total = " << eXrayN1+eelecN1 << " / " << counteree << " = " << (eXrayN1+eelecN1)/((double)(counteree)) << std::endl;
         std::cout << "PeXvectorN1[" << i << "][" << m << "] = " << PeXvectorN1[i][m] << std::endl;
         


         //--------------------------------------------------
         // Normalisation 2 [absolute]
         //--------------------------------------------------         
         eXrayN2 = 0; eelecN2 = 0;
      
         for (int a=0; a<allvEvIDSDEmu[0].size(); a++) {

//            if (allvEdepSDFmu[i][a] < Ethr1) {
			   if (((allvEdepTDmu[i][a]) > Ethr) && (allvEdepTDmu[i][a] < Ethr22)) {
			      if (allvEdepSDEmu[i][a] < Ethr3) {
				     eXrayN2 += 1;
				  } else {
				     eelecN2 += 1;
				  }
			   } else { eelecN2 += 1; }
//			} else { eelecN2 += 1; }
		 }
			   
         PeXvectorN2[i][m] = eXrayN2/(double)(countereeN2);
         PeevectorN2[i][m] = eelecN2/(double)(countereeN2); 
        
         //std::cout << "TEST: eX + ee = " << eXrayN2 << " + " << eelecN2 << " and total = " << eXrayN2+eelecN2 << " / " << countereeN2 << " = " << (eXrayN2+eelecN2)/((double)(countereeN2)) << std::endl;
         std::cout << "PeXvectorN2[" << i << "][" << m << "] = " << PeXvectorN2[i][m] << std::endl;
        
      
      }   

      std::cout << "counteree = " << counteree << " countereeN2 = " << countereeN2 << std::endl;
        
   }

    
   // X-ray cascade	  
   for (int i=0; i<allvEvIDTDx.size(); i++) {

      std::cout << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m--------------------- X-ray cascade ----------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


      for (int m=0; m < nsamps; m++) {

         Ethr = Ethrmu[m];

         counterXX = 0; 	
         for (int a=0; a<allvEvIDSDEx[0].size(); a++) {
		    //if (allvEdepSDEx[i][a] > Ethr3) {
		    //if (allvEdepTDx[i][a] > Ethr21) {
		    if ((allvEdepTDx[i][a] > Ethr21) || (allvEdepSDEx[i][a] > Ethr3)) {
			   counterXX++;
			}
		 }
		 

         //--------------------------------------------------
         // Normalisation 1 [relative]
         //-------------------------------------------------- 
         XXrayN1 = 0; XelecN1 = 0;
      
         for (int a=0; a<allvEvIDTDx[0].size(); a++) {

//            if (allvEdepSDFx[i][a] < Ethr1) {
			   if (((allvEdepTDx[i][a]) > Ethr) && (allvEdepTDx[i][a] < Ethr22)) {
			      if (allvEdepSDEx[i][a] < Ethr3) {
				     XXrayN1 += 1;
				  } else { XelecN1 += 1; }
			   } else { XelecN1 += 1; }
//			} else { XelecN1 += 1; }
		 }
		 
         PXXvectorN1[i][m] = XXrayN1/(double)(counterXX);
         PXevectorN1[i][m] = XelecN1/(double)(counterXX); 

         std::cout << std::endl;
         //std::cout << "TEST: XX + Xe = " << XXrayN1 << " + " << XelecN1 << " and total = " << XXrayN1+XelecN1 << " / " << counterXX << " = " << (XXrayN1+XelecN1)/((double)(counterXX)) << std::endl;
         std::cout << "PXXvectorN1[" << i << "][" << m << "] = " << PXXvectorN1[i][m] << std::endl;



         //--------------------------------------------------
         // Normalisation 2 [absolute]
         //-------------------------------------------------- 
         XXrayN2 = 0; XelecN2 = 0;
      
         for (int a=0; a<allvEvIDTDx[0].size(); a++) {

//            if (allvEdepSDFx[i][a] < Ethr1) {
			   if (((allvEdepTDx[i][a]) > Ethr) && (allvEdepTDx[i][a] < Ethr22)) {
			      if (allvEdepSDEx[i][a] < Ethr3) {
				     XXrayN2 += 1;
				  } else { XelecN2 += 1; }
			   } else { XelecN2 += 1; }
//			} else { XelecN2 += 1; }
		 }
		 
         PXXvectorN2[i][m] = XXrayN2/(double)(counterXXN2);
         PXevectorN2[i][m] = XelecN2/(double)(counterXXN2); 

         //std::cout << "TEST: XX + Xe = " << XXrayN2 << " + " << XelecN2 << " and total = " << XXrayN2+XelecN2 << " / " << counterXXN2 << " = " << (XXrayN2+XelecN2)/((double)(counterXXN2)) << std::endl;
         std::cout << "PXXvectorN2[" << i << "][" << m << "] = " << PXXvectorN2[i][m] << std::endl;

        
      
      } 
      
      std::cout << "counterXX = " << counterXX << " counterXXN2 = " << counterXXN2 << std::endl;
      std::cout << "counteree = " << counteree << " countereeN2 = " << countereeN2 << std::endl;  
        
   }

   //-------------------------------------------------------------------
   //                     Plotting business
   //-------------------------------------------------------------------     
    
    
   std::cout << std::endl;
   std::cout << "\033[1;33m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;33m-------------------- Plotting business -------------------\033[0m" << std::endl;
   std::cout << "\033[1;33m----------------------------------------------------------\033[0m" << std::endl;

  
   // Array declarations
   // Normalisation 1 [rel]
   float PeXarrN1[nsamps] = {}; // Mu-decay
   float PeearrN1[nsamps] = {};
   float PXXarrN1[nsamps] = {}; // X-ray cascade
   float PXearrN1[nsamps] = {};
   // Normalisation 2 [abs]
   float PeXarrN2[nsamps] = {}; 
   float PeearrN2[nsamps] = {};
   float PXXarrN2[nsamps] = {}; 
   float PXearrN2[nsamps] = {};
   // Ratio of N2 [absolute]
   float PeXXXarrN2r[nsamps] = {};
   
       
   for (int i=0; i<nsamps; i++) {
      // Normalisation 1 [relative]
      PeXarrN1[i] = PeXvectorN1[0][i];
      PeearrN1[i] = PeevectorN1[0][i];
      PXXarrN1[i] = PXXvectorN1[0][i];
      PXearrN1[i] = PXevectorN1[0][i];
      // Normalisation 2 [absolute]
      PeXarrN2[i] = PeXvectorN2[0][i];
      PeearrN2[i] = PeevectorN2[0][i];
      PXXarrN2[i] = PXXvectorN2[0][i];
      PXearrN2[i] = PXevectorN2[0][i];
      // Ratio of N2 [absolute]
      PeXXXarrN2r[i] = (PeXvectorN2[0][i])/(double)(PXXvectorN2[0][i]);
      
      
   }	   
	   

   
   
   TCanvas *c = new TCanvas("c","E_{THR}",800,600);
   c->Divide(3,3);
/*
   c->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPXXN1 = new TGraph(nsamps,Ethrmu,PXXarrN1);
   grPXXN1->SetTitle("N1 normalisation {relative}: 50-mm round BGO [10^6 events]");
   grPXXN1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXXN1->GetXaxis()->SetRangeUser(0,2.05);
   grPXXN1->GetYaxis()->SetRangeUser(1e-6,1.21);
   grPXXN1->GetYaxis()->SetTitle("P_{e/X->X}(E_{THR})");
   grPXXN1->GetYaxis()->SetTitleOffset(1.8);
   grPXXN1->SetMarkerColor(kRed);
   grPXXN1->SetMarkerStyle(31);
   grPXXN1->SetLineColor(kRed);
   grPXXN1->Draw("ALP");
   TGraph *grPeXN1 = new TGraph(nsamps,Ethrmu,PeXarrN1); 
   grPeXN1->SetMarkerColor(kBlack);
   grPeXN1->SetMarkerStyle(33);
   grPeXN1->SetLineColor(kBlack);
   grPeXN1->Draw("LP");
   legPXXPeXN1 = new TLegend(0.2,-0.005,0.4,0.08);
   legPXXPeXN1->AddEntry(grPXXN1,"P_{X->X}","lp");
   legPXXPeXN1->AddEntry(grPeXN1,"P_{e->X}","lp");
   legPXXPeXN1->Draw();
*/
   c->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPXXN2 = new TGraph(nsamps,Ethrmu,PXXarrN2);
   grPXXN2->SetTitle("N2 normalisation {absolute}: 50-mm round BGO [10^6 events]");
   grPXXN2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXXN2->GetXaxis()->SetRangeUser(0,2.05);
   grPXXN2->GetYaxis()->SetRangeUser(1e-6,1.1);
   grPXXN2->GetYaxis()->SetTitle("P_{e/X->X}(E_{THR})");
   grPXXN2->GetYaxis()->SetTitleOffset(1.8);
   grPXXN2->SetMarkerColor(kRed);
   grPXXN2->SetMarkerStyle(31);
   grPXXN2->SetLineColor(kRed);
   grPXXN2->Draw("ALP");
   TGraph *grPeXN2 = new TGraph(nsamps,Ethrmu,PeXarrN2); 
   grPeXN2->SetMarkerColor(kBlack);
   grPeXN2->SetMarkerStyle(33);
   grPeXN2->SetLineColor(kBlack);
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
   grPeXXXN2r->GetYaxis()->SetRangeUser(1e-2,3e-2);
   grPeXXXN2r->GetYaxis()->SetTitle("#frac{P_{e->X}}{P_{X->X}}(E_{THR})");
   grPeXXXN2r->GetYaxis()->SetTitleOffset(1.6);
   grPeXXXN2r->GetYaxis()->SetMoreLogLabels(1);
   grPeXXXN2r->SetLineColor(kBlue+1);
   grPeXXXN2r->SetLineWidth(3);
   grPeXXXN2r->Draw("ALP");
   legPeXXXN2r = new TLegend(0.2,-0.005,0.4,0.08);
   legPeXXXN2r->AddEntry(grPeXXXN2r,"P_{e->X} / P_{X->X}","lp");
   legPeXXXN2r->Draw();


   c->SaveAs("Bfield_5T_wider_noSDF_MULTIplicities_eff.pdf");
   c->SaveAs("Bfield_5T_wider_noSDF_MULTIplicities_eff.png");
   c->SaveAs("Bfield_5T_wider_noSDF_MULTIplicities_eff.C");
  
  
 }
 
 
 int main() {
   magneticMULTIeff();
   return 0;
}  
