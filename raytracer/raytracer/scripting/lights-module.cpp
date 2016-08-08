#include "scripting/lights-module.h"
#include "scripting/scripting-util.h"
#include "lights/lights.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;
using namespace imaging;


namespace
{
    struct LightLibrary
    {
        LightSource omnidirectional(const Point3D& position, const Color& c) const
        {
            return lights::omnidirectional(position, c);
        }

        LightSource directional(const Vector3D& direction, const Color& c) const
        {
            return lights::directional(direction, c);
        }

        LightSource area(const math::Rectangle3D& rectangle, raytracer::Sampler sampler, const imaging::Color& color) const
        {
            return lights::area(rectangle, sampler, color);
        }

        LightSource spot_direction(const math::Point3D& position, const math::Vector3D& direction, math::Angle angle, const imaging::Color& color)
        {
            return lights::spot(position, direction, angle, color);
        }

        LightSource spot_point_at(const math::Point3D& position, const math::Point3D& point_at, math::Angle angle, const imaging::Color& color)
        {
            return lights::spot(position, point_at, angle, color);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_lights_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<LightSource>(*module, "LightSource");

    auto lights_library = std::make_shared<LightLibrary>();
    module->add_global_const(chaiscript::const_var(lights_library), "Lights");

#define LIGHT(NAME) module->add(fun(&LightLibrary::NAME), #NAME)
#define LIGHT_NAMED(INTERNAL, EXTERNAL) module->add(fun(&LightLibrary::INTERNAL), #EXTERNAL)
    LIGHT(omnidirectional);
    LIGHT(directional);
    LIGHT(area);
    LIGHT_NAMED(spot_direction, spot);
    LIGHT_NAMED(spot_point_at, spot);
#undef LIGHT_NAMED
#undef LIGHT

    return module;
}