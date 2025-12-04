// definicja generatora

#include "PrimaryGeneratorAction.hh"

#include "CLHEP/Random/RandGauss.h"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include <CLHEP/Units/SystemOfUnits.h>
#include <Randomize.hh>

// definicja czastek ktore generujemy
PrimaryGeneratorAction::PrimaryGeneratorAction() {
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition *particle =
      particleTable->FindParticle(particleName = "gamma");
  fParticleGun->SetParticleDefinition(particle);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() { delete fParticleGun; }

// jest wywolywana na poczatku kazdej generacji czastki
void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event) {

  G4double meanEnergy = 1500.0 * keV;
  // energia jest losowana zgodnie z rozkladem gausa
  G4double energy = CLHEP::RandGauss::shoot(meanEnergy, 1 * keV);

  fParticleGun->SetParticleEnergy(energy);

  // ustawinie pozycji generatora
  G4double xPos{(G4UniformRand() - 0.5) * 8};
  G4double yPos{(G4UniformRand() - 0.5) * 8};

  G4ThreeVector position = G4ThreeVector(xPos * cm, yPos * cm, 5.0 * cm);
  fParticleGun->SetParticlePosition(position);

  G4ThreeVector direction(0, 0, -1);

  fParticleGun->SetParticleMomentumDirection(direction);

  fParticleGun->GeneratePrimaryVertex(event);
}
