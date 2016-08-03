#include "scripting/primitives-module.h"
#include "primitives/primitives.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;


namespace
{
    struct PrimitiveLibrary
    {
        Primitive sphere() const
        {
            return primitives::sphere(); 
        }

        Primitive xy_plane() const
        {
            return primitives::xy_plane();
        }

        Primitive xz_plane() const
        {
            return primitives::xz_plane();
        }

        Primitive yz_plane() const
        {
            return primitives::yz_plane();
        }

        Primitive translate(const Vector3D& displacement, Primitive primitive) const 
        {
            return primitives::translate(displacement, primitive); 
        }

        Primitive make_union(std::vector<Primitive>& children) const
        {
            return primitives::make_union(children);
        }

        Primitive decorate(Material material, Primitive decorated) const
        {
            return primitives::decorate(material, decorated);
        }

        Primitive mesh(const std::string& path) const
        {
            return primitives::fast_mesh(path);
        }

        Primitive center(const Point3D& center, Primitive primitive) const
        {
            return primitives::center(center, primitive);
        }

        Primitive group(unsigned group_id, Primitive primitive) const
        {
            return primitives::group(group_id, primitive);
        }

        Primitive intersection(Primitive child1, Primitive child2) const
        {
            return primitives::intersection(child1, child2);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_primitives_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    auto primitive_library = std::make_shared<PrimitiveLibrary>();
    module->add_global_const(chaiscript::const_var(primitive_library), "Primitives");

#define PRIMITIVE(NAME) module->add(fun(&PrimitiveLibrary::NAME), #NAME)
#define PRIMITIVE_WITH_NAME(FACTORY, NAME) module->add(fun(&PrimitiveLibrary::FACTORY), #NAME)
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
#undef PRIMITIVE
#undef PRIMITIVE_WITH_NAME

    return module;
}