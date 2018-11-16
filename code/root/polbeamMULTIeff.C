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

void polbeamMULTIeff(){

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
   const int length = 1;
   float phiArray[length] = {0};
   float zArray[length] = {0};


   int phishift, zshift;
      
   for (int phi=0; phi<length; phi++) {

      for (int z=0; z<length; z++) {
	     phishift = phiArray[phi];
	     zshift = zArray[z];

   
		 std::stringstream phishiftss;
		 std::stringstream zshiftss;
		 phishiftss << phishift;
		 zshiftss << zshift;


		 // Names of the files
         // Mu-decay POL-X0Y0Z0 without SpinTracking
         std::string filemuSciD1POL000noST = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z0_noST_1e5mudecay_SciD1.txt";
		 std::string filemuSciD2POL000noST = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z0_noST_1e5mudecay_SciD2.txt";
		 std::string filemuSciDTPOL000noST = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z0_noST_1e5mudecay_SciDT.txt";
		 std::string filemuSciDBPOL000noST = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z0_noST_1e5mudecay_SciDB.txt";
		 std::string filemuSciDLPOL000noST = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z0_noST_1e5mudecay_SciDL.txt";
		 std::string filemuSciDRPOL000noST = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z0_noST_1e5mudecay_SciDR.txt";
		 std::string filemuBGOD1POL000noST = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z0_noST_1e5mudecay_BGOD1.txt";

         // Mu-decay POL-X0Y0Z0
         std::string filemuSciD1POL000 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z0_1e5mudecay_SciD1.txt";
		 std::string filemuSciD2POL000 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z0_1e5mudecay_SciD2.txt";
		 std::string filemuSciDTPOL000 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z0_1e5mudecay_SciDT.txt";
		 std::string filemuSciDBPOL000 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z0_1e5mudecay_SciDB.txt";
		 std::string filemuSciDLPOL000 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z0_1e5mudecay_SciDL.txt";
		 std::string filemuSciDRPOL000 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z0_1e5mudecay_SciDR.txt";
		 std::string filemuBGOD1POL000 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z0_1e5mudecay_BGOD1.txt";
         
         // Mu-decay POL-X0Y0Z1
         std::string filemuSciD1POL001 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z1_1e5mudecay_SciD1.txt";
		 std::string filemuSciD2POL001 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z1_1e5mudecay_SciD2.txt";
		 std::string filemuSciDTPOL001 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z1_1e5mudecay_SciDT.txt";
		 std::string filemuSciDBPOL001 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z1_1e5mudecay_SciDB.txt";
		 std::string filemuSciDLPOL001 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z1_1e5mudecay_SciDL.txt";
		 std::string filemuSciDRPOL001 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z1_1e5mudecay_SciDR.txt";
		 std::string filemuBGOD1POL001 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y0Z1_1e5mudecay_BGOD1.txt";

         // Mu-decay POL-X0Y1Z0
         std::string filemuSciD1POL010 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y1Z0_1e5mudecay_SciD1.txt";
		 std::string filemuSciD2POL010 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y1Z0_1e5mudecay_SciD2.txt";
		 std::string filemuSciDTPOL010 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y1Z0_1e5mudecay_SciDT.txt";
		 std::string filemuSciDBPOL010 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y1Z0_1e5mudecay_SciDB.txt";
		 std::string filemuSciDLPOL010 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y1Z0_1e5mudecay_SciDL.txt";
		 std::string filemuSciDRPOL010 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y1Z0_1e5mudecay_SciDR.txt";
		 std::string filemuBGOD1POL010 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y1Z0_1e5mudecay_BGOD1.txt";

         // Mu-decay POL-X1Y0Z0
         std::string filemuSciD1POL100 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y0Z0_1e5mudecay_SciD1.txt";
		 std::string filemuSciD2POL100 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y0Z0_1e5mudecay_SciD2.txt";
		 std::string filemuSciDTPOL100 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y0Z0_1e5mudecay_SciDT.txt";
		 std::string filemuSciDBPOL100 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y0Z0_1e5mudecay_SciDB.txt";
		 std::string filemuSciDLPOL100 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y0Z0_1e5mudecay_SciDL.txt";
		 std::string filemuSciDRPOL100 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y0Z0_1e5mudecay_SciDR.txt";
		 std::string filemuBGOD1POL100 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y0Z0_1e5mudecay_BGOD1.txt";

         // Mu-decay POL-X1Y1Z0
         std::string filemuSciD1POL110 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y1Z0_1e5mudecay_SciD1.txt";
		 std::string filemuSciD2POL110 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y1Z0_1e5mudecay_SciD2.txt";
		 std::string filemuSciDTPOL110 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y1Z0_1e5mudecay_SciDT.txt";
		 std::string filemuSciDBPOL110 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y1Z0_1e5mudecay_SciDB.txt";
		 std::string filemuSciDLPOL110 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y1Z0_1e5mudecay_SciDL.txt";
		 std::string filemuSciDRPOL110 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y1Z0_1e5mudecay_SciDR.txt";
		 std::string filemuBGOD1POL110 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y1Z0_1e5mudecay_BGOD1.txt";

         // Mu-decay POL-X1Y0Z1
         std::string filemuSciD1POL101 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y0Z1_1e5mudecay_SciD1.txt";
		 std::string filemuSciD2POL101 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y0Z1_1e5mudecay_SciD2.txt";
		 std::string filemuSciDTPOL101 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y0Z1_1e5mudecay_SciDT.txt";
		 std::string filemuSciDBPOL101 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y0Z1_1e5mudecay_SciDB.txt";
		 std::string filemuSciDLPOL101 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y0Z1_1e5mudecay_SciDL.txt";
		 std::string filemuSciDRPOL101 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y0Z1_1e5mudecay_SciDR.txt";
		 std::string filemuBGOD1POL101 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y0Z1_1e5mudecay_BGOD1.txt";

         // Mu-decay POL-X0Y1Z1
         std::string filemuSciD1POL011 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y1Z1_1e5mudecay_SciD1.txt";
		 std::string filemuSciD2POL011 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y1Z1_1e5mudecay_SciD2.txt";
		 std::string filemuSciDTPOL011 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y1Z1_1e5mudecay_SciDT.txt";
		 std::string filemuSciDBPOL011 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y1Z1_1e5mudecay_SciDB.txt";
		 std::string filemuSciDLPOL011 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y1Z1_1e5mudecay_SciDL.txt";
		 std::string filemuSciDRPOL011 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y1Z1_1e5mudecay_SciDR.txt";
		 std::string filemuBGOD1POL011 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX0Y1Z1_1e5mudecay_BGOD1.txt";

         // Mu-decay POL-X1Y1Z1
         std::string filemuSciD1POL111 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y1Z1_1e5mudecay_SciD1.txt";
		 std::string filemuSciD2POL111 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y1Z1_1e5mudecay_SciD2.txt";
		 std::string filemuSciDTPOL111 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y1Z1_1e5mudecay_SciDT.txt";
		 std::string filemuSciDBPOL111 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y1Z1_1e5mudecay_SciDB.txt";
		 std::string filemuSciDLPOL111 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y1Z1_1e5mudecay_SciDL.txt";
		 std::string filemuSciDRPOL111 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y1Z1_1e5mudecay_SciDR.txt";
		 std::string filemuBGOD1POL111 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_polX1Y1Z1_1e5mudecay_BGOD1.txt";


		 // Vectors with filenames   
		 std::vector<std::string> mufiles;

		 // Mu-decay
		 mufiles.push_back(filemuSciD1POL000noST);
		 mufiles.push_back(filemuSciD2POL000noST);
		 mufiles.push_back(filemuSciDTPOL000noST);
		 mufiles.push_back(filemuSciDBPOL000noST);
		 mufiles.push_back(filemuSciDLPOL000noST);
		 mufiles.push_back(filemuSciDRPOL000noST);
		 mufiles.push_back(filemuBGOD1POL000noST);
		 		 
		 mufiles.push_back(filemuSciD1POL000);
		 mufiles.push_back(filemuSciD2POL000);
		 mufiles.push_back(filemuSciDTPOL000);
		 mufiles.push_back(filemuSciDBPOL000);
		 mufiles.push_back(filemuSciDLPOL000);
		 mufiles.push_back(filemuSciDRPOL000);
		 mufiles.push_back(filemuBGOD1POL000);

		 mufiles.push_back(filemuSciD1POL001);
		 mufiles.push_back(filemuSciD2POL001);
		 mufiles.push_back(filemuSciDTPOL001);
		 mufiles.push_back(filemuSciDBPOL001);
		 mufiles.push_back(filemuSciDLPOL001);
		 mufiles.push_back(filemuSciDRPOL001);
		 mufiles.push_back(filemuBGOD1POL001);

		 mufiles.push_back(filemuSciD1POL010);
		 mufiles.push_back(filemuSciD2POL010);
		 mufiles.push_back(filemuSciDTPOL010);
		 mufiles.push_back(filemuSciDBPOL010);
		 mufiles.push_back(filemuSciDLPOL010);
		 mufiles.push_back(filemuSciDRPOL010);
		 mufiles.push_back(filemuBGOD1POL010);

		 mufiles.push_back(filemuSciD1POL100);
		 mufiles.push_back(filemuSciD2POL100);
		 mufiles.push_back(filemuSciDTPOL100);
		 mufiles.push_back(filemuSciDBPOL100);
		 mufiles.push_back(filemuSciDLPOL100);
		 mufiles.push_back(filemuSciDRPOL100);
		 mufiles.push_back(filemuBGOD1POL100);

		 mufiles.push_back(filemuSciD1POL110);
		 mufiles.push_back(filemuSciD2POL110);
		 mufiles.push_back(filemuSciDTPOL110);
		 mufiles.push_back(filemuSciDBPOL110);
		 mufiles.push_back(filemuSciDLPOL110);
		 mufiles.push_back(filemuSciDRPOL110);
		 mufiles.push_back(filemuBGOD1POL110);

		 mufiles.push_back(filemuSciD1POL101);
		 mufiles.push_back(filemuSciD2POL101);
		 mufiles.push_back(filemuSciDTPOL101);
		 mufiles.push_back(filemuSciDBPOL101);
		 mufiles.push_back(filemuSciDLPOL101);
		 mufiles.push_back(filemuSciDRPOL101);
		 mufiles.push_back(filemuBGOD1POL101);

		 mufiles.push_back(filemuSciD1POL011);
		 mufiles.push_back(filemuSciD2POL011);
		 mufiles.push_back(filemuSciDTPOL011);
		 mufiles.push_back(filemuSciDBPOL011);
		 mufiles.push_back(filemuSciDLPOL011);
		 mufiles.push_back(filemuSciDRPOL011);
		 mufiles.push_back(filemuBGOD1POL011);

		 mufiles.push_back(filemuSciD1POL111);
		 mufiles.push_back(filemuSciD2POL111);
		 mufiles.push_back(filemuSciDTPOL111);
		 mufiles.push_back(filemuSciDBPOL111);
		 mufiles.push_back(filemuSciDLPOL111);
		 mufiles.push_back(filemuSciDRPOL111);
		 mufiles.push_back(filemuBGOD1POL111);


		 /*********************************/
		 /*           Analysis            */
		 /*********************************/

		 float Edep, EventID;
		 float iEventID;

		 float Ethr1 = 0.5;
		 float Ethr21 = 0.5;
		 float Ethr22 = 8;
		 float Ethr3 = 1;
		 float Estep = 2.0/(nsamps-1);
		 float Ethrmu[nsamps] = {};
		   
		 // Storage vectors
		 // Normalisation 2 [abs = total]
		 std::vector< std::vector<double> > PeXvectorPOL000noST(mufiles.size()/63,std::vector<double>(nsamps));
		 std::vector< std::vector<double> > PeevectorPOL000noST(mufiles.size()/63,std::vector<double>(nsamps));      
		 std::vector< std::vector<double> > PeXvectorPOL000(mufiles.size()/63,std::vector<double>(nsamps));
		 std::vector< std::vector<double> > PeevectorPOL000(mufiles.size()/63,std::vector<double>(nsamps));      
		 std::vector< std::vector<double> > PeXvectorPOL001(mufiles.size()/63,std::vector<double>(nsamps));
		 std::vector< std::vector<double> > PeevectorPOL001(mufiles.size()/63,std::vector<double>(nsamps));      
		 std::vector< std::vector<double> > PeXvectorPOL010(mufiles.size()/63,std::vector<double>(nsamps));
		 std::vector< std::vector<double> > PeevectorPOL010(mufiles.size()/63,std::vector<double>(nsamps));      
		 std::vector< std::vector<double> > PeXvectorPOL100(mufiles.size()/63,std::vector<double>(nsamps));
		 std::vector< std::vector<double> > PeevectorPOL100(mufiles.size()/63,std::vector<double>(nsamps));      
		 std::vector< std::vector<double> > PeXvectorPOL110(mufiles.size()/63,std::vector<double>(nsamps));
		 std::vector< std::vector<double> > PeevectorPOL110(mufiles.size()/63,std::vector<double>(nsamps));      
		 std::vector< std::vector<double> > PeXvectorPOL101(mufiles.size()/63,std::vector<double>(nsamps));
		 std::vector< std::vector<double> > PeevectorPOL101(mufiles.size()/63,std::vector<double>(nsamps));      
		 std::vector< std::vector<double> > PeXvectorPOL011(mufiles.size()/63,std::vector<double>(nsamps));
		 std::vector< std::vector<double> > PeevectorPOL011(mufiles.size()/63,std::vector<double>(nsamps));      
		 std::vector< std::vector<double> > PeXvectorPOL111(mufiles.size()/63,std::vector<double>(nsamps));
		 std::vector< std::vector<double> > PeevectorPOL111(mufiles.size()/63,std::vector<double>(nsamps));      

		 // Mu-decay
		 std::vector< std::vector< double > > allvEvIDSD1muPOL000noST;
		 std::vector< std::vector< double > > allvEdepSD1muPOL000noST;
		 std::vector< std::vector< double > > allvEvIDSD2muPOL000noST;
		 std::vector< std::vector< double > > allvEdepSD2muPOL000noST;
		 std::vector< std::vector< double > > allvEvIDSDTmuPOL000noST;
		 std::vector< std::vector< double > > allvEdepSDTmuPOL000noST;
		 std::vector< std::vector< double > > allvEvIDSDBmuPOL000noST;
		 std::vector< std::vector< double > > allvEdepSDBmuPOL000noST;
		 std::vector< std::vector< double > > allvEvIDSDLmuPOL000noST;
		 std::vector< std::vector< double > > allvEdepSDLmuPOL000noST;
		 std::vector< std::vector< double > > allvEvIDSDRmuPOL000noST;
		 std::vector< std::vector< double > > allvEdepSDRmuPOL000noST;
		 std::vector< std::vector< double > > allvEvIDBD1muPOL000noST;
		 std::vector< std::vector< double > > allvEdepBD1muPOL000noST;

		 std::vector< std::vector< double > > allvEvIDSD1muPOL000;
		 std::vector< std::vector< double > > allvEdepSD1muPOL000;
		 std::vector< std::vector< double > > allvEvIDSD2muPOL000;
		 std::vector< std::vector< double > > allvEdepSD2muPOL000;
		 std::vector< std::vector< double > > allvEvIDSDTmuPOL000;
		 std::vector< std::vector< double > > allvEdepSDTmuPOL000;
		 std::vector< std::vector< double > > allvEvIDSDBmuPOL000;
		 std::vector< std::vector< double > > allvEdepSDBmuPOL000;
		 std::vector< std::vector< double > > allvEvIDSDLmuPOL000;
		 std::vector< std::vector< double > > allvEdepSDLmuPOL000;
		 std::vector< std::vector< double > > allvEvIDSDRmuPOL000;
		 std::vector< std::vector< double > > allvEdepSDRmuPOL000;
		 std::vector< std::vector< double > > allvEvIDBD1muPOL000;
		 std::vector< std::vector< double > > allvEdepBD1muPOL000;

		 std::vector< std::vector< double > > allvEvIDSD1muPOL001;
		 std::vector< std::vector< double > > allvEdepSD1muPOL001;
		 std::vector< std::vector< double > > allvEvIDSD2muPOL001;
		 std::vector< std::vector< double > > allvEdepSD2muPOL001;
		 std::vector< std::vector< double > > allvEvIDSDTmuPOL001;
		 std::vector< std::vector< double > > allvEdepSDTmuPOL001;
		 std::vector< std::vector< double > > allvEvIDSDBmuPOL001;
		 std::vector< std::vector< double > > allvEdepSDBmuPOL001;
		 std::vector< std::vector< double > > allvEvIDSDLmuPOL001;
		 std::vector< std::vector< double > > allvEdepSDLmuPOL001;
		 std::vector< std::vector< double > > allvEvIDSDRmuPOL001;
		 std::vector< std::vector< double > > allvEdepSDRmuPOL001;
		 std::vector< std::vector< double > > allvEvIDBD1muPOL001;
		 std::vector< std::vector< double > > allvEdepBD1muPOL001;

		 std::vector< std::vector< double > > allvEvIDSD1muPOL010;
		 std::vector< std::vector< double > > allvEdepSD1muPOL010;
		 std::vector< std::vector< double > > allvEvIDSD2muPOL010;
		 std::vector< std::vector< double > > allvEdepSD2muPOL010;
		 std::vector< std::vector< double > > allvEvIDSDTmuPOL010;
		 std::vector< std::vector< double > > allvEdepSDTmuPOL010;
		 std::vector< std::vector< double > > allvEvIDSDBmuPOL010;
		 std::vector< std::vector< double > > allvEdepSDBmuPOL010;
		 std::vector< std::vector< double > > allvEvIDSDLmuPOL010;
		 std::vector< std::vector< double > > allvEdepSDLmuPOL010;
		 std::vector< std::vector< double > > allvEvIDSDRmuPOL010;
		 std::vector< std::vector< double > > allvEdepSDRmuPOL010;
		 std::vector< std::vector< double > > allvEvIDBD1muPOL010;
		 std::vector< std::vector< double > > allvEdepBD1muPOL010;

		 std::vector< std::vector< double > > allvEvIDSD1muPOL100;
		 std::vector< std::vector< double > > allvEdepSD1muPOL100;
		 std::vector< std::vector< double > > allvEvIDSD2muPOL100;
		 std::vector< std::vector< double > > allvEdepSD2muPOL100;
		 std::vector< std::vector< double > > allvEvIDSDTmuPOL100;
		 std::vector< std::vector< double > > allvEdepSDTmuPOL100;
		 std::vector< std::vector< double > > allvEvIDSDBmuPOL100;
		 std::vector< std::vector< double > > allvEdepSDBmuPOL100;
		 std::vector< std::vector< double > > allvEvIDSDLmuPOL100;
		 std::vector< std::vector< double > > allvEdepSDLmuPOL100;
		 std::vector< std::vector< double > > allvEvIDSDRmuPOL100;
		 std::vector< std::vector< double > > allvEdepSDRmuPOL100;
		 std::vector< std::vector< double > > allvEvIDBD1muPOL100;
		 std::vector< std::vector< double > > allvEdepBD1muPOL100;

		 std::vector< std::vector< double > > allvEvIDSD1muPOL110;
		 std::vector< std::vector< double > > allvEdepSD1muPOL110;
		 std::vector< std::vector< double > > allvEvIDSD2muPOL110;
		 std::vector< std::vector< double > > allvEdepSD2muPOL110;
		 std::vector< std::vector< double > > allvEvIDSDTmuPOL110;
		 std::vector< std::vector< double > > allvEdepSDTmuPOL110;
		 std::vector< std::vector< double > > allvEvIDSDBmuPOL110;
		 std::vector< std::vector< double > > allvEdepSDBmuPOL110;
		 std::vector< std::vector< double > > allvEvIDSDLmuPOL110;
		 std::vector< std::vector< double > > allvEdepSDLmuPOL110;
		 std::vector< std::vector< double > > allvEvIDSDRmuPOL110;
		 std::vector< std::vector< double > > allvEdepSDRmuPOL110;
		 std::vector< std::vector< double > > allvEvIDBD1muPOL110;
		 std::vector< std::vector< double > > allvEdepBD1muPOL110;

		 std::vector< std::vector< double > > allvEvIDSD1muPOL101;
		 std::vector< std::vector< double > > allvEdepSD1muPOL101;
		 std::vector< std::vector< double > > allvEvIDSD2muPOL101;
		 std::vector< std::vector< double > > allvEdepSD2muPOL101;
		 std::vector< std::vector< double > > allvEvIDSDTmuPOL101;
		 std::vector< std::vector< double > > allvEdepSDTmuPOL101;
		 std::vector< std::vector< double > > allvEvIDSDBmuPOL101;
		 std::vector< std::vector< double > > allvEdepSDBmuPOL101;
		 std::vector< std::vector< double > > allvEvIDSDLmuPOL101;
		 std::vector< std::vector< double > > allvEdepSDLmuPOL101;
		 std::vector< std::vector< double > > allvEvIDSDRmuPOL101;
		 std::vector< std::vector< double > > allvEdepSDRmuPOL101;
		 std::vector< std::vector< double > > allvEvIDBD1muPOL101;
		 std::vector< std::vector< double > > allvEdepBD1muPOL101;

		 std::vector< std::vector< double > > allvEvIDSD1muPOL011;
		 std::vector< std::vector< double > > allvEdepSD1muPOL011;
		 std::vector< std::vector< double > > allvEvIDSD2muPOL011;
		 std::vector< std::vector< double > > allvEdepSD2muPOL011;
		 std::vector< std::vector< double > > allvEvIDSDTmuPOL011;
		 std::vector< std::vector< double > > allvEdepSDTmuPOL011;
		 std::vector< std::vector< double > > allvEvIDSDBmuPOL011;
		 std::vector< std::vector< double > > allvEdepSDBmuPOL011;
		 std::vector< std::vector< double > > allvEvIDSDLmuPOL011;
		 std::vector< std::vector< double > > allvEdepSDLmuPOL011;
		 std::vector< std::vector< double > > allvEvIDSDRmuPOL011;
		 std::vector< std::vector< double > > allvEdepSDRmuPOL011;
		 std::vector< std::vector< double > > allvEvIDBD1muPOL011;
		 std::vector< std::vector< double > > allvEdepBD1muPOL011;

		 std::vector< std::vector< double > > allvEvIDSD1muPOL111;
		 std::vector< std::vector< double > > allvEdepSD1muPOL111;
		 std::vector< std::vector< double > > allvEvIDSD2muPOL111;
		 std::vector< std::vector< double > > allvEdepSD2muPOL111;
		 std::vector< std::vector< double > > allvEvIDSDTmuPOL111;
		 std::vector< std::vector< double > > allvEdepSDTmuPOL111;
		 std::vector< std::vector< double > > allvEvIDSDBmuPOL111;
		 std::vector< std::vector< double > > allvEdepSDBmuPOL111;
		 std::vector< std::vector< double > > allvEvIDSDLmuPOL111;
		 std::vector< std::vector< double > > allvEdepSDLmuPOL111;
		 std::vector< std::vector< double > > allvEvIDSDRmuPOL111;
		 std::vector< std::vector< double > > allvEdepSDRmuPOL111;
		 std::vector< std::vector< double > > allvEvIDBD1muPOL111;
		 std::vector< std::vector< double > > allvEdepBD1muPOL111;

		 float Ethr;
		 int countereeN2 = 1e5;
		 int eXrayPOL000noST = 0;
		 int eelecPOL000noST = 0;
		 int eXrayPOL000 = 0; // electrons i-fied as X-rays
		 int eelecPOL000 = 0; // electrons i-fied as electrons
		 int eXrayPOL001 = 0;
		 int eelecPOL001 = 0;
		 int eXrayPOL010 = 0;
		 int eelecPOL010 = 0;
		 int eXrayPOL100 = 0;
		 int eelecPOL100 = 0;
		 int eXrayPOL110 = 0;
		 int eelecPOL110 = 0;
		 int eXrayPOL101 = 0;
		 int eelecPOL101 = 0;
		 int eXrayPOL011 = 0;
		 int eelecPOL011 = 0;
		 int eXrayPOL111 = 0;
		 int eelecPOL111 = 0;
		   
		 Ethrmu[0] = 0;
		 for (int i=1; i<nsamps; i++) Ethrmu[i] = Ethrmu[i-1] + Estep;


		 //-------------------------------------------------------------------
		 //                           Reading
		 //-------------------------------------------------------------------
		   
		 std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
		 std::cout << "\033[1;34m---------------------- Reading ---------------------------\033[0m" << std::endl;
		 std::cout << "\033[1;34m------------------- X-ray cascade ------------------------\033[0m" << std::endl;
		 std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;


		 for (int k=0; k<((mufiles.size())/63); k++) {
			  
			// Polarization X0-Y0-Z0 without SpinTracking  
		    // SciD1POL000noST
			std::ifstream mufSciD1POL000noST(TString(mufiles[k*63]));
			std::vector<double> vEvIDSD1muPOL000noST;
			std::vector<double> vEdepSD1muPOL000noST;
			  
			while (!mufSciD1POL000noST.eof()) {
			   double EvIDSD1POL000noST, EdepSD1POL000noST;
			   mufSciD1POL000noST >> EvIDSD1POL000noST >> EdepSD1POL000noST;
			   vEvIDSD1muPOL000noST.push_back(EvIDSD1POL000noST);
			   vEdepSD1muPOL000noST.push_back(EdepSD1POL000noST);
			}
			vEvIDSD1muPOL000noST.pop_back(); vEdepSD1muPOL000noST.pop_back();
			vEvIDSD1muPOL000noST.pop_back(); vEdepSD1muPOL000noST.pop_back();
			  
			mufSciD1POL000noST.close();
			allvEvIDSD1muPOL000noST.push_back(vEvIDSD1muPOL000noST);
			allvEdepSD1muPOL000noST.push_back(vEdepSD1muPOL000noST);


			// SciD2POL000noST
			std::ifstream mufSciD2POL000noST(TString(mufiles[(k*63)+1]));
			std::vector<double> vEvIDSD2muPOL000noST;
			std::vector<double> vEdepSD2muPOL000noST;
			  
			while (!mufSciD2POL000noST.eof()) {
			   double EvIDSD2POL000noST, EdepSD2POL000noST;
			   mufSciD2POL000noST >> EvIDSD2POL000noST >> EdepSD2POL000noST;
			   vEvIDSD2muPOL000noST.push_back(EvIDSD2POL000noST);
			   vEdepSD2muPOL000noST.push_back(EdepSD2POL000noST);
			}
			vEvIDSD2muPOL000noST.pop_back(); vEdepSD2muPOL000noST.pop_back();
			vEvIDSD2muPOL000noST.pop_back(); vEdepSD2muPOL000noST.pop_back();
			  
			mufSciD2POL000noST.close();
			allvEvIDSD2muPOL000noST.push_back(vEvIDSD2muPOL000noST);
			allvEdepSD2muPOL000noST.push_back(vEdepSD2muPOL000noST);
			  
			  
			// SciDTPOL000noST
			std::ifstream mufSciDTPOL000noST(TString(mufiles[(k*63)+2]));
			std::vector<double> vEvIDSDTmuPOL000noST;
			std::vector<double> vEdepSDTmuPOL000noST;
			  
			while (!mufSciDTPOL000noST.eof()) {
			   double EvIDSDTPOL000noST, EdepSDTPOL000noST;
			   mufSciDTPOL000noST >> EvIDSDTPOL000noST >> EdepSDTPOL000noST;
			   vEvIDSDTmuPOL000noST.push_back(EvIDSDTPOL000noST);
			   vEdepSDTmuPOL000noST.push_back(EdepSDTPOL000noST);
			}
			vEvIDSDTmuPOL000noST.pop_back(); vEdepSDTmuPOL000noST.pop_back();
			vEvIDSDTmuPOL000noST.pop_back(); vEdepSDTmuPOL000noST.pop_back();
			  
			mufSciDTPOL000noST.close();
			allvEvIDSDTmuPOL000noST.push_back(vEvIDSDTmuPOL000noST);
			allvEdepSDTmuPOL000noST.push_back(vEdepSDTmuPOL000noST);


			// SciDBPOL000noST
			std::ifstream mufSciDBPOL000noST(TString(mufiles[(k*63)+3]));
			std::vector<double> vEvIDSDBmuPOL000noST;
			std::vector<double> vEdepSDBmuPOL000noST;
			  
			while (!mufSciDBPOL000noST.eof()) {
			   double EvIDSDBPOL000noST, EdepSDBPOL000noST;
			   mufSciDBPOL000noST >> EvIDSDBPOL000noST >> EdepSDBPOL000noST;
			   vEvIDSDBmuPOL000noST.push_back(EvIDSDBPOL000noST);
			   vEdepSDBmuPOL000noST.push_back(EdepSDBPOL000noST);
			}
			vEvIDSDBmuPOL000noST.pop_back(); vEdepSDBmuPOL000noST.pop_back();
			vEvIDSDBmuPOL000noST.pop_back(); vEdepSDBmuPOL000noST.pop_back();
			  
			mufSciDBPOL000noST.close();
			allvEvIDSDBmuPOL000noST.push_back(vEvIDSDBmuPOL000noST);
			allvEdepSDBmuPOL000noST.push_back(vEdepSDBmuPOL000noST);


			// SciDLPOL000noST
			std::ifstream mufSciDLPOL000noST(TString(mufiles[(k*63)+4]));
			std::vector<double> vEvIDSDLmuPOL000noST;
			std::vector<double> vEdepSDLmuPOL000noST;
			  
			while (!mufSciDLPOL000noST.eof()) {
			   double EvIDSDLPOL000noST, EdepSDLPOL000noST;
			   mufSciDLPOL000noST >> EvIDSDLPOL000noST >> EdepSDLPOL000noST;
			   vEvIDSDLmuPOL000noST.push_back(EvIDSDLPOL000noST);
			   vEdepSDLmuPOL000noST.push_back(EdepSDLPOL000noST);
			}
			vEvIDSDLmuPOL000noST.pop_back(); vEdepSDLmuPOL000noST.pop_back();
			vEvIDSDLmuPOL000noST.pop_back(); vEdepSDLmuPOL000noST.pop_back();
			  
			mufSciDLPOL000noST.close();
			allvEvIDSDLmuPOL000noST.push_back(vEvIDSDLmuPOL000noST);
			allvEdepSDLmuPOL000noST.push_back(vEdepSDLmuPOL000noST);


			// SciDRPOL000noST
			std::ifstream mufSciDRPOL000noST(TString(mufiles[(k*63)+5]));
			std::vector<double> vEvIDSDRmuPOL000noST;
			std::vector<double> vEdepSDRmuPOL000noST;
			  
			while (!mufSciDRPOL000noST.eof()) {
			   double EvIDSDRPOL000noST, EdepSDRPOL000noST;
			   mufSciDRPOL000noST >> EvIDSDRPOL000noST >> EdepSDRPOL000noST;
			   vEvIDSDRmuPOL000noST.push_back(EvIDSDRPOL000noST);
			   vEdepSDRmuPOL000noST.push_back(EdepSDRPOL000noST);
			}
			vEvIDSDRmuPOL000noST.pop_back(); vEdepSDRmuPOL000noST.pop_back();
			vEvIDSDRmuPOL000noST.pop_back(); vEdepSDRmuPOL000noST.pop_back();
			  
			mufSciDRPOL000noST.close();
			allvEvIDSDRmuPOL000noST.push_back(vEvIDSDRmuPOL000noST);
			allvEdepSDRmuPOL000noST.push_back(vEdepSDRmuPOL000noST);


			// BGOD1POL000noST
			std::ifstream mufBGOD1POL000noST(TString(mufiles[(k*63)+6]));
			std::vector<double> vEvIDBD1muPOL000noST;
			std::vector<double> vEdepBD1muPOL000noST;
			  
			while (!mufBGOD1POL000noST.eof()) {
			   double EvIDBD1POL000noST, EdepBD1POL000noST;
			   mufBGOD1POL000noST >> EvIDBD1POL000noST >> EdepBD1POL000noST;
			   vEvIDBD1muPOL000noST.push_back(EvIDBD1POL000noST);
			   vEdepBD1muPOL000noST.push_back(EdepBD1POL000noST);
			}
			vEvIDBD1muPOL000noST.pop_back(); vEdepBD1muPOL000noST.pop_back();
			vEvIDBD1muPOL000noST.pop_back(); vEdepBD1muPOL000noST.pop_back();
			  
			mufBGOD1POL000noST.close();
			allvEvIDBD1muPOL000noST.push_back(vEvIDBD1muPOL000noST);
			allvEdepBD1muPOL000noST.push_back(vEdepBD1muPOL000noST);



			// Polarization X0-Y0-Z0  
		    // SciD1POL000
			std::ifstream mufSciD1POL000(TString(mufiles[(k*63)+7]));
			std::vector<double> vEvIDSD1muPOL000;
			std::vector<double> vEdepSD1muPOL000;
			  
			while (!mufSciD1POL000.eof()) {
			   double EvIDSD1POL000, EdepSD1POL000;
			   mufSciD1POL000 >> EvIDSD1POL000 >> EdepSD1POL000;
			   vEvIDSD1muPOL000.push_back(EvIDSD1POL000);
			   vEdepSD1muPOL000.push_back(EdepSD1POL000);
			}
			vEvIDSD1muPOL000.pop_back(); vEdepSD1muPOL000.pop_back();
			vEvIDSD1muPOL000.pop_back(); vEdepSD1muPOL000.pop_back();
			  
			mufSciD1POL000.close();
			allvEvIDSD1muPOL000.push_back(vEvIDSD1muPOL000);
			allvEdepSD1muPOL000.push_back(vEdepSD1muPOL000);


			// SciD2POL000
			std::ifstream mufSciD2POL000(TString(mufiles[(k*63)+8]));
			std::vector<double> vEvIDSD2muPOL000;
			std::vector<double> vEdepSD2muPOL000;
			  
			while (!mufSciD2POL000.eof()) {
			   double EvIDSD2POL000, EdepSD2POL000;
			   mufSciD2POL000 >> EvIDSD2POL000 >> EdepSD2POL000;
			   vEvIDSD2muPOL000.push_back(EvIDSD2POL000);
			   vEdepSD2muPOL000.push_back(EdepSD2POL000);
			}
			vEvIDSD2muPOL000.pop_back(); vEdepSD2muPOL000.pop_back();
			vEvIDSD2muPOL000.pop_back(); vEdepSD2muPOL000.pop_back();
			  
			mufSciD2POL000.close();
			allvEvIDSD2muPOL000.push_back(vEvIDSD2muPOL000);
			allvEdepSD2muPOL000.push_back(vEdepSD2muPOL000);
			  
			  
			// SciDTPOL000
			std::ifstream mufSciDTPOL000(TString(mufiles[(k*63)+9]));
			std::vector<double> vEvIDSDTmuPOL000;
			std::vector<double> vEdepSDTmuPOL000;
			  
			while (!mufSciDTPOL000.eof()) {
			   double EvIDSDTPOL000, EdepSDTPOL000;
			   mufSciDTPOL000 >> EvIDSDTPOL000 >> EdepSDTPOL000;
			   vEvIDSDTmuPOL000.push_back(EvIDSDTPOL000);
			   vEdepSDTmuPOL000.push_back(EdepSDTPOL000);
			}
			vEvIDSDTmuPOL000.pop_back(); vEdepSDTmuPOL000.pop_back();
			vEvIDSDTmuPOL000.pop_back(); vEdepSDTmuPOL000.pop_back();
			  
			mufSciDTPOL000.close();
			allvEvIDSDTmuPOL000.push_back(vEvIDSDTmuPOL000);
			allvEdepSDTmuPOL000.push_back(vEdepSDTmuPOL000);


			// SciDBPOL000
			std::ifstream mufSciDBPOL000(TString(mufiles[(k*63)+10]));
			std::vector<double> vEvIDSDBmuPOL000;
			std::vector<double> vEdepSDBmuPOL000;
			  
			while (!mufSciDBPOL000.eof()) {
			   double EvIDSDBPOL000, EdepSDBPOL000;
			   mufSciDBPOL000 >> EvIDSDBPOL000 >> EdepSDBPOL000;
			   vEvIDSDBmuPOL000.push_back(EvIDSDBPOL000);
			   vEdepSDBmuPOL000.push_back(EdepSDBPOL000);
			}
			vEvIDSDBmuPOL000.pop_back(); vEdepSDBmuPOL000.pop_back();
			vEvIDSDBmuPOL000.pop_back(); vEdepSDBmuPOL000.pop_back();
			  
			mufSciDBPOL000.close();
			allvEvIDSDBmuPOL000.push_back(vEvIDSDBmuPOL000);
			allvEdepSDBmuPOL000.push_back(vEdepSDBmuPOL000);


			// SciDLPOL000
			std::ifstream mufSciDLPOL000(TString(mufiles[(k*63)+11]));
			std::vector<double> vEvIDSDLmuPOL000;
			std::vector<double> vEdepSDLmuPOL000;
			  
			while (!mufSciDLPOL000.eof()) {
			   double EvIDSDLPOL000, EdepSDLPOL000;
			   mufSciDLPOL000 >> EvIDSDLPOL000 >> EdepSDLPOL000;
			   vEvIDSDLmuPOL000.push_back(EvIDSDLPOL000);
			   vEdepSDLmuPOL000.push_back(EdepSDLPOL000);
			}
			vEvIDSDLmuPOL000.pop_back(); vEdepSDLmuPOL000.pop_back();
			vEvIDSDLmuPOL000.pop_back(); vEdepSDLmuPOL000.pop_back();
			  
			mufSciDLPOL000.close();
			allvEvIDSDLmuPOL000.push_back(vEvIDSDLmuPOL000);
			allvEdepSDLmuPOL000.push_back(vEdepSDLmuPOL000);


			// SciDRPOL000
			std::ifstream mufSciDRPOL000(TString(mufiles[(k*63)+12]));
			std::vector<double> vEvIDSDRmuPOL000;
			std::vector<double> vEdepSDRmuPOL000;
			  
			while (!mufSciDRPOL000.eof()) {
			   double EvIDSDRPOL000, EdepSDRPOL000;
			   mufSciDRPOL000 >> EvIDSDRPOL000 >> EdepSDRPOL000;
			   vEvIDSDRmuPOL000.push_back(EvIDSDRPOL000);
			   vEdepSDRmuPOL000.push_back(EdepSDRPOL000);
			}
			vEvIDSDRmuPOL000.pop_back(); vEdepSDRmuPOL000.pop_back();
			vEvIDSDRmuPOL000.pop_back(); vEdepSDRmuPOL000.pop_back();
			  
			mufSciDRPOL000.close();
			allvEvIDSDRmuPOL000.push_back(vEvIDSDRmuPOL000);
			allvEdepSDRmuPOL000.push_back(vEdepSDRmuPOL000);


			// BGOD1POL000
			std::ifstream mufBGOD1POL000(TString(mufiles[(k*63)+13]));
			std::vector<double> vEvIDBD1muPOL000;
			std::vector<double> vEdepBD1muPOL000;
			  
			while (!mufBGOD1POL000.eof()) {
			   double EvIDBD1POL000, EdepBD1POL000;
			   mufBGOD1POL000 >> EvIDBD1POL000 >> EdepBD1POL000;
			   vEvIDBD1muPOL000.push_back(EvIDBD1POL000);
			   vEdepBD1muPOL000.push_back(EdepBD1POL000);
			}
			vEvIDBD1muPOL000.pop_back(); vEdepBD1muPOL000.pop_back();
			vEvIDBD1muPOL000.pop_back(); vEdepBD1muPOL000.pop_back();
			  
			mufBGOD1POL000.close();
			allvEvIDBD1muPOL000.push_back(vEvIDBD1muPOL000);
			allvEdepBD1muPOL000.push_back(vEdepBD1muPOL000);



			// Polarization X0-Y0-Z1  
		    // SciD1POL001
			std::ifstream mufSciD1POL001(TString(mufiles[(k*63)+14]));
			std::vector<double> vEvIDSD1muPOL001;
			std::vector<double> vEdepSD1muPOL001;
			  
			while (!mufSciD1POL001.eof()) {
			   double EvIDSD1POL001, EdepSD1POL001;
			   mufSciD1POL001 >> EvIDSD1POL001 >> EdepSD1POL001;
			   vEvIDSD1muPOL001.push_back(EvIDSD1POL001);
			   vEdepSD1muPOL001.push_back(EdepSD1POL001);
			}
			vEvIDSD1muPOL001.pop_back(); vEdepSD1muPOL001.pop_back();
			vEvIDSD1muPOL001.pop_back(); vEdepSD1muPOL001.pop_back();
			  
			mufSciD1POL001.close();
			allvEvIDSD1muPOL001.push_back(vEvIDSD1muPOL001);
			allvEdepSD1muPOL001.push_back(vEdepSD1muPOL001);


			// SciD2POL001
			std::ifstream mufSciD2POL001(TString(mufiles[(k*63)+15]));
			std::vector<double> vEvIDSD2muPOL001;
			std::vector<double> vEdepSD2muPOL001;
			  
			while (!mufSciD2POL001.eof()) {
			   double EvIDSD2POL001, EdepSD2POL001;
			   mufSciD2POL001 >> EvIDSD2POL001 >> EdepSD2POL001;
			   vEvIDSD2muPOL001.push_back(EvIDSD2POL001);
			   vEdepSD2muPOL001.push_back(EdepSD2POL001);
			}
			vEvIDSD2muPOL001.pop_back(); vEdepSD2muPOL001.pop_back();
			vEvIDSD2muPOL001.pop_back(); vEdepSD2muPOL001.pop_back();
			  
			mufSciD2POL001.close();
			allvEvIDSD2muPOL001.push_back(vEvIDSD2muPOL001);
			allvEdepSD2muPOL001.push_back(vEdepSD2muPOL001);
			  
			  
			// SciDTPOL001
			std::ifstream mufSciDTPOL001(TString(mufiles[(k*63)+16]));
			std::vector<double> vEvIDSDTmuPOL001;
			std::vector<double> vEdepSDTmuPOL001;
			  
			while (!mufSciDTPOL001.eof()) {
			   double EvIDSDTPOL001, EdepSDTPOL001;
			   mufSciDTPOL001 >> EvIDSDTPOL001 >> EdepSDTPOL001;
			   vEvIDSDTmuPOL001.push_back(EvIDSDTPOL001);
			   vEdepSDTmuPOL001.push_back(EdepSDTPOL001);
			}
			vEvIDSDTmuPOL001.pop_back(); vEdepSDTmuPOL001.pop_back();
			vEvIDSDTmuPOL001.pop_back(); vEdepSDTmuPOL001.pop_back();
			  
			mufSciDTPOL001.close();
			allvEvIDSDTmuPOL001.push_back(vEvIDSDTmuPOL001);
			allvEdepSDTmuPOL001.push_back(vEdepSDTmuPOL001);


			// SciDBPOL001
			std::ifstream mufSciDBPOL001(TString(mufiles[(k*63)+17]));
			std::vector<double> vEvIDSDBmuPOL001;
			std::vector<double> vEdepSDBmuPOL001;
			  
			while (!mufSciDBPOL001.eof()) {
			   double EvIDSDBPOL001, EdepSDBPOL001;
			   mufSciDBPOL001 >> EvIDSDBPOL001 >> EdepSDBPOL001;
			   vEvIDSDBmuPOL001.push_back(EvIDSDBPOL001);
			   vEdepSDBmuPOL001.push_back(EdepSDBPOL001);
			}
			vEvIDSDBmuPOL001.pop_back(); vEdepSDBmuPOL001.pop_back();
			vEvIDSDBmuPOL001.pop_back(); vEdepSDBmuPOL001.pop_back();
			  
			mufSciDBPOL001.close();
			allvEvIDSDBmuPOL001.push_back(vEvIDSDBmuPOL001);
			allvEdepSDBmuPOL001.push_back(vEdepSDBmuPOL001);


			// SciDLPOL001
			std::ifstream mufSciDLPOL001(TString(mufiles[(k*63)+18]));
			std::vector<double> vEvIDSDLmuPOL001;
			std::vector<double> vEdepSDLmuPOL001;
			  
			while (!mufSciDLPOL001.eof()) {
			   double EvIDSDLPOL001, EdepSDLPOL001;
			   mufSciDLPOL001 >> EvIDSDLPOL001 >> EdepSDLPOL001;
			   vEvIDSDLmuPOL001.push_back(EvIDSDLPOL001);
			   vEdepSDLmuPOL001.push_back(EdepSDLPOL001);
			}
			vEvIDSDLmuPOL001.pop_back(); vEdepSDLmuPOL001.pop_back();
			vEvIDSDLmuPOL001.pop_back(); vEdepSDLmuPOL001.pop_back();
			  
			mufSciDLPOL001.close();
			allvEvIDSDLmuPOL001.push_back(vEvIDSDLmuPOL001);
			allvEdepSDLmuPOL001.push_back(vEdepSDLmuPOL001);


			// SciDRPOL001
			std::ifstream mufSciDRPOL001(TString(mufiles[(k*63)+19]));
			std::vector<double> vEvIDSDRmuPOL001;
			std::vector<double> vEdepSDRmuPOL001;
			  
			while (!mufSciDRPOL001.eof()) {
			   double EvIDSDRPOL001, EdepSDRPOL001;
			   mufSciDRPOL001 >> EvIDSDRPOL001 >> EdepSDRPOL001;
			   vEvIDSDRmuPOL001.push_back(EvIDSDRPOL001);
			   vEdepSDRmuPOL001.push_back(EdepSDRPOL001);
			}
			vEvIDSDRmuPOL001.pop_back(); vEdepSDRmuPOL001.pop_back();
			vEvIDSDRmuPOL001.pop_back(); vEdepSDRmuPOL001.pop_back();
			  
			mufSciDRPOL001.close();
			allvEvIDSDRmuPOL001.push_back(vEvIDSDRmuPOL001);
			allvEdepSDRmuPOL001.push_back(vEdepSDRmuPOL001);


			// BGOD1POL001
			std::ifstream mufBGOD1POL001(TString(mufiles[(k*63)+20]));
			std::vector<double> vEvIDBD1muPOL001;
			std::vector<double> vEdepBD1muPOL001;
			  
			while (!mufBGOD1POL001.eof()) {
			   double EvIDBD1POL001, EdepBD1POL001;
			   mufBGOD1POL001 >> EvIDBD1POL001 >> EdepBD1POL001;
			   vEvIDBD1muPOL001.push_back(EvIDBD1POL001);
			   vEdepBD1muPOL001.push_back(EdepBD1POL001);
			}
			vEvIDBD1muPOL001.pop_back(); vEdepBD1muPOL001.pop_back();
			vEvIDBD1muPOL001.pop_back(); vEdepBD1muPOL001.pop_back();
			  
			mufBGOD1POL001.close();
			allvEvIDBD1muPOL001.push_back(vEvIDBD1muPOL001);
			allvEdepBD1muPOL001.push_back(vEdepBD1muPOL001);



			// Polarization X0-Y1-Z0  
		    // SciD1POL010
			std::ifstream mufSciD1POL010(TString(mufiles[(k*63)+21]));
			std::vector<double> vEvIDSD1muPOL010;
			std::vector<double> vEdepSD1muPOL010;
			  
			while (!mufSciD1POL010.eof()) {
			   double EvIDSD1POL010, EdepSD1POL010;
			   mufSciD1POL010 >> EvIDSD1POL010 >> EdepSD1POL010;
			   vEvIDSD1muPOL010.push_back(EvIDSD1POL010);
			   vEdepSD1muPOL010.push_back(EdepSD1POL010);
			}
			vEvIDSD1muPOL010.pop_back(); vEdepSD1muPOL010.pop_back();
			vEvIDSD1muPOL010.pop_back(); vEdepSD1muPOL010.pop_back();
			  
			mufSciD1POL010.close();
			allvEvIDSD1muPOL010.push_back(vEvIDSD1muPOL010);
			allvEdepSD1muPOL010.push_back(vEdepSD1muPOL010);


			// SciD2POL010
			std::ifstream mufSciD2POL010(TString(mufiles[(k*63)+22]));
			std::vector<double> vEvIDSD2muPOL010;
			std::vector<double> vEdepSD2muPOL010;
			  
			while (!mufSciD2POL010.eof()) {
			   double EvIDSD2POL010, EdepSD2POL010;
			   mufSciD2POL010 >> EvIDSD2POL010 >> EdepSD2POL010;
			   vEvIDSD2muPOL010.push_back(EvIDSD2POL010);
			   vEdepSD2muPOL010.push_back(EdepSD2POL010);
			}
			vEvIDSD2muPOL010.pop_back(); vEdepSD2muPOL010.pop_back();
			vEvIDSD2muPOL010.pop_back(); vEdepSD2muPOL010.pop_back();
			  
			mufSciD2POL010.close();
			allvEvIDSD2muPOL010.push_back(vEvIDSD2muPOL010);
			allvEdepSD2muPOL010.push_back(vEdepSD2muPOL010);
			  
			  
			// SciDTPOL010
			std::ifstream mufSciDTPOL010(TString(mufiles[(k*63)+23]));
			std::vector<double> vEvIDSDTmuPOL010;
			std::vector<double> vEdepSDTmuPOL010;
			  
			while (!mufSciDTPOL010.eof()) {
			   double EvIDSDTPOL010, EdepSDTPOL010;
			   mufSciDTPOL010 >> EvIDSDTPOL010 >> EdepSDTPOL010;
			   vEvIDSDTmuPOL010.push_back(EvIDSDTPOL010);
			   vEdepSDTmuPOL010.push_back(EdepSDTPOL010);
			}
			vEvIDSDTmuPOL010.pop_back(); vEdepSDTmuPOL010.pop_back();
			vEvIDSDTmuPOL010.pop_back(); vEdepSDTmuPOL010.pop_back();
			  
			mufSciDTPOL010.close();
			allvEvIDSDTmuPOL010.push_back(vEvIDSDTmuPOL010);
			allvEdepSDTmuPOL010.push_back(vEdepSDTmuPOL010);


			// SciDBPOL010
			std::ifstream mufSciDBPOL010(TString(mufiles[(k*63)+24]));
			std::vector<double> vEvIDSDBmuPOL010;
			std::vector<double> vEdepSDBmuPOL010;
			  
			while (!mufSciDBPOL010.eof()) {
			   double EvIDSDBPOL010, EdepSDBPOL010;
			   mufSciDBPOL010 >> EvIDSDBPOL010 >> EdepSDBPOL010;
			   vEvIDSDBmuPOL010.push_back(EvIDSDBPOL010);
			   vEdepSDBmuPOL010.push_back(EdepSDBPOL010);
			}
			vEvIDSDBmuPOL010.pop_back(); vEdepSDBmuPOL010.pop_back();
			vEvIDSDBmuPOL010.pop_back(); vEdepSDBmuPOL010.pop_back();
			  
			mufSciDBPOL010.close();
			allvEvIDSDBmuPOL010.push_back(vEvIDSDBmuPOL010);
			allvEdepSDBmuPOL010.push_back(vEdepSDBmuPOL010);


			// SciDLPOL010
			std::ifstream mufSciDLPOL010(TString(mufiles[(k*63)+25]));
			std::vector<double> vEvIDSDLmuPOL010;
			std::vector<double> vEdepSDLmuPOL010;
			  
			while (!mufSciDLPOL010.eof()) {
			   double EvIDSDLPOL010, EdepSDLPOL010;
			   mufSciDLPOL010 >> EvIDSDLPOL010 >> EdepSDLPOL010;
			   vEvIDSDLmuPOL010.push_back(EvIDSDLPOL010);
			   vEdepSDLmuPOL010.push_back(EdepSDLPOL010);
			}
			vEvIDSDLmuPOL010.pop_back(); vEdepSDLmuPOL010.pop_back();
			vEvIDSDLmuPOL010.pop_back(); vEdepSDLmuPOL010.pop_back();
			  
			mufSciDLPOL010.close();
			allvEvIDSDLmuPOL010.push_back(vEvIDSDLmuPOL010);
			allvEdepSDLmuPOL010.push_back(vEdepSDLmuPOL010);


			// SciDRPOL010
			std::ifstream mufSciDRPOL010(TString(mufiles[(k*63)+26]));
			std::vector<double> vEvIDSDRmuPOL010;
			std::vector<double> vEdepSDRmuPOL010;
			  
			while (!mufSciDRPOL010.eof()) {
			   double EvIDSDRPOL010, EdepSDRPOL010;
			   mufSciDRPOL010 >> EvIDSDRPOL010 >> EdepSDRPOL010;
			   vEvIDSDRmuPOL010.push_back(EvIDSDRPOL010);
			   vEdepSDRmuPOL010.push_back(EdepSDRPOL010);
			}
			vEvIDSDRmuPOL010.pop_back(); vEdepSDRmuPOL010.pop_back();
			vEvIDSDRmuPOL010.pop_back(); vEdepSDRmuPOL010.pop_back();
			  
			mufSciDRPOL010.close();
			allvEvIDSDRmuPOL010.push_back(vEvIDSDRmuPOL010);
			allvEdepSDRmuPOL010.push_back(vEdepSDRmuPOL010);


			// BGOD1POL010
			std::ifstream mufBGOD1POL010(TString(mufiles[(k*63)+27]));
			std::vector<double> vEvIDBD1muPOL010;
			std::vector<double> vEdepBD1muPOL010;
			  
			while (!mufBGOD1POL010.eof()) {
			   double EvIDBD1POL010, EdepBD1POL010;
			   mufBGOD1POL010 >> EvIDBD1POL010 >> EdepBD1POL010;
			   vEvIDBD1muPOL010.push_back(EvIDBD1POL010);
			   vEdepBD1muPOL010.push_back(EdepBD1POL010);
			}
			vEvIDBD1muPOL010.pop_back(); vEdepBD1muPOL010.pop_back();
			vEvIDBD1muPOL010.pop_back(); vEdepBD1muPOL010.pop_back();
			  
			mufBGOD1POL010.close();
			allvEvIDBD1muPOL010.push_back(vEvIDBD1muPOL010);
			allvEdepBD1muPOL010.push_back(vEdepBD1muPOL010);



            // Polarization X1-Y0-Z0  
		    // SciD1POL100
			std::ifstream mufSciD1POL100(TString(mufiles[(k*63)+28]));
			std::vector<double> vEvIDSD1muPOL100;
			std::vector<double> vEdepSD1muPOL100;
			  
			while (!mufSciD1POL100.eof()) {
			   double EvIDSD1POL100, EdepSD1POL100;
			   mufSciD1POL100 >> EvIDSD1POL100 >> EdepSD1POL100;
			   vEvIDSD1muPOL100.push_back(EvIDSD1POL100);
			   vEdepSD1muPOL100.push_back(EdepSD1POL100);
			}
			vEvIDSD1muPOL100.pop_back(); vEdepSD1muPOL100.pop_back();
			vEvIDSD1muPOL100.pop_back(); vEdepSD1muPOL100.pop_back();
			  
			mufSciD1POL100.close();
			allvEvIDSD1muPOL100.push_back(vEvIDSD1muPOL100);
			allvEdepSD1muPOL100.push_back(vEdepSD1muPOL100);


			// SciD2POL100
			std::ifstream mufSciD2POL100(TString(mufiles[(k*63)+29]));
			std::vector<double> vEvIDSD2muPOL100;
			std::vector<double> vEdepSD2muPOL100;
			  
			while (!mufSciD2POL100.eof()) {
			   double EvIDSD2POL100, EdepSD2POL100;
			   mufSciD2POL100 >> EvIDSD2POL100 >> EdepSD2POL100;
			   vEvIDSD2muPOL100.push_back(EvIDSD2POL100);
			   vEdepSD2muPOL100.push_back(EdepSD2POL100);
			}
			vEvIDSD2muPOL100.pop_back(); vEdepSD2muPOL100.pop_back();
			vEvIDSD2muPOL100.pop_back(); vEdepSD2muPOL100.pop_back();
			  
			mufSciD2POL100.close();
			allvEvIDSD2muPOL100.push_back(vEvIDSD2muPOL100);
			allvEdepSD2muPOL100.push_back(vEdepSD2muPOL100);
			  
			  
			// SciDTPOL100
			std::ifstream mufSciDTPOL100(TString(mufiles[(k*63)+30]));
			std::vector<double> vEvIDSDTmuPOL100;
			std::vector<double> vEdepSDTmuPOL100;
			  
			while (!mufSciDTPOL100.eof()) {
			   double EvIDSDTPOL100, EdepSDTPOL100;
			   mufSciDTPOL100 >> EvIDSDTPOL100 >> EdepSDTPOL100;
			   vEvIDSDTmuPOL100.push_back(EvIDSDTPOL100);
			   vEdepSDTmuPOL100.push_back(EdepSDTPOL100);
			}
			vEvIDSDTmuPOL100.pop_back(); vEdepSDTmuPOL100.pop_back();
			vEvIDSDTmuPOL100.pop_back(); vEdepSDTmuPOL100.pop_back();
			  
			mufSciDTPOL100.close();
			allvEvIDSDTmuPOL100.push_back(vEvIDSDTmuPOL100);
			allvEdepSDTmuPOL100.push_back(vEdepSDTmuPOL100);


			// SciDBPOL100
			std::ifstream mufSciDBPOL100(TString(mufiles[(k*63)+31]));
			std::vector<double> vEvIDSDBmuPOL100;
			std::vector<double> vEdepSDBmuPOL100;
			  
			while (!mufSciDBPOL100.eof()) {
			   double EvIDSDBPOL100, EdepSDBPOL100;
			   mufSciDBPOL100 >> EvIDSDBPOL100 >> EdepSDBPOL100;
			   vEvIDSDBmuPOL100.push_back(EvIDSDBPOL100);
			   vEdepSDBmuPOL100.push_back(EdepSDBPOL100);
			}
			vEvIDSDBmuPOL100.pop_back(); vEdepSDBmuPOL100.pop_back();
			vEvIDSDBmuPOL100.pop_back(); vEdepSDBmuPOL100.pop_back();
			  
			mufSciDBPOL100.close();
			allvEvIDSDBmuPOL100.push_back(vEvIDSDBmuPOL100);
			allvEdepSDBmuPOL100.push_back(vEdepSDBmuPOL100);


			// SciDLPOL100
			std::ifstream mufSciDLPOL100(TString(mufiles[(k*63)+32]));
			std::vector<double> vEvIDSDLmuPOL100;
			std::vector<double> vEdepSDLmuPOL100;
			  
			while (!mufSciDLPOL100.eof()) {
			   double EvIDSDLPOL100, EdepSDLPOL100;
			   mufSciDLPOL100 >> EvIDSDLPOL100 >> EdepSDLPOL100;
			   vEvIDSDLmuPOL100.push_back(EvIDSDLPOL100);
			   vEdepSDLmuPOL100.push_back(EdepSDLPOL100);
			}
			vEvIDSDLmuPOL100.pop_back(); vEdepSDLmuPOL100.pop_back();
			vEvIDSDLmuPOL100.pop_back(); vEdepSDLmuPOL100.pop_back();
			  
			mufSciDLPOL100.close();
			allvEvIDSDLmuPOL100.push_back(vEvIDSDLmuPOL100);
			allvEdepSDLmuPOL100.push_back(vEdepSDLmuPOL100);


			// SciDRPOL100
			std::ifstream mufSciDRPOL100(TString(mufiles[(k*63)+33]));
			std::vector<double> vEvIDSDRmuPOL100;
			std::vector<double> vEdepSDRmuPOL100;
			  
			while (!mufSciDRPOL100.eof()) {
			   double EvIDSDRPOL100, EdepSDRPOL100;
			   mufSciDRPOL100 >> EvIDSDRPOL100 >> EdepSDRPOL100;
			   vEvIDSDRmuPOL100.push_back(EvIDSDRPOL100);
			   vEdepSDRmuPOL100.push_back(EdepSDRPOL100);
			}
			vEvIDSDRmuPOL100.pop_back(); vEdepSDRmuPOL100.pop_back();
			vEvIDSDRmuPOL100.pop_back(); vEdepSDRmuPOL100.pop_back();
			  
			mufSciDRPOL100.close();
			allvEvIDSDRmuPOL100.push_back(vEvIDSDRmuPOL100);
			allvEdepSDRmuPOL100.push_back(vEdepSDRmuPOL100);


			// BGOD1POL100
			std::ifstream mufBGOD1POL100(TString(mufiles[(k*63)+34]));
			std::vector<double> vEvIDBD1muPOL100;
			std::vector<double> vEdepBD1muPOL100;
			  
			while (!mufBGOD1POL100.eof()) {
			   double EvIDBD1POL100, EdepBD1POL100;
			   mufBGOD1POL100 >> EvIDBD1POL100 >> EdepBD1POL100;
			   vEvIDBD1muPOL100.push_back(EvIDBD1POL100);
			   vEdepBD1muPOL100.push_back(EdepBD1POL100);
			}
			vEvIDBD1muPOL100.pop_back(); vEdepBD1muPOL100.pop_back();
			vEvIDBD1muPOL100.pop_back(); vEdepBD1muPOL100.pop_back();
			  
			mufBGOD1POL100.close();
			allvEvIDBD1muPOL100.push_back(vEvIDBD1muPOL100);
			allvEdepBD1muPOL100.push_back(vEdepBD1muPOL100);



            // Polarization X1-Y1-Z0  
		    // SciD1POL110
			std::ifstream mufSciD1POL110(TString(mufiles[(k*63)+35]));
			std::vector<double> vEvIDSD1muPOL110;
			std::vector<double> vEdepSD1muPOL110;
			  
			while (!mufSciD1POL110.eof()) {
			   double EvIDSD1POL110, EdepSD1POL110;
			   mufSciD1POL110 >> EvIDSD1POL110 >> EdepSD1POL110;
			   vEvIDSD1muPOL110.push_back(EvIDSD1POL110);
			   vEdepSD1muPOL110.push_back(EdepSD1POL110);
			}
			vEvIDSD1muPOL110.pop_back(); vEdepSD1muPOL110.pop_back();
			vEvIDSD1muPOL110.pop_back(); vEdepSD1muPOL110.pop_back();
			  
			mufSciD1POL110.close();
			allvEvIDSD1muPOL110.push_back(vEvIDSD1muPOL110);
			allvEdepSD1muPOL110.push_back(vEdepSD1muPOL110);


			// SciD2POL110
			std::ifstream mufSciD2POL110(TString(mufiles[(k*63)+36]));
			std::vector<double> vEvIDSD2muPOL110;
			std::vector<double> vEdepSD2muPOL110;
			  
			while (!mufSciD2POL110.eof()) {
			   double EvIDSD2POL110, EdepSD2POL110;
			   mufSciD2POL110 >> EvIDSD2POL110 >> EdepSD2POL110;
			   vEvIDSD2muPOL110.push_back(EvIDSD2POL110);
			   vEdepSD2muPOL110.push_back(EdepSD2POL110);
			}
			vEvIDSD2muPOL110.pop_back(); vEdepSD2muPOL110.pop_back();
			vEvIDSD2muPOL110.pop_back(); vEdepSD2muPOL110.pop_back();
			  
			mufSciD2POL110.close();
			allvEvIDSD2muPOL110.push_back(vEvIDSD2muPOL110);
			allvEdepSD2muPOL110.push_back(vEdepSD2muPOL110);
			  
			  
			// SciDTPOL110
			std::ifstream mufSciDTPOL110(TString(mufiles[(k*63)+37]));
			std::vector<double> vEvIDSDTmuPOL110;
			std::vector<double> vEdepSDTmuPOL110;
			  
			while (!mufSciDTPOL110.eof()) {
			   double EvIDSDTPOL110, EdepSDTPOL110;
			   mufSciDTPOL110 >> EvIDSDTPOL110 >> EdepSDTPOL110;
			   vEvIDSDTmuPOL110.push_back(EvIDSDTPOL110);
			   vEdepSDTmuPOL110.push_back(EdepSDTPOL110);
			}
			vEvIDSDTmuPOL110.pop_back(); vEdepSDTmuPOL110.pop_back();
			vEvIDSDTmuPOL110.pop_back(); vEdepSDTmuPOL110.pop_back();
			  
			mufSciDTPOL110.close();
			allvEvIDSDTmuPOL110.push_back(vEvIDSDTmuPOL110);
			allvEdepSDTmuPOL110.push_back(vEdepSDTmuPOL110);


			// SciDBPOL110
			std::ifstream mufSciDBPOL110(TString(mufiles[(k*63)+38]));
			std::vector<double> vEvIDSDBmuPOL110;
			std::vector<double> vEdepSDBmuPOL110;
			  
			while (!mufSciDBPOL110.eof()) {
			   double EvIDSDBPOL110, EdepSDBPOL110;
			   mufSciDBPOL110 >> EvIDSDBPOL110 >> EdepSDBPOL110;
			   vEvIDSDBmuPOL110.push_back(EvIDSDBPOL110);
			   vEdepSDBmuPOL110.push_back(EdepSDBPOL110);
			}
			vEvIDSDBmuPOL110.pop_back(); vEdepSDBmuPOL110.pop_back();
			vEvIDSDBmuPOL110.pop_back(); vEdepSDBmuPOL110.pop_back();
			  
			mufSciDBPOL110.close();
			allvEvIDSDBmuPOL110.push_back(vEvIDSDBmuPOL110);
			allvEdepSDBmuPOL110.push_back(vEdepSDBmuPOL110);


			// SciDLPOL110
			std::ifstream mufSciDLPOL110(TString(mufiles[(k*63)+39]));
			std::vector<double> vEvIDSDLmuPOL110;
			std::vector<double> vEdepSDLmuPOL110;
			  
			while (!mufSciDLPOL110.eof()) {
			   double EvIDSDLPOL110, EdepSDLPOL110;
			   mufSciDLPOL110 >> EvIDSDLPOL110 >> EdepSDLPOL110;
			   vEvIDSDLmuPOL110.push_back(EvIDSDLPOL110);
			   vEdepSDLmuPOL110.push_back(EdepSDLPOL110);
			}
			vEvIDSDLmuPOL110.pop_back(); vEdepSDLmuPOL110.pop_back();
			vEvIDSDLmuPOL110.pop_back(); vEdepSDLmuPOL110.pop_back();
			  
			mufSciDLPOL110.close();
			allvEvIDSDLmuPOL110.push_back(vEvIDSDLmuPOL110);
			allvEdepSDLmuPOL110.push_back(vEdepSDLmuPOL110);


			// SciDRPOL110
			std::ifstream mufSciDRPOL110(TString(mufiles[(k*63)+40]));
			std::vector<double> vEvIDSDRmuPOL110;
			std::vector<double> vEdepSDRmuPOL110;
			  
			while (!mufSciDRPOL110.eof()) {
			   double EvIDSDRPOL110, EdepSDRPOL110;
			   mufSciDRPOL110 >> EvIDSDRPOL110 >> EdepSDRPOL110;
			   vEvIDSDRmuPOL110.push_back(EvIDSDRPOL110);
			   vEdepSDRmuPOL110.push_back(EdepSDRPOL110);
			}
			vEvIDSDRmuPOL110.pop_back(); vEdepSDRmuPOL110.pop_back();
			vEvIDSDRmuPOL110.pop_back(); vEdepSDRmuPOL110.pop_back();
			  
			mufSciDRPOL110.close();
			allvEvIDSDRmuPOL110.push_back(vEvIDSDRmuPOL110);
			allvEdepSDRmuPOL110.push_back(vEdepSDRmuPOL110);


			// BGOD1POL110
			std::ifstream mufBGOD1POL110(TString(mufiles[(k*63)+41]));
			std::vector<double> vEvIDBD1muPOL110;
			std::vector<double> vEdepBD1muPOL110;
			  
			while (!mufBGOD1POL110.eof()) {
			   double EvIDBD1POL110, EdepBD1POL110;
			   mufBGOD1POL110 >> EvIDBD1POL110 >> EdepBD1POL110;
			   vEvIDBD1muPOL110.push_back(EvIDBD1POL110);
			   vEdepBD1muPOL110.push_back(EdepBD1POL110);
			}
			vEvIDBD1muPOL110.pop_back(); vEdepBD1muPOL110.pop_back();
			vEvIDBD1muPOL110.pop_back(); vEdepBD1muPOL110.pop_back();
			  
			mufBGOD1POL110.close();
			allvEvIDBD1muPOL110.push_back(vEvIDBD1muPOL110);
			allvEdepBD1muPOL110.push_back(vEdepBD1muPOL110);



            // Polarization X1-Y0-Z1  
		    // SciD1POL101
			std::ifstream mufSciD1POL101(TString(mufiles[(k*63)+42]));
			std::vector<double> vEvIDSD1muPOL101;
			std::vector<double> vEdepSD1muPOL101;
			  
			while (!mufSciD1POL101.eof()) {
			   double EvIDSD1POL101, EdepSD1POL101;
			   mufSciD1POL101 >> EvIDSD1POL101 >> EdepSD1POL101;
			   vEvIDSD1muPOL101.push_back(EvIDSD1POL101);
			   vEdepSD1muPOL101.push_back(EdepSD1POL101);
			}
			vEvIDSD1muPOL101.pop_back(); vEdepSD1muPOL101.pop_back();
			vEvIDSD1muPOL101.pop_back(); vEdepSD1muPOL101.pop_back();
			  
			mufSciD1POL101.close();
			allvEvIDSD1muPOL101.push_back(vEvIDSD1muPOL101);
			allvEdepSD1muPOL101.push_back(vEdepSD1muPOL101);


			// SciD2POL101
			std::ifstream mufSciD2POL101(TString(mufiles[(k*63)+43]));
			std::vector<double> vEvIDSD2muPOL101;
			std::vector<double> vEdepSD2muPOL101;
			  
			while (!mufSciD2POL101.eof()) {
			   double EvIDSD2POL101, EdepSD2POL101;
			   mufSciD2POL101 >> EvIDSD2POL101 >> EdepSD2POL101;
			   vEvIDSD2muPOL101.push_back(EvIDSD2POL101);
			   vEdepSD2muPOL101.push_back(EdepSD2POL101);
			}
			vEvIDSD2muPOL101.pop_back(); vEdepSD2muPOL101.pop_back();
			vEvIDSD2muPOL101.pop_back(); vEdepSD2muPOL101.pop_back();
			  
			mufSciD2POL101.close();
			allvEvIDSD2muPOL101.push_back(vEvIDSD2muPOL101);
			allvEdepSD2muPOL101.push_back(vEdepSD2muPOL101);
			  
			  
			// SciDTPOL101
			std::ifstream mufSciDTPOL101(TString(mufiles[(k*63)+44]));
			std::vector<double> vEvIDSDTmuPOL101;
			std::vector<double> vEdepSDTmuPOL101;
			  
			while (!mufSciDTPOL101.eof()) {
			   double EvIDSDTPOL101, EdepSDTPOL101;
			   mufSciDTPOL101 >> EvIDSDTPOL101 >> EdepSDTPOL101;
			   vEvIDSDTmuPOL101.push_back(EvIDSDTPOL101);
			   vEdepSDTmuPOL101.push_back(EdepSDTPOL101);
			}
			vEvIDSDTmuPOL101.pop_back(); vEdepSDTmuPOL101.pop_back();
			vEvIDSDTmuPOL101.pop_back(); vEdepSDTmuPOL101.pop_back();
			  
			mufSciDTPOL101.close();
			allvEvIDSDTmuPOL101.push_back(vEvIDSDTmuPOL101);
			allvEdepSDTmuPOL101.push_back(vEdepSDTmuPOL101);


			// SciDBPOL101
			std::ifstream mufSciDBPOL101(TString(mufiles[(k*63)+45]));
			std::vector<double> vEvIDSDBmuPOL101;
			std::vector<double> vEdepSDBmuPOL101;
			  
			while (!mufSciDBPOL101.eof()) {
			   double EvIDSDBPOL101, EdepSDBPOL101;
			   mufSciDBPOL101 >> EvIDSDBPOL101 >> EdepSDBPOL101;
			   vEvIDSDBmuPOL101.push_back(EvIDSDBPOL101);
			   vEdepSDBmuPOL101.push_back(EdepSDBPOL101);
			}
			vEvIDSDBmuPOL101.pop_back(); vEdepSDBmuPOL101.pop_back();
			vEvIDSDBmuPOL101.pop_back(); vEdepSDBmuPOL101.pop_back();
			  
			mufSciDBPOL101.close();
			allvEvIDSDBmuPOL101.push_back(vEvIDSDBmuPOL101);
			allvEdepSDBmuPOL101.push_back(vEdepSDBmuPOL101);


			// SciDLPOL101
			std::ifstream mufSciDLPOL101(TString(mufiles[(k*63)+46]));
			std::vector<double> vEvIDSDLmuPOL101;
			std::vector<double> vEdepSDLmuPOL101;
			  
			while (!mufSciDLPOL101.eof()) {
			   double EvIDSDLPOL101, EdepSDLPOL101;
			   mufSciDLPOL101 >> EvIDSDLPOL101 >> EdepSDLPOL101;
			   vEvIDSDLmuPOL101.push_back(EvIDSDLPOL101);
			   vEdepSDLmuPOL101.push_back(EdepSDLPOL101);
			}
			vEvIDSDLmuPOL101.pop_back(); vEdepSDLmuPOL101.pop_back();
			vEvIDSDLmuPOL101.pop_back(); vEdepSDLmuPOL101.pop_back();
			  
			mufSciDLPOL101.close();
			allvEvIDSDLmuPOL101.push_back(vEvIDSDLmuPOL101);
			allvEdepSDLmuPOL101.push_back(vEdepSDLmuPOL101);


			// SciDRPOL101
			std::ifstream mufSciDRPOL101(TString(mufiles[(k*63)+47]));
			std::vector<double> vEvIDSDRmuPOL101;
			std::vector<double> vEdepSDRmuPOL101;
			  
			while (!mufSciDRPOL101.eof()) {
			   double EvIDSDRPOL101, EdepSDRPOL101;
			   mufSciDRPOL101 >> EvIDSDRPOL101 >> EdepSDRPOL101;
			   vEvIDSDRmuPOL101.push_back(EvIDSDRPOL101);
			   vEdepSDRmuPOL101.push_back(EdepSDRPOL101);
			}
			vEvIDSDRmuPOL101.pop_back(); vEdepSDRmuPOL101.pop_back();
			vEvIDSDRmuPOL101.pop_back(); vEdepSDRmuPOL101.pop_back();
			  
			mufSciDRPOL101.close();
			allvEvIDSDRmuPOL101.push_back(vEvIDSDRmuPOL101);
			allvEdepSDRmuPOL101.push_back(vEdepSDRmuPOL101);


			// BGOD1POL101
			std::ifstream mufBGOD1POL101(TString(mufiles[(k*63)+48]));
			std::vector<double> vEvIDBD1muPOL101;
			std::vector<double> vEdepBD1muPOL101;
			  
			while (!mufBGOD1POL101.eof()) {
			   double EvIDBD1POL101, EdepBD1POL101;
			   mufBGOD1POL101 >> EvIDBD1POL101 >> EdepBD1POL101;
			   vEvIDBD1muPOL101.push_back(EvIDBD1POL101);
			   vEdepBD1muPOL101.push_back(EdepBD1POL101);
			}
			vEvIDBD1muPOL101.pop_back(); vEdepBD1muPOL101.pop_back();
			vEvIDBD1muPOL101.pop_back(); vEdepBD1muPOL101.pop_back();
			  
			mufBGOD1POL101.close();
			allvEvIDBD1muPOL101.push_back(vEvIDBD1muPOL101);
			allvEdepBD1muPOL101.push_back(vEdepBD1muPOL101);



            // Polarization X0-Y1-Z1  
		    // SciD1POL001
			std::ifstream mufSciD1POL011(TString(mufiles[(k*63)+49]));
			std::vector<double> vEvIDSD1muPOL011;
			std::vector<double> vEdepSD1muPOL011;
			  
			while (!mufSciD1POL011.eof()) {
			   double EvIDSD1POL011, EdepSD1POL011;
			   mufSciD1POL011 >> EvIDSD1POL011 >> EdepSD1POL011;
			   vEvIDSD1muPOL011.push_back(EvIDSD1POL011);
			   vEdepSD1muPOL011.push_back(EdepSD1POL011);
			}
			vEvIDSD1muPOL011.pop_back(); vEdepSD1muPOL011.pop_back();
			vEvIDSD1muPOL011.pop_back(); vEdepSD1muPOL011.pop_back();
			  
			mufSciD1POL011.close();
			allvEvIDSD1muPOL011.push_back(vEvIDSD1muPOL011);
			allvEdepSD1muPOL011.push_back(vEdepSD1muPOL011);


			// SciD2POL011
			std::ifstream mufSciD2POL011(TString(mufiles[(k*63)+50]));
			std::vector<double> vEvIDSD2muPOL011;
			std::vector<double> vEdepSD2muPOL011;
			  
			while (!mufSciD2POL011.eof()) {
			   double EvIDSD2POL011, EdepSD2POL011;
			   mufSciD2POL011 >> EvIDSD2POL011 >> EdepSD2POL011;
			   vEvIDSD2muPOL011.push_back(EvIDSD2POL011);
			   vEdepSD2muPOL011.push_back(EdepSD2POL011);
			}
			vEvIDSD2muPOL011.pop_back(); vEdepSD2muPOL011.pop_back();
			vEvIDSD2muPOL011.pop_back(); vEdepSD2muPOL011.pop_back();
			  
			mufSciD2POL011.close();
			allvEvIDSD2muPOL011.push_back(vEvIDSD2muPOL011);
			allvEdepSD2muPOL011.push_back(vEdepSD2muPOL011);
			  
			  
			// SciDTPOL011
			std::ifstream mufSciDTPOL011(TString(mufiles[(k*63)+51]));
			std::vector<double> vEvIDSDTmuPOL011;
			std::vector<double> vEdepSDTmuPOL011;
			  
			while (!mufSciDTPOL011.eof()) {
			   double EvIDSDTPOL011, EdepSDTPOL011;
			   mufSciDTPOL011 >> EvIDSDTPOL011 >> EdepSDTPOL011;
			   vEvIDSDTmuPOL011.push_back(EvIDSDTPOL011);
			   vEdepSDTmuPOL011.push_back(EdepSDTPOL011);
			}
			vEvIDSDTmuPOL011.pop_back(); vEdepSDTmuPOL011.pop_back();
			vEvIDSDTmuPOL011.pop_back(); vEdepSDTmuPOL011.pop_back();
			  
			mufSciDTPOL011.close();
			allvEvIDSDTmuPOL011.push_back(vEvIDSDTmuPOL011);
			allvEdepSDTmuPOL011.push_back(vEdepSDTmuPOL011);


			// SciDBPOL011
			std::ifstream mufSciDBPOL011(TString(mufiles[(k*63)+52]));
			std::vector<double> vEvIDSDBmuPOL011;
			std::vector<double> vEdepSDBmuPOL011;
			  
			while (!mufSciDBPOL011.eof()) {
			   double EvIDSDBPOL011, EdepSDBPOL011;
			   mufSciDBPOL011 >> EvIDSDBPOL011 >> EdepSDBPOL011;
			   vEvIDSDBmuPOL011.push_back(EvIDSDBPOL011);
			   vEdepSDBmuPOL011.push_back(EdepSDBPOL011);
			}
			vEvIDSDBmuPOL011.pop_back(); vEdepSDBmuPOL011.pop_back();
			vEvIDSDBmuPOL011.pop_back(); vEdepSDBmuPOL011.pop_back();
			  
			mufSciDBPOL011.close();
			allvEvIDSDBmuPOL011.push_back(vEvIDSDBmuPOL011);
			allvEdepSDBmuPOL011.push_back(vEdepSDBmuPOL011);


			// SciDLPOL011
			std::ifstream mufSciDLPOL011(TString(mufiles[(k*63)+53]));
			std::vector<double> vEvIDSDLmuPOL011;
			std::vector<double> vEdepSDLmuPOL011;
			  
			while (!mufSciDLPOL011.eof()) {
			   double EvIDSDLPOL011, EdepSDLPOL011;
			   mufSciDLPOL011 >> EvIDSDLPOL011 >> EdepSDLPOL011;
			   vEvIDSDLmuPOL011.push_back(EvIDSDLPOL011);
			   vEdepSDLmuPOL011.push_back(EdepSDLPOL011);
			}
			vEvIDSDLmuPOL011.pop_back(); vEdepSDLmuPOL011.pop_back();
			vEvIDSDLmuPOL011.pop_back(); vEdepSDLmuPOL011.pop_back();
			  
			mufSciDLPOL011.close();
			allvEvIDSDLmuPOL011.push_back(vEvIDSDLmuPOL011);
			allvEdepSDLmuPOL011.push_back(vEdepSDLmuPOL011);


			// SciDRPOL011
			std::ifstream mufSciDRPOL011(TString(mufiles[(k*63)+54]));
			std::vector<double> vEvIDSDRmuPOL011;
			std::vector<double> vEdepSDRmuPOL011;
			  
			while (!mufSciDRPOL011.eof()) {
			   double EvIDSDRPOL011, EdepSDRPOL011;
			   mufSciDRPOL011 >> EvIDSDRPOL011 >> EdepSDRPOL011;
			   vEvIDSDRmuPOL011.push_back(EvIDSDRPOL011);
			   vEdepSDRmuPOL011.push_back(EdepSDRPOL011);
			}
			vEvIDSDRmuPOL011.pop_back(); vEdepSDRmuPOL011.pop_back();
			vEvIDSDRmuPOL011.pop_back(); vEdepSDRmuPOL011.pop_back();
			  
			mufSciDRPOL011.close();
			allvEvIDSDRmuPOL011.push_back(vEvIDSDRmuPOL011);
			allvEdepSDRmuPOL011.push_back(vEdepSDRmuPOL011);


			// BGOD1POL011
			std::ifstream mufBGOD1POL011(TString(mufiles[(k*63)+55]));
			std::vector<double> vEvIDBD1muPOL011;
			std::vector<double> vEdepBD1muPOL011;
			  
			while (!mufBGOD1POL011.eof()) {
			   double EvIDBD1POL011, EdepBD1POL011;
			   mufBGOD1POL011 >> EvIDBD1POL011 >> EdepBD1POL011;
			   vEvIDBD1muPOL011.push_back(EvIDBD1POL011);
			   vEdepBD1muPOL011.push_back(EdepBD1POL011);
			}
			vEvIDBD1muPOL011.pop_back(); vEdepBD1muPOL011.pop_back();
			vEvIDBD1muPOL011.pop_back(); vEdepBD1muPOL011.pop_back();
			  
			mufBGOD1POL011.close();
			allvEvIDBD1muPOL011.push_back(vEvIDBD1muPOL011);
			allvEdepBD1muPOL011.push_back(vEdepBD1muPOL011);



            // Polarization X1-Y1-Z1  
		    // SciD1POL111
			std::ifstream mufSciD1POL111(TString(mufiles[(k*63)+56]));
			std::vector<double> vEvIDSD1muPOL111;
			std::vector<double> vEdepSD1muPOL111;
			  
			while (!mufSciD1POL111.eof()) {
			   double EvIDSD1POL111, EdepSD1POL111;
			   mufSciD1POL111 >> EvIDSD1POL111 >> EdepSD1POL111;
			   vEvIDSD1muPOL111.push_back(EvIDSD1POL111);
			   vEdepSD1muPOL111.push_back(EdepSD1POL111);
			}
			vEvIDSD1muPOL111.pop_back(); vEdepSD1muPOL111.pop_back();
			vEvIDSD1muPOL111.pop_back(); vEdepSD1muPOL111.pop_back();
			  
			mufSciD1POL111.close();
			allvEvIDSD1muPOL111.push_back(vEvIDSD1muPOL111);
			allvEdepSD1muPOL111.push_back(vEdepSD1muPOL111);


			// SciD2POL111
			std::ifstream mufSciD2POL111(TString(mufiles[(k*63)+57]));
			std::vector<double> vEvIDSD2muPOL111;
			std::vector<double> vEdepSD2muPOL111;
			  
			while (!mufSciD2POL111.eof()) {
			   double EvIDSD2POL111, EdepSD2POL111;
			   mufSciD2POL111 >> EvIDSD2POL111 >> EdepSD2POL111;
			   vEvIDSD2muPOL111.push_back(EvIDSD2POL111);
			   vEdepSD2muPOL111.push_back(EdepSD2POL111);
			}
			vEvIDSD2muPOL111.pop_back(); vEdepSD2muPOL111.pop_back();
			vEvIDSD2muPOL111.pop_back(); vEdepSD2muPOL111.pop_back();
			  
			mufSciD2POL111.close();
			allvEvIDSD2muPOL111.push_back(vEvIDSD2muPOL111);
			allvEdepSD2muPOL111.push_back(vEdepSD2muPOL111);
			  
			  
			// SciDTPOL111
			std::ifstream mufSciDTPOL111(TString(mufiles[(k*63)+58]));
			std::vector<double> vEvIDSDTmuPOL111;
			std::vector<double> vEdepSDTmuPOL111;
			  
			while (!mufSciDTPOL111.eof()) {
			   double EvIDSDTPOL111, EdepSDTPOL111;
			   mufSciDTPOL111 >> EvIDSDTPOL111 >> EdepSDTPOL111;
			   vEvIDSDTmuPOL111.push_back(EvIDSDTPOL111);
			   vEdepSDTmuPOL111.push_back(EdepSDTPOL111);
			}
			vEvIDSDTmuPOL111.pop_back(); vEdepSDTmuPOL111.pop_back();
			vEvIDSDTmuPOL111.pop_back(); vEdepSDTmuPOL111.pop_back();
			  
			mufSciDTPOL111.close();
			allvEvIDSDTmuPOL111.push_back(vEvIDSDTmuPOL111);
			allvEdepSDTmuPOL111.push_back(vEdepSDTmuPOL111);


			// SciDBPOL111
			std::ifstream mufSciDBPOL111(TString(mufiles[(k*63)+59]));
			std::vector<double> vEvIDSDBmuPOL111;
			std::vector<double> vEdepSDBmuPOL111;
			  
			while (!mufSciDBPOL111.eof()) {
			   double EvIDSDBPOL111, EdepSDBPOL111;
			   mufSciDBPOL111 >> EvIDSDBPOL111 >> EdepSDBPOL111;
			   vEvIDSDBmuPOL111.push_back(EvIDSDBPOL111);
			   vEdepSDBmuPOL111.push_back(EdepSDBPOL111);
			}
			vEvIDSDBmuPOL111.pop_back(); vEdepSDBmuPOL111.pop_back();
			vEvIDSDBmuPOL111.pop_back(); vEdepSDBmuPOL111.pop_back();
			  
			mufSciDBPOL111.close();
			allvEvIDSDBmuPOL111.push_back(vEvIDSDBmuPOL111);
			allvEdepSDBmuPOL111.push_back(vEdepSDBmuPOL111);


			// SciDLPOL111
			std::ifstream mufSciDLPOL111(TString(mufiles[(k*63)+60]));
			std::vector<double> vEvIDSDLmuPOL111;
			std::vector<double> vEdepSDLmuPOL111;
			  
			while (!mufSciDLPOL111.eof()) {
			   double EvIDSDLPOL111, EdepSDLPOL111;
			   mufSciDLPOL111 >> EvIDSDLPOL111 >> EdepSDLPOL111;
			   vEvIDSDLmuPOL111.push_back(EvIDSDLPOL111);
			   vEdepSDLmuPOL111.push_back(EdepSDLPOL111);
			}
			vEvIDSDLmuPOL111.pop_back(); vEdepSDLmuPOL111.pop_back();
			vEvIDSDLmuPOL111.pop_back(); vEdepSDLmuPOL111.pop_back();
			  
			mufSciDLPOL111.close();
			allvEvIDSDLmuPOL111.push_back(vEvIDSDLmuPOL111);
			allvEdepSDLmuPOL111.push_back(vEdepSDLmuPOL111);


			// SciDRPOL111
			std::ifstream mufSciDRPOL111(TString(mufiles[(k*63)+61]));
			std::vector<double> vEvIDSDRmuPOL111;
			std::vector<double> vEdepSDRmuPOL111;
			  
			while (!mufSciDRPOL111.eof()) {
			   double EvIDSDRPOL111, EdepSDRPOL111;
			   mufSciDRPOL111 >> EvIDSDRPOL111 >> EdepSDRPOL111;
			   vEvIDSDRmuPOL111.push_back(EvIDSDRPOL111);
			   vEdepSDRmuPOL111.push_back(EdepSDRPOL111);
			}
			vEvIDSDRmuPOL111.pop_back(); vEdepSDRmuPOL111.pop_back();
			vEvIDSDRmuPOL111.pop_back(); vEdepSDRmuPOL111.pop_back();
			  
			mufSciDRPOL111.close();
			allvEvIDSDRmuPOL111.push_back(vEvIDSDRmuPOL111);
			allvEdepSDRmuPOL111.push_back(vEdepSDRmuPOL111);


			// BGOD1POL111
			std::ifstream mufBGOD1POL111(TString(mufiles[(k*63)+62]));
			std::vector<double> vEvIDBD1muPOL111;
			std::vector<double> vEdepBD1muPOL111;
			  
			while (!mufBGOD1POL111.eof()) {
			   double EvIDBD1POL111, EdepBD1POL111;
			   mufBGOD1POL111 >> EvIDBD1POL111 >> EdepBD1POL111;
			   vEvIDBD1muPOL111.push_back(EvIDBD1POL111);
			   vEdepBD1muPOL111.push_back(EdepBD1POL111);
			}
			vEvIDBD1muPOL111.pop_back(); vEdepBD1muPOL111.pop_back();
			vEvIDBD1muPOL111.pop_back(); vEdepBD1muPOL111.pop_back();
			  
			mufBGOD1POL111.close();
			allvEvIDBD1muPOL111.push_back(vEvIDBD1muPOL111);
			allvEdepBD1muPOL111.push_back(vEdepBD1muPOL111);


		 }
			  

			
		 //-------------------------------------------------------------------
		 //                     Bin-by-bin analysis
		 //                          Mu-decay
		 //-------------------------------------------------------------------     

			
		 // Mu-decay	  
		 for (int i=0; i<allvEvIDBD1muPOL000.size(); i++) {

			std::cout << std::endl;
			std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
			std::cout << "\033[1;31m-------------------- Analysis Loop  " << i+1 << " --------------------\033[0m" << std::endl;
			std::cout << "\033[1;31m----------------------- Mu-decay -------------------------\033[0m" << std::endl;
			std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


            for (int m=0; m<nsamps; m++) {

			   Ethr = Ethrmu[m];

			   //--------------------------------------------------
			   // Normalisation 2 [absolute] :: POL X0-Y0-Z0
			   //-------------------------------------------------- 
			   eXrayPOL000noST = 0; eelecPOL000noST = 0;
			  
			   for (int a=0; a<allvEvIDBD1muPOL000noST[0].size(); a++) {

			      if ((allvEdepSD1muPOL000noST[i][a] < Ethr1) && (allvEdepSD2muPOL000noST[i][a] < Ethr1)) {
				     if ((allvEdepBD1muPOL000noST[i][a] > Ethr) && (allvEdepBD1muPOL000noST[i][a] < Ethr22)) {
					    if ((allvEdepSDTmuPOL000noST[i][a] < Ethr3) || (allvEdepSDTmuPOL000noST[i][a] < Ethr3) || (allvEdepSDLmuPOL000noST[i][a] < Ethr3) || (allvEdepSDRmuPOL000noST[i][a] < Ethr3)) {
						   eXrayPOL000noST += 1;
						} else { eelecPOL000noST += 1; }
					 } else { eelecPOL000noST += 1; }
				  } else { eelecPOL000noST += 1; }
			   }
				 
			   PeXvectorPOL000noST[i][m] = eXrayPOL000noST/(double)(countereeN2);
			   PeevectorPOL000noST[i][m] = eelecPOL000noST/(double)(countereeN2); 


			   //--------------------------------------------------
			   // Normalisation 2 [absolute] :: POL X0-Y0-Z0
			   //-------------------------------------------------- 
			   eXrayPOL000 = 0; eelecPOL000 = 0;
			  
			   for (int a=0; a<allvEvIDBD1muPOL000[0].size(); a++) {

			      if ((allvEdepSD1muPOL000[i][a] < Ethr1) && (allvEdepSD2muPOL000[i][a] < Ethr1)) {
				     if ((allvEdepBD1muPOL000[i][a] > Ethr) && (allvEdepBD1muPOL000[i][a] < Ethr22)) {
					    if ((allvEdepSDTmuPOL000[i][a] < Ethr3) || (allvEdepSDTmuPOL000[i][a] < Ethr3) || (allvEdepSDLmuPOL000[i][a] < Ethr3) || (allvEdepSDRmuPOL000[i][a] < Ethr3)) {
						   eXrayPOL000 += 1;
						} else { eelecPOL000 += 1; }
					 } else { eelecPOL000 += 1; }
				  } else { eelecPOL000 += 1; }
			   }
				 
			   PeXvectorPOL000[i][m] = eXrayPOL000/(double)(countereeN2);
			   PeevectorPOL000[i][m] = eelecPOL000/(double)(countereeN2); 
							   	
			  
			   //--------------------------------------------------
			   // Normalisation 2 [absolute] :: POL X0-Y0-Z1
			   //-------------------------------------------------- 
			   eXrayPOL001 = 0; eelecPOL001 = 0;
			  
			   for (int a=0; a<allvEvIDBD1muPOL001[0].size(); a++) {

			      if ((allvEdepSD1muPOL001[i][a] < Ethr1) && (allvEdepSD2muPOL001[i][a] < Ethr1)) {
				     if ((allvEdepBD1muPOL001[i][a] > Ethr) && (allvEdepBD1muPOL001[i][a] < Ethr22)) {
					    if ((allvEdepSDTmuPOL001[i][a] < Ethr3) || (allvEdepSDTmuPOL001[i][a] < Ethr3) || (allvEdepSDLmuPOL001[i][a] < Ethr3) || (allvEdepSDRmuPOL001[i][a] < Ethr3)) {
						   eXrayPOL001 += 1;
						} else { eelecPOL001 += 1; }
					 } else { eelecPOL001 += 1; }
				  } else { eelecPOL001 += 1; }
			   }
				 
			   PeXvectorPOL001[i][m] = eXrayPOL001/(double)(countereeN2);
			   PeevectorPOL001[i][m] = eelecPOL001/(double)(countereeN2); 


			   //--------------------------------------------------
			   // Normalisation 2 [absolute] :: POL X0-Y1-Z0
			   //-------------------------------------------------- 
			   eXrayPOL010 = 0; eelecPOL010 = 0;
			  
			   for (int a=0; a<allvEvIDBD1muPOL010[0].size(); a++) {

			      if ((allvEdepSD1muPOL010[i][a] < Ethr1) && (allvEdepSD2muPOL010[i][a] < Ethr1)) {
				     if ((allvEdepBD1muPOL010[i][a] > Ethr) && (allvEdepBD1muPOL010[i][a] < Ethr22)) {
					    if ((allvEdepSDTmuPOL010[i][a] < Ethr3) || (allvEdepSDTmuPOL010[i][a] < Ethr3) || (allvEdepSDLmuPOL010[i][a] < Ethr3) || (allvEdepSDRmuPOL010[i][a] < Ethr3)) {
						   eXrayPOL010 += 1;
						} else { eelecPOL010 += 1; }
					 } else { eelecPOL010 += 1; }
				  } else { eelecPOL010 += 1; }
			   }
				 
			   PeXvectorPOL010[i][m] = eXrayPOL010/(double)(countereeN2);
			   PeevectorPOL010[i][m] = eelecPOL010/(double)(countereeN2); 


			   //--------------------------------------------------
			   // Normalisation 2 [absolute] :: POL X1-Y0-Z0
			   //-------------------------------------------------- 
			   eXrayPOL100 = 0; eelecPOL100 = 0;
			  
			   for (int a=0; a<allvEvIDBD1muPOL100[0].size(); a++) {

			      if ((allvEdepSD1muPOL100[i][a] < Ethr1) && (allvEdepSD2muPOL100[i][a] < Ethr1)) {
				     if ((allvEdepBD1muPOL100[i][a] > Ethr) && (allvEdepBD1muPOL100[i][a] < Ethr22)) {
					    if ((allvEdepSDTmuPOL100[i][a] < Ethr3) || (allvEdepSDTmuPOL100[i][a] < Ethr3) || (allvEdepSDLmuPOL100[i][a] < Ethr3) || (allvEdepSDRmuPOL100[i][a] < Ethr3)) {
						   eXrayPOL100 += 1;
						} else { eelecPOL100 += 1; }
					 } else { eelecPOL100 += 1; }
				  } else { eelecPOL100 += 1; }
			   }
				 
			   PeXvectorPOL100[i][m] = eXrayPOL100/(double)(countereeN2);
			   PeevectorPOL100[i][m] = eelecPOL100/(double)(countereeN2); 


			   //--------------------------------------------------
			   // Normalisation 2 [absolute] :: POL X1-Y1-Z0
			   //-------------------------------------------------- 
			   eXrayPOL110 = 0; eelecPOL110 = 0;
			  
			   for (int a=0; a<allvEvIDBD1muPOL110[0].size(); a++) {

			      if ((allvEdepSD1muPOL110[i][a] < Ethr1) && (allvEdepSD2muPOL110[i][a] < Ethr1)) {
				     if ((allvEdepBD1muPOL110[i][a] > Ethr) && (allvEdepBD1muPOL110[i][a] < Ethr22)) {
					    if ((allvEdepSDTmuPOL110[i][a] < Ethr3) || (allvEdepSDTmuPOL110[i][a] < Ethr3) || (allvEdepSDLmuPOL110[i][a] < Ethr3) || (allvEdepSDRmuPOL110[i][a] < Ethr3)) {
						   eXrayPOL110 += 1;
						} else { eelecPOL110 += 1; }
					 } else { eelecPOL110 += 1; }
				  } else { eelecPOL110 += 1; }
			   }
				 
			   PeXvectorPOL110[i][m] = eXrayPOL110/(double)(countereeN2);
			   PeevectorPOL110[i][m] = eelecPOL110/(double)(countereeN2); 


			   //--------------------------------------------------
			   // Normalisation 2 [absolute] :: POL X1-Y0-Z1
			   //-------------------------------------------------- 
			   eXrayPOL101 = 0; eelecPOL101 = 0;
			  
			   for (int a=0; a<allvEvIDBD1muPOL101[0].size(); a++) {

			      if ((allvEdepSD1muPOL101[i][a] < Ethr1) && (allvEdepSD2muPOL101[i][a] < Ethr1)) {
				     if ((allvEdepBD1muPOL101[i][a] > Ethr) && (allvEdepBD1muPOL101[i][a] < Ethr22)) {
					    if ((allvEdepSDTmuPOL101[i][a] < Ethr3) || (allvEdepSDTmuPOL101[i][a] < Ethr3) || (allvEdepSDLmuPOL101[i][a] < Ethr3) || (allvEdepSDRmuPOL101[i][a] < Ethr3)) {
						   eXrayPOL101 += 1;
						} else { eelecPOL101 += 1; }
					 } else { eelecPOL101 += 1; }
				  } else { eelecPOL101 += 1; }
			   }
				 
			   PeXvectorPOL101[i][m] = eXrayPOL101/(double)(countereeN2);
			   PeevectorPOL101[i][m] = eelecPOL101/(double)(countereeN2); 


			   //--------------------------------------------------
			   // Normalisation 2 [absolute] :: POL X0-Y1-Z1
			   //-------------------------------------------------- 
			   eXrayPOL011 = 0; eelecPOL011 = 0;
			  
			   for (int a=0; a<allvEvIDBD1muPOL011[0].size(); a++) {

			      if ((allvEdepSD1muPOL011[i][a] < Ethr1) && (allvEdepSD2muPOL011[i][a] < Ethr1)) {
				     if ((allvEdepBD1muPOL011[i][a] > Ethr) && (allvEdepBD1muPOL011[i][a] < Ethr22)) {
					    if ((allvEdepSDTmuPOL011[i][a] < Ethr3) || (allvEdepSDTmuPOL011[i][a] < Ethr3) || (allvEdepSDLmuPOL011[i][a] < Ethr3) || (allvEdepSDRmuPOL011[i][a] < Ethr3)) {
						   eXrayPOL011 += 1;
						} else { eelecPOL011 += 1; }
					 } else { eelecPOL011 += 1; }
				  } else { eelecPOL011 += 1; }
			   }
				 
			   PeXvectorPOL011[i][m] = eXrayPOL011/(double)(countereeN2);
			   PeevectorPOL011[i][m] = eelecPOL011/(double)(countereeN2); 


			   //--------------------------------------------------
			   // Normalisation 2 [absolute] :: POL X1-Y1-Z1
			   //-------------------------------------------------- 
			   eXrayPOL111 = 0; eelecPOL111 = 0;
			  
			   for (int a=0; a<allvEvIDBD1muPOL111[0].size(); a++) {

			      if ((allvEdepSD1muPOL111[i][a] < Ethr1) && (allvEdepSD2muPOL111[i][a] < Ethr1)) {
				     if ((allvEdepBD1muPOL111[i][a] > Ethr) && (allvEdepBD1muPOL111[i][a] < Ethr22)) {
					    if ((allvEdepSDTmuPOL111[i][a] < Ethr3) || (allvEdepSDTmuPOL111[i][a] < Ethr3) || (allvEdepSDLmuPOL111[i][a] < Ethr3) || (allvEdepSDRmuPOL111[i][a] < Ethr3)) {
						   eXrayPOL111 += 1;
						} else { eelecPOL111 += 1; }
					 } else { eelecPOL111 += 1; }
				  } else { eelecPOL111 += 1; }
			   }
				 
			   PeXvectorPOL111[i][m] = eXrayPOL111/(double)(countereeN2);
			   PeevectorPOL111[i][m] = eelecPOL111/(double)(countereeN2); 

			  
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
		 float PeXarrPOL000noST[nsamps] = {};
		 float PeearrPOL000noST[nsamps] = {};
		 float PeXarrPOL000[nsamps] = {}; // Mu-decay
		 float PeearrPOL000[nsamps] = {};
         float PeXarrPOL001[nsamps] = {};
         float PeearrPOL001[nsamps] = {};
         float PeXarrPOL010[nsamps] = {};
         float PeearrPOL010[nsamps] = {};
         float PeXarrPOL100[nsamps] = {};
         float PeearrPOL100[nsamps] = {};
         float PeXarrPOL110[nsamps] = {};
         float PeearrPOL110[nsamps] = {};
         float PeXarrPOL101[nsamps] = {};
         float PeearrPOL101[nsamps] = {};
         float PeXarrPOL011[nsamps] = {};
         float PeearrPOL011[nsamps] = {};
         float PeXarrPOL111[nsamps] = {};
         float PeearrPOL111[nsamps] = {};
         float PeXarrN2c1[nsamps] = {};
		 	   
		 for (int i=0; i<nsamps; i++) {
			// Normalisation 2 [absolute]
			PeXarrPOL000noST[i] = PeXvectorPOL000noST[0][i];
			PeearrPOL000noST[i] = PeevectorPOL000noST[0][i];
			PeXarrPOL000[i] = PeXvectorPOL000[0][i];
			PeearrPOL000[i] = PeevectorPOL000[0][i];
			PeXarrPOL001[i] = PeXvectorPOL001[0][i];
			PeearrPOL001[i] = PeevectorPOL001[0][i];
			PeXarrPOL010[i] = PeXvectorPOL010[0][i];
			PeearrPOL010[i] = PeevectorPOL010[0][i];
			PeXarrPOL100[i] = PeXvectorPOL100[0][i];
			PeearrPOL100[i] = PeevectorPOL100[0][i];
			PeXarrPOL110[i] = PeXvectorPOL110[0][i];
			PeearrPOL110[i] = PeevectorPOL110[0][i];
			PeXarrPOL101[i] = PeXvectorPOL101[0][i];
			PeearrPOL101[i] = PeevectorPOL101[0][i];
			PeXarrPOL011[i] = PeXvectorPOL011[0][i];
			PeearrPOL011[i] = PeevectorPOL011[0][i];
			PeXarrPOL111[i] = PeXvectorPOL111[0][i];
			PeearrPOL111[i] = PeevectorPOL111[0][i];
		 }	   

		   		   
		 TCanvas *c = new TCanvas("c","E_{THR}",800,600);
		 //c->Divide(3,3);
		 //c->cd(1);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPeXPOL000noST = new TGraph(nsamps,Ethrmu,PeXarrPOL000noST);
		 grPeXPOL000noST->SetTitle("#mu-decay polarisations: X{0,1}-Y{0,1}-Z{0,1} :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]");
         grPeXPOL000noST->GetXaxis()->SetTitle("E_{THR} [MeV]");
         grPeXPOL000noST->GetXaxis()->SetRangeUser(0,2.05);
         //grPeXPOL000noST->GetYaxis()->SetRangeUser(1e-4,1.1);
         grPeXPOL000noST->GetYaxis()->SetMoreLogLabels(1);
		 grPeXPOL000noST->GetYaxis()->SetTitle("P_{e->X}(E_{THR})");
		 grPeXPOL000noST->GetYaxis()->SetTitleOffset(1.8);
		 //grPeXPOL000noST->SetMarkerColor(kMagenta+2);
		 //grPeXPOL000noST->SetMarkerStyle(31);
		 grPeXPOL000noST->SetLineColor(kMagenta+2);
		 grPeXPOL000noST->SetLineWidth(3);
		 grPeXPOL000noST->Draw("ALP");
		 TGraph *grPeXPOL000 = new TGraph(nsamps,Ethrmu,PeXarrPOL000);
		 grPeXPOL000->SetLineColor(kRed);
		 grPeXPOL000->SetLineWidth(3);
		 grPeXPOL000->Draw("LP");
		 TGraph *grPeXPOL001 = new TGraph(nsamps,Ethrmu,PeXarrPOL001); 
		 grPeXPOL001->SetLineColor(kBlack);
		 grPeXPOL001->SetLineWidth(3);
		 grPeXPOL001->Draw("LP");
		 TGraph *grPeXPOL010 = new TGraph(nsamps,Ethrmu,PeXarrPOL010);
		 grPeXPOL010->SetLineColor(kGreen-2);
		 grPeXPOL010->SetLineWidth(3);
		 grPeXPOL010->Draw("LP");
		 TGraph *grPeXPOL100 = new TGraph(nsamps,Ethrmu,PeXarrPOL100);
		 grPeXPOL100->SetLineColor(kViolet+1);
		 grPeXPOL100->SetLineWidth(3);
		 grPeXPOL100->Draw("LP");
		 TGraph *grPeXPOL110 = new TGraph(nsamps,Ethrmu,PeXarrPOL110);
		 grPeXPOL110->SetLineColor(kOrange+1);
		 grPeXPOL110->SetLineWidth(3);
		 grPeXPOL110->Draw("LP");
		 TGraph *grPeXPOL101 = new TGraph(nsamps,Ethrmu,PeXarrPOL101);
		 grPeXPOL101->SetLineColor(kRed-9);
		 grPeXPOL101->SetLineWidth(3);
		 grPeXPOL101->Draw("LP");
		 TGraph *grPeXPOL011 = new TGraph(nsamps,Ethrmu,PeXarrPOL011);
		 grPeXPOL011->SetLineColor(kBlue-3);
		 grPeXPOL011->SetLineWidth(3);
		 grPeXPOL011->Draw("LP");
		 TGraph *grPeXPOL111 = new TGraph(nsamps,Ethrmu,PeXarrPOL111);
		 grPeXPOL111->SetLineColor(kCyan+1);
		 grPeXPOL111->SetLineWidth(3);
		 grPeXPOL111->Draw("LP");
		 legPeXPOL = new TLegend(0.2,-0.005,0.6,0.08);
		 legPeXPOL->SetNColumns(2);
		 legPeXPOL->AddEntry(grPeXPOL000noST,"POL X0-Y0-Z0 [no SpinTracking]","lp");
		 legPeXPOL->AddEntry(grPeXPOL000,"POL X0-Y0-Z0","lp");
		 legPeXPOL->AddEntry(grPeXPOL001,"POL X0-Y0-Z1","lp");
		 legPeXPOL->AddEntry(grPeXPOL010,"POL X0-Y1-Z0","lp");
		 legPeXPOL->AddEntry(grPeXPOL100,"POL X1-Y0-Z0","lp");
		 legPeXPOL->AddEntry(grPeXPOL110,"POL X1-Y1-Z0","lp");
		 legPeXPOL->AddEntry(grPeXPOL101,"POL X1-Y0-Z1","lp");
		 legPeXPOL->AddEntry(grPeXPOL011,"POL X0-Y1-Z1","lp");
		 legPeXPOL->AddEntry(grPeXPOL111,"POL X1-Y1-Z1","lp");
		 legPeXPOL->Draw();
		 
		 c->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shift_polarisations_MULTIplicities_eff.pdf");
		 c->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shift_polarisations_MULTIplicities_eff.png");
		 c->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shift_polarisations_MULTIplicities_eff.C");
		  
		 
		 
		 TCanvas *d = new TCanvas("d","E_{THR}",800,600);
		 d->Divide(3,3);
		 d->cd(1);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPeXPOL000noST2 = new TGraph(nsamps,Ethrmu,PeXarrPOL000noST);
		 grPeXPOL000noST2->SetTitle("#mu-decay polarisations: X0-Y0-Z0 :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]");
         grPeXPOL000noST2->GetXaxis()->SetTitle("E_{THR} [MeV]");
         grPeXPOL000noST2->GetXaxis()->SetRangeUser(0,2.05);
         //grPeXPOL000noST2->GetYaxis()->SetRangeUser(1e-4,1.1);
         grPeXPOL000noST2->GetYaxis()->SetMoreLogLabels(1);
		 grPeXPOL000noST2->GetYaxis()->SetTitle("P_{e->X}(E_{THR})");
		 grPeXPOL000noST2->GetYaxis()->SetTitleOffset(1.8);
		 //grPeXPOL000noST2->SetMarkerColor(kMagenta+2);
		 //grPeXPOL000noST2->SetMarkerStyle(31);
		 grPeXPOL000noST2->SetLineColor(kMagenta+2);
		 grPeXPOL000noST2->SetLineWidth(3);
		 grPeXPOL000noST2->Draw("ALP");
		 TGraph *grPeXPOL0002 = new TGraph(nsamps,Ethrmu,PeXarrPOL000);
		 grPeXPOL0002->SetLineColor(kRed);
		 grPeXPOL0002->SetLineWidth(3);
		 grPeXPOL0002->Draw("LP");
		 legPeXPOL000 = new TLegend(0.2,-0.005,0.6,0.08);
		 legPeXPOL000->AddEntry(grPeXPOL0002,"POL X0-Y0-Z0","lp");
		 legPeXPOL000->AddEntry(grPeXPOL000noST2,"POL X0-Y0-Z0 [no SpinTracking","lp");
		 legPeXPOL000->Draw();

		 d->cd(2);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPeXPOL000noST2 = new TGraph(nsamps,Ethrmu,PeXarrPOL000noST);
		 grPeXPOL000noST2->SetTitle("#mu-decay polarisations: X0-Y0-Z1 :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]");
         grPeXPOL000noST2->GetXaxis()->SetTitle("E_{THR} [MeV]");
         grPeXPOL000noST2->GetXaxis()->SetRangeUser(0,2.05);
         //grPeXPOL000noST2->GetYaxis()->SetRangeUser(1e-4,1.1);
         grPeXPOL000noST2->GetYaxis()->SetMoreLogLabels(1);
		 grPeXPOL000noST2->GetYaxis()->SetTitle("P_{e->X}(E_{THR})");
		 grPeXPOL000noST2->GetYaxis()->SetTitleOffset(1.8);
		 //grPeXPOL000noST2->SetMarkerColor(kMagenta+2);
		 //grPeXPOL000noST2->SetMarkerStyle(31);
		 grPeXPOL000noST2->SetLineColor(kMagenta+2);
		 grPeXPOL000noST2->SetLineWidth(3);
		 grPeXPOL000noST2->Draw("ALP");
		 TGraph *grPeXPOL0012 = new TGraph(nsamps,Ethrmu,PeXarrPOL001); 
		 grPeXPOL0012->SetLineColor(kBlack);
		 grPeXPOL0012->SetLineWidth(3);
		 grPeXPOL0012->Draw("LP");
		 legPeXPOL0012 = new TLegend(0.2,-0.005,0.6,0.08);
		 legPeXPOL0012->AddEntry(grPeXPOL0012,"POL X0-Y0-Z1","lp");
		 legPeXPOL0012->AddEntry(grPeXPOL000noST2,"POL X0-Y0-Z0 [no SpinTracking","lp");
		 legPeXPOL0012->Draw();

		 d->cd(3);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPeXPOL000noST2 = new TGraph(nsamps,Ethrmu,PeXarrPOL000noST);
		 grPeXPOL000noST2->SetTitle("#mu-decay polarisations: X0-Y1-Z0 :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]");
         grPeXPOL000noST2->GetXaxis()->SetTitle("E_{THR} [MeV]");
         grPeXPOL000noST2->GetXaxis()->SetRangeUser(0,2.05);
         grPeXPOL000noST2->GetYaxis()->SetMoreLogLabels(1);
		 grPeXPOL000noST2->GetYaxis()->SetTitle("P_{e->X}(E_{THR})");
		 grPeXPOL000noST2->GetYaxis()->SetTitleOffset(1.8);
		 grPeXPOL000noST2->SetLineColor(kMagenta+2);
		 grPeXPOL000noST2->SetLineWidth(3);
		 grPeXPOL000noST2->Draw("ALP");
         TGraph *grPeXPOL0102 = new TGraph(nsamps,Ethrmu,PeXarrPOL010);
		 grPeXPOL0102->SetLineColor(kGreen-2);
		 grPeXPOL0102->SetLineWidth(3);
		 grPeXPOL0102->Draw("LP");		 
		 legPeXPOL0102 = new TLegend(0.2,-0.005,0.6,0.08);
		 legPeXPOL0102->AddEntry(grPeXPOL0102,"POL X0-Y1-Z0","lp");
		 legPeXPOL0102->AddEntry(grPeXPOL000noST2,"POL X0-Y0-Z0 [no SpinTracking","lp");
		 legPeXPOL0102->Draw();

         d->cd(4);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPeXPOL000noST2 = new TGraph(nsamps,Ethrmu,PeXarrPOL000noST);
		 grPeXPOL000noST2->SetTitle("#mu-decay polarisations: X1-Y0-Z0 :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]");
         grPeXPOL000noST2->GetXaxis()->SetTitle("E_{THR} [MeV]");
         grPeXPOL000noST2->GetXaxis()->SetRangeUser(0,2.05);
         grPeXPOL000noST2->GetYaxis()->SetMoreLogLabels(1);
		 grPeXPOL000noST2->GetYaxis()->SetTitle("P_{e->X}(E_{THR})");
		 grPeXPOL000noST2->GetYaxis()->SetTitleOffset(1.8);
		 grPeXPOL000noST2->SetLineColor(kMagenta+2);
		 grPeXPOL000noST2->SetLineWidth(3);
		 grPeXPOL000noST2->Draw("ALP");
         TGraph *grPeXPOL1002 = new TGraph(nsamps,Ethrmu,PeXarrPOL100);
		 grPeXPOL1002->SetLineColor(kViolet+1);
		 grPeXPOL1002->SetLineWidth(3);
		 grPeXPOL1002->Draw("LP");	 
		 legPeXPOL1002 = new TLegend(0.2,-0.005,0.6,0.08);
		 legPeXPOL1002->AddEntry(grPeXPOL1002,"POL X1-Y0-Z0","lp");
		 legPeXPOL1002->AddEntry(grPeXPOL000noST2,"POL X0-Y0-Z0 [no SpinTracking","lp");
		 legPeXPOL1002->Draw();

         d->cd(5);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPeXPOL000noST2 = new TGraph(nsamps,Ethrmu,PeXarrPOL000noST);
		 grPeXPOL000noST2->SetTitle("#mu-decay polarisations: X1-Y1-Z0 :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]");
         grPeXPOL000noST2->GetXaxis()->SetTitle("E_{THR} [MeV]");
         grPeXPOL000noST2->GetXaxis()->SetRangeUser(0,2.05);
         grPeXPOL000noST2->GetYaxis()->SetMoreLogLabels(1);
		 grPeXPOL000noST2->GetYaxis()->SetTitle("P_{e->X}(E_{THR})");
		 grPeXPOL000noST2->GetYaxis()->SetTitleOffset(1.8);
		 grPeXPOL000noST2->SetLineColor(kMagenta+2);
		 grPeXPOL000noST2->SetLineWidth(3);
		 grPeXPOL000noST2->Draw("ALP");
         TGraph *grPeXPOL1102 = new TGraph(nsamps,Ethrmu,PeXarrPOL110);
		 grPeXPOL1102->SetLineColor(kOrange+1);
		 grPeXPOL1102->SetLineWidth(3);
		 grPeXPOL1102->Draw("LP");		 
		 legPeXPOL1102 = new TLegend(0.2,-0.005,0.6,0.08);
		 legPeXPOL1102->AddEntry(grPeXPOL1102,"POL X1-Y1-Z0","lp");
		 legPeXPOL1102->AddEntry(grPeXPOL000noST2,"POL X0-Y0-Z0 [no SpinTracking","lp");
		 legPeXPOL1102->Draw();

         d->cd(6);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPeXPOL000noST2 = new TGraph(nsamps,Ethrmu,PeXarrPOL000noST);
		 grPeXPOL000noST2->SetTitle("#mu-decay polarisations: X1-Y0-Z1 :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]");
         grPeXPOL000noST2->GetXaxis()->SetTitle("E_{THR} [MeV]");
         grPeXPOL000noST2->GetXaxis()->SetRangeUser(0,2.05);
         grPeXPOL000noST2->GetYaxis()->SetMoreLogLabels(1);
		 grPeXPOL000noST2->GetYaxis()->SetTitle("P_{e->X}(E_{THR})");
		 grPeXPOL000noST2->GetYaxis()->SetTitleOffset(1.8);
		 grPeXPOL000noST2->SetLineColor(kMagenta+2);
		 grPeXPOL000noST2->SetLineWidth(3);
		 grPeXPOL000noST2->Draw("ALP");
         TGraph *grPeXPOL1012 = new TGraph(nsamps,Ethrmu,PeXarrPOL101);
		 grPeXPOL1012->SetLineColor(kRed-9);
		 grPeXPOL1012->SetLineWidth(3);
		 grPeXPOL1012->Draw("LP");
		 legPeXPOL1012 = new TLegend(0.2,-0.005,0.6,0.08);
		 legPeXPOL1012->AddEntry(grPeXPOL1012,"POL X1-Y0-Z1","lp");
		 legPeXPOL1012->AddEntry(grPeXPOL000noST2,"POL X0-Y0-Z0 [no SpinTracking","lp");
		 legPeXPOL1012->Draw();

         d->cd(7);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPeXPOL000noST2 = new TGraph(nsamps,Ethrmu,PeXarrPOL000noST);
		 grPeXPOL000noST2->SetTitle("#mu-decay polarisations: X0-Y1-Z1 :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]");
         grPeXPOL000noST2->GetXaxis()->SetTitle("E_{THR} [MeV]");
         grPeXPOL000noST2->GetXaxis()->SetRangeUser(0,2.05);
         grPeXPOL000noST2->GetYaxis()->SetMoreLogLabels(1);
		 grPeXPOL000noST2->GetYaxis()->SetTitle("P_{e->X}(E_{THR})");
		 grPeXPOL000noST2->GetYaxis()->SetTitleOffset(1.8);
		 grPeXPOL000noST2->SetLineColor(kMagenta+2);
		 grPeXPOL000noST2->SetLineWidth(3);
		 grPeXPOL000noST2->Draw("ALP");
         TGraph *grPeXPOL0112 = new TGraph(nsamps,Ethrmu,PeXarrPOL011);
		 grPeXPOL0112->SetLineColor(kBlue-3);
		 grPeXPOL0112->SetLineWidth(3);
		 grPeXPOL0112->Draw("LP");
		 legPeXPOL0112 = new TLegend(0.2,-0.005,0.6,0.08);
		 legPeXPOL0112->AddEntry(grPeXPOL0112,"POL X0-Y1-Z1","lp");
		 legPeXPOL0112->AddEntry(grPeXPOL000noST2,"POL X0-Y0-Z0 [no SpinTracking","lp");
		 legPeXPOL0112->Draw();

         d->cd(8);
		 gPad->SetLogy();
		 gPad->SetGrid(1,1);
		 TGraph *grPeXPOL000noST2 = new TGraph(nsamps,Ethrmu,PeXarrPOL000noST);
		 grPeXPOL000noST2->SetTitle("#mu-decay polarisations: X1-Y1-Z1 :: "+TString(phishiftss.str())+"-mm #Phi-shift and "+TString(zshiftss.str())+"-mm z-shift [10^5 events]");
         grPeXPOL000noST2->GetXaxis()->SetTitle("E_{THR} [MeV]");
         grPeXPOL000noST2->GetXaxis()->SetRangeUser(0,2.05);
         grPeXPOL000noST2->GetYaxis()->SetMoreLogLabels(1);
		 grPeXPOL000noST2->GetYaxis()->SetTitle("P_{e->X}(E_{THR})");
		 grPeXPOL000noST2->GetYaxis()->SetTitleOffset(1.8);
		 grPeXPOL000noST2->SetLineColor(kMagenta+2);
		 grPeXPOL000noST2->SetLineWidth(3);
		 grPeXPOL000noST2->Draw("ALP");
         TGraph *grPeXPOL1112 = new TGraph(nsamps,Ethrmu,PeXarrPOL111);
		 grPeXPOL1112->SetLineColor(kCyan+1);
		 grPeXPOL1112->SetLineWidth(3);
		 grPeXPOL1112->Draw("LP");
		 legPeXPOL1112 = new TLegend(0.2,-0.005,0.6,0.08);
		 legPeXPOL1112->AddEntry(grPeXPOL1112,"POL X1-Y1-Z1","lp");
		 legPeXPOL1112->AddEntry(grPeXPOL000noST2,"POL X0-Y0-Z0 [no SpinTracking","lp");
		 legPeXPOL1112->Draw();

         d->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shift_polarisations_w000_MULTIplicities_eff.pdf");
		 d->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shift_polarisations_w000_MULTIplicities_eff.png");
		 d->SaveAs("Recover_Planar_4mm_Al_4mm_Al_6xSDs_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shift_polarisations_w000_MULTIplicities_eff.C");
		 

      }

  
   }  


 }
 
 
 int main() {
   polbeamMULTIeff();
   return 0;
}  
