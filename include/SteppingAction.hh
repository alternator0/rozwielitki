#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1

#include "G4UserSteppingAction.hh"

class G4LogicalVolume;
class G4Step;

class EventAction;

/// Stepping action class

class SteppingAction : public G4UserSteppingAction {
public:
  SteppingAction(EventAction *eventAction, const G4LogicalVolume *volume);
  ~SteppingAction() override = default;

  // method from the base class
  void UserSteppingAction(const G4Step *) override;

private:
  EventAction *fEventAction = nullptr;
  const G4LogicalVolume *fScoringVolume = nullptr;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
