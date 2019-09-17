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

void plothist(){

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

   const int nbins = 200;
   double norm = 1e5;
   double int20mu[200], int25mu[200], int30mu[200], int35mu[200], int40mu[200];
   double int20el[200], int25el[200], int30el[200], int35el[200], int40el[200];
   double mubins[200], elbins[200];

   // TFiles 
   // E = 0 MeV ; mu-decay 
   TFile* f20mu = new TFile("../../simdata/finead/Cu_20mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f25mu = new TFile("../../simdata/finead/Cu_25mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f30mu = new TFile("../../simdata/finead/Cu_30mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f35mu = new TFile("../../simdata/finead/Cu_35mm_P_0_0MeV_BGO_1e5mudecay.root");
   TFile* f40mu = new TFile("../../simdata/finead/Cu_40mm_P_0_0MeV_BGO_1e5mudecay.root");
   
   // E = 15 MeV ; electrons
   TFile* f20el = new TFile("../../simdata/finead/Cu_20mm_P_15_50MeV_BGO_1e5electron.root");
   TFile* f25el = new TFile("../../simdata/finead/Cu_25mm_P_15_50MeV_BGO_1e5electron.root");
   TFile* f30el = new TFile("../../simdata/finead/Cu_30mm_P_15_50MeV_BGO_1e5electron.root");
   TFile* f35el = new TFile("../../simdata/finead/Cu_35mm_P_15_50MeV_BGO_1e5electron.root");
   TFile* f40el = new TFile("../../simdata/finead/Cu_40mm_P_15_50MeV_BGO_1e5electron.root");


   // Histograms
   // Mu-decay (E=0 MeV)
   TH1F *h20mu = new TH1F("h20mu","Edep",nbins,0,40);
   TH1F *h25mu = new TH1F("h25mu","Edep",nbins,0,40);
   TH1F *h30mu = new TH1F("h30mu","Edep",nbins,0,40);
   TH1F *h35mu = new TH1F("h35mu","Edep",nbins,0,40);
   TH1F *h40mu = new TH1F("h40mu","Edep",nbins,0,40);

   // Electrons (E=15 MeV)
   TH1F *h20el = new TH1F("h20el","Edep",nbins,0,14);
   TH1F *h25el = new TH1F("h25el","Edep",nbins,0,14);
   TH1F *h30el = new TH1F("h30el","Edep",nbins,0,14);
   TH1F *h35el = new TH1F("h35el","Edep",nbins,0,14);
   TH1F *h40el = new TH1F("h40el","Edep",nbins,0,14);

   
   // TTrees
   // Mu-decay (E=0 MeV)
   TTree *t20mu = (TTree*)f20mu->Get("Detector/BGOD1");
   TTree *t25mu = (TTree*)f25mu->Get("Detector/BGOD1");
   TTree *t30mu = (TTree*)f30mu->Get("Detector/BGOD1");
   TTree *t35mu = (TTree*)f35mu->Get("Detector/BGOD1");
   TTree *t40mu = (TTree*)f40mu->Get("Detector/BGOD1");
   
   // Electrons (E=15 MeV)
   TTree *t20el = (TTree*)f20el->Get("Detector/BGOD1");
   TTree *t25el = (TTree*)f25el->Get("Detector/BGOD1");
   TTree *t30el = (TTree*)f30el->Get("Detector/BGOD1");
   TTree *t35el = (TTree*)f35el->Get("Detector/BGOD1");
   TTree *t40el = (TTree*)f40el->Get("Detector/BGOD1");


   // Drawings
   // Mu-decay (E=0 MeV)
   t20mu->Draw("Edep>>h20mu","","");
   t25mu->Draw("Edep>>h25mu","","");
   t30mu->Draw("Edep>>h30mu","","");
   t35mu->Draw("Edep>>h35mu","","");
   t40mu->Draw("Edep>>h40mu","","");
   
   // Electrons (E=15 MeV)
   t20el->Draw("Edep>>h20el","","");
   t25el->Draw("Edep>>h25el","","");
   t30el->Draw("Edep>>h30el","","");
   t35el->Draw("Edep>>h35el","","");
   t40el->Draw("Edep>>h40el","","");


   // Normalisation
   // Mu-decay (E=0 MeV)
   for (Int_t i=0; i < nbins; i++) {mubins[i] = h20mu->GetXaxis()->GetBinCenter(i);}   
   for (Int_t i=1; i <= nbins; i++) {int20mu[i-1] = (h20mu->Integral(0,i,""))/(h20mu->Integral(""));}   
   for (Int_t i=1; i <= nbins; i++) {int25mu[i-1] = (h25mu->Integral(0,i,""))/(h25mu->Integral(""));}   
   for (Int_t i=1; i <= nbins; i++) {int30mu[i-1] = (h30mu->Integral(0,i,""))/(h30mu->Integral(""));}
   for (Int_t i=1; i <= nbins; i++) {int35mu[i-1] = (h35mu->Integral(0,i,""))/(h35mu->Integral(""));}
   for (Int_t i=1; i <= nbins; i++) {int40mu[i-1] = (h40mu->Integral(0,i,""))/(h40mu->Integral(""));}
   
   // Electrons (E=15 MeV)
   for (Int_t i=0; i < nbins; i++) {elbins[i] = h20el->GetXaxis()->GetBinCenter(i);}   
   for (Int_t i=1; i <= nbins; i++) {int20el[i-1] = (h20el->Integral(0,i,""))/(h20el->Integral(""));}
   for (Int_t i=1; i <= nbins; i++) {int25el[i-1] = (h25el->Integral(0,i,""))/(h25el->Integral(""));} 
   for (Int_t i=1; i <= nbins; i++) {int30el[i-1] = (h30el->Integral(0,i,""))/(h30el->Integral(""));}
   for (Int_t i=1; i <= nbins; i++) {int35el[i-1] = (h35el->Integral(0,i,""))/(h35el->Integral(""));}
   for (Int_t i=1; i <= nbins; i++) {int40el[i-1] = (h40el->Integral(0,i,""))/(h40el->Integral(""));}

   // Colours
   // Mu-decay (E=0 MeV)
   h20mu->SetLineColor(kRed);
   h25mu->SetLineColor(kMagenta-8);
   h30mu->SetLineColor(kAzure+10);
   h35mu->SetLineColor(kBlue);
   h40mu->SetLineColor(kOrange+1);
   
   // Electrons (E=15 MeV)
   h20el->SetLineColor(kYellow-7);
   h25el->SetLineColor(kCyan+1);
   h30el->SetLineColor(kBlue-8);
   h35el->SetLineColor(kMagenta-1);
   h40el->SetLineColor(kRed-9);



   //-------------------------------------------------------------------
   //                          Plotting 
   //-------------------------------------------------------------------


   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(2,2);
   c->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr20mu = new TGraph(nbins,mubins,int20mu);
   gr20mu->SetTitle("");
   gr20mu->GetXaxis()->SetTitle("E [MeV]");
   gr20mu->GetXaxis()->SetRangeUser(0,40);
   gr20mu->GetXaxis()->SetNdivisions(-304);
   TGaxis::SetMaxDigits(2);
   gr20mu->GetYaxis()->SetMoreLogLabels(1);
   gr20mu->GetYaxis()->SetTitle("# of counts [norm.]");
   gr20mu->GetYaxis()->SetTitleOffset(2.1);
   gr20mu->SetLineColor(kRed);
   gr20mu->SetLineWidth(3);
   gr20mu->Draw("ALP");
   TGraph *gr25mu = new TGraph(nbins,mubins,int25mu);
   gr25mu->SetLineColor(kMagenta-8);
   gr25mu->SetLineWidth(3);
   gr25mu->Draw("LP");
   TGraph *gr30mu = new TGraph(nbins,mubins,int30mu);
   gr30mu->SetLineColor(kAzure+10);
   gr30mu->SetLineWidth(3);
   gr30mu->Draw("LP");
   TGraph *gr35mu = new TGraph(nbins,mubins,int35mu);
   gr35mu->SetLineColor(kBlue);
   gr35mu->SetLineWidth(3);
   gr35mu->Draw("LP");
   TGraph *gr40mu = new TGraph(nbins,mubins,int40mu);
   gr40mu->SetLineColor(kOrange+1);
   gr40mu->SetLineWidth(3);
   gr40mu->Draw("LP");
   mulegend = new TLegend(0.55,0.2,0.89,0.35);
   mulegend->AddEntry(gr20mu,"Mu-decay (E=0 MeV), w_{Cu} = 20 mm","l");
   mulegend->AddEntry(gr25mu,"Mu-decay (E=0 MeV), w_{Cu} = 25 mm","l");
   mulegend->AddEntry(gr30mu,"Mu-decay (E=0 MeV), w_{Cu} = 30 mm","l");
   mulegend->AddEntry(gr35mu,"Mu-decay (E=0 MeV), w_{Cu} = 35 mm","l");
   mulegend->AddEntry(gr40mu,"Mu-decay (E=0 MeV), w_{Cu} = 40 mm","l");
   mulegend->Draw();
   
   c->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr20el = new TGraph(nbins,elbins,int20el);
   gr20el->SetTitle("");
   gr20el->GetXaxis()->SetTitle("E [MeV]");
   gr20el->GetXaxis()->SetRangeUser(0,40);
   gr20el->GetXaxis()->SetNdivisions(-304);
   TGaxis::SetMaxDigits(2);
   gr20el->GetYaxis()->SetMoreLogLabels(1);
   gr20el->GetYaxis()->SetTitle("# of counts [norm.]");
   gr20el->GetYaxis()->SetTitleOffset(2.1);
   gr20el->SetLineColor(kYellow-7);
   gr20el->SetLineWidth(3);
   gr20el->Draw("ALP");
   TGraph *gr25el = new TGraph(nbins,elbins,int25el);
   gr25el->SetTitle("");
   gr25el->SetLineColor(kCyan+1);
   gr25el->SetLineWidth(3);
   gr25el->Draw("LP");
   TGraph *gr30el = new TGraph(nbins,elbins,int30el);
   gr30el->SetLineColor(kBlue-8);
   gr30el->SetLineWidth(3);
   gr30el->Draw("LP");
   TGraph *gr35el = new TGraph(nbins,elbins,int35el);
   gr35el->SetLineColor(kMagenta-1);
   gr35el->SetLineWidth(3);
   gr35el->Draw("LP");
   TGraph *gr40el = new TGraph(nbins,elbins,int40el);
   gr40el->SetLineColor(kRed-9);
   gr40el->SetLineWidth(3);
   gr40el->Draw("LP");
   ellegend = new TLegend(0.55,0.2,0.89,0.35);
   ellegend->AddEntry(gr20el,"Electrons (E=15 MeV), w_{Cu} = 20 mm","l");
   ellegend->AddEntry(gr25el,"Electrons (E=15 MeV), w_{Cu} = 25 mm","l");
   ellegend->AddEntry(gr30el,"Electrons (E=15 MeV), w_{Cu} = 30 mm","l");
   ellegend->AddEntry(gr35el,"Electrons (E=15 MeV), w_{Cu} = 35 mm","l");
   ellegend->AddEntry(gr40el,"Electrons (E=15 MeV), w_{Cu} = 40 mm","l");
   ellegend->Draw();
   
   c->cd(3);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h20mu->SetTitle("");
   h20mu->GetXaxis()->SetTitle("E [MeV]");
   h20mu->GetYaxis()->SetTitle("# of counts");
   h20mu->GetYaxis()->SetTitleOffset(1.0);
   h20mu->Draw();
   h25mu->Draw("same");  
   h30mu->Draw("same");
   h35mu->Draw("same");
   h40mu->Draw("same");  
   auto legendmu = new TLegend(0.55,0.7,0.89,0.85);
   legendmu->AddEntry(h20mu,"Mu-decay (E=0 MeV), w_{Cu}=20 mm","l");
   legendmu->AddEntry(h25mu,"Mu-decay (E=0 MeV), w_{Cu}=25 mm","l");
   legendmu->AddEntry(h30mu,"Mu-decay (E=0 MeV), w_{Cu}=30 mm","l");
   legendmu->AddEntry(h35mu,"Mu-decay (E=0 MeV), w_{Cu}=35 mm","l");
   legendmu->AddEntry(h40mu,"Mu-decay (E=0 MeV), w_{Cu}=40 mm","l");
   legendmu->Draw();
   
   c->cd(4);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   h20el->SetTitle("");
   h20el->GetXaxis()->SetTitle("E [MeV]");
   h20el->GetYaxis()->SetTitle("# of counts");
   h20el->GetYaxis()->SetTitleOffset(1.0);
   h20el->Draw();
   h25el->Draw("same");  
   h30el->Draw("same");
   h35el->Draw("same");
   h40el->Draw("same");  
   auto legendel = new TLegend(0.55,0.7,0.89,0.85);
   legendel->AddEntry(h20el,"Electrons (E=15 MeV), w_{Cu}=20 mm","l");
   legendel->AddEntry(h25el,"Electrons (E=15 MeV), w_{Cu}=25 mm","l");
   legendel->AddEntry(h30el,"Electrons (E=15 MeV), w_{Cu}=30 mm","l");
   legendel->AddEntry(h35el,"Electrons (E=15 MeV), w_{Cu}=35 mm","l");
   legendel->AddEntry(h40el,"Electrons (E=15 MeV), w_{Cu}=40 mm","l");
   legendel->Draw();
   
//   c->SaveAs("w_comp_mu_vs_el.pdf");
//   c->SaveAs("w_comp_mu_vs_el.png");
//   c->SaveAs("w_comp_mu_vs_el.C");
   
} 
 
 int main() {
   plothist();
   return 0;
}  
