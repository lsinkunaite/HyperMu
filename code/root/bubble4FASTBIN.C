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

void bubble4FASTBIN(){

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
   std::string filemu250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filemu500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filemu750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filex250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6goldcascade.root";
   std::string filex500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_3mm_Al_1e6goldcascade.root";
   std::string filex750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_3mm_Al_1e6goldcascade.root";
   // With {250,500,750}-mm SciD3 6-mm Al
   std::string file6Almu250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string file6Almu500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Almu750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Alx250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_6mm_Al_1e6goldcascade.root";
   std::string file6Alx500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_6mm_Al_1e6goldcascade.root";
   std::string file6Alx750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_6mm_Al_1e6goldcascade.root";

   std::vector<std::string> Xfiles;
   std::vector<std::string> mufiles;

   // X-ray cascade
   Xfiles.push_back(filex250);
   Xfiles.push_back(filex500);
   Xfiles.push_back(filex750);
   Xfiles.push_back(file6Alx250);
   Xfiles.push_back(file6Alx500);
   Xfiles.push_back(file6Alx750);

   // mu-decay
   mufiles.push_back(filemu250);
   mufiles.push_back(filemu500);
   mufiles.push_back(filemu750);
   mufiles.push_back(file6Almu250);
   mufiles.push_back(file6Almu500);
   mufiles.push_back(file6Almu750);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep, EventID;
   float iEventID;

   const int nsamps = 101;
   float Ethr3 = 0.5;
   float Estep = 2.0/(nsamps-1);
   float Ethrx[nsamps] = {};
   float Ethrmu[nsamps] = {};
   
  
   // X-cascade storage vectors 
   std::vector< std::vector< double > > PXXvector(Xfiles.size(), std::vector< double >(nsamps));
   std::vector< std::vector< double > > PXevector(Xfiles.size(), std::vector< double >(nsamps));
   // mu-decay storage vectors
   std::vector< std::vector< double > > Peevector(mufiles.size(), std::vector< double >(nsamps));
   std::vector< std::vector< double > > PeXvector(mufiles.size(), std::vector< double >(nsamps)); 
  
      
   float PXX[nsamps] = {}; // X-cascade
   float PXe[nsamps] = {}; // X-cascade
   float Pee[nsamps] = {}; // mu-decay
   float PeX[nsamps] = {}; // mu-decay
   float Ethr;
   float Pxx = 0;
   float tPxx, tPex; 
   int Xray = 0;
   int elec = 0;
   
   Ethrx[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrx[i] = Ethrx[i-1] + Estep;

   
   
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



  // for (int k = 0; k<mufiles.size(); k++) {
   for (int k = 0; k < 2s; k++) {
      std::cout << "File: " << (mufiles[k]).substr(22,((mufiles[k]).find(".root"))) << " is being analysed" << std::endl;

      TFile *mufile = new TFile(TString(mufiles[k]));
      
      TNtuple * muSciDet1 = (TNtuple*)mufile->Get("Detector/SciDet1");
      TNtuple * muSciDet2 = (TNtuple*)mufile->Get("Detector/SciDet2");
      TNtuple * muSciDet3 = (TNtuple*)mufile->Get("Detector/SciDet3");

      muSciDet1->SetBranchAddress("Edep",&Edep);
      muSciDet1->SetBranchAddress("EventID",&EventID);
      muSciDet2->SetBranchAddress("Edep",&Edep);
      muSciDet2->SetBranchAddress("EventID",&EventID);
      muSciDet3->SetBranchAddress("Edep",&Edep);
      muSciDet3->SetBranchAddress("EventID",&EventID);
   
   
     // for (int m=0; m < nsamps; m++) {
	  for (int m=0; m < 2; m++)  { 
	   
	     Ethr = Ethrx[m];
         Xray = 0; elec = 0;
	     
	     for (int i=0; i< muSciDet1->GetEntries(); i++) {
	
		    muSciDet1->GetEntry(i);
		    tPex = 0;
		    iEventID = EventID;
		   
		    if (Edep < Ethr) {
			   tPex += 1;   
		  
		       muSciDet2->GetEntry(i);
		       if (EventID != iEventID) {
				  std::cout << "EventID2 = " << EventID << " iEventID = " << iEventID << std::endl;
			   }
/*
		       if (Edep < Ethr) {
			      tPex += 1;

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
*/			} else {
			   elec += 1;
			}	
		 }

    /*     PeX[m] = Xray/(double)(muSciDet1->GetEntries());
         Pee[m] = elec/(double)(muSciDet1->GetEntries());
         PeXvector[k][m] = PeX[m];
         Peevector[k][m] = Pee[m];
     
        
         std::cout << "PeX[" << m << "] = " << PeX[m] << " Pee[" << m << "] = " << Pee[m] << " PeX[" << m << "] + Pee[" << m << "] = " << PeX[m] + Pee[m] <<std::endl;
      */  
      }
      

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
   bubble4FASTBIN();
   return 0;
}  
