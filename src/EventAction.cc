
#include "EventAction.hh"
#include "G4Event.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "RunAction.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction *runAction) : fRunAction(runAction) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event *event) {
  G4int eventID = event->GetEventID();

  // pobiera liczbę cząstek z RunManagera
  G4int totalEvents = G4RunManager::GetRunManager()
                          ->GetCurrentRun()
                          ->GetNumberOfEventToBeProcessed();

  G4int printModulo = totalEvents / 100;

  if (eventID % printModulo == 0) {
    G4double progress = (G4double)eventID / totalEvents * 100.0;
    std::cout << "[ POSTĘP SYMULACJI: " << std::fixed << std::setprecision(1)
              << progress << "% ]" << std::endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event *) {
  // accumulate statistics in run action
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
