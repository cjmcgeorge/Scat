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

#ifndef Tangle2RunAction_hh
#define Tangle2RunAction_hh

#include "G4UserRunAction.hh"

#include <vector>

class G4Run;

class Tangle2RunAction : public G4UserRunAction
{
public:
  Tangle2RunAction();
  virtual ~Tangle2RunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);
  
private:
  static Tangle2RunAction* fpMasterRunAction;
};

#endif
