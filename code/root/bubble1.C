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

//ROOT includes
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

void bubble1(){

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
   gStyle->SetTitleFillColor(0);
   gStyle->SetPalette(1,0);
   //gStyle->SetOptTitle(kFALSE);
   gStyle->SetLabelSize(0.045,"XYZ");
   gStyle->SetTitleSize(0.05,"XYZ");
   gStyle->SetHistLineWidth(2);

   /*********************************/
   /*         Input files           */
   /*********************************/

   // Names of the files
   std::string filemu = "bubble_Nevts_BGOSphere_1e6_mudecay.root";
   std::string filex = "bubble_Nevts_BGOSphere_1e6_goldcascade.root";
   std::string filemx = "bubble_Nevts_BGOSphere_1e6_5MeVxray.root";
   
   /*********************************/
   /*           Analysis            */
   /*********************************/

   const int nbins=200;

   TFile* fmu = new TFile(TString(filemu));
   TFile* fx = new TFile(TString(filex));
   TFile* fmx = new TFile(TString(filemx));

   TH1F *hmu = new TH1F("hmu","Edep",nbins,0.01,63.5);
   TH1F *hx = new TH1F("hx","Edep",nbins,9.2,10.4);
   TH1F *hmx = new TH1F("hmx","Edep",nbins,0.01,10);

   TTree *tmu = (TTree*)fmu->Get("Detector/BGOdet");
   TTree *tx = (TTree*)fx->Get("Detector/BGOdet");
   TTree *tmx = (TTree*)fmx->Get("Detector/BGOdet");

   tmu->Draw("Edep>>hmu","","");
   tx->Draw("Edep>>hx","","");
   tmx->Draw("Edep>>hmx","","");

   hmu->SetLineColor(kBlack);
   hx->SetLineColor(kRed);
   hmx->SetLineColor(kGreen-3);

   
   /***********************************/
   /*            Plotting             */
   /***********************************/

   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(2,3);
   c->cd(1);
   hmu->SetTitle("Mu-decay: spherical 3000mm BGO");
   hmu->GetXaxis()->SetTitle("Edep [MeV]");
   hmu->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu->GetYaxis()->SetTitleOffset(2.0);
   hmu->Draw();
  
   c->cd(3);
   hmx->SetTitle("5-MeV X-ray: spherical 3000mm BGO");
   hmx->GetXaxis()->SetTitle("Edep [MeV]");
   hmx->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmx->GetYaxis()->SetTitleOffset(2.0);
   hmx->Draw();
  
   c->cd(5);
   hx->SetTitle("X-cascade Au: spherical 3000mm BGO");
   hx->GetXaxis()->SetTitle("Edep [MeV]");
   hx->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx->GetYaxis()->SetTitleOffset(2.0);
   hx->Draw();

   c->cd(2);
   hmu->SetTitle("Mu-decay: spherical 3000mm BGO");
   hmu->GetXaxis()->SetTitle("Edep [MeV]");
   hmu->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu->GetYaxis()->SetTitleOffset(2.0);
   hmu->Draw();
  
   c->cd(4);
   hmx->SetTitle("5-MeV X-ray: spherical 3000mm BGO");
   hmx->GetXaxis()->SetTitle("Edep [MeV]");
   hmx->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmx->GetYaxis()->SetTitleOffset(2.0);
   hmx->Draw();
  
   c->cd(6);
   hx->SetTitle("X-cascade Au: spherical 3000mm BGO");
   hx->GetXaxis()->SetTitle("Edep [MeV]");
   hx->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx->GetYaxis()->SetTitleOffset(2.0);
   hx->Draw();

   c->SaveAs("BubbleTest1.pdf");
   c->SaveAs("BubbleTest1.png");
   c->SaveAs("BubbleTest1.C");   

}

int main() {
   bubble1();
   return 0;
}

