// definicja swiata i detektorow

#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Ellipsoid.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PhysicalVolumeModel.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trd.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VisAttributes.hh"
#include <G4Material.hh>
#include <G4ThreeVector.hh>
#include <array>
#include <format>

void DetectorConstruction::createDaphnia(const char *name, G4ThreeVector *pos,
                                         G4LogicalVolume *motherVolume,
                                         G4Material *material, int copyNo,
                                         G4bool checkOverlaps = true,
                                         G4VisAttributes *visAttr = nullptr) {
  const G4ThreeVector daphniaDimentions{2 / 2.0 * mm, 1.5 / 2.0 * mm,
                                        1 / 2.0 * mm};

  G4Ellipsoid *solidDaphnia =
      new G4Ellipsoid(name, daphniaDimentions.x(), daphniaDimentions.y(),
                      daphniaDimentions.z());

  G4LogicalVolume *logicDaphnia =
      new G4LogicalVolume(solidDaphnia, material, name);

  if (visAttr != nullptr) {
    logicDaphnia->SetVisAttributes(visAttr);
  }

  new G4PVPlacement(nullptr,        // no rotation
                    *pos,           // at position
                    logicDaphnia,   // its logical volume
                    name,           // its name
                    motherVolume,   // its mother  volume
                    false,          // no boolean operation
                    copyNo,         // copy number
                    checkOverlaps); // overlaps

  // add Daphnia to detection
  //  this->fScoringVolumes.push_back(logicDaphnia);
}

// Cell sizes

constexpr G4double wallThickness = 0.3 * mm;
constexpr G4double baseThickness = 0.5 * mm;

constexpr G4double shapeOuterdxa = 25 * mm, shapeOuterdxb = (25 + 1.439) * mm;
constexpr G4double shapeOuterdya = 25 * mm, shapeOuterdyb = (25 + 1.439) * mm;
constexpr G4double shapeOuterdz = 10 * mm;

constexpr G4double shapeInnerdxa = shapeOuterdxa - wallThickness * 2;
constexpr G4double shapeInnerdxb = shapeOuterdxb - wallThickness * 2;
constexpr G4double shapeInnerdya = shapeOuterdya - wallThickness * 2;
constexpr G4double shapeInnerdyb = shapeOuterdyb - wallThickness * 2;
constexpr G4double shapeInnerdz = shapeOuterdz - baseThickness;

void DetectorConstruction::createCellWithDaphnia(
    const char *name, G4ThreeVector *pos, G4LogicalVolume *motherVolume,
    G4Material *cellMat, G4Material *cellMatInside, G4Material *daphniaMat,
    int copyNo, G4bool checkOverlaps = true,
    G4VisAttributes *visAttrInner = nullptr,
    G4VisAttributes *visAttrOuter = nullptr,
    G4VisAttributes *visAttrDaphnia = nullptr) {
  // Cell shapes, logical volumes, physical volumes

  auto innerName = std::format("Inner{}", name);
  auto outerName = std::format("Outer{}", name);
  auto cellName = std::format("Cell{}", name);

  auto solidShapeOuter1 =
      new G4Trd(outerName.c_str(), // its name
                shapeOuterdxa / 2, shapeOuterdxb / 2, shapeOuterdya / 2,
                shapeOuterdyb / 2, shapeOuterdz / 2); // its size

  auto solidShapeInner1 =
      new G4Trd(innerName.c_str(), // its name
                shapeInnerdxa / 2, shapeInnerdxb / 2, shapeInnerdya / 2,
                shapeInnerdyb / 2, shapeInnerdz / 2); // its size

  auto logicCellOuter1 = new G4LogicalVolume(solidShapeOuter1,  // its solid
                                             cellMat,           // its material
                                             cellName.c_str()); // its namespace

  auto logicCellInner1 =
      new G4LogicalVolume(solidShapeInner1, cellMatInside, innerName.c_str());
  this->fScoringVolumes.push_back(logicCellInner1);

  // cell visualas
  if (visAttrInner != nullptr)
    logicCellInner1->SetVisAttributes(visAttrInner);

  if (visAttrOuter != nullptr)
    logicCellOuter1->SetVisAttributes(visAttrOuter);

  // PhysicalVolume Cell

  new G4PVPlacement(nullptr,          // no rotation
                    *pos,             // at position
                    logicCellOuter1,  // its logical volume
                    cellName.c_str(), // its name
                    motherVolume,     // its mother  volume
                    false,            // no boolean operation
                    copyNo,           // copy number
                    checkOverlaps);   // overlaps checking

  new G4PVPlacement(nullptr, G4ThreeVector(0, 0, baseThickness / 2),
                    logicCellInner1, innerName.c_str(), logicCellOuter1, false,
                    copyNo, checkOverlaps);

  //  auto daphniaPos = G4ThreeVector();
  //  this->createDaphnia(std::format("Daphnia{}", name).c_str(), &daphniaPos,
  //                      logicCellInner1, daphniaMat, copyNo, checkOverlaps,
  //                      visAttrDaphnia);
}

