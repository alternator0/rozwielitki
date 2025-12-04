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
#include <G4ThreeVector.hh>
#include <array>

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

  //----------------------------------------------------------------------------------------
  // Cells and daphnias

  // placements of centers of cells with daphnia
  std::array<G4ThreeVector, 4> cPos = {
      G4ThreeVector(14.2195 * mm, 14.2195 * mm, 0 * mm),
      G4ThreeVector(-14.2195 * mm, -14.2195 * mm, 0 * mm),
      G4ThreeVector(-14.2195 * mm, 14.2195 * mm, 0 * mm),
      G4ThreeVector(14.2195 * mm, -14.2195 * mm, 0 * mm)};

  //
  //
  // Daphnia
  //
  //
  // properities of a daphnia
  G4ThreeVector daphniaDimentions{2 / 2.0 * mm, 1.5 / 2.0 * mm, 1 / 2.0 * mm};

  G4Material *daphniaMat = nist->FindOrBuildMaterial("G4_WATER");

  auto visAttributesDaphnia =
      new G4VisAttributes(G4Colour(1.0, 0.0, 0.5, 1.0)); // pink
  visAttributesDaphnia->SetVisibility(true);
  //
  // Daphnia 1
  //

  G4ThreeVector daphniaPos1 = cPos.at(0);
  // Daphnia shape, logical volume, physical volume

  G4Ellipsoid *solidDaphnia1 =
      new G4Ellipsoid("Daphnia1", daphniaDimentions.x(), daphniaDimentions.y(),
                      daphniaDimentions.z());

  G4LogicalVolume *logicDaphnia1 =
      new G4LogicalVolume(solidDaphnia1, daphniaMat, "Daphnia1");

  logicDaphnia1->SetVisAttributes(visAttributesDaphnia);

  new G4PVPlacement(nullptr,        // no rotation
                    daphniaPos1,    // at position
                    logicDaphnia1,  // its logical volume
                    "Daphnia1",     // its name
                    logicWorld,     // its mother  volume
                    false,          // no boolean operation
                    0,              // copy number
                    checkOverlaps); // overlaps checking
  //
  // Daphnia 2
  //

  G4ThreeVector daphniaPos2 = cPos.at(1);
  // Daphnia shape, logical volume, physical volume

  G4Ellipsoid *solidDaphnia2 =
      new G4Ellipsoid("Daphnia2", daphniaDimentions.x(), daphniaDimentions.y(),
                      daphniaDimentions.z());

  G4LogicalVolume *logicDaphnia2 =
      new G4LogicalVolume(solidDaphnia2, daphniaMat, "Daphnia2");

  logicDaphnia2->SetVisAttributes(visAttributesDaphnia);

  new G4PVPlacement(nullptr,        // no rotation
                    daphniaPos2,    // at position
                    logicDaphnia2,  // its logical volume
                    "Daphnia2",     // its name
                    logicWorld,     // its mother  volume
                    false,          // no boolean operation
                    0,              // copy number
                    checkOverlaps); // overlaps checking
  //
  // Daphnia 3
  //

  G4ThreeVector daphniaPos3 = cPos.at(2);
  // Daphnia shape, logical volume, physical volume

  G4Ellipsoid *solidDaphnia3 =
      new G4Ellipsoid("Daphnia3", daphniaDimentions.x(), daphniaDimentions.y(),
                      daphniaDimentions.z());

  G4LogicalVolume *logicDaphnia3 =
      new G4LogicalVolume(solidDaphnia3, daphniaMat, "Daphnia3");

  logicDaphnia3->SetVisAttributes(visAttributesDaphnia);

  new G4PVPlacement(nullptr,        // no rotation
                    daphniaPos3,    // at position
                    logicDaphnia3,  // its logical volume
                    "Daphnia3",     // its name
                    logicWorld,     // its mother  volume
                    false,          // no boolean operation
                    0,              // copy number
                    checkOverlaps); // overlaps checking
                                    //
  //
  // Daphnia 4
  //

  G4ThreeVector daphniaPos4 = cPos.at(3);
  // Daphnia shape, logical volume, physical volume

  G4Ellipsoid *solidDaphnia4 =
      new G4Ellipsoid("Daphnia4", daphniaDimentions.x(), daphniaDimentions.y(),
                      daphniaDimentions.z());

  G4LogicalVolume *logicDaphnia4 =
      new G4LogicalVolume(solidDaphnia4, daphniaMat, "Daphnia4");

  logicDaphnia4->SetVisAttributes(visAttributesDaphnia);

  new G4PVPlacement(nullptr,        // no rotation
                    daphniaPos4,    // at position
                    logicDaphnia4,  // its logical volume
                    "Daphnia3",     // its name
                    logicWorld,     // its mother  volume
                    false,          // no boolean operation
                    0,              // copy number
                    checkOverlaps); // overlaps checking
                                    //
  //
  //
  // Cells
  //
  //
  // properities of a cell
  G4Material *cellMat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
  G4Material *cellMatInside = nist->FindOrBuildMaterial("G4_WATER");

  G4double wallThickness = 0.3 * mm;
  G4double baseThickness = 0.5 * mm;

  G4double shapeOuterdxa = 25 * mm, shapeOuterdxb = (25 + 1.439) * mm;
  G4double shapeOuterdya = 25 * mm, shapeOuterdyb = (25 + 1.439) * mm;
  G4double shapeOuterdz = 10 * mm;

  G4double shapeInnerdxa = shapeOuterdxa - wallThickness * 2;
  G4double shapeInnerdxb = shapeOuterdxb - wallThickness * 2;
  G4double shapeInnerdya = shapeOuterdya - wallThickness * 2;
  G4double shapeInnerdyb = shapeOuterdyb - wallThickness * 2;
  G4double shapeInnerdz = shapeOuterdz - baseThickness;

  auto visAttributesInner =
      new G4VisAttributes(G4Colour(0.0, 0.0, 1.0, 0.2)); // blue
  visAttributesInner->SetVisibility(true);

  auto visAttributesOuter =
      new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.7)); // white
  visAttributesOuter->SetVisibility(true);

  //
  // Cell 1
  //
  G4ThreeVector cellPos1 = cPos.at(0);
  // Cell shapes, logical volumes, physical volumes

  auto solidShapeOuter1 =
      new G4Trd("OuterTRD1", // its name
                shapeOuterdxa / 2, shapeOuterdxb / 2, shapeOuterdya / 2,
                shapeOuterdyb / 2, shapeOuterdz / 2); // its size

  auto solidShapeInner1 =
      new G4Trd("InnerTRD1", // its name
                shapeInnerdxa / 2, shapeInnerdxb / 2, shapeInnerdya / 2,
                shapeInnerdyb / 2, shapeInnerdz / 2); // its size

  auto logicCellOuter1 = new G4LogicalVolume(solidShapeOuter1, // its solid
                                             cellMat,          // its material
                                             "CellTRD1");      // its namespace

  auto logicCellInner1 =
      new G4LogicalVolume(solidShapeInner1, cellMatInside, "InnerTRD1");

  // cell visualas

  logicCellInner1->SetVisAttributes(visAttributesInner);

  logicCellOuter1->SetVisAttributes(visAttributesOuter);

  // PhysicalVolume Cell

  new G4PVPlacement(nullptr,         // no rotation
                    cellPos1,        // at position
                    logicCellOuter1, // its logical volume
                    "CellTRD1",      // its name
                    logicWorld,      // its mother  volume
                    false,           // no boolean operation
                    0,               // copy number
                    checkOverlaps);  // overlaps checking
                                     //

  new G4PVPlacement(nullptr,                                //
                    G4ThreeVector(0, 0, baseThickness / 2), //
                    logicCellInner1,                        //
                    "InnerTRD1",                            //
                    logicCellOuter1,                        //
                    false,                                  //
                    0,                                      //
                    checkOverlaps);                         //
                                                            //

  //
  // Cell 2
  //
  G4ThreeVector cellPos2 = cPos.at(1);

  // Cell shapes, logical volumes, physical volumes

  auto solidShapeOuter2 =
      new G4Trd("CellTRD2", // its name
                shapeOuterdxa / 2, shapeOuterdxb / 2, shapeOuterdya / 2,
                shapeOuterdyb / 2, shapeOuterdz / 2); // its size

  auto solidShapeInner2 =
      new G4Trd("InnerTRD2", // its name
                shapeInnerdxa / 2, shapeInnerdxb / 2, shapeInnerdya / 2,
                shapeInnerdyb / 2, shapeInnerdz / 2); // its size

  auto logicCellOuter2 = new G4LogicalVolume(solidShapeOuter2, // its solid
                                             cellMat,          // its material
                                             "CellTRD2");      // its namespace

  auto logicCellInner2 =
      new G4LogicalVolume(solidShapeInner2, cellMatInside, "InnerTRD2");

  // cell visualas

  logicCellInner2->SetVisAttributes(visAttributesInner);

  logicCellOuter2->SetVisAttributes(visAttributesOuter);

  // PhysicalVolume Cell

  new G4PVPlacement(nullptr,         // no rotation
                    cellPos2,        // at position
                    logicCellOuter2, // its logical volume
                    "CellTRD2",      // its name
                    logicWorld,      // its mother  volume
                    false,           // no boolean operation
                    0,               // copy number
                    checkOverlaps);  // overlaps checking
                                     //

  new G4PVPlacement(nullptr,                                //
                    G4ThreeVector(0, 0, baseThickness / 2), //
                    logicCellInner2,                        //
                    "InnerTRD2",                            //
                    logicCellOuter2,                        //
                    false,                                  //
                    0,                                      //
                    checkOverlaps);                         //
                                                            //
  ////
  // Cell 3
  //
  G4ThreeVector cellPos3 = cPos.at(2);

  // Cell shapes, logical volumes, physical volumes

  auto solidShapeOuter3 =
      new G4Trd("CellTRD3", // its name
                shapeOuterdxa / 2, shapeOuterdxb / 2, shapeOuterdya / 2,
                shapeOuterdyb / 2, shapeOuterdz / 2); // its size

  auto solidShapeInner3 =
      new G4Trd("InnerTRD3", // its name
                shapeInnerdxa / 2, shapeInnerdxb / 2, shapeInnerdya / 2,
                shapeInnerdyb / 2, shapeInnerdz / 2); // its size

  auto logicCellOuter3 = new G4LogicalVolume(solidShapeOuter3, // its solid
                                             cellMat,          // its material
                                             "CellTRD3");      // its namespace

  auto logicCellInner3 =
      new G4LogicalVolume(solidShapeInner3, cellMatInside, "InnerTRD3");

  // cell visualas

  logicCellInner3->SetVisAttributes(visAttributesInner);

  logicCellOuter3->SetVisAttributes(visAttributesOuter);

  // PhysicalVolume Cell

  new G4PVPlacement(nullptr,         // no rotation
                    cellPos3,        // at position
                    logicCellOuter3, // its logical volume
                    "CellTRD3",      // its name
                    logicWorld,      // its mother  volume
                    false,           // no boolean operation
                    0,               // copy number
                    checkOverlaps);  // overlaps checking
                                     //

  new G4PVPlacement(nullptr,                                //
                    G4ThreeVector(0, 0, baseThickness / 2), //
                    logicCellInner3,                        //
                    "InnerTRD3",                            //
                    logicCellOuter3,                        //
                    false,                                  //
                    0,                                      //
                    checkOverlaps);                         //
                                                            //
                                                            //
  // Cell 4
  //
  G4ThreeVector cellPos4 = cPos.at(3);

  // Cell shapes, logical volumes, physical volumes

  auto solidShapeOuter4 =
      new G4Trd("CellTRD4", // its name
                shapeOuterdxa / 2, shapeOuterdxb / 2, shapeOuterdya / 2,
                shapeOuterdyb / 2, shapeOuterdz / 2); // its size

  auto solidShapeInner4 =
      new G4Trd("InnerTRD4", // its name
                shapeInnerdxa / 2, shapeInnerdxb / 2, shapeInnerdya / 2,
                shapeInnerdyb / 2, shapeInnerdz / 2); // its size

  auto logicCellOuter4 = new G4LogicalVolume(solidShapeOuter4, // its solid
                                             cellMat,          // its material
                                             "CellTRD4");      // its namespace

  auto logicCellInner4 =
      new G4LogicalVolume(solidShapeInner4, cellMatInside, "InnerTRD4");

  // cell visualas

  logicCellInner4->SetVisAttributes(visAttributesInner);

  logicCellOuter4->SetVisAttributes(visAttributesOuter);

  // PhysicalVolume Cell

  new G4PVPlacement(nullptr,         // no rotation
                    cellPos4,        // at position
                    logicCellOuter4, // its logical volume
                    "CellTRD4",      // its name
                    logicWorld,      // its mother  volume
                    false,           // no boolean operation
                    0,               // copy number
                    checkOverlaps);  // overlaps checking
                                     //

  new G4PVPlacement(nullptr,                                //
                    G4ThreeVector(0, 0, baseThickness / 2), //
                    logicCellInner4,                        //
                    "InnerTRD4",                            //
                    logicCellOuter4,                        //
                    false,                                  //
                    0,                                      //
                    checkOverlaps);                         //
                                                            //
                                                            //
  //
  // Foundation pad
  //
  // properities of pad
  G4ThreeVector padDimentions{8 * cm, 8 * cm, 2 * cm};
  G4ThreeVector padPos{.0 / 2 * mm, .0 / 2 * mm,
                       -(padDimentions.z() / 2. + shapeOuterdz / 2) * mm};
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

  fScoringVolume = logicDaphnia1;

  return physWorld;
}
