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
#include "TGaxis.h"
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

void finalcavCuGlassVert(){

   //Some style definitions
   //gROOT->Reset();
   //gROOT->SetStyle("Plain");
   gStyle->SetPaperSize(26,20);
   gStyle->SetOptStat(1);
   gStyle->SetTitleXOffset(1.15);
   gStyle->SetTitleYOffset(1.15);
   gStyle->SetTitleBorderSize(0.1);
   gStyle->SetLegendBorderSize(0.1);
   //gStyle->SetPadBottomMargin(0.32);
   gStyle->SetPadBottomMargin(0.12);
   gStyle->SetPadLeftMargin(0.24);
   //gStyle->SetPadTopMargin(0.32);
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

   const int nsamps = 101;
   std::string phishift = "0";
   std::string zshift = "0";
   std::string dB = "4";
   std::string dA1 = "300";
   std::string dA12 = "350";
   std::string dA13 = "400";
   std::string dA14 = "450";
   std::string dA15 = "500";

   // Names of the files
   // X-ray cascade dA1 = 300 mm
   std::string filexSciD1 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5goldcascade_SciD1.txt";
   std::string filexSciD2 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5goldcascade_SciD2.txt";
   std::string filexSciD3 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5goldcascade_SciD3.txt";
   std::string filexBGOD1 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD2 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5goldcascade_BGOD2.txt";

   // X-ray cascade dA1 = 300 mm
   std::string filex2SciD1 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5goldcascade_SciD1.txt";
   std::string filex2SciD2 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5goldcascade_SciD2.txt";
   std::string filex2SciD3 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5goldcascade_SciD3.txt";
   std::string filex2BGOD1 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5goldcascade_BGOD1.txt";
   std::string filex2BGOD2 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5goldcascade_BGOD2.txt";

   // X-ray cascade dA1 = 350 mm
   std::string filexSciD12 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5goldcascade_SciD1.txt";
   std::string filexSciD22 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5goldcascade_SciD2.txt";
   std::string filexSciD32 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5goldcascade_SciD3.txt";
   std::string filexBGOD12 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD22 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5goldcascade_BGOD2.txt";

   // X-ray cascade dA1 = 350 mm
   std::string filex2SciD12 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5goldcascade_SciD1.txt";
   std::string filex2SciD22 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5goldcascade_SciD2.txt";
   std::string filex2SciD32 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5goldcascade_SciD3.txt";
   std::string filex2BGOD12 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5goldcascade_BGOD1.txt";
   std::string filex2BGOD22 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5goldcascade_BGOD2.txt";

   // X-ray cascade dA1 = 400 mm
   std::string filexSciD13 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5goldcascade_SciD1.txt";
   std::string filexSciD23 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5goldcascade_SciD2.txt";
   std::string filexSciD33 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5goldcascade_SciD3.txt";
   std::string filexBGOD13 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD23 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5goldcascade_BGOD2.txt";

   // X-ray cascade dA1 = 400 mm
   std::string filex2SciD13 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5goldcascade_SciD1.txt";
   std::string filex2SciD23 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5goldcascade_SciD2.txt";
   std::string filex2SciD33 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5goldcascade_SciD3.txt";
   std::string filex2BGOD13 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5goldcascade_BGOD1.txt";
   std::string filex2BGOD23 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5goldcascade_BGOD2.txt";

   // X-ray cascade dA1 = 450 mm
   std::string filexSciD14 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5goldcascade_SciD1.txt";
   std::string filexSciD24 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5goldcascade_SciD2.txt";
   std::string filexSciD34 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5goldcascade_SciD3.txt";
   std::string filexBGOD14 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD24 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5goldcascade_BGOD2.txt";

   // X-ray cascade dA1 = 450 mm
   std::string filex2SciD14 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5goldcascade_SciD1.txt";
   std::string filex2SciD24 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5goldcascade_SciD2.txt";
   std::string filex2SciD34 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5goldcascade_SciD3.txt";
   std::string filex2BGOD14 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5goldcascade_BGOD1.txt";
   std::string filex2BGOD24 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5goldcascade_BGOD2.txt";

   // X-ray cascade dA1 = 500 mm
   std::string filexSciD15 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5goldcascade_SciD1.txt";
   std::string filexSciD25 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5goldcascade_SciD2.txt";
   std::string filexSciD35 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5goldcascade_SciD3.txt";
   std::string filexBGOD15 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD25 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5goldcascade_BGOD2.txt";

   // X-ray cascade dA1 = 500 mm
   std::string filex2SciD15 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5goldcascade_SciD1.txt";
   std::string filex2SciD25 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5goldcascade_SciD2.txt";
   std::string filex2SciD35 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5goldcascade_SciD3.txt";
   std::string filex2BGOD15 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5goldcascade_BGOD1.txt";
   std::string filex2BGOD25 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5goldcascade_BGOD2.txt";


   // Mu-decay dA1 = 300 mm
   std::string filemuSciD1 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5mudecay_SciD1.txt";
   std::string filemuSciD2 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5mudecay_SciD2.txt";
   std::string filemuSciD3 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5mudecay_SciD3.txt";
   std::string filemuBGOD1 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD2 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5mudecay_BGOD2.txt";

   // Mu-decay dA1 = 300 mm
   std::string filemu2SciD1 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5mudecay_SciD1.txt";
   std::string filemu2SciD2 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5mudecay_SciD2.txt";
   std::string filemu2SciD3 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5mudecay_SciD3.txt";
   std::string filemu2BGOD1 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5mudecay_BGOD1.txt";
   std::string filemu2BGOD2 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA1+"mm_1e5mudecay_BGOD2.txt";

   // Mu-decay dA1 = 350 mm
   std::string filemuSciD12 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5mudecay_SciD1.txt";
   std::string filemuSciD22 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5mudecay_SciD2.txt";
   std::string filemuSciD32 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5mudecay_SciD3.txt";
   std::string filemuBGOD12 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD22 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5mudecay_BGOD2.txt";

   // Mu-decay dA1 = 350 mm
   std::string filemu2SciD12 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5mudecay_SciD1.txt";
   std::string filemu2SciD22 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5mudecay_SciD2.txt";
   std::string filemu2SciD32 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5mudecay_SciD3.txt";
   std::string filemu2BGOD12 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5mudecay_BGOD1.txt";
   std::string filemu2BGOD22 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA12+"mm_1e5mudecay_BGOD2.txt";

   // Mu-decay dA1 = 400 mm
   std::string filemuSciD13 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5mudecay_SciD1.txt";
   std::string filemuSciD23 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5mudecay_SciD2.txt";
   std::string filemuSciD33 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5mudecay_SciD3.txt";
   std::string filemuBGOD13 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD23 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5mudecay_BGOD2.txt";

   // Mu-decay dA1 = 400 mm
   std::string filemu2SciD13 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5mudecay_SciD1.txt";
   std::string filemu2SciD23 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5mudecay_SciD2.txt";
   std::string filemu2SciD33 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5mudecay_SciD3.txt";
   std::string filemu2BGOD13 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5mudecay_BGOD1.txt";
   std::string filemu2BGOD23 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA13+"mm_1e5mudecay_BGOD2.txt";

   // Mu-decay dA1 = 450 mm
   std::string filemuSciD14 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5mudecay_SciD1.txt";
   std::string filemuSciD24 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5mudecay_SciD2.txt";
   std::string filemuSciD34 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5mudecay_SciD3.txt";
   std::string filemuBGOD14 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD24 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5mudecay_BGOD2.txt";

   // Mu-decay dA1 = 450 mm
   std::string filemu2SciD14 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5mudecay_SciD1.txt";
   std::string filemu2SciD24 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5mudecay_SciD2.txt";
   std::string filemu2SciD34 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5mudecay_SciD3.txt";
   std::string filemu2BGOD14 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5mudecay_BGOD1.txt";
   std::string filemu2BGOD24 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA14+"mm_1e5mudecay_BGOD2.txt";

   // Mu-decay dA1 = 500 mm
   std::string filemuSciD15 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5mudecay_SciD1.txt";
   std::string filemuSciD25 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5mudecay_SciD2.txt";
   std::string filemuSciD35 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5mudecay_SciD3.txt";
   std::string filemuBGOD15 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD25 = "../../simdata/final/Cu_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5mudecay_BGOD2.txt";

   // Mu-decay dA1 = 500 mm
   std::string filemu2SciD15 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5mudecay_SciD1.txt";
   std::string filemu2SciD25 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5mudecay_SciD2.txt";
   std::string filemu2SciD35 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5mudecay_SciD3.txt";
   std::string filemu2BGOD15 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5mudecay_BGOD1.txt";
   std::string filemu2BGOD25 = "../../simdata/final/Glass_cav_Sci_"+phishift+"mm_phi_"+zshift+"mm_z_dB_"+dB+"mm_dA1_"+dA15+"mm_1e5mudecay_BGOD2.txt";


   // Vectors with filenames   
   std::vector<std::string> Xfiles;
   std::vector<std::string> mufiles;

   // X-ray cascade dA1 = 300 mm
   Xfiles.push_back(filexSciD1);
   Xfiles.push_back(filexSciD2);
   Xfiles.push_back(filexSciD3);
   Xfiles.push_back(filexBGOD1);
   Xfiles.push_back(filexBGOD2);

   Xfiles.push_back(filex2SciD1);
   Xfiles.push_back(filex2SciD2);
   Xfiles.push_back(filex2SciD3);
   Xfiles.push_back(filex2BGOD1);
   Xfiles.push_back(filex2BGOD2);

   // X-ray cascade	dA1 = 350 mm	 
   Xfiles.push_back(filexSciD12);
   Xfiles.push_back(filexSciD22);
   Xfiles.push_back(filexSciD32);
   Xfiles.push_back(filexBGOD12);
   Xfiles.push_back(filexBGOD22);

   Xfiles.push_back(filex2SciD12);
   Xfiles.push_back(filex2SciD22);
   Xfiles.push_back(filex2SciD32);
   Xfiles.push_back(filex2BGOD12);
   Xfiles.push_back(filex2BGOD22);

   // X-ray cascade dA1 = 400 mm		 
   Xfiles.push_back(filexSciD13);
   Xfiles.push_back(filexSciD23);
   Xfiles.push_back(filexSciD33);
   Xfiles.push_back(filexBGOD13);
   Xfiles.push_back(filexBGOD23);

   Xfiles.push_back(filex2SciD13);
   Xfiles.push_back(filex2SciD23);
   Xfiles.push_back(filex2SciD33);
   Xfiles.push_back(filex2BGOD13);
   Xfiles.push_back(filex2BGOD23);

   // X-ray cascade dA1 = 450 mm		 
   Xfiles.push_back(filexSciD14);
   Xfiles.push_back(filexSciD24);
   Xfiles.push_back(filexSciD34);
   Xfiles.push_back(filexBGOD14);
   Xfiles.push_back(filexBGOD24);

   Xfiles.push_back(filex2SciD14);
   Xfiles.push_back(filex2SciD24);
   Xfiles.push_back(filex2SciD34);
   Xfiles.push_back(filex2BGOD14);
   Xfiles.push_back(filex2BGOD24);

   // X-ray cascade dA1 = 500 mm		 
   Xfiles.push_back(filexSciD15);
   Xfiles.push_back(filexSciD25);
   Xfiles.push_back(filexSciD35);
   Xfiles.push_back(filexBGOD15);
   Xfiles.push_back(filexBGOD25);

   Xfiles.push_back(filex2SciD15);
   Xfiles.push_back(filex2SciD25);
   Xfiles.push_back(filex2SciD35);
   Xfiles.push_back(filex2BGOD15);
   Xfiles.push_back(filex2BGOD25);


   // Mu-decay dA1 = 300 mm
   mufiles.push_back(filemuSciD1);
   mufiles.push_back(filemuSciD2);
   mufiles.push_back(filemuSciD3);
   mufiles.push_back(filemuBGOD1);
   mufiles.push_back(filemuBGOD2);

   mufiles.push_back(filemu2SciD1);
   mufiles.push_back(filemu2SciD2);
   mufiles.push_back(filemu2SciD3);
   mufiles.push_back(filemu2BGOD1);
   mufiles.push_back(filemu2BGOD2);

   // Mu-decay dA1 = 350 mm
   mufiles.push_back(filemuSciD12);
   mufiles.push_back(filemuSciD22);
   mufiles.push_back(filemuSciD32);
   mufiles.push_back(filemuBGOD12);
   mufiles.push_back(filemuBGOD22);

   mufiles.push_back(filemu2SciD12);
   mufiles.push_back(filemu2SciD22);
   mufiles.push_back(filemu2SciD32);
   mufiles.push_back(filemu2BGOD12);
   mufiles.push_back(filemu2BGOD22);

   // Mu-decay dA1 = 400 mm
   mufiles.push_back(filemuSciD13);
   mufiles.push_back(filemuSciD23);
   mufiles.push_back(filemuSciD33);
   mufiles.push_back(filemuBGOD13);
   mufiles.push_back(filemuBGOD23);

   mufiles.push_back(filemu2SciD13);
   mufiles.push_back(filemu2SciD23);
   mufiles.push_back(filemu2SciD33);
   mufiles.push_back(filemu2BGOD13);
   mufiles.push_back(filemu2BGOD23);
   
   // Mu-decay dA1 = 450 mm
   mufiles.push_back(filemuSciD14);
   mufiles.push_back(filemuSciD24);
   mufiles.push_back(filemuSciD34);
   mufiles.push_back(filemuBGOD14);
   mufiles.push_back(filemuBGOD24);

   mufiles.push_back(filemu2SciD14);
   mufiles.push_back(filemu2SciD24);
   mufiles.push_back(filemu2SciD34);
   mufiles.push_back(filemu2BGOD14);
   mufiles.push_back(filemu2BGOD24);

   // Mu-decay dA1 = 500 mm
   mufiles.push_back(filemuSciD15);
   mufiles.push_back(filemuSciD25);
   mufiles.push_back(filemuSciD35);
   mufiles.push_back(filemuBGOD15);
   mufiles.push_back(filemuBGOD25);

   mufiles.push_back(filemu2SciD15);
   mufiles.push_back(filemu2SciD25);
   mufiles.push_back(filemu2SciD35);
   mufiles.push_back(filemu2BGOD15);
   mufiles.push_back(filemu2BGOD25);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep, EventID;
   float iEventID;

   float Ethr1 = 0.3;
   float Ethr21 = 0.5;
   float Ethr22 = 10;
   float Ethr3 = 1;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
   
   std::stringstream Ethr1str;
   
   Ethr1str << Ethr1;
		   
   // Storage vectors
   // Normalisation 2 [abs = total] :: X-ray cascade [Cu] dA1 = 300 mm
   std::vector< std::vector<double> > PXevector(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector(Xfiles.size()/50,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector(Xfiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [glass] dA1 = 300 mm
   std::vector< std::vector<double> > PXevector2(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2(Xfiles.size()/50,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector2(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2(Xfiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [Cu] dA1 = 350 mm
   std::vector< std::vector<double> > PXevectord2(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectord2(Xfiles.size()/50,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevectord2(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectord2(Xfiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [glass] dA1 = 350 mm
   std::vector< std::vector<double> > PXevector2d2(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2d2(Xfiles.size()/50,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector2d2(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2d2(Xfiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [Cu] dA1 = 400 mm
   std::vector< std::vector<double> > PXevectord3(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectord3(Xfiles.size()/50,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevectord3(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectord3(Xfiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [glass] dA1 = 400 mm
   std::vector< std::vector<double> > PXevector2d3(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2d3(Xfiles.size()/50,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector2d3(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2d3(Xfiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [Cu] dA1 = 450 mm
   std::vector< std::vector<double> > PXevectord4(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectord4(Xfiles.size()/50,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevectord4(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectord4(Xfiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [glass] dA1 = 450 mm
   std::vector< std::vector<double> > PXevector2d4(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2d4(Xfiles.size()/50,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector2d4(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2d4(Xfiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [Cu] dA1 = 500 mm
   std::vector< std::vector<double> > PXevectord5(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectord5(Xfiles.size()/50,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevectord5(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectord5(Xfiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade [glass] dA1 = 500 mm
   std::vector< std::vector<double> > PXevector2d5(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2d5(Xfiles.size()/50,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector2d5(Xfiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector2d5(Xfiles.size()/50,std::vector<double>(nsamps));      



   // Normalisation 2 [abs = total] :: Mu-decay [Cu] dA1 = 300 mm
   std::vector< std::vector<double> > Peevector(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector(mufiles.size()/50,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector(mufiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [glass] dA1 = 300 mm
   std::vector< std::vector<double> > Peevector2(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2(mufiles.size()/50,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector2(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2(mufiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [Cu] dA1 = 350 mm
   std::vector< std::vector<double> > Peevectord2(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectord2(mufiles.size()/50,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevectord2(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectord2(mufiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [glass] dA1 = 350 mm
   std::vector< std::vector<double> > Peevector2d2(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2d2(mufiles.size()/50,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector2d2(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2d2(mufiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [Cu] dA1 = 400 mm
   std::vector< std::vector<double> > Peevectord3(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectord3(mufiles.size()/50,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevectord3(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectord3(mufiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [glass] dA1 = 400 mm
   std::vector< std::vector<double> > Peevector2d3(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2d3(mufiles.size()/50,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector2d3(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2d3(mufiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [Cu] dA1 = 450 mm
   std::vector< std::vector<double> > Peevectord4(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectord4(mufiles.size()/50,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevectord4(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectord4(mufiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [glass] dA1 = 450 mm
   std::vector< std::vector<double> > Peevector2d4(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2d4(mufiles.size()/50,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector2d4(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2d4(mufiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [Cu] dA1 = 500 mm
   std::vector< std::vector<double> > Peevectord5(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectord5(mufiles.size()/50,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevectord5(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectord5(mufiles.size()/50,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay [glass] dA1 = 500 mm
   std::vector< std::vector<double> > Peevector2d5(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2d5(mufiles.size()/50,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector2d5(mufiles.size()/50,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector2d5(mufiles.size()/50,std::vector<double>(nsamps));      


   // X-ray cascade dA1 = 300 mm
   std::vector< std::vector< double > > allvEvIDSD1x;
   std::vector< std::vector< double > > allvEdepSD1x;
   std::vector< std::vector< double > > allvEvIDSD2x;
   std::vector< std::vector< double > > allvEdepSD2x;
   std::vector< std::vector< double > > allvEvIDSD3x;
   std::vector< std::vector< double > > allvEdepSD3x;
   std::vector< std::vector< double > > allvEvIDBD1x;
   std::vector< std::vector< double > > allvEdepBD1x;
   std::vector< std::vector< double > > allvEvIDBD2x;
   std::vector< std::vector< double > > allvEdepBD2x;

   std::vector< std::vector< double > > allvEvIDSD1x2;
   std::vector< std::vector< double > > allvEdepSD1x2;
   std::vector< std::vector< double > > allvEvIDSD2x2;
   std::vector< std::vector< double > > allvEdepSD2x2;
   std::vector< std::vector< double > > allvEvIDSD3x2;
   std::vector< std::vector< double > > allvEdepSD3x2;
   std::vector< std::vector< double > > allvEvIDBD1x2;
   std::vector< std::vector< double > > allvEdepBD1x2;
   std::vector< std::vector< double > > allvEvIDBD2x2;
   std::vector< std::vector< double > > allvEdepBD2x2;

   // X-ray cascade dA1 = 350 mm
   std::vector< std::vector< double > > allvEvIDSD1xd2;
   std::vector< std::vector< double > > allvEdepSD1xd2;
   std::vector< std::vector< double > > allvEvIDSD2xd2;
   std::vector< std::vector< double > > allvEdepSD2xd2;
   std::vector< std::vector< double > > allvEvIDSD3xd2;
   std::vector< std::vector< double > > allvEdepSD3xd2;
   std::vector< std::vector< double > > allvEvIDBD1xd2;
   std::vector< std::vector< double > > allvEdepBD1xd2;
   std::vector< std::vector< double > > allvEvIDBD2xd2;
   std::vector< std::vector< double > > allvEdepBD2xd2;

   std::vector< std::vector< double > > allvEvIDSD1x2d2;
   std::vector< std::vector< double > > allvEdepSD1x2d2;
   std::vector< std::vector< double > > allvEvIDSD2x2d2;
   std::vector< std::vector< double > > allvEdepSD2x2d2;
   std::vector< std::vector< double > > allvEvIDSD3x2d2;
   std::vector< std::vector< double > > allvEdepSD3x2d2;
   std::vector< std::vector< double > > allvEvIDBD1x2d2;
   std::vector< std::vector< double > > allvEdepBD1x2d2;
   std::vector< std::vector< double > > allvEvIDBD2x2d2;
   std::vector< std::vector< double > > allvEdepBD2x2d2;
   
   // X-ray cascade dA1 = 400 mm
   std::vector< std::vector< double > > allvEvIDSD1xd3;
   std::vector< std::vector< double > > allvEdepSD1xd3;
   std::vector< std::vector< double > > allvEvIDSD2xd3;
   std::vector< std::vector< double > > allvEdepSD2xd3;
   std::vector< std::vector< double > > allvEvIDSD3xd3;
   std::vector< std::vector< double > > allvEdepSD3xd3;
   std::vector< std::vector< double > > allvEvIDBD1xd3;
   std::vector< std::vector< double > > allvEdepBD1xd3;
   std::vector< std::vector< double > > allvEvIDBD2xd3;
   std::vector< std::vector< double > > allvEdepBD2xd3;

   std::vector< std::vector< double > > allvEvIDSD1x2d3;
   std::vector< std::vector< double > > allvEdepSD1x2d3;
   std::vector< std::vector< double > > allvEvIDSD2x2d3;
   std::vector< std::vector< double > > allvEdepSD2x2d3;
   std::vector< std::vector< double > > allvEvIDSD3x2d3;
   std::vector< std::vector< double > > allvEdepSD3x2d3;
   std::vector< std::vector< double > > allvEvIDBD1x2d3;
   std::vector< std::vector< double > > allvEdepBD1x2d3;
   std::vector< std::vector< double > > allvEvIDBD2x2d3;
   std::vector< std::vector< double > > allvEdepBD2x2d3;

   // X-ray cascade dA1 = 450 mm
   std::vector< std::vector< double > > allvEvIDSD1xd4;
   std::vector< std::vector< double > > allvEdepSD1xd4;
   std::vector< std::vector< double > > allvEvIDSD2xd4;
   std::vector< std::vector< double > > allvEdepSD2xd4;
   std::vector< std::vector< double > > allvEvIDSD3xd4;
   std::vector< std::vector< double > > allvEdepSD3xd4;
   std::vector< std::vector< double > > allvEvIDBD1xd4;
   std::vector< std::vector< double > > allvEdepBD1xd4;
   std::vector< std::vector< double > > allvEvIDBD2xd4;
   std::vector< std::vector< double > > allvEdepBD2xd4;

   std::vector< std::vector< double > > allvEvIDSD1x2d4;
   std::vector< std::vector< double > > allvEdepSD1x2d4;
   std::vector< std::vector< double > > allvEvIDSD2x2d4;
   std::vector< std::vector< double > > allvEdepSD2x2d4;
   std::vector< std::vector< double > > allvEvIDSD3x2d4;
   std::vector< std::vector< double > > allvEdepSD3x2d4;
   std::vector< std::vector< double > > allvEvIDBD1x2d4;
   std::vector< std::vector< double > > allvEdepBD1x2d4;
   std::vector< std::vector< double > > allvEvIDBD2x2d4;
   std::vector< std::vector< double > > allvEdepBD2x2d4;

   // X-ray cascade dA1 = 500 mm
   std::vector< std::vector< double > > allvEvIDSD1xd5;
   std::vector< std::vector< double > > allvEdepSD1xd5;
   std::vector< std::vector< double > > allvEvIDSD2xd5;
   std::vector< std::vector< double > > allvEdepSD2xd5;
   std::vector< std::vector< double > > allvEvIDSD3xd5;
   std::vector< std::vector< double > > allvEdepSD3xd5;
   std::vector< std::vector< double > > allvEvIDBD1xd5;
   std::vector< std::vector< double > > allvEdepBD1xd5;
   std::vector< std::vector< double > > allvEvIDBD2xd5;
   std::vector< std::vector< double > > allvEdepBD2xd5;

   std::vector< std::vector< double > > allvEvIDSD1x2d5;
   std::vector< std::vector< double > > allvEdepSD1x2d5;
   std::vector< std::vector< double > > allvEvIDSD2x2d5;
   std::vector< std::vector< double > > allvEdepSD2x2d5;
   std::vector< std::vector< double > > allvEvIDSD3x2d5;
   std::vector< std::vector< double > > allvEdepSD3x2d5;
   std::vector< std::vector< double > > allvEvIDBD1x2d5;
   std::vector< std::vector< double > > allvEdepBD1x2d5;
   std::vector< std::vector< double > > allvEvIDBD2x2d5;
   std::vector< std::vector< double > > allvEdepBD2x2d5;


   // Mu-decay dA1 = 300 mm
   std::vector< std::vector< double > > allvEvIDSD1mu;
   std::vector< std::vector< double > > allvEdepSD1mu;
   std::vector< std::vector< double > > allvEvIDSD2mu;
   std::vector< std::vector< double > > allvEdepSD2mu;
   std::vector< std::vector< double > > allvEvIDSD3mu;
   std::vector< std::vector< double > > allvEdepSD3mu;
   std::vector< std::vector< double > > allvEvIDBD1mu;
   std::vector< std::vector< double > > allvEdepBD1mu;
   std::vector< std::vector< double > > allvEvIDBD2mu;
   std::vector< std::vector< double > > allvEdepBD2mu;

   std::vector< std::vector< double > > allvEvIDSD1mu2;
   std::vector< std::vector< double > > allvEdepSD1mu2;
   std::vector< std::vector< double > > allvEvIDSD2mu2;
   std::vector< std::vector< double > > allvEdepSD2mu2;
   std::vector< std::vector< double > > allvEvIDSD3mu2;
   std::vector< std::vector< double > > allvEdepSD3mu2;
   std::vector< std::vector< double > > allvEvIDBD1mu2;
   std::vector< std::vector< double > > allvEdepBD1mu2;
   std::vector< std::vector< double > > allvEvIDBD2mu2;
   std::vector< std::vector< double > > allvEdepBD2mu2;

   // Mu-decay dA1 = 350 mm
   std::vector< std::vector< double > > allvEvIDSD1mud2;
   std::vector< std::vector< double > > allvEdepSD1mud2;
   std::vector< std::vector< double > > allvEvIDSD2mud2;
   std::vector< std::vector< double > > allvEdepSD2mud2;
   std::vector< std::vector< double > > allvEvIDSD3mud2;
   std::vector< std::vector< double > > allvEdepSD3mud2;
   std::vector< std::vector< double > > allvEvIDBD1mud2;
   std::vector< std::vector< double > > allvEdepBD1mud2;
   std::vector< std::vector< double > > allvEvIDBD2mud2;
   std::vector< std::vector< double > > allvEdepBD2mud2;

   std::vector< std::vector< double > > allvEvIDSD1mu2d2;
   std::vector< std::vector< double > > allvEdepSD1mu2d2;
   std::vector< std::vector< double > > allvEvIDSD2mu2d2;
   std::vector< std::vector< double > > allvEdepSD2mu2d2;
   std::vector< std::vector< double > > allvEvIDSD3mu2d2;
   std::vector< std::vector< double > > allvEdepSD3mu2d2;
   std::vector< std::vector< double > > allvEvIDBD1mu2d2;
   std::vector< std::vector< double > > allvEdepBD1mu2d2;
   std::vector< std::vector< double > > allvEvIDBD2mu2d2;
   std::vector< std::vector< double > > allvEdepBD2mu2d2;
   
   // Mu-decay dA1 = 400 mm
   std::vector< std::vector< double > > allvEvIDSD1mud3;
   std::vector< std::vector< double > > allvEdepSD1mud3;
   std::vector< std::vector< double > > allvEvIDSD2mud3;
   std::vector< std::vector< double > > allvEdepSD2mud3;
   std::vector< std::vector< double > > allvEvIDSD3mud3;
   std::vector< std::vector< double > > allvEdepSD3mud3;
   std::vector< std::vector< double > > allvEvIDBD1mud3;
   std::vector< std::vector< double > > allvEdepBD1mud3;
   std::vector< std::vector< double > > allvEvIDBD2mud3;
   std::vector< std::vector< double > > allvEdepBD2mud3;

   std::vector< std::vector< double > > allvEvIDSD1mu2d3;
   std::vector< std::vector< double > > allvEdepSD1mu2d3;
   std::vector< std::vector< double > > allvEvIDSD2mu2d3;
   std::vector< std::vector< double > > allvEdepSD2mu2d3;
   std::vector< std::vector< double > > allvEvIDSD3mu2d3;
   std::vector< std::vector< double > > allvEdepSD3mu2d3;
   std::vector< std::vector< double > > allvEvIDBD1mu2d3;
   std::vector< std::vector< double > > allvEdepBD1mu2d3;
   std::vector< std::vector< double > > allvEvIDBD2mu2d3;
   std::vector< std::vector< double > > allvEdepBD2mu2d3;
   
   // Mu-decay dA1 = 450 mm
   std::vector< std::vector< double > > allvEvIDSD1mud4;
   std::vector< std::vector< double > > allvEdepSD1mud4;
   std::vector< std::vector< double > > allvEvIDSD2mud4;
   std::vector< std::vector< double > > allvEdepSD2mud4;
   std::vector< std::vector< double > > allvEvIDSD3mud4;
   std::vector< std::vector< double > > allvEdepSD3mud4;
   std::vector< std::vector< double > > allvEvIDBD1mud4;
   std::vector< std::vector< double > > allvEdepBD1mud4;
   std::vector< std::vector< double > > allvEvIDBD2mud4;
   std::vector< std::vector< double > > allvEdepBD2mud4;

   std::vector< std::vector< double > > allvEvIDSD1mu2d4;
   std::vector< std::vector< double > > allvEdepSD1mu2d4;
   std::vector< std::vector< double > > allvEvIDSD2mu2d4;
   std::vector< std::vector< double > > allvEdepSD2mu2d4;
   std::vector< std::vector< double > > allvEvIDSD3mu2d4;
   std::vector< std::vector< double > > allvEdepSD3mu2d4;
   std::vector< std::vector< double > > allvEvIDBD1mu2d4;
   std::vector< std::vector< double > > allvEdepBD1mu2d4;
   std::vector< std::vector< double > > allvEvIDBD2mu2d4;
   std::vector< std::vector< double > > allvEdepBD2mu2d4;
   
   // Mu-decay dA1 = 500 mm
   std::vector< std::vector< double > > allvEvIDSD1mud5;
   std::vector< std::vector< double > > allvEdepSD1mud5;
   std::vector< std::vector< double > > allvEvIDSD2mud5;
   std::vector< std::vector< double > > allvEdepSD2mud5;
   std::vector< std::vector< double > > allvEvIDSD3mud5;
   std::vector< std::vector< double > > allvEdepSD3mud5;
   std::vector< std::vector< double > > allvEvIDBD1mud5;
   std::vector< std::vector< double > > allvEdepBD1mud5;
   std::vector< std::vector< double > > allvEvIDBD2mud5;
   std::vector< std::vector< double > > allvEdepBD2mud5;

   std::vector< std::vector< double > > allvEvIDSD1mu2d5;
   std::vector< std::vector< double > > allvEdepSD1mu2d5;
   std::vector< std::vector< double > > allvEvIDSD2mu2d5;
   std::vector< std::vector< double > > allvEdepSD2mu2d5;
   std::vector< std::vector< double > > allvEvIDSD3mu2d5;
   std::vector< std::vector< double > > allvEdepSD3mu2d5;
   std::vector< std::vector< double > > allvEvIDBD1mu2d5;
   std::vector< std::vector< double > > allvEdepBD1mu2d5;
   std::vector< std::vector< double > > allvEvIDBD2mu2d5;
   std::vector< std::vector< double > > allvEdepBD2mu2d5;


   float Ethr;
   int counterXX = 1e5;
   int counteree = 1e5;
   int XXray = 0; // X-rays i-fied as X-rays
   int Xelec = 0; // X-rays i-fied as electrons
   int XXray2 = 0;
   int Xelec2 = 0;
   int XXrayd2 = 0;
   int Xelecd2 = 0;
   int XXray2d2 = 0;
   int Xelec2d2 = 0;
   int XXrayd3 = 0;
   int Xelecd3 = 0;
   int XXray2d3 = 0;
   int Xelec2d3 = 0;
   int XXrayd4 = 0;
   int Xelecd4 = 0;
   int XXray2d4 = 0;
   int Xelec2d4 = 0;
   int XXrayd5 = 0;
   int Xelecd5 = 0;
   int XXray2d5 = 0;
   int Xelec2d5 = 0;
   int eXray = 0; // Electrons i-fied as X-rays
   int eelec = 0; // Electrons i-fied as electrons
   int eXray2 = 0;
   int eelec2 = 0;	
   int eXrayd2 = 0;
   int eelecd2 = 0;   
   int eXray2d2 = 0;
   int eelec2d2 = 0;	
   int eXrayd3 = 0;
   int eelecd3 = 0;   
   int eXray2d3 = 0;
   int eelec2d3 = 0;	
   int eXrayd4 = 0;
   int eelecd4 = 0;   
   int eXray2d4 = 0;
   int eelec2d4 = 0;	
   int eXrayd5 = 0;
   int eelecd5 = 0;
   int eXray2d5 = 0;
   int eelec2d5 = 0;  

   Ethrmu[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;


   //-------------------------------------------------------------------
   //                           Reading
   //-------------------------------------------------------------------
		   
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m------------------- X-ray cascade ------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


   for (int k=0; k<((Xfiles.size())/50); k++) {
			  
      // SciD1 dA1 = 300 mm
	  std::ifstream xfSciD1(TString(Xfiles[k*50]));
	  std::vector<double> vEvIDSD1x;
	  std::vector<double> vEdepSD1x;
			  
	  while (!xfSciD1.eof()) {
	     double EvIDSD1, EdepSD1;
		 xfSciD1 >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1x.push_back(EvIDSD1);
		 vEdepSD1x.push_back(EdepSD1);
	  }
	  vEvIDSD1x.pop_back(); vEdepSD1x.pop_back();
	  vEvIDSD1x.pop_back(); vEdepSD1x.pop_back();
			  
	  xfSciD1.close();
	  allvEvIDSD1x.push_back(vEvIDSD1x);
	  allvEdepSD1x.push_back(vEdepSD1x);


	  // SciD2
	  std::ifstream xfSciD2(TString(Xfiles[(k*50)+1]));
	  std::vector<double> vEvIDSD2x;
	  std::vector<double> vEdepSD2x;
			  
	  while (!xfSciD2.eof()) {
	     double EvIDSD2, EdepSD2;
		 xfSciD2 >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2x.push_back(EvIDSD2);
		 vEdepSD2x.push_back(EdepSD2);
	  }
	  vEvIDSD2x.pop_back(); vEdepSD2x.pop_back();
	  vEvIDSD2x.pop_back(); vEdepSD2x.pop_back();
			  
	  xfSciD2.close();
	  allvEvIDSD2x.push_back(vEvIDSD2x);
	  allvEdepSD2x.push_back(vEdepSD2x);


	  // SciD3
	  std::ifstream xfSciD3(TString(Xfiles[(k*50)+2]));
	  std::vector<double> vEvIDSD3x;
	  std::vector<double> vEdepSD3x;
			  
	  while (!xfSciD3.eof()) {
	     double EvIDSD3, EdepSD3;
		 xfSciD3 >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3x.push_back(EvIDSD3);
		 vEdepSD3x.push_back(EdepSD3);
	  }
	  vEvIDSD3x.pop_back(); vEdepSD3x.pop_back();
	  vEvIDSD3x.pop_back(); vEdepSD3x.pop_back();
			  
	  xfSciD3.close();
	  allvEvIDSD3x.push_back(vEvIDSD3x);
	  allvEdepSD3x.push_back(vEdepSD3x);
			  
			  
	  // BGOD1
	  std::ifstream xfBGOD1(TString(Xfiles[(k*50)+3]));
	  std::vector<double> vEvIDBD1x;
	  std::vector<double> vEdepBD1x;
			  
	  while (!xfBGOD1.eof()) {
	     double EvIDBD1, EdepBD1;
		 xfBGOD1 >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1x.push_back(EvIDBD1);
		 vEdepBD1x.push_back(EdepBD1);
	  }
	  vEvIDBD1x.pop_back(); vEdepBD1x.pop_back();
	  vEvIDBD1x.pop_back(); vEdepBD1x.pop_back();
			  
	  xfBGOD1.close();
	  allvEvIDBD1x.push_back(vEvIDBD1x);
	  allvEdepBD1x.push_back(vEdepBD1x);


	  // BGOD2
	  std::ifstream xfBGOD2(TString(Xfiles[(k*50)+4]));
	  std::vector<double> vEvIDBD2x;
	  std::vector<double> vEdepBD2x;
			  
	  while (!xfBGOD2.eof()) {
	     double EvIDBD2, EdepBD2;
		 xfBGOD2 >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2x.push_back(EvIDBD2);
		 vEdepBD2x.push_back(EdepBD2);
	  }
	  vEvIDBD2x.pop_back(); vEdepBD2x.pop_back();
	  vEvIDBD2x.pop_back(); vEdepBD2x.pop_back();
			  
	  xfBGOD2.close();
	  allvEvIDBD2x.push_back(vEvIDBD2x);
	  allvEdepBD2x.push_back(vEdepBD2x);


      // SciD1
	  std::ifstream x2fSciD1(TString(Xfiles[(k*50)+5]));
	  std::vector<double> vEvIDSD1x2;
	  std::vector<double> vEdepSD1x2;
			  
	  while (!x2fSciD1.eof()) {
	     double EvIDSD1, EdepSD1;
		 x2fSciD1 >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1x2.push_back(EvIDSD1);
		 vEdepSD1x2.push_back(EdepSD1);
	  }
	  vEvIDSD1x2.pop_back(); vEdepSD1x2.pop_back();
	  vEvIDSD1x2.pop_back(); vEdepSD1x2.pop_back();
			  
	  x2fSciD1.close();
	  allvEvIDSD1x2.push_back(vEvIDSD1x2);
	  allvEdepSD1x2.push_back(vEdepSD1x2);


	  // SciD2
	  std::ifstream x2fSciD2(TString(Xfiles[(k*50)+6]));
	  std::vector<double> vEvIDSD2x2;
	  std::vector<double> vEdepSD2x2;
			  
	  while (!x2fSciD2.eof()) {
	     double EvIDSD2, EdepSD2;
		 x2fSciD2 >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2x2.push_back(EvIDSD2);
		 vEdepSD2x2.push_back(EdepSD2);
	  }
	  vEvIDSD2x2.pop_back(); vEdepSD2x2.pop_back();
	  vEvIDSD2x2.pop_back(); vEdepSD2x2.pop_back();
			  
	  x2fSciD2.close();
	  allvEvIDSD2x2.push_back(vEvIDSD2x2);
	  allvEdepSD2x2.push_back(vEdepSD2x2);


	  // SciD3
	  std::ifstream x2fSciD3(TString(Xfiles[(k*50)+7]));
	  std::vector<double> vEvIDSD3x2;
	  std::vector<double> vEdepSD3x2;
			  
	  while (!x2fSciD3.eof()) {
	     double EvIDSD3, EdepSD3;
		 x2fSciD3 >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3x2.push_back(EvIDSD3);
		 vEdepSD3x2.push_back(EdepSD3);
	  }
	  vEvIDSD3x2.pop_back(); vEdepSD3x2.pop_back();
	  vEvIDSD3x2.pop_back(); vEdepSD3x2.pop_back();
			  
	  x2fSciD3.close();
	  allvEvIDSD3x2.push_back(vEvIDSD3x2);
	  allvEdepSD3x2.push_back(vEdepSD3x2);
			  
			  
	  // BGOD1
	  std::ifstream x2fBGOD1(TString(Xfiles[(k*50)+8]));
	  std::vector<double> vEvIDBD1x2;
	  std::vector<double> vEdepBD1x2;
			  
	  while (!x2fBGOD1.eof()) {
	     double EvIDBD1, EdepBD1;
		 x2fBGOD1 >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1x2.push_back(EvIDBD1);
		 vEdepBD1x2.push_back(EdepBD1);
	  }
	  vEvIDBD1x2.pop_back(); vEdepBD1x2.pop_back();
	  vEvIDBD1x2.pop_back(); vEdepBD1x2.pop_back();
			  
	  x2fBGOD1.close();
	  allvEvIDBD1x2.push_back(vEvIDBD1x2);
	  allvEdepBD1x2.push_back(vEdepBD1x2);


	  // BGOD2
	  std::ifstream x2fBGOD2(TString(Xfiles[(k*50)+9]));
	  std::vector<double> vEvIDBD2x2;
	  std::vector<double> vEdepBD2x2;
			  
	  while (!x2fBGOD2.eof()) {
	     double EvIDBD2, EdepBD2;
		 x2fBGOD2 >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2x2.push_back(EvIDBD2);
		 vEdepBD2x2.push_back(EdepBD2);
	  }
	  vEvIDBD2x2.pop_back(); vEdepBD2x2.pop_back();
	  vEvIDBD2x2.pop_back(); vEdepBD2x2.pop_back();
			  
	  x2fBGOD2.close();
	  allvEvIDBD2x2.push_back(vEvIDBD2x2);
	  allvEdepBD2x2.push_back(vEdepBD2x2);


      // SciD1 dA1 = 350 mm
	  std::ifstream xfSciD1d2(TString(Xfiles[(k*50)+10]));
	  std::vector<double> vEvIDSD1xd2;
	  std::vector<double> vEdepSD1xd2;
			  
	  while (!xfSciD1d2.eof()) {
	     double EvIDSD1, EdepSD1;
		 xfSciD1d2 >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1xd2.push_back(EvIDSD1);
		 vEdepSD1xd2.push_back(EdepSD1);
	  }
	  vEvIDSD1xd2.pop_back(); vEdepSD1xd2.pop_back();
	  vEvIDSD1xd2.pop_back(); vEdepSD1xd2.pop_back();
			  
	  xfSciD1d2.close();
	  allvEvIDSD1xd2.push_back(vEvIDSD1xd2);
	  allvEdepSD1xd2.push_back(vEdepSD1xd2);


	  // SciD2
	  std::ifstream xfSciD2d2(TString(Xfiles[(k*50)+11]));
	  std::vector<double> vEvIDSD2xd2;
	  std::vector<double> vEdepSD2xd2;
			  
	  while (!xfSciD2d2.eof()) {
	     double EvIDSD2, EdepSD2;
		 xfSciD2d2 >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2xd2.push_back(EvIDSD2);
		 vEdepSD2xd2.push_back(EdepSD2);
	  }
	  vEvIDSD2xd2.pop_back(); vEdepSD2xd2.pop_back();
	  vEvIDSD2xd2.pop_back(); vEdepSD2xd2.pop_back();
			  
	  xfSciD2d2.close();
	  allvEvIDSD2xd2.push_back(vEvIDSD2xd2);
	  allvEdepSD2xd2.push_back(vEdepSD2xd2);


	  // SciD3
	  std::ifstream xfSciD3d2(TString(Xfiles[(k*50)+12]));
	  std::vector<double> vEvIDSD3xd2;
	  std::vector<double> vEdepSD3xd2;
			  
	  while (!xfSciD3d2.eof()) {
	     double EvIDSD3, EdepSD3;
		 xfSciD3d2 >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3xd2.push_back(EvIDSD3);
		 vEdepSD3xd2.push_back(EdepSD3);
	  }
	  vEvIDSD3xd2.pop_back(); vEdepSD3xd2.pop_back();
	  vEvIDSD3xd2.pop_back(); vEdepSD3xd2.pop_back();
			  
	  xfSciD3d2.close();
	  allvEvIDSD3xd2.push_back(vEvIDSD3x);
	  allvEdepSD3xd2.push_back(vEdepSD3x);
			  
			  
	  // BGOD1
	  std::ifstream xfBGOD1d2(TString(Xfiles[(k*50)+13]));
	  std::vector<double> vEvIDBD1xd2;
	  std::vector<double> vEdepBD1xd2;
			  
	  while (!xfBGOD1d2.eof()) {
	     double EvIDBD1, EdepBD1;
		 xfBGOD1d2 >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1xd2.push_back(EvIDBD1);
		 vEdepBD1xd2.push_back(EdepBD1);
	  }
	  vEvIDBD1xd2.pop_back(); vEdepBD1xd2.pop_back();
	  vEvIDBD1xd2.pop_back(); vEdepBD1xd2.pop_back();
			  
	  xfBGOD1d2.close();
	  allvEvIDBD1xd2.push_back(vEvIDBD1xd2);
	  allvEdepBD1xd2.push_back(vEdepBD1xd2);


	  // BGOD2
	  std::ifstream xfBGOD2d2(TString(Xfiles[(k*50)+14]));
	  std::vector<double> vEvIDBD2xd2;
	  std::vector<double> vEdepBD2xd2;
			  
	  while (!xfBGOD2d2.eof()) {
	     double EvIDBD2, EdepBD2;
		 xfBGOD2d2 >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2xd2.push_back(EvIDBD2);
		 vEdepBD2xd2.push_back(EdepBD2);
	  }
	  vEvIDBD2xd2.pop_back(); vEdepBD2xd2.pop_back();
	  vEvIDBD2xd2.pop_back(); vEdepBD2xd2.pop_back();
			  
	  xfBGOD2d2.close();
	  allvEvIDBD2xd2.push_back(vEvIDBD2xd2);
	  allvEdepBD2xd2.push_back(vEdepBD2xd2);


      // SciD1
	  std::ifstream x2fSciD1d2(TString(Xfiles[(k*50)+15]));
	  std::vector<double> vEvIDSD1x2d2;
	  std::vector<double> vEdepSD1x2d2;
			  
	  while (!x2fSciD1d2.eof()) {
	     double EvIDSD1, EdepSD1;
		 x2fSciD1d2 >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1x2d2.push_back(EvIDSD1);
		 vEdepSD1x2d2.push_back(EdepSD1);
	  }
	  vEvIDSD1x2d2.pop_back(); vEdepSD1x2d2.pop_back();
	  vEvIDSD1x2d2.pop_back(); vEdepSD1x2d2.pop_back();
			  
	  x2fSciD1d2.close();
	  allvEvIDSD1x2d2.push_back(vEvIDSD1x2d2);
	  allvEdepSD1x2d2.push_back(vEdepSD1x2d2);


	  // SciD2
	  std::ifstream x2fSciD2d2(TString(Xfiles[(k*50)+16]));
	  std::vector<double> vEvIDSD2x2d2;
	  std::vector<double> vEdepSD2x2d2;
			  
	  while (!x2fSciD2d2.eof()) {
	     double EvIDSD2, EdepSD2;
		 x2fSciD2d2 >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2x2d2.push_back(EvIDSD2);
		 vEdepSD2x2d2.push_back(EdepSD2);
	  }
	  vEvIDSD2x2d2.pop_back(); vEdepSD2x2d2.pop_back();
	  vEvIDSD2x2d2.pop_back(); vEdepSD2x2d2.pop_back();
			  
	  x2fSciD2d2.close();
	  allvEvIDSD2x2d2.push_back(vEvIDSD2x2d2);
	  allvEdepSD2x2d2.push_back(vEdepSD2x2d2);


	  // SciD3
	  std::ifstream x2fSciD3d2(TString(Xfiles[(k*50)+17]));
	  std::vector<double> vEvIDSD3x2d2;
	  std::vector<double> vEdepSD3x2d2;
			  
	  while (!x2fSciD3d2.eof()) {
	     double EvIDSD3, EdepSD3;
		 x2fSciD3d2 >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3x2d2.push_back(EvIDSD3);
		 vEdepSD3x2d2.push_back(EdepSD3);
	  }
	  vEvIDSD3x2d2.pop_back(); vEdepSD3x2d2.pop_back();
	  vEvIDSD3x2d2.pop_back(); vEdepSD3x2d2.pop_back();
			  
	  x2fSciD3d2.close();
	  allvEvIDSD3x2d2.push_back(vEvIDSD3x2d2);
	  allvEdepSD3x2d2.push_back(vEdepSD3x2d2);
			  
			  
	  // BGOD1
	  std::ifstream x2fBGOD1d2(TString(Xfiles[(k*50)+18]));
	  std::vector<double> vEvIDBD1x2d2;
	  std::vector<double> vEdepBD1x2d2;
			  
	  while (!x2fBGOD1d2.eof()) {
	     double EvIDBD1, EdepBD1;
		 x2fBGOD1d2 >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1x2d2.push_back(EvIDBD1);
		 vEdepBD1x2d2.push_back(EdepBD1);
	  }
	  vEvIDBD1x2d2.pop_back(); vEdepBD1x2d2.pop_back();
	  vEvIDBD1x2d2.pop_back(); vEdepBD1x2d2.pop_back();
			  
	  x2fBGOD1d2.close();
	  allvEvIDBD1x2d2.push_back(vEvIDBD1x2d2);
	  allvEdepBD1x2d2.push_back(vEdepBD1x2d2);


	  // BGOD2
	  std::ifstream x2fBGOD2d2(TString(Xfiles[(k*50)+19]));
	  std::vector<double> vEvIDBD2x2d2;
	  std::vector<double> vEdepBD2x2d2;
			  
	  while (!x2fBGOD2d2.eof()) {
	     double EvIDBD2, EdepBD2;
		 x2fBGOD2d2 >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2x2d2.push_back(EvIDBD2);
		 vEdepBD2x2d2.push_back(EdepBD2);
	  }
	  vEvIDBD2x2d2.pop_back(); vEdepBD2x2d2.pop_back();
	  vEvIDBD2x2d2.pop_back(); vEdepBD2x2d2.pop_back();
			  
	  x2fBGOD2d2.close();
	  allvEvIDBD2x2d2.push_back(vEvIDBD2x2d2);
	  allvEdepBD2x2d2.push_back(vEdepBD2x2d2);


      // SciD1 dA1 = 400 mm
	  std::ifstream xfSciD1d3(TString(Xfiles[(k*50)+20]));
	  std::vector<double> vEvIDSD1xd3;
	  std::vector<double> vEdepSD1xd3;
			  
	  while (!xfSciD1d3.eof()) {
	     double EvIDSD1, EdepSD1;
		 xfSciD1d3 >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1xd3.push_back(EvIDSD1);
		 vEdepSD1xd3.push_back(EdepSD1);
	  }
	  vEvIDSD1xd3.pop_back(); vEdepSD1xd3.pop_back();
	  vEvIDSD1xd3.pop_back(); vEdepSD1xd3.pop_back();
			  
	  xfSciD1d3.close();
	  allvEvIDSD1xd3.push_back(vEvIDSD1xd3);
	  allvEdepSD1xd3.push_back(vEdepSD1xd3);


	  // SciD2
	  std::ifstream xfSciD2d3(TString(Xfiles[(k*50)+21]));
	  std::vector<double> vEvIDSD2xd3;
	  std::vector<double> vEdepSD2xd3;
			  
	  while (!xfSciD2d3.eof()) {
	     double EvIDSD2, EdepSD2;
		 xfSciD2d3 >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2xd3.push_back(EvIDSD2);
		 vEdepSD2xd3.push_back(EdepSD2);
	  }
	  vEvIDSD2xd3.pop_back(); vEdepSD2xd3.pop_back();
	  vEvIDSD2xd3.pop_back(); vEdepSD2xd3.pop_back();
			  
	  xfSciD2d3.close();
	  allvEvIDSD2xd3.push_back(vEvIDSD2xd3);
	  allvEdepSD2xd3.push_back(vEdepSD2xd3);


	  // SciD3
	  std::ifstream xfSciD3d3(TString(Xfiles[(k*50)+22]));
	  std::vector<double> vEvIDSD3xd3;
	  std::vector<double> vEdepSD3xd3;
			  
	  while (!xfSciD3d3.eof()) {
	     double EvIDSD3, EdepSD3;
		 xfSciD3d3 >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3xd3.push_back(EvIDSD3);
		 vEdepSD3xd3.push_back(EdepSD3);
	  }
	  vEvIDSD3xd3.pop_back(); vEdepSD3xd3.pop_back();
	  vEvIDSD3xd3.pop_back(); vEdepSD3xd3.pop_back();
			  
	  xfSciD3d3.close();
	  allvEvIDSD3xd3.push_back(vEvIDSD3xd3);
	  allvEdepSD3xd3.push_back(vEdepSD3xd3);
			  
			  
	  // BGOD1
	  std::ifstream xfBGOD1d3(TString(Xfiles[(k*50)+23]));
	  std::vector<double> vEvIDBD1xd3;
	  std::vector<double> vEdepBD1xd3;
			  
	  while (!xfBGOD1d3.eof()) {
	     double EvIDBD1, EdepBD1;
		 xfBGOD1d3 >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1xd3.push_back(EvIDBD1);
		 vEdepBD1xd3.push_back(EdepBD1);
	  }
	  vEvIDBD1xd3.pop_back(); vEdepBD1xd3.pop_back();
	  vEvIDBD1xd3.pop_back(); vEdepBD1xd3.pop_back();
			  
	  xfBGOD1d3.close();
	  allvEvIDBD1xd3.push_back(vEvIDBD1xd3);
	  allvEdepBD1xd3.push_back(vEdepBD1xd3);


	  // BGOD2
	  std::ifstream xfBGOD2d3(TString(Xfiles[(k*50)+24]));
	  std::vector<double> vEvIDBD2xd3;
	  std::vector<double> vEdepBD2xd3;
			  
	  while (!xfBGOD2d3.eof()) {
	     double EvIDBD2, EdepBD2;
		 xfBGOD2d3 >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2xd3.push_back(EvIDBD2);
		 vEdepBD2xd3.push_back(EdepBD2);
	  }
	  vEvIDBD2xd3.pop_back(); vEdepBD2xd3.pop_back();
	  vEvIDBD2xd3.pop_back(); vEdepBD2xd3.pop_back();
			  
	  xfBGOD2d3.close();
	  allvEvIDBD2xd3.push_back(vEvIDBD2xd3);
	  allvEdepBD2xd3.push_back(vEdepBD2xd3);


      // SciD1
	  std::ifstream x2fSciD1d3(TString(Xfiles[(k*50)+25]));
	  std::vector<double> vEvIDSD1x2d3;
	  std::vector<double> vEdepSD1x2d3;
			  
	  while (!x2fSciD1d3.eof()) {
	     double EvIDSD1, EdepSD1;
		 x2fSciD1d3 >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1x2d3.push_back(EvIDSD1);
		 vEdepSD1x2d3.push_back(EdepSD1);
	  }
	  vEvIDSD1x2d3.pop_back(); vEdepSD1x2d3.pop_back();
	  vEvIDSD1x2d3.pop_back(); vEdepSD1x2d3.pop_back();
			  
	  x2fSciD1d3.close();
	  allvEvIDSD1x2d3.push_back(vEvIDSD1x2d3);
	  allvEdepSD1x2d3.push_back(vEdepSD1x2d3);


	  // SciD2
	  std::ifstream x2fSciD2d3(TString(Xfiles[(k*50)+26]));
	  std::vector<double> vEvIDSD2x2d3;
	  std::vector<double> vEdepSD2x2d3;
			  
	  while (!x2fSciD2d3.eof()) {
	     double EvIDSD2, EdepSD2;
		 x2fSciD2d3 >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2x2d3.push_back(EvIDSD2);
		 vEdepSD2x2d3.push_back(EdepSD2);
	  }
	  vEvIDSD2x2d3.pop_back(); vEdepSD2x2d3.pop_back();
	  vEvIDSD2x2d3.pop_back(); vEdepSD2x2d3.pop_back();
			  
	  x2fSciD2d3.close();
	  allvEvIDSD2x2d3.push_back(vEvIDSD2x2d3);
	  allvEdepSD2x2d3.push_back(vEdepSD2x2d3);


	  // SciD3
	  std::ifstream x2fSciD3d3(TString(Xfiles[(k*50)+27]));
	  std::vector<double> vEvIDSD3x2d3;
	  std::vector<double> vEdepSD3x2d3;
			  
	  while (!x2fSciD3d3.eof()) {
	     double EvIDSD3, EdepSD3;
		 x2fSciD3d3 >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3x2d3.push_back(EvIDSD3);
		 vEdepSD3x2d3.push_back(EdepSD3);
	  }
	  vEvIDSD3x2d3.pop_back(); vEdepSD3x2d3.pop_back();
	  vEvIDSD3x2d3.pop_back(); vEdepSD3x2d3.pop_back();
			  
	  x2fSciD3d3.close();
	  allvEvIDSD3x2d3.push_back(vEvIDSD3x2d3);
	  allvEdepSD3x2d3.push_back(vEdepSD3x2d3);
			  
			  
	  // BGOD1
	  std::ifstream x2fBGOD1d3(TString(Xfiles[(k*50)+28]));
	  std::vector<double> vEvIDBD1x2d3;
	  std::vector<double> vEdepBD1x2d3;
			  
	  while (!x2fBGOD1d3.eof()) {
	     double EvIDBD1, EdepBD1;
		 x2fBGOD1d3 >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1x2d3.push_back(EvIDBD1);
		 vEdepBD1x2d3.push_back(EdepBD1);
	  }
	  vEvIDBD1x2d3.pop_back(); vEdepBD1x2d3.pop_back();
	  vEvIDBD1x2d3.pop_back(); vEdepBD1x2d3.pop_back();
			  
	  x2fBGOD1d3.close();
	  allvEvIDBD1x2d3.push_back(vEvIDBD1x2d3);
	  allvEdepBD1x2d3.push_back(vEdepBD1x2d3);


	  // BGOD2
	  std::ifstream x2fBGOD2d3(TString(Xfiles[(k*50)+29]));
	  std::vector<double> vEvIDBD2x2d3;
	  std::vector<double> vEdepBD2x2d3;
			  
	  while (!x2fBGOD2d3.eof()) {
	     double EvIDBD2, EdepBD2;
		 x2fBGOD2d3 >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2x2d3.push_back(EvIDBD2);
		 vEdepBD2x2d3.push_back(EdepBD2);
	  }
	  vEvIDBD2x2d3.pop_back(); vEdepBD2x2d3.pop_back();
	  vEvIDBD2x2d3.pop_back(); vEdepBD2x2d3.pop_back();
			  
	  x2fBGOD2d3.close();
	  allvEvIDBD2x2d3.push_back(vEvIDBD2x2d3);
	  allvEdepBD2x2d3.push_back(vEdepBD2x2d3);


      // SciD1 dA1 = 450 mm
	  std::ifstream xfSciD1d4(TString(Xfiles[(k*50)+30]));
	  std::vector<double> vEvIDSD1xd4;
	  std::vector<double> vEdepSD1xd4;
			  
	  while (!xfSciD1d4.eof()) {
	     double EvIDSD1, EdepSD1;
		 xfSciD1d4 >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1xd4.push_back(EvIDSD1);
		 vEdepSD1xd4.push_back(EdepSD1);
	  }
	  vEvIDSD1xd4.pop_back(); vEdepSD1xd4.pop_back();
	  vEvIDSD1xd4.pop_back(); vEdepSD1xd4.pop_back();
			  
	  xfSciD1d4.close();
	  allvEvIDSD1xd4.push_back(vEvIDSD1xd4);
	  allvEdepSD1xd4.push_back(vEdepSD1xd4);


	  // SciD2
	  std::ifstream xfSciD2d4(TString(Xfiles[(k*50)+31]));
	  std::vector<double> vEvIDSD2xd4;
	  std::vector<double> vEdepSD2xd4;
			  
	  while (!xfSciD2d4.eof()) {
	     double EvIDSD2, EdepSD2;
		 xfSciD2d4 >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2xd4.push_back(EvIDSD2);
		 vEdepSD2xd4.push_back(EdepSD2);
	  }
	  vEvIDSD2xd4.pop_back(); vEdepSD2xd4.pop_back();
	  vEvIDSD2xd4.pop_back(); vEdepSD2xd4.pop_back();
			  
	  xfSciD2d4.close();
	  allvEvIDSD2xd4.push_back(vEvIDSD2xd4);
	  allvEdepSD2xd4.push_back(vEdepSD2xd4);


	  // SciD3
	  std::ifstream xfSciD3d4(TString(Xfiles[(k*50)+32]));
	  std::vector<double> vEvIDSD3xd4;
	  std::vector<double> vEdepSD3xd4;
			  
	  while (!xfSciD3d4.eof()) {
	     double EvIDSD3, EdepSD3;
		 xfSciD3d4 >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3xd4.push_back(EvIDSD3);
		 vEdepSD3xd4.push_back(EdepSD3);
	  }
	  vEvIDSD3xd4.pop_back(); vEdepSD3xd4.pop_back();
	  vEvIDSD3xd4.pop_back(); vEdepSD3xd4.pop_back();
			  
	  xfSciD3d4.close();
	  allvEvIDSD3xd4.push_back(vEvIDSD3xd4);
	  allvEdepSD3xd4.push_back(vEdepSD3xd4);
			  
			  
	  // BGOD1
	  std::ifstream xfBGOD1d4(TString(Xfiles[(k*50)+33]));
	  std::vector<double> vEvIDBD1xd4;
	  std::vector<double> vEdepBD1xd4;
			  
	  while (!xfBGOD1d4.eof()) {
	     double EvIDBD1, EdepBD1;
		 xfBGOD1d4 >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1xd4.push_back(EvIDBD1);
		 vEdepBD1xd4.push_back(EdepBD1);
	  }
	  vEvIDBD1xd4.pop_back(); vEdepBD1xd4.pop_back();
	  vEvIDBD1xd4.pop_back(); vEdepBD1xd4.pop_back();
			  
	  xfBGOD1d4.close();
	  allvEvIDBD1xd4.push_back(vEvIDBD1xd4);
	  allvEdepBD1xd4.push_back(vEdepBD1xd4);


	  // BGOD2
	  std::ifstream xfBGOD2d4(TString(Xfiles[(k*50)+34]));
	  std::vector<double> vEvIDBD2xd4;
	  std::vector<double> vEdepBD2xd4;
			  
	  while (!xfBGOD2d4.eof()) {
	     double EvIDBD2, EdepBD2;
		 xfBGOD2d4 >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2xd4.push_back(EvIDBD2);
		 vEdepBD2xd4.push_back(EdepBD2);
	  }
	  vEvIDBD2xd4.pop_back(); vEdepBD2xd4.pop_back();
	  vEvIDBD2xd4.pop_back(); vEdepBD2xd4.pop_back();
			  
	  xfBGOD2d4.close();
	  allvEvIDBD2xd4.push_back(vEvIDBD2xd4);
	  allvEdepBD2xd4.push_back(vEdepBD2xd4);


      // SciD1
	  std::ifstream x2fSciD1d4(TString(Xfiles[(k*50)+35]));
	  std::vector<double> vEvIDSD1x2d4;
	  std::vector<double> vEdepSD1x2d4;
			  
	  while (!x2fSciD1d4.eof()) {
	     double EvIDSD1, EdepSD1;
		 x2fSciD1d4 >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1x2d4.push_back(EvIDSD1);
		 vEdepSD1x2d4.push_back(EdepSD1);
	  }
	  vEvIDSD1x2d4.pop_back(); vEdepSD1x2d4.pop_back();
	  vEvIDSD1x2d4.pop_back(); vEdepSD1x2d4.pop_back();
			  
	  x2fSciD1d4.close();
	  allvEvIDSD1x2d4.push_back(vEvIDSD1x2d4);
	  allvEdepSD1x2d4.push_back(vEdepSD1x2d4);


	  // SciD2
	  std::ifstream x2fSciD2d4(TString(Xfiles[(k*50)+36]));
	  std::vector<double> vEvIDSD2x2d4;
	  std::vector<double> vEdepSD2x2d4;
			  
	  while (!x2fSciD2d4.eof()) {
	     double EvIDSD2, EdepSD2;
		 x2fSciD2d4 >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2x2d4.push_back(EvIDSD2);
		 vEdepSD2x2d4.push_back(EdepSD2);
	  }
	  vEvIDSD2x2d4.pop_back(); vEdepSD2x2d4.pop_back();
	  vEvIDSD2x2d4.pop_back(); vEdepSD2x2d4.pop_back();
			  
	  x2fSciD2d4.close();
	  allvEvIDSD2x2d4.push_back(vEvIDSD2x2d4);
	  allvEdepSD2x2d4.push_back(vEdepSD2x2d4);


	  // SciD3
	  std::ifstream x2fSciD3d4(TString(Xfiles[(k*50)+37]));
	  std::vector<double> vEvIDSD3x2d4;
	  std::vector<double> vEdepSD3x2d4;
			  
	  while (!x2fSciD3d4.eof()) {
	     double EvIDSD3, EdepSD3;
		 x2fSciD3d4 >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3x2d4.push_back(EvIDSD3);
		 vEdepSD3x2d4.push_back(EdepSD3);
	  }
	  vEvIDSD3x2d4.pop_back(); vEdepSD3x2d4.pop_back();
	  vEvIDSD3x2d4.pop_back(); vEdepSD3x2d4.pop_back();
			  
	  x2fSciD3d4.close();
	  allvEvIDSD3x2d4.push_back(vEvIDSD3x2d4);
	  allvEdepSD3x2d4.push_back(vEdepSD3x2d4);
			  
			  
	  // BGOD1
	  std::ifstream x2fBGOD1d4(TString(Xfiles[(k*50)+38]));
	  std::vector<double> vEvIDBD1x2d4;
	  std::vector<double> vEdepBD1x2d4;
			  
	  while (!x2fBGOD1d4.eof()) {
	     double EvIDBD1, EdepBD1;
		 x2fBGOD1d4 >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1x2d4.push_back(EvIDBD1);
		 vEdepBD1x2d4.push_back(EdepBD1);
	  }
	  vEvIDBD1x2d4.pop_back(); vEdepBD1x2d4.pop_back();
	  vEvIDBD1x2d4.pop_back(); vEdepBD1x2d4.pop_back();
			  
	  x2fBGOD1d4.close();
	  allvEvIDBD1x2d4.push_back(vEvIDBD1x2d4);
	  allvEdepBD1x2d4.push_back(vEdepBD1x2d4);


	  // BGOD2
	  std::ifstream x2fBGOD2d4(TString(Xfiles[(k*50)+39]));
	  std::vector<double> vEvIDBD2x2d4;
	  std::vector<double> vEdepBD2x2d4;
			  
	  while (!x2fBGOD2d4.eof()) {
	     double EvIDBD2, EdepBD2;
		 x2fBGOD2d4 >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2x2d4.push_back(EvIDBD2);
		 vEdepBD2x2d4.push_back(EdepBD2);
	  }
	  vEvIDBD2x2d4.pop_back(); vEdepBD2x2d4.pop_back();
	  vEvIDBD2x2d4.pop_back(); vEdepBD2x2d4.pop_back();
			  
	  x2fBGOD2d4.close();
	  allvEvIDBD2x2d4.push_back(vEvIDBD2x2d4);
	  allvEdepBD2x2d4.push_back(vEdepBD2x2d4);


      // SciD1 dA1 = 500 mm
	  std::ifstream xfSciD1d5(TString(Xfiles[(k*50)+40]));
	  std::vector<double> vEvIDSD1xd5;
	  std::vector<double> vEdepSD1xd5;
			  
	  while (!xfSciD1d5.eof()) {
	     double EvIDSD1, EdepSD1;
		 xfSciD1d5 >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1xd5.push_back(EvIDSD1);
		 vEdepSD1xd5.push_back(EdepSD1);
	  }
	  vEvIDSD1xd5.pop_back(); vEdepSD1xd5.pop_back();
	  vEvIDSD1xd5.pop_back(); vEdepSD1xd5.pop_back();
			  
	  xfSciD1d5.close();
	  allvEvIDSD1xd5.push_back(vEvIDSD1xd5);
	  allvEdepSD1xd5.push_back(vEdepSD1xd5);


	  // SciD2
	  std::ifstream xfSciD2d5(TString(Xfiles[(k*50)+41]));
	  std::vector<double> vEvIDSD2xd5;
	  std::vector<double> vEdepSD2xd5;
			  
	  while (!xfSciD2d5.eof()) {
	     double EvIDSD2, EdepSD2;
		 xfSciD2d5 >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2xd5.push_back(EvIDSD2);
		 vEdepSD2xd5.push_back(EdepSD2);
	  }
	  vEvIDSD2xd5.pop_back(); vEdepSD2xd5.pop_back();
	  vEvIDSD2xd5.pop_back(); vEdepSD2xd5.pop_back();
			  
	  xfSciD2d5.close();
	  allvEvIDSD2xd5.push_back(vEvIDSD2xd5);
	  allvEdepSD2xd5.push_back(vEdepSD2xd5);


	  // SciD3
	  std::ifstream xfSciD3d5(TString(Xfiles[(k*50)+42]));
	  std::vector<double> vEvIDSD3xd5;
	  std::vector<double> vEdepSD3xd5;
			  
	  while (!xfSciD3d5.eof()) {
	     double EvIDSD3, EdepSD3;
		 xfSciD3d5 >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3xd5.push_back(EvIDSD3);
		 vEdepSD3xd5.push_back(EdepSD3);
	  }
	  vEvIDSD3xd5.pop_back(); vEdepSD3xd5.pop_back();
	  vEvIDSD3xd5.pop_back(); vEdepSD3xd5.pop_back();
			  
	  xfSciD3d5.close();
	  allvEvIDSD3xd5.push_back(vEvIDSD3xd5);
	  allvEdepSD3xd5.push_back(vEdepSD3xd5);
			  
			  
	  // BGOD1
	  std::ifstream xfBGOD1d5(TString(Xfiles[(k*50)+43]));
	  std::vector<double> vEvIDBD1xd5;
	  std::vector<double> vEdepBD1xd5;
			  
	  while (!xfBGOD1d5.eof()) {
	     double EvIDBD1, EdepBD1;
		 xfBGOD1d5 >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1xd5.push_back(EvIDBD1);
		 vEdepBD1xd5.push_back(EdepBD1);
	  }
	  vEvIDBD1xd5.pop_back(); vEdepBD1xd5.pop_back();
	  vEvIDBD1xd5.pop_back(); vEdepBD1xd5.pop_back();
			  
	  xfBGOD1d5.close();
	  allvEvIDBD1xd5.push_back(vEvIDBD1xd5);
	  allvEdepBD1xd5.push_back(vEdepBD1xd5);


	  // BGOD2
	  std::ifstream xfBGOD2d5(TString(Xfiles[(k*50)+44]));
	  std::vector<double> vEvIDBD2xd5;
	  std::vector<double> vEdepBD2xd5;
			  
	  while (!xfBGOD2d5.eof()) {
	     double EvIDBD2, EdepBD2;
		 xfBGOD2d5 >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2xd5.push_back(EvIDBD2);
		 vEdepBD2xd5.push_back(EdepBD2);
	  }
	  vEvIDBD2xd5.pop_back(); vEdepBD2xd5.pop_back();
	  vEvIDBD2xd5.pop_back(); vEdepBD2xd5.pop_back();
			  
	  xfBGOD2d5.close();
	  allvEvIDBD2xd5.push_back(vEvIDBD2xd5);
	  allvEdepBD2xd5.push_back(vEdepBD2xd5);


      // SciD1
	  std::ifstream x2fSciD1d5(TString(Xfiles[(k*50)+45]));
	  std::vector<double> vEvIDSD1x2d5;
	  std::vector<double> vEdepSD1x2d5;
			  
	  while (!x2fSciD1d5.eof()) {
	     double EvIDSD1, EdepSD1;
		 x2fSciD1d5 >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1x2d5.push_back(EvIDSD1);
		 vEdepSD1x2d5.push_back(EdepSD1);
	  }
	  vEvIDSD1x2d5.pop_back(); vEdepSD1x2d5.pop_back();
	  vEvIDSD1x2d5.pop_back(); vEdepSD1x2d5.pop_back();
			  
	  x2fSciD1d5.close();
	  allvEvIDSD1x2d5.push_back(vEvIDSD1x2d5);
	  allvEdepSD1x2d5.push_back(vEdepSD1x2d5);


	  // SciD2
	  std::ifstream x2fSciD2d5(TString(Xfiles[(k*50)+46]));
	  std::vector<double> vEvIDSD2x2d5;
	  std::vector<double> vEdepSD2x2d5;
			  
	  while (!x2fSciD2d5.eof()) {
	     double EvIDSD2, EdepSD2;
		 x2fSciD2d5 >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2x2d5.push_back(EvIDSD2);
		 vEdepSD2x2d5.push_back(EdepSD2);
	  }
	  vEvIDSD2x2d5.pop_back(); vEdepSD2x2d5.pop_back();
	  vEvIDSD2x2d5.pop_back(); vEdepSD2x2d5.pop_back();
			  
	  x2fSciD2d5.close();
	  allvEvIDSD2x2d5.push_back(vEvIDSD2x2d5);
	  allvEdepSD2x2d5.push_back(vEdepSD2x2d5);


	  // SciD3
	  std::ifstream x2fSciD3d5(TString(Xfiles[(k*50)+47]));
	  std::vector<double> vEvIDSD3x2d5;
	  std::vector<double> vEdepSD3x2d5;
			  
	  while (!x2fSciD3d5.eof()) {
	     double EvIDSD3, EdepSD3;
		 x2fSciD3d5 >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3x2d5.push_back(EvIDSD3);
		 vEdepSD3x2d5.push_back(EdepSD3);
	  }
	  vEvIDSD3x2d5.pop_back(); vEdepSD3x2d5.pop_back();
	  vEvIDSD3x2d5.pop_back(); vEdepSD3x2d5.pop_back();
			  
	  x2fSciD3d5.close();
	  allvEvIDSD3x2d5.push_back(vEvIDSD3x2d5);
	  allvEdepSD3x2d5.push_back(vEdepSD3x2d5);
			  
			  
	  // BGOD1
	  std::ifstream x2fBGOD1d5(TString(Xfiles[(k*50)+48]));
	  std::vector<double> vEvIDBD1x2d5;
	  std::vector<double> vEdepBD1x2d5;
			  
	  while (!x2fBGOD1d5.eof()) {
	     double EvIDBD1, EdepBD1;
		 x2fBGOD1d5 >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1x2d5.push_back(EvIDBD1);
		 vEdepBD1x2d5.push_back(EdepBD1);
	  }
	  vEvIDBD1x2d5.pop_back(); vEdepBD1x2d5.pop_back();
	  vEvIDBD1x2d5.pop_back(); vEdepBD1x2d5.pop_back();
			  
	  x2fBGOD1d5.close();
	  allvEvIDBD1x2d5.push_back(vEvIDBD1x2d5);
	  allvEdepBD1x2d5.push_back(vEdepBD1x2d5);


	  // BGOD2
	  std::ifstream x2fBGOD2d5(TString(Xfiles[(k*50)+49]));
	  std::vector<double> vEvIDBD2x2d5;
	  std::vector<double> vEdepBD2x2d5;
			  
	  while (!x2fBGOD2d5.eof()) {
	     double EvIDBD2, EdepBD2;
		 x2fBGOD2d5 >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2x2d5.push_back(EvIDBD2);
		 vEdepBD2x2d5.push_back(EdepBD2);
	  }
	  vEvIDBD2x2d5.pop_back(); vEdepBD2x2d5.pop_back();
	  vEvIDBD2x2d5.pop_back(); vEdepBD2x2d5.pop_back();
			  
	  x2fBGOD2d5.close();
	  allvEvIDBD2x2d5.push_back(vEvIDBD2x2d5);
	  allvEdepBD2x2d5.push_back(vEdepBD2x2d5);

   }


   for (int k=0; k<((mufiles.size())/50); k++) {
   
      // SciD1mu dA1 = 300 mm
	  std::ifstream mufSciD1(TString(mufiles[k*50]));
	  std::vector<double> vEvIDSD1mu;
	  std::vector<double> vEdepSD1mu;
			  
	  while (!mufSciD1.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mufSciD1 >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1mu.push_back(EvIDSD1mu);
		 vEdepSD1mu.push_back(EdepSD1mu);
	  }
	  vEvIDSD1mu.pop_back(); vEdepSD1mu.pop_back();
	  vEvIDSD1mu.pop_back(); vEdepSD1mu.pop_back();
			  
	  mufSciD1.close();
	  allvEvIDSD1mu.push_back(vEvIDSD1mu);
	  allvEdepSD1mu.push_back(vEdepSD1mu);


	  // SciD2mu
	  std::ifstream mufSciD2(TString(mufiles[(k*50)+1]));
	  std::vector<double> vEvIDSD2mu;
	  std::vector<double> vEdepSD2mu;
			  
	  while (!mufSciD2.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mufSciD2 >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2mu.push_back(EvIDSD2mu);
		 vEdepSD2mu.push_back(EdepSD2mu);
	  }
	  vEvIDSD2mu.pop_back(); vEdepSD2mu.pop_back();
	  vEvIDSD2mu.pop_back(); vEdepSD2mu.pop_back();
			  
	  mufSciD2.close();
	  allvEvIDSD2mu.push_back(vEvIDSD2mu);
	  allvEdepSD2mu.push_back(vEdepSD2mu);


	  // SciD3mu
	  std::ifstream mufSciD3(TString(mufiles[(k*50)+2]));
	  std::vector<double> vEvIDSD3mu;
	  std::vector<double> vEdepSD3mu;
			  
	  while (!mufSciD3.eof()) {
	     double EvIDSD3mu, EdepSD3mu;
		 mufSciD3 >> EvIDSD3mu >> EdepSD3mu;
		 vEvIDSD3mu.push_back(EvIDSD3mu);
		 vEdepSD3mu.push_back(EdepSD3mu);
	  }
	  vEvIDSD3mu.pop_back(); vEdepSD3mu.pop_back();
	  vEvIDSD3mu.pop_back(); vEdepSD3mu.pop_back();
			  
	  mufSciD3.close();
	  allvEvIDSD3mu.push_back(vEvIDSD3mu);
	  allvEdepSD3mu.push_back(vEdepSD3mu);
			  

	  // BGOD1mu
	  std::ifstream mufBGOD1(TString(mufiles[(k*50)+3]));
	  std::vector<double> vEvIDBD1mu;
	  std::vector<double> vEdepBD1mu;
			  
	  while (!mufBGOD1.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mufBGOD1 >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1mu.push_back(EvIDBD1mu);
		 vEdepBD1mu.push_back(EdepBD1mu);
	  }
	  vEvIDBD1mu.pop_back(); vEdepBD1mu.pop_back();
	  vEvIDBD1mu.pop_back(); vEdepBD1mu.pop_back();
			  
	  mufBGOD1.close();
	  allvEvIDBD1mu.push_back(vEvIDBD1mu);
	  allvEdepBD1mu.push_back(vEdepBD1mu);


	  // BGOD2mu
	  std::ifstream mufBGOD2(TString(mufiles[(k*50)+4]));
	  std::vector<double> vEvIDBD2mu;
	  std::vector<double> vEdepBD2mu;
			  
	  while (!mufBGOD2.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mufBGOD2 >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2mu.push_back(EvIDBD2mu);
		 vEdepBD2mu.push_back(EdepBD2mu);
	  }
	  vEvIDBD2mu.pop_back(); vEdepBD2mu.pop_back();
	  vEvIDBD2mu.pop_back(); vEdepBD2mu.pop_back();
			  
	  mufBGOD2.close();
	  allvEvIDBD2mu.push_back(vEvIDBD2mu);
	  allvEdepBD2mu.push_back(vEdepBD2mu);


      // SciD1mu2
	  std::ifstream mu2fSciD1(TString(mufiles[(k*50)+5]));
	  std::vector<double> vEvIDSD1mu2;
	  std::vector<double> vEdepSD1mu2;
			  
	  while (!mu2fSciD1.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mu2fSciD1 >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1mu2.push_back(EvIDSD1mu);
		 vEdepSD1mu2.push_back(EdepSD1mu);
	  }
	  vEvIDSD1mu2.pop_back(); vEdepSD1mu2.pop_back();
	  vEvIDSD1mu2.pop_back(); vEdepSD1mu2.pop_back();
			  
	  mu2fSciD1.close();
	  allvEvIDSD1mu2.push_back(vEvIDSD1mu2);
	  allvEdepSD1mu2.push_back(vEdepSD1mu2);


	  // SciD2mu
	  std::ifstream mu2fSciD2(TString(mufiles[(k*50)+6]));
	  std::vector<double> vEvIDSD2mu2;
	  std::vector<double> vEdepSD2mu2;
			  
	  while (!mu2fSciD2.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mu2fSciD2 >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2mu2.push_back(EvIDSD2mu);
		 vEdepSD2mu2.push_back(EdepSD2mu);
	  }
	  vEvIDSD2mu2.pop_back(); vEdepSD2mu2.pop_back();
	  vEvIDSD2mu2.pop_back(); vEdepSD2mu2.pop_back();
			  
	  mu2fSciD2.close();
	  allvEvIDSD2mu2.push_back(vEvIDSD2mu2);
	  allvEdepSD2mu2.push_back(vEdepSD2mu2);


	  // SciD3mu
	  std::ifstream mu2fSciD3(TString(mufiles[(k*50)+7]));
	  std::vector<double> vEvIDSD3mu2;
	  std::vector<double> vEdepSD3mu2;
			  
	  while (!mu2fSciD3.eof()) {
	     double EvIDSD3mu, EdepSD3mu;
		 mu2fSciD3 >> EvIDSD3mu >> EdepSD3mu;
		 vEvIDSD3mu2.push_back(EvIDSD3mu);
		 vEdepSD3mu2.push_back(EdepSD3mu);
	  }
	  vEvIDSD3mu2.pop_back(); vEdepSD3mu2.pop_back();
	  vEvIDSD3mu2.pop_back(); vEdepSD3mu2.pop_back();
			  
	  mu2fSciD3.close();
	  allvEvIDSD3mu2.push_back(vEvIDSD3mu2);
	  allvEdepSD3mu2.push_back(vEdepSD3mu2);
			  
			  
	  // BGOD1mu
	  std::ifstream mu2fBGOD1(TString(mufiles[(k*50)+8]));
	  std::vector<double> vEvIDBD1mu2;
	  std::vector<double> vEdepBD1mu2;
			  
	  while (!mu2fBGOD1.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mu2fBGOD1 >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1mu2.push_back(EvIDBD1mu);
		 vEdepBD1mu2.push_back(EdepBD1mu);
	  }
	  vEvIDBD1mu2.pop_back(); vEdepBD1mu2.pop_back();
	  vEvIDBD1mu2.pop_back(); vEdepBD1mu2.pop_back();
			  
	  mu2fBGOD1.close();
	  allvEvIDBD1mu2.push_back(vEvIDBD1mu2);
	  allvEdepBD1mu2.push_back(vEdepBD1mu2);


	  // BGOD2mu
	  std::ifstream mu2fBGOD2(TString(mufiles[(k*50)+9]));
	  std::vector<double> vEvIDBD2mu2;
	  std::vector<double> vEdepBD2mu2;
			  
	  while (!mu2fBGOD2.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mu2fBGOD2 >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2mu2.push_back(EvIDBD2mu);
		 vEdepBD2mu2.push_back(EdepBD2mu);
	  }
	  vEvIDBD2mu2.pop_back(); vEdepBD2mu2.pop_back();
	  vEvIDBD2mu2.pop_back(); vEdepBD2mu2.pop_back();
			  
	  mu2fBGOD2.close();
	  allvEvIDBD2mu2.push_back(vEvIDBD2mu2);
	  allvEdepBD2mu2.push_back(vEdepBD2mu2);


      // SciD1mu dA1 = 350 mm
	  std::ifstream mufSciD1d2(TString(mufiles[(k*50)+10]));
	  std::vector<double> vEvIDSD1mud2;
	  std::vector<double> vEdepSD1mud2;
			  
	  while (!mufSciD1d2.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mufSciD1d2 >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1mud2.push_back(EvIDSD1mu);
		 vEdepSD1mud2.push_back(EdepSD1mu);
	  }
	  vEvIDSD1mud2.pop_back(); vEdepSD1mud2.pop_back();
	  vEvIDSD1mud2.pop_back(); vEdepSD1mud2.pop_back();
			  
	  mufSciD1d2.close();
	  allvEvIDSD1mud2.push_back(vEvIDSD1mud2);
	  allvEdepSD1mud2.push_back(vEdepSD1mud2);


	  // SciD2mu
	  std::ifstream mufSciD2d2(TString(mufiles[(k*50)+11]));
	  std::vector<double> vEvIDSD2mud2;
	  std::vector<double> vEdepSD2mud2;
			  
	  while (!mufSciD2d2.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mufSciD2d2 >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2mud2.push_back(EvIDSD2mu);
		 vEdepSD2mud2.push_back(EdepSD2mu);
	  }
	  vEvIDSD2mud2.pop_back(); vEdepSD2mud2.pop_back();
	  vEvIDSD2mud2.pop_back(); vEdepSD2mud2.pop_back();
			  
	  mufSciD2d2.close();
	  allvEvIDSD2mud2.push_back(vEvIDSD2mud2);
	  allvEdepSD2mud2.push_back(vEdepSD2mud2);


	  // SciD3mu
	  std::ifstream mufSciD3d2(TString(mufiles[(k*50)+12]));
	  std::vector<double> vEvIDSD3mud2;
	  std::vector<double> vEdepSD3mud2;
			  
	  while (!mufSciD3d2.eof()) {
	     double EvIDSD3mu, EdepSD3mu;
		 mufSciD3d2 >> EvIDSD3mu >> EdepSD3mu;
		 vEvIDSD3mud2.push_back(EvIDSD3mu);
		 vEdepSD3mud2.push_back(EdepSD3mu);
	  }
	  vEvIDSD3mud2.pop_back(); vEdepSD3mud2.pop_back();
	  vEvIDSD3mud2.pop_back(); vEdepSD3mud2.pop_back();
			  
	  mufSciD3d2.close();
	  allvEvIDSD3mud2.push_back(vEvIDSD3mud2);
	  allvEdepSD3mud2.push_back(vEdepSD3mud2);
			  

	  // BGOD1mu
	  std::ifstream mufBGOD1d2(TString(mufiles[(k*50)+13]));
	  std::vector<double> vEvIDBD1mud2;
	  std::vector<double> vEdepBD1mud2;
			  
	  while (!mufBGOD1d2.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mufBGOD1d2 >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1mud2.push_back(EvIDBD1mu);
		 vEdepBD1mud2.push_back(EdepBD1mu);
	  }
	  vEvIDBD1mud2.pop_back(); vEdepBD1mud2.pop_back();
	  vEvIDBD1mud2.pop_back(); vEdepBD1mud2.pop_back();
			  
	  mufBGOD1d2.close();
	  allvEvIDBD1mud2.push_back(vEvIDBD1mud2);
	  allvEdepBD1mud2.push_back(vEdepBD1mud2);


	  // BGOD2mu
	  std::ifstream mufBGOD2d2(TString(mufiles[(k*50)+14]));
	  std::vector<double> vEvIDBD2mud2;
	  std::vector<double> vEdepBD2mud2;
			  
	  while (!mufBGOD2d2.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mufBGOD2d2 >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2mud2.push_back(EvIDBD2mu);
		 vEdepBD2mud2.push_back(EdepBD2mu);
	  }
	  vEvIDBD2mud2.pop_back(); vEdepBD2mud2.pop_back();
	  vEvIDBD2mud2.pop_back(); vEdepBD2mud2.pop_back();
			  
	  mufBGOD2d2.close();
	  allvEvIDBD2mud2.push_back(vEvIDBD2mud2);
	  allvEdepBD2mud2.push_back(vEdepBD2mud2);


      // SciD1mu2
	  std::ifstream mu2fSciD1d2(TString(mufiles[(k*50)+15]));
	  std::vector<double> vEvIDSD1mu2d2;
	  std::vector<double> vEdepSD1mu2d2;
			  
	  while (!mu2fSciD1d2.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mu2fSciD1d2 >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1mu2d2.push_back(EvIDSD1mu);
		 vEdepSD1mu2d2.push_back(EdepSD1mu);
	  }
	  vEvIDSD1mu2d2.pop_back(); vEdepSD1mu2d2.pop_back();
	  vEvIDSD1mu2d2.pop_back(); vEdepSD1mu2d2.pop_back();
			  
	  mu2fSciD1d2.close();
	  allvEvIDSD1mu2d2.push_back(vEvIDSD1mu2d2);
	  allvEdepSD1mu2d2.push_back(vEdepSD1mu2d2);


	  // SciD2mu
	  std::ifstream mu2fSciD2d2(TString(mufiles[(k*50)+16]));
	  std::vector<double> vEvIDSD2mu2d2;
	  std::vector<double> vEdepSD2mu2d2;
			  
	  while (!mu2fSciD2d2.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mu2fSciD2d2 >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2mu2d2.push_back(EvIDSD2mu);
		 vEdepSD2mu2d2.push_back(EdepSD2mu);
	  }
	  vEvIDSD2mu2d2.pop_back(); vEdepSD2mu2d2.pop_back();
	  vEvIDSD2mu2d2.pop_back(); vEdepSD2mu2d2.pop_back();
			  
	  mu2fSciD2d2.close();
	  allvEvIDSD2mu2d2.push_back(vEvIDSD2mu2d2);
	  allvEdepSD2mu2d2.push_back(vEdepSD2mu2d2);


	  // SciD3mu
	  std::ifstream mu2fSciD3d2(TString(mufiles[(k*50)+17]));
	  std::vector<double> vEvIDSD3mu2d2;
	  std::vector<double> vEdepSD3mu2d2;
			  
	  while (!mu2fSciD3d2.eof()) {
	     double EvIDSD3mu, EdepSD3mu;
		 mu2fSciD3d2 >> EvIDSD3mu >> EdepSD3mu;
		 vEvIDSD3mu2d2.push_back(EvIDSD3mu);
		 vEdepSD3mu2d2.push_back(EdepSD3mu);
	  }
	  vEvIDSD3mu2d2.pop_back(); vEdepSD3mu2d2.pop_back();
	  vEvIDSD3mu2d2.pop_back(); vEdepSD3mu2d2.pop_back();
			  
	  mu2fSciD3d2.close();
	  allvEvIDSD3mu2d2.push_back(vEvIDSD3mu2d2);
	  allvEdepSD3mu2d2.push_back(vEdepSD3mu2d2);
			  
			  
	  // BGOD1mu
	  std::ifstream mu2fBGOD1d2(TString(mufiles[(k*50)+18]));
	  std::vector<double> vEvIDBD1mu2d2;
	  std::vector<double> vEdepBD1mu2d2;
			  
	  while (!mu2fBGOD1d2.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mu2fBGOD1d2 >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1mu2d2.push_back(EvIDBD1mu);
		 vEdepBD1mu2d2.push_back(EdepBD1mu);
	  }
	  vEvIDBD1mu2d2.pop_back(); vEdepBD1mu2d2.pop_back();
	  vEvIDBD1mu2d2.pop_back(); vEdepBD1mu2d2.pop_back();
			  
	  mu2fBGOD1d2.close();
	  allvEvIDBD1mu2d2.push_back(vEvIDBD1mu2d2);
	  allvEdepBD1mu2d2.push_back(vEdepBD1mu2d2);


	  // BGOD2mu
	  std::ifstream mu2fBGOD2d2(TString(mufiles[(k*50)+19]));
	  std::vector<double> vEvIDBD2mu2d2;
	  std::vector<double> vEdepBD2mu2d2;
			  
	  while (!mu2fBGOD2d2.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mu2fBGOD2d2 >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2mu2d2.push_back(EvIDBD2mu);
		 vEdepBD2mu2d2.push_back(EdepBD2mu);
	  }
	  vEvIDBD2mu2d2.pop_back(); vEdepBD2mu2d2.pop_back();
	  vEvIDBD2mu2d2.pop_back(); vEdepBD2mu2d2.pop_back();
			  
	  mu2fBGOD2d2.close();
	  allvEvIDBD2mu2d2.push_back(vEvIDBD2mu2d2);
	  allvEdepBD2mu2d2.push_back(vEdepBD2mu2d2);


      // SciD1mu dA1 = 400 mm
	  std::ifstream mufSciD1d3(TString(mufiles[(k*50)+20]));
	  std::vector<double> vEvIDSD1mud3;
	  std::vector<double> vEdepSD1mud3;
			  
	  while (!mufSciD1d3.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mufSciD1d3 >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1mud3.push_back(EvIDSD1mu);
		 vEdepSD1mud3.push_back(EdepSD1mu);
	  }
	  vEvIDSD1mud3.pop_back(); vEdepSD1mud3.pop_back();
	  vEvIDSD1mud3.pop_back(); vEdepSD1mud3.pop_back();
			  
	  mufSciD1d3.close();
	  allvEvIDSD1mud3.push_back(vEvIDSD1mud3);
	  allvEdepSD1mud3.push_back(vEdepSD1mud3);


	  // SciD2mu
	  std::ifstream mufSciD2d3(TString(mufiles[(k*50)+21]));
	  std::vector<double> vEvIDSD2mud3;
	  std::vector<double> vEdepSD2mud3;
			  
	  while (!mufSciD2d3.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mufSciD2d3 >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2mud3.push_back(EvIDSD2mu);
		 vEdepSD2mud3.push_back(EdepSD2mu);
	  }
	  vEvIDSD2mud3.pop_back(); vEdepSD2mud3.pop_back();
	  vEvIDSD2mud3.pop_back(); vEdepSD2mud3.pop_back();
			  
	  mufSciD2d3.close();
	  allvEvIDSD2mud3.push_back(vEvIDSD2mud3);
	  allvEdepSD2mud3.push_back(vEdepSD2mud3);


	  // SciD3mu
	  std::ifstream mufSciD3d3(TString(mufiles[(k*50)+22]));
	  std::vector<double> vEvIDSD3mud3;
	  std::vector<double> vEdepSD3mud3;
			  
	  while (!mufSciD3d3.eof()) {
	     double EvIDSD3mu, EdepSD3mu;
		 mufSciD3d3 >> EvIDSD3mu >> EdepSD3mu;
		 vEvIDSD3mud3.push_back(EvIDSD3mu);
		 vEdepSD3mud3.push_back(EdepSD3mu);
	  }
	  vEvIDSD3mud3.pop_back(); vEdepSD3mud3.pop_back();
	  vEvIDSD3mud3.pop_back(); vEdepSD3mud3.pop_back();
			  
	  mufSciD3d3.close();
	  allvEvIDSD3mud3.push_back(vEvIDSD3mud3);
	  allvEdepSD3mud3.push_back(vEdepSD3mud3);
			  

	  // BGOD1mu
	  std::ifstream mufBGOD1d3(TString(mufiles[(k*50)+23]));
	  std::vector<double> vEvIDBD1mud3;
	  std::vector<double> vEdepBD1mud3;
			  
	  while (!mufBGOD1d3.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mufBGOD1d3 >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1mud3.push_back(EvIDBD1mu);
		 vEdepBD1mud3.push_back(EdepBD1mu);
	  }
	  vEvIDBD1mud3.pop_back(); vEdepBD1mud3.pop_back();
	  vEvIDBD1mud3.pop_back(); vEdepBD1mud3.pop_back();
			  
	  mufBGOD1d3.close();
	  allvEvIDBD1mud3.push_back(vEvIDBD1mud3);
	  allvEdepBD1mud3.push_back(vEdepBD1mud3);


	  // BGOD2mu
	  std::ifstream mufBGOD2d3(TString(mufiles[(k*50)+24]));
	  std::vector<double> vEvIDBD2mud3;
	  std::vector<double> vEdepBD2mud3;
			  
	  while (!mufBGOD2d3.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mufBGOD2d3 >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2mud3.push_back(EvIDBD2mu);
		 vEdepBD2mud3.push_back(EdepBD2mu);
	  }
	  vEvIDBD2mud3.pop_back(); vEdepBD2mud3.pop_back();
	  vEvIDBD2mud3.pop_back(); vEdepBD2mud3.pop_back();
			  
	  mufBGOD2d3.close();
	  allvEvIDBD2mud3.push_back(vEvIDBD2mud3);
	  allvEdepBD2mud3.push_back(vEdepBD2mud3);


      // SciD1mu2
	  std::ifstream mu2fSciD1d3(TString(mufiles[(k*50)+25]));
	  std::vector<double> vEvIDSD1mu2d3;
	  std::vector<double> vEdepSD1mu2d3;
			  
	  while (!mu2fSciD1d3.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mu2fSciD1d3 >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1mu2d3.push_back(EvIDSD1mu);
		 vEdepSD1mu2d3.push_back(EdepSD1mu);
	  }
	  vEvIDSD1mu2d3.pop_back(); vEdepSD1mu2d3.pop_back();
	  vEvIDSD1mu2d3.pop_back(); vEdepSD1mu2d3.pop_back();
			  
	  mu2fSciD1d3.close();
	  allvEvIDSD1mu2d3.push_back(vEvIDSD1mu2d3);
	  allvEdepSD1mu2d3.push_back(vEdepSD1mu2d3);


	  // SciD2mu
	  std::ifstream mu2fSciD2d3(TString(mufiles[(k*50)+26]));
	  std::vector<double> vEvIDSD2mu2d3;
	  std::vector<double> vEdepSD2mu2d3;
			  
	  while (!mu2fSciD2d3.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mu2fSciD2d3 >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2mu2d3.push_back(EvIDSD2mu);
		 vEdepSD2mu2d3.push_back(EdepSD2mu);
	  }
	  vEvIDSD2mu2d3.pop_back(); vEdepSD2mu2d3.pop_back();
	  vEvIDSD2mu2d3.pop_back(); vEdepSD2mu2d3.pop_back();
			  
	  mu2fSciD2d3.close();
	  allvEvIDSD2mu2d3.push_back(vEvIDSD2mu2d3);
	  allvEdepSD2mu2d3.push_back(vEdepSD2mu2d3);


	  // SciD3mu
	  std::ifstream mu2fSciD3d3(TString(mufiles[(k*50)+27]));
	  std::vector<double> vEvIDSD3mu2d3;
	  std::vector<double> vEdepSD3mu2d3;
			  
	  while (!mu2fSciD3d3.eof()) {
	     double EvIDSD3mu, EdepSD3mu;
		 mu2fSciD3d3 >> EvIDSD3mu >> EdepSD3mu;
		 vEvIDSD3mu2d3.push_back(EvIDSD3mu);
		 vEdepSD3mu2d3.push_back(EdepSD3mu);
	  }
	  vEvIDSD3mu2d3.pop_back(); vEdepSD3mu2d3.pop_back();
	  vEvIDSD3mu2d3.pop_back(); vEdepSD3mu2d3.pop_back();
			  
	  mu2fSciD3d3.close();
	  allvEvIDSD3mu2d3.push_back(vEvIDSD3mu2d3);
	  allvEdepSD3mu2d3.push_back(vEdepSD3mu2d3);
			  
			  
	  // BGOD1mu
	  std::ifstream mu2fBGOD1d3(TString(mufiles[(k*50)+28]));
	  std::vector<double> vEvIDBD1mu2d3;
	  std::vector<double> vEdepBD1mu2d3;
			  
	  while (!mu2fBGOD1d3.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mu2fBGOD1d3 >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1mu2d3.push_back(EvIDBD1mu);
		 vEdepBD1mu2d3.push_back(EdepBD1mu);
	  }
	  vEvIDBD1mu2d3.pop_back(); vEdepBD1mu2d3.pop_back();
	  vEvIDBD1mu2d3.pop_back(); vEdepBD1mu2d3.pop_back();
			  
	  mu2fBGOD1d3.close();
	  allvEvIDBD1mu2d3.push_back(vEvIDBD1mu2d3);
	  allvEdepBD1mu2d3.push_back(vEdepBD1mu2d3);


	  // BGOD2mu
	  std::ifstream mu2fBGOD2d3(TString(mufiles[(k*50)+29]));
	  std::vector<double> vEvIDBD2mu2d3;
	  std::vector<double> vEdepBD2mu2d3;
			  
	  while (!mu2fBGOD2d3.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mu2fBGOD2d3 >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2mu2d3.push_back(EvIDBD2mu);
		 vEdepBD2mu2d3.push_back(EdepBD2mu);
	  }
	  vEvIDBD2mu2d3.pop_back(); vEdepBD2mu2d3.pop_back();
	  vEvIDBD2mu2d3.pop_back(); vEdepBD2mu2d3.pop_back();
			  
	  mu2fBGOD2d3.close();
	  allvEvIDBD2mu2d3.push_back(vEvIDBD2mu2d3);
	  allvEdepBD2mu2d3.push_back(vEdepBD2mu2d3);


      // SciD1mu dA1 = 450 mm
	  std::ifstream mufSciD1d4(TString(mufiles[(k*50)+30]));
	  std::vector<double> vEvIDSD1mud4;
	  std::vector<double> vEdepSD1mud4;
			  
	  while (!mufSciD1d4.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mufSciD1d4 >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1mud4.push_back(EvIDSD1mu);
		 vEdepSD1mud4.push_back(EdepSD1mu);
	  }
	  vEvIDSD1mud4.pop_back(); vEdepSD1mud4.pop_back();
	  vEvIDSD1mud4.pop_back(); vEdepSD1mud4.pop_back();
			  
	  mufSciD1d4.close();
	  allvEvIDSD1mud4.push_back(vEvIDSD1mud4);
	  allvEdepSD1mud4.push_back(vEdepSD1mud4);


	  // SciD2mu
	  std::ifstream mufSciD2d4(TString(mufiles[(k*50)+31]));
	  std::vector<double> vEvIDSD2mud4;
	  std::vector<double> vEdepSD2mud4;
			  
	  while (!mufSciD2d4.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mufSciD2d4 >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2mud4.push_back(EvIDSD2mu);
		 vEdepSD2mud4.push_back(EdepSD2mu);
	  }
	  vEvIDSD2mud4.pop_back(); vEdepSD2mud4.pop_back();
	  vEvIDSD2mud4.pop_back(); vEdepSD2mud4.pop_back();
			  
	  mufSciD2d4.close();
	  allvEvIDSD2mud4.push_back(vEvIDSD2mud4);
	  allvEdepSD2mud4.push_back(vEdepSD2mud4);


	  // SciD3mu
	  std::ifstream mufSciD3d4(TString(mufiles[(k*50)+32]));
	  std::vector<double> vEvIDSD3mud4;
	  std::vector<double> vEdepSD3mud4;
			  
	  while (!mufSciD3d4.eof()) {
	     double EvIDSD3mu, EdepSD3mu;
		 mufSciD3d4 >> EvIDSD3mu >> EdepSD3mu;
		 vEvIDSD3mud4.push_back(EvIDSD3mu);
		 vEdepSD3mud4.push_back(EdepSD3mu);
	  }
	  vEvIDSD3mud4.pop_back(); vEdepSD3mud4.pop_back();
	  vEvIDSD3mud4.pop_back(); vEdepSD3mud4.pop_back();
			  
	  mufSciD3d4.close();
	  allvEvIDSD3mud4.push_back(vEvIDSD3mud4);
	  allvEdepSD3mud4.push_back(vEdepSD3mud4);
			  

	  // BGOD1mu
	  std::ifstream mufBGOD1d4(TString(mufiles[(k*50)+33]));
	  std::vector<double> vEvIDBD1mud4;
	  std::vector<double> vEdepBD1mud4;
			  
	  while (!mufBGOD1d4.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mufBGOD1d4 >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1mud4.push_back(EvIDBD1mu);
		 vEdepBD1mud4.push_back(EdepBD1mu);
	  }
	  vEvIDBD1mud4.pop_back(); vEdepBD1mud4.pop_back();
	  vEvIDBD1mud4.pop_back(); vEdepBD1mud4.pop_back();
			  
	  mufBGOD1d4.close();
	  allvEvIDBD1mud4.push_back(vEvIDBD1mud4);
	  allvEdepBD1mud4.push_back(vEdepBD1mud4);


	  // BGOD2mu
	  std::ifstream mufBGOD2d4(TString(mufiles[(k*50)+34]));
	  std::vector<double> vEvIDBD2mud4;
	  std::vector<double> vEdepBD2mud4;
			  
	  while (!mufBGOD2d4.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mufBGOD2d4 >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2mud4.push_back(EvIDBD2mu);
		 vEdepBD2mud4.push_back(EdepBD2mu);
	  }
	  vEvIDBD2mud4.pop_back(); vEdepBD2mud4.pop_back();
	  vEvIDBD2mud4.pop_back(); vEdepBD2mud4.pop_back();
			  
	  mufBGOD2d4.close();
	  allvEvIDBD2mud4.push_back(vEvIDBD2mud4);
	  allvEdepBD2mud4.push_back(vEdepBD2mud4);


      // SciD1mu2
	  std::ifstream mu2fSciD1d4(TString(mufiles[(k*50)+35]));
	  std::vector<double> vEvIDSD1mu2d4;
	  std::vector<double> vEdepSD1mu2d4;
			  
	  while (!mu2fSciD1d4.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mu2fSciD1d4 >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1mu2d4.push_back(EvIDSD1mu);
		 vEdepSD1mu2d4.push_back(EdepSD1mu);
	  }
	  vEvIDSD1mu2d4.pop_back(); vEdepSD1mu2d4.pop_back();
	  vEvIDSD1mu2d4.pop_back(); vEdepSD1mu2d4.pop_back();
			  
	  mu2fSciD1d4.close();
	  allvEvIDSD1mu2d4.push_back(vEvIDSD1mu2d4);
	  allvEdepSD1mu2d4.push_back(vEdepSD1mu2d4);


	  // SciD2mu
	  std::ifstream mu2fSciD2d4(TString(mufiles[(k*50)+36]));
	  std::vector<double> vEvIDSD2mu2d4;
	  std::vector<double> vEdepSD2mu2d4;
			  
	  while (!mu2fSciD2d4.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mu2fSciD2d4 >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2mu2d4.push_back(EvIDSD2mu);
		 vEdepSD2mu2d4.push_back(EdepSD2mu);
	  }
	  vEvIDSD2mu2d4.pop_back(); vEdepSD2mu2d4.pop_back();
	  vEvIDSD2mu2d4.pop_back(); vEdepSD2mu2d4.pop_back();
			  
	  mu2fSciD2d4.close();
	  allvEvIDSD2mu2d4.push_back(vEvIDSD2mu2d4);
	  allvEdepSD2mu2d4.push_back(vEdepSD2mu2d4);


	  // SciD3mu
	  std::ifstream mu2fSciD3d4(TString(mufiles[(k*50)+37]));
	  std::vector<double> vEvIDSD3mu2d4;
	  std::vector<double> vEdepSD3mu2d4;
			  
	  while (!mu2fSciD3d4.eof()) {
	     double EvIDSD3mu, EdepSD3mu;
		 mu2fSciD3d4 >> EvIDSD3mu >> EdepSD3mu;
		 vEvIDSD3mu2d4.push_back(EvIDSD3mu);
		 vEdepSD3mu2d4.push_back(EdepSD3mu);
	  }
	  vEvIDSD3mu2d4.pop_back(); vEdepSD3mu2d4.pop_back();
	  vEvIDSD3mu2d4.pop_back(); vEdepSD3mu2d4.pop_back();
			  
	  mu2fSciD3d4.close();
	  allvEvIDSD3mu2d4.push_back(vEvIDSD3mu2d4);
	  allvEdepSD3mu2d4.push_back(vEdepSD3mu2d4);
			  
			  
	  // BGOD1mu
	  std::ifstream mu2fBGOD1d4(TString(mufiles[(k*50)+38]));
	  std::vector<double> vEvIDBD1mu2d4;
	  std::vector<double> vEdepBD1mu2d4;
			  
	  while (!mu2fBGOD1d4.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mu2fBGOD1d4 >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1mu2d4.push_back(EvIDBD1mu);
		 vEdepBD1mu2d4.push_back(EdepBD1mu);
	  }
	  vEvIDBD1mu2d4.pop_back(); vEdepBD1mu2d4.pop_back();
	  vEvIDBD1mu2d4.pop_back(); vEdepBD1mu2d4.pop_back();
			  
	  mu2fBGOD1d4.close();
	  allvEvIDBD1mu2d4.push_back(vEvIDBD1mu2d4);
	  allvEdepBD1mu2d4.push_back(vEdepBD1mu2d4);


	  // BGOD2mu
	  std::ifstream mu2fBGOD2d4(TString(mufiles[(k*50)+39]));
	  std::vector<double> vEvIDBD2mu2d4;
	  std::vector<double> vEdepBD2mu2d4;
			  
	  while (!mu2fBGOD2d4.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mu2fBGOD2d4 >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2mu2d4.push_back(EvIDBD2mu);
		 vEdepBD2mu2d4.push_back(EdepBD2mu);
	  }
	  vEvIDBD2mu2d4.pop_back(); vEdepBD2mu2d4.pop_back();
	  vEvIDBD2mu2d4.pop_back(); vEdepBD2mu2d4.pop_back();
			  
	  mu2fBGOD2d4.close();
	  allvEvIDBD2mu2d4.push_back(vEvIDBD2mu2d4);
	  allvEdepBD2mu2d4.push_back(vEdepBD2mu2d4);


      // SciD1mu dA1 = 500 mm
	  std::ifstream mufSciD1d5(TString(mufiles[(k*50)+40]));
	  std::vector<double> vEvIDSD1mud5;
	  std::vector<double> vEdepSD1mud5;
			  
	  while (!mufSciD1d5.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mufSciD1d5 >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1mud5.push_back(EvIDSD1mu);
		 vEdepSD1mud5.push_back(EdepSD1mu);
	  }
	  vEvIDSD1mud5.pop_back(); vEdepSD1mud5.pop_back();
	  vEvIDSD1mud5.pop_back(); vEdepSD1mud5.pop_back();
			  
	  mufSciD1d5.close();
	  allvEvIDSD1mud5.push_back(vEvIDSD1mud5);
	  allvEdepSD1mud5.push_back(vEdepSD1mud5);


	  // SciD2mu
	  std::ifstream mufSciD2d5(TString(mufiles[(k*50)+41]));
	  std::vector<double> vEvIDSD2mud5;
	  std::vector<double> vEdepSD2mud5;
			  
	  while (!mufSciD2d5.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mufSciD2d5 >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2mud5.push_back(EvIDSD2mu);
		 vEdepSD2mud5.push_back(EdepSD2mu);
	  }
	  vEvIDSD2mud5.pop_back(); vEdepSD2mud5.pop_back();
	  vEvIDSD2mud5.pop_back(); vEdepSD2mud5.pop_back();
			  
	  mufSciD2d5.close();
	  allvEvIDSD2mud5.push_back(vEvIDSD2mud5);
	  allvEdepSD2mud5.push_back(vEdepSD2mud5);


	  // SciD3mu
	  std::ifstream mufSciD3d5(TString(mufiles[(k*50)+42]));
	  std::vector<double> vEvIDSD3mud5;
	  std::vector<double> vEdepSD3mud5;
			  
	  while (!mufSciD3d5.eof()) {
	     double EvIDSD3mu, EdepSD3mu;
		 mufSciD3d5 >> EvIDSD3mu >> EdepSD3mu;
		 vEvIDSD3mud5.push_back(EvIDSD3mu);
		 vEdepSD3mud5.push_back(EdepSD3mu);
	  }
	  vEvIDSD3mud5.pop_back(); vEdepSD3mud5.pop_back();
	  vEvIDSD3mud5.pop_back(); vEdepSD3mud5.pop_back();
			  
	  mufSciD3d5.close();
	  allvEvIDSD3mud5.push_back(vEvIDSD3mud5);
	  allvEdepSD3mud5.push_back(vEdepSD3mud5);
			  

	  // BGOD1mu
	  std::ifstream mufBGOD1d5(TString(mufiles[(k*50)+43]));
	  std::vector<double> vEvIDBD1mud5;
	  std::vector<double> vEdepBD1mud5;
			  
	  while (!mufBGOD1d5.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mufBGOD1d5 >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1mud5.push_back(EvIDBD1mu);
		 vEdepBD1mud5.push_back(EdepBD1mu);
	  }
	  vEvIDBD1mud5.pop_back(); vEdepBD1mud5.pop_back();
	  vEvIDBD1mud5.pop_back(); vEdepBD1mud5.pop_back();
			  
	  mufBGOD1d5.close();
	  allvEvIDBD1mud5.push_back(vEvIDBD1mud5);
	  allvEdepBD1mud5.push_back(vEdepBD1mud5);


	  // BGOD2mu
	  std::ifstream mufBGOD2d5(TString(mufiles[(k*50)+44]));
	  std::vector<double> vEvIDBD2mud5;
	  std::vector<double> vEdepBD2mud5;
			  
	  while (!mufBGOD2d5.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mufBGOD2d5 >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2mud5.push_back(EvIDBD2mu);
		 vEdepBD2mud5.push_back(EdepBD2mu);
	  }
	  vEvIDBD2mud5.pop_back(); vEdepBD2mud5.pop_back();
	  vEvIDBD2mud5.pop_back(); vEdepBD2mud5.pop_back();
			  
	  mufBGOD2d5.close();
	  allvEvIDBD2mud5.push_back(vEvIDBD2mud5);
	  allvEdepBD2mud5.push_back(vEdepBD2mud5);


      // SciD1mu2
	  std::ifstream mu2fSciD1d5(TString(mufiles[(k*50)+45]));
	  std::vector<double> vEvIDSD1mu2d5;
	  std::vector<double> vEdepSD1mu2d5;
			  
	  while (!mu2fSciD1d5.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mu2fSciD1d5 >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1mu2d5.push_back(EvIDSD1mu);
		 vEdepSD1mu2d5.push_back(EdepSD1mu);
	  }
	  vEvIDSD1mu2d5.pop_back(); vEdepSD1mu2d5.pop_back();
	  vEvIDSD1mu2d5.pop_back(); vEdepSD1mu2d5.pop_back();
			  
	  mu2fSciD1d5.close();
	  allvEvIDSD1mu2d5.push_back(vEvIDSD1mu2d5);
	  allvEdepSD1mu2d5.push_back(vEdepSD1mu2d5);


	  // SciD2mu
	  std::ifstream mu2fSciD2d5(TString(mufiles[(k*50)+46]));
	  std::vector<double> vEvIDSD2mu2d5;
	  std::vector<double> vEdepSD2mu2d5;
			  
	  while (!mu2fSciD2d5.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mu2fSciD2d5 >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2mu2d5.push_back(EvIDSD2mu);
		 vEdepSD2mu2d5.push_back(EdepSD2mu);
	  }
	  vEvIDSD2mu2d5.pop_back(); vEdepSD2mu2d5.pop_back();
	  vEvIDSD2mu2d5.pop_back(); vEdepSD2mu2d5.pop_back();
			  
	  mu2fSciD2d5.close();
	  allvEvIDSD2mu2d5.push_back(vEvIDSD2mu2d5);
	  allvEdepSD2mu2d5.push_back(vEdepSD2mu2d5);


	  // SciD3mu
	  std::ifstream mu2fSciD3d5(TString(mufiles[(k*50)+47]));
	  std::vector<double> vEvIDSD3mu2d5;
	  std::vector<double> vEdepSD3mu2d5;
			  
	  while (!mu2fSciD3d5.eof()) {
	     double EvIDSD3mu, EdepSD3mu;
		 mu2fSciD3d5 >> EvIDSD3mu >> EdepSD3mu;
		 vEvIDSD3mu2d5.push_back(EvIDSD3mu);
		 vEdepSD3mu2d5.push_back(EdepSD3mu);
	  }
	  vEvIDSD3mu2d5.pop_back(); vEdepSD3mu2d5.pop_back();
	  vEvIDSD3mu2d5.pop_back(); vEdepSD3mu2d5.pop_back();
			  
	  mu2fSciD3d5.close();
	  allvEvIDSD3mu2d5.push_back(vEvIDSD3mu2d5);
	  allvEdepSD3mu2d5.push_back(vEdepSD3mu2d5);
			  
			  
	  // BGOD1mu
	  std::ifstream mu2fBGOD1d5(TString(mufiles[(k*50)+48]));
	  std::vector<double> vEvIDBD1mu2d5;
	  std::vector<double> vEdepBD1mu2d5;
			  
	  while (!mu2fBGOD1d5.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mu2fBGOD1d5 >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1mu2d5.push_back(EvIDBD1mu);
		 vEdepBD1mu2d5.push_back(EdepBD1mu);
	  }
	  vEvIDBD1mu2d5.pop_back(); vEdepBD1mu2d5.pop_back();
	  vEvIDBD1mu2d5.pop_back(); vEdepBD1mu2d5.pop_back();
			  
	  mu2fBGOD1d5.close();
	  allvEvIDBD1mu2d5.push_back(vEvIDBD1mu2d5);
	  allvEdepBD1mu2d5.push_back(vEdepBD1mu2d5);


	  // BGOD2mu
	  std::ifstream mu2fBGOD2d5(TString(mufiles[(k*50)+49]));
	  std::vector<double> vEvIDBD2mu2d5;
	  std::vector<double> vEdepBD2mu2d5;
			  
	  while (!mu2fBGOD2d5.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mu2fBGOD2d5 >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2mu2d5.push_back(EvIDBD2mu);
		 vEdepBD2mu2d5.push_back(EdepBD2mu);
	  }
	  vEvIDBD2mu2d5.pop_back(); vEdepBD2mu2d5.pop_back();
	  vEvIDBD2mu2d5.pop_back(); vEdepBD2mu2d5.pop_back();
			  
	  mu2fBGOD2d5.close();
	  allvEvIDBD2mu2d5.push_back(vEvIDBD2mu2d5);
	  allvEdepBD2mu2d5.push_back(vEdepBD2mu2d5);


   }  

		
   //-------------------------------------------------------------------
   //                     Bin-by-bin analysis
   //                          Mu-decay
   //-------------------------------------------------------------------     
			
   // X-ray cascade	  
   for (int i=0; i<allvEvIDBD1mu.size(); i++) {
      
      std::cout << std::endl;
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m--------------------- X-ray cascade ----------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

      for (int m=0; m<nsamps; m++) {

	     Ethr = Ethrmu[m];

		 //--------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Cu dA1 = 300 mm
		 //-------------------------------------------------------- 
		 XXray = 0; Xelec = 0;
			  
		 for (int a=0; a<allvEvIDBD1x[0].size(); a++) {

		    if ((allvEdepSD1x[i][a] < Ethr1) && (allvEdepSD2x[i][a] < Ethr1) && (allvEdepSD3x[i][a] < Ethr1)) {
			   if (((allvEdepBD1x[i][a] > Ethr) && (allvEdepBD1x[i][a] < Ethr22)) || ((allvEdepBD2x[i][a] > Ethr) && (allvEdepBD2x[i][a] < Ethr22))) {
			      XXray += 1;
			   } else { Xelec += 1; }
		    } else { Xelec += 1; }
		 }
				 
		 PXXvector[i][m] = XXray/(double)(counterXX);
		 PXevector[i][m] = Xelec/(double)(counterXX); 


		 //-----------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Glass dA1 = 300 mm
		 //----------------------------------------------------------- 
		 XXray2 = 0; Xelec2 = 0;
			  
		 for (int a=0; a<allvEvIDBD1x2[0].size(); a++) {

		    if ((allvEdepSD1x2[i][a] < Ethr1) && (allvEdepSD2x2[i][a] < Ethr1) && (allvEdepSD3x2[i][a] < Ethr1)) {
			   if (((allvEdepBD1x2[i][a] > Ethr) && (allvEdepBD1x2[i][a] < Ethr22)) || ((allvEdepBD2x2[i][a] > Ethr) && (allvEdepBD2x2[i][a] < Ethr22))) {
			      XXray2 += 1;
			   } else { Xelec2 += 1; }
		    } else { Xelec2 += 1; }
		 }
				 
		 PXXvector2[i][m] = XXray2/(double)(counterXX);
		 PXevector2[i][m] = Xelec2/(double)(counterXX); 


         //--------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Cu dA1 = 350 mm
		 //-------------------------------------------------------- 
		 XXrayd2 = 0; Xelecd2 = 0;
			  
		 for (int a=0; a<allvEvIDBD1xd2[0].size(); a++) {

		    if ((allvEdepSD1xd2[i][a] < Ethr1) && (allvEdepSD2xd2[i][a] < Ethr1) && (allvEdepSD3xd2[i][a] < Ethr1)) {
			   if (((allvEdepBD1xd2[i][a] > Ethr) && (allvEdepBD1xd2[i][a] < Ethr22)) || ((allvEdepBD2xd2[i][a] > Ethr) && (allvEdepBD2xd2[i][a] < Ethr22))) {
			      XXrayd2 += 1;
			   } else { Xelecd2 += 1; }
		    } else { Xelecd2 += 1; }
		 }
				 
		 PXXvectord2[i][m] = XXrayd2/(double)(counterXX);
		 PXevectord2[i][m] = Xelecd2/(double)(counterXX); 


		 //-----------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Glass dA1 = 350 mm
		 //----------------------------------------------------------- 
		 XXray2d2 = 0; Xelec2d2 = 0;
			  
		 for (int a=0; a<allvEvIDBD1x2d2[0].size(); a++) {

		    if ((allvEdepSD1x2d2[i][a] < Ethr1) && (allvEdepSD2x2d2[i][a] < Ethr1) && (allvEdepSD3x2d2[i][a] < Ethr1)) {
			   if (((allvEdepBD1x2d2[i][a] > Ethr) && (allvEdepBD1x2d2[i][a] < Ethr22)) || ((allvEdepBD2x2d2[i][a] > Ethr) && (allvEdepBD2x2d2[i][a] < Ethr22))) {
			      XXray2d2 += 1;
			   } else { Xelec2d2 += 1; }
		    } else { Xelec2d2 += 1; }
		 }
				 
		 PXXvector2d2[i][m] = XXray2d2/(double)(counterXX);
		 PXevector2d2[i][m] = Xelec2d2/(double)(counterXX); 


         //--------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Cu dA1 = 400 mm
		 //-------------------------------------------------------- 
		 XXrayd3 = 0; Xelecd3 = 0;
			  
		 for (int a=0; a<allvEvIDBD1xd3[0].size(); a++) {

		    if ((allvEdepSD1xd3[i][a] < Ethr1) && (allvEdepSD2xd3[i][a] < Ethr1) && (allvEdepSD3xd3[i][a] < Ethr1)) {
			   if (((allvEdepBD1xd3[i][a] > Ethr) && (allvEdepBD1xd3[i][a] < Ethr22)) || ((allvEdepBD2xd3[i][a] > Ethr) && (allvEdepBD2xd3[i][a] < Ethr22))) {
			      XXrayd3 += 1;
			   } else { Xelecd3 += 1; }
		    } else { Xelecd3 += 1; }
		 }
				 
		 PXXvectord3[i][m] = XXrayd3/(double)(counterXX);
		 PXevectord3[i][m] = Xelecd3/(double)(counterXX); 


		 //-----------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Glass dA1 = 400 mm
		 //----------------------------------------------------------- 
		 XXray2d3 = 0; Xelec2d3 = 0;
			  
		 for (int a=0; a<allvEvIDBD1x2d3[0].size(); a++) {

		    if ((allvEdepSD1x2d3[i][a] < Ethr1) && (allvEdepSD2x2d3[i][a] < Ethr1) && (allvEdepSD3x2d3[i][a] < Ethr1)) {
			   if (((allvEdepBD1x2d3[i][a] > Ethr) && (allvEdepBD1x2d3[i][a] < Ethr22)) || ((allvEdepBD2x2d3[i][a] > Ethr) && (allvEdepBD2x2d3[i][a] < Ethr22))) {
			      XXray2d3 += 1;
			   } else { Xelec2d3 += 1; }
		    } else { Xelec2d3 += 1; }
		 }
				 
		 PXXvector2d3[i][m] = XXray2d3/(double)(counterXX);
		 PXevector2d3[i][m] = Xelec2d3/(double)(counterXX); 


         //--------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Cu dA1 = 450 mm
		 //-------------------------------------------------------- 
		 XXrayd4 = 0; Xelecd4 = 0;
			  
		 for (int a=0; a<allvEvIDBD1xd4[0].size(); a++) {

		    if ((allvEdepSD1xd4[i][a] < Ethr1) && (allvEdepSD2xd4[i][a] < Ethr1) && (allvEdepSD3xd4[i][a] < Ethr1)) {
			   if (((allvEdepBD1xd4[i][a] > Ethr) && (allvEdepBD1xd4[i][a] < Ethr22)) || ((allvEdepBD2xd4[i][a] > Ethr) && (allvEdepBD2xd4[i][a] < Ethr22))) {
			      XXrayd4 += 1;
			   } else { Xelecd4 += 1; }
		    } else { Xelecd4 += 1; }
		 }
				 
		 PXXvectord4[i][m] = XXrayd4/(double)(counterXX);
		 PXevectord4[i][m] = Xelecd4/(double)(counterXX); 


		 //-----------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Glass dA1 = 450 mm
		 //----------------------------------------------------------- 
		 XXray2d4 = 0; Xelec2d4 = 0;
			  
		 for (int a=0; a<allvEvIDBD1x2d4[0].size(); a++) {

		    if ((allvEdepSD1x2d4[i][a] < Ethr1) && (allvEdepSD2x2d4[i][a] < Ethr1) && (allvEdepSD3x2d4[i][a] < Ethr1)) {
			   if (((allvEdepBD1x2d4[i][a] > Ethr) && (allvEdepBD1x2d4[i][a] < Ethr22)) || ((allvEdepBD2x2d4[i][a] > Ethr) && (allvEdepBD2x2d4[i][a] < Ethr22))) {
			      XXray2d4 += 1;
			   } else { Xelec2d4 += 1; }
		    } else { Xelec2d4 += 1; }
		 }
				 
		 PXXvector2d4[i][m] = XXray2d4/(double)(counterXX);
		 PXevector2d4[i][m] = Xelec2d4/(double)(counterXX); 


         //--------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Cu dA1 = 500 mm
		 //-------------------------------------------------------- 
		 XXrayd5 = 0; Xelecd5 = 0;
			  
		 for (int a=0; a<allvEvIDBD1xd5[0].size(); a++) {

		    if ((allvEdepSD1xd5[i][a] < Ethr1) && (allvEdepSD2xd5[i][a] < Ethr1) && (allvEdepSD3xd5[i][a] < Ethr1)) {
			   if (((allvEdepBD1xd5[i][a] > Ethr) && (allvEdepBD1xd5[i][a] < Ethr22)) || ((allvEdepBD2xd5[i][a] > Ethr) && (allvEdepBD2xd5[i][a] < Ethr22))) {
			      XXrayd5 += 1;
			   } else { Xelecd5 += 1; }
		    } else { Xelecd5 += 1; }
		 }
				 
		 PXXvectord5[i][m] = XXrayd5/(double)(counterXX);
		 PXevectord5[i][m] = Xelecd5/(double)(counterXX); 


		 //-----------------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade Glass dA1 = 500 mm
		 //----------------------------------------------------------- 
		 XXray2d5 = 0; Xelec2d5 = 0;
			  
		 for (int a=0; a<allvEvIDBD1x2d5[0].size(); a++) {

		    if ((allvEdepSD1x2d5[i][a] < Ethr1) && (allvEdepSD2x2d5[i][a] < Ethr1) && (allvEdepSD3x2d5[i][a] < Ethr1)) {
			   if (((allvEdepBD1x2d5[i][a] > Ethr) && (allvEdepBD1x2d5[i][a] < Ethr22)) || ((allvEdepBD2x2d5[i][a] > Ethr) && (allvEdepBD2x2d5[i][a] < Ethr22))) {
			      XXray2d5 += 1;
			   } else { Xelec2d5 += 1; }
		    } else { Xelec2d5 += 1; }
		 }
				 
		 PXXvector2d5[i][m] = XXray2d5/(double)(counterXX);
		 PXevector2d5[i][m] = Xelec2d5/(double)(counterXX); 



		 //---------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Cu dA1 = 300 mm
		 //--------------------------------------------------------- 
		 eXray = 0; eelec = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu[0].size(); a++) {

		    if ((allvEdepSD1mu[i][a] < Ethr1) && (allvEdepSD2mu[i][a] < Ethr1) && (allvEdepSD3mu[i][a] < Ethr1)) {
		       if (((allvEdepBD1mu[i][a] > Ethr) && (allvEdepBD1mu[i][a] < Ethr22)) || ((allvEdepBD2mu[i][a] > Ethr) && (allvEdepBD2mu[i][a] < Ethr22))) {
			      eXray += 1;
			   } else { eelec += 1; }
		    } else { eelec += 1; }
		 }
				 
		 PeXvector[i][m] = eXray/(double)(counteree);
		 Peevector[i][m] = eelec/(double)(counteree); 


		 //------------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Glass dA1 = 300 mm
		 //------------------------------------------------------------ 
		 eXray2 = 0; eelec2 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu2[0].size(); a++) {

		    if ((allvEdepSD1mu2[i][a] < Ethr1) && (allvEdepSD2mu2[i][a] < Ethr1) && (allvEdepSD3mu2[i][a] < Ethr1)) {
		       if (((allvEdepBD1mu2[i][a] > Ethr) && (allvEdepBD1mu2[i][a] < Ethr22)) || ((allvEdepBD2mu2[i][a] > Ethr) && (allvEdepBD2mu2[i][a] < Ethr22))) {
			      eXray2 += 1;
			   } else { eelec2 += 1; }
		    } else { eelec2 += 1; }
		 }
				 
		 PeXvector2[i][m] = eXray2/(double)(counteree);
		 Peevector2[i][m] = eelec2/(double)(counteree); 


		 //---------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Cu dA1 = 350 mm
		 //--------------------------------------------------------- 
		 eXrayd2 = 0; eelecd2 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mud2[0].size(); a++) {

		    if ((allvEdepSD1mud2[i][a] < Ethr1) && (allvEdepSD2mud2[i][a] < Ethr1) && (allvEdepSD3mud2[i][a] < Ethr1)) {
		       if (((allvEdepBD1mud2[i][a] > Ethr) && (allvEdepBD1mud2[i][a] < Ethr22)) || ((allvEdepBD2mud2[i][a] > Ethr) && (allvEdepBD2mud2[i][a] < Ethr22))) {
			      eXrayd2 += 1;
			   } else { eelecd2 += 1; }
		    } else { eelecd2 += 1; }
		 }
				 
		 PeXvectord2[i][m] = eXrayd2/(double)(counteree);
		 Peevectord2[i][m] = eelecd2/(double)(counteree); 


		 //------------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Glass dA1 = 350 mm
		 //------------------------------------------------------------ 
		 eXray2d2 = 0; eelec2d2 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu2d2[0].size(); a++) {

		    if ((allvEdepSD1mu2d2[i][a] < Ethr1) && (allvEdepSD2mu2d2[i][a] < Ethr1) && (allvEdepSD3mu2d2[i][a] < Ethr1)) {
		       if (((allvEdepBD1mu2d2[i][a] > Ethr) && (allvEdepBD1mu2d2[i][a] < Ethr22)) || ((allvEdepBD2mu2d2[i][a] > Ethr) && (allvEdepBD2mu2d2[i][a] < Ethr22))) {
			      eXray2d2 += 1;
			   } else { eelec2d2 += 1; }
		    } else { eelec2d2 += 1; }
		 }
				 
		 PeXvector2d2[i][m] = eXray2d2/(double)(counteree);
		 Peevector2d2[i][m] = eelec2d2/(double)(counteree); 


		 //---------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Cu dA1 = 400 mm
		 //--------------------------------------------------------- 
		 eXrayd3 = 0; eelecd3 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mud3[0].size(); a++) {

		    if ((allvEdepSD1mud3[i][a] < Ethr1) && (allvEdepSD2mud3[i][a] < Ethr1) && (allvEdepSD3mud3[i][a] < Ethr1)) {
		       if (((allvEdepBD1mud3[i][a] > Ethr) && (allvEdepBD1mud3[i][a] < Ethr22)) || ((allvEdepBD2mud3[i][a] > Ethr) && (allvEdepBD2mud3[i][a] < Ethr22))) {
			      eXrayd3 += 1;
			   } else { eelecd3 += 1; }
		    } else { eelecd3 += 1; }
		 }
				 
		 PeXvectord3[i][m] = eXrayd3/(double)(counteree);
		 Peevectord3[i][m] = eelecd3/(double)(counteree); 


		 //------------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Glass dA1 = 400 mm
		 //------------------------------------------------------------ 
		 eXray2d3 = 0; eelec2d3 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu2d3[0].size(); a++) {

		    if ((allvEdepSD1mu2d3[i][a] < Ethr1) && (allvEdepSD2mu2d3[i][a] < Ethr1) && (allvEdepSD3mu2d3[i][a] < Ethr1)) {
		       if (((allvEdepBD1mu2d3[i][a] > Ethr) && (allvEdepBD1mu2d3[i][a] < Ethr22)) || ((allvEdepBD2mu2d3[i][a] > Ethr) && (allvEdepBD2mu2d3[i][a] < Ethr22))) {
			      eXray2d3 += 1;
			   } else { eelec2d3 += 1; }
		    } else { eelec2d3 += 1; }
		 }
				 
		 PeXvector2d3[i][m] = eXray2d3/(double)(counteree);
		 Peevector2d3[i][m] = eelec2d3/(double)(counteree); 


		 //---------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Cu dA1 = 450 mm
		 //--------------------------------------------------------- 
		 eXrayd4 = 0; eelecd4 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mud4[0].size(); a++) {

		    if ((allvEdepSD1mud4[i][a] < Ethr1) && (allvEdepSD2mud4[i][a] < Ethr1) && (allvEdepSD3mud4[i][a] < Ethr1)) {
		       if (((allvEdepBD1mud4[i][a] > Ethr) && (allvEdepBD1mud4[i][a] < Ethr22)) || ((allvEdepBD2mud4[i][a] > Ethr) && (allvEdepBD2mud4[i][a] < Ethr22))) {
			      eXrayd4 += 1;
			   } else { eelecd4 += 1; }
		    } else { eelecd4 += 1; }
		 }
				 
		 PeXvectord4[i][m] = eXrayd4/(double)(counteree);
		 Peevectord4[i][m] = eelecd4/(double)(counteree); 


		 //------------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Glass dA1 = 450 mm 
		 //------------------------------------------------------------ 
		 eXray2d4 = 0; eelec2d4 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu2d4[0].size(); a++) {

		    if ((allvEdepSD1mu2d4[i][a] < Ethr1) && (allvEdepSD2mu2d4[i][a] < Ethr1) && (allvEdepSD3mu2d4[i][a] < Ethr1)) {
		       if (((allvEdepBD1mu2d4[i][a] > Ethr) && (allvEdepBD1mu2d4[i][a] < Ethr22)) || ((allvEdepBD2mu2d4[i][a] > Ethr) && (allvEdepBD2mu2d4[i][a] < Ethr22))) {
			      eXray2d4 += 1;
			   } else { eelec2d4 += 1; }
		    } else { eelec2d4 += 1; }
		 }
				 
		 PeXvector2d4[i][m] = eXray2d4/(double)(counteree);
		 Peevector2d4[i][m] = eelec2d4/(double)(counteree); 


		 //---------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Cu dA1 = 500 mm
		 //--------------------------------------------------------- 
		 eXrayd5 = 0; eelecd5 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mud5[0].size(); a++) {

		    if ((allvEdepSD1mud5[i][a] < Ethr1) && (allvEdepSD2mud5[i][a] < Ethr1) && (allvEdepSD3mud5[i][a] < Ethr1)) {
		       if (((allvEdepBD1mud5[i][a] > Ethr) && (allvEdepBD1mud5[i][a] < Ethr22)) || ((allvEdepBD2mud5[i][a] > Ethr) && (allvEdepBD2mud5[i][a] < Ethr22))) {
			      eXrayd5 += 1;
			   } else { eelecd5 += 1; }
		    } else { eelecd5 += 1; }
		 }
				 
		 PeXvectord5[i][m] = eXrayd5/(double)(counteree);
		 Peevectord5[i][m] = eelecd5/(double)(counteree); 


		 //------------------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay Glass dA1 = 500 mm
		 //------------------------------------------------------------ 
		 eXray2d5 = 0; eelec2d5 = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu2d5[0].size(); a++) {

		    if ((allvEdepSD1mu2d5[i][a] < Ethr1) && (allvEdepSD2mu2d5[i][a] < Ethr1) && (allvEdepSD3mu2d5[i][a] < Ethr1)) {
		       if (((allvEdepBD1mu2d5[i][a] > Ethr) && (allvEdepBD1mu2d5[i][a] < Ethr22)) || ((allvEdepBD2mu2d5[i][a] > Ethr) && (allvEdepBD2mu2d5[i][a] < Ethr22))) {
			      eXray2d5 += 1;
			   } else { eelec2d5 += 1; }
		    } else { eelec2d5 += 1; }
		 }
				 
		 PeXvector2d5[i][m] = eXray2d5/(double)(counteree);
		 Peevector2d5[i][m] = eelec2d5/(double)(counteree); 

	  
	  } 

				
   }  

   //-------------------------------------------------------------------
   //                     Plotting business
   //-------------------------------------------------------------------     
						
   std::cout << std::endl;
   std::cout << "\033[1;33m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;33m-------------------- Plotting business -------------------\033[0m" << std::endl;
   std::cout << "\033[1;33m----------------------------------------------------------\033[0m" << std::endl;

   // Array declarations
   // Normalisation 2 [abs]
   float PXXarr[nsamps] = {}; // X-ray cascade
   float PXXarr2[nsamps] = {};
   float PXXarrd2[nsamps] = {};
   float PXXarr2d2[nsamps] = {};
   float PXXarrd3[nsamps] = {};
   float PXXarr2d3[nsamps] = {};
   float PXXarrd4[nsamps] = {};
   float PXXarr2d4[nsamps] = {};
   float PXXarrd5[nsamps] = {};
   float PXXarr2d5[nsamps] = {};
   float PeXarr[nsamps] = {};
   float PeXarr2[nsamps] = {};
   float PeXarrd2[nsamps] = {};
   float PeXarr2d2[nsamps] = {};
   float PeXarrd3[nsamps] = {};
   float PeXarr2d3[nsamps] = {};
   float PeXarrd4[nsamps] = {};
   float PeXarr2d4[nsamps] = {};
   float PeXarrd5[nsamps] = {};
   float PeXarr2d5[nsamps] = {};
 		 	   
   for (int i=0; i<nsamps; i++) {
      // Normalisation 2 [absolute]
	  PXXarr[i] = PXXvector[0][i];
	  PXXarr2[i] = PXXvector2[0][i];
	  PXXarrd2[i] = PXXvectord2[0][i];
	  PXXarr2d2[i] = PXXvector2d2[0][i];
	  PXXarrd3[i] = PXXvectord3[0][i];
	  PXXarr2d3[i] = PXXvector2d3[0][i];
	  PXXarrd4[i] = PXXvectord4[0][i];
	  PXXarr2d4[i] = PXXvector2d4[0][i];
	  PXXarrd5[i] = PXXvectord5[0][i];
	  PXXarr2d5[i] = PXXvector2d5[0][i];
	  PeXarr[i] = PeXvector[0][i];
	  PeXarr2[i] = PeXvector2[0][i];
	  PeXarrd2[i] = PeXvectord2[0][i];
	  PeXarr2d2[i] = PeXvector2d2[0][i];
      PeXarrd3[i] = PeXvectord3[0][i];
	  PeXarr2d3[i] = PeXvector2d3[0][i];
      PeXarrd4[i] = PeXvectord4[0][i];
	  PeXarr2d4[i] = PeXvector2d4[0][i];
      PeXarrd5[i] = PeXvectord5[0][i];
	  PeXarr2d5[i] = PeXvector2d5[0][i];


   }	   

		  
   TCanvas *f = new TCanvas("f","E_{THR}",800,600);
   f->Divide(2,1);
   f->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   //gPad->SetFixedAspectRatio();
   TGraph *grPXX = new TGraph(nsamps,Ethrmu,PXXarr);
   grPXX->SetTitle(""); 
   grPXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXX->GetXaxis()->SetRangeUser(0,2.04);
   //grPXX->GetXaxis()->SetNdivisions(-304);
   grPXX->GetYaxis()->SetMoreLogLabels(1);
   grPXX->GetYaxis()->SetTitle("P_{XX}");
   grPXX->GetYaxis()->SetTitleOffset(2.1);
   grPXX->SetLineColor(kRed);
   grPXX->SetLineWidth(3);
   grPXX->SetLineStyle(1);
   grPXX->Draw("ALP");
   TGraph *grPXXd2 = new TGraph(nsamps,Ethrmu,PXXarrd2);
   grPXXd2->SetLineColor(kRed);
   grPXXd2->SetLineWidth(3);
   grPXXd2->SetLineStyle(3);
   grPXXd2->Draw("LP");
   TGraph *grPXXd3 = new TGraph(nsamps,Ethrmu,PXXarrd3);
   grPXXd3->SetLineColor(kRed);
   grPXXd3->SetLineWidth(3);
   grPXXd3->SetLineStyle(5);
   grPXXd3->Draw("LP");
   TGraph *grPXXd4 = new TGraph(nsamps,Ethrmu,PXXarrd4);
   grPXXd4->SetLineColor(kRed);
   grPXXd4->SetLineWidth(3);
   grPXXd4->SetLineStyle(7);
   grPXXd4->Draw("LP");
   TGraph *grPXXd5 = new TGraph(nsamps,Ethrmu,PXXarrd5);
   grPXXd5->SetLineColor(kRed);
   grPXXd5->SetLineWidth(3);
   grPXXd5->SetLineStyle(9);
   grPXXd5->Draw("LP");
   TGraph *grPXX2 = new TGraph(nsamps,Ethrmu,PXXarr2);
   grPXX2->SetLineColor(kBlack);
   grPXX2->SetLineWidth(3);
   grPXX2->SetLineStyle(1);
   grPXX2->Draw("LP");
   TGraph *grPXX2d2 = new TGraph(nsamps,Ethrmu,PXXarr2d2);
   grPXX2d2->SetLineColor(kBlack);
   grPXX2d2->SetLineWidth(3);
   grPXX2d2->SetLineStyle(3);
   grPXX2d2->Draw("LP");
   TGraph *grPXX2d3 = new TGraph(nsamps,Ethrmu,PXXarr2d3);
   grPXX2d3->SetLineColor(kBlack);
   grPXX2d3->SetLineWidth(3);
   grPXX2d3->SetLineStyle(5);
   grPXX2d3->Draw("LP");
   TGraph *grPXX2d4 = new TGraph(nsamps,Ethrmu,PXXarr2d4);
   grPXX2d4->SetLineColor(kBlack);
   grPXX2d4->SetLineWidth(3);
   grPXX2d4->SetLineStyle(7);
   grPXX2d4->Draw("LP");
   TGraph *grPXX2d5 = new TGraph(nsamps,Ethrmu,PXXarr2d5);
   grPXX2d5->SetLineColor(kBlack);
   grPXX2d5->SetLineWidth(3);
   grPXX2d5->SetLineStyle(9);
   grPXX2d5->Draw("LP");

   legPXX4mm = new TLegend(0.55,0.75,1.0,1.0);
   legPXX4mm->SetTextSize(0.03);
   legPXX4mm->AddEntry(grPXX,"Copper, d_{A1} = "+TString(dA1)+"mm","lp");
   legPXX4mm->AddEntry(grPXXd2,"Copper, d_{A1} = "+TString(dA12)+"mm","lp");
   legPXX4mm->AddEntry(grPXXd3,"Copper, d_{A1} = "+TString(dA13)+"mm","lp");
   legPXX4mm->AddEntry(grPXXd4,"Copper, d_{A1} = "+TString(dA14)+"mm","lp");
   legPXX4mm->AddEntry(grPXXd5,"Copper, d_{A1} = "+TString(dA15)+"mm","lp");
   legPXX4mm->AddEntry(grPXX2,"Glass, d_{A1} = "+TString(dA1)+"mm","lp");
   legPXX4mm->AddEntry(grPXX2d2,"Glass, d_{A1} = "+TString(dA12)+"mm","lp");
   legPXX4mm->AddEntry(grPXX2d3,"Glass, d_{A1} = "+TString(dA13)+"mm","lp");
   legPXX4mm->AddEntry(grPXX2d4,"Glass, d_{A1} = "+TString(dA14)+"mm","lp");
   legPXX4mm->AddEntry(grPXX2d5,"Glass, d_{A1} = "+TString(dA15)+"mm","lp");
   legPXX4mm->Draw();
   
   f->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeX = new TGraph(nsamps,Ethrmu,PeXarr);
   grPeX->SetTitle("");
   grPeX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeX->GetXaxis()->SetRangeUser(0,2.04);
   //grPeX->GetXaxis()->SetNdivisions(-304);
   //TGaxis::SetMaxDigits(2);
   grPeX->GetYaxis()->SetMoreLogLabels(1);
   grPeX->GetYaxis()->SetTitle("P_{eX}");
   grPeX->GetYaxis()->SetTitleOffset(2.1);
   grPeX->SetLineColor(kRed);
   grPeX->SetLineWidth(3);
   grPeX->SetLineStyle(1);
   grPeX->Draw("ALP");
   TGraph *grPeXd2 = new TGraph(nsamps,Ethrmu,PeXarrd2);
   grPeXd2->SetLineColor(kRed);
   grPeXd2->SetLineWidth(3);
   grPeXd2->SetLineStyle(3);
   grPeXd2->Draw("LP");
   TGraph *grPeXd3 = new TGraph(nsamps,Ethrmu,PeXarrd3);
   grPeXd3->SetLineColor(kRed);
   grPeXd3->SetLineWidth(3);
   grPeXd3->SetLineStyle(5);
   grPeXd3->Draw("LP");
   TGraph *grPeXd4 = new TGraph(nsamps,Ethrmu,PeXarrd4);
   grPeXd4->SetLineColor(kRed);
   grPeXd4->SetLineWidth(3);
   grPeXd4->SetLineStyle(7);
   grPeXd4->Draw("LP");
   TGraph *grPeXd5 = new TGraph(nsamps,Ethrmu,PeXarrd5);
   grPeXd5->SetLineColor(kRed);
   grPeXd5->SetLineWidth(3);
   grPeXd5->SetLineStyle(9);
   grPeXd5->Draw("LP");
   TGraph *grPeX2 = new TGraph(nsamps,Ethrmu,PeXarr2);
   grPeX2->SetLineColor(kBlack);
   grPeX2->SetLineWidth(3);
   grPeX2->SetLineStyle(1);
   grPeX2->Draw("LP");
   TGraph *grPeX2d2 = new TGraph(nsamps,Ethrmu,PeXarr2d2);
   grPeX2d2->SetLineColor(kBlack);
   grPeX2d2->SetLineWidth(3);
   grPeX2d2->SetLineStyle(3);
   grPeX2d2->Draw("LP");
   TGraph *grPeX2d3 = new TGraph(nsamps,Ethrmu,PeXarr2d3);
   grPeX2d3->SetLineColor(kBlack);
   grPeX2d3->SetLineWidth(3);
   grPeX2d3->SetLineStyle(5);
   grPeX2d3->Draw("LP");
   TGraph *grPeX2d4 = new TGraph(nsamps,Ethrmu,PeXarr2d4);
   grPeX2d4->SetLineColor(kBlack);
   grPeX2d4->SetLineWidth(3);
   grPeX2d4->SetLineStyle(7);
   grPeX2d4->Draw("LP");
   TGraph *grPeX2d5 = new TGraph(nsamps,Ethrmu,PeXarr2d5);
   grPeX2d5->SetLineColor(kBlack);
   grPeX2d5->SetLineWidth(3);
   grPeX2d5->SetLineStyle(9);
   grPeX2d5->Draw("LP");
   
   legPeX4mm = new TLegend(0.55,0.75,1.0,1.0);
   legPeX4mm->SetTextSize(0.03);
   legPeX4mm->AddEntry(grPeX,"Copper, d_{A1} = "+TString(dA1)+"mm","lp");
   legPeX4mm->AddEntry(grPeXd2,"Copper, d_{A1} = "+TString(dA12)+"mm","lp");
   legPeX4mm->AddEntry(grPeXd3,"Copper, d_{A1} = "+TString(dA13)+"mm","lp");
   legPeX4mm->AddEntry(grPeXd4,"Copper, d_{A1} = "+TString(dA14)+"mm","lp");
   legPeX4mm->AddEntry(grPeXd5,"Copper, d_{A1} = "+TString(dA15)+"mm","lp");
   legPeX4mm->AddEntry(grPeX2,"Glass, d_{A1} = "+TString(dA1)+"mm","lp");
   legPeX4mm->AddEntry(grPeX2d2,"Glass, d_{A1} = "+TString(dA12)+"mm","lp");
   legPeX4mm->AddEntry(grPeX2d3,"Glass, d_{A1} = "+TString(dA13)+"mm","lp");
   legPeX4mm->AddEntry(grPeX2d4,"Glass, d_{A1} = "+TString(dA14)+"mm","lp");
   legPeX4mm->AddEntry(grPeX2d5,"Glass, d_{A1} = "+TString(dA15)+"mm","lp");
   legPeX4mm->Draw();

   f->SaveAs("Cu_glass_Sci_Vert_dB_"+TString(dB)+"mm_dA1.pdf");
   f->SaveAs("Cu_glass_Sci_Vert_dB_"+TString(dB)+"mm_dA1.png");
   f->SaveAs("Cu_glass_Sci_Vert_dB_"+TString(dB)+"mm_dA1.C");

 
} 
 
 int main() {
   finalcavCuGlassVert();
   return 0;
}  
