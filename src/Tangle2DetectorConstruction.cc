// *******************************************************************
// * License and Disclaimer                                          *
// *                                                                 *
// * This software is copyright of Geant4 Associates International   *
// * Ltd (hereafter 'G4AI'). It is provided under the terms and      *
// * conditions described in the file 'LICENSE' included in the      *
// * software system.                                                *
// * Neither the authors of this software system nor G4AI make any   *
// * representation or warranty, express or implied, regarding this  *
// * software system or assume any liability for its use.            *
// * Please see the file 'LICENSE' for full disclaimer and the       *
// * limitation of liability.                                        *
// *******************************************************************

#include "Tangle2DetectorConstruction.hh"
#include "Tangle2Data.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"


Tangle2DetectorConstruction::Tangle2DetectorConstruction()
  : G4VUserDetectorConstruction(),
    fCheckOverlaps(true)
{
  DefineMaterials();
}

Tangle2DetectorConstruction::~Tangle2DetectorConstruction()
{ }

void Tangle2DetectorConstruction::DefineMaterials()
{

  G4double a; // mass of a mole
  G4double z; // mean number of protons
  G4String name, symbol;

  a=16.00*g/mole;
  G4Element*  elO = new G4Element(name="Oxygen",
				  symbol="O",
				  z=8., a);
  a=28.09*g/mole;
  G4Element*  elSi = new G4Element(name="Silicon",
				   symbol="Si",
				   z=14., a);
  a=174.97*g/mole;
  G4Element* elLu = new G4Element(name="Lutetium",
				  symbol="Lu",
				  z=71., a);
  a=207.2*g/mole;
  G4Element*  elPb = new G4Element(name="Lead",
				   symbol="Pb",
				   z=82., a);     

  G4Material* LSO;
  G4Material* lead;

  // Change to LYSO
  G4double density = 7.4*g/cm3;
  LSO = new G4Material("Lu2SiO5",   
                       density,    
                       3);
  //Add Element for Material "Lu2SiO5"
  LSO->AddElement(elSi, 1);
  LSO->AddElement(elLu, 2);
  LSO->AddElement(elO , 5);
    
  G4double density_lead = 11.3*g/cm3;
  lead = new G4Material("lead",
			density_lead,
			1);
  
  lead->AddElement(elPb, 1);
  
  // Dump the Table of registered materials 
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume* Tangle2DetectorConstruction::Construct()
{  
  G4NistManager* nist = G4NistManager::Instance();
  
  // Crystal Arrays
  G4double cryst_dX = 22*mm, cryst_dY = 4*mm, cryst_dZ = 4*mm;

  G4Material* cryst_mat   = nist->FindOrBuildMaterial("Lu2SiO5");
  
  G4bool checkOverlaps = true;
  
  // World
  G4double world_sizeX  = 108.5*mm; 
  G4double world_sizeYZ = 2*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",
	      0.5*world_sizeX,
	      0.5*world_sizeYZ,
	      0.5*world_sizeYZ);
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          
                        world_mat,          
                        "World");           
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     
                      G4ThreeVector(),       
                      logicWorld,            
                      "World",               
                      0,                     
                      false,                 
                      0,                     
                      checkOverlaps);        
  
  // Crystal
  G4double pos_dX = 0.5*(world_sizeX-cryst_dX);
  

  G4Box* solidCryst =    
    new G4Box("crystal",                    
	      0.5*cryst_dX, 0.5*cryst_dY, 0.5*cryst_dZ); 
