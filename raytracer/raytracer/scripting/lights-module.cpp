#include "scripting/lights-module.h"
#include "lights/lights.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;
using namespace imaging;


namespace
{
    struct LightLibrary
    {
        LightSource omnidirectional(const Point3D& position, const color& c) const
        {
            return lights::omnidirectional(position, c);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_lights_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    auto lights_library = std::make_shared<LightLibrary>();
    module->add_global_const(chaiscript::const_var(lights_library), "Lights");

#define LIGHT(NAME) module->add(fun(&LightLibrary::NAME), #NAME)
    LIGHT(omnidirectional);
#undef LIGHT

    return module;
}