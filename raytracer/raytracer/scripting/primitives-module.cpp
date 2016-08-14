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

#define BIND(NAME)                  BIND_AS(NAME, NAME)
#define BIND_NS(NAMESPACE, NAME)    BIND_AS(NAMESPACE::NAME, NAME)
#define BIND_AS(FACTORY, NAME)      module->add(fun(&FACTORY), #NAME)
    BIND_NS(raytracer::primitives, sphere);
    BIND_NS(raytracer::primitives, xy_plane);
    BIND_NS(raytracer::primitives, xz_plane);
    BIND_NS(raytracer::primitives, yz_plane);
    BIND_NS(raytracer::primitives, cylinder_along_x);
    BIND_NS(raytracer::primitives, cylinder_along_y);
    BIND_NS(raytracer::primitives, cylinder_along_z);
    BIND_NS(raytracer::primitives, triangle);
    BIND_NS(raytracer::primitives, translate);
    BIND_NS(raytracer::primitives, rotate_around_x);
    BIND_NS(raytracer::primitives, rotate_around_y);
    BIND_NS(raytracer::primitives, rotate_around_z);
    BIND_NS(raytracer::primitives, align_y_to);
    BIND_NS(raytracer::primitives, scale);
    BIND_AS(make_union, union);
    BIND_AS(make_accelerated_union, bbunion);
    BIND_NS(raytracer::primitives, decorate);
    BIND(mesh);
    BIND_NS(raytracer::primitives, center);
    BIND_NS(raytracer::primitives, group);
    BIND_NS(raytracer::primitives, intersection);
    BIND_NS(raytracer::primitives, crop_along_x);
    BIND_NS(raytracer::primitives, crop_along_y);
    BIND_NS(raytracer::primitives, crop_along_z);
    BIND_NS(raytracer::primitives, crop_spherical);
    BIND_AS(bumpify2d_timed, bumpify);
#undef BIND_AS
#undef BIND

    return module;
}

#endif