G4VPhysicalVolume *DetectorConstruction::Construct() {

  // Get nist material manager
  G4NistManager *nist = G4NistManager::Instance();

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;
  //
  //
  // World
  //
  //
  G4double worldSizeX = 50 * cm;
  G4double worldSizeY = 30 * cm;
  G4double worldSizeZ = 15 * cm;
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

  auto solidWorld =
      new G4Box("World", worldSizeX, worldSizeY, worldSizeZ); // name,x,y,z

  auto logicWorld = new G4LogicalVolume(solidWorld, // its solid
                                        worldMat,   // its material
                                        "World");   // its name

  auto physWorld = new G4PVPlacement(nullptr,                // no rotation
                                     G4ThreeVector(0, 0, 0), // at (0,0,0)
                                     logicWorld,     // its logical volume
                                     "World",        // its name
                                     nullptr,        // its mother  volume
                                     false,          // no boolean operation
                                     0,              // copy number
                                     checkOverlaps); // overlaps checking
                                                     //

  //----------------------------------------------------------------------------------------
  // Cells and daphnias

  // placements of centers of cells with daphnia
  //  std::array<G4ThreeVector, 4> cPos = {
  //      G4ThreeVector(14.2195 * mm, 14.2195 * mm, 0 * mm),
  //      G4ThreeVector(-14.2195 * mm, -14.2195 * mm, 0 * mm),
  //      G4ThreeVector(-14.2195 * mm, 14.2195 * mm, 0 * mm),
  //      G4ThreeVector(14.2195 * mm, -14.2195 * mm, 0 * mm)

  //  };

  std::array<G4ThreeVector, 10> cPos = {
      G4ThreeVector(-185 * mm, 40 * mm, 0 * mm),     // 0
      G4ThreeVector(-185 * mm, 5 * mm, 0 * mm),      // 1
      G4ThreeVector(-185 * mm, -30 * mm, 0 * mm),    // 2
      G4ThreeVector(-185 * mm, -60 * mm, 0 * mm),    // 3
      G4ThreeVector(-147.5 * mm, 17.5 * mm, 0 * mm), // 4
      G4ThreeVector(-145 * mm, -50 * mm, 0 * mm),    // 5
      G4ThreeVector(-65 * mm, -85 * mm, 0 * mm),     // 6
      G4ThreeVector(60 * mm, -85 * mm, 0 * mm),      // 7
      G4ThreeVector(60 * mm, 60 * mm, 0 * mm),       // 8
      G4ThreeVector(90 * mm, 60 * mm, 0 * mm)        // 9

  };

  // Cells
  G4Material *cellMat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
  G4Material *cellMatInside = nist->FindOrBuildMaterial("G4_WATER");

  // Daphnia
  G4Material *daphniaMat = nist->FindOrBuildMaterial("G4_WATER");
  auto visAttributesDaphnia =
      new G4VisAttributes(G4Colour(1.0, 0.0, 0.5, 1.0)); // pink
  visAttributesDaphnia->SetVisibility(true);

  auto visAttributesInner =
      new G4VisAttributes(G4Colour(0.0, 0.0, 1.0, 0.2)); // blue
  visAttributesInner->SetVisibility(true);

  auto visAttributesOuter =
      new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.7)); // white
  visAttributesOuter->SetVisibility(true);

  for (int i = 0; i < cPos.size(); i++) {
    createCellWithDaphnia(std::format("TRD{}", i).c_str(), &cPos.at(i),
                          logicWorld, cellMat, cellMatInside, daphniaMat, i,
                          checkOverlaps, visAttributesInner, visAttributesOuter,
                          visAttributesDaphnia);
  }

  //
  // Foundation pad
  //
  // properities of pad
  G4ThreeVector padDimentions{50 * cm, 30 * cm, 2 * cm};

  G4ThreeVector padPos{0, 0, -(padDimentions.z() / 2. + shapeOuterdz / 2) * mm};
  G4Material *padMat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
  auto visAttributesPad =
      new G4VisAttributes(G4Colour(0.3, 0.3, 0.3, 1.0)); // gray
  visAttributesPad->SetVisibility(true);

  // Pad shape, logical volume, physical volume

  G4Box *solidPad = new G4Box("Pad", padDimentions.x() / 2,
                              padDimentions.y() / 2, padDimentions.z() / 2);

  G4LogicalVolume *logicPad = new G4LogicalVolume(solidPad, padMat, "Pad");
  logicPad->SetVisAttributes(visAttributesPad);

  new G4PVPlacement(nullptr,        // no rotation
                    padPos,         // at position
                    logicPad,       // its logical volume
                    "Pad1",         // its name
                    logicWorld,     // its mother  volume
                    false,          // no boolean operation
                    0,              // copy number
                    checkOverlaps); // overlaps checking

  //  fScoringVolume = logicDaphnia1;

  G4double totalWaterMass{fScoringVolumes.at(0)->GetMass()};

  // for (auto volume : this->fScoringVolumes) {
  //   totalWaterMass += volume->GetMass();
  // }

  // Wypisujemy wynik do terminala podczas uruchamiania symulacji
  G4cout << "\n==================================================" << G4endl;
  G4cout << "=== PODSUMOWANIE GEOMETRII ===" << G4endl;
  G4cout << "Liczba rozwielitek: " << this->fScoringVolumes.size() << G4endl;
  G4cout << "Masa wody w jednej celce: " << totalWaterMass / kg << " kg"
         << G4endl;
  G4cout << "Masa wody w jednej celce: " << totalWaterMass / g << " g"
         << G4endl;
  G4cout << "==================================================\n" << G4endl;

  return physWorld;
}
