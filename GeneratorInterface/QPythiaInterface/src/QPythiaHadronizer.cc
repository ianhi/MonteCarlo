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
#include "GeneratorInterface/Pythia6Interface/interface/Pythia6Service.h"

#include "GeneratorInterface/QPythiaInterface/interface/QPythiaHadronizer.h"
#include "GeneratorInterface/QPythiaInterface/interface/QPythiaPythiaWrapper.h"
#include "GeneratorInterface/QPythiaInterface/interface/QPythiaWrapper.h"
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

QPythiaHadronizer::QPythiaHadronizer(const ParameterSet &pset) :
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
    rotate_(pset.getParameter<bool>("rotateEventPlane")),
    pythia6Service_(new Pythia6Service(pset))
{
  // Default constructor
  Service<RandomNumberGenerator> rng;
  hijRandomEngine = &(rng->getEngine());


}


//_____________________________________________________________________
QPythiaHadronizer::~QPythiaHadronizer()
{
  // destructor
  delete pythia6Service_;
}

//_____________________________________________________________________
void QPythiaHadronizer::add_heavy_ion_rec(HepMC::GenEvent *evt)
{
 // heavy ion record in the final CMSSW Event

 double centr= 0;
 HepMC::HeavyIon* hi = new HepMC::HeavyIon(
    1,                               // Ncoll_hard/N of SubEvents
    1,                               // Npart_proj
    1,                               // Npart_targ
    1,                               // Ncoll
    0,                               // spectator_neutrons
    1,                               // spectator_protons
    1,                               // N_Nwounded_collisions
    1,                               // Nwounded_N_collisions
    1,                               // Nwounded_Nwounded_collisions
                                     //gsfs Changed from 19 to 18 (Fortran counts from 1 , not 0) 
    centr,                               // impact_parameter in [fm]
    0,                               // event_plane_angle
    0,                               // eccentricity
                                     //gsfs Changed from 12 to 11 (Fortran counts from 1 , not 0) 
    0                                // sigma_inel_NN
  );
  
  evt->set_heavy_ion(*hi);
  delete hi;
}

bool QPythiaHadronizer::generatePartonsAndHadronize()
{
   Pythia6Service::InstanceWrapper guard(pythia6Service_);

   // generate a JEWEL event
   static int j=0;
   j++;
   GENEVENT(j);
   cout <<"CKIN[3]"<<pysubs_.ckin[2]<<endl;
   cout <<"CKIN[4]"<<pysubs_.ckin[3]<<endl;
   cout <<"CKIN[5]"<<pysubs_.ckin[4]<<endl;
   call_pyhepc(1);   
   HepMC::GenEvent* evt = hepevtio.read_next_event();
   add_heavy_ion_rec(evt);
   evt->set_signal_process_id(pypars.msti[0]);	 // type of the process
   evt->set_event_scale(pypars.pari[16]);  	 // Q^2

   event().reset(evt);
   return true;
}

//_____________________________________________________________________  
bool QPythiaHadronizer::get_particles(HepMC::GenEvent *evt )
{      
   return 0;
}

//_____________________________________________________________________
bool QPythiaHadronizer::call_hijset(double efrm, std::string frame, std::string proj, std::string targ, int iap, int izp, int iat, int izt)
{
 //  Pythia6Service::InstanceWrapper guard(pythia6Service_);
 //  pythia6Service_->setGeneralParams();
 //  pythia6Service_->setCSAParams();
   INIT();
   cout <<"initial CKIN[3]"<<pysubs_.ckin[2]<<endl;
   cout <<"initial CKIN[4]"<<pysubs_.ckin[3]<<endl;
   cout <<"initial CKIN[5]"<<pysubs_.ckin[4]<<endl;
      
   return true;
}

//______________________________________________________________
bool QPythiaHadronizer::initializeForInternalPartons(){
   call_hijset(efrm_,frame_,proj_,targ_,iap_,izp_,iat_,izt_);

   return true;
}

bool QPythiaHadronizer::declareStableParticles( std::vector<int> pdg )
{
   return true;
}

//________________________________________________________________                                                                    
void QPythiaHadronizer::rotateEvtPlane(){

   phi0_ = 2.*pi*gen::hijran_(0) - pi;
   sinphi0_ = sin(phi0_);
   cosphi0_ = cos(phi0_);
}

//________________________________________________________________ 
bool QPythiaHadronizer::hadronize()
{
   return false;
}

bool QPythiaHadronizer::decay()
{
   return true;
}
   
bool QPythiaHadronizer::residualDecay()
{  
   return true;
}

void QPythiaHadronizer::finalizeEvent(){
    return;
}

void QPythiaHadronizer::statistics(){
    return;
}

const char* QPythiaHadronizer::classname() const
{  
   return "gen::QPythiaHadronizer";
}

