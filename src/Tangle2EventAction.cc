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

#include "Tangle2EventAction.hh"

#include "Tangle2Data.hh"
#include "Tangle2RunAction.hh"
#include "Tangle2VSteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

#include "G4Event.hh"

Tangle2EventAction::Tangle2EventAction
(Tangle2VSteppingAction* onePhotonSteppingAction)
: fpTangle2VSteppingAction(onePhotonSteppingAction)
{}

Tangle2EventAction::~Tangle2EventAction()
{
delete G4AnalysisManager::Instance();
}

void Tangle2EventAction::BeginOfEventAction(const G4Event*)
{
  fpTangle2VSteppingAction->BeginOfEventAction();
  
  Tangle2::nEvents += 1;

  //  G4cout << G4endl;
  //  G4cout << " -----------------" << G4endl;
  //  G4cout << "  event  " << (Tangle2::nEvents-1) << G4endl;
  
  // (re)initialise output variables
  for (G4int i = 0; i<18; i++)
    Tangle2::eDepCryst[i] = 0.;
  Tangle2::eDepColl1 = 0;
  Tangle2::eDepColl2 = 0;

  for (G4int i = 0; i<18; i++)
    Tangle2::nb_Compt[i] = 0.;
    Tangle2::nb_Compt_Coll = 0.;
  Tangle2::posA_1 = G4ThreeVector(-99.,-99.,-99.);
  Tangle2::posA_2 = G4ThreeVector(-99.,-99.,-99.);
  Tangle2::posB_1 = G4ThreeVector(-99.,-99.,-99.);
  Tangle2::posB_2 = G4ThreeVector(-99.,-99.,-99.);
  Tangle2::thetaA = 0;
  Tangle2::thetaB = 0;
  Tangle2::phiA = 0;
  Tangle2::phiB = 0;
  Tangle2::dphi = -99;
  Tangle2::thetaA2 = 500;
  Tangle2::thetaB2 = 500;
  Tangle2::phiA2 = 500;
  Tangle2::phiB2 = 500;
  
  Tangle2::dphiA1B2 = -99;
  Tangle2::dphiA2B1 = -99;
  Tangle2::dphiA2B2 = -99;
  
}

void Tangle2EventAction::EndOfEventAction(const G4Event*)
{   
  fpTangle2VSteppingAction->EndOfEventAction();
  
  G4int nb_HitsA = 0, nb_HitsB = 0;
  G4double eDepEvent = 0., eThres = 5*keV;
  
  // record number of hits above threshold
  // and total energy deposited 
  for (G4int i = 0; i < 9 ; i++){
    // Array A
    if (Tangle2::eDepCryst[i] > eThres){
      nb_HitsA += 1;
      eDepEvent += Tangle2::eDepCryst[i];
    }
    // Array B
    if (Tangle2::eDepCryst[i+9] > eThres){
      nb_HitsB += 1;
      eDepEvent += Tangle2::eDepCryst[i+9];
    }
  }
  
  // Output to the root file 
  // 4 and 13 are the central crystals
  if ((Tangle2::eDepCryst[4]  > eThres) && 
      (Tangle2::eDepCryst[13] > eThres) &&  
            (Tangle2::thetaA !=0)             &&
      (Tangle2::thetaB !=0)
      ){
    G4cout << "Conditional Satisfied!" << G4endl;
    
    G4AnalysisManager* man = G4AnalysisManager::Instance();

    for (G4int i = 0 ; i < 18 ; i++)
      man->FillNtupleDColumn(i, Tangle2::eDepCryst[i]/MeV);
    
    man->FillNtupleDColumn(18, Tangle2::eDepColl1/MeV);
    man->FillNtupleDColumn(19, Tangle2::eDepColl2/MeV);
    
    for (G4int i = 0 ; i < 18 ; i++)
      man->FillNtupleIColumn(i+20, Tangle2::nb_Compt[i]);
    
    man->FillNtupleDColumn(38, Tangle2::posA_1[0]/mm);
    man->FillNtupleDColumn(39, Tangle2::posA_1[1]/mm);
    man->FillNtupleDColumn(40, Tangle2::posA_1[2]/mm);
    
    man->FillNtupleDColumn(41, Tangle2::posA_2[0]/mm);
    man->FillNtupleDColumn(42, Tangle2::posA_2[1]/mm);
    man->FillNtupleDColumn(43, Tangle2::posA_2[2]/mm);
    
    man->FillNtupleDColumn(44, Tangle2::posB_1[0]/mm);
    man->FillNtupleDColumn(45, Tangle2::posB_1[1]/mm);
    man->FillNtupleDColumn(46, Tangle2::posB_1[2]/mm);
    
    man->FillNtupleDColumn(47, Tangle2::posB_2[0]/mm);
    man->FillNtupleDColumn(48, Tangle2::posB_2[1]/mm);
    man->FillNtupleDColumn(49, Tangle2::posB_2[2]/mm);
    
    man->FillNtupleDColumn(50, Tangle2::thetaA/radian);
    man->FillNtupleDColumn(51, Tangle2::phiA/radian);
    
    man->FillNtupleDColumn(52, Tangle2::thetaB/radian);
    man->FillNtupleDColumn(53, Tangle2::phiB/radian);
    
    man->FillNtupleDColumn(54, Tangle2::dphi/radian);
    
    man->FillNtupleDColumn(55, Tangle2::thetaA2/radian);
    man->FillNtupleDColumn(56, Tangle2::phiA2/radian);
    
    man->FillNtupleDColumn(57, Tangle2::thetaB2/radian);
    man->FillNtupleDColumn(58, Tangle2::phiB2/radian);
    
    man->FillNtupleDColumn(59, Tangle2::dphiA1B2/radian);
    man->FillNtupleDColumn(60, Tangle2::dphiA2B1/radian);
    man->FillNtupleDColumn(61, Tangle2::dphiA2B2/radian);

    //print number of compton scatters in the collimator 
   
    man->FillNtupleDColumn(62, Tangle2::nb_Compt_Coll);
    
    
    man->AddNtupleRow();
  }
  
  // Count total number events with energy 
  // dep. in central crystals
  if ((Tangle2::eDepCryst[4]  > eThres) && 
      (Tangle2::eDepCryst[13] > eThres)){
    Tangle2::nEventsPh += 1;
  }
  
} // end of: void Tangle2EventAction::EndOfEventAction...
