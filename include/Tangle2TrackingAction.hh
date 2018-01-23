#ifndef Tangle2TrackingAction_hh
#define Tangle2TrackingAction_hh

#include "G4UserTrackingAction.hh"

class Tangle2TrackingAction : public G4UserTrackingAction
{
public:
  virtual void PreUserTrackingAction(const G4Track*);
  virtual void PostUserTrackingAction(const G4Track*);
};

#endif
