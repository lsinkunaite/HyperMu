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


void FileFillerRecover(){	
	
   //const int length = 5;
   //float phiArray[length] = {0, 25, 50, 75, 100};
   //float zArray[length] = {0, 15, 30, 45, 60};
   const int length = 1;
   float phiArray[length] = {50};
   float zArray[length] = {30};

   int phishift, zshift;
   
   for (int phi=0; phi<length; phi++) {
      for (int z=0; z < length; z++) {
	     phishift = phiArray[phi];
	     zshift = zArray[z];

   
		 std::stringstream phishiftss;
		 std::stringstream zshiftss;
		 phishiftss << phishift;
		 zshiftss << zshift;

		 // X-ray cascade
		 //std::string filex = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_fixed_1e5goldcascade.root";
         std::string filex = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade1_1e5goldcascade.root";
         std::string filex2 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade2_1e5goldcascade.root";
         std::string filex3 = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_cascade3_1e5goldcascade.root";
		 // Mu-decay
		 //std::string filemu = "../../simdata/recover/6xSciDs_4mm_Al_4mm_Al_300mm_BGO_40mm_Al_Cav_"+TString(phishiftss.str())+"mm_phi_"+TString(zshiftss.str())+"mm_z_shifted_fixed_1e5mudecay.root";
   
   	     std::vector<std::string> Xfiles;
		 std::vector<std::string> mufiles;
		   
		 Xfiles.push_back(filex);
         Xfiles.push_back(filex2);
         Xfiles.push_back(filex3);
//		 mufiles.push_back(filemu);



		   //-------------------------------------------------------------------
		   //                          Mu-decay
		   //-------------------------------------------------------------------


		   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;
		   std::cout << "\033[1;35m----------------------- Mu-decay -------------------------\033[0m" << std::endl;
		   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;


		 
		   for (int k = 0; k<mufiles.size(); k++) {
			  TFile *fmu = new TFile(TString(mufiles[k]));
			  
			  TTree *tSciD1 = (TTree*)fmu->Get("Detector/SciDet1"); // D-stream
			  TTree *tSciD2 = (TTree*)fmu->Get("Detector/SciDet2");
			  TTree *tSciDT = (TTree*)fmu->Get("Detector/SciDetT");
			  TTree *tSciDB = (TTree*)fmu->Get("Detector/SciDetB");
			  TTree *tSciDL = (TTree*)fmu->Get("Detector/SciDetL");
			  TTree *tSciDR = (TTree*)fmu->Get("Detector/SciDetR");
			  TTree *tBGOD1 = (TTree*)fmu->Get("Detector/BGODet1");
			  
			  float EventID,Edep; 

			  tSciD1->SetBranchAddress("EventID",&EventID); // D-stream 
			  tSciD1->SetBranchAddress("Edep",&Edep);
			  tSciD2->SetBranchAddress("EventID",&EventID);
			  tSciD2->SetBranchAddress("Edep",&Edep);
			  tSciDT->SetBranchAddress("EventID",&EventID);
			  tSciDT->SetBranchAddress("Edep",&Edep);
			  tSciDB->SetBranchAddress("EventID",&EventID);
			  tSciDB->SetBranchAddress("Edep",&Edep);
			  tSciDL->SetBranchAddress("EventID",&EventID);
			  tSciDL->SetBranchAddress("Edep",&Edep);
			  tSciDR->SetBranchAddress("EventID",&EventID);
			  tSciDR->SetBranchAddress("Edep",&Edep);
			  tBGOD1->SetBranchAddress("EventID",&EventID);
			  tBGOD1->SetBranchAddress("Edep",&Edep);

		  
			  //----------------------------------------------------------------
			  //                          Writing
			  //----------------------------------------------------------------


			  std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
			  std::cout << "\033[1;34m--------------------- Writing Loop " << k+1 << " ---------------------\033[0m" << std::endl;
			  std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;

			  
			  // SciD1 
			  ofstream tmpSciD1;
			  tmpSciD1.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD1.txt"));
			  tmpSciD1 << "EventID        Edep\n";
			  for (int i=0; i<tSciD1->GetEntries(); i++){
				 tSciD1->GetEntry(i);
				 tmpSciD1 << EventID << " " << Edep << "\n";
			  }
			  tmpSciD1.close();
			  std::cout << std::endl << "File: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD1.txt" << " written!" << std::endl;

			  
			  // SciD2
			  ofstream tmpSciD2;
			  tmpSciD2.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD2.txt"));
			  tmpSciD2 << "EventID        Edep\n";
			  for (int i=0; i<tSciD2->GetEntries(); i++){
				 tSciD2->GetEntry(i);
				 tmpSciD2 << EventID << " " << Edep << "\n";
			  }
			  tmpSciD2.close();
			  std::cout << std::endl << "File: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD2.txt" << " written!" << std::endl;


			  // SciDT
			  ofstream tmpSciDT;
			  tmpSciDT.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDT.txt"));
			  tmpSciDT << "EventID        Edep\n";
			  for (int i=0; i<tSciDT->GetEntries(); i++){
				 tSciDT->GetEntry(i);
				 tmpSciDT << EventID << " " << Edep << "\n";
			  }
			  tmpSciDT.close();
			  std::cout << std::endl << "File: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDT.txt" << " written!" << std::endl;

			  
			  // SciDB
			  ofstream tmpSciDB;
			  tmpSciDB.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDB.txt"));
			  tmpSciDB << "EventID        Edep\n";
			  for (int i=0; i<tSciDB->GetEntries(); i++){
				 tSciDB->GetEntry(i);
				 tmpSciDB << EventID << " " << Edep << "\n";
			  }
			  tmpSciDB.close();
			  std::cout << std::endl << "File: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDB.txt" << " written!" << std::endl;
			  
			  
			  // SciDL
			  ofstream tmpSciDL;
			  tmpSciDL.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDL.txt"));
			  tmpSciDL << "EventID        Edep\n";
			  for (int i=0; i<tSciDL->GetEntries(); i++){
				 tSciDL->GetEntry(i);
				 tmpSciDL << EventID << " " << Edep << "\n";
			  }
			  tmpSciDL.close();
			  std::cout << std::endl << "File: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDL.txt" << " written!" << std::endl;

		   
			  // SciDR
			  ofstream tmpSciDR;
			  tmpSciDR.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDR.txt"));
			  tmpSciDR << "EventID        Edep\n";
			  for (int i=0; i<tSciDR->GetEntries(); i++){
				 tSciDR->GetEntry(i);
				 tmpSciDR << EventID << " " << Edep << "\n";
			  }
			  tmpSciDR.close();
			  std::cout << std::endl << "File: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDR.txt" << " written!" << std::endl;


			  // BGOD1 
			  ofstream tmpBGOD1;
			  tmpBGOD1.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpBGOD1.txt"));
			  tmpBGOD1 << "EventID        Edep\n";
			  for (int i=0; i<tBGOD1->GetEntries(); i++){
				 tBGOD1->GetEntry(i);
				 tmpBGOD1 << EventID << " " << Edep << "\n";
			  }
			  tmpBGOD1.close();
			  std::cout << std::endl << "File: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpBGOD1.txt" << " written!" << std::endl;

				
		   
			  //----------------------------------------------------------------
			  //                          Rewriting
			  //----------------------------------------------------------------
		 
			  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
			  std::cout << "\033[1;31m-------------------- Rewriting Loop " << k+1 << " --------------------\033[0m" << std::endl;
			  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


		 
			  // SciD1     
			  std::ifstream inputSciD1(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD1.txt"));
			  std::string lineSciD1;
			  std::getline(inputSciD1, lineSciD1);
			 
			  ifstream ifileSD1(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD1.txt"));
			  if (ifileSD1) {
				 remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD1.txt"));
				 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD1.txt" << " successfully removed!" << std::endl;
			  }
			 
			  ofstream finSciD1;
			  finSciD1.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD1.txt"));
			  
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

			  if ((remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD1.txt"))) == 0) {
				 std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD1.txt") << " generated! " << std::endl;
			  }



			  // SciD2     
			  std::ifstream inputSciD2(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD2.txt"));
			  std::string lineSciD2;
			  std::getline(inputSciD2, lineSciD2);
			 
			  ifstream ifileSD2(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD2.txt"));
			  if (ifileSD2) {
				 remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD2.txt"));
				 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD2.txt" << " successfully removed!" << std::endl;
			  }
			 
			  ofstream finSciD2;
			  finSciD2.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD2.txt"));
			  
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

			  if ((remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD2.txt"))) == 0) {
				 std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD2.txt") << " generated! " << std::endl;
			  }



			  // SciDT     
			  std::ifstream inputSciDT(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDT.txt"));
			  std::string lineSciDT;
			  std::getline(inputSciDT, lineSciDT);
			 
			  ifstream ifileSDT(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDT.txt"));
			  if (ifileSDT) {
				 remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDT.txt"));
				 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDT.txt" << " successfully removed!" << std::endl;
			  }
			 
			  ofstream finSciDT;
			  finSciDT.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDT.txt"));
			  
			  int ncounterSDT = 1;
			  while (!inputSciDT.eof()) {
				 double EvIDSDT, EdepSDT;
				 inputSciDT >> EvIDSDT >> EdepSDT;
				 if (EvIDSDT == ncounterSDT) {
					finSciDT << EvIDSDT << " " << EdepSDT << "\n";
					ncounterSDT++;
				 } else {
					  int diffSDT = EvIDSDT - ncounterSDT;
					  for (int i=0; i<diffSDT; i++) {
						 finSciDT << ncounterSDT+i << " " << 0.0 << "\n"; 
					  }
					  finSciDT << EvIDSDT << " " << EdepSDT << "\n";
					  ncounterSDT = ncounterSDT + diffSDT + 1;
				 }   
			  }
			  finSciDT.close();

			  if ((remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDT.txt"))) == 0) {
				 std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDT.txt") << " generated! " << std::endl;
			  }



			  // SciDB     
			  std::ifstream inputSciDB(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDB.txt"));
			  std::string lineSciDB;
			  std::getline(inputSciDB, lineSciDB);
			 
			  ifstream ifileSDB(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDB.txt"));
			  if (ifileSDB) {
				 remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDB.txt"));
				 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDB.txt" << " successfully removed!" << std::endl;
			  }
			 
			  ofstream finSciDB;
			  finSciDB.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDB.txt"));
			  
			  int ncounterSDB = 1;
			  while (!inputSciDB.eof()) {
				 double EvIDSDB, EdepSDB;
				 inputSciDB >> EvIDSDB >> EdepSDB;
				 if (EvIDSDB == ncounterSDB) {
					finSciDB << EvIDSDB << " " << EdepSDB << "\n";
					ncounterSDB++;
				 } else {
					  int diffSDB = EvIDSDB - ncounterSDB;
					  for (int i=0; i<diffSDB; i++) {
						 finSciDB << ncounterSDB+i << " " << 0.0 << "\n"; 
					  }
					  finSciDB << EvIDSDB << " " << EdepSDB << "\n";
					  ncounterSDB = ncounterSDB + diffSDB + 1;
				 }   
			  }
			  finSciDB.close();

			  if ((remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDB.txt"))) == 0) {
				 std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDB.txt") << " generated! " << std::endl;
			  }



			  // SciDL     
			  std::ifstream inputSciDL(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDL.txt"));
			  std::string lineSciDL;
			  std::getline(inputSciDL, lineSciDL);
			 
			  ifstream ifileSDL(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDL.txt"));
			  if (ifileSDL) {
				 remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDL.txt"));
				 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDL.txt" << " successfully removed!" << std::endl;
			  }
			 
			  ofstream finSciDL;
			  finSciDL.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDL.txt"));
			  
			  int ncounterSDL = 1;
			  while (!inputSciDL.eof()) {
				 double EvIDSDL, EdepSDL;
				 inputSciDL >> EvIDSDL >> EdepSDL;
				 if (EvIDSDL == ncounterSDL) {
					finSciDL << EvIDSDL << " " << EdepSDL << "\n";
					ncounterSDL++;
				 } else {
					  int diffSDL = EvIDSDL - ncounterSDL;
					  for (int i=0; i<diffSDL; i++) {
						 finSciDL << ncounterSDL+i << " " << 0.0 << "\n"; 
					  }
					  finSciDL << EvIDSDL << " " << EdepSDL << "\n";
					  ncounterSDL = ncounterSDL + diffSDL + 1;
				 }   
			  }
			  finSciDL.close();

			  if ((remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDL.txt"))) == 0) {
				 std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDL.txt") << " generated! " << std::endl;
			  }



			  // SciDR     
			  std::ifstream inputSciDR(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDR.txt"));
			  std::string lineSciDR;
			  std::getline(inputSciDR, lineSciDR);
			 
			  ifstream ifileSDR(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDR.txt"));
			  if (ifileSDR) {
				 remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDR.txt"));
				 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDR.txt" << " successfully removed!" << std::endl;
			  }
			 
			  ofstream finSciDR;
			  finSciDR.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDR.txt"));
			  
			  int ncounterSDR = 1;
			  while (!inputSciDR.eof()) {
				 double EvIDSDR, EdepSDR;
				 inputSciDR >> EvIDSDR >> EdepSDR;
				 if (EvIDSDR == ncounterSDR) {
					finSciDR << EvIDSDR << " " << EdepSDR << "\n";
					ncounterSDR++;
				 } else {
					  int diffSDR = EvIDSDR - ncounterSDR;
					  for (int i=0; i<diffSDR; i++) {
						 finSciDR << ncounterSDR+i << " " << 0.0 << "\n"; 
					  }
					  finSciDR << EvIDSDR << " " << EdepSDR << "\n";
					  ncounterSDR = ncounterSDR + diffSDR + 1;
				 }   
			  }
			  finSciDR.close();

			  if ((remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciDR.txt"))) == 0) {
				 std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciDR.txt") << " generated! " << std::endl;
			  }



			  // BGOD1     
			  std::ifstream inputBGOD1(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpBGOD1.txt"));
			  std::string lineBGOD1;
			  std::getline(inputBGOD1, lineBGOD1);
			 
			  ifstream ifileBD1(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_BGOD1.txt"));
			  if (ifileBD1) {
				 remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_BGOD1.txt"));
				 std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_BGOD1.txt" << " successfully removed!" << std::endl;
			  }
			 
			  ofstream finBGOD1;
			  finBGOD1.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_BGOD1.txt"));
			  
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

			  if ((remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpBGOD1.txt"))) == 0) {
				 std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_BGOD1.txt") << " generated! " << std::endl;
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
			  TTree *txSciD2 = (TTree*)fx->Get("Detector/SciDet2");
			  TTree *txSciDT = (TTree*)fx->Get("Detector/SciDetT");
			  TTree *txSciDB = (TTree*)fx->Get("Detector/SciDetB");
			  TTree *txSciDL = (TTree*)fx->Get("Detector/SciDetL");
			  TTree *txSciDR = (TTree*)fx->Get("Detector/SciDetR");
			  TTree *txBGOD1 = (TTree*)fx->Get("Detector/BGODet1");
			  
			  float EventID,Edep; 

			  txSciD1->SetBranchAddress("EventID",&EventID); // D-stream 
			  txSciD1->SetBranchAddress("Edep",&Edep);
			  txSciD2->SetBranchAddress("EventID",&EventID);
			  txSciD2->SetBranchAddress("Edep",&Edep);
			  txSciDT->SetBranchAddress("EventID",&EventID);
			  txSciDT->SetBranchAddress("Edep",&Edep);
			  txSciDB->SetBranchAddress("EventID",&EventID);
			  txSciDB->SetBranchAddress("Edep",&Edep);
			  txSciDL->SetBranchAddress("EventID",&EventID);
			  txSciDL->SetBranchAddress("Edep",&Edep);
			  txSciDR->SetBranchAddress("EventID",&EventID);
			  txSciDR->SetBranchAddress("Edep",&Edep);
			  txBGOD1->SetBranchAddress("EventID",&EventID);
			  txBGOD1->SetBranchAddress("Edep",&Edep);
		  
		  
			  //----------------------------------------------------------------
			  //                          Writing
			  //----------------------------------------------------------------


			  std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
			  std::cout << "\033[1;34m--------------------- Writing Loop " << k+1 << " ---------------------\033[0m" << std::endl;
			  std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;

			  
			  // SciD1 
			  ofstream tmpxSciD1;
			  tmpxSciD1.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciD1.txt"));
			  tmpxSciD1 << "EventID        Edep\n";
			  for (int i=0; i<txSciD1->GetEntries(); i++){
				 txSciD1->GetEntry(i);
				 tmpxSciD1 << EventID << " " << Edep << "\n";
			  }
			  tmpxSciD1.close();
			  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciD1.txt" << " written!" << std::endl;


			  // SciD2 
			  ofstream tmpxSciD2;
			  tmpxSciD2.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciD2.txt"));
			  tmpxSciD2 << "EventID        Edep\n";
			  for (int i=0; i<txSciD2->GetEntries(); i++){
				 txSciD2->GetEntry(i);
				 tmpxSciD2 << EventID << " " << Edep << "\n";
			  }
			  tmpxSciD2.close();
			  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciD2.txt" << " written!" << std::endl;

			  
			  // SciDT 
			  ofstream tmpxSciDT;
			  tmpxSciDT.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDT.txt"));
			  tmpxSciDT << "EventID        Edep\n";
			  for (int i=0; i<txSciDT->GetEntries(); i++){
				 txSciDT->GetEntry(i);
				 tmpxSciDT << EventID << " " << Edep << "\n";
			  }
			  tmpxSciDT.close();
			  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDT.txt" << " written!" << std::endl;


			  // SciDB 
			  ofstream tmpxSciDB;
			  tmpxSciDB.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDB.txt"));
			  tmpxSciDB << "EventID        Edep\n";
			  for (int i=0; i<txSciDB->GetEntries(); i++){
				 txSciDB->GetEntry(i);
				 tmpxSciDB << EventID << " " << Edep << "\n";
			  }
			  tmpxSciDB.close();
			  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDB.txt" << " written!" << std::endl;


			  // SciDL 
			  ofstream tmpxSciDL;
			  tmpxSciDL.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDL.txt"));
			  tmpxSciDL << "EventID        Edep\n";
			  for (int i=0; i<txSciDL->GetEntries(); i++){
				 txSciDL->GetEntry(i);
				 tmpxSciDL << EventID << " " << Edep << "\n";
			  }
			  tmpxSciDL.close();
			  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDL.txt" << " written!" << std::endl;


			  // SciDR 
			  ofstream tmpxSciDR;
			  tmpxSciDR.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDR.txt"));
			  tmpxSciDR << "EventID        Edep\n";
			  for (int i=0; i<txSciDR->GetEntries(); i++){
				 txSciDR->GetEntry(i);
				 tmpxSciDR << EventID << " " << Edep << "\n";
			  }
			  tmpxSciDR.close();
			  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDR.txt" << " written!" << std::endl;


			  // BGOD1 
			  ofstream tmpxBGOD1;
			  tmpxBGOD1.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxBGOD1.txt"));
			  tmpxBGOD1 << "EventID        Edep\n";
			  for (int i=0; i<txBGOD1->GetEntries(); i++){
				 txBGOD1->GetEntry(i);
				 tmpxBGOD1 << EventID << " " << Edep << "\n";
			  }
			  tmpxBGOD1.close();
			  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxBGOD1.txt" << " written!" << std::endl;
		  
		  
		   
			  //----------------------------------------------------------------
			  //                          Rewriting
			  //----------------------------------------------------------------
		 
			  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
			  std::cout << "\033[1;31m-------------------- Rewriting Loop " << k+1 << " --------------------\033[0m" << std::endl;
			  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


		 
			  // SciD1     
			  std::ifstream inputSciD1x(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciD1.txt"));
			  std::string lineSciD1x;
			  std::getline(inputSciD1x, lineSciD1x);
			 
			  ifstream ifileSD1x(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD1.txt"));
			  if (ifileSD1x) {
				 remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD1.txt"));
				 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD1.txt" << " successfully removed!" << std::endl;
			  }
			 
			  ofstream finSciD1x;
			  finSciD1x.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD1.txt"));
			  
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

			  if ((remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciD1.txt"))) == 0) {
				 std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD1.txt") << " generated! " << std::endl;
			  }


			  // SciD2     
			  std::ifstream inputSciD2x(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciD2.txt"));
			  std::string lineSciD2x;
			  std::getline(inputSciD2x, lineSciD2x);
			 
			  ifstream ifileSD2x(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD2.txt"));
			  if (ifileSD2x) {
				 remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD2.txt"));
				 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD2.txt" << " successfully removed!" << std::endl;
			  }
			 
			  ofstream finSciD2x;
			  finSciD2x.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD2.txt"));
			  
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

			  if ((remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciD2.txt"))) == 0) {
				 std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD2.txt") << " generated! " << std::endl;
			  }


			  // SciDT     
			  std::ifstream inputSciDTx(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDT.txt"));
			  std::string lineSciDTx;
			  std::getline(inputSciDTx, lineSciDTx);
			 
			  ifstream ifileSDTx(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDT.txt"));
			  if (ifileSDTx) {
				 remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDT.txt"));
				 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDT.txt" << " successfully removed!" << std::endl;
			  }
			 
			  ofstream finSciDTx;
			  finSciDTx.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDT.txt"));
			  
			  int ncounterSDTx = 1;
			  while (!inputSciDTx.eof()) {
				 double EvIDSDTx, EdepSDTx;
				 inputSciDTx >> EvIDSDTx >> EdepSDTx;
				 if (EvIDSDTx == ncounterSDTx) {
					finSciDTx << EvIDSDTx << " " << EdepSDTx << "\n";
					ncounterSDTx++;
				 } else {
					  int diffSDTx = EvIDSDTx - ncounterSDTx;
					  for (int i=0; i<diffSDTx; i++) {
						 finSciDTx << ncounterSDTx+i << " " << 0.0 << "\n"; 
					  }
					  finSciDTx << EvIDSDTx << " " << EdepSDTx << "\n";
					  ncounterSDTx = ncounterSDTx + diffSDTx + 1;
				 }   
			  }
			  finSciDTx.close();

			  if ((remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDT.txt"))) == 0) {
				 std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDT.txt") << " generated! " << std::endl;
			  }


			  // SciDB     
			  std::ifstream inputSciDBx(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDB.txt"));
			  std::string lineSciDBx;
			  std::getline(inputSciDBx, lineSciDBx);
			 
			  ifstream ifileSDBx(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDB.txt"));
			  if (ifileSDBx) {
				 remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDB.txt"));
				 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDB.txt" << " successfully removed!" << std::endl;
			  }
			 
			  ofstream finSciDBx;
			  finSciDBx.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDB.txt"));
			  
			  int ncounterSDBx = 1;
			  while (!inputSciDBx.eof()) {
				 double EvIDSDBx, EdepSDBx;
				 inputSciDBx >> EvIDSDBx >> EdepSDBx;
				 if (EvIDSDBx == ncounterSDBx) {
					finSciDBx << EvIDSDBx << " " << EdepSDBx << "\n";
					ncounterSDBx++;
				 } else {
					  int diffSDBx = EvIDSDBx - ncounterSDBx;
					  for (int i=0; i<diffSDBx; i++) {
						 finSciDBx << ncounterSDBx+i << " " << 0.0 << "\n"; 
					  }
					  finSciDBx << EvIDSDBx << " " << EdepSDBx << "\n";
					  ncounterSDBx = ncounterSDBx + diffSDBx + 1;
				 }   
			  }
			  finSciDBx.close();

			  if ((remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDB.txt"))) == 0) {
				 std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDB.txt") << " generated! " << std::endl;
			  }


			  // SciDL     
			  std::ifstream inputSciDLx(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDL.txt"));
			  std::string lineSciDLx;
			  std::getline(inputSciDLx, lineSciDLx);
			 
			  ifstream ifileSDLx(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDL.txt"));
			  if (ifileSDLx) {
				 remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDL.txt"));
				 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDL.txt" << " successfully removed!" << std::endl;
			  }
			 
			  ofstream finSciDLx;
			  finSciDLx.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDL.txt"));
			  
			  int ncounterSDLx = 1;
			  while (!inputSciDLx.eof()) {
				 double EvIDSDLx, EdepSDLx;
				 inputSciDLx >> EvIDSDLx >> EdepSDLx;
				 if (EvIDSDLx == ncounterSDLx) {
					finSciDLx << EvIDSDLx << " " << EdepSDLx << "\n";
					ncounterSDLx++;
				 } else {
					  int diffSDLx = EvIDSDLx - ncounterSDLx;
					  for (int i=0; i<diffSDLx; i++) {
						 finSciDLx << ncounterSDLx+i << " " << 0.0 << "\n"; 
					  }
					  finSciDLx << EvIDSDLx << " " << EdepSDLx << "\n";
					  ncounterSDLx = ncounterSDLx + diffSDLx + 1;
				 }   
			  }
			  finSciDLx.close();

			  if ((remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDL.txt"))) == 0) {
				 std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDL.txt") << " generated! " << std::endl;
			  }


			  // SciDR     
			  std::ifstream inputSciDRx(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDR.txt"));
			  std::string lineSciDRx;
			  std::getline(inputSciDRx, lineSciDRx);
			 
			  ifstream ifileSDRx(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDR.txt"));
			  if (ifileSDRx) {
				 remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDR.txt"));
				 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDR.txt" << " successfully removed!" << std::endl;
			  }
			 
			  ofstream finSciDRx;
			  finSciDRx.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDR.txt"));
			  
			  int ncounterSDRx = 1;
			  while (!inputSciDRx.eof()) {
				 double EvIDSDRx, EdepSDRx;
				 inputSciDRx >> EvIDSDRx >> EdepSDRx;
				 if (EvIDSDRx == ncounterSDRx) {
					finSciDRx << EvIDSDRx << " " << EdepSDRx << "\n";
					ncounterSDRx++;
				 } else {
					  int diffSDRx = EvIDSDRx - ncounterSDRx;
					  for (int i=0; i<diffSDRx; i++) {
						 finSciDRx << ncounterSDRx+i << " " << 0.0 << "\n"; 
					  }
					  finSciDRx << EvIDSDRx << " " << EdepSDRx << "\n";
					  ncounterSDRx = ncounterSDRx + diffSDRx + 1;
				 }   
			  }
			  finSciDRx.close();

			  if ((remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciDR.txt"))) == 0) {
				 std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciDR.txt") << " generated! " << std::endl;
			  }


			  // BGOD1     
			  std::ifstream inputBGOD1x(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxBGOD1.txt"));
			  std::string lineBGOD1x;
			  std::getline(inputBGOD1x, lineBGOD1x);
			 
			  ifstream ifileBD1x(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_BGOD1.txt"));
			  if (ifileBD1x) {
				 remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_BGOD1.txt"));
				 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_BGOD1.txt" << " successfully removed!" << std::endl;
			  }
			 
			  ofstream finBGOD1x;
			  finBGOD1x.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_BGOD1.txt"));
			  
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

			  if ((remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxBGOD1.txt"))) == 0) {
				 std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_BGOD1.txt") << " generated! " << std::endl;
			  }

		 
		   }

      }
   }   


}


int main() {
   FileFillerRecover();
   return 0;
}  
