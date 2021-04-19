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

void CalibrationCompare(){

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

   //const int nsamps = 101;
   //const int nbins = 150;

   // Names of the files
   std::string preinputback = "~/media/HD02/analysis20/calibration/calhis00360.root";
   std::string postinputback = "~/media/HD02/analysis20/calibration/calhis00572.root";
   std::string preinputfront = "~/media/HD02/analysis20/calibration/calhis00361.root";
   std::string postinputfront = "~/media/HD02/analysis20/calibration/calhis00574.root";
   TFile* preinpb = new TFile(TString(preinputback));
   TFile* postinpb = new TFile(TString(postinputback));
   TFile *preinpf = new TFile(TString(preinputfront));
   TFile *postinpf = new TFile(TString(postinputfront));

   // Back cluster
   TH2F *preBGOsb = (TH2F*)preinpb->Get("hBGOEnergy");
   preBGOsb->SetName("preBGOsb");
   TH2F *postBGOsb = (TH2F*)postinpb->Get("hBGOEnergy");
   postBGOsb->SetName("postBGOsb");
   // Front cluster
   TH2F *preBGOsf = (TH2F*)preinpf->Get("hBGOEnergy");
   preBGOsf->SetName("preBGOsf");
   TH2F *postBGOsf = (TH2F*)postinpf->Get("hBGOEnergy");
   postBGOsf->SetName("postBGOsf");


   // Back BGOs: pre-calibration
   TH1* preBackA = preBGOsb->ProjectionX("Pre_Back_BGO_A",1,1);
   preBackA->SetName("preBackA");
   TH1* preBackB = preBGOsb->ProjectionX("Pre_Back_BGO_B",2,2);
   preBackB->SetName("preBackB");
   TH1* preBackC = preBGOsb->ProjectionX("Pre_Back_BGO_C",3,3);
   preBackC->SetName("preBackC");
   TH1* preBackD = preBGOsb->ProjectionX("Pre_Back_BGO_D",4,4);
   preBackD->SetName("preBackD");
   TH1* preBackE = preBGOsb->ProjectionX("Pre_Back_BGO_E",5,5);
   preBackE->SetName("preBackE");
   TH1* preBackF = preBGOsb->ProjectionX("Pre_Back_BGO_F",6,6);
   preBackF->SetName("preBackF");
   TH1* preBackG = preBGOsb->ProjectionX("Pre_Back_BGO_G",7,7);
   preBackG->SetName("preBackG");
   TH1* preBackH = preBGOsb->ProjectionX("Pre_Back_BGO_H",8,8);
   preBackH->SetName("preBackH");
   TH1* preBackI = preBGOsb->ProjectionX("Pre_Back_BGO_I",9,9);
   preBackI->SetName("preBackI");
   TH1* preBackJ = preBGOsb->ProjectionX("Pre_Back_BGO_J",10,10);
   preBackJ->SetName("preBackJ");
   
   // Back BGOs: post-calibration
   TH1* postBackA = postBGOsb->ProjectionX("Post_Back_BGO_A",1,1);
   postBackA->SetName("postBackA");
   TH1* postBackB = postBGOsb->ProjectionX("Post_Back_BGO_B",2,2);
   postBackB->SetName("postBackB");
   TH1* postBackC = postBGOsb->ProjectionX("Post_Back_BGO_C",3,3);
   postBackC->SetName("postBackC");
   TH1* postBackD = postBGOsb->ProjectionX("Post_Back_BGO_D",4,4);
   postBackD->SetName("postBackD");
   TH1* postBackE = postBGOsb->ProjectionX("Post_Back_BGO_E",5,5);
   postBackE->SetName("postBackE");
   TH1* postBackF = postBGOsb->ProjectionX("Post_Back_BGO_F",6,6);
   postBackF->SetName("postBackF");
   TH1* postBackG = postBGOsb->ProjectionX("Post_Back_BGO_G",7,7);
   postBackG->SetName("postBackG");
   TH1* postBackH = postBGOsb->ProjectionX("Post_Back_BGO_H",8,8);
   postBackH->SetName("postBackH");
   TH1* postBackI = postBGOsb->ProjectionX("Post_Back_BGO_I",9,9);
   postBackI->SetName("postBackI");
   TH1* postBackJ = postBGOsb->ProjectionX("Post_Back_BGO_J",10,10);
   postBackJ->SetName("postBackJ");

   // Front BGOs: pre-calibration
   TH1* preFrontA = preBGOsf->ProjectionX("Pre_Front_BGO_A",17,17);
   preFrontA->SetName("preFrontA");
   TH1* preFrontB = preBGOsf->ProjectionX("Pre_Front_BGO_B",18,18);
   preFrontB->SetName("preFrontB");
   TH1* preFrontC = preBGOsf->ProjectionX("Pre_Front_BGO_C",19,19);
   preFrontC->SetName("preFrontC");
   TH1* preFrontD = preBGOsf->ProjectionX("Pre_Front_BGO_D",20,20);
   preFrontD->SetName("preFrontD");
   TH1* preFrontE = preBGOsf->ProjectionX("Pre_Front_BGO_E",21,21);
   preFrontE->SetName("preFrontE");
   TH1* preFrontF = preBGOsf->ProjectionX("Pre_Front_BGO_F",22,22);
   preFrontF->SetName("preFrontF");
   TH1* preFrontG = preBGOsf->ProjectionX("Pre_Front_BGO_G",23,23);
   preFrontG->SetName("preFrontG");
   TH1* preFrontH = preBGOsf->ProjectionX("Pre_Front_BGO_H",24,24);
   preFrontH->SetName("preFrontH");

   // Front BGOs: post-calibration
   TH1* postFrontA = postBGOsf->ProjectionX("Post_Front_BGO_A",17,17);
   postFrontA->SetName("postFrontA");
   TH1* postFrontB = postBGOsf->ProjectionX("Post_Front_BGO_B",18,18);
   postFrontB->SetName("postFrontB");
   TH1* postFrontC = postBGOsf->ProjectionX("Post_Front_BGO_C",19,19);
   postFrontC->SetName("postFrontC");
   TH1* postFrontD = postBGOsf->ProjectionX("Post_Front_BGO_D",20,20);
   postFrontD->SetName("postFrontD");
   TH1* postFrontE = postBGOsf->ProjectionX("Post_Front_BGO_E",21,21);
   postFrontE->SetName("postFrontE");
   TH1* postFrontF = postBGOsf->ProjectionX("Post_Front_BGO_F",22,22);
   postFrontF->SetName("postFrontF");
   TH1* postFrontG = postBGOsf->ProjectionX("Post_Front_BGO_G",23,23);
   postFrontG->SetName("postFrontG");
   TH1* postFrontH = postBGOsf->ProjectionX("Post_Front_BGO_H",24,24);
   postFrontH->SetName("postFrontH");


   // Histograms
   // Back BGOs: pre-calibration
   TH1F *preBackAcal = new TH1F("preBackAcal","preBackAcal",1024,0.0,32768.0);
   TH1F *preBackBcal = new TH1F("preBackBcal","preBackBcal",1024,0.0,32768.0);
   TH1F *preBackCcal = new TH1F("preBackCcal","preBackCcal",1024,0.0,32768.0);
   TH1F *preBackDcal = new TH1F("preBackDcal","preBackDcal",1024,0.0,32768.0);
   TH1F *preBackEcal = new TH1F("preBackEcal","preBackEcal",1024,0.0,32768.0);
   TH1F *preBackFcal = new TH1F("preBackFcal","preBackFcal",1024,0.0,32768.0);
   TH1F *preBackGcal = new TH1F("preBackGcal","preBackGcal",1024,0.0,32768.0);
   TH1F *preBackHcal = new TH1F("preBackHcal","preBackHcal",1024,0.0,32768.0);
   TH1F *preBackIcal = new TH1F("preBackIcal","preBackIcal",1024,0.0,32768.0);
   TH1F *preBackJcal = new TH1F("preBackJcal","preBackJcal",1024,0.0,32768.0);   
   // Back BGOs: post-calibration
   TH1F *postBackAcal = new TH1F("postBackAcal","postBackAcal",1024,0.0,32768.0);
   TH1F *postBackBcal = new TH1F("postBackBcal","postBackBcal",1024,0.0,32768.0);
   TH1F *postBackCcal = new TH1F("postBackCcal","postBackCcal",1024,0.0,32768.0);
   TH1F *postBackDcal = new TH1F("postBackDcal","postBackDcal",1024,0.0,32768.0);
   TH1F *postBackEcal = new TH1F("postBackEcal","postBackEcal",1024,0.0,32768.0);
   TH1F *postBackFcal = new TH1F("postBackFcal","postBackFcal",1024,0.0,32768.0);
   TH1F *postBackGcal = new TH1F("postBackGcal","postBackGcal",1024,0.0,32768.0);
   TH1F *postBackHcal = new TH1F("postBackHcal","postBackHcal",1024,0.0,32768.0);
   TH1F *postBackIcal = new TH1F("postBackIcal","postBackIcal",1024,0.0,32768.0);
   TH1F *postBackJcal = new TH1F("postBackJcal","postBackJcal",1024,0.0,32768.0);
   // Front BGOs: pre-calibration
   TH1F *preFrontAcal = new TH1F("preFrontAcal","preFrontAcal",1024,0.0,32768.0);
   TH1F *preFrontBcal = new TH1F("preFrontBcal","preFrontBcal",1024,0.0,32768.0);
   TH1F *preFrontCcal = new TH1F("preFrontCcal","preFrontCcal",1024,0.0,32768.0);
   TH1F *preFrontDcal = new TH1F("preFrontDcal","preFrontDcal",1024,0.0,32768.0);
   TH1F *preFrontEcal = new TH1F("preFrontEcal","preFrontEcal",1024,0.0,32768.0);
   TH1F *preFrontFcal = new TH1F("preFrontFcal","preFrontFcal",1024,0.0,32768.0);
   TH1F *preFrontGcal = new TH1F("preFrontGcal","preFrontGcal",1024,0.0,32768.0);
   TH1F *preFrontHcal = new TH1F("preFrontHcal","preFrontHcal",1024,0.0,32768.0);
   // Front BGOs: post-calibration
   TH1F *postFrontAcal = new TH1F("postFrontAcal","postFrontAcal",1024,0.0,32768.0);
   TH1F *postFrontBcal = new TH1F("postFrontBcal","postFrontBcal",1024,0.0,32768.0);
   TH1F *postFrontCcal = new TH1F("postFrontCcal","postFrontCcal",1024,0.0,32768.0);
   TH1F *postFrontDcal = new TH1F("postFrontDcal","postFrontDcal",1024,0.0,32768.0);
   TH1F *postFrontEcal = new TH1F("postFrontEcal","postFrontEcal",1024,0.0,32768.0);
   TH1F *postFrontFcal = new TH1F("postFrontFcal","postFrontFcal",1024,0.0,32768.0);
   TH1F *postFrontGcal = new TH1F("postFrontGcal","postFrontGcal",1024,0.0,32768.0);
   TH1F *postFrontHcal = new TH1F("postFrontHcal","poatFrontHcal",1024,0.0,32768.0);

   // Back BGOs: pre-calibration
   for (int m=1; m<=preBackA->GetNbinsX(); m++) {
      for (int a=0; a<preBackA->GetBinContent(m); a++) preBackAcal->Fill((preBackA->GetXaxis()->GetBinCenter(m))*1.74+12.46);
      for (int b=0; b<preBackB->GetBinContent(m); b++) preBackBcal->Fill((preBackB->GetXaxis()->GetBinCenter(m))*1.94+10.34);
      for (int c=0; c<preBackC->GetBinContent(m); c++) preBackCcal->Fill((preBackC->GetXaxis()->GetBinCenter(m))*1.82+11.70);
      for (int d=0; d<preBackD->GetBinContent(m); d++) preBackDcal->Fill((preBackD->GetXaxis()->GetBinCenter(m))*1.86+22.30);
      for (int e=0; e<preBackE->GetBinContent(m); e++) preBackEcal->Fill((preBackE->GetXaxis()->GetBinCenter(m))*1.88+20.78);
      for (int f=0; f<preBackF->GetBinContent(m); f++) preBackFcal->Fill((preBackF->GetXaxis()->GetBinCenter(m))*2.65+13.41);
      for (int g=0; g<preBackG->GetBinContent(m); g++) preBackGcal->Fill((preBackG->GetXaxis()->GetBinCenter(m))*1.92+13.03);
      for (int h=0; h<preBackH->GetBinContent(m); h++) preBackHcal->Fill((preBackH->GetXaxis()->GetBinCenter(m))*2.00+14.92);
      for (int i=0; i<preBackI->GetBinContent(m); i++) preBackIcal->Fill((preBackI->GetXaxis()->GetBinCenter(m))*2.10+13.37);
      for (int j=0; j<preBackJ->GetBinContent(m); j++) preBackJcal->Fill((preBackJ->GetXaxis()->GetBinCenter(m))*2.52+13.16);
   }
   // Back BGOs: post-calibration
   for (int m=1; m<=postBackA->GetNbinsX(); m++) { 
      for (int a=0; a<postBackA->GetBinContent(m); a++) postBackAcal->Fill((postBackA->GetXaxis()->GetBinCenter(m))*1.63+13.06);
      for (int b=0; b<postBackB->GetBinContent(m); b++) postBackBcal->Fill((postBackB->GetXaxis()->GetBinCenter(m))*1.90+8.87);
      for (int c=0; c<postBackC->GetBinContent(m); c++) postBackCcal->Fill((postBackC->GetXaxis()->GetBinCenter(m))*1.78+11.98);
      for (int d=0; d<postBackD->GetBinContent(m); d++) postBackDcal->Fill((postBackD->GetXaxis()->GetBinCenter(m))*1.84+25.73);
      for (int e=0; e<postBackE->GetBinContent(m); e++) postBackEcal->Fill((postBackE->GetXaxis()->GetBinCenter(m))*1.87+22.42);
      for (int f=0; f<postBackF->GetBinContent(m); f++) postBackFcal->Fill((postBackF->GetXaxis()->GetBinCenter(m))*2.68+12.77);
      for (int g=0; g<postBackG->GetBinContent(m); g++) postBackGcal->Fill((postBackG->GetXaxis()->GetBinCenter(m))*1.84+16.04);
      for (int h=0; h<postBackH->GetBinContent(m); h++) postBackHcal->Fill((postBackH->GetXaxis()->GetBinCenter(m))*2.06+14.81);
      for (int i=0; i<postBackI->GetBinContent(m); i++) postBackIcal->Fill((postBackI->GetXaxis()->GetBinCenter(m))*2.05+16.53);
      for (int j=0; j<postBackJ->GetBinContent(m); j++) postBackJcal->Fill((postBackJ->GetXaxis()->GetBinCenter(m))*2.71+10.48);
   }
   // Front BGOs: pre-calibration
   for (int m=1; m<=preFrontA->GetNbinsX(); m++) {
      for (int a=0; a<preFrontA->GetBinContent(m); a++) preFrontAcal->Fill((preFrontA->GetXaxis()->GetBinCenter(m))*1.90+24.51);
      for (int b=0; b<preFrontB->GetBinContent(m); b++) preFrontBcal->Fill((preFrontB->GetXaxis()->GetBinCenter(m))*1.81+34.33);
      for (int c=0; c<preFrontC->GetBinContent(m); c++) preFrontCcal->Fill((preFrontC->GetXaxis()->GetBinCenter(m))*1.90+32.27);
      for (int d=0; d<preFrontD->GetBinContent(m); d++) preFrontDcal->Fill((preFrontD->GetXaxis()->GetBinCenter(m))*2.00+50.30);
      for (int e=0; e<preFrontE->GetBinContent(m); e++) preFrontEcal->Fill((preFrontE->GetXaxis()->GetBinCenter(m))*1.96+82.73);
      for (int f=0; f<preFrontF->GetBinContent(m); f++) preFrontFcal->Fill((preFrontF->GetXaxis()->GetBinCenter(m))*1.95+33.43);
      for (int g=0; g<preFrontG->GetBinContent(m); g++) preFrontGcal->Fill((preFrontG->GetXaxis()->GetBinCenter(m))*1.80+32.41);
      for (int h=0; h<preFrontH->GetBinContent(m); h++) preFrontHcal->Fill((preFrontH->GetXaxis()->GetBinCenter(m))*1.94+27.70);
   }
   // Front BGOs: post-calibration
   for (int m=1; m<=postFrontA->GetNbinsX(); m++) {
      for (int a=0; a<postFrontA->GetBinContent(m); a++) postFrontAcal->Fill((postFrontA->GetXaxis()->GetBinCenter(m))*1.79+21.78);
      for (int b=0; b<postFrontB->GetBinContent(m); b++) postFrontBcal->Fill((postFrontB->GetXaxis()->GetBinCenter(m))*1.73+37.47);
      for (int c=0; c<postFrontC->GetBinContent(m); c++) postFrontCcal->Fill((postFrontC->GetXaxis()->GetBinCenter(m))*1.82+31.57);
      for (int d=0; d<postFrontD->GetBinContent(m); d++) postFrontDcal->Fill((postFrontD->GetXaxis()->GetBinCenter(m))*1.89+49.41);
      for (int e=0; e<postFrontE->GetBinContent(m); e++) postFrontEcal->Fill((postFrontE->GetXaxis()->GetBinCenter(m))*1.92+64.81);
      for (int f=0; f<postFrontF->GetBinContent(m); f++) postFrontFcal->Fill((postFrontF->GetXaxis()->GetBinCenter(m))*1.92+31.06);
      for (int g=0; g<postFrontG->GetBinContent(m); g++) postFrontGcal->Fill((postFrontG->GetXaxis()->GetBinCenter(m))*1.68+38.62);  
      for (int h=0; h<postFrontH->GetBinContent(m); h++) postFrontHcal->Fill((postFrontH->GetXaxis()->GetBinCenter(m))*1.85+30.46);
   }

   // Back BGOs: pre-calibration
   TList *prelistb = new TList;
   prelistb->Add(preBackAcal);
   prelistb->Add(preBackBcal);
   prelistb->Add(preBackCcal);
   prelistb->Add(preBackDcal);
   prelistb->Add(preBackEcal);
   prelistb->Add(preBackFcal);
   prelistb->Add(preBackGcal);
   prelistb->Add(preBackHcal);
   prelistb->Add(preBackIcal);
   prelistb->Add(preBackJcal);

   // Back BGOs: post-calibration
   TList *postlistb = new TList;
   postlistb->Add(postBackAcal);
   postlistb->Add(postBackBcal);
   postlistb->Add(postBackCcal);
   postlistb->Add(postBackDcal);
   postlistb->Add(postBackEcal);
   postlistb->Add(postBackFcal);
   postlistb->Add(postBackGcal);
   postlistb->Add(postBackHcal);
   postlistb->Add(postBackIcal);
   postlistb->Add(postBackJcal);

   // Front BGOs: pre-calibration
   TList *prelistf = new TList;
   prelistf->Add(preFrontAcal);
   prelistf->Add(preFrontBcal);
   prelistf->Add(preFrontCcal);
   prelistf->Add(preFrontDcal);
   prelistf->Add(preFrontEcal);
   prelistf->Add(preFrontFcal);
   prelistf->Add(preFrontGcal);
   prelistf->Add(preFrontHcal);

   // Front BGOs: post-calibration
   TList *postlistf = new TList;
   postlistf->Add(postFrontAcal);
   postlistf->Add(postFrontBcal);
   postlistf->Add(postFrontCcal);
   postlistf->Add(postFrontDcal);
   postlistf->Add(postFrontEcal);
   postlistf->Add(postFrontFcal);
   postlistf->Add(postFrontGcal);
   postlistf->Add(postFrontHcal);
   

   // Back BGOs: pre-calibration
   TH1F *precalClusterb = (TH1F*)preBackAcal->Clone("precalClusterb");
   precalClusterb->Reset();
   precalClusterb->Merge(prelistb);

   // Back BGOs: post-calibration
   TH1F *postcalClusterb = (TH1F*)postBackAcal->Clone("postcalClusterb");
   postcalClusterb->Reset();
   postcalClusterb->Merge(postlistb);

   // Front BGOs: pre-calibration
   TH1F *precalClusterf = (TH1F*)preFrontAcal->Clone("precalClusterf");
   precalClusterf->Reset();
   precalClusterf->Merge(prelistf);
 
   // Front BGOs: post-calibration
   TH1F *postcalClusterf = (TH1F*)postFrontAcal->Clone("postcalClusterf");
   postcalClusterf->Reset();
   postcalClusterf->Merge(postlistf);

   precalClusterb->Scale(1/(precalClusterb->Integral()),"nosw2");
   postcalClusterb->Scale(1/(postcalClusterb->Integral()),"nosw2");
   precalClusterf->Scale(1/(precalClusterf->Integral()),"nosw2");
   postcalClusterf->Scale(1/(postcalClusterf->Integral()),"nosw2");

   //std::cout << "A = " << preBackAcal->GetEntries() << ", B = " << preBackBcal->GetEntries() << ", C = " << preBackCcal->GetEntries() << ", D = " << preBackDcal->GetEntries() << ", E = " << preBackEcal->GetEntries() << preBackEcal->GetEntries() << ", F = " << preBackFcal->GetEntries() << ", G = " << preBackGcal->GetEntries() << ", H = " << preBackHcal->GetEntries() << ", I = " << preBackIcal->GetEntries() << ", J = " << preBackJcal->GetEntries() << ", A+B+C+D+E+F+G+H+I+J = " << (preBackAcal->GetEntries()) + (preBackBcal->GetEntries()) + (preBackCcal->GetEntries()) + (preBackDcal->GetEntries()) + (preBackEcal->GetEntries()) + (preBackFcal->GetEntries()) + (preBackGcal->GetEntries()) + (preBackHcal->GetEntries()) + (preBackIcal->GetEntries()) + (preBackJcal->GetEntries()) << std::endl;
   //std::cout << "Cluster: A + B + C + D + E + F + G + H + I + J = " << precalClusterb->GetEntries() << std::endl;

   //std::cout << "A = " << postBackAcal->GetEntries() << ", B = " << postBackBcal->GetEntries() << ", C = " << postBackCcal->GetEntries() << ", D = " << postBackDcal->GetEntries() << ", E = " << postBackEcal->GetEntries() << postBackEcal->GetEntries() << ", F = " << postBackFcal->GetEntries() << ", G = " << postBackGcal->GetEntries() << ", H = " << postBackHcal->GetEntries() << ", I = " << postBackIcal->GetEntries() << ", J = " << postBackJcal->GetEntries() << ", A+B+C+D+E+F+G+H+I+J = " << (postBackAcal->GetEntries()) + (postBackBcal->GetEntries()) + (postBackCcal->GetEntries()) + (postBackDcal->GetEntries()) + (postBackEcal->GetEntries()) + (postBackFcal->GetEntries()) + (postBackGcal->GetEntries()) + (postBackHcal->GetEntries()) + (postBackIcal->GetEntries()) + (postBackJcal->GetEntries()) << std::endl;
   //std::cout << "Cluster: A + B + C + D + E + F + G + H + I + J = " << postcalClusterb->GetEntries() << std::endl;

   //std::cout << "A = " << preFrontAcal->GetEntries() << ", B = " << preFrontBcal->GetEntries() << ", C = " << preFrontCcal->GetEntries() << ", D = " << preFrontDcal->GetEntries() << ", E = " << preFrontEcal->GetEntries() << preFrontEcal->GetEntries() << ", F = " << preFrontFcal->GetEntries() << ", G = " << preFrontGcal->GetEntries() << ", H = " << preFrontHcal->GetEntries() << ", A+B+C+D+E+F+G+H = " << (preFrontAcal->GetEntries()) + (preFrontBcal->GetEntries()) + (preFrontCcal->GetEntries()) + (preFrontDcal->GetEntries()) + (preFrontEcal->GetEntries()) + (preFrontFcal->GetEntries()) + (preFrontGcal->GetEntries()) + (preFrontHcal->GetEntries()) << std::endl;
   //std::cout << "Cluster: A + B + C + D + E + F + G + H  = " << precalClusterf->GetEntries() << std::endl;

   //std::cout << "A = " << postFrontAcal->GetEntries() << ", B = " << postFrontBcal->GetEntries() << ", C = " << postFrontCcal->GetEntries() << ", D = " << postFrontDcal->GetEntries() << ", E = " << postFrontEcal->GetEntries() << postFrontEcal->GetEntries() << ", F = " << postFrontFcal->GetEntries() << ", G = " << postFrontGcal->GetEntries() << ", H = " << postFrontHcal->GetEntries() << ", A+B+C+D+E+F+G+H = " << (postFrontAcal->GetEntries()) + (postFrontBcal->GetEntries()) + (postFrontCcal->GetEntries()) + (postFrontDcal->GetEntries()) + (postFrontEcal->GetEntries()) + (postFrontFcal->GetEntries()) + (postFrontGcal->GetEntries()) + (postFrontHcal->GetEntries()) << std::endl; 
   //std::cout << "Cluster: A + B + C + D + E + F + G + H  = " << postcalClusterf->GetEntries() << std::endl;


   
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
   precalClusterb->SetTitle("");
   precalClusterb->GetXaxis()->SetTitle("E [keV]");
   precalClusterb->SetLineColor(kBlack);
   precalClusterb->Draw();
   //precalClusterb->Fit("g1","R");
   //precalClusterb->Fit("g2","R+");
   //g1->SetLineColor(kTeal-5);
   //g1->Draw("SAME");
   //g2->SetLineColor(kTeal-5);
   //g2->Draw("SAME");
   precalClusterb->GetXaxis()->SetRangeUser(0.0,2500.0);
   postcalClusterb->SetLineColor(kOrange-5);
   postcalClusterb->Draw("same");
   //postcalClusterb->Fit("g3","R");
   //postcalClusterb->Fit("g4","R+");
   //g3->SetLineColor(kViolet-5);
   //g3->Draw("SAME");
   //g4->SetLineColor(kViolet-5);
   //g4->Draw("SAME");
   auto blegend = new TLegend(0.62,0.78,0.9,0.88);
   blegend->AddEntry(precalClusterb,"Pre-calibration","l");
   blegend->AddEntry(postcalClusterb,"Post-calibration","l"); 
   blegend->Draw();
   //auto calblegend = new TLegend(0.12,0.18,0.58,0.36);
   //calblegend->AddEntry(g1,TString::Format("Pre-cal: ^{88}Y_{898} = %4.2f #pm %4.2f keV",(g1->GetParameter(1)),(g1->GetParError(1))),"l");
   //calblegend->AddEntry(g2,TString::Format("Pre-cal: ^{88}Y_{1836} = %4.2f #pm %4.2f keV",(g2->GetParameter(1)),(g2->GetParError(1))),"l");
   //calblegend->AddEntry(g3,TString::Format("Post-cal: ^{88}Y_{898} = %4.2f #pm %4.2f keV",(g3->GetParameter(1)),(g3->GetParError(1))),"l");
   //calblegend->AddEntry(g4,TString::Format("Post-cal: ^{88}y_{1836} = %4.2f #pm %4.2f keV",(g4->GetParameter(1)),(g4->GetParError(1))),"l");
   //calblegend->Draw();
   canb->SaveAs("BGO_Back_cal.pdf");
   //canb->SaveAs("BGO_Back_cal_fits.pdf");
  
   TCanvas *canf = new TCanvas("canf","canf",800,600);
   canf->SetGrid();
   gStyle->SetOptStat(0);
   gPad->SetLogy();
   precalClusterf->SetTitle("");
   precalClusterf->GetXaxis()->SetTitle("E [keV]");
   precalClusterf->SetLineColor(kGray+2);
   precalClusterf->Draw();
   //precalClusterf->Fit("g5","R");
   //precalClusterf->Fit("g6","R+");
   //g5->SetLineColor(kTeal-5);
   //g5->Draw("SAME");
   //g6->SetLineColor(kTeal-5);
   //g6->Draw("SAME");
   precalClusterf->GetXaxis()->SetRangeUser(0.0,2500.0);
   postcalClusterf->SetLineColor(kOrange+1);
   postcalClusterf->Draw("same");
   //postcalClusterf->Fit("g7","R");
   //postcalClusterf->Fit("g8","R+");
   //g7->SetLineColor(kViolet-5);
   //g7->Draw("SAME");
   //g8->SetLineColor(kViolet-5);
   //g8->Draw("SAME");
   auto flegend = new TLegend(0.62,0.78,0.9,0.88);
   flegend->AddEntry(precalClusterf,"Pre-calibration","l");
   flegend->AddEntry(postcalClusterf,"Post-calibration","l");
   flegend->Draw();
   //auto calflegend = new TLegend(0.12,0.18,0.58,0.36);
   //calflegend->AddEntry(g5,TString::Format("Pre-cal: ^{88}Y_{898} = %4.2f #pm %4.2f keV",(g5->GetParameter(1)),(g5->GetParError(1))),"l");
   //calflegend->AddEntry(g6,TString::Format("Pre-cal: ^{88}Y_{1836} = %4.2f #pm %4.2f keV",(g6->GetParameter(1)),(g6->GetParError(1))),"l");
   //calflegend->AddEntry(g7,TString::Format("Post-cal: ^{88}Y_{898} = %4.2f #pm %4.2f keV",(g7->GetParameter(1)),(g7->GetParError(1))),"l");
   //calflegend->AddEntry(g8,TString::Format("Post-cal: ^{88}y_{1836} = %4.2f #pm %4.2f keV",(g8->GetParameter(1)),(g8->GetParError(1))),"l");
   //calflegend->Draw();
   canf->SaveAs("BGO_Front_cal.pdf");
   //canf->SaveAs("BGO_Front_cal_fits.pdf");

   TCanvas *canbf = new TCanvas("canbf","canbf",800,600);
   canbf->SetGrid();
   gStyle->SetOptStat(0);
   gPad->SetLogy();
   precalClusterb->SetTitle("");
   precalClusterb->GetXaxis()->SetTitle("E [keV]");
   precalClusterb->SetLineColor(kBlack);
   precalClusterb->Draw();
   precalClusterb->GetXaxis()->SetRangeUser(0.0,2500.0);
   postcalClusterb->SetLineColor(kOrange-5);
   postcalClusterb->Draw("same");
   precalClusterf->SetLineColor(kGray+2);
   precalClusterf->Draw("same");
   postcalClusterf->SetLineColor(kOrange+1);
   postcalClusterf->Draw("same");
   auto bflegend = new TLegend(0.72,0.72,0.9,0.88);
   bflegend->AddEntry(precalClusterb,"Back pre-cal.","l");
   bflegend->AddEntry(postcalClusterb,"Back post-cal.","l");
   bflegend->AddEntry(precalClusterf,"Front pre-cal.","l");
   bflegend->AddEntry(postcalClusterf,"Front post-cal.","l");
   bflegend->Draw();
   canbf->SaveAs("BGO_Back_Front_cal.pdf");

 

} 
 
 int main() {
   CalibrationCompare();
   return 0;
}  
