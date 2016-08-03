#include "scripting/materials-module.h"
#include "materials/materials.h"
#include "imaging/color.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;
using namespace imaging;


namespace
{
    struct MaterialLibrary
    {
        Material uniform(const Color& ambient, const Color& diffuse, const Color& specular, double specular_exponent, double reflectivity, double transparency, double refractive_index) const
        {
            MaterialProperties properties(ambient, diffuse, specular, specular_exponent, reflectivity, transparency, refractive_index);

            return raytracer::materials::uniform(properties);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_materials_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    auto material_library = std::make_shared<MaterialLibrary>();
    module->add_global_const(chaiscript::const_var(material_library), "Materials");

#define MATERIAL(NAME) module->add(fun(&MaterialLibrary::NAME), #NAME)
    MATERIAL(uniform);
#undef MATERIAL

    return module;
}
