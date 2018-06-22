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

void bubble4BIN(){

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
   // With {250,500,750}-mm SciD3 3-mm Al
   std::string filemu250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e3mudecay.root";
   std::string filemu500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filemu750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filex250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e3goldcascade.root";
   std::string filex500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_3mm_Al_1e6goldcascade.root";
   std::string filex750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_3mm_Al_1e6goldcascade.root";
   // With {250,500,750}-mm SciD3 6-mm Al
   std::string file6Almu250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Almu500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Almu750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Alx250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_6mm_Al_1e6goldcascade.root";
   std::string file6Alx500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_6mm_Al_1e6goldcascade.root";
   std::string file6Alx750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_6mm_Al_1e6goldcascade.root";
   // With {250,500,750}-mm SciD3 0-mm Al
   std::string file0Almu250 = "../../simdata/bubble4/bubble_0x5mm_250mm_SciD_Nevts_SciSphere_0mm_Al_1e6mudecay.root";
   std::string file0Almu500 = "../../simdata/bubble4/bubble_0x5mm_500mm_SciD_Nevts_SciSphere_0mm_Al_1e6mudecay.root";
   std::string file0Almu750 = "../../simdata/bubble4/bubble_0x5mm_750mm_SciD_Nevts_SciSphere_0mm_Al_1e6mudecay.root";
   std::string file0Alx250 = "../../simdata/bubble4/bubble_0x5mm_250mm_SciD_Nevts_SciSphere_0mm_Al_1e6goldcascade.root";
   std::string file0Alx500 = "../../simdata/bubble4/bubble_0x5mm_500mm_SciD_Nevts_SciSphere_0mm_Al_1e6goldcascade.root";
   std::string file0Alx750 = "../../simdata/bubble4/bubble_0x5mm_750mm_SciD_Nevts_SciSphere_0mm_Al_1e6goldcascade.root";

   /*********************************/
   /*           Analysis            */
   /*********************************/

   const int nbins = 300;
  
   // TFiles
   // 3-mm Al 
   TFile* fmu250 = new TFile(TString(filemu250));
   TFile* fmu500 = new TFile(TString(filemu500));
   TFile* fmu750 = new TFile(TString(filemu750));
   TFile* fx250 = new TFile(TString(filex250));
   TFile* fx500 = new TFile(TString(filex500));
   TFile* fx750 = new TFile(TString(filex750));
   // 6-mm Al
   TFile* f6Almu250 = new TFile(TString(file6Almu250));
   TFile* f6Almu500 = new TFile(TString(file6Almu500));
   TFile* f6Almu750 = new TFile(TString(file6Almu750));
   TFile* f6Alx250 = new TFile(TString(file6Alx250));
   TFile* f6Alx500 = new TFile(TString(file6Alx500));
   TFile* f6Alx750 = new TFile(TString(file6Alx750));
   // 0-mm Al
   TFile* f0Almu250 = new TFile(TString(file0Almu250));
   TFile* f0Almu500 = new TFile(TString(file0Almu500));
   TFile* f0Almu750 = new TFile(TString(file0Almu750));
   TFile* f0Alx250 = new TFile(TString(file0Alx250));
   TFile* f0Alx500 = new TFile(TString(file0Alx500));
   TFile* f0Alx750 = new TFile(TString(file0Alx750));

 
   float Edep, EventID;
   float tEdep, iEventID, jEventID, kEventID;
   float Ethr = 0.5;
   float Pxx = 0;
   float tPxx;
   int Xray = 0;
   int elec = 0;
   
   TNtuple * mu250SciDet1 = (TNtuple*)fmu250->Get("Detector/SciDet1");
   TNtuple * mu250SciDet2 = (TNtuple*)fmu250->Get("Detector/SciDet2");
   TNtuple * mu250SciDet3 = (TNtuple*)fmu250->Get("Detector/SciDet3");
   TNtuple * x250SciDet1 = (TNtuple*)fx250->Get("Detector/SciDet1");
   TNtuple * x250SciDet2 = (TNtuple*)fx250->Get("Detector/SciDet2");
   TNtuple * x250SciDet3 = (TNtuple*)fx250->Get("Detector/SciDet3");
   mu250SciDet1->SetBranchAddress("Edep",&Edep);
   mu250SciDet1->SetBranchAddress("EventID",&EventID);
   mu250SciDet2->SetBranchAddress("Edep",&Edep);
   mu250SciDet2->SetBranchAddress("EventID",&EventID);
   mu250SciDet3->SetBranchAddress("Edep",&Edep);
   mu250SciDet3->SetBranchAddress("EventID",&EventID);
   x250SciDet1->SetBranchAddress("Edep",&Edep);
   x250SciDet1->SetBranchAddress("EventID",&EventID);
   x250SciDet2->SetBranchAddress("Edep",&Edep);
   x250SciDet2->SetBranchAddress("EventID",&EventID);
   x250SciDet3->SetBranchAddress("Edep",&Edep);
   x250SciDet3->SetBranchAddress("EventID",&EventID);
   

   for (int i=0; i< x250SciDet1->GetEntries(); i++) {
//   for (int i=0; i < 20; i++) {
      x250SciDet1->GetEntry(i);
	  tPxx = 0;
	  iEventID = EventID;
	   
	  if (Edep < Ethr) {
         tPxx += 1;   
	  
	     for (int j=0; j< x250SciDet2->GetEntries(); j++) {		
		    x250SciDet2->GetEntry(j);		  
		    if (EventID == iEventID) {
			   jEventID = EventID;
		       if (Edep < Ethr) {
			      tPxx += 1;

                  for (int k=0; k< x250SciDet3->GetEntries(); k++) {
		             x250SciDet3->GetEntry(k);
             
		             if ((EventID == iEventID) && (EventID == jEventID)) {
				        //std::cout << "EventID = " << EventID << " iEventID = " << iEventID << " jEventID = " << jEventID <<std::endl;
			            if ((Edep >= Ethr) && (Edep < 10) && (tPxx == 2)) {
			               Xray += 1;
			               std::cout << "i,j,k = " << i << "," << j << "," << k << " Edep= " << Edep << " Pass = " << tPxx << std::endl;
			            } else {
			               elec += 1;
			            }
			         }
			           
		          }
		             
		       } else {
				   elec += 1;
			   }	   
		    }     
         }		   	  
      } else {
	       elec += 1;
	  }      	  
   }
			   
   std::cout << "Xray = " << Xray << " and elec = " << elec << std::endl;

  
 }
 
 
 int main() {
   bubble4BIN();
   return 0;
}  
