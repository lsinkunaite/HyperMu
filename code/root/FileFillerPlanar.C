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


void FileFillerPlanar(){	
	
   // X-ray cascade
   std::string file3Alx250 = "../../simdata/planar/planar_SMALL_2x5mm_250mm_SciD_3mm_Al_1e6goldcascade.root"; // 3-mm
   std::string file3Alx500 = "../../simdata/planar/planar_SMALL_2x5mm_500mm_SciD_3mm_Al_1e6goldcascade.root";
   std::string file3Alx750 = "../../simdata/planar/planar_SMALL_2x5mm_750mm_SciD_3mm_Al_1e6goldcascade.root";
   std::string file6Alx250 = "../../simdata/planar/planar_SMALL_2x5mm_250mm_SciD_6mm_Al_1e6goldcascade.root"; // 6-mm
   std::string file6Alx500 = "../../simdata/planar/planar_SMALL_2x5mm_500mm_SciD_6mm_Al_1e6goldcascade.root";
   std::string file6Alx750 = "../../simdata/planar/planar_SMALL_2x5mm_750mm_SciD_6mm_Al_1e6goldcascade.root";   
   // Mu-decay
   std::string file3Almu250 = "../../simdata/planar/planar_SMALL_2x5mm_250mm_SciD_3mm_Al_1e6mudecay.root"; // 3-mm
   std::string file3Almu500 = "../../simdata/planar/planar_SMALL_2x5mm_500mm_SciD_3mm_Al_1e6mudecay.root";
   std::string file3Almu750 = "../../simdata/planar/planar_SMALL_2x5mm_750mm_SciD_3mm_Al_1e6mudecay.root";
   std::string file6Almu250 = "../../simdata/planar/planar_SMALL_2x5mm_250mm_SciD_6mm_Al_1e6mudecay.root"; // 6-mm
   std::string file6Almu500 = "../../simdata/planar/planar_SMALL_2x5mm_500mm_SciD_6mm_Al_1e6mudecay.root";
   std::string file6Almu750 = "../../simdata/planar/planar_SMALL_2x5mm_750mm_SciD_6mm_Al_1e6mudecay.root";
   
   std::vector<std::string> Xfiles;
   std::vector<std::string> mufiles;
   
   Xfiles.push_back(file3Alx250);
   Xfiles.push_back(file3Alx500);
   Xfiles.push_back(file3Alx750);
   Xfiles.push_back(file6Alx250);
   Xfiles.push_back(file6Alx500);
   Xfiles.push_back(file6Alx750);
   
   mufiles.push_back(file3Almu250);
   mufiles.push_back(file3Almu500);
   mufiles.push_back(file3Almu750);
   mufiles.push_back(file6Almu250);
   mufiles.push_back(file6Almu500);
   mufiles.push_back(file6Almu750);



   //-------------------------------------------------------------------
   //                          Mu-decay
   //-------------------------------------------------------------------


   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m----------------------- Mu-decay -------------------------\033[0m" << std::endl;
   std::cout << "\033[1;35m----------------------------------------------------------\033[0m" << std::endl;


 
   for (int k = 0; k<mufiles.size(); k++) {
      TFile *fmu = new TFile(TString(mufiles[k]));
      
      TTree *tSciD1D = (TTree*)fmu->Get("Detector/SciDet1D"); // D-stream
      TTree *tSciD2D = (TTree*)fmu->Get("Detector/SciDet2D");
      TTree *tSciD3D = (TTree*)fmu->Get("Detector/SciDet3D");
      TTree *tSciD1U = (TTree*)fmu->Get("Detector/SciDet1U"); // U-stream
      TTree *tSciD2U = (TTree*)fmu->Get("Detector/SciDet2U");
      TTree *tSciD3U = (TTree*)fmu->Get("Detector/SciDet3U");
      
      float EventID,Edep; 

      tSciD1D->SetBranchAddress("EventID",&EventID); // D-stream 
      tSciD1D->SetBranchAddress("Edep",&Edep);
      tSciD2D->SetBranchAddress("EventID",&EventID);
      tSciD2D->SetBranchAddress("Edep",&Edep);
      tSciD3D->SetBranchAddress("EventID",&EventID);
      tSciD3D->SetBranchAddress("Edep",&Edep);
      tSciD1U->SetBranchAddress("EventID",&EventID); // U-stream 
      tSciD1U->SetBranchAddress("Edep",&Edep);
      tSciD2U->SetBranchAddress("EventID",&EventID);
      tSciD2U->SetBranchAddress("Edep",&Edep);
      tSciD3U->SetBranchAddress("EventID",&EventID);
      tSciD3U->SetBranchAddress("Edep",&Edep);
  
  
      //----------------------------------------------------------------
      //                          Writing
      //----------------------------------------------------------------


      std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;34m--------------------- Writing Loop " << k+1 << " ---------------------\033[0m" << std::endl;
      std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;

      
      // SciD1D 
      ofstream tmpSciD1D;
      tmpSciD1D.open(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD1D.txt"));
      tmpSciD1D << "EventID        Edep\n";
      for (int i=0; i<tSciD1D->GetEntries(); i++){
	     tSciD1D->GetEntry(i);
	     tmpSciD1D << EventID << " " << Edep << "\n";
	  }
      tmpSciD1D.close();
      std::cout << std::endl << "File: " << ((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD1D.txt" << " written!" << std::endl;

      
      // SciD2D
      ofstream tmpSciD2D;
      tmpSciD2D.open(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD2D.txt"));
      tmpSciD2D << "EventID        Edep\n";
      for (int i=0; i<tSciD2D->GetEntries(); i++){
	     tSciD2D->GetEntry(i);
	     tmpSciD2D << EventID << " " << Edep << "\n";
	  }
      tmpSciD2D.close();
      std::cout << std::endl << "File: " << ((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD2D.txt" << " written!" << std::endl;

      
      // SciD3D
      ofstream tmpSciD3D;
      tmpSciD3D.open(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD3D.txt"));
      tmpSciD3D << "EventID        Edep\n";
      for (int i=0; i<tSciD3D->GetEntries(); i++){
	     tSciD3D->GetEntry(i);
	     tmpSciD3D << EventID << " " << Edep << "\n";
	  }
      tmpSciD3D.close();
      std::cout << std::endl << "File: " << ((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD3D.txt" << " written!" << std::endl;
      
   
      // SciD1U 
      ofstream tmpSciD1U;
      tmpSciD1U.open(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD1U.txt"));
      tmpSciD1U << "EventID        Edep\n";
      for (int i=0; i<tSciD1U->GetEntries(); i++){
	     tSciD1U->GetEntry(i);
	     tmpSciD1U << EventID << " " << Edep << "\n";
	  }
      tmpSciD1U.close();
      std::cout << std::endl << "File: " << ((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD1U.txt" << " written!" << std::endl;

      
      // SciD2U
      ofstream tmpSciD2U;
      tmpSciD2U.open(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD2U.txt"));
      tmpSciD2U << "EventID        Edep\n";
      for (int i=0; i<tSciD2U->GetEntries(); i++){
	     tSciD2U->GetEntry(i);
	     tmpSciD2U << EventID << " " << Edep << "\n";
	  }
      tmpSciD2U.close();
      std::cout << std::endl << "File: " << ((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD2U.txt" << " written!" << std::endl;

      
      // SciD3U
      ofstream tmpSciD3U;
      tmpSciD3U.open(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD3U.txt"));
      tmpSciD3U << "EventID        Edep\n";
      for (int i=0; i<tSciD3U->GetEntries(); i++){
	     tSciD3U->GetEntry(i);
	     tmpSciD3U << EventID << " " << Edep << "\n";
	  }
      tmpSciD3U.close();
      std::cout << std::endl << "File: " << ((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD3U.txt" << " written!" << std::endl;
  
  
   
      //----------------------------------------------------------------
      //                          Rewriting
      //----------------------------------------------------------------
 
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Rewriting Loop " << k+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


 
      // SciD1D     
      std::ifstream inputSciD1D(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD1D.txt"));
      std::string lineSciD1D;
      std::getline(inputSciD1D, lineSciD1D);
     
      ifstream ifile1D(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD1D.txt"));
      if (ifile1D) {
         remove(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD1D.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD1D.txt" << " successfully removed!" << std::endl;
	  }
     
      ofstream finSciD1D;
      finSciD1D.open(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD1D.txt"));
      
      int ncounter1D = 1;
      while (!inputSciD1D.eof()) {
         double EvID1D, Edep1D;
	     inputSciD1D >> EvID1D >> Edep1D;
	     if (EvID1D == ncounter1D) {
		    finSciD1D << EvID1D << " " << Edep1D << "\n";
		    ncounter1D++;
	     } else {
		      int diff1D = EvID1D - ncounter1D;
		      for (int i=0; i<diff1D; i++) {
			     finSciD1D << ncounter1D+i << " " << 0.0 << "\n"; 
			  }
			  finSciD1D << EvID1D << " " << Edep1D << "\n";
		      ncounter1D = ncounter1D + diff1D + 1;
	     }   
      }
      finSciD1D.close();

      if ((remove(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD1D.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD1D.txt") << " generated! " << std::endl;
      }



      // SciD2D     
      std::ifstream inputSciD2D(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD2D.txt"));
      std::string lineSciD2D;
      std::getline(inputSciD2D, lineSciD2D);

      ifstream ifile2D(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD2D.txt"));
      if (ifile2D) {
         remove(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD2D.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD2D.txt" << " successfully removed!" << std::endl;
	  }
     
      ofstream finSciD2D;
      finSciD2D.open(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD2D.txt"));
      
      int ncounter2D = 1;
      while (!inputSciD2D.eof()) {
         double EvID2D, Edep2D;
	     inputSciD2D >> EvID2D >> Edep2D;
	     if (EvID2D == ncounter2D) {
		    finSciD2D << EvID2D << " " << Edep2D << "\n";
		    ncounter2D++;
	     } else {
		      int diff2D = EvID2D - ncounter2D;
		      for (int i=0; i<diff2D; i++) {
			     finSciD2D << ncounter2D+i << " " << 0.0 << "\n"; 
			  }
			  finSciD2D << EvID2D << " " << Edep2D << "\n";
		      ncounter2D = ncounter2D + diff2D + 1;
	     }   
      }
      finSciD2D.close();
      
      if ((remove(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD2D.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD2D.txt") << " generated! " << std::endl;
      }



      // SciD3D     
      std::ifstream inputSciD3D(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD3D.txt"));
      std::string lineSciD3D;
      std::getline(inputSciD3D, lineSciD3D);
     
      ifstream ifile3D(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD3D.txt"));
      if (ifile3D) {
         remove(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD3D.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD3D.txt" << " successfully removed!" << std::endl;
	  }
        
      ofstream finSciD3D;
      finSciD3D.open(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD3D.txt"));
      
      int ncounter3D = 1;
      while (!inputSciD3D.eof()) {
         double EvID3D, Edep3D;
	     inputSciD3D >> EvID3D >> Edep3D;
	     if (EvID3D == ncounter3D) {
		    finSciD3D << EvID3D << " " << Edep3D << "\n";
		    ncounter3D++;
	     } else {
		      int diff3D = EvID3D - ncounter3D;
		      for (int i=0; i<diff3D; i++) {
			     finSciD3D << ncounter3D+i << " " << 0.0 << "\n"; 
			  }
			  finSciD3D << EvID3D << " " << Edep3D << "\n";
		      ncounter3D = ncounter3D + diff3D + 1;
	     }   
      }
      finSciD3D.close();

      if ((remove(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD3D.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD3D.txt") << " generated! " << std::endl;
      }



      // SciD1U     
      std::ifstream inputSciD1U(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD1U.txt"));
      std::string lineSciD1U;
      std::getline(inputSciD1U, lineSciD1U);
     
      ifstream ifile1U(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD1U.txt"));
      if (ifile1U) {
         remove(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD1U.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD1U.txt" << " successfully removed!" << std::endl;
	  }
     
      ofstream finSciD1U;
      finSciD1U.open(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD1U.txt"));
      
      int ncounter1U = 1;
      while (!inputSciD1U.eof()) {
         double EvID1U, Edep1U;
	     inputSciD1U >> EvID1U >> Edep1U;
	     if (EvID1U == ncounter1U) {
		    finSciD1U << EvID1U << " " << Edep1U << "\n";
		    ncounter1U++;
	     } else {
		      int diff1U = EvID1U - ncounter1U;
		      for (int i=0; i<diff1U; i++) {
			     finSciD1U << ncounter1U+i << " " << 0.0 << "\n"; 
			  }
			  finSciD1U << EvID1U << " " << Edep1U << "\n";
		      ncounter1U = ncounter1U + diff1U + 1;
	     }   
      }
      finSciD1U.close();

      if ((remove(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD1U.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD1U.txt") << " generated! " << std::endl;
      }



      // SciD2U     
      std::ifstream inputSciD2U(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD2U.txt"));
      std::string lineSciD2U;
      std::getline(inputSciD2U, lineSciD2U);

      ifstream ifile2U(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD2U.txt"));
      if (ifile2U) {
         remove(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD2U.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD2U.txt" << " successfully removed!" << std::endl;
	  }
     
      ofstream finSciD2U;
      finSciD2U.open(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD2U.txt"));
      
      int ncounter2U = 1;
      while (!inputSciD2U.eof()) {
         double EvID2U, Edep2U;
	     inputSciD2U >> EvID2U >> Edep2U;
	     if (EvID2U == ncounter2U) {
		    finSciD2U << EvID2U << " " << Edep2U << "\n";
		    ncounter2U++;
	     } else {
		      int diff2U = EvID2U - ncounter2U;
		      for (int i=0; i<diff2U; i++) {
			     finSciD2U << ncounter2U+i << " " << 0.0 << "\n"; 
			  }
			  finSciD2U << EvID2U << " " << Edep2U << "\n";
		      ncounter2U = ncounter2U + diff2U + 1;
	     }   
      }
      finSciD2U.close();
      
      if ((remove(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD2U.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD2U.txt") << " generated! " << std::endl;
      }



      // SciD3U     
      std::ifstream inputSciD3U(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD3U.txt"));
      std::string lineSciD3U;
      std::getline(inputSciD3U, lineSciD3U);
     
      ifstream ifile3U(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD3U.txt"));
      if (ifile3U) {
         remove(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD3U.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD3U.txt" << " successfully removed!" << std::endl;
	  }
        
      ofstream finSciD3U;
      finSciD3U.open(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD3U.txt"));
      
      int ncounter3U = 1;
      while (!inputSciD3U.eof()) {
         double EvID3U, Edep3U;
	     inputSciD3U >> EvID3U >> Edep3U;
	     if (EvID3U == ncounter3U) {
		    finSciD3U << EvID3U << " " << Edep3U << "\n";
		    ncounter3U++;
	     } else {
		      int diff3U = EvID3U - ncounter3U;
		      for (int i=0; i<diff3U; i++) {
			     finSciD3U << ncounter3U+i << " " << 0.0 << "\n"; 
			  }
			  finSciD3U << EvID3U << " " << Edep3U << "\n";
		      ncounter3U = ncounter3U + diff3U + 1;
	     }   
      }
      finSciD3U.close();

      if ((remove(TString("../../simdata/planar/"+((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_tmpSciD3U.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(21,((mufiles[k]).find(".root"))-21))+"_SciD3U.txt") << " generated! " << std::endl;
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
      
      TTree *txSciD1D = (TTree*)fx->Get("Detector/SciDet1D"); // D-stream
      TTree *txSciD2D = (TTree*)fx->Get("Detector/SciDet2D");
      TTree *txSciD3D = (TTree*)fx->Get("Detector/SciDet3D");
      TTree *txSciD1U = (TTree*)fx->Get("Detector/SciDet1U"); // U-stream
      TTree *txSciD2U = (TTree*)fx->Get("Detector/SciDet2U");
      TTree *txSciD3U = (TTree*)fx->Get("Detector/SciDet3U");
      
      float EventID,Edep; 

      txSciD1D->SetBranchAddress("EventID",&EventID); // D-stream 
      txSciD1D->SetBranchAddress("Edep",&Edep);
      txSciD2D->SetBranchAddress("EventID",&EventID);
      txSciD2D->SetBranchAddress("Edep",&Edep);
      txSciD3D->SetBranchAddress("EventID",&EventID);
      txSciD3D->SetBranchAddress("Edep",&Edep);
      txSciD1U->SetBranchAddress("EventID",&EventID); // U-stream 
      txSciD1U->SetBranchAddress("Edep",&Edep);
      txSciD2U->SetBranchAddress("EventID",&EventID);
      txSciD2U->SetBranchAddress("Edep",&Edep);
      txSciD3U->SetBranchAddress("EventID",&EventID);
      txSciD3U->SetBranchAddress("Edep",&Edep);
  
  
      //----------------------------------------------------------------
      //                          Writing
      //----------------------------------------------------------------


      std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;34m--------------------- Writing Loop " << k+1 << " ---------------------\033[0m" << std::endl;
      std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;

      
      // SciD1D 
      ofstream tmpxSciD1D;
      tmpxSciD1D.open(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD1D.txt"));
      tmpxSciD1D << "EventID        Edep\n";
      for (int i=0; i<txSciD1D->GetEntries(); i++){
	     txSciD1D->GetEntry(i);
	     tmpxSciD1D << EventID << " " << Edep << "\n";
	  }
      tmpxSciD1D.close();
      std::cout << std::endl << "File: " << ((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD1D.txt" << " written!" << std::endl;

      
      // SciD2D
      ofstream tmpxSciD2D;
      tmpxSciD2D.open(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD2D.txt"));
      tmpxSciD2D << "EventID        Edep\n";
      for (int i=0; i<txSciD2D->GetEntries(); i++){
	     txSciD2D->GetEntry(i);
	     tmpxSciD2D << EventID << " " << Edep << "\n";
	  }
      tmpxSciD2D.close();
      std::cout << std::endl << "File: " << ((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD2D.txt" << " written!" << std::endl;

      
      // SciD3D
      ofstream tmpxSciD3D;
      tmpxSciD3D.open(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD3D.txt"));
      tmpxSciD3D << "EventID        Edep\n";
      for (int i=0; i<txSciD3D->GetEntries(); i++){
	     txSciD3D->GetEntry(i);
	     tmpxSciD3D << EventID << " " << Edep << "\n";
	  }
      tmpxSciD3D.close();
      std::cout << std::endl << "File: " << ((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD3D.txt" << " written!" << std::endl;
      
   
      // SciD1U 
      ofstream tmpxSciD1U;
      tmpxSciD1U.open(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD1U.txt"));
      tmpxSciD1U << "EventID        Edep\n";
      for (int i=0; i<txSciD1U->GetEntries(); i++){
	     txSciD1U->GetEntry(i);
	     tmpxSciD1U << EventID << " " << Edep << "\n";
	  }
      tmpxSciD1U.close();
      std::cout << std::endl << "File: " << ((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD1U.txt" << " written!" << std::endl;

      
      // SciD2U
      ofstream tmpxSciD2U;
      tmpxSciD2U.open(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD2U.txt"));
      tmpxSciD2U << "EventID        Edep\n";
      for (int i=0; i<txSciD2U->GetEntries(); i++){
	     txSciD2U->GetEntry(i);
	     tmpxSciD2U << EventID << " " << Edep << "\n";
	  }
      tmpxSciD2U.close();
      std::cout << std::endl << "File: " << ((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD2U.txt" << " written!" << std::endl;

      
      // SciD3U
      ofstream tmpxSciD3U;
      tmpxSciD3U.open(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD3U.txt"));
      tmpxSciD3U << "EventID        Edep\n";
      for (int i=0; i<txSciD3U->GetEntries(); i++){
	     txSciD3U->GetEntry(i);
	     tmpxSciD3U << EventID << " " << Edep << "\n";
	  }
      tmpxSciD3U.close();
      std::cout << std::endl << "File: " << ((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD3U.txt" << " written!" << std::endl;
  
  
   
      //----------------------------------------------------------------
      //                          Rewriting
      //----------------------------------------------------------------
 
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Rewriting Loop " << k+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


 
      // SciD1D     
      std::ifstream inputSciD1Dx(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD1D.txt"));
      std::string lineSciD1Dx;
      std::getline(inputSciD1Dx, lineSciD1Dx);
     
      ifstream ifile1Dx(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD1D.txt"));
      if (ifile1Dx) {
         remove(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD1D.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD1D.txt" << " successfully removed!" << std::endl;
	  }
     
      ofstream finSciD1Dx;
      finSciD1Dx.open(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD1D.txt"));
      
      int ncounter1Dx = 1;
      while (!inputSciD1Dx.eof()) {
         double EvID1Dx, Edep1Dx;
	     inputSciD1Dx >> EvID1Dx >> Edep1Dx;
	     if (EvID1Dx == ncounter1Dx) {
		    finSciD1Dx << EvID1Dx << " " << Edep1Dx << "\n";
		    ncounter1Dx++;
	     } else {
		      int diff1Dx = EvID1Dx - ncounter1Dx;
		      for (int i=0; i<diff1Dx; i++) {
			     finSciD1Dx << ncounter1Dx+i << " " << 0.0 << "\n"; 
			  }
			  finSciD1Dx << EvID1Dx << " " << Edep1Dx << "\n";
		      ncounter1Dx = ncounter1Dx + diff1Dx + 1;
	     }   
      }
      finSciD1Dx.close();

      if ((remove(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD1D.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD1D.txt") << " generated! " << std::endl;
      }



      // SciD2D     
      std::ifstream inputSciD2Dx(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD2D.txt"));
      std::string lineSciD2Dx;
      std::getline(inputSciD2Dx, lineSciD2Dx);

      ifstream ifile2Dx(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD2D.txt"));
      if (ifile2Dx) {
         remove(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD2D.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD2D.txt" << " successfully removed!" << std::endl;
	  }
     
      ofstream finSciD2Dx;
      finSciD2Dx.open(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD2D.txt"));
      
      int ncounter2Dx = 1;
      while (!inputSciD2Dx.eof()) {
         double EvID2Dx, Edep2Dx;
	     inputSciD2Dx >> EvID2Dx >> Edep2Dx;
	     if (EvID2Dx == ncounter2Dx) {
		    finSciD2Dx << EvID2Dx << " " << Edep2Dx << "\n";
		    ncounter2Dx++;
	     } else {
		      int diff2Dx = EvID2Dx - ncounter2Dx;
		      for (int i=0; i<diff2Dx; i++) {
			     finSciD2Dx << ncounter2Dx+i << " " << 0.0 << "\n"; 
			  }
			  finSciD2Dx << EvID2Dx << " " << Edep2Dx << "\n";
		      ncounter2Dx = ncounter2Dx + diff2Dx + 1;
	     }   
      }
      finSciD2Dx.close();
      
      if ((remove(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD2D.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD2D.txt") << " generated! " << std::endl;
      }



      // SciD3D     
      std::ifstream inputSciD3Dx(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD3D.txt"));
      std::string lineSciD3Dx;
      std::getline(inputSciD3Dx, lineSciD3Dx);
     
      ifstream ifile3Dx(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD3D.txt"));
      if (ifile3Dx) {
         remove(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD3D.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD3D.txt" << " successfully removed!" << std::endl;
	  }
        
      ofstream finSciD3Dx;
      finSciD3Dx.open(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD3D.txt"));
      
      int ncounter3Dx = 1;
      while (!inputSciD3Dx.eof()) {
         double EvID3Dx, Edep3Dx;
	     inputSciD3Dx >> EvID3Dx >> Edep3Dx;
	     if (EvID3Dx == ncounter3Dx) {
		    finSciD3Dx << EvID3Dx << " " << Edep3Dx << "\n";
		    ncounter3Dx++;
	     } else {
		      int diff3Dx = EvID3Dx - ncounter3Dx;
		      for (int i=0; i<diff3Dx; i++) {
			     finSciD3Dx << ncounter3Dx+i << " " << 0.0 << "\n"; 
			  }
			  finSciD3Dx << EvID3Dx << " " << Edep3Dx << "\n";
		      ncounter3Dx = ncounter3Dx + diff3Dx + 1;
	     }   
      }
      finSciD3Dx.close();

      if ((remove(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD3D.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD3D.txt") << " generated! " << std::endl;
      }



      // SciD1U     
      std::ifstream inputSciD1Ux(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD1U.txt"));
      std::string lineSciD1Ux;
      std::getline(inputSciD1Ux, lineSciD1Ux);
     
      ifstream ifile1Ux(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD1U.txt"));
      if (ifile1Ux) {
         remove(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD1U.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD1Ux.txt" << " successfully removed!" << std::endl;
	  }
     
      ofstream finSciD1Ux;
      finSciD1Ux.open(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD1U.txt"));
      
      int ncounter1Ux = 1;
      while (!inputSciD1Ux.eof()) {
         double EvID1Ux, Edep1Ux;
	     inputSciD1Ux >> EvID1Ux >> Edep1Ux;
	     if (EvID1Ux == ncounter1Ux) {
		    finSciD1Ux << EvID1Ux << " " << Edep1Ux << "\n";
		    ncounter1Ux++;
	     } else {
		      int diff1Ux = EvID1Ux - ncounter1Ux;
		      for (int i=0; i<diff1Ux; i++) {
			     finSciD1Ux << ncounter1Ux+i << " " << 0.0 << "\n"; 
			  }
			  finSciD1Ux << EvID1Ux << " " << Edep1Ux << "\n";
		      ncounter1Ux = ncounter1Ux + diff1Ux + 1;
	     }   
      }
      finSciD1Ux.close();

      if ((remove(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD1U.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD1U.txt") << " generated! " << std::endl;
      }



      // SciD2U     
      std::ifstream inputSciD2Ux(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD2U.txt"));
      std::string lineSciD2Ux;
      std::getline(inputSciD2Ux, lineSciD2Ux);

      ifstream ifile2Ux(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD2U.txt"));
      if (ifile2Ux) {
         remove(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD2U.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD2U.txt" << " successfully removed!" << std::endl;
	  }
     
      ofstream finSciD2Ux;
      finSciD2Ux.open(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD2U.txt"));
      
      int ncounter2Ux = 1;
      while (!inputSciD2Ux.eof()) {
         double EvID2Ux, Edep2Ux;
	     inputSciD2Ux >> EvID2Ux >> Edep2Ux;
	     if (EvID2Ux == ncounter2Ux) {
		    finSciD2Ux << EvID2Ux << " " << Edep2Ux << "\n";
		    ncounter2Ux++;
	     } else {
		      int diff2Ux = EvID2Ux - ncounter2Ux;
		      for (int i=0; i<diff2Ux; i++) {
			     finSciD2Ux << ncounter2Ux+i << " " << 0.0 << "\n"; 
			  }
			  finSciD2Ux << EvID2Ux << " " << Edep2Ux << "\n";
		      ncounter2Ux = ncounter2Ux + diff2Ux + 1;
	     }   
      }
      finSciD2Ux.close();
      
      if ((remove(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD2U.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD2U.txt") << " generated! " << std::endl;
      }



      // SciD3U     
      std::ifstream inputSciD3Ux(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD3U.txt"));
      std::string lineSciD3Ux;
      std::getline(inputSciD3Ux, lineSciD3Ux);
     
      ifstream ifile3Ux(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD3U.txt"));
      if (ifile3Ux) {
         remove(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD3Ux.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD3U.txt" << " successfully removed!" << std::endl;
	  }
        
      ofstream finSciD3Ux;
      finSciD3Ux.open(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD3U.txt"));
      
      int ncounter3Ux = 1;
      while (!inputSciD3Ux.eof()) {
         double EvID3Ux, Edep3Ux;
	     inputSciD3Ux >> EvID3Ux >> Edep3Ux;
	     if (EvID3Ux == ncounter3Ux) {
		    finSciD3Ux << EvID3Ux << " " << Edep3Ux << "\n";
		    ncounter3Ux++;
	     } else {
		      int diff3Ux = EvID3Ux - ncounter3Ux;
		      for (int i=0; i<diff3Ux; i++) {
			     finSciD3Ux << ncounter3Ux+i << " " << 0.0 << "\n"; 
			  }
			  finSciD3Ux << EvID3Ux << " " << Edep3Ux << "\n";
		      ncounter3Ux = ncounter3Ux + diff3Ux + 1;
	     }   
      }
      finSciD3Ux.close();

      if ((remove(TString("../../simdata/planar/"+((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_tmpxSciD3U.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(21,((Xfiles[k]).find(".root"))-21))+"_SciD3U.txt") << " generated! " << std::endl;
      }

 
   }





}


int main() {
   FileFillerPlanar();
   return 0;
}  
