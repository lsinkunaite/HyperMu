////////////////////////////////////////////////////////////////////////
//                                                                    //
//                           FileFiller.C                             //
//                                                                    //
//  Writes ntuple data for mu-decay into an ascii file and then re-   //
//  arranges the file so that all the missing events would get an     //
//  Edep value of 0.00 MeV.                                           //
//                                                                    //
//                             Laura P.S.                             //
//                             11-07-2018                             //
//                                                                    //
////////////////////////////////////////////////////////////////////////

// I/O
#include <fstream>
#include <iostream>
#include <stdio>

// ROOT
#include "TFile.h"
#include "TTree.h"
using namespace std;


void FileFillerThesis(){	
	
   // Path name
   std::string path = "../../simdata/beamtime/";
   int pathL = path.length();
   std::string cavmaterial = "Cu";
	
   // X-ray cascade
   std::string filex = path+cavmaterial+"_cav_pink_1e5goldcascade.root";
   
   // Mu-decay
   std::string filemu = path+cavmaterial+"_cav_pink_1e5mudecay.root";
   
   std::vector<std::string> Xfiles;
   std::vector<std::string> mufiles;
		   
   Xfiles.push_back(filex);
   mufiles.push_back(filemu);

   //-------------------------------------------------------------------
   //                          Mu-decay
   //-------------------------------------------------------------------

   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m----------------------- Mu-decay -------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;
	 
   for (int k = 0; k<mufiles.size(); k++) {
      TFile *fmu = new TFile(TString(mufiles[k]));
			  
      TTree *tSciD1 = (TTree*)fmu->Get("Detector/SciDet1"); // D-stream
	  TTree *tSciD2 = (TTree*)fmu->Get("Detector/SciDet2"); // U-stream
	  TTree *tBGOD1 = (TTree*)fmu->Get("Detector/BGODet1"); // D-stream
	  TTree *tBGOD2 = (TTree*)fmu->Get("Detector/BGODet2"); // U-stream
	  	  
	  float EventID,Edep; 

	  tSciD1->SetBranchAddress("EventID",&EventID); // D-stream 
	  tSciD1->SetBranchAddress("Edep",&Edep);
	  tSciD2->SetBranchAddress("EventID",&EventID);
	  tSciD2->SetBranchAddress("Edep",&Edep);
	  tBGOD1->SetBranchAddress("EventID",&EventID);
	  tBGOD1->SetBranchAddress("Edep",&Edep);
	  tBGOD2->SetBranchAddress("EventID",&EventID);
	  tBGOD2->SetBranchAddress("Edep",&Edep);

		  
	  //----------------------------------------------------------------
	  //                          Writing
	  //----------------------------------------------------------------

	  std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
	  std::cout << "\033[1;34m--------------------- Writing Loop " << k+1 << " ---------------------\033[0m" << std::endl;
	  std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
	  
	  // SciD1 
	  ofstream tmpSciD1;
	  tmpSciD1.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciD1.txt"));
	  tmpSciD1 << "EventID        Edep\n";
	  for (int i=0; i<tSciD1->GetEntries(); i++){
	     tSciD1->GetEntry(i);
		 tmpSciD1 << EventID << " " << Edep << "\n";
	  }
	  tmpSciD1.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciD1.txt" << " written!" << std::endl;

			  
	  // SciD2
	  ofstream tmpSciD2;
	  tmpSciD2.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciD2.txt"));
	  tmpSciD2 << "EventID        Edep\n";
	  for (int i=0; i<tSciD2->GetEntries(); i++){
	     tSciD2->GetEntry(i);
		 tmpSciD2 << EventID << " " << Edep << "\n";
	  }
	  tmpSciD2.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciD2.txt" << " written!" << std::endl;


	  // BGOD1 
	  ofstream tmpBGOD1;
	  tmpBGOD1.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpBGOD1.txt"));
	  tmpBGOD1 << "EventID        Edep\n";
	  for (int i=0; i<tBGOD1->GetEntries(); i++){
	     tBGOD1->GetEntry(i);
		 tmpBGOD1 << EventID << " " << Edep << "\n";
	  }
	  tmpBGOD1.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpBGOD1.txt" << " written!" << std::endl;


	  // BGOD2 
	  ofstream tmpBGOD2;
	  tmpBGOD2.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpBGOD2.txt"));
	  tmpBGOD2 << "EventID        Edep\n";
	  for (int i=0; i<tBGOD2->GetEntries(); i++){
	     tBGOD2->GetEntry(i);
		 tmpBGOD2 << EventID << " " << Edep << "\n";
	  }
	  tmpBGOD2.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpBGOD2.txt" << " written!" << std::endl;

						   
	  //----------------------------------------------------------------
	  //                          Rewriting
	  //----------------------------------------------------------------
		 
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m-------------------- Rewriting Loop " << k+1 << " --------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
		 
	  // SciD1     
	  std::ifstream inputSciD1(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciD1.txt"));
	  std::string lineSciD1;
	  std::getline(inputSciD1, lineSciD1);
			 
	  ifstream ifileSD1(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD1.txt"));
	  if (ifileSD1) {
	     remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD1.txt"));
	     std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD1.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciD1;
	  finSciD1.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD1.txt"));
			  
	  int ncounterSD1 = 1;
	  while (!inputSciD1.eof()) {
	     double EvIDSD1, EdepSD1;
		 inputSciD1 >> EvIDSD1 >> EdepSD1;
		 if (EvIDSD1 == ncounterSD1) {
		    finSciD1 << EvIDSD1 << " " << EdepSD1 << "\n";
			ncounterSD1++;
		 } else {
		    int diffSD1 = EvIDSD1 - ncounterSD1;
			for (int i=0; i<diffSD1; i++) {
			   finSciD1 << ncounterSD1+i << " " << 0.0 << "\n"; 
			}
			finSciD1 << EvIDSD1 << " " << EdepSD1 << "\n";
			ncounterSD1 = ncounterSD1 + diffSD1 + 1;
		 }   
	  }
	  finSciD1.close();

	  if ((remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciD1.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD1.txt") << " generated! " << std::endl;
	  }



	  // SciD2     
	  std::ifstream inputSciD2(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciD2.txt"));
	  std::string lineSciD2;
	  std::getline(inputSciD2, lineSciD2);
			 
	  ifstream ifileSD2(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD2.txt"));
	  if (ifileSD2) {
	     remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD2.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD2.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciD2;
	  finSciD2.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD2.txt"));
			  
	  int ncounterSD2 = 1;
	  while (!inputSciD2.eof()) {
	     double EvIDSD2, EdepSD2;
		 inputSciD2 >> EvIDSD2 >> EdepSD2;
		 if (EvIDSD2 == ncounterSD2) {
		    finSciD2 << EvIDSD2 << " " << EdepSD2 << "\n";
			ncounterSD2++;
		 } else {
		    int diffSD2 = EvIDSD2 - ncounterSD2;
			for (int i=0; i<diffSD2; i++) {
			   finSciD2 << ncounterSD2+i << " " << 0.0 << "\n"; 
			}
			finSciD2 << EvIDSD2 << " " << EdepSD2 << "\n";
			ncounterSD2 = ncounterSD2 + diffSD2 + 1;
		 }   
	  }
	  finSciD2.close();

	  if ((remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciD2.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD2.txt") << " generated! " << std::endl;
	  }



      // BGOD1     
	  std::ifstream inputBGOD1(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpBGOD1.txt"));
	  std::string lineBGOD1;
	  std::getline(inputBGOD1, lineBGOD1);
			 
	  ifstream ifileBD1(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_BGOD1.txt"));
	  if (ifileBD1) {
	     remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_BGOD1.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_BGOD1.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finBGOD1;
	  finBGOD1.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_BGOD1.txt"));
			  
	  int ncounterBD1 = 1;
	  while (!inputBGOD1.eof()) {
	     double EvIDBD1, EdepBD1;
		 inputBGOD1 >> EvIDBD1 >> EdepBD1;
		 if (EvIDBD1 == ncounterBD1) {
		    finBGOD1 << EvIDBD1 << " " << EdepBD1 << "\n";
			ncounterBD1++;
		 } else {
		    int diffBD1 = EvIDBD1 - ncounterBD1;
			for (int i=0; i<diffBD1; i++) {
			   finBGOD1 << ncounterBD1+i << " " << 0.0 << "\n"; 
			}
			finBGOD1 << EvIDBD1 << " " << EdepBD1 << "\n";
			ncounterBD1 = ncounterBD1 + diffBD1 + 1;
		 }   
	  }
	  finBGOD1.close();

	  if ((remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpBGOD1.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_BGOD1.txt") << " generated! " << std::endl;
	  }



      // BGOD2     
	  std::ifstream inputBGOD2(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpBGOD2.txt"));
	  std::string lineBGOD2;
	  std::getline(inputBGOD2, lineBGOD2);
			 
	  ifstream ifileBD2(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_BGOD2.txt"));
	  if (ifileBD2) {
	     remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_BGOD2.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_BGOD2.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finBGOD2;
	  finBGOD2.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_BGOD2.txt"));
			  
	  int ncounterBD2 = 1;
	  while (!inputBGOD2.eof()) {
	     double EvIDBD2, EdepBD2;
		 inputBGOD2 >> EvIDBD2 >> EdepBD2;
		 if (EvIDBD2 == ncounterBD2) {
		    finBGOD2 << EvIDBD2 << " " << EdepBD2 << "\n";
			ncounterBD2++;
		 } else {
		    int diffBD2 = EvIDBD2 - ncounterBD2;
			for (int i=0; i<diffBD2; i++) {
			   finBGOD2 << ncounterBD2+i << " " << 0.0 << "\n"; 
			}
			finBGOD2 << EvIDBD2 << " " << EdepBD2 << "\n";
			ncounterBD2 = ncounterBD2 + diffBD2 + 1;
		 }   
	  }
	  finBGOD2.close();

	  if ((remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpBGOD2.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_BGOD2.txt") << " generated! " << std::endl;
	  }		 

		 
   }



   //-------------------------------------------------------------------
   //                         X-ray cascade
   //-------------------------------------------------------------------

   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m--------------------- X-ray cascade ----------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;
	 
   for (int k = 0; k<Xfiles.size(); k++) {
      TFile *fx = new TFile(TString(Xfiles[k]));
			  
	  TTree *txSciD1 = (TTree*)fx->Get("Detector/SciDet1"); // D-stream
	  TTree *txSciD2 = (TTree*)fx->Get("Detector/SciDet2"); // U-stream
	  TTree *txBGOD1 = (TTree*)fx->Get("Detector/BGODet1"); // D-stream
	  TTree *txBGOD2 = (TTree*)fx->Get("Detector/BGODet2"); // U-stream
			  
	  float EventID,Edep; 

	  txSciD1->SetBranchAddress("EventID",&EventID); // D-stream 
	  txSciD1->SetBranchAddress("Edep",&Edep);
	  txSciD2->SetBranchAddress("EventID",&EventID); // U-stream
	  txSciD2->SetBranchAddress("Edep",&Edep);
	  txBGOD1->SetBranchAddress("EventID",&EventID); // D-stream
	  txBGOD1->SetBranchAddress("Edep",&Edep);
	  txBGOD2->SetBranchAddress("EventID",&EventID); // U-stream
	  txBGOD2->SetBranchAddress("Edep",&Edep);
		  
		  
	  //----------------------------------------------------------------
	  //                          Writing
	  //----------------------------------------------------------------

	  std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
	  std::cout << "\033[1;34m--------------------- Writing Loop " << k+1 << " ---------------------\033[0m" << std::endl;
	  std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
	  
	  // SciD1 
	  ofstream tmpxSciD1;
	  tmpxSciD1.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciD1.txt"));
	  tmpxSciD1 << "EventID        Edep\n";
	  for (int i=0; i<txSciD1->GetEntries(); i++){
	     txSciD1->GetEntry(i);
		 tmpxSciD1 << EventID << " " << Edep << "\n";
	  }
	  tmpxSciD1.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciD1.txt" << " written!" << std::endl;


	  // SciD2 
	  ofstream tmpxSciD2;
	  tmpxSciD2.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciD2.txt"));
	  tmpxSciD2 << "EventID        Edep\n";
	  for (int i=0; i<txSciD2->GetEntries(); i++){
	     txSciD2->GetEntry(i);
		 tmpxSciD2 << EventID << " " << Edep << "\n";
	  }
	  tmpxSciD2.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciD2.txt" << " written!" << std::endl;

			  
	  // BGOD1 
	  ofstream tmpxBGOD1;
	  tmpxBGOD1.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxBGOD1.txt"));
	  tmpxBGOD1 << "EventID        Edep\n";
	  for (int i=0; i<txBGOD1->GetEntries(); i++){
	     txBGOD1->GetEntry(i);
		 tmpxBGOD1 << EventID << " " << Edep << "\n";
	  }
	  tmpxBGOD1.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxBGOD1.txt" << " written!" << std::endl;
		  

	  // BGOD2 
	  ofstream tmpxBGOD2;
	  tmpxBGOD2.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxBGOD2.txt"));
	  tmpxBGOD2 << "EventID        Edep\n";
	  for (int i=0; i<txBGOD2->GetEntries(); i++){
	     txBGOD2->GetEntry(i);
		 tmpxBGOD2 << EventID << " " << Edep << "\n";
	  }
	  tmpxBGOD2.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxBGOD2.txt" << " written!" << std::endl;
		  
		   
	  //----------------------------------------------------------------
	  //                          Rewriting
	  //----------------------------------------------------------------
		 
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m-------------------- Rewriting Loop " << k+1 << " --------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

 
	  // SciD1     
	  std::ifstream inputSciD1x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciD1.txt"));
	  std::string lineSciD1x;
	  std::getline(inputSciD1x, lineSciD1x);
			 
	  ifstream ifileSD1x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD1.txt"));
	  if (ifileSD1x) {
	     remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD1.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD1.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciD1x;
	  finSciD1x.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD1.txt"));
			  
	  int ncounterSD1x = 1;
	  while (!inputSciD1x.eof()) {
	     double EvIDSD1x, EdepSD1x;
		 inputSciD1x >> EvIDSD1x >> EdepSD1x;
		 if (EvIDSD1x == ncounterSD1x) {
		    finSciD1x << EvIDSD1x << " " << EdepSD1x << "\n";
			ncounterSD1x++;
		 } else {
		    int diffSD1x = EvIDSD1x - ncounterSD1x;
			for (int i=0; i<diffSD1x; i++) {
			   finSciD1x << ncounterSD1x+i << " " << 0.0 << "\n"; 
			}
		    finSciD1x << EvIDSD1x << " " << EdepSD1x << "\n";
		    ncounterSD1x = ncounterSD1x + diffSD1x + 1;
	     }   
	  }
	  finSciD1x.close();

	  if ((remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciD1.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD1.txt") << " generated! " << std::endl;
	  }



	  // SciD2     
	  std::ifstream inputSciD2x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciD2.txt"));
	  std::string lineSciD2x;
	  std::getline(inputSciD2x, lineSciD2x);
			 
	  ifstream ifileSD2x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD2.txt"));
	  if (ifileSD2x) {
	     remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD2.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD2.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciD2x;
	  finSciD2x.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD2.txt"));
			  
	  int ncounterSD2x = 1;
	  while (!inputSciD2x.eof()) {
	     double EvIDSD2x, EdepSD2x;
		 inputSciD2x >> EvIDSD2x >> EdepSD2x;
		 if (EvIDSD2x == ncounterSD2x) {
		    finSciD2x << EvIDSD2x << " " << EdepSD2x << "\n";
			ncounterSD2x++;
		 } else {
		    int diffSD2x = EvIDSD2x - ncounterSD2x;
			for (int i=0; i<diffSD2x; i++) {
			   finSciD2x << ncounterSD2x+i << " " << 0.0 << "\n"; 
			}
		    finSciD2x << EvIDSD2x << " " << EdepSD2x << "\n";
		    ncounterSD2x = ncounterSD2x + diffSD2x + 1;
		 }   
	  }
	  finSciD2x.close();

	  if ((remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciD2.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD2.txt") << " generated! " << std::endl;
	  }



	  // BGOD1     
	  std::ifstream inputBGOD1x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxBGOD1.txt"));
	  std::string lineBGOD1x;
	  std::getline(inputBGOD1x, lineBGOD1x);
			 
	  ifstream ifileBD1x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_BGOD1.txt"));
	  if (ifileBD1x) {
	     remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_BGOD1.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_BGOD1.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finBGOD1x;
	  finBGOD1x.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_BGOD1.txt"));
			  
	  int ncounterBD1x = 1;
	  while (!inputBGOD1x.eof()) {
	     double EvIDBD1x, EdepBD1x;
		 inputBGOD1x >> EvIDBD1x >> EdepBD1x;
		 if (EvIDBD1x == ncounterBD1x) {
		    finBGOD1x << EvIDBD1x << " " << EdepBD1x << "\n";
			ncounterBD1x++;
		 } else {
		    int diffBD1x = EvIDBD1x - ncounterBD1x;
			for (int i=0; i<diffBD1x; i++) {
			   finBGOD1x << ncounterBD1x+i << " " << 0.0 << "\n"; 
			}
			finBGOD1x << EvIDBD1x << " " << EdepBD1x << "\n";
			ncounterBD1x = ncounterBD1x + diffBD1x + 1;
		 }   
	  }
	  finBGOD1x.close();

	  if ((remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxBGOD1.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_BGOD1.txt") << " generated! " << std::endl;
	  }



	  // BGOD2     
	  std::ifstream inputBGOD2x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxBGOD2.txt"));
	  std::string lineBGOD2x;
	  std::getline(inputBGOD2x, lineBGOD2x);
			 
	  ifstream ifileBD2x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_BGOD2.txt"));
	  if (ifileBD2x) {
	     remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_BGOD2.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_BGOD2.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finBGOD2x;
	  finBGOD2x.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_BGOD2.txt"));
			  
	  int ncounterBD2x = 1;
	  while (!inputBGOD2x.eof()) {
	     double EvIDBD2x, EdepBD2x;
		 inputBGOD2x >> EvIDBD2x >> EdepBD2x;
		 if (EvIDBD2x == ncounterBD2x) {
		    finBGOD2x << EvIDBD2x << " " << EdepBD2x << "\n";
			ncounterBD2x++;
		 } else {
		    int diffBD2x = EvIDBD2x - ncounterBD2x;
			for (int i=0; i<diffBD2x; i++) {
			   finBGOD2x << ncounterBD2x+i << " " << 0.0 << "\n"; 
			}
			finBGOD2x << EvIDBD2x << " " << EdepBD2x << "\n";
			ncounterBD2x = ncounterBD2x + diffBD2x + 1;
		 }   
	  }
	  finBGOD2x.close();

	  if ((remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxBGOD2.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_BGOD2.txt") << " generated! " << std::endl;
	  }

		 
   }


}


int main() {
   FileFillerThesis();
   return 0;
}  