G4LogicalVolume* logicCryst =                         
    new G4LogicalVolume(solidCryst,            
                        cryst_mat,
                        "CrystalLV");         

  //make your detector geometry choice here

 G4bool horseshoeCrystal = false;


 if (horseshoeCrystal) {
  
  G4double innerRad = cryst_dY;
  G4double outerRad = 2*cryst_dY;
  G4double height = cryst_dZ;
  G4double startAngle = 90.*deg;
  G4double endAngle = 180.*deg;

  G4Tubs* roundCryst = new G4Tubs("horseshoe",
				 innerRad,
				 outerRad,
				 height,
				 startAngle,
				 endAngle);
  G4LogicalVolume* logicScat = new G4LogicalVolume(roundCryst,
						   cryst_mat,
						   "RoundLV");
  G4RotationMatrix* rotm  = new G4RotationMatrix();                                                      
  rotm->rotateX(90*deg); 


 G4int nbPos = 2;
 G4ThreeVector positions[2] = {
   G4ThreeVector(pos_dX,0,0),
   G4ThreeVector(-pos_dX,0,0)};
 
   new G4PVPlacement(0,
		     positions[0],
		     logicCryst,	     
		     "crystal",
		     logicWorld,
		     false,
		     1,
		     checkOverlaps);
  new G4PVPlacement(rotm,
		    positions[1],
		    logicScat,
		    "scatterer",
		    logicWorld,
		    false,
		    1,
		    checkOverlaps);				 


  //Cuboid scatterer (collimator)

   G4ThreeVector pos1 = G4ThreeVector(-pos_dX*mm, 0.*mm, 0.*mm);

   G4Material* coll_mat   = nist->FindOrBuildMaterial("lead");



  G4Box* outer = new G4Box("Outer",
			    0.5*mm,
			    0.5*mm,
			    0.5*mm);


   G4LogicalVolume* logicColl = new G4LogicalVolume(outer,
						    coll_mat,
						    "Coll_LV");

   new G4PVPlacement(0,
		     pos1,
		     logicColl,
		     "Coll_right",
		     logicWorld,
		     false,
		     18,
		     checkOverlaps);


 }

  //array of positions for 18 crystals

 else {
  G4int nb_cryst = 18;
 
    G4ThreeVector positions[18] = {
    G4ThreeVector(pos_dX,-cryst_dY,cryst_dZ),
    G4ThreeVector(pos_dX,0,cryst_dZ),
    G4ThreeVector(pos_dX,cryst_dY,cryst_dZ),
    G4ThreeVector(pos_dX,-cryst_dY,0),
    G4ThreeVector(pos_dX,0,0),
    G4ThreeVector(pos_dX,cryst_dY,0),
    G4ThreeVector(pos_dX,-cryst_dY,-cryst_dZ),
    G4ThreeVector(pos_dX,0,-cryst_dZ),
    G4ThreeVector(pos_dX,cryst_dY,-cryst_dZ),
    G4ThreeVector(-pos_dX,-cryst_dY,cryst_dZ),
    G4ThreeVector(-pos_dX,0,cryst_dZ),
    G4ThreeVector(-pos_dX,cryst_dY,cryst_dZ),
    G4ThreeVector(-pos_dX,-cryst_dY,0),
    G4ThreeVector(-pos_dX,0,0),
    G4ThreeVector(-pos_dX,cryst_dY,0),
    G4ThreeVector(-pos_dX,-cryst_dY,-cryst_dZ),
    G4ThreeVector(-pos_dX,0,-cryst_dZ),
    G4ThreeVector(-pos_dX,cryst_dY,-cryst_dZ)};
  

  for (G4int icrys = 0; icrys < nb_cryst; icrys++) {
    new G4PVPlacement(0,                      
		      positions[icrys],       
		      logicCryst,             
		      "crystal",              
		      logicWorld,             
		      false,                  
		      icrys,
		      checkOverlaps);          
  }
 }

  

  //scattering disc
  

   /*    G4Material* disc_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");


  /*  G4Material* disc_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

  G4double disc_Rmax = 4*mm;
  G4double disc_Rmin = 0*mm;
  G4double disc_dX = 2*mm;
  G4Tubs* solidDisc =
    new G4Tubs("disc",
           disc_Rmin, disc_Rmax, 0.5*disc_dX, 0*deg, 360*deg);
  G4LogicalVolume* logicDisc = new G4LogicalVolume(solidDisc,
     disc_mat,
        "DiscLV");
  
  G4RotationMatrix* rot  = new G4RotationMatrix();
  rotm->rotateY(90*deg);


  new G4PVPlacement(rot,
		    G4ThreeVector(),
		    logicDisc,
		    "disc",
		    logicWorld,
		    false,
		    20,
		    checkOverlaps);
   */
  		    
   //Collimator
  // G4RotationMatrix* rotm  = new G4RotationMatrix();
  //rotm->rotateY(90*deg);

  // G4double coll_dZ = 25.25*mm;
 //G4double coll_dY = 25.25*mm;
 // G4double coll_dX = 10.*mm;

   //G4double inner_Rmax = 2.*mm;                                                                         
   //G4double inner_Rmin = 0.*mm;                                                                         



   /*
   new G4PVPlacement(0,
		     pos2,
		     logicColl,
		     "Coll_left",
		     logicWorld,
		     false,
		     19,
		     checkOverlaps);
   */

     /*  new G4PVPlacement(rotm,
      G4ThreeVector(),
          logicDisc,
	      "disc",
	          logicWorld,
		      false,
		          20,
			      checkOverlaps);
     */
			          
   //Collimator
   /*
  // G4RotationMatrix* rotm  = new G4RotationMatrix();
  //rotm->rotateY(90*deg);
   
  G4double coll_dZ = 25.25*mm;
  G4double coll_dY = 46.*mm;
  G4double coll_dX = 42.*mm;
  G4double inner_Rmax = 2.*mm;
  G4double inner_Rmin = 0.*mm;
  G4ThreeVector pos1 = G4ThreeVector(17.625*mm, 0.*mm, 0.*mm);
  G4ThreeVector pos2 = G4ThreeVector(-17.625*mm, 0.*mm, 0.*mm);
  G4Material* coll_mat   = nist->FindOrBuildMaterial("lead");
 
  G4Box* outerBox = new G4Box("Outer Box",
        0.5*coll_dX,
	      0.5*coll_dY,
	            0.5*coll_dZ);
  G4Tubs* innerCyl = new G4Tubs("inner Cyl",
  inner_Rmin,
  inner_Rmax,
  0.5*coll_dX,
  0*deg,
  360*deg);
 
  
  G4SubtractionSolid* Collimator = new G4SubtractionSolid("Collimator",
    outerBox,
      innerCyl);
  G4LogicalVolume* logicColl = new G4LogicalVolume(Collimator,
     //innerCyl,
        coll_mat,
	   "Coll_LV");
  
     new G4PVPlacement(rotm,                      
            pos1,       
	           logicColl,             
		          "Coll_right",              
			         logicWorld,             
				        false,                  
					       18,
					              checkOverlaps);
     
     new G4PVPlacement(rotm,                      
            pos2,       
	           logicColl,             
		          "Coll_left",              
			         logicWorld,             
				        false,                  
					       19,
					              checkOverlaps); 
  */  
  

  return physWorld; 
}
