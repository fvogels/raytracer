#include "chai/materials-module.h"
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
        Material uniform(const color& ambient, const color& diffuse, const color& specular, double specular_exponent, double reflectivity)
        {
            MaterialProperties properties;

            properties.ambient = ambient;
            properties.diffuse = diffuse;
            properties.specular = specular;
            properties.specular_exponent = specular_exponent;
            properties.reflectivity = reflectivity;

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
#undef COLOR

    return module;
}