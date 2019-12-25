//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// 
/// \file B4DetectorConstruction.cc
/// \brief Implementation of the B4DetectorConstruction class

#include "B4DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//G4ThreadLocal 
//G4GlobalMagFieldMessenger* B4DetectorConstruction::fMagFieldMessenger = nullptr; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::B4DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fDetectorPV(nullptr),
   fGapPV(nullptr),
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

//                         энергии фотонов
//*******************************************************************
G4double photonEnergy[] =
           /* {1.379*eV, 1.427*eV, 1.478*eV, 1.530*eV, 1.584*eV, 
             1.640*eV, 1.700*eV, 1.757*eV, 1.819*eV, 1.883*eV, 
             1.949*eV, 2.018*eV, 2.090*eV, 2.163*eV, 2.239*eV, 
             2.318*eV, 2.400*eV, 2.484*eV, 2.571*eV, 2.662*eV, 
             2.756*eV, 2.853*eV, 2.954*eV, 3.058*eV, 3.165*eV, 
             3.277*eV, 3.392*eV, 3.512*eV, 3.635*eV, 3.764*eV, 
             3.896*eV, 4.033*eV, 4.176*eV, 4.323*eV, 4.476*eV,
             4.633*eV, 4.796*eV, 4.965*eV, 5.140*eV, 5.321*eV,
             5.507*eV, 5.703*eV, 5.904*eV};*/
             {1.4*eV, 1.6*eV, 1.8*eV, 2.0*eV, 2.2*eV, 2.4*eV};


const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);
//*******************************************************************


// Air
//*******************************************************************
 // Lead material defined using NIST Manager
  auto nistManager = G4NistManager::Instance();
// Выбор материала для мира из предопределенных в Geant4, берем воздух
  G4Material* worldMaterial = nistManager->FindOrBuildMaterial("G4_AIR");
//коэффициент преломления для воздуха

  G4double refractiveIndex0[] =
            /*{ 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 
              1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 
              1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 
              1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00};*/
              { 1.00, 1.00, 1.00, 1.00, 1.00,1.00};

 G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
  myMPT2->AddProperty("RINDEX", photonEnergy, refractiveIndex0, nEntries);
myMPT2->DumpTable();
worldMaterial->SetMaterialPropertiesTable(myMPT2); 
//**********************************************+**************************************

                         //Quartz
//*******************************************************************

  G4double refractiveIndex1[] =
           /* { 1.4517, 1.4522, 1.4526, 1.4531, 1.4536,
              1.4541, 1.4546, 1.4552, 1.4557, 1.4563,
              1.4569, 1.4575, 1.4583, 1.4590, 1.4598,
              1.4606, 1.4614, 1.4624, 1.4634, 1.4644,
              1.4656, 1.4668, 1.4681, 1.4695, 1.4711,
              1.4727, 1.4745, 1.4764, 1.4785, 1.4807,
              1.4831, 1.4858, 1.4887, 1.4918, 1.4953,
              1.4990, 1.5031, 1.5076, 1.5125, 1.5180,
              1.5241, 1.5308, 1.5384};*/
            /*{1.3, 1.3, 1.3, 1.3, 1.3,
              1.3, 1.3, 1.3, 1.3, 1.3,
              1.3, 1.3, 1.3, 1.3, 1.3,
              1.3, 1.3, 1.3, 1.3, 1.3,
              1.3, 1.3, 1.3, 1.3, 1.3,
              1.3, 1.3, 1.3, 1.3, 1.3,
              1.3, 1.3, 1.3, 1.3, 1.3,
              1.3, 1.3, 1.3, 1.3, 1.3,
              1.3, 1.3, 1.3};*/
              {2.4, 2.406, 2.4062, 2.4065, 2.411,2.421
              };
            
 assert(sizeof(refractiveIndex1) == sizeof(photonEnergy));

 G4double absorption[] =
            /* {5*mm, 5*mm, 5*mm, 5*mm, 5*mm,
             5*mm, 5*mm, 5*mm, 5*mm, 5*mm,
             5*mm, 5*mm, 5*mm, 5*mm, 5*mm,
             5*mm, 5*mm, 5*mm, 5*mm, 5*mm, 
             5*mm, 5*mm, 5*mm, 5*mm, 5*mm,
             5*mm, 5*mm, 5*mm, 5*mm, 5*mm,
             5*mm, 5*mm, 5*mm, 5*mm, 5*mm,
             5*mm, 5*mm, 5*mm, 5*mm, 5*mm, 
             5*mm, 5*mm, 5*mm};*/
             {5*mm, 5*mm, 5*mm, 5*mm, 5*mm,5*mm};
           /* {500*m, 500*m, 500*m, 500*m, 500*m,
             500*m, 500*m, 500*m, 500*m, 500*m,
             500*m, 500*m, 500*m, 500*m, 500*m,
             500*m, 500*m, 500*m, 500*m, 500*m, 
             500*m, 500*m, 500*m, 500*m, 500*m,
             500*m, 500*m, 500*m, 500*m, 500*m,
             500*m, 500*m, 500*m, 500*m, 500*m,
             500*m, 500*m, 500*m, 500*m, 500*m, 
             500*m, 500*m, 500*m};*/
          /* {35*mm,  35*mm,  35*mm,  35*mm, 35*mm,
             35*mm,  35*mm,  35*mm,  35*mm, 35*mm,
             35*mm,  35*mm,  35*mm,  35*mm, 35*mm,
             35*mm,  35*mm,  35*mm,  35*mm, 35*mm,
             35*mm,  35*mm,  35*mm,  35*mm, 35*mm,
             35*mm,  35*mm,  35*mm,  35*mm, 35*mm,
             35*mm,  35*mm,  35*mm,  35*mm, 35*mm,
             35*mm,  35*mm,  35*mm,  35*mm, 35*mm,
             35*mm, 35*mm, 35*mm};*/

  assert(sizeof(absorption) == sizeof(photonEnergy));


  // Описываем кварц:
