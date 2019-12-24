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
/// \file B4EventAction.cc
/// \brief Implementation of the B4EventAction class

#include "B4EventAction.hh"
#include "B4RunAction.hh"
#include "B4Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>
#include "G4ThreeVector.hh"
#include "G4RootAnalysisManager.hh"
#include "G4CsvAnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4EventAction::B4EventAction()
 : G4UserEventAction(),
   fEnergyAbs(0.),
   fEnergyGap(0.),
   fTrackLAbs(0.),
   fTrackLGap(0.),
  // fPositionX(0.),
 //  fPositionY(0.),
   fPositionXY(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4EventAction::~B4EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4EventAction::BeginOfEventAction(const G4Event* /*event*/)
{  
  // initialisation per event
  fEnergyAbs = 0.;
  fEnergyGap = 0.;
  fTrackLAbs = 0.;
  fTrackLGap = 0.;
 // fPositionX = 0.;
  //fPositionY = 0.;
  fPositionXY = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4EventAction::EndOfEventAction(const G4Event* event)
{
  // Accumulate statistics
  //

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  //analysisManager->FillH1(0, fEnergyAbs);
 // analysisManager->FillH1(1, fPositionX);
 // analysisManager->FillH1(2, fPositionY);
 // analysisManager->FillH2(0, fPositionX, fPositionY);//, fPositionXY);
  //analysisManager->FillP2(0, 50, 100, 20);
 // analysisManager->FillH2(0, 0, 0);
  //cout<<"filling histogram";
  
  // fill ntuple
/*
  analysisManager->FillNtupleDColumn(0, fEnergyAbs);
  analysisManager->FillNtupleDColumn(1, fEnergyGap);
  analysisManager->FillNtupleDColumn(2, fTrackLAbs);
  analysisManager->FillNtupleDColumn(3, fTrackLGap);
  analysisManager->AddNtupleRow();  
*/
  
  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();

}  
//Накапливаем энергию частиц
//void B4EventAction::addParticle(const G4Step* step)
//{   //Здесь мы берем энергию (кинетическую, без массы покоя) в эВ-ах
//    energ+=step->GetTrack()->GetKineticEnergy()/eV;
//}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
