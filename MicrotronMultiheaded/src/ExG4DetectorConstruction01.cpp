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
/// \file ExG4DetectorConstruction01.cpp
/// \brief Implementation of the ExG4DetectorConstruction01 class

//Создано специально для проекта http://dev.asifmoda.com/geant4
//Сообщество в facebook  https://www.facebook.com/groups/248240199204054/

#include "ExG4DetectorConstruction01.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4TransportationManager.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4GenericMessenger.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExG4DetectorConstruction01::ExG4DetectorConstruction01()
: G4VUserDetectorConstruction(),
            fMessenger(nullptr),
            fTargetAngle(90.*deg), fTargetRotation(nullptr), fTargetPhys(nullptr)
{
fTargetRotation = new G4RotationMatrix();
  fTargetRotation->rotateY(fTargetAngle);
 
  DefineCommands();
 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExG4DetectorConstruction01::~ExG4DetectorConstruction01()
{ 
    delete fTargetRotation;
    delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Создаем детекторы

G4VPhysicalVolume* ExG4DetectorConstruction01::Construct()
{  
//                         энергии фотонов
//*******************************************************************
//   рассматриваются длины волн 0.3 мкм -- 0.806 мкм
G4double photonEnergy[] =
            { 1.4*eV, 1.6*eV, 1.8*eV, 2.0*eV, 2.2*eV, 
			2.2226 *eV, 2.2553 *eV, 2.289 *eV, 2.3132 *eV, 2.3309 *eV,
			2.3561 *eV, 2.3782 *eV, 2.3932 *eV, 2.4122 *eV, 2.4237 *eV,
			2.4395 *eV, 2.4555 *eV, 2.4677 *eV, 2.4801 *eV, 2.4885 *eV,
			2.497 *eV, 2.5014 *eV, 2.514 *eV, 2.5227 *eV, 2.5333 *eV, 
			2.5399 *eV, 2.5444 *eV, 2.5615 *eV, 2.5661 *eV, 2.5835 *eV,
			2.6094 *eV, 2.6267 *eV, 2.6399 *eV, 2.6532 *eV, 2.6666 *eV,
			2.7039 *eV, 2.7327 *eV, 2.7771 *eV, 2.8127 *eV, 2.8493 *eV,
			2.8753 *eV, 2.8964 *eV, 2.9286 *eV, 2.9556 *eV, 2.9607 *eV,
			2.9831 *eV, 3.003 *eV, 3.0119 *eV, 3.0407 *eV, 3.0823 *eV,
			3.1315 *eV, 3.1759 *eV, 3.2023 *eV, 3.2086 *eV, 3.2217 *eV,
			3.2764 *eV, 3.2829 *eV, 3.3109 *eV, 3.3321 *eV, 3.346 *eV,
			3.3756 *eV, 3.3973 *eV, 3.42 *eV, 3.4425 *eV, 3.474 *eV,
			3.4809 *eV, 3.5129 *eV ,3.5285 *eV, 3.5535 *eV, 3.5856 *eV,
			3.6103 *eV, 3.6284 *eV, 3.6622 *eV, 3.6704 *eV, 3.6976 *eV,
			3.7236 *eV, 			
			  3.8*eV, 4.0*eV, 4.2*eV, 
              4.4*eV, 4.6*eV, 4.8*eV, 5.0*eV, 5.2*eV, 
              5.4*eV, 5.6*eV, 5.8*eV, 6.0*eV};
            
const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);
//*******************************************************************

// Air
//*******************************************************************
 // Lead material defined using NIST Manager
  auto nistManager = G4NistManager::Instance();
// Выбор материала для мира из предопределенных в Geant4, берем воздух
  G4Material* world_mat = nistManager->FindOrBuildMaterial("G4_AIR");
//коэффициент преломления для воздуха

  G4double refractiveIndex0[] =
           { 1.00, 1.00, 1.00, 1.00, 1.00, 
			   1.00, 1.00, 1.00, 1.00, 1.00, 
              1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 
              1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 
              1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 
              1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 
              1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 
              1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 
              1.00, 1.00, 1.00, 1.00, 1.00,
              1.00,  
              1.00, 1.00, 1.00, 
              1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00};


 G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
  myMPT2->AddProperty("RINDEX", photonEnergy, refractiveIndex0, nEntries);
myMPT2->DumpTable();
world_mat->SetMaterialPropertiesTable(myMPT2); 
//**********************************************+************************************** 

             //Quartz
//*******************************************************************

  G4double refractiveIndex1[] =
            
            { 2.400, 2.406, 2.407, 2.411, 2.421,
			2.4159, 2.4167, 2.4176,2.4182, 2.4187,
			2.4194, 2.4201, 2.4205, 2.4211,2.4215,
			2.422, 2.4225, 2.423, 2.4234, 2.4237,
			2.424, 2.4241, 2.4246, 2.4249, 2.4253,
			2.4255, 2.4257, 2.4263, 2.4265, 2.4272,
			2.4282, 2.4289, 2.4294, 2.43, 2.4305,
			2.4321, 2.4334, 2.4354, 2.4371, 2.4389,
			2.4402, 2.4413, 2.443, 2.4444, 2.4447,
			2.4459, 2.447, 2.4475, 2.4492, 2.4516,
			2.4546, 2.4573, 2.459, 2.4594, 2.4603,
			2.4639, 2.4643, 2.4663, 2.4677, 2.4687,
			2.4708, 2.4724, 2.474, 2.4757, 2.478,
			2.4785, 2.481, 2.4822, 2.4842, 2.4867,
			2.4887, 2.4902, 2.493, 2.4937, 2.4959,
			2.4982,
			2.506, 2.524, 2.541, 
            2.561, 2.582, 2.606, 2.639, 2.667, 
            2.691, 2.728, 2.771,2.818};
            
            
 assert(sizeof(refractiveIndex1) == sizeof(photonEnergy));

 G4double absorption[] =
           
          /* {500*cm, 500*cm, 500*cm, 500*cm, 500*cm,
             500*cm, 500*cm, 500*cm, 500*cm, 500*cm,
             500*cm, 500*cm, 500*cm, 500*cm, 500*cm,
             500*cm, 500*cm, 500*cm, 500*cm, 500*cm, 
             500*cm, 500*cm, 500*cm, 500*cm};*/
          {5*cm, 5*cm, 5*cm, 5*cm, 5*cm,
			  5*cm, 5*cm, 5*cm, 5*cm, 5*cm,
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm, 
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm,
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm, 
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm,
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm, 
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm,
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm, 
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm,
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm, 
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm,
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm, 
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm,
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm, 
             5*cm,
             5*cm, 5*cm, 5*cm,
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm, 
             5*cm, 5*cm, 5*cm, 5*cm};
            


  assert(sizeof(absorption) == sizeof(photonEnergy));
  
  
   G4double scintilFast[] =
            { 0.00, 0.00, 0.00, 0.00, 0.00, 
			6.6516 ,
8.0056 ,
9.5578 ,
10.784 ,
11.8367 ,
13.923 ,
15.5365 ,
16.9595 ,
18.9301 ,
19.8599 ,
22.3487 ,
24.8702 ,
27.2092 ,
29.743 ,
31.7329 ,
34.254 ,
35.8669 ,
37.9579 ,
40.5265 ,
42.273 ,
44.1361 ,
45.4423 ,
46.99 ,
48.4898 ,
49.8927 ,
49.3239 ,
47.4841 ,
46.4535 ,
44.8618 ,
43.6229 ,
43.6851 ,
44.7252 ,
46.2315 ,
47.8051 ,
49.6167 ,
47.5 ,
45.6584 ,
43.1488 ,
39.0725 ,
36.8972 ,
34.9205 ,
45.7155 ,
34.0203 ,
31.0012 ,
27.6126 ,
24.6134 ,
22.348 ,
22.7617 ,
21.4814 ,
20.2399 ,
20.8243 ,
18.8304 ,
18.5422 ,
17.7477 ,
15.9806 ,
17.0597 ,
15.0676 ,
15.6455 ,
14.3304 ,
16.3849 ,
13.0603 ,
14.3989 ,
13.0077 ,
15.3102 ,
12.2434 ,
10.5916 ,
14.6505 ,
12.5231 ,
10.7821 ,
13.6717 ,
11.4643 ,
              0.00, 0.00, 0.00,  
              0.00, 0.00, 0.00, 0.00, 0.00, 
              0.00, 0.00, 0.00, 0.00,  
               };
   assert(sizeof(scintilFast) == sizeof(photonEnergy));
              
   G4double scintilSlow[] =
             {0.00, 0.00, 0.00, 0.00, 0.00, 
			  0.00, 0.00, 0.00, 0.00, 0.00,  
              0.00, 0.00, 0.00, 0.00, 0.00,
              0.00, 0.00, 0.00, 0.00, 0.00,  
              0.00, 0.00, 0.00, 0.00, 0.00,
              0.00, 0.00, 0.00, 0.00, 0.00,  
              0.00, 0.00, 0.00, 0.00, 0.00,
              0.00, 0.00, 0.00, 0.00, 0.00,  
              0.00, 0.00, 0.00, 0.00, 0.00,
              0.00, 0.00, 0.00, 0.00, 0.00,  
              0.00, 0.00, 0.00, 0.00, 0.00,
              0.00, 0.00, 0.00, 0.00, 0.00,  
              0.00, 0.00, 0.00, 0.00, 0.00,
              0.00, 0.00, 0.00, 0.00, 0.00,  
              0.00, 0.00, 0.00, 0.00, 0.00,
              0.00,
              0.00, 0.00, 0.00,  
              0.00, 0.00, 0.00, 0.00, 0.00, 
              0.00, 0.00, 0.00, 0.00 
               };

  assert(sizeof(scintilSlow) == sizeof(photonEnergy));

  //описываем бериллий
///********************************************************************************

G4double z1, aBe;
aBe = 9.01*g/mole;
G4Element* elBe  = new G4Element("beryllium","Be" , z1 = 4., aBe);

G4double densityBe = 1.85*g/cm3;
G4Material* Beryllium =new G4Material("Beryllium", densityBe, 1);
Beryllium->AddElement(elBe, 1);
///********************************************************************************


  // Описываем кварц:
//*****************************
  G4double z, aSi, aO;
  aSi = 28.085*g/mole;
  aO = 15.999*g/mole;
  G4Element* elSi  = new G4Element("Silicium","Si" , z = 14., aSi);
  G4Element* elO  = new G4Element("Oxigen", "O" , z = 8., aO);
//*****************************
// Option to switch on/off checking of volumes overlaps
  // Опция для включения выключения проверки перекрытия объемов
  //
  //G4bool checkOverlaps = true;
  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();
//*****************************
     
  G4double density = 2.600*g/cm3;
  G4Material* SiO2 = new G4Material("quartz", density, 2);
  SiO2->AddElement(elSi, 1);
  SiO2->AddElement(elO , 2);  
 SiO2->SetMaterialPropertiesTable(myMPT1); 
//*********************************
 //myMPT1->AddConstProperty("SCINTILLATIONYIELD",5./MeV);

    myMPT1->AddProperty("RINDEX",       photonEnergy, refractiveIndex1,nEntries)
        ->SetSpline(true);
    myMPT1->AddProperty("ABSLENGTH",    photonEnergy, absorption,     nEntries)
        ->SetSpline(true);
    myMPT1->AddProperty("FASTCOMPONENT",photonEnergy, scintilFast,     nEntries)
        ->SetSpline(true);
	myMPT1->AddProperty("SLOWCOMPONENT",photonEnergy, scintilSlow,     nEntries)
        ->SetSpline(true);
        
        
    myMPT1->AddConstProperty("SCINTILLATIONYIELD",1000./MeV);
	myMPT1->AddConstProperty("RESOLUTIONSCALE",1*eV);
	myMPT1->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
	myMPT1->AddConstProperty("SLOWTIMECONSTANT",1.*ns);
	myMPT1->AddConstProperty("YIELDRATIO",0.8);
///******************************************************************************** 

// Get nist material manager
  // Для обучения используем предопределенные в Geant4 материалы
  // Так объявляется менеджер, из которого из можно извлечь
  //
  G4NistManager* nist = G4NistManager::Instance();
  
  // Detector parameters
  // Параметры детектора,
  //
  
  // Материал детектора, здесь вольфрам
  //
  G4Material* det_mat = nist->FindOrBuildMaterial("G4_W");
   
  // Option to switch on/off checking of volumes overlaps
  // Опция для включения выключения проверки перекрытия объемов
  //
  G4bool checkOverlaps = true;

  
  
  // Создание объема для мира, определяется просто сама форма объема, берем параллелепипед
  G4Box* solidWorld =    
    new G4Box("World",                       //its name, название объема
       15*cm, 15*cm, 15*cm);     //its size, его размеры

  // Логический объем, здесь подключается материал, из которого сделан объем
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid, объем
                        world_mat,           //its material, материал объема
                        "World");            //its name, название логического объема
                                             //совпадает с названием объема, но
                                             //для Geant4 это разные объекты
                                             //объем и логический объем

  //Физический объем, а теперь наш логический объем помещае в "ральный" мир
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation, нет вращения
                      G4ThreeVector(),       //at (0,0,0), расположение в центре (0,0,0)
                      logicWorld,            //its logical volume, логический объем этого физического
                      "World",               //its name, название физического объема
                      0,                     //its mother  volume, материнский объем, этот самый первый
                      false,                 //no boolean operation, без логических (булевых) операций
                      0,                     //copy number, номер копии
                      checkOverlaps);        //overlaps checking, флаг проверки перекрытия объемов
                     
  //     
 
