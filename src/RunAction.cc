#include "RunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"

// uruchamia sie na starcie programu
RunAction::RunAction() {
  // ustawienie pod multithreading, zeby na koncu laczylo dane z roznych watkow
  G4AnalysisManager::Instance()->SetNtupleMerging(true);
}

// wykonuje sie zawsze przed /run/beamOn
void RunAction::BeginOfRunAction(const G4Run *run) {
  // pointer do automatycznie tworzonego w kazdym programie analysis managera
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  // musi byc .root, bo csv rozdziela sie na kilka plikow dla kazdego watku
  // osobno
  const char *fileName = "WynikiSymulacji.root";

  bool status = analysisManager->OpenFile(fileName);
  if (!status)
    G4cout << "Failed to open file: " << fileName << "\n";

  G4cout << "Liczba generowanych zdarzeń: "
         << run->GetNumberOfEventToBeProcessed() << G4endl;

  // Tworzymy tabelę
  analysisManager->CreateNtuple("Dane", "Trafienia");
  analysisManager->CreateNtupleIColumn("DaphniaID");          // ID 0
  analysisManager->CreateNtupleDColumn("EnergiaKinetyczna");  // ID 1
  analysisManager->CreateNtupleDColumn("EnergiaZdeponowana"); // ID 2

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
