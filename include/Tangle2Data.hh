#ifndef Tangle2Data_hh
#define Tangle2Data_hh

#include "globals.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"

#include <fstream>

#include "g4root.hh"
#include "G4ThreeVector.hh"

class G4VPhysicalVolume;

// This is a lazy way of sharing memory. To avoid polluting the global
// namespace we define our own distinctive namespace.
namespace Tangle2 {

  extern G4bool positrons;
  extern G4bool fixedAxis;
  extern G4bool perpPol;
  extern G4bool polYZ;
  
  extern G4int nMasterEvents;
  extern G4int nMasterEventsPh;  
  
  // Worker quantities
  extern G4ThreadLocal G4int nEvents;
  extern G4ThreadLocal G4int nEventsPh;
  extern G4ThreadLocal G4double eDepEvent;
  extern G4ThreadLocal G4double eDepCryst[18];
  extern G4ThreadLocal G4double eDepColl1;
  extern G4ThreadLocal G4double eDepColl2;
  extern G4ThreadLocal G4int nb_Compt[19];
  extern G4ThreadLocal G4ThreeVector posA_1;
  extern G4ThreadLocal G4ThreeVector posB_1;
  extern G4ThreadLocal G4ThreeVector posA_2;
  extern G4ThreadLocal G4ThreeVector posB_2;
  extern G4ThreadLocal G4double thetaA;
  extern G4ThreadLocal G4double thetaB;
  extern G4ThreadLocal G4double phiA;
  extern G4ThreadLocal G4double phiB;
  extern G4ThreadLocal G4double dphi;
  extern G4ThreadLocal G4double thetaA2;
  extern G4ThreadLocal G4double thetaB2;
  extern G4ThreadLocal G4double phiA2;
  extern G4ThreadLocal G4double phiB2;

  extern G4ThreadLocal G4double dphiA1B2;
  extern G4ThreadLocal G4double dphiA2B1;
  extern G4ThreadLocal G4double dphiA2B2;

  extern G4ThreadLocal G4int nA1B1;
  extern G4ThreadLocal G4int nA2B1;
  extern G4ThreadLocal G4int nA1B2;
  extern G4ThreadLocal G4int nA2B2;
  
}

#endif
