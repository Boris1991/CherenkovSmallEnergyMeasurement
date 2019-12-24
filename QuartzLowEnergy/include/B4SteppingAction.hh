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
/// \file B4SteppingAction.hh
/// \brief Definition of the B4SteppingAction class

#ifndef B4SteppingAction_h
#define B4SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class B4DetectorConstruction;
class B4EventAction;

/// Stepping action class.
///
/// In UserSteppingAction() there are collected the energy deposit and track 
/// lengths of charged particles in Absober and Gap layers and
/// updated in B4EventAction.

class B4SteppingAction : public G4UserSteppingAction
{
public:
  B4SteppingAction(const B4DetectorConstruction* detectorConstruction,
                    B4EventAction* eventAction);
  virtual ~B4SteppingAction();

  virtual void UserSteppingAction(const G4Step* step);


     void AddPos(G4int x, G4int y);    


private:

    G4double  fPositionX;
    G4double  fPositionY;


  const B4DetectorConstruction* fDetConstruction;
  B4EventAction*  fEventAction;  
  B4SteppingAction*  fSteppingAction;  
};

//inline void B4SteppingAction::AddPos(G4int x, G4int y) {
//  fPositionX +=  x; 
//  fPositionY +=  y; 
  
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
