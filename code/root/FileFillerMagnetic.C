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


void FileFillerMagnetic(){	
	
   // X-ray cascade
   //std::string filex = "../../simdata/magnetic/Bfield_5T_simple_4mm_Al_det_BGO1e6goldcascade.root";
   std::string filex = "../../simdata/magnetic/Bfield_5T_simple_4mm_Al_det_NaI1e6goldcascade.root";
   // Mu-decay
   //std::string filemu = "../../simdata/magnetic/Bfield_5T_simple_4mm_Al_det_BGO1e6mudecay.root";
   std::string filemu = "../../simdata/magnetic/Bfield_5T_simple_4mm_Al_det_NaI1e6mudecay.root";
   
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
      
      TTree *tTubeD = (TTree*)fmu->Get("Detector/TubeDet");
      float EventID,Edep; 

      tTubeD->SetBranchAddress("EventID",&EventID); // D-stream 
      tTubeD->SetBranchAddress("Edep",&Edep);
      
  
      //----------------------------------------------------------------
      //                          Writing
      //----------------------------------------------------------------


      std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;34m--------------------- Writing Loop " << k+1 << " ---------------------\033[0m" << std::endl;
      std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;

      
      // TubeD
      ofstream tmpTubeD;
      tmpTubeD.open(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpTubeD.txt"));
      tmpTubeD << "EventID        Edep\n";
      for (int i=0; i < tTubeD->GetEntries(); i++) {
	     tTubeD->GetEntry(i);
	     tmpTubeD << EventID << " " << Edep << "\n";
	  }
	  tmpTubeD.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpTubeD.txt" << " written!" << std::endl;
      
        
      //----------------------------------------------------------------
      //                          Rewriting
      //----------------------------------------------------------------
 
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Rewriting Loop " << k+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;



      // TubeD
      std::ifstream inputTubeD(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpTubeD.txt"));
      std::string lineTubeD;
      std::getline(inputTubeD, lineTubeD);
      
      ifstream ifileTD(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpTubeD.txt"));
      if (ifileTD) {
	     remove(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_TubeD.txt"));
	     std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_TubeD.txt" << " successfully removed!" << std::endl;
	  }
	  
	  ofstream finTubeD;
	  finTubeD.open(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_TubeD.txt"));
	  
	  int ncounterTD = 1;
	  while (!inputTubeD.eof()) {
	     double EvIDTD, EdepTD;
	     inputTubeD >> EvIDTD >> EdepTD;
	     if (EvIDTD == ncounterTD) {
		    finTubeD << EvIDTD << " " << EdepTD << "\n";
		    ncounterTD++;
		 } else {
	          int diffTD = EvIDTD - ncounterTD;
	          for (int i=0; i<diffTD; i++) {
			     finTubeD << ncounterTD+i << " " << 0.0 << "\n";
			  }
			  finTubeD << EvIDTD << " " << EdepTD << "\n";
			  ncounterTD = ncounterTD + diffTD + 1;
		 }
      }
      finTubeD.close();
    
      if ((remove(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpTubeD.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_TubeD.txt") << " generated! " << std::endl;
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

      TTree *txTubeD = (TTree*)fx->Get("Detector/TubeDet");
      
      float EventID,Edep; 

      txTubeD->SetBranchAddress("EventID",&EventID); 
      txTubeD->SetBranchAddress("Edep",&Edep);
  
  
      //----------------------------------------------------------------
      //                          Writing
      //----------------------------------------------------------------


      std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;34m--------------------- Writing Loop " << k+1 << " ---------------------\033[0m" << std::endl;
      std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;

  
      // TubeD
      ofstream tmpxTubeD;
      tmpxTubeD.open(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxTubeD.txt"));
      tmpxTubeD << "EventID        Edep\n";
      for (int i=0; i < txTubeD->GetEntries(); i++) {
	     txTubeD->GetEntry(i);
	     tmpxTubeD << EventID << " " << Edep << "\n";
	  }
	  tmpxTubeD.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxTubeD.txt" << " written!" << std::endl;
	  
      
   
      //----------------------------------------------------------------
      //                          Rewriting
      //----------------------------------------------------------------
 
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Rewriting Loop " << k+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;



      // TubeD
      std::ifstream inputTubeDx(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxTubeD.txt"));
      std::string lineTubeDx;
      std::getline(inputTubeDx, lineTubeDx);
      
      ifstream ifileTDx(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxTubeD.txt"));
      if (ifileTDx) {
	     remove(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_TubeD.txt"));
	     std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_TubeD.txt" << " successfully removed!" << std::endl;
	  }

      ofstream finTubeTDx;
      finTubeTDx.open(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_TubeD.txt"));
      
      int ncounterTDx = 1;
      while (!inputTubeDx.eof()) {
	     double EvIDTDx, EdepTDx;
	     inputTubeDx >> EvIDTDx >> EdepTDx;
	     if (EvIDTDx == ncounterTDx) {
	        finTubeTDx << EvIDTDx << " " << EdepTDx << "\n";
	        ncounterTDx++;
	     } else {
			 int diffTDx = EvIDTDx - ncounterTDx;
			 for (int i=0; i < diffTDx; i++) {
			    finTubeTDx << ncounterTDx+i << " " << 0.0 << "\n";
			 }
			 finTubeTDx << EvIDTDx << " " << EdepTDx << "\n";
			 ncounterTDx = ncounterTDx + diffTDx + 1;
		 }
	  }	     
      finTubeTDx.close();
      
      if ((remove(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxTubeD.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_TubeD.txt") << " generated! " << std::endl;
      }

  
   }





}


int main() {
   FileFillerMagnetic();
   return 0;
}  
