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


void FileFiller(){	
	
   // Mu-decay with {250,500,750}-mm SciD3 3-mm Al
   std::string filemu250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filemu500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   std::string filemu750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root";
   // Mu-decay with {250,500,750}-mm SciD3 6-mm Al
   std::string file6Almu250 = "../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Almu500 = "../../simdata/bubble4/bubble_2x5mm_500mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   std::string file6Almu750 = "../../simdata/bubble4/bubble_2x5mm_750mm_SciD_Nevts_SciSphere_6mm_Al_1e6mudecay.root";
   
   std::vector<std::string> mufiles;
   mufiles.push_back(filemu250);
   mufiles.push_back(filemu500);
   mufiles.push_back(filemu750);
   mufiles.push_back(file6Almu250);
   mufiles.push_back(file6Almu500);
   mufiles.push_back(file6Almu750);

   
   for (int k = 0; k<mufiles.size(); k++) {
      TFile *fmu = new TFile(TString(mufiles[k]));
      
      TTree *tSciD1 = (TTree*)fmu->Get("Detector/SciDet1");
      TTree *tSciD2 = (TTree*)fmu->Get("Detector/SciDet2");
      TTree *tSciD3 = (TTree*)fmu->Get("Detector/SciDet3");

      float EventID,Edep; 

      tSciD1->SetBranchAddress("EventID",&EventID); 
      tSciD1->SetBranchAddress("Edep",&Edep);
      tSciD2->SetBranchAddress("EventID",&EventID);
      tSciD2->SetBranchAddress("Edep",&Edep);
      tSciD3->SetBranchAddress("EventID",&EventID);
      tSciD3->SetBranchAddress("Edep",&Edep);
  
      //----------------------------------------------------------------
      //                          Writing
      //----------------------------------------------------------------


      std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;34m--------------------- Writing Loop " << k+1 << " ---------------------\033[0m" << std::endl;
      std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;

      
      // SciD1 
      ofstream tmpSciD1;
      tmpSciD1.open(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD1.txt"));
      tmpSciD1 << "EventID        Edep\n";
      for (int i=0; i<tSciD1->GetEntries(); i++){
	     tSciD1->GetEntry(i);
	     tmpSciD1 << EventID << " " << Edep << "\n";
	  }
      tmpSciD1.close();
      std::cout << std::endl << "File: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD1.txt" << " written!" << std::endl;

      
      // SciD2
      ofstream tmpSciD2;
      tmpSciD2.open(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD2.txt"));
      tmpSciD1 << "EventID        Edep\n";
      for (int i=0; i<tSciD2->GetEntries(); i++){
	     tSciD2->GetEntry(i);
	     tmpSciD2 << EventID << " " << Edep << "\n";
	  }
      tmpSciD2.close();
      std::cout << std::endl << "File: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD2.txt" << " written!" << std::endl;

      
      // SciD3
      ofstream tmpSciD3;
      tmpSciD3.open(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD3.txt"));
      tmpSciD3 << "EventID        Edep\n";
      for (int i=0; i<tSciD3->GetEntries(); i++){
	     tSciD3->GetEntry(i);
	     tmpSciD3 << EventID << " " << Edep << "\n";
	  }
      tmpSciD3.close();
      std::cout << std::endl << "File: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD3.txt" << " written!" << std::endl;
      
   
   
      //----------------------------------------------------------------
      //                          Rewriting
      //----------------------------------------------------------------
 
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Rewriting Loop " << k+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;


 
      // SciD1     
      std::ifstream inputSciD1(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD1.txt"));
      std::string lineSciD1;
      std::getline(inputSciD1, lineSciD1);
     
      ifstream ifile1(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD1.txt"));
      if (ifile1) {
         remove(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD1.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD1.txt" << " successfully removed!" << std::endl;
	  }
     
      ofstream finSciD1;
      finSciD1.open(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD1.txt"));
      
      int ncounter1 = 1;
      while (!inputSciD1.eof()) {
         double EvID1, Edep1;
	     inputSciD1 >> EvID1 >> Edep1;
	     if (EvID1 == ncounter1) {
		    finSciD1 << EvID1 << " " << Edep1 << "\n";
		    ncounter1++;
	     } else {
		      int diff1 = EvID1 - ncounter1;
		      for (int i=0; i<diff1; i++) {
			     finSciD1 << ncounter1+i << " " << 0.0 << "\n"; 
			  }
			  finSciD1 << EvID1 << " " << Edep1 << "\n";
		      ncounter1 = ncounter1 + diff1 + 1;
	     }   
      }
      finSciD1.close();

      if ((remove(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD1.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD1.txt") << " generated! " << std::endl;
      }



      // SciD2     
      std::ifstream inputSciD2(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD2.txt"));
      std::string lineSciD2;
      std::getline(inputSciD2, lineSciD2);

      ifstream ifile2(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD2.txt"));
      if (ifile2) {
         remove(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD2.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD2.txt" << " successfully removed!" << std::endl;
	  }
     
      ofstream finSciD2;
      finSciD2.open(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD2.txt"));
      
      int ncounter2 = 1;
      while (!inputSciD2.eof()) {
         double EvID2, Edep2;
	     inputSciD2 >> EvID2 >> Edep2;
	     if (EvID2 == ncounter2) {
		    finSciD2 << EvID2 << " " << Edep2 << "\n";
		    ncounter2++;
	     } else {
		      int diff2 = EvID2 - ncounter2;
		      for (int i=0; i<diff2; i++) {
			     finSciD2 << ncounter2+i << " " << 0.0 << "\n"; 
			  }
			  finSciD2 << EvID2 << " " << Edep2 << "\n";
		      ncounter2 = ncounter2 + diff2 + 1;
	     }   
      }
      finSciD2.close();
      
      if ((remove(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD2.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD2.txt") << " generated! " << std::endl;
      }



      // SciD3     
      std::ifstream inputSciD3(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD3.txt"));
      std::string lineSciD3;
      std::getline(inputSciD3, lineSciD3);
     
      ifstream ifile3(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD3.txt"));
      if (ifile3) {
         remove(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD3.txt"));
         std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD3.txt" << " successfully removed!" << std::endl;
	  }
        
      ofstream finSciD3;
      finSciD3.open(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD3.txt"));
      
      int ncounter3 = 1;
      while (!inputSciD3.eof()) {
         double EvID3, Edep3;
	     inputSciD3 >> EvID3 >> Edep3;
	     if (EvID3 == ncounter3) {
		    finSciD3 << EvID3 << " " << Edep3 << "\n";
		    ncounter3++;
	     } else {
		      int diff3 = EvID3 - ncounter3;
		      for (int i=0; i<diff3; i++) {
			     finSciD3 << ncounter3+i << " " << 0.0 << "\n"; 
			  }
			  finSciD3 << EvID3 << " " << Edep3 << "\n";
		      ncounter3 = ncounter3 + diff3 + 1;
	     }   
      }
      finSciD3.close();

      if ((remove(TString("../../simdata/bubble4/"+((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_tmpSciD3.txt"))) == 0) {
         std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(22,((mufiles[k]).find(".root"))-22))+"_SciD3.txt") << " generated! " << std::endl;
      }


 
 
   }


}


int main() {
   FileFiller();
   return 0;
}  
