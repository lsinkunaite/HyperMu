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

void Recover_MULTI(){

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
   std::string filemu = "../../simdata/recover/4mm_Al_4mm_SciD_4mm_Al_300mm_BGO_10mm_SciD_TB_1e5mudecay.root";
   std::string filex = "../../simdata/recover/4mm_Al_4mm_SciD_4mm_Al_300mm_BGO_10mm_SciD_TB_1e5goldcascade.root";

   std::string filemuSciD1 = "../../simdata/recover/4mm_Al_4mm_SciD_4mm_Al_300mm_BGO_10mm_SciD_TB_1e5mudecay_SciD1.txt";
   std::string filexSciD1 = "../../simdata/recover/4mm_Al_4mm_SciD_4mm_Al_300mm_BGO_10mm_SciD_TB_1e5goldcascade_SciD1.txt";
   std::string filemuSciD2 = "../../simdata/recover/4mm_Al_4mm_SciD_4mm_Al_300mm_BGO_10mm_SciD_TB_1e5mudecay_SciD2.txt";
   std::string filexSciD2 = "../../simdata/recover/4mm_Al_4mm_SciD_4mm_Al_300mm_BGO_10mm_SciD_TB_1e5goldcascade_SciD2.txt";
   std::string filemuSciD3 = "../../simdata/recover/4mm_Al_4mm_SciD_4mm_Al_300mm_BGO_10mm_SciD_TB_1e5mudecay_SciD3.txt";
   std::string filexSciD3 = "../../simdata/recover/4mm_Al_4mm_SciD_4mm_Al_300mm_BGO_10mm_SciD_TB_1e5goldcascade_SciD3.txt";
   std::string filemuBGOD1 = "../../simdata/recover/4mm_Al_4mm_SciD_4mm_Al_300mm_BGO_10mm_SciD_TB_1e5mudecay_BGOD1.txt";
   std::string filexBGOD1 = "../../simdata/recover/4mm_Al_4mm_SciD_4mm_Al_300mm_BGO_10mm_SciD_TB_1e5goldcascade_BGOD1.txt";

   
   const int nbins = 150;


   // TFiles 
   TFile* fmu = new TFile(TString(filemu));
   TFile* fx = new TFile(TString(filex));

   // Histograms
   TH1F *hmuSciD1 = new TH1F("hmuSciD1","Edep",4*nbins+1,-0.05,60);
   TH1F *hxSciD1 = new TH1F("hxSciD1","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciD2 = new TH1F("hmuSciD2","Edep",4*nbins+1,-0.05,60);
   TH1F *hxSciD2 = new TH1F("hxSciD2","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciD3 = new TH1F("hmuSciD3","Edep",4*nbins+1,-0.05,60);
   TH1F *hxSciD3 = new TH1F("hxSciD3","Edep",nbins+1,-0.05,15);
   TH1F *hmuBGOD1 = new TH1F("hmuBGOD1","Edep",4*nbins+1,-0.05,60);
   TH1F *hxBGOD1 = new TH1F("hxBGOD1","Edep",nbins+1,-0.05,15);
   
   TH1F *hmuSciD1Z = new TH1F("hmuSciD1Z","Edep",3*nbins+1,-0.05,5);
   TH1F *hxSciD1Z = new TH1F("hxSciD1Z","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciD2Z = new TH1F("hmuSciD2Z","Edep",3*nbins+1,-0.05,15);
   TH1F *hxSciD2Z = new TH1F("hxSciD2Z","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciD3Z = new TH1F("hmuSciD3Z","Edep",3*nbins+1,-0.05,15);
   TH1F *hxSciD3Z = new TH1F("hxSciD3Z","Edep",nbins+1,-0.05,15);
   TH1F *hmuBGOD1Z = new TH1F("hmuBGOD1Z","Edep",3*nbins+1,-0.05,15);
   TH1F *hxBGOD1Z = new TH1F("hxBGOD1Z","Edep",nbins+1,-0.05,15);


   // TTrees
   TTree *tmuSciD1 = (TTree*)fmu->Get("Detector/SciDet1");
   TTree *txSciD1 = (TTree*)fx->Get("Detector/SciDet1");
   TTree *tmuSciD2 = (TTree*)fmu->Get("Detector/SciDet2");
   TTree *txSciD2 = (TTree*)fx->Get("Detector/SciDet2");
   TTree *tmuSciD3 = (TTree*)fmu->Get("Detector/SciDet3");
   TTree *txSciD3 = (TTree*)fx->Get("Detector/SciDet3");
   TTree *tmuBGOD1 = (TTree*)fmu->Get("Detector/BGODet1");
   TTree *txBGOD1 = (TTree*)fx->Get("Detector/BGODet1");

   // Drawings
   tmuSciD1->Draw("Edep>>hmuSciD1","","");
   txSciD1->Draw("Edep>>hxSciD1","","");
   tmuSciD2->Draw("Edep>>hmuSciD2","","");
   txSciD2->Draw("Edep>>hxSciD2","","");
   tmuSciD3->Draw("Edep>>hmuSciD3","","");
   txSciD3->Draw("Edep>>hxSciD3","","");
   tmuBGOD1->Draw("Edep>>hmuBGOD1","","");
   txBGOD1->Draw("Edep>>hxBGOD1","","");   
   
   tmuSciD1->Draw("Edep>>hmuSciD1Z","","");
   txSciD1->Draw("Edep>>hxSciD1Z","","");
   tmuSciD2->Draw("Edep>>hmuSciD2Z","","");
   txSciD2->Draw("Edep>>hxSciD2Z","","");
   tmuSciD3->Draw("Edep>>hmuSciD3Z","","");
   txSciD3->Draw("Edep>>hxSciD3Z","","");
   tmuBGOD1->Draw("Edep>>hmuBGOD1Z","","");
   txBGOD1->Draw("Edep>>hxBGOD1Z","","");


   std::vector<std::string> mufiles;
   std::vector<std::string> Xfiles;

   // Mu-decay
   mufiles.push_back(filemuSciD1);
   mufiles.push_back(filemuSciD2);
   mufiles.push_back(filemuSciD3);
   mufiles.push_back(filemuBGOD1);
   // X-ray cascade
   Xfiles.push_back(filexSciD1);
   Xfiles.push_back(filexSciD2);
   Xfiles.push_back(filexSciD3);
   Xfiles.push_back(filexBGOD1);


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

   std::vector< std::vector<double> > TotEdepmuSD1(mufiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxSD1(Xfiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuSD2(mufiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxSD2(Xfiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuSD3(mufiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxSD3(Xfiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuBD1(mufiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxBD1(Xfiles.size()/4,std::vector<double>(nsamps));


   int binmuSD1, binxSD1, binmuSD2, binxSD2, binmuSD3, binxSD3, binmuBD1, binxBD1;
   double integralmuSD1, integralxSD1, integralmuSD2, integralxSD2, integralmuSD3, integralxSD3, integralmuBD1, integralxBD1;
   
   for (int m=0; m < nsamps; m++) {
	   
      Ethr = Ethrmu[m];

      // SciD1
      binmuSD1 = hmuSciD1->GetXaxis()->FindBin(Ethr);
      integralmuSD1 = hmuSciD1->Integral(0,binmuSD1,"");
      binxSD1 = hxSciD1->GetXaxis()->FindBin(Ethr);
      integralxSD1 = hxSciD1->Integral(0,binxSD1,"");
      // SciD2
      binmuSD2 = hmuSciD2->GetXaxis()->FindBin(Ethr);
      integralmuSD2 = hmuSciD2->Integral(0,binmuSD2,"");
      binxSD2 = hxSciD2->GetXaxis()->FindBin(Ethr);
      integralxSD2 = hxSciD2->Integral(0,binxSD2,"");
      // SciD3
      binmuSD3 = hmuSciD3->GetXaxis()->FindBin(Ethr);
      integralmuSD3 = hmuSciD3->Integral(0,binmuSD3,"");
      binxSD3 = hxSciD3->GetXaxis()->FindBin(Ethr);
      integralxSD3 = hxSciD3->Integral(0,binxSD3,"");
      // BGOD1
      binmuBD1 = hmuBGOD1->GetXaxis()->FindBin(Ethr);
      integralmuBD1 = hmuBGOD1->Integral(0,binmuBD1,"");
      binxBD1 = hxBGOD1->GetXaxis()->FindBin(Ethr);
      integralxBD1 = hxBGOD1->Integral(0,binxBD1,"");

      TotEdepmuSD1[0][m] = integralmuSD1;
      TotEdepxSD1[0][m] = integralxSD1;
      TotEdepmuSD2[0][m] = integralmuSD2;
      TotEdepxSD2[0][m] = integralxSD2;
      TotEdepmuSD3[0][m] = integralmuSD3;
      TotEdepxSD3[0][m] = integralxSD3;
      TotEdepmuBD1[0][m] = integralmuBD1;
      TotEdepxBD1[0][m] = integralxBD1;     
      
   }
   	 
   float EdepmuSciD1[nsamps] = {};
   float EdepxSciD1[nsamps] = {};
   float EdepmuSciD2[nsamps] = {};
   float EdepxSciD2[nsamps] = {};
   float EdepmuSciD3[nsamps] = {};
   float EdepxSciD3[nsamps] = {};
   float EdepmuBGOD1[nsamps] = {};
   float EdepxBGOD1[nsamps] = {};
   
   
   for (int i=0; i<nsamps; i++) {
      EdepmuSciD1[i] = TotEdepmuSD1[0][i]/TotEdepmuSD1[0][nsamps-1];
      EdepxSciD1[i] = TotEdepxSD1[0][i]/TotEdepxSD1[0][nsamps-1];
      EdepmuSciD2[i] = TotEdepmuSD2[0][i]/TotEdepmuSD2[0][nsamps-1];
      EdepxSciD2[i] = TotEdepxSD2[0][i]/TotEdepxSD2[0][nsamps-1];
      EdepmuSciD3[i] = TotEdepmuSD3[0][i]/TotEdepmuSD3[0][nsamps-1];
      EdepxSciD3[i] = TotEdepxSD3[0][i]/TotEdepxSD3[0][nsamps-1];
      EdepmuBGOD1[i] = TotEdepmuBD1[0][i]/TotEdepmuBD1[0][nsamps-1];
      EdepxBGOD1[i] = TotEdepxBD1[0][i]/TotEdepxBD1[0][nsamps-1];
   }


   // Colours
   hmuSciD1->SetLineColor(kBlack);
   hxSciD1->SetLineColor(kGreen-2);
   hmuSciD2->SetLineColor(kBlack);
   hxSciD2->SetLineColor(kGreen-2);
   hmuSciD3->SetLineColor(kBlack);
   hxSciD3->SetLineColor(kGreen-2);
   hmuBGOD1->SetLineColor(kBlack);
   hxBGOD1->SetLineColor(kGreen-2);

   hmuSciD1Z->SetLineColor(kBlack);
   hxSciD1Z->SetLineColor(kGreen-2);
   hmuSciD2Z->SetLineColor(kBlack);
   hxSciD2Z->SetLineColor(kGreen-2);
   hmuSciD3Z->SetLineColor(kBlack);
   hxSciD3Z->SetLineColor(kGreen-2);
   hmuBGOD1Z->SetLineColor(kBlack);
   hxBGOD1Z->SetLineColor(kGreen-2);

   
   /********************************/
   /*           Plotting           */
   /********************************/

   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(4,3);
   c->cd(1);
   gPad->SetLogy();
   hmuSciD1->SetTitle("2 x 4-mm Al, 4-mm SciD_{1}, 2 x 10-mm SciD_{2,3}, 300-mm BGO: #mu-decay vs X-ray cascade SciD_{1}");
   hmuSciD1->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciD1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciD1->GetYaxis()->SetTitleOffset(2.0);
   hmuSciD1->Draw();
   c->Update();
   TPaveStats *stmuSciD1 = (TPaveStats*)hmuSciD1->GetListOfFunctions()->FindObject("stats");
   stmuSciD1->SetY1NDC(0.63); stmuSciD1->SetY2NDC(0.78);
   hxSciD1->Draw("sames");
   c->Update();
   TPaveStats *stxSciD1 = (TPaveStats*)hxSciD1->GetListOfFunctions()->FindObject("stats");
   stxSciD1->SetTextColor(kGreen-2);
   stxSciD1->Draw();
 
   c->cd(2);
   gPad->SetLogy();
   hmuSciD2->SetTitle("2 x 4-mm Al, 4-mm SciD_{1}, 2 x 10-mm SciD_{2,3}, 300-mm BGO: #mu-decay vs X-ray cascade SciD_{2}");
   hmuSciD2->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciD2->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciD2->GetYaxis()->SetTitleOffset(2.0);
   hmuSciD2->Draw();
   c->Update();
   TPaveStats *stmuSciD2 = (TPaveStats*)hmuSciD2->GetListOfFunctions()->FindObject("stats");
   stmuSciD2->SetY1NDC(0.63); stmuSciD2->SetY2NDC(0.78);
   hxSciD2->Draw("sames");
   c->Update();
   TPaveStats *stxSciD2 = (TPaveStats*)hxSciD2->GetListOfFunctions()->FindObject("stats");
   stxSciD2->SetTextColor(kGreen-2);
   stxSciD2->Draw();
   
   c->cd(3);
   gPad->SetLogy();
   hmuSciD3->SetTitle("2 x 4-mm Al, 4-mm SciD_{1}, 2 x 10-mm SciD_{2,3}, 300-mm BGO: #mu-decay vs X-ray cascade SciD_{3}");
   hmuSciD3->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciD3->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciD3->GetYaxis()->SetTitleOffset(2.0);
   hmuSciD3->Draw();
   c->Update();
   TPaveStats *stmuSciD3 = (TPaveStats*)hmuSciD3->GetListOfFunctions()->FindObject("stats");
   stmuSciD3->SetY1NDC(0.63); stmuSciD3->SetY2NDC(0.78);
   hxSciD3->Draw("sames");
   c->Update();
   TPaveStats *stxSciD3 = (TPaveStats*)hxSciD3->GetListOfFunctions()->FindObject("stats");
   stxSciD3->SetTextColor(kGreen-2);
   stxSciD3->Draw();
   
   c->cd(4);
   gPad->SetLogy();
   hmuBGOD1->SetTitle("2 x 4-mm Al, 4-mm SciD_{1}, 2 x 10-mm SciD_{2,3}, 300-mm BGO: #mu-decay vs X-ray cascade BGOD_{1}");
   hmuBGOD1->GetXaxis()->SetTitle("Edep [MeV]");
   hmuBGOD1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuBGOD1->GetYaxis()->SetTitleOffset(2.0);
   hmuBGOD1->Draw();
   c->Update();
   TPaveStats *stmuBGOD1 = (TPaveStats*)hmuBGOD1->GetListOfFunctions()->FindObject("stats");
   stmuBGOD1->SetY1NDC(0.63); stmuBGOD1->SetY2NDC(0.78);
   hxBGOD1->Draw("sames");
   c->Update();
   TPaveStats *stxBGOD1 = (TPaveStats*)hxBGOD1->GetListOfFunctions()->FindObject("stats");
   stxBGOD1->SetTextColor(kGreen-2);
   stxBGOD1->Draw();

   c->cd(5);
   gPad->SetLogy();
   hmuSciD1Z->SetTitle("2 x 4-mm Al, 4-mm SciD_{1}, 2 x 10-mm SciD_{2,3}, 300-mm BGO: #mu-decay vs X-ray cascade SciD_{1}");
   hmuSciD1Z->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciD1Z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciD1Z->GetYaxis()->SetTitleOffset(2.0);
   hmuSciD1Z->Draw();
   c->Update();
   TPaveStats *stmuSciD1Z = (TPaveStats*)hmuSciD1Z->GetListOfFunctions()->FindObject("stats");
   stmuSciD1Z->SetY1NDC(0.63); stmuSciD1Z->SetY2NDC(0.78);
   hxSciD1Z->Draw("sames");
   c->Update();
   TPaveStats *stxSciD1Z = (TPaveStats*)hxSciD1Z->GetListOfFunctions()->FindObject("stats");
   stxSciD1Z->SetTextColor(kGreen-2);
   stxSciD1Z->Draw();
 
   c->cd(6);
   gPad->SetLogy();
   hmuSciD2Z->SetTitle("2 x 4-mm Al, 4-mm SciD_{1}, 2 x 10-mm SciD_{2,3}, 300-mm BGO: #mu-decay vs X-ray cascade SciD_{2}");
   hmuSciD2Z->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciD2Z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciD2Z->GetYaxis()->SetTitleOffset(2.0);
   hmuSciD2Z->Draw();
   c->Update();
   TPaveStats *stmuSciD2Z = (TPaveStats*)hmuSciD2Z->GetListOfFunctions()->FindObject("stats");
   stmuSciD2Z->SetY1NDC(0.63); stmuSciD2Z->SetY2NDC(0.78);
   hxSciD2Z->Draw("sames");
   c->Update();
   TPaveStats *stxSciD2Z = (TPaveStats*)hxSciD2Z->GetListOfFunctions()->FindObject("stats");
   stxSciD2Z->SetTextColor(kGreen-2);
   stxSciD2Z->Draw();
   
   c->cd(7);
   gPad->SetLogy();
   hmuSciD3Z->SetTitle("2 x 4-mm Al, 4-mm SciD_{1}, 2 x 10-mm SciD_{2,3}, 300-mm BGO: #mu-decay vs X-ray cascade SciD_{3}");
   hmuSciD3Z->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciD3Z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciD3Z->GetYaxis()->SetTitleOffset(2.0);
   hmuSciD3Z->Draw();
   c->Update();
   TPaveStats *stmuSciD3Z = (TPaveStats*)hmuSciD3Z->GetListOfFunctions()->FindObject("stats");
   stmuSciD3Z->SetY1NDC(0.63); stmuSciD3Z->SetY2NDC(0.78);
   hxSciD3Z->Draw("sames");
   c->Update();
   TPaveStats *stxSciD3Z = (TPaveStats*)hxSciD3->GetListOfFunctions()->FindObject("stats");
   stxSciD3Z->SetTextColor(kGreen-2);
   stxSciD3Z->Draw();
   
   c->cd(8);
   gPad->SetLogy();
   hmuBGOD1Z->SetTitle("2 x 4-mm Al, 4-mm SciD_{1}, 2 x 10-mm SciD_{2,3}, 300-mm BGO: #mu-decay vs X-ray cascade BGOD_{1}");
   hmuBGOD1Z->GetXaxis()->SetTitle("Edep [MeV]");
   hmuBGOD1Z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuBGOD1Z->GetYaxis()->SetTitleOffset(2.0);
   hmuBGOD1Z->Draw();
   c->Update();
   TPaveStats *stmuBGOD1Z = (TPaveStats*)hmuBGOD1Z->GetListOfFunctions()->FindObject("stats");
   stmuBGOD1Z->SetY1NDC(0.63); stmuBGOD1Z->SetY2NDC(0.78);
   hxBGOD1Z->Draw("sames");
   c->Update();
   TPaveStats *stxBGOD1Z = (TPaveStats*)hxBGOD1Z->GetListOfFunctions()->FindObject("stats");
   stxBGOD1Z->SetTextColor(kGreen-2);
   stxBGOD1Z->Draw();

   c->cd(9);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmuSD1 = new TGraph(nsamps,Ethrmu,EdepmuSciD1);
   grmuSD1->SetTitle("2 x 4-mm Al, 4-mm SciD_{1}, 2 x 10-mm SciD_{2,3}, 300-mm BGO: #mu-decay vs X-ray cascade SciD_{1}");
   grmuSD1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmuSD1->GetXaxis()->SetRangeUser(0,2);
   grmuSD1->GetYaxis()->SetRangeUser(0,1);
   grmuSD1->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmuSD1->GetYaxis()->SetTitleOffset(1.8);
   grmuSD1->GetYaxis()->SetMoreLogLabels(1);
   grmuSD1->SetMarkerColor(kBlack);
   grmuSD1->SetMarkerStyle(33);
   grmuSD1->Draw("ALP");
   c->Update();
   TGraph *grxSD1 = new TGraph(nsamps,Ethrmu,EdepxSciD1);
   grxSD1->SetMarkerColor(kGreen-2);
   grxSD1->SetMarkerStyle(33);
   grxSD1->SetLineColor(kGreen-2);
   grxSD1->Draw("LP");

   c->cd(10);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmuSD2 = new TGraph(nsamps,Ethrmu,EdepmuSciD2);
   grmuSD2->SetTitle("2 x 4-mm Al, 4-mm SciD_{1}, 2 x 10-mm SciD_{2,3}, 300-mm BGO: #mu-decay vs X-ray cascade SciD_{2}");
   grmuSD2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmuSD2->GetXaxis()->SetRangeUser(0,2);
   grmuSD2->GetYaxis()->SetRangeUser(0,1);
   grmuSD2->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmuSD2->GetYaxis()->SetTitleOffset(1.8);
   grmuSD2->GetYaxis()->SetMoreLogLabels(1);
   grmuSD2->SetMarkerColor(kBlack);
   grmuSD2->SetMarkerStyle(33);
   grmuSD2->Draw("ALP");
   c->Update();
   TGraph *grxSD2 = new TGraph(nsamps,Ethrmu,EdepxSciD2);
   grxSD2->SetMarkerColor(kGreen-2);
   grxSD2->SetMarkerStyle(33);
   grxSD2->SetLineColor(kGreen-2);
   grxSD2->Draw("LP");

   c->cd(11);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmuSD3 = new TGraph(nsamps,Ethrmu,EdepmuSciD3);
   grmuSD3->SetTitle("2 x 4-mm Al, 4-mm SciD_{1}, 2 x 10-mm SciD_{2,3}, 300-mm BGO: #mu-decay vs X-ray cascade SciD_{3}");
   grmuSD3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmuSD3->GetXaxis()->SetRangeUser(0,2);
   grmuSD3->GetYaxis()->SetRangeUser(0,1);
   grmuSD3->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmuSD3->GetYaxis()->SetTitleOffset(1.8);
   grmuSD3->GetYaxis()->SetMoreLogLabels(1);
   grmuSD3->SetMarkerColor(kBlack);
   grmuSD3->SetMarkerStyle(33);
   grmuSD3->Draw("ALP");
   c->Update();
   TGraph *grxSD3 = new TGraph(nsamps,Ethrmu,EdepxSciD3);
   grxSD3->SetMarkerColor(kGreen-2);
   grxSD3->SetMarkerStyle(33);
   grxSD3->SetLineColor(kGreen-2);
   grxSD3->Draw("LP");

   c->cd(12);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmuBD1 = new TGraph(nsamps,Ethrmu,EdepmuBGOD1);
   grmuBD1->SetTitle("2 x 4-mm Al, 4-mm SciD_{1}, 2 x 10-mm SciD_{2,3}, 300-mm BGO: #mu-decay vs X-ray cascade BGOD_{1}");
   grmuBD1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmuBD1->GetXaxis()->SetRangeUser(0,2);
   grmuBD1->GetYaxis()->SetRangeUser(0,1);
   grmuBD1->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmuBD1->GetYaxis()->SetTitleOffset(1.8);
   grmuBD1->GetYaxis()->SetMoreLogLabels(1);
   grmuBD1->SetMarkerColor(kBlack);
   grmuBD1->SetMarkerStyle(33);
   grmuBD1->Draw("ALP");
   c->Update();
   TGraph *grxBD1 = new TGraph(nsamps,Ethrmu,EdepxBGOD1);
   grxBD1->SetMarkerColor(kGreen-2);
   grxBD1->SetMarkerStyle(33);
   grxBD1->SetLineColor(kGreen-2);
   grxBD1->Draw("LP");
 
 
   c->SaveAs("Recover_Planar_MULTI_Edep.pdf");
   c->SaveAs("Recover_Planar_MULTI_Edep.png");
   c->SaveAs("Recover_Planar_MULTI_Edep.C");


}


int main() {
   Recover_MULTI();
return 0;
}  
