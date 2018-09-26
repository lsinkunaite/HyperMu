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
//#include "TVector.h"

void Bfield_5T_MULTI(){

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
   std::string filemu = "../../simdata/magnetic/Bfield_5T_simple_4mm_Al_det_BGO1e6mudecay.root";
   std::string filex = "../../simdata/magnetic/Bfield_5T_simple_4mm_Al_det_BGO1e6goldcascade.root";

   std::string filemuTubeD = "../../simdata/magnetic/Bfield_5T_simple_4mm_Al_det_BGO1e6mudecay_TubeD.txt";
   std::string filexTubeD = "../../simdata/magnetic/Bfield_5T_simple_4mm_Al_det_BGO1e6goldcascade_TubeD.txt";
   
   const int nbins = 150;


   // TFiles 
   TFile* fmu = new TFile(TString(filemu));
   TFile* fx = new TFile(TString(filex));

   // Histograms
   TH1F *hmuTubeD = new TH1F("hmuTubeD","Edep",4*nbins+1,-0.05,60);
   TH1F *hxTubeD = new TH1F("hxTubeD","Edep",nbins+1,-0.05,15);
   TH1F *hmuTubeDZ = new TH1F("hmuTubeDZ","Edep",3*nbins+1,-0.05,5);
   TH1F *hxTubeDZ = new TH1F("hxTubeDZ","Edep",nbins+1,-0.05,15);

   // TTrees
   TTree *tmuTubeD = (TTree*)fmu->Get("Detector/TubeDet");
   TTree *txTubeD = (TTree*)fx->Get("Detector/TubeDet");


   // Drawings
   tmuTubeD->Draw("Edep>>hmuTubeD","","");
   txTubeD->Draw("Edep>>hxTubeD","","");
   
   tmuTubeD->Draw("Edep>>hmuTubeDZ","","");
   txTubeD->Draw("Edep>>hxTubeDZ","","");



   std::vector<std::string> mufiles;
   std::vector<std::string> Xfiles;

   // Mu-decay
   mufiles.push_back(filemuTubeD);
   // X-ray cascade
   Xfiles.push_back(filexTubeD);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep;

   const int nsamps = 101;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
   float Ethr;
   
   Ethrmu[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;

   std::vector< std::vector<double> > TotEdepmuTD(mufiles.size(),std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxTD(Xfiles.size(),std::vector<double>(nsamps));

   int binmuTD, binxTD;
   double integralmuTD, integralxTD;
   
   for (int m=0; m < nsamps; m++) {
	   
      Ethr = Ethrmu[m];

      binmuTD = hmuTubeD->GetXaxis()->FindBin(Ethr);
      integralmuTD = hmuTubeD->Integral(0,binmuTD,"");	     
      binxTD = hxTubeD->GetXaxis()->FindBin(Ethr);
      integralxTD = hxTubeD->Integral(0,binxTD,"");

      TotEdepmuTD[0][m] = integralmuTD;
      TotEdepxTD[0][m] = integralxTD;     
      
   }
   	  	     
   float EdepmuTubeD[nsamps] = {};
   float EdepxTubeD[nsamps] = {};
   
   for (int i=0; i<nsamps; i++) {
	  EdepmuTubeD[i] = TotEdepmuTD[0][i]/TotEdepmuTD[0][nsamps-1];
	  EdepxTubeD[i] = TotEdepxTD[0][i]/TotEdepxTD[0][nsamps-1]; 
   }



   // Colours 
   hmuTubeD->SetLineColor(kBlack);
   hxTubeD->SetLineColor(kGreen-2);

   hmuTubeDZ->SetLineColor(kBlack);
   hxTubeDZ->SetLineColor(kGreen-2);

   
   /********************************/
   /*           Plotting           */
   /********************************/

   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(3,3);
   c->cd(1);
   gPad->SetLogy();
   hmuTubeD->SetTitle("Bfield_5T_4mm_Al: #mu-decay vs X-ray cascade: 50-mm round BGO");
   hmuTubeD->GetXaxis()->SetTitle("Edep [MeV]");
   hmuTubeD->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuTubeD->GetYaxis()->SetTitleOffset(2.0);
   hmuTubeD->Draw();
   c->Update();
   TPaveStats *stmuTubeD = (TPaveStats*)hmuTubeD->GetListOfFunctions()->FindObject("stats");
   stmuTubeD->SetY1NDC(0.63); stmuTubeD->SetY2NDC(0.78);
   hxTubeD->Draw("sames");
   c->Update();
   TPaveStats *stxTubeD = (TPaveStats*)hxTubeD->GetListOfFunctions()->FindObject("stats");
   stxTubeD->SetTextColor(kGreen-2);
   stxTubeD->Draw();

   c->cd(4);
   gPad->SetLogy();
   hmuTubeDZ->SetTitle("Bfield_5T_4mm_Al: #mu-decay vs X-ray cascade: 50-mm round BGO");
   hmuTubeDZ->GetXaxis()->SetTitle("Edep [MeV]");
   hmuTubeDZ->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuTubeDZ->GetYaxis()->SetTitleOffset(2.0);
   hmuTubeDZ->Draw();
   c->Update();
   TPaveStats *stmuTubeDZ = (TPaveStats*)hmuTubeDZ->GetListOfFunctions()->FindObject("stats");
   stmuTubeDZ->SetY1NDC(0.63); stmuTubeDZ->SetY2NDC(0.78);
   hxTubeDZ->Draw("sames");
   c->Update();
   TPaveStats *stxTubeDZ = (TPaveStats*)hxTubeDZ->GetListOfFunctions()->FindObject("stats");
   stxTubeDZ->SetTextColor(kGreen-2);
   stxTubeDZ->Draw();
   
   c->cd(7);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu1 = new TGraph(nsamps,Ethrmu,EdepmuTubeD);
   grmu1->SetTitle("Bfield_5T_4mm_Al: #mu-decay vs X-ray cascade: 50-mm round BGO");
   grmu1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu1->GetXaxis()->SetRangeUser(0,2);
   grmu1->GetYaxis()->SetRangeUser(0,1);
   grmu1->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu1->GetYaxis()->SetTitleOffset(1.8);
   grmu1->SetMarkerColor(kBlack);
   grmu1->SetMarkerStyle(33);
   grmu1->Draw("ALP");
   c->Update();
   TGraph *grx1 = new TGraph(nsamps,Ethrmu,EdepxTubeD);
   grx1->SetMarkerColor(kGreen-2);
   grx1->SetMarkerStyle(33);
   grx1->SetLineColor(kGreen-2);
   grx1->Draw("LP");

   c->SaveAs("Bfield_5T_MULTI_Edep.pdf");
   c->SaveAs("Bfield_5T_MULTI_Edep.png");
   c->SaveAs("Bfield_5T_MULTI_Edep.C");


}


int main() {
   Bfield_5T_MULTI();
return 0;
}  
