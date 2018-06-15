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

void bubble2THR(){

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
   std::string filemu1 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6mudecay1.root";
   std::string filemu2 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6mudecay2.root";
   std::string filemu3 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6mudecay3.root";
   std::string filemu5 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6mudecay5.root";
   std::string filemu10 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6mudecay10.root";
   std::string filemu20 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6mudecay20.root";
   std::string filex1 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6goldcascade1.root";
   std::string filex2 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6goldcascade2.root";
   std::string filex3 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6goldcascade3.root";
   std::string filex5 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6goldcascade5.root";
   std::string filex10 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6goldcascade10.root";
   std::string filex20 = "../../simdata/bubble2/bubble_Nevts_SciSphere_SciD_1e6goldcascade20.root";
   // With a 3-mm Al layer
   std::string fileAlmu1 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay1.root";
   std::string fileAlmu2 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay2.root";
   std::string fileAlmu3 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay3.root";
   std::string fileAlmu5 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay5.root";
   std::string fileAlmu10 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay10.root";
   std::string fileAlmu20 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6mudecay20.root";
   std::string fileAlx1 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade1.root";
   std::string fileAlx2 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade2.root";
   std::string fileAlx3 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade3.root";
   std::string fileAlx5 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade5.root";
   std::string fileAlx10 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade10.root";
   std::string fileAlx20 = "../../simdata/bubble2/bubble_3mm_Al_Nevts_SciSphere_SciD_1e6goldcascade20.root"; 
   // With 6-mm Al layer
   std::string file6Almu1 = "../../simdata/bubble2/bubble_6mm_Al_Nevts_SciSphere_SciD_1e6mudecay1.root";
   std::string file6Almu2 = "../../simdata/bubble2/bubble_6mm_Al_Nevts_SciSphere_SciD_1e6mudecay2.root";
   std::string file6Almu3 = "../../simdata/bubble2/bubble_6mm_Al_Nevts_SciSphere_SciD_1e6mudecay3.root";
   std::string file6Almu5 = "../../simdata/bubble2/bubble_6mm_Al_Nevts_SciSphere_SciD_1e6mudecay5.root";
   std::string file6Almu10 = "../../simdata/bubble2/bubble_6mm_Al_Nevts_SciSphere_SciD_1e6mudecay10.root";
   std::string file6Almu20 = "../../simdata/bubble2/bubble_6mm_Al_Nevts_SciSphere_SciD_1e6mudecay20.root";
   std::string file6Alx1 = "../../simdata/bubble2/bubble_6mm_Al_Nevts_SciSphere_SciD_1e6goldcascade1.root";
   std::string file6Alx2 = "../../simdata/bubble2/bubble_6mm_Al_Nevts_SciSphere_SciD_1e6goldcascade2.root";
   std::string file6Alx3 = "../../simdata/bubble2/bubble_6mm_Al_Nevts_SciSphere_SciD_1e6goldcascade3.root";
   std::string file6Alx5 = "../../simdata/bubble2/bubble_6mm_Al_Nevts_SciSphere_SciD_1e6goldcascade5.root";
   std::string file6Alx10 = "../../simdata/bubble2/bubble_6mm_Al_Nevts_SciSphere_SciD_1e6goldcascade10.root";
   std::string file6Alx20 = "../../simdata/bubble2/bubble_6mm_Al_Nevts_SciSphere_SciD_1e6goldcascade20.root";
   // With a 10-mm Al layer
   std::string file10Almu1 = "../../simdata/bubble2/bubble_10mm_Al_Nevts_SciSphere_SciD_1e6mudecay1.root";
   std::string file10Almu2 = "../../simdata/bubble2/bubble_10mm_Al_Nevts_SciSphere_SciD_1e6mudecay2.root";
   std::string file10Almu3 = "../../simdata/bubble2/bubble_10mm_Al_Nevts_SciSphere_SciD_1e6mudecay3.root";
   std::string file10Almu5 = "../../simdata/bubble2/bubble_10mm_Al_Nevts_SciSphere_SciD_1e6mudecay5.root";
   std::string file10Almu10 = "../../simdata/bubble2/bubble_10mm_Al_Nevts_SciSphere_SciD_1e6mudecay10.root";
   std::string file10Almu20 = "../../simdata/bubble2/bubble_10mm_Al_Nevts_SciSphere_SciD_1e6mudecay20.root";
   std::string file10Alx1 = "../../simdata/bubble2/bubble_10mm_Al_Nevts_SciSphere_SciD_1e6goldcascade1.root";
   std::string file10Alx2 = "../../simdata/bubble2/bubble_10mm_Al_Nevts_SciSphere_SciD_1e6goldcascade2.root";
   std::string file10Alx3 = "../../simdata/bubble2/bubble_10mm_Al_Nevts_SciSphere_SciD_1e6goldcascade3.root";
   std::string file10Alx5 = "../../simdata/bubble2/bubble_10mm_Al_Nevts_SciSphere_SciD_1e6goldcascade5.root";
   std::string file10Alx10 = "../../simdata/bubble2/bubble_10mm_Al_Nevts_SciSphere_SciD_1e6goldcascade10.root";
   std::string file10Alx20 = "../../simdata/bubble2/bubble_10mm_Al_Nevts_SciSphere_SciD_1e6goldcascade20.root"; 


   /*********************************/
   /*           Analysis            */
   /*********************************/

   const int nbins = 300;
  
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
   // 6-mm Al layer
   TFile* f6Almu1 = new TFile(TString(fileAlmu1));
   TFile* f6Almu2 = new TFile(TString(fileAlmu2));
   TFile* f6Almu3 = new TFile(TString(fileAlmu3));
   TFile* f6Almu5 = new TFile(TString(fileAlmu5));
   TFile* f6Almu10 = new TFile(TString(fileAlmu10));
   TFile* f6Almu20 = new TFile(TString(fileAlmu20));
   TFile* f6Alx1 = new TFile(TString(fileAlx1));
   TFile* f6Alx2 = new TFile(TString(fileAlx2));
   TFile* f6Alx3 = new TFile(TString(fileAlx3));
   TFile* f6Alx5 = new TFile(TString(fileAlx5));
   TFile* f6Alx10 = new TFile(TString(fileAlx10));
   TFile* f6Alx20 = new TFile(TString(fileAlx20));
   // 10-mm Al layer
   TFile* f10Almu1 = new TFile(TString(fileAlmu1));
   TFile* f10Almu2 = new TFile(TString(fileAlmu2));
   TFile* f10Almu3 = new TFile(TString(fileAlmu3));
   TFile* f10Almu5 = new TFile(TString(fileAlmu5));
   TFile* f10Almu10 = new TFile(TString(fileAlmu10));
   TFile* f10Almu20 = new TFile(TString(fileAlmu20));
   TFile* f10Alx1 = new TFile(TString(fileAlx1));
   TFile* f10Alx2 = new TFile(TString(fileAlx2));
   TFile* f10Alx3 = new TFile(TString(fileAlx3));
   TFile* f10Alx5 = new TFile(TString(fileAlx5));
   TFile* f10Alx10 = new TFile(TString(fileAlx10));
   TFile* f10Alx20 = new TFile(TString(fileAlx20));


   // 0-mm Al layer
   TH1F *hmu1 = new TH1F("hmu1","Edep",3*nbins+1,-0.05,45);
   TH1F *hmu2 = new TH1F("hmu2","Edep",3*nbins+1,-0.05,45);
   TH1F *hmu3 = new TH1F("hmu3","Edep",3*nbins+1,-0.05,45);
   TH1F *hmu5 = new TH1F("hmu5","Edep",3*nbins+1,-0.05,45);
   TH1F *hmu10 = new TH1F("hmu10","Edep",3*nbins+1,-0.05,45);
   TH1F *hmu20 = new TH1F("hmu20","Edep",3*nbins+1,-0.05,45);
   TH1F *hx1 = new TH1F("hx1","Edep",nbins+1,-0.05,15);
   TH1F *hx2 = new TH1F("hx2","Edep",nbins+1,-0.05,15);
   TH1F *hx3 = new TH1F("hx3","Edep",nbins+1,-0.05,15);
   TH1F *hx5 = new TH1F("hx5","Edep",nbins+1,-0.05,15);
   TH1F *hx10 = new TH1F("hx10","Edep",nbins+1,-0.05,15);
   TH1F *hx20 = new TH1F("hx20","Edep",nbins+1,-0.05,15);
   // 3-mm Al layer
   TH1F *hAlmu1 = new TH1F("hAlmu1","Edep",3*nbins+1,-0.05,45);
   TH1F *hAlmu2 = new TH1F("hAlmu2","Edep",3*nbins+1,-0.05,45);
   TH1F *hAlmu3 = new TH1F("hAlmu3","Edep",3*nbins+1,-0.05,45);
   TH1F *hAlmu5 = new TH1F("hAlmu5","Edep",3*nbins+1,-0.05,45);
   TH1F *hAlmu10 = new TH1F("hAlmu10","Edep",3*nbins+1,-0.05,45);
   TH1F *hAlmu20 = new TH1F("hAlmu20","Edep",3*nbins+1,-0.05,45);
   TH1F *hAlx1 = new TH1F("hAlx1","Edep",nbins+1,-0.05,15);
   TH1F *hAlx2 = new TH1F("hAlx2","Edep",nbins+1,-0.05,15);
   TH1F *hAlx3 = new TH1F("hAlx3","Edep",nbins+1,-0.05,15);
   TH1F *hAlx5 = new TH1F("hAlx5","Edep",nbins+1,-0.05,15);
   TH1F *hAlx10 = new TH1F("hAlx10","Edep",nbins+1,-0.05,15);
   TH1F *hAlx20 = new TH1F("hAlx20","Edep",nbins+1,-0.05,15);
   // 6-mm Al layer
   TH1F *h6Almu1 = new TH1F("h6Almu1","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Almu2 = new TH1F("h6Almu2","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Almu3 = new TH1F("h6Almu3","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Almu5 = new TH1F("h6Almu5","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Almu10 = new TH1F("h6Almu10","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Almu20 = new TH1F("h6Almu20","Edep",3*nbins+1,-0.05,45);
   TH1F *h6Alx1 = new TH1F("h6Alx1","Edep",nbins+1,-0.05,15);
   TH1F *h6Alx2 = new TH1F("h6Alx2","Edep",nbins+1,-0.05,15);
   TH1F *h6Alx3 = new TH1F("h6Alx3","Edep",nbins+1,-0.05,15);
   TH1F *h6Alx5 = new TH1F("h6Alx5","Edep",nbins+1,-0.05,15);
   TH1F *h6Alx10 = new TH1F("h6Alx10","Edep",nbins+1,-0.05,15);
   TH1F *h6Alx20 = new TH1F("h6Alx20","Edep",nbins+1,-0.05,15);
   // 10-mm Al layer
   TH1F *h10Almu1 = new TH1F("h10Almu1","Edep",3*nbins+1,-0.05,45);
   TH1F *h10Almu2 = new TH1F("h10Almu2","Edep",3*nbins+1,-0.05,45);
   TH1F *h10Almu3 = new TH1F("h10Almu3","Edep",3*nbins+1,-0.05,45);
   TH1F *h10Almu5 = new TH1F("h10Almu5","Edep",3*nbins+1,-0.05,45);
   TH1F *h10Almu10 = new TH1F("h10Almu10","Edep",3*nbins+1,-0.05,45);
   TH1F *h10Almu20 = new TH1F("h10Almu20","Edep",3*nbins+1,-0.05,45);
   TH1F *h10Alx1 = new TH1F("h10Alx1","Edep",nbins+1,-0.05,15);
   TH1F *h10Alx2 = new TH1F("h10Alx2","Edep",nbins+1,-0.05,15);
   TH1F *h10Alx3 = new TH1F("h10Alx3","Edep",nbins+1,-0.05,15);
   TH1F *h10Alx5 = new TH1F("h10Alx5","Edep",nbins+1,-0.05,15);
   TH1F *h10Alx10 = new TH1F("h10Alx10","Edep",nbins+1,-0.05,15);
   TH1F *h10Alx20 = new TH1F("h10Alx20","Edep",nbins+1,-0.05,15);
   
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
   // 6-mm Al layer
   TTree *t6Almu1 = (TTree*)f6Almu1->Get("Detector/SciDet");
   TTree *t6Almu2 = (TTree*)f6Almu2->Get("Detector/SciDet");
   TTree *t6Almu3 = (TTree*)f6Almu3->Get("Detector/SciDet");
   TTree *t6Almu5 = (TTree*)f6Almu5->Get("Detector/SciDet");
   TTree *t6Almu10 = (TTree*)f6Almu10->Get("Detector/SciDet");
   TTree *t6Almu20 = (TTree*)f6Almu20->Get("Detector/SciDet");
   TTree *t6Alx1 = (TTree*)f6Alx1->Get("Detector/SciDet");
   TTree *t6Alx2 = (TTree*)f6Alx2->Get("Detector/SciDet");
   TTree *t6Alx3 = (TTree*)f6Alx3->Get("Detector/SciDet");
   TTree *t6Alx5 = (TTree*)f6Alx5->Get("Detector/SciDet");
   TTree *t6Alx10 = (TTree*)f6Alx10->Get("Detector/SciDet");
   TTree *t6Alx20 = (TTree*)f6Alx20->Get("Detector/SciDet"); 
   // 10-mm Al layer
   TTree *t10Almu1 = (TTree*)f10Almu1->Get("Detector/SciDet");
   TTree *t10Almu2 = (TTree*)f10Almu2->Get("Detector/SciDet");
   TTree *t10Almu3 = (TTree*)f10Almu3->Get("Detector/SciDet");
   TTree *t10Almu5 = (TTree*)f10Almu5->Get("Detector/SciDet");
   TTree *t10Almu10 = (TTree*)f10Almu10->Get("Detector/SciDet");
   TTree *t10Almu20 = (TTree*)f10Almu20->Get("Detector/SciDet");
   TTree *t10Alx1 = (TTree*)f10Alx1->Get("Detector/SciDet");
   TTree *t10Alx2 = (TTree*)f10Alx2->Get("Detector/SciDet");
   TTree *t10Alx3 = (TTree*)f10Alx3->Get("Detector/SciDet");
   TTree *t10Alx5 = (TTree*)f10Alx5->Get("Detector/SciDet");
   TTree *t10Alx10 = (TTree*)f10Alx10->Get("Detector/SciDet");
   TTree *t10Alx20 = (TTree*)f10Alx20->Get("Detector/SciDet"); 
   
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
   // 6-mm Al layer
   t6Almu1->Draw("Edep>>h6Almu1","","");
   t6Almu2->Draw("Edep>>h6Almu2","","");
   t6Almu3->Draw("Edep>>h6Almu3","","");
   t6Almu5->Draw("Edep>>h6Almu5","","");
   t6Almu10->Draw("Edep>>h6Almu10","","");
   t6Almu20->Draw("Edep>>h6Almu20","","");
   t6Alx1->Draw("Edep>>h6Alx1","","");
   t6Alx2->Draw("Edep>>h6Alx2","","");
   t6Alx3->Draw("Edep>>h6Alx3","","");
   t6Alx5->Draw("Edep>>h6Alx5","","");
   t6Alx10->Draw("Edep>>h6Alx10","","");
   t6Alx20->Draw("Edep>>h6Alx20","","");
   // 10-mm Al layer
   t10Almu1->Draw("Edep>>h10Almu1","","");
   t10Almu2->Draw("Edep>>h10Almu2","","");
   t10Almu3->Draw("Edep>>h10Almu3","","");
   t10Almu5->Draw("Edep>>h10Almu5","","");
   t10Almu10->Draw("Edep>>h10Almu10","","");
   t10Almu20->Draw("Edep>>h10Almu20","","");
   t10Alx1->Draw("Edep>>h10Alx1","","");
   t10Alx2->Draw("Edep>>h10Alx2","","");
   t10Alx3->Draw("Edep>>h10Alx3","","");
   t10Alx5->Draw("Edep>>h10Alx5","","");
   t10Alx10->Draw("Edep>>h10Alx10","","");
   t10Alx20->Draw("Edep>>h10Alx20","","");
   
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
   // 6-mm Al layer
   h6Almu1->SetLineColor(kRed);
   h6Almu2->SetLineColor(kRed);
   h6Almu3->SetLineColor(kRed);
   h6Almu5->SetLineColor(kRed);
   h6Almu10->SetLineColor(kRed);
   h6Almu20->SetLineColor(kRed);
   h6Alx1->SetLineColor(kRed);
   h6Alx2->SetLineColor(kRed);
   h6Alx3->SetLineColor(kRed);
   h6Alx5->SetLineColor(kRed);
   h6Alx10->SetLineColor(kRed);
   h6Alx20->SetLineColor(kRed);
   // 10-mm Al layer
   h10Almu1->SetLineColor(kRed);
   h10Almu2->SetLineColor(kRed);
   h10Almu3->SetLineColor(kRed);
   h10Almu5->SetLineColor(kRed);
   h10Almu10->SetLineColor(kRed);
   h10Almu20->SetLineColor(kRed);
   h10Alx1->SetLineColor(kRed);
   h10Alx2->SetLineColor(kRed);
   h10Alx3->SetLineColor(kRed);
   h10Alx5->SetLineColor(kRed);
   h10Alx10->SetLineColor(kRed);
   h10Alx20->SetLineColor(kRed);
   
   float binCentersmu1[nbins] = {};
   float binCentersAlmu1[nbins] = {};
   float binCenters6Almu1[nbins] = {};
   float binCenters10Almu1[nbins] = {};
   float binCentersx1[nbins] = {};
   float binCentersAlx1[nbins] = {};
   float binCenters6Alx1[nbins] = {};
   float binCenters10Alx1[nbins] = {};
   float binCentersmu2[nbins] = {};
   float binCentersAlmu2[nbins] = {};
   float binCenters6Almu2[nbins] = {};
   float binCenters10Almu2[nbins] = {};
   float binCentersx2[nbins] = {};
   float binCentersAlx2[nbins] = {};
   float binCenters6Alx2[nbins] = {};
   float binCenters10Alx2[nbins] = {};
   float binCentersmu3[nbins] = {};
   float binCentersAlmu3[nbins] = {};
   float binCenters6Almu3[nbins] = {};
   float binCenters10Almu3[nbins] = {};
   float binCentersx3[nbins] = {};
   float binCentersAlx3[nbins] = {};
   float binCenters6Alx3[nbins] = {};
   float binCenters10Alx3[nbins] = {};
   float binCentersmu5[nbins] = {};
   float binCentersAlmu5[nbins] = {};
   float binCenters6Almu5[nbins] = {};
   float binCenters10Almu5[nbins] = {};
   float binCentersx5[nbins] = {};
   float binCentersAlx5[nbins] = {};
   float binCenters6Alx5[nbins] = {};
   float binCenters10Alx5[nbins] = {};
   float binCentersmu10[nbins] = {};
   float binCentersAlmu10[nbins] = {};
   float binCenters6Almu10[nbins] = {};
   float binCenters10Almu10[nbins] = {};
   float binCentersx10[nbins] = {};
   float binCentersAlx10[nbins] = {};
   float binCenters6Alx10[nbins] = {};
   float binCenters10Alx10[nbins] = {};
   float binCentersmu20[nbins] = {};
   float binCentersAlmu20[nbins] = {};
   float binCenters6Almu20[nbins] = {};
   float binCenters10Almu20[nbins] = {};
   float binCentersx20[nbins] = {};
   float binCentersAlx20[nbins] = {};
   float binCenters6Alx20[nbins] = {};
   float binCenters10Alx20[nbins] = {};

   float integralsmu1[nbins] = {};
   float integralsAlmu1[nbins] = {};
   float integrals6Almu1[nbins] = {};
   float integrals10Almu1[nbins] = {};
   float integralsx1[nbins] = {};
   float integralsAlx1[nbins] = {};
   float integrals6Alx1[nbins] = {};
   float integrals10Alx1[nbins] = {};
   float integralsmu2[nbins] = {};
   float integralsAlmu2[nbins] = {};
   float integrals6Almu2[nbins] = {};
   float integrals10Almu2[nbins] = {};
   float integralsx2[nbins] = {};
   float integralsAlx2[nbins] = {};
   float integrals6Alx2[nbins] = {};
   float integrals10Alx2[nbins] = {};
   float integralsmu3[nbins] = {};
   float integralsAlmu3[nbins] = {};
   float integrals6Almu3[nbins] = {};
   float integrals10Almu3[nbins] = {};
   float integralsx3[nbins] = {};
   float integralsAlx3[nbins] = {};
   float integrals6Alx3[nbins] = {};
   float integrals10Alx3[nbins] = {};
   float integralsmu5[nbins] = {};
   float integralsAlmu5[nbins] = {};
   float integrals6Almu5[nbins] = {};
   float integrals10Almu5[nbins] = {};
   float integralsx5[nbins] = {};
   float integralsAlx5[nbins] = {};
   float integrals6Alx5[nbins] = {};
   float integrals10Alx5[nbins] = {};
   float integralsmu10[nbins] = {};
   float integralsAlmu10[nbins] = {};
   float integrals6Almu10[nbins] = {};
   float integrals10Almu10[nbins] = {};
   float integralsx10[nbins] = {};
   float integralsAlx10[nbins] = {};
   float integrals6Alx10[nbins] = {};
   float integrals10Alx10[nbins] = {};
   float integralsmu20[nbins] = {};
   float integralsAlmu20[nbins] = {};
   float integrals6Almu20[nbins] = {};
   float integrals10Almu20[nbins] = {};
   float integralsx20[nbins] = {};
   float integralsAlx20[nbins] = {};
   float integrals6Alx20[nbins] = {};
   float integrals10Alx20[nbins] = {};

   float binCentermu1, binCenterAlmu1, binCenterx1, binCenterAlx1;
   float binCenter6Almu1, binCenter10Almu1, binCenter6Alx1, binCenter10Alx1;
   float integralmu1, integralAlmu1, integralx1, integralAlx1;
   float integral6Almu1, integral10Almu1, integral6Alx1, integral10Alx1;
   float binCentermu2, binCenterAlmu2, binCenterx2, binCenterAlx2;
   float binCenter6Almu2, binCenter10Almu2, binCenter6Alx2, binCenter10Alx2;
   float integralmu2, integralAlmu2, integralx2, integralAlx2;
   float integral6Almu2, integral10Almu2, integral6Alx2, integral10Alx2;
   float binCentermu3, binCenterAlmu3, binCenterx3, binCenterAlx3;
   float binCenter6Almu3, binCenter10Almu3, binCenter6Alx3, binCenter10Alx3;
   float integralmu3, integralAlmu3, integralx3, integralAlx3;
   float integral6Almu3, integral10Almu3, integral6Alx3, integral10Alx3;
   float binCentermu5, binCenterAlmu5, binCenterx5, binCenterAlx5;
   float binCenter6Almu5, binCenter10Almu5, binCenter6Alx5, binCenter10Alx5;
   float integralmu5, integralAlmu5, integralx5, integralAlx5;
   float integral6Almu5, integral10Almu5, integral6Alx5, integral10Alx5;
   float binCentermu10, binCenterAlmu10, binCenterx10, binCenterAlx10;
   float binCenter6Almu10, binCenter10Almu10, binCenter6Alx10, binCenter10Alx10;
   float integralmu10, integralAlmu10, integralx10, integralAlx10;
   float integral6Almu10, integral10Almu10, integral6Alx10, integral10Alx10;
   float binCentermu20, binCenterAlmu20, binCenterx20, binCenterAlx20;
   float binCenter6Almu20, binCenter10Almu20, binCenter6Alx20, binCenter10Alx20;
   float integralmu20, integralAlmu20, integralx20, integralAlx20;
   float integral6Almu20, integral10Almu20, integral6Alx20, integral10Alx20;
   
   
   // Filling the arrays
   for (int i=1; i<=nbins; i++) {
	   // LS: BinCentermu1 is not the center but the lower edge of the (i+1)th bin
	   binCentermu1 = hmu1->GetXaxis()->GetBinLowEdge(i+1); // 1-mm
	   binCenterAlmu1 = hAlmu1->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Almu1 = h6Almu1->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter10Almu1 = h10Almu1->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx1 = hx1->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterAlx1 = hAlx1->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx1 = h6Alx1->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter10Alx1 = h10Alx1->GetXaxis()->GetBinLowEdge(i+1);
	   binCentermu2 = hmu2->GetXaxis()->GetBinLowEdge(i+1); // 2-mm
	   binCenterAlmu2 = hAlmu2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Almu2 = h6Almu2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter10Almu2 = h10Almu2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx2 = hx2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterAlx2 = hAlx2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx2 = h6Alx2->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter10Alx2 = h10Alx2->GetXaxis()->GetBinLowEdge(i+1);
	   binCentermu3 = hmu3->GetXaxis()->GetBinLowEdge(i+1); // 3-mm
	   binCenterAlmu3 = hAlmu3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Almu3 = h6Almu3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter10Almu3 = h10Almu3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx3 = hx3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterAlx3 = hAlx3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx3 = h6Alx3->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter10Alx3 = h10Alx3->GetXaxis()->GetBinLowEdge(i+1);
	   binCentermu5 = hmu5->GetXaxis()->GetBinLowEdge(i+1); // 5-mm
	   binCenterAlmu5 = hAlmu5->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Almu5 = h6Almu5->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter10Almu5 = h10Almu5->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx5 = hx5->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterAlx5 = hAlx5->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx5 = h6Alx5->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter10Alx5 = h10Alx5->GetXaxis()->GetBinLowEdge(i+1);
	   binCentermu10 = hmu10->GetXaxis()->GetBinLowEdge(i+1); // 10-mm
	   binCenterAlmu10 = hAlmu10->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Almu10 = h6Almu10->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter10Almu10 = h10Almu10->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx10 = hx10->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterAlx10 = hAlx10->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx10 = h6Alx10->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter10Alx10 = h10Alx10->GetXaxis()->GetBinLowEdge(i+1);
	   binCentermu20 = hmu20->GetXaxis()->GetBinLowEdge(i+1); // 20-mm
	   binCenterAlmu20 = hAlmu20->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Almu20 = h6Almu20->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter10Almu20 = h10Almu20->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterx20 = hx20->GetXaxis()->GetBinLowEdge(i+1);
	   binCenterAlx20 = hAlx20->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter6Alx20 = h6Alx20->GetXaxis()->GetBinLowEdge(i+1);
	   binCenter10Alx20 = h10Alx20->GetXaxis()->GetBinLowEdge(i+1);

	   integralmu1 = hmu1->Integral(0,i,""); // includes underflow and overflow bins
	   integralAlmu1 = hAlmu1->Integral(0,i,"");
       integral6Almu1 = h6Almu1->Integral(0,i,"");
       integral10Almu1 = h10Almu1->Integral(0,i,"");
	   integralx1 = (hx1->Integral(0,nbins+1,""))-(hx1->Integral(0,i,""));
	   integralAlx1 = (hAlx1->Integral(0,nbins+1,""))-(hAlx1->Integral(0,i,""));
       integral6Alx1 = (h6Alx1->Integral(0,nbins+1,""))-(h6Alx1->Integral(0,i,""));
       integral10Alx1 = (h10Alx1->Integral(0,nbins+1,""))-(h10Alx1->Integral(0,i,""));
	   integralmu2 = hmu2->Integral(0,i,""); // includes underflow and overflow bins
	   integralAlmu2 = hAlmu2->Integral(0,i,"");
       integral6Almu2 = h6Almu2->Integral(0,i,"");
       integral10Almu2 = h10Almu2->Integral(0,i,"");
	   integralx2 = (hx2->Integral(0,nbins+1,""))-(hx2->Integral(0,i,""));
	   integralAlx2 = (hAlx2->Integral(0,nbins+1,""))-(hAlx2->Integral(0,i,""));
	   integral6Alx2 = (h6Alx2->Integral(0,nbins+1,""))-(h6Alx2->Integral(0,i,""));
       integral10Alx2 = (h10Alx2->Integral(0,nbins+1,""))-(h10Alx2->Integral(0,i,""));
	   integralmu3 = hmu3->Integral(0,i,""); // includes underflow and overflow bins
	   integralAlmu3 = hAlmu3->Integral(0,i,"");
       integral6Almu3 = h6Almu3->Integral(0,i,"");
       integral10Almu3 = h10Almu3->Integral(0,i,"");
	   integralx3 = (hx3->Integral(0,nbins+1,""))-(hx3->Integral(0,i,""));
	   integralAlx3 = (hAlx3->Integral(0,nbins+1,""))-(hAlx3->Integral(0,i,""));
	   integral6Alx3 = (h6Alx3->Integral(0,nbins+1,""))-(h6Alx3->Integral(0,i,""));
       integral10Alx3 = (h10Alx3->Integral(0,nbins+1,""))-(h10Alx3->Integral(0,i,""));
	   integralmu5 = hmu5->Integral(0,i,""); // includes underflow and overflow bins
	   integralAlmu5 = hAlmu5->Integral(0,i,"");
       integral6Almu5 = h6Almu5->Integral(0,i,"");
       integral10Almu5 = h10Almu5->Integral(0,i,"");
	   integralx5 = (hx5->Integral(0,nbins+1,""))-(hx5->Integral(0,i,""));
	   integralAlx5 = (hAlx5->Integral(0,nbins+1,""))-(hAlx5->Integral(0,i,""));
	   integral6Alx5 = (h6Alx5->Integral(0,nbins+1,""))-(h6Alx5->Integral(0,i,""));
       integral10Alx5 = (h10Alx5->Integral(0,nbins+1,""))-(h10Alx5->Integral(0,i,""));
	   integralmu10 = hmu10->Integral(0,i,""); // includes underflow and overflow bins
	   integralAlmu10 = hAlmu10->Integral(0,i,"");
       integral6Almu10 = h6Almu10->Integral(0,i,"");
       integral10Almu10 = h10Almu10->Integral(0,i,"");
	   integralx10 = (hx10->Integral(0,nbins+1,""))-(hx10->Integral(0,i,""));
	   integralAlx10 = (hAlx10->Integral(0,nbins+1,""))-(hAlx10->Integral(0,i,""));
	   integral6Alx10 = (h6Alx10->Integral(0,nbins+1,""))-(h6Alx10->Integral(0,i,""));
       integral10Alx10 = (h10Alx10->Integral(0,nbins+1,""))-(h10Alx10->Integral(0,i,""));
	   integralmu20 = hmu20->Integral(0,i,""); // includes underflow and overflow bins
	   integralAlmu20 = hAlmu20->Integral(0,i,"");
       integral6Almu20 = h6Almu20->Integral(0,i,"");
       integral10Almu20 = h10Almu20->Integral(0,i,"");
	   integralx20 = (hx20->Integral(0,nbins+1,""))-(hx20->Integral(0,i,""));
	   integralAlx20 = (hAlx20->Integral(0,nbins+1,""))-(hAlx20->Integral(0,i,""));
	   integral6Alx20 = (h6Alx20->Integral(0,nbins+1,""))-(h6Alx20->Integral(0,i,""));
       integral10Alx20 = (h10Alx20->Integral(0,nbins+1,""))-(h10Alx20->Integral(0,i,""));

	   
       binCentersmu1[(const int)(i-1)] = binCentermu1; // 1-mm
       binCentersAlmu1[(const int)(i-1)] = binCenterAlmu1;
       binCenters6Almu1[(const int)(i-1)] = binCenter6Almu1;
       binCenters10Almu1[(const int)(i-1)] = binCenter10Almu1;
       binCentersx1[(const int)(i-1)] = binCenterx1;
       binCentersAlx1[(const int)(i-1)] = binCenterAlx1;
       binCenters6Alx1[(const int)(i-1)] = binCenter6Alx1;
       binCenters10Alx1[(const int)(i-1)] = binCenter10Alx1;
       binCentersmu2[(const int)(i-1)] = binCentermu2; // 2-mm
       binCentersAlmu2[(const int)(i-1)] = binCenterAlmu2;
       binCenters6Almu2[(const int)(i-1)] = binCenter6Almu2;
       binCenters10Almu2[(const int)(i-1)] = binCenter10Almu2;
       binCentersx2[(const int)(i-1)] = binCenterx2;
       binCentersAlx2[(const int)(i-1)] = binCenterAlx2;
       binCenters6Alx2[(const int)(i-1)] = binCenter6Alx2;
       binCenters10Alx2[(const int)(i-1)] = binCenter10Alx2;
       binCentersmu3[(const int)(i-1)] = binCentermu3; // 3-mm
       binCentersAlmu3[(const int)(i-1)] = binCenterAlmu3;
       binCenters6Almu3[(const int)(i-1)] = binCenter6Almu3;
       binCenters10Almu3[(const int)(i-1)] = binCenter10Almu3;
       binCentersx3[(const int)(i-1)] = binCenterx3;
       binCentersAlx3[(const int)(i-1)] = binCenterAlx3;
       binCenters6Alx3[(const int)(i-1)] = binCenter6Alx3;
       binCenters10Alx3[(const int)(i-1)] = binCenter10Alx3;
       binCentersmu5[(const int)(i-1)] = binCentermu5; // 5-mm
       binCentersAlmu5[(const int)(i-1)] = binCenterAlmu5;
       binCenters6Almu5[(const int)(i-1)] = binCenter6Almu5;
       binCenters10Almu5[(const int)(i-1)] = binCenter10Almu5;
       binCentersx5[(const int)(i-1)] = binCenterx5;
       binCentersAlx5[(const int)(i-1)] = binCenterAlx5;
       binCenters6Alx5[(const int)(i-1)] = binCenter6Alx5;
       binCenters10Alx5[(const int)(i-1)] = binCenter10Alx5;
       binCentersmu10[(const int)(i-1)] = binCentermu10; // 10-mm
       binCentersAlmu10[(const int)(i-1)] = binCenterAlmu10;
       binCenters6Almu10[(const int)(i-1)] = binCenter6Almu10;
       binCenters10Almu10[(const int)(i-1)] = binCenter10Almu10;
       binCentersx10[(const int)(i-1)] = binCenterx10;
       binCentersAlx10[(const int)(i-1)] = binCenterAlx10;
       binCenters6Alx10[(const int)(i-1)] = binCenter6Alx10;
       binCenters10Alx10[(const int)(i-1)] = binCenter10Alx10;
       binCentersmu20[(const int)(i-1)] = binCentermu20; // 20-mm
       binCentersAlmu20[(const int)(i-1)] = binCenterAlmu20;
       binCenters6Almu20[(const int)(i-1)] = binCenter6Almu20;
       binCenters10Almu20[(const int)(i-1)] = binCenter10Almu20;
       binCentersx20[(const int)(i-1)] = binCenterx20;
       binCentersAlx20[(const int)(i-1)] = binCenterAlx20;
       binCenters6Alx20[(const int)(i-1)] = binCenter6Alx20;
       binCenters10Alx20[(const int)(i-1)] = binCenter10Alx20;
       
       integralsmu1[(const int)(i-1)] = integralmu1/(hmu1->GetEntries()); // 1-mm
       integralsAlmu1[(const int)(i-1)] = integralAlmu1/(hAlmu1->GetEntries());
       integrals6Almu1[(const int)(i-1)] = integral6Almu1/(h6Almu1->GetEntries());
       integrals10Almu1[(const int)(i-1)] = integral10Almu1/(h10Almu1->GetEntries());
       integralsx1[(const int)(i-1)] = integralx1/(hx1->GetEntries());
       integralsAlx1[(const int)(i-1)] = integralAlx1/(hAlx1->GetEntries());
       integrals6Alx1[(const int)(i-1)] = integral6Alx1/(h6Alx1->GetEntries());
       integrals10Alx1[(const int)(i-1)] = integral10Alx1/(h10Alx1->GetEntries());
       integralsmu2[(const int)(i-1)] = integralmu2/(hmu2->GetEntries()); // 2-mm
       integralsAlmu2[(const int)(i-1)] = integralAlmu2/(hAlmu2->GetEntries());
       integrals6Almu2[(const int)(i-1)] = integral6Almu2/(h6Almu2->GetEntries());
       integrals10Almu2[(const int)(i-1)] = integral10Almu2/(h10Almu2->GetEntries());
       integralsx2[(const int)(i-1)] = integralx2/(hx2->GetEntries());
       integralsAlx2[(const int)(i-1)] = integralAlx2/(hAlx2->GetEntries());
       integrals6Alx2[(const int)(i-1)] = integral6Alx2/(h6Alx2->GetEntries());
       integrals10Alx2[(const int)(i-1)] = integral10Alx2/(h10Alx2->GetEntries());
       integralsmu3[(const int)(i-1)] = integralmu3/(hmu3->GetEntries()); // 3-mm
       integralsAlmu3[(const int)(i-1)] = integralAlmu3/(hAlmu3->GetEntries());
       integrals6Almu3[(const int)(i-1)] = integral6Almu3/(h6Almu3->GetEntries());
       integrals10Almu3[(const int)(i-1)] = integral10Almu3/(h10Almu3->GetEntries());
       integralsx3[(const int)(i-1)] = integralx3/(hx3->GetEntries());
       integralsAlx3[(const int)(i-1)] = integralAlx3/(hAlx3->GetEntries());
       integrals6Alx3[(const int)(i-1)] = integral6Alx3/(h6Alx3->GetEntries());
       integrals10Alx3[(const int)(i-1)] = integral10Alx3/(h10Alx3->GetEntries());
       integralsmu5[(const int)(i-1)] = integralmu5/(hmu5->GetEntries()); // 5-mm
       integralsAlmu5[(const int)(i-1)] = integralAlmu5/(hAlmu5->GetEntries());
       integrals6Almu5[(const int)(i-1)] = integral6Almu5/(h6Almu5->GetEntries());
       integrals10Almu5[(const int)(i-1)] = integral10Almu5/(h10Almu5->GetEntries());
       integralsx5[(const int)(i-1)] = integralx5/(hx5->GetEntries());
       integralsAlx5[(const int)(i-1)] = integralAlx5/(hAlx5->GetEntries());
       integrals6Alx5[(const int)(i-1)] = integral6Alx5/(h6Alx5->GetEntries());
       integrals10Alx5[(const int)(i-1)] = integral10Alx5/(h10Alx5->GetEntries());
       integralsmu10[(const int)(i-1)] = integralmu10/(hmu10->GetEntries()); // 10-mm
       integralsAlmu10[(const int)(i-1)] = integralAlmu10/(hAlmu10->GetEntries());
       integrals6Almu10[(const int)(i-1)] = integral6Almu10/(h6Almu10->GetEntries());
       integrals10Almu10[(const int)(i-1)] = integral10Almu10/(h10Almu10->GetEntries());
       integralsx10[(const int)(i-1)] = integralx10/(hx10->GetEntries());
       integralsAlx10[(const int)(i-1)] = integralAlx10/(hAlx10->GetEntries());
       integrals6Alx10[(const int)(i-1)] = integral6Alx10/(h6Alx10->GetEntries());
       integrals10Alx10[(const int)(i-1)] = integral10Alx10/(h10Alx10->GetEntries());
       integralsmu20[(const int)(i-1)] = integralmu20/(hmu20->GetEntries()); // 20-mm
       integralsAlmu20[(const int)(i-1)] = integralAlmu20/(hAlmu20->GetEntries());
       integrals6Almu20[(const int)(i-1)] = integral6Almu20/(h6Almu20->GetEntries());
       integrals10Almu20[(const int)(i-1)] = integral10Almu20/(h10Almu20->GetEntries());
       integralsx20[(const int)(i-1)] = integralx20/(hx20->GetEntries());
       integralsAlx20[(const int)(i-1)] = integralAlx20/(hAlx20->GetEntries());
       integrals6Alx20[(const int)(i-1)] = integral6Alx20/(h6Alx20->GetEntries());
       integrals10Alx20[(const int)(i-1)] = integral10Alx20/(h10Alx20->GetEntries());
   }
   

   TCanvas *c = new TCanvas("c","E_{THR}",800,600);
   c->Divide(3,2);
   c->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu1 = new TGraph(nbins,binCentersmu1,integralsmu1);
   grmu1->SetTitle("1-mm SciD + 0-mm Al");
   grmu1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu1->GetXaxis()->SetRangeUser(0,1);
   grmu1->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu1->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu1->GetYaxis()->SetTitleOffset(1.8);
   grmu1->SetMarkerColor(kBlack);
   grmu1->SetMarkerStyle(33);
   grmu1->SetLineColor(kBlack);
   grmu1->Draw("ALP");
   TGraph *grx1 = new TGraph(nbins,binCentersx1,integralsx1);
   grx1->GetXaxis()->SetRangeUser(0,0.4);
   grx1->SetMarkerColor(kRed);
   grx1->SetMarkerStyle(31);
   grx1->SetLineColor(kRed);
   grx1->Draw("LP");
   leg1 = new TLegend(0.2,-0.01,0.4,0.08);
   leg1->AddEntry(grmu1,"#mu - decay","lp");
   leg1->AddEntry(grx1,"X-rays","lp");
   leg1->Draw();
   
   c->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu2 = new TGraph(nbins,binCentersmu2,integralsmu2);
   grmu2->SetTitle("2-mm SciD + 0-mm Al");
   grmu2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu2->GetXaxis()->SetRangeUser(0,1.4);
   grmu2->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu2->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu2->GetYaxis()->SetTitleOffset(1.8);
   grmu2->SetMarkerColor(kBlack);
   grmu2->SetMarkerStyle(33);
   grmu2->SetLineColor(kBlack);
   grmu2->Draw("ALP");
   TGraph *grx2 = new TGraph(nbins,binCentersx2,integralsx2);
   grx2->SetMarkerColor(kRed);
   grx2->SetMarkerStyle(31);
   grx2->SetLineColor(kRed);
   grx2->Draw("LP");
   leg2 = new TLegend(0.2,-0.01,0.4,0.08);
   leg2->AddEntry(grmu2,"#mu - decay","lp");
   leg2->AddEntry(grx2,"X-rays","lp");
   leg2->Draw();   

   c->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu3 = new TGraph(nbins,binCentersmu3,integralsmu3);
   grmu3->SetTitle("3-mm SciD + 0-mm Al");
   grmu3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu3->GetXaxis()->SetRangeUser(0,1.8);
   grmu3->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu3->GetYaxis()->SetTitleOffset(1.8);
   grmu3->SetMarkerColor(kBlack);
   grmu3->SetMarkerStyle(33);
   grmu3->SetLineColor(kBlack);
   grmu3->Draw("ALP");
   TGraph *grx3 = new TGraph(nbins,binCentersx3,integralsx3);
   grx3->SetMarkerColor(kRed);
   grx3->SetMarkerStyle(31);
   grx3->SetLineColor(kRed);
   grx3->Draw("LP");
   leg3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg3->AddEntry(grmu3,"#mu - decay","lp");
   leg3->AddEntry(grx3,"X-rays","lp");
   leg3->Draw();
   
   c->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu5 = new TGraph(nbins,binCentersmu5,integralsmu5);
   grmu5->SetTitle("5-mm SciD + 0-mm Al");
   grmu5->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu5->GetXaxis()->SetRangeUser(0,2);
   grmu5->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu5->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu5->GetYaxis()->SetTitleOffset(1.8);
   grmu5->SetMarkerColor(kBlack);
   grmu5->SetMarkerStyle(33);
   grmu5->SetLineColor(kBlack);
   grmu5->Draw("ALP");
   TGraph *grx5 = new TGraph(nbins,binCentersx5,integralsx5);
   grx5->SetMarkerColor(kRed);
   grx5->SetMarkerStyle(31);
   grx5->SetLineColor(kRed);
   grx5->Draw("LP");
   leg5 = new TLegend(0.2,-0.01,0.4,0.08);
   leg5->AddEntry(grmu5,"#mu - decay","lp");
   leg5->AddEntry(grx5,"X-rays","lp");
   leg5->Draw();
   
   c->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu10 = new TGraph(nbins,binCentersmu10,integralsmu10);
   grmu10->SetTitle("10-mm SciD + 0-mm Al");
   grmu10->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu10->GetXaxis()->SetRangeUser(0,3);
   grmu10->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu10->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu10->GetYaxis()->SetTitleOffset(1.8);
   grmu10->SetMarkerColor(kBlack);
   grmu10->SetMarkerStyle(33);
   grmu10->SetLineColor(kBlack);
   grmu10->Draw("ALP");
   TGraph *grx10 = new TGraph(nbins,binCentersx10,integralsx10);
   grx10->SetMarkerColor(kRed);
   grx10->SetMarkerStyle(31);
   grx10->SetLineColor(kRed);
   grx10->Draw("LP");
   leg10 = new TLegend(0.2,-0.01,0.4,0.08);
   leg10->AddEntry(grmu10,"#mu - decay","lp");
   leg10->AddEntry(grx10,"X-rays","lp");
   leg10->Draw();
     
   c->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grmu20 = new TGraph(nbins,binCentersmu20,integralsmu20);
   grmu20->SetTitle("20-mm SciD + 0-mm Al");
   grmu20->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grmu20->GetXaxis()->SetRangeUser(0,5);
   grmu20->GetYaxis()->SetRangeUser(1e-4,1.1);
   grmu20->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grmu20->GetYaxis()->SetTitleOffset(1.8);
   grmu20->SetMarkerColor(kBlack);
   grmu20->SetMarkerStyle(33);
   grmu20->SetLineColor(kBlack);
   grmu20->Draw("ALP");
   TGraph *grx20 = new TGraph(nbins,binCentersx20,integralsx20);
   grx20->SetMarkerColor(kRed);
   grx20->SetMarkerStyle(31);
   grx20->SetLineColor(kRed);
   grx20->Draw("LP");
   leg20 = new TLegend(0.2,-0.01,0.4,0.08);
   leg20->AddEntry(grmu20,"#mu - decay","lp");
   leg20->AddEntry(grx20,"X-rays","lp");
   leg20->Draw();
   
   c->SaveAs("BubbleTHR_0mm_Al.pdf");
   c->SaveAs("BubbleTHR_0mm_Al.png");
   c->SaveAs("BubbleTHR_0mm_Al.C");
   
   
   
   TCanvas *d = new TCanvas("d","E_{THR}",800,600);
   d->Divide(3,2);
   d->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grAlmu1 = new TGraph(nbins,binCentersAlmu1,integralsAlmu1);
   grAlmu1->SetTitle("1-mm SciD + 3-mm Al");
   grAlmu1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grAlmu1->GetXaxis()->SetRangeUser(0,1);
   grAlmu1->GetYaxis()->SetRangeUser(1e-4,1.1);
   grAlmu1->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grAlmu1->GetYaxis()->SetTitleOffset(1.8);
   grAlmu1->SetMarkerColor(kBlack);
   grAlmu1->SetMarkerStyle(33);
   grAlmu1->SetLineColor(kBlack);
   grAlmu1->Draw("ALP");
   TGraph *grAlx1 = new TGraph(nbins,binCentersAlx1,integralsAlx1);
   grAlx1->SetMarkerColor(kRed);
   grAlx1->SetMarkerStyle(31);
   grAlx1->SetLineColor(kRed);
   grAlx1->Draw("LP");
   legAl1 = new TLegend(0.2,-0.01,0.4,0.08);
   legAl1->AddEntry(grAlmu1,"#mu - decay","lp");
   legAl1->AddEntry(grAlx1,"X-rays","lp");
   legAl1->Draw();
   
   d->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grAlmu2 = new TGraph(nbins,binCentersAlmu2,integralsAlmu2);
   grAlmu2->SetTitle("2-mm SciD + 3-mm Al");
   grAlmu2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grAlmu2->GetXaxis()->SetRangeUser(0,1.4);
   grAlmu2->GetYaxis()->SetRangeUser(1e-4,1.1);
   grAlmu2->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grAlmu2->GetYaxis()->SetTitleOffset(1.8);
   grAlmu2->SetMarkerColor(kBlack);
   grAlmu2->SetMarkerStyle(33);
   grAlmu2->SetLineColor(kBlack);
   grAlmu2->Draw("ALP");
   TGraph *grAlx2 = new TGraph(nbins,binCentersAlx2,integralsAlx2);
   grAlx2->SetMarkerColor(kRed);
   grAlx2->SetMarkerStyle(31);
   grAlx2->SetLineColor(kRed);
   grAlx2->Draw("LP");
   legAl2 = new TLegend(0.2,-0.01,0.4,0.08);
   legAl2->AddEntry(grAlmu2,"#mu - decay","lp");
   legAl2->AddEntry(grAlx2,"X-rays","lp");
   legAl2->Draw();

   d->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grAlmu3 = new TGraph(nbins,binCentersAlmu3,integralsAlmu3);
   grAlmu3->SetTitle("3-mm SciD + 3-mm Al");
   grAlmu3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grAlmu3->GetXaxis()->SetRangeUser(0,1.8);
   grAlmu3->GetYaxis()->SetRangeUser(1e-4,1.1);
   grAlmu3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grAlmu3->GetYaxis()->SetTitleOffset(1.8);
   grAlmu3->SetMarkerColor(kBlack);
   grAlmu3->SetMarkerStyle(33);
   grAlmu3->SetLineColor(kBlack);
   grAlmu3->Draw("ALP");
   TGraph *grAlx3 = new TGraph(nbins,binCentersAlx3,integralsAlx3);
   grAlx3->SetMarkerColor(kRed);
   grAlx3->SetMarkerStyle(31);
   grAlx3->SetLineColor(kRed);
   grAlx3->Draw("LP");
   legAl3 = new TLegend(0.2,-0.01,0.4,0.08);
   legAl3->AddEntry(grAlmu3,"#mu - decay","lp");
   legAl3->AddEntry(grAlx3,"X-rays","lp");
   legAl3->Draw();
   
   d->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grAlmu5 = new TGraph(nbins,binCentersAlmu5,integralsAlmu5);
   grAlmu5->SetTitle("5-mm SciD + 3-mm Al");
   grAlmu5->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grAlmu5->GetXaxis()->SetRangeUser(0,2);
   grAlmu5->GetYaxis()->SetRangeUser(1e-4,1.1);
   grAlmu5->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grAlmu5->GetYaxis()->SetTitleOffset(1.8);
   grAlmu5->SetMarkerColor(kBlack);
   grAlmu5->SetMarkerStyle(33);
   grAlmu5->SetLineColor(kBlack);
   grAlmu5->Draw("ALP");
   TGraph *grAlx5 = new TGraph(nbins,binCentersAlx5,integralsAlx5);
   grAlx5->SetMarkerColor(kRed);
   grAlx5->SetMarkerStyle(31);
   grAlx5->SetLineColor(kRed);
   grAlx5->Draw("LP");
   legAl5 = new TLegend(0.2,-0.01,0.4,0.08);
   legAl5->AddEntry(grAlmu5,"#mu - decay","lp");
   legAl5->AddEntry(grAlx5,"X-rays","lp");
   legAl5->Draw();
   
   d->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grAlmu10 = new TGraph(nbins,binCentersAlmu10,integralsAlmu10);
   grAlmu10->SetTitle("10-mm SciD + 3-mm Al");
   grAlmu10->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grAlmu10->GetXaxis()->SetRangeUser(0,3);
   grAlmu10->GetYaxis()->SetRangeUser(1e-4,1.1);
   grAlmu10->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grAlmu10->GetYaxis()->SetTitleOffset(1.8);
   grAlmu10->SetMarkerColor(kBlack);
   grAlmu10->SetMarkerStyle(33);
   grAlmu10->SetLineColor(kBlack);
   grAlmu10->Draw("ALP");
   TGraph *grAlx10 = new TGraph(nbins,binCentersAlx10,integralsAlx10);
   grAlx10->SetMarkerColor(kRed);
   grAlx10->SetMarkerStyle(31);
   grAlx10->SetLineColor(kRed);
   grAlx10->Draw("LP");
   legAl10 = new TLegend(0.2,-0.01,0.4,0.08);
   legAl10->AddEntry(grAlmu10,"#mu - decay","lp");
   legAl10->AddEntry(grAlx10,"X-rays","lp");
   legAl10->Draw();
     
   d->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grAlmu20 = new TGraph(nbins,binCentersAlmu20,integralsAlmu20);
   grAlmu20->SetTitle("20-mm SciD + 3-mm Al");
   grAlmu20->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grAlmu20->GetXaxis()->SetRangeUser(0,5);
   grAlmu20->GetYaxis()->SetRangeUser(1e-4,1.1);
   grAlmu20->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   grAlmu20->GetYaxis()->SetTitleOffset(1.8);
   grAlmu20->SetMarkerColor(kBlack);
   grAlmu20->SetMarkerStyle(33);
   grAlmu20->SetLineColor(kBlack);
   grAlmu20->Draw("ALP");
   TGraph *grAlx20 = new TGraph(nbins,binCentersAlx20,integralsAlx20);
   grAlx20->SetMarkerColor(kRed);
   grAlx20->SetMarkerStyle(31);
   grAlx20->SetLineColor(kRed);
   grAlx20->Draw("LP");
   legAl20 = new TLegend(0.2,-0.01,0.4,0.08);
   legAl20->AddEntry(grAlmu20,"#mu - decay","lp");
   legAl20->AddEntry(grAlx20,"X-rays","lp");
   legAl20->Draw();
   
   d->SaveAs("BubbleTHR_3mm_Al.pdf");
   d->SaveAs("BubbleTHR_3mm_Al.png");
   d->SaveAs("BubbleTHR_3mm_Al.C");



   TCanvas *e = new TCanvas("e","E_{THR}",800,600);
   e->Divide(3,2);
   e->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu1 = new TGraph(nbins,binCenters6Almu1,integrals6Almu1);
   gr6Almu1->SetTitle("1-mm SciD + 6-mm Al");
   gr6Almu1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu1->GetXaxis()->SetRangeUser(0,1);
   gr6Almu1->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu1->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu1->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu1->SetMarkerColor(kBlack);
   gr6Almu1->SetMarkerStyle(33);
   gr6Almu1->SetLineColor(kBlack);
   gr6Almu1->Draw("ALP");
   TGraph *gr6Alx1 = new TGraph(nbins,binCenters6Alx1,integrals6Alx1);
   gr6Alx1->SetMarkerColor(kRed);
   gr6Alx1->SetMarkerStyle(31);
   gr6Alx1->SetLineColor(kRed);
   gr6Alx1->Draw("LP");
   leg6Al1 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al1->AddEntry(gr6Almu1,"#mu - decay","lp");
   leg6Al1->AddEntry(gr6Alx1,"X-rays","lp");
   leg6Al1->Draw();
   
   e->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu2 = new TGraph(nbins,binCenters6Almu2,integrals6Almu2);
   gr6Almu2->SetTitle("2-mm SciD + 6-mm Al");
   gr6Almu2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu2->GetXaxis()->SetRangeUser(0,1.4);
   gr6Almu2->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu2->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu2->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu2->SetMarkerColor(kBlack);
   gr6Almu2->SetMarkerStyle(33);
   gr6Almu2->SetLineColor(kBlack);
   gr6Almu2->Draw("ALP");
   TGraph *gr6Alx2 = new TGraph(nbins,binCenters6Alx2,integrals6Alx2);
   gr6Alx2->SetMarkerColor(kRed);
   gr6Alx2->SetMarkerStyle(31);
   gr6Alx2->SetLineColor(kRed);
   gr6Alx2->Draw("LP");
   leg6Al2 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al2->AddEntry(gr6Almu2,"#mu - decay","lp");
   leg6Al2->AddEntry(gr6Alx2,"X-rays","lp");
   leg6Al2->Draw();

   e->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu3 = new TGraph(nbins,binCenters6Almu3,integrals6Almu3);
   gr6Almu3->SetTitle("3-mm SciD + 6-mm Al");
   gr6Almu3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu3->GetXaxis()->SetRangeUser(0,1.8);
   gr6Almu3->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu3->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu3->SetMarkerColor(kBlack);
   gr6Almu3->SetMarkerStyle(33);
   gr6Almu3->SetLineColor(kBlack);
   gr6Almu3->Draw("ALP");
   TGraph *gr6Alx3 = new TGraph(nbins,binCenters6Alx3,integrals6Alx3);
   gr6Alx3->SetMarkerColor(kRed);
   gr6Alx3->SetMarkerStyle(31);
   gr6Alx3->SetLineColor(kRed);
   gr6Alx3->Draw("LP");
   leg6Al3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al3->AddEntry(gr6Almu3,"#mu - decay","lp");
   leg6Al3->AddEntry(gr6Alx3,"X-rays","lp");
   leg6Al3->Draw();
   
   e->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu5 = new TGraph(nbins,binCenters6Almu5,integrals6Almu5);
   gr6Almu5->SetTitle("5-mm SciD + 6-mm Al");
   gr6Almu5->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu5->GetXaxis()->SetRangeUser(0,2);
   gr6Almu5->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu5->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu5->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu5->SetMarkerColor(kBlack);
   gr6Almu5->SetMarkerStyle(33);
   gr6Almu5->SetLineColor(kBlack);
   gr6Almu5->Draw("ALP");
   TGraph *gr6Alx5 = new TGraph(nbins,binCenters6Alx5,integrals6Alx5);
   gr6Alx5->SetMarkerColor(kRed);
   gr6Alx5->SetMarkerStyle(31);
   gr6Alx5->SetLineColor(kRed);
   gr6Alx5->Draw("LP");
   leg6Al5 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al5->AddEntry(gr6Almu5,"#mu - decay","lp");
   leg6Al5->AddEntry(gr6Alx5,"X-rays","lp");
   leg6Al5->Draw();
   
   e->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu10 = new TGraph(nbins,binCenters6Almu10,integrals6Almu10);
   gr6Almu10->SetTitle("10-mm SciD + 6-mm Al");
   gr6Almu10->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu10->GetXaxis()->SetRangeUser(0,3);
   gr6Almu10->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu10->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu10->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu10->SetMarkerColor(kBlack);
   gr6Almu10->SetMarkerStyle(33);
   gr6Almu10->SetLineColor(kBlack);
   gr6Almu10->Draw("ALP");
   TGraph *gr6Alx10 = new TGraph(nbins,binCenters6Alx10,integrals6Alx10);
   gr6Alx10->SetMarkerColor(kRed);
   gr6Alx10->SetMarkerStyle(31);
   gr6Alx10->SetLineColor(kRed);
   gr6Alx10->Draw("LP");
   leg6Al10 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al10->AddEntry(gr6Almu10,"#mu - decay","lp");
   leg6Al10->AddEntry(gr6Alx10,"X-rays","lp");
   leg6Al10->Draw();
     
   e->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr6Almu20 = new TGraph(nbins,binCenters6Almu20,integrals6Almu20);
   gr6Almu20->SetTitle("20-mm SciD + 6-mm Al");
   gr6Almu20->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr6Almu20->GetXaxis()->SetRangeUser(0,5);
   gr6Almu20->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr6Almu20->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr6Almu20->GetYaxis()->SetTitleOffset(1.8);
   gr6Almu20->SetMarkerColor(kBlack);
   gr6Almu20->SetMarkerStyle(33);
   gr6Almu20->SetLineColor(kBlack);
   gr6Almu20->Draw("ALP");
   TGraph *gr6Alx20 = new TGraph(nbins,binCenters6Alx20,integrals6Alx20);
   gr6Alx20->SetMarkerColor(kRed);
   gr6Alx20->SetMarkerStyle(31);
   gr6Alx20->SetLineColor(kRed);
   gr6Alx20->Draw("LP");
   leg6Al20 = new TLegend(0.2,-0.01,0.4,0.08);
   leg6Al20->AddEntry(gr6Almu20,"#mu - decay","lp");
   leg6Al20->AddEntry(gr6Alx20,"X-rays","lp");
   leg6Al20->Draw();
   
   e->SaveAs("BubbleTHR_6mm_Al.pdf");
   e->SaveAs("BubbleTHR_6mm_Al.png");
   e->SaveAs("BubbleTHR_6mm_Al.C");



   TCanvas *g = new TCanvas("g","E_{THR}",800,600);
   g->Divide(3,2);
   g->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr10Almu1 = new TGraph(nbins,binCenters10Almu1,integrals10Almu1);
   gr10Almu1->SetTitle("1-mm SciD + 10-mm Al");
   gr10Almu1->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr10Almu1->GetXaxis()->SetRangeUser(0,1);
   gr10Almu1->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr10Almu1->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr10Almu1->GetYaxis()->SetTitleOffset(1.8);
   gr10Almu1->SetMarkerColor(kBlack);
   gr10Almu1->SetMarkerStyle(33);
   gr10Almu1->SetLineColor(kBlack);
   gr10Almu1->Draw("ALP");
   TGraph *gr10Alx1 = new TGraph(nbins,binCenters10Alx1,integrals10Alx1);
   gr10Alx1->SetMarkerColor(kRed);
   gr10Alx1->SetMarkerStyle(31);
   gr10Alx1->SetLineColor(kRed);
   gr10Alx1->Draw("LP");
   leg10Al1 = new TLegend(0.2,-0.01,0.4,0.08);
   leg10Al1->AddEntry(gr10Almu1,"#mu - decay","lp");
   leg10Al1->AddEntry(gr10Alx1,"X-rays","lp");
   leg10Al1->Draw();
 
   g->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr10Almu2 = new TGraph(nbins,binCenters10Almu2,integrals10Almu2);
   gr10Almu2->SetTitle("2-mm SciD + 10-mm Al");
   gr10Almu2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr10Almu2->GetXaxis()->SetRangeUser(0,1.4);
   gr10Almu2->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr10Almu2->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr10Almu2->GetYaxis()->SetTitleOffset(1.8);
   gr10Almu2->SetMarkerColor(kBlack);
   gr10Almu2->SetMarkerStyle(33);
   gr10Almu2->SetLineColor(kBlack);
   gr10Almu2->Draw("ALP");
   TGraph *gr10Alx2 = new TGraph(nbins,binCenters10Alx2,integrals10Alx2);
   gr10Alx2->SetMarkerColor(kRed);
   gr10Alx2->SetMarkerStyle(31);
   gr10Alx2->SetLineColor(kRed);
   gr10Alx2->Draw("LP");
   leg10Al2 = new TLegend(0.2,-0.01,0.4,0.08);
   leg10Al2->AddEntry(gr10Almu2,"#mu - decay","lp");
   leg10Al2->AddEntry(gr10Alx2,"X-rays","lp");
   leg10Al2->Draw();

   g->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr10Almu3 = new TGraph(nbins,binCenters10Almu3,integrals10Almu3);
   gr10Almu3->SetTitle("3-mm SciD + 10-mm Al");
   gr10Almu3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr10Almu3->GetXaxis()->SetRangeUser(0,1.8);
   gr10Almu3->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr10Almu3->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr10Almu3->GetYaxis()->SetTitleOffset(1.8);
   gr10Almu3->SetMarkerColor(kBlack);
   gr10Almu3->SetMarkerStyle(33);
   gr10Almu3->SetLineColor(kBlack);
   gr10Almu3->Draw("ALP");
   TGraph *gr10Alx3 = new TGraph(nbins,binCenters10Alx3,integrals10Alx3);
   gr10Alx3->SetMarkerColor(kRed);
   gr10Alx3->SetMarkerStyle(31);
   gr10Alx3->SetLineColor(kRed);
   gr10Alx3->Draw("LP");
   leg10Al3 = new TLegend(0.2,-0.01,0.4,0.08);
   leg10Al3->AddEntry(gr10Almu3,"#mu - decay","lp");
   leg10Al3->AddEntry(gr10Alx3,"X-rays","lp");
   leg10Al3->Draw();
   
   g->cd(4);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr10Almu5 = new TGraph(nbins,binCenters10Almu5,integrals10Almu5);
   gr10Almu5->SetTitle("5-mm SciD + 10-mm Al");
   gr10Almu5->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr10Almu5->GetXaxis()->SetRangeUser(0,2);
   gr10Almu5->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr10Almu5->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr10Almu5->GetYaxis()->SetTitleOffset(1.8);
   gr10Almu5->SetMarkerColor(kBlack);
   gr10Almu5->SetMarkerStyle(33);
   gr10Almu5->SetLineColor(kBlack);
   gr10Almu5->Draw("ALP");
   TGraph *gr10Alx5 = new TGraph(nbins,binCenters10Alx5,integrals10Alx5);
   gr10Alx5->SetMarkerColor(kRed);
   gr10Alx5->SetMarkerStyle(31);
   gr10Alx5->SetLineColor(kRed);
   gr10Alx5->Draw("LP");
   leg10Al5 = new TLegend(0.2,-0.01,0.4,0.08);
   leg10Al5->AddEntry(gr10Almu5,"#mu - decay","lp");
   leg10Al5->AddEntry(gr10Alx5,"X-rays","lp");
   leg10Al5->Draw();
   
   g->cd(5);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr10Almu10 = new TGraph(nbins,binCenters10Almu10,integrals10Almu10);
   gr10Almu10->SetTitle("10-mm SciD + 10-mm Al");
   gr10Almu10->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr10Almu10->GetXaxis()->SetRangeUser(0,3);
   gr10Almu10->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr10Almu10->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr10Almu10->GetYaxis()->SetTitleOffset(1.8);
   gr10Almu10->SetMarkerColor(kBlack);
   gr10Almu10->SetMarkerStyle(33);
   gr10Almu10->SetLineColor(kBlack);
   gr10Almu10->Draw("ALP");
   TGraph *gr10Alx10 = new TGraph(nbins,binCenters10Alx10,integrals10Alx10);
   gr10Alx10->SetMarkerColor(kRed);
   gr10Alx10->SetMarkerStyle(31);
   gr10Alx10->SetLineColor(kRed);
   gr10Alx10->Draw("LP");
   leg10Al10 = new TLegend(0.2,-0.01,0.4,0.08);
   leg10Al10->AddEntry(gr10Almu10,"#mu - decay","lp");
   leg10Al10->AddEntry(gr10Alx10,"X-rays","lp");
   leg10Al10->Draw();
     
   g->cd(6);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *gr10Almu20 = new TGraph(nbins,binCenters10Almu20,integrals10Almu20);
   gr10Almu20->SetTitle("20-mm SciD + 10-mm Al");
   gr10Almu20->GetXaxis()->SetTitle("E_{THR} [MeV]");
   gr10Almu20->GetXaxis()->SetRangeUser(0,5);
   gr10Almu20->GetYaxis()->SetRangeUser(1e-4,1.1);
   gr10Almu20->GetYaxis()->SetTitle("P_{mis. id.}(E_{THR})");
   gr10Almu20->GetYaxis()->SetTitleOffset(1.8);
   gr10Almu20->SetMarkerColor(kBlack);
   gr10Almu20->SetMarkerStyle(33);
   gr10Almu20->SetLineColor(kBlack);
   gr10Almu20->Draw("ALP");
   TGraph *gr10Alx20 = new TGraph(nbins,binCenters10Alx20,integrals10Alx20);
   gr10Alx20->SetMarkerColor(kRed);
   gr10Alx20->SetMarkerStyle(31);
   gr10Alx20->SetLineColor(kRed);
   gr10Alx20->Draw("LP");
   leg10Al20 = new TLegend(0.2,-0.01,0.4,0.08);
   leg10Al20->AddEntry(gr10Almu20,"#mu - decay","lp");
   leg10Al20->AddEntry(gr10Alx20,"X-rays","lp");
   leg10Al20->Draw();
   
   g->SaveAs("BubbleTHR_10mm_Al.pdf");
   g->SaveAs("BubbleTHR_10mm_Al.png");
   g->SaveAs("BubbleTHR_10mm_Al.C");

 }
 
 
 int main() {
   bubble2THR();
   return 0;
}  
