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

void bubble4RED(){

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
   // With {250,500,750}-mm SciD3
   std::string filemu250 = "../../simdata/bubble4/bubble_0x5mm_250mm_SciD_Nevts_SciSphere_0mm_Al_1e6mudecay.root";
   std::string filemu500 = "../../simdata/bubble4/bubble_0x5mm_500mm_SciD_Nevts_SciSphere_0mm_Al_1e6mudecay.root";
   std::string filemu750 = "../../simdata/bubble4/bubble_0x5mm_750mm_SciD_Nevts_SciSphere_0mm_Al_1e6mudecay.root";
   std::string filex250 = "../../simdata/bubble4/bubble_0x5mm_250mm_SciD_Nevts_SciSphere_0mm_Al_1e6goldcascade.root";
   std::string filex500 = "../../simdata/bubble4/bubble_0x5mm_500mm_SciD_Nevts_SciSphere_0mm_Al_1e6goldcascade.root";
   std::string filex750 = "../../simdata/bubble4/bubble_0x5mm_750mm_SciD_Nevts_SciSphere_0mm_Al_1e6goldcascade.root";
   

   /*********************************/
   /*           Analysis            */
   /*********************************/

   const int nbins = 150;
  
   // TFiles
   TFile* fmu250 = new TFile(TString(filemu250));
   TFile* fmu500 = new TFile(TString(filemu500));
   TFile* fmu750 = new TFile(TString(filemu750));
   TFile* fx250 = new TFile(TString(filex250));
   TFile* fx500 = new TFile(TString(filex500));
   TFile* fx750 = new TFile(TString(filex750));
   
   // Histograms
   // 3-mm Al
   TH1F *hmu250SciDet3 = new TH1F("hmu250SciDet3","Edep",nbins,0,55);
   TH1F *hmu500SciDet3 = new TH1F("hmu500SciDet3","Edep",nbins,0,55);
   TH1F *hmu750SciDet3 = new TH1F("hmu750SciDet3","Edep",nbins,0,55);
   TH1F *hx250SciDet3 = new TH1F("hx250SciDet3","Edep",nbins,0,55);
   TH1F *hx500SciDet3 = new TH1F("hx500SciDet3","Edep",nbins,0,55);
   TH1F *hx750SciDet3 = new TH1F("hx750SciDet3","Edep",nbins,0,55);
   // 3-mm Al [copies]
   TH1F *hmu250SciDet3n = new TH1F("hmu250SciDet3n","Edep",nbins,0,65);
   TH1F *hmu500SciDet3n = new TH1F("hmu500SciDet3n","Edep",nbins,0,65);
   TH1F *hmu750SciDet3n = new TH1F("hmu750SciDet3n","Edep",nbins,0,65);
   TH1F *hx250SciDet3n = new TH1F("hx250SciDet3n","Edep",nbins,0,12.5);
   TH1F *hx500SciDet3n = new TH1F("hx500SciDet3n","Edep",nbins,0,12.5);
   TH1F *hx750SciDet3n = new TH1F("hx750SciDet3n","Edep",nbins,0,12.5);
     
   // TTrees
   // 3-mm Al
   TTree *tmu250SciDet3 = (TTree*)fmu250->Get("Detector/SciDet3");
   TTree *tmu500SciDet3 = (TTree*)fmu500->Get("Detector/SciDet3");
   TTree *tmu750SciDet3 = (TTree*)fmu750->Get("Detector/SciDet3");
   TTree *tx250SciDet3 = (TTree*)fx250->Get("Detector/SciDet3");
   TTree *tx500SciDet3 = (TTree*)fx500->Get("Detector/SciDet3");
   TTree *tx750SciDet3 = (TTree*)fx750->Get("Detector/SciDet3");
   
   
   // Drawings
   // 3-mm Al  
   tmu250SciDet3->Draw("Edep>>hmu250SciDet3","","");
   tmu500SciDet3->Draw("Edep>>hmu500SciDet3","","");
   tmu750SciDet3->Draw("Edep>>hmu750SciDet3","","");
   tx250SciDet3->Draw("Edep>>hx250SciDet3","","");
   tx500SciDet3->Draw("Edep>>hx500SciDet3","","");
   tx750SciDet3->Draw("Edep>>hx750SciDet3","","");
   // 3-mm Al [copies]
   tmu250SciDet3->Draw("Edep>>hmu250SciDet3n","","");
   tmu500SciDet3->Draw("Edep>>hmu500SciDet3n","","");
   tmu750SciDet3->Draw("Edep>>hmu750SciDet3n","","");
   tx250SciDet3->Draw("Edep>>hx250SciDet3n","","");
   tx500SciDet3->Draw("Edep>>hx500SciDet3n","","");
   tx750SciDet3->Draw("Edep>>hx750SciDet3n","","");
   
  
   // Colours 
   // 3-mm Al
   hmu250SciDet3->SetLineColor(kGreen-2);
   hmu500SciDet3->SetLineColor(kGreen-2);
   hmu750SciDet3->SetLineColor(kGreen-2);
   hx250SciDet3->SetLineColor(kBlack);
   hx500SciDet3->SetLineColor(kBlack);
   hx750SciDet3->SetLineColor(kBlack);
   // 3-mm Al [copies]
   hmu250SciDet3n->SetLineColor(kBlack);
   hmu500SciDet3n->SetLineColor(kRed);
   hmu750SciDet3n->SetLineColor(kGreen-2);
   hx250SciDet3n->SetLineColor(kBlack);
   hx500SciDet3n->SetLineColor(kRed);
   hx750SciDet3n->SetLineColor(kGreen-2);
   
   /********************************/
   /*           Plotting           */
   /********************************/

   // Mu-decay: 3-mm/ 6-mm Al 250-mm/ 500-mm/ 750-mm SciD3
   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(3,2);
   c->cd(1);
   gPad->SetLogy();
   hx250SciDet3->SetTitle("#mu-decay vs X-ray cascade: 250-mm SciD_{3}");
   hx250SciDet3->GetXaxis()->SetTitle("Edep [MeV]");
   hx250SciDet3->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx250SciDet3->GetYaxis()->SetTitleOffset(2.0);
   hx250SciDet3->Draw();
   c->Update();
   TPaveStats *stx250SciDet3 = (TPaveStats*)hx250SciDet3->GetListOfFunctions()->FindObject("stats");
   stx250SciDet3->SetY1NDC(0.63); stx250SciDet3->SetY2NDC(0.78);
   stx250SciDet3->SetTextColor(kBlack);
   hmu250SciDet3->Draw("sames");
   c->Update();
   TPaveStats *stmu250SciDet3 = (TPaveStats*)hmu250SciDet3->GetListOfFunctions()->FindObject("stats");
   stmu250SciDet3->SetTextColor(kGreen-2);
   stmu250SciDet3->Draw();
   
   c->cd(2);
   gPad->SetLogy();
   hx500SciDet3->SetTitle("#mu-decay vs X-ray cascade: 500-mm SciD_{3}");
   hx500SciDet3->GetXaxis()->SetTitle("Edep [MeV]");
   hx500SciDet3->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx500SciDet3->GetYaxis()->SetTitleOffset(2.0);
   hx500SciDet3->Draw();
   c->Update();
   TPaveStats *stx500SciDet3 = (TPaveStats*)hx500SciDet3->GetListOfFunctions()->FindObject("stats");
   stx500SciDet3->SetY1NDC(0.63); stx500SciDet3->SetY2NDC(0.78);
   stx500SciDet3->SetTextColor(kBlack);
   hmu500SciDet3->Draw("sames");
   c->Update();
   TPaveStats *stmu500SciDet3 = (TPaveStats*)hmu500SciDet3->GetListOfFunctions()->FindObject("stats");
   stmu500SciDet3->SetTextColor(kGreen-2);
   stmu500SciDet3->Draw();

   c->cd(3);
   gPad->SetLogy();
   hx750SciDet3->SetTitle("#mu-decay vs X-ray cascade: 750-mm SciD_{3}");
   hx750SciDet3->GetXaxis()->SetTitle("Edep [MeV]");
   hx750SciDet3->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx750SciDet3->GetYaxis()->SetTitleOffset(2.0);
   hx750SciDet3->Draw();
   c->Update();
   TPaveStats *stx750SciDet3 = (TPaveStats*)hx750SciDet3->GetListOfFunctions()->FindObject("stats");
   stx750SciDet3->SetY1NDC(0.63); stx750SciDet3->SetY2NDC(0.78);
   stx750SciDet3->SetTextColor(kBlack);
   hmu750SciDet3->Draw("sames");
   c->Update();
   TPaveStats *stmu750SciDet3 = (TPaveStats*)hmu750SciDet3->GetListOfFunctions()->FindObject("stats");
   stmu750SciDet3->SetTextColor(kGreen-2);
   stmu750SciDet3->Draw();

   c->cd(4);
   gPad->SetLogy();
   hmu250SciDet3n->SetTitle("#mu-decay: {250,500,750}-mm SciD_{3}");
   hmu250SciDet3n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu250SciDet3n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu250SciDet3n->GetYaxis()->SetTitleOffset(2.0);
   hmu250SciDet3n->Draw();
   c->Update();
   TPaveStats *stmu250SciDet3n = (TPaveStats*)hmu250SciDet3n->GetListOfFunctions()->FindObject("stats");
   stmu250SciDet3n->SetY1NDC(0.48); stmu250SciDet3n->SetY2NDC(0.63);
   stmu250SciDet3n->SetTextColor(kBlack);
   hmu500SciDet3n->Draw("sames");
   c->Update();
   TPaveStats *stmu500SciDet3n = (TPaveStats*)hmu500SciDet3n->GetListOfFunctions()->FindObject("stats");
   stmu500SciDet3n->SetY1NDC(0.63); stmu500SciDet3n->SetY2NDC(0.78);
   stmu500SciDet3n->SetTextColor(kRed);
   hmu750SciDet3n->Draw("sames");
   c->Update();
   TPaveStats *stmu750SciDet3n = (TPaveStats*)hmu750SciDet3n->GetListOfFunctions()->FindObject("stats");
   stmu750SciDet3n->SetTextColor(kGreen-2);
   stmu750SciDet3n->Draw();

   c->cd(5);
   gPad->SetLogy();
   hx750SciDet3n->SetTitle("X-ray cascade: {250,500,750}-mm SciD_{3}");
   hx750SciDet3n->GetXaxis()->SetTitle("Edep [MeV]");
   hx750SciDet3n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx750SciDet3n->GetYaxis()->SetTitleOffset(2.0);
   hx750SciDet3n->Draw();
   c->Update();
   TPaveStats *stx750SciDet3n = (TPaveStats*)hx750SciDet3n->GetListOfFunctions()->FindObject("stats");
   stx750SciDet3n->SetTextColor(kGreen-2);
   hx500SciDet3n->Draw("sames");
   c->Update();
   TPaveStats *stx500SciDet3n = (TPaveStats*)hx500SciDet3n->GetListOfFunctions()->FindObject("stats");
   stx500SciDet3n->SetY1NDC(0.63); stx500SciDet3n->SetY2NDC(0.78);
   stx500SciDet3n->SetTextColor(kRed);
   hx250SciDet3n->Draw("sames");
   c->Update();
   TPaveStats *stx250SciDet3n = (TPaveStats*)hx250SciDet3n->GetListOfFunctions()->FindObject("stats");
   stx250SciDet3n->SetY1NDC(0.48); stx250SciDet3n->SetY2NDC(0.63);
   stx250SciDet3n->SetTextColor(kBlack);
   stx250SciDet3n->Draw();
   
   c->SaveAs("BubblePlot_RED_0mm_Al_SciD3.pdf");
   c->SaveAs("BubblePlot_RED_0mm_Al_SciD3.png");
   c->SaveAs("BubblePlot_RED_0mm_Al_SciD3.C");   




}


int main() {
   bubble4RED();
   return 0;
}
