#include <iostream>
#include <cmath>

#include "boost/lexical_cast.hpp"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "GeneratorInterface/Core/interface/RNDMEngineAccess.h"

#include "GeneratorInterface/YajemInterface/interface/YajemHadronizer.h"
#include "GeneratorInterface/YajemInterface/interface/YajemPythiaWrapper.h"
#include "GeneratorInterface/YajemInterface/interface/YajemWrapper.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"

#include "HepMC/IO_HEPEVT.h"
#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"
#include "HepMC/SimpleVector.h"
#include "CLHEP/Random/RandomEngine.h"

static const double pi = 3.14159265358979;

using namespace edm;
using namespace std;
using namespace gen;

HepMC::IO_HEPEVT hepevtio;

YajemHadronizer::YajemHadronizer(const ParameterSet &pset) :
    BaseHadronizer(pset),
    evt(0), 
    pset_(pset),
    bmax_(pset.getParameter<double>("bMax")),
    bmin_(pset.getParameter<double>("bMin")),
    efrm_(pset.getParameter<double>("comEnergy")),
    frame_(pset.getParameter<string>("frame")),
    proj_(pset.getParameter<string>("proj")),
    targ_(pset.getParameter<string>("targ")),
    iap_(pset.getParameter<int>("iap")),
    izp_(pset.getParameter<int>("izp")),
    iat_(pset.getParameter<int>("iat")),
    izt_(pset.getParameter<int>("izt")),
    phi0_(0.),
    sinphi0_(0.),
    cosphi0_(1.),
    rotate_(pset.getParameter<bool>("rotateEventPlane"))
{
  // Default constructor
  Service<RandomNumberGenerator> rng;
  hijRandomEngine = &(rng->getEngine());

}


//_____________________________________________________________________
YajemHadronizer::~YajemHadronizer()
{
  // destructor
}

//_____________________________________________________________________
void YajemHadronizer::add_heavy_ion_rec(HepMC::GenEvent *evt)
{
  // heavy ion record in the final CMSSW Event
  // Yen-Jie: set to 0 for the moment
  HepMC::HeavyIon* hi = new HepMC::HeavyIon(
    0,                               // Ncoll_hard/N of SubEvents
    0,                               // Npart_proj
    0,                               // Npart_targ
    0,                               // Ncoll
    0,                               // spectator_neutrons
    0,                               // spectator_protons
    0,                               // N_Nwounded_collisions
    0,                               // Nwounded_N_collisions
    0,                               // Nwounded_Nwounded_collisions
                                     //gsfs Changed from 19 to 18 (Fortran counts from 1 , not 0) 
    0,                               // impact_parameter in [fm]
    0,                               // event_plane_angle
    0,                               // eccentricity
                                     //gsfs Changed from 12 to 11 (Fortran counts from 1 , not 0) 
    0                                // sigma_inel_NN
  );
  evt->set_heavy_ion(*hi);
  delete hi;
}

bool YajemHadronizer::generatePartonsAndHadronize()
{
   // generate a Yajem event
   static int j=0;
   j++;
   GENEVENT(j);
   cout <<pydat1_.parj[84]<<endl;
   call_pyhepc(1);   
   cout <<pyjets_.k[1][2]<<endl;
   cout <<"I am alive"<<endl;
   HepMC::GenEvent* evt = hepevtio.read_next_event();

   evt->set_signal_process_id(pypars.msti[0]);	 // type of the process
   evt->set_event_scale(pypars.pari[16]);  	 // Q^2
   cout <<"Keeping up"<<endl;

   event().reset(evt);
   cout <<"Made it!"<<endl;   
   return true;
}

//_____________________________________________________________________  
bool YajemHadronizer::get_particles(HepMC::GenEvent *evt )
{      
   return 0;
}

//_____________________________________________________________________
bool YajemHadronizer::call_hijset(double efrm, std::string frame, std::string proj, std::string targ, int iap, int izp, int iat, int izt)
{
   INIT();
      
   return true;
}

//______________________________________________________________
bool YajemHadronizer::initializeForInternalPartons(){
   call_hijset(efrm_,frame_,proj_,targ_,iap_,izp_,iat_,izt_);
   return true;
}

bool YajemHadronizer::declareStableParticles( std::vector<int> pdg )
{
   return true;
}

//________________________________________________________________                                                                    
void YajemHadronizer::rotateEvtPlane(){

   phi0_ = 2.*pi*gen::hijran_(0) - pi;
   sinphi0_ = sin(phi0_);
   cosphi0_ = cos(phi0_);
}

//________________________________________________________________ 
bool YajemHadronizer::hadronize()
{
   return false;
}

bool YajemHadronizer::decay()
{
   return true;
}
   
bool YajemHadronizer::residualDecay()
{  
   return true;
}

void YajemHadronizer::finalizeEvent(){
    return;
}

void YajemHadronizer::statistics(){
    return;
}

const char* YajemHadronizer::classname() const
{  
   return "gen::YajemHadronizer";
}