//*****************************
  G4double z, aSi, aO;
  aSi = 28.085*g/mole;
  aO = 15.999*g/mole;
  G4Element* elSi  = new G4Element("Silicium","Si" , z = 14., aSi);
  G4Element* elO  = new G4Element("Oxigen", "O" , z = 8., aO);


//G4Element* elC = new G4Element ("Carbon", "C", 6, 12.01* g/mole);

            

//*****************************
// Option to switch on/off checking of volumes overlaps
  // Опция для включения выключения проверки перекрытия объемов
  //
  //G4bool checkOverlaps = true;
  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();
//*****************************
   //G4Material* diamond = new G4Material("diamond", 3.515*g/cm3, 1);
   //diamond -> AddElement(elC, 1); 
   //diamond->SetMaterialPropertiesTable(myMPT1);   
  
  G4double density = 2.600*g/cm3;
  G4Material* SiO2 = new G4Material("quartz", density, 2);
  SiO2->AddElement(elSi, 1);
  SiO2->AddElement(elO , 2);  
 SiO2->SetMaterialPropertiesTable(myMPT1); 
//*********************************
 myMPT1->AddConstProperty("SCINTILLATIONYIELD",5./MeV);

    myMPT1->AddProperty("RINDEX", photonEnergy, refractiveIndex1,nEntries)
        ->SetSpline(true);
    myMPT1->AddProperty("ABSLENGTH", photonEnergy, absorption, nEntries)
        ->SetSpline(true);




 //myMPT1->AddProperty("ABSLENGTH", photonEnergy, nEntries)
   //     ->SetSpline(true);
///********************************************************************************



                           //описываем бериллий
///********************************************************************************
//G4double z;
G4double  aBe;
aBe = 9.01*g/mole;
G4Element* elBe  = new G4Element("beryllium","Be" , 4., aBe);

