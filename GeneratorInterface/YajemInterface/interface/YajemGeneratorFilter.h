#ifndef gen_YajemGeneratorFilter_h
#define gen_YajemGeneratorFilter_h

#include "GeneratorInterface/YajemInterface/interface/YajemHadronizer.h"
#include "GeneratorInterface/Core/interface/GeneratorFilter.h"
#include "GeneratorInterface/ExternalDecays/interface/ExternalDecayDriver.h"

namespace gen
{
   typedef edm::GeneratorFilter<gen::YajemHadronizer, gen::ExternalDecayDriver> YajemGeneratorFilter;
}

#endif
