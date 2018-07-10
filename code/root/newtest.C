#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include <fstream>
using namespace std;

void newtest(){
  TFile *f=new TFile("../../simdata/bubble4/bubble_2x5mm_250mm_SciD_Nevts_SciSphere_3mm_Al_1e6mudecay.root");
  TTree *tr1=(TTree*)f->Get("Detector/SciDet1"); // creates the TTree object
  TTree *tr2=(TTree*)f->Get("Detector/SciDet2");
  TTree *tr3=(TTree*)f->Get("Detector/SciDet3");
  //tr1->Scan(); // prints the content on the screen
  //tr2->Scan();
  //tr3->Scan();

  float EventID,Edep; // create variables of the same type as the branches you want to access

  tr1->SetBranchAddress("EventID",&EventID); // for all the TTree branches you need this
  tr1->SetBranchAddress("Edep",&Edep);
  tr2->SetBranchAddress("EventID",&EventID);
  tr2->SetBranchAddress("Edep",&Edep);
  tr3->SetBranchAddress("EventID",&EventID);
  tr3->SetBranchAddress("Edep",&Edep);



/*
  ofstream myfile1;
  myfile1.open ("example1.txt");
  myfile1 << "EventID1    Edep1\n";

  for (int i=0;i<tr1->GetEntries();i++){
    // loop over the tree
    tr1->GetEntry(i);
    myfile1 << EventID << " " << Edep <<"\n"; //write to file
  }
  myfile1.close();
  */
  
   std::ifstream input( "example1.txt" );
   std::string line;
   std::getline(input, line);
   std::cout << tr1->GetEntries() << std::endl;
  /* 
   std::getline(input, line);
   double EvID1, Edep1;
   line >> EvID1 >> Edep1;
*/
   std::vector<double> vEvID1;
   std::vector<double> vEdep1;


   int ncounter = 1;
   while (!input.eof()) {
   //while (ncounter <= 300000) {
	   double EvID1, Edep1;
	   input >> EvID1 >> Edep1;
	   //std::cout << std::endl;
	   //std::cout << "X-check :: ncounter = " << ncounter << " EvID1 = " << EvID1 << std::endl;
	   if (EvID1 == ncounter) {
		   vEvID1.push_back(EvID1);
		   vEdep1.push_back(Edep1);
		   std::cout << "I-ncounter: " << ncounter << " EvID1 = " << vEvID1.back() << " Edep1 = " << vEdep1.back() << std::endl;
		   ncounter++;
	   } else {
		   int diff = EvID1 - ncounter;
		   for (int i=0; i<diff; i++) {
		   	   vEvID1.push_back(ncounter+i);
		   	   vEdep1.push_back(0.0);
               std::cout << "***********************************************************E-ncounter: " << ncounter << " EvID1 = " << vEvID1.back() << " Edep1 = " << vEdep1.back() << std::endl;
		   }
		   vEvID1.push_back(EvID1);
		   vEdep1.push_back(Edep1);
		   ncounter = ncounter+diff+1;
		   std::cout <<" ncounter: " << ncounter << " EvID1 = " << vEvID1.back() << " Edep1 = " << vEdep1.back() << std::endl;
	   }
	   //std::cout << "EvID1 = " << vEvID1[ncounter-1] << " Edep1 = " << vEdep1[ncounter-1] << std::endl;
	   //ncounter++;
   }
   std::cout << " last test: EvID = " << vEvID1.back() << " and Edep = " << vEdep1.back() << std::endl;
   vEvID1.pop_back(); vEdep1.pop_back();
   std::cout << " does it work? EvID = " << vEvID1.back() << " and Edep = " << vEdep1.back() << std::endl;
   vEvID1.pop_back(); vEdep1.pop_back();
   std::cout << " does it really work? EvID = " << vEvID1.back() << " and Edep = " << vEdep1.back() << std::endl;
	   
   


   //vEvID1.push_back(EvID1);
   //vEdep1.push_back(Edep1);

/*
   
   while (!input.eof()) {
	   getline(input, line);
       
       while (line >> EvID1 >> Edep1) {
		   if 

   
   std::stringstream LineStream(line);
   
   while (std::getline(iss, token, ','))
      {   
      // process each token
            std::cout << token << " ";
        }
        std::cout << std::endl;
*/  
  
/*  
  ofstream myfile2;
  myfile2.open ("example2.txt");
  myfile2 << "EventID2    Edep2\n";

  for (int i=0;i<tr2->GetEntries();i++){
    // loop over the tree
    tr2->GetEntry(i);
    std::cout << EventID << " " << Edep << std::endl; //print to the screen
    myfile2 << EventID << " " << Edep <<"\n"; //write to file
  }
  myfile2.close();


  ofstream myfile3;
  myfile3.open ("example3.txt");
  myfile3 << "EventID3    Edep3\n";

  for (int i=0;i<tr3->GetEntries();i++){
    // loop over the tree
    tr3->GetEntry(i);
    std::cout << EventID << " " << Edep << std::endl; //print to the screen
    myfile3 << EventID << " " << Edep <<"\n"; //write to file
  }
  myfile3.close();
*/
}


int main() {
   newtest();
   return 0;
}  
