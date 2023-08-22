#include "ExN03PrimaryGeneratorMessenger.hh"

#include "ExN03PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

ExN03PrimaryGeneratorMessenger::ExN03PrimaryGeneratorMessenger(ExN03PrimaryGeneratorAction* ExN03Gun)
:ExN03Action(ExN03Gun)
{
  gunDir = new G4UIdirectory("/N03/gun/");
  gunDir->SetGuidance("PrimaryGenerator control");
   
  posCmd = new G4UIcmdWithAString("/N03/gun/rndm_pos",this);
  posCmd->SetGuidance("generate random injection positions.");
  posCmd->SetGuidance("  Choice : on, off(default)");
  posCmd->SetParameterName("choice",true);
  posCmd->SetDefaultValue("off");
  posCmd->SetCandidates("on off");
  posCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  dirCmd = new G4UIcmdWithAString("/N03/gun/rndm_dir",this);
  dirCmd->SetGuidance("generate random injection directions.");
  dirCmd->SetGuidance("  Choice : on, off(default)");
  dirCmd->SetParameterName("choice",true);
  dirCmd->SetDefaultValue("off");
  dirCmd->SetCandidates("on off");
  dirCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  bkgCmd = new G4UIcmdWithAString("/N03/gun/rndm_bkg",this);
  bkgCmd->SetGuidance("sets gun to act as background by firing at specified pt from the world's edge.");
  bkgCmd->SetGuidance(  "set with x y z, type 'off' to turn off.");
  bkgCmd->SetParameterName("choice",true);
  bkgCmd->SetDefaultValue("off");
  bkgCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}



ExN03PrimaryGeneratorMessenger::~ExN03PrimaryGeneratorMessenger()
{
  delete posCmd;
  delete dirCmd;
  delete gunDir;
  delete bkgCmd;
}


void ExN03PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if(command == posCmd) {
   ExN03Action->SetPosRndmFlag(newValue);}
  else if (command == dirCmd) {
   ExN03Action->SetDirRndmFlag(newValue);}
  else if (command == bkgCmd) {
   ExN03Action->SetBkgRndmFlag(newValue);} 
}



