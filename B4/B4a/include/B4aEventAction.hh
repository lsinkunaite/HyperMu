//
/// \file B4aEventAction.hh
/// \brief Definition of the B4aEventAction class

#ifndef B4aEventAction_h
#define B4aEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///
/// It defines data members to hold the energy deposit and track lengths
/// of charged particles in Absober and Gap layers:
/// - fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap
/// which are collected step by step via the functions
/// - AddAbs(), AddGap()

class B4aEventAction : public G4UserEventAction
{
  public:
    B4aEventAction();
    virtual ~B4aEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
    void AddAbs(G4double de, G4double dl, G4double dtg, G4double dtl, G4double dtp);
    
  private:
    G4double  fEnergyAbs;
    G4double  fTrackLAbs; 
    G4double  fGlobalTAbs;
    G4double  fLocalTAbs;
    G4double  fProperTAbs;
};

// inline functions

inline void B4aEventAction::AddAbs(G4double de, G4double dl, G4double dtg, G4double dtl, G4double dtp) {
  fEnergyAbs += de; 
  fTrackLAbs += dl;
  fGlobalTAbs += dtg;
  fLocalTAbs += dtl;
  fProperTAbs += dtp;
}
                     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
