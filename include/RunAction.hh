#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"

class G4Run;

class RunAction : public G4UserRunAction {
public:
  RunAction();
  ~RunAction() override = default;

  void BeginOfRunAction(const G4Run *) override;
  void EndOfRunAction(const G4Run *) override;

private:
};

#endif
