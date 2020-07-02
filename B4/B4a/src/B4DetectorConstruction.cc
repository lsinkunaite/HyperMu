//
/// \file B4DetectorConstruction.cc
/// \brief Implementation of the B4DetectorConstruction class

#include "B4DetectorConstruction.hh"

#include "G4AutoDelete.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4GeometryManager.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4PVPlacement.hh"
#include "G4SolidStore.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::B4DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fAbsorberPV(nullptr),
   fCheckOverlaps(true)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::~B4DetectorConstruction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4DetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4DetectorConstruction::DefineMaterials()
{ 
  // Lead material defined using NIST Manager
  //auto nistManager = G4NistManager::Instance();
  
  // Liquid argon material
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density; 
  new G4Material("liquidArgon", z=18., a= 39.95*g/mole, density= 1.390*g/cm3);
         // The argon by NIST Manager is a gas with a different density

  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4DetectorConstruction::DefineVolumes()
{
    G4NistManager* nist = G4NistManager::Instance();
    
  // Geometry parameters
  G4double calorThickness = 350.*mm;
  G4double calorSizeXY  = 400.*mm;
  //G4double calorThickness = 600.*mm;
  //G4double calorSizeXY = 600.*mm;
    
  //auto worldSizeXY = 1.2 * calorSizeXY;
  //auto worldSizeZ  = 1.2 * calorThickness;
  auto worldSizeXY = 2. * calorSizeXY;
  auto worldSizeZ = 2. * calorThickness;
    
    
  // Get materials
  auto defaultMaterial = G4Material::GetMaterial("Galactic");
    G4Material* BGO_mat = nist->FindOrBuildMaterial("G4_BGO");
    G4Material* plastic_mat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    G4Material* carbon_mat = nist->FindOrBuildMaterial("G4_C");
    G4Material* hydrogen_mat = nist->FindOrBuildMaterial("G4_H");
   
  //     
  // World
  //
  auto worldS 
    = new G4Box("World",           // its name
                 worldSizeXY, worldSizeXY, worldSizeZ); // its size
                         
  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 defaultMaterial,  // its material
                 "World");         // its name
                                   
  auto worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
    
  //                               
  // Calorimeter
  //  
  auto calorimeterS = new G4Box("Calorimeter", calorSizeXY, calorSizeXY, calorThickness); // its size
                         
  auto calorLV = new G4LogicalVolume(calorimeterS, carbon_mat, "Calorimeter");   // its name
                                   
  fAbsorberPV = new G4PVPlacement(0, G4ThreeVector(), calorLV, "Calorimeter", worldLV, false, 0, fCheckOverlaps);
  
 
    /*
    // Spherical calorimeter
    G4double shape3_prmin = 200*mm, shape3_prmax = 600*mm;
    G4double shape3_psphi = 0, shape3_pdphi = 360;
    G4double shape3_pstheta = 0, shape3_pdtheta = 180;
    
    auto CalspheS = new G4Sphere("Calsphe", shape3_prmin, shape3_prmax, shape3_psphi    , shape3_pdphi, shape3_pstheta, shape3_pdtheta);
    
    auto CalspheLV = new G4LogicalVolume(CalspheS, plastic_mat, "Calsphe");
    
    fAbsorberPV = new G4PVPlacement(0,G4ThreeVector(),CalspheLV,"Calsphe",worldLV,    false,0,fCheckOverlaps);
*/
    
    
    
    
  //                                        
  // Visualization attributes
  //
  worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());

  auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
  calorLV->SetVisAttributes(simpleBoxVisAtt);
  //CalspheLV->SetVisAttributes(simpleBoxVisAtt);
    
  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
