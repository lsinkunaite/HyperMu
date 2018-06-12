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

void bubble2(){

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
   // With 0-mm Al layer
   std::string filemu1 = "bubble_Nevts_SciSphere_SciD_1e6mudecay1.root";
   std::string filemu2 = "bubble_Nevts_SciSphere_SciD_1e6mudecay2.root";
   std::string filemu3 = "bubble_Nevts_SciSphere_SciD_1e6mudecay3.root";
   std::string filemu5 = "bubble_Nevts_SciSphere_SciD_1e6mudecay5.root";
   std::string filemu10 = "bubble_Nevts_SciSphere_SciD_1e6mudecay10.root";
   std::string filemu20 = "bubble_Nevts_SciSphere_SciD_1e6mudecay20.root";
   std::string filex1 = "bubble_Nevts_SciSphere_SciD_1e6goldcascade1.root";
   std::string filex2 = "bubble_Nevts_SciSphere_SciD_1e6goldcascade2.root";
   std::string filex3 = "bubble_Nevts_SciSphere_SciD_1e6goldcascade3.root";
   std::string filex5 = "bubble_Nevts_SciSphere_SciD_1e6goldcascade5.root";
   std::string filex10 = "bubble_Nevts_SciSphere_SciD_1e6goldcascade10.root";
   std::string filex20 = "bubble_Nevts_SciSphere_SciD_1e6goldcascade20.root";
   // With a 3-mm Al layer
   std::string fileAlmu1 = "bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay1.root";
   std::string fileAlmu2 = "bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay2.root";
   std::string fileAlmu3 = "bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay3.root";
   std::string fileAlmu5 = "bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay5.root";
   std::string fileAlmu10 = "bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay10.root";
   std::string fileAlmu20 = "bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay20.root";
   std::string fileAlx1 = "bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade1.root";
   std::string fileAlx2 = "bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade2.root";
   std::string fileAlx3 = "bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade3.root";
   std::string fileAlx5 = "bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade5.root";
   std::string fileAlx10 = "bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade10.root";
   std::string fileAlx20 = "bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade20.root"; 


   /*********************************/
   /*           Analysis            */
   /*********************************/

   const int nbins = 150;
  
   // 0-mm Al layer 
   TFile* fmu1 = new TFile(TString(filemu1));
   TFile* fmu2 = new TFile(TString(filemu2));
   TFile* fmu3 = new TFile(TString(filemu3));
   TFile* fmu5 = new TFile(TString(filemu5));
   TFile* fmu10 = new TFile(TString(filemu10));
   TFile* fmu20 = new TFile(TString(filemu20));
   TFile* fx1 = new TFile(TString(filex1));
   TFile* fx2 = new TFile(TString(filex2));
   TFile* fx3 = new TFile(TString(filex3));
   TFile* fx5 = new TFile(TString(filex5));
   TFile* fx10 = new TFile(TString(filex10));
   TFile* fx20 = new TFile(TString(filex20));

   // 3-mm Al layer
   TFile* fAlmu1 = new TFile(TString(fileAlmu1));
   TFile* fAlmu2 = new TFile(TString(fileAlmu2));
   TFile* fAlmu3 = new TFile(TString(fileAlmu3));
   TFile* fAlmu5 = new TFile(TString(fileAlmu5));
   TFile* fAlmu10 = new TFile(TString(fileAlmu10));
   TFile* fAlmu20 = new TFile(TString(fileAlmu20));
   TFile* fAlx1 = new TFile(TString(fileAlx1));
   TFile* fAlx2 = new TFile(TString(fileAlx2));
   TFile* fAlx3 = new TFile(TString(fileAlx3));
   TFile* fAlx5 = new TFile(TString(fileAlx5));
   TFile* fAlx10 = new TFile(TString(fileAlx10));
   TFile* fAlx20 = new TFile(TString(fileAlx20));


   // 0-mm Al layer
   TH1F *hmu1 = new TH1F("hmu1","Edep",nbins,0.01,1.5);
   TH1F *hmu2 = new TH1F("hmu2","Edep",nbins,0.01,2.3);
   TH1F *hmu3 = new TH1F("hmu3","Edep",nbins,0.01,3.2);
   TH1F *hmu5 = new TH1F("hmu5","Edep",nbins,0.01,4.8);
   TH1F *hmu10 = new TH1F("hmu10","Edep",nbins,0.01,9);
   TH1F *hmu20 = new TH1F("hmu20","Edep",nbins,0.01,17);
   TH1F *hx1 = new TH1F("hx1","Edep",nbins,0.01,1.8);
   TH1F *hx2 = new TH1F("hx2","Edep",nbins,0.01,2.6);
   TH1F *hx3 = new TH1F("hx3","Edep",nbins,0.01,2.6);
   TH1F *hx5 = new TH1F("hx5","Edep",nbins,0.01,4.3);
   TH1F *hx10 = new TH1F("hx10","Edep",nbins,0.01,6.2);
   TH1F *hx20 = new TH1F("hx20","Edep",nbins,0.01,8.8);
   // 0-mm Al layer [norm.]
   TH1F *hmu1n = new TH1F("hmu1n","Edep",nbins,0.01,1.5);
   TH1F *hmu2n = new TH1F("hmu2n","Edep",nbins,0.01,2.4);
   TH1F *hmu3n = new TH1F("hmu3n","Edep",nbins,0.01,3.1);
   TH1F *hmu5n = new TH1F("hmu5n","Edep",nbins,0.01,5.2);
   TH1F *hmu10n = new TH1F("hmu10n","Edep",nbins,0.01,9.2);
   TH1F *hmu20n = new TH1F("hmu20n","Edep",nbins,0.01,15);
   TH1F *hx1n = new TH1F("hx1n","Edep",nbins,0.01,1.5);
   TH1F *hx2n = new TH1F("hx2n","Edep",nbins,0.01,2.4);
   TH1F *hx3n = new TH1F("hx3n","Edep",nbins,0.01,3.1);
   TH1F *hx5n = new TH1F("hx5n","Edep",nbins,0.01,5.2);
   TH1F *hx10n = new TH1F("hx10n","Edep",nbins,0.01,9.2);
   TH1F *hx20n = new TH1F("hx20n","Edep",nbins,0.01,15);

   // 3-mm Al layer
   TH1F *hAlmu1 = new TH1F("hAlmu1","Edep",nbins,0.01,1.5);
   TH1F *hAlmu2 = new TH1F("hAlmu2","Edep",nbins,0.01,2.3);
   TH1F *hAlmu3 = new TH1F("hAlmu3","Edep",nbins,0.01,3.2);
   TH1F *hAlmu5 = new TH1F("hAlmu5","Edep",nbins,0.01,4.8);
   TH1F *hAlmu10 = new TH1F("hAlmu10","Edep",nbins,0.01,9);
   TH1F *hAlmu20 = new TH1F("hAlmu20","Edep",nbins,0.01,17);
   TH1F *hAlx1 = new TH1F("hAlx1","Edep",nbins,0.01,1.8);
   TH1F *hAlx2 = new TH1F("hAlx2","Edep",nbins,0.01,2.6);
   TH1F *hAlx3 = new TH1F("hAlx3","Edep",nbins,0.01,2.2);
   TH1F *hAlx5 = new TH1F("hAlx5","Edep",nbins,0.01,4.3);
   TH1F *hAlx10 = new TH1F("hAlx10","Edep",nbins,0.01,6.2);
   TH1F *hAlx20 = new TH1F("hAlx20","Edep",nbins,0.01,8.8);
   // 3-mm Al layer [norm.]
   TH1F *hAlmu1n = new TH1F("hAlmu1n","Edep",nbins,0.01,1.8);
   TH1F *hAlmu2n = new TH1F("hAlmu2n","Edep",nbins,0.01,2.6);
   TH1F *hAlmu3n = new TH1F("hAlmu3n","Edep",nbins,0.01,3.8);
   TH1F *hAlmu5n = new TH1F("hAlmu5n","Edep",nbins,0.01,5.4);
   TH1F *hAlmu10n = new TH1F("hAlmu10n","Edep",nbins,0.01,9);
   TH1F *hAlmu20n = new TH1F("hAlmu20n","Edep",nbins,0.01,15);
   TH1F *hAlx1n = new TH1F("hAlx1n","Edep",nbins,0.01,1.8);
   TH1F *hAlx2n = new TH1F("hAlx2n","Edep",nbins,0.01,2.6);
   TH1F *hAlx3n = new TH1F("hAlx3n","Edep",nbins,0.01,3.8);
   TH1F *hAlx5n = new TH1F("hAlx5n","Edep",nbins,0.01,5.4);
   TH1F *hAlx10n = new TH1F("hAlx10n","Edep",nbins,0.01,9);
   TH1F *hAlx20n = new TH1F("hAlx20n","Edep",nbins,0.01,15);

   // 0-mm Al layer
   TTree *tmu1 = (TTree*)fmu1->Get("Detector/SciDet");
   TTree *tmu2 = (TTree*)fmu2->Get("Detector/SciDet");
   TTree *tmu3 = (TTree*)fmu3->Get("Detector/SciDet");
   TTree *tmu5 = (TTree*)fmu5->Get("Detector/SciDet");
   TTree *tmu10 = (TTree*)fmu10->Get("Detector/SciDet");
   TTree *tmu20 = (TTree*)fmu20->Get("Detector/SciDet");
   TTree *tx1 = (TTree*)fx1->Get("Detector/SciDet");
   TTree *tx2 = (TTree*)fx2->Get("Detector/SciDet");
   TTree *tx3 = (TTree*)fx3->Get("Detector/SciDet");
   TTree *tx5 = (TTree*)fx5->Get("Detector/SciDet");
   TTree *tx10 = (TTree*)fx10->Get("Detector/SciDet");
   TTree *tx20 = (TTree*)fx20->Get("Detector/SciDet");

   // 3-mm Al layer
   TTree *tAlmu1 = (TTree*)fAlmu1->Get("Detector/SciDet");
   TTree *tAlmu2 = (TTree*)fAlmu2->Get("Detector/SciDet");
   TTree *tAlmu3 = (TTree*)fAlmu3->Get("Detector/SciDet");
   TTree *tAlmu5 = (TTree*)fAlmu5->Get("Detector/SciDet");
   TTree *tAlmu10 = (TTree*)fAlmu10->Get("Detector/SciDet");
   TTree *tAlmu20 = (TTree*)fAlmu20->Get("Detector/SciDet");
   TTree *tAlx1 = (TTree*)fAlx1->Get("Detector/SciDet");
   TTree *tAlx2 = (TTree*)fAlx2->Get("Detector/SciDet");
   TTree *tAlx3 = (TTree*)fAlx3->Get("Detector/SciDet");
   TTree *tAlx5 = (TTree*)fAlx5->Get("Detector/SciDet");
   TTree *tAlx10 = (TTree*)fAlx10->Get("Detector/SciDet");
   TTree *tAlx20 = (TTree*)fAlx20->Get("Detector/SciDet"); 


   // 0-mm Al layer   
   tmu1->Draw("Edep>>hmu1","","");
   tmu2->Draw("Edep>>hmu2","","");
   tmu3->Draw("Edep>>hmu3","","");
   tmu5->Draw("Edep>>hmu5","","");
   tmu10->Draw("Edep>>hmu10","","");
   tmu20->Draw("Edep>>hmu20","","");
   tx1->Draw("Edep>>hx1","","");
   tx2->Draw("Edep>>hx2","","");
   tx3->Draw("Edep>>hx3","","");
   tx5->Draw("Edep>>hx5","","");
   tx10->Draw("Edep>>hx10","","");
   tx20->Draw("Edep>>hx20","","");
   // 0-mm Al layer [norm.]
   tmu1->Draw("Edep>>hmu1n","","");
   tmu2->Draw("Edep>>hmu2n","","");
   tmu3->Draw("Edep>>hmu3n","","");
   tmu5->Draw("Edep>>hmu5n","","");
   tmu10->Draw("Edep>>hmu10n","","");
   tmu20->Draw("Edep>>hmu20n","","");
   tx1->Draw("Edep>>hx1n","","");
   tx2->Draw("Edep>>hx2n","","");
   tx3->Draw("Edep>>hx3n","","");
   tx5->Draw("Edep>>hx5n","","");
   tx10->Draw("Edep>>hx10n","","");
   tx20->Draw("Edep>>hx20n","","");

   // 3-mm Al layer
   tAlmu1->Draw("Edep>>hAlmu1","","");
   tAlmu2->Draw("Edep>>hAlmu2","","");
   tAlmu3->Draw("Edep>>hAlmu3","","");
   tAlmu5->Draw("Edep>>hAlmu5","","");
   tAlmu10->Draw("Edep>>hAlmu10","","");
   tAlmu20->Draw("Edep>>hAlmu20","","");
   tAlx1->Draw("Edep>>hAlx1","","");
   tAlx2->Draw("Edep>>hAlx2","","");
   tAlx3->Draw("Edep>>hAlx3","","");
   tAlx5->Draw("Edep>>hAlx5","","");
   tAlx10->Draw("Edep>>hAlx10","","");
   tAlx20->Draw("Edep>>hAlx20","","");
   // 3-mm Al layer [norm.]
   tAlmu1->Draw("Edep>>hAlmu1n","","");
   tAlmu2->Draw("Edep>>hAlmu2n","","");
   tAlmu3->Draw("Edep>>hAlmu3n","","");
   tAlmu5->Draw("Edep>>hAlmu5n","","");
   tAlmu10->Draw("Edep>>hAlmu10n","","");
   tAlmu20->Draw("Edep>>hAlmu20n","","");
   tAlx1->Draw("Edep>>hAlx1n","","");
   tAlx2->Draw("Edep>>hAlx2n","","");
   tAlx3->Draw("Edep>>hAlx3n","","");
   tAlx5->Draw("Edep>>hAlx5n","","");
   tAlx10->Draw("Edep>>hAlx10n","","");
   tAlx20->Draw("Edep>>hAlx20n","","");

   // 0-mm Al layer
   hmu1->SetLineColor(kBlack);
   hmu2->SetLineColor(kBlack);
   hmu3->SetLineColor(kBlack);
   hmu5->SetLineColor(kBlack);
   hmu10->SetLineColor(kBlack);
   hmu20->SetLineColor(kBlack);
   hx1->SetLineColor(kBlack);
   hx2->SetLineColor(kBlack);
   hx3->SetLineColor(kBlack);
   hx5->SetLineColor(kBlack);
   hx10->SetLineColor(kBlack);
   hx20->SetLineColor(kBlack);
   // 0-mm Al layer [norm.]
   hmu1n->SetLineColor(kBlack);
   hmu2n->SetLineColor(kBlack);
   hmu3n->SetLineColor(kBlack);
   hmu5n->SetLineColor(kBlack);
   hmu10n->SetLineColor(kBlack);
   hmu20n->SetLineColor(kBlack);
   hx1n->SetLineColor(kRed);
   hx2n->SetLineColor(kRed);
   hx3n->SetLineColor(kRed);
   hx5n->SetLineColor(kRed);
   hx10n->SetLineColor(kRed);
   hx20n->SetLineColor(kRed);

   // 3-mm Al layer
   hAlmu1->SetLineColor(kRed);
   hAlmu2->SetLineColor(kRed);
   hAlmu3->SetLineColor(kRed);
   hAlmu5->SetLineColor(kRed);
   hAlmu10->SetLineColor(kRed);
   hAlmu20->SetLineColor(kRed);
   hAlx1->SetLineColor(kRed);
   hAlx2->SetLineColor(kRed);
   hAlx3->SetLineColor(kRed);
   hAlx5->SetLineColor(kRed);
   hAlx10->SetLineColor(kRed);
   hAlx20->SetLineColor(kRed);
   // 3-mm Al layer [norm.]
   hAlmu1n->SetLineColor(kBlack);
   hAlmu2n->SetLineColor(kBlack);
   hAlmu3n->SetLineColor(kBlack);
   hAlmu5n->SetLineColor(kBlack);
   hAlmu10n->SetLineColor(kBlack);
   hAlmu20n->SetLineColor(kBlack);
   hAlx1n->SetLineColor(kRed);
   hAlx2n->SetLineColor(kRed);
   hAlx3n->SetLineColor(kRed);
   hAlx5n->SetLineColor(kRed);
   hAlx10n->SetLineColor(kRed);
   hAlx20n->SetLineColor(kRed);


   /********************************/
   /*           Plotting           */
   /********************************/

   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(3,2);
   c->cd(1);
   gPad->SetLogy();
   hmu1->SetTitle("Mu-decay: 1-mm SciD vs 1-mm SciD + 3-mm Al");
   hmu1->GetXaxis()->SetTitle("Edep [MeV]");
   hmu1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu1->GetYaxis()->SetTitleOffset(2.0);
   hmu1->Draw();
   c->Update();
   TPaveStats *stmu1 = (TPaveStats*)hmu1->GetListOfFunctions()->FindObject("stats");
   stmu1->SetY1NDC(0.6); stmu1->SetY2NDC(0.75);
   hAlmu1->Draw("sames");
   c->Update();
   TPaveStats *stAlmu1 = (TPaveStats*)hAlmu1->GetListOfFunctions()->FindObject("stats");
   stAlmu1->SetTextColor(kRed);
   stAlmu1->Draw();

   c->cd(2);
   gPad->SetLogy();
   hmu2->SetTitle("Mu-decay: 2-mm SciD vs 2-mm SciD + 3-mm Al");
   hmu2->GetXaxis()->SetTitle("Edep [MeV]");
   hmu2->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu2->GetYaxis()->SetTitleOffset(2.0);
   hmu2->Draw();
   c->Update();
   TPaveStats *stmu2 = (TPaveStats*)hmu2->GetListOfFunctions()->FindObject("stats");
   stmu2->SetY1NDC(0.6); stmu2->SetY2NDC(0.75);
   hAlmu2->Draw("sames");
   c->Update();
   TPaveStats *stAlmu2 = (TPaveStats*)hAlmu2->GetListOfFunctions()->FindObject("stats");
   stAlmu2->SetTextColor(kRed);
   stAlmu2->Draw();

   c->cd(3);
   gPad->SetLogy();
   hmu3->SetTitle("Mu-decay: 3-mm SciD vs 3-mm SciD + 3-mm Al");
   hmu3->GetXaxis()->SetTitle("Edep [MeV]");
   hmu3->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu3->GetYaxis()->SetTitleOffset(2.0);
   hmu3->Draw();
   c->Update();
   TPaveStats *stmu3 = (TPaveStats*)hmu3->GetListOfFunctions()->FindObject("stats");
   stmu3->SetY1NDC(0.6); stmu3->SetY2NDC(0.75);
   hAlmu3->Draw("sames");
   c->Update();
   TPaveStats *stAlmu3 = (TPaveStats*)hAlmu3->GetListOfFunctions()->FindObject("stats");
   stAlmu3->SetTextColor(kRed);
   stAlmu3->Draw();

   c->cd(4);
   gPad->SetLogy();
   hmu5->SetTitle("Mu-decay: 5-mm SciD vs 5-mm SciD + 3-mm Al");
   hmu5->GetXaxis()->SetTitle("Edep [MeV]");
   hmu5->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu5->GetYaxis()->SetTitleOffset(2.0);
   hmu5->Draw();
   c->Update();
   TPaveStats *stmu5 = (TPaveStats*)hmu5->GetListOfFunctions()->FindObject("stats");
   stmu5->SetY1NDC(0.6); stmu5->SetY2NDC(0.75);
   hAlmu5->Draw("sames");
   c->Update();
   TPaveStats *stAlmu5 = (TPaveStats*)hAlmu5->GetListOfFunctions()->FindObject("stats");
   stAlmu5->SetTextColor(kRed);
   stAlmu5->Draw();

   c->cd(5);
   gPad->SetLogy();
   hmu10->SetTitle("Mu-decay: 10-mm SciD vs 10-mm SciD + 3-mm Al");
   hmu10->GetXaxis()->SetTitle("Edep [MeV]");
   hmu10->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu10->GetYaxis()->SetTitleOffset(2.0);
   hmu10->Draw();
   c->Update();
   TPaveStats *stmu10 = (TPaveStats*)hmu10->GetListOfFunctions()->FindObject("stats");
   stmu10->SetY1NDC(0.6); stmu10->SetY2NDC(0.75);
   hAlmu10->Draw("sames");
   c->Update();
   TPaveStats *stAlmu10 = (TPaveStats*)hAlmu10->GetListOfFunctions()->FindObject("stats");
   stAlmu10->SetTextColor(kRed);
   stAlmu10->Draw();

   c->cd(6);
   gPad->SetLogy();
   hmu20->SetTitle("Mu-decay: 20-mm SciD vs 20-mm SciD + 3-mm Al");
   hmu20->GetXaxis()->SetTitle("Edep [MeV]");
   hmu20->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu20->GetYaxis()->SetTitleOffset(2.0);
   hmu20->Draw();
   c->Update();
   TPaveStats *stmu20 = (TPaveStats*)hmu20->GetListOfFunctions()->FindObject("stats");
   stmu20->SetY1NDC(0.6); stmu20->SetY2NDC(0.75);
   hAlmu20->Draw("sames");
   c->Update();
   TPaveStats *stAlmu20 = (TPaveStats*)hAlmu20->GetListOfFunctions()->FindObject("stats");
   stAlmu20->SetTextColor(kRed);
   stAlmu20->Draw();

   c->SaveAs("BubbleTest2_mudecay_p1.pdf");
   c->SaveAs("BubbleTest2_mudecay_p1.png");
   c->SaveAs("BubbleTest2_mudecay_p1.C");



   TCanvas *d = new TCanvas("d","Edep",800,600);
   d->Divide(3,2);
   d->cd(1);
   gPad->SetLogy();
   hx1->SetTitle("X-ray cascade: 1-mm SciD vs 1-mm SciD + 3-mm Al");
   hx1->GetXaxis()->SetTitle("Edep [MeV]");
   hx1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx1->GetYaxis()->SetTitleOffset(2.0);
   hx1->Draw();
   d->Update();
   TPaveStats *stx1 = (TPaveStats*)hx1->GetListOfFunctions()->FindObject("stats");
   stx1->SetY1NDC(0.6); stx1->SetY2NDC(0.75);
   hAlx1->Draw("sames");
   d->Update();
   TPaveStats *stAlx1 = (TPaveStats*)hAlx1->GetListOfFunctions()->FindObject("stats");
   stAlx1->SetTextColor(kRed);
   stAlx1->Draw();

   d->cd(2);
   gPad->SetLogy();
   hx2->SetTitle("X-ray cascade: 2-mm SciD vs 2-mm SciD + 3-mm Al");
   hx2->GetXaxis()->SetTitle("Edep [MeV]");
   hx2->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx2->GetYaxis()->SetTitleOffset(2.0);
   hx2->Draw();
   d->Update();
   TPaveStats *stx2 = (TPaveStats*)hx2->GetListOfFunctions()->FindObject("stats");
   stx2->SetY1NDC(0.6); stx2->SetY2NDC(0.75);
   hAlx2->Draw("sames");
   d->Update();
   TPaveStats *stAlx2 = (TPaveStats*)hAlx2->GetListOfFunctions()->FindObject("stats");
   stAlx2->SetTextColor(kRed);
   stAlx2->Draw();

   d->cd(3);
   gPad->SetLogy();
   hx3->SetTitle("X-ray cascade: 3-mm SciD vs 3-mm SciD + 3-mm Al");
   hx3->GetXaxis()->SetTitle("Edep [MeV]");
   hx3->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx3->GetYaxis()->SetTitleOffset(2.0);
   hx3->Draw();
   d->Update();
   TPaveStats *stx3 = (TPaveStats*)hx3->GetListOfFunctions()->FindObject("stats");
   stx3->SetY1NDC(0.6); stx3->SetY2NDC(0.75);
   hAlx3->Draw("sames");
   d->Update();
   TPaveStats *stAlx3 = (TPaveStats*)hAlx3->GetListOfFunctions()->FindObject("stats");
   stAlx3->SetTextColor(kRed);
   stAlx3->Draw();

   d->cd(4);
   gPad->SetLogy();
   hx5->SetTitle("X-ray cascade: 5-mm SciD vs 5-mm SciD + 3-mm Al");
   hx5->GetXaxis()->SetTitle("Edep [MeV]");
   hx5->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx5->GetYaxis()->SetTitleOffset(2.0);
   hx5->Draw();
   d->Update();
   TPaveStats *stx5 = (TPaveStats*)hx5->GetListOfFunctions()->FindObject("stats");
   stx5->SetY1NDC(0.6); stx5->SetY2NDC(0.75);
   hAlx5->Draw("sames");
   d->Update();
   TPaveStats *stAlx5 = (TPaveStats*)hAlx5->GetListOfFunctions()->FindObject("stats");
   stAlx5->SetTextColor(kRed);
   stAlx5->Draw();

   d->cd(5);
   gPad->SetLogy();
   hx10->SetTitle("X-ray cascade: 10-mm SciD vs 10-mm SciD + 3-mm Al");
   hx10->GetXaxis()->SetTitle("Edep [MeV]");
   hx10->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx10->GetYaxis()->SetTitleOffset(2.0);
   hx10->Draw();
   d->Update();
   TPaveStats *stx10 = (TPaveStats*)hx10->GetListOfFunctions()->FindObject("stats");
   stx10->SetY1NDC(0.6); stx10->SetY2NDC(0.75);
   hAlx10->Draw("sames");
   d->Update();
   TPaveStats *stAlx10 = (TPaveStats*)hAlx10->GetListOfFunctions()->FindObject("stats");
   stAlx10->SetTextColor(kRed);
   stAlx10->Draw();

   d->cd(6);
   gPad->SetLogy();
   hx20->SetTitle("X-ray cascade: 20-mm SciD vs 20-mm SciD + 3-mm Al");
   hx20->GetXaxis()->SetTitle("Edep [MeV]");
   hx20->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx20->GetYaxis()->SetTitleOffset(2.0);
   hx20->Draw();
   d->Update();
   TPaveStats *stx20 = (TPaveStats*)hx20->GetListOfFunctions()->FindObject("stats");
   stx20->SetY1NDC(0.6); stx20->SetY2NDC(0.75);
   hAlx20->Draw("sames");
   d->Update();
   TPaveStats *stAlx20 = (TPaveStats*)hAlx20->GetListOfFunctions()->FindObject("stats");
   stAlx20->SetTextColor(kRed);
   stAlx20->Draw();

   d->SaveAs("BubbleTest2_goldcascade_p1.pdf");
   d->SaveAs("BubbleTest2_goldcascade_p1.png");
   d->SaveAs("BubbleTest2_goldcascade_p1.C");



   TCanvas *e = new TCanvas("e","Edep",800,600);
   e->Divide(3,2);
   e->cd(1);
   gPad->SetLogy();
   hmu1n->SetTitle("Mu-decay vs X-ray cascade: 1-mm SciD");
   hmu1n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu1n->GetYaxis()->SetTitleOffset(2.0);
   hmu1n->Draw();
   e->Update();
   TPaveStats *stmu1n = (TPaveStats*)hmu1n->GetListOfFunctions()->FindObject("stats");
   stmu1n->SetY1NDC(0.6); stmu1n->SetY2NDC(0.75);
   hx1n->Draw("sames");
   e->Update();
   TPaveStats *stx1n = (TPaveStats*)hx1n->GetListOfFunctions()->FindObject("stats");
   stx1n->SetTextColor(kRed);
   stx1n->Draw();
   
   e->cd(2);
   gPad->SetLogy();
   hmu2n->SetTitle("Mu-decay vs X-ray cascade: 2-mm SciD");
   hmu2n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu2n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu2n->GetYaxis()->SetTitleOffset(2.0);
   hmu2n->Draw();
   e->Update();
   TPaveStats *stmu2n = (TPaveStats*)hmu2n->GetListOfFunctions()->FindObject("stats");
   stmu2n->SetY1NDC(0.6); stmu2n->SetY2NDC(0.75);
   hx2n->Draw("sames");
   e->Update();
   TPaveStats *stx2n = (TPaveStats*)hx2n->GetListOfFunctions()->FindObject("stats");
   stx2n->SetTextColor(kRed);
   stx2n->Draw();

   e->cd(3);
   gPad->SetLogy();
   hmu3n->SetTitle("Mu-decay vs X-ray cascade: 3-mm SciD");
   hmu3n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu3n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu3n->GetYaxis()->SetTitleOffset(2.0);
   hmu3n->Draw();
   e->Update();
   TPaveStats *stmu3n = (TPaveStats*)hmu3n->GetListOfFunctions()->FindObject("stats");
   stmu3n->SetY1NDC(0.6); stmu3n->SetY2NDC(0.75);
   hx3n->Draw("sames");
   e->Update();
   TPaveStats *stx3n = (TPaveStats*)hx3n->GetListOfFunctions()->FindObject("stats");
   stx3n->SetTextColor(kRed);
   stx3n->Draw();

   e->cd(4);
   gPad->SetLogy();
   hmu5n->SetTitle("Mu-decay vs X-ray cascade: 5-mm SciD");
   hmu5n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu5n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu5n->GetYaxis()->SetTitleOffset(2.0);
   hmu5n->Draw();
   e->Update();
   TPaveStats *stmu5n = (TPaveStats*)hmu5n->GetListOfFunctions()->FindObject("stats");
   stmu5n->SetY1NDC(0.6); stmu5n->SetY2NDC(0.75);
   hx5n->Draw("sames");
   e->Update();
   TPaveStats *stx5n = (TPaveStats*)hx5n->GetListOfFunctions()->FindObject("stats");
   stx5n->SetTextColor(kRed);
   stx5n->Draw();

   e->cd(5);
   gPad->SetLogy();
   hmu10n->SetTitle("Mu-decay vs X-ray cascade: 10-mm SciD");
   hmu10n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu10n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu10n->GetYaxis()->SetTitleOffset(2.0);
   hmu10n->Draw();
   e->Update();
   TPaveStats *stmu10n = (TPaveStats*)hmu10n->GetListOfFunctions()->FindObject("stats");
   stmu10n->SetY1NDC(0.6); stmu10n->SetY2NDC(0.75);
   hx10n->Draw("sames");
   e->Update();
   TPaveStats *stx10n = (TPaveStats*)hx10n->GetListOfFunctions()->FindObject("stats");
   stx10n->SetTextColor(kRed);
   stx10n->Draw();

   e->cd(6);
   gPad->SetLogy();
   hmu20n->SetTitle("Mu-decay vs X-ray cascade: 20-mm SciD");
   hmu20n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu20n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu20n->GetYaxis()->SetTitleOffset(2.0);
   hmu20n->Draw();
   e->Update();
   TPaveStats *stmu20n = (TPaveStats*)hmu20n->GetListOfFunctions()->FindObject("stats");
   stmu20n->SetY1NDC(0.6); stmu20n->SetY2NDC(0.75);
   hx20n->Draw("sames");
   e->Update();
   TPaveStats *stx20n = (TPaveStats*)hx20n->GetListOfFunctions()->FindObject("stats");
   stx20n->SetTextColor(kRed);
   stx20n->Draw();

   e->SaveAs("BubbleTest2_muX_p2.pdf");
   e->SaveAs("BubbleTest2_muX_p2.png");
   e->SaveAs("BubbleTest2_muX_p2.C");



   TCanvas *f = new TCanvas("f","Edep",800,600);
   f->Divide(3,2);
   f->cd(1);
   gPad->SetLogy();
   hAlmu1n->SetTitle("Mu-decay vs X-ray cascade: 1-mm SciD + 3-mm Al");
   hAlmu1n->GetXaxis()->SetTitle("Edep [MeV]");
   hAlmu1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hAlmu1n->GetYaxis()->SetTitleOffset(2.0);
   hAlmu1n->Draw();
   f->Update();
   TPaveStats *stAlmu1n = (TPaveStats*)hAlmu1n->GetListOfFunctions()->FindObject("stats");
   stAlmu1n->SetY1NDC(0.6); stAlmu1n->SetY2NDC(0.75);
   hAlx1n->Draw("sames");
   f->Update();
   TPaveStats *stAlx1n = (TPaveStats*)hAlx1n->GetListOfFunctions()->FindObject("stats");
   stAlx1n->SetTextColor(kRed);
   stAlx1n->Draw();

   f->cd(2);
   gPad->SetLogy();
   hAlmu2n->SetTitle("Mu-decay vs X-ray cascade: 2-mm SciD + 3-mm Al");
   hAlmu2n->GetXaxis()->SetTitle("Edep [MeV]");
   hAlmu2n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hAlmu2n->GetYaxis()->SetTitleOffset(2.0);
   hAlmu2n->Draw();
   f->Update();
   TPaveStats *stAlmu2n = (TPaveStats*)hAlmu2n->GetListOfFunctions()->FindObject("stats");
   stAlmu2n->SetY1NDC(0.6); stAlmu2n->SetY2NDC(0.75);
   hAlx2n->Draw("sames");
   f->Update();
   TPaveStats *stAlx2n = (TPaveStats*)hAlx2n->GetListOfFunctions()->FindObject("stats");
   stAlx2n->SetTextColor(kRed);
   stAlx2n->Draw();

   f->cd(3);
   gPad->SetLogy();
   hAlmu3n->SetTitle("Mu-decay vs X-ray cascade: 3-mm SciD + 3-mm Al");
   hAlmu3n->GetXaxis()->SetTitle("Edep [MeV]");
   hAlmu3n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hAlmu3n->GetYaxis()->SetTitleOffset(2.0);
   hAlmu3n->Draw();
   f->Update();
   TPaveStats *stAlmu3n = (TPaveStats*)hAlmu3n->GetListOfFunctions()->FindObject("stats");
   stAlmu3n->SetY1NDC(0.6); stAlmu3n->SetY2NDC(0.75);
   hAlx3n->Draw("sames");
   f->Update();
   TPaveStats *stAlx3n = (TPaveStats*)hAlx3n->GetListOfFunctions()->FindObject("stats");
   stAlx3n->SetTextColor(kRed);
   stAlx3n->Draw();

   f->cd(4);
   gPad->SetLogy();
   hAlmu5n->SetTitle("Mu-decay vs X-ray cascade: 5-mm SciD + 3-mm Al");
   hAlmu5n->GetXaxis()->SetTitle("Edep [MeV]");
   hAlmu5n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hAlmu5n->GetYaxis()->SetTitleOffset(2.0);
   hAlmu5n->Draw();
   f->Update();
   TPaveStats *stAlmu5n = (TPaveStats*)hAlmu5n->GetListOfFunctions()->FindObject("stats");
   stAlmu5n->SetY1NDC(0.6); stAlmu5n->SetY2NDC(0.75);
   hAlx5n->Draw("sames");
   f->Update();
   TPaveStats *stAlx5n = (TPaveStats*)hAlx5n->GetListOfFunctions()->FindObject("stats");
   stAlx5n->SetTextColor(kRed);
   stAlx5n->Draw();   

   f->cd(5);
   gPad->SetLogy();
   hAlmu10n->SetTitle("Mu-decay vs X-ray cascade: 10-mm SciD + 3-mm Al");
   hAlmu10n->GetXaxis()->SetTitle("Edep [MeV]");
   hAlmu10n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hAlmu10n->GetYaxis()->SetTitleOffset(2.0);
   hAlmu10n->Draw();
   f->Update();
   TPaveStats *stAlmu10n = (TPaveStats*)hAlmu10n->GetListOfFunctions()->FindObject("stats");
   stAlmu10n->SetY1NDC(0.6); stAlmu10n->SetY2NDC(0.75);
   hAlx10n->Draw("sames");
   f->Update();
   TPaveStats *stAlx10n = (TPaveStats*)hAlx10n->GetListOfFunctions()->FindObject("stats");
   stAlx10n->SetTextColor(kRed);
   stAlx10n->Draw();

   f->cd(6);
   gPad->SetLogy();
   hAlmu20n->SetTitle("Mu-decay vs X-ray cascade: 20-mm SciD + 3-mm Al");
   hAlmu20n->GetXaxis()->SetTitle("Edep [MeV]");
   hAlmu20n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hAlmu20n->GetYaxis()->SetTitleOffset(2.0);
   hAlmu20n->Draw();
   f->Update();
   TPaveStats *stAlmu20n = (TPaveStats*)hAlmu20n->GetListOfFunctions()->FindObject("stats");
   stAlmu20n->SetY1NDC(0.6); stAlmu20n->SetY2NDC(0.75);
   hAlx20n->Draw("sames");
   f->Update();
   TPaveStats *stAlx20n = (TPaveStats*)hAlx20n->GetListOfFunctions()->FindObject("stats");
   stAlx20n->SetTextColor(kRed);
   stAlx20n->Draw();

   f->SaveAs("BubbleTest2_Al_muX_p2.pdf");
   f->SaveAs("BubbleTest2_Al_muX_p2.png");
   f->SaveAs("BubbleTest2_Al_muX_p2.C");
 
/*

   TCanvas *g = new TCanvas("g","Edep",800,600);
   g->Divide(3,2);
   g->cd(1);
   hmu1n->SetTitle("Mu-decay vs X-ray cascade: 1-mm SciD");
   hmu1n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu1n->GetYaxis()->SetTitleOffset(2.0);
   hmu1n->Draw();
   g->Update();
   TPaveStats *stmu1N = (TPaveStats*)hmu1n->GetListOfFunctionss()->FindObject("stats");
   
*/









}


int main() {
   bubble2();
   return 0;
}
