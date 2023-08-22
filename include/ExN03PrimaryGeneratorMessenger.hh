#ifndef ExN03PrimaryGeneratorMessenger_h
#define ExN03PrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class ExN03PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWith3Vector;

class ExN03PrimaryGeneratorMessenger: public G4UImessenger
{
public:
  ExN03PrimaryGeneratorMessenger(ExN03PrimaryGeneratorAction*);
  virtual ~ExN03PrimaryGeneratorMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  ExN03PrimaryGeneratorAction* ExN03Action;
  G4UIdirectory*               gunDir; 
  G4UIcmdWithAString*          posCmd;
  G4UIcmdWithAString*          dirCmd;
  G4UIcmdWithAString*          bkgCmd;
};


#endif

