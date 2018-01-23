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

// An intermediate inheritable class for stepping action.  It introduces a
// BeginOfEventAction and an EndOfEventAction - very useful.  So any
// stepping action in this project should inherit.
//
// BeginOfEventAction and EndOfEventAction are called from Tangle2EventAction.

#ifndef Tangle2VSteppingAction_hh
#define Tangle2VSteppingAction_hh

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class Tangle2VSteppingAction : public G4UserSteppingAction
{
public:
  virtual void BeginOfEventAction() {};
  virtual void EndOfEventAction() {};
};

#endif
