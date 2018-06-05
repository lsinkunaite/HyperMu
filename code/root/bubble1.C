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
   std::string filemu = "bubble_Nevts_BGOSphere_1e6mudecay.root";
   std::string filex = "bubble_Nevts_BGOSphere_1e6goldcascade.root";
   
   /*********************************/
   /*           Analysis            */
   /*********************************/

   const int nbins=200;

   TFile* fmu = new TFile(TString(filemu));
   TFile* fx = new TFile(TString(filex));

   TH1F *hmu = new TH1F("hmu","Edep",nbins,0.01,50);
   TH1F *hx = new TH1F("hx","Edep",nbins,0.01,10);

   TTree *tmu = (TTree*)fmu->Get("Detector/BGOdet");
   TTree *tx = (TTree*)fx->Get("Detector/BGOdet");

   tmu->Draw("Edep>>hmu","","");
   tx->Draw("Edep>>hx","","");

   hmu->SetLineColor(kBlack);
   hx->SetLineColor(kRed);

   
   /***********************************/
   /*            Plotting             */
   /***********************************/

   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(2,2);
   c->cd(1);
   hmu->SetTitle("Mu-decay: spherical 3000mm BGO");
   hmu->GetXaxis()->SetTitle("Edep [MeV]");
   hmu->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu->GetYaxis()->SetTitleOffset(2.0);
   hmu->Draw();
  
   c->cd(3);
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

