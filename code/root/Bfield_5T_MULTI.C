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
   std::string filemu = "../../simdata/magnetic/adBfield_5T_smSDE_5mmAlBGO_2mm_Al_det_BGO1e5mudecay.root";
   std::string filex = "../../simdata/magnetic/adBfield_5T_smSDE_5mmAlBGO_2mm_Al_det_BGO1e5goldcascade.root";

   std::string filemuSciDF = "../../simdata/magnetic/adBfield_5T_smSDE_5mmAlBGO_2mm_Al_det_BGO1e5mudecay_SciDF.txt";
   std::string filexSciDF = "../../simdata/magnetic/adBfield_5T_smSDE_5mmAlBGO_2mm_Al_det_BGO1e5goldcascade_SciDF.txt";
   std::string filemuTubeD = "../../simdata/magnetic/adBfield_5T_smSDE_5mmAlBGO_2mm_Al_det_BGO1e5mudecay_TubeD.txt";
   std::string filexTubeD = "../../simdata/magnetic/adBfield_5T_smSDE_5mmAlBGO_2mm_Al_det_BGO1e5goldcascade_TubeD.txt";
   std::string filemuSciDE = "../../simdata/magnetic/adBfield_5T_smSDE_5mmAlBGO_2mm_Al_det_BGO1e5mudecay_SciDE.txt";
   std::string filexSciDE = "../../simdata/magnetic/adBfield_5T_smSDE_5mmAlBGO_2mm_Al_det_BGO1e5goldcascade_SciDE.txt";

   
   const int nbins = 150;


   // TFiles 
   TFile* fmu = new TFile(TString(filemu));
   TFile* fx = new TFile(TString(filex));

   // Histograms
   TH1F *hmuSciDF = new TH1F("hmuSciDF","Edep",4*nbins+1,-0.05,60);
   TH1F *hxSciDF = new TH1F("hxSciDF","Edep",nbins+1,-0.05,15);
   TH1F *hmuTubeD = new TH1F("hmuTubeD","Edep",4*nbins+1,-0.05,60);
   TH1F *hxTubeD = new TH1F("hxTubeD","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciDE = new TH1F("hmuSciDE","Edep",4*nbins+1,-0.05,60);
   TH1F *hxSciDE = new TH1F("hxSciDE","Edep",nbins+1,-0.05,15);
   
   TH1F *hmuSciDFZ = new TH1F("hmuSciDFZ","Edep",3*nbins+1,-0.05,5);
   TH1F *hxSciDFZ = new TH1F("hxSciDFZ","Edep",nbins+1,-0.05,15);
   TH1F *hmuTubeDZ = new TH1F("hmuTubeDZ","Edep",3*nbins+1,-0.05,5);
   TH1F *hxTubeDZ = new TH1F("hxTubeDZ","Edep",nbins+1,-0.05,15);
   TH1F *hmuSciDEZ = new TH1F("hmuSciDEZ","Edep",3*nbins+1,-0.05,5);
   TH1F *hxSciDEZ = new TH1F("hxSciDEZ","Edep",nbins+1,-0.05,15);


   // TTrees
   TTree *tmuSciDF = (TTree*)fmu->Get("Detector/SciDetFront");
   TTree *txSciDF = (TTree*)fx->Get("Detector/SciDetFront");
   TTree *tmuTubeD = (TTree*)fmu->Get("Detector/TubeDet");
   TTree *txTubeD = (TTree*)fx->Get("Detector/TubeDet");
   TTree *tmuSciDE = (TTree*)fmu->Get("Detector/SciDetEnd");
   TTree *txSciDE = (TTree*)fx->Get("Detector/SciDetEnd");


   // Drawings
   tmuSciDF->Draw("Edep>>hmuSciDF","","");
   txSciDF->Draw("Edep>>hxSciDF","","");   
   tmuTubeD->Draw("Edep>>hmuTubeD","","");
   txTubeD->Draw("Edep>>hxTubeD","","");
   tmuSciDE->Draw("Edep>>hmuSciDE","","");
   txSciDE->Draw("Edep>>hxSciDE","","");
   
   tmuSciDF->Draw("Edep>>hmuSciDFZ","","");
   txSciDF->Draw("Edep>>hxSciDFZ","","");
   tmuTubeD->Draw("Edep>>hmuTubeDZ","","");
   txTubeD->Draw("Edep>>hxTubeDZ","","");
   tmuSciDE->Draw("Edep>>hmuSciDEZ","","");
   txSciDE->Draw("Edep>>hxSciDEZ","","");


   std::vector<std::string> mufiles;
   std::vector<std::string> Xfiles;

   // Mu-decay
   mufiles.push_back(filemuSciDF);
   mufiles.push_back(filemuTubeD);
   mufiles.push_back(filemuSciDE);
   // X-ray cascade
   Xfiles.push_back(filexSciDF);
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

   std::vector< std::vector<double> > TotEdepmuSDF(mufiles.size()/3,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxSDF(Xfiles.size()/3,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuTD(mufiles.size()/3,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxTD(Xfiles.size()/3,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepmuSDE(mufiles.size()/3,std::vector<double>(nsamps));
   std::vector< std::vector<double> > TotEdepxSDE(Xfiles.size()/3,std::vector<double>(nsamps));


   int binmuSDF, binxSDF, binmuTD, binxTD, binmuSDE, binxSDE;
   double integralmuSDF, integralxSDF, integralmuTD, integralxTD, integralmuSDE, integralxSDE;
   
   for (int m=0; m < nsamps; m++) {
	   
      Ethr = Ethrmu[m];

      // SciDF
      binmuSDF = hmuSciDF->GetXaxis()->FindBin(Ethr);
      integralmuSDF = hmuSciDF->Integral(0,binmuSDF,"");	     
      binxSDF = hxSciDF->GetXaxis()->FindBin(Ethr);
      integralxSDF = hxSciDF->Integral(0,binxSDF,"");
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

      TotEdepmuSDF[0][m] = integralmuSDF;
      TotEdepxSDF[0][m] = integralxSDF;     
      TotEdepmuTD[0][m] = integralmuTD;
      TotEdepxTD[0][m] = integralxTD;     
      TotEdepmuSDE[0][m] = integralmuSDE;
      TotEdepxSDE[0][m] = integralxSDE;     


      
   }
   	  	     
   float EdepmuSciDF[nsamps] = {};
   float EdepxSciDF[nsamps] = {};	  	     
   float EdepmuTubeD[nsamps] = {};
   float EdepxTubeD[nsamps] = {};
   float EdepmuSciDE[nsamps] = {};
   float EdepxSciDE[nsamps] = {};
   
   for (int i=0; i<nsamps; i++) {
	  EdepmuSciDF[i] = TotEdepmuSDF[0][i]/TotEdepmuSDF[0][nsamps-1];
	  EdepxSciDF[i] = TotEdepxSDF[0][i]/TotEdepxSDF[0][nsamps-1]; 
	  EdepmuTubeD[i] = TotEdepmuTD[0][i]/TotEdepmuTD[0][nsamps-1];
	  EdepxTubeD[i] = TotEdepxTD[0][i]/TotEdepxTD[0][nsamps-1]; 
      EdepmuSciDE[i] = TotEdepmuSDE[0][i]/TotEdepmuSDE[0][nsamps-1];
	  EdepxSciDE[i] = TotEdepxSDE[0][i]/TotEdepxSDE[0][nsamps-1];
   }


   // Colours
   hmuSciDF->SetLineColor(kBlack);
   hxSciDF->SetLineColor(kGreen-2); 
   hmuTubeD->SetLineColor(kBlack);
   hxTubeD->SetLineColor(kGreen-2);
   hmuSciDE->SetLineColor(kBlack);
   hxSciDE->SetLineColor(kGreen-2);

   hmuSciDFZ->SetLineColor(kBlack);
   hxSciDFZ->SetLineColor(kGreen-2);
   hmuTubeDZ->SetLineColor(kBlack);
   hxTubeDZ->SetLineColor(kGreen-2);
   hmuSciDEZ->SetLineColor(kBlack);
   hxSciDEZ->SetLineColor(kGreen-2);

   
   /********************************/
   /*           Plotting           */
   /********************************/

   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(3,3);
   c->cd(1);
   gPad->SetLogy();
   hmuSciDF->SetTitle("Bfield_5T_5mmAlBGO_2mm_Al: #mu-decay vs X-ray cascade: 200-mm x 200-mm 4-mm SciDF");
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
 
   c->cd(2);
   gPad->SetLogy();
   hmuTubeD->SetTitle("Bfield_5T_5mmAlBGO_2mm_Al: #mu-decay vs X-ray cascade: 50-mm round BGO");
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

   c->cd(3);
   gPad->SetLogy();
   hmuSciDE->SetTitle("Bfield_5T_5mmAlBGO_2mm_Al: #mu-decay vs X-ray cascade: 100-mm x 100-mm 200-mm SciDE");
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

   c->cd(4);
   gPad->SetLogy();
   hmuSciDFZ->SetTitle("Bfield_5T_5mmAlBGO_2mm_Al: #mu-decay vs X-ray cascade: 200-mm x 200-mm 4-mm SciDF");
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

   c->cd(5);
   gPad->SetLogy();
   hmuTubeDZ->SetTitle("Bfield_5T_5mmAlBGO_2mm_Al: #mu-decay vs X-ray cascade: 50-mm round BGO");
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
   
   c->cd(6);
   gPad->SetLogy();
   hmuSciDEZ->SetTitle("Bfield_5T_5mmAlBGO_2mm_Al: #mu-decay vs X-ray cascade: 100-mm x 100-mm 200-mm SciDE");
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
   
   c->cd(7);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu1 = new TGraph(nsamps,Ethrmu,EdepmuSciDF);
   grmu1->SetTitle("Bfield_5T_5mmAlBGO_2mm_Al: #mu-decay vs X-ray cascade: 200-mm x 200-mm 4-mm SciDF");
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
   
   c->cd(8);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu2 = new TGraph(nsamps,Ethrmu,EdepmuTubeD);
   grmu2->SetTitle("Bfield_5T_5mmAlBGO_2mm_Al: #mu-decay vs X-ray cascade: 50-mm round BGO");
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

   c->cd(9);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu3 = new TGraph(nsamps,Ethrmu,EdepmuSciDE);
   grmu3->SetTitle("Bfield_5T_5mmAlBGO_2mm_Al: #mu-decay vs X-ray cascade: 100-mm x 100-mm 200-mm SciDE");
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

   c->SaveAs("ad_3dets_smSDE_5mmAlBGO_2mm_Al_Bfield_5T_MULTI_Edep.pdf");
   c->SaveAs("ad_3dets_smSDE_5mmAlBGO_2mm_Al_Bfield_5T_MULTI_Edep.png");
   c->SaveAs("ad_3dets_smSDE_5mmAlBGO_2mm_Al_Bfield_5T_MULTI_Edep.C");


}


int main() {
   Bfield_5T_MULTI();
return 0;
}  
