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

void finalcavMULTIeff(){

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

   const int nsamps = 101;
   std::string phishift = "0";
   std::string zshift = "0";
   std::string material = "Glass";

   // Names of the files
   // X-ray cascade3
   std::string filex3SciD1 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_SciD1.txt";
   std::string filex3SciD2 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_SciD2.txt";
   std::string filex3SciD3 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_SciD3.txt";
   std::string filex3SciDS1 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_SciDS1.txt";
   std::string filex3SciDS2 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_SciDS2.txt";
   std::string filex3BGOD1 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_BGOD1.txt";
   std::string filex3BGOD2 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_BGOD2.txt";
   std::string filex3SciVeto = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_SciVeto.txt";

   // X-ray cascade2
   std::string filex2SciD1 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_SciD1.txt";
   std::string filex2SciD2 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_SciD2.txt";
   std::string filex2SciD3 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_SciD3.txt";
   std::string filex2SciDS1 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_SciDS1.txt";
   std::string filex2SciDS2 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_SciDS2.txt";
   std::string filex2BGOD1 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_BGOD1.txt";
   std::string filex2BGOD2 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_BGOD2.txt";
   std::string filex2SciVeto = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_SciVeto.txt";

   // X-ray cascade
   std::string filexSciD1 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_SciD1.txt";
   std::string filexSciD2 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_SciD2.txt";
   std::string filexSciD3 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_SciD3.txt";
   std::string filexSciDS1 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_SciDS1.txt";
   std::string filexSciDS2 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_SciDS2.txt";
   std::string filexBGOD1 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD2 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_BGOD2.txt";
   std::string filexSciVeto = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_SciVeto.txt";

   // Mu-decay
   std::string filemuSciD1 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_SciD1.txt";
   std::string filemuSciD2 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_SciD2.txt";
   std::string filemuSciD3 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_SciD3.txt";
   std::string filemuSciDS1 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_SciDS1.txt";
   std::string filemuSciDS2 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_SciDS2.txt";
   std::string filemuBGOD1 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD2 = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_BGOD2.txt";
   std::string filemuSciVeto = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_SciVeto.txt";


   std::string phishift = "50";
   std::string zshift = "30";
   
   // X-ray cascade3
   std::string filex3SciD1phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_SciD1.txt";
   std::string filex3SciD2phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_SciD2.txt";
   std::string filex3SciD3phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_SciD3.txt";
   std::string filex3SciDS1phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_SciDS1.txt";
   std::string filex3SciDS2phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_SciDS2.txt";
   std::string filex3BGOD1phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_BGOD1.txt";
   std::string filex3BGOD2phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_BGOD2.txt";
   std::string filex3SciVetophiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade3_SciVeto.txt";

   // X-ray cascade2
   std::string filex2SciD1phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_SciD1.txt";
   std::string filex2SciD2phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_SciD2.txt";
   std::string filex2SciD3phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_SciD3.txt";
   std::string filex2SciDS1phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_SciDS1.txt";
   std::string filex2SciDS2phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_SciDS2.txt";
   std::string filex2BGOD1phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_BGOD1.txt";
   std::string filex2BGOD2phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_BGOD2.txt";
   std::string filex2SciVetophiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade2_SciVeto.txt";

   // X-ray cascade
   std::string filexSciD1phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_SciD1.txt";
   std::string filexSciD2phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_SciD2.txt";
   std::string filexSciD3phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_SciD3.txt";
   std::string filexSciDS1phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_SciDS1.txt";
   std::string filexSciDS2phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_SciDS2.txt";
   std::string filexBGOD1phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_BGOD1.txt";
   std::string filexBGOD2phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_BGOD2.txt";
   std::string filexSciVetophiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5goldcascade_SciVeto.txt";

   // Mu-decay
   std::string filemuSciD1phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_SciD1.txt";
   std::string filemuSciD2phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_SciD2.txt";
   std::string filemuSciD3phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_SciD3.txt";
   std::string filemuSciDS1phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_SciDS1.txt";
   std::string filemuSciDS2phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_SciDS2.txt";
   std::string filemuBGOD1phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_BGOD1.txt";
   std::string filemuBGOD2phiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_BGOD2.txt";
   std::string filemuSciVetophiz = "../../simdata/final/"+material+"_cav_NaI_"+phishift+"mm_phi_"+zshift+"mm_z_no_Al_1e5mudecay_SciVeto.txt";




   // Vectors with filenames   
   std::vector<std::string> Xfiles;
   std::vector<std::string> mufiles;

   // X-ray cascade
   Xfiles.push_back(filex3SciD1);
   Xfiles.push_back(filex3SciD2);
   Xfiles.push_back(filex3SciD3);
   Xfiles.push_back(filex3SciDS1);
   Xfiles.push_back(filex3SciDS2);
   Xfiles.push_back(filex3BGOD1);
   Xfiles.push_back(filex3BGOD2);
   Xfiles.push_back(filex3SciVeto);

   Xfiles.push_back(filex2SciD1);
   Xfiles.push_back(filex2SciD2);
   Xfiles.push_back(filex2SciD3);
   Xfiles.push_back(filex2SciDS1);
   Xfiles.push_back(filex2SciDS2);
   Xfiles.push_back(filex2BGOD1);
   Xfiles.push_back(filex2BGOD2);
   Xfiles.push_back(filex2SciVeto);
		 
   Xfiles.push_back(filexSciD1);
   Xfiles.push_back(filexSciD2);
   Xfiles.push_back(filexSciD3);
   Xfiles.push_back(filexSciDS1);
   Xfiles.push_back(filexSciDS2);
   Xfiles.push_back(filexBGOD1);
   Xfiles.push_back(filexBGOD2);
   Xfiles.push_back(filexSciVeto);

   Xfiles.push_back(filex3SciD1phiz);
   Xfiles.push_back(filex3SciD2phiz);
   Xfiles.push_back(filex3SciD3phiz);
   Xfiles.push_back(filex3SciDS1phiz);
   Xfiles.push_back(filex3SciDS2phiz);
   Xfiles.push_back(filex3BGOD1phiz);
   Xfiles.push_back(filex3BGOD2phiz);
   Xfiles.push_back(filex3SciVetophiz);

   Xfiles.push_back(filex2SciD1phiz);
   Xfiles.push_back(filex2SciD2phiz);
   Xfiles.push_back(filex2SciD3phiz);
   Xfiles.push_back(filex2SciDS1phiz);
   Xfiles.push_back(filex2SciDS2phiz);
   Xfiles.push_back(filex2BGOD1phiz);
   Xfiles.push_back(filex2BGOD2phiz);
   Xfiles.push_back(filex2SciVetophiz);
		 
   Xfiles.push_back(filexSciD1phiz);
   Xfiles.push_back(filexSciD2phiz);
   Xfiles.push_back(filexSciD3phiz);
   Xfiles.push_back(filexSciDS1phiz);
   Xfiles.push_back(filexSciDS2phiz);
   Xfiles.push_back(filexBGOD1phiz);
   Xfiles.push_back(filexBGOD2phiz);
   Xfiles.push_back(filexSciVetophiz);


   // Mu-decay
   mufiles.push_back(filemuSciD1);
   mufiles.push_back(filemuSciD2);
   mufiles.push_back(filemuSciD3);
   mufiles.push_back(filemuSciDS1);
   mufiles.push_back(filemuSciDS2);
   mufiles.push_back(filemuBGOD1);
   mufiles.push_back(filemuBGOD2);
   mufiles.push_back(filemuSciVeto);

   mufiles.push_back(filemuSciD1phiz);
   mufiles.push_back(filemuSciD2phiz);
   mufiles.push_back(filemuSciD3phiz);
   mufiles.push_back(filemuSciDS1phiz);
   mufiles.push_back(filemuSciDS2phiz);
   mufiles.push_back(filemuBGOD1phiz);
   mufiles.push_back(filemuBGOD2phiz);
   mufiles.push_back(filemuSciVetophiz);


   /*********************************/
   /*           Analysis            */
   /*********************************/

   float Edep, EventID;
   float iEventID;

   float Ethr1 = 0.5;
   float Ethr21 = 0.5;
   float Ethr22 = 10;
   float Ethr3 = 1;
   float Estep = 2.0/(nsamps-1);
   float Ethrmu[nsamps] = {};
		   
   // Storage vectors
   // Normalisation 2 [abs = total] :: X-ray cascade 3
   std::vector< std::vector<double> > PXevectorx3(Xfiles.size()/48,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorx3(Xfiles.size()/48,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevectorx3(Xfiles.size()/48,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorx3(Xfiles.size()/48,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade 2
   std::vector< std::vector<double> > PXevectorx2(Xfiles.size()/48,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorx2(Xfiles.size()/48,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevectorx2(Xfiles.size()/48,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorx2(Xfiles.size()/48,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade
   std::vector< std::vector<double> > PXevector(Xfiles.size()/48,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector(Xfiles.size()/48,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevector(Xfiles.size()/48,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvector(Xfiles.size()/48,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay
   std::vector< std::vector<double> > Peevector(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector(mufiles.size()/16,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevector(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvector(mufiles.size()/16,std::vector<double>(nsamps));      

   // Normalisation 2 [abs = total] :: X-ray cascade 3 phi-z
   std::vector< std::vector<double> > PXevectorx3phiz(Xfiles.size()/48,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorx3phiz(Xfiles.size()/48,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevectorx3phiz(Xfiles.size()/48,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorx3phiz(Xfiles.size()/48,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade 2 phi-z
   std::vector< std::vector<double> > PXevectorx2phiz(Xfiles.size()/48,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorx2phiz(Xfiles.size()/48,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevectorx2phiz(Xfiles.size()/48,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorx2phiz(Xfiles.size()/48,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: X-ray cascade phi-z
   std::vector< std::vector<double> > PXevectorphiz(Xfiles.size()/48,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorphiz(Xfiles.size()/48,std::vector<double>(nsamps));          
   std::vector< std::vector<double> > PXevectorphiz(Xfiles.size()/48,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PXXvectorphiz(Xfiles.size()/48,std::vector<double>(nsamps));      
   // Normalisation 2 [abs = total] :: Mu-decay phi-z
   std::vector< std::vector<double> > Peevectorphiz(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorphiz(mufiles.size()/16,std::vector<double>(nsamps));      
   std::vector< std::vector<double> > Peevectorphiz(mufiles.size()/16,std::vector<double>(nsamps));
   std::vector< std::vector<double> > PeXvectorphiz(mufiles.size()/16,std::vector<double>(nsamps));      



   // X-ray cascade 3
   std::vector< std::vector< double > > allvEvIDSD1x3;
   std::vector< std::vector< double > > allvEdepSD1x3;
   std::vector< std::vector< double > > allvEvIDSD2x3;
   std::vector< std::vector< double > > allvEdepSD2x3;
   std::vector< std::vector< double > > allvEvIDSD3x3;
   std::vector< std::vector< double > > allvEdepSD3x3;
   std::vector< std::vector< double > > allvEvIDSDS1x3;
   std::vector< std::vector< double > > allvEdepSDS1x3;
   std::vector< std::vector< double > > allvEvIDSDS2x3;
   std::vector< std::vector< double > > allvEdepSDS2x3;
   std::vector< std::vector< double > > allvEvIDBD1x3;
   std::vector< std::vector< double > > allvEdepBD1x3;
   std::vector< std::vector< double > > allvEvIDBD2x3;
   std::vector< std::vector< double > > allvEdepBD2x3;
   std::vector< std::vector< double > > allvEvIDSVx3;
   std::vector< std::vector< double > > allvEdepSVx3;

   // X-ray cascade 2
   std::vector< std::vector< double > > allvEvIDSD1x2;
   std::vector< std::vector< double > > allvEdepSD1x2;
   std::vector< std::vector< double > > allvEvIDSD2x2;
   std::vector< std::vector< double > > allvEdepSD2x2;
   std::vector< std::vector< double > > allvEvIDSD3x2;
   std::vector< std::vector< double > > allvEdepSD3x2;
   std::vector< std::vector< double > > allvEvIDSDS1x2;
   std::vector< std::vector< double > > allvEdepSDS1x2;
   std::vector< std::vector< double > > allvEvIDSDS2x2;
   std::vector< std::vector< double > > allvEdepSDS2x2;
   std::vector< std::vector< double > > allvEvIDBD1x2;
   std::vector< std::vector< double > > allvEdepBD1x2;
   std::vector< std::vector< double > > allvEvIDBD2x2;
   std::vector< std::vector< double > > allvEdepBD2x2;
   std::vector< std::vector< double > > allvEvIDSVx2;
   std::vector< std::vector< double > > allvEdepSVx2;

   // X-ray cascade
   std::vector< std::vector< double > > allvEvIDSD1x;
   std::vector< std::vector< double > > allvEdepSD1x;
   std::vector< std::vector< double > > allvEvIDSD2x;
   std::vector< std::vector< double > > allvEdepSD2x;
   std::vector< std::vector< double > > allvEvIDSD3x;
   std::vector< std::vector< double > > allvEdepSD3x;
   std::vector< std::vector< double > > allvEvIDSDS1x;
   std::vector< std::vector< double > > allvEdepSDS1x;
   std::vector< std::vector< double > > allvEvIDSDS2x;
   std::vector< std::vector< double > > allvEdepSDS2x;
   std::vector< std::vector< double > > allvEvIDBD1x;
   std::vector< std::vector< double > > allvEdepBD1x;
   std::vector< std::vector< double > > allvEvIDBD2x;
   std::vector< std::vector< double > > allvEdepBD2x;
   std::vector< std::vector< double > > allvEvIDSVx;
   std::vector< std::vector< double > > allvEdepSVx;

   // Mu-decay
   std::vector< std::vector< double > > allvEvIDSD1mu;
   std::vector< std::vector< double > > allvEdepSD1mu;
   std::vector< std::vector< double > > allvEvIDSD2mu;
   std::vector< std::vector< double > > allvEdepSD2mu;
   std::vector< std::vector< double > > allvEvIDSD3mu;
   std::vector< std::vector< double > > allvEdepSD3mu;
   std::vector< std::vector< double > > allvEvIDSDS1mu;
   std::vector< std::vector< double > > allvEdepSDS1mu;
   std::vector< std::vector< double > > allvEvIDSDS2mu;
   std::vector< std::vector< double > > allvEdepSDS2mu;
   std::vector< std::vector< double > > allvEvIDBD1mu;
   std::vector< std::vector< double > > allvEdepBD1mu;
   std::vector< std::vector< double > > allvEvIDBD2mu;
   std::vector< std::vector< double > > allvEdepBD2mu;
   std::vector< std::vector< double > > allvEvIDSVmu;
   std::vector< std::vector< double > > allvEdepSVmu;

   // X-ray cascade 3 phi-z
   std::vector< std::vector< double > > allvEvIDSD1x3phiz;
   std::vector< std::vector< double > > allvEdepSD1x3phiz;
   std::vector< std::vector< double > > allvEvIDSD2x3phiz;
   std::vector< std::vector< double > > allvEdepSD2x3phiz;
   std::vector< std::vector< double > > allvEvIDSD3x3phiz;
   std::vector< std::vector< double > > allvEdepSD3x3phiz;
   std::vector< std::vector< double > > allvEvIDSDS1x3phiz;
   std::vector< std::vector< double > > allvEdepSDS1x3phiz;
   std::vector< std::vector< double > > allvEvIDSDS2x3phiz;
   std::vector< std::vector< double > > allvEdepSDS2x3phiz;
   std::vector< std::vector< double > > allvEvIDBD1x3phiz;
   std::vector< std::vector< double > > allvEdepBD1x3phiz;
   std::vector< std::vector< double > > allvEvIDBD2x3phiz;
   std::vector< std::vector< double > > allvEdepBD2x3phiz;
   std::vector< std::vector< double > > allvEvIDSVx3phiz;
   std::vector< std::vector< double > > allvEdepSVx3phiz;

   // X-ray cascade 2 phi-z
   std::vector< std::vector< double > > allvEvIDSD1x2phiz;
   std::vector< std::vector< double > > allvEdepSD1x2phiz;
   std::vector< std::vector< double > > allvEvIDSD2x2phiz;
   std::vector< std::vector< double > > allvEdepSD2x2phiz;
   std::vector< std::vector< double > > allvEvIDSD3x2phiz;
   std::vector< std::vector< double > > allvEdepSD3x2phiz;
   std::vector< std::vector< double > > allvEvIDSDS1x2phiz;
   std::vector< std::vector< double > > allvEdepSDS1x2phiz;
   std::vector< std::vector< double > > allvEvIDSDS2x2phiz;
   std::vector< std::vector< double > > allvEdepSDS2x2phiz;
   std::vector< std::vector< double > > allvEvIDBD1x2phiz;
   std::vector< std::vector< double > > allvEdepBD1x2phiz;
   std::vector< std::vector< double > > allvEvIDBD2x2phiz;
   std::vector< std::vector< double > > allvEdepBD2x2phiz;
   std::vector< std::vector< double > > allvEvIDSVx2phiz;
   std::vector< std::vector< double > > allvEdepSVx2phiz;

   // X-ray cascade phi-z
   std::vector< std::vector< double > > allvEvIDSD1xphiz;
   std::vector< std::vector< double > > allvEdepSD1xphiz;
   std::vector< std::vector< double > > allvEvIDSD2xphiz;
   std::vector< std::vector< double > > allvEdepSD2xphiz;
   std::vector< std::vector< double > > allvEvIDSD3xphiz;
   std::vector< std::vector< double > > allvEdepSD3xphiz;
   std::vector< std::vector< double > > allvEvIDSDS1xphiz;
   std::vector< std::vector< double > > allvEdepSDS1xphiz;
   std::vector< std::vector< double > > allvEvIDSDS2xphiz;
   std::vector< std::vector< double > > allvEdepSDS2xphiz;
   std::vector< std::vector< double > > allvEvIDBD1xphiz;
   std::vector< std::vector< double > > allvEdepBD1xphiz;
   std::vector< std::vector< double > > allvEvIDBD2xphiz;
   std::vector< std::vector< double > > allvEdepBD2xphiz;
   std::vector< std::vector< double > > allvEvIDSVxphiz;
   std::vector< std::vector< double > > allvEdepSVxphiz;

   // Mu-decay
   std::vector< std::vector< double > > allvEvIDSD1muphiz;
   std::vector< std::vector< double > > allvEdepSD1muphiz;
   std::vector< std::vector< double > > allvEvIDSD2muphiz;
   std::vector< std::vector< double > > allvEdepSD2muphiz;
   std::vector< std::vector< double > > allvEvIDSD3muphiz;
   std::vector< std::vector< double > > allvEdepSD3muphiz;
   std::vector< std::vector< double > > allvEvIDSDS1muphiz;
   std::vector< std::vector< double > > allvEdepSDS1muphiz;
   std::vector< std::vector< double > > allvEvIDSDS2muphiz;
   std::vector< std::vector< double > > allvEdepSDS2muphiz;
   std::vector< std::vector< double > > allvEvIDBD1muphiz;
   std::vector< std::vector< double > > allvEdepBD1muphiz;
   std::vector< std::vector< double > > allvEvIDBD2muphiz;
   std::vector< std::vector< double > > allvEdepBD2muphiz;
   std::vector< std::vector< double > > allvEvIDSVmuphiz;
   std::vector< std::vector< double > > allvEdepSVmuphiz;




   float Ethr;
   int counterXX = 1e5;
   int counteree = 1e5;
   int XXrayx3 = 0; // X-rays i-fied as X-rays
   int Xelecx3 = 0; // X-rays i-fied as electrons
   int XXrayx2 = 0;
   int Xelecx2 = 0;
   int XXray = 0;
   int Xelec = 0;
   int XXrayx3phiz = 0;
   int Xelecx3phiz = 0;
   int XXrayx2phiz = 0;
   int Xelecx2phiz = 0;
   int XXrayphiz = 0;
   int Xelecphiz = 0;
   int eXray = 0; // Electrons i-fied as X-rays
   int eelec = 0; // Electrons i-fied as electrons
   int eXrayphiz = 0;
   int eelecphiz = 0;	   
   	   
   Ethrmu[0] = 0;
   for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;


   //-------------------------------------------------------------------
   //                           Reading
   //-------------------------------------------------------------------
		   
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m------------------- X-ray cascade ------------------------\033[0m" << std::endl;
   std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


   for (int k=0; k<((Xfiles.size())/48); k++) {
			  
      // SciD1 x3
	  std::ifstream x3fSciD1(TString(Xfiles[k*48]));
	  std::vector<double> vEvIDSD1x3;
	  std::vector<double> vEdepSD1x3;
			  
	  while (!x3fSciD1.eof()) {
	     double EvIDSD1, EdepSD1;
		 x3fSciD1 >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1x3.push_back(EvIDSD1);
		 vEdepSD1x3.push_back(EdepSD1);
	  }
	  vEvIDSD1x3.pop_back(); vEdepSD1x3.pop_back();
	  vEvIDSD1x3.pop_back(); vEdepSD1x3.pop_back();
			  
	  x3fSciD1.close();
	  allvEvIDSD1x3.push_back(vEvIDSD1x3);
	  allvEdepSD1x3.push_back(vEdepSD1x3);


	  // SciD2 x3
	  std::ifstream x3fSciD2(TString(Xfiles[(k*48)+1]));
	  std::vector<double> vEvIDSD2x3;
	  std::vector<double> vEdepSD2x3;
			  
	  while (!x3fSciD2.eof()) {
	     double EvIDSD2, EdepSD2;
		 x3fSciD2 >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2x3.push_back(EvIDSD2);
		 vEdepSD2x3.push_back(EdepSD2);
	  }
	  vEvIDSD2x3.pop_back(); vEdepSD2x3.pop_back();
	  vEvIDSD2x3.pop_back(); vEdepSD2x3.pop_back();
			  
	  x3fSciD2.close();
	  allvEvIDSD2x3.push_back(vEvIDSD2x3);
	  allvEdepSD2x3.push_back(vEdepSD2x3);


	  // SciD3 x3
	  std::ifstream x3fSciD3(TString(Xfiles[(k*48)+2]));
	  std::vector<double> vEvIDSD3x3;
	  std::vector<double> vEdepSD3x3;
			  
	  while (!x3fSciD3.eof()) {
	     double EvIDSD3, EdepSD3;
		 x3fSciD3 >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3x3.push_back(EvIDSD3);
		 vEdepSD3x3.push_back(EdepSD3);
	  }
	  vEvIDSD3x3.pop_back(); vEdepSD3x3.pop_back();
	  vEvIDSD3x3.pop_back(); vEdepSD3x3.pop_back();
			  
	  x3fSciD3.close();
	  allvEvIDSD3x3.push_back(vEvIDSD3x3);
	  allvEdepSD3x3.push_back(vEdepSD3x3);
			  
			  
	  // SciDS1 x3
	  std::ifstream x3fSciDS1(TString(Xfiles[(k*48)+3]));
	  std::vector<double> vEvIDSDS1x3;
	  std::vector<double> vEdepSDS1x3;
			  
	  while (!x3fSciDS1.eof()) {
	     double EvIDSDS1, EdepSDS1;
		 x3fSciDS1 >> EvIDSDS1 >> EdepSDS1;
		 vEvIDSDS1x3.push_back(EvIDSDS1);
		 vEdepSDS1x3.push_back(EdepSDS1);
	  }
	  vEvIDSDS1x3.pop_back(); vEdepSDS1x3.pop_back();
	  vEvIDSDS1x3.pop_back(); vEdepSDS1x3.pop_back();
			  
	  x3fSciDS1.close();
	  allvEvIDSDS1x3.push_back(vEvIDSDS1x3);
	  allvEdepSDS1x3.push_back(vEdepSDS1x3);


	  // SciDS2 x3
	  std::ifstream x3fSciDS2(TString(Xfiles[(k*48)+4]));
	  std::vector<double> vEvIDSDS2x3;
	  std::vector<double> vEdepSDS2x3;
			  
	  while (!x3fSciDS2.eof()) {
	     double EvIDSDS2, EdepSDS2;
		 x3fSciDS2 >> EvIDSDS2 >> EdepSDS2;
		 vEvIDSDS2x3.push_back(EvIDSDS2);
		 vEdepSDS2x3.push_back(EdepSDS2);
	  }
	  vEvIDSDS2x3.pop_back(); vEdepSDS2x3.pop_back();
	  vEvIDSDS2x3.pop_back(); vEdepSDS2x3.pop_back();
			  
	  x3fSciDS2.close();
	  allvEvIDSDS2x3.push_back(vEvIDSDS2x3);
	  allvEdepSDS2x3.push_back(vEdepSDS2x3);


	  // BGOD1 x3
	  std::ifstream x3fBGOD1(TString(Xfiles[(k*48)+5]));
	  std::vector<double> vEvIDBD1x3;
	  std::vector<double> vEdepBD1x3;
			  
	  while (!x3fBGOD1.eof()) {
	     double EvIDBD1, EdepBD1;
		 x3fBGOD1 >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1x3.push_back(EvIDBD1);
		 vEdepBD1x3.push_back(EdepBD1);
	  }
	  vEvIDBD1x3.pop_back(); vEdepBD1x3.pop_back();
	  vEvIDBD1x3.pop_back(); vEdepBD1x3.pop_back();
			  
	  x3fBGOD1.close();
	  allvEvIDBD1x3.push_back(vEvIDBD1x3);
	  allvEdepBD1x3.push_back(vEdepBD1x3);


	  // BGOD2 x3
	  std::ifstream x3fBGOD2(TString(Xfiles[(k*48)+6]));
	  std::vector<double> vEvIDBD2x3;
	  std::vector<double> vEdepBD2x3;
			  
	  while (!x3fBGOD2.eof()) {
	     double EvIDBD2, EdepBD2;
		 x3fBGOD2 >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2x3.push_back(EvIDBD2);
		 vEdepBD2x3.push_back(EdepBD2);
	  }
	  vEvIDBD2x3.pop_back(); vEdepBD2x3.pop_back();
	  vEvIDBD2x3.pop_back(); vEdepBD2x3.pop_back();
			  
	  x3fBGOD2.close();
	  allvEvIDBD2x3.push_back(vEvIDBD2x3);
	  allvEdepBD2x3.push_back(vEdepBD2x3);


	  // SciVeto x3
	  std::ifstream x3fSciVeto(TString(Xfiles[(k*48)+7]));
	  std::vector<double> vEvIDSVx3;
	  std::vector<double> vEdepSVx3;
			  
	  while (!x3fSciVeto.eof()) {
	     double EvIDSV, EdepSV;
		 x3fSciVeto >> EvIDSV >> EdepSV;
		 vEvIDSVx3.push_back(EvIDSV);
		 vEdepSVx3.push_back(EdepSV);
	  }
	  vEvIDSVx3.pop_back(); vEdepSVx3.pop_back();
	  vEvIDSVx3.pop_back(); vEdepSVx3.pop_back();
			  
	  x3fSciVeto.close();
	  allvEvIDSVx3.push_back(vEvIDSVx3);
	  allvEdepSVx3.push_back(vEdepSVx3);


      // SciD1 x2
	  std::ifstream x2fSciD1(TString(Xfiles[(k*48)+8]));
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


	  // SciD2 x2
	  std::ifstream x2fSciD2(TString(Xfiles[(k*48)+9]));
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


	  // SciD3 x2
	  std::ifstream x2fSciD3(TString(Xfiles[(k*48)+10]));
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
			  
			  
	  // SciDS1 x2
	  std::ifstream x2fSciDS1(TString(Xfiles[(k*48)+11]));
	  std::vector<double> vEvIDSDS1x2;
	  std::vector<double> vEdepSDS1x2;
			  
	  while (!x2fSciDS1.eof()) {
	     double EvIDSDS1, EdepSDS1;
		 x2fSciDS1 >> EvIDSDS1 >> EdepSDS1;
		 vEvIDSDS1x2.push_back(EvIDSDS1);
		 vEdepSDS1x2.push_back(EdepSDS1);
	  }
	  vEvIDSDS1x2.pop_back(); vEdepSDS1x2.pop_back();
	  vEvIDSDS1x2.pop_back(); vEdepSDS1x2.pop_back();
			  
	  x2fSciDS1.close();
	  allvEvIDSDS1x2.push_back(vEvIDSDS1x2);
	  allvEdepSDS1x2.push_back(vEdepSDS1x2);


	  // SciDS2 x2
	  std::ifstream x2fSciDS2(TString(Xfiles[(k*48)+12]));
	  std::vector<double> vEvIDSDS2x2;
	  std::vector<double> vEdepSDS2x2;
			  
	  while (!x2fSciDS2.eof()) {
	     double EvIDSDS2, EdepSDS2;
		 x2fSciDS2 >> EvIDSDS2 >> EdepSDS2;
		 vEvIDSDS2x2.push_back(EvIDSDS2);
		 vEdepSDS2x2.push_back(EdepSDS2);
	  }
	  vEvIDSDS2x2.pop_back(); vEdepSDS2x2.pop_back();
	  vEvIDSDS2x2.pop_back(); vEdepSDS2x2.pop_back();
			  
	  x2fSciDS2.close();
	  allvEvIDSDS2x2.push_back(vEvIDSDS2x2);
	  allvEdepSDS2x2.push_back(vEdepSDS2x2);


	  // BGOD1 x2
	  std::ifstream x2fBGOD1(TString(Xfiles[(k*48)+13]));
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


	  // BGOD2 x2
	  std::ifstream x2fBGOD2(TString(Xfiles[(k*48)+14]));
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


	  // SciVeto x2
	  std::ifstream x2fSciVeto(TString(Xfiles[(k*48)+15]));
	  std::vector<double> vEvIDSVx2;
	  std::vector<double> vEdepSVx2;
			  
	  while (!x2fSciVeto.eof()) {
	     double EvIDSV, EdepSV;
		 x2fSciVeto >> EvIDSV >> EdepSV;
		 vEvIDSVx2.push_back(EvIDSV);
		 vEdepSVx2.push_back(EdepSV);
	  }
	  vEvIDSVx2.pop_back(); vEdepSVx2.pop_back();
	  vEvIDSVx2.pop_back(); vEdepSVx2.pop_back();
			  
	  x2fSciVeto.close();
	  allvEvIDSVx2.push_back(vEvIDSVx2);
	  allvEdepSVx2.push_back(vEdepSVx2);


      // SciD1
	  std::ifstream xfSciD1(TString(Xfiles[(k*48)+16]));
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
	  std::ifstream xfSciD2(TString(Xfiles[(k*48)+17]));
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
	  std::ifstream xfSciD3(TString(Xfiles[(k*48)+18]));
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
			  
			  
	  // SciDS1
	  std::ifstream xfSciDS1(TString(Xfiles[(k*48)+19]));
	  std::vector<double> vEvIDSDS1x;
	  std::vector<double> vEdepSDS1x;
			  
	  while (!xfSciDS1.eof()) {
	     double EvIDSDS1, EdepSDS1;
		 xfSciDS1 >> EvIDSDS1 >> EdepSDS1;
		 vEvIDSDS1x.push_back(EvIDSDS1);
		 vEdepSDS1x.push_back(EdepSDS1);
	  }
	  vEvIDSDS1x.pop_back(); vEdepSDS1x.pop_back();
	  vEvIDSDS1x.pop_back(); vEdepSDS1x.pop_back();
			  
	  xfSciDS1.close();
	  allvEvIDSDS1x.push_back(vEvIDSDS1x);
	  allvEdepSDS1x.push_back(vEdepSDS1x);


	  // SciDS2
	  std::ifstream xfSciDS2(TString(Xfiles[(k*48)+20]));
	  std::vector<double> vEvIDSDS2x;
	  std::vector<double> vEdepSDS2x;
			  
	  while (!xfSciDS2.eof()) {
	     double EvIDSDS2, EdepSDS2;
		 xfSciDS2 >> EvIDSDS2 >> EdepSDS2;
		 vEvIDSDS2x.push_back(EvIDSDS2);
		 vEdepSDS2x.push_back(EdepSDS2);
	  }
	  vEvIDSDS2x.pop_back(); vEdepSDS2x.pop_back();
	  vEvIDSDS2x.pop_back(); vEdepSDS2x.pop_back();
			  
	  xfSciDS2.close();
	  allvEvIDSDS2x.push_back(vEvIDSDS2x);
	  allvEdepSDS2x.push_back(vEdepSDS2x);


	  // BGOD1
	  std::ifstream xfBGOD1(TString(Xfiles[(k*48)+21]));
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
	  std::ifstream xfBGOD2(TString(Xfiles[(k*48)+22]));
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


	  // SciVeto
	  std::ifstream xfSciVeto(TString(Xfiles[(k*48)+23]));
	  std::vector<double> vEvIDSVx;
	  std::vector<double> vEdepSVx;
			  
	  while (!xfSciVeto.eof()) {
	     double EvIDSV, EdepSV;
		 xfSciVeto >> EvIDSV >> EdepSV;
		 vEvIDSVx.push_back(EvIDSV);
		 vEdepSVx.push_back(EdepSV);
	  }
	  vEvIDSVx.pop_back(); vEdepSVx.pop_back();
	  vEvIDSVx.pop_back(); vEdepSVx.pop_back();
			  
	  xfSciVeto.close();
	  allvEvIDSVx.push_back(vEvIDSVx);
	  allvEdepSVx.push_back(vEdepSVx);


      // SciD1 x3 phi-z
	  std::ifstream x3fSciD1phiz(TString(Xfiles[(k*48)+24]));
	  std::vector<double> vEvIDSD1x3phiz;
	  std::vector<double> vEdepSD1x3phiz;
			  
	  while (!x3fSciD1phiz.eof()) {
	     double EvIDSD1, EdepSD1;
		 x3fSciD1phiz >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1x3phiz.push_back(EvIDSD1);
		 vEdepSD1x3phiz.push_back(EdepSD1);
	  }
	  vEvIDSD1x3phiz.pop_back(); vEdepSD1x3phiz.pop_back();
	  vEvIDSD1x3phiz.pop_back(); vEdepSD1x3phiz.pop_back();
			  
	  x3fSciD1phiz.close();
	  allvEvIDSD1x3phiz.push_back(vEvIDSD1x3phiz);
	  allvEdepSD1x3phiz.push_back(vEdepSD1x3phiz);


	  // SciD2 x3 phi-z
	  std::ifstream x3fSciD2phiz(TString(Xfiles[(k*48)+25]));
	  std::vector<double> vEvIDSD2x3phiz;
	  std::vector<double> vEdepSD2x3phiz;
			  
	  while (!x3fSciD2phiz.eof()) {
	     double EvIDSD2, EdepSD2;
		 x3fSciD2phiz >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2x3phiz.push_back(EvIDSD2);
		 vEdepSD2x3phiz.push_back(EdepSD2);
	  }
	  vEvIDSD2x3phiz.pop_back(); vEdepSD2x3phiz.pop_back();
	  vEvIDSD2x3phiz.pop_back(); vEdepSD2x3phiz.pop_back();
			  
	  x3fSciD2.close();
	  allvEvIDSD2x3phiz.push_back(vEvIDSD2x3phiz);
	  allvEdepSD2x3phiz.push_back(vEdepSD2x3phiz);


	  // SciD3 x3 phi-z
	  std::ifstream x3fSciD3phiz(TString(Xfiles[(k*48)+26]));
	  std::vector<double> vEvIDSD3x3phiz;
	  std::vector<double> vEdepSD3x3phiz;
			  
	  while (!x3fSciD3phiz.eof()) {
	     double EvIDSD3, EdepSD3;
		 x3fSciD3phiz >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3x3phiz.push_back(EvIDSD3);
		 vEdepSD3x3phiz.push_back(EdepSD3);
	  }
	  vEvIDSD3x3phiz.pop_back(); vEdepSD3x3phiz.pop_back();
	  vEvIDSD3x3phiz.pop_back(); vEdepSD3x3phiz.pop_back();
			  
	  x3fSciD3phiz.close();
	  allvEvIDSD3x3phiz.push_back(vEvIDSD3x3phiz);
	  allvEdepSD3x3phiz.push_back(vEdepSD3x3phiz);
			  
			  
	  // SciDS1 x3 phi-z
	  std::ifstream x3fSciDS1phiz(TString(Xfiles[(k*48)+27]));
	  std::vector<double> vEvIDSDS1x3phiz;
	  std::vector<double> vEdepSDS1x3phiz;
			  
	  while (!x3fSciDS1phiz.eof()) {
	     double EvIDSDS1, EdepSDS1;
		 x3fSciDS1phiz >> EvIDSDS1 >> EdepSDS1;
		 vEvIDSDS1x3phiz.push_back(EvIDSDS1);
		 vEdepSDS1x3phiz.push_back(EdepSDS1);
	  }
	  vEvIDSDS1x3phiz.pop_back(); vEdepSDS1x3phiz.pop_back();
	  vEvIDSDS1x3phiz.pop_back(); vEdepSDS1x3phiz.pop_back();
			  
	  x3fSciDS1phiz.close();
	  allvEvIDSDS1x3phiz.push_back(vEvIDSDS1x3phiz);
	  allvEdepSDS1x3phiz.push_back(vEdepSDS1x3phiz);


	  // SciDS2 x3 phi-z
	  std::ifstream x3fSciDS2phiz(TString(Xfiles[(k*48)+28]));
	  std::vector<double> vEvIDSDS2x3phiz;
	  std::vector<double> vEdepSDS2x3phiz;
			  
	  while (!x3fSciDS2phiz.eof()) {
	     double EvIDSDS2, EdepSDS2;
		 x3fSciDS2phiz >> EvIDSDS2 >> EdepSDS2;
		 vEvIDSDS2x3phiz.push_back(EvIDSDS2);
		 vEdepSDS2x3phiz.push_back(EdepSDS2);
	  }
	  vEvIDSDS2x3phiz.pop_back(); vEdepSDS2x3phiz.pop_back();
	  vEvIDSDS2x3phiz.pop_back(); vEdepSDS2x3phiz.pop_back();
			  
	  x3fSciDS2phiz.close();
	  allvEvIDSDS2x3phiz.push_back(vEvIDSDS2x3phiz);
	  allvEdepSDS2x3phiz.push_back(vEdepSDS2x3phiz);


	  // BGOD1 x3 phi-z
	  std::ifstream x3fBGOD1phiz(TString(Xfiles[(k*48)+29]));
	  std::vector<double> vEvIDBD1x3phiz;
	  std::vector<double> vEdepBD1x3phiz;
			  
	  while (!x3fBGOD1phiz.eof()) {
	     double EvIDBD1, EdepBD1;
		 x3fBGOD1phiz >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1x3phiz.push_back(EvIDBD1);
		 vEdepBD1x3phiz.push_back(EdepBD1);
	  }
	  vEvIDBD1x3phiz.pop_back(); vEdepBD1x3phiz.pop_back();
	  vEvIDBD1x3phiz.pop_back(); vEdepBD1x3phiz.pop_back();
			  
	  x3fBGOD1phiz.close();
	  allvEvIDBD1x3phiz.push_back(vEvIDBD1x3phiz);
	  allvEdepBD1x3phiz.push_back(vEdepBD1x3phiz);


	  // BGOD2 x3 phi-z
	  std::ifstream x3fBGOD2phiz(TString(Xfiles[(k*48)+30]));
	  std::vector<double> vEvIDBD2x3phiz;
	  std::vector<double> vEdepBD2x3phiz;
			  
	  while (!x3fBGOD2phiz.eof()) {
	     double EvIDBD2, EdepBD2;
		 x3fBGOD2phiz >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2x3phiz.push_back(EvIDBD2);
		 vEdepBD2x3phiz.push_back(EdepBD2);
	  }
	  vEvIDBD2x3phiz.pop_back(); vEdepBD2x3phiz.pop_back();
	  vEvIDBD2x3phiz.pop_back(); vEdepBD2x3phiz.pop_back();
			  
	  x3fBGOD2phiz.close();
	  allvEvIDBD2x3phiz.push_back(vEvIDBD2x3phiz);
	  allvEdepBD2x3phiz.push_back(vEdepBD2x3phiz);


	  // SciVeto x3 phi-z
	  std::ifstream x3fSciVetophiz(TString(Xfiles[(k*48)+31]));
	  std::vector<double> vEvIDSVx3phiz;
	  std::vector<double> vEdepSVx3phiz;
			  
	  while (!x3fSciVetophiz.eof()) {
	     double EvIDSV, EdepSV;
		 x3fSciVetophiz >> EvIDSV >> EdepSV;
		 vEvIDSVx3phiz.push_back(EvIDSV);
		 vEdepSVx3phiz.push_back(EdepSV);
	  }
	  vEvIDSVx3phiz.pop_back(); vEdepSVx3phiz.pop_back();
	  vEvIDSVx3phiz.pop_back(); vEdepSVx3phiz.pop_back();
			  
	  x3fSciVetophiz.close();
	  allvEvIDSVx3phiz.push_back(vEvIDSVx3phiz);
	  allvEdepSVx3phiz.push_back(vEdepSVx3phiz);


      // SciD1 x2 phi-z
	  std::ifstream x2fSciD1phiz(TString(Xfiles[(k*48)+32]));
	  std::vector<double> vEvIDSD1x2phiz;
	  std::vector<double> vEdepSD1x2phiz;
			  
	  while (!x2fSciD1phiz.eof()) {
	     double EvIDSD1, EdepSD1;
		 x2fSciD1phiz >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1x2phiz.push_back(EvIDSD1);
		 vEdepSD1x2phiz.push_back(EdepSD1);
	  }
	  vEvIDSD1x2phiz.pop_back(); vEdepSD1x2phiz.pop_back();
	  vEvIDSD1x2phiz.pop_back(); vEdepSD1x2phiz.pop_back();
			  
	  x2fSciD1phiz.close();
	  allvEvIDSD1x2phiz.push_back(vEvIDSD1x2phiz);
	  allvEdepSD1x2phiz.push_back(vEdepSD1x2phiz);


	  // SciD2 x2 phi-z
	  std::ifstream x2fSciD2phiz(TString(Xfiles[(k*48)+33]));
	  std::vector<double> vEvIDSD2x2phiz;
	  std::vector<double> vEdepSD2x2phiz;
			  
	  while (!x2fSciD2phiz.eof()) {
	     double EvIDSD2, EdepSD2;
		 x2fSciD2phiz >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2x2phiz.push_back(EvIDSD2);
		 vEdepSD2x2phiz.push_back(EdepSD2);
	  }
	  vEvIDSD2x2phiz.pop_back(); vEdepSD2x2phiz.pop_back();
	  vEvIDSD2x2phiz.pop_back(); vEdepSD2x2phiz.pop_back();
			  
	  x2fSciD2phiz.close();
	  allvEvIDSD2x2phiz.push_back(vEvIDSD2x2phiz);
	  allvEdepSD2x2phiz.push_back(vEdepSD2x2phiz);


	  // SciD3 x2 phi-z
	  std::ifstream x2fSciD3phiz(TString(Xfiles[(k*48)+34]));
	  std::vector<double> vEvIDSD3x2phiz;
	  std::vector<double> vEdepSD3x2phiz;
			  
	  while (!x2fSciD3phiz.eof()) {
	     double EvIDSD3, EdepSD3;
		 x2fSciD3phiz >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3x2phiz.push_back(EvIDSD3);
		 vEdepSD3x2phiz.push_back(EdepSD3);
	  }
	  vEvIDSD3x2phiz.pop_back(); vEdepSD3x2phiz.pop_back();
	  vEvIDSD3x2phiz.pop_back(); vEdepSD3x2phiz.pop_back();
			  
	  x2fSciD3phiz.close();
	  allvEvIDSD3x2phiz.push_back(vEvIDSD3x2phiz);
	  allvEdepSD3x2phiz.push_back(vEdepSD3x2phiz);
			  
			  
	  // SciDS1 x2 phi-z
	  std::ifstream x2fSciDS1phiz(TString(Xfiles[(k*48)+35]));
	  std::vector<double> vEvIDSDS1x2phiz;
	  std::vector<double> vEdepSDS1x2phiz;
			  
	  while (!x2fSciDS1phiz.eof()) {
	     double EvIDSDS1, EdepSDS1;
		 x2fSciDS1phiz >> EvIDSDS1 >> EdepSDS1;
		 vEvIDSDS1x2phiz.push_back(EvIDSDS1);
		 vEdepSDS1x2phiz.push_back(EdepSDS1);
	  }
	  vEvIDSDS1x2phiz.pop_back(); vEdepSDS1x2phiz.pop_back();
	  vEvIDSDS1x2phiz.pop_back(); vEdepSDS1x2phiz.pop_back();
			  
	  x2fSciDS1phiz.close();
	  allvEvIDSDS1x2phiz.push_back(vEvIDSDS1x2phiz);
	  allvEdepSDS1x2phiz.push_back(vEdepSDS1x2phiz);


	  // SciDS2 x2 phi-z
	  std::ifstream x2fSciDS2phiz(TString(Xfiles[(k*48)+36]));
	  std::vector<double> vEvIDSDS2x2phiz;
	  std::vector<double> vEdepSDS2x2phiz;
			  
	  while (!x2fSciDS2phiz.eof()) {
	     double EvIDSDS2phiz, EdepSDS2phiz;
		 x2fSciDS2phiz >> EvIDSDS2 >> EdepSDS2;
		 vEvIDSDS2x2phiz.push_back(EvIDSDS2);
		 vEdepSDS2x2phiz.push_back(EdepSDS2);
	  }
	  vEvIDSDS2x2phiz.pop_back(); vEdepSDS2x2phiz.pop_back();
	  vEvIDSDS2x2phiz.pop_back(); vEdepSDS2x2phiz.pop_back();
			  
	  x2fSciDS2phiz.close();
	  allvEvIDSDS2x2phiz.push_back(vEvIDSDS2x2phiz);
	  allvEdepSDS2x2phiz.push_back(vEdepSDS2x2phiz);


	  // BGOD1 x2 phi-z
	  std::ifstream x2fBGOD1phiz(TString(Xfiles[(k*48)+37]));
	  std::vector<double> vEvIDBD1x2phiz;
	  std::vector<double> vEdepBD1x2phiz;
			  
	  while (!x2fBGOD1phiz.eof()) {
	     double EvIDBD1, EdepBD1;
		 x2fBGOD1phiz >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1x2phiz.push_back(EvIDBD1);
		 vEdepBD1x2phiz.push_back(EdepBD1);
	  }
	  vEvIDBD1x2phiz.pop_back(); vEdepBD1x2phiz.pop_back();
	  vEvIDBD1x2phiz.pop_back(); vEdepBD1x2phiz.pop_back();
			  
	  x2fBGOD1phiz.close();
	  allvEvIDBD1x2phiz.push_back(vEvIDBD1x2phiz);
	  allvEdepBD1x2phiz.push_back(vEdepBD1x2phiz);


	  // BGOD2 x2 phi-z
	  std::ifstream x2fBGOD2phiz(TString(Xfiles[(k*48)+38]));
	  std::vector<double> vEvIDBD2x2phiz;
	  std::vector<double> vEdepBD2x2phiz;
			  
	  while (!x2fBGOD2phiz.eof()) {
	     double EvIDBD2, EdepBD2;
		 x2fBGOD2phiz >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2x2phiz.push_back(EvIDBD2);
		 vEdepBD2x2phiz.push_back(EdepBD2);
	  }
	  vEvIDBD2x2phiz.pop_back(); vEdepBD2x2phiz.pop_back();
	  vEvIDBD2x2phiz.pop_back(); vEdepBD2x2phiz.pop_back();
			  
	  x2fBGOD2phiz.close();
	  allvEvIDBD2x2phiz.push_back(vEvIDBD2x2phiz);
	  allvEdepBD2x2phiz.push_back(vEdepBD2x2phiz);


	  // SciVeto x2 phi-z
	  std::ifstream x2fSciVetophiz(TString(Xfiles[(k*48)+39]));
	  std::vector<double> vEvIDSVx2phiz;
	  std::vector<double> vEdepSVx2phiz;
			  
	  while (!x2fSciVetophiz.eof()) {
	     double EvIDSV, EdepSV;
		 x2fSciVetophiz >> EvIDSV >> EdepSV;
		 vEvIDSVx2phiz.push_back(EvIDSV);
		 vEdepSVx2phiz.push_back(EdepSV);
	  }
	  vEvIDSVx2phiz.pop_back(); vEdepSVx2phiz.pop_back();
	  vEvIDSVx2phiz.pop_back(); vEdepSVx2phiz.pop_back();
			  
	  x2fSciVetophiz.close();
	  allvEvIDSVx2phiz.push_back(vEvIDSVx2phiz);
	  allvEdepSVx2phiz.push_back(vEdepSVx2phiz);


      // SciD1 phi-z
	  std::ifstream xfSciD1phiz(TString(Xfiles[(k*48)+40]));
	  std::vector<double> vEvIDSD1xphiz;
	  std::vector<double> vEdepSD1xphiz;
			  
	  while (!xfSciD1phiz.eof()) {
	     double EvIDSD1, EdepSD1;
		 xfSciD1phiz >> EvIDSD1 >> EdepSD1;
		 vEvIDSD1xphiz.push_back(EvIDSD1);
		 vEdepSD1xphiz.push_back(EdepSD1);
	  }
	  vEvIDSD1xphiz.pop_back(); vEdepSD1xphiz.pop_back();
	  vEvIDSD1xphiz.pop_back(); vEdepSD1xphiz.pop_back();
			  
	  xfSciD1phiz.close();
	  allvEvIDSD1xphiz.push_back(vEvIDSD1xphiz);
	  allvEdepSD1xphiz.push_back(vEdepSD1xphiz);


	  // SciD2 phi-z
	  std::ifstream xfSciD2phiz(TString(Xfiles[(k*48)+41]));
	  std::vector<double> vEvIDSD2xphiz;
	  std::vector<double> vEdepSD2xphiz;
			  
	  while (!xfSciD2phiz.eof()) {
	     double EvIDSD2, EdepSD2;
		 xfSciD2phiz >> EvIDSD2 >> EdepSD2;
		 vEvIDSD2xphiz.push_back(EvIDSD2);
		 vEdepSD2xphiz.push_back(EdepSD2);
	  }
	  vEvIDSD2xphiz.pop_back(); vEdepSD2xphiz.pop_back();
	  vEvIDSD2xphiz.pop_back(); vEdepSD2xphiz.pop_back();
			  
	  xfSciD2phiz.close();
	  allvEvIDSD2xphiz.push_back(vEvIDSD2xphiz);
	  allvEdepSD2xphiz.push_back(vEdepSD2xphiz);


	  // SciD3 phi-z
	  std::ifstream xfSciD3phiz(TString(Xfiles[(k*48)+42]));
	  std::vector<double> vEvIDSD3xphiz;
	  std::vector<double> vEdepSD3xphiz;
			  
	  while (!xfSciD3phiz.eof()) {
	     double EvIDSD3, EdepSD3;
		 xfSciD3phiz >> EvIDSD3 >> EdepSD3;
		 vEvIDSD3xphiz.push_back(EvIDSD3);
		 vEdepSD3xphiz.push_back(EdepSD3);
	  }
	  vEvIDSD3xphiz.pop_back(); vEdepSD3xphiz.pop_back();
	  vEvIDSD3xphiz.pop_back(); vEdepSD3xphiz.pop_back();
			  
	  xfSciD3phiz.close();
	  allvEvIDSD3xphiz.push_back(vEvIDSD3xphiz);
	  allvEdepSD3xphiz.push_back(vEdepSD3xphiz);
			  
			  
	  // SciDS1 phi-z
	  std::ifstream xfSciDS1phiz(TString(Xfiles[(k*48)+43]));
	  std::vector<double> vEvIDSDS1xphiz;
	  std::vector<double> vEdepSDS1xphiz;
			  
	  while (!xfSciDS1phiz.eof()) {
	     double EvIDSDS1, EdepSDS1;
		 xfSciDS1phiz >> EvIDSDS1 >> EdepSDS1;
		 vEvIDSDS1xphiz.push_back(EvIDSDS1);
		 vEdepSDS1xphiz.push_back(EdepSDS1);
	  }
	  vEvIDSDS1xphiz.pop_back(); vEdepSDS1xphiz.pop_back();
	  vEvIDSDS1xphiz.pop_back(); vEdepSDS1xphiz.pop_back();
			  
	  xfSciDS1phiz.close();
	  allvEvIDSDS1xphiz.push_back(vEvIDSDS1xphiz);
	  allvEdepSDS1xphiz.push_back(vEdepSDS1xphiz);


	  // SciDS2 phi-z 
	  std::ifstream xfSciDS2phiz(TString(Xfiles[(k*48)+44]));
	  std::vector<double> vEvIDSDS2xphiz;
	  std::vector<double> vEdepSDS2xphiz;
			  
	  while (!xfSciDS2phiz.eof()) {
	     double EvIDSDS2, EdepSDS2;
		 xfSciDS2phiz >> EvIDSDS2 >> EdepSDS2;
		 vEvIDSDS2xphiz.push_back(EvIDSDS2);
		 vEdepSDS2xphiz.push_back(EdepSDS2);
	  }
	  vEvIDSDS2xphiz.pop_back(); vEdepSDS2xphiz.pop_back();
	  vEvIDSDS2xphiz.pop_back(); vEdepSDS2xphiz.pop_back();
			  
	  xfSciDS2phiz.close();
	  allvEvIDSDS2xphiz.push_back(vEvIDSDS2xphiz);
	  allvEdepSDS2xphiz.push_back(vEdepSDS2xphiz);


	  // BGOD1 phi-z
	  std::ifstream xfBGOD1phiz(TString(Xfiles[(k*48)+45]));
	  std::vector<double> vEvIDBD1xphiz;
	  std::vector<double> vEdepBD1xphiz;
			  
	  while (!xfBGOD1phiz.eof()) {
	     double EvIDBD1, EdepBD1;
		 xfBGOD1phiz >> EvIDBD1 >> EdepBD1;
		 vEvIDBD1xphiz.push_back(EvIDBD1);
		 vEdepBD1xphiz.push_back(EdepBD1);
	  }
	  vEvIDBD1xphiz.pop_back(); vEdepBD1xphiz.pop_back();
	  vEvIDBD1xphiz.pop_back(); vEdepBD1xphiz.pop_back();
			  
	  xfBGOD1phiz.close();
	  allvEvIDBD1xphiz.push_back(vEvIDBD1xphiz);
	  allvEdepBD1xphiz.push_back(vEdepBD1xphiz);


	  // BGOD2 phi-z
	  std::ifstream xfBGOD2phiz(TString(Xfiles[(k*48)+46]));
	  std::vector<double> vEvIDBD2xphiz;
	  std::vector<double> vEdepBD2xphiz;
			  
	  while (!xfBGOD2phiz.eof()) {
	     double EvIDBD2, EdepBD2;
		 xfBGOD2phiz >> EvIDBD2 >> EdepBD2;
		 vEvIDBD2xphiz.push_back(EvIDBD2);
		 vEdepBD2xphiz.push_back(EdepBD2);
	  }
	  vEvIDBD2xphiz.pop_back(); vEdepBD2xphiz.pop_back();
	  vEvIDBD2xphiz.pop_back(); vEdepBD2xphiz.pop_back();
			  
	  xfBGOD2phiz.close();
	  allvEvIDBD2xphiz.push_back(vEvIDBD2xphiz);
	  allvEdepBD2xphiz.push_back(vEdepBD2xphiz);


	  // SciVeto phi-z
	  std::ifstream xfSciVetophiz(TString(Xfiles[(k*48)+47]));
	  std::vector<double> vEvIDSVxphiz;
	  std::vector<double> vEdepSVxphiz;
			  
	  while (!xfSciVetophiz.eof()) {
	     double EvIDSV, EdepSV;
		 xfSciVetophiz >> EvIDSV >> EdepSV;
		 vEvIDSVxphiz.push_back(EvIDSV);
		 vEdepSVxphiz.push_back(EdepSV);
	  }
	  
	  vEvIDSVxphiz.pop_back(); vEdepSVxphiz.pop_back();
	  vEvIDSVxphiz.pop_back(); vEdepSVxphiz.pop_back();
			  
	  xfSciVetophiz.close();
	  allvEvIDSVxphiz.push_back(vEvIDSVxphiz);
	  allvEdepSVxphiz.push_back(vEdepSVxphiz);


   }



   for (int k=0; k<((mufiles.size())/16); k++) {
   
      // SciD1mu
	  std::ifstream mufSciD1(TString(mufiles[k*16]));
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
	  std::ifstream mufSciD2(TString(mufiles[(k*16)+1]));
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
	  std::ifstream mufSciD3(TString(mufiles[(k*16)+2]));
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
			  
			  
	  // SciDS1mu
	  std::ifstream mufSciDS1(TString(mufiles[(k*16)+3]));
	  std::vector<double> vEvIDSDS1mu;
	  std::vector<double> vEdepSDS1mu;
			  
	  while (!mufSciDS1.eof()) {
	     double EvIDSDS1mu, EdepSDS1mu;
		 mufSciDS1 >> EvIDSDS1mu >> EdepSDS1mu;
		 vEvIDSDS1mu.push_back(EvIDSDS1mu);
		 vEdepSDS1mu.push_back(EdepSDS1mu);
	  }
	  vEvIDSDS1mu.pop_back(); vEdepSDS1mu.pop_back();
	  vEvIDSDS1mu.pop_back(); vEdepSDS1mu.pop_back();
			  
	  mufSciDS1.close();
	  allvEvIDSDS1mu.push_back(vEvIDSDS1mu);
	  allvEdepSDS1mu.push_back(vEdepSDS1mu);


	  // SciDS2mu
	  std::ifstream mufSciDS2(TString(mufiles[(k*16)+4]));
	  std::vector<double> vEvIDSDS2mu;
	  std::vector<double> vEdepSDS2mu;
			  
	  while (!mufSciDS2.eof()) {
	     double EvIDSDS2mu, EdepSDS2mu;
		 mufSciDS2 >> EvIDSDS2mu >> EdepSDS2mu;
		 vEvIDSDS2mu.push_back(EvIDSDS2mu);
		 vEdepSDS2mu.push_back(EdepSDS2mu);
	  }
	  vEvIDSDS2mu.pop_back(); vEdepSDS2mu.pop_back();
	  vEvIDSDS2mu.pop_back(); vEdepSDS2mu.pop_back();
			  
	  mufSciDS2.close();
	  allvEvIDSDS2mu.push_back(vEvIDSDS2mu);
	  allvEdepSDS2mu.push_back(vEdepSDS2mu);


	  // BGOD1mu
	  std::ifstream mufBGOD1(TString(mufiles[(k*16)+5]));
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
	  std::ifstream mufBGOD2(TString(mufiles[(k*16)+6]));
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


	  // SciVetomu
	  std::ifstream mufSciVeto(TString(mufiles[(k*16)+7]));
	  std::vector<double> vEvIDSVmu;
	  std::vector<double> vEdepSVmu;
			  
	  while (!mufSciVeto.eof()) {
	     double EvIDSVmu, EdepSVmu;
		 mufSciVeto >> EvIDSVmu >> EdepSVmu;
		 vEvIDSVmu.push_back(EvIDSVmu);
		 vEdepSVmu.push_back(EdepSVmu);
	  }
	  vEvIDSVmu.pop_back(); vEdepSVmu.pop_back();
	  vEvIDSVmu.pop_back(); vEdepSVmu.pop_back();
			  
	  mufSciVeto.close();
	  allvEvIDSVmu.push_back(vEvIDSVmu);
	  allvEdepSVmu.push_back(vEdepSVmu);


      // SciD1mu phi-z
	  std::ifstream mufSciD1phiz(TString(mufiles[(k*16)+8]));
	  std::vector<double> vEvIDSD1muphiz;
	  std::vector<double> vEdepSD1muphiz;
			  
	  while (!mufSciD1phiz.eof()) {
	     double EvIDSD1mu, EdepSD1mu;
		 mufSciD1phiz >> EvIDSD1mu >> EdepSD1mu;
		 vEvIDSD1muphiz.push_back(EvIDSD1mu);
		 vEdepSD1muphiz.push_back(EdepSD1mu);
	  }
	  vEvIDSD1muphiz.pop_back(); vEdepSD1muphiz.pop_back();
	  vEvIDSD1muphiz.pop_back(); vEdepSD1muphiz.pop_back();
			  
	  mufSciD1phiz.close();
	  allvEvIDSD1muphiz.push_back(vEvIDSD1muphiz);
	  allvEdepSD1muphiz.push_back(vEdepSD1muphiz);


	  // SciD2mu phi-z
	  std::ifstream mufSciD2phiz(TString(mufiles[(k*16)+9]));
	  std::vector<double> vEvIDSD2muphiz;
	  std::vector<double> vEdepSD2muphiz;
			  
	  while (!mufSciD2phiz.eof()) {
	     double EvIDSD2mu, EdepSD2mu;
		 mufSciD2phiz >> EvIDSD2mu >> EdepSD2mu;
		 vEvIDSD2muphiz.push_back(EvIDSD2mu);
		 vEdepSD2muphiz.push_back(EdepSD2mu);
	  }
	  vEvIDSD2muphiz.pop_back(); vEdepSD2muphiz.pop_back();
	  vEvIDSD2muphiz.pop_back(); vEdepSD2muphiz.pop_back();
			  
	  mufSciD2phiz.close();
	  allvEvIDSD2muphiz.push_back(vEvIDSD2muphiz);
	  allvEdepSD2muphiz.push_back(vEdepSD2muphiz);


	  // SciD3mu phi-z
	  std::ifstream mufSciD3phiz(TString(mufiles[(k*16)+10]));
	  std::vector<double> vEvIDSD3muphiz;
	  std::vector<double> vEdepSD3muphiz;
			  
	  while (!mufSciD3phiz.eof()) {
	     double EvIDSD3mu, EdepSD3mu;
		 mufSciD3phiz >> EvIDSD3mu >> EdepSD3mu;
		 vEvIDSD3muphiz.push_back(EvIDSD3mu);
		 vEdepSD3muphiz.push_back(EdepSD3mu);
	  }
	  vEvIDSD3muphiz.pop_back(); vEdepSD3muphiz.pop_back();
	  vEvIDSD3muphiz.pop_back(); vEdepSD3muphiz.pop_back();
			  
	  mufSciD3phiz.close();
	  allvEvIDSD3muphiz.push_back(vEvIDSD3muphiz);
	  allvEdepSD3muphiz.push_back(vEdepSD3muphiz);
			  
			  
	  // SciDS1mu phi-z
	  std::ifstream mufSciDS1phiz(TString(mufiles[(k*16)+11]));
	  std::vector<double> vEvIDSDS1muphiz;
	  std::vector<double> vEdepSDS1muphiz;
			  
	  while (!mufSciDS1phiz.eof()) {
	     double EvIDSDS1mu, EdepSDS1mu;
		 mufSciDS1phiz >> EvIDSDS1mu >> EdepSDS1mu;
		 vEvIDSDS1muphiz.push_back(EvIDSDS1mu);
		 vEdepSDS1muphiz.push_back(EdepSDS1mu);
	  }
	  vEvIDSDS1muphiz.pop_back(); vEdepSDS1muphiz.pop_back();
	  vEvIDSDS1muphiz.pop_back(); vEdepSDS1muphiz.pop_back();
			  
	  mufSciDS1phiz.close();
	  allvEvIDSDS1muphiz.push_back(vEvIDSDS1muphiz);
	  allvEdepSDS1muphiz.push_back(vEdepSDS1muphiz);


	  // SciDS2mu phi-z
	  std::ifstream mufSciDS2phiz(TString(mufiles[(k*16)+12]));
	  std::vector<double> vEvIDSDS2muphiz;
	  std::vector<double> vEdepSDS2muphiz;
			  
	  while (!mufSciDS2phiz.eof()) {
	     double EvIDSDS2mu, EdepSDS2mu;
		 mufSciDS2phiz >> EvIDSDS2mu >> EdepSDS2mu;
		 vEvIDSDS2muphiz.push_back(EvIDSDS2mu);
		 vEdepSDS2muphiz.push_back(EdepSDS2mu);
	  }
	  vEvIDSDS2muphiz.pop_back(); vEdepSDS2muphiz.pop_back();
	  vEvIDSDS2muphiz.pop_back(); vEdepSDS2muphiz.pop_back();
			  
	  mufSciDS2phiz.close();
	  allvEvIDSDS2muphiz.push_back(vEvIDSDS2muphiz);
	  allvEdepSDS2muphiz.push_back(vEdepSDS2muphiz);


	  // BGOD1mu phi-z
	  std::ifstream mufBGOD1phiz(TString(mufiles[(k*16)+13]));
	  std::vector<double> vEvIDBD1muphiz;
	  std::vector<double> vEdepBD1muphiz;
			  
	  while (!mufBGOD1phiz.eof()) {
	     double EvIDBD1mu, EdepBD1mu;
		 mufBGOD1phiz >> EvIDBD1mu >> EdepBD1mu;
		 vEvIDBD1muphiz.push_back(EvIDBD1mu);
		 vEdepBD1muphiz.push_back(EdepBD1mu);
	  }
	  vEvIDBD1muphiz.pop_back(); vEdepBD1muphiz.pop_back();
	  vEvIDBD1muphiz.pop_back(); vEdepBD1muphiz.pop_back();
			  
	  mufBGOD1phiz.close();
	  allvEvIDBD1muphiz.push_back(vEvIDBD1muphiz);
	  allvEdepBD1muphiz.push_back(vEdepBD1muphiz);


	  // BGOD2mu phi-z
	  std::ifstream mufBGOD2phiz(TString(mufiles[(k*16)+14]));
	  std::vector<double> vEvIDBD2muphiz;
	  std::vector<double> vEdepBD2muphiz;
			  
	  while (!mufBGOD2phiz.eof()) {
	     double EvIDBD2mu, EdepBD2mu;
		 mufBGOD2phiz >> EvIDBD2mu >> EdepBD2mu;
		 vEvIDBD2muphiz.push_back(EvIDBD2mu);
		 vEdepBD2muphiz.push_back(EdepBD2mu);
	  }
	  vEvIDBD2muphiz.pop_back(); vEdepBD2muphiz.pop_back();
	  vEvIDBD2muphiz.pop_back(); vEdepBD2muphiz.pop_back();
			  
	  mufBGOD2phiz.close();
	  allvEvIDBD2muphiz.push_back(vEvIDBD2muphiz);
	  allvEdepBD2muphiz.push_back(vEdepBD2muphiz);


	  // SciVetomu phi-z
	  std::ifstream mufSciVetophiz(TString(mufiles[(k*16)+15]));
	  std::vector<double> vEvIDSVmuphiz;
	  std::vector<double> vEdepSVmuphiz;
			  
	  while (!mufSciVetophiz.eof()) {
	     double EvIDSVmu, EdepSVmu;
		 mufSciVetophiz >> EvIDSVmu >> EdepSVmu;
		 vEvIDSVmuphiz.push_back(EvIDSVmu);
		 vEdepSVmuphiz.push_back(EdepSVmu);
	  }
	  vEvIDSVmuphiz.pop_back(); vEdepSVmuphiz.pop_back();
	  vEvIDSVmuphiz.pop_back(); vEdepSVmuphiz.pop_back();
			  
	  mufSciVetophiz.close();
	  allvEvIDSVmuphiz.push_back(vEvIDSVmuphiz);
	  allvEdepSVmuphiz.push_back(vEdepSVmuphiz);


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

		 //--------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade 3
		 //-------------------------------------------------- 
		 XXrayx3 = 0; Xelecx3 = 0;
			  
		 for (int a=0; a<allvEvIDBD1x3[0].size(); a++) {

		    if ((allvEdepSD1x3[i][a] < Ethr1) && (allvEdepSD2x3[i][a] < Ethr1) && (allvEdepSD3x3[i][a] < Ethr1)) {
		       if ((allvEdepBD1x3[i][a] > Ethr) || (allvEdepBD1x3[i][a] < Ethr22) && (allvEdepBD2x3[i][a] > Ethr) && (allvEdepBD2x3[i][a] < Ethr22)) {
                  if ((allvEdepSDS1x3[i][a] < Ethr3) && (allvEdepSDS2x3[i][a] < Ethr3) && (allvEdepSVx3[i][a] < Ethr3)) {
				     XXrayx3 += 1;
				  } else { Xelecx3 += 1; }
			   } else { Xelecx3 += 1; }
			} else { Xelecx3 += 1; }
		 }
				 
		 PXXvectorx3[i][m] = XXrayx3/(double)(counterXX);
		 PXevectorx3[i][m] = Xelecx3/(double)(counterXX); 
				

		 //--------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade 2
		 //-------------------------------------------------- 
		 XXrayx3 = 0; Xelecx2 = 0;
			  
		 for (int a=0; a<allvEvIDBD1x2[0].size(); a++) {

		    if ((allvEdepSD1x2[i][a] < Ethr1) && (allvEdepSD2x2[i][a] < Ethr1) && (allvEdepSD3x2[i][a] < Ethr1)) {
			   if ((allvEdepBD1x2[i][a] > Ethr) || (allvEdepBD1x2[i][a] < Ethr22) && (allvEdepBD2x2[i][a] > Ethr) && (allvEdepBD2x2[i][a] < Ethr22)) {
			      if ((allvEdepSDS1x2[i][a] < Ethr3) && (allvEdepSDS2x2[i][a] < Ethr3) && (allvEdepSVx2[i][a] < Ethr3)) {
				     XXrayx2 += 1;
				  } else { Xelecx2 += 1; }
			   } else { Xelecx2 += 1; }
		    } else { Xelecx2 += 1; }
		 }
				 
		 PXXvectorx2[i][m] = XXrayx2/(double)(counterXX);
		 PXevectorx2[i][m] = Xelecx2/(double)(counterXX); 
				

		 //--------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade
		 //-------------------------------------------------- 
		 XXray = 0; Xelec = 0;
			  
		 for (int a=0; a<allvEvIDBD1x[0].size(); a++) {

		    if ((allvEdepSD1x[i][a] < Ethr1) && (allvEdepSD2x[i][a] < Ethr1) && (allvEdepSD3x[i][a] < Ethr1)) {
			   if ((allvEdepBD1x[i][a] > Ethr) || (allvEdepBD1x[i][a] < Ethr22) && (allvEdepBD2x[i][a] > Ethr) && (allvEdepBD2x[i][a] < Ethr22)) {
			      if ((allvEdepSDS1x[i][a] < Ethr3) && (allvEdepSDS2x[i][a] < Ethr3) && (allvEdepSVx[i][a] < Ethr3)) {
				     XXray += 1;
				  } else { Xelec += 1; }
			   } else { Xelec += 1; }
		    } else { Xelec += 1; }
		 }
				 
		 PXXvector[i][m] = XXray/(double)(counterXX);
		 PXevector[i][m] = Xelec/(double)(counterXX); 



		 //--------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay
		 //-------------------------------------------------- 
		 eXray = 0; eelec = 0;
			  
		 for (int a=0; a<allvEvIDBD1mu[0].size(); a++) {

		    if ((allvEdepSD1mu[i][a] < Ethr1) && (allvEdepSD2mu[i][a] < Ethr1) && (allvEdepSD3mu[i][a] < Ethr1)) {
		       if ((allvEdepBD1mu[i][a] > Ethr) || (allvEdepBD1mu[i][a] < Ethr22) && (allvEdepBD2mu[i][a] > Ethr) && (allvEdepBD2mu[i][a] < Ethr22)) {
			      if ((allvEdepSDS1mu[i][a] < Ethr3) && (allvEdepSDS2mu[i][a] < Ethr3) && (allvEdepSVmu[i][a] < Ethr3)) {
				     eXray += 1;
				  } else { eelec += 1; }
			   } else { eelec += 1; }
		    } else { eelec += 1; }
		 }
				 
		 PeXvector[i][m] = eXray/(double)(counteree);
		 Peevector[i][m] = eelec/(double)(counteree); 



         //--------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade 3 phi-z
		 //-------------------------------------------------- 
		 XXrayx3phiz = 0; Xelecx3phiz = 0;
			  
		 for (int a=0; a<allvEvIDBD1x3phiz[0].size(); a++) {

		    if ((allvEdepSD1x3phiz[i][a] < Ethr1) && (allvEdepSD2x3phiz[i][a] < Ethr1) && (allvEdepSD3x3phiz[i][a] < Ethr1)) {
		       if ((allvEdepBD1x3phiz[i][a] > Ethr) || (allvEdepBD1x3phiz[i][a] < Ethr22) && (allvEdepBD2x3phiz[i][a] > Ethr) && (allvEdepBD2x3phiz[i][a] < Ethr22)) {
                  if ((allvEdepSDS1x3phiz[i][a] < Ethr3) && (allvEdepSDS2x3phiz[i][a] < Ethr3) && (allvEdepSVx3phiz[i][a] < Ethr3)) {
				     XXrayx3phiz += 1;
				  } else { Xelecx3phiz += 1; }
			   } else { Xelecx3phiz += 1; }
			} else { Xelecx3phiz += 1; }
		 }
				 
		 PXXvectorx3phiz[i][m] = XXrayx3phiz/(double)(counterXX);
		 PXevectorx3phiz[i][m] = Xelecx3phiz/(double)(counterXX); 
				

		 //--------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade 2 phi-z
		 //-------------------------------------------------- 
		 XXrayx3phiz = 0; Xelecx2phiz = 0;
			  
		 for (int a=0; a<allvEvIDBD1x2phiz[0].size(); a++) {

		    if ((allvEdepSD1x2phiz[i][a] < Ethr1) && (allvEdepSD2x2phiz[i][a] < Ethr1) && (allvEdepSD3x2phiz[i][a] < Ethr1)) {
			   if ((allvEdepBD1x2phiz[i][a] > Ethr) || (allvEdepBD1x2phiz[i][a] < Ethr22) && (allvEdepBD2x2phiz[i][a] > Ethr) && (allvEdepBD2x2phiz[i][a] < Ethr22)) {
			      if ((allvEdepSDS1x2phiz[i][a] < Ethr3) && (allvEdepSDS2x2phiz[i][a] < Ethr3) && (allvEdepSVx2phiz[i][a] < Ethr3)) {
				     XXrayx2phiz += 1;
				  } else { Xelecx2phiz += 1; }
			   } else { Xelecx2phiz += 1; }
		    } else { Xelecx2phiz += 1; }
		 }
				 
		 PXXvectorx2phiz[i][m] = XXrayx2phiz/(double)(counterXX);
		 PXevectorx2phiz[i][m] = Xelecx2phiz/(double)(counterXX); 
				

		 //--------------------------------------------------
		 // Normalisation 2 [absolute] :: cascade phi-z
		 //-------------------------------------------------- 
		 XXrayphiz = 0; Xelecphiz = 0;
			  
		 for (int a=0; a<allvEvIDBD1xphiz[0].size(); a++) {

		    if ((allvEdepSD1xphiz[i][a] < Ethr1) && (allvEdepSD2xphiz[i][a] < Ethr1) && (allvEdepSD3xphiz[i][a] < Ethr1)) {
			   if ((allvEdepBD1xphiz[i][a] > Ethr) || (allvEdepBD1xphiz[i][a] < Ethr22) && (allvEdepBD2xphiz[i][a] > Ethr) && (allvEdepBD2xphiz[i][a] < Ethr22)) {
			      if ((allvEdepSDS1xphiz[i][a] < Ethr3) && (allvEdepSDS2xphiz[i][a] < Ethr3) && (allvEdepSVxphiz[i][a] < Ethr3)) {
				     XXrayphiz += 1;
				  } else { Xelecphiz += 1; }
			   } else { Xelecphiz += 1; }
		    } else { Xelecphiz += 1; }
		 }
				 
		 PXXvectorphiz[i][m] = XXrayphiz/(double)(counterXX);
		 PXevectorphiz[i][m] = Xelecphiz/(double)(counterXX); 



		 //--------------------------------------------------
	     // Normalisation 2 [absolute] :: mu-decay phi-z
		 //-------------------------------------------------- 
		 eXrayphiz = 0; eelecphiz = 0;
			  
		 for (int a=0; a<allvEvIDBD1muphiz[0].size(); a++) {

		    if ((allvEdepSD1muphiz[i][a] < Ethr1) && (allvEdepSD2muphiz[i][a] < Ethr1) && (allvEdepSD3muphiz[i][a] < Ethr1)) {
		       if ((allvEdepBD1muphiz[i][a] > Ethr) || (allvEdepBD1muphiz[i][a] < Ethr22) && (allvEdepBD2muphiz[i][a] > Ethr) && (allvEdepBD2muphiz[i][a] < Ethr22)) {
			      if ((allvEdepSDS1muphiz[i][a] < Ethr3) && (allvEdepSDS2muphiz[i][a] < Ethr3) && (allvEdepSVmuphiz[i][a] < Ethr3)) {
				     eXrayphiz += 1;
				  } else { eelecphiz += 1; }
			   } else { eelecphiz += 1; }
		    } else { eelecphiz += 1; }
		 }
				 
		 PeXvectorphiz[i][m] = eXrayphiz/(double)(counteree);
		 Peevectorphiz[i][m] = eelecphiz/(double)(counteree); 

	  
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
   float PXXarrx3[nsamps] = {}; // X-ray cascade
   float PXXarrx2[nsamps] = {};
   float PXXarr[nsamps] = {};
   float PeXarr[nsamps] = {};
   float PeXXXarrx3[nsamps] = {};
   float PeXXXarrx2[nsamps] = {};
   float PeXXXarr[nsamps] = {};
   float PXXarrx3phiz[nsamps] = {}; 
   float PXXarrx2phiz[nsamps] = {};
   float PXXarrphiz[nsamps] = {};
   float PeXarrphiz[nsamps] = {};
   float PeXXXarrx3phiz[nsamps] = {};
   float PeXXXarrx2phiz[nsamps] = {};
   float PeXXXarrphiz[nsamps] = {};

 		 	   
   for (int i=0; i<nsamps; i++) {
      // Normalisation 2 [absolute]
	  PXXarrx3[i] = PXXvectorx3[0][i];
	  PXXarrx2[i] = PXXvectorx2[0][i];
	  PXXarr[i] = PXXvector[0][i];
	  PeXarr[i] = PeXvector[0][i];
	  PeXXXarrx3[i] = (PeXvector[0][i])/(double)(PXXvectorx3[0][i]);
	  PeXXXarrx2[i] = (PeXvector[0][i])/(double)(PXXvectorx2[0][i]);
	  PeXXXarr[i] = (PeXvector[0][i])/(double)(PXXvector[0][i]);
	  PXXarrx3phiz[i] = PXXvectorx3phiz[0][i];
	  PXXarrx2phiz[i] = PXXvectorx2phiz[0][i];
	  PXXarrphiz[i] = PXXvectorphiz[0][i];
	  PeXarrphiz[i] = PeXvectorphiz[0][i];
	  PeXXXarrx3phiz[i] = (PeXvectorphiz[0][i])/(double)(PXXvectorx3phiz[0][i]);
	  PeXXXarrx2phiz[i] = (PeXvectorphiz[0][i])/(double)(PXXvectorx2phiz[0][i]);
	  PeXXXarrphiz[i] = (PeXvectorphiz[0][i])/(double)(PXXvectorphiz[0][i]);
   }	   

		  
   TCanvas *d = new TCanvas("d","E_{THR}",800,600);
   d->Divide(3,1);
   d->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPXXx3 = new TGraph(nsamps,Ethrmu,PXXarrx3);
   grPXXx3->SetTitle(TString(material)+" cavity, cascade-3 [10^5 events]"); 
   grPXXx3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXXx3->GetXaxis()->SetRangeUser(0,2.05);
   //grPXXx3->GetYaxis()->SetRangeUser(3e-1,1.1);
   grPXXx3->GetYaxis()->SetMoreLogLabels(1);
   grPXXx3->GetYaxis()->SetTitle("P_{XX}");
   grPXXx3->GetYaxis()->SetTitleOffset(1.8);
   //grPXXx3->SetMarkerColor(kRed);
   //grPXXx3->SetMarkerStyle(31);
   grPXXx3->SetLineColor(kRed);
   grPXXx3->SetLineWidth(3);
   grPXXx3->Draw("ALP");
   TGraph *grPXXx3phiz = new TGraph(nsamps,Ethrmu,PXXarrx3phiz); 
   grPXXx3phiz->SetLineColor(kBlack);
   grPXXx3phiz->SetLineWidth(3);
   grPXXx3phiz->Draw("LP");
   legPXXx3 = new TLegend(0.2,-0.005,0.4,0.08);
   legPXXx3->AddEntry(grPXXx3,"#Phi = 0-mm, z = 0-mm","lp");
   legPXXx3->AddEntry(grPXXx3phiz,"#Phi = 50-mm, z = 30-mm","lp");
   legPXXx3->Draw();

   d->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeXx3 = new TGraph(nsamps,Ethrmu,PeXarr);
   grPeXx3->SetTitle(TString(material)+" cavity, cascade-3 [10^5 events]");
   grPeXx3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeXx3->GetXaxis()->SetRangeUser(0,2.05);
   //grPeXx3->GetYaxis()->SetRangeUser(3e-1,1.1);
   grPeXx3->GetYaxis()->SetMoreLogLabels(1);
   grPeXx3->GetYaxis()->SetTitle("P_{eX}");
   grPeXx3->GetYaxis()->SetTitleOffset(1.8);
   grPeXx3->SetLineColor(kRed);
   grPeXx3->SetLineWidth(3);
   grPeXx3->Draw("ALP");
   TGraph *grPeXx3phiz = new TGraph(nsamps,Ethrmu,PeXarrphiz);
   grPeXx3phiz->SetLineColor(kBlack);
   grPeXx3phiz->SetLineWidth(3);
   grPeXx3phiz->Draw("LP");
   legPeXx3 = new TLegend(0.2,-0.005,0.4,0.08);
   legPeXx3->AddEntry(grPeXx3,"#Phi = 0-mm, z = 0-mm","lp");
   legPeXx3->AddEntry(grPeXx3phiz,"#Phi = 50-mm, z = 30-mm","lp");
   legPeXx3->Draw(); 
    
   d->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeXXXx3 = new TGraph(nsamps,Ethrmu,PeXXXarrx3);
   grPeXXXx3->SetTitle(TString(material)+" cavity, cascade-3 [10^5 events]");
   grPeXXXx3->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeXXXx3->GetXaxis()->SetRangeUser(0,2.05);
   grPeXXXx3->GetYaxis()->SetMoreLogLabels(1);
   grPeXXXx3->GetYaxis()->SetTitle("#frac{P_{eX}}{P_{XX}}");
   grPeXXXx3->GetYaxis()->SetTitleOffset(1.7);
   grPeXXXx3->SetLineColor(kRed);
   grPeXXXx3->SetLineWidth(3);
   grPeXXXx3->Draw("ALP");
   TGraph *grPeXXXx3phiz = new TGraph(nsamps,Ethrmu,PeXXXarrx3phiz);
   grPeXXXx3phiz->SetLineColor(kBlack);
   grPeXXXx3phiz->SetLineWidth(3);
   grPeXXXx3phiz->Draw("LP");
   legPeXXXx3 = new TLegend(0.2,-0.005,0.4,0.08);
   legPeXXXx3->AddEntry(grPeXXXx3,"#Phi = 0-mm, z = 0-mm","lp");
   legPeXXXx3->AddEntry(grPeXXXx3phiz,"#Phi = 50-mm, z = 30-mm","lp");
   legPeXXXx3->Draw();

   d->SaveAs(TString(material)+"_goldcascade3_eff.pdf");
   d->SaveAs(TString(material)+"_goldcascade3_eff.png");
   d->SaveAs(TString(material)+"_goldcascade3_eff.C");



   TCanvas *e = new TCanvas("e","E_{THR}",800,600);
   e->Divide(3,1);
   e->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPXXx2 = new TGraph(nsamps,Ethrmu,PXXarrx2);
   grPXXx2->SetTitle(TString(material)+" cavity, cascade-2 [10^5 events]"); 
   grPXXx2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXXx2->GetXaxis()->SetRangeUser(0,2.05);
   //grPXXx2->GetYaxis()->SetRangeUser(3e-1,1.1);
   grPXXx2->GetYaxis()->SetMoreLogLabels(1);
   grPXXx2->GetYaxis()->SetTitle("P_{XX}");
   grPXXx2->GetYaxis()->SetTitleOffset(1.8);
   //grPXXx2->SetMarkerColor(kRed);
   //grPXXx2->SetMarkerStyle(31);
   grPXXx2->SetLineColor(kRed);
   grPXXx2->SetLineWidth(3);
   grPXXx2->Draw("ALP");
   TGraph *grPXXx2phiz = new TGraph(nsamps,Ethrmu,PXXarrx2phiz); 
   grPXXx2phiz->SetLineColor(kBlack);
   grPXXx2phiz->SetLineWidth(3);
   grPXXx2phiz->Draw("LP");
   legPXXx2 = new TLegend(0.2,-0.005,0.4,0.08);
   legPXXx2->AddEntry(grPXXx2,"#Phi = 0-mm, z = 0-mm","lp");
   legPXXx2->AddEntry(grPXXx2phiz,"#Phi = 50-mm, z = 30-mm","lp");
   legPXXx2->Draw();

   e->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeXx2 = new TGraph(nsamps,Ethrmu,PeXarr);
   grPeXx2->SetTitle(TString(material)+" cavity, cascade-2 [10^5 events]");
   grPeXx2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeXx2->GetXaxis()->SetRangeUser(0,2.05);
   //grPeXx2->GetYaxis()->SetRangeUser(3e-1,1.1);
   grPeXx2->GetYaxis()->SetMoreLogLabels(1);
   grPeXx2->GetYaxis()->SetTitle("P_{eX}");
   grPeXx2->GetYaxis()->SetTitleOffset(1.8);
   grPeXx2->SetLineColor(kRed);
   grPeXx2->SetLineWidth(3);
   grPeXx2->Draw("ALP");
   TGraph *grPeXx2phiz = new TGraph(nsamps,Ethrmu,PeXarrphiz);
   grPeXx2phiz->SetLineColor(kBlack);
   grPeXx2phiz->SetLineWidth(3);
   grPeXx2phiz->Draw("LP");
   legPeXx2 = new TLegend(0.2,-0.005,0.4,0.08);
   legPeXx2->AddEntry(grPeXx2,"#Phi = 0-mm, z = 0-mm","lp");
   legPeXx2->AddEntry(grPeXx2phiz,"#Phi = 50-mm, z = 30-mm","lp");
   legPeXx2->Draw(); 
    
   e->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeXXXx2 = new TGraph(nsamps,Ethrmu,PeXXXarrx2);
   grPeXXXx2->SetTitle(TString(material)+" cavity, cascade-2 [10^5 events]");
   grPeXXXx2->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeXXXx2->GetXaxis()->SetRangeUser(0,2.05);
   grPeXXXx2->GetYaxis()->SetMoreLogLabels(1);
   grPeXXXx2->GetYaxis()->SetTitle("#frac{P_{eX}}{P_{XX}}");
   grPeXXXx2->GetYaxis()->SetTitleOffset(1.7);
   grPeXXXx2->SetLineColor(kRed);
   grPeXXXx2->SetLineWidth(3);
   grPeXXXx2->Draw("ALP");
   TGraph *grPeXXXx2phiz = new TGraph(nsamps,Ethrmu,PeXXXarrx2phiz);
   grPeXXXx2phiz->SetLineColor(kBlack);
   grPeXXXx2phiz->SetLineWidth(3);
   grPeXXXx2phiz->Draw("LP");
   legPeXXXx2 = new TLegend(0.2,-0.005,0.4,0.08);
   legPeXXXx2->AddEntry(grPeXXXx2,"#Phi = 0-mm, z = 0-mm","lp");
   legPeXXXx2->AddEntry(grPeXXXx2phiz,"#Phi = 50-mm, z = 30-mm","lp");
   legPeXXXx2->Draw();

   e->SaveAs(TString(material)+"_goldcascade2_eff.pdf");
   e->SaveAs(TString(material)+"_goldcascade2_eff.png");
   e->SaveAs(TString(material)+"_goldcascade2_eff.C");



   TCanvas *f = new TCanvas("f","E_{THR}",800,600);
   f->Divide(3,1);
   f->cd(1);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPXX = new TGraph(nsamps,Ethrmu,PXXarr);
   grPXX->SetTitle(TString(material)+" cavity, cascade [10^5 events]"); 
   grPXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPXX->GetXaxis()->SetRangeUser(0,2.05);
   //grPXX->GetYaxis()->SetRangeUser(3e-1,1.1);
   grPXX->GetYaxis()->SetMoreLogLabels(1);
   grPXX->GetYaxis()->SetTitle("P_{XX}");
   grPXX->GetYaxis()->SetTitleOffset(1.8);
   //grPXX->SetMarkerColor(kRed);
   //grPXX->SetMarkerStyle(31);
   grPXX->SetLineColor(kRed);
   grPXX->SetLineWidth(3);
   grPXX->Draw("ALP");
   TGraph *grPXXphiz = new TGraph(nsamps,Ethrmu,PXXarrphiz); 
   grPXXphiz->SetLineColor(kBlack);
   grPXXphiz->SetLineWidth(3);
   grPXXphiz->Draw("LP");
   legPXX = new TLegend(0.2,-0.005,0.4,0.08);
   legPXX->AddEntry(grPXX,"#Phi = 0-mm, z = 0-mm","lp");
   legPXX->AddEntry(grPXXphiz,"#Phi = 50-mm, z = 30-mm","lp");
   legPXX->Draw();

   f->cd(2);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeX = new TGraph(nsamps,Ethrmu,PeXarr);
   grPeX->SetTitle(TString(material)+" cavity, cascade [10^5 events]");
   grPeX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeX->GetXaxis()->SetRangeUser(0,2.05);
   //grPeX->GetYaxis()->SetRangeUser(3e-1,1.1);
   grPeX->GetYaxis()->SetMoreLogLabels(1);
   grPeX->GetYaxis()->SetTitle("P_{eX}");
   grPeX->GetYaxis()->SetTitleOffset(1.8);
   grPeX->SetLineColor(kRed);
   grPeX->SetLineWidth(3);
   grPeX->Draw("ALP");
   TGraph *grPeXphiz = new TGraph(nsamps,Ethrmu,PeXarrphiz);
   grPeXphiz->SetLineColor(kBlack);
   grPeXphiz->SetLineWidth(3);
   grPeXphiz->Draw("LP");
   legPeX = new TLegend(0.2,-0.005,0.4,0.08);
   legPeX->AddEntry(grPeX,"#Phi = 0-mm, z = 0-mm","lp");
   legPeX->AddEntry(grPeXphiz,"#Phi = 50-mm, z = 30-mm","lp");
   legPeX->Draw(); 
    
   f->cd(3);
   gPad->SetLogy();
   gPad->SetGrid(1,1);
   TGraph *grPeXXX = new TGraph(nsamps,Ethrmu,PeXXXarr);
   grPeXXX->SetTitle(TString(material)+" cavity, cascade [10^5 events]");
   grPeXXX->GetXaxis()->SetTitle("E_{THR} [MeV]");
   grPeXXX->GetXaxis()->SetRangeUser(0,2.05);
   grPeXXX->GetYaxis()->SetMoreLogLabels(1);
   grPeXXX->GetYaxis()->SetTitle("#frac{P_{eX}}{P_{XX}}");
   grPeXXX->GetYaxis()->SetTitleOffset(1.7);
   grPeXXX->SetLineColor(kRed);
   grPeXXX->SetLineWidth(3);
   grPeXXX->Draw("ALP");
   TGraph *grPeXXXphiz = new TGraph(nsamps,Ethrmu,PeXXXarrphiz);
   grPeXXXphiz->SetLineColor(kBlack);
   grPeXXXphiz->SetLineWidth(3);
   grPeXXXphiz->Draw("LP");
   legPeXXX = new TLegend(0.2,-0.005,0.4,0.08);
   legPeXXX->AddEntry(grPeXXX,"#Phi = 0-mm, z = 0-mm","lp");
   legPeXXX->AddEntry(grPeXXXphiz,"#Phi = 50-mm, z = 30-mm","lp");
   legPeXXX->Draw();

   f->SaveAs(TString(material)+"_goldcascade_eff.pdf");
   f->SaveAs(TString(material)+"_goldcascade_eff.png");
   f->SaveAs(TString(material)+"_goldcascade_eff.C");


 
} 
 
 int main() {
   finalcavMULTIeff();
   return 0;
}  
