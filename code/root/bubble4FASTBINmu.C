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

void bubble4FASTBINmu(){

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
   // With {250,500,750}-mm SciD3 3-mm Al
   std::string filemu250SciD1 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay_SciD1.txt";
   std::string filemu250SciD2 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay_SciD2.txt";
   std::string filemu250SciD3 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay_SciD3.txt";
   std::string filemu500SciD1 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay_SciD1.txt";
   std::string filemu500SciD2 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay_SciD2.txt";
   std::string filemu500SciD3 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay_SciD3.txt";
   std::string filemu750SciD1 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay_SciD1.txt";
   std::string filemu750SciD2 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay_SciD2.txt";
   std::string filemu750SciD3 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay_SciD3.txt";
   // With {250,500,750}-mm SciD3 6-mm Al
   std::string file6Almu250SciD1 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay_SciD1.txt";
   std::string file6Almu250SciD2 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay_SciD2.txt";
   std::string file6Almu250SciD3 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay_SciD3.txt";
   std::string file6Almu500SciD1 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay_SciD1.txt";
   std::string file6Almu500SciD2 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay_SciD2.txt";
   std::string file6Almu500SciD3 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay_SciD3.txt"; 
   std::string file6Almu750SciD1 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay_SciD1.txt";
   std::string file6Almu750SciD2 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay_SciD2.txt";
   std::string file6Almu750SciD3 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay_SciD3.txt";
   
   std::vector<std::string> mufiles;

   // mu-decay
   mufiles.push_back(filemu250SciD1);
   mufiles.push_back(filemu250SciD2);
   mufiles.push_back(filemu250SciD3);
   mufiles.push_back(filemu500SciD1);
   mufiles.push_back(filemu500SciD2);
   mufiles.push_back(filemu500SciD3);
   mufiles.push_back(filemu750SciD1);
   mufiles.push_back(filemu750SciD2);
   mufiles.push_back(filemu750SciD3);
   mufiles.push_back(file6Almu250SciD1);
   mufiles.push_back(file6Almu250SciD2);
   mufiles.push_back(file6Almu250SciD3);
   mufiles.push_back(file6Almu500SciD1);
   mufiles.push_back(file6Almu500SciD2);
   mufiles.push_back(file6Almu500SciD3);
   mufiles.push_back(file6Almu750SciD1);
   mufiles.push_back(file6Almu750SciD2);
   mufiles.push_back(file6Almu750SciD3);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep, EventID;
   float iEventID;

   const int nsamps = 101;
   float Ethr3 = 0.5;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
   
   // mu-decay storage vectors
   std::vector< std::vector<double> > Peevector(mufiles.size(),std::vector<double>(nsamps)); // method A
   std::vector< std::vector<double> > PeXvector(mufiles.size(),std::vector<double>(nsamps));
   
   std::vector< std::vector< double > > allvEvID1;
   std::vector< std::vector< double > > allvEvID2;
   std::vector< std::vector< double > > allvEvID3;
   
   std::vector< std::vector< double > > allvEdep1;
   std::vector< std::vector< double > > allvEdep2;
   std::vector< std::vector< double > > allvEdep3;

   float Ethr;
   float tPex, tPeeB, tPexC; 
   int Xray = 0;
   int elec = 0;
   
   Ethrmu[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;


   //-------------------------------------------------------------------
   //                           Reading
   //-------------------------------------------------------------------


   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


   for (int k=0; k<((mufiles.size())/3); k++) {
	  // SciD1
      std::ifstream mufSciD1(TString(mufiles[k*3]));
      std::string mulSciD1;
      std::vector<double> vEvID1;
      std::vector<double> vEdep1;
     
      while (!mufSciD1.eof()) {
         double EvID1, Edep1;
	     mufSciD1 >> EvID1 >> Edep1;
	     vEvID1.push_back(EvID1);
	     vEdep1.push_back(Edep1);
	  }
	  vEvID1.pop_back(); vEdep1.pop_back();    
      vEvID1.pop_back(); vEdep1.pop_back();    
      
      mufSciD1.close();
      allvEvID1.push_back(vEvID1);
      allvEdep1.push_back(vEdep1);


      // SciD2
      std::ifstream mufSciD2(TString(mufiles[(k*3)+1]));
      std::string mulSciD2;
      std::vector<double> vEvID2;
      std::vector<double> vEdep2;
     
      while (!mufSciD2.eof()) {
         double EvID2, Edep2;
	     mufSciD2 >> EvID2 >> Edep2;
	     vEvID2.push_back(EvID2);
	     vEdep2.push_back(Edep2);
	  }
	  vEvID2.pop_back(); vEdep2.pop_back();    
      vEvID2.pop_back(); vEdep2.pop_back();    
      
      mufSciD2.close();
      allvEvID2.push_back(vEvID2);
      allvEdep2.push_back(vEdep2);


      // SciD3
      std::ifstream mufSciD3(TString(mufiles[(k*3)+2]));
      std::string mulSciD3;
      std::vector<double> vEvID3;
      std::vector<double> vEdep3;
     
      while (!mufSciD3.eof()) {
         double EvID3, Edep3;
	     mufSciD3 >> EvID3 >> Edep3;
	     vEvID3.push_back(EvID3);
	     vEdep3.push_back(Edep3);
	  }
	  vEvID3.pop_back(); vEdep3.pop_back();    
      vEvID3.pop_back(); vEdep3.pop_back();    
      
      mufSciD3.close();
      allvEvID3.push_back(vEvID3);
      allvEdep3.push_back(vEdep3);


   }

     
   //-------------------------------------------------------------------
   //                     Bin-by-bin analysis
   //                          Method A
   //-------------------------------------------------------------------     
     
	  
   for (int i=0; i<allvEvID1.size(); i++) {

      std::cout << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------- Method A -------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

	
      for (int m=0; m < nsamps; m++) {
	     Ethr = Ethrmu[m];
         Xray = 0; elec = 0;
         
         std::vector<double> vPeX;
         std::vector<double> vPee;

		 for (int j=0; j<allvEvID1[0].size(); j++) {
			  
			tPex = 0;
			//iEventID = allvEvID1[i][j];
		   
			if (allvEdep1[i][j] < Ethr) {
			   tPex += 1;   
		  
			   //if (allvEvID2[i][j] != iEventID) std::cout << "EventID2 = " << allvEvID2[i][j] << " iEventID = " << iEventID << std::endl;
			   if (allvEdep2[i][j] < Ethr) {
				  tPex += 1;

				  //if (allvEvID3[i][j] != iEventID) std::cout << "EventID3 = " << allvEvID3[i][j] << " iEventID = " << iEventID << std::endl;
				  if ((allvEdep3[i][j] >= Ethr3) && (allvEdep3[i][j] < 6) && (tPex == 2)) {
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

      PeXvector[i][m] = Xray/(double)(allvEvID1[0].size());
      Peevector[i][m] = elec/(double)(allvEvID1[0].size()); 
       
      std::cout << " PeX[" << i << "][" << m << "] = " << PeXvector[i][m] << " Pee[" << i << "][" << m << "] = " << Peevector[i][m] << std::endl;
     

      }   
       
        
   }



   //-------------------------------------------------------------------
   //                     Plotting business
   //-------------------------------------------------------------------     
    
    
   std::cout << std::endl;
   std::cout << "\033[1;33m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;33m-------------------- Plotting business -------------------\033[0m" << std::endl;
   std::cout << "\033[1;33m----------------------------------------------------------\033[0m" << std::endl;



   std::cout << std::endl << "Test :: nsamps = " << nsamps << " and PeXvector = " << PeXvector.size() << std::endl;
  
   // Method A
   float PeXarr250mu[nsamps] = {};
   float Peearr250mu[nsamps] = {};
   float PeXarr500mu[nsamps] = {};
   float Peearr500mu[nsamps] = {};
   float PeXarr750mu[nsamps] = {};
   float Peearr750mu[nsamps] = {};
   float PeXarr250mu6Al[nsamps] = {};
   float Peearr250mu6Al[nsamps] = {};
   float PeXarr500mu6Al[nsamps] = {};
   float Peearr500mu6Al[nsamps] = {};
   float PeXarr750mu6Al[nsamps] = {};
   float Peearr750mu6Al[nsamps] = {};
   
    
   for (int i=0; i<nsamps; i++) {
      PeXarr250mu[i] = PeXvector[0][i];
      Peearr250mu[i] = Peevector[0][i];
      PeXarr500mu[i] = PeXvector[1][i];
      Peearr500mu[i] = Peevector[1][i];
      PeXarr750mu[i] = PeXvector[2][i];
      Peearr750mu[i] = Peevector[2][i];
      PeXarr250mu6Al[i] = PeXvector[3][i];
      Peearr250mu6Al[i] = Peevector[3][i];
      PeXarr500mu6Al[i] = PeXvector[4][i];
      Peearr500mu6Al[i] = Peevector[4][i];
      PeXarr750mu6Al[i] = PeXvector[5][i];
      Peearr750mu6Al[i] = Peevector[5][i];
 
      std::cout << "Ethrmu = " << Ethrmu[i] << ", PeXvector[" << i << "] = " << PeXvector[0][i] << ", Peevector[" << i << "] = " << Peevector[0][i] << std::endl;
 
   }
  
  
   
   TCanvas *c = new TCanvas("c","E_{THR}",800,600);
   c->Divide(3,2);
   c->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr250muSciDet1PeX = new TGraph(nsamps,Ethrmu,PeXarr250mu);
   gr250muSciDet1PeX->SetTitle("6 MeV: 3-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3} [10^6 events]");
   gr250muSciDet1PeX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr250muSciDet1PeX->GetXaxis()->SetRangeUser(0,2.05);
   gr250muSciDet1PeX->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr250muSciDet1PeX->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr250muSciDet1PeX->GetYaxis()->SetTitleOffset(1.8);
   gr250muSciDet1PeX->SetMarkerColor(kBlack);
   gr250muSciDet1PeX->SetMarkerStyle(33);
   gr250muSciDet1PeX->SetLineColor(kBlack);
   gr250muSciDet1PeX->Draw("ALP");
   TGraph *gr250muSciDet1Pee = new TGraph(nsamps,Ethrmu,Peearr250mu); 
   gr250muSciDet1Pee->SetMarkerColor(kRed);
   gr250muSciDet1Pee->SetMarkerStyle(31);
   gr250muSciDet1Pee->SetLineColor(kRed);
   gr250muSciDet1Pee->Draw("LP");
   leg250muSciDet1PeXPee = new TLegend(0.2,-0.005,0.4,0.08);
   leg250muSciDet1PeXPee->AddEntry(gr250muSciDet1PeX,"P_{e->X}","lp");
   leg250muSciDet1PeXPee->AddEntry(gr250muSciDet1Pee,"P_{e->e}","lp");
   leg250muSciDet1PeXPee->Draw();
  
   c->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr500muSciDet1PeX = new TGraph(nsamps,Ethrmu,PeXarr500mu);  
   gr500muSciDet1PeX->SetTitle("6 MeV: 3-mm Al + 2x5-mm SCiD_{1,2} + 500-mm SciD_{3} [10^6 events]");
   gr500muSciDet1PeX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr500muSciDet1PeX->GetXaxis()->SetRangeUser(0,2.05);
   gr500muSciDet1PeX->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr500muSciDet1PeX->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr500muSciDet1PeX->GetYaxis()->SetTitleOffset(1.8);
   gr500muSciDet1PeX->SetMarkerColor(kBlack);
   gr500muSciDet1PeX->SetMarkerStyle(33);
   gr500muSciDet1PeX->SetLineColor(kBlack);
   gr500muSciDet1PeX->Draw("ALP");
   TGraph *gr500muSciDet1Pee = new TGraph(nsamps,Ethrmu,Peearr500mu); 
   gr500muSciDet1Pee->SetMarkerColor(kRed);
   gr500muSciDet1Pee->SetMarkerStyle(31);
   gr500muSciDet1Pee->SetLineColor(kRed);
   gr500muSciDet1Pee->Draw("LP");
   leg500muSciDet1PeXPee = new TLegend(0.2,-0.005,0.4,0.08);
   leg500muSciDet1PeXPee->AddEntry(gr500muSciDet1PeX,"P_{e->X}","lp");
   leg500muSciDet1PeXPee->AddEntry(gr500muSciDet1Pee,"P_{e->e}","lp");
   leg500muSciDet1PeXPee->Draw();

   c->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr750muSciDet1PeX = new TGraph(nsamps,Ethrmu,PeXarr750mu); 
   gr750muSciDet1PeX->SetTitle("6 MeV: 3-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3} [10^6 events]");
   gr750muSciDet1PeX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr750muSciDet1PeX->GetXaxis()->SetRangeUser(0,2.05);
   gr750muSciDet1PeX->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr750muSciDet1PeX->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr750muSciDet1PeX->GetYaxis()->SetTitleOffset(1.8);
   gr750muSciDet1PeX->SetMarkerColor(kBlack);
   gr750muSciDet1PeX->SetMarkerStyle(33);
   gr750muSciDet1PeX->SetLineColor(kBlack);
   gr750muSciDet1PeX->Draw("ALP");
   TGraph *gr750muSciDet1Pee = new TGraph(nsamps,Ethrmu,Peearr750mu); 
   gr750muSciDet1Pee->SetMarkerColor(kRed);
   gr750muSciDet1Pee->SetMarkerStyle(31);
   gr750muSciDet1Pee->SetLineColor(kRed);
   gr750muSciDet1Pee->Draw("LP");
   leg750muSciDet1PeXPee = new TLegend(0.2,-0.005,0.4,0.08);
   leg750muSciDet1PeXPee->AddEntry(gr750muSciDet1PeX,"P_{e->X}","lp");
   leg750muSciDet1PeXPee->AddEntry(gr750muSciDet1Pee,"P_{e->e}","lp");
   leg750muSciDet1PeXPee->Draw();
  
   c->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr250mu6AlSciDet1PeX = new TGraph(nsamps,Ethrmu,PeXarr250mu6Al);
   gr250mu6AlSciDet1PeX->SetTitle("6 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3} [10^6 events]");
   gr250mu6AlSciDet1PeX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr250mu6AlSciDet1PeX->GetXaxis()->SetRangeUser(0,2.05);
   gr250mu6AlSciDet1PeX->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr250mu6AlSciDet1PeX->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr250mu6AlSciDet1PeX->GetYaxis()->SetTitleOffset(1.8);
   gr250mu6AlSciDet1PeX->SetMarkerColor(kBlack);
   gr250mu6AlSciDet1PeX->SetMarkerStyle(33);
   gr250mu6AlSciDet1PeX->SetLineColor(kBlack);
   gr250mu6AlSciDet1PeX->Draw("ALP");
   TGraph *gr250mu6AlSciDet1Pee = new TGraph(nsamps,Ethrmu,Peearr250mu6Al); 
   gr250mu6AlSciDet1Pee->SetMarkerColor(kRed);
   gr250mu6AlSciDet1Pee->SetMarkerStyle(31);
   gr250mu6AlSciDet1Pee->SetLineColor(kRed);
   gr250mu6AlSciDet1Pee->Draw("LP");
   leg250mu6AlSciDet1PeXPee = new TLegend(0.2,-0.005,0.4,0.08);
   leg250mu6AlSciDet1PeXPee->AddEntry(gr250mu6AlSciDet1PeX,"P_{e->X}","lp");
   leg250mu6AlSciDet1PeXPee->AddEntry(gr250mu6AlSciDet1Pee,"P_{e->e}","lp");
   leg250mu6AlSciDet1PeXPee->Draw();
    
   c->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr500mu6AlSciDet1PeX = new TGraph(nsamps,Ethrmu,PeXarr500mu6Al);
   gr500mu6AlSciDet1PeX->SetTitle("6 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3} [10^6 events]");
   gr500mu6AlSciDet1PeX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr500mu6AlSciDet1PeX->GetXaxis()->SetRangeUser(0,2.05);
   gr500mu6AlSciDet1PeX->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr500mu6AlSciDet1PeX->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr500mu6AlSciDet1PeX->GetYaxis()->SetTitleOffset(1.8);
   gr500mu6AlSciDet1PeX->SetMarkerColor(kBlack);
   gr500mu6AlSciDet1PeX->SetMarkerStyle(33);
   gr500mu6AlSciDet1PeX->SetLineColor(kBlack);
   gr500mu6AlSciDet1PeX->Draw("ALP");
   TGraph *gr500mu6AlSciDet1Pee = new TGraph(nsamps,Ethrmu,Peearr500mu6Al); 
   gr500mu6AlSciDet1Pee->SetMarkerColor(kRed);
   gr500mu6AlSciDet1Pee->SetMarkerStyle(31);
   gr500mu6AlSciDet1Pee->SetLineColor(kRed);
   gr500mu6AlSciDet1Pee->Draw("LP");
   leg500mu6AlSciDet1PeXPee = new TLegend(0.2,-0.005,0.4,0.08);
   leg500mu6AlSciDet1PeXPee->AddEntry(gr500mu6AlSciDet1PeX,"P_{e->X}","lp");
   leg500mu6AlSciDet1PeXPee->AddEntry(gr500mu6AlSciDet1Pee,"P_{e->e}","lp");
   leg500mu6AlSciDet1PeXPee->Draw();
    
   c->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr750mu6AlSciDet1PeX = new TGraph(nsamps,Ethrmu,PeXarr750mu6Al);
   gr750mu6AlSciDet1PeX->SetTitle("6 MeV: 6-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3} [10^6 events]");
   gr750mu6AlSciDet1PeX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr750mu6AlSciDet1PeX->GetXaxis()->SetRangeUser(0,2.05);
   gr750mu6AlSciDet1PeX->GetYaxis()->SetRangeUser(1e-6,1.1);
   gr750mu6AlSciDet1PeX->GetYaxis()->SetTitle("P_{e->X/e}(E_{THR})");
   gr750mu6AlSciDet1PeX->GetYaxis()->SetTitleOffset(1.8);
   gr750mu6AlSciDet1PeX->SetMarkerColor(kBlack);
   gr750mu6AlSciDet1PeX->SetMarkerStyle(33);
   gr750mu6AlSciDet1PeX->SetLineColor(kBlack);
   gr750mu6AlSciDet1PeX->Draw("ALP");
   TGraph *gr750mu6AlSciDet1Pee = new TGraph(nsamps,Ethrmu,Peearr750mu6Al); 
   gr750mu6AlSciDet1Pee->SetMarkerColor(kRed);
   gr750mu6AlSciDet1Pee->SetMarkerStyle(31);
   gr750mu6AlSciDet1Pee->SetLineColor(kRed);
   gr750mu6AlSciDet1Pee->Draw("LP");
   leg750mu6AlSciDet1PeXPee = new TLegend(0.2,-0.005,0.4,0.08);
   leg750mu6AlSciDet1PeXPee->AddEntry(gr750mu6AlSciDet1PeX,"P_{e->X}","lp");
   leg750mu6AlSciDet1PeXPee->AddEntry(gr750mu6AlSciDet1Pee,"P_{e->e}","lp");
   leg750mu6AlSciDet1PeXPee->Draw();

   c->SaveAs("Bubble4BinPlot_PeX_Pee_3mm_6mm_6_MeV_method_A.pdf");
   c->SaveAs("Bubble4BinPlot_PeX_Pee_3mm_6mm_6_MeV_method_A.png");
   c->SaveAs("Bubble4BinPlot_PeX_Pee_3mm_6mm_6_MeV_method_A.C");
 
  
  
  
 }
 
 
 int main() {
   bubble4FASTBINmu();
   return 0;
}  
