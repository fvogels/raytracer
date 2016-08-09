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
    Primitive sphere()
    {
        return primitives::sphere(); 
    }

    Primitive xy_plane()
    {
        return primitives::xy_plane();
    }

    Primitive xz_plane()
    {
        return primitives::xz_plane();
    }

    Primitive yz_plane()
    {
        return primitives::yz_plane();
    }

    Primitive translate(const Vector3D& displacement, Primitive primitive) 
    {
        return primitives::translate(displacement, primitive); 
    }

    Primitive make_union(const std::vector<chaiscript::Boxed_Value>& boxed_children)
    {
        std::vector<Primitive> children(boxed_children.size());

        std::transform(boxed_children.begin(), boxed_children.end(), children.begin(), [](chaiscript::Boxed_Value boxed) {
            return chaiscript::boxed_cast<Primitive>(boxed);
        });

        return primitives::make_union(children);
    }

    Primitive decorate(Material material, Primitive decorated)
    {
        return primitives::decorate(material, decorated);
    }

    Primitive mesh(const std::string& path)
    {
        return primitives::fast_mesh(path);
    }

    Primitive center(const Point3D& center, Primitive primitive)
    {
        return primitives::center(center, primitive);
    }

    Primitive group(unsigned group_id, Primitive primitive)
    {
        return primitives::group(group_id, primitive);
    }

    Primitive intersection(Primitive child1, Primitive child2)
    {
        return primitives::intersection(child1, child2);
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

#define PRIMITIVE(NAME) module->add(fun(&NAME), #NAME)
#define PRIMITIVE_WITH_NAME(FACTORY, NAME) module->add(fun(&FACTORY), #NAME)
    PRIMITIVE(sphere);
    PRIMITIVE(xy_plane);
    PRIMITIVE(xz_plane);
    PRIMITIVE(yz_plane);
    PRIMITIVE(translate);
    PRIMITIVE_WITH_NAME(make_union, union);
    PRIMITIVE(decorate);
    PRIMITIVE(mesh);
    PRIMITIVE(center);
    PRIMITIVE(group);
    PRIMITIVE(intersection);
    PRIMITIVE_WITH_NAME(bumpify2d_timed, bumpify);
#undef PRIMITIVE
#undef PRIMITIVE_WITH_NAME

    return module;
}