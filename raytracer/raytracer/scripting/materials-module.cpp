#include "scripting/materials-module.h"
#include "scripting/scripting-util.h"
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

        Material uniform_by_map(const std::map<std::string, Boxed_Value> argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(Color, ambient);
            ARGUMENT(Color, diffuse);
            ARGUMENT(Color, specular);
            ARGUMENT(double, specular_exponent);
            ARGUMENT(double, reflectivity);
            ARGUMENT(double, transparency);
            ARGUMENT(double, refractive_index);
            END_ARGUMENTS();

            MaterialProperties properties(ambient, diffuse, specular, specular_exponent, reflectivity, transparency, refractive_index);

            return raytracer::materials::uniform(properties);
        }

        Material texture(const std::string& path) const
        {
            return raytracer::materials::texture(path);
        }

        Material checkered(Material x, Material y) const
        {
            return raytracer::materials::checkered(x, y);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_materials_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<Material>(*module, "Material");

    auto material_library = std::make_shared<MaterialLibrary>();
    module->add_global_const(chaiscript::const_var(material_library), "Materials");

#define MATERIAL_NAMED(INTERNAL, EXTERNAL) module->add(fun(&MaterialLibrary::INTERNAL), #EXTERNAL)
#define MATERIAL(NAME) MATERIAL_NAMED(NAME, NAME)
    MATERIAL(uniform);
    MATERIAL_NAMED(uniform_by_map, uniform);
    MATERIAL(texture);
    MATERIAL(checkered);
#undef MATERIAL
#undef MATERIAL_NAMED

    return module;
}
