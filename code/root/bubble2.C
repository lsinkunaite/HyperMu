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
   // With a 6-mm Al layer
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

   // 6-mm Al layer
   TFile* f6Almu1 = new TFile(TString(file6Almu1));
   TFile* f6Almu2 = new TFile(TString(file6Almu2));
   TFile* f6Almu3 = new TFile(TString(file6Almu3));
   TFile* f6Almu5 = new TFile(TString(file6Almu5));
   TFile* f6Almu10 = new TFile(TString(file6Almu10));
   TFile* f6Almu20 = new TFile(TString(file6Almu20));
   TFile* f6Alx1 = new TFile(TString(file6Alx1));
   TFile* f6Alx2 = new TFile(TString(file6Alx2));
   TFile* f6Alx3 = new TFile(TString(file6Alx3));
   TFile* f6Alx5 = new TFile(TString(file6Alx5));
   TFile* f6Alx10 = new TFile(TString(file6Alx10));
   TFile* f6Alx20 = new TFile(TString(file6Alx20));

   // 10-mm Al layer
   TFile* f10Almu1 = new TFile(TString(file10Almu1));
   TFile* f10Almu2 = new TFile(TString(file10Almu2));
   TFile* f10Almu3 = new TFile(TString(file10Almu3));
   TFile* f10Almu5 = new TFile(TString(file10Almu5));
   TFile* f10Almu10 = new TFile(TString(file10Almu10));
   TFile* f10Almu20 = new TFile(TString(file10Almu20));
   TFile* f10Alx1 = new TFile(TString(file10Alx1));
   TFile* f10Alx2 = new TFile(TString(file10Alx2));
   TFile* f10Alx3 = new TFile(TString(file10Alx3));
   TFile* f10Alx5 = new TFile(TString(file10Alx5));
   TFile* f10Alx10 = new TFile(TString(file10Alx10));
   TFile* f10Alx20 = new TFile(TString(file10Alx20));



   // 0-mm Al layer
   TH1F *hmu1 = new TH1F("hmu1","Edep",nbins,0,1.5);
   TH1F *hmu2 = new TH1F("hmu2","Edep",nbins,0,2.3);
   TH1F *hmu3 = new TH1F("hmu3","Edep",nbins,0,3.2);
   TH1F *hmu5 = new TH1F("hmu5","Edep",nbins,0,4.8);
   TH1F *hmu10 = new TH1F("hmu10","Edep",nbins,0,9);
   TH1F *hmu20 = new TH1F("hmu20","Edep",nbins,0,17);
   TH1F *hx1 = new TH1F("hx1","Edep",nbins,0,1.8);
   TH1F *hx2 = new TH1F("hx2","Edep",nbins,0,2.6);
   TH1F *hx3 = new TH1F("hx3","Edep",nbins,0,2.6);
   TH1F *hx5 = new TH1F("hx5","Edep",nbins,0,4.3);
   TH1F *hx10 = new TH1F("hx10","Edep",nbins,0,6.2);
   TH1F *hx20 = new TH1F("hx20","Edep",nbins,0,8.8);
   // 0-mm Al layer [norm.]
   TH1F *hmu1n = new TH1F("hmu1n","Edep",nbins,0,1.5);
   TH1F *hmu2n = new TH1F("hmu2n","Edep",nbins,0,2.4);
   TH1F *hmu3n = new TH1F("hmu3n","Edep",nbins,0,3.1);
   TH1F *hmu5n = new TH1F("hmu5n","Edep",nbins,0,5.2);
   TH1F *hmu10n = new TH1F("hmu10n","Edep",nbins,0,9.2);
   TH1F *hmu20n = new TH1F("hmu20n","Edep",nbins,0,15);
   TH1F *hx1n = new TH1F("hx1n","Edep",nbins,0,1.5);
   TH1F *hx2n = new TH1F("hx2n","Edep",nbins,0,2.4);
   TH1F *hx3n = new TH1F("hx3n","Edep",nbins,0,3.1);
   TH1F *hx5n = new TH1F("hx5n","Edep",nbins,0,5.2);
   TH1F *hx10n = new TH1F("hx10n","Edep",nbins,0,9.2);
   TH1F *hx20n = new TH1F("hx20n","Edep",nbins,0,15);
   // 0-mm Al layer [zoomed in]
   TH1F *hmu1z = new TH1F("hmu1z","Edep",nbins,0,0.4);
   TH1F *hmu2z = new TH1F("hmu2z","Edep",nbins,0,0.8);
   TH1F *hmu3z = new TH1F("hmu3z","Edep",nbins,0,1.3);
   TH1F *hmu5z = new TH1F("hmu5z","Edep",nbins,0,2);
   TH1F *hmu10z = new TH1F("hmu10z","Edep",nbins,0,3.7);
   TH1F *hmu20z = new TH1F("hmu20z","Edep",nbins,0,8);
   TH1F *hx1z = new TH1F("hx1z","Edep",nbins,0,0.4);
   TH1F *hx2z = new TH1F("hx2z","Edep",nbins,0,0.5);
   TH1F *hx3z = new TH1F("hx3z","Edep",nbins,0,0.7);
   TH1F *hx5z = new TH1F("hx5z","Edep",nbins,0,1);
   TH1F *hx10z = new TH1F("hx10z","Edep",nbins,0,1.5);
   TH1F *hx20z = new TH1F("hx20z","Edep",nbins,0,3);

   // 3-mm Al layer
   TH1F *hAlmu1 = new TH1F("hAlmu1","Edep",nbins,0,1.5);
   TH1F *hAlmu2 = new TH1F("hAlmu2","Edep",nbins,0,2.3);
   TH1F *hAlmu3 = new TH1F("hAlmu3","Edep",nbins,0,3.2);
   TH1F *hAlmu5 = new TH1F("hAlmu5","Edep",nbins,0,4.8);
   TH1F *hAlmu10 = new TH1F("hAlmu10","Edep",nbins,0,9);
   TH1F *hAlmu20 = new TH1F("hAlmu20","Edep",nbins,0,17);
   TH1F *hAlx1 = new TH1F("hAlx1","Edep",nbins,0,1.8);
   TH1F *hAlx2 = new TH1F("hAlx2","Edep",nbins,0,2.6);
   TH1F *hAlx3 = new TH1F("hAlx3","Edep",nbins,0,2.2);
   TH1F *hAlx5 = new TH1F("hAlx5","Edep",nbins,0,4.3);
   TH1F *hAlx10 = new TH1F("hAlx10","Edep",nbins,0,6.2);
   TH1F *hAlx20 = new TH1F("hAlx20","Edep",nbins,0,8.8);
   // 3-mm Al layer [norm.]
   TH1F *hAlmu1n = new TH1F("hAlmu1n","Edep",nbins,0,1.8);
   TH1F *hAlmu2n = new TH1F("hAlmu2n","Edep",nbins,0,2.6);
   TH1F *hAlmu3n = new TH1F("hAlmu3n","Edep",nbins,0,3.8);
   TH1F *hAlmu5n = new TH1F("hAlmu5n","Edep",nbins,0,5.4);
   TH1F *hAlmu10n = new TH1F("hAlmu10n","Edep",nbins,0,9);
   TH1F *hAlmu20n = new TH1F("hAlmu20n","Edep",nbins,0,15);
   TH1F *hAlx1n = new TH1F("hAlx1n","Edep",nbins,0,1.8);
   TH1F *hAlx2n = new TH1F("hAlx2n","Edep",nbins,0,2.6);
   TH1F *hAlx3n = new TH1F("hAlx3n","Edep",nbins,0,3.8);
   TH1F *hAlx5n = new TH1F("hAlx5n","Edep",nbins,0,5.4);
   TH1F *hAlx10n = new TH1F("hAlx10n","Edep",nbins,0,9);
   TH1F *hAlx20n = new TH1F("hAlx20n","Edep",nbins,0,15);
   // 3-mm Al layer [zoomed in]
   TH1F *hAlmu1z = new TH1F("hAlmu1z","Edep",nbins,0,0.4);
   TH1F *hAlmu2z = new TH1F("hAlmu2z","Edep",nbins,0,0.8);
   TH1F *hAlmu3z = new TH1F("hAlmu3z","Edep",nbins,0,1.3);
   TH1F *hAlmu5z = new TH1F("hAlmu5z","Edep",nbins,0,2);
   TH1F *hAlmu10z = new TH1F("hAlmu10z","Edep",nbins,0,3.7);
   TH1F *hAlmu20z = new TH1F("hAlmu20z","Edep",nbins,0,8);
   TH1F *hAlx1z = new TH1F("hAlx1z","Edep",nbins,0,0.4);
   TH1F *hAlx2z = new TH1F("hAlx2z","Edep",nbins,0,0.5);
   TH1F *hAlx3z = new TH1F("hAlx3z","Edep",nbins,0,0.7);
   TH1F *hAlx5z = new TH1F("hAlx5z","Edep",nbins,0,1);
   TH1F *hAlx10z = new TH1F("hAlx10z","Edep",nbins,0,1.5);
   TH1F *hAlx20z = new TH1F("hAlx20z","Edep",nbins,0,3);
   
   // 6-mm Al layer
   TH1F *h6Almu1 = new TH1F("h6Almu1","Edep",nbins,0,1.5);
   TH1F *h6Almu2 = new TH1F("h6Almu2","Edep",nbins,0,2.3);
   TH1F *h6Almu3 = new TH1F("h6Almu3","Edep",nbins,0,3.2);
   TH1F *h6Almu5 = new TH1F("h6Almu5","Edep",nbins,0,4.8);
   TH1F *h6Almu10 = new TH1F("h6Almu10","Edep",nbins,0,9);
   TH1F *h6Almu20 = new TH1F("h6Almu20","Edep",nbins,0,17);
   TH1F *h6Alx1 = new TH1F("h6Alx1","Edep",nbins,0,1.8);
   TH1F *h6Alx2 = new TH1F("h6Alx2","Edep",nbins,0,2.6);
   TH1F *h6Alx3 = new TH1F("h6Alx3","Edep",nbins,0,2.2);
   TH1F *h6Alx5 = new TH1F("h6Alx5","Edep",nbins,0,4.3);
   TH1F *h6Alx10 = new TH1F("h6Alx10","Edep",nbins,0,6.2);
   TH1F *h6Alx20 = new TH1F("h6Alx20","Edep",nbins,0,8.8);
   // 6-mm Al layer [norm.]
   TH1F *h6Almu1n = new TH1F("h6Almu1n","Edep",nbins,0,1.8);
   TH1F *h6Almu2n = new TH1F("h6Almu2n","Edep",nbins,0,2.6);
   TH1F *h6Almu3n = new TH1F("h6Almu3n","Edep",nbins,0,3.8);
   TH1F *h6Almu5n = new TH1F("h6Almu5n","Edep",nbins,0,5.4);
   TH1F *h6Almu10n = new TH1F("h6Almu10n","Edep",nbins,0,9);
   TH1F *h6Almu20n = new TH1F("h6Almu20n","Edep",nbins,0,15);
   TH1F *h6Alx1n = new TH1F("h6Alx1n","Edep",nbins,0,1.8);
   TH1F *h6Alx2n = new TH1F("h6Alx2n","Edep",nbins,0,2.6);
   TH1F *h6Alx3n = new TH1F("h6Alx3n","Edep",nbins,0,3.8);
   TH1F *h6Alx5n = new TH1F("h6Alx5n","Edep",nbins,0,5.4);
   TH1F *h6Alx10n = new TH1F("h6Alx10n","Edep",nbins,0,9);
   TH1F *h6Alx20n = new TH1F("h6Alx20n","Edep",nbins,0,15);
   // 6-mm Al layer [zoomed in]
   TH1F *h6Almu1z = new TH1F("h6Almu1z","Edep",nbins,0,0.4);
   TH1F *h6Almu2z = new TH1F("h6Almu2z","Edep",nbins,0,0.8);
   TH1F *h6Almu3z = new TH1F("h6Almu3z","Edep",nbins,0,1.3);
   TH1F *h6Almu5z = new TH1F("h6Almu5z","Edep",nbins,0,2);
   TH1F *h6Almu10z = new TH1F("h6Almu10z","Edep",nbins,0,3.7);
   TH1F *h6Almu20z = new TH1F("h6Almu20z","Edep",nbins,0,8);
   TH1F *h6Alx1z = new TH1F("h6Alx1z","Edep",nbins,0,0.4);
   TH1F *h6Alx2z = new TH1F("h6Alx2z","Edep",nbins,0,0.5);
   TH1F *h6Alx3z = new TH1F("h6Alx3z","Edep",nbins,0,0.7);
   TH1F *h6Alx5z = new TH1F("h6Alx5z","Edep",nbins,0,1);
   TH1F *h6Alx10z = new TH1F("h6Alx10z","Edep",nbins,0,1.5);
   TH1F *h6Alx20z = new TH1F("h6Alx20z","Edep",nbins,0,3);
   
   // 10-mm Al layer
   TH1F *h10Almu1 = new TH1F("h10Almu1","Edep",nbins,0,1.5);
   TH1F *h10Almu2 = new TH1F("h10Almu2","Edep",nbins,0,2.3);
   TH1F *h10Almu3 = new TH1F("h10Almu3","Edep",nbins,0,3.2);
   TH1F *h10Almu5 = new TH1F("h10Almu5","Edep",nbins,0,4.8);
   TH1F *h10Almu10 = new TH1F("h10Almu10","Edep",nbins,0,9);
   TH1F *h10Almu20 = new TH1F("h10Almu20","Edep",nbins,0,17);
   TH1F *h10Alx1 = new TH1F("h10Alx1","Edep",nbins,0,1.8);
   TH1F *h10Alx2 = new TH1F("h10Alx2","Edep",nbins,0,2.6);
   TH1F *h10Alx3 = new TH1F("h10Alx3","Edep",nbins,0,2.2);
   TH1F *h10Alx5 = new TH1F("h10Alx5","Edep",nbins,0,4.3);
   TH1F *h10Alx10 = new TH1F("h10Alx10","Edep",nbins,0,6.2);
   TH1F *h10Alx20 = new TH1F("h10Alx20","Edep",nbins,0,8.8);
   // 10-mm Al layer [norm.]
   TH1F *h10Almu1n = new TH1F("h10Almu1n","Edep",nbins,0,1.8);
   TH1F *h10Almu2n = new TH1F("h10Almu2n","Edep",nbins,0,2.6);
   TH1F *h10Almu3n = new TH1F("h10Almu3n","Edep",nbins,0,3.8);
   TH1F *h10Almu5n = new TH1F("h10Almu5n","Edep",nbins,0,5.4);
   TH1F *h10Almu10n = new TH1F("h10Almu10n","Edep",nbins,0,9);
   TH1F *h10Almu20n = new TH1F("h10Almu20n","Edep",nbins,0,15);
   TH1F *h10Alx1n = new TH1F("h10Alx1n","Edep",nbins,0,1.8);
   TH1F *h10Alx2n = new TH1F("h10Alx2n","Edep",nbins,0,2.6);
   TH1F *h10Alx3n = new TH1F("h10Alx3n","Edep",nbins,0,3.8);
   TH1F *h10Alx5n = new TH1F("h10Alx5n","Edep",nbins,0,5.4);
   TH1F *h10Alx10n = new TH1F("h10Alx10n","Edep",nbins,0,9);
   TH1F *h10Alx20n = new TH1F("h10Alx20n","Edep",nbins,0,15);
   // 10-mm Al layer [zoomed in]
   TH1F *h10Almu1z = new TH1F("h10Almu1z","Edep",nbins,0,0.4);
   TH1F *h10Almu2z = new TH1F("h10Almu2z","Edep",nbins,0,0.8);
   TH1F *h10Almu3z = new TH1F("h10Almu3z","Edep",nbins,0,1.3);
   TH1F *h10Almu5z = new TH1F("h10Almu5z","Edep",nbins,0,2);
   TH1F *h10Almu10z = new TH1F("h10Almu10z","Edep",nbins,0,3.7);
   TH1F *h10Almu20z = new TH1F("h10Almu20z","Edep",nbins,0,8);
   TH1F *h10Alx1z = new TH1F("h10Alx1z","Edep",nbins,0,0.4);
   TH1F *h10Alx2z = new TH1F("h10Alx2z","Edep",nbins,0,0.5);
   TH1F *h10Alx3z = new TH1F("h10Alx3z","Edep",nbins,0,0.7);
   TH1F *h10Alx5z = new TH1F("h10Alx5z","Edep",nbins,0,1);
   TH1F *h10Alx10z = new TH1F("h10Alx10z","Edep",nbins,0,1.5);
   TH1F *h10Alx20z = new TH1F("h10Alx20z","Edep",nbins,0,3);


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
   // 0-mm Al layer [zoomed in]
   tmu1->Draw("Edep>>hmu1z","","");
   tmu2->Draw("Edep>>hmu2z","","");
   tmu3->Draw("Edep>>hmu3z","","");
   tmu5->Draw("Edep>>hmu5z","","");
   tmu10->Draw("Edep>>hmu10z","","");
   tmu20->Draw("Edep>>hmu20z","","");
   tx1->Draw("Edep>>hx1z","","");
   tx2->Draw("Edep>>hx2z","","");
   tx3->Draw("Edep>>hx3z","","");
   tx5->Draw("Edep>>hx5z","","");
   tx10->Draw("Edep>>hx10z","","");
   tx20->Draw("Edep>>hx20z","","");
   
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
   // 3-mm Al layer [zoomed in]
   tAlmu1->Draw("Edep>>hAlmu1z","","");
   tAlmu2->Draw("Edep>>hAlmu2z","","");
   tAlmu3->Draw("Edep>>hAlmu3z","","");
   tAlmu5->Draw("Edep>>hAlmu5z","","");
   tAlmu10->Draw("Edep>>hAlmu10z","","");
   tAlmu20->Draw("Edep>>hAlmu20z","","");
   tAlx1->Draw("Edep>>hAlx1z","","");
   tAlx2->Draw("Edep>>hAlx2z","","");
   tAlx3->Draw("Edep>>hAlx3z","","");
   tAlx5->Draw("Edep>>hAlx5z","","");
   tAlx10->Draw("Edep>>hAlx10z","","");
   tAlx20->Draw("Edep>>hAlx20z","","");
   
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
   // 6-mm Al layer [norm.]
   t6Almu1->Draw("Edep>>h6Almu1n","","");
   t6Almu2->Draw("Edep>>h6Almu2n","","");
   t6Almu3->Draw("Edep>>h6Almu3n","","");
   t6Almu5->Draw("Edep>>h6Almu5n","","");
   t6Almu10->Draw("Edep>>h6Almu10n","","");
   t6Almu20->Draw("Edep>>h6Almu20n","","");
   t6Alx1->Draw("Edep>>h6Alx1n","","");
   t6Alx2->Draw("Edep>>h6Alx2n","","");
   t6Alx3->Draw("Edep>>h6Alx3n","","");
   t6Alx5->Draw("Edep>>h6Alx5n","","");
   t6Alx10->Draw("Edep>>h6Alx10n","","");
   t6Alx20->Draw("Edep>>h6Alx20n","","");
   // 6-mm Al layer [zoomed in]
   t6Almu1->Draw("Edep>>h6Almu1z","","");
   t6Almu2->Draw("Edep>>h6Almu2z","","");
   t6Almu3->Draw("Edep>>h6Almu3z","","");
   t6Almu5->Draw("Edep>>h6Almu5z","","");
   t6Almu10->Draw("Edep>>h6Almu10z","","");
   t6Almu20->Draw("Edep>>h6Almu20z","","");
   t6Alx1->Draw("Edep>>h6Alx1z","","");
   t6Alx2->Draw("Edep>>h6Alx2z","","");
   t6Alx3->Draw("Edep>>h6Alx3z","","");
   t6Alx5->Draw("Edep>>h6Alx5z","","");
   t6Alx10->Draw("Edep>>h6Alx10z","","");
   t6Alx20->Draw("Edep>>h6Alx20z","","");
   
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
   // 10-mm Al layer [norm.]
   t10Almu1->Draw("Edep>>h10Almu1n","","");
   t10Almu2->Draw("Edep>>h10Almu2n","","");
   t10Almu3->Draw("Edep>>h10Almu3n","","");
   t10Almu5->Draw("Edep>>h10Almu5n","","");
   t10Almu10->Draw("Edep>>h10Almu10n","","");
   t10Almu20->Draw("Edep>>h10Almu20n","","");
   t10Alx1->Draw("Edep>>h10Alx1n","","");
   t10Alx2->Draw("Edep>>h10Alx2n","","");
   t10Alx3->Draw("Edep>>h10Alx3n","","");
   t10Alx5->Draw("Edep>>h10Alx5n","","");
   t10Alx10->Draw("Edep>>h10Alx10n","","");
   t10Alx20->Draw("Edep>>h10Alx20n","","");
   // 10-mm Al layer [zoomed in]
   t10Almu1->Draw("Edep>>h10Almu1z","","");
   t10Almu2->Draw("Edep>>h10Almu2z","","");
   t10Almu3->Draw("Edep>>h10Almu3z","","");
   t10Almu5->Draw("Edep>>h10Almu5z","","");
   t10Almu10->Draw("Edep>>h10Almu10z","","");
   t10Almu20->Draw("Edep>>h10Almu20z","","");
   t10Alx1->Draw("Edep>>h10Alx1z","","");
   t10Alx2->Draw("Edep>>h10Alx2z","","");
   t10Alx3->Draw("Edep>>h10Alx3z","","");
   t10Alx5->Draw("Edep>>h10Alx5z","","");
   t10Alx10->Draw("Edep>>h10Alx10z","","");
   t10Alx20->Draw("Edep>>h10Alx20z","","");


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
   // 0-mm Al layer [zoomed in]
   hmu1z->SetLineColor(kBlack);
   hmu2z->SetLineColor(kBlack);
   hmu3z->SetLineColor(kBlack);
   hmu5z->SetLineColor(kBlack);
   hmu10z->SetLineColor(kBlack);
   hmu20z->SetLineColor(kBlack);
   hx1z->SetLineColor(kBlack);
   hx2z->SetLineColor(kBlack);
   hx3z->SetLineColor(kBlack);
   hx5z->SetLineColor(kBlack);
   hx10z->SetLineColor(kBlack);
   hx20z->SetLineColor(kBlack);

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
   // 3-mm Al layer [zoomed in]
   hAlmu1z->SetLineColor(kRed);
   hAlmu2z->SetLineColor(kRed);
   hAlmu3z->SetLineColor(kRed);
   hAlmu5z->SetLineColor(kRed);
   hAlmu10z->SetLineColor(kRed);
   hAlmu20z->SetLineColor(kRed);
   hAlx1z->SetLineColor(kRed);
   hAlx2z->SetLineColor(kRed);
   hAlx3z->SetLineColor(kRed);
   hAlx5z->SetLineColor(kRed);
   hAlx10z->SetLineColor(kRed);
   hAlx20z->SetLineColor(kRed);

   // 6-mm Al layer
   h6Almu1->SetLineColor(kGreen-2);
   h6Almu2->SetLineColor(kGreen-2);
   h6Almu3->SetLineColor(kGreen-2);
   h6Almu5->SetLineColor(kGreen-2);
   h6Almu10->SetLineColor(kGreen-2);
   h6Almu20->SetLineColor(kGreen-2);
   h6Alx1->SetLineColor(kGreen-2);
   h6Alx2->SetLineColor(kGreen-2);
   h6Alx3->SetLineColor(kGreen-2);
   h6Alx5->SetLineColor(kGreen-2);
   h6Alx10->SetLineColor(kGreen-2);
   h6Alx20->SetLineColor(kGreen-2);
   // 6-mm Al layer [norm.]
   h6Almu1n->SetLineColor(kBlack);
   h6Almu2n->SetLineColor(kBlack);
   h6Almu3n->SetLineColor(kBlack);
   h6Almu5n->SetLineColor(kBlack);
   h6Almu10n->SetLineColor(kBlack);
   h6Almu20n->SetLineColor(kBlack);
   h6Alx1n->SetLineColor(kRed);
   h6Alx2n->SetLineColor(kRed);
   h6Alx3n->SetLineColor(kRed);
   h6Alx5n->SetLineColor(kRed);
   h6Alx10n->SetLineColor(kRed);
   h6Alx20n->SetLineColor(kRed);
   // 6-mm Al layer [zoomed in]
   h6Almu1z->SetLineColor(kGreen-2);
   h6Almu2z->SetLineColor(kGreen-2);
   h6Almu3z->SetLineColor(kGreen-2);
   h6Almu5z->SetLineColor(kGreen-2);
   h6Almu10z->SetLineColor(kGreen-2);
   h6Almu20z->SetLineColor(kGreen-2);
   h6Alx1z->SetLineColor(kGreen-2);
   h6Alx2z->SetLineColor(kGreen-2);
   h6Alx3z->SetLineColor(kGreen-2);
   h6Alx5z->SetLineColor(kGreen-2);
   h6Alx10z->SetLineColor(kGreen-2);
   h6Alx20z->SetLineColor(kGreen-2);
   
   // 10-mm Al layer
   h10Almu1->SetLineColor(kBlue+1);
   h10Almu2->SetLineColor(kBlue+1);
   h10Almu3->SetLineColor(kBlue+1);
   h10Almu5->SetLineColor(kBlue+1);
   h10Almu10->SetLineColor(kBlue+1);
   h10Almu20->SetLineColor(kBlue+1);
   h10Alx1->SetLineColor(kBlue+1);
   h10Alx2->SetLineColor(kBlue+1);
   h10Alx3->SetLineColor(kBlue+1);
   h10Alx5->SetLineColor(kBlue+1);
   h10Alx10->SetLineColor(kBlue+1);
   h10Alx20->SetLineColor(kBlue+1);
   // 10-mm Al layer [norm.]
   h10Almu1n->SetLineColor(kBlack);
   h10Almu2n->SetLineColor(kBlack);
   h10Almu3n->SetLineColor(kBlack);
   h10Almu5n->SetLineColor(kBlack);
   h10Almu10n->SetLineColor(kBlack);
   h10Almu20n->SetLineColor(kBlack);
   h10Alx1n->SetLineColor(kRed);
   h10Alx2n->SetLineColor(kRed);
   h10Alx3n->SetLineColor(kRed);
   h10Alx5n->SetLineColor(kRed);
   h10Alx10n->SetLineColor(kRed);
   h10Alx20n->SetLineColor(kRed);
   // 10-mm Al layer [zoomed in]
   h10Almu1z->SetLineColor(kBlue+1);
   h10Almu2z->SetLineColor(kBlue+1);
   h10Almu3z->SetLineColor(kBlue+1);
   h10Almu5z->SetLineColor(kBlue+1);
   h10Almu10z->SetLineColor(kBlue+1);
   h10Almu20z->SetLineColor(kBlue+1);
   h10Alx1z->SetLineColor(kBlue+1);
   h10Alx2z->SetLineColor(kBlue+1);
   h10Alx3z->SetLineColor(kBlue+1);
   h10Alx5z->SetLineColor(kBlue+1);
   h10Alx10z->SetLineColor(kBlue+1);
   h10Alx20z->SetLineColor(kBlue+1);


   /********************************/
   /*           Plotting           */
   /********************************/

   // Mu-decay with various-thickness SciD: 0-,3-,6-,10-mm Al
   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(3,2);
   c->cd(1);
   gPad->SetLogy();
   hmu1->SetTitle("Mu-decay: 1-mm SciD with {0,3,6,10}-mm Al");
   hmu1->GetXaxis()->SetTitle("Edep [MeV]");
   hmu1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu1->GetYaxis()->SetTitleOffset(2.0);
   hmu1->Draw();
   c->Update();
   TPaveStats *stmu1 = (TPaveStats*)hmu1->GetListOfFunctions()->FindObject("stats");
   stmu1->SetY1NDC(0.33); stmu1->SetY2NDC(0.48);
   hAlmu1->Draw("sames");
   c->Update();
   TPaveStats *stAlmu1 = (TPaveStats*)hAlmu1->GetListOfFunctions()->FindObject("stats");
   stAlmu1->SetY1NDC(0.48); stAlmu1->SetY2NDC(0.63);
   stAlmu1->SetTextColor(kRed);
   h6Almu1->Draw("sames");
   c->Update();
   TPaveStats *st6Almu1 = (TPaveStats*)h6Almu1->GetListOfFunctions()->FindObject("stats");
   st6Almu1->SetY1NDC(0.63); st6Almu1->SetY2NDC(0.78);
   st6Almu1->SetTextColor(kGreen-2);
   h10Almu1->Draw("sames");
   c->Update();
   TPaveStats *st10Almu1 = (TPaveStats*)h10Almu1->GetListOfFunctions()->FindObject("stats");
   st10Almu1->SetTextColor(kBlue+1);
   st10Almu1->Draw();

   c->cd(2);
   gPad->SetLogy();
   hmu2->SetTitle("Mu-decay: 2-mm SciD with {0,3,6,10}-mm Al");
   hmu2->GetXaxis()->SetTitle("Edep [MeV]");
   hmu2->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu2->GetYaxis()->SetTitleOffset(2.0);
   hmu2->Draw();
   c->Update();
   TPaveStats *stmu2 = (TPaveStats*)hmu2->GetListOfFunctions()->FindObject("stats");
   stmu2->SetY1NDC(0.33); stmu2->SetY2NDC(0.48);
   hAlmu2->Draw("sames");
   c->Update();
   TPaveStats *stAlmu2 = (TPaveStats*)hAlmu2->GetListOfFunctions()->FindObject("stats");
   stAlmu2->SetY1NDC(0.48); stAlmu2->SetY2NDC(0.63);
   stAlmu2->SetTextColor(kRed);
   h6Almu2->Draw("sames");
   c->Update();
   TPaveStats *st6Almu2 = (TPaveStats*)h6Almu2->GetListOfFunctions()->FindObject("stats");
   st6Almu2->SetY1NDC(0.63); st6Almu2->SetY2NDC(0.78);
   st6Almu2->SetTextColor(kGreen-2);
   h10Almu2->Draw("sames");
   c->Update();
   TPaveStats *st10Almu2 = (TPaveStats*)h10Almu2->GetListOfFunctions()->FindObject("stats");
   st10Almu2->SetTextColor(kBlue+1);
   st10Almu2->Draw();

   c->cd(3);
   gPad->SetLogy();
   hmu3->SetTitle("Mu-decay: 3-mm SciD with {0,3,6,10}-mm Al");
   hmu3->GetXaxis()->SetTitle("Edep [MeV]");
   hmu3->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu3->GetYaxis()->SetTitleOffset(2.0);
   hmu3->Draw();
   c->Update();
   TPaveStats *stmu3 = (TPaveStats*)hmu3->GetListOfFunctions()->FindObject("stats");
   stmu3->SetY1NDC(0.33); stmu3->SetY2NDC(0.48);
   hAlmu3->Draw("sames");
   c->Update();
   TPaveStats *stAlmu3 = (TPaveStats*)hAlmu3->GetListOfFunctions()->FindObject("stats");
   stAlmu3->SetY1NDC(0.48); stAlmu3->SetY2NDC(0.63);
   stAlmu3->SetTextColor(kRed);
   h6Almu3->Draw("sames");
   c->Update();
   TPaveStats *st6Almu3 = (TPaveStats*)h6Almu3->GetListOfFunctions()->FindObject("stats");
   st6Almu3->SetY1NDC(0.63); st6Almu3->SetY2NDC(0.78);
   st6Almu3->SetTextColor(kGreen-2);
   h10Almu3->Draw("sames");
   c->Update();
   TPaveStats *st10Almu3 = (TPaveStats*)h10Almu3->GetListOfFunctions()->FindObject("stats");
   st10Almu3->SetTextColor(kBlue+1);
   st10Almu3->Draw();

   c->cd(4);
   gPad->SetLogy();
   hmu5->SetTitle("Mu-decay: 5-mm SciD with {0,3,6,10}-mm Al");
   hmu5->GetXaxis()->SetTitle("Edep [MeV]");
   hmu5->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu5->GetYaxis()->SetTitleOffset(2.0);
   hmu5->Draw();
   c->Update();
   TPaveStats *stmu5 = (TPaveStats*)hmu5->GetListOfFunctions()->FindObject("stats");
   stmu5->SetY1NDC(0.33); stmu5->SetY2NDC(0.48);
   hAlmu5->Draw("sames");
   c->Update();
   TPaveStats *stAlmu5 = (TPaveStats*)hAlmu5->GetListOfFunctions()->FindObject("stats");
   stAlmu5->SetY1NDC(0.48); stAlmu5->SetY2NDC(0.63);
   stAlmu5->SetTextColor(kRed);
   h6Almu5->Draw("sames");
   c->Update();
   TPaveStats *st6Almu5 = (TPaveStats*)h6Almu5->GetListOfFunctions()->FindObject("stats");
   st6Almu5->SetY1NDC(0.63); st6Almu5->SetY2NDC(0.78);
   st6Almu5->SetTextColor(kGreen-2);
   h10Almu5->Draw("sames");
   c->Update();
   TPaveStats *st10Almu5 = (TPaveStats*)h10Almu5->GetListOfFunctions()->FindObject("stats");
   st10Almu5->SetTextColor(kBlue+1);
   st10Almu5->Draw();

   c->cd(5);
   gPad->SetLogy();
   hmu10->SetTitle("Mu-decay: 10-mm SciD with {0,3,6,10}-mm Al");
   hmu10->GetXaxis()->SetTitle("Edep [MeV]");
   hmu10->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu10->GetYaxis()->SetTitleOffset(2.0);
   hmu10->Draw();
   c->Update();
   TPaveStats *stmu10 = (TPaveStats*)hmu10->GetListOfFunctions()->FindObject("stats");
   stmu10->SetY1NDC(0.33); stmu10->SetY2NDC(0.48);
   hAlmu10->Draw("sames");
   c->Update();
   TPaveStats *stAlmu10 = (TPaveStats*)hAlmu10->GetListOfFunctions()->FindObject("stats");
   stAlmu10->SetY1NDC(0.48); stAlmu10->SetY2NDC(0.63);
   stAlmu10->SetTextColor(kRed);
   h6Almu10->Draw("sames");
   c->Update();
   TPaveStats *st6Almu10 = (TPaveStats*)h6Almu10->GetListOfFunctions()->FindObject("stats");
   st6Almu10->SetY1NDC(0.63); st6Almu10->SetY2NDC(0.78);
   st6Almu10->SetTextColor(kGreen-2);
   h10Almu10->Draw("sames");
   c->Update();
   TPaveStats *st10Almu10 = (TPaveStats*)h10Almu10->GetListOfFunctions()->FindObject("stats");
   st10Almu10->SetTextColor(kBlue+1);
   st10Almu10->Draw();

   c->cd(6);
   gPad->SetLogy();
   hmu20->SetTitle("Mu-decay: 20-mm SciD with {0,3,6,10}-mm Al");
   hmu20->GetXaxis()->SetTitle("Edep [MeV]");
   hmu20->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu20->GetYaxis()->SetTitleOffset(2.0);
   hmu20->Draw();
   c->Update();
   TPaveStats *stmu20 = (TPaveStats*)hmu20->GetListOfFunctions()->FindObject("stats");
   stmu20->SetY1NDC(0.33); stmu20->SetY2NDC(0.48);
   hAlmu20->Draw("sames");
   c->Update();
   TPaveStats *stAlmu20 = (TPaveStats*)hAlmu20->GetListOfFunctions()->FindObject("stats");
   stAlmu20->SetY1NDC(0.48); stAlmu20->SetY2NDC(0.63);
   stAlmu20->SetTextColor(kRed);
   h6Almu20->Draw("sames");
   c->Update();
   TPaveStats *st6Almu20 = (TPaveStats*)h6Almu20->GetListOfFunctions()->FindObject("stats");
   st6Almu20->SetY1NDC(0.63); st6Almu20->SetY2NDC(0.78);
   st6Almu20->SetTextColor(kGreen-2);
   h10Almu20->Draw("sames");
   c->Update();
   TPaveStats *st10Almu20 = (TPaveStats*)h10Almu20->GetListOfFunctions()->FindObject("stats");
   st10Almu20->SetTextColor(kBlue+1);
   stAlmu20->Draw();

   c->SaveAs("BubbleTest2_mudecay_p1.pdf");
   c->SaveAs("BubbleTest2_mudecay_p1.png");
   c->SaveAs("BubbleTest2_mudecay_p1.C");



   // X-ray cascade with various-thickness SciD: 0-,3-,6-,10-mm Al
   TCanvas *d = new TCanvas("d","Edep",800,600);
   d->Divide(3,2);
   d->cd(1);
   gPad->SetLogy();
   hx1->SetTitle("X-ray cascade: 1-mm SciD with {0,3,6,10}-mm Al");
   hx1->GetXaxis()->SetTitle("Edep [MeV]");
   hx1->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx1->GetYaxis()->SetTitleOffset(2.0);
   hx1->Draw();
   d->Update();
   TPaveStats *stx1 = (TPaveStats*)hx1->GetListOfFunctions()->FindObject("stats");
   stx1->SetY1NDC(0.33); stx1->SetY2NDC(0.48);
   hAlx1->Draw("sames");
   d->Update();
   TPaveStats *stAlx1 = (TPaveStats*)hAlx1->GetListOfFunctions()->FindObject("stats");
   stAlx1->SetY1NDC(0.48); stAlx1->SetY2NDC(0.63);
   stAlx1->SetTextColor(kRed);
   h6Alx1->Draw("sames");
   d->Update();
   TPaveStats *st6Alx1 = (TPaveStats*)h6Alx1->GetListOfFunctions()->FindObject("stats");
   st6Alx1->SetY1NDC(0.63); st6Alx1->SetY2NDC(0.78);
   st6Alx1->SetTextColor(kGreen-2);
   h10Alx1->Draw("sames");
   d->Update();
   TPaveStats *st10Alx1 = (TPaveStats*)h10Alx1->GetListOfFunctions()->FindObject("stats");
   st10Alx1->SetTextColor(kBlue+1);
   st10Alx1->Draw();

   d->cd(2);
   gPad->SetLogy();
   hx2->SetTitle("X-ray cascade: 2-mm SciD with {0,3,6,10}-mm Al");
   hx2->GetXaxis()->SetTitle("Edep [MeV]");
   hx2->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx2->GetYaxis()->SetTitleOffset(2.0);
   hx2->Draw();
   d->Update();
   TPaveStats *stx2 = (TPaveStats*)hx2->GetListOfFunctions()->FindObject("stats");
   stx2->SetY1NDC(0.33); stx2->SetY2NDC(0.48);
   hAlx2->Draw("sames");
   d->Update();
   TPaveStats *stAlx2 = (TPaveStats*)hAlx2->GetListOfFunctions()->FindObject("stats");
   stAlx2->SetY1NDC(0.48); stAlx2->SetY2NDC(0.63);
   stAlx2->SetTextColor(kRed);
   h6Alx2->Draw("sames");
   d->Update();
   TPaveStats *st6Alx2 = (TPaveStats*)h6Alx2->GetListOfFunctions()->FindObject("stats");
   st6Alx2->SetY1NDC(0.63); st6Alx2->SetY2NDC(0.78);
   st6Alx2->SetTextColor(kGreen-2);
   h10Alx2->Draw("sames");
   d->Update();
   TPaveStats *st10Alx2 = (TPaveStats*)h10Alx2->GetListOfFunctions()->FindObject("stats");
   st10Alx2->SetTextColor(kBlue+1);
   st10Alx2->Draw();

   d->cd(3);
   gPad->SetLogy();
   hx3->SetTitle("X-ray cascade: 3-mm SciD with {0,3,6,10}-mm Al");
   hx3->GetXaxis()->SetTitle("Edep [MeV]");
   hx3->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx3->GetYaxis()->SetTitleOffset(2.0);
   hx3->Draw();
   d->Update();
   TPaveStats *stx3 = (TPaveStats*)hx3->GetListOfFunctions()->FindObject("stats");
   stx3->SetY1NDC(0.33); stx3->SetY2NDC(0.48);
   hAlx3->Draw("sames");
   d->Update();
   TPaveStats *stAlx3 = (TPaveStats*)hAlx3->GetListOfFunctions()->FindObject("stats");
   stAlx3->SetY1NDC(0.48); stAlx3->SetY2NDC(0.63);
   stAlx3->SetTextColor(kRed);
   h6Alx3->Draw("sames");
   d->Update();
   TPaveStats *st6Alx3 = (TPaveStats*)h6Alx3->GetListOfFunctions()->FindObject("stats");
   st6Alx3->SetY1NDC(0.63); st6Alx3->SetY2NDC(0.78);
   st6Alx3->SetTextColor(kGreen-2);
   h10Alx3->Draw("sames");
   d->Update();
   TPaveStats *st10Alx3 = (TPaveStats*)h10Alx3->GetListOfFunctions()->FindObject("stats");
   st10Alx3->SetTextColor(kBlue+1);
   st10Alx3->Draw();

   d->cd(4);
   gPad->SetLogy();
   hx5->SetTitle("X-ray cascade: 5-mm SciD with {0,3,6,10}-mm Al");
   hx5->GetXaxis()->SetTitle("Edep [MeV]");
   hx5->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx5->GetYaxis()->SetTitleOffset(2.0);
   hx5->Draw();
   d->Update();
   TPaveStats *stx5 = (TPaveStats*)hx5->GetListOfFunctions()->FindObject("stats");
   stx5->SetY1NDC(0.33); stx5->SetY2NDC(0.48);
   hAlx5->Draw("sames");
   d->Update();
   TPaveStats *stAlx5 = (TPaveStats*)hAlx5->GetListOfFunctions()->FindObject("stats");
   stAlx5->SetY1NDC(0.48); stAlx5->SetY2NDC(0.63);
   stAlx5->SetTextColor(kRed);
   h6Alx5->Draw("sames");
   d->Update();
   TPaveStats *st6Alx5 = (TPaveStats*)h6Alx5->GetListOfFunctions()->FindObject("stats");
   st6Alx5->SetY1NDC(0.63); st6Alx5->SetY2NDC(0.78);
   st6Alx5->SetTextColor(kGreen-2);
   h10Alx5->Draw("sames");
   d->Update();
   TPaveStats *st10Alx5 = (TPaveStats*)h10Alx5->GetListOfFunctions()->FindObject("stats");
   st10Alx5->SetTextColor(kBlue+1);
   st10Alx5->Draw();

   d->cd(5);
   gPad->SetLogy();
   hx10->SetTitle("X-ray cascade: 10-mm SciD with {0,3,6,10}-mm Al");
   hx10->GetXaxis()->SetTitle("Edep [MeV]");
   hx10->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx10->GetYaxis()->SetTitleOffset(2.0);
   hx10->Draw();
   d->Update();
   TPaveStats *stx10 = (TPaveStats*)hx10->GetListOfFunctions()->FindObject("stats");
   stx10->SetY1NDC(0.33); stx10->SetY2NDC(0.48);
   hAlx10->Draw("sames");
   d->Update();
   TPaveStats *stAlx10 = (TPaveStats*)hAlx10->GetListOfFunctions()->FindObject("stats");
   stAlx10->SetY1NDC(0.48); stAlx10->SetY2NDC(0.63);
   stAlx10->SetTextColor(kRed);
   h6Alx10->Draw("sames");
   d->Update();
   TPaveStats *st6Alx10 = (TPaveStats*)h6Alx10->GetListOfFunctions()->FindObject("stats");
   st6Alx10->SetY1NDC(0.63); st6Alx10->SetY2NDC(0.78);
   st6Alx10->SetTextColor(kGreen-2);
   h10Alx10->Draw("sames");
   d->Update();
   TPaveStats *st10Alx10 = (TPaveStats*)h10Alx10->GetListOfFunctions()->FindObject("stats");
   st10Alx10->SetTextColor(kBlue+1);
   st10Alx10->Draw();

   d->cd(6);
   gPad->SetLogy();
   hx20->SetTitle("X-ray cascade: 20-mm SciD with {0,3,6,10}-mm Al");
   hx20->GetXaxis()->SetTitle("Edep [MeV]");
   hx20->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx20->GetYaxis()->SetTitleOffset(2.0);
   hx20->Draw();
   d->Update();
   TPaveStats *stx20 = (TPaveStats*)hx20->GetListOfFunctions()->FindObject("stats");
   stx20->SetY1NDC(0.33); stx20->SetY2NDC(0.48);
   hAlx20->Draw("sames");
   d->Update();
   TPaveStats *stAlx20 = (TPaveStats*)hAlx20->GetListOfFunctions()->FindObject("stats");
   stAlx20->SetY1NDC(0.48); stAlx20->SetY2NDC(0.63);
   stAlx20->SetTextColor(kRed);
   h6Alx20->Draw("sames");
   d->Update();
   TPaveStats *st6Alx20 = (TPaveStats*)h6Alx20->GetListOfFunctions()->FindObject("stats");
   st6Alx20->SetY1NDC(0.63); st6Alx20->SetY2NDC(0.78);
   st6Alx20->SetTextColor(kGreen-2);
   h10Alx20->Draw("sames");
   d->Update();
   TPaveStats *st10Alx20 = (TPaveStats*)h10Alx20->GetListOfFunctions()->FindObject("stats");
   st10Alx20->SetTextColor(kBlue+1);
   st10Alx20->Draw();

   d->SaveAs("BubbleTest2_goldcascade_p1.pdf");
   d->SaveAs("BubbleTest2_goldcascade_p1.png");
   d->SaveAs("BubbleTest2_goldcascade_p1.C");



   // Mu-decay vs X-ray cascade [0-mm Al]
   TCanvas *e = new TCanvas("e","Edep",800,600);
   e->Divide(3,2);
   e->cd(1);
   gPad->SetLogy();
   hmu1n->SetTitle("Mu-decay vs X-ray cascade: 1-mm SciD + 0-mm Al");
   hmu1n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu1n->GetYaxis()->SetTitleOffset(2.0);
   hmu1n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
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
   hmu2n->SetTitle("Mu-decay vs X-ray cascade: 2-mm SciD + 0-mm Al");
   hmu2n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu2n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu2n->GetYaxis()->SetTitleOffset(2.0);
   hmu2n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
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
   hmu3n->SetTitle("Mu-decay vs X-ray cascade: 3-mm SciD + 0-mm Al");
   hmu3n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu3n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu3n->GetYaxis()->SetTitleOffset(2.0);
   hmu3n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
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
   hmu5n->SetTitle("Mu-decay vs X-ray cascade: 5-mm SciD + 0-mm Al");
   hmu5n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu5n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu5n->GetYaxis()->SetTitleOffset(2.0);
   hmu5n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
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
   hmu10n->SetTitle("Mu-decay vs X-ray cascade: 10-mm SciD + 0-mm Al");
   hmu10n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu10n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu10n->GetYaxis()->SetTitleOffset(2.0);
   hmu10n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
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
   hmu20n->SetTitle("Mu-decay vs X-ray cascade: 20-mm SciD + 0-mm Al");
   hmu20n->GetXaxis()->SetTitle("Edep [MeV]");
   hmu20n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu20n->GetYaxis()->SetTitleOffset(2.0);
   hmu20n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
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



   // Mu-decay vs X-ray cascade [3-mm Al]
   TCanvas *f = new TCanvas("f","Edep",800,600);
   f->Divide(3,2);
   f->cd(1);
   gPad->SetLogy();
   hAlmu1n->SetTitle("Mu-decay vs X-ray cascade: 1-mm SciD + 3-mm Al");
   hAlmu1n->GetXaxis()->SetTitle("Edep [MeV]");
   hAlmu1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   hAlmu1n->GetYaxis()->SetTitleOffset(2.0);
   hAlmu1n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
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
   hAlmu2n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
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
   hAlmu3n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
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
   hAlmu5n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
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
   hAlmu10n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
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
   hAlmu20n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
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
 
 
 
   // Mu-decay vs X-ray cascade [6-mm Al]
   TCanvas *i = new TCanvas("i","Edep",800,600);
   i->Divide(3,2);
   i->cd(1);
   gPad->SetLogy();
   h6Almu1n->SetTitle("Mu-decay vs X-ray cascade: 1-mm SciD + 6-mm Al");
   h6Almu1n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Almu1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Almu1n->GetYaxis()->SetTitleOffset(2.0);
   h6Almu1n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
   h6Almu1n->Draw();
   i->Update();
   TPaveStats *st6Almu1n = (TPaveStats*)h6Almu1n->GetListOfFunctions()->FindObject("stats");
   st6Almu1n->SetY1NDC(0.6); st6Almu1n->SetY2NDC(0.75);
   h6Alx1n->Draw("sames");
   i->Update();
   TPaveStats *st6Alx1n = (TPaveStats*)h6Alx1n->GetListOfFunctions()->FindObject("stats");
   st6Alx1n->SetTextColor(kRed);
   st6Alx1n->Draw();

   i->cd(2);
   gPad->SetLogy();
   h6Almu2n->SetTitle("Mu-decay vs X-ray cascade: 2-mm SciD + 6-mm Al");
   h6Almu2n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Almu2n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Almu2n->GetYaxis()->SetTitleOffset(2.0);
   h6Almu2n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
   h6Almu2n->Draw();
   i->Update();
   TPaveStats *st6Almu2n = (TPaveStats*)h6Almu2n->GetListOfFunctions()->FindObject("stats");
   st6Almu2n->SetY1NDC(0.6); st6Almu2n->SetY2NDC(0.75);
   h6Alx2n->Draw("sames");
   i->Update();
   TPaveStats *st6Alx2n = (TPaveStats*)h6Alx2n->GetListOfFunctions()->FindObject("stats");
   st6Alx2n->SetTextColor(kRed);
   st6Alx2n->Draw();

   i->cd(3);
   gPad->SetLogy();
   h6Almu3n->SetTitle("Mu-decay vs X-ray cascade: 3-mm SciD + 6-mm Al");
   h6Almu3n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Almu3n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Almu3n->GetYaxis()->SetTitleOffset(2.0);
   h6Almu3n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
   h6Almu3n->Draw();
   i->Update();
   TPaveStats *st6Almu3n = (TPaveStats*)h6Almu3n->GetListOfFunctions()->FindObject("stats");
   st6Almu3n->SetY1NDC(0.6); st6Almu3n->SetY2NDC(0.75);
   h6Alx3n->Draw("sames");
   i->Update();
   TPaveStats *st6Alx3n = (TPaveStats*)h6Alx3n->GetListOfFunctions()->FindObject("stats");
   st6Alx3n->SetTextColor(kRed);
   st6Alx3n->Draw();

   i->cd(4);
   gPad->SetLogy();
   h6Almu5n->SetTitle("Mu-decay vs X-ray cascade: 5-mm SciD + 6-mm Al");
   h6Almu5n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Almu5n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Almu5n->GetYaxis()->SetTitleOffset(2.0);
   h6Almu5n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
   h6Almu5n->Draw();
   i->Update();
   TPaveStats *st6Almu5n = (TPaveStats*)h6Almu5n->GetListOfFunctions()->FindObject("stats");
   st6Almu5n->SetY1NDC(0.6); st6Almu5n->SetY2NDC(0.75);
   h6Alx5n->Draw("sames");
   i->Update();
   TPaveStats *st6Alx5n = (TPaveStats*)h6Alx5n->GetListOfFunctions()->FindObject("stats");
   st6Alx5n->SetTextColor(kRed);
   st6Alx5n->Draw();   

   i->cd(5);
   gPad->SetLogy();
   h6Almu10n->SetTitle("Mu-decay vs X-ray cascade: 10-mm SciD + 6-mm Al");
   h6Almu10n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Almu10n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Almu10n->GetYaxis()->SetTitleOffset(2.0);
   h6Almu10n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
   h6Almu10n->Draw();
   i->Update();
   TPaveStats *st6Almu10n = (TPaveStats*)h6Almu10n->GetListOfFunctions()->FindObject("stats");
   st6Almu10n->SetY1NDC(0.6); st6Almu10n->SetY2NDC(0.75);
   h6Alx10n->Draw("sames");
   i->Update();
   TPaveStats *st6Alx10n = (TPaveStats*)h6Alx10n->GetListOfFunctions()->FindObject("stats");
   st6Alx10n->SetTextColor(kRed);
   st6Alx10n->Draw();

   i->cd(6);
   gPad->SetLogy();
   h6Almu20n->SetTitle("Mu-decay vs X-ray cascade: 20-mm SciD + 6-mm Al");
   h6Almu20n->GetXaxis()->SetTitle("Edep [MeV]");
   h6Almu20n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h6Almu20n->GetYaxis()->SetTitleOffset(2.0);
   h6Almu20n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
   h6Almu20n->Draw();
   i->Update();
   TPaveStats *st6Almu20n = (TPaveStats*)h6Almu20n->GetListOfFunctions()->FindObject("stats");
   st6Almu20n->SetY1NDC(0.6); st6Almu20n->SetY2NDC(0.75);
   h6Alx20n->Draw("sames");
   i->Update();
   TPaveStats *st6Alx20n = (TPaveStats*)h6Alx20n->GetListOfFunctions()->FindObject("stats");
   st6Alx20n->SetTextColor(kRed);
   st6Alx20n->Draw();

   i->SaveAs("BubbleTest2_6Al_muX_p2.pdf");
   i->SaveAs("BubbleTest2_6Al_muX_p2.png");
   i->SaveAs("BubbleTest2_6Al_muX_p2.C");
 
 
 
   // Mu-decay vs X-ray cascade [10-mm Al]
   TCanvas *j = new TCanvas("j","Edep",800,600);
   j->Divide(3,2);
   j->cd(1);
   gPad->SetLogy();
   h10Almu1n->SetTitle("Mu-decay vs X-ray cascade: 1-mm SciD + 10-mm Al");
   h10Almu1n->GetXaxis()->SetTitle("Edep [MeV]");
   h10Almu1n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h10Almu1n->GetYaxis()->SetTitleOffset(2.0);
   h10Almu1n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
   h10Almu1n->Draw();
   j->Update();
   TPaveStats *st10Almu1n = (TPaveStats*)h10Almu1n->GetListOfFunctions()->FindObject("stats");
   st10Almu1n->SetY1NDC(0.6); st10Almu1n->SetY2NDC(0.75);
   h10Alx1n->Draw("sames");
   j->Update();
   TPaveStats *st10Alx1n = (TPaveStats*)h10Alx1n->GetListOfFunctions()->FindObject("stats");
   st10Alx1n->SetTextColor(kRed);
   st10Alx1n->Draw();

   j->cd(2);
   gPad->SetLogy();
   h10Almu2n->SetTitle("Mu-decay vs X-ray cascade: 2-mm SciD + 10-mm Al");
   h10Almu2n->GetXaxis()->SetTitle("Edep [MeV]");
   h10Almu2n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h10Almu2n->GetYaxis()->SetTitleOffset(2.0);
   h10Almu2n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
   h10Almu2n->Draw();
   j->Update();
   TPaveStats *st10Almu2n = (TPaveStats*)h10Almu2n->GetListOfFunctions()->FindObject("stats");
   st10Almu2n->SetY1NDC(0.6); st10Almu2n->SetY2NDC(0.75);
   h10Alx2n->Draw("sames");
   j->Update();
   TPaveStats *st10Alx2n = (TPaveStats*)h10Alx2n->GetListOfFunctions()->FindObject("stats");
   st10Alx2n->SetTextColor(kRed);
   st10Alx2n->Draw();

   j->cd(3);
   gPad->SetLogy();
   h10Almu3n->SetTitle("Mu-decay vs X-ray cascade: 3-mm SciD + 10-mm Al");
   h10Almu3n->GetXaxis()->SetTitle("Edep [MeV]");
   h10Almu3n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h10Almu3n->GetYaxis()->SetTitleOffset(2.0);
   h10Almu3n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
   h10Almu3n->Draw();
   j->Update();
   TPaveStats *st10Almu3n = (TPaveStats*)h10Almu3n->GetListOfFunctions()->FindObject("stats");
   st10Almu3n->SetY1NDC(0.6); st10Almu3n->SetY2NDC(0.75);
   h10Alx3n->Draw("sames");
   j->Update();
   TPaveStats *st10Alx3n = (TPaveStats*)h10Alx3n->GetListOfFunctions()->FindObject("stats");
   st10Alx3n->SetTextColor(kRed);
   st10Alx3n->Draw();

   j->cd(4);
   gPad->SetLogy();
   h10Almu5n->SetTitle("Mu-decay vs X-ray cascade: 5-mm SciD + 10-mm Al");
   h10Almu5n->GetXaxis()->SetTitle("Edep [MeV]");
   h10Almu5n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h10Almu5n->GetYaxis()->SetTitleOffset(2.0);
   h10Almu5n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
   h10Almu5n->Draw();
   j->Update();
   TPaveStats *st10Almu5n = (TPaveStats*)h10Almu5n->GetListOfFunctions()->FindObject("stats");
   st10Almu5n->SetY1NDC(0.6); st10Almu5n->SetY2NDC(0.75);
   h10Alx5n->Draw("sames");
   j->Update();
   TPaveStats *st10Alx5n = (TPaveStats*)h10Alx5n->GetListOfFunctions()->FindObject("stats");
   st10Alx5n->SetTextColor(kRed);
   st10Alx5n->Draw();   

   j->cd(5);
   gPad->SetLogy();
   h10Almu10n->SetTitle("Mu-decay vs X-ray cascade: 10-mm SciD + 10-mm Al");
   h10Almu10n->GetXaxis()->SetTitle("Edep [MeV]");
   h10Almu10n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h10Almu10n->GetYaxis()->SetTitleOffset(2.0);
   h10Almu10n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
   h10Almu10n->Draw();
   j->Update();
   TPaveStats *st10Almu10n = (TPaveStats*)h10Almu10n->GetListOfFunctions()->FindObject("stats");
   st10Almu10n->SetY1NDC(0.6); st10Almu10n->SetY2NDC(0.75);
   h10Alx10n->Draw("sames");
   j->Update();
   TPaveStats *st10Alx10n = (TPaveStats*)h10Alx10n->GetListOfFunctions()->FindObject("stats");
   st10Alx10n->SetTextColor(kRed);
   st10Alx10n->Draw();

   j->cd(6);
   gPad->SetLogy();
   h10Almu20n->SetTitle("Mu-decay vs X-ray cascade: 20-mm SciD + 10-mm Al");
   h10Almu20n->GetXaxis()->SetTitle("Edep [MeV]");
   h10Almu20n->GetYaxis()->SetTitle("# of counts [a.u.]");
   h10Almu20n->GetYaxis()->SetTitleOffset(2.0);
   h10Almu20n->GetYaxis()->SetRangeUser(5e-1,1.5e6);
   h10Almu20n->Draw();
   j->Update();
   TPaveStats *st10Almu20n = (TPaveStats*)h10Almu20n->GetListOfFunctions()->FindObject("stats");
   st10Almu20n->SetY1NDC(0.6); st10Almu20n->SetY2NDC(0.75);
   h10Alx20n->Draw("sames");
   j->Update();
   TPaveStats *st10Alx20n = (TPaveStats*)h10Alx20n->GetListOfFunctions()->FindObject("stats");
   st10Alx20n->SetTextColor(kRed);
   st10Alx20n->Draw();

   j->SaveAs("BubbleTest2_10Al_muX_p2.pdf");
   j->SaveAs("BubbleTest2_10Al_muX_p2.png");
   j->SaveAs("BubbleTest2_10Al_muX_p2.C");


 
   // Mu-decay with {0,3,6,10}-mm Al, zoomed in
   TCanvas *g = new TCanvas("g","Edep",800,600);
   g->Divide(3,2);
   g->cd(1);
   gPad->SetLogy();
   hmu1z->SetTitle("Mu-decay [zoomed in]: 1-mm SciD with {0,3,6,10}-mm Al");
   hmu1z->GetXaxis()->SetTitle("Edep [MeV]");
   hmu1z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu1z->GetYaxis()->SetTitleOffset(2.0);
   hmu1z->Draw();
   g->Update();
   TPaveStats *stmu1z = (TPaveStats*)hmu1z->GetListOfFunctions()->FindObject("stats");
   stmu1z->SetY1NDC(0.33); stmu1z->SetY2NDC(0.48);
   hAlmu1z->Draw("sames");
   g->Update();
   TPaveStats *stAlmu1z = (TPaveStats*)hAlmu1z->GetListOfFunctions()->FindObject("stats");
   stAlmu1z->SetY1NDC(0.48); stAlmu1z->SetY2NDC(0.63);
   stAlmu1z->SetTextColor(kRed);
   h6Almu1z->Draw("sames");
   g->Update();
   TPaveStats *st6Almu1z = (TPaveStats*)h6Almu1z->GetListOfFunctions()->FindObject("stats");
   st6Almu1z->SetY1NDC(0.63); st6Almu1z->SetY2NDC(0.78);
   st6Almu1z->SetTextColor(kGreen-2);
   h10Almu1z->Draw("sames");
   g->Update();
   TPaveStats *st10Almu1z = (TPaveStats*)h10Almu1z->GetListOfFunctions()->FindObject("stats");
   st10Almu1z->SetTextColor(kBlue+1);
   st10Almu1z->Draw();

   g->cd(2);
   gPad->SetLogy();
   hmu2z->SetTitle("Mu-decay [zoomed in]: 2-mm SciD with {0,3,6,10}-mm Al");
   hmu2z->GetXaxis()->SetTitle("Edep [MeV]");
   hmu2z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu2z->GetYaxis()->SetTitleOffset(2.0);
   hmu2z->Draw();
   g->Update();
   TPaveStats *stmu2z = (TPaveStats*)hmu2z->GetListOfFunctions()->FindObject("stats");
   stmu2z->SetY1NDC(0.33); stmu2z->SetY2NDC(0.48);
   hAlmu2z->Draw("sames");
   g->Update();
   TPaveStats *stAlmu2z = (TPaveStats*)hAlmu2z->GetListOfFunctions()->FindObject("stats");
   stAlmu2z->SetY1NDC(0.48); stAlmu2z->SetY2NDC(0.63);
   stAlmu2z->SetTextColor(kRed);
   h6Almu2z->Draw("sames");
   g->Update();
   TPaveStats *st6Almu2z = (TPaveStats*)h6Almu2z->GetListOfFunctions()->FindObject("stats");
   st6Almu2z->SetY1NDC(0.63); st6Almu2z->SetY2NDC(0.78);
   st6Almu2z->SetTextColor(kGreen-2);
   h10Almu2z->Draw("sames");
   g->Update();
   TPaveStats *st10Almu2z = (TPaveStats*)h10Almu2z->GetListOfFunctions()->FindObject("stats");
   st10Almu2z->SetTextColor(kBlue+1);
   st10Almu2z->Draw();

   g->cd(3);
   gPad->SetLogy();
   hmu3z->SetTitle("Mu-decay [zoomed in]: 3-mm SciD with {0,3,6,10}-mm Al");
   hmu3z->GetXaxis()->SetTitle("Edep [MeV]");
   hmu3z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu3z->GetYaxis()->SetTitleOffset(2.0);
   hmu3z->Draw();
   g->Update();
   TPaveStats *stmu3z = (TPaveStats*)hmu3z->GetListOfFunctions()->FindObject("stats");
   stmu3z->SetY1NDC(0.33); stmu3z->SetY2NDC(0.48);
   hAlmu3z->Draw("sames");
   g->Update();
   TPaveStats *stAlmu3z = (TPaveStats*)hAlmu3z->GetListOfFunctions()->FindObject("stats");
   stAlmu3z->SetY1NDC(0.48); stAlmu3z->SetY2NDC(0.63);
   stAlmu3z->SetTextColor(kRed);
   h6Almu3z->Draw("sames");
   g->Update();
   TPaveStats *st6Almu3z = (TPaveStats*)h6Almu3z->GetListOfFunctions()->FindObject("stats");
   st6Almu3z->SetY1NDC(0.63); st6Almu3z->SetY2NDC(0.78);
   st6Almu3z->SetTextColor(kGreen-2);
   h10Almu3z->Draw("sames");
   g->Update();
   TPaveStats *st10Almu3z = (TPaveStats*)h10Almu3z->GetListOfFunctions()->FindObject("stats");
   st10Almu3z->SetTextColor(kBlue+1);
   st10Almu3z->Draw();

   g->cd(4);
   gPad->SetLogy();
   hmu5z->SetTitle("Mu-decay [zoomed in]: 5-mm SciD with {0,3,6,10}-mm Al");
   hmu5z->GetXaxis()->SetTitle("Edep [MeV]");
   hmu5z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu5z->GetYaxis()->SetTitleOffset(2.0);
   hmu5z->Draw();
   g->Update();
   TPaveStats *stmu5z = (TPaveStats*)hmu5z->GetListOfFunctions()->FindObject("stats");
   stmu5z->SetY1NDC(0.33); stmu5z->SetY2NDC(0.48);
   hAlmu5z->Draw("sames");
   g->Update();
   TPaveStats *stAlmu5z = (TPaveStats*)hAlmu5z->GetListOfFunctions()->FindObject("stats");
   stAlmu5z->SetY1NDC(0.48); stAlmu5z->SetY2NDC(0.63);
   stAlmu5z->SetTextColor(kRed);
   h6Almu5z->Draw("sames");
   g->Update();
   TPaveStats *st6Almu5z = (TPaveStats*)h6Almu5z->GetListOfFunctions()->FindObject("stats");
   st6Almu5z->SetY1NDC(0.63); st6Almu5z->SetY2NDC(0.78);
   st6Almu5z->SetTextColor(kGreen-2);
   h10Almu5z->Draw("sames");
   g->Update();
   TPaveStats *st10Almu5z = (TPaveStats*)h10Almu5z->GetListOfFunctions()->FindObject("stats");
   st10Almu5z->SetTextColor(kBlue+1);
   st10Almu5z->Draw();

   g->cd(5);
   gPad->SetLogy();
   hmu10z->SetTitle("Mu-decay [zoomed in]: 10-mm SciD with {0,3,6,10}-mm Al");
   hmu10z->GetXaxis()->SetTitle("Edep [MeV]");
   hmu10z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu10z->GetYaxis()->SetTitleOffset(2.0);
   hmu10z->Draw();
   g->Update();
   TPaveStats *stmu10z = (TPaveStats*)hmu10z->GetListOfFunctions()->FindObject("stats");
   stmu10z->SetY1NDC(0.33); stmu10z->SetY2NDC(0.48);
   hAlmu10z->Draw("sames");
   g->Update();
   TPaveStats *stAlmu10z = (TPaveStats*)hAlmu10z->GetListOfFunctions()->FindObject("stats");
   stAlmu10z->SetY1NDC(0.48); stAlmu10z->SetY2NDC(0.63);
   stAlmu10z->SetTextColor(kRed);
   h6Almu10z->Draw("sames");
   g->Update();
   TPaveStats *st6Almu10z = (TPaveStats*)h6Almu10z->GetListOfFunctions()->FindObject("stats");
   st6Almu10z->SetY1NDC(0.63); st6Almu10z->SetY2NDC(0.78);
   st6Almu10z->SetTextColor(kGreen-2);
   h10Almu10z->Draw("sames");
   g->Update();
   TPaveStats *st10Almu10z = (TPaveStats*)h10Almu10z->GetListOfFunctions()->FindObject("stats");
   st10Almu10z->SetTextColor(kBlue+1);
   st10Almu10z->Draw();

   g->cd(6);
   gPad->SetLogy();
   hmu20z->SetTitle("Mu-decay [zoomed in]: 20-mm SciD with {0,3,6,10}-mm Al");
   hmu20z->GetXaxis()->SetTitle("Edep [MeV]");
   hmu20z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hmu20z->GetYaxis()->SetTitleOffset(2.0);
   hmu20z->Draw();
   g->Update();
   TPaveStats *stmu20z = (TPaveStats*)hmu20z->GetListOfFunctions()->FindObject("stats");
   stmu20z->SetY1NDC(0.33); stmu20z->SetY2NDC(0.48);
   hAlmu20z->Draw("sames");
   g->Update();
   TPaveStats *stAlmu20z = (TPaveStats*)hAlmu20z->GetListOfFunctions()->FindObject("stats");
   stAlmu20z->SetY1NDC(0.48); stAlmu20z->SetY2NDC(0.63);
   stAlmu20z->SetTextColor(kRed);
   h6Almu20z->Draw("sames");
   g->Update();
   TPaveStats *st6Almu20z = (TPaveStats*)h6Almu20z->GetListOfFunctions()->FindObject("stats");
   st6Almu20z->SetY1NDC(0.63); st6Almu20z->SetY2NDC(0.78);
   st6Almu20z->SetTextColor(kGreen-2);
   h10Almu20z->Draw("sames");
   g->Update();
   TPaveStats *st10Almu20z = (TPaveStats*)h10Almu20z->GetListOfFunctions()->FindObject("stats");
   st10Almu20z->SetTextColor(kBlue+1);
   st10Almu20z->Draw();

   g->SaveAs("BubbleTest2_mudecay_zoom_p3.pdf");
   g->SaveAs("BubbleTest2_mudecay_zoom_p3.png");
   g->SaveAs("BubbleTest2_mudecay_zoom_p3.C");   
 
 

   // X-ray cascade with {0,3,6,10}-mm Al, zoomed in
   TCanvas *h = new TCanvas("h","Edep",800,600);
   h->Divide(3,2);
   h->cd(1);
   gPad->SetLogy();
   hx1z->SetTitle("X-ray cascade [zoomed in]: 1-mm SciD with {0,3,6,10}-mm Al");
   hx1z->GetXaxis()->SetTitle("Edep [MeV]");
   hx1z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx1z->GetYaxis()->SetTitleOffset(2.0);
   hx1z->Draw();
   h->Update();
   TPaveStats *stx1z = (TPaveStats*)hx1z->GetListOfFunctions()->FindObject("stats");
   stx1z->SetY1NDC(0.33); stx1z->SetY2NDC(0.48);
   hAlx1z->Draw("sames");
   h->Update();
   TPaveStats *stAlx1z = (TPaveStats*)hAlx1z->GetListOfFunctions()->FindObject("stats");
   stAlx1z->SetY1NDC(0.48); stAlx1z->SetY2NDC(0.63);
   stAlx1z->SetTextColor(kRed);
   h6Alx1z->Draw("sames");
   h->Update();
   TPaveStats *st6Alx1z = (TPaveStats*)h6Alx1z->GetListOfFunctions()->FindObject("stats");
   st6Alx1z->SetY1NDC(0.63); st6Alx1z->SetY2NDC(0.78);
   st6Alx1z->SetTextColor(kGreen-2);
   h10Alx1z->Draw("sames");
   h->Update();
   TPaveStats *st10Alx1z = (TPaveStats*)h10Alx1z->GetListOfFunctions()->FindObject("stats");
   st10Alx1z->SetTextColor(kBlue+1);
   st10Alx1z->Draw();

   h->cd(2);
   gPad->SetLogy();
   hx2z->SetTitle("X-ray cascade [zoomed in]: 2-mm SciD with {0,3,6,10}-mm Al");
   hx2z->GetXaxis()->SetTitle("Edep [MeV]");
   hx2z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx2z->GetYaxis()->SetTitleOffset(2.0);
   hx2z->Draw();
   h->Update();
   TPaveStats *stx2z = (TPaveStats*)hx2z->GetListOfFunctions()->FindObject("stats");
   stx2z->SetY1NDC(0.33); stx2z->SetY2NDC(0.48);
   hAlx2z->Draw("sames");
   h->Update();
   TPaveStats *stAlx2z = (TPaveStats*)hAlx2z->GetListOfFunctions()->FindObject("stats");
   stAlx2z->SetY1NDC(0.48); stAlx2z->SetY2NDC(0.63);
   stAlx2z->SetTextColor(kRed);
   h6Alx2z->Draw("sames");
   h->Update();
   TPaveStats *st6Alx2z = (TPaveStats*)h6Alx2z->GetListOfFunctions()->FindObject("stats");
   st6Alx2z->SetY1NDC(0.63); st6Alx2z->SetY2NDC(0.78);
   st6Alx2z->SetTextColor(kGreen-2);
   h10Alx2z->Draw("sames");
   h->Update();
   TPaveStats *st10Alx2z = (TPaveStats*)h10Alx2z->GetListOfFunctions()->FindObject("stats");
   st10Alx2z->SetTextColor(kBlue+1);
   st10Alx2z->Draw();

   h->cd(3);
   gPad->SetLogy();
   hx3z->SetTitle("X-ray cascade [zoomed in]: 3-mm SciD with {0,3,6,10}-mm Al");
   hx3z->GetXaxis()->SetTitle("Edep [MeV]");
   hx3z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx3z->GetYaxis()->SetTitleOffset(2.0);
   hx3z->Draw();
   h->Update();
   TPaveStats *stx3z = (TPaveStats*)hx3z->GetListOfFunctions()->FindObject("stats");
   stx3z->SetY1NDC(0.33); stx3z->SetY2NDC(0.48);
   hAlx3z->Draw("sames");
   h->Update();
   TPaveStats *stAlx3z = (TPaveStats*)hAlx3z->GetListOfFunctions()->FindObject("stats");
   stAlx3z->SetY1NDC(0.48); stAlx3z->SetY2NDC(0.63);
   stAlx3z->SetTextColor(kRed);
   h6Alx3z->Draw("sames");
   h->Update();
   TPaveStats *st6Alx3z = (TPaveStats*)h6Alx3z->GetListOfFunctions()->FindObject("stats");
   st6Alx3z->SetY1NDC(0.63); st6Alx3z->SetY2NDC(0.78);
   st6Alx3z->SetTextColor(kGreen-2);
   h10Alx3z->Draw("sames");
   h->Update();
   TPaveStats *st10Alx3z = (TPaveStats*)h10Alx3z->GetListOfFunctions()->FindObject("stats");
   st10Alx3z->SetTextColor(kBlue+1);
   st10Alx3z->Draw();

   h->cd(4);
   gPad->SetLogy();
   hx5z->SetTitle("X-ray cascade [zoomed in]: 5-mm SciD with {0,3,6,10}-mm Al");
   hx5z->GetXaxis()->SetTitle("Edep [MeV]");
   hx5z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx5z->GetYaxis()->SetTitleOffset(2.0);
   hx5z->Draw();
   h->Update();
   TPaveStats *stx5z = (TPaveStats*)hx5z->GetListOfFunctions()->FindObject("stats");
   stx5z->SetY1NDC(0.33); stx5z->SetY2NDC(0.48);
   hAlx5z->Draw("sames");
   h->Update();
   TPaveStats *stAlx5z = (TPaveStats*)hAlx5z->GetListOfFunctions()->FindObject("stats");
   stAlx5z->SetY1NDC(0.48); stAlx5z->SetY2NDC(0.63);
   stAlx5z->SetTextColor(kRed);
   h6Alx5z->Draw("sames");
   h->Update();
   TPaveStats *st6Alx5z = (TPaveStats*)h6Alx5z->GetListOfFunctions()->FindObject("stats");
   st6Alx5z->SetY1NDC(0.63); st6Alx5z->SetY2NDC(0.78);
   st6Alx5z->SetTextColor(kGreen-2);
   h10Alx5z->Draw("sames");
   h->Update();
   TPaveStats *st10Alx5z = (TPaveStats*)h10Alx5z->GetListOfFunctions()->FindObject("stats");
   st10Alx5z->SetTextColor(kBlue+1);
   st10Alx5z->Draw();

   h->cd(5);
   gPad->SetLogy();
   hx10z->SetTitle("X-ray cascade [zoomed in]: 10-mm SciD with {0,3,6,10}-mm Al");
   hx10z->GetXaxis()->SetTitle("Edep [MeV]");
   hx10z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx10z->GetYaxis()->SetTitleOffset(2.0);
   hx10z->Draw();
   h->Update();
   TPaveStats *stx10z = (TPaveStats*)hx10z->GetListOfFunctions()->FindObject("stats");
   stx10z->SetY1NDC(0.33); stx10z->SetY2NDC(0.48);
   hAlx10z->Draw("sames");
   h->Update();
   TPaveStats *stAlx10z = (TPaveStats*)hAlx10z->GetListOfFunctions()->FindObject("stats");
   stAlx10z->SetY1NDC(0.48); stAlx10z->SetY2NDC(0.63);
   stAlx10z->SetTextColor(kRed);
   h6Alx10z->Draw("sames");
   h->Update();
   TPaveStats *st6Alx10z = (TPaveStats*)h6Alx10z->GetListOfFunctions()->FindObject("stats");
   st6Alx10z->SetY1NDC(0.63); st6Alx10z->SetY2NDC(0.78);
   st6Alx10z->SetTextColor(kGreen-2);
   h10Alx10z->Draw("sames");
   h->Update();
   TPaveStats *st10Alx10z = (TPaveStats*)h10Alx10z->GetListOfFunctions()->FindObject("stats");
   st10Alx10z->SetTextColor(kBlue+1);
   st10Alx10z->Draw();

   h->cd(6);
   gPad->SetLogy();
   hx20z->SetTitle("X-ray cascade [zoomed in]: 20-mm SciD with {0,3,6,10}-mm Al");
   hx20z->GetXaxis()->SetTitle("Edep [MeV]");
   hx20z->GetYaxis()->SetTitle("# of counts [a.u.]");
   hx20z->GetYaxis()->SetTitleOffset(2.0);
   hx20z->Draw();
   h->Update();
   TPaveStats *stx20z = (TPaveStats*)hx20z->GetListOfFunctions()->FindObject("stats");
   stx20z->SetY1NDC(0.33); stx20z->SetY2NDC(0.48);
   hAlx20z->Draw("sames");
   h->Update();
   TPaveStats *stAlx20z = (TPaveStats*)hAlx20z->GetListOfFunctions()->FindObject("stats");
   stAlx20z->SetY1NDC(0.48); stAlx20z->SetY2NDC(0.63);
   stAlx20z->SetTextColor(kRed);
   h6Alx20z->Draw("sames");
   h->Update();
   TPaveStats *st6Alx20z = (TPaveStats*)h6Alx20z->GetListOfFunctions()->FindObject("stats");
   st6Alx20z->SetY1NDC(0.63); st6Alx20z->SetY2NDC(0.78);
   st6Alx20z->SetTextColor(kGreen-2);
   h10Alx20z->Draw("sames");
   h->Update();
   TPaveStats *st10Alx20z = (TPaveStats*)h10Alx20z->GetListOfFunctions()->FindObject("stats");
   st10Alx20z->SetTextColor(kBlue+1);
   st10Alx20z->Draw();

   h->SaveAs("BubbleTest2_goldcascade_zoom_p3.pdf");
   h->SaveAs("BubbleTest2_goldcascade_zoom_p3.png");
   h->SaveAs("BubbleTest2_goldcascade_zoom_p3.C");



}


int main() {
   bubble2();
   return 0;
}
