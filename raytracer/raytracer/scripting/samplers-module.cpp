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
        Sampler single()
        {
            return samplers::single();
        }

        Sampler grid(unsigned horizontal, unsigned vertical)
        {
            return samplers::grid(horizontal, vertical);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_samplers_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    auto camera_library = std::make_shared<SamplerLibrary>();
    module->add_global_const(chaiscript::const_var(camera_library), "Samplers");

#define SAMPLER(NAME) module->add(fun(&SamplerLibrary::NAME), #NAME)
    SAMPLER(single);
    SAMPLER(grid);
#undef COLOR

    return module;
}