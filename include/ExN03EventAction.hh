#ifndef ExN03EventAction_h
#define ExN03EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include <vector>
#include <TString.h>


class ExN03RunAction;


class ExN03EventAction : public G4UserEventAction
{
public:
  ExN03EventAction(ExN03RunAction*);
  virtual ~ExN03EventAction();

  void  BeginOfEventAction(const G4Event*);
  void  EndOfEventAction(const G4Event*);

  /*
  void  AddCyl(G4double edep)          {ECyl += edep;};
  void  AddVol(G4double edep, G4int n) {Evol.at(n) += edep;};
  void  AddProc(G4String proc)         {procArr.push_back(TString(proc.data()));};
  void  AddPname(G4String pn)          {pnameArr.push_back(TString(pn.data()));};
  void  AddEstep(G4double edep)        {EstepArr.push_back(edep);};
  void  SetX0(G4double x[3])           {x0[0]=x[0];x0[1]=x[1];x0[2]=x[2];};
  void  SetE0(G4double e0)             {E0=e0;}; 
 
  */      
private:
  /*
   ExN03RunAction*  runAct;
   
   G4double ECyl;
   std::vector<G4double> Evol;
   std::vector<TString> procArr;
   std::vector<TString> pnameArr;
   std::vector<G4double> EstepArr;
   G4int np;
   G4double x0[3];
   G4double E0;

  */                    
  
                             
};



#endif

    
