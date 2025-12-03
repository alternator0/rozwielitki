// przygotowanie pod zebranie danych

#include "RunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"

namespace B1 {

// uruchamia sie na starcie programu
RunAction::RunAction() {
  // ustawienie pod multithreading, zeby na koncu laczylo dane z roznych watkow
  G4AnalysisManager::Instance()->SetNtupleMerging(true);
}

// wykonuje sie zawsze przed /run/beamOn
void RunAction::BeginOfRunAction(const G4Run *) {
  // pointer do automatycznie tworzonego w kazdym programie analysis managera
  auto analysisManager = G4AnalysisManager::Instance();
  // musi byc .root, bo csv rozdziela sie na kilka plikow dla kazdego watku
  // osobno
  analysisManager->OpenFile("WynikiSymulacji.root");

  // Tworzymy tabelę
  analysisManager->CreateNtuple("Dane", "Kroki czastek");
  analysisManager->CreateNtupleDColumn("Energia Kinetyczna");  // ID 0
  analysisManager->CreateNtupleDColumn("Energia Zdeponowana"); // ID 1

  analysisManager->FinishNtuple();
}

// uruchamia sie na koncu runa
void RunAction::EndOfRunAction(const G4Run *run) {

  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0)
    return;

  // Zapis i zamknięcie pliku z danymi
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

  /*
  //Debug
  if (isMaster) {
    G4cout << G4endl << "  " << run->GetNumberOfEvent()
           << "." << G4endl;
  }
  */
}

} // namespace B1
