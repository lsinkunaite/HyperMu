// 
/// \file B4aEventAction.cc
/// \brief Implementation of the B4aEventAction class

#include "B4aEventAction.hh"
#include "B4RunAction.hh"
#include "B4Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aEventAction::B4aEventAction()
 : G4UserEventAction(),
   fEnergyAbs(0.),
   fTrackLAbs(0.),
   fGlobalTAbs(0.),
   fLocalTAbs(0.),
   fProperTAbs(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aEventAction::~B4aEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4aEventAction::BeginOfEventAction(const G4Event* /*event*/)
{  
  // initialisation per event
  fEnergyAbs = 0.;
  fTrackLAbs = 0.;
  fGlobalTAbs = 0.;
  fLocalTAbs = 0.;
  fProperTAbs = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4aEventAction::EndOfEventAction(const G4Event* event)
{
  // Accumulate statistics
  //

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  analysisManager->FillH1(0, fEnergyAbs);
  analysisManager->FillH1(1, fTrackLAbs);
  analysisManager->FillH1(2, fGlobalTAbs);
  analysisManager->FillH1(3, fLocalTAbs);
  analysisManager->FillH1(4, fProperTAbs);
    
    analysisManager->FillH2(0, fEnergyAbs, fGlobalTAbs);
    analysisManager->FillH2(1, fEnergyAbs,fTrackLAbs);
    
  
  // fill ntuple
  analysisManager->FillNtupleDColumn(0, fEnergyAbs);
  analysisManager->FillNtupleDColumn(1, fTrackLAbs);
  analysisManager->FillNtupleDColumn(2, fGlobalTAbs);
  analysisManager->FillNtupleDColumn(3, fLocalTAbs);
  analysisManager->FillNtupleDColumn(4, fProperTAbs);
  analysisManager->AddNtupleRow();  
  
  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;     

    G4cout
       << "   Absorber: total energy: " << std::setw(7)
                                        << G4BestUnit(fEnergyAbs,"Energy")
       << "       total track length: " << std::setw(7)
                                        << G4BestUnit(fTrackLAbs,"Length")
       << "              global time: " << std::setw(7)
                                        << G4BestUnit(fGlobalTAbs,"Time")
       << "               local time: " << std::setw(7)
                                        << G4BestUnit(fLocalTAbs,"Time")
       << "              proper time: " << std::setw(7)
                                        << G4BestUnit(fProperTAbs,"Time")
       << G4endl;
  }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
