#include "ExN03EventAction.hh"

#include "ExN03RunAction.hh"

#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VTrajectory.hh"
#include "G4VVisManager.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

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



ExN03EventAction::ExN03EventAction(ExN03RunAction* run)
{

}


ExN03EventAction::~ExN03EventAction()
{
}


void ExN03EventAction::BeginOfEventAction(const G4Event* evt)
{
 G4int evtn = evt->GetEventID();
 
 if(!(evtn%10000)) G4cout<<"EventID: "<<evtn<<G4endl;
 
 ncapsuleprimary=0;
 nemission=0;
 Eemission.clear();
 idpdgemission.clear();
 costhemission.clear();
 E0capsule.clear();
 E0capsule.clear();
 x0capsule.clear();
 y0capsule.clear();
 z0capsule.clear();

}

void ExN03EventAction::EndOfEventAction(const G4Event* evt)
{
 G4int evtn = evt->GetEventID();
  tcapsule->Fill();
  if (ncapsuleprimary != 1){
 G4cout << "Event : " << evtn << " Number of primary particles: " << ncapsuleprimary << G4endl;
}
}

