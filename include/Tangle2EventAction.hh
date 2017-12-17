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

#ifndef Tangle2EventAction_hh
#define Tangle2EventAction_hh

#include "G4UserEventAction.hh"
#include "globals.hh"

class Tangle2RunAction;
class Tangle2VSteppingAction;

class Tangle2EventAction : public G4UserEventAction
{
public:

  Tangle2EventAction(Tangle2VSteppingAction*);

  virtual ~Tangle2EventAction();

  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);
  
private:
  
  Tangle2VSteppingAction* fpTangle2VSteppingAction;
};

#endif
