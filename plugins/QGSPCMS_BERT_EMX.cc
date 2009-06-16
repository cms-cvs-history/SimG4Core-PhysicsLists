#include "QGSPCMS_BERT_EMX.hh"
#include "SimG4Core/PhysicsLists/interface/CMSEmStandardPhysics71.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "G4Material.hh"
#include "G4MaterialTable.hh"

#include "G4DecayPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4QStoppingPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4NeutronTrackingCut.hh"

#include "G4DataQuestionaire.hh"
#include "HadronPhysicsQGSP_BERT.hh"

#include "G4EmProcessOptions.hh"
#include "G4UrbanMscModel2.hh"

QGSPCMS_BERT_EMX::QGSPCMS_BERT_EMX(G4LogicalVolumeToDDLogicalPartMap& map,
				   const edm::ParameterSet & p) : PhysicsList(map, p) {

  G4DataQuestionaire it(photon);
  
  int  ver     = p.getUntrackedParameter<int>("Verbosity",0);
  bool emPhys  = p.getUntrackedParameter<bool>("EMPhysics",true);
  bool hadPhys = p.getUntrackedParameter<bool>("HadPhysics",true);
  edm::LogInfo("PhysicsList") << "You are using the simulation engine: "
			      << "QGSP_BERT_EMX 3.3 with Flags for EM Physics "
			      << emPhys << " and for Hadronic Physics "
			      << hadPhys << "\n";

  if (emPhys) {
    // EM Physics
    RegisterPhysics( new CMSEmStandardPhysics71("standard EM v71",ver));

    // Synchroton Radiation & GN Physics
    RegisterPhysics( new G4EmExtraPhysics("extra EM"));
  }

  // Decays
  RegisterPhysics( new G4DecayPhysics("decay",ver) );

  if (hadPhys) {
    // Hadron Elastic scattering
    RegisterPhysics( new G4HadronElasticPhysics("elastic",ver,false));

    // Hadron Physics
    G4bool quasiElastic=true;
    RegisterPhysics( new HadronPhysicsQGSP_BERT("hadron",quasiElastic));
  
    // Stopping Physics
    RegisterPhysics( new G4QStoppingPhysics("stopping"));

    // Ion Physics
    RegisterPhysics( new G4IonPhysics("ion"));

    // Neutron tracking cut
    RegisterPhysics( new G4NeutronTrackingCut("Neutron tracking cut", ver));
  }

  if (emPhys) {
    G4EmProcessOptions opt;
    opt.SetApplyCuts(true);

    G4UrbanMscModel2* msc_el  = new G4UrbanMscModel2();
    G4UrbanMscModel2* msc_pos = new G4UrbanMscModel2();
    msc_el->SetRangeFactor(0.04);
    msc_pos->SetRangeFactor(0.04);
    conf.SetExtraEmModel("e-","msc",msc_el, "HCAL",0.,100.*MeV);
    conf.SetExtraEmModel("e+","msc",msc_pos,"HCAL",0.,100.*MeV);
  }
}

void QGSPCMS_BERT_EMX::SetCuts() { 
  
  PhysicsList::SetCuts();  

  conf.AddModels();
}