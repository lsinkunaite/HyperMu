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
   std::string filemu = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5mudecay.root";
   std::string filex = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5goldcascade.root";

   std::string filemuSciDFIn1 = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5mudecay_SciDFIn1.txt";
   std::string filexSciDFIn1 = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5goldcascade_SciDFIn1.txt";
   std::string filemuSciDFIn2 = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5mudecay_SciDFIn2.txt";
   std::string filexSciDFIn2 = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5goldcascade_SciDFIn2.txt";
   //std::string filemuSciDF = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5mudecay_SciDF.txt";
   //std::string filexSciDF = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5goldcascade_SciDF.txt";
   std::string filemuTubeD = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5mudecay_TubeD.txt";
   std::string filexTubeD = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5goldcascade_TubeD.txt";
   std::string filemuSciDE = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5mudecay_SciDE.txt";
   std::string filexSciDE = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5goldcascade_SciDE.txt";

   
   const int nbins = 150;


   // TFiles 
   TFile* fmu = new TFile(TString(filemu));
   TFile* fx = new TFile(TString(filex));

   // Histograms
   TH1F *hmuSciDFIn1 = new TH1F("hmuSciDFIn1","Edep",4*nbins+1,-0.05,60);
   TH1F *hxSciDFIn1 = new TH1F("hxSciDFIn1","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciDFIn2 = new TH1F("hmuSciDFIn2","Edep",4*nbins+1,-0.05,60);
   TH1F *hxSciDFIn2 = new TH1F("hxSciDFIn2","Edep",nbins+1,-0.05,15);
   //TH1F *hmuSciDF = new TH1F("hmuSciDF","Edep",4*nbins+1,-0.05,60);
   //TH1F *hxSciDF = new TH1F("hxSciDF","Edep",nbins+1,-0.05,15);
   TH1F *hmuTubeD = new TH1F("hmuTubeD","Edep",4*nbins+1,-0.05,60);
   TH1F *hxTubeD = new TH1F("hxTubeD","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciDE = new TH1F("hmuSciDE","Edep",4*nbins+1,-0.05,60);
   TH1F *hxSciDE = new TH1F("hxSciDE","Edep",nbins+1,-0.05,15);
   
   TH1F *hmuSciDFIn1Z = new TH1F("hmuSciDFIn1Z","Edep",3*nbins+1,-0.05,5);
   TH1F *hxSciDFIn1Z = new TH1F("hxSciDFIn1Z","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciDFIn2Z = new TH1F("hmuSciDFIn2Z","Edep",3*nbins+1,-0.05,5);
   TH1F *hxSciDFIn2Z = new TH1F("hxSciDFIn2Z","Edep",nbins+1,-0.05,15);
   //TH1F *hmuSciDFZ = new TH1F("hmuSciDFZ","Edep",3*nbins+1,-0.05,5);
   //TH1F *hxSciDFZ = new TH1F("hxSciDFZ","Edep",nbins+1,-0.05,15);
   TH1F *hmuTubeDZ = new TH1F("hmuTubeDZ","Edep",3*nbins+1,-0.05,5);
   TH1F *hxTubeDZ = new TH1F("hxTubeDZ","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciDEZ = new TH1F("hmuSciDEZ","Edep",3*nbins+1,-0.05,5);
   TH1F *hxSciDEZ = new TH1F("hxSciDEZ","Edep",nbins+1,-0.05,15);


   // TTrees
   TTree *tmuSciDFIn1 = (TTree*)fmu->Get("Detector/H2BoxSciDetFrontIn1");
   TTree *txSciDFIn1 = (TTree*)fx->Get("Detector/H2BoxSciDetFrontIn1");
   TTree *tmuSciDFIn2 = (TTree*)fmu->Get("Detector/H2BoxSciDetFrontIn2");
   TTree *txSciDFIn2 = (TTree*)fx->Get("Detector/H2BoxSciDetFrontIn2");
   //TTree *tmuSciDF = (TTree*)fmu->Get("Detector/SciDetFront");
   //TTree *txSciDF = (TTree*)fx->Get("Detector/SciDetFront");
   TTree *tmuTubeD = (TTree*)fmu->Get("Detector/TubeDet");
   TTree *txTubeD = (TTree*)fx->Get("Detector/TubeDet");
   TTree *tmuSciDE = (TTree*)fmu->Get("Detector/SciDetEnd");
   TTree *txSciDE = (TTree*)fx->Get("Detector/SciDetEnd");


   // Drawings
   tmuSciDFIn1->Draw("Edep>>hmuSciDFIn1","","");
   txSciDFIn1->Draw("Edep>>hxSciDFIn1","","");
   tmuSciDFIn2->Draw("Edep>>hmuSciDFIn2","","");
   txSciDFIn2->Draw("Edep>>hxSciDFIn2","","");
   //tmuSciDF->Draw("Edep>>hmuSciDF","","");
   //txSciDF->Draw("Edep>>hxSciDF","","");   
   tmuTubeD->Draw("Edep>>hmuTubeD","","");
   txTubeD->Draw("Edep>>hxTubeD","","");
   tmuSciDE->Draw("Edep>>hmuSciDE","","");
   txSciDE->Draw("Edep>>hxSciDE","","");
   
   tmuSciDFIn1->Draw("Edep>>hmuSciDFIn1Z","","");
   txSciDFIn1->Draw("Edep>>hxSciDFIn1Z","","");
   tmuSciDFIn2->Draw("Edep>>hmuSciDFIn2Z","","");
   txSciDFIn2->Draw("Edep>>hxSciDFIn2z","","");
   //tmuSciDF->Draw("Edep>>hmuSciDFZ","","");
   //txSciDF->Draw("Edep>>hxSciDFZ","","");
   tmuTubeD->Draw("Edep>>hmuTubeDZ","","");
   txTubeD->Draw("Edep>>hxTubeDZ","","");
   tmuSciDE->Draw("Edep>>hmuSciDEZ","","");
   txSciDE->Draw("Edep>>hxSciDEZ","","");


   std::vector<std::string> mufiles;
   std::vector<std::string> Xfiles;

   // Mu-decay
   mufiles.push_back(filemuSciDFIn1);
   mufiles.push_back(filemuSciDFIn2);
   //mufiles.push_back(filemuSciDF);
   mufiles.push_back(filemuTubeD);
   mufiles.push_back(filemuSciDE);
   // X-ray cascade
   Xfiles.push_back(filexSciDFIn1);
   Xfiles.push_back(filexSciDFIn2);
   //Xfiles.push_back(filexSciDF);
   Xfiles.push_back(filexTubeD);
   Xfiles.push_back(filexSciDE);


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

   //std::vector< std::vector<double> > TotEdepmuSDF(mufiles.size()/3,std::vector<double>(nsamps));
   //std::vector< std::vector<double> > TotEdepxSDF(Xfiles.size()/3,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuSDFIn1(mufiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxSDFIn1(Xfiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuSDFIn2(mufiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxSDFIn2(Xfiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuTD(mufiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxTD(Xfiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuSDE(mufiles.size()/4,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxSDE(Xfiles.size()/4,std::vector<double>(nsamps));


   int binmuSDFIn1, binxSDFIn1, binmuSDFIn2, binxSDFIn2, binmuTD, binxTD, binmuSDE, binxSDE;
   double integralmuSDFIn1, integralxSDFIn1, integralmuSDFIn2, integralxSDFIn2, integralmuTD, integralxTD, integralmuSDE, integralxSDE;
   
   for (int m=0; m < nsamps; m++) {
	   
      Ethr = Ethrmu[m];
/*
      // SciDF
      binmuSDF = hmuSciDF->GetXaxis()->FindBin(Ethr);
      integralmuSDF = hmuSciDF->Integral(0,binmuSDF,"");	     
      binxSDF = hxSciDF->GetXaxis()->FindBin(Ethr);
      integralxSDF = hxSciDF->Integral(0,binxSDF,"");
*/
      // SciDFIn1
      binmuSDFIn1 = hmuSciDFIn1->GetXaxis()->FindBin(Ethr);
      integralmuSDFIn1 = hmuSciDFIn1->Integral(0,binmuSDFIn1,"");
      binxSDFIn1 = hxSciDFIn1->GetXaxis()->FindBin(Ethr);
      integralxSDFIn1 = hxSciDFIn1->Integral(0,binxSDFIn1,"");
      // SciDFIn2
      binmuSDFIn2 = hmuSciDFIn2->GetXaxis()->FindBin(Ethr);
      integralmuSDFIn2 = hmuSciDFIn2->Integral(0,binmuSDFIn2,"");
      binxSDFIn2 = hxSciDFIn2->GetXaxis()->FindBin(Ethr);
      integralxSDFIn2 = hxSciDFIn2->Integral(0,binxSDFIn2,"");
      // TubeD
      binmuTD = hmuTubeD->GetXaxis()->FindBin(Ethr);
      integralmuTD = hmuTubeD->Integral(0,binmuTD,"");	     
      binxTD = hxTubeD->GetXaxis()->FindBin(Ethr);
      integralxTD = hxTubeD->Integral(0,binxTD,"");
      // SciDE
      binmuSDE = hmuSciDE->GetXaxis()->FindBin(Ethr);
      integralmuSDE = hmuSciDE->Integral(0,binmuSDE,"");	     
      binxSDE = hxSciDE->GetXaxis()->FindBin(Ethr);
      integralxSDE = hxSciDE->Integral(0,binxSDE,"");

      TotEdepmuSDFIn1[0][m] = integralmuSDFIn1;
      TotEdepxSDFIn1[0][m] = integralxSDFIn1;
      TotEdepmuSDFIn2[0][m] = integralmuSDFIn2;
      TotEdepxSDFIn2[0][m] = integralxSDFIn2;
      //TotEdepmuSDF[0][m] = integralmuSDF;
      //TotEdepxSDF[0][m] = integralxSDF;     
      TotEdepmuTD[0][m] = integralmuTD;
      TotEdepxTD[0][m] = integralxTD;     
      TotEdepmuSDE[0][m] = integralmuSDE;
      TotEdepxSDE[0][m] = integralxSDE;     


      
   }
   	 
   float EdepmuSciDFIn1[nsamps]	= {};
   float EdepxSciDFIn1[nsamps] = {};
   float EdepmuSciDFIn2[nsamps] = {};
   float EdepxSciDFIn2[nsamps] = {};  	     
   //float EdepmuSciDF[nsamps] = {};
   //float EdepxSciDF[nsamps] = {};	  	     
   float EdepmuTubeD[nsamps] = {};
   float EdepxTubeD[nsamps] = {};
   float EdepmuSciDE[nsamps] = {};
   float EdepxSciDE[nsamps] = {};
   
   for (int i=0; i<nsamps; i++) {
	  //EdepmuSciDF[i] = TotEdepmuSDF[0][i]/TotEdepmuSDF[0][nsamps-1];
	  //EdepxSciDF[i] = TotEdepxSDF[0][i]/TotEdepxSDF[0][nsamps-1]; 
	  EdepmuSciDFIn1[i] = TotEdepmuSDFIn1[0][i]/TotEdepmuSDFIn1[0][nsamps-1];
	  EdepxSciDFIn1[i] = TotEdepxSDFIn1[0][i]/TotEdepxSDFIn1[0][nsamps-1];
	  EdepmuSciDFIn2[i] = TotEdepmuSDFIn2[0][i]/TotEdepmuSDFIn2[0][nsamps-1];
	  EdepxSciDFIn2[i] = TotEdepxSDFIn2[0][i]/TotEdepxSDFIn2[0][nsamps-1];
	  EdepmuTubeD[i] = TotEdepmuTD[0][i]/TotEdepmuTD[0][nsamps-1];
	  EdepxTubeD[i] = TotEdepxTD[0][i]/TotEdepxTD[0][nsamps-1]; 
      EdepmuSciDE[i] = TotEdepmuSDE[0][i]/TotEdepmuSDE[0][nsamps-1];
	  EdepxSciDE[i] = TotEdepxSDE[0][i]/TotEdepxSDE[0][nsamps-1];
   }


   // Colours
   hmuSciDFIn1->SetLineColor(kBlack);
   hxSciDFIn1->SetLineColor(kGreen-2);
   hmuSciDFIn2->SetLineColor(kBlack);
   hxSciDFIn2->SetLineColor(kGreen-2);
   //hmuSciDF->SetLineColor(kBlack);
   //hxSciDF->SetLineColor(kGreen-2); 
   hmuTubeD->SetLineColor(kBlack);
   hxTubeD->SetLineColor(kGreen-2);
   hmuSciDE->SetLineColor(kBlack);
   hxSciDE->SetLineColor(kGreen-2);

   hmuSciDFIn1Z->SetLineColor(kBlack);
   hxSciDFIn1Z->SetLineColor(kGreen-2);
   hmuSciDFIn2Z->SetLineColor(kBlack);
   hxSciDFIn2Z->SetLineColor(kGreen-2);
   //hmuSciDFZ->SetLineColor(kBlack);
   //hxSciDFZ->SetLineColor(kGreen-2);
   hmuTubeDZ->SetLineColor(kBlack);
   hxTubeDZ->SetLineColor(kGreen-2);
   hmuSciDEZ->SetLineColor(kBlack);
   hxSciDEZ->SetLineColor(kGreen-2);

   
   /********************************/
   /*           Plotting           */
   /********************************/

   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(4,3);
/*   c->cd(1);
   gPad->SetLogy();
   hmuSciDF->SetTitle("Bfield_5T_5mmAlTD_2mm_Al: #mu-decay vs X-ray cascade: 200-mm x 200-mm 4-mm SciDF");
   hmuSciDF->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDF->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDF->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDF->Draw();
   c->Update();
   TPaveStats *stmuSciDF = (TPaveStats*)hmuSciDF->GetListOfFunctions()->FindObject("stats");
   stmuSciDF->SetY1NDC(0.63); stmuSciDF->SetY2NDC(0.78);
   hxSciDF->Draw("sames");
   c->Update();
   TPaveStats *stxSciDF = (TPaveStats*)hxSciDF->GetListOfFunctions()->FindObject("stats");
   stxSciDF->SetTextColor(kGreen-2);
   stxSciDF->Draw();
*/
   c->cd(1);
   gPad->SetLogy();
   hmuSciDFIn1->SetTitle("Bfield_5T_SDFInx2_2mm_Al: #mu-decay vs X-ray cascade: 200-mm x 200-mm 1-mm SciDFIn1");
   hmuSciDFIn1->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDFIn1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDFIn1->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDFIn1->Draw();
   c->Update();
   TPaveStats *stmuSciDFIn1 = (TPaveStats*)hmuSciDFIn1->GetListOfFunctions()->FindObject("stats");
   stmuSciDFIn1->SetY1NDC(0.63); stmuSciDFIn1->SetY2NDC(0.78);
   hxSciDFIn1->Draw("sames");
   c->Update();
   TPaveStats *stxSciDFIn1 = (TPaveStats*)hxSciDFIn1->GetListOfFunctions()->FindObject("stats");
   stxSciDFIn1->SetTextColor(kGreen-2);
   stxSciDFIn1->Draw();
 
   c->cd(2);
   gPad->SetLogy();
   hmuSciDFIn2->SetTitle("Bfield_5T_SDFInx2_2mm_Al: #mu-decay vs X-ray cascade: 200-mm x 200-mm 1-mm SciDFIn2");
   hmuSciDFIn2->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDFIn2->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDFIn2->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDFIn2->Draw();
   c->Update();
   TPaveStats *stmuSciDFIn2 = (TPaveStats*)hmuSciDFIn2->GetListOfFunctions()->FindObject("stats");
   stmuSciDFIn2->SetY1NDC(0.63); stmuSciDFIn2->SetY2NDC(0.78);
   hxSciDFIn2->Draw("sames");
   c->Update();
   TPaveStats *stxSciDFIn2 = (TPaveStats*)hxSciDFIn2->GetListOfFunctions()->FindObject("stats");
   stxSciDFIn2->SetTextColor(kGreen-2);
   stxSciDFIn2->Draw();

   c->cd(3);
   gPad->SetLogy();
   hmuTubeD->SetTitle("Bfield_5T_SDFInx2_2mm_Al: #mu-decay vs X-ray cascade: 50-mm round BGO");
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
   hmuSciDE->SetTitle("Bfield_5T_SDFInx2_2mm_Al: #mu-decay vs X-ray cascade: 100-mm x 100-mm 10-mm SciDE");
   hmuSciDE->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDE->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDE->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDE->Draw();
   c->Update();
   TPaveStats *stmuSciDE = (TPaveStats*)hmuSciDE->GetListOfFunctions()->FindObject("stats");
   stmuSciDE->SetY1NDC(0.63); stmuSciDE->SetY2NDC(0.78);
   hxSciDE->Draw("sames");
   c->Update();
   TPaveStats *stxSciDE = (TPaveStats*)hxSciDE->GetListOfFunctions()->FindObject("stats");
   stxSciDE->SetTextColor(kGreen-2);
   stxSciDE->Draw();
/*
   c->cd(4);
   gPad->SetLogy();
   hmuSciDFZ->SetTitle("Bfield_5T_5mmAlTD_2mm_Al: #mu-decay vs X-ray cascade: 200-mm x 200-mm 4-mm SciDF");
   hmuSciDFZ->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDFZ->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDFZ->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDFZ->Draw();
   c->Update();
   TPaveStats *stmuSciDFZ = (TPaveStats*)hmuSciDFZ->GetListOfFunctions()->FindObject("stats");
   stmuSciDFZ->SetY1NDC(0.63); stmuSciDFZ->SetY2NDC(0.78);
   hxSciDFZ->Draw("sames");
   c->Update();
   TPaveStats *stxSciDFZ = (TPaveStats*)hxSciDFZ->GetListOfFunctions()->FindObject("stats");
   stxSciDFZ->SetTextColor(kGreen-2);
   stxSciDFZ->Draw();
*/
   c->cd(5);
   gPad->SetLogy();
   hmuSciDFIn1Z->SetTitle("Bfield_5T_SDFInx2_2mm_Al: #mu-decay vs X-ray cascade: 200-mm x 200-mm 1-mm SciDFIn1");
   hmuSciDFIn1Z->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDFIn1Z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDFIn1Z->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDFIn1Z->Draw();
   c->Update();
   TPaveStats *stmuSciDFIn1Z = (TPaveStats*)hmuSciDFIn1Z->GetListOfFunctions()->FindObject("stats");
   stmuSciDFIn1Z->SetY1NDC(0.63); stmuSciDFIn1Z->SetY2NDC(0.78);
   hxSciDFIn1Z->Draw("sames");
   c->Update();
   TPaveStats *stxSciDFIn1Z = (TPaveStats*)hxSciDFIn1Z->GetListOfFunctions()->FindObject("stats");
   stxSciDFIn1Z->SetTextColor(kGreen-2);
   stxSciDFIn1Z->Draw();

   c->cd(6);
   gPad->SetLogy();
   hmuSciDFIn2Z->SetTitle("Bfield_5T_SDFInx2_2mm_Al: #mu-decay vs X-ray cascade: 200-mm x 200-mm 1-mm SciDFIn2");
   hmuSciDFIn2Z->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDFIn2Z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDFIn2Z->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDFIn2Z->Draw();
   c->Update();
   TPaveStats *stmuSciDFIn2Z = (TPaveStats*)hmuSciDFIn2Z->GetListOfFunctions()->FindObject("stats");
   stmuSciDFIn2Z->SetY1NDC(0.63); stmuSciDFIn2Z->SetY2NDC(0.78);
   hxSciDFIn2Z->Draw("sames");
   c->Update();
   TPaveStats *stxSciDFIn2Z = (TPaveStats*)hxSciDFIn2Z->GetListOfFunctions()->FindObject("stats");
   stxSciDFIn2Z->SetTextColor(kGreen-2);
   stxSciDFIn2Z->Draw();

   c->cd(7);
   gPad->SetLogy();
   hmuTubeDZ->SetTitle("Bfield_5T_SDFInx2_2mm_Al: #mu-decay vs X-ray cascade: 50-mm round BGO");
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
   
   c->cd(8);
   gPad->SetLogy();
   hmuSciDEZ->SetTitle("Bfield_5T_SDFInx2_2mm_Al: #mu-decay vs X-ray cascade: 100-mm x 100-mm 10-mm SciDE");
   hmuSciDEZ->GetXaxis()->SetTitle("Edep [MeV]");
   hmuSciDEZ->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmuSciDEZ->GetYaxis()->SetTitleOffset(2.0);
   hmuSciDEZ->Draw();
   c->Update();
   TPaveStats *stmuSciDEZ = (TPaveStats*)hmuSciDEZ->GetListOfFunctions()->FindObject("stats");
   stmuSciDEZ->SetY1NDC(0.63); stmuSciDEZ->SetY2NDC(0.78);
   hxSciDEZ->Draw("sames");
   c->Update();
   TPaveStats *stxSciDEZ = (TPaveStats*)hxSciDEZ->GetListOfFunctions()->FindObject("stats");
   stxSciDEZ->SetTextColor(kGreen-2);
   stxSciDEZ->Draw();

   c->cd(9);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmuIn1 = new TGraph(nsamps,Ethrmu,EdepmuSciDFIn1);
   grmuIn1->SetTitle("Bfield_5T_SDFInx2_2mm_Al: #mu-decay vs X-ray cascade: 200-mm x 200-mm 1-mm SciDFIn1");
   grmuIn1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmuIn1->GetXaxis()->SetRangeUser(0,2);
   grmuIn1->GetYaxis()->SetRangeUser(0,1);
   grmuIn1->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmuIn1->GetYaxis()->SetTitleOffset(1.8);
   grmuIn1->GetYaxis()->SetMoreLogLabels(1);
   grmuIn1->SetMarkerColor(kBlack);
   grmuIn1->SetMarkerStyle(33);
   grmuIn1->Draw("ALP");
   c->Update();
   TGraph *grxIn1 = new TGraph(nsamps,Ethrmu,EdepxSciDFIn1);
   grxIn1->SetMarkerColor(kGreen-2);
   grxIn1->SetMarkerStyle(33);
   grxIn1->SetLineColor(kGreen-2);
   grxIn1->Draw("LP");

   c->cd(10);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmuIn2 = new TGraph(nsamps,Ethrmu,EdepmuSciDFIn2);
   grmuIn2->SetTitle("Bfield_5T_SDFInx2_2mm_Al: #mu-decay vs X-ray cascade: 200-mm x 200-mm 1-mm SciDFIn2");
   grmuIn2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmuIn2->GetXaxis()->SetRangeUser(0,2);
   grmuIn2->GetYaxis()->SetRangeUser(0,1);
   grmuIn2->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmuIn2->GetYaxis()->SetTitleOffset(1.8);
   grmuIn2->GetYaxis()->SetMoreLogLabels(1);
   grmuIn2->SetMarkerColor(kBlack);
   grmuIn2->SetMarkerStyle(33);
   grmuIn2->Draw("ALP");
   c->Update();
   TGraph *grxIn2 = new TGraph(nsamps,Ethrmu,EdepxSciDFIn2);
   grxIn2->SetMarkerColor(kGreen-2);
   grxIn2->SetMarkerStyle(33);
   grxIn2->SetLineColor(kGreen-2);
   grxIn2->Draw("LP");


/*   
   c->cd(7);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu1 = new TGraph(nsamps,Ethrmu,EdepmuSciDF);
   grmu1->SetTitle("Bfield_5T_5mmAlTD_2mm_Al: #mu-decay vs X-ray cascade: 200-mm x 200-mm 4-mm SciDF");
   grmu1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu1->GetXaxis()->SetRangeUser(0,2);
   grmu1->GetYaxis()->SetRangeUser(0,1);
   grmu1->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu1->GetYaxis()->SetTitleOffset(1.8);
   grmu1->GetYaxis()->SetMoreLogLabels(1);
   grmu1->SetMarkerColor(kBlack);
   grmu1->SetMarkerStyle(33);
   grmu1->Draw("ALP");
   c->Update();
   TGraph *grx1 = new TGraph(nsamps,Ethrmu,EdepxSciDF);
   grx1->SetMarkerColor(kGreen-2);
   grx1->SetMarkerStyle(33);
   grx1->SetLineColor(kGreen-2);
   grx1->Draw("LP");
*/   
   c->cd(11);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu2 = new TGraph(nsamps,Ethrmu,EdepmuTubeD);
   grmu2->SetTitle("Bfield_5T_SDFInx2_2mm_Al: #mu-decay vs X-ray cascade: 50-mm round BGO");
   grmu2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu2->GetXaxis()->SetRangeUser(0,2);
   grmu2->GetYaxis()->SetRangeUser(0,1);
   grmu2->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu2->GetYaxis()->SetTitleOffset(1.8);
   grmu2->GetYaxis()->SetMoreLogLabels(1);
   grmu2->SetMarkerColor(kBlack);
   grmu2->SetMarkerStyle(33);
   grmu2->Draw("ALP");
   c->Update();
   TGraph *grx2 = new TGraph(nsamps,Ethrmu,EdepxTubeD);
   grx2->SetMarkerColor(kGreen-2);
   grx2->SetMarkerStyle(33);
   grx2->SetLineColor(kGreen-2);
   grx2->Draw("LP");

   c->cd(12);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu3 = new TGraph(nsamps,Ethrmu,EdepmuSciDE);
   grmu3->SetTitle("Bfield_5T_SDFInx2_2mm_Al: #mu-decay vs X-ray cascade: 100-mm x 100-mm 10-mm SciDE");
   grmu3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu3->GetXaxis()->SetRangeUser(0,2);
   grmu3->GetYaxis()->SetRangeUser(0,1);
   grmu3->GetYaxis()->SetTitle("E_{dep}(E_{THR})");
   grmu3->GetYaxis()->SetTitleOffset(1.8);
   grmu3->GetYaxis()->SetMoreLogLabels(1);
   grmu3->SetMarkerColor(kBlack);
   grmu3->SetMarkerStyle(33);
   grmu3->Draw("ALP");
   c->Update();
   TGraph *grx3 = new TGraph(nsamps,Ethrmu,EdepxSciDE);
   grx3->SetMarkerColor(kGreen-2);
   grx3->SetMarkerStyle(33);
   grx3->SetLineColor(kGreen-2);
   grx3->Draw("LP");

   c->SaveAs("ad_3dets_SDFInx2_2mm_Al_BGO_Bfield_5T_MULTI_Edep.pdf");
   c->SaveAs("ad_3dets_SDFInx2_2mm_Al_BGO_Bfield_5T_MULTI_Edep.png");
   c->SaveAs("ad_3dets_SDFInx2_2mm_Al_BGO_Bfield_5T_MULTI_Edep.C");


}


int main() {
   Bfield_5T_MULTI();
return 0;
}  
