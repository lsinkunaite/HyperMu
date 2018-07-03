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
   // With {250,500,750}-mm SciD3 0-mm Al
   std::string file0Almu250 = "../../simdata/bubble4/bubble_0x5mm_250mm_SciD_Nevts_SciSphere_0mm_Al_1e6mudecay.root";
   std::string file0Almu500 = "../../simdata/bubble4/bubble_0x5mm_500mm_SciD_Nevts_SciSphere_0mm_Al_1e6mudecay.root";
   std::string file0Almu750 = "../../simdata/bubble4/bubble_0x5mm_750mm_SciD_Nevts_SciSphere_0mm_Al_1e6mudecay.root";
   std::string file0Alx250 = "../../simdata/bubble4/bubble_0x5mm_250mm_SciD_Nevts_SciSphere_0mm_Al_1e6goldcascade.root";
   std::string file0Alx500 = "../../simdata/bubble4/bubble_0x5mm_500mm_SciD_Nevts_SciSphere_0mm_Al_1e6goldcascade.root";
   std::string file0Alx750 = "../../simdata/bubble4/bubble_0x5mm_750mm_SciD_Nevts_SciSphere_0mm_Al_1e6goldcascade.root";

   /*********************************/
   /*           Analysis            */
   /*********************************/


   //using clock = std::chrono::steady_clock;

   //const int nbins = 300;
  
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
   // 0-mm Al
   TFile* f0Almu250 = new TFile(TString(file0Almu250));
   TFile* f0Almu500 = new TFile(TString(file0Almu500));
   TFile* f0Almu750 = new TFile(TString(file0Almu750));
   TFile* f0Alx250 = new TFile(TString(file0Alx250));
   TFile* f0Alx500 = new TFile(TString(file0Alx500));
   TFile* f0Alx750 = new TFile(TString(file0Alx750));

 
   float Edep, EventID;
   float tEdep, iEventID, jEventID, kEventID;

   const int nsamps = 11;
   float Ethrx[nsamps] = {};
   float Ethrmu[nsamps] = {};
   float PXX[nsamps] = {};
   float PXe[nsamps] = {};
   float Pee[nsamps] = {};
   float PeX[nsamps] = {};
   float Ethr = 0.5;
   float Pxx = 0;
   float tPxx, tPee, tPex; 
   int Xray = 0;
   int elec = 0;
   
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
   
    
   system("[ -e data/PXX/test.txt ] && rm data/PXX/test.txt");
   system("[ -e data/PXe/test.txt ] && rm data/PXe/test.txt");
        


   
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
 
 
         freopen("data/PXX/ETHR_"+TString(Ethrxss.str())+"keV.txt","w",stdout);
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
       
       
    }     
  
  
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
    c->Divide(2,1);
    c->cd(1);
    gPad->SetLogy();
    gPad->SetGrid(1,1);
    TGraph *grSciDet1PXX = new TGraph(nsamps,Ethrx,PXX);
    grSciDet1PXX->SetTitle("P_{X->X} vs P_{X->e} 250x [10^3 events]");
    grSciDet1PXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
    grSciDet1PXX->GetXaxis()->SetRangeUser(0,2.05);
    grSciDet1PXX->GetYaxis()->SetRangeUser(1e-4,1.1);
    grSciDet1PXX->GetYaxis()->SetTitle("P_{X->X/e}(E_{THR})");
    grSciDet1PXX->GetYaxis()->SetTitleOffset(1.8);
    grSciDet1PXX->SetMarkerColor(kBlack);
    grSciDet1PXX->SetMarkerStyle(33);
    grSciDet1PXX->SetLineColor(kBlack);
    grSciDet1PXX->Draw("ALP");
    TGraph *grSciDet1PXe = new TGraph(nsamps,Ethrx,PXe);
    grSciDet1PXe->SetMarkerColor(kRed);
    grSciDet1PXe->SetMarkerStyle(31);
    grSciDet1PXe->SetLineColor(kRed);
    grSciDet1PXe->Draw("LP");
    legSciDet1PXXPXe = new TLegend(0.2,-0.01,0.4,0.08);
    legSciDet1PXXPXe->AddEntry(grSciDet1PXX,"P_{X->X}","lp");
    legSciDet1PXXPXe->AddEntry(grSciDet1PXe,"P_{X->e}","lp");
    legSciDet1PXXPXe->Draw();
  
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
    c->SaveAs("Bubble4BinPlot_Xmutest.pdf");
    c->SaveAs("Bubble4BinPlot_Xmutest.png");
    c->SaveAs("Bubble4BinPlot_Xmutest.C");
  
  
  
  
  
  
  
 }
 
 
 int main() {
   bubble4FASTBIN();
   return 0;
}  
