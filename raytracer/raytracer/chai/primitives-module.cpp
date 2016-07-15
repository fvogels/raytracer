#include "chai/primitives-module.h"
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

        Primitive translate(const Vector3D& displacement, Primitive primitive) const 
        {
            return primitives::translate(displacement, primitive); 
        }

        Primitive group(std::vector<Primitive>& children) const
        {
            return primitives::group(children);
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
    PRIMITIVE(translate);
    PRIMITIVE_WITH_NAME(group, union);
#undef COLOR

    return module;
}