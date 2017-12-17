// *******************************************************************
// * License and Disclaimer                                          *
// *                                                                 *
// * This software is copyright of Geant4 Associates International   *
// * Ltd (hereafter 'G4AI'). It is provided under the terms and      *
// * conditions described in the file 'LICENSE' included in the      *
// * software system.                                                *
// * Neither the authors of this software system nor G4AI make any   *
// * representation or warranty, express or implied, regarding this  *
// * software system or assume any liability for its use.            *
// * Please see the file 'LICENSE' for full disclaimer and the       *
// * limitation of liability.                                        *
// *******************************************************************
// $Id$
// John Allison  22nd May 2017

#include "Tangle2RunAction.hh"
#include "Tangle2Data.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"
#include <cassert>
#include <fstream>

Tangle2RunAction* Tangle2RunAction::fpMasterRunAction = 0;

namespace {
  G4Mutex runActionMutex = G4MUTEX_INITIALIZER;
}

Tangle2RunAction::Tangle2RunAction()
{
  if (G4Threading::IsMasterThread()) {
    fpMasterRunAction = this;
  }
  G4AutoLock lock(&runActionMutex);
}

Tangle2RunAction::~Tangle2RunAction()
{
  delete G4AnalysisManager::Instance();
}

void Tangle2RunAction::BeginOfRunAction(const G4Run*)
{
  G4cout
    << "Tangle2RunAction::BeginOfRunAction: Thread: "
    << G4Threading::G4GetThreadId()
    << G4endl;
  
  if (G4Threading::IsWorkerThread()) {

    Tangle2::nEvents   = 0;
    Tangle2::nEventsPh = 0;
   
  } else {  // Master thread

    Tangle2::nMasterEvents = 0;
    Tangle2::nMasterEventsPh = 0;
  }

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFirstNtupleId(1);
  
  analysisManager->CreateNtuple("Tangle2", "Tangle2");
  
  //energy deposited in crystals in A
  analysisManager->CreateNtupleDColumn("edep0");
  analysisManager->CreateNtupleDColumn("edep1");
  analysisManager->CreateNtupleDColumn("edep2");
  analysisManager->CreateNtupleDColumn("edep3");
  analysisManager->CreateNtupleDColumn("edep4");
  analysisManager->CreateNtupleDColumn("edep5");
  analysisManager->CreateNtupleDColumn("edep6");
  analysisManager->CreateNtupleDColumn("edep7");
  analysisManager->CreateNtupleDColumn("edep8");
  //energy deposited in crystals in B
  analysisManager->CreateNtupleDColumn("edep9");
  analysisManager->CreateNtupleDColumn("edep10");
  analysisManager->CreateNtupleDColumn("edep11");
  analysisManager->CreateNtupleDColumn("edep12");
  analysisManager->CreateNtupleDColumn("edep13");
  analysisManager->CreateNtupleDColumn("edep14");
  analysisManager->CreateNtupleDColumn("edep15");
  analysisManager->CreateNtupleDColumn("edep16");
  analysisManager->CreateNtupleDColumn("edep17"); 

  //energy deposited in collimator 
  analysisManager->CreateNtupleDColumn("edepColl1");
  analysisManager->CreateNtupleDColumn("edepColl2"); // 20

  //number of Compton scattering processes in each crystal
  analysisManager->CreateNtupleIColumn("nb_Compt0");
  analysisManager->CreateNtupleIColumn("nb_Compt1");
  analysisManager->CreateNtupleIColumn("nb_Compt2");
  analysisManager->CreateNtupleIColumn("nb_Compt3");
  analysisManager->CreateNtupleIColumn("nb_Compt4");
  analysisManager->CreateNtupleIColumn("nb_Compt5");
  analysisManager->CreateNtupleIColumn("nb_Compt6");
  analysisManager->CreateNtupleIColumn("nb_Compt7");
  analysisManager->CreateNtupleIColumn("nb_Compt8");
    
  analysisManager->CreateNtupleIColumn("nb_Compt9");
  analysisManager->CreateNtupleIColumn("nb_Compt10");
  analysisManager->CreateNtupleIColumn("nb_Compt11");
  analysisManager->CreateNtupleIColumn("nb_Compt12");
  analysisManager->CreateNtupleIColumn("nb_Compt13");
  analysisManager->CreateNtupleIColumn("nb_Compt14");
  analysisManager->CreateNtupleIColumn("nb_Compt15");
  analysisManager->CreateNtupleIColumn("nb_Compt16");
  analysisManager->CreateNtupleIColumn("nb_Compt17"); // 38

  //number of Compton scattering in the collimator
  analysisManager->CreateNtupleIColumn("nb_Compt_Coll");


  //position of first Compton in A
  analysisManager->CreateNtupleDColumn("XposA_1st");
  analysisManager->CreateNtupleDColumn("YposA_1st");
  analysisManager->CreateNtupleDColumn("ZposA_1st");
  //position of second Compton in A
  analysisManager->CreateNtupleDColumn("XposA_2nd");
  analysisManager->CreateNtupleDColumn("YposA_2nd");
  analysisManager->CreateNtupleDColumn("ZposA_2nd");
  //position of first Compton in B
  analysisManager->CreateNtupleDColumn("XposB_1st");
  analysisManager->CreateNtupleDColumn("YposB_1st");
  analysisManager->CreateNtupleDColumn("ZposB_1st");
  //position of second Compton in B
  analysisManager->CreateNtupleDColumn("XposB_2nd");
  analysisManager->CreateNtupleDColumn("YposB_2nd");
  analysisManager->CreateNtupleDColumn("ZposB_2nd");
  
  //angles --> theta and phi 
  //first Compton scatter
  analysisManager->CreateNtupleDColumn("ThetaA_1st");
  analysisManager->CreateNtupleDColumn("PhiA_1st");
  analysisManager->CreateNtupleDColumn("ThetaB_1st");
  analysisManager->CreateNtupleDColumn("PhiB_1st");
  analysisManager->CreateNtupleDColumn("dPhi_1st");
  //second Compton scatter
  analysisManager->CreateNtupleDColumn("ThetaA_2nd");
  analysisManager->CreateNtupleDColumn("PhiA_2nd");
  analysisManager->CreateNtupleDColumn("ThetaB_2nd");
  analysisManager->CreateNtupleDColumn("PhiB_2nd");
  
  analysisManager->CreateNtupleDColumn("dPhi_A1B2");
  analysisManager->CreateNtupleDColumn("dPhi_A2B1");
  analysisManager->CreateNtupleDColumn("dPhi_A2B2");
   
  analysisManager->FinishNtuple();
  
  analysisManager->OpenFile("Tangle2");
  
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  
}

namespace {
  G4Mutex mutex = G4MUTEX_INITIALIZER;
}

void Tangle2RunAction::EndOfRunAction(const G4Run* run)
{
  
  G4cout << G4endl;
  
  if (G4Threading::IsWorkerThread()) {
    
    G4cout
      << "Tangle2RunAction::EndOfRunAction: Thread: "
      << G4Threading::G4GetThreadId() << G4endl;
    
    G4cout << Tangle2::nEvents << " events, "
	   << ", " << Tangle2::nEventsPh << " 511 keV deposit events"
	   << G4endl;
    
    // Always use a lock when writing to a 
    // location that is shared by threads
    G4AutoLock lock(&mutex);
    Tangle2::nMasterEvents += Tangle2::nEvents;
    Tangle2::nMasterEventsPh += Tangle2::nEventsPh;
    
  } else {  // Master thread
    Tangle2::nMasterEvents += Tangle2::nEvents;
    Tangle2::nMasterEventsPh += Tangle2::nEventsPh;
    G4cout
      << "Tangle2RunAction::EndOfRunAction: Master thread: "
      << G4endl;
    
    G4cout << Tangle2::nMasterEvents   << " events, "
	   << Tangle2::nMasterEventsPh << " 511 keV deposit events"
	   << G4endl;
  }
  
  //   G4cout << G4endl;
  //   G4cout << " nA1B1 = " << Tangle2::nA1B1 << G4endl;
  //   G4cout << " nA1B2 = " << Tangle2::nA1B2 << G4endl;
  //   G4cout << " nA2B1 = " << Tangle2::nA2B1 << G4endl;
  //   G4cout << " nA2B2 = " << Tangle2::nA2B2 << G4endl;
  //   G4cout << G4endl;
  
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  man->Write();
  man->CloseFile();
  
}