//*******************************************************8

//Бериллиевый рассеиватель
 /* G4Box* solidDet0 =
    new G4Box("Detector",                    //its name, имя
        5*mm, 5*mm, 0.025*mm); //its size, размеры

  //Логический объем
  G4LogicalVolume* logicDiff =
    new G4LogicalVolume(solidDet0,            //its solid, объем
                        Beryllium,             //its material, указываем материал детектора
                        "Diffuser");         //its name, его имя



  //Физический объем детектора
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0*cm,0,-9.9*cm),//G4ThreeVector(det_sizeXY*0,0,0*cm),         //at (0,0,0)
                    logicDiff,                //its logical volume, подключаем логический объем
                    "Detector",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0,                       //copy number, номер копии
                    checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов

*/
//******************************************************
G4Box* solidDet =
    new G4Box("Detector",                    //its name, имя
        100*mm, 100*mm, 0.015*mm); //its size, размеры*/

  //Логический объем
  G4LogicalVolume* logicDet =
    new G4LogicalVolume(solidDet,            //its solid, объем
                        world_mat,             //its material, указываем материал детектора
                        "Detector");         //its name, его имя
G4RotationMatrix* detRot = new G4RotationMatrix;// Rotates X and Z axes only
     detRot->rotateY(-54*deg);// Rotates 45 degrees

 //Физический объем детектора
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0*mm,0,25*mm),         //at (0,0,0)
                    logicDet,                //its logical volume, подключаем логический объем
                    "Detector",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0,                       //copy number, номер копии
                    checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов
