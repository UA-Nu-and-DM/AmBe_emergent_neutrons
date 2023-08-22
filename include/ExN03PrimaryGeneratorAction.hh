#ifndef ExN03PrimaryGeneratorAction_h
#define ExN03PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class ExN03PrimaryGeneratorMessenger;
class ExN03DetectorConstruction;

class ExN03PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  ExN03PrimaryGeneratorAction(ExN03DetectorConstruction*);    
  virtual ~ExN03PrimaryGeneratorAction();

  void GeneratePrimaries(G4Event*); 
  void SetPosRndmFlag(G4String val) { posFlag = val;}
  void SetDirRndmFlag(G4String val) { dirFlag = val;}
  void SetBkgRndmFlag(G4String val) { bkgFlag = val;}
  

private:
  G4ParticleGun*                particleGun;	  //pointer a to G4  class
  ExN03DetectorConstruction*    ExN03Detector;    //pointer to the geometry
  ExN03PrimaryGeneratorMessenger* gunMessenger;   //messenger of this class
  G4String                      posFlag;	  
  G4String                      dirFlag;
  G4String                      bkgFlag;
};


#endif


