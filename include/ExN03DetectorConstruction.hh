
#ifndef ExN03DetectorConstruction_h
#define ExN03DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"


class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
/*
//keele
class G4Box;

*/

class ExN03DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    ExN03DetectorConstruction();
   ~ExN03DetectorConstruction();

  public:
     
  
     
     G4VPhysicalVolume* Construct();


         
     G4double GetWorldSize() {return worldsize;};
     G4VPhysicalVolume* GetSrcCorePV() const; //added for LZ AmBe source
    
      
  private:
  G4VPhysicalVolume *world_phys, *wCapsuleBase_phys, *wCapsuleCap_phys, *ssShield_phys, *ssShieldLid_phys, *wShield_phys, *wShieldLid_phys, *srcCore_phys; 
  //  G4VPhysicalVolume *holes_phys[4], *tubes_phys[4], *counters_phys[4], *cylinder_phys, *box_phys, *crete_phys1a, *crete_phys1b, *crete_phys2a, *crete_phys2b, *crete_phys3;
          G4double worldsize;

          G4VPhysicalVolume* ConstructCounter();  
/*
  public:      
	  G4VPhysicalVolume* GetSrcCorePV() {return srcCore_phys;};
*/
  
};

inline G4VPhysicalVolume* ExN03DetectorConstruction::GetSrcCorePV() const {
     return srcCore_phys;     //added for AmBe
}

#endif

