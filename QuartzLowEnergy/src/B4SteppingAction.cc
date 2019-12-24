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
/// \file B4aSteppingAction.cc
/// \brief Implementation of the B4aSteppingAction class

#include "B4SteppingAction.hh"
#include "B4EventAction.hh"
#include "B4DetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "B4Analysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4SteppingAction::B4SteppingAction(
                      const B4DetectorConstruction* detectorConstruction,
                      B4EventAction* eventAction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction),
    fPositionX(0.),
    fPositionY(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4SteppingAction::~B4SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4SteppingAction::UserSteppingAction(const G4Step* step)
{
// Collect energy and track length step by step
//**************************************
G4Track * track = step->GetTrack();//new
//************************************88

fPositionX = 0.;
fPositionY = 0.;

//fEventAction->addParticle(step);
  // get volume of the current step
   auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

//G4cout<<track<<G4endl;
  
/*
    G4Track * track = step->GetTrack();
    //Узнаем физический объем в котором находится частица
    G4VPhysicalVolume* vel=track->GetVolume();
    //Название физического объема в котором мы будем регистрировать
    //частицы, он у нас будет играть роль чуствительного объема
    G4String name="Detector";
    //Условие или частица находится в интересуещем нас объеме
    if(name==vel->GetName()){
        //Если находится то учитываем ее энергию
        fEventAction->addParticle(step);
        //Нефизично, но нам нужно подсчитать энергию частиц попавших
        //в детектор, поэтому эту частицу уничтожаем что бы она
        //не зарегистрировалась несколько раз
        step->GetTrack()->SetTrackStatus(fStopAndKill);
    }
*/
// energy deposit
   // G4Track* track = step -> GetTrack();
auto edep = step->GetTotalEnergyDeposit();

 
  
 

//G4cout<<"xyz.x"<<xyz[0]<<G4endl;
//auto edep2 = step->GetEnergy();
// step length
  G4double stepLength = 0.;
  
  //if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {

  //  stepLength = step->GetStepLength();
  //}  
auto analysisManager = G4AnalysisManager::Instance();
//************************
 /*  if ( volume == fDetConstruction->GetGapPV() )
 {
        G4String particleName = track->GetDefinition()->GetParticleName();
        G4cout << particleName<< G4endl;
        
        if(particleName == "opticalphoton")
    {
            double energy = step->GetTrack()->GetDynamicParticle()->GetTotalEnergy();
            analysisManager->FillH1(2, energy);
            G4cout<<"loch2 "<<energy<<G4endl;
            step->GetTrack()->SetTrackStatus(fStopAndKill);
}}*/
//*****************
    //Если частица попадает в объем детектора:
  if ( volume == fDetConstruction->GetDetectorPV() )
 {
        G4String particleName = track->GetDefinition()->GetParticleName();
        G4cout << particleName<< G4endl;
        
        if(particleName == "opticalphoton")
       {    G4cout << "this is a "<<particleName<< G4endl;
            //G4Track * track = step->GetTrack();
            G4ThreeVector xyz = track->GetPosition()/mm;
            G4ThreeVector angle = track->GetMomentumDirection();
            fEventAction->AddAbs(edep,stepLength);
            //fSteppingAction->AddPos(round(xyz[0]), round(xyz[1]));
             //G4cout << "for the local thread " << angle[2]<<G4endl;
             analysisManager->FillH2(0, angle[0], angle[1]);
              analysisManager->FillH2(1, xyz[0], xyz[1]);
            //спектр гамма излучения
            double energy = step->GetTrack()->GetDynamicParticle()->GetTotalEnergy();
//***********
            //analysisManager->FillH1(2, energy);
         //*************   
         G4ThreeVector angle2 = track->GetMomentumDirection();
           if (angle2[1]<0.2 && angle2[1]>-0.2)
                    {   //  одномерное угловое распределение
                        
                        double angle = std::asin(angle2[0]); //1./(std::tan(angle2[2]/angle2[0]));
                        analysisManager->FillH1(1, angle);
                        
                        G4ThreeVector xyz2 = track->GetPosition()/mm;
                        analysisManager->FillH1(3, xyz2[0]/mm);
                    }
           // analysisManager->FillH2(0, atan(xyz[0]/10), atan(xyz[1]/10));
           
            step->GetTrack()->SetTrackStatus(fStopAndKill);
 
        }
        if(particleName == "e-")
            {    
                G4cout << "this is a "<<particleName<< G4endl;
                double energye = step->GetTrack()->GetDynamicParticle()->GetKineticEnergy();
                analysisManager->FillH1(0, energye);
                //step->GetTrack()->SetTrackStatus(fStopAndKill);
            }
    }
  
  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
