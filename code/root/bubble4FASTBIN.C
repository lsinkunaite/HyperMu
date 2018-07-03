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
   float Ethrx[nsamps] = {};
   float Ethrmu[nsamps] = {};
   
   float PXX250[nsamps] = {};
   float PXX500[nsamps] = {};
   float PXX750[nsamps] = {};
   float PXX6Al250[nsamps] = {};
   float PXX6Al500[nsamps] = {};
   float PXX6Al750[nsamps] = {};
   float PXe250[nsamps] = {};
   float PXe500[nsamps] = {};
   float PXe750[nsamps] = {};
   float PXe6Al250[nsamps] = {};
   float PXe6Al500[nsamps] = {};
   float PXe6Al750[nsamps] = {};
      
   float PXX[nsamps] = {};
   float PXe[nsamps] = {};
   float Pee[nsamps] = {};
   float PeX[nsamps] = {};
   float Ethr;
   float Pxx = 0;
   float tPxx, tPee, tPex; 
   int Xray = 0;
   int elec = 0;

   std::vector<float> PXXvector;
   std::vector<float> PXevector;
/*
   // X-ray cascade
   PXXvector.push_back(*PXX250);
   PXXvector.push_back(*PXX500);
   PXXvector.push_back(*PXX750);
   PXXvector.push_back(*PXX6Al250);
   PXXvector.push_back(*PXX6Al500);
   PXXvector.push_back(*PXX6Al750);
   PXXvector.push_back(*PXX0Al250);
   PXXvector.push_back(*PXX0Al500);
   PXXvector.push_back(*PXX0Al750);
   
   // mu-decay
   PXevector.push_back(*PXe250);
   PXevector.push_back(*PXe500);
   PXevector.push_back(*PXe750);
   PXevector.push_back(*PXe6Al250);
   PXevector.push_back(*PXe6Al500);
   PXevector.push_back(*PXe6Al750);
   PXevector.push_back(*PXe0Al250);
   PXevector.push_back(*PXe0Al500);
   PXevector.push_back(*PXe0Al750);
*/

   for (std::vector<std::string>::iterator it = Xfiles.begin(); it != Xfiles.end(); ++it) {
      std::cout << "File: " << (*it).substr(22,(*it).find(".root")) << " is being analysed" <<std::endl;

      //int index = std::distance(Xfiles.begin(), it);

      TFile *xfile = new TFile(TString(*it));
      
      Ethrx[0] = 0;
      for (int i=1; i<nsamps; i++) Ethrx[i] = Ethrx[i-1] + 0.02;

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
		    iEventID = EventID;
		   
		    if (Edep < Ethr) {
			   tPxx += 1;   
		  
		       xSciDet2->GetEntry(i);
		       if (EventID != iEventID) std::cout << "EventID2 = " << EventID << " iEventID = " << iEventID << std::endl;
		       if (Edep < Ethr) {
			      tPxx += 1;

                  xSciDet3->GetEntry(i);
                  if (EventID != iEventID) std::cout << "EventID3 = " << EventID << " iEventID = " << iEventID << std::endl;
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
        
      }
      
      std::cout << std::endl;
      std::cout << "PXX[0,3,5,8,10]: " << PXX[0] << std::setw(10) << PXX[3] << std::setw(10) << PXX[5] << std::setw(10) << PXX[8] << std::setw(10) << PXX[10] <<std::endl;        
      std::cout << "PXe[0,3,5,8,10]: " << PXe[0] << std::setw(10) << PXe[3] << std::setw(10) << PXe[5] << std::setw(10) << PXe[8] << std::setw(10) << PXe[10] <<std::endl;        
      std::cout << std::endl;   
         
      PXXvector.push_back(*PXX);
      PXevector.push_back(*PXe);


   }




/*
  
   // TFiles
   // 3-mm Al 
   TFile* fmu250 = new TFile(TString(filemu250));
   TFile* fmu500 = new TFile(TString(filemu500));
   TFile* fmu750 = new TFile(TString(filemu750));
   TFile* fx250 = new TFile(TString(filex250));
   TFile* fx500 = new TFile(TString(filex500));
   TFile* fx750 = new TFile(TString(filex750));
   // 6-mm Al
   TFile* f6Almu250 = new TFile(TString(file6Almu250));
   TFile* f6Almu500 = new TFile(TString(file6Almu500));
   TFile* f6Almu750 = new TFile(TString(file6Almu750));
   TFile* f6Alx250 = new TFile(TString(file6Alx250));
   TFile* f6Alx500 = new TFile(TString(file6Alx500));
   TFile* f6Alx750 = new TFile(TString(file6Alx750));
 
   
   
   Ethrx[0] = 0; Ethrmu[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrx[i] = Ethrx[i-1] + 0.2;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + 0.2;
   
   TNtuple * mu250SciDet1 = (TNtuple*)fmu250->Get("Detector/SciDet1");
   TNtuple * mu250SciDet2 = (TNtuple*)fmu250->Get("Detector/SciDet2");
   TNtuple * mu250SciDet3 = (TNtuple*)fmu250->Get("Detector/SciDet3");
   TNtuple * x250SciDet1 = (TNtuple*)fx250->Get("Detector/SciDet1");
   TNtuple * x250SciDet2 = (TNtuple*)fx250->Get("Detector/SciDet2");
   TNtuple * x250SciDet3 = (TNtuple*)fx250->Get("Detector/SciDet3");
   mu250SciDet1->SetBranchAddress("Edep",&Edep);
   mu250SciDet1->SetBranchAddress("EventID",&EventID);
   mu250SciDet2->SetBranchAddress("Edep",&Edep);
   mu250SciDet2->SetBranchAddress("EventID",&EventID);
   mu250SciDet3->SetBranchAddress("Edep",&Edep);
   mu250SciDet3->SetBranchAddress("EventID",&EventID);
   x250SciDet1->SetBranchAddress("Edep",&Edep);
   x250SciDet1->SetBranchAddress("EventID",&EventID);
   x250SciDet2->SetBranchAddress("Edep",&Edep);
   x250SciDet2->SetBranchAddress("EventID",&EventID);
   x250SciDet3->SetBranchAddress("Edep",&Edep);
   x250SciDet3->SetBranchAddress("EventID",&EventID);
  
 */ 
  
   
 /*   
   // Removing old files with PXX/PXe output, if they exist
   system("[ -e data/PXX/test.txt ] && rm data/PXX/test.txt");
   system("[ -e data/PXe/test.txt ] && rm data/PXe/test.txt");
  */     

/*
   
   for (int m=0; m < nsamps; m++) {
	   
	   Ethr = Ethrx[m];

       Xray = 0; elec = 0;
	   for (int i=0; i< x250SciDet1->GetEntries(); i++) {
	
		  x250SciDet1->GetEntry(i);
		  tPxx = 0;
		  iEventID = EventID;
		   
		  if (Edep < Ethr) {
			 tPxx += 1;   
		  
		     x250SciDet2->GetEntry(i);
		     //if (EventID != iEventID) std::cout << "EventID2 = " << EventID << " iEventID = " << iEventID << std::endl;
		     if (Edep < Ethr) {
			    tPxx += 1;

                x250SciDet3->GetEntry(i);
                if (EventID != iEventID) std::cout << "EventID3 = " << EventID << " iEventID = " << iEventID << std::endl;
                   if ((Edep >= 0.5) && (Edep < 10) && (tPxx == 2)) {
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


         PXX[m] = Xray/(double)(x250SciDet1->GetEntries());
         PXe[m] = elec/(double)(x250SciDet1->GetEntries());
 
         std::stringstream Ethrxss; Ethrxss << Ethrx[m]*1000;
 
 */
 
 
         // Saving output data to the files
/*         freopen("data/PXX/ETHR_"+TString(Ethrxss.str())+"keV.txt","w",stdout);
         std::cout << PXX[m] << std::endl;
         fclose(stdout);
         freopen("/dev/tty","a",stdout);
         freopen("data/PXe/ETHR_"+TString(Ethrxss.str())+"keV.txt","w",stdout);
         std::cout << PXe[m] << std::endl;
         fclose(stdout);
         freopen("/dev/tty","a",stdout);
       
         freopen("data/PXX/test.txt","a",stdout);
         std::cout << Ethrx[m]*1000 << std::setw(10) << PXX[m] << std::endl;
         fclose(stdout);
         freopen("/dev/tty","a",stdout);
       
         freopen("data/PXe/test.txt","a",stdout);
         std::cout << Ethrx[m]*1000 << std::setw(10) << PXe[m] << std::endl;
         fclose(stdout);
         freopen("/dev/tty","a",stdout);
*/       
       
  //  }     
  
  
 /*   for (int l=0; l<sizeTHRx; l++) {
		std::cout << "Ethrx = " << Ethrx[l] << " PXX = " << PXX[l] << " PXe = " << PXe[l] << std::endl;
    }
  */
    
 /* 
  
  for (int n=0; n < nsamps; n++) {
	   Ethr = Ethrmu[n];
	   //   std::cout << "Ethr = " << Ethr << std::endl;

       Xray = 0; elec = 0;
	   for (int i=0; i< mu250SciDet1->GetEntries(); i++) {
		  mu250SciDet1->GetEntry(i);
		  tPee = 0;
		  iEventID = EventID;
		   
		  if (Edep > Ethr) {
			 tPee += 1;   
		  
			 for (int j=0; j< mu250SciDet2->GetEntries(); j++) {		
				x250SciDet2->GetEntry(j);		  
				if (EventID == iEventID) {
				   jEventID = EventID;
				   if (Edep > Ethr) {
					  tPee += 1;

					  for (int k=0; k< mu250SciDet3->GetEntries(); k++) {
						 mu250SciDet3->GetEntry(k);
				 
						 if ((EventID == iEventID) && (EventID == jEventID)) {
							if ((Edep > 10) && (tPee != 0)) {
							   elec += 1;
							} else {
							   Xray += 1;
							}
						 }
						   
					  }
						 
				   } //else if (tPee == 0) {
					  // Xray += 1;
				  // }	   
				}     
			 }		   	  
		  } //else {
			//   elec += 1;
		 // }      	  
	   }
				   
	   std::cout << "Xray = " << Xray << " and elec = " << elec << std::endl;

       Pee[n] = elec/(double)(1e6);
       PeX[n] = Xray/(double)(1e6);
       std::cout << "nEntries = " << mu250SciDet1->GetEntries() << std::endl;
       std::cout << "Pee[n] = " << Pee[n] << " PeX[n] = " << PeX[n] << std::endl;
       
       
    }     
  */
  
  
    TCanvas *c = new TCanvas("c","E_{THR}",800,600);
    c->Divide(3,2);
    c->cd(1);
    gPad->SetLogy();
    gPad->SetGrid(1,1);
    TGraph *gr250xSciDet1PXX = new TGraph(nsamps,Ethrx,&PXXvector[0]);
    gr250xSciDet1PXX->SetTitle("3-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3} [10**6 events]");
    gr250xSciDet1PXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
    gr250xSciDet1PXX->GetXaxis()->SetRangeUser(0,2.05);
    gr250xSciDet1PXX->GetYaxis()->SetRangeUser(1e-6,1.1);
    gr250xSciDet1PXX->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
    gr250xSciDet1PXX->GetYaxis()->SetTitleOffset(1.8);
    gr250xSciDet1PXX->SetMarkerColor(kBlack);
    gr250xSciDet1PXX->SetMarkerStyle(33);
    gr250xSciDet1PXX->SetLineColor(kBlack);
    gr250xSciDet1PXX->Draw("ALP");
    TGraph *gr250xSciDet1PXe = new TGraph(nsamps,Ethrx,&PXevector[0]);
    gr250xSciDet1PXe->SetMarkerColor(kRed);
    gr250xSciDet1PXe->SetMarkerStyle(31);
    gr250xSciDet1PXe->SetLineColor(kRed);
    gr250xSciDet1PXe->Draw("LP");
    leg250xSciDet1PXXPXe = new TLegend(0.2,-0.01,0.4,0.08);
    leg250xSciDet1PXXPXe->AddEntry(gr250xSciDet1PXX,"P_{X->X}","lp");
    leg250xSciDet1PXXPXe->AddEntry(gr250xSciDet1PXe,"P_{X->e}","lp");
    leg250xSciDet1PXXPXe->Draw();
  
    c->cd(2);
    gPad->SetLogy();
    gPad->SetGrid(1,1);
    TGraph *gr500xSciDet1PXX = new TGraph(nsamps,Ethrx,&PXXvector[1]);
    gr500xSciDet1PXX->SetTitle("3-mm Al + 2x5-mm SCiD_{1,2} + 500-mm SciD_{3} [10**6 events]");
    gr500xSciDet1PXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
    gr500xSciDet1PXX->GetXaxis()->SetRangeUser(0,2.05);
    gr500xSciDet1PXX->GetYaxis()->SetRangeUser(1e-6,1.1);
    gr500xSciDet1PXX->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
    gr500xSciDet1PXX->GetYaxis()->SetTitleOffset(1.8);
    gr500xSciDet1PXX->SetMarkerColor(kBlack);
    gr500xSciDet1PXX->SetMarkerStyle(33);
    gr500xSciDet1PXX->SetLineColor(kBlack);
    gr500xSciDet1PXX->Draw("ALP");
    TGraph *gr500xSciDet1PXe = new TGraph(nsamps,Ethrx,&PXevector[1]);
    gr500xSciDet1PXe->SetMarkerColor(kRed);
    gr500xSciDet1PXe->SetMarkerStyle(31);
    gr500xSciDet1PXe->SetLineColor(kRed);
    gr500xSciDet1PXe->Draw("LP");
    leg500xSciDet1PXXPXe = new TLegend(0.2,-0.01,0.4,0.08);
    leg500xSciDet1PXXPXe->AddEntry(gr500xSciDet1PXX,"P_{X->X}","lp");
    leg500xSciDet1PXXPXe->AddEntry(gr500xSciDet1PXe,"P_{X->e}","lp");
    leg500xSciDet1PXXPXe->Draw();

    c->cd(3);
    gPad->SetLogy();
    gPad->SetGrid(1,1);
    TGraph *gr750xSciDet1PXX = new TGraph(nsamps,Ethrx,&PXXvector[2]);
    gr750xSciDet1PXX->SetTitle("3-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3} [10**6 events]");
    gr750xSciDet1PXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
    gr750xSciDet1PXX->GetXaxis()->SetRangeUser(0,2.05);
    gr750xSciDet1PXX->GetYaxis()->SetRangeUser(1e-6,1.1);
    gr750xSciDet1PXX->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
    gr750xSciDet1PXX->GetYaxis()->SetTitleOffset(1.8);
    gr750xSciDet1PXX->SetMarkerColor(kBlack);
    gr750xSciDet1PXX->SetMarkerStyle(33);
    gr750xSciDet1PXX->SetLineColor(kBlack);
    gr750xSciDet1PXX->Draw("ALP");
    TGraph *gr750xSciDet1PXe = new TGraph(nsamps,Ethrx,&PXevector[2]);
    gr750xSciDet1PXe->SetMarkerColor(kRed);
    gr750xSciDet1PXe->SetMarkerStyle(31);
    gr750xSciDet1PXe->SetLineColor(kRed);
    gr750xSciDet1PXe->Draw("LP");
    leg750xSciDet1PXXPXe = new TLegend(0.2,-0.01,0.4,0.08);
    leg750xSciDet1PXXPXe->AddEntry(gr750xSciDet1PXX,"P_{X->X}","lp");
    leg750xSciDet1PXXPXe->AddEntry(gr750xSciDet1PXe,"P_{X->e}","lp");
    leg750xSciDet1PXXPXe->Draw();
  
    c->cd(4);
    gPad->SetLogy();
    gPad->SetGrid(1,1);
    TGraph *gr250x6AlSciDet1PXX = new TGraph(nsamps,Ethrx,&PXXvector[3]);
    gr250x6AlSciDet1PXX->SetTitle("6-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3} [10**6 events]");
    gr250x6AlSciDet1PXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
    gr250x6AlSciDet1PXX->GetXaxis()->SetRangeUser(0,2.05);
    gr250x6AlSciDet1PXX->GetYaxis()->SetRangeUser(1e-6,1.1);
    gr250x6AlSciDet1PXX->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
    gr250x6AlSciDet1PXX->GetYaxis()->SetTitleOffset(1.8);
    gr250x6AlSciDet1PXX->SetMarkerColor(kBlack);
    gr250x6AlSciDet1PXX->SetMarkerStyle(33);
    gr250x6AlSciDet1PXX->SetLineColor(kBlack);
    gr250x6AlSciDet1PXX->Draw("ALP");
    TGraph *gr250x6AlSciDet1PXe = new TGraph(nsamps,Ethrx,&PXevector[3]);
    gr250x6AlSciDet1PXe->SetMarkerColor(kRed);
    gr250x6AlSciDet1PXe->SetMarkerStyle(31);
    gr250x6AlSciDet1PXe->SetLineColor(kRed);
    gr250x6AlSciDet1PXe->Draw("LP");
    leg250x6AlSciDet1PXXPXe = new TLegend(0.2,-0.01,0.4,0.08);
    leg250x6AlSciDet1PXXPXe->AddEntry(gr250x6AlSciDet1PXX,"P_{X->X}","lp");
    leg250x6AlSciDet1PXXPXe->AddEntry(gr250x6AlSciDet1PXe,"P_{X->e}","lp");
    leg250x6AlSciDet1PXXPXe->Draw();
    
    c->cd(5);
    gPad->SetLogy();
    gPad->SetGrid(1,1);
    TGraph *gr500x6AlSciDet1PXX = new TGraph(nsamps,Ethrx,&PXXvector[4]);
    gr500x6AlSciDet1PXX->SetTitle("6-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3} [10**6 events]");
    gr500x6AlSciDet1PXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
    gr500x6AlSciDet1PXX->GetXaxis()->SetRangeUser(0,2.05);
    gr500x6AlSciDet1PXX->GetYaxis()->SetRangeUser(1e-6,1.1);
    gr500x6AlSciDet1PXX->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
    gr500x6AlSciDet1PXX->GetYaxis()->SetTitleOffset(1.8);
    gr500x6AlSciDet1PXX->SetMarkerColor(kBlack);
    gr500x6AlSciDet1PXX->SetMarkerStyle(33);
    gr500x6AlSciDet1PXX->SetLineColor(kBlack);
    gr500x6AlSciDet1PXX->Draw("ALP");
    TGraph *gr500x6AlSciDet1PXe = new TGraph(nsamps,Ethrx,&PXevector[4]);
    gr500x6AlSciDet1PXe->SetMarkerColor(kRed);
    gr500x6AlSciDet1PXe->SetMarkerStyle(31);
    gr500x6AlSciDet1PXe->SetLineColor(kRed);
    gr500x6AlSciDet1PXe->Draw("LP");
    leg500x6AlSciDet1PXXPXe = new TLegend(0.2,-0.01,0.4,0.08);
    leg500x6AlSciDet1PXXPXe->AddEntry(gr500x6AlSciDet1PXX,"P_{X->X}","lp");
    leg500x6AlSciDet1PXXPXe->AddEntry(gr500x6AlSciDet1PXe,"P_{X->e}","lp");
    leg500x6AlSciDet1PXXPXe->Draw();
    
    c->cd(6);
    gPad->SetLogy();
    gPad->SetGrid(1,1);
    TGraph *gr750x6AlSciDet1PXX = new TGraph(nsamps,Ethrx,&PXXvector[5]);
    gr750x6AlSciDet1PXX->SetTitle("6-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3} [10**6 events]");
    gr750x6AlSciDet1PXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
    gr750x6AlSciDet1PXX->GetXaxis()->SetRangeUser(0,2.05);
    gr750x6AlSciDet1PXX->GetYaxis()->SetRangeUser(1e-6,1.1);
    gr750x6AlSciDet1PXX->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
    gr750x6AlSciDet1PXX->GetYaxis()->SetTitleOffset(1.8);
    gr750x6AlSciDet1PXX->SetMarkerColor(kBlack);
    gr750x6AlSciDet1PXX->SetMarkerStyle(33);
    gr750x6AlSciDet1PXX->SetLineColor(kBlack);
    gr750x6AlSciDet1PXX->Draw("ALP");
    TGraph *gr750x6AlSciDet1PXe = new TGraph(nsamps,Ethrx,&PXevector[5]);
    gr750x6AlSciDet1PXe->SetMarkerColor(kRed);
    gr750x6AlSciDet1PXe->SetMarkerStyle(31);
    gr750x6AlSciDet1PXe->SetLineColor(kRed);
    gr750x6AlSciDet1PXe->Draw("LP");
    leg750x6AlSciDet1PXXPXe = new TLegend(0.2,-0.01,0.4,0.08);
    leg750x6AlSciDet1PXXPXe->AddEntry(gr750x6AlSciDet1PXX,"P_{X->X}","lp");
    leg750x6AlSciDet1PXXPXe->AddEntry(gr750x6AlSciDet1PXe,"P_{X->e}","lp");
    leg750x6AlSciDet1PXXPXe->Draw();




  /*
    c->cd(2);
    gPad->SetLogy();
    gPad->SetGrid(1,1);
    TGraph *grmu250Pee = new TGraph(nsamps,Ethrmu,Pee);
    grmu250Pee->SetTitle("P_{e->e} vs P_{e->X} 250mu [10^3 events]");
    grmu250Pee->GetXaxis()->SetTitle("E_{THR} [MeV]");
    grmu250Pee->GetXaxis()->SetRangeUser(0,2.05);
    //grmu250Pee->GetYaxis()->SetRangeUser(1e-4,1.1);
    grmu250Pee->GetYaxis()->SetTitle("P_{e->e/X}(E_{THR})");
    grmu250Pee->GetYaxis()->SetTitleOffset(1.8);
    grmu250Pee->SetMarkerColor(kBlack);
    grmu250Pee->SetMarkerStyle(33);
    grmu250Pee->SetLineColor(kBlack);
    grmu250Pee->Draw("ALP");
    TGraph *grmu250PeX = new TGraph(nsamps,Ethrmu,PeX);
    grmu250PeX->SetMarkerColor(kRed);
    grmu250PeX->SetMarkerStyle(31);
    grmu250PeX->SetLineColor(kRed);
    grmu250PeX->Draw("LP");
    legmu250PeePeX = new TLegend(0.2,-0.01,0.4,0.08);
    legmu250PeePeX->AddEntry(grmu250Pee,"P_{e->e}","lp");
    legmu250PeePeX->AddEntry(grmu250PeX,"P_{e->X}","lp");
    legmu250PeePeX->Draw();
  */
    c->SaveAs("Bubble4BinPlot_PXX_PXe_3mm_6mm.pdf");
    c->SaveAs("Bubble4BinPlot_PXX_PXe_3mm_6mm.png");
    c->SaveAs("Bubble4BinPlot_PXX_PXe_3mm_6mm.C");
  
  
  
  
  
  
  
 }
 
 
 int main() {
   bubble4FASTBIN();
   return 0;
}  
