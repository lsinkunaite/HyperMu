//
/// \file B4aActionInitialization.cc
/// \brief Implementation of the B4aActionInitialization class

#include "B4aActionInitialization.hh"
#include "B4PrimaryGeneratorAction.hh"
#include "B4RunAction.hh"
#include "B4aEventAction.hh"
#include "B4aSteppingAction.hh"
#include "B4DetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aActionInitialization::B4aActionInitialization
                            (B4DetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aActionInitialization::~B4aActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4aActionInitialization::BuildForMaster() const
{
  SetUserAction(new B4RunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4aActionInitialization::Build() const
{
  SetUserAction(new B4PrimaryGeneratorAction);
  SetUserAction(new B4RunAction);
  auto eventAction = new B4aEventAction;
  SetUserAction(eventAction);
  SetUserAction(new B4aSteppingAction(fDetConstruction,eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
