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

void EdepPlanar() {
	
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
   
   //TString process = "mudecay";
   TString process = "goldcascade";
   TString fileType = "BIG";
   
   // Names of the files
   // With {250,500,750}-mm SciD3 3-mm Al
   std::string filemu250 = "../../simdata/planar/planar_"+fileType+"_2x5mm_250mm_SciD_3mm_Al_1e6"+process+".root";
   std::string filemu500 = "../../simdata/planar/planar_"+fileType+"_2x5mm_500mm_SciD_3mm_Al_1e6"+process+".root";
   std::string filemu750 = "../../simdata/planar/planar_"+fileType+"_2x5mm_750mm_SciD_3mm_Al_1e6"+process+".root";
   // With {250,500,750}-mm SciD3 6-mm Al
   std::string file6Almu250 = "../../simdata/planar/planar_"+fileType+"_2x5mm_250mm_SciD_6mm_Al_1e6"+process+".root";
   std::string file6Almu500 = "../../simdata/planar/planar_"+fileType+"_2x5mm_500mm_SciD_6mm_Al_1e6"+process+".root";
   std::string file6Almu750 = "../../simdata/planar/planar_"+fileType+"_2x5mm_750mm_SciD_6mm_Al_1e6"+process+".root";
   
   std::vector<std::string> mufiles;

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

   float Edep;

   const int nbins = 300;
   const int nsamps = 101;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
   float Ethr;
   
   Ethrmu[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;

   std::vector< std::vector<double> > TotEdep1D(mufiles.size(),std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdep1U(mufiles.size(),std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdep2D(mufiles.size(),std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdep2U(mufiles.size(),std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdep3D(mufiles.size(),std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdep3U(mufiles.size(),std::vector<double>(nsamps));

   
   for (int k = 0; k<mufiles.size(); k++) {
      //std::cout << "File: " << (mufiles[k]).substr(22,((mufiles[k]).find(".root"))) << " is being analysed" << std::endl;

      TFile *mufile = new TFile(TString(mufiles[k]));
      
      TH1F *hmu1D = new TH1F("hmu1D","Edep",3*nbins+1,-0.05,55);
      TH1F *hmu1U = new TH1F("hmu1U","Edep",3*nbins+1,-0.05,55);
      TH1F *hmu2D = new TH1F("hmu2D","Edep",3*nbins+1,-0.05,55);
      TH1F *hmu2U = new TH1F("hmu2U","Edep",3*nbins+1,-0.05,55);
      TH1F *hmu3D = new TH1F("hmu3D","Edep",3*nbins+1,-0.05,55);
      TH1F *hmu3U = new TH1F("hmu3U","Edep",3*nbins+1,-0.05,55);
      
      TTree *tmu1D = (TTree*)mufile->Get("Detector/SciDet1D");
      TTree *tmu1U = (TTree*)mufile->Get("Detector/SciDet1U");
      TTree *tmu2D = (TTree*)mufile->Get("Detector/SciDet2D");
      TTree *tmu2U = (TTree*)mufile->Get("Detector/SciDet2U");
      TTree *tmu3D = (TTree*)mufile->Get("Detector/SciDet3D");
      TTree *tmu3U = (TTree*)mufile->Get("Detector/SciDet3U");
   
      tmu1D->Draw("Edep>>hmu1D","","");
      tmu1U->Draw("Edep>>hmu1U","","");
      tmu2D->Draw("Edep>>hmu2D","","");
      tmu2U->Draw("Edep>>hmu2U","","");
      tmu3D->Draw("Edep>>hmu3D","","");
      tmu3U->Draw("Edep>>hmu3U","","");
      
      int binx1D, binx1U, binx2D, binx2U, binx3D, binx3U;
      double integral1D, integral1U, integral2D, integral2U, integral3D, integral3U;
   
      for (int m=0; m < nsamps; m++) {
	   
	     Ethr = Ethrmu[m];
	     
         binx1D = hmu1D->GetXaxis()->FindBin(Ethr);
         integral1D = hmu1D->Integral(0,binx1D,"");
         binx1U = hmu1U->GetXaxis()->FindBin(Ethr);
         integral1U = hmu1U->Integral(0,binx1U,"");
         binx2D = hmu2D->GetXaxis()->FindBin(Ethr);
         integral2D = hmu2D->Integral(0,binx2D,"");
         binx2U = hmu2U->GetXaxis()->FindBin(Ethr);
         integral2U = hmu2U->Integral(0,binx2U,"");
         binx3D = hmu3D->GetXaxis()->FindBin(Ethr);
         integral3D = hmu3D->Integral(0,binx3D,"");
         binx3U = hmu3U->GetXaxis()->FindBin(Ethr);
         integral3U = hmu3U->Integral(0,binx3U,"");
         
         TotEdep1D[k][m] = integral1D;
         TotEdep1U[k][m] = integral1U;
         TotEdep2D[k][m] = integral2D;
         TotEdep2U[k][m] = integral2U;
         TotEdep3D[k][m] = integral3D;
         TotEdep3U[k][m] = integral3U;
         
   	  }
   	  
   }	     
   	     
   	
   float Edep250mu3Al1D[nsamps] = {};
   float Edep250mu3Al1U[nsamps] = {};
   float Edep250mu3Al2D[nsamps] = {};
   float Edep250mu3Al2U[nsamps] = {};
   float Edep250mu3Al3D[nsamps] = {};
   float Edep250mu3Al3U[nsamps] = {};
   float Edep500mu3Al1D[nsamps] = {};
   float Edep500mu3Al1U[nsamps] = {};
   float Edep500mu3Al2D[nsamps] = {};
   float Edep500mu3Al2U[nsamps] = {};
   float Edep500mu3Al3D[nsamps] = {};
   float Edep500mu3Al3U[nsamps] = {};
   float Edep750mu3Al1D[nsamps] = {};
   float Edep750mu3Al1U[nsamps] = {};
   float Edep750mu3Al2D[nsamps] = {};
   float Edep750mu3Al2U[nsamps] = {};
   float Edep750mu3Al3D[nsamps] = {};
   float Edep750mu3Al3U[nsamps] = {};
   float Edep250mu6Al1D[nsamps] = {};
   float Edep250mu6Al1U[nsamps] = {};
   float Edep250mu6Al2D[nsamps] = {};
   float Edep250mu6Al2U[nsamps] = {};
   float Edep250mu6Al3D[nsamps] = {};
   float Edep250mu6Al3U[nsamps] = {};
   float Edep500mu6Al1D[nsamps] = {};
   float Edep500mu6Al1U[nsamps] = {};
   float Edep500mu6Al2D[nsamps] = {};
   float Edep500mu6Al2U[nsamps] = {};
   float Edep500mu6Al3D[nsamps] = {};
   float Edep500mu6Al3U[nsamps] = {};
   float Edep750mu6Al1D[nsamps] = {};
   float Edep750mu6Al1U[nsamps] = {};
   float Edep750mu6Al2D[nsamps] = {};
   float Edep750mu6Al2U[nsamps] = {};
   float Edep750mu6Al3D[nsamps] = {};
   float Edep750mu6Al3U[nsamps] = {};	
   
   for (int i=0; i<nsamps; i++) {
      Edep250mu3Al1D[i] = TotEdep1D[0][i]/TotEdep1D[0][nsamps-1];
      Edep250mu3Al1U[i] = TotEdep1U[0][i]/TotEdep1U[0][nsamps-1];
      Edep250mu3Al2D[i] = TotEdep2D[0][i]/TotEdep2D[0][nsamps-1];
      Edep250mu3Al2U[i] = TotEdep2U[0][i]/TotEdep2U[0][nsamps-1];
      Edep250mu3Al3D[i] = TotEdep3D[0][i]/TotEdep3D[0][nsamps-1];
      Edep250mu3Al3U[i] = TotEdep3U[0][i]/TotEdep3U[0][nsamps-1];
      Edep500mu3Al1D[i] = TotEdep1D[1][i]/TotEdep1D[1][nsamps-1];
      Edep500mu3Al1U[i] = TotEdep1U[1][i]/TotEdep1U[1][nsamps-1];
      Edep500mu3Al2D[i] = TotEdep2D[1][i]/TotEdep2D[1][nsamps-1];
      Edep500mu3Al2U[i] = TotEdep2U[1][i]/TotEdep2U[1][nsamps-1];
      Edep500mu3Al3D[i] = TotEdep3D[1][i]/TotEdep3D[1][nsamps-1];
      Edep500mu3Al3U[i] = TotEdep3U[1][i]/TotEdep3U[1][nsamps-1];
      Edep750mu3Al1D[i] = TotEdep1D[2][i]/TotEdep1D[2][nsamps-1];
      Edep750mu3Al1U[i] = TotEdep1U[2][i]/TotEdep1U[2][nsamps-1];
      Edep750mu3Al2D[i] = TotEdep2D[2][i]/TotEdep2D[2][nsamps-1];
      Edep750mu3Al2U[i] = TotEdep2U[2][i]/TotEdep2U[2][nsamps-1];
      Edep750mu3Al3D[i] = TotEdep3D[2][i]/TotEdep3D[2][nsamps-1];
      Edep750mu3Al3U[i] = TotEdep3U[2][i]/TotEdep3U[2][nsamps-1];
      Edep250mu6Al1D[i] = TotEdep1D[3][i]/TotEdep1D[3][nsamps-1];
      Edep250mu6Al1U[i] = TotEdep1U[3][i]/TotEdep1U[3][nsamps-1];
      Edep250mu6Al2D[i] = TotEdep2D[3][i]/TotEdep2D[3][nsamps-1];
      Edep250mu6Al2U[i] = TotEdep2U[3][i]/TotEdep3U[3][nsamps-1];
      Edep250mu6Al3D[i] = TotEdep3D[3][i]/TotEdep3D[3][nsamps-1];
      Edep250mu6Al3U[i] = TotEdep3U[3][i]/TotEdep3U[3][nsamps-1];
      Edep500mu6Al1D[i] = TotEdep1D[4][i]/TotEdep1D[4][nsamps-1];
      Edep500mu6Al1U[i] = TotEdep1U[4][i]/TotEdep1U[4][nsamps-1];
      Edep500mu6Al2D[i] = TotEdep2D[4][i]/TotEdep2D[4][nsamps-1];
      Edep500mu6Al2U[i] = TotEdep2U[4][i]/TotEdep2U[4][nsamps-1];
      Edep500mu6Al3D[i] = TotEdep3D[4][i]/TotEdep3D[4][nsamps-1];
      Edep500mu6Al3U[i] = TotEdep3U[4][i]/TotEdep3U[4][nsamps-1];
      Edep750mu6Al1D[i] = TotEdep1D[5][i]/TotEdep1D[5][nsamps-1];
      Edep750mu6Al1U[i] = TotEdep1U[5][i]/TotEdep1U[5][nsamps-1];
      Edep750mu6Al2D[i] = TotEdep2D[5][i]/TotEdep2D[5][nsamps-1];
      Edep750mu6Al2U[i] = TotEdep2U[5][i]/TotEdep2U[5][nsamps-1];
      Edep750mu6Al3D[i] = TotEdep3D[5][i]/TotEdep3D[5][nsamps-1];
      Edep750mu6Al3U[i] = TotEdep3U[5][i]/TotEdep3U[5][nsamps-1];
   }


   	     
   TCanvas *c = new TCanvas("c","E_{THR}",800,600);
   c->Divide(3,3);
   c->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu1D = new TGraph(nsamps,Ethrmu,Edep250mu3Al1D);
   grmu1D->SetTitle("5-mm SciD_{1} [3-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3}] D-stream");
   grmu1D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu1D->GetXaxis()->SetRangeUser(0,2);
   grmu1D->GetYaxis()->SetRangeUser(0,1);
   grmu1D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu1D->GetYaxis()->SetTitleOffset(1.8);
   grmu1D->SetMarkerColor(kGreen-2);
   grmu1D->SetMarkerStyle(33);
   grmu1D->SetLineColor(kGreen-2);
   grmu1D->Draw("ALP");
   	     
   c->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu2D = new TGraph(nsamps,Ethrmu,Edep250mu3Al2D);
   grmu2D->SetTitle("5-mm SciD_{2} [3-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3}] D-stream");
   grmu2D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu2D->GetXaxis()->SetRangeUser(0,2);
   grmu2D->GetYaxis()->SetRangeUser(0,1);
   grmu2D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu2D->GetYaxis()->SetTitleOffset(1.8);
   grmu2D->SetMarkerColor(kGreen-2);
   grmu2D->SetMarkerStyle(33);
   grmu2D->SetLineColor(kGreen-2);
   grmu2D->Draw("ALP");	     
   	     
   c->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu3D = new TGraph(nsamps,Ethrmu,Edep250mu3Al3D);
   grmu3D->SetTitle("250-mm SciD_{3} [3-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3}] D-stream");
   grmu3D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu3D->GetXaxis()->SetRangeUser(0,2);
   grmu3D->GetYaxis()->SetRangeUser(0,0);
   grmu3D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu3D->GetYaxis()->SetTitleOffset(1.8);
   grmu3D->SetMarkerColor(kGreen-2);
   grmu3D->SetMarkerStyle(33);
   grmu3D->SetLineColor(kGreen-2);
   grmu3D->Draw("ALP");
   	     
   c->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu4D = new TGraph(nsamps,Ethrmu,Edep500mu3Al1D);
   grmu4D->SetTitle("5-mm SciD_{1} [3-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3}] D-stream");
   grmu4D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu4D->GetXaxis()->SetRangeUser(0,2);
   grmu4D->GetYaxis()->SetRangeUser(0,1);
   grmu4D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu4D->GetYaxis()->SetTitleOffset(1.8);
   grmu4D->SetMarkerColor(kGreen-2);
   grmu4D->SetMarkerStyle(33);
   grmu4D->SetLineColor(kGreen-2);
   grmu4D->Draw("ALP");	     	     
	     
   c->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu5D = new TGraph(nsamps,Ethrmu,Edep500mu3Al2D);
   grmu5D->SetTitle("5-mm SciD_{2} [3-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3}] D-stream");
   grmu5D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu5D->GetXaxis()->SetRangeUser(0,2);
   grmu5D->GetYaxis()->SetRangeUser(0,1);
   grmu5D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu5D->GetYaxis()->SetTitleOffset(1.8);
   grmu5D->SetMarkerColor(kGreen-2);
   grmu5D->SetMarkerStyle(33);
   grmu5D->SetLineColor(kGreen-2);
   grmu5D->Draw("ALP");	     
   	     
   c->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu6D = new TGraph(nsamps,Ethrmu,Edep500mu3Al3D);
   grmu6D->SetTitle("500-mm SciD_{3} [3-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3}] D-stream");
   grmu6D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu6D->GetXaxis()->SetRangeUser(0,2);
   grmu6D->GetYaxis()->SetRangeUser(0,1);
   grmu6D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu6D->GetYaxis()->SetTitleOffset(1.8);
   grmu6D->SetMarkerColor(kGreen-2);
   grmu6D->SetMarkerStyle(33);
   grmu6D->SetLineColor(kGreen-2);
   grmu6D->Draw("ALP");    

   c->cd(7);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu7D = new TGraph(nsamps,Ethrmu,Edep750mu3Al1D);
   grmu7D->SetTitle("5-mm SciD_{1} [3-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3}] D-stream");
   grmu7D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu7D->GetXaxis()->SetRangeUser(0,2);
   grmu7D->GetYaxis()->SetRangeUser(0,1);
   grmu7D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu7D->GetYaxis()->SetTitleOffset(1.8);
   grmu7D->SetMarkerColor(kGreen-2);
   grmu7D->SetMarkerStyle(33);
   grmu7D->SetLineColor(kGreen-2);
   grmu7D->Draw("ALP");	     	     
	    
   c->cd(8);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu8D = new TGraph(nsamps,Ethrmu,Edep750mu3Al2D);
   grmu8D->SetTitle("5-mm SciD_{2} [3-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3}] D-stream");
   grmu8D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu8D->GetXaxis()->SetRangeUser(0,2);
   grmu8D->GetYaxis()->SetRangeUser(0,1);
   grmu8D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu8D->GetYaxis()->SetTitleOffset(1.8);
   grmu8D->SetMarkerColor(kGreen-2);
   grmu8D->SetMarkerStyle(33);
   grmu8D->SetLineColor(kGreen-2);
   grmu8D->Draw("ALP");	     
   	     
   c->cd(9);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu9D = new TGraph(nsamps,Ethrmu,Edep750mu3Al3D);
   grmu9D->SetTitle("750-mm SciD_{3} [3-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3}] D-stream");
   grmu9D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu9D->GetXaxis()->SetRangeUser(0,2);
   grmu9D->GetYaxis()->SetRangeUser(0,1);
   grmu9D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu9D->GetYaxis()->SetTitleOffset(1.8);
   grmu9D->SetMarkerColor(kGreen-2);
   grmu9D->SetMarkerStyle(33);
   grmu9D->SetLineColor(kGreen-2);
   grmu9D->Draw("ALP");    

   c->SaveAs("Planar_"+fileType+"_Edep_vs_Ethr_3mm_Al_D_stream_"+process+".pdf");
   c->SaveAs("Planar_"+fileType+"_Edep_vs_Ethr_3mm_Al_D_stream_"+process+".png");
   c->SaveAs("Planar_"+fileType+"_Edep_vs_Ethr_3mm_Al_D_stream_"+process+".C");
   
     
   
   TCanvas *d = new TCanvas("d","E_{THR}",800,600);
   d->Divide(3,3);
   d->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu1D = new TGraph(nsamps,Ethrmu,Edep250mu6Al1D);
   gr6Almu1D->SetTitle("5-mm SciD_{1} [6-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3}] D-stream");
   gr6Almu1D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu1D->GetXaxis()->SetRangeUser(0,2);
   gr6Almu1D->GetYaxis()->SetRangeUser(0,1);
   gr6Almu1D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu1D->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu1D->SetMarkerColor(kGreen-2);
   gr6Almu1D->SetMarkerStyle(33);
   gr6Almu1D->SetLineColor(kGreen-2);
   gr6Almu1D->Draw("ALP");
   	     
   d->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu2D = new TGraph(nsamps,Ethrmu,Edep250mu6Al2D);
   gr6Almu2D->SetTitle("5-mm SciD_{2} [6-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3}] D-stream");
   gr6Almu2D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu2D->GetXaxis()->SetRangeUser(0,2);
   gr6Almu2D->GetYaxis()->SetRangeUser(0,1);
   gr6Almu2D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu2D->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu2D->SetMarkerColor(kGreen-2);
   gr6Almu2D->SetMarkerStyle(33);
   gr6Almu2D->SetLineColor(kGreen-2);
   gr6Almu2D->Draw("ALP");	     
   	     
   d->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu3D = new TGraph(nsamps,Ethrmu,Edep250mu6Al3D);
   gr6Almu3D->SetTitle("250-mm SciD_{3} [6-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3}] D-stream");
   gr6Almu3D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu3D->GetXaxis()->SetRangeUser(0,2);
   gr6Almu3D->GetYaxis()->SetRangeUser(0,1);
   gr6Almu3D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu3D->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu3D->SetMarkerColor(kGreen-2);
   gr6Almu3D->SetMarkerStyle(33);
   gr6Almu3D->SetLineColor(kGreen-2);
   gr6Almu3D->Draw("ALP");
   	     
   d->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu4D = new TGraph(nsamps,Ethrmu,Edep500mu6Al1D);
   gr6Almu4D->SetTitle("5-mm SciD_{1} [6-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3}] D-stream");
   gr6Almu4D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu4D->GetXaxis()->SetRangeUser(0,2);
   gr6Almu4D->GetYaxis()->SetRangeUser(0,1);
   gr6Almu4D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu4D->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu4D->SetMarkerColor(kGreen-2);
   gr6Almu4D->SetMarkerStyle(33);
   gr6Almu4D->SetLineColor(kGreen-2);
   gr6Almu4D->Draw("ALP");	     	     
	     
   d->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu5D = new TGraph(nsamps,Ethrmu,Edep500mu6Al2D);
   gr6Almu5D->SetTitle("5-mm SciD_{2} [6-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3}] D-stream");
   gr6Almu5D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu5D->GetXaxis()->SetRangeUser(0,2);
   gr6Almu5D->GetYaxis()->SetRangeUser(0,1);
   gr6Almu5D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu5D->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu5D->SetMarkerColor(kGreen-2);
   gr6Almu5D->SetMarkerStyle(33);
   gr6Almu5D->SetLineColor(kGreen-2);
   gr6Almu5D->Draw("ALP");	     
   	     
   d->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu6D = new TGraph(nsamps,Ethrmu,Edep500mu6Al3D);
   gr6Almu6D->SetTitle("500-mm SciD_{3} [6-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3}] D-stream");
   gr6Almu6D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu6D->GetXaxis()->SetRangeUser(0,2);
   gr6Almu6D->GetYaxis()->SetRangeUser(0,1);
   gr6Almu6D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu6D->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu6D->SetMarkerColor(kGreen-2);
   gr6Almu6D->SetMarkerStyle(33);
   gr6Almu6D->SetLineColor(kGreen-2);
   gr6Almu6D->Draw("ALP");    

   d->cd(7);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu7D = new TGraph(nsamps,Ethrmu,Edep750mu6Al1D);
   gr6Almu7D->SetTitle("5-mm SciD_{1} [6-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3}] D-stream");
   gr6Almu7D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu7D->GetXaxis()->SetRangeUser(0,2);
   gr6Almu7D->GetYaxis()->SetRangeUser(0,1);
   gr6Almu7D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu7D->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu7D->SetMarkerColor(kGreen-2);
   gr6Almu7D->SetMarkerStyle(33);
   gr6Almu7D->SetLineColor(kGreen-2);
   gr6Almu7D->Draw("ALP");	     	     
	    
   d->cd(8);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu8D = new TGraph(nsamps,Ethrmu,Edep750mu6Al2D);
   gr6Almu8D->SetTitle("5-mm SciD_{2} [6-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3}] D-stream");
   gr6Almu8D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu8D->GetXaxis()->SetRangeUser(0,2);
   gr6Almu8D->GetYaxis()->SetRangeUser(0,1);
   gr6Almu8D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu8D->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu8D->SetMarkerColor(kGreen-2);
   gr6Almu8D->SetMarkerStyle(33);
   gr6Almu8D->SetLineColor(kGreen-2);
   gr6Almu8D->Draw("ALP");	     
   	     
   d->cd(9);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu9D = new TGraph(nsamps,Ethrmu,Edep750mu6Al3D);
   gr6Almu9D->SetTitle("750-mm SciD_{3} [6-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3}] D-stream");
   gr6Almu9D->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu9D->GetXaxis()->SetRangeUser(0,2);
   gr6Almu9D->GetYaxis()->SetRangeUser(0,1);
   gr6Almu9D->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu9D->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu9D->SetMarkerColor(kGreen-2);
   gr6Almu9D->SetMarkerStyle(33);
   gr6Almu9D->SetLineColor(kGreen-2);
   gr6Almu9D->Draw("ALP");    
   
   d->SaveAs("Planar_"+fileType+"_Edep_vs_Ethr_6mm_Al_D_stream_"+process+".pdf");
   d->SaveAs("Planar_"+fileType+"_Edep_vs_Ethr_6mm_Al_D_stream_"+process+".png");
   d->SaveAs("Planar_"+fileType+"_Edep_vs_Ethr_6mm_Al_D_stream_"+process+".C");

	
	
   TCanvas *e = new TCanvas("e","E_{THR}",800,600);
   e->Divide(3,3);
   e->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu1U = new TGraph(nsamps,Ethrmu,Edep250mu3Al1U);
   grmu1U->SetTitle("5-mm SciD_{1} [3-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3}] U-stream");
   grmu1U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu1U->GetXaxis()->SetRangeUser(0,2);
   grmu1U->GetYaxis()->SetRangeUser(0,1);
   grmu1U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu1U->GetYaxis()->SetTitleOffset(1.8);
   grmu1U->SetMarkerColor(kGreen-2);
   grmu1U->SetMarkerStyle(33);
   grmu1U->SetLineColor(kGreen-2);
   grmu1U->Draw("ALP");
   	     
   e->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu2U = new TGraph(nsamps,Ethrmu,Edep250mu3Al2U);
   grmu2U->SetTitle("5-mm SciD_{2} [3-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3}] U-stream");
   grmu2U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu2U->GetXaxis()->SetRangeUser(0,2);
   grmu2U->GetYaxis()->SetRangeUser(0,1);
   grmu2U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu2U->GetYaxis()->SetTitleOffset(1.8);
   grmu2U->SetMarkerColor(kGreen-2);
   grmu2U->SetMarkerStyle(33);
   grmu2U->SetLineColor(kGreen-2);
   grmu2U->Draw("ALP");	     
   	     
   e->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu3U = new TGraph(nsamps,Ethrmu,Edep250mu3Al3U);
   grmu3U->SetTitle("250-mm SciD_{3} [3-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3}] U-stream");
   grmu3U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu3U->GetXaxis()->SetRangeUser(0,2);
   grmu3U->GetYaxis()->SetRangeUser(0,0);
   grmu3U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu3U->GetYaxis()->SetTitleOffset(1.8);
   grmu3U->SetMarkerColor(kGreen-2);
   grmu3U->SetMarkerStyle(33);
   grmu3U->SetLineColor(kGreen-2);
   grmu3U->Draw("ALP");
   	     
   e->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu4U = new TGraph(nsamps,Ethrmu,Edep500mu3Al1U);
   grmu4U->SetTitle("5-mm SciD_{1} [3-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3}] U-stream");
   grmu4U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu4U->GetXaxis()->SetRangeUser(0,2);
   grmu4U->GetYaxis()->SetRangeUser(0,1);
   grmu4U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu4U->GetYaxis()->SetTitleOffset(1.8);
   grmu4U->SetMarkerColor(kGreen-2);
   grmu4U->SetMarkerStyle(33);
   grmu4U->SetLineColor(kGreen-2);
   grmu4U->Draw("ALP");	     	     
	     
   e->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu5U = new TGraph(nsamps,Ethrmu,Edep500mu3Al2U);
   grmu5U->SetTitle("5-mm SciD_{2} [3-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3}] U-stream");
   grmu5U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu5U->GetXaxis()->SetRangeUser(0,2);
   grmu5U->GetYaxis()->SetRangeUser(0,1);
   grmu5U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu5U->GetYaxis()->SetTitleOffset(1.8);
   grmu5U->SetMarkerColor(kGreen-2);
   grmu5U->SetMarkerStyle(33);
   grmu5U->SetLineColor(kGreen-2);
   grmu5U->Draw("ALP");	     
   	     
   e->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu6U = new TGraph(nsamps,Ethrmu,Edep500mu3Al3U);
   grmu6U->SetTitle("500-mm SciD_{3} [3-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3}] U-stream");
   grmu6U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu6U->GetXaxis()->SetRangeUser(0,2);
   grmu6U->GetYaxis()->SetRangeUser(0,1);
   grmu6U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu6U->GetYaxis()->SetTitleOffset(1.8);
   grmu6U->SetMarkerColor(kGreen-2);
   grmu6U->SetMarkerStyle(33);
   grmu6U->SetLineColor(kGreen-2);
   grmu6U->Draw("ALP");    

   e->cd(7);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu7U = new TGraph(nsamps,Ethrmu,Edep750mu3Al1U);
   grmu7U->SetTitle("5-mm SciD_{1} [3-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3}] U-stream");
   grmu7U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu7U->GetXaxis()->SetRangeUser(0,2);
   grmu7U->GetYaxis()->SetRangeUser(0,1);
   grmu7U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu7U->GetYaxis()->SetTitleOffset(1.8);
   grmu7U->SetMarkerColor(kGreen-2);
   grmu7U->SetMarkerStyle(33);
   grmu7U->SetLineColor(kGreen-2);
   grmu7U->Draw("ALP");	     	     
	    
   e->cd(8);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu8U = new TGraph(nsamps,Ethrmu,Edep750mu3Al2U);
   grmu8U->SetTitle("5-mm SciD_{2} [3-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3}] U-stream");
   grmu8U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu8U->GetXaxis()->SetRangeUser(0,2);
   grmu8U->GetYaxis()->SetRangeUser(0,1);
   grmu8U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu8U->GetYaxis()->SetTitleOffset(1.8);
   grmu8U->SetMarkerColor(kGreen-2);
   grmu8U->SetMarkerStyle(33);
   grmu8U->SetLineColor(kGreen-2);
   grmu8U->Draw("ALP");	     
   	     
   e->cd(9);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu9U = new TGraph(nsamps,Ethrmu,Edep750mu3Al3U);
   grmu9U->SetTitle("750-mm SciD_{3} [3-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3}] U-stream");
   grmu9U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu9U->GetXaxis()->SetRangeUser(0,2);
   grmu9U->GetYaxis()->SetRangeUser(0,1);
   grmu9U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu9U->GetYaxis()->SetTitleOffset(1.8);
   grmu9U->SetMarkerColor(kGreen-2);
   grmu9U->SetMarkerStyle(33);
   grmu9U->SetLineColor(kGreen-2);
   grmu9U->Draw("ALP");    

   e->SaveAs("Planar_"+fileType+"_Edep_vs_Ethr_3mm_Al_U_stream_"+process+".pdf");
   e->SaveAs("Planar_"+fileType+"_Edep_vs_Ethr_3mm_Al_U_stream_"+process+".png");
   e->SaveAs("Planar_"+fileType+"_Edep_vs_Ethr_3mm_Al_U_stream_"+process+".C");
   
     
   
   TCanvas *f = new TCanvas("f","E_{THR}",800,600);
   f->Divide(3,3);
   f->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu1U = new TGraph(nsamps,Ethrmu,Edep250mu6Al1U);
   gr6Almu1U->SetTitle("5-mm SciD_{1} [6-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3}] U-stream");
   gr6Almu1U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu1U->GetXaxis()->SetRangeUser(0,2);
   gr6Almu1U->GetYaxis()->SetRangeUser(0,1);
   gr6Almu1U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu1U->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu1U->SetMarkerColor(kGreen-2);
   gr6Almu1U->SetMarkerStyle(33);
   gr6Almu1U->SetLineColor(kGreen-2);
   gr6Almu1U->Draw("ALP");
   	     
   f->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu2U = new TGraph(nsamps,Ethrmu,Edep250mu6Al2U);
   gr6Almu2U->SetTitle("5-mm SciD_{2} [6-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3}] U-stream");
   gr6Almu2U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu2U->GetXaxis()->SetRangeUser(0,2);
   gr6Almu2U->GetYaxis()->SetRangeUser(0,1);
   gr6Almu2U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu2U->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu2U->SetMarkerColor(kGreen-2);
   gr6Almu2U->SetMarkerStyle(33);
   gr6Almu2U->SetLineColor(kGreen-2);
   gr6Almu2U->Draw("ALP");	     
   	     
   f->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu3U = new TGraph(nsamps,Ethrmu,Edep250mu6Al3U);
   gr6Almu3U->SetTitle("250-mm SciD_{3} [6-mm Al + 2x5-mm SciD_{1,2} + 250-mm SciD_{3}] U-stream");
   gr6Almu3U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu3U->GetXaxis()->SetRangeUser(0,2);
   gr6Almu3U->GetYaxis()->SetRangeUser(0,1);
   gr6Almu3U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu3U->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu3U->SetMarkerColor(kGreen-2);
   gr6Almu3U->SetMarkerStyle(33);
   gr6Almu3U->SetLineColor(kGreen-2);
   gr6Almu3U->Draw("ALP");
   	     
   f->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu4U = new TGraph(nsamps,Ethrmu,Edep500mu6Al1U);
   gr6Almu4U->SetTitle("5-mm SciD_{1} [6-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3}] U-stream");
   gr6Almu4U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu4U->GetXaxis()->SetRangeUser(0,2);
   gr6Almu4U->GetYaxis()->SetRangeUser(0,1);
   gr6Almu4U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu4U->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu4U->SetMarkerColor(kGreen-2);
   gr6Almu4U->SetMarkerStyle(33);
   gr6Almu4U->SetLineColor(kGreen-2);
   gr6Almu4U->Draw("ALP");	     	     
	     
   f->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu5U = new TGraph(nsamps,Ethrmu,Edep500mu6Al2U);
   gr6Almu5U->SetTitle("5-mm SciD_{2} [6-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3}] U-stream");
   gr6Almu5U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu5U->GetXaxis()->SetRangeUser(0,2);
   gr6Almu5U->GetYaxis()->SetRangeUser(0,1);
   gr6Almu5U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu5U->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu5U->SetMarkerColor(kGreen-2);
   gr6Almu5U->SetMarkerStyle(33);
   gr6Almu5U->SetLineColor(kGreen-2);
   gr6Almu5U->Draw("ALP");	     
   	     
   f->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu6U = new TGraph(nsamps,Ethrmu,Edep500mu6Al3U);
   gr6Almu6U->SetTitle("500-mm SciD_{3} [6-mm Al + 2x5-mm SciD_{1,2} + 500-mm SciD_{3}] U-stream");
   gr6Almu6U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu6U->GetXaxis()->SetRangeUser(0,2);
   gr6Almu6U->GetYaxis()->SetRangeUser(0,1);
   gr6Almu6U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu6U->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu6U->SetMarkerColor(kGreen-2);
   gr6Almu6U->SetMarkerStyle(33);
   gr6Almu6U->SetLineColor(kGreen-2);
   gr6Almu6U->Draw("ALP");    

   f->cd(7);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu7U = new TGraph(nsamps,Ethrmu,Edep750mu6Al1U);
   gr6Almu7U->SetTitle("5-mm SciD_{1} [6-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3}] U-stream");
   gr6Almu7U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu7U->GetXaxis()->SetRangeUser(0,2);
   gr6Almu7U->GetYaxis()->SetRangeUser(0,1);
   gr6Almu7U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu7U->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu7U->SetMarkerColor(kGreen-2);
   gr6Almu7U->SetMarkerStyle(33);
   gr6Almu7U->SetLineColor(kGreen-2);
   gr6Almu7U->Draw("ALP");	     	     
	    
   f->cd(8);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu8U = new TGraph(nsamps,Ethrmu,Edep750mu6Al2U);
   gr6Almu8U->SetTitle("5-mm SciD_{2} [6-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3}] U-stream");
   gr6Almu8U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu8U->GetXaxis()->SetRangeUser(0,2);
   gr6Almu8U->GetYaxis()->SetRangeUser(0,1);
   gr6Almu8U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu8U->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu8U->SetMarkerColor(kGreen-2);
   gr6Almu8U->SetMarkerStyle(33);
   gr6Almu8U->SetLineColor(kGreen-2);
   gr6Almu8U->Draw("ALP");	     
   	     
   f->cd(9);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu9U = new TGraph(nsamps,Ethrmu,Edep750mu6Al3U);
   gr6Almu9U->SetTitle("750-mm SciD_{3} [6-mm Al + 2x5-mm SciD_{1,2} + 750-mm SciD_{3}] U-stream");
   gr6Almu9U->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu9U->GetXaxis()->SetRangeUser(0,2);
   gr6Almu9U->GetYaxis()->SetRangeUser(0,1);
   gr6Almu9U->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   gr6Almu9D->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu9U->SetMarkerColor(kGreen-2);
   gr6Almu9U->SetMarkerStyle(33);
   gr6Almu9U->SetLineColor(kGreen-2);
   gr6Almu9U->Draw("ALP");    
   
   f->SaveAs("Planar_"+fileType+"_Edep_vs_Ethr_6mm_Al_U_stream_"+process+".pdf");
   f->SaveAs("Planar_"+fileType+"_Edep_vs_Ethr_6mm_Al_U_stream_"+process+".png");
   f->SaveAs("Planar_"+fileType+"_Edep_vs_Ethr_6mm_Al_U_stream_"+process+".C");
	
	
	
	
}


int main() {
   EdepPlanar();
   return 0;
}
