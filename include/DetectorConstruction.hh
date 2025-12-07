#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4VisAttributes.hh"
#include <G4Material.hh>
#include <G4ThreeVector.hh>

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
  DetectorConstruction() = default;
  ~DetectorConstruction() override = default;

  G4VPhysicalVolume *Construct() override;

  const std::vector<G4LogicalVolume*>& GetScoringVolumes() const { return this->fScoringVolumes; }

protected:
  std::vector<G4LogicalVolume*> fScoringVolumes;

  void createDaphnia(
    const char* name,
    G4ThreeVector* pos,
    G4LogicalVolume* motherVolume,
    G4Material* material,
    G4bool checkOverlaps,
    G4VisAttributes* visAttr
  );

  void createCellWithDaphnia(
    const char* name,
    G4ThreeVector* pos,
    G4LogicalVolume* motherVolume,
    G4Material* cellMat,
    G4Material* cellMatInside,
    G4Material* daphniaMat,
    G4bool checkOverlaps,
    G4VisAttributes* visAttrInner,
    G4VisAttributes* visAttrOuter,
    G4VisAttributes* visAttrDaphnia
  );
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
