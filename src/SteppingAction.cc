// Zbieranie danych z pojedynczego korku

#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4SystemOfUnits.hh>
#include <G4ThreeVector.hh>
#include <G4Types.hh>
#include <G4ios.hh>
namespace B1 {

SteppingAction::SteppingAction(EventAction *eventAction)
    : fEventAction(eventAction) {}

// jest wywolywana po kazdym kroku czastki
void SteppingAction::UserSteppingAction(const G4Step *step) {
  if (step->GetPreStepPoint()->GetPhysicalVolume()->GetName() !=
      "CellInnerTRD") {
    if (step->GetTrack()->GetDefinition()->GetParticleName() == "gamma" ||
        step->GetTrack()->GetDefinition()->GetParticleName() == "e-") {
      G4double totalEnergyDeposit = step->GetTotalEnergyDeposit();

      if (totalEnergyDeposit > 0) {

        //  step->GetPostStepPoint()->GetPhysicalVolume();

        G4double kineticEnergy = step->GetTrack()->GetKineticEnergy();

        //  G4ThreeVector totalMomentum = step->GetTrack()->GetMomentum();

        //  G4ThreeVector position = step->GetTrack()->GetPosition();

        // DEBUG
        //
        //
        G4cout << G4endl << " Detector got hit" << G4endl;
        //
        //
        //
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
} // namespace B1
