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
/// \file B4EventAction.hh
/// \brief Definition of the B4EventAction class

#ifndef B4EventAction_h
#define B4EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"

/// Event action class
///
/// It defines data members to hold the energy deposit and track lengths
/// of charged particles in Absober and Gap layers:
/// - fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap
/// which are collected step by step via the functions
/// - AddAbs(), AddGap()

class B4EventAction : public G4UserEventAction
{
  public:
    B4EventAction();
    virtual ~B4EventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
    void AddAbs(G4double de, G4double dl);
    void AddGap(G4double de, G4double dl);
    //void AddPos(G4int x, G4int y);
    void AddPos2D(G4double xy);
    
  private:
    G4double  fEnergyAbs;
    G4double  fEnergyGap;
    G4double  fTrackLAbs; 
    G4double  fTrackLGap;
   // G4double  fPositionX;
   // G4double  fPositionY;
    G4double  fPositionXY;
    

    ///В эту переменную будем накапливать энергию частиц
    /// пришедших в детектор
    G4double energ;
    ///Функция регистрации частицы в детекторе
    void addParticle(const G4Step* step);
};

// inline functions

inline void B4EventAction::AddAbs(G4double de, G4double dl) {
  fEnergyAbs += de; 
  fTrackLAbs += dl;
}

inline void B4EventAction::AddGap(G4double de, G4double dl) {
  fEnergyGap += de; 
  fTrackLGap += dl;
}
/*inline void B4EventAction::AddPos(G4int x, G4int y) {
  fPositionX +=  x; 
  fPositionY +=  y; 
  
}*/

inline void B4EventAction::AddPos2D(G4double xy) {
  fPositionXY += xy; 
  }
//inline void B4EventAction::AddParticle(const G4Step* step) {
   //Здесь мы берем энергию (кинетическую, без массы покоя) в ГэВ-ах
   // energ+=step->GetTrack()->GetKineticEnergy()/eV;
//}
                     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
