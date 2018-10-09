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
	
   // X-ray cascade
   std::string filex = "../../simdata/recover/4mm_Al_4mm_SciD_4mm_Al_300mm_BGO_10mm_SciD_TB_1e5goldcascade.root";
   // Mu-decay
   std::string filemu = "../../simdata/recover/4mm_Al_4mm_SciD_4mm_Al_300mm_BGO_10mm_SciD_TB_1e5mudecay.root";
   
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
      TTree *tSciD2 = (TTree*)fmu->Get("Detector/SciDet2");
      TTree *tSciD3 = (TTree*)fmu->Get("Detector/SciDet3");
      TTree *tBGOD1 = (TTree*)fmu->Get("Detector/BGODet1");
      
      float EventID,Edep; 

      tSciD1->SetBranchAddress("EventID",&EventID); // D-stream 
      tSciD1->SetBranchAddress("Edep",&Edep);
      tSciD2->SetBranchAddress("EventID",&EventID);
      tSciD2->SetBranchAddress("Edep",&Edep);
      tSciD3->SetBranchAddress("EventID",&EventID);
      tSciD3->SetBranchAddress("Edep",&Edep);
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

      
      // SciD3
      ofstream tmpSciD3;
      tmpSciD3.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD3.txt"));
      tmpSciD3 << "EventID        Edep\n";
      for (int i=0; i<tSciD3->GetEntries(); i++){
	     tSciD3->GetEntry(i);
	     tmpSciD3 << EventID << " " << Edep << "\n";
	  }
      tmpSciD3.close();
      std::cout << std::endl << "File: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD3.txt" << " written!" << std::endl;
      
   
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



      // SciD3     
      std::ifstream inputSciD3(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD3.txt"));
      std::string lineSciD3;
      std::getline(inputSciD3, lineSciD3);
     
      ifstream ifileSD3(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD3.txt"));
      if (ifileSD3) {
         remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD3.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD3.txt" << " successfully removed!" << std::endl;
	  }
     
      ofstream finSciD3;
      finSciD3.open(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD3.txt"));
      
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

      if ((remove(TString("../../simdata/recover/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD3.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD3.txt") << " generated! " << std::endl;
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
      TTree *txSciD3 = (TTree*)fx->Get("Detector/SciDet3");
      TTree *txBGOD1 = (TTree*)fx->Get("Detector/BGODet1");
      
      float EventID,Edep; 

      txSciD1->SetBranchAddress("EventID",&EventID); // D-stream 
      txSciD1->SetBranchAddress("Edep",&Edep);
      txSciD2->SetBranchAddress("EventID",&EventID);
      txSciD2->SetBranchAddress("Edep",&Edep);
      txSciD3->SetBranchAddress("EventID",&EventID);
      txSciD3->SetBranchAddress("Edep",&Edep);
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


      // SciD3 
      ofstream tmpxSciD3;
      tmpxSciD3.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciD3.txt"));
      tmpxSciD3 << "EventID        Edep\n";
      for (int i=0; i<txSciD3->GetEntries(); i++){
	     txSciD3->GetEntry(i);
	     tmpxSciD3 << EventID << " " << Edep << "\n";
	  }
      tmpxSciD3.close();
      std::cout << std::endl << "File: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciD3.txt" << " written!" << std::endl;


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


      // SciD3     
      std::ifstream inputSciD3x(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciD3.txt"));
      std::string lineSciD3x;
      std::getline(inputSciD3x, lineSciD3x);
     
      ifstream ifileSD3x(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD3.txt"));
      if (ifileSD3x) {
         remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD3.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD3.txt" << " successfully removed!" << std::endl;
	  }
     
      ofstream finSciD3x;
      finSciD3x.open(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD3.txt"));
      
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

      if ((remove(TString("../../simdata/recover/"+((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_tmpxSciD3.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(22,((Xfiles[k]).find(".root"))-22))+"_SciD3.txt") << " generated! " << std::endl;
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


int main() {
   FileFillerRecover();
   return 0;
}  
