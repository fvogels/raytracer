#include "scripting/samplers-module.h"
#include "sampling/samplers.h"
#include "scripting/scripting-util.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;


namespace
{
    struct SamplerLibrary
    {
        Sampler single() const
        {
            return samplers::single();
        }

        Sampler random(unsigned sample_count) const
        {
            return samplers::random(sample_count);
        }

        Sampler stratified(unsigned horizontal, unsigned vertical) const
        {
            return samplers::stratified_fixed(horizontal, vertical);
        }

        Sampler jittered(unsigned horizontal, unsigned vertical) const
        {
            return samplers::stratified_jittered(horizontal, vertical);
        }

        Sampler halfjittered(unsigned horizontal, unsigned vertical) const
        {
            return samplers::stratified_half_jittered(horizontal, vertical);
        }

        Sampler nrooks(unsigned sample_count) const
        {
            return samplers::nrooks(sample_count);
        }

        Sampler multijittered(unsigned sqrt_sample_count) const
        {
            return samplers::multi_jittered(sqrt_sample_count);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_samplers_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<Sampler>(*module, "Sampler");

    auto sampler_library = std::make_shared<SamplerLibrary>();
    module->add_global_const(chaiscript::const_var(sampler_library), "Samplers");

#define SAMPLER(NAME) module->add(fun(&SamplerLibrary::NAME), #NAME)
    SAMPLER(single);
    SAMPLER(random);
    SAMPLER(stratified);
    SAMPLER(jittered);
    SAMPLER(halfjittered);
    SAMPLER(nrooks);
    SAMPLER(multijittered);
#undef SAMPLER

    return module;
}