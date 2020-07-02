
//
/// \file B4aActionInitialization.hh
/// \brief Definition of the B4aActionInitialization class

#ifndef B4aActionInitialization_h
#define B4aActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class B4DetectorConstruction;

/// Action initialization class.
///

class B4aActionInitialization : public G4VUserActionInitialization
{
  public:
    B4aActionInitialization(B4DetectorConstruction*);
    virtual ~B4aActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    B4DetectorConstruction* fDetConstruction;
};

#endif

    
