#include "ExN03RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

#include <vector>


#include <TFile.h>
#include <TTree.h>
#include <TString.h>

TFile *outcapsule; 
TTree *tcapsule;
G4int nemission;
std::vector<double> Eemission;
std::vector<int> idpdgemission;
std::vector<double> costhemission;
G4int ncapsuleprimary;
std::vector<double> E0capsule;
std::vector<double> x0capsule;
std::vector<double> y0capsule;
std::vector<double> z0capsule;


ExN03RunAction::ExN03RunAction()
{
 outcapsule = new TFile("outcapsule.root","RECREATE");
 
 tcapsule = new TTree("tcapsule","tree");
 tcapsule->Branch("Eemission",&Eemission);
 tcapsule->Branch("nemission",&nemission,"nemission/I");
 tcapsule->Branch("idpdgemission",&idpdgemission);
 tcapsule->Branch("costhemission",&costhemission);
 tcapsule->Branch("E0capsule",&E0capsule);
 tcapsule->Branch("ncapsuleprimary",&ncapsuleprimary,"ncapsuleprimary/I");
 tcapsule->Branch("x0capsule",&x0capsule);
 tcapsule->Branch("y0capsule",&y0capsule);
 tcapsule->Branch("z0capsule",&z0capsule);

}

  

ExN03RunAction::~ExN03RunAction()
{
}



void ExN03RunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

}


void ExN03RunAction::EndOfRunAction(const G4Run* aRun)
{

 outcapsule->cd();
 tcapsule->Write();
 outcapsule->Close();
}
