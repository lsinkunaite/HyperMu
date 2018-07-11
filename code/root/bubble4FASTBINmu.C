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
   std::string file6Almu250SciD1 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay_SciD1.txt";
   std::string file6Almu250SciD2 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay_SciD2.txt";
   std::string file6Almu250SciD3 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay_SciD3.txt";
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
   std::vector< std::vector< double > > Peevector;
   std::vector< std::vector< double > > PeXvector;

   std::vector< std::vector< double > > allvEvID1;
   std::vector< std::vector< double > > allvEvID2;
   std::vector< std::vector< double > > allvEvID3;
   
   std::vector< std::vector< double > > allvEdep1;
   std::vector< std::vector< double > > allvEdep2;
   std::vector< std::vector< double > > allvEdep3;


//   float Pee[nsamps] = {}; // mu-decay
//   float PeX[nsamps] = {}; // mu-decay
   float Ethr;
   float Pxx = 0;
   float tPxx, tPex; 
   int Xray = 0;
   int elec = 0;
   
   Ethrmu[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;

   
   
/*
   for (int k = 0; k<Xfiles.size(); k++) {
      std::cout << "File: " << (Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))) << " is being analysed" << std::endl;

      TFile *xfile = new TFile(TString(Xfiles[k]));
      
      TNtuple * xSciDet1 = (TNtuple*)xfile->Get("Detector/SciDet1");
      TNtuple * xSciDet2 = (TNtuple*)xfile->Get("Detector/SciDet2");
      TNtuple * xSciDet3 = (TNtuple*)xfile->Get("Detector/SciDet3");

      xSciDet1->SetBranchAddress("Edep",&Edep);
      xSciDet1->SetBranchAddress("EventID",&EventID);
      xSciDet2->SetBranchAddress("Edep",&Edep);
      xSciDet2->SetBranchAddress("EventID",&EventID);
      xSciDet3->SetBranchAddress("Edep",&Edep);
      xSciDet3->SetBranchAddress("EventID",&EventID);
   
      for (int m=0; m < nsamps; m++) {
	   
	     Ethr = Ethrx[m];
         Xray = 0; elec = 0;
	     
	     for (int i=0; i< xSciDet1->GetEntries(); i++) {
	
		    xSciDet1->GetEntry(i);
		    tPxx = 0;
		    //iEventID = EventID;
		   
		    if (Edep < Ethr) {
			   tPxx += 1;   
		  
		       xSciDet2->GetEntry(i);
		       //if (EventID != iEventID) std::cout << "EventID2 = " << EventID << " iEventID = " << iEventID << std::endl;
		       if (Edep < Ethr) {
			      tPxx += 1;

                  xSciDet3->GetEntry(i);
                  //if (EventID != iEventID) std::cout << "EventID3 = " << EventID << " iEventID = " << iEventID << std::endl;
                  if ((Edep >= Ethr3) && (Edep < 10) && (tPxx == 2)) {
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

         PXX[m] = Xray/(double)(xSciDet1->GetEntries());
         PXe[m] = elec/(double)(xSciDet1->GetEntries());
         PXXvector[k][m] = PXX[m];
         PXevector[k][m] = PXe[m];
     
        
         //std::cout << "PXX[" << m << "] = " << PXX[m] << " PXe[" << m << "] = " << PXe[m] << " PXX[" << m << "] + PXe[" << m << "] = " << PXX[m] + PXe[m] <<std::endl;
        
      }
      

   }
*/

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
   //-------------------------------------------------------------------     
     
	  
   for (int i=0; i<allvEvID1.size(); i++) {
      Xray = 0; elec = 0;

      std::cout << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
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
				  if ((allvEdep3[i][j] >= Ethr3) && (allvEdep3[i][j] < 10) && (tPex == 2)) {
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

      vPeX.push_back(Xray/(double)(allvEvID1[0].size()));
      vPee.push_back(elec/(double)(allvEvID1[0].size()));
       
      std::cout << "PeX[" << m << "] = " << vPeX.back() << " Pee[" << m << "] = " << vPee.back() << " PeX[" << m << "] + Pee[" << m << "] = " << vPeX.back() + vPee.back() <<std::endl;
     

      }   
      
      PeXvector.push_back(vPeX);
      Peevector.push_back(vPee);
       
        
   }
   
   
   
   
   
   
   




/*  
    TCanvas *c = new TCanvas("c","E_{THR}",800,600);
    c->Divide(3,2);
    c->cd(1);
    gPad->SetLogy();
    gPad->SetGrid(1,1);
    float PXXarr250x[nsamps] = {};
    std::copy(PXXvector[0].begin(), PXXvector[0].end(), PXXarr250x);
    TGraph *gr250xSciDet1PXX = new TGraph(nsamps,Ethrx,PXXarr250x);
    gr250xSciDet1PXX->SetTitle("3-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3} [10^6 events]");
    gr250xSciDet1PXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
    gr250xSciDet1PXX->GetXaxis()->SetRangeUser(0,2.05);
    gr250xSciDet1PXX->GetYaxis()->SetRangeUser(1e-6,1.1);
    gr250xSciDet1PXX->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
    gr250xSciDet1PXX->GetYaxis()->SetTitleOffset(1.8);
    gr250xSciDet1PXX->SetMarkerColor(kBlack);
    gr250xSciDet1PXX->SetMarkerStyle(33);
    gr250xSciDet1PXX->SetLineColor(kBlack);
    gr250xSciDet1PXX->Draw("ALP");
    float PXearr250x[nsamps] = {};
    std::copy(PXevector[0].begin(), PXevector[0].end(), PXearr250x);
    TGraph *gr250xSciDet1PXe = new TGraph(nsamps,Ethrx,PXearr250x); 
    gr250xSciDet1PXe->SetMarkerColor(kRed);
    gr250xSciDet1PXe->SetMarkerStyle(31);
    gr250xSciDet1PXe->SetLineColor(kRed);
    gr250xSciDet1PXe->Draw("LP");
    leg250xSciDet1PXXPXe = new TLegend(0.2,-0.005,0.4,0.08);
    leg250xSciDet1PXXPXe->AddEntry(gr250xSciDet1PXX,"P_{X->X}","lp");
    leg250xSciDet1PXXPXe->AddEntry(gr250xSciDet1PXe,"P_{X->e}","lp");
    leg250xSciDet1PXXPXe->Draw();
  
    c->cd(2);
    gPad->SetLogy();
    gPad->SetGrid(1,1);
    float PXXarr500x[nsamps] = {};
    std::copy(PXXvector[1].begin(), PXXvector[1].end(), PXXarr500x);  
    TGraph *gr500xSciDet1PXX = new TGraph(nsamps,Ethrx,PXXarr500x);  
    gr500xSciDet1PXX->SetTitle("3-mm Al + 2x5-mm SCiD_{1,2} + 500-mm SciD_{3} [10^6 events]");
    gr500xSciDet1PXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
    gr500xSciDet1PXX->GetXaxis()->SetRangeUser(0,2.05);
    gr500xSciDet1PXX->GetYaxis()->SetRangeUser(1e-6,1.1);
    gr500xSciDet1PXX->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
    gr500xSciDet1PXX->GetYaxis()->SetTitleOffset(1.8);
    gr500xSciDet1PXX->SetMarkerColor(kBlack);
    gr500xSciDet1PXX->SetMarkerStyle(33);
    gr500xSciDet1PXX->SetLineColor(kBlack);
    gr500xSciDet1PXX->Draw("ALP");
    float PXearr500x[nsamps] = {};
    std::copy(PXevector[1].begin(), PXevector[1].end(), PXearr500x);
    TGraph *gr500xSciDet1PXe = new TGraph(nsamps,Ethrx,PXearr500x); 
    gr500xSciDet1PXe->SetMarkerColor(kRed);
    gr500xSciDet1PXe->SetMarkerStyle(31);
    gr500xSciDet1PXe->SetLineColor(kRed);
    gr500xSciDet1PXe->Draw("LP");
    leg500xSciDet1PXXPXe = new TLegend(0.2,-0.005,0.4,0.08);
    leg500xSciDet1PXXPXe->AddEntry(gr500xSciDet1PXX,"P_{X->X}","lp");
    leg500xSciDet1PXXPXe->AddEntry(gr500xSciDet1PXe,"P_{X->e}","lp");
    leg500xSciDet1PXXPXe->Draw();

    c->cd(3);
    gPad->SetLogy();
    gPad->SetGrid(1,1);
    float PXXarr750x[nsamps] = {};
    std::copy(PXXvector[2].begin(), PXXvector[2].end(), PXXarr750x);    
    TGraph *gr750xSciDet1PXX = new TGraph(nsamps,Ethrx,PXXarr750x); 
    gr750xSciDet1PXX->SetTitle("3-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3} [10^6 events]");
    gr750xSciDet1PXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
    gr750xSciDet1PXX->GetXaxis()->SetRangeUser(0,2.05);
    gr750xSciDet1PXX->GetYaxis()->SetRangeUser(1e-6,1.1);
    gr750xSciDet1PXX->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
    gr750xSciDet1PXX->GetYaxis()->SetTitleOffset(1.8);
    gr750xSciDet1PXX->SetMarkerColor(kBlack);
    gr750xSciDet1PXX->SetMarkerStyle(33);
    gr750xSciDet1PXX->SetLineColor(kBlack);
    gr750xSciDet1PXX->Draw("ALP");
    float PXearr750x[nsamps] = {};
    std::copy(PXevector[2].begin(), PXevector[2].end(), PXearr750x);
    TGraph *gr750xSciDet1PXe = new TGraph(nsamps,Ethrx,PXearr750x); 
    gr750xSciDet1PXe->SetMarkerColor(kRed);
    gr750xSciDet1PXe->SetMarkerStyle(31);
    gr750xSciDet1PXe->SetLineColor(kRed);
    gr750xSciDet1PXe->Draw("LP");
    leg750xSciDet1PXXPXe = new TLegend(0.2,-0.005,0.4,0.08);
    leg750xSciDet1PXXPXe->AddEntry(gr750xSciDet1PXX,"P_{X->X}","lp");
    leg750xSciDet1PXXPXe->AddEntry(gr750xSciDet1PXe,"P_{X->e}","lp");
    leg750xSciDet1PXXPXe->Draw();
  
    c->cd(4);
    gPad->SetLogy();
    gPad->SetGrid(1,1);
    float PXXarr250x6Al[nsamps] = {};
    std::copy(PXXvector[3].begin(), PXXvector[3].end(), PXXarr250x6Al);    
    TGraph *gr250x6AlSciDet1PXX = new TGraph(nsamps,Ethrx,PXXarr250x6Al);
    gr250x6AlSciDet1PXX->SetTitle("6-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3} [10^6 events]");
    gr250x6AlSciDet1PXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
    gr250x6AlSciDet1PXX->GetXaxis()->SetRangeUser(0,2.05);
    gr250x6AlSciDet1PXX->GetYaxis()->SetRangeUser(1e-6,1.1);
    gr250x6AlSciDet1PXX->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
    gr250x6AlSciDet1PXX->GetYaxis()->SetTitleOffset(1.8);
    gr250x6AlSciDet1PXX->SetMarkerColor(kBlack);
    gr250x6AlSciDet1PXX->SetMarkerStyle(33);
    gr250x6AlSciDet1PXX->SetLineColor(kBlack);
    gr250x6AlSciDet1PXX->Draw("ALP");
    float PXearr250x6Al[nsamps] = {};
    std::copy(PXevector[3].begin(), PXevector[3].end(), PXearr250x6Al);
    TGraph *gr250x6AlSciDet1PXe = new TGraph(nsamps,Ethrx,PXearr250x6Al); 
    gr250x6AlSciDet1PXe->SetMarkerColor(kRed);
    gr250x6AlSciDet1PXe->SetMarkerStyle(31);
    gr250x6AlSciDet1PXe->SetLineColor(kRed);
    gr250x6AlSciDet1PXe->Draw("LP");
    leg250x6AlSciDet1PXXPXe = new TLegend(0.2,-0.005,0.4,0.08);
    leg250x6AlSciDet1PXXPXe->AddEntry(gr250x6AlSciDet1PXX,"P_{X->X}","lp");
    leg250x6AlSciDet1PXXPXe->AddEntry(gr250x6AlSciDet1PXe,"P_{X->e}","lp");
    leg250x6AlSciDet1PXXPXe->Draw();
    
    c->cd(5);
    gPad->SetLogy();
    gPad->SetGrid(1,1);
    float PXXarr500x6Al[nsamps] = {};
    std::copy(PXXvector[4].begin(), PXXvector[4].end(), PXXarr500x6Al);    
    TGraph *gr500x6AlSciDet1PXX = new TGraph(nsamps,Ethrx,PXXarr500x6Al);
    gr500x6AlSciDet1PXX->SetTitle("6-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3} [10^6 events]");
    gr500x6AlSciDet1PXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
    gr500x6AlSciDet1PXX->GetXaxis()->SetRangeUser(0,2.05);
    gr500x6AlSciDet1PXX->GetYaxis()->SetRangeUser(1e-6,1.1);
    gr500x6AlSciDet1PXX->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
    gr500x6AlSciDet1PXX->GetYaxis()->SetTitleOffset(1.8);
    gr500x6AlSciDet1PXX->SetMarkerColor(kBlack);
    gr500x6AlSciDet1PXX->SetMarkerStyle(33);
    gr500x6AlSciDet1PXX->SetLineColor(kBlack);
    gr500x6AlSciDet1PXX->Draw("ALP");
    float PXearr500x6Al[nsamps] = {};
    std::copy(PXevector[4].begin(), PXevector[4].end(), PXearr500x6Al);
    TGraph *gr500x6AlSciDet1PXe = new TGraph(nsamps,Ethrx,PXearr500x6Al); 
    gr500x6AlSciDet1PXe->SetMarkerColor(kRed);
    gr500x6AlSciDet1PXe->SetMarkerStyle(31);
    gr500x6AlSciDet1PXe->SetLineColor(kRed);
    gr500x6AlSciDet1PXe->Draw("LP");
    leg500x6AlSciDet1PXXPXe = new TLegend(0.2,-0.005,0.4,0.08);
    leg500x6AlSciDet1PXXPXe->AddEntry(gr500x6AlSciDet1PXX,"P_{X->X}","lp");
    leg500x6AlSciDet1PXXPXe->AddEntry(gr500x6AlSciDet1PXe,"P_{X->e}","lp");
    leg500x6AlSciDet1PXXPXe->Draw();
    
    c->cd(6);
    gPad->SetLogy();
    gPad->SetGrid(1,1);
    float PXXarr750x6Al[nsamps] = {};
    std::copy(PXXvector[5].begin(), PXXvector[5].end(), PXXarr750x6Al);    
    TGraph *gr750x6AlSciDet1PXX = new TGraph(nsamps,Ethrx,PXXarr750x6Al);
    gr750x6AlSciDet1PXX->SetTitle("6-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3} [10^6 events]");
    gr750x6AlSciDet1PXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
    gr750x6AlSciDet1PXX->GetXaxis()->SetRangeUser(0,2.05);
    gr750x6AlSciDet1PXX->GetYaxis()->SetRangeUser(1e-6,1.1);
    gr750x6AlSciDet1PXX->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
    gr750x6AlSciDet1PXX->GetYaxis()->SetTitleOffset(1.8);
    gr750x6AlSciDet1PXX->SetMarkerColor(kBlack);
    gr750x6AlSciDet1PXX->SetMarkerStyle(33);
    gr750x6AlSciDet1PXX->SetLineColor(kBlack);
    gr750x6AlSciDet1PXX->Draw("ALP");
    float PXearr750x6Al[nsamps] = {};
    std::copy(PXevector[5].begin(), PXevector[5].end(), PXearr750x6Al);
    TGraph *gr750x6AlSciDet1PXe = new TGraph(nsamps,Ethrx,PXearr750x6Al); 
    gr750x6AlSciDet1PXe->SetMarkerColor(kRed);
    gr750x6AlSciDet1PXe->SetMarkerStyle(31);
    gr750x6AlSciDet1PXe->SetLineColor(kRed);
    gr750x6AlSciDet1PXe->Draw("LP");
    leg750x6AlSciDet1PXXPXe = new TLegend(0.2,-0.005,0.4,0.08);
    leg750x6AlSciDet1PXXPXe->AddEntry(gr750x6AlSciDet1PXX,"P_{X->X}","lp");
    leg750x6AlSciDet1PXXPXe->AddEntry(gr750x6AlSciDet1PXe,"P_{X->e}","lp");
    leg750x6AlSciDet1PXXPXe->Draw();



    c->SaveAs("Bubble4BinPlot_PXX_PXe_3mm_6mm.pdf");
    c->SaveAs("Bubble4BinPlot_PXX_PXe_3mm_6mm.png");
    c->SaveAs("Bubble4BinPlot_PXX_PXe_3mm_6mm.C");
  
*/  
  
  
  
  
  
 }
 
 
 int main() {
   bubble4FASTBINmu();
   return 0;
}  
