#ifndef EXCLUDE_SCRIPTING

#include "scripting/patterns-module.h"
#include "scripting/scripting-util.h"
#include "math/functions/patterns/patterns.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;


namespace
{
    struct PatternLibrary
    {
        math::functions::Pattern2D lines(double thickness, double separation, math::Angle angle) const
        {
            return math::functions::patterns::lines(thickness, separation, angle);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_pattern_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<math::functions::Pattern2D>(*module, "Pattern2D");
    util::register_type<math::functions::Pattern3D>(*module, "Pattern3D");

    auto lights_library = std::make_shared<PatternLibrary>();
    module->add_global_const(chaiscript::const_var(lights_library), "Patterns");

#   define BIND(NAME)                      BIND_AS(NAME, NAME)
#   define BIND_AS(INTERNAL, EXTERNAL)     module->add(fun(&PatternLibrary::INTERNAL), #EXTERNAL)
    BIND(lines);
#   undef BIND_AS
#   undef BIND

    return module;
}

#endif
