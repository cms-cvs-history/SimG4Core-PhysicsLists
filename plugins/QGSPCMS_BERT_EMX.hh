#ifndef SimG4Core_PhysicsLists_QGSPCMS_BERT_EMX_H
#define SimG4Core_PhysicsLists_QGSPCMS_BERT_EMX_H
 
#include "SimG4Core/Physics/interface/PhysicsList.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "G4EmConfigurator.hh"
 
class QGSPCMS_BERT_EMX: public PhysicsList {

public:
  QGSPCMS_BERT_EMX(G4LogicalVolumeToDDLogicalPartMap& map, 
		   const edm::ParameterSet & p);
  virtual void SetCuts();

private:
  edm::ParameterSet    m_pPhysics;
  G4EmConfigurator     conf;
};

#endif

