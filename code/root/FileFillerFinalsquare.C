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


void FileFillerFinalsquare(){	
	
   // Path name
   std::string path = "../../simdata/final/";
   int pathL = path.length();
	
   // X-ray cascade
   std::string filexNaI = path+"square_both_sides_NaI_1e5goldcascade.root";
   std::string filexSci = path+"square_both_sides_Sci_1e5goldcascade.root";

   // Mu-decay
   std::string filemuNaI = path+"square_both_sides_NaI_1e5mudecay.root";
   std::string filemuSci = path+"square_both_sides_Sci_1e5mudecay.root";
   
   std::vector<std::string> Xfiles;
   std::vector<std::string> mufiles;
		   
   Xfiles.push_back(filexNaI);
   Xfiles.push_back(filexSci);
   mufiles.push_back(filemuNaI);
   mufiles.push_back(filemuSci);

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
	  TTree *tSciD3 = (TTree*)fmu->Get("Detector/SciDet3"); // U-stream
	  TTree *tSciDT1 = (TTree*)fmu->Get("Detector/SciDetT1"); // D-stream
	  TTree *tSciDB1 = (TTree*)fmu->Get("Detector/SciDetB1"); // D-stream
	  TTree *tSciDL1 = (TTree*)fmu->Get("Detector/SciDetL1"); // D-stream
	  TTree *tSciDR1 = (TTree*)fmu->Get("Detector/SciDetR1"); // D-stream
	  TTree *tSciDT2 = (TTree*)fmu->Get("Detector/SciDetT2"); // U-stream
	  TTree *tSciDB2 = (TTree*)fmu->Get("Detector/SciDetB2"); // U-stream
	  TTree *tSciDL2 = (TTree*)fmu->Get("Detector/SciDetL2"); // U-stream
	  TTree *tSciDR2 = (TTree*)fmu->Get("Detector/SciDetR2"); // U-stream
	  if (k == 0) { TTree *tBGOD1 = (TTree*)fmu->Get("Detector/BGONaIDet1"); TTree *tBGOD2 = (TTree*)fmu->Get("Detector/BGONaIDet2"); }
	  if (k == 1) { TTree *tBGOD1 = (TTree*)fmu->Get("Detector/BGOSciDet1"); TTree *tBGOD2 = (TTree*)fmu->Get("Detector/BGOSciDet2"); }	
			  
	  float EventID,Edep; 

	  tSciD1->SetBranchAddress("EventID",&EventID); // D-stream 
	  tSciD1->SetBranchAddress("Edep",&Edep);
	  tSciD2->SetBranchAddress("EventID",&EventID);
	  tSciD2->SetBranchAddress("Edep",&Edep);
	  tSciD3->SetBranchAddress("EventID",&EventID);
	  tSciD3->SetBranchAddress("Edep",&Edep);
	  tSciDT1->SetBranchAddress("EventID",&EventID);
	  tSciDT1->SetBranchAddress("Edep",&Edep);
	  tSciDB1->SetBranchAddress("EventID",&EventID);
	  tSciDB1->SetBranchAddress("Edep",&Edep);
	  tSciDL1->SetBranchAddress("EventID",&EventID);
	  tSciDL1->SetBranchAddress("Edep",&Edep);
	  tSciDR1->SetBranchAddress("EventID",&EventID);
	  tSciDR1->SetBranchAddress("Edep",&Edep);
	  tSciDT2->SetBranchAddress("EventID",&EventID);
	  tSciDT2->SetBranchAddress("Edep",&Edep);
	  tSciDB2->SetBranchAddress("EventID",&EventID);
	  tSciDB2->SetBranchAddress("Edep",&Edep);
	  tSciDL2->SetBranchAddress("EventID",&EventID);
	  tSciDL2->SetBranchAddress("Edep",&Edep);
	  tSciDR2->SetBranchAddress("EventID",&EventID);
	  tSciDR2->SetBranchAddress("Edep",&Edep);
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


      // SciD3
	  ofstream tmpSciD3;
	  ofstream tmpSciD3;
	  tmpSciD3.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciD3.txt"));
	  tmpSciD3 << "EventID        Edep\n";
	  for (int i=0; i<tSciD3->GetEntries(); i++){
	     tSciD3->GetEntry(i);
		 tmpSciD3 << EventID << " " << Edep << "\n";
	  }
	  tmpSciD3.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciD3.txt" << " written!" << std::endl;


	  // SciDT1
	  ofstream tmpSciDT1;
	  tmpSciDT1.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDT1.txt"));
	  tmpSciDT1 << "EventID        Edep\n";
	  for (int i=0; i<tSciDT1->GetEntries(); i++){
	     tSciDT1->GetEntry(i);
		 tmpSciDT1 << EventID << " " << Edep << "\n";
	  }
	  tmpSciDT1.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDT1.txt" << " written!" << std::endl;

			  
	  // SciDB1
	  ofstream tmpSciDB1;
	  tmpSciDB1.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDB1.txt"));
	  tmpSciDB1 << "EventID        Edep\n";
	  for (int i=0; i<tSciDB1->GetEntries(); i++){
	     tSciDB1->GetEntry(i);
		 tmpSciDB1 << EventID << " " << Edep << "\n";
	  }
	  tmpSciDB1.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDB1.txt" << " written!" << std::endl;
			  
			  
	  // SciDL1
	  ofstream tmpSciDL1;
	  tmpSciDL1.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDL1.txt"));
	  tmpSciDL1 << "EventID        Edep\n";
	  for (int i=0; i<tSciDL1->GetEntries(); i++){
	     tSciDL1->GetEntry(i);
		 tmpSciDL1 << EventID << " " << Edep << "\n";
	  }
	  tmpSciDL1.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDL1.txt" << " written!" << std::endl;

		   
	  // SciDR1
	  ofstream tmpSciDR1;
	  tmpSciDR1.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDR1.txt"));
	  tmpSciDR1 << "EventID        Edep\n";
	  for (int i=0; i<tSciDR1->GetEntries(); i++){
	     tSciDR1->GetEntry(i);
		 tmpSciDR1 << EventID << " " << Edep << "\n";
	  }
	  tmpSciDR1.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDR1.txt" << " written!" << std::endl;


	  // SciDT2
	  ofstream tmpSciDT2;
	  tmpSciDT2.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDT2.txt"));
	  tmpSciDT2 << "EventID        Edep\n";
	  for (int i=0; i<tSciDT2->GetEntries(); i++){
	     tSciDT2->GetEntry(i);
		 tmpSciDT2 << EventID << " " << Edep << "\n";
	  }
	  tmpSciDT2.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDT2.txt" << " written!" << std::endl;

			  
	  // SciDB2
	  ofstream tmpSciDB2;
	  tmpSciDB2.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDB2.txt"));
	  tmpSciDB2 << "EventID        Edep\n";
	  for (int i=0; i<tSciDB2->GetEntries(); i++){
	     tSciDB2->GetEntry(i);
		 tmpSciDB2 << EventID << " " << Edep << "\n";
	  }
	  tmpSciDB2.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDB2.txt" << " written!" << std::endl;
			  
			  
	  // SciDL2
	  ofstream tmpSciDL2;
	  tmpSciDL2.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDL2.txt"));
	  tmpSciDL2 << "EventID        Edep\n";
	  for (int i=0; i<tSciDL2->GetEntries(); i++){
	     tSciDL2->GetEntry(i);
		 tmpSciDL2 << EventID << " " << Edep << "\n";
	  }
	  tmpSciDL2.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDL2.txt" << " written!" << std::endl;

		   
	  // SciDR2
	  ofstream tmpSciDR2;
	  tmpSciDR2.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDR2.txt"));
	  tmpSciDR2 << "EventID        Edep\n";
	  for (int i=0; i<tSciDR2->GetEntries(); i++){
	     tSciDR2->GetEntry(i);
		 tmpSciDR2 << EventID << " " << Edep << "\n";
	  }
	  tmpSciDR2.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDR2.txt" << " written!" << std::endl;


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



	  // SciD3     
	  std::ifstream inputSciD3(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciD3.txt"));
	  std::string lineSciD3;
	  std::getline(inputSciD3, lineSciD3);
			 
	  ifstream ifileSD3(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD3.txt"));
	  if (ifileSD3) {
	     remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD3.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD3.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciD3;
	  finSciD3.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD3.txt"));
			  
	  int ncounterSD3 = 1;
	  while (!inputSciD3.eof()) {
	     double EvIDSD3, EdepSD3;
		 inputSciD3 >> EvIDSD3 >> EdepSD3;
		 if (EvIDSD3 == ncounterSD3) {
		    finSciD3 << EvIDSD3 << " " << EdepSD3 << "\n";
			ncounterSD3++;
		 } else {
		    int diffSD3 = EvIDSD3 - ncounterSD3;
			for (int i=0; i<diffSD3; i++) {
			   finSciD3 << ncounterSD3+i << " " << 0.0 << "\n"; 
			}
			finSciD3 << EvIDSD3 << " " << EdepSD3 << "\n";
			ncounterSD3 = ncounterSD3 + diffSD3 + 1;
		 }   
	  }
	  finSciD3.close();

	  if ((remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciD3.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciD3.txt") << " generated! " << std::endl;
	  }



	  // SciDT1     
	  std::ifstream inputSciDT1(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDT1.txt"));
	  std::string lineSciDT1;
	  std::getline(inputSciDT1, lineSciDT1);
			 
	  ifstream ifileSDT1(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDT1.txt"));
	  if (ifileSDT1) {
	     remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDT1.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDT1.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDT1;
	  finSciDT1.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDT1.txt"));
			  
	  int ncounterSDT1 = 1;
	  while (!inputSciDT1.eof()) {
	     double EvIDSDT1, EdepSDT1;
		 inputSciDT1 >> EvIDSDT1 >> EdepSDT1;
		 if (EvIDSDT1 == ncounterSDT1) {
		    finSciDT1 << EvIDSDT1 << " " << EdepSDT1 << "\n";
			ncounterSDT1++;
		 } else {
		    int diffSDT1 = EvIDSDT1 - ncounterSDT1;
			for (int i=0; i<diffSDT1; i++) {
			   finSciDT1 << ncounterSDT1+i << " " << 0.0 << "\n"; 
			}
			finSciDT1 << EvIDSDT1 << " " << EdepSDT1 << "\n";
			ncounterSDT1 = ncounterSDT1 + diffSDT1 + 1;
		 }   
	  }
	  finSciDT1.close();

	  if ((remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDT1.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDT1.txt") << " generated! " << std::endl;
	  }



	  // SciDB1     
	  std::ifstream inputSciDB1(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDB1.txt"));
	  std::string lineSciDB1;
	  std::getline(inputSciDB1, lineSciDB1);
			 
	  ifstream ifileSDB1(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDB1.txt"));
	  if (ifileSDB1) {
	     remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDB1.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDB1.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDB1;
	  finSciDB1.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDB1.txt"));
			  
	  int ncounterSDB1 = 1;
	  while (!inputSciDB1.eof()) {
	     double EvIDSDB1, EdepSDB1;
		 inputSciDB1 >> EvIDSDB1 >> EdepSDB1;
		 if (EvIDSDB1 == ncounterSDB1) {
		    finSciDB1 << EvIDSDB1 << " " << EdepSDB1 << "\n";
			ncounterSDB1++;
		 } else {
		    int diffSDB1 = EvIDSDB1 - ncounterSDB1;
			for (int i=0; i<diffSDB1; i++) {
			   finSciDB1 << ncounterSDB1+i << " " << 0.0 << "\n"; 
			}
			finSciDB1 << EvIDSDB1 << " " << EdepSDB1 << "\n";
			ncounterSDB1 = ncounterSDB1 + diffSDB1 + 1;
		 }   
	  }
	  finSciDB1.close();

	  if ((remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDB1.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDB1.txt") << " generated! " << std::endl;
	  }



	  // SciDL1     
	  std::ifstream inputSciDL1(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDL1.txt"));
	  std::string lineSciDL1;
	  std::getline(inputSciDL1, lineSciDL1);
			 
	  ifstream ifileSDL1(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDL1.txt"));
	  if (ifileSDL1) {
	     remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDL1.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDL1.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDL1;
	  finSciDL1.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDL1.txt"));
			  
	  int ncounterSDL1 = 1;
	  while (!inputSciDL1.eof()) {
	     double EvIDSDL1, EdepSDL1;
		 inputSciDL1 >> EvIDSDL1 >> EdepSDL1;
		 if (EvIDSDL1 == ncounterSDL1) {
		    finSciDL1 << EvIDSDL1 << " " << EdepSDL1 << "\n";
			ncounterSDL1++;
		 } else {
		    int diffSDL1 = EvIDSDL1 - ncounterSDL1;
			for (int i=0; i<diffSDL1; i++) {
			   finSciDL1 << ncounterSDL1+i << " " << 0.0 << "\n"; 
			}
			finSciDL1 << EvIDSDL1 << " " << EdepSDL1 << "\n";
			ncounterSDL1 = ncounterSDL1 + diffSDL1 + 1;
		 }   
	  }
	  finSciDL1.close();

	  if ((remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDL1.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDL1.txt") << " generated! " << std::endl;
	  }



	  // SciDR1     
	  std::ifstream inputSciDR1(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDR1.txt"));
	  std::string lineSciDR1;
	  std::getline(inputSciDR1, lineSciDR1);
			 
	  ifstream ifileSDR1(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDR1.txt"));
	  if (ifileSDR1) {
	     remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDR1.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDR1.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDR1;
	  finSciDR1.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDR1.txt"));
			  
	  int ncounterSDR1 = 1;
	  while (!inputSciDR1.eof()) {
	     double EvIDSDR1, EdepSDR1;
		 inputSciDR1 >> EvIDSDR1 >> EdepSDR1;
		 if (EvIDSDR1 == ncounterSDR1) {
		    finSciDR1 << EvIDSDR1 << " " << EdepSDR1 << "\n";
			ncounterSDR1++;
	     } else {
	        int diffSDR1 = EvIDSDR1 - ncounterSDR1;
		    for (int i=0; i<diffSDR1; i++) {
		       finSciDR1 << ncounterSDR1+i << " " << 0.0 << "\n"; 
		    }
		    finSciDR1 << EvIDSDR1 << " " << EdepSDR1 << "\n";
		    ncounterSDR1 = ncounterSDR1 + diffSDR1 + 1;
	     }   
      }
	  finSciDR1.close();

	  if ((remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDR1.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDR1.txt") << " generated! " << std::endl;
	  }



	  // SciDT2     
	  std::ifstream inputSciDT2(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDT2.txt"));
	  std::string lineSciDT2;
	  std::getline(inputSciDT2, lineSciDT2);
			 
	  ifstream ifileSDT2(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDT2.txt"));
	  if (ifileSDT2) {
	     remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDT2.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDT2.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDT2;
	  finSciDT2.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDT2.txt"));
			  
	  int ncounterSDT2 = 1;
	  while (!inputSciDT2.eof()) {
	     double EvIDSDT2, EdepSDT2;
		 inputSciDT2 >> EvIDSDT2 >> EdepSDT2;
		 if (EvIDSDT2 == ncounterSDT2) {
		    finSciDT2 << EvIDSDT2 << " " << EdepSDT2 << "\n";
			ncounterSDT2++;
		 } else {
		    int diffSDT2 = EvIDSDT2 - ncounterSDT2;
			for (int i=0; i<diffSDT2; i++) {
			   finSciDT2 << ncounterSDT2+i << " " << 0.0 << "\n"; 
			}
			finSciDT2 << EvIDSDT2 << " " << EdepSDT2 << "\n";
			ncounterSDT2 = ncounterSDT2 + diffSDT2 + 1;
		 }   
	  }
	  finSciDT2.close();

	  if ((remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDT2.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDT2.txt") << " generated! " << std::endl;
	  }



	  // SciDB2     
	  std::ifstream inputSciDB2(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDB2.txt"));
	  std::string lineSciDB2;
	  std::getline(inputSciDB2, lineSciDB2);
			 
	  ifstream ifileSDB2(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDB2.txt"));
	  if (ifileSDB2) {
	     remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDB2.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDB2.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDB2;
	  finSciDB2.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDB2.txt"));
			  
	  int ncounterSDB2 = 1;
	  while (!inputSciDB2.eof()) {
	     double EvIDSDB2, EdepSDB2;
		 inputSciDB2 >> EvIDSDB2 >> EdepSDB2;
		 if (EvIDSDB2 == ncounterSDB2) {
		    finSciDB2 << EvIDSDB2 << " " << EdepSDB2 << "\n";
			ncounterSDB2++;
		 } else {
		    int diffSDB2 = EvIDSDB2 - ncounterSDB2;
			for (int i=0; i<diffSDB2; i++) {
			   finSciDB2 << ncounterSDB2+i << " " << 0.0 << "\n"; 
			}
			finSciDB2 << EvIDSDB2 << " " << EdepSDB2 << "\n";
			ncounterSDB2 = ncounterSDB2 + diffSDB2 + 1;
		 }   
	  }
	  finSciDB2.close();

	  if ((remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDB2.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDB2.txt") << " generated! " << std::endl;
	  }



	  // SciDL2     
	  std::ifstream inputSciDL2(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDL2.txt"));
	  std::string lineSciDL2;
	  std::getline(inputSciDL2, lineSciDL2);
			 
	  ifstream ifileSDL2(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDL2.txt"));
	  if (ifileSDL2) {
	     remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDL2.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDL2.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDL2;
	  finSciDL2.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDL2.txt"));
			  
	  int ncounterSDL2 = 1;
	  while (!inputSciDL2.eof()) {
	     double EvIDSDL2, EdepSDL2;
		 inputSciDL2 >> EvIDSDL2 >> EdepSDL2;
		 if (EvIDSDL2 == ncounterSDL2) {
		    finSciDL2 << EvIDSDL2 << " " << EdepSDL2 << "\n";
			ncounterSDL2++;
		 } else {
		    int diffSDL2 = EvIDSDL2 - ncounterSDL2;
			for (int i=0; i<diffSDL2; i++) {
			   finSciDL2 << ncounterSDL2+i << " " << 0.0 << "\n"; 
			}
			finSciDL2 << EvIDSDL2 << " " << EdepSDL2 << "\n";
			ncounterSDL2 = ncounterSDL2 + diffSDL2 + 1;
		 }   
	  }
	  finSciDL2.close();

	  if ((remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDL2.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDL2.txt") << " generated! " << std::endl;
	  }



	  // SciDR2     
	  std::ifstream inputSciDR2(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDR2.txt"));
	  std::string lineSciDR2;
	  std::getline(inputSciDR2, lineSciDR2);
			 
	  ifstream ifileSDR2(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDR2.txt"));
	  if (ifileSDR2) {
	     remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDR2.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDR2.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDR2;
	  finSciDR2.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDR2.txt"));
			  
	  int ncounterSDR2 = 1;
	  while (!inputSciDR2.eof()) {
	     double EvIDSDR2, EdepSDR2;
		 inputSciDR2 >> EvIDSDR2 >> EdepSDR2;
		 if (EvIDSDR2 == ncounterSDR2) {
		    finSciDR2 << EvIDSDR2 << " " << EdepSDR2 << "\n";
			ncounterSDR2++;
	     } else {
	        int diffSDR2 = EvIDSDR2 - ncounterSDR2;
		    for (int i=0; i<diffSDR2; i++) {
		       finSciDR2 << ncounterSDR2+i << " " << 0.0 << "\n"; 
		    }
		    finSciDR2 << EvIDSDR2 << " " << EdepSDR2 << "\n";
		    ncounterSDR2 = ncounterSDR2 + diffSDR2 + 1;
	     }   
      }
	  finSciDR2.close();

	  if ((remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpSciDR2.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_SciDR2.txt") << " generated! " << std::endl;
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
	  TTree *txSciD3 = (TTree*)fx->Get("Detector/SciDet3"); // U-stream
	  TTree *txSciDT1 = (TTree*)fx->Get("Detector/SciDetT1"); // D-stream
	  TTree *txSciDB1 = (TTree*)fx->Get("Detector/SciDetB1"); // D-stream
	  TTree *txSciDL1 = (TTree*)fx->Get("Detector/SciDetL1"); // D-stream
	  TTree *txSciDR1 = (TTree*)fx->Get("Detector/SciDetR1"); // D-stream
	  TTree *txSciDT2 = (TTree*)fx->Get("Detector/SciDetT2"); // U-stream
	  TTree *txSciDB2 = (TTree*)fx->Get("Detector/SciDetB2"); // U-stream
	  TTree *txSciDL2 = (TTree*)fx->Get("Detector/SciDetL2"); // U-stream
	  TTree *txSciDR2 = (TTree*)fx->Get("Detector/SciDetR2"); // U-stream
	  if (k == 0) { TTree *txBGOD1 = (TTree*)fx->Get("Detector/BGONaIDet1"); TTree *txBGOD2 = (TTree*)fx->Get("Detector/BGONaIDet2"); }
	  if (k == 1) { TTree *txBGOD1 = (TTree*)fx->Get("Detector/BGOSciDet1"); TTree *txBGOD2 = (TTree*)fx->Get("Detector/BGOSciDet2"); }	
			  
	  float EventID,Edep; 

	  txSciD1->SetBranchAddress("EventID",&EventID); // D-stream 
	  txSciD1->SetBranchAddress("Edep",&Edep);
	  txSciD2->SetBranchAddress("EventID",&EventID); // U-stream
	  txSciD2->SetBranchAddress("Edep",&Edep);
	  txSciD3->SetBranchAddress("EventID",&EventID); // U-stream
	  txSciD3->SetBranchAddress("Edep",&Edep);
	  txSciDT1->SetBranchAddress("EventID",&EventID); // D-stream
	  txSciDT1->SetBranchAddress("Edep",&Edep);
	  txSciDB1->SetBranchAddress("EventID",&EventID); // D-stream
	  txSciDB1->SetBranchAddress("Edep",&Edep);
	  txSciDL1->SetBranchAddress("EventID",&EventID); // D-stream
	  txSciDL1->SetBranchAddress("Edep",&Edep);
	  txSciDR1->SetBranchAddress("EventID",&EventID); // D-stream
	  txSciDR1->SetBranchAddress("Edep",&Edep);
	  txSciDT2->SetBranchAddress("EventID",&EventID); // U-stream
	  txSciDT2->SetBranchAddress("Edep",&Edep);
	  txSciDB2->SetBranchAddress("EventID",&EventID); // U-stream
	  txSciDB2->SetBranchAddress("Edep",&Edep);
	  txSciDL2->SetBranchAddress("EventID",&EventID); // U-stream
	  txSciDL2->SetBranchAddress("Edep",&Edep);
	  txSciDR2->SetBranchAddress("EventID",&EventID); // U-stream
	  txSciDR2->SetBranchAddress("Edep",&Edep);
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


	  // SciD3 
	  ofstream tmpxSciD3;
	  tmpxSciD3.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciD3.txt"));
	  tmpxSciD3 << "EventID        Edep\n";
	  for (int i=0; i<txSciD3->GetEntries(); i++){
	     txSciD3->GetEntry(i);
		 tmpxSciD3 << EventID << " " << Edep << "\n";
	  }
	  tmpxSciD3.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciD3.txt" << " written!" << std::endl;

			  
	  // SciDT1 
	  ofstream tmpxSciDT1;
	  tmpxSciDT1.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDT1.txt"));
	  tmpxSciDT1 << "EventID        Edep\n";
	  for (int i=0; i<txSciDT1->GetEntries(); i++){
	     txSciDT1->GetEntry(i);
		 tmpxSciDT1 << EventID << " " << Edep << "\n";
	  }
	  tmpxSciDT1.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDT1.txt" << " written!" << std::endl;


	  // SciDB1 
	  ofstream tmpxSciDB1;
	  tmpxSciDB1.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDB1.txt"));
	  tmpxSciDB1 << "EventID        Edep\n";
	  for (int i=0; i<txSciDB1->GetEntries(); i++){
	     txSciDB1->GetEntry(i);
		 tmpxSciDB1 << EventID << " " << Edep << "\n";
	  }
	  tmpxSciDB1.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDB1.txt" << " written!" << std::endl;


	  // SciDL1 
	  ofstream tmpxSciDL1;
	  tmpxSciDL1.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDL1.txt"));
	  tmpxSciDL1 << "EventID        Edep\n";
	  for (int i=0; i<txSciDL1->GetEntries(); i++){
	     txSciDL1->GetEntry(i);
	     tmpxSciDL1 << EventID << " " << Edep << "\n";
	  }
	  tmpxSciDL1.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDL1.txt" << " written!" << std::endl;


	  // SciDR1 
	  ofstream tmpxSciDR1;
	  tmpxSciDR1.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDR1.txt"));
	  tmpxSciDR1 << "EventID        Edep\n";
	  for (int i=0; i<txSciDR1->GetEntries(); i++){
	     txSciDR1->GetEntry(i);
		 tmpxSciDR1 << EventID << " " << Edep << "\n";
	  }
	  tmpxSciDR1.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDR1.txt" << " written!" << std::endl;


	  // SciDT2 
	  ofstream tmpxSciDT2;
	  tmpxSciDT2.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDT2.txt"));
	  tmpxSciDT2 << "EventID        Edep\n";
	  for (int i=0; i<txSciDT2->GetEntries(); i++){
	     txSciDT2->GetEntry(i);
		 tmpxSciDT2 << EventID << " " << Edep << "\n";
	  }
	  tmpxSciDT2.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDT2.txt" << " written!" << std::endl;


	  // SciDB2 
	  ofstream tmpxSciDB2;
	  tmpxSciDB2.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDB2.txt"));
	  tmpxSciDB2 << "EventID        Edep\n";
	  for (int i=0; i<txSciDB2->GetEntries(); i++){
	     txSciDB2->GetEntry(i);
		 tmpxSciDB2 << EventID << " " << Edep << "\n";
	  }
	  tmpxSciDB2.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDB2.txt" << " written!" << std::endl;


	  // SciDL2 
	  ofstream tmpxSciDL2;
	  tmpxSciDL2.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDL2.txt"));
	  tmpxSciDL2 << "EventID        Edep\n";
	  for (int i=0; i<txSciDL2->GetEntries(); i++){
	     txSciDL2->GetEntry(i);
	     tmpxSciDL2 << EventID << " " << Edep << "\n";
	  }
	  tmpxSciDL2.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDL2.txt" << " written!" << std::endl;


	  // SciDR2 
	  ofstream tmpxSciDR2;
	  tmpxSciDR2.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDR2.txt"));
	  tmpxSciDR2 << "EventID        Edep\n";
	  for (int i=0; i<txSciDR2->GetEntries(); i++){
	     txSciDR2->GetEntry(i);
		 tmpxSciDR2 << EventID << " " << Edep << "\n";
	  }
	  tmpxSciDR2.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDR2.txt" << " written!" << std::endl;


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



	  // SciD3     
	  std::ifstream inputSciD3x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciD3.txt"));
	  std::string lineSciD3x;
	  std::getline(inputSciD3x, lineSciD3x);
			 
	  ifstream ifileSD3x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD3.txt"));
	  if (ifileSD3x) {
	     remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD3.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD3.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciD3x;
	  finSciD3x.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD3.txt"));
			  
	  int ncounterSD3x = 1;
	  while (!inputSciD3x.eof()) {
	     double EvIDSD3x, EdepSD3x;
		 inputSciD3x >> EvIDSD3x >> EdepSD3x;
		 if (EvIDSD3x == ncounterSD3x) {
		    finSciD3x << EvIDSD3x << " " << EdepSD3x << "\n";
			ncounterSD3x++;
		 } else {
		    int diffSD3x = EvIDSD3x - ncounterSD3x;
			for (int i=0; i<diffSD3x; i++) {
			   finSciD3x << ncounterSD3x+i << " " << 0.0 << "\n"; 
			}
		    finSciD3x << EvIDSD3x << " " << EdepSD3x << "\n";
		    ncounterSD3x = ncounterSD3x + diffSD3x + 1;
		 }   
	  }
	  finSciD3x.close();

	  if ((remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciD3.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciD3.txt") << " generated! " << std::endl;
	  }



	  // SciDT1     
	  std::ifstream inputSciDT1x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDT1.txt"));
	  std::string lineSciDT1x;
	  std::getline(inputSciDT1x, lineSciDT1x);
			 
	  ifstream ifileSDT1x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDT1.txt"));
	  if (ifileSDT1x) {
	     remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDT1.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDT1.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDT1x;
	  finSciDT1x.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDT1.txt"));
			  
	  int ncounterSDT1x = 1;
	  while (!inputSciDT1x.eof()) {
	     double EvIDSDT1x, EdepSDT1x;
	     inputSciDT1x >> EvIDSDT1x >> EdepSDT1x;
		 if (EvIDSDT1x == ncounterSDT1x) {
		    finSciDT1x << EvIDSDT1x << " " << EdepSDT1x << "\n";
			ncounterSDT1x++;
		 } else {
		    int diffSDT1x = EvIDSDT1x - ncounterSDT1x;
			for (int i=0; i<diffSDT1x; i++) {
			   finSciDT1x << ncounterSDT1x+i << " " << 0.0 << "\n"; 
			}
			finSciDT1x << EvIDSDT1x << " " << EdepSDT1x << "\n";
			ncounterSDT1x = ncounterSDT1x + diffSDT1x + 1;
		 }   
	  }
	  finSciDT1x.close();

	  if ((remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDT1.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDT1.txt") << " generated! " << std::endl;
	  }



	  // SciDB1    
	  std::ifstream inputSciDB1x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDB1.txt"));
	  std::string lineSciDB1x;
	  std::getline(inputSciDB1x, lineSciDB1x);
			 
	  ifstream ifileSDB1x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDB1.txt"));
	  if (ifileSDB1x) {
	     remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDB1.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDB1.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDB1x;
	  finSciDB1x.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDB1.txt"));
			  
	  int ncounterSDB1x = 1;
	  while (!inputSciDB1x.eof()) {
	     double EvIDSDB1x, EdepSDB1x;
		 inputSciDB1x >> EvIDSDB1x >> EdepSDB1x;
		 if (EvIDSDB1x == ncounterSDB1x) {
		    finSciDB1x << EvIDSDB1x << " " << EdepSDB1x << "\n";
		    ncounterSDB1x++;
	     } else {
	        int diffSDB1x = EvIDSDB1x - ncounterSDB1x;
		    for (int i=0; i<diffSDB1x; i++) {
		       finSciDB1x << ncounterSDB1x+i << " " << 0.0 << "\n"; 
		    }
		    finSciDB1x << EvIDSDB1x << " " << EdepSDB1x << "\n";
		    ncounterSDB1x = ncounterSDB1x + diffSDB1x + 1;
	     }   
	  }
	  finSciDB1x.close();

	  if ((remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDB1.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDB1.txt") << " generated! " << std::endl;
	  }



	  // SciDL1     
	  std::ifstream inputSciDL1x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDL1.txt"));
	  std::string lineSciDL1x;
	  std::getline(inputSciDL1x, lineSciDL1x);
			 
	  ifstream ifileSDL1x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDL1.txt"));
	  if (ifileSDL1x) {
	     remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDL1.txt"));
	     std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDL1.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDL1x;
	  finSciDL1x.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDL1.txt"));
			  
	  int ncounterSDL1x = 1;
	  while (!inputSciDL1x.eof()) {
	     double EvIDSDL1x, EdepSDL1x;
		 inputSciDL1x >> EvIDSDL1x >> EdepSDL1x;
		 if (EvIDSDL1x == ncounterSDL1x) {
		    finSciDL1x << EvIDSDL1x << " " << EdepSDL1x << "\n";
		    ncounterSDL1x++;
		 } else {
		    int diffSDL1x = EvIDSDL1x - ncounterSDL1x;
			for (int i=0; i<diffSDL1x; i++) {
			   finSciDL1x << ncounterSDL1x+i << " " << 0.0 << "\n"; 
			}
			finSciDL1x << EvIDSDL1x << " " << EdepSDL1x << "\n";
			ncounterSDL1x = ncounterSDL1x + diffSDL1x + 1;
		 }   
	  }
	  finSciDL1x.close();

	  if ((remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDL1.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDL1.txt") << " generated! " << std::endl;
	  }



	  // SciDR1     
	  std::ifstream inputSciDR1x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDR1.txt"));
	  std::string lineSciDR1x;
	  std::getline(inputSciDR1x, lineSciDR1x);
			 
	  ifstream ifileSDR1x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDR1.txt"));
	  if (ifileSDR1x) {
	     remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDR1.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDR1.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDR1x;
	  finSciDR1x.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDR1.txt"));
			  
	  int ncounterSDR1x = 1;
	  while (!inputSciDR1x.eof()) {
	     double EvIDSDR1x, EdepSDR1x;
		 inputSciDR1x >> EvIDSDR1x >> EdepSDR1x;
		 if (EvIDSDR1x == ncounterSDR1x) {
		    finSciDR1x << EvIDSDR1x << " " << EdepSDR1x << "\n";
			ncounterSDR1x++;
		 } else {
		    int diffSDR1x = EvIDSDR1x - ncounterSDR1x;
			for (int i=0; i<diffSDR1x; i++) {
			   finSciDR1x << ncounterSDR1x+i << " " << 0.0 << "\n"; 
			}
			finSciDR1x << EvIDSDR1x << " " << EdepSDR1x << "\n";
			ncounterSDR1x = ncounterSDR1x + diffSDR1x + 1;
		 }     
      }
	  finSciDR1x.close();

	  if ((remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDR1.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDR1.txt") << " generated! " << std::endl;
	  }



	  // SciDT2     
	  std::ifstream inputSciDT2x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDT2.txt"));
	  std::string lineSciDT2x;
	  std::getline(inputSciDT2x, lineSciDT2x);
			 
	  ifstream ifileSDT2x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDT2.txt"));
	  if (ifileSDT2x) {
	     remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDT2.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDT2.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDT2x;
	  finSciDT2x.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDT2.txt"));
			  
	  int ncounterSDT2x = 1;
	  while (!inputSciDT2x.eof()) {
	     double EvIDSDT2x, EdepSDT2x;
	     inputSciDT2x >> EvIDSDT2x >> EdepSDT2x;
		 if (EvIDSDT2x == ncounterSDT2x) {
		    finSciDT2x << EvIDSDT2x << " " << EdepSDT2x << "\n";
			ncounterSDT2x++;
		 } else {
		    int diffSDT2x = EvIDSDT2x - ncounterSDT2x;
			for (int i=0; i<diffSDT2x; i++) {
			   finSciDT2x << ncounterSDT2x+i << " " << 0.0 << "\n"; 
			}
			finSciDT2x << EvIDSDT2x << " " << EdepSDT2x << "\n";
			ncounterSDT2x = ncounterSDT2x + diffSDT2x + 1;
		 }   
	  }
	  finSciDT2x.close();

	  if ((remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDT2.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDT2.txt") << " generated! " << std::endl;
	  }



	  // SciDB2    
	  std::ifstream inputSciDB2x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDB2.txt"));
	  std::string lineSciDB2x;
	  std::getline(inputSciDB2x, lineSciDB2x);
			 
	  ifstream ifileSDB2x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDB2.txt"));
	  if (ifileSDB2x) {
	     remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDB2.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDB2.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDB2x;
	  finSciDB2x.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDB2.txt"));
			  
	  int ncounterSDB2x = 1;
	  while (!inputSciDB2x.eof()) {
	     double EvIDSDB2x, EdepSDB2x;
		 inputSciDB2x >> EvIDSDB2x >> EdepSDB2x;
		 if (EvIDSDB2x == ncounterSDB2x) {
		    finSciDB2x << EvIDSDB2x << " " << EdepSDB2x << "\n";
		    ncounterSDB2x++;
	     } else {
	        int diffSDB2x = EvIDSDB2x - ncounterSDB2x;
		    for (int i=0; i<diffSDB2x; i++) {
		       finSciDB2x << ncounterSDB2x+i << " " << 0.0 << "\n"; 
		    }
		    finSciDB2x << EvIDSDB2x << " " << EdepSDB2x << "\n";
		    ncounterSDB2x = ncounterSDB2x + diffSDB2x + 1;
	     }   
	  }
	  finSciDB2x.close();

	  if ((remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDB2.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDB2.txt") << " generated! " << std::endl;
	  }



	  // SciDL2     
	  std::ifstream inputSciDL2x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDL2.txt"));
	  std::string lineSciDL2x;
	  std::getline(inputSciDL2x, lineSciDL2x);
			 
	  ifstream ifileSDL2x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDL2.txt"));
	  if (ifileSDL2x) {
	     remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDL2.txt"));
	     std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDL2.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDL2x;
	  finSciDL2x.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDL2.txt"));
			  
	  int ncounterSDL2x = 1;
	  while (!inputSciDL2x.eof()) {
	     double EvIDSDL2x, EdepSDL2x;
		 inputSciDL2x >> EvIDSDL2x >> EdepSDL2x;
		 if (EvIDSDL2x == ncounterSDL2x) {
		    finSciDL2x << EvIDSDL2x << " " << EdepSDL2x << "\n";
		    ncounterSDL2x++;
		 } else {
		    int diffSDL2x = EvIDSDL2x - ncounterSDL2x;
			for (int i=0; i<diffSDL2x; i++) {
			   finSciDL2x << ncounterSDL2x+i << " " << 0.0 << "\n"; 
			}
			finSciDL2x << EvIDSDL2x << " " << EdepSDL2x << "\n";
			ncounterSDL2x = ncounterSDL2x + diffSDL2x + 1;
		 }   
	  }
	  finSciDL2x.close();

	  if ((remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDL2.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDL2.txt") << " generated! " << std::endl;
	  }



	  // SciDR2     
	  std::ifstream inputSciDR2x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDR2.txt"));
	  std::string lineSciDR2x;
	  std::getline(inputSciDR2x, lineSciDR2x);
			 
	  ifstream ifileSDR2x(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDR2.txt"));
	  if (ifileSDR2x) {
	     remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDR2.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDR2.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finSciDR2x;
	  finSciDR2x.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDR2.txt"));
			  
	  int ncounterSDR2x = 1;
	  while (!inputSciDR2x.eof()) {
	     double EvIDSDR2x, EdepSDR2x;
		 inputSciDR2x >> EvIDSDR2x >> EdepSDR2x;
		 if (EvIDSDR2x == ncounterSDR2x) {
		    finSciDR2x << EvIDSDR2x << " " << EdepSDR2x << "\n";
			ncounterSDR2x++;
		 } else {
		    int diffSDR2x = EvIDSDR2x - ncounterSDR2x;
			for (int i=0; i<diffSDR2x; i++) {
			   finSciDR2x << ncounterSDR2x+i << " " << 0.0 << "\n"; 
			}
			finSciDR2x << EvIDSDR2x << " " << EdepSDR2x << "\n";
			ncounterSDR2x = ncounterSDR2x + diffSDR2x + 1;
		 }     
      }
	  finSciDR2x.close();

	  if ((remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxSciDR2.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_SciDR2.txt") << " generated! " << std::endl;
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
   FileFillerFinalsquare();
   return 0;
}  
