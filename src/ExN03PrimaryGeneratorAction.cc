#include "ExN03PrimaryGeneratorAction.hh"
#include "ExN03PrimaryGeneratorMessenger.hh"
#include "ExN03DetectorConstruction.hh"
#include <math.h>
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "globals.hh"
#include "G4Tubs.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4HEPEvtInterface.hh"
#include "G4UnitsTable.hh"



G4VPrimaryGenerator* HEPEvt;



ExN03PrimaryGeneratorAction::ExN03PrimaryGeneratorAction(ExN03DetectorConstruction* ExN03DC):ExN03Detector(ExN03DC)
{
    HEPEvt = new G4HEPEvtInterface("generator.data");
    G4cout << "Opened generator data file " << G4endl;
}

ExN03PrimaryGeneratorAction::~ExN03PrimaryGeneratorAction()
{
    delete HEPEvt;
}

void ExN03PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

   float unit=1*CLHEP::mm;
   static const G4double inch = 2.54*CLHEP::cm;

   float ssShieldTopVoidHeight = 0.89*unit;

   float ssShieldBottomVoidHeight = 0.25267*unit; // ssShieldInnerDia/2*tg(22.5deg) if the bore was made with 135deg point angle drill bit
   float ssShieldCentralVoidHeight = 5.11*unit-ssShieldBottomVoidHeight;
   float ssShieldHeight = 6.50*unit;






   float wShieldHeight = 4.19*unit;
   float wShieldBoreHeight = 4*unit;


   float wWireHeight = 1.8*unit;
   float wWireTop = 0.3*unit;



   float srcCoreHeight = wShieldBoreHeight-(wWireHeight-wWireTop);
   float srcCoreOffset = 0.5*wShieldHeight - (wWireHeight-wWireTop)-0.5*srcCoreHeight;


   float wCapsCapHeight = 21*unit;

   float wCapsBaseOuterDia = 18*unit;
   float wCapsBaseHeight = 16*unit;
   float wCapsBaseBottomHeight = 9*unit;
   float wCapsBaseBoreHeight = 7.62*unit;
   float wCapsBaseBoreOffset = wCapsBaseOuterDia/2 - 5*unit;


   float fEndCapLength = 159.0*CLHEP::mm;
   float fHeadLength = (81.5-13.0)*CLHEP::mm; ; 
   float fDetectorEnclosureLength = fEndCapLength + fHeadLength;
   float fNeckOffset = 30.0*CLHEP::mm; // distance from neck center to "back" of head
   float fNeckLocation = 8.125*inch; //distance from inner cavity center to neck center.

   double endCapFace = fDetectorEnclosureLength - fNeckOffset - fNeckLocation;

   auto srcGenOffsetZ = wCapsBaseHeight-0.5*wCapsBaseBottomHeight-wCapsBaseBoreHeight+0.5*ssShieldHeight+0.5*ssShieldHeight-ssShieldTopVoidHeight-0.5*ssShieldCentralVoidHeight+srcCoreOffset;


   auto srcGenOffsetY = wCapsBaseBoreOffset;//when source is in the outer W capsule
   

   auto theta = 270.*CLHEP::degree;//angle of the outer W capsule rotation wrt the outer W capsule z axis. Set to 0 if no outer capsule



   auto sourcePV  = ExN03Detector->GetSrcCorePV();
   auto sourceLV = sourcePV->GetLogicalVolume();
   auto sourceS = sourceLV->GetSolid();

   auto srcCtrInCvtyCord =  G4ThreeVector(endCapFace+0.5*wCapsBaseOuterDia,0*CLHEP::mm,-0.5*wCapsCapHeight);;
   

    auto source = (G4Tubs*)sourceS;
    auto rSource = source->GetOuterRadius();
    auto hSource=source->GetZHalfLength();
    auto rSourceRnd = rSource*G4UniformRand();
    auto alpha = CLHEP::twopi*G4UniformRand();   
   
    auto xRnd = rSourceRnd*std::cos(alpha)+srcGenOffsetY*std::sin(theta);
    auto yRnd = rSourceRnd*std::sin(alpha)+srcGenOffsetY*std::cos(theta);
    auto zRnd = hSource*(2*G4UniformRand()-1)+srcGenOffsetZ;



    G4ThreeVector position(srcCtrInCvtyCord.getX()+xRnd, srcCtrInCvtyCord.getY()+yRnd, srcCtrInCvtyCord.getZ()+zRnd);






    HEPEvt->SetParticlePosition(position);
    HEPEvt->GeneratePrimaryVertex(anEvent);
}
