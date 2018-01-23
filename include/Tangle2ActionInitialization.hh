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

#ifndef Tangle2ActionInitialization_hh
#define Tangle2ActionInitialization_hh 1

#include "G4VUserActionInitialization.hh"

class Tangle2ActionInitialization : public G4VUserActionInitialization
{
public:
  Tangle2ActionInitialization();
  virtual ~Tangle2ActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;
};

#endif


