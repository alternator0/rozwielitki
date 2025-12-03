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

namespace B1 {

G4VPhysicalVolume *DetectorConstruction::Construct() {

  // Get nist material manager
  G4NistManager *nist = G4NistManager::Instance();

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double worldSizeXY = 10 * cm;
  G4double worldSizeZ = 10 * cm;
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

  auto solidWorld =
      new G4Box("World", worldSizeXY, worldSizeXY, worldSizeZ); // name,x,y,z

  auto logicWorld = new G4LogicalVolume(solidWorld, // its solid
                                        worldMat,   // its material
                                        "World");   // its name

  auto physWorld = new G4PVPlacement(nullptr,         // no rotation
                                     G4ThreeVector(), // at (0,0,0)
                                     logicWorld,      // its logical volume
                                     "World",         // its name
                                     nullptr,         // its mother  volume
                                     false,           // no boolean operation
                                     0,               // copy number
                                     checkOverlaps);  // overlaps checking

  //
  //
  // Daphnia
  //
  //

  G4ThreeVector daphniaPos = G4ThreeVector(0 * cm, 0 * cm, 0 * cm);

  // Daphnia shape

  G4ThreeVector daphniaDimentions{2 / 2.0 * mm, 1.5 / 2.0 * mm, 1 / 2.0 * mm};

  G4Material *daphniaMat = nist->FindOrBuildMaterial("G4_WATER");

  G4Ellipsoid *solidDaphnia =
      new G4Ellipsoid("Daphnia", daphniaDimentions.x(), daphniaDimentions.y(),
                      daphniaDimentions.z());

  G4LogicalVolume *logicDaphnia =
      new G4LogicalVolume(solidDaphnia, daphniaMat, "Body");

  auto visAttributesDaphnia =
      new G4VisAttributes(G4Colour(1.0, 0.0, 0.5, 1.0)); // pink
  visAttributesDaphnia->SetVisibility(true);
  logicDaphnia->SetVisAttributes(visAttributesDaphnia);

  new G4PVPlacement(nullptr,        // no rotation
                    daphniaPos,     // at position
                    logicDaphnia,   // its logical volume
                    "Daphnia",      // its name
                    logicWorld,     // its mother  volume
                    false,          // no boolean operation
                    0,              // copy number
                    checkOverlaps); // overlaps checking

  //
  //
  //
  // Cell
  //
  //

  G4Material *cellMat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
  G4Material *cellMatInside = nist->FindOrBuildMaterial("G4_WATER");

  G4ThreeVector cellPos = G4ThreeVector(0 * cm, 0 * cm, 0 * cm);

  // Trapezoid shapes
  //
  G4double wallThickness = 0.3 * mm;
  G4double baseThickness = 0.5 * mm;

  G4double shapeOuterdxa = 25 * mm, shapeOuterdxb = (25 + 1.439) * mm;
  G4double shapeOuterdya = 25 * mm, shapeOuterdyb = (25 + 1.439) * mm;
  G4double shapeOuterdz = 10 * mm;
  auto solidShapeOuter =
      new G4Trd("OuterTRD", // its name
                shapeOuterdxa / 2, shapeOuterdxb / 2, shapeOuterdya / 2,
                shapeOuterdyb / 2, shapeOuterdz / 2); // its size

  G4double shapeInnerdxa = shapeOuterdxa - wallThickness * 2;
  G4double shapeInnerdxb = shapeOuterdxb - wallThickness * 2;
  G4double shapeInnerdya = shapeOuterdya - wallThickness * 2;
  G4double shapeInnerdyb = shapeOuterdyb - wallThickness * 2;
  G4double shapeInnerdz = shapeOuterdz - baseThickness;

  auto solidShapeInner =
      new G4Trd("InnerTRD", // its name
                shapeInnerdxa / 2, shapeInnerdxb / 2, shapeInnerdya / 2,
                shapeInnerdyb / 2, shapeInnerdz / 2); // its size

  auto logicCellOuter = new G4LogicalVolume(solidShapeOuter, // its solid
                                            cellMat,         // its material
                                            "CellTRD");      // its namespace

  auto logicCellInner =
      new G4LogicalVolume(solidShapeInner, cellMatInside, "CellInnerTRD");

  // cell visualas

  auto visAttributesInner =
      new G4VisAttributes(G4Colour(0.0, 0.0, 1.0, 0.2)); // blue
  visAttributesInner->SetVisibility(true);
  logicCellInner->SetVisAttributes(visAttributesInner);

  auto visAttributesOuter =
      new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.7)); // white
  visAttributesOuter->SetVisibility(true);
  logicCellOuter->SetVisAttributes(visAttributesOuter);

  // PhysicalVolume Cell

  new G4PVPlacement(nullptr,        // no rotation
                    cellPos,        // at position
                    logicCellOuter, // its logical volume
                    "CellTRD",      // its name
                    logicWorld,     // its mother  volume
                    false,          // no boolean operation
                    0,              // copy number
                    checkOverlaps); // overlaps checking
                                    //

  new G4PVPlacement(nullptr,                                //
                    G4ThreeVector(0, 0, baseThickness / 2), //
                    logicCellInner,                         //
                    "CellInnerTRD",                         //
                    logicCellOuter,                         //
                    false,                                  //
                    0,                                      //
                    checkOverlaps);                         //

  fScoringVolume = logicDaphnia;

  return physWorld;
}

} // namespace B1