G4double densityBe = 1.85*g/cm3;
G4Material* Beryllium =new G4Material("Beryllium", densityBe, 1);
Beryllium->AddElement(elBe, 1);
///********************************************************************************



  // Lead material defined using NIST Manager
  //auto nistManager = G4NistManager::Instance();
  //nistManager->FindOrBuildMaterial("G4_Pb");
  
  // Liquid argon material
  //G4double a;  // mass of a mole;
  //G4double z;  // z=mean number of protons;  
 // G4double density; 
  new G4Material("liquidArgon", 18., 39.95*g/mole, 1.390*g/cm3);
         // The argon by NIST Manager is a gas with a different density

  // Vacuum
  new G4Material("Galactic", 1., 1.01*g/mole, universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

// Выбор материала для мира из предопределенных в Geant4, берем воздух
 // G4Material* world_mat = nistManager->FindOrBuildMaterial("G4_AIR");

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4DetectorConstruction::DefineVolumes()
{

  // Geometry parameters
  G4int nofLayers = 10;
  G4double absoThickness = 10.*mm;
  G4double gapThickness =  5.*mm;
  //G4double calorSizeXY  = 10.*cm;

  //auto layerThickness = absoThickness + gapThickness;
  //auto calorThickness = nofLayers * layerThickness;
  //auto worldSizeXY = 1.2 * calorSizeXY;
  //auto worldSizeZ  = 1.2 * calorThickness; 
  
  // Get materials
  //auto defaultMaterial = G4Material::GetMaterial("Galactic");
  auto SiO2 = G4Material::GetMaterial("quartz");
  auto gapMaterial = G4Material::GetMaterial("liquidArgon");
  auto worldMaterial = G4Material::GetMaterial("G4_AIR");
  
 // if ( ! defaultMaterial || ! absorberMaterial || ! gapMaterial ) {
  //  G4ExceptionDescription msg;
  //  msg << "Cannot retrieve materials already defined."; 
  //  G4Exception("B4DetectorConstruction::DefineVolumes()",
   //   "MyCode0001", FatalException, msg);
 // }  
   
  //     
  // World
  //
  auto worldS 
    = new G4Box("World",           // its name
                 100*mm, 100*mm, 100*mm); // its size
                         
  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 worldMaterial,  // its material
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
  /*auto target
    = new G4Box("Target",     // its name
                 calorSizeXY/2, calorSizeXY/2, calorThickness/2); // its size*/



 //круглая форма
    
  G4double shape1_rmina =  0.*mm, shape1_rmaxa = 20*mm;
  G4double shape1_hz = 1.*mm;
  G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
  G4Tubs* target=    
    new G4Tubs("Target", 
    shape1_rmina, shape1_rmaxa, shape1_hz, shape1_phimin, shape1_phimax);
   /*    
auto target 
    = new G4Box("Target",           // its name
                 10*mm, 10*mm, 0.25*mm); // its size
*/
/* G4double Rmin = 0*mm;
 G4double Rmax = 20*mm;
 G4double pSPhi = 0*deg;
 G4double pDPhi = 360*deg;
 G4double pSTheta = 0*deg;
 G4double pDTheta = 90*deg;
  auto target
    = new  G4Sphere("Target", Rmin, Rmax , pSPhi, pDPhi,pSTheta,pDTheta); */     
 
  auto calorLV
    = new G4LogicalVolume(
                 target,     // its solid
                 SiO2,  // its material
                 "Target");   // its name


//вращение мишени
    G4RotationMatrix* yRot = new G4RotationMatrix;// Rotates X and Z axes only
     yRot->rotateY(-50*deg);// Rotates 45 degrees
                                   
 fGapPV = new G4PVPlacement(
                 yRot,                // no rotation
                 G4ThreeVector(0,0,0),  // at (0,0,0)
                 calorLV,          // its logical volume                         
                 "Target",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 


//                             Detector
//**********************************************************************
     
//          Детектор, также используем параллелепипед
  
  auto solidDet//absorberS 
    = new G4Box("Detector",            // its name
                 100*mm, 100*mm, 0.001*mm); // its size
   //круглая форма
    
 /* G4double pRmin =  100.*mm, pRmax = 101.*mm;
  G4double pSPhi = 270.*deg, PDPhi = 360.*deg;
  G4double PsTheta = 0.*deg, PDTheta = 90. *deg;
  G4Sphere* solidDet=    
    new G4Sphere("Detector", 
    pRmin, pRmax, pSPhi, PDPhi, PsTheta, PDTheta);*/
                         
  auto detectorLV//absorberLV
    = new G4LogicalVolume(
                 solidDet,        // its solid
                 worldMaterial, // its material
                 "Detector");          // its name
                                   
  fDetectorPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., (30*0-12*0)*mm), // its position
                 detectorLV,//absorberLV,       // its logical volume                         
                 "Detector",           // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

 
  //
  // print parameters
  //
 /* G4cout
    << G4endl 
    << "------------------------------------------------------------" << G4endl
    << "---> The calorimeter is " << nofLayers << " layers of: [ "
    << absoThickness/mm << "mSiO2m of " << worldMaterial->GetName() 
    << " + "
    << gapThickness/mm << "mm of " << gapMaterial->GetName() << " ] " << G4endl
    << "------------------------------------------------------------" << G4endl;*/
  
  //                                        
  // Visualization attributes
  //
  worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());

  auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
  //calorLV->SetVisAttributes(simpleBoxVisAtt);

  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4DetectorConstruction::ConstructSDandField()
{ 
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
//  G4ThreeVector fieldValue;
 // fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
//  fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
 // G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
