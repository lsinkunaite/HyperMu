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

void OrderEdepSuper(){

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
   std::string BGOmaterial1 = "plastic";
   std::string BGOmaterial2 = "BGO";
   std::string BGOmaterial3 = "NaI";	
   std::string dA1 = "500";
   std::string dL11 = "250";
   std::string dL12 = "30";
   std::string dL13 = "100";
   
   /*********************************/
   /*         Input files           */
   /*********************************/

   const int nsamps = 101;
   const int nbins = 150;


   // Names of the files
   // X-ray cascade
   std::string filex1 = path+cavmaterial+"_cav_"+BGOmaterial1+"_dA1_"+dA1+"mm_dL1_"+dL11+"mm_1e5goldcascade.root";
   std::string filex2 = path+cavmaterial+"_cav_"+BGOmaterial2+"_dA1_"+dA1+"mm_dL1_"+dL12+"mm_1e5goldcascade.root";
   std::string filex3 = path+cavmaterial+"_cav_"+BGOmaterial3+"_dA1_"+dA1+"mm_dL1_"+dL13+"mm_1e5goldcascade.root";

   // Mu-decay
   std::string filemu1 = path+cavmaterial+"_cav_"+BGOmaterial1+"_dA1_"+dA1+"mm_dL1_"+dL11+"mm_1e5mudecay.root";
   std::string filemu2 = path+cavmaterial+"_cav_"+BGOmaterial2+"_dA1_"+dA1+"mm_dL1_"+dL12+"mm_1e5mudecay.root";
   std::string filemu3 = path+cavmaterial+"_cav_"+BGOmaterial3+"_dA1_"+dA1+"mm_dL1_"+dL13+"mm_1e5mudecay.root";


   // TFiles 
   TFile* fmu1 = new TFile(TString(filemu1));
   TFile* fmu2 = new TFile(TString(filemu2));
   TFile* fmu3 = new TFile(TString(filemu3));
   TFile* fx1 = new TFile(TString(filex1));
   TFile* fx2 = new TFile(TString(filex2));
   TFile* fx3 = new TFile(TString(filex3));

   // Histograms
   TH1F *hmuSciDet11 = new TH1F("hmuSciDet11","Edep",2*nbins+1,-0.01,1.5);
   TH1F *hmuSciDet12 = new TH1F("hmuSciDet12","Edep",2*nbins+1,-0.01,1.5);
   TH1F *hmuSciDet13 = new TH1F("hmuSciDet13","Edep",2*nbins+1,-0.01,1.5);
   TH1F *hxSciDet11 = new TH1F("hxSciDet11","Edep",2*nbins+1,-0.01,1.5);
   TH1F *hxSciDet12 = new TH1F("hxSciDet12","Edep",2*nbins+1,-0.01,1.5);
   TH1F *hxSciDet13 = new TH1F("hxSciDet13","Edep",2*nbins+1,-0.01,1.5);
   
   // TTrees
   TTree *tmuSciDet11 = (TTree*)fmu1->Get("Detector/SciDet1");
   TTree *tmuSciDet12 = (TTree*)fmu2->Get("Detector/SciDet1");
   TTree *tmuSciDet13 = (TTree*)fmu3->Get("Detector/SciDet1");
   TTree *txSciDet11 = (TTree*)fx1->Get("Detector/SciDet1");
   TTree *txSciDet12 = (TTree*)fx2->Get("Detector/SciDet1");
   TTree *txSciDet13 = (TTree*)fx3->Get("Detector/SciDet1");


   // Drawings
   tmuSciDet11->Draw("Edep>>hmuSciDet11","","");
   tmuSciDet12->Draw("Edep>>hmuSciDet12","","");
   tmuSciDet13->Draw("Edep>>hmuSciDet13","","");
   txSciDet11->Draw("Edep>>hxSciDet11","","");
   txSciDet12->Draw("Edep>>hxSciDet12","","");
   txSciDet13->Draw("Edep>>hxSciDet13","","");


   // Colours
   hmuSciDet11->SetLineColor(kRed);
   hmuSciDet12->SetLineColor(kOrange);
   hmuSciDet13->SetLineColor(kYellow);
   hxSciDet11->SetLineColor(kBlack);
   hxSciDet12->SetLineColor(kBlue);
   hxSciDet13->SetLineColor(kGreen-2);


   //-------------------------------------------------------------------
   //                          Plotting 
   //-------------------------------------------------------------------


   TCanvas *c = new TCanvas("c","Edep",800,600);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   hxSciDet11->SetTitle("d_{A1} = "+TString(dA1)+"-mm");
   hxSciDet11->GetXaxis()->SetTitle("E [MeV]");
   hxSciDet11->GetYaxis()->SetTitle("# of counts");
   hxSciDet11->GetYaxis()->SetTitleOffset(1.0);
   hxSciDet11->Draw();
   hxSciDet12->Draw("same");
   hxSciDet13->Draw("same");
   hmuSciDet11->Draw("same");
   hmuSciDet12->Draw("same");
   hmuSciDet13->Draw("same");
   TLegend *legend = new TLegend(0.65,0.65,0.86,0.82);
   legend->AddEntry(hxSciDet11,"#muAu X-ray cascade: Plastic","f");
   legend->AddEntry(hxSciDet12,"#muAu X-ray cascade: BGO","f");
   legend->AddEntry(hxSciDet13,"#muAu X-ray cascade: NaI","f");
   legend->AddEntry(hmuSciDet11,"#mu-decay: Plastic","f");
   legend->AddEntry(hmuSciDet12,"#mu-decay: BGO","f");
   legend->AddEntry(hmuSciDet13,"#mu-decay: NaI","f");
   legend->Draw();
      

   c->SaveAs("Ordering/"+TString(cavmaterial)+"_cav_dA1_"+TString(dA1)+"_Edep_SciDet1.pdf");
   c->SaveAs("Ordering/"+TString(cavmaterial)+"_cav_dA1_"+TString(dA1)+"_Edep_SciDet1.png");
   c->SaveAs("Ordering/"+TString(cavmaterial)+"_cav_dA1_"+TString(dA1)+"_Edep_SciDet1.C");


 
} 
 
 int main() {
   OrderEdepSuper();
   return 0;
}  
