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
   std::string filemu = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5mudecay.root";
   std::string filex = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5goldcascade.root";

   std::string filemuSciD1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5mudecay_SciD1.txt";
   std::string filexSciD1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5goldcascade_SciD1.txt";
   std::string filemuSciD2 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5mudecay_SciD2.txt";
   std::string filexSciD2 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5goldcascade_SciD2.txt";
   std::string filemuSciDT = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5mudecay_SciDT.txt";
   std::string filexSciDT = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5goldcascade_SciDT.txt";
   std::string filemuSciDB = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5mudecay_SciDB.txt";
   std::string filexSciDB = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5goldcascade_SciDB.txt";
   std::string filemuSciDL = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5mudecay_SciDL.txt";
   std::string filexSciDL = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5goldcascade_SciDL.txt";
   std::string filemuSciDR = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5mudecay_SciDR.txt";
   std::string filexSciDR = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5goldcascade_SciDR.txt";
   std::string filemuBGOD1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5mudecay_BGOD1.txt";
   std::string filexBGOD1 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_phi_z_shifted_1e5goldcascade_BGOD1.txt";

   
   const int nbins = 150;


   // TFiles 
   TFile* fmu = new TFile(TString(filemu));
   TFile* fx = new TFile(TString(filex));

   // Histograms
   TH1F *hmuSciD1 = new TH1F("hmuSciD1","Edep",4*nbins+1,-0.05,60);
   TH1F *hxSciD1 = new TH1F("hxSciD1","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciD2 = new TH1F("hmuSciD2","Edep",4*nbins+1,-0.05,60);
   TH1F *hxSciD2 = new TH1F("hxSciD2","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciDT = new TH1F("hmuSciDT","Edep",4*nbins+1,-0.05,60);
   TH1F *hxSciDT = new TH1F("hxSciDT","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciDB = new TH1F("hmuSciDB","Edep",4*nbins+1,-0.05,60);
   TH1F *hxSciDB = new TH1F("hxSciDB","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciDL = new TH1F("hmuSciDL","Edep",4*nbins+1,-0.05,60);
   TH1F *hxSciDL = new TH1F("hxSciDL","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciDR = new TH1F("hmuSciDR","Edep",4*nbins+1,-0.05,60);
   TH1F *hxSciDR = new TH1F("hxSciDR","Edep",nbins+1,-0.05,15);
   TH1F *hmuBGODL = new TH1F("hmuBGOD1","Edep",4*nbins+1,-0.05,60);
   TH1F *hxBGODL = new TH1F("hxBGOD1","Edep",nbins+1,-0.05,15);
   
   TH1F *hmuSciD1Z = new TH1F("hmuSciD1Z","Edep",3*nbins+1,-0.05,5);
   TH1F *hxSciD1Z = new TH1F("hxSciD1Z","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciD2Z = new TH1F("hmuSciD2Z","Edep",3*nbins+1,-0.05,5);
   TH1F *hxSciD2Z = new TH1F("hxSciD2Z","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciDTZ = new TH1F("hmuSciDTZ","Edep",3*nbins+1,-0.05,15);
   TH1F *hxSciDTZ = new TH1F("hxSciDTZ","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciDBZ = new TH1F("hmuSciDBZ","Edep",3*nbins+1,-0.05,15);
   TH1F *hxSciDBZ = new TH1F("hxSciDBZ","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciDLZ = new TH1F("hmuSciDLZ","Edep",3*nbins+1,-0.05,15);
   TH1F *hxSciDLZ = new TH1F("hxSciDLZ","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciDRZ = new TH1F("hmuSciDRZ","Edep",3*nbins+1,-0.05,15);
   TH1F *hxSciDRZ = new TH1F("hxSciDRZ","Edep",nbins+1,-0.05,15);
   TH1F *hmuBGOD1Z = new TH1F("hmuBGOD1Z","Edep",3*nbins+1,-0.05,15);
   TH1F *hxBGOD1Z = new TH1F("hxBGOD1Z","Edep",nbins+1,-0.05,15);


   // TTrees
   TTree *tmuSciD1 = (TTree*)fmu->Get("Detector/SciDet1");
   TTree *txSciD1 = (TTree*)fx->Get("Detector/SciDet1");
   TTree *tmuSciD2 = (TTree*)fmu->Get("Detector/SciDet2");
   TTree *txSciD2 = (TTree*)fx->Get("Detector/SciDet2");
   TTree *tmuSciDT = (TTree*)fmu->Get("Detector/SciDetT");
   TTree *txSciDT = (TTree*)fx->Get("Detector/SciDetT");
   TTree *tmuSciDB = (TTree*)fmu->Get("Detector/SciDetB");
   TTree *txSciDB = (TTree*)fx->Get("Detector/SciDetB");
   TTree *tmuSciDL = (TTree*)fmu->Get("Detector/SciDetL");
   TTree *txSciDL = (TTree*)fx->Get("Detector/SciDetL");
   TTree *tmuSciDR = (TTree*)fmu->Get("Detector/SciDetR");
   TTree *txSciDR = (TTree*)fx->Get("Detector/SciDetR");
   TTree *tmuBGOD1 = (TTree*)fmu->Get("Detector/BGODet1");
   TTree *txBGOD1 = (TTree*)fx->Get("Detector/BGODet1");

   // Drawings
   tmuSciD1->Draw("Edep>>hmuSciD1","","");
   txSciD1->Draw("Edep>>hxSciD1","","");
   tmuSciD2->Draw("Edep>>hmuSciD2","","");
   txSciD2->Draw("Edep>>hxSciD2","","");
   tmuSciDT->Draw("Edep>>hmuSciDT","","");
   txSciDT->Draw("Edep>>hxSciDT","","");
   tmuSciDB->Draw("Edep>>hmuSciDB","","");
   txSciDB->Draw("Edep>>hxSciDB","","");
   tmuSciDL->Draw("Edep>>hmuSciDL","","");
   txSciDL->Draw("Edep>>hxSciDL","","");
   tmuSciDR->Draw("Edep>>hmuSciDR","","");
   txSciDR->Draw("Edep>>hxSciDR","","");
   tmuBGOD1->Draw("Edep>>hmuBGOD1","","");
   txBGOD1->Draw("Edep>>hxBGOD1","","");   
   
   tmuSciD1->Draw("Edep>>hmuSciD1Z","","");
   txSciD1->Draw("Edep>>hxSciD1Z","","");
   tmuSciD2->Draw("Edep>>hmuSciD2Z","","");
   txSciD2->Draw("Edep>>hxSciD2Z","","");
   tmuSciDT->Draw("Edep>>hmuSciDTZ","","");
   txSciDT->Draw("Edep>>hxSciDTZ","","");
   tmuSciDB->Draw("Edep>>hmuSciDBZ","","");
   txSciDB->Draw("Edep>>hxSciDBZ","","");
   tmuSciDL->Draw("Edep>>hmuSciDLZ","","");
   txSciDL->Draw("Edep>>hxSciDLZ","","");
   tmuSciDR->Draw("Edep>>hmuSciDRZ","","");
   txSciDR->Draw("Edep>>hxSciDRZ","","");
   tmuBGOD1->Draw("Edep>>hmuBGOD1Z","","");
   txBGOD1->Draw("Edep>>hxBGOD1Z","","");


   std::vector<std::string> mufiles;
   std::vector<std::string> Xfiles;

   // Mu-decay
   mufiles.push_back(filemuSciD1);
   mufiles.push_back(filemuSciD2);
   mufiles.push_back(filemuSciDT);
   mufiles.push_back(filemuSciDB);
   mufiles.push_back(filemuSciDL);
   mufiles.push_back(filemuSciDR);
   mufiles.push_back(filemuBGOD1);
   // X-ray cascade
   Xfiles.push_back(filexSciD1);
   Xfiles.push_back(filexSciD2);
   Xfiles.push_back(filexSciDT);
   Xfiles.push_back(filexSciDB);
   Xfiles.push_back(filexSciDL);
   Xfiles.push_back(filexSciDR);
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

   std::vector< std::vector<double> > TotEdepmuSD1(mufiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxSD1(Xfiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuSD2(mufiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxSD2(Xfiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuSDT(mufiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxSDT(Xfiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuSDB(mufiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxSDB(Xfiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuSDL(mufiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxSDL(Xfiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuSDR(mufiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxSDR(Xfiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuBD1(mufiles.size()/7,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxBD1(Xfiles.size()/7,std::vector<double>(nsamps));


   int binmuSD1, binmuSD2, binmuSDT, binmuSDB, binmuSDL, binmuSDR, binmuBD1;
   int binxSD1, binxSD2, binxSDT, binxSDB, binxSDL, binxSDR, binxBD1;
   double integralmuSD1, integralmuSD2, integralmuSDT, integralmuSDB, integralmuSDL, integralmuSDR, integralmuBD1;
   double integralxSD1, integralxSD2, integralxSDT, integralxSDB, integralxSDL, integralxSDR, integralxBD1;
   
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
      // SciDT
      binmuSDT = hmuSciDT->GetXaxis()->FindBin(Ethr);
      integralmuSDT = hmuSciDT->Integral(0,binmuSDT,"");
      binxSDT = hxSciDT->GetXaxis()->FindBin(Ethr);
      integralxSDT = hxSciDT->Integral(0,binxSDT,"");
      // SciDB
      binmuSDB = hmuSciDB->GetXaxis()->FindBin(Ethr);
      integralmuSDB = hmuSciDB->Integral(0,binmuSDB,"");
      binxSDB = hxSciDB->GetXaxis()->FindBin(Ethr);
      integralxSDB = hxSciDB->Integral(0,binxSDB,"");
      // SciDL
      binmuSDL = hmuSciDL->GetXaxis()->FindBin(Ethr);
      integralmuSDL = hmuSciDL->Integral(0,binmuSDL,"");
      binxSDL = hxSciDL->GetXaxis()->FindBin(Ethr);
      integralxSDL = hxSciDL->Integral(0,binxSDL,"");
      // SciDR
      binmuSDR = hmuSciDR->GetXaxis()->FindBin(Ethr);
      integralmuSDR = hmuSciDR->Integral(0,binmuSDR,"");
      binxSDR = hxSciDR->GetXaxis()->FindBin(Ethr);
      integralxSDR = hxSciDR->Integral(0,binxSDR,"");
      // BGOD1
      binmuBD1 = hmuBGOD1->GetXaxis()->FindBin(Ethr);
      integralmuBD1 = hmuBGOD1->Integral(0,binmuBD1,"");
      binxBD1 = hxBGOD1->GetXaxis()->FindBin(Ethr);
      integralxBD1 = hxBGOD1->Integral(0,binxBD1,"");

      TotEdepmuSD1[0][m] = integralmuSD1;
      TotEdepxSD1[0][m] = integralxSD1;
      TotEdepmuSD2[0][m] = integralmuSD2;
      TotEdepxSD2[0][m] = integralxSD2;
      TotEdepmuSDT[0][m] = integralmuSDT;
      TotEdepxSDT[0][m] = integralxSDT;
      TotEdepmuSDB[0][m] = integralmuSDB;
      TotEdepxSDB[0][m] = integralxSDB;
      TotEdepmuSDL[0][m] = integralmuSDL;
      TotEdepxSDL[0][m] = integralxSDL;
      TotEdepmuSDR[0][m] = integralmuSDR;
      TotEdepxSDR[0][m] = integralxSDR;
      TotEdepmuBD1[0][m] = integralmuBD1;
      TotEdepxBD1[0][m] = integralxBD1;     
      
   }
   	 
   float EdepmuSciD1[nsamps] = {};
   float EdepxSciD1[nsamps] = {};
   float EdepmuSciD2[nsamps] = {};
   float EdepxSciD2[nsamps] = {};
   float EdepmuSciDT[nsamps] = {};
   float EdepxSciDT[nsamps] = {};
   float EdepmuSciDB[nsamps] = {};
   float EdepxSciDB[nsamps] = {};
   float EdepmuSciDL[nsamps] = {};
   float EdepxSciDL[nsamps] = {};
   float EdepmuSciDR[nsamps] = {};
   float EdepxSciDR[nsamps] = {};
   float EdepmuBGOD1[nsamps] = {};
   float EdepxBGOD1[nsamps] = {};
   
   
   for (int i=0; i<nsamps; i++) {
      EdepmuSciD1[i] = TotEdepmuSD1[0][i]/TotEdepmuSD1[0][nsamps-1];
      EdepxSciD1[i] = TotEdepxSD1[0][i]/TotEdepxSD1[0][nsamps-1];
      EdepmuSciD2[i] = TotEdepmuSD2[0][i]/TotEdepmuSD2[0][nsamps-1];
      EdepxSciD2[i] = TotEdepxSD2[0][i]/TotEdepxSD2[0][nsamps-1];
      EdepmuSciDT[i] = TotEdepmuSDT[0][i]/TotEdepmuSDT[0][nsamps-1];
      EdepxSciDT[i] = TotEdepxSDT[0][i]/TotEdepxSDT[0][nsamps-1];
      EdepmuSciDB[i] = TotEdepmuSDB[0][i]/TotEdepmuSDB[0][nsamps-1];
      EdepxSciDB[i] = TotEdepxSDB[0][i]/TotEdepxSDB[0][nsamps-1];
      EdepmuSciDL[i] = TotEdepmuSDL[0][i]/TotEdepmuSDL[0][nsamps-1];
      EdepxSciDL[i] = TotEdepxSDL[0][i]/TotEdepxSDL[0][nsamps-1];
      EdepmuSciDR[i] = TotEdepmuSDR[0][i]/TotEdepmuSDR[0][nsamps-1];
      EdepxSciDR[i] = TotEdepxSDR[0][i]/TotEdepxSDR[0][nsamps-1];
      EdepmuBGOD1[i] = TotEdepmuBD1[0][i]/TotEdepmuBD1[0][nsamps-1];
      EdepxBGOD1[i] = TotEdepxBD1[0][i]/TotEdepxBD1[0][nsamps-1];
   }


   // Colours
   hmuSciD1->SetLineColor(kBlack);
   hxSciD1->SetLineColor(kGreen-2);
   hmuSciD2->SetLineColor(kBlack);
   hxSciD2->SetLineColor(kGreen-2);
   hmuSciDT->SetLineColor(kBlack);
   hxSciDT->SetLineColor(kGreen-2);
   hmuSciDB->SetLineColor(kBlack);
   hxSciDB->SetLineColor(kGreen-2);
   hmuSciDL->SetLineColor(kBlack);
   hxSciDL->SetLineColor(kGreen-2);
   hmuSciDR->SetLineColor(kBlack);
   hxSciDR->SetLineColor(kGreen-2);
   hmuBGOD1->SetLineColor(kBlack);
   hxBGOD1->SetLineColor(kGreen-2);

   hmuSciD1Z->SetLineColor(kBlack);
   hxSciD1Z->SetLineColor(kGreen-2);
   hmuSciD2Z->SetLineColor(kBlack);
   hxSciD2Z->SetLineColor(kGreen-2);
   hmuSciDTZ->SetLineColor(kBlack);
   hxSciDTZ->SetLineColor(kGreen-2);
   hmuSciDBZ->SetLineColor(kBlack);
   hxSciDBZ->SetLineColor(kGreen-2);
   hmuSciDLZ->SetLineColor(kBlack);
   hxSciDLZ->SetLineColor(kGreen-2);
   hmuSciDRZ->SetLineColor(kBlack);
   hxSciDRZ->SetLineColor(kGreen-2);
   hmuBGOD1Z->SetLineColor(kBlack);
   hxBGOD1Z->SetLineColor(kGreen-2);

   
   /********************************/
   /*           Plotting           */
   /********************************/

   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(7,3);
   c->cd(1);
   gPad->SetLogy();
   hmuSciD1->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{1}");
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
   hmuSciD2->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{2}");
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
   hmuSciDT->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{T}");
   hmuSciDT->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDT->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDT->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDT->Draw();
   c->Update();
   TPaveStats *stmuSciDT = (TPaveStats*)hmuSciDT->GetListOfFunctions()->FindObject("stats");
   stmuSciDT->SetY1NDC(0.63); stmuSciDT->SetY2NDC(0.78);
   hxSciDT->Draw("sames");
   c->Update();
   TPaveStats *stxSciDT = (TPaveStats*)hxSciDT->GetListOfFunctions()->FindObject("stats");
   stxSciDT->SetTextColor(kGreen-2);
   stxSciDT->Draw();
   
   c->cd(4);
   gPad->SetLogy();
   hmuSciDB->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{B}");
   hmuSciDB->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDB->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDB->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDB->Draw();
   c->Update();
   TPaveStats *stmuSciDB = (TPaveStats*)hmuSciDB->GetListOfFunctions()->FindObject("stats");
   stmuSciDB->SetY1NDC(0.63); stmuSciDB->SetY2NDC(0.78);
   hxSciDB->Draw("sames");
   c->Update();
   TPaveStats *stxSciDB = (TPaveStats*)hxSciDB->GetListOfFunctions()->FindObject("stats");
   stxSciDB->SetTextColor(kGreen-2);
   stxSciDB->Draw();

   c->cd(5);
   gPad->SetLogy();
   hmuSciDL->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{L}");
   hmuSciDL->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDL->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDL->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDL->Draw();
   c->Update();
   TPaveStats *stmuSciDL = (TPaveStats*)hmuSciDL->GetListOfFunctions()->FindObject("stats");
   stmuSciDL->SetY1NDC(0.63); stmuSciDL->SetY2NDC(0.78);
   hxSciDL->Draw("sames");
   c->Update();
   TPaveStats *stxSciDL = (TPaveStats*)hxSciDL->GetListOfFunctions()->FindObject("stats");
   stxSciDL->SetTextColor(kGreen-2);
   stxSciDL->Draw();
   
   c->cd(6);
   gPad->SetLogy();
   hmuSciDR->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{R}");
   hmuSciDR->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDR->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDR->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDR->Draw();
   c->Update();
   TPaveStats *stmuSciDR = (TPaveStats*)hmuSciDR->GetListOfFunctions()->FindObject("stats");
   stmuSciDR->SetY1NDC(0.63); stmuSciDR->SetY2NDC(0.78);
   hxSciDR->Draw("sames");
   c->Update();
   TPaveStats *stxSciDR = (TPaveStats*)hxSciDR->GetListOfFunctions()->FindObject("stats");
   stxSciDR->SetTextColor(kGreen-2);
   stxSciDR->Draw();
   
   c->cd(7);
   gPad->SetLogy();
   hmuBGOD1->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade BGOD_{1}");
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

   c->cd(8);
   gPad->SetLogy();
   hmuSciD1Z->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{1}");
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
 
   c->cd(9);
   gPad->SetLogy();
   hmuSciD2Z->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{2}");
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

   c->cd(10);
   gPad->SetLogy();
   hmuSciDTZ->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{T}");
   hmuSciDTZ->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDTZ->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDTZ->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDTZ->Draw();
   c->Update();
   TPaveStats *stmuSciDTZ = (TPaveStats*)hmuSciDTZ->GetListOfFunctions()->FindObject("stats");
   stmuSciDTZ->SetY1NDC(0.63); stmuSciDTZ->SetY2NDC(0.78);
   hxSciDTZ->Draw("sames");
   c->Update();
   TPaveStats *stxSciDTZ = (TPaveStats*)hxSciDTZ->GetListOfFunctions()->FindObject("stats");
   stxSciDTZ->SetTextColor(kGreen-2);
   stxSciDTZ->Draw();
   
   c->cd(11);
   gPad->SetLogy();
   hmuSciDBZ->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{B}");
   hmuSciDBZ->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDBZ->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDBZ->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDBZ->Draw();
   c->Update();
   TPaveStats *stmuSciDBZ = (TPaveStats*)hmuSciDBZ->GetListOfFunctions()->FindObject("stats");
   stmuSciDBZ->SetY1NDC(0.63); stmuSciDBZ->SetY2NDC(0.78);
   hxSciDBZ->Draw("sames");
   c->Update();
   TPaveStats *stxSciDBZ = (TPaveStats*)hxSciDB->GetListOfFunctions()->FindObject("stats");
   stxSciDBZ->SetTextColor(kGreen-2);
   stxSciDBZ->Draw();
   
   c->cd(12);
   gPad->SetLogy();
   hmuSciDLZ->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{L}");
   hmuSciDLZ->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDLZ->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDLZ->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDLZ->Draw();
   c->Update();
   TPaveStats *stmuSciDLZ = (TPaveStats*)hmuSciDLZ->GetListOfFunctions()->FindObject("stats");
   stmuSciDLZ->SetY1NDC(0.63); stmuSciDLZ->SetY2NDC(0.78);
   hxSciDLZ->Draw("sames");
   c->Update();
   TPaveStats *stxSciDLZ = (TPaveStats*)hxSciDLZ->GetListOfFunctions()->FindObject("stats");
   stxSciDLZ->SetTextColor(kGreen-2);
   stxSciDLZ->Draw();
   
   c->cd(13);
   gPad->SetLogy();
   hmuSciDRZ->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{R}");
   hmuSciDRZ->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDRZ->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDRZ->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDRZ->Draw();
   c->Update();
   TPaveStats *stmuSciDRZ = (TPaveStats*)hmuSciDRZ->GetListOfFunctions()->FindObject("stats");
   stmuSciDRZ->SetY1NDC(0.63); stmuSciDRZ->SetY2NDC(0.78);
   hxSciDRZ->Draw("sames");
   c->Update();
   TPaveStats *stxSciDRZ = (TPaveStats*)hxSciDR->GetListOfFunctions()->FindObject("stats");
   stxSciDRZ->SetTextColor(kGreen-2);
   stxSciDRZ->Draw();
   
   c->cd(14);
   gPad->SetLogy();
   hmuBGOD1Z->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade BGOD_{1}");
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

   c->cd(15);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmuSD1 = new TGraph(nsamps,Ethrmu,EdepmuSciD1);
   grmuSD1->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{1}");
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

   c->cd(16);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmuSD2 = new TGraph(nsamps,Ethrmu,EdepmuSciD2);
   grmuSD2->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{2}");
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

   c->cd(17);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmuSDT = new TGraph(nsamps,Ethrmu,EdepmuSciDT);
   grmuSDT->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{T}");
   grmuSDT->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmuSDT->GetXaxis()->SetRangeUser(0,2);
   grmuSDT->GetYaxis()->SetRangeUser(0,1);
   grmuSDT->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmuSDT->GetYaxis()->SetTitleOffset(1.8);
   grmuSDT->GetYaxis()->SetMoreLogLabels(1);
   grmuSDT->SetMarkerColor(kBlack);
   grmuSDT->SetMarkerStyle(33);
   grmuSDT->Draw("ALP");
   c->Update();
   TGraph *grxSDT = new TGraph(nsamps,Ethrmu,EdepxSciDT);
   grxSDT->SetMarkerColor(kGreen-2);
   grxSDT->SetMarkerStyle(33);
   grxSDT->SetLineColor(kGreen-2);
   grxSDT->Draw("LP");

   c->cd(18);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmuSDB = new TGraph(nsamps,Ethrmu,EdepmuSciDB);
   grmuSDB->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{B}");
   grmuSDB->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmuSDB->GetXaxis()->SetRangeUser(0,2);
   grmuSDB->GetYaxis()->SetRangeUser(0,1);
   grmuSDB->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmuSDB->GetYaxis()->SetTitleOffset(1.8);
   grmuSDB->GetYaxis()->SetMoreLogLabels(1);
   grmuSDB->SetMarkerColor(kBlack);
   grmuSDB->SetMarkerStyle(33);
   grmuSDB->Draw("ALP");
   c->Update();
   TGraph *grxSDB = new TGraph(nsamps,Ethrmu,EdepxSciDB);
   grxSDB->SetMarkerColor(kGreen-2);
   grxSDB->SetMarkerStyle(33);
   grxSDB->SetLineColor(kGreen-2);
   grxSDB->Draw("LP");

   c->cd(19);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmuSDL = new TGraph(nsamps,Ethrmu,EdepmuSciDL);
   grmuSDL->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{L}");
   grmuSDL->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmuSDL->GetXaxis()->SetRangeUser(0,2);
   grmuSDL->GetYaxis()->SetRangeUser(0,1);
   grmuSDL->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmuSDL->GetYaxis()->SetTitleOffset(1.8);
   grmuSDL->GetYaxis()->SetMoreLogLabels(1);
   grmuSDL->SetMarkerColor(kBlack);
   grmuSDL->SetMarkerStyle(33);
   grmuSDL->Draw("ALP");
   c->Update();
   TGraph *grxSDL = new TGraph(nsamps,Ethrmu,EdepxSciDL);
   grxSDL->SetMarkerColor(kGreen-2);
   grxSDL->SetMarkerStyle(33);
   grxSDL->SetLineColor(kGreen-2);
   grxSDL->Draw("LP");

   c->cd(20);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmuSDR = new TGraph(nsamps,Ethrmu,EdepmuSciDR);
   grmuSDR->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade SciD_{R}");
   grmuSDR->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmuSDR->GetXaxis()->SetRangeUser(0,2);
   grmuSDR->GetYaxis()->SetRangeUser(0,1);
   grmuSDR->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmuSDR->GetYaxis()->SetTitleOffset(1.8);
   grmuSDR->GetYaxis()->SetMoreLogLabels(1);
   grmuSDR->SetMarkerColor(kBlack);
   grmuSDR->SetMarkerStyle(33);
   grmuSDR->Draw("ALP");
   c->Update();
   TGraph *grxSDR = new TGraph(nsamps,Ethrmu,EdepxSciDR);
   grxSDR->SetMarkerColor(kGreen-2);
   grxSDR->SetMarkerStyle(33);
   grxSDR->SetLineColor(kGreen-2);
   grxSDR->Draw("LP");

   c->cd(21);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmuBD1 = new TGraph(nsamps,Ethrmu,EdepmuBGOD1);
   grmuBD1->SetTitle("4-mm Al, 4-mm Al, 2 x 4-mm SciD_{1,2}, 4 x 10-mm SciD_{T,B,L,R}, 300-mm BGO, 40-mm Al Cavity, 15-mm z-shift + 50-mm phi-shift: #mu-decay vs X-ray cascade BGOD_{1}");
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
 
 
   c->SaveAs("Recover_Planar_6xSDs_BGO_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_50mm_phi_shift_MULTI_Edep.pdf");
   c->SaveAs("Recover_Planar_6xSDs_BGO_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_50mm_phi_shift_MULTI_Edep.png");
   c->SaveAs("Recover_Planar_6xSDs_BGO_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_50mm_phi_shift_MULTI_Edep.C");


}


int main() {
   Recover_MULTI();
return 0;
}  
