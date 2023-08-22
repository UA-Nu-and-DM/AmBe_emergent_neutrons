#ifndef ExN03RunAction_h
#define ExN03RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include <vector>
#include <TString.h>
#include <TTree.h>
#include <TFile.h>


class G4Run;
class TTree;
class TFile;

class ExN03RunAction : public G4UserRunAction
{
public:
  ExN03RunAction();
  virtual ~ExN03RunAction();

  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);
  void RecordParticle(G4int, G4double, G4double);




private:
  G4String particle_name;
  G4int particle_pdg_id;
  G4double particle_costheta,particle_ke;
  TTree *t;

  TFile *out;     

};


#endif

