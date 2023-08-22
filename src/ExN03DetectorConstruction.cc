#include "ExN03DetectorConstruction.hh"
#include <fstream>
using namespace std;
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"

#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"

#include "G4Transform3D.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4NistManager.hh"
#include <vector>

ExN03DetectorConstruction::ExN03DetectorConstruction() 
{
 worldsize=.1*CLHEP::m;
   }

 
ExN03DetectorConstruction::~ExN03DetectorConstruction() {}



G4VPhysicalVolume* ExN03DetectorConstruction::Construct()
{
  return ConstructCounter();
}



G4VPhysicalVolume* ExN03DetectorConstruction::ConstructCounter()
{

  // Clean old geometry, if any
  //
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();


  //make materials
  ///////////////////////////////////////////////////////////
  G4int nelements;
  G4double density,a,z;
  G4String name,symbol;
 

  G4NistManager* man = G4NistManager::Instance();
  //Vacuum, taken to be air at galactic density and pressure
  G4Material* vacuum = man->FindOrBuildMaterial("G4_Galactic");

  //Air
  G4Material* air = man->FindOrBuildMaterial("G4_AIR");

  //Aluminum
  G4Material *aluminum = man->FindOrBuildMaterial("G4_Al");
 
  //SS
  G4Element* Fe = new G4Element(name="Iron",symbol="Fe",z=26,a=55.845*CLHEP::g/CLHEP::mole);
  G4Element* Ni = new G4Element(name="Nickel",symbol="Ni",28,58.693*CLHEP::g/CLHEP::mole);   
  G4Element* Cr = new G4Element(name="Chromium",symbol="Cr",24,51.996*CLHEP::g/CLHEP::mole);
  G4Material* SS = new G4Material(name="Stainless",density=7.87*CLHEP::g/CLHEP::cm3,nelements=3);
  SS->AddElement(Fe,71.*CLHEP::perCent);
  SS->AddElement(Cr,19.*CLHEP::perCent);
  SS->AddElement(Ni,10.*CLHEP::perCent);

  //Tungsten alloy
  G4Element* W = new G4Element(name="Tungsten",symbol="W",74,183.84*CLHEP::g/CLHEP::mole);
  G4Material* Walloy = new G4Material(name="TungstenAlloy",density=18.51*CLHEP::g/CLHEP::cm3,nelements=3);
  Walloy->AddElement(W,97.*CLHEP::perCent);
  Walloy->AddElement(Ni,2.1*CLHEP::perCent);
  Walloy->AddElement(Fe,0.9*CLHEP::perCent);



  //Polyethylene
  G4Material* pet = man->FindOrBuildMaterial("G4_POLYETHYLENE");


  auto Be = new G4Element("Beryllium","Be", 4., 9.1218*CLHEP::g/CLHEP::mole);
  auto Am241 = new G4Element("Americium","Am",95,241.057*CLHEP::g/CLHEP::mole);
  auto O = new G4Element("Oxygen","O",8,16.00*CLHEP::g/CLHEP::mole);
  //americum di-oxide with beryllium mixture (based om AmBe1 description in thesis of I. Ostrovsky)
  //density: 0.199 g/cm3: 0.127 mg mixture mass pressed into a cylindrical volume with d=0.57 mm and h=2.5 mm
  //atomic ratio rescaled from AmO2 for 140:10 Am to Be ratio in the micture
  auto AmO2_Be = new G4Material("Americium_Di-Oxide_Beryllium_mixture",0.199*CLHEP::g/CLHEP::cm3,3);
  AmO2_Be->AddElement(Am241,83.15*CLHEP::perCent);
  AmO2_Be->AddElement(O,10.91*CLHEP::perCent);
  AmO2_Be->AddElement(Be,5.94*CLHEP::perCent);

  
  /////////////////////////////////////////////////////////////


  //make objects
  //////////////////////////////////////////////////////////////

   float unit=1*CLHEP::mm;
   float ssShieldOuterDia = 2.01*unit;
   float ssShieldInnerDia = 1.22*unit;
   float ssShieldTopVoidHeight = 0.89*unit;
   float ssShieldTopVoidDia = 1.605*unit;
   float ssShieldBottomVoidHeight = 0.25267*unit; // ssShieldInnerDia/2*tg(22.5deg) if the bore was made with 135deg point angle drill bit
   float ssShieldCentralVoidHeight = 5.11*unit-ssShieldBottomVoidHeight;
   float ssShieldHeight = 6.50*unit;

   float ssShieldLidBottomDia = 1.6*unit;
   float ssShieldLidBottomHeight = 1.02*unit;
   float ssShieldLidTopHeight = 5*0.2*unit;
   float ssShieldLidTopDia = 1.4*unit;

   float wShieldOuterDia = 1.13*unit;
   float wShieldHeight = 4.19*unit;
   float wShieldBoreHeight = 4*unit;

   float wWireDia = 0.5*unit;
   float wWireHeight = 1.8*unit;
   float wWireTop = 0.3*unit;
   float wWireOffset = wShieldBoreHeight/2-wWireHeight/2+wWireTop;

   float srcCoreDia = 0.57*unit;
   float srcCoreHeight = wShieldBoreHeight-(wWireHeight-wWireTop);
   float srcCoreOffset = 0.5*wShieldHeight - (wWireHeight-wWireTop)-0.5*srcCoreHeight;




   float wCapsBaseOuterDia = 18*unit;
   float wCapsBaseInnerDia = 16*unit;//????????????
   float wCapsBaseHeight = 16*unit;
   float wCapsBaseBottomHeight = 9*unit;
   float wCapsBaseBoreHeight = 7.62*unit;
   float wCapsBaseBoreDia = 2.06*unit;
   float wCapsBaseBoreOffset = wCapsBaseOuterDia/2 - 5*unit;



   float wCapsCapOuterDia = 18*unit;
   float wCapsCapInnerDia = 16*unit;//????????????
   float wCapsCapHeight = 21*unit;
   float wCapsCapBottomVoidHeight = 7*unit;
   float wCapsCapBoreHeight = 10*unit;
   float wCapsCapBoreDia = 4*unit;
   float wCapsCapOffset = 0.5*wCapsBaseBottomHeight+0.5*wCapsCapHeight; //will be added/subtracted to the corresponding dimension depending on rotation




   auto rotationSS = new G4RotationMatrix();



   G4double theta = 270*CLHEP::degree;//angle of rotation along own z axis

   G4ThreeVector AxisOfRotation = G4ThreeVector(0,0,1).unit();
   G4RotationMatrix* rotationW  = new G4RotationMatrix();
   rotationW -> rotate(theta, AxisOfRotation);


    //world
 


    auto rotation = new G4RotationMatrix();
    rotation->rotateY(0.);

    auto positionSS = G4ThreeVector(0,0,-0.5*wCapsCapHeight);// this is to make the source at the center of the world volume

    G4Tubs* world_solid = new G4Tubs("world_solid",0.,0.5*worldsize,0.5*worldsize,0.,2.0*CLHEP::pi);
    G4LogicalVolume* world_log = new G4LogicalVolume(world_solid,vacuum,"world_log");
    world_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0),world_log,"world_phys",0,false,0);







   //outer W capsule base
   auto wCapsuleBaseBottom = new G4Tubs("wCapsuleBaseBottom",0.,0.5*wCapsBaseOuterDia,0.5*wCapsBaseBottomHeight,0.,2.0*CLHEP::pi);
   auto wCapsuleBaseTop = new G4Tubs("wCapsuleBaseTop",0.,0.5*wCapsBaseInnerDia,0.5*(wCapsBaseHeight-wCapsBaseBottomHeight),0.,2.0*CLHEP::pi);

   auto wCapsuleBaseBody =  new G4UnionSolid("wCapsuleBaseBody", wCapsuleBaseBottom, wCapsuleBaseTop,0,G4ThreeVector(0,0.,0.5*wCapsBaseBottomHeight+0.5*(wCapsBaseHeight-wCapsBaseBottomHeight))); 



   auto wCapsuleBaseVoid = new G4Tubs("wCapsuleBaseVoid",0.,0.5*wCapsBaseBoreDia,0.5*wCapsBaseBoreHeight,0.,2.0*CLHEP::pi);



   auto wCapsuleBaseS = new G4SubtractionSolid("wCapsuleBaseS", wCapsuleBaseBody, wCapsuleBaseVoid, 0, G4ThreeVector(0.,wCapsBaseBoreOffset,wCapsBaseHeight-0.5*wCapsBaseBottomHeight-0.5*wCapsBaseBoreHeight));


 

   auto wCapsuleBase_log = new G4LogicalVolume(wCapsuleBaseS, Walloy,"wCapsuleBaseLV");
   wCapsuleBase_phys = new G4PVPlacement(rotationW,positionSS,wCapsuleBase_log,"wCapsuleBasePV",world_log,false,0,true);

   auto visAttw = new G4VisAttributes(G4Colour(0.7,0.7,0.9,0.75));
   wCapsuleBase_log->SetVisAttributes(visAttw);


   //outer W capsule cap
   auto wCapsuleCapCylinder = new G4Tubs("wCapsuleCapCylinder",0.,0.5*wCapsCapOuterDia,0.5*wCapsCapHeight,0.,2.0*CLHEP::pi);
   auto wCapsuleCapBottomVoid = new G4Tubs("wCapsuleCapBottomVoid",0.,0.5*wCapsBaseInnerDia,0.5*wCapsCapBottomVoidHeight,0.,2.0*CLHEP::pi);
   auto wCapsuleCapBore = new G4Tubs("wCapsuleCapBore",0.,0.5*wCapsCapBoreDia,0.5*wCapsCapBoreHeight,0.,2.0*CLHEP::pi);

   auto SubtractwCapsuleCapBottomVoid = new G4SubtractionSolid("SubtractwCapsuleCapBottomVoid", wCapsuleCapCylinder, wCapsuleCapBottomVoid, 0, G4ThreeVector(0.,0.,-0.5*wCapsCapHeight+0.5*wCapsCapBottomVoidHeight));

   auto wCapsuleCapS = new G4SubtractionSolid("wCapsuleCapS", SubtractwCapsuleCapBottomVoid, wCapsuleCapBore, 0, G4ThreeVector(0.,0.,0.5*wCapsCapHeight-0.5*wCapsCapBoreHeight));

   auto wCapsuleCap_log = new G4LogicalVolume(wCapsuleCapS, Walloy,"wCapsuleCapLV");
   wCapsuleCap_phys = new G4PVPlacement(rotationSS,G4ThreeVector(positionSS.getX(), positionSS.getY(), positionSS.getZ()+ wCapsCapOffset),wCapsuleCap_log,"wCapsuleBasePV",world_log,false,0,true);


   wCapsuleCap_log->SetVisAttributes(visAttw);

   //outer SS capsule


   auto ssShieldCylinder = new G4Tubs("ssShieldCylinder",0.,0.5*ssShieldOuterDia,0.5*ssShieldHeight,0.,2.0*CLHEP::pi);

   auto ssShieldVoidTop = new G4Tubs("ssShieldVoidTop",0.,0.5*ssShieldTopVoidDia,0.5*ssShieldTopVoidHeight,0.,2.0*CLHEP::pi);
   auto ssShieldVoidCenter = new G4Tubs("ssShieldVoidCenter",0.,0.5*ssShieldInnerDia,0.5*(ssShieldCentralVoidHeight+0.002*unit),0.,2.0*CLHEP::pi);
   auto ssShieldVoidBottom = new G4Cons("ssShieldVoidBottom", 0., 0, 0, 0.5*ssShieldInnerDia, 0.5*ssShieldBottomVoidHeight,0.,2.0*CLHEP::pi);


   auto SubtractssShieldVoidTop = new G4SubtractionSolid("SubtractssShieldVoidTop", ssShieldCylinder, ssShieldVoidTop, 0, G4ThreeVector(0,0.,0.5*ssShieldHeight-0.5*ssShieldTopVoidHeight));
   auto SubtractssShieldVoidCenter = new G4SubtractionSolid("SubtractssShieldVoidCenter", SubtractssShieldVoidTop, ssShieldVoidCenter, 0, G4ThreeVector(0,0.,0.5*ssShieldHeight-ssShieldTopVoidHeight-0.5*ssShieldCentralVoidHeight));

   auto ssShieldS = new G4SubtractionSolid("ssShieldS", SubtractssShieldVoidCenter, ssShieldVoidBottom, 0, G4ThreeVector(0,0.,0.5*ssShieldHeight-ssShieldTopVoidHeight-ssShieldCentralVoidHeight-0.5*ssShieldBottomVoidHeight));

   auto ssShield_log = new G4LogicalVolume(ssShieldS, SS,"ssShieldLV");
   ssShield_phys = new G4PVPlacement(0,G4ThreeVector(0.,wCapsBaseBoreOffset,wCapsBaseHeight-0.5*wCapsBaseBottomHeight-wCapsBaseBoreHeight+0.5*ssShieldHeight),ssShield_log,"ssShieldPV",wCapsuleBase_log,false,0,true);

   auto visAttSS = new G4VisAttributes(G4Colour(0.8,0.8,0.7,0.5));
   ssShield_log->SetVisAttributes(visAttSS);


   //Lid of the outer SS capsule




   auto ssShieldLidSTop = new G4Tubs("ssShieldCylinder",0.,0.5*ssShieldLidTopDia,0.5*ssShieldLidTopHeight,0.,2.0*CLHEP::pi);
   auto ssShieldLidSBottom = new G4Tubs("ssShieldCylinder",0.,0.5*ssShieldLidBottomDia,0.5*ssShieldLidBottomHeight,0.,2.0*CLHEP::pi);
   auto ssShieldLidS =  new G4UnionSolid("ssShieldLidS", ssShieldLidSBottom, ssShieldLidSTop,0,G4ThreeVector(0,0.,0.5*ssShieldLidBottomHeight+0.5*ssShieldLidTopHeight)); 


   auto ssShieldLid_log = new G4LogicalVolume(ssShieldLidS, SS,"ssShieldLidLV");
   ssShieldLid_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0.5*ssShieldHeight-0.5*ssShieldTopVoidHeight),ssShieldLid_log,"ssShieldLidPV",ssShield_log,false,0,true);


   ssShieldLid_log->SetVisAttributes(visAttSS);

   //inner W capsule


   auto wShieldCylinder = new G4Tubs("wShieldCylinder",0.,0.5*wShieldOuterDia,0.5*wShieldHeight,0.,2.0*CLHEP::pi);

   auto wShieldVoid = new G4Tubs("wShieldVoid",0.,0.5*srcCoreDia,0.5*wShieldBoreHeight,0.,2.0*CLHEP::pi);


   auto wShieldS = new G4SubtractionSolid("wShieldS", wShieldCylinder, wShieldVoid, 0, G4ThreeVector(0,0.,0.5*wShieldHeight-0.5*wShieldBoreHeight));






   auto wShield_log = new G4LogicalVolume(wShieldS, Walloy,"wShieldLV");
   wShield_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0.5*ssShieldHeight-ssShieldTopVoidHeight-0.5*ssShieldCentralVoidHeight),wShield_log,"wShieldPV",ssShield_log,false,0,true);

   //auto visAttw = new G4VisAttributes(G4Colour(0.7,0.7,0.9,0.75));
   wShield_log->SetVisAttributes(visAttw);


   //SS lid of the inner W capsule


   auto wShieldLidS = new G4Tubs("wShieldS",0.,0.5*wWireDia,0.5*wWireHeight,0.,2.0*CLHEP::pi);
   auto wShieldLid_log = new G4LogicalVolume(wShieldLidS, SS,"wShieldLidLV");
   wShieldLid_phys = new G4PVPlacement(0,G4ThreeVector(0,0,wWireOffset),wShieldLid_log,"wShieldLidPV",ssShield_log,false,0,true);


   wShieldLid_log->SetVisAttributes(visAttw);


   //source core
   auto srcCoreS = new G4Tubs("srcCoreS",0.,0.5*srcCoreDia,0.5*srcCoreHeight,0.,2.0*CLHEP::pi);
   auto srcCore_log = new G4LogicalVolume(srcCoreS, AmO2_Be,"srcCoreLV");
   srcCore_phys = new G4PVPlacement(0,G4ThreeVector(0,0,srcCoreOffset),srcCore_log,"srcCorePV",wShield_log,false,0,true);

   auto visAttsrcCore = new G4VisAttributes( G4Colour(0.5,0.5,0.6,1.0) );
   srcCore_log->SetVisAttributes( visAttsrcCore);



   return world_phys;
}


