#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1

#include "G4UserSteppingAction.hh"

#include <vector>

class G4LogicalVolume;
class G4Step;

class EventAction;

/// Stepping action class

class SteppingAction : public G4UserSteppingAction {
public:
  SteppingAction(EventAction *eventAction, const std::vector<G4LogicalVolume*>& volumes);
  ~SteppingAction() override = default;

  // method from the base class
  void UserSteppingAction(const G4Step *) override;

private:
  EventAction *fEventAction = nullptr;
  const std::vector<G4LogicalVolume*>& fScoringVolumes;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
