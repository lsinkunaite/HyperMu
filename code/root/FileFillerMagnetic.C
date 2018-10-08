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
   std::string filex = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5goldcascade.root";
   // Mu-decay
   std::string filemu = "../../simdata/magnetic/adBfield_5T_SDFInx2_2mm_Al_det_BGO1e5mudecay.root";
   
   
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
      
      //TTree *tSciDF = (TTree*)fmu->Get("Detector/SciDetFront");
      TTree *tSciDFIn1 = (TTree*)fmu->Get("Detector/H2BoxSciDetFrontIn1");
      TTree *tSciDFIn2 = (TTree*)fmu->Get("Detector/H2BoxSciDetFrontIn2");
      TTree *tTubeD = (TTree*)fmu->Get("Detector/TubeDet");
      TTree *tSciDE = (TTree*)fmu->Get("Detector/SciDetEnd");
      
      float EventID,Edep; 

      tSciDFIn1->SetBranchAddress("EventID",&EventID);
      tSciDFIn1->SetBranchAddress("Edep",&Edep);
      tSciDFIn2->SetBranchAddress("EventID",&EventID);
      tSciDFIn2->SetBranchAddress("Edep",&Edep);
      //tSciDF->SetBranchAddress("EventID",&EventID);
      //tSciDF->SetBranchAddress("Edep",&Edep);
      tTubeD->SetBranchAddress("EventID",&EventID);
      tTubeD->SetBranchAddress("Edep",&Edep);
      tSciDE->SetBranchAddress("EventID",&EventID);
      tSciDE->SetBranchAddress("Edep",&Edep);
  
      //----------------------------------------------------------------
      //                          Writing
      //----------------------------------------------------------------


      std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;34m--------------------- Writing Loop " << k+1 << " ---------------------\033[0m" << std::endl;
      std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;

/*      
      // SciDF
      ofstream tmpSciDF;
      tmpSciDF.open(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDF.txt"));
      tmpSciDF << "EventID        Edep\n";
      for (int i=0; i < tSciDF->GetEntries(); i++) {
	     tSciDF->GetEntry(i);
	     tmpSciDF << EventID << " " << Edep << "\n";
	  }
	  tmpSciDF.close();
      std::cout << std::endl << "File: " << ((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDF.txt" << " written!" << std::endl;
*/      

      // SciDFIn1
      ofstream tmpSciDFIn1;
      tmpSciDFIn1.open(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDFIn1.txt"));
      tmpSciDFIn1 << "EventID        Edep\n";
      for (int i=0; i < tSciDFIn1->GetEntries(); i++) {
	     tSciDFIn1->GetEntry(i);
	     tmpSciDFIn1 << EventID << " " << Edep << "\n";
	  }
	  tmpSciDFIn1.close();
      std::cout << std::endl << "File: " << ((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDFIn1.txt" << " written!" << std::endl;


      // SciDFIn2
      ofstream tmpSciDFIn2;
      tmpSciDFIn2.open(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDFIn2.txt"));
      tmpSciDFIn2 << "EventID        Edep\n";
      for (int i=0; i < tSciDFIn2->GetEntries(); i++) {
	     tSciDFIn2->GetEntry(i);
	     tmpSciDFIn2 << EventID << " " << Edep << "\n";
	  }
	  tmpSciDFIn2.close();
      std::cout << std::endl << "File: " << ((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDFIn2.txt" << " written!" << std::endl;


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

      // SciDE
      ofstream tmpSciDE;
      tmpSciDE.open(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDE.txt"));
      tmpSciDE << "EventID        Edep\n";
      for (int i=0; i < tSciDE->GetEntries(); i++) {
	     tSciDE->GetEntry(i);
	     tmpSciDE << EventID << " " << Edep << "\n";
	  }
	  tmpSciDE.close();
	  std::cout << std::endl << "File: " << ((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDE.txt" << " written!" << std::endl;

      
        
      //----------------------------------------------------------------
      //                          Rewriting
      //----------------------------------------------------------------
 
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Rewriting Loop " << k+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

/*
      // SciDF
      std::ifstream inputSciDF(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDF.txt"));
      std::string lineSciDF;
      std::getline(inputSciDF, lineSciDF);
      
      ifstream ifileSDF(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDF.txt"));
      if (ifileSDF) {
	     remove(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDF.txt"));
	     std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDF.txt" << " successfully removed!" << std::endl;
	  }
	  
	  ofstream finSciDF;
	  finSciDF.open(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDF.txt"));
	  
	  int ncounterSDF = 1;
	  while (!inputSciDF.eof()) {
	     double EvIDSDF, EdepSDF;
	     inputSciDF >> EvIDSDF >> EdepSDF;
	     if (EvIDSDF == ncounterSDF) {
		    finSciDF << EvIDSDF << " " << EdepSDF << "\n";
		    ncounterSDF++;
		 } else {
	          int diffSDF = EvIDSDF - ncounterSDF;
	          for (int i=0; i<diffSDF; i++) {
			     finSciDF << ncounterSDF+i << " " << 0.0 << "\n";
			  }
			  finSciDF << EvIDSDF << " " << EdepSDF << "\n";
			  ncounterSDF = ncounterSDF + diffSDF + 1;
		 }
      }
      finSciDF.close();
    
      if ((remove(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDF.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDF.txt") << " generated! " << std::endl;
	  }     
*/

      // SciDFIn1
      std::ifstream inputSciDFIn1(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDFIn1.txt"));
      std::string lineSciDFIn1;
      std::getline(inputSciDFIn1, lineSciDFIn1);
      
      ifstream ifileSDFIn1(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDFIn1.txt"));
      if (ifileSDFIn1) {
	     remove(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDFIn1.txt"));
	     std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDFIn1.txt" << " successfully removed!" << std::endl;
	  }
	  
	  ofstream finSciDFIn1;
	  finSciDFIn1.open(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDFIn1.txt"));
	  
	  int ncounterSDFIn1 = 1;
	  while (!inputSciDFIn1.eof()) {
	     double EvIDSDFIn1, EdepSDFIn1;
	     inputSciDFIn1 >> EvIDSDFIn1 >> EdepSDFIn1;
	     if (EvIDSDFIn1 == ncounterSDFIn1) {
		    finSciDFIn1 << EvIDSDFIn1 << " " << EdepSDFIn1 << "\n";
		    ncounterSDFIn1++;
		 } else {
	          int diffSDFIn1 = EvIDSDFIn1 - ncounterSDFIn1;
	          for (int i=0; i<diffSDFIn1; i++) {
			     finSciDFIn1 << ncounterSDFIn1+i << " " << 0.0 << "\n";
			  }
			  finSciDFIn1 << EvIDSDFIn1 << " " << EdepSDFIn1 << "\n";
			  ncounterSDFIn1 = ncounterSDFIn1 + diffSDFIn1 + 1;
		 }
      }
      finSciDFIn1.close();
    
      if ((remove(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDFIn1.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDFIn1.txt") << " generated! " << std::endl;
	  }     


      // SciDFIn2
      std::ifstream inputSciDFIn2(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDFIn2.txt"));
      std::string lineSciDFIn2;
      std::getline(inputSciDFIn2, lineSciDFIn2);
      
      ifstream ifileSDFIn2(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDFIn2.txt"));
      if (ifileSDFIn2) {
	     remove(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDFIn2.txt"));
	     std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDFIn2.txt" << " successfully removed!" << std::endl;
	  }
	  
	  ofstream finSciDFIn2;
	  finSciDFIn2.open(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDFIn2.txt"));
	  
	  int ncounterSDFIn2 = 1;
	  while (!inputSciDFIn2.eof()) {
	     double EvIDSDFIn2, EdepSDFIn2;
	     inputSciDFIn2 >> EvIDSDFIn2 >> EdepSDFIn2;
	     if (EvIDSDFIn2 == ncounterSDFIn2) {
		    finSciDFIn2 << EvIDSDFIn2 << " " << EdepSDFIn2 << "\n";
		    ncounterSDFIn2++;
		 } else {
	          int diffSDFIn2 = EvIDSDFIn2 - ncounterSDFIn2;
	          for (int i=0; i<diffSDFIn2; i++) {
			     finSciDFIn2 << ncounterSDFIn2+i << " " << 0.0 << "\n";
			  }
			  finSciDFIn2 << EvIDSDFIn2 << " " << EdepSDFIn2 << "\n";
			  ncounterSDFIn2 = ncounterSDFIn2 + diffSDFIn2 + 1;
		 }
      }
      finSciDFIn2.close();
    
      if ((remove(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDFIn2.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDFIn2.txt") << " generated! " << std::endl;
	  }     


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


      // SciDE
      std::ifstream inputSciDE(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDE.txt"));
      std::string lineSciDE;
      std::getline(inputSciDE, lineSciDE);
      
      ifstream ifileSDE(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDE.txt"));
      if (ifileSDE) {
	     remove(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDE.txt"));
	     std::cout << std::endl << "Previously existing output file: " << ((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDE.txt" << " successfully removed!" << std::endl;
	  }
	  
	  ofstream finSciDE;
	  finSciDE.open(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDE.txt"));
	  
	  int ncounterSDE = 1;
	  while (!inputSciDE.eof()) {
	     double EvIDSDE, EdepSDE;
	     inputSciDE >> EvIDSDE >> EdepSDE;
	     if (EvIDSDE == ncounterSDE) {
		    finSciDE << EvIDSDE << " " << EdepSDE << "\n";
		    ncounterSDE++;
		 } else {
	          int diffSDE = EvIDSDE - ncounterSDE;
	          for (int i=0; i<diffSDE; i++) {
			     finSciDE << ncounterSDE+i << " " << 0.0 << "\n";
			  }
			  finSciDE << EvIDSDE << " " << EdepSDE << "\n";
			  ncounterSDE = ncounterSDE + diffSDE + 1;
		 }
      }
      finSciDE.close();
    
      if ((remove(TString("../../simdata/magnetic/"+((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_tmpSciDE.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((mufiles[k]).substr(23,((mufiles[k]).find(".root"))-23))+"_SciDE.txt") << " generated! " << std::endl;
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

      //TTree *txSciDF = (TTree*)fx->Get("Detector/SciDetFront");
      TTree *txSciDFIn1 = (TTree*)fx->Get("Detector/H2BoxSciDetFrontIn1");
      TTree *txSciDFIn2 = (TTree*)fx->Get("Detector/H2BoxSciDetFrontIn2");
      TTree *txTubeD = (TTree*)fx->Get("Detector/TubeDet");
      TTree *txSciDE = (TTree*)fx->Get("Detector/SciDetEnd");
      
      float EventID,Edep; 

      txSciDFIn1->SetBranchAddress("EventID",&EventID);
      txSciDFIn1->SetBranchAddress("Edep",&Edep);
      txSciDFIn2->SetBranchAddress("EventID",&EventID);
      txSciDFIn2->SetBranchAddress("Edep",&Edep);
      //txSciDF->SetBranchAddress("EventID",&EventID);
      //txSciDF->SetBranchAddress("Edep",&Edep);
      txTubeD->SetBranchAddress("EventID",&EventID); 
      txTubeD->SetBranchAddress("Edep",&Edep);
      txSciDE->SetBranchAddress("EventID",&EventID);
      txSciDE->SetBranchAddress("Edep",&Edep);
  
  
      //----------------------------------------------------------------
      //                          Writing
      //----------------------------------------------------------------


      std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;34m--------------------- Writing Loop " << k+1 << " ---------------------\033[0m" << std::endl;
      std::cout << "\033[1;34m----------------------------------------------------------\033[0m" << std::endl;

/*  
      // SciDF
      ofstream tmpxSciDF;
      tmpxSciDF.open(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDF.txt"));
      tmpxSciDF << "EventID        Edep\n";
      for (int i=0; i < txSciDF->GetEntries(); i++) {
	     txSciDF->GetEntry(i);
	     tmpxSciDF << EventID << " " << Edep << "\n";
	  }
	  tmpxSciDF.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDF.txt" << " written!" << std::endl;
*/
      // SciDFIn1
      ofstream tmpxSciDFIn1;
      tmpxSciDFIn1.open(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDFIn1.txt"));
      tmpxSciDFIn1 << "EventID        Edep\n";
      for (int i=0; i < txSciDFIn1->GetEntries(); i++) {
	     txSciDFIn1->GetEntry(i);
	     tmpxSciDFIn1 << EventID << " " << Edep << "\n";
	  }
	  tmpxSciDFIn1.close();
      std::cout << std::endl << "File: " << ((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDFIn1.txt" << " written!" << std::endl;

      // SciDFIn2
      ofstream tmpxSciDFIn2;
      tmpxSciDFIn2.open(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDFIn2.txt"));
      tmpxSciDFIn2 << "EventID        Edep\n";
      for (int i=0; i < txSciDFIn2->GetEntries(); i++) {
	     txSciDFIn2->GetEntry(i);
	     tmpxSciDFIn2 << EventID << " " << Edep << "\n";
	  }
	  tmpxSciDFIn2.close();
      std::cout << std::endl << "File: " << ((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDFIn2.txt" << " written!" << std::endl;
	   
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
	  
	  // SciDE
      ofstream tmpxSciDE;
      tmpxSciDE.open(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDE.txt"));
      tmpxSciDE << "EventID        Edep\n";
      for (int i=0; i < txSciDE->GetEntries(); i++) {
	     txSciDE->GetEntry(i);
	     tmpxSciDE << EventID << " " << Edep << "\n";
	  }
	  tmpxSciDE.close();
	  std::cout << std::endl << "File: " << ((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDE.txt" << " written!" << std::endl;
	  
      
   
      //----------------------------------------------------------------
      //                          Rewriting
      //----------------------------------------------------------------
 
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m-------------------- Rewriting Loop " << k+1 << " --------------------\033[0m" << std::endl;
      std::cout << "\033[1;31m----------------------------------------------------------\033[0m" << std::endl;

/*
      // SciDF
      std::ifstream inputSciDFx(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDF.txt"));
      std::string lineSciDFx;
      std::getline(inputSciDFx, lineSciDFx);
      
      ifstream ifileSDFx(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDF.txt"));
      if (ifileSDFx) {
	     remove(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDF.txt"));
	     std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDF.txt" << " successfully removed!" << std::endl;
	  }

      ofstream finSciDFx;
      finSciDFx.open(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDF.txt"));
      
      int ncounterSDFx = 1;
      while (!inputSciDFx.eof()) {
	     double EvIDSDFx, EdepSDFx;
	     inputSciDFx >> EvIDSDFx >> EdepSDFx;
	     if (EvIDSDFx == ncounterSDFx) {
	        finSciDFx << EvIDSDFx << " " << EdepSDFx << "\n";
	        ncounterSDFx++;
	     } else {
			 int diffSDFx = EvIDSDFx - ncounterSDFx;
			 for (int i=0; i < diffSDFx; i++) {
			    finSciDFx << ncounterSDFx+i << " " << 0.0 << "\n";
			 }
			 finSciDFx << EvIDSDFx << " " << EdepSDFx << "\n";
			 ncounterSDFx = ncounterSDFx + diffSDFx + 1;
		 }
	  }	     
      finSciDFx.close();
      
      if ((remove(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDF.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDF.txt") << " generated! " << std::endl;
      }
*/

      // SciDFIn1
      std::ifstream inputSciDFIn1x(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDFIn1.txt"));
      std::string lineSciDFIn1x;
      std::getline(inputSciDFIn1x, lineSciDFIn1x);
      
      ifstream ifileSDFIn1x(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDFIn1.txt"));
      if (ifileSDFIn1x) {
	     remove(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDFIn1.txt"));
	     std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDFIn1.txt" << " successfully removed!" << std::endl;
	  }

      ofstream finSciDFIn1x;
      finSciDFIn1x.open(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDFIn1.txt"));
      
      int ncounterSDFIn1x = 1;
      while (!inputSciDFIn1x.eof()) {
	     double EvIDSDFIn1x, EdepSDFIn1x;
	     inputSciDFIn1x >> EvIDSDFIn1x >> EdepSDFIn1x;
	     if (EvIDSDFIn1x == ncounterSDFIn1x) {
	        finSciDFIn1x << EvIDSDFIn1x << " " << EdepSDFIn1x << "\n";
	        ncounterSDFIn1x++;
	     } else {
			 int diffSDFIn1x = EvIDSDFIn1x - ncounterSDFIn1x;
			 for (int i=0; i < diffSDFIn1x; i++) {
			    finSciDFIn1x << ncounterSDFIn1x+i << " " << 0.0 << "\n";
			 }
			 finSciDFIn1x << EvIDSDFIn1x << " " << EdepSDFIn1x << "\n";
			 ncounterSDFIn1x = ncounterSDFIn1x + diffSDFIn1x + 1;
		 }
	  }	     
      finSciDFIn1x.close();
      
      if ((remove(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDFIn1.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDFIn1.txt") << " generated! " << std::endl;
      }


      // SciDFIn2
      std::ifstream inputSciDFIn2x(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDFIn2.txt"));
      std::string lineSciDFIn2x;
      std::getline(inputSciDFIn2x, lineSciDFIn2x);
      
      ifstream ifileSDFIn2x(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDFIn2.txt"));
      if (ifileSDFIn2x) {
	     remove(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDFIn2.txt"));
	     std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDFIn2.txt" << " successfully removed!" << std::endl;
	  }

      ofstream finSciDFIn2x;
      finSciDFIn2x.open(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDFIn2.txt"));
      
      int ncounterSDFIn2x = 1;
      while (!inputSciDFIn2x.eof()) {
	     double EvIDSDFIn2x, EdepSDFIn2x;
	     inputSciDFIn2x >> EvIDSDFIn2x >> EdepSDFIn2x;
	     if (EvIDSDFIn2x == ncounterSDFIn2x) {
	        finSciDFIn2x << EvIDSDFIn2x << " " << EdepSDFIn2x << "\n";
	        ncounterSDFIn2x++;
	     } else {
			 int diffSDFIn2x = EvIDSDFIn2x - ncounterSDFIn2x;
			 for (int i=0; i < diffSDFIn2x; i++) {
			    finSciDFIn2x << ncounterSDFIn2x+i << " " << 0.0 << "\n";
			 }
			 finSciDFIn2x << EvIDSDFIn2x << " " << EdepSDFIn2x << "\n";
			 ncounterSDFIn2x = ncounterSDFIn2x + diffSDFIn2x + 1;
		 }
	  }	     
      finSciDFIn2x.close();
      
      if ((remove(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDFIn2.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDFIn2.txt") << " generated! " << std::endl;
      }


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


      // SciDE
      std::ifstream inputSciDEx(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDE.txt"));
      std::string lineSciDEx;
      std::getline(inputSciDEx, lineSciDEx);
      
      ifstream ifileSDEx(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDE.txt"));
      if (ifileSDEx) {
	     remove(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDE.txt"));
	     std::cout << std::endl << "Previously existing output file: " << ((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDE.txt" << " successfully removed!" << std::endl;
	  }

      ofstream finSciDEx;
      finSciDEx.open(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDE.txt"));
      
      int ncounterSDEx = 1;
      while (!inputSciDEx.eof()) {
	     double EvIDSDEx, EdepSDEx;
	     inputSciDEx >> EvIDSDEx >> EdepSDEx;
	     if (EvIDSDEx == ncounterSDEx) {
	        finSciDEx << EvIDSDEx << " " << EdepSDEx << "\n";
	        ncounterSDEx++;
	     } else {
			 int diffSDEx = EvIDSDEx - ncounterSDEx;
			 for (int i=0; i < diffSDEx; i++) {
			    finSciDEx << ncounterSDEx+i << " " << 0.0 << "\n";
			 }
			 finSciDEx << EvIDSDEx << " " << EdepSDEx << "\n";
			 ncounterSDEx = ncounterSDEx + diffSDEx + 1;
		 }
	  }	     
      finSciDEx.close();
      
      if ((remove(TString("../../simdata/magnetic/"+((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_tmpxSciDE.txt"))) == 0) {
	     std::cout << std::endl << "File: " << TString(((Xfiles[k]).substr(23,((Xfiles[k]).find(".root"))-23))+"_SciDE.txt") << " generated! " << std::endl;
      }

  
   }



}


int main() {
   FileFillerMagnetic();
   return 0;
}  
