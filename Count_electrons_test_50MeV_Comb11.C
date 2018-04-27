// I/O
#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdio>
#include <stdlib>
using namespace std;

//ROOT includes
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


void Count_electrons_test_50MeV_Comb11(){

   //Some style definitions
   //gROOT->Reset();
   //gROOT->SetStyle("Plain");
   gStyle->SetPaperSize(26,20);
   gStyle->SetOptStat(1);
   gStyle->SetTitleXOffset(1.15);
   gStyle->SetTitleYOffset(1.15);
   gStyle->SetTitleBorderSize(0);
   gStyle->SetLegendBorderSize(0.1);
   gStyle->SetPadBottomMargin(0.12);
   gStyle->SetPadLeftMargin(0.12);
   gStyle->SetPadTopMargin(0.12);
   //gStyle->SetPadRightMargin(0.05);
   gStyle->SetCanvasColor(0);
   gStyle->SetPadColor(0);
   gStyle->SetTitleFillColor(0);
   gStyle->SetPalette(1,0);
   //gStyle->SetOptTitle(kFALSE);
   gStyle->SetLabelSize(0.045,"XYZ");
   gStyle->SetTitleSize(0.05,"XYZ");
   gStyle->SetHistLineWidth(2);

   TGraph *g1 = new TGraph();
   
   /********************************/
   /*  10 MeV isotropic e- source  */
   /********************************/
   // Name of the file
   std::string file1 = "Real_Cav_test_50MeV_elec_Comb11_Nevts_SciL_1e63.root";
   std::string file1sub = file1.substr(0,file1.find(".root"));
   std::string FileName1 = ""+file1;
   std::string plotName1 = "Plot_"+file1sub;

   TFile* f1 = new TFile(TString(FileName1));
   
   Float_t PDGid, EventID, TrackID, Edep, ParentID;


   /**************************/
   /*       Parameters       */
   /**************************/
   int scintillator = 3; //mm

   float Etrsh = 0.5;   // Threshold (noise)
   float EElecTh = 10.0; // Threshold (electron)
   float ESciTh = 0.2; // Threshold (light scintillator)
   const int nEvts = 1000000;
   const int scidepo = 0; // Counter of detections in SciDets 
   const int bgodepo = 0; // Counter of detections in BGOs 
   const int scidepoR = 0; // Counter of incident detections in SciDets
   const int bgodepoR = 0; // Counter of incident detections in BGOs
   const int grid = 0; // Counter of detections in grid [X-check]
   const int sci = 0; // Counter of detections in SciDets
   const int bgo = 0; // Counter of detections in BGOs
   const int sciR = 0; // Counter of incident detections in SciDets 
   const int bgoR = 0; // Counter of incident detections in BGOs

   /*************************/
   /*       Integrals       */
   /*************************/
   float intE = 0;
   float intNum = 0;
   float intDen = 0;
   float intOver50 = 0;

   float sumh1 = 0;
   float sumh2 = 0;
   float sumh3 = 0;
   float sumh4 = 0;
   float sumh5 = 0;
   float sumh6 = 0;

   /*************************/
   /*       Detectors       */
   /*************************/
   float Edeptot[nEvts] = {};
   float EdeptotSci[nEvts] = {};
   float EdeptotBGO[nEvts] = {};
   float EdeptotGrid[nEvts] = {}; // [X-check only]
   float rEdeppSciDetIn0[nEvts] = {};
   float rEdeppSciDetIn1[nEvts] = {};
   float rEdeppSciDetIn2[nEvts] = {};
   float rEdeppSciDetFIn0[nEvts] = {};
   float rEdeppSciDetFIn1[nEvts] = {};
   float rEdeppSciDetFIn2[nEvts] = {};
   float rEdeppBGODet1B[nEvts] = {};
   float rEdeppBGODet2B[nEvts] = {};
   float rEdeppBGODet3F[nEvts] = {};
   float rEdeppGrid1F[nEvts] = {}; // Cross-check
   float rEdeppGrid2B[nEvts] = {}; // Cross-check

   //SciDetIn0
   TNtuple * SciDetIn0 = (TNtuple*)f1->Get("Detector/FullSetArietteFoxTheOuterBoxAlBoxVacBoxTorinoMolinoSciDetIn0");
   SciDetIn0->SetBranchAddress("Edep", &Edep);
   SciDetIn0->SetBranchAddress("PDGid", &PDGid);
   SciDetIn0->SetBranchAddress("EventID", &EventID);
   SciDetIn0->SetBranchAddress("ParentID", &ParentID);
   
   for (int i=0; i<SciDetIn0->GetEntries(); ++i) {
      SciDetIn0->GetEntry(i);
      rEdeppSciDetIn0[(const int)EventID] = Edep;
      if (rEdeppSciDetIn0[(const int)EventID] != 0) sci++;
      if ((rEdeppSciDetIn0[(const int)EventID] != 0) && (Edeptot[(const int)EventID] == 0)) sciR++;
   }
   scidepo += SciDetIn0->GetEntries();
   std::cout << "sciR = " << sciR << " sci = " << sci << std::endl;
   ////std::cout << "SciDetIn0 = " << SciDetIn0->GetEntries() << std::endl;
   ////std::cout << "sci = " << sci << std::endl;
   //std::cout << "sci/scidepo = " << sci/(double)scidepo << std::endl;

   //SciDetFIn0
   TNtuple * SciDetFIn0 = (TNtuple*)f1->Get("Detector/FullSetArietteFoxTheOuterBoxAlBoxVacBoxTorinoMolinoSciDetFIn0");
   SciDetFIn0->SetBranchAddress("Edep", &Edep);
   SciDetFIn0->SetBranchAddress("PDGid", &PDGid);
   SciDetFIn0->SetBranchAddress("EventID", &EventID);
   SciDetFIn0->SetBranchAddress("ParentID", &ParentID);
  
   for (int i=0; i<SciDetFIn0->GetEntries(); ++i) {
      SciDetFIn0->GetEntry(i);
      rEdeppSciDetFIn0[(const int)EventID] = Edep;
      if (rEdeppSciDetFIn0[(const int)EventID] != 0) sci++;
      if ((rEdeppSciDetFIn0[(const int)EventID] != 0) && (Edeptot[(const int)EventID] == 0)) sciR++;
      Edeptot[(const int)EventID] += rEdeppSciDetFIn0[(const int)EventID];
   }
   scidepo += SciDetFIn0->GetEntries();
   std::cout << " sciR = "<< sciR << " sci = " << sci << std::endl;
   ////std::cout << "SciDetFIn0 = " << SciDetFIn0->GetEntries() << std::endl;
   ////std::cout << "sci = " << sci << std::endl;
   //std::cout << "sci/scidepo = " << sci/(double)scidepo << std::endl;
   

   //SciDetIn1
   TNtuple * SciDetIn1 = (TNtuple*)f1->Get("Detector/FullSetArietteFoxTheOuterBoxAlBoxVacBoxTorinoMolinoSciDetIn1");
   SciDetIn1->SetBranchAddress("Edep", &Edep);
   SciDetIn1->SetBranchAddress("PDGid", &PDGid);
   SciDetIn1->SetBranchAddress("EventID", &EventID);
   SciDetIn1->SetBranchAddress("ParentID", &ParentID);

   for (int i=0; i<SciDetIn1->GetEntries(); ++i) {
      SciDetIn1->GetEntry(i);
      rEdeppSciDetIn1[(const int)EventID] = Edep;
      if (rEdeppSciDetIn1[(const int)EventID] != 0) sci++;
      if ((rEdeppSciDetIn1[(const int)EventID] != 0) && (Edeptot[(const int)EventID] == 0)) sciR++;
      Edeptot[(const int)EventID] += rEdeppSciDetIn1[(const int)EventID];
   }
   scidepo += SciDetIn1->GetEntries();
   std::cout << "sciR = " << sciR << " sci = " << sci << std::endl;
   ////std::cout << "SciDetIn1 = " << SciDetIn1->GetEntries() << std::endl;
   ////std::cout << "sci = " << sci << std::endl;  
   //std::cout << "sci/scidepo = " <<sci/(double)scidepo << std::endl;


   //SciDetFIn1
   TNtuple * SciDetFIn1 = (TNtuple*)f1->Get("Detector/FullSetArietteFoxTheOuterBoxAlBoxVacBoxTorinoMolinoSciDetFIn1");
   SciDetFIn1->SetBranchAddress("Edep", &Edep);
   SciDetFIn1->SetBranchAddress("PDGid", &PDGid);
   SciDetFIn1->SetBranchAddress("EventID", &EventID);
   SciDetFIn1->SetBranchAddress("ParentID", &ParentID);

   for (int i=0; i<SciDetFIn1->GetEntries(); ++i) {
      SciDetFIn1->GetEntry(i);
      rEdeppSciDetFIn1[(const int)EventID] = Edep;
      if (rEdeppSciDetFIn1[(const int)EventID] != 0) sci++;
      if ((rEdeppSciDetFIn1[(const int)EventID] != 0) && (Edeptot[(const int)EventID] == 0)) sciR++;
      Edeptot[(const int)EventID] += rEdeppSciDetFIn1[(const int)EventID];
   }
   scidepo += SciDetFIn1->GetEntries();
   std::cout <<" sciR= " << sciR << " sci = " << sci <<std::endl;
   ////std::cout << "SciDetFIn1 = " << SciDetFIn1->GetEntries() << std::endl;
   ////std::cout << "sci = " << sci << std::endl;
   //std::cout << "sci/scidepo = " << sci/(double)scidepo << std::endl;


   //SciDetIn2
   TNtuple * SciDetIn2 = (TNtuple*)f1->Get("Detector/FullSetArietteFoxTheOuterBoxAlBoxVacBoxTorinoMolinoSciDetIn2");
   SciDetIn2->SetBranchAddress("Edep", &Edep);
   SciDetIn2->SetBranchAddress("PDGid", &PDGid);
   SciDetIn2->SetBranchAddress("EventID", &EventID);
   SciDetIn2->SetBranchAddress("ParentID", &ParentID);

   for (int i=0; i<SciDetIn2->GetEntries(); ++i) {
      SciDetIn2->GetEntry(i);
      rEdeppSciDetIn2[(const int)EventID] = Edep;
      if (rEdeppSciDetIn2[(const int)EventID] != 0) sci++;
      if ((rEdeppSciDetIn2[(const int)EventID] != 0) && (Edeptot[(const int)EventID] == 0)) sciR++;
      Edeptot[(const int)EventID] += rEdeppSciDetIn2[(const int)EventID];
   }
   scidepo += SciDetIn2->GetEntries();
   std::cout << "sciR="<< sciR <<  " sci = " << sci << std::endl;
   ////std::cout << "SciDetIn2 = " << SciDetIn2->GetEntries() << std::endl;
   ////std::cout << "sci = " << sci << std::endl;
   //std::cout << "sci/scidepo = " << sci/(double)scidepo << std::endl;   


   //SciDetFIn2
   TNtuple * SciDetFIn2 = (TNtuple*)f1->Get("Detector/FullSetArietteFoxTheOuterBoxAlBoxVacBoxTorinoMolinoSciDetFIn2");
   SciDetFIn2->SetBranchAddress("Edep", &Edep);
   SciDetFIn2->SetBranchAddress("PDGid", &PDGid);
   SciDetFIn2->SetBranchAddress("EventID", &EventID);
   SciDetFIn2->SetBranchAddress("ParentID", &ParentID);
 
   for (int i=0; i<SciDetFIn2->GetEntries(); ++i) {
      SciDetFIn2->GetEntry(i);
      rEdeppSciDetFIn2[(const int)EventID] = Edep;
      if (rEdeppSciDetFIn2[(const int)EventID] != 0) sci++;
      if ((rEdeppSciDetFIn2[(const int)EventID] != 0) && (Edeptot[(const int)EventID] == 0)) sciR++;
      Edeptot[(const int)EventID] += rEdeppSciDetFIn2[(const int)EventID];
   } 
   scidepo += SciDetFIn2->GetEntries();
   std::cout << "sciR = "<<sciR <<" sci = " << sci <<std::endl;
   ////std::cout << "SciDetFIn2 = " << SciDetFIn2->GetEntries() << std::endl;
   ////std::cout << "sci = " << sci << std::endl;
   //std::cout << "sci/scidepo = " << sci/(double)scidepo << std::endl;


   //BGODet1B
   TNtuple * BGODet1B = (TNtuple*)f1->Get("Detector/FullSetArietteBGODet1B");
   BGODet1B->SetBranchAddress("Edep", &Edep);
   BGODet1B->SetBranchAddress("PDGid", &PDGid);
   BGODet1B->SetBranchAddress("EventID", &EventID);

   for (int i=0; i<BGODet1B->GetEntries(); ++i) {
      BGODet1B->GetEntry(i);
      std::cout << "Edep[" << i << "] = " << Edep << std::endl;
      rEdeppBGODet1B[i] = Edep;
      std::cout << "EventID[" << i << "] = " << EventID[i] << std::endl;
      //rEdeppBGODet1B[(const int)EventID] = Edep;
      EdeptotBGO[(const int)EventID] += rEdeppBGODet1B[(const int)EventID];
      if (rEdeppBGODet1B[(const int)EventID] != 0) bgo++;
      if ((rEdeppBGODet1B[(const int)EventID] != 0) && (Edeptot[(const int)EventID] == 0)) bgoR++;
      Edeptot[(const int)EventID] += rEdeppBGODet1B[(const int)EventID];
   }
   bgodepo += BGODet1B->GetEntries();
   std::cout << " bgoR = " << bgoR << " bgo = "<< bgo << std::endl;
   //std::cout << "BGODet1B = " << BGODet1B->GetEntries() << std::endl;
   //std::cout << "bgo = " << bgo << std::endl;
   //std::cout << "bgo/bgodepo = " << bgo/(double)bgodepo << std::endl;   


   //BGODet2B
   TNtuple * BGODet2B = (TNtuple*)f1->Get("Detector/FullSetArietteBGODet2B");
   BGODet2B->SetBranchAddress("Edep", &Edep);
   BGODet2B->SetBranchAddress("PDGid", &PDGid);
   BGODet2B->SetBranchAddress("EventID", &EventID);
  
   for (int i=0; i<BGODet2B->GetEntries(); ++i) {
      BGODet2B->GetEntry(i);
      rEdeppBGODet2B[(const int)EventID] = Edep;
      EdeptotBGO[(const int)EventID] += rEdeppBGODet2B[(const int)EventID];
      if (rEdeppBGODet2B[(const int)EventID] != 0) bgo++;
      if ((rEdeppBGODet2B[(const int)EventID] != 0) && (Edeptot[(const int)EventID] == 0)) bgoR++;
      Edeptot[(const int)EventID] += rEdeppBGODet2B[(const int)EventID];
   }
   bgodepo += BGODet2B->GetEntries();
   std::cout <<" bgoR = " << bgoR << " bgo = " << bgo << std::endl;
   //std::cout << "BGODet2B = " << BGODet2B->GetEntries() << std::endl;
   //std::cout << "bgo = " << bgo << std::endl;
   //std::cout << "bgo/bgodepo = " << bgo/(double)bgodepo << std::endl;


   //BGODet3F
   TNtuple * BGODet3F = (TNtuple*)f1->Get("Detector/FullSetArietteBGODet3F");
   BGODet3F->SetBranchAddress("Edep", &Edep);
   BGODet3F->SetBranchAddress("PDGid", &PDGid);
   BGODet3F->SetBranchAddress("EventID", &EventID);

   for (int i=0; i<BGODet3F->GetEntries(); ++i) {
      BGODet3F->GetEntry(i);
      rEdeppBGODet3F[(const int)EventID] = Edep;
      EdeptotBGO[(const int)EventID] += rEdeppBGODet3F[(const int)EventID];
      if (rEdeppBGODet3F[(const int)EventID] != 0) bgo++;
      if ((rEdeppBGODet3F[(const int)EventID] != 0) && (Edeptot[(const int)EventID] == 0)) bgoR++;
      Edeptot[(const int)EventID] += rEdeppBGODet3F[(const int)EventID];
   }
   bgodepo += BGODet3F->GetEntries();
   std::cout << "bgoR = " << bgoR << " bgo = " << bgo << std::endl;
   //std::cout << "BGODet3F = " << BGODet3F->GetEntries() << std::endl;
   //std::cout << "bgo = " << bgo << std::endl;
   //std::cout << "bgo/bgodepo = " << bgo/(double)bgodepo << std::endl;


   //Cross-check
   //Grid1F
   TNtuple * Grid1F = (TNtuple*)f1->Get("Detector/FullSetArietteFoxTheOuterBoxAlBoxVacBoxTorinoMolinoOuterGrid1F");
   Grid1F->SetBranchAddress("Edep", &Edep);
   Grid1F->SetBranchAddress("EventID", &EventID);

   for (int i=0; i<Grid1F->GetEntries(); ++i) {
      Grid1F->GetEntry(i);
      rEdeppGrid1F[(const int)EventID] = Edep;
   }
   //std::cout << "Cross-check: Grid1F = " << Grid1F->GetEntries() << std::endl;


   //Grid2B
   TNtuple * Grid2B = (TNtuple*)f1->Get("Detector/FullSetArietteFoxTheOuterBoxAlBoxVacBoxTorinoMolinoOuterGrid2B");
   Grid2B->SetBranchAddress("Edep", &Edep);
   Grid2B->SetBranchAddress("EventID", &EventID);
   
   for (int i=0; i<Grid2B->GetEntries(); ++i) {
      Grid2B->GetEntry(i);
      rEdeppGrid2B[(const int)EventID] = Edep;
   }
   //std::cout << "Cross-check: Grid2B = " << Grid2B->GetEntries() << std::endl;


   
   /*********************************/
   /*      Conditions for cuts      */
   /*********************************/

   for (int j=0; j<nEvts; j++) {
      if (Edeptot[j] > 10) {
         intE += 1;
      }
      if (Edeptot[j] > 50) {
         intOver50 += 1;
         freopen(TString("buggology_"+file1sub+".txt"),"a",stdout);
         std::cout << "Edeptot[" << j << "] = "<< Edeptot[j] << std::endl;
         std::cout << "SciDetIn0[" << j << "] = " << rEdeppSciDetIn0[j] << std::endl;
         std::cout << "SciDetFIn0[" << j << "] = "<< rEdeppSciDetFIn0[j] << std::endl;
         std::cout << "SciDetIn1[" << j << "] = " << rEdeppSciDetIn1[j] << std::endl;
         std::cout << "SciDetFIn1[" << j << "] = " << rEdeppSciDetFIn1[j] << std::endl;
         std::cout << "SciDetIn2[" << j << "] = " << rEdeppSciDetIn2[j] << std::endl;
         std::cout << "SciDetFIn2[" << j << "] = " << rEdeppSciDetFIn2[j] << std::endl;
         std::cout << "BGODet1B[" << j << "] = " << rEdeppBGODet1B[j] << std::endl;
         std::cout << "BGODet2B[" << j << "] = " << rEdeppBGODet2B[j] << std::endl;
         std::cout << "BGODet3F[" << j << "] = " << rEdeppBGODet3F[j] << std::endl;
         std::cout << std::endl;
         fclose(stdout);
         freopen("/dev/tty","a",stdout);

         //std::cout << "Edep[" << j << "] = " << Edeptot[j] << std::endl;
      }
   
      //Numerator
      if ((((rEdeppBGODet1B[j] + rEdeppBGODet2B[j]) > Etrsh) && ((rEdeppBGODet1B[j] + rEdeppBGODet2B[j]) < EElecTh)) || ((rEdeppBGODet3F[j] > Etrsh) && (rEdeppBGODet3F[j] < EElecTh))) {
         if ((rEdeppSciDetIn0[j] < ESciTh) && (rEdeppSciDetIn1[j] < ESciTh) && (rEdeppSciDetIn2[j] < ESciTh) && (rEdeppSciDetFIn0[j] < ESciTh) && (rEdeppSciDetFIn1[j] < ESciTh) && (rEdeppSciDetFIn2[j] < ESciTh)) {
            intNum += 1;
         }
      }

      //Denominator
      if ((EdeptotBGO[j] > Etrsh) && (EdeptotBGO[j] < EElecTh)) {
         intDen += 1;
      }
   } //Closing loop j


   std::cout << "Loaded file: " << file1 << std::endl;
//   std::cout << std::fixed << std::setprecision(2) << std::fixed;
   std::cout << "Counts of electrons: " << intE << "/" << nEvts << " = " << (double)(intE/nEvts*100) << "%" << std::endl;
   std::cout << "Hits on SCI: " << scidepo << "/" << nEvts << " = " << scidepo/(double)nEvts*100 << "%" << std::endl;
   std::cout << "Hits on BGO: " << bgodepo << "/" << nEvts << " = " << bgodepo/(double)nEvts*100 << "%" << std::endl;
   std::cout << "Incident hits on SCI: " << sciR << "/" << nEvts << " = " << sciR/(double)nEvts*100 << "%" << std::endl;
   std::cout << "Incident hits on BGO: " << bgoR << "/" << nEvts << " = " << bgoR/(double)nEvts*100 << "%" << std::endl;
   std::cout << "E(e->X) = " << intNum << "/" << intDen << " = " << intNum/(double)intDen*100 << "%" << std::endl;
   std::cout << "Counts of >50 MeV: " << intOver50 << "/" << nEvts << " = " << (double)(intOver50/nEvts*100) << "%" << std::endl;  

   //Save the results in the output file
   freopen(TString("Edep_"+file1sub+".txt"),"a",stdout);
   std::cout << "Loaded file: " << file1 << std::endl;
//   std::cout << std::fixed << std::setprecision(2) << std::fixed;
   std::cout << "Counts of electrons: " << intE << "/" << nEvts << " = " << intE/(double)nEvts*100 << "%" << std::endl;
   std::cout << "Hits on SCI: " << scidepo << "/" << nEvts << " = " << scidepo/(double)nEvts*100 << "%" << std::endl;
   std::cout << "Hits on BGO: " << bgodepo << "/" << nEvts << " = " << bgodepo/(double)nEvts*100 << "%" << std::endl;
   std::cout << "Incident hits on SCI: " << sciR << "/" << nEvts << " = " << sciR/(double)nEvts*100 << "%" << std::endl;
   std::cout << "Incident hits on BGO: " << bgoR << "/" << nEvts << " = " << bgoR/(double)nEvts*100 << "%" << std::endl;
   std::cout << "E(e->X) = " << intNum << "/" << intDen << " = " << intNum/(double)intDen*100 << "%" << std::endl;
   std::cout << "Counts of >50 MeV: " << intOver50 << "/" << nEvts << " = " << (double)(intOver50/nEvts*100) << "%" << std::endl;
   std::cout << std::endl;
   fclose(stdout);
   freopen("/dev/tty","a",stdout); 

   //Plotting
   const int nbins = 100;
   float h1counts[nbins] = {};
   float h1counts[nbins] = {};
   float h2counts[nbins] = {};
   float h3counts[nbins] = {};
   float h4counts[nbins] = {};
   float h5counts[nbins] = {};
   float h6counts[nbins] = {};
   float cuth1counts[nbins] = {};
   float cutlowerbinedgesh1[nbins] = {};
   float cutupperbinedgesh1[nbins] = {};
   float lowerbinedgesh1[nbins] = {};
   float lowerbinedgesh2[nbins] = {};
   float lowerbinedgesh3[nbins] = {};
   float lowerbinedgesh4[nbins] = {};
   float lowerbinedgesh5[nbins] = {};
   float lowerbinedgesh6[nbins] = {};
   float upperbinedgesh1[nbins] = {};
   float upperbinedgesh2[nbins] = {};
   float upperbinedgesh3[nbins] = {};
   float upperbinedgesh4[nbins] = {};
   float upperbinedgesh5[nbins] = {};
   float upperbinedgesh6[nbins] = {};

   float loweredgeh1, loweredgeh2, loweredgeh3, loweredgeh4, loweredgeh5, loweredgeh6;
   float upperedgeh1, upperedgeh2, upperedgeh3, upperedgeh4, upperedgeh5, upperedgeh6;

   if (scintillator == 1) {  //1mm
      //loweredgeh1 = -0.46;
      //loweredgeh2 = -0.455;
      //loweredgeh3 = -0.46;
      //loweredgeh1 = 0;
      loweredgeh1 = 0;
      loweredgeh2 = 0;
      loweredgeh3 = 0;
      loweredgeh4 = -0.072;
      loweredgeh5 = -0.104;
      loweredgeh6 = -0.056;
      upperedgeh1 = 38.0;
//      upperedgeh1 = 45.54;
      upperedgeh2 = 45.955;
      upperedgeh3 = 46.46;
      upperedgeh4 = 7.272;
      upperedgeh5 = 10.504;
      upperedgeh6 = 5.656;
   }

   if (scintillator == 2) {   //2mm
      //loweredgeh1 = -0.445;
      //loweredgeh2 = -0.455;
      //loweredgeh3 = -0.45;
      loweredgeh1 = 0;
      loweredgeh2 = 0;
      loweredgeh3 = 0;
      loweredgeh4 = -0.09;
      loweredgeh5 = -0.075;
      loweredgeh6 = -0.093;
      upperedgeh1 = 44.055;
      upperedgeh2 = 45.955;
      upperedgeh3 = 45.45;
      upperedgeh4 = 9.09;
      upperedgeh5 = 7.575;
      upperedgeh6 = 9.393;
   }

   if (scintillator == 3) {   //3mm
      //loweredgeh1 = -0.435;
      //loweredgeh2 = -0.44;
      //loweredgeh3 = -0.45;
      loweredgeh1 = 0;
      loweredgeh2 = 0;
      loweredgeh3 = 0;
      loweredgeh4 = -0.108;
      loweredgeh5 = -0.134;
      loweredgeh6 = -0.116;
      upperedgeh1 = 43.065;
      upperedgeh2 = 44.44;
      upperedgeh3 = 45.45;
      upperedgeh4 = 10.908;
      upperedgeh5 = 13.534;
      upperedgeh6 = 11.716;
   }
/*
   float loweredgeh1 = -0.46; //1mm
   //float loweredgeh1 = -0.445; //2mm
   //float loweredgeh1 = -0.435; //3mm
   float loweredgeh2 = -0.455; //1mm
   //float loweredgeh2 = -0.455; //2mm
   //float loweredgeh2 = -0.44; //3mm
   float loweredgeh3 = -0.46; //1mm
   //float loweredgeh3 = -0.45; //2mm
   //float loweredgeh3 = -0.45; //3mm
   float loweredgeh4 = -0.072; //1mm
   //float loweredgeh4 = -0.09; //2mm
   //float loweredgeh4 = -0.108; //3mm
   float loweredgeh5 = -0.104; //1mm
   //float loweredgeh5 = -0.075; //2mm
   //float loweredgeh5 = -0.134; //3mm
   float loweredgeh6 = -0.056; //1mm
   //float loweredgeh6 = -0.093; //2mm
   //float loweredgeh6 = -0.116; //3mm
   float upperedgeh1 = 45.54; //1mm
   //float upperedgeh1 = 44.055; //2mm
   //float upperedgeh1 = 43.065; //3mm
   float upperedgeh2 = 45.955; //1mm
   //float upperedgeh2 = 45.955; //2mm
   //float upperedgeh2 = 44.44; //3mm
   float upperedgeh3 = 46.46; //1mm
   //float upperedgeh3 = 45.45; //2mm
   //float upperedgeh3 = 45.45; //3mm
   float upperedgeh4 = 7.272; //1mm
   //float upperedgeh4 = 9.09; //2mm
   //float upperedgeh4 = 10.908; //3mm
   float upperedgeh5 = 10.504; //1mm
   //float upperedgeh5 = 7.575; //2mm
   //float upperedgeh5 = 13.534; //3mm
   float upperedgeh6 = 5.656; //1mm
   //float upperedgeh6 = 9.393; //2mm
   //float upperedgeh6 = 11.716; //3mm
*/
   float binwidthh1 = (upperedgeh1 - loweredgeh1)/nbins;
   float binwidthh2 = (upperedgeh2 - loweredgeh2)/nbins;
   float binwidthh3 = (upperedgeh3 - loweredgeh3)/nbins;
   float binwidthh4 = (upperedgeh4 - loweredgeh4)/nbins;
   float binwidthh5 = (upperedgeh5 - loweredgeh5)/nbins;
   float binwidthh6 = (upperedgeh6 - loweredgeh6)/nbins;
 

   for (int i=0; i<nbins; i++) {
      if (i == 0) { 
         lowerbinedgesh1[0] = loweredgeh1;
         upperbinedgesh1[0] = lowerbinedgesh1[0]+binwidthh1;    

         lowerbinedgesh2[0] = loweredgeh2;
         lowerbinedgesh2[0] = lowerbinedgesh2[0]+binwidthh2;
   
         lowerbinedgesh3[0] = loweredgeh3;
         lowerbinedgesh3[0] = lowerbinedgesh3[0]+binwidthh3;

         lowerbinedgesh4[0] = loweredgeh4;
         upperbinedgesh4[0] = lowerbinedgesh4[0]+binwidthh4;
         //bincentersh4[0] = loweredgeh4 + (binwidthh4*0.5);
         
         lowerbinedgesh5[0] = loweredgeh5;
         upperbinedgesh5[0] = lowerbinedgesh5[0]+binwidthh5;

         lowerbinedgesh6[0] = loweredgeh6;
         upperbinedgesh6[0] = lowerbinedgesh6[0]+binwidthh6;
      } else {
         lowerbinedgesh1[i] = lowerbinedgesh1[i-1] + binwidthh1;
         upperbinedgesh1[i] = upperbinedgesh1[i-1] + binwidthh1;

         lowerbinedgesh2[i] = lowerbinedgesh2[i-1] + binwidthh2;
         upperbinedgesh2[i] = upperbinedgesh2[i-1] + binwidthh2;

         lowerbinedgesh3[i] = lowerbinedgesh3[i-1] + binwidthh3;
         upperbinedgesh3[i] = upperbinedgesh3[i-1] + binwidthh3;

         lowerbinedgesh4[i] = lowerbinedgesh4[i-1] + binwidthh4;
         upperbinedgesh4[i] = upperbinedgesh4[i-1] + binwidthh4;
         //bincentersh4[i] = bincentersh4[i-1] + binwidthh4;
         
         lowerbinedgesh5[i] = lowerbinedgesh5[i-1] + binwidthh5;
         upperbinedgesh5[i] = upperbinedgesh5[i-1] + binwidthh5;

         lowerbinedgesh6[i] = lowerbinedgesh6[i-1] + binwidthh6;
         upperbinedgesh6[i] = upperbinedgesh6[i-1] + binwidthh6;
     }
   }
   for (int i=0; i<BGODet1B->GetEntries(); i++) {
   //for (int i=0; i<nbins; i++) {
   std::cout << "BGODet1B[" << i << "] = " << rEdeppBGODet1B[i] << std::endl;
      for (int j=0; j<nbins; j++) {
         if (rEdeppBGODet1B[i] >= lowerbinedgesh1[j]) {
            if (j < (nbins-1)) {
               h1counts[j+1] += 1;
            } else {
               h1counts[j] += 1;
            }
         }
   } 
   }  

   std::cout << "lower edge: " << lowerbinedgesh1[0] << " upper edge: " << upperbinedgesh1[0] << std::endl;

   for (int i=0; i<nbins; i++) {
         if (rEdeppBGODet2B[i] > lowerbinedgesh2[j]) {
            if (j < (nbins-1)) {
               h2counts[j+1] += 1;
            } else {
               h2counts[j] += 1;
            }
         }

         if (rEdeppBGODet3F[i] > lowerbinedgesh3[j]) {
            if (j < (nbins-1)) {
               h3counts[j+1] += 1;
            } else {
               h3counts[j] += 1;
            }
         }

         if (rEdeppSciDetIn0[i] > lowerbinedgesh4[j]) {
            if (j < (nbins-1)) {            
               h4counts[j+1] += 1;
            } else {
               h4counts[j] += 1;
            }
         }
    
         if (rEdeppSciDetIn1[i] > lowerbinedgesh5[j]) {
            if (j < (nbins-1)) {
               h5counts[j+1] += 1;
            } else {
               h5counts[j] += 1;
            }
         }

         if (rEdeppSciDetIn2[i] > lowerbinedgesh6[j]) {
            if (j < (nbins-1)) {
               h6counts[j+1] += 1;
            } else {
               h6counts[j] += 1;
            }
         }
      }
//   }


   TCanvas *c = new TCanvas("c","Edep",800,600);
   c->Divide(3,2);
   //const int EntriesSciDetIn0 = SciDetIn0->GetEntries();
   //std::cout << "EntriesSciDetIn0 = "<< EntriesSciDetIn0 << std::endl;
   //double xSciDetIn0[EntriesSciDetIn0];
//   TH1F *hist1 = new TH1F("BGODet1B","Edep [summed], BGODet1B",nbins,lowerbinedgesh1[0],upperbinedgesh1[nbins-1]);
   TH1F *hist1 = new TH1F("BGODet1B","Edep [summed], BGODet1B",nbins,lowerbinedgesh1[0],upperbinedgesh1[nbins-1]);
   TH1F *hist2 = new TH1F("BGODet2B","Edep [summed], BGODet2B",nbins,5,upperbinedgesh2[nbins-1]);
   TH1F *hist3 = new TH1F("BGODet3F","Edep [summed], BGODet3F",nbins,5,upperbinedgesh3[nbins-1]);
   TH1F *hist4 = new TH1F("SciDetIn0","Edep [summed], SciDetIn0",nbins,lowerbinedgesh4[0],upperbinedgesh4[nbins-1]);
   TH1F *hist5 = new TH1F("SciDetIn1","Edep [summed], SciDetIn1",nbins,lowerbinedgesh5[0],upperbinedgesh5[nbins-1]);
   TH1F *hist6 = new TH1F("SciDetIn2","Edep [summed], SciDetIn2",nbins,lowerbinedgesh6[0],upperbinedgesh6[nbins-1]);

   for (int i=0; i<BGODet1B->GetEntries();i++) {
      hist1->Fill(rEdeppBGODet1B[i],1);
   }

   TH1F *copyhist = (TH1F*) hist1->Clone();
   copyhist->SetName("copyhist");
   std::cout << "entries: " << copyhist->GetEntries() << " mean: " << copyhist->GetMean() << " getRMS: " << copyhist->GetRMS() << std::endl;  
   copyhist->GetXaxis()->SetRangeUser(5,upperbinedgesh1[nbins-1]);
   std::cout << "NEW: entries: " << copyhist->GetEntries() << " mean: " << copyhist->GetMean() << " getRMS: " << copyhist->GetRMS() << std::endl;
   TAxis *chaxis = copyhist->GetXaxis();
   Int_t binx = chaxis->FindBin(5);
   std::cout << "bin number: " << binx << " (" << chaxis->GetBinLowEdge(binx) << "," << chaxis->GetBinUpEdge(binx) << ")" << " bin contents: " << copyhist->GetBinContent(binx) << std::endl;


  for (int i=0; i<BGODet2B->GetEntries();i++) {
      hist2->Fill(rEdeppBGODet2B[i],1);
   }

   for (int i=0; i<BGODet3F->GetEntries();i++) {
      hist3->Fill(rEdeppBGODet3F[i],1);
   }

   for (int i=0; i<SciDetIn0->GetEntries();i++) {
      hist4->Fill(rEdeppSciDetIn0[i],1);
   }
  
   for (int i=0; i<SciDetIn1->GetEntries();i++) {
      hist5->Fill(rEdeppSciDetIn1[i],1);
   }

   for (int i=0; i<SciDetIn2->GetEntries();i++) {
      hist6->Fill(rEdeppSciDetIn2[i],1);
   }

   TAxis* xAxish1 = hist1->GetXaxis();
   //Debugging
/*   for (int i=0; i<nbins; i++ ) {
      std::cout << "bin #" << i << " out of " << hist1->GetNbinsX() << " with a range: (" << xAxish1->GetBinLowEdge(i) << "," << xAxish1->GetBinUpEdge(i) << "), contains: " << hist1->GetBinContent(i) << std::endl;
   }
*/
   c->cd(1); copyhist->Draw();
   //c->Update();
   //TPaveStats *statsBox = (TPaveStats*)copyhist->GetListOfFunctions()->FindObject("stats");
   //TPaveStats *ps = (TPaveStats*)c->GetPrimitive("stats");
   //TPaveStats *ps = (TPaveStats*)copyhist->GetListOfFunctions()->FindObject("stats");
   //ps->SetName("mystats");
   //TList *listoflines = ps->GetListOfLines();
   //TText *tconst = ps->GetLineWith("Entries");
   //std::cout << tconst << std::endl;
   //std::cout << ps->GetLineWith("Entries") << std::endl;
   //std::cout << "\nh1 X1NDC: " << ps->GetX1NDC() << std::endl;
   //std::cout << "h1 Y1NDC: " << statsBox->GetY1NDC() << std::endl;
   //copyhist->Draw();
//   c->cd(1); hist1->Draw();
   c->cd(2); hist2->Draw();
   c->cd(3); hist3->Draw();
   c->cd(4); hist4->Draw();
   c->cd(5); hist5->Draw();
   c->cd(6); hist6->Draw();
   c->cd();

   TPad *cpad = new TPad("cpad", "c pad",0,0,1,1);
   cpad->SetFillStyle(4000);
   cpad->Draw();
   cpad->cd();
   TPaveLabel *ctitle = new TPaveLabel(0.1,0.0,0.94,0.04,TString(plotName1)); //(0.1,0.94,0.94,1.0)
   ctitle->SetFillColor(17);
   ctitle->SetTextFont(52);
   ctitle->Draw();

   c->SaveAs("plots/sumPlot_"+TString(plotName1)+".pdf");
   c->SaveAs("plots/sumPlot_"+TString(plotName1)+".png");
/*
   //TGraph  
   TCanvas *d = new TCanvas("d","Edep",800,600);
   gr = new TGraph(nbins,bincenters, testcounts);
   gr->Draw("AB");
   d->SaveAs("plots/sumPlot_gr_"+TString(plotName1)+".pdf");
   d->SaveAs("plots/sumPlot_gr_"+TString(plotName1)+".png");
*/ 

   // Checks
   for (int i=0; i<hist1->GetNbinsX(); i++) sumh1 += (hist1->GetBinContent(i))*(hist1->GetBinCenter(i));
   for (int i=0; i<hist2->GetNbinsX(); i++) sumh2 += (hist2->GetBinContent(i))*(hist2->GetBinCenter(i));
   for (int i=0; i<hist3->GetNbinsX(); i++) sumh3 += (hist3->GetBinContent(i))*(hist3->GetBinCenter(i));
   for (int i=0; i<hist4->GetNbinsX(); i++) sumh4 += (hist4->GetBinContent(i))*(hist4->GetBinCenter(i));
   for (int i=0; i<hist5->GetNbinsX(); i++) sumh5 += (hist5->GetBinContent(i))*(hist5->GetBinCenter(i));
   for (int i=0; i<hist6->GetNbinsX(); i++) sumh6 += (hist6->GetBinContent(i))*(hist6->GetBinCenter(i));

   std::cout << " sumh1: " << sumh1 << std::endl;
   std::cout << " sumh2: " << sumh2 << std::endl;
   std::cout << " sumh3: " << sumh3 << std::endl;
   std::cout << " sumh4: " << sumh4 << std::endl;
   std::cout << " sumh5: " << sumh5 << std::endl;
   std::cout << " sumh6: " << sumh6 << std::endl; 





} // Close function

int main() {
   Count_electrons_test_50MeV_Comb11();
   return 0;
}
