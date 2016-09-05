#ifndef EXCLUDE_SCRIPTING

#include "scripting/primitives-module.h"
#include "scripting/scripting-util.h"
#include "primitives/primitives.h"
#include "math/functions.h"
#include "animation/time-stamp.h"
#include "animation/redimensioner.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;


namespace
{
    Primitive make_union(const std::vector<chaiscript::Boxed_Value>& boxed_children)
    {
        std::vector<Primitive> children(boxed_children.size());

        std::transform(boxed_children.begin(), boxed_children.end(), children.begin(), [](chaiscript::Boxed_Value boxed) {
            return chaiscript::boxed_cast<Primitive>(boxed);
        });

        return primitives::make_union(children);
    }

    Primitive make_accelerated_union(const std::vector<chaiscript::Boxed_Value>& boxed_children)
    {
        std::vector<Primitive> children(boxed_children.size());

        std::transform(boxed_children.begin(), boxed_children.end(), children.begin(), [](chaiscript::Boxed_Value boxed) {
            return chaiscript::boxed_cast<Primitive>(boxed);
        });

        return primitives::accelerated_union(children);
    }

    Primitive mesh(const std::string& path)
    {
        return primitives::fast_mesh(path);
    }

    Primitive bumpify2d_timed(Function<Vector3D(const Point3D&)> noise, Primitive primitive, animation::TimeStamp now)
    {
        auto perlin = animation::xyz_to_xyt(noise);

        return primitives::bumpify(perlin(now), primitive);
    }    
}

ModulePtr raytracer::scripting::_private_::create_primitives_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<Primitive>(*module, "Primitive");

#define BIND_HELPER_FUNCTION(NAME)                  BIND_HELPER_FUNCTION_AS(NAME, NAME)
#define BIND_DIRECTLY(NAME)                         BIND_HELPER_FUNCTION_AS(raytracer::primitives::NAME, NAME)
#define BIND_HELPER_FUNCTION_AS(FACTORY, NAME)      module->add(fun(&FACTORY), #NAME)
    BIND_DIRECTLY(sphere);
    BIND_DIRECTLY(xy_plane);
    BIND_DIRECTLY(xz_plane);
    BIND_DIRECTLY(yz_plane);
    BIND_DIRECTLY(cylinder_along_x);
    BIND_DIRECTLY(cylinder_along_y);
    BIND_DIRECTLY(cylinder_along_z);
    BIND_DIRECTLY(cone_along_x);
    BIND_DIRECTLY(cone_along_y);
    BIND_DIRECTLY(cone_along_z);
    BIND_DIRECTLY(triangle);
    BIND_DIRECTLY(disk);
    BIND_DIRECTLY(square);
    BIND_DIRECTLY(cube);
    BIND_DIRECTLY(translate);
    BIND_DIRECTLY(rotate_around_x);
    BIND_DIRECTLY(rotate_around_y);
    BIND_DIRECTLY(rotate_around_z);
    BIND_DIRECTLY(align_y_to);
    BIND_DIRECTLY(scale);
    BIND_HELPER_FUNCTION_AS(make_union, union);
    BIND_HELPER_FUNCTION_AS(make_accelerated_union, bbunion);
    BIND_DIRECTLY(decorate);   
    BIND_HELPER_FUNCTION(mesh);
    BIND_DIRECTLY(center);
    BIND_DIRECTLY(group);
    BIND_DIRECTLY(intersection);
    BIND_DIRECTLY(difference);
    BIND_DIRECTLY(crop_along_x);
    BIND_DIRECTLY(crop_along_y);
    BIND_DIRECTLY(crop_along_z);
    BIND_DIRECTLY(crop_spherical);
    BIND_HELPER_FUNCTION_AS(bumpify2d_timed, bumpify);
#undef BIND_HELPER_FUNCTION_AS
#undef BIND_DIRECTLY
#undef BIND_HELPER_FUNCTION

    return module;
}

#endif
