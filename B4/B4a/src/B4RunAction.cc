//
/// \file B4RunAction.cc
/// \brief Implementation of the B4RunAction class

#include "B4RunAction.hh"
#include "B4Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4RunAction::B4RunAction()
 : G4UserRunAction()
{ 
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);     

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in B4Analysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Create directories 
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
    // Note: merging ntuples is available only with Root output

  // Book histograms, ntuple
  //
  
  // Creating histograms
  analysisManager->CreateH1("Eabs","Edep in absorber", 100, 0., 15*MeV);
  analysisManager->CreateH1("Labs","trackL in absorber", 100, 0., 60*cm);
  analysisManager->CreateH1("Tgabs","globalT in absorber", 100, 0., 100*s);
  analysisManager->CreateH1("Tlabs","localT in absorber", 100, 0., 100*s);
  analysisManager->CreateH1("Tpabs","properT in absorber", 100, 0., 100*s);
    
  // Creating ntuple
  //
  analysisManager->CreateNtuple("B4", "Edep and TrackL");
  analysisManager->CreateNtupleDColumn("Eabs");
  analysisManager->CreateNtupleDColumn("Labs");
  analysisManager->CreateNtupleDColumn("Tgabs");
  analysisManager->CreateNtupleDColumn("Tlabs");
  analysisManager->CreateNtupleDColumn("Tpabs");
  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4RunAction::~B4RunAction()
{
  delete G4AnalysisManager::Instance();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4RunAction::BeginOfRunAction(const G4Run* /*run*/)
{ 
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "B4";
  analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // print histogram statistics
  //
  auto analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->GetH1(1) ) {
    G4cout << G4endl << " ----> print histograms statistic ";
    if(isMaster) {
      G4cout << "for the entire run " << G4endl << G4endl; 
    }
    else {
      G4cout << "for the local thread " << G4endl << G4endl; 
    }
    
    G4cout << " EAbs : mean = " 
       << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy") 
       << " rms = " 
       << G4BestUnit(analysisManager->GetH1(0)->rms(),  "Energy") << G4endl;
    
    G4cout << " LAbs : mean = "
       << G4BestUnit(analysisManager->GetH1(1)->mean(), "Length")
       << " rms = " 
       << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Length") << G4endl;
    
    G4cout << " Tgabs : mean = "
      << G4BestUnit(analysisManager->GetH1(2)->mean(), "Time")
      << " rms = " 
      << G4BestUnit(analysisManager->GetH1(2)->rms(),  "Time") << G4endl;

    G4cout << " Tlabs : mean = "
      << G4BestUnit(analysisManager->GetH1(3)->mean(), "Time")
      << " rms = " 
      << G4BestUnit(analysisManager->GetH1(3)->rms(),  "Time") << G4endl;

    G4cout << " Tpabs : mean = "
      << G4BestUnit(analysisManager->GetH1(4)->mean(), "Time")
      << " rms = "
      << G4BestUnit(analysisManager->GetH1(4)->rms(),  "Time") << G4endl;

  }

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
