#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "Randomize.hh"

#include "ExN03DetectorConstruction.hh"
//#include "ExN03PhysicsList.hh"
#include "ExN03PrimaryGeneratorAction.hh"
#include "ExN03RunAction.hh"
#include "ExN03EventAction.hh"
#include "ExN03SteppingAction.hh"
//#include "QGSP_BERT_HP.hh"
//#include "G4StepLimiterPhysics.hh"
//#include "G4StepLimiterBuilder.hh"
//#include "G4EmStandardPhysics.hh"
#include "PhysicsList.hh"
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#if defined(G4UI_USE_TCSH)
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#else
#include "G4UIterminal.hh"
#endif



int main(int argc,char** argv)
{
  // Choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  
     
  // Construct the default run manager
  G4RunManager * runManager = new G4RunManager;

  // Set mandatory initialization classes
  ExN03DetectorConstruction* detector = new ExN03DetectorConstruction;
  runManager->SetUserInitialization(detector);

//  G4VUserPhysicsList* physics = new ExN03PhysicsList;
//  runManager->SetUserInitialization(physics);
  //auto physicsList = new QGSP_BERT_HP;
  auto physicsList = new PhysicsList();
  //physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  //physicsList->RegisterPhysics(new G4StepLimiterBuilder());
  runManager->SetUserInitialization(physicsList);
    
  // Set user action classes
  G4VUserPrimaryGeneratorAction* gen_action = new ExN03PrimaryGeneratorAction(detector);
  runManager->SetUserAction(gen_action);
  

  ExN03RunAction* run_action = new ExN03RunAction;  
  runManager->SetUserAction(run_action);

  ExN03EventAction* event_action = new ExN03EventAction(run_action);
  runManager->SetUserAction(event_action);

  G4UserSteppingAction* stepping_action = new ExN03SteppingAction(detector, event_action);
  runManager->SetUserAction(stepping_action);
  

  // Initialize G4 kernel
  runManager->Initialize();
  
  
#ifdef G4VIS_USE
  // Initialize visualization
   G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif
  
  // Get the pointer to the User Interface manager
  G4UImanager* UI = G4UImanager::GetUIpointer();      
 
  if (argc!=1)   // batch mode
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI->ApplyCommand(command+fileName);    
    }
  else           // interactive mode : define visualization UI terminal
    {
      G4UIsession* session = 0;

#if defined(G4UI_USE_TCSH)
      session = new G4UIterminal(new G4UItcsh);      
#else
      session = new G4UIterminal();
#endif
#ifdef G4VIS_USE
      UI->ApplyCommand("/control/execute vis.mac");
#endif
      session->SessionStart();
      delete session;
    }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !
#ifdef G4VIS_USE
  delete visManager;
#endif                
  delete runManager;

  return 0;
}


