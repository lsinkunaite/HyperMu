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

void OrderEdep(){

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
   
   // Path name
   std::string path = "../../simdata/order/";
   int pathL = path.length();
   std::string cavmaterial = "Cu";
   std::string BGOmaterial = "NaI";	
   std::string dA1 = "500";
   std::string dL1 = "200";
   
   /*********************************/
   /*         Input files           */
   /*********************************/

   const int nsamps = 101;
   const int nbins = 150;


   // Names of the files
   // X-ray cascade
   std::string filex = path+cavmaterial+"_cav_"+BGOmaterial+"_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5goldcascade.root";

   // Mu-decay
   std::string filemu = path+cavmaterial+"_cav_"+BGOmaterial+"_dA1_"+dA1+"mm_dL1_"+dL1+"mm_1e5mudecay.root";


   // TFiles 
   TFile* fmu = new TFile(TString(filemu));
   TFile* fx = new TFile(TString(filex));

   // Histograms
   TH1F *hmuBGONaIDet1 = new TH1F("hmuBGONaIDet1","Edep",4*nbins+1,-0.01,53.0);
   TH1F *hxBGONaIDet1 = new TH1F("hxBGONaIDet1","Edep",4*nbins+1,-0.01,53.0);
   
   // TTrees
   TTree *tmuBGONaIDet1 = (TTree*)fmu->Get("Detector/BGONaIDet1");
   TTree *txBGONaIDet1 = (TTree*)fx->Get("Detector/BGONaIDet1");

   // Drawings
   tmuBGONaIDet1->Draw("Edep>>hmuBGONaIDet1","","");
   txBGONaIDet1->Draw("Edep>>hxBGONaIDet1","","");

   // Colours
   hmuBGONaIDet1->SetLineColor(kRed);
   hxBGONaIDet1->SetLineColor(kBlack);


   //-------------------------------------------------------------------
   //                          Plotting 
   //-------------------------------------------------------------------


   TCanvas *c = new TCanvas("c","Edep",800,600);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   hxBGONaIDet1->SetTitle(TString(BGOmaterial)+" d_{A1}="+TString(dA1)+"-mm d_{L1}="+TString(dL1)+"-mm");
   hxBGONaIDet1->GetXaxis()->SetTitle("E [MeV]");
   hxBGONaIDet1->GetYaxis()->SetTitle("# of counts");
   hxBGONaIDet1->GetYaxis()->SetTitleOffset(1.0);
   hxBGONaIDet1->Draw();
   hmuBGONaIDet1->Draw("same");   
   
   TLine *separator = new TLine(6.5,c->GetUymin(),6.5,5e4);
   separator->SetLineColor(kGreen-2);
   separator->SetLineStyle(3);
   separator->SetLineWidth(8);
//   separator->Draw("same");

   c->SaveAs("Ordering/"+TString(cavmaterial)+"_cav_"+TString(BGOmaterial)+"_dA1_"+TString(dA1)+"mm_dL1_"+TString(dL1)+"mm_Edep_BGO1.pdf");
   c->SaveAs("Ordering/"+TString(cavmaterial)+"_cav_"+TString(BGOmaterial)+"_dA1_"+TString(dA1)+"mm_dL1_"+TString(dL1)+"mm_Edep_BGO1.png");
   c->SaveAs("Ordering/"+TString(cavmaterial)+"_cav_"+TString(BGOmaterial)+"_dA1_"+TString(dA1)+"mm_dL1_"+TString(dL1)+"mm_Edep_BGO1.C");


 
} 
 
 int main() {
   OrderEdep();
   return 0;
}  
