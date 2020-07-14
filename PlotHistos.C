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
#include "stdio.h"
#include "stdlib.h"
#include <vector>
using namespace std;

// ROOT
#include "TAttMarker.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TCut.h"
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

void PlotHistos(){

   //Some style definitions
   //gROOT->Reset();
   //gROOT->SetStyle("Plain");
/*   gStyle->SetPaperSize(26,20);
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
*/
   
   
   
   /*********************************/
   /*         Input files           */
   /*********************************/

   const int nsamps = 101;
   const int nbins = 150;


   // Names of the files
   // X-ray cascade
   std::string filex1 = "B4_carbon_inf_sph.root";
   //std::string filex1 = "B4_plastic_inf_sph.root";
   //std::string filex2 = "B4_hydrogen_inf_sph.root";
   std::string filex2 = "B4_carbon_inf_sph_2500keV.root";
   //std::string filex4 = "QGSP_BERT_HP_B4_cal.root";
   //std::string filex5 = "QGSP_INCLXX_B4_cal.root";
/*   std::string filex1 = "B4_100ns_cal.root";
   std::string filex2 = "B4_800ns_cal.root";
   std::string filex3 = "B4_750s_cal.root";
   std::string filex4 = "B4_800s_cal.root";
   std::string filex5 = "B4_1000s_cal.root";*/

   

   // TFiles 
   TFile* fx1 = new TFile(TString(filex1));
   TFile* fx2 = new TFile(TString(filex2));
   //TFile* fx3 = new TFile(TString(filex3));
   //TFile* fx4 = new TFile(TString(filex4));
   //TFile* fx5 = new TFile(TString(filex5));
  
   
   // Histograms
   TH1F *hx1 = new TH1F("hx1","hx1",4*nbins+1,-0.01,40.0);
   TH1F *hx2 = new TH1F("hx2","hx2",4*nbins+1,-0.01,40.0);
   TH1F *hx3 = new TH1F("hx3","hx3",4*nbins,-0.01,1.5e12);
   TH1F *hx4 = new TH1F("hx4","hx4",4*nbins,-0.01,1.5e12);
   //TH1F *hx5 = new TH1F("hx5","hx5",4*nbins+1,-0.01,15.0);
   TH2F *hxc = new TH2F("hxc","hxc",4*nbins+1,-0.01,2e12,4*nbins,-0.01,40);
    
    
   // TTrees
   TTree *tx1 = (TTree*)fx1->Get("B4");
   TTree *tx2 = (TTree*)fx2->Get("B4");
   TTree *tx3 = (TTree*)fx1->Get("B4");
   TTree *tx4 = (TTree*)fx1->Get("B4");
   //TTree *tx5 = (TTree*)fx5->Get("B4");

   // Drawings
   TCut tcut1 = "Eabs > 9.9 && Eabs < 10.1 && Tgabs <= 600000000";
   TCut tcut2 = "Tgabs <= 600000000";
   tx1->Draw("Eabs>>hx1","","");
    //tx1->Draw("Eabs>>hx1",tcut);
   tx2->Draw("Eabs>>hx2","","");
   //tx1->Draw("Eabs:Tgabs>>hxc","","");
   //tx1->Draw("Eabs:Tgabs>>hxc",tcut);
   tx1->Draw("Eabs:Tgabs>>hxc",tcut1);
   tx3->Draw("Tgabs>>hx3",tcut2);
   tx4->Draw("Tgabs>>hx4",tcut1);
   //tx5->Draw("Eabs>>hx5","","");

    
    
   // Colours
   hx1->SetLineColor(kGreen-2); hx1->SetLineWidth(2);
   //hx2->SetLineColor(kCyan-3); hx2->SetLineWidth(2);
   hx2->SetLineColor(kOrange); hx2->SetLineWidth(2);
   hx3->SetLineColor(kRed); hx3->SetLineWidth(2);
   hx4->SetLineColor(kOrange); hx4->SetLineWidth(2);
   hx4->Rebin(2);
   //hx5->SetLineColor(kBlack); hx5->SetLineWidth(2);
  

   //-------------------------------------------------------------------
   //                          Plotting 
   //-------------------------------------------------------------------


   TCanvas *c = new TCanvas("c","Edep",800,600);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   hx1->SetTitle("Infinite carbon sphere");
   hx1->GetXaxis()->SetTitle("Eabs [MeV]");
   hx1->GetYaxis()->SetTitle("# of counts");
   hx1->GetYaxis()->SetTitleOffset(1.0);
   hx1->Draw();
   hx2->Draw("same");
   //hx3->Draw("same");
   //hx4->Draw("same");
   //hx5->Draw("same");

   TLegend *legendx = new TLegend(0.65,0.65,0.9,0.9);
   legendx->AddEntry(hx1,"5 MeV neutron","l");
   legendx->AddEntry(hx2,"2.5 MeV neutron","l");
   //legendx->AddEntry(hx3,"Carbon","l");
   //legendx->AddEntry(hx4,"QGSP_BERT_HP","l");
   //legendx->AddEntry(hx5,"QGSP_INCLXX","l");
/*   legendx->AddEntry(hx1,"100 ns","l");
   legendx->AddEntry(hx2,"800 ns","l");
   legendx->AddEntry(hx3,"750 s","l");
   legendx->AddEntry(hx4,"800 s","l");
   legendx->AddEntry(hx5,"1000 s","l");*/
   legendx->Draw();

   
    TCanvas *d = new TCanvas("d","Edep",800,600);
    hxc->GetXaxis()->SetTitle("gTime [ns]");
    hxc->GetYaxis()->SetTitle("Eabs [MeV]");
    hxc->Draw("colz");
    //hxc->Draw();
   
    TCanvas *e = new TCanvas("e","Edep",800,600);
    gPad->SetLogy();
    hx3->GetXaxis()->SetTitle("gTime [ns]");
    //hx3->SetMarkerStyle(3);
    //hx3->Draw("P");
    //hx4->SetMarkerStyle(3);
    //hx4->SetMarkerColor(kRed);
    //hx4->Draw("psame");
    hx3->Draw();
    hx4->Draw("same");
    TLegend *elegend = new TLegend(0.65,0.65,0.9,0.9);
    elegend->AddEntry(hx3,"gTime, all Eabs","l");
    elegend->AddEntry(hx4,"gTime, 9.9 MeV < Eabs < 10.1 MeV","l");
    elegend->Draw();
    
   //c->SaveAs("PlotsSA/A_d_5mm_w_5mm_Sci_goldcascade.pdf");

   /*
   TLine *separator = new TLine(6.5,c->GetUymin(),6.5,5e4);
   separator->SetLineColor(kGreen-2);
   separator->SetLineStyle(3);
   separator->SetLineWidth(8);
//   separator->Draw("same");

   c->SaveAs("Ordering/"+TString(cavmaterial)+"_cav_"+TString(BGOmaterial)+"_dA1_"+TString(dA1)+"mm_dL1_"+TString(dL1)+"mm_Edep_BGO1.pdf");
   c->SaveAs("Ordering/"+TString(cavmaterial)+"_cav_"+TString(BGOmaterial)+"_dA1_"+TString(dA1)+"mm_dL1_"+TString(dL1)+"mm_Edep_BGO1.png");
   c->SaveAs("Ordering/"+TString(cavmaterial)+"_cav_"+TString(BGOmaterial)+"_dA1_"+TString(dA1)+"mm_dL1_"+TString(dL1)+"mm_Edep_BGO1.C");

*/
 
//   d->SaveAs("PlotsSA/A_d_5mm_w_5mm_Sci_mudecay.pdf");
 
/* 
   TCanvas *e = new TCanvas("e","Edep",800,600);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   hmu1->SetTitle("100 #times 100 mm^2");
   hmu1->GetXaxis()->SetTitle("E [MeV]");
   hmu1->GetYaxis()->SetTitle("# of counts");
   hmu1->GetYaxis()->SetTitleOffset(1.0);
   hmu1->Draw();
   hmu2->Draw("SAME");
   hmu3->Draw("SAME");
   
   TLegend *legend3 = new TLegend(0.65,0.65,0.86,0.82);
   legend3->AddEntry(hmu1,"#muAu X-ray cascade: d = 5 mm","l");
   legend3->AddEntry(hmu2,"#muAu X-ray cascade: d = 10 mm","l");
   legend3->AddEntry(hmu3,"muAu X-ray cascade: d = 250 mm","l");
   legend3->Draw();
   
   
   TCanvas *f = new TCanvas("f","Edep",800,600);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   hmu1->SetTitle("200 #times 200 mm^2");
   hmu1->GetXaxis()->SetTitle("E [MeV]");
   hmu1->GetYaxis()->SetTitle("# of counts");
   hmu1->GetYaxis()->SetTitleOffset(1.0);
   hmu1->Draw();
   hmu2->Draw("SAME");
   hmu3->Draw("SAME");
   
   TLegend *legend4 = new TLegend(0.65,0.65,0.86,0.82);
   legend4->AddEntry(hmu1,"#muAu X-ray cascade: d = 5 mm","l");
   legend4->AddEntry(hmu2,"#muAu X-ray cascade: d = 10 mm","l");
   legend4->AddEntry(hmu3,"#muAu X-ray cascade: d = 250 mm","l");
   legend4->Draw();
   
   
   TCanvas *g = new TCanvas("g","Edep",800,600);
   gPad->SetLogy();
   gStyle->SetOptStat(0);
   hmu1->SetTitle("100 #times 100 mm^2");
   hmu1->GetXaxis()->SetTitle("E [Mev]");
   hmu1->GetYaxis()->SetTitle("# of counts");
   hmu1->GetYaxis()->SetTitleOffset(1.0);
   hmu1->Draw();
   hmu2->Draw("SAME");
   hmu3->Draw("SAME");
   
*/ 
} 
 
 int main() {
   PlotHistos();
   return 0;
}

