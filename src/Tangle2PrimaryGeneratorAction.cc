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
// Gary Smith    27th Nov 2017

#include "Tangle2PrimaryGeneratorAction.hh"

#include "Tangle2Data.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ChargedGeantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4RandomDirection.hh"

#include "G4GeneralParticleSource.hh"


Tangle2PrimaryGeneratorAction::Tangle2PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
}

Tangle2PrimaryGeneratorAction::~Tangle2PrimaryGeneratorAction()
{
  delete fParticleGun; 
}

void Tangle2PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;

  // Use positrons or
  // back to back photons
  G4bool generatePositrons = false;
  if(Tangle2::positrons)
    generatePositrons = true;
  
  // For back to back photons
  // a fixed axis beam can be chosen
  G4bool generateFixedAxis = false; 
  
  if (Tangle2::fixedAxis){
    if(!generatePositrons)
      generateFixedAxis = true;
    else
      G4cout << " Invalid choice: positrons with fixed axis " << G4endl;
  }
  
  G4bool generatePerpPol = false;
  
  // For back to back photons
  // the relative polarisation
  // can be orthogonal or random
  if(Tangle2::perpPol){
    if(!generatePositrons) 
      generatePerpPol = true;
    else 
      G4cout << " Invalid choice: positrons with perp pol  " << G4endl;
  }
  
  G4bool generatePolYZ = false;
  
  if(Tangle2::polYZ)
    generatePolYZ = true;
  
  // vertex
  G4double x0  = 0*cm, y0  = 0*cm, z0  = 0*cm;
  
  //-----------------------Back to back photons------------------------ 
  if(!generatePositrons){
    
    G4double a = 10;
    //Generate two random numbers between 1 and -1
    G4double b = (2*(( (G4double) rand() / (RAND_MAX)) - 0.5));
    G4double c = (2*(( (G4double) rand() / (RAND_MAX)) - 0.5));
    
    if (generateFixedAxis){
      a = 1;
      b = 0;
      c = 0;
    }
    
    // random direction +/- 8deg about x-axis
    // or x-axis (generateFixedAxis)
    G4ThreeVector x_axis = G4ThreeVector(a, b, c); 
    
    // Photon 1
    fParticleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
    fParticleGun->SetParticleEnergy(511*keV);
    
    fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
    fParticleGun->SetParticleMomentumDirection(x_axis);
    
    G4ThreeVector random = G4RandomDirection();
    
    random = random.cross(x_axis);
    
    if(generatePolYZ)
      fParticleGun->SetParticlePolarization(G4ThreeVector(0,1,0));
    else
      fParticleGun->SetParticlePolarization(random);
    
    fParticleGun->GeneratePrimaryVertex(anEvent);
    
    // Photon 2
    fParticleGun->SetParticleEnergy(511*keV);
    fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
    fParticleGun->SetParticleMomentumDirection(-x_axis);
    
    if(!generatePerpPol)
      random = G4RandomDirection().cross(x_axis);
    
    G4ThreeVector PerpPolarization = x_axis.cross(random);
    
    if(generatePolYZ)
      fParticleGun->SetParticlePolarization(G4ThreeVector(0,0,1));
    else
      fParticleGun->SetParticlePolarization(PerpPolarization);
        
    fParticleGun->GeneratePrimaryVertex(anEvent);
  } // end of: if(!generatePositrons){
  else { // if (generatePositrons)
    
    fParticleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e+"));
    
    // To do: investigate positron range
    fParticleGun->SetParticleEnergy(0*keV);
    
    fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
    
    //create vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
  }
  
}

