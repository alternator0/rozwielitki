#include "DetectorConstruction.hh"
#include <G4LogicalVolume.hh>
#ifndef B1ActionInitialization_h
#define B1ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class DetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization {
public:
  ActionInitialization(DetectorConstruction *detector);
  ~ActionInitialization() override = default;

  void BuildForMaster() const override;
  void Build() const override;

private:
  DetectorConstruction *fDetConstruction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
