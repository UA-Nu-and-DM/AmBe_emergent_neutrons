#include "ExN03SteppingAction.hh"

#include "ExN03DetectorConstruction.hh"
#include "ExN03EventAction.hh"
#include "ExN03RunAction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4TrackVector.hh"

//#include "ExN03.hh"

extern TFile *outcapsule; 
extern TTree *tcapsule;
extern G4int nemission;
extern std::vector<double> Eemission;
extern std::vector<int> idpdgemission;
extern std::vector<double> costhemission;
extern G4int ncapsuleprimary;
extern std::vector<double> E0capsule;
extern std::vector<double> x0capsule;
extern std::vector<double> y0capsule;
extern std::vector<double> z0capsule;


ExN03RunAction *info;

ExN03SteppingAction::ExN03SteppingAction(ExN03DetectorConstruction* det,
                                         ExN03EventAction* evt)
:detector(det), eventaction(evt)					 
{ }



ExN03SteppingAction::~ExN03SteppingAction()
{ }



void ExN03SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  G4VPhysicalVolume* volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  G4LogicalVolume *logicalvolume=volume->GetLogicalVolume();
  G4StepPoint *steppoint=aStep->GetPreStepPoint();
  G4Track* track = aStep->GetTrack();
  const G4VProcess* pr = track->GetCreatorProcess();  
  G4String prevol;
  prevol=logicalvolume->GetName();
  if(prevol == "world_log" && track->GetNextVolume() == 0){
    G4String pN = track->GetDefinition()->GetParticleName();
    G4int pdgid=track->GetDefinition()->GetPDGEncoding();
    G4double ke=track->GetKineticEnergy()/CLHEP::keV;
    G4double costh=track->GetMomentumDirection().z();
    nemission=nemission+1;
    Eemission.push_back(ke);
    idpdgemission.push_back(pdgid);
    costhemission.push_back(costh);
  };
    //register primary particles here
  if(track->GetParentID()==0) {//primary
    if(track->GetCurrentStepNumber() == 1){
    G4double nke= (track->GetVertexKineticEnergy())/CLHEP::keV;
    x0capsule.push_back(track->GetVertexPosition().x()/CLHEP::mm);
    y0capsule.push_back(track->GetVertexPosition().y()/CLHEP::mm);
    z0capsule.push_back(track->GetVertexPosition().z()/CLHEP::mm);
    ncapsuleprimary++;
    E0capsule.push_back(nke);
    //flag pathological cases here
    if(nke < 25.){
       G4int tempid=track->GetDefinition()->GetPDGEncoding();
       G4cout << "primary particle number, energy (keV), PDG ID: " << ncapsuleprimary << " " << nke << " " << tempid << G4endl;
    }
    //    G4cout << "primary particle number and energy is " << ncapsuleprimary << " " << nke << G4endl;
    }
  }

}


