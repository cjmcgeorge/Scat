#include "Tangle2Data.hh"

G4bool Tangle2::positrons = false;
G4bool Tangle2::fixedAxis = false;
G4bool Tangle2::perpPol   = false;
G4bool Tangle2::polYZ     = false;

// For runs with multi-threading
G4int Tangle2::nMasterEventsPh = 0;
G4int Tangle2::nMasterEvents = 0;

// Worker quantities
G4ThreadLocal G4int Tangle2::nEvents = 0;
G4ThreadLocal G4int Tangle2::nEventsPh = 0;
G4ThreadLocal G4double Tangle2::eDepEvent = 0.;
G4ThreadLocal G4double Tangle2::eDepCryst[18] ={0.};
G4ThreadLocal G4double Tangle2::eDepColl1 =0.;
G4ThreadLocal G4double Tangle2::eDepColl2 =0.;

//G4ThreadLocal G4double Tangle2::thetaColl = 0;

G4ThreadLocal G4int Tangle2::nb_Compt[18] ={0};
G4ThreadLocal G4int Tangle2::nb_Compt_Coll = 0;
G4ThreadLocal G4ThreeVector Tangle2::posA_1 = G4ThreeVector();
G4ThreadLocal G4ThreeVector Tangle2::posB_1 = G4ThreeVector();
G4ThreadLocal G4ThreeVector Tangle2::posA_2 = G4ThreeVector();
G4ThreadLocal G4ThreeVector Tangle2::posB_2 = G4ThreeVector();
G4ThreadLocal G4double Tangle2::thetaA = 0;
G4ThreadLocal G4double Tangle2::thetaB = 0;
G4ThreadLocal G4double Tangle2::phiA = 0;
G4ThreadLocal G4double Tangle2::phiB = 0;
G4ThreadLocal G4double Tangle2::dphi = 0;
G4ThreadLocal G4double Tangle2::thetaA2 = 0;
G4ThreadLocal G4double Tangle2::thetaB2 = 0;
G4ThreadLocal G4double Tangle2::phiA2 = 0;
G4ThreadLocal G4double Tangle2::phiB2 = 0;
G4ThreadLocal G4double Tangle2::dphiA1B2 = 0;
G4ThreadLocal G4double Tangle2::dphiA2B1 = 0;
G4ThreadLocal G4double Tangle2::dphiA2B2 = 0;

// create new dphis where the LOR for scattered 
// events is used for the 'beam' ie pretent that 
// scattering is not known about:
// dphiA1B2_S e.g.

G4ThreadLocal G4int Tangle2::nA1B1 = 0;
G4ThreadLocal G4int Tangle2::nA2B1 = 0;
G4ThreadLocal G4int Tangle2::nA1B2 = 0;
G4ThreadLocal G4int Tangle2::nA2B2 = 0;