//для листа
//******************************************************************************************8
  /*//Физический объем детектора
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,5*cm),         //at (0,0,0)
                    logicDet,                //its logical volume, подключаем логический объем
                    "Detector",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0,                       //copy number, номер копии
                    checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов*/
//*********************************************************************************************


  //*********************************************************************************************
 //     
  // Target
  // мишень, также используем параллелепипед
  //  
  G4double shape1_rmina =  0.*mm, shape1_rmaxa = 7.5*mm;
  G4double shape1_hz = 0.15*mm;
  G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
  
G4Tubs* target=    
    new G4Tubs("Target", 
    shape1_rmina, shape1_rmaxa, shape1_hz, shape1_phimin, shape1_phimax);

//Логический объем
  G4LogicalVolume* logicTar =
    new G4LogicalVolume(target,            //its solid, объем
                        SiO2,             //its material, указываем материал детектора
                        "Target");         //its name, его имя
//Матрица поворота
G4RotationMatrix* yRot = new G4RotationMatrix;// Rotates X and Z axes only
     yRot->rotateY(-fTargetAngle);// Rotates 45 degrees
    //G4double angleRot = fTargetAngle;
  //Физический объем детектора
//std::cout<<"rotate of target is "<<yRot<<std::endl;
//std::cout<<"rotate of target2 is "<<fTargetAngle<<std::endl;
 fTargetPhys =
 new G4PVPlacement(yRot,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,0*cm),         //at (0,0,0)
                    logicTar,                //its logical volume, подключаем логический объем
                    "Target",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0,                       //copy number, номер копии
                    checkOverlaps);

  //
  //always return the physical World
  //Всегда возвращает физический объем
  //
  return physWorld;
}
void ExG4DetectorConstruction01::SetTargetAngle(G4double val)
{
   
  fTargetAngle = val;
  *fTargetRotation = G4RotationMatrix();  // make it unit vector
  fTargetRotation->rotateY(fTargetAngle);
  //G4double angleRot = fTargetAngle;
 
G4RotationMatrix* yRot = new G4RotationMatrix;// Rotates X and Z axes only
     yRot->rotateY(-fTargetAngle);// Rotates 45 degrees

fTargetPhys->SetRotation(yRot);
    //logicTar->SetRotation(45 deg);
  
  // tell G4RunManager that we change the geometry
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
//std::cout<<"rotate of target2 is "<<GetTargetAngle()<<std::endl;
//std::ofstream file_energy_dep("total_particles_energy.txt", std::ios::app);
        //Выводим в файл
  //      file_energy_dep<<round(fTargetAngle/deg);//<<std::endl;
        //Закрываем поток вывода
 //       file_energy_dep.close();
}

void ExG4DetectorConstruction01::DefineCommands()
{
  // Define /B5/detector command directory using generic messenger class
  fMessenger = new G4GenericMessenger(this, 
                                      "/B5/detector/", 
                                      "Detector control");

  // targetAngle command
  auto& targetAngleCmd
    = fMessenger->DeclareMethodWithUnit("targetAngle","deg",
                                &ExG4DetectorConstruction01::SetTargetAngle, 
                                "Set rotation angle of the second arm.");
  targetAngleCmd.SetParameterName("angle", true);
  //armAngleCmd.SetRange("angle>=0. && angle<180.");
  targetAngleCmd.SetDefaultValue("30.");
    
}


