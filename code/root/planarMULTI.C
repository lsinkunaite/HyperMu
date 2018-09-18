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
//#include "TVector.h"

void planarMULTI(){

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
   std::string filemu = "../../simdata/planar/planar_MULTI_2x5mm_500mm_SciD_1mm_Al_5mm_Al_1e6mudecay.root";
   std::string filex = "../../simdata/planar/planar_MULTI_2x5mm_500mm_SciD_1mm_Al_5mm_Al_1e6goldcascade.root";
   
   const int nbins = 150;


   // TFiles 
   TFile* fmu = new TFile(TString(filemu));
   TFile* fx = new TFile(TString(filex));

   // Histograms
   TH1F *hmuSciDet1D = new TH1F("hmuSciDet1D","Edep",3*nbins+1,-0.05,45);
   TH1F *hmuSciDet2D = new TH1F("hmuSciDet2D","Edep",3*nbins+1,-0.05,45);
   TH1F *hmuSciDet3D = new TH1F("hmuSciDet3D","Edep",3*nbins+1,-0.05,45);
   TH1F *hmuSciDet1U = new TH1F("hmuSciDet1U","Edep",3*nbins+1,-0.05,45);
   TH1F *hmuSciDet2U = new TH1F("hmuSciDet2U","Edep",3*nbins+1,-0.05,45);
   TH1F *hmuSciDet3U = new TH1F("hmuSciDet3U","Edep",3*nbins+1,-0.05,45);
   TH1F *hxSciDet1D = new TH1F("hxSciDet1D","Edep",nbins+1,-0.05,15);
   TH1F *hxSciDet2D = new TH1F("hxSciDet2D","Edep",nbins+1,-0.05,15);
   TH1F *hxSciDet3D = new TH1F("hxSciDet3D","Edep",nbins+1,-0.05,15);
   TH1F *hxSciDet1U = new TH1F("hxSciDet1U","Edep",nbins+1,-0.05,15);
   TH1F *hxSciDet2U = new TH1F("hxSciDet2U","Edep",nbins+1,-0.05,15);
   TH1F *hxSciDet3U = new TH1F("hxSciDet3U","Edep",nbins+1,-0.05,15);


   // TTrees
   TTree *tmuSciDet1D = (TTree*)fmu->Get("Detector/SciDet1D");
   TTree *tmuSciDet2D = (TTree*)fmu->Get("Detector/SciDet2D");
   TTree *tmuSciDet3D = (TTree*)fmu->Get("Detector/SciDet3D");
   TTree *tmuSciDet1U = (TTree*)fmu->Get("Detector/SciDet1U");
   TTree *tmuSciDet2U = (TTree*)fmu->Get("Detector/SciDet2U");
   TTree *tmuSciDet3U = (TTree*)fmu->Get("Detector/SciDet3U");
   TTree *txSciDet1D = (TTree*)fx->Get("Detector/SciDet1D");
   TTree *txSciDet2D = (TTree*)fx->Get("Detector/SciDet2D");
   TTree *txSciDet3D = (TTree*)fx->Get("Detector/SciDet3D");
   TTree *txSciDet1U = (TTree*)fx->Get("Detector/SciDet1U");
   TTree *txSciDet2U = (TTree*)fx->Get("Detector/SciDet2U");
   TTree *txSciDet3U = (TTree*)fx->Get("Detector/SciDet3U");


   // Drawings
   tmuSciDet1D->Draw("Edep>>hmuSciDet1D","","");
   tmuSciDet2D->Draw("Edep>>hmuSciDet2D","","");
   tmuSciDet3D->Draw("Edep>>hmuSciDet3D","","");
   tmuSciDet1U->Draw("Edep>>hmuSciDet1U","","");
   tmuSciDet2U->Draw("Edep>>hmuSciDet2U","","");
   tmuSciDet3U->Draw("Edep>>hmuSciDet3U","","");
   txSciDet1D->Draw("Edep>>hxSciDet1D","","");
   txSciDet2D->Draw("Edep>>hxSciDet2D","","");
   txSciDet3D->Draw("Edep>>hxSciDet3D","","");
   txSciDet1U->Draw("Edep>>hxSciDet1U","","");
   txSciDet2U->Draw("Edep>>hxSciDet2U","","");
   txSciDet3U->Draw("Edep>>hxSciDet3U","","");

   // Colours 
   hmuSciDet1D->SetLineColor(kBlack);
   hmuSciDet2D->SetLineColor(kBlack);
   hmuSciDet3D->SetLineColor(kBlack);
   hmuSciDet1U->SetLineColor(kBlack);
   hmuSciDet2U->SetLineColor(kBlack);
   hmuSciDet3U->SetLineColor(kBlack);
   hxSciDet1D->SetLineColor(kGreen-2);
   hxSciDet2D->SetLineColor(kGreen-2);
   hxSciDet3D->SetLineColor(kGreen-2);
   hxSciDet1U->SetLineColor(kGreen-2);
   hxSciDet2U->SetLineColor(kGreen-2);
   hxSciDet3U->SetLineColor(kGreen-2);
   

   
   /********************************/
   /*           Plotting           */
   /********************************/

   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(3,2);
   c->cd(1);
   gPad->SetLogy();
   hmuSciDet1D->SetTitle("Planar MULTI D-stream [600mm x 600mm]: #mu-decay vs X-ray cascade: 5-mm SciD_{1}");
   hmuSciDet1D->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDet1D->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDet1D->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDet1D->Draw();
   c->Update();
   TPaveStats *stmuSciDet1D = (TPaveStats*)hmuSciDet1D->GetListOfFunctions()->FindObject("stats");
   stmuSciDet1D->SetY1NDC(0.63); stmuSciDet1D->SetY2NDC(0.78);
   hxSciDet1D->Draw("sames");
   c->Update();
   TPaveStats *stxSciDet1D = (TPaveStats*)hxSciDet1D->GetListOfFunctions()->FindObject("stats");
   stxSciDet1D->SetTextColor(kGreen-2);
   stxSciDet1D->Draw();

   c->cd(2);
   gPad->SetLogy();
   hmuSciDet2D->SetTitle("Planar MULTI D-stream [600mm x 600mm]: #mu-decay vs X-ray cascade: 5-mm SciD_{2}");
   hmuSciDet2D->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDet2D->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDet2D->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDet2D->Draw();
   c->Update();
   TPaveStats *stmuSciDet2D = (TPaveStats*)hmuSciDet2D->GetListOfFunctions()->FindObject("stats");
   stmuSciDet2D->SetY1NDC(0.63); stmuSciDet2D->SetY2NDC(0.78);
   hxSciDet2D->Draw("sames");
   c->Update();
   TPaveStats *stxSciDet2D = (TPaveStats*)hxSciDet2D->GetListOfFunctions()->FindObject("stats");
   stxSciDet2D->SetTextColor(kGreen-2);
   stxSciDet2D->Draw();

   c->cd(3);
   gPad->SetLogy();
   hmuSciDet3D->SetTitle("Planar MULTI D-stream [600mm x 600mm]: #mu-decay vs X-ray cascade: 500-mm SciD_{3}");
   hmuSciDet3D->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDet3D->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDet3D->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDet3D->Draw();
   c->Update();
   TPaveStats *stmuSciDet3D = (TPaveStats*)hmuSciDet3D->GetListOfFunctions()->FindObject("stats");
   stmuSciDet3D->SetY1NDC(0.63); stmuSciDet3D->SetY2NDC(0.78);
   hxSciDet3D->Draw("sames");
   c->Update();
   TPaveStats *stxSciDet3D = (TPaveStats*)hxSciDet3D->GetListOfFunctions()->FindObject("stats");
   stxSciDet3D->SetTextColor(kGreen-2);
   stxSciDet3D->Draw();

   c->cd(4);
   gPad->SetLogy();
   hmuSciDet1U->SetTitle("Planar MULTI U-stream [600mm x 600mm]: #mu-decay vs X-ray cascade: 5-mm SciD_{1}");
   hmuSciDet1U->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDet1U->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDet1U->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDet1U->Draw();
   c->Update();
   TPaveStats *stmuSciDet1U = (TPaveStats*)hmuSciDet1U->GetListOfFunctions()->FindObject("stats");
   stmuSciDet1U->SetY1NDC(0.63); stmuSciDet1U->SetY2NDC(0.78);
   hxSciDet1U->Draw("sames");
   c->Update();
   TPaveStats *stxSciDet1U = (TPaveStats*)hxSciDet1U->GetListOfFunctions()->FindObject("stats");
   stxSciDet1U->SetTextColor(kGreen-2);
   stxSciDet1U->Draw();

   c->cd(5);
   gPad->SetLogy();
   hmuSciDet2U->SetTitle("Planar MULTI U-stream [600mm x 600mm]: #mu-decay vs X-ray cascade: 5-mm SciD_{2}");
   hmuSciDet2U->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDet2U->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDet2U->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDet2U->Draw();
   c->Update();
   TPaveStats *stmuSciDet2U = (TPaveStats*)hmuSciDet2U->GetListOfFunctions()->FindObject("stats");
   stmuSciDet2U->SetY1NDC(0.63); stmuSciDet2U->SetY2NDC(0.78);
   hxSciDet2U->Draw("sames");
   c->Update();
   TPaveStats *stxSciDet2U = (TPaveStats*)hxSciDet2U->GetListOfFunctions()->FindObject("stats");
   stxSciDet2U->SetTextColor(kGreen-2);
   stxSciDet2U->Draw();

   c->cd(6);
   gPad->SetLogy();
   hmuSciDet3U->SetTitle("Planar MULTI U-stream [600mm x 600mm]: #mu-decay vs X-ray cascade: 500-mm SciD_{3}");
   hmuSciDet3U->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDet3U->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDet3U->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDet3U->Draw();
   c->Update();
   TPaveStats *stmuSciDet3U = (TPaveStats*)hmuSciDet3U->GetListOfFunctions()->FindObject("stats");
   stmuSciDet3U->SetY1NDC(0.63); stmuSciDet3U->SetY2NDC(0.78);
   hxSciDet3U->Draw("sames");
   c->Update();
   TPaveStats *stxSciDet3U = (TPaveStats*)hxSciDet3U->GetListOfFunctions()->FindObject("stats");
   stxSciDet3U->SetTextColor(kGreen-2);
   stxSciDet3U->Draw();

   c->SaveAs("../../simdata/planar/planarMULTI_Edep.pdf");
   c->SaveAs("../../simdata/planar/planarMULTI_Edep.png");
   c->SaveAs("../../simdata/planar/planarMULTI_Edep.C");


}


int main() {
   planarMULTI();
return 0;
}  
