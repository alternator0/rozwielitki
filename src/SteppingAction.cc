// Zbieranie danych z pojedynczego korku

#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4LogicalVolume.hh>
#include <G4SystemOfUnits.hh>
#include <G4ThreeVector.hh>
#include <G4Types.hh>
#include <G4ios.hh>

SteppingAction::SteppingAction(EventAction *eventAction,
                               const std::vector<G4LogicalVolume*>& volumes)
    : fEventAction(eventAction), fScoringVolumes(volumes) {}

// jest wywolywana po kazdym kroku czastki
void SteppingAction::UserSteppingAction(const G4Step *step) {
  // sprawdzenie czy trafiony obiekt to rozwielitka (fScoringVolume
  // zdefiniowane w constructorze DetectorConstruction)
  for (auto volume : this->fScoringVolumes) {
    // DEBUG
    // G4cout << "Comparing: " << step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume() << " and " << volume << "\n";
    if (step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume() ==
        volume) {
      if (step->GetTrack()->GetDefinition()->GetParticleName() == "gamma" ||
          step->GetTrack()->GetDefinition()->GetParticleName() == "e-") {
        G4double totalEnergyDeposit = step->GetTotalEnergyDeposit();

        if (totalEnergyDeposit > 0) {

          //  step->GetPostStepPoint()->GetPhysicalVolume();

          G4double kineticEnergy = step->GetTrack()->GetKineticEnergy();

          //  G4ThreeVector totalMomentum = step->GetTrack()->GetMomentum();

          //  G4ThreeVector position = step->GetTrack()->GetPosition();

          // DEBUG
          G4cout << G4endl << "Detector got hit\n";

          // wpisanie danych do pliku
          auto man = G4AnalysisManager::Instance();
          man->FillNtupleDColumn(0, step->GetTrack()->GetKineticEnergy() / MeV);
          man->FillNtupleDColumn(1, totalEnergyDeposit / MeV);
          //  man->FillNtupleDColumn(2, totalMomentum);
          // man->FillNtupleDColumn(3, position);
          man->AddNtupleRow();
        }
      }
    }
  }
}
