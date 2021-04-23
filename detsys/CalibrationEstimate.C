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
#include "TF1.h"
#include "TF2.h"
#include "TF3.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
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

void CalibrationEstimate(){

   //Some style definitions
   //gROOT->Reset();
   //gROOT->SetStyle("Plain");
   gStyle->SetPaperSize(26,20);
   gStyle->SetOptStat(1);
   gStyle->SetTitleXOffset(1.15);
   gStyle->SetTitleYOffset(1.15);
   gStyle->SetTitleBorderSize(0);
   //gStyle->SetLegendBorderSize(0.1);
   gStyle->SetPadBottomMargin(0.12);
   gStyle->SetPadLeftMargin(0.10);
   gStyle->SetPadTopMargin(0.10);
   gStyle->SetPadRightMargin(0.08);
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
   std::string goldinput = "~/media/HD02/analysis20/histos/his00373.root";
   TFile* goldinp = new TFile(TString(goldinput));
   std::string oldinput = "~/media/HD02/laura_offline/histos/his00373.root";
   TFile* oldinp = new TFile(TString(oldinput));

   // Back cluster
   TH3F *goldBGOsb = (TH3F*)goldinp->Get("hBGOEnergyVsTime");
   goldBGOsb->SetName("goldBGOsb");
   // Front cluster
   TH3F *goldBGOsf = (TH3F*)goldinp->Get("hBGOEnergyVsTime");
   goldBGOsf->SetName("goldBGOsf");

   //std::cout << "Bin -30 :: " << goldBGOsb->GetXaxis()->FindBin(-30) << ", bin +30 = " << goldBGOsb->GetXaxis()->FindBin(30) << std::endl;


   // Back BGOs: pre-calibration
   TH1* goldBackA = goldBGOsb->ProjectionZ("Back_BGO_A",98,104,1,1);
   goldBackA->SetName("goldBackA");
   TH1* goldBackB = goldBGOsb->ProjectionZ("Back_BGO_B",98,104,2,2);
   goldBackB->SetName("goldBackB");
   TH1* goldBackC = goldBGOsb->ProjectionZ("Back_BGO_C",98,104,3,3);
   goldBackC->SetName("goldBackC");
   TH1* goldBackD = goldBGOsb->ProjectionZ("Back_BGO_D",98,104,4,4);
   goldBackD->SetName("goldBackD");
   TH1* goldBackE = goldBGOsb->ProjectionZ("Back_BGO_E",98,104,5,5);
   goldBackE->SetName("goldBackE");
   TH1* goldBackF = goldBGOsb->ProjectionZ("Back_BGO_F",98,104,6,6);
   goldBackF->SetName("goldBackF");
   TH1* goldBackG = goldBGOsb->ProjectionZ("Back_BGO_G",98,104,7,7);
   goldBackG->SetName("goldBackG");
   TH1* goldBackH = goldBGOsb->ProjectionZ("Back_BGO_H",98,104,8,8);
   goldBackH->SetName("goldBackH");
   TH1* goldBackI = goldBGOsb->ProjectionZ("Back_BGO_I",98,104,9,9);
   goldBackI->SetName("goldBackI");
   TH1* goldBackJ = goldBGOsb->ProjectionZ("Back_BGO_J",98,104,10,10);
   goldBackJ->SetName("goldBackJ");
   

   // Front BGOs: pre-calibration
   TH1* goldFrontA = goldBGOsf->ProjectionZ("Front_BGO_A",98,104,17,17);
   goldFrontA->SetName("goldFrontA");
   TH1* goldFrontB = goldBGOsf->ProjectionZ("Front_BGO_B",98,104,18,18);
   goldFrontB->SetName("goldFrontB");
   TH1* goldFrontC = goldBGOsf->ProjectionZ("Front_BGO_C",98,104,19,19);
   goldFrontC->SetName("goldFrontC");
   TH1* goldFrontD = goldBGOsf->ProjectionZ("Front_BGO_D",98,104,20,20);
   goldFrontD->SetName("goldFrontD");
   TH1* goldFrontE = goldBGOsf->ProjectionZ("Front_BGO_E",98,104,21,21);
   goldFrontE->SetName("goldFrontE");
   TH1* goldFrontF = goldBGOsf->ProjectionZ("Front_BGO_F",98,104,22,22);
   goldFrontF->SetName("goldFrontF");
   TH1* goldFrontG = goldBGOsf->ProjectionZ("Front_BGO_G",98,104,23,23);
   goldFrontG->SetName("goldFrontG");
   TH1* goldFrontH = goldBGOsf->ProjectionZ("Front_BGO_H",98,104,24,24);
   goldFrontH->SetName("goldFrontH");


   // Histograms
   // Back BGOs: pre-calibration
   TH1F *goldBackAcal = new TH1F("goldBackAcal","goldBackAcal",128,0.0,8192.0);
   TH1F *goldBackBcal = new TH1F("goldBackBcal","goldBackBcal",128,0.0,8192.0);
   TH1F *goldBackCcal = new TH1F("goldBackCcal","goldBackCcal",128,0.0,8192.0);
   TH1F *goldBackDcal = new TH1F("goldBackDcal","goldBackDcal",128,0.0,8192.0);
   TH1F *goldBackEcal = new TH1F("goldBackEcal","goldBackEcal",128,0.0,8192.0);
   TH1F *goldBackFcal = new TH1F("goldBackFcal","goldBackFcal",128,0.0,8192.0);
   TH1F *goldBackGcal = new TH1F("goldBackGcal","goldBackGcal",128,0.0,8192.0);
   TH1F *goldBackHcal = new TH1F("goldBackHcal","goldBackHcal",128,0.0,8192.0);
   TH1F *goldBackIcal = new TH1F("goldBackIcal","goldBackIcal",128,0.0,8192.0);
   TH1F *goldBackJcal = new TH1F("goldBackJcal","goldBackJcal",128,0.0,8192.0);   
   // Front BGOs: pre-calibration
   TH1F *goldFrontAcal = new TH1F("goldFrontAcal","goldFrontAcal",128,0.0,8192.0);
   TH1F *goldFrontBcal = new TH1F("goldFrontBcal","goldFrontBcal",128,0.0,8192.0);
   TH1F *goldFrontCcal = new TH1F("goldFrontCcal","goldFrontCcal",128,0.0,8192.0);
   TH1F *goldFrontDcal = new TH1F("goldFrontDcal","goldFrontDcal",128,0.0,8192.0);
   TH1F *goldFrontEcal = new TH1F("goldFrontEcal","goldFrontEcal",128,0.0,8192.0);
   TH1F *goldFrontFcal = new TH1F("goldFrontFcal","goldFrontFcal",128,0.0,8192.0);
   TH1F *goldFrontGcal = new TH1F("goldFrontGcal","goldFrontGcal",128,0.0,8192.0);
   TH1F *goldFrontHcal = new TH1F("goldFrontHcal","goldFrontHcal",128,0.0,8192.0);

   // Back BGOs: pre-calibration
   for (int m=1; m<=goldBackA->GetNbinsX(); m++) {
      for (int a=0; a<goldBackA->GetBinContent(m); a++) goldBackAcal->Fill((goldBackA->GetXaxis()->GetBinCenter(m))*1.74+12.46);
      for (int b=0; b<goldBackB->GetBinContent(m); b++) goldBackBcal->Fill((goldBackB->GetXaxis()->GetBinCenter(m))*1.94+10.34);
      for (int c=0; c<goldBackC->GetBinContent(m); c++) goldBackCcal->Fill((goldBackC->GetXaxis()->GetBinCenter(m))*1.82+11.70);
      for (int d=0; d<goldBackD->GetBinContent(m); d++) goldBackDcal->Fill((goldBackD->GetXaxis()->GetBinCenter(m))*1.86+22.30);
      for (int e=0; e<goldBackE->GetBinContent(m); e++) goldBackEcal->Fill((goldBackE->GetXaxis()->GetBinCenter(m))*1.88+20.78);
      for (int f=0; f<goldBackF->GetBinContent(m); f++) goldBackFcal->Fill((goldBackF->GetXaxis()->GetBinCenter(m))*2.65+13.41);
      for (int g=0; g<goldBackG->GetBinContent(m); g++) goldBackGcal->Fill((goldBackG->GetXaxis()->GetBinCenter(m))*1.92+13.03);
      for (int h=0; h<goldBackH->GetBinContent(m); h++) goldBackHcal->Fill((goldBackH->GetXaxis()->GetBinCenter(m))*2.00+14.92);
      for (int i=0; i<goldBackI->GetBinContent(m); i++) goldBackIcal->Fill((goldBackI->GetXaxis()->GetBinCenter(m))*2.10+13.37);
      for (int j=0; j<goldBackJ->GetBinContent(m); j++) goldBackJcal->Fill((goldBackJ->GetXaxis()->GetBinCenter(m))*2.52+13.16);
   }
   // Front BGOs: pre-calibration
   for (int m=1; m<=goldFrontA->GetNbinsX(); m++) {
      for (int a=0; a<goldFrontA->GetBinContent(m); a++) goldFrontAcal->Fill((goldFrontA->GetXaxis()->GetBinCenter(m))*1.90+24.51);
      for (int b=0; b<goldFrontB->GetBinContent(m); b++) goldFrontBcal->Fill((goldFrontB->GetXaxis()->GetBinCenter(m))*1.81+34.33);
      for (int c=0; c<goldFrontC->GetBinContent(m); c++) goldFrontCcal->Fill((goldFrontC->GetXaxis()->GetBinCenter(m))*1.90+32.27);
      for (int d=0; d<goldFrontD->GetBinContent(m); d++) goldFrontDcal->Fill((goldFrontD->GetXaxis()->GetBinCenter(m))*2.00+50.30);
      for (int e=0; e<goldFrontE->GetBinContent(m); e++) goldFrontEcal->Fill((goldFrontE->GetXaxis()->GetBinCenter(m))*1.96+82.73);
      for (int f=0; f<goldFrontF->GetBinContent(m); f++) goldFrontFcal->Fill((goldFrontF->GetXaxis()->GetBinCenter(m))*1.95+33.43);
      for (int g=0; g<goldFrontG->GetBinContent(m); g++) goldFrontGcal->Fill((goldFrontG->GetXaxis()->GetBinCenter(m))*1.80+32.41);
      for (int h=0; h<goldFrontH->GetBinContent(m); h++) goldFrontHcal->Fill((goldFrontH->GetXaxis()->GetBinCenter(m))*1.94+27.70);
   }

   // Back BGOs: pre-calibration
   TList *goldlistb = new TList;
   goldlistb->Add(goldBackAcal);
   goldlistb->Add(goldBackBcal);
   goldlistb->Add(goldBackCcal);
   goldlistb->Add(goldBackDcal);
   goldlistb->Add(goldBackEcal);
   goldlistb->Add(goldBackFcal);
   goldlistb->Add(goldBackGcal);
   goldlistb->Add(goldBackHcal);
   goldlistb->Add(goldBackIcal);
   goldlistb->Add(goldBackJcal);

   // Front BGOs: pre-calibration
   TList *goldlistf = new TList;
   goldlistf->Add(goldFrontAcal);
   goldlistf->Add(goldFrontBcal);
   goldlistf->Add(goldFrontCcal);
   goldlistf->Add(goldFrontDcal);
   goldlistf->Add(goldFrontEcal);
   goldlistf->Add(goldFrontFcal);
   goldlistf->Add(goldFrontGcal);
   goldlistf->Add(goldFrontHcal);
   

   // Back BGOs: pre-calibration
   TH1F *goldClusterb = (TH1F*)goldBackAcal->Clone("goldClusterb");
   goldClusterb->Reset();
   goldClusterb->Merge(goldlistb);

   // Front BGOs: pre-calibration
   TH1F *goldClusterf = (TH1F*)goldFrontAcal->Clone("goldClusterf");
   goldClusterf->Reset();
   goldClusterf->Merge(goldlistf);

   goldClusterb->Scale(1/(goldClusterb->Integral()),"nosw2");
   goldClusterf->Scale(1/(goldClusterf->Integral()),"nosw2");
   
   TF1* g1 = new TF1("g1","gaus",800,1000);
   TF1* g2 = new TF1("g2","gaus",1650,2050);
   TF1* g3 = new TF1("g3","gaus",800,1000);
   TF1* g4 = new TF1("g4","gaus",1650,2050);

   TF1 *g5 = new TF1("g5","gaus",750,1150);
   TF1 *g6 = new TF1("g6","gaus",1550,2250);
   TF1 *g7 = new TF1("g7","gaus",750,1150);
   TF1 *g8 = new TF1("g8","gaus",1550,2250);


   TCanvas *canb = new TCanvas("canb","canb",800,600);
   canb->SetGrid();
   gStyle->SetOptStat(0);
   gPad->SetLogy();
   goldClusterb->SetTitle("");
   goldClusterb->GetXaxis()->SetTitle("E [keV]");
   goldClusterb->GetXaxis()->SetRangeUser(0.0,8000.0);
   //goldClusterb->GetYaxis()->SetRangeUser(1e1,1.5e6);
   goldClusterb->SetLineColor(kBlack);
   goldClusterb->Draw();
   //precalClusterb->Fit("g1","R");
   //precalClusterb->Fit("g2","R+");
   //g1->SetLineColor(kTeal-5);
   //g1->Draw("SAME");
   //g2->SetLineColor(kTeal-5);
   //g2->Draw("SAME");
   //goldClusterb->GetXaxis()->SetRangeUser(0.0,2500.0);
   goldClusterf->SetLineColor(kOrange-5);
   goldClusterf->Draw("same");
   //postcalClusterb->Fit("g3","R");
   //postcalClusterb->Fit("g4","R+");
   //g3->SetLineColor(kViolet-5);
   //g3->Draw("SAME");
   //g4->SetLineColor(kViolet-5);
   //g4->Draw("SAME");
   //oldclusterb->SetLineColor(kGreen-2);
   //oldclusterb->Draw("same");
   //oldclusterf->SetLineColor(kRed-3);
   //oldclusterf->Draw("same");
   //voldclusterb->SetLineColor(kTeal-5);
   //voldclusterb->Draw("same");
   //voldclusterf->SetLineColor(kViolet-5);
   //voldclusterf->Draw("same");
   auto goldlegend = new TLegend(0.62,0.78,0.9,0.88);
   goldlegend->AddEntry(goldClusterb,"Back","l");
   goldlegend->AddEntry(goldClusterf,"Front","l");
   //goldlegend->AddEntry(oldclusterb,"Back old","l");
   //goldlegend->AddEntry(oldclusterf,"Front old","l"); 
   goldlegend->Draw();
   //auto calblegend = new TLegend(0.12,0.18,0.58,0.36);
   //calblegend->AddEntry(g1,TString::Format("Pre-cal: ^{88}Y_{898} = %4.2f #pm %4.2f keV",(g1->GetParameter(1)),(g1->GetParError(1))),"l");
   //calblegend->AddEntry(g2,TString::Format("Pre-cal: ^{88}Y_{1836} = %4.2f #pm %4.2f keV",(g2->GetParameter(1)),(g2->GetParError(1))),"l");
   //calblegend->AddEntry(g3,TString::Format("Post-cal: ^{88}Y_{898} = %4.2f #pm %4.2f keV",(g3->GetParameter(1)),(g3->GetParError(1))),"l");
   //calblegend->AddEntry(g4,TString::Format("Post-cal: ^{88}y_{1836} = %4.2f #pm %4.2f keV",(g4->GetParameter(1)),(g4->GetParError(1))),"l");
   //calblegend->Draw();
   //canb->SaveAs("BGO_Back_cal.pdf");
   //canb->SaveAs("BGO_Back_cal_fits.pdf");
  
 

} 
 
 int main() {
   CalibrationEstimate();
   return 0;
}  
