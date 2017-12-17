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

#include "Tangle2ActionInitialization.hh"

#include "Tangle2PrimaryGeneratorAction.hh"
#include "Tangle2RunAction.hh"
#include "Tangle2EventAction.hh"
#include "Tangle2TrackingAction.hh"
#include "Tangle2SteppingAction.hh"

Tangle2ActionInitialization::Tangle2ActionInitialization()
{}

Tangle2ActionInitialization::~Tangle2ActionInitialization()
{}

void Tangle2ActionInitialization::BuildForMaster() const
{
  SetUserAction(new Tangle2RunAction);
}

void Tangle2ActionInitialization::Build() const
{
  Tangle2RunAction* runAction = new Tangle2RunAction;
  
  Tangle2SteppingAction* steppingAction
    = new Tangle2SteppingAction(runAction);

  Tangle2EventAction* eventAction
    = new Tangle2EventAction(steppingAction);

  G4UserTrackingAction* trackingAction = new Tangle2TrackingAction;

  SetUserAction(new Tangle2PrimaryGeneratorAction);
  SetUserAction(runAction);
  SetUserAction(eventAction);
  SetUserAction(trackingAction);
  SetUserAction(steppingAction);
}
