#include "DummyPhysics.hh"
#include "SimG4Core/PhysicsLists/interface/DummyEMPhysics.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "G4DecayPhysics.hh"

DummyPhysics::DummyPhysics(G4LogicalVolumeToDDLogicalPartMap& map,
			   const edm::ParameterSet & p) : PhysicsList(map, p) {

  bool emPhys  = p.getUntrackedParameter<bool>("EMPhysics",true);
  RegisterPhysics(new G4DecayPhysics("decay"));
  if (emPhys) 
    RegisterPhysics(new DummyEMPhysics("dummyEM"));
  edm::LogInfo("PhysicsList") << "DummyPhysics constructed with EM Physics "
			      << emPhys << "\n";
}

DummyPhysics::~DummyPhysics() {}

