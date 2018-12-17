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


void FileFillerRP(){	
	
   // Path name
   std::string path = "../../simdata/researchplan/";
   int pathL = path.length();
	
   // X-ray cascade
   std::string filex = path+"SciSphere_1e5goldcascade.root";
   // Mu-decay
   std::string filemu = path+"SciSphere_1e5mudecay.root";

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
			  
      TTree *tDetSphere = (TTree*)fmu->Get("Detector/DetSphere"); 
			  
	  float EventID,Edep; 

	  tDetSphere->SetBranchAddress("EventID",&EventID); 
	  tDetSphere->SetBranchAddress("Edep",&Edep);

		  
	  //----------------------------------------------------------------
	  //                          Writing
	  //----------------------------------------------------------------

	  std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
	  std::cout << "\033[1;34m--------------------- Writing Loop " << k+1 << " ---------------------\033[0m" << std::endl;
	  std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
	  
	  // DetSphere 
	  ofstream tmpDetSphere;
	  tmpDetSphere.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpDetSphere.txt"));
	  tmpDetSphere << "EventID        Edep\n";
	  for (int i=0; i<tDetSphere->GetEntries(); i++){
	     tDetSphere->GetEntry(i);
		 tmpDetSphere << EventID << " " << Edep << "\n";
	  }
	  tmpDetSphere.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpDetSphere.txt" << " written!" << std::endl;

	
						   
	  //----------------------------------------------------------------
	  //                          Rewriting
	  //----------------------------------------------------------------
		 
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m-------------------- Rewriting Loop " << k+1 << " --------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
		 
	  // DetSphere     
	  std::ifstream inputDetSphere(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpDetSphere.txt"));
	  std::string lineDetSphere;
	  std::getline(inputDetSphere, lineDetSphere);
			 
	  ifstream ifileDS(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_DetSphere.txt"));
	  if (ifileDS) {
	     remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_DetSphere.txt"));
	     std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_DetSphere.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finDetSphere;
	  finDetSphere.open(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_DetSphere.txt"));
			  
	  int ncounterDS = 1;
	  while (!inputDetSphere.eof()) {
	     double EvIDDS, EdepDS;
		 inputDetSphere >> EvIDDS >> EdepDS;
		 if (EvIDDS == ncounterDS) {
		    finDetSphere << EvIDDS << " " << EdepDS << "\n";
			ncounterDS++;
		 } else {
		    int diffDS = EvIDDS - ncounterDS;
			for (int i=0; i<diffDS; i++) {
			   finDetSphere << ncounterDS+i << " " << 0.0 << "\n"; 
			}
			finDetSphere << EvIDDS << " " << EdepDS << "\n";
			ncounterDS = ncounterDS + diffDS + 1;
		 }   
	  }
	  finDetSphere.close();

	  if ((remove(TString(path+((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_tmpDetSphere.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(pathL,((mufiles[k]).find(".root"))-pathL))+"_DetSphere.txt") << " generated! " << std::endl;
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
			  
	  TTree *txDetSphere = (TTree*)fx->Get("Detector/DetSphere");			  
	  float EventID,Edep; 

	  txDetSphere->SetBranchAddress("EventID",&EventID);  
	  txDetSphere->SetBranchAddress("Edep",&Edep);		  
		  
		  
	  //----------------------------------------------------------------
	  //                          Writing
	  //----------------------------------------------------------------

	  std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
	  std::cout << "\033[1;34m--------------------- Writing Loop " << k+1 << " ---------------------\033[0m" << std::endl;
	  std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
	  
	  // DetSphere 
	  ofstream tmpxDetSphere;
	  tmpxDetSphere.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxDetSphere.txt"));
	  tmpxDetSphere << "EventID        Edep\n";
	  for (int i=0; i<txDetSphere->GetEntries(); i++){
	     txDetSphere->GetEntry(i);
		 tmpxDetSphere << EventID << " " << Edep << "\n";
	  }
	  tmpxDetSphere.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxDetSphere.txt" << " written!" << std::endl;

		  
		   
	  //----------------------------------------------------------------
	  //                          Rewriting
	  //----------------------------------------------------------------
		 
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m-------------------- Rewriting Loop " << k+1 << " --------------------\033[0m" << std::endl;
	  std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

 
	  // DetSphere     
	  std::ifstream inputDetSpherex(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxDetSphere.txt"));
	  std::string lineDetSpherex;
	  std::getline(inputDetSpherex, lineDetSpherex);
			 
	  ifstream ifileDSx(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_DetSphere.txt"));
	  if (ifileDSx) {
	     remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_DetSphere.txt"));
		 std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_DetSphere.txt" << " successfully removed!" << std::endl;
	  }
			 
	  ofstream finDetSpherex;
	  finDetSpherex.open(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_DetSphere.txt"));
			  
	  int ncounterDSx = 1;
	  while (!inputDetSpherex.eof()) {
	     double EvIDDSx, EdepDSx;
		 inputDetSpherex >> EvIDDSx >> EdepDSx;
		 if (EvIDDSx == ncounterDSx) {
		    finDetSpherex << EvIDDSx << " " << EdepDSx << "\n";
			ncounterDSx++;
		 } else {
		    int diffDSx = EvIDDSx - ncounterDSx;
			for (int i=0; i<diffDSx; i++) {
			   finDetSpherex << ncounterDSx+i << " " << 0.0 << "\n"; 
			}
		    finDetSpherex << EvIDDSx << " " << EdepDSx << "\n";
		    ncounterDSx = ncounterDSx + diffDSx + 1;
	     }   
	  }
	  finDetSpherex.close();

	  if ((remove(TString(path+((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_tmpxDetSphere.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(pathL,((Xfiles[k]).find(".root"))-pathL))+"_DetSphere.txt") << " generated! " << std::endl;
	  }

		 
   }


}


int main() {
   FileFillerRP();
   return 0;
}  
