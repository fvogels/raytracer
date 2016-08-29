#ifndef EXCLUDE_SCRIPTING

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

        Material uniform_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
        {
            START_ARGUMENTS(argument_map);
            OPTIONAL_ARGUMENT(Color, ambient, colors::black());
            OPTIONAL_ARGUMENT(Color, diffuse, colors::black());
            OPTIONAL_ARGUMENT(Color, specular, colors::black());
            OPTIONAL_ARGUMENT(double, specular_exponent, 10);
            OPTIONAL_ARGUMENT(double, reflectivity, 0.0);
            OPTIONAL_ARGUMENT(double, transparency, 0.0);
            OPTIONAL_ARGUMENT(double, refractive_index, 1.0);
            END_ARGUMENTS();

            MaterialProperties properties(ambient, diffuse, specular, specular_exponent, reflectivity, transparency, refractive_index);

            return raytracer::materials::uniform(properties);
        }

        Material texture(const std::string& path) const
        {
            return raytracer::materials::texture(path);
        }

        Material lines(double thickness, Material m1, Material m2) const
        {
            return raytracer::materials::horizontal_lines(thickness, m1, m2);
        }

        Material grid(double thickness, Material m1, Material m2) const
        {
            return raytracer::materials::grid(thickness, m1, m2);
        }

        Material checkered(Material x, Material y) const
        {
            return raytracer::materials::checkered(x, y);
        }

        Material polka(double radius, Material x, Material y) const
        {
            return raytracer::materials::polka(radius, x, y);
        }

        Material chaotic_polka(unsigned density, Material x, Material y) const
        {
            return raytracer::materials::chaotic_polka(density, x, y);
        }

        Material marble2d(unsigned octaves, double turbulence) const
        {
            return raytracer::materials::marble2d(octaves, turbulence);
        }

        Material marble3d(unsigned octaves, double turbulence) const
        {
            return raytracer::materials::marble3d(octaves, turbulence);
        }

        Material wood2d(unsigned octaves, double turbulence) const
        {
            return raytracer::materials::wood2d(octaves, turbulence);
        }

        Material worley2d(unsigned density, double factor, double power) const
        {
            return raytracer::materials::worley2d(density, factor, power);
        }

        Material worley3d(unsigned density, double factor, double power) const
        {
            return raytracer::materials::worley3d(density, factor, power);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_materials_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<Material>(*module, "Material");

    auto material_library = std::make_shared<MaterialLibrary>();
    module->add_global_const(chaiscript::const_var(material_library), "Materials");

#define BIND_AS(INTERNAL, EXTERNAL)     module->add(fun(&MaterialLibrary::INTERNAL), #EXTERNAL)
#define BIND(NAME)                      BIND_AS(NAME, NAME)
    BIND(uniform);
    BIND_AS(uniform_by_map, uniform);
    BIND(texture);
    BIND(lines);
    BIND(grid);
    BIND(checkered);
    BIND(polka);
    BIND(chaotic_polka);
    BIND(marble2d);
    BIND(marble3d);
    BIND(wood2d);
    BIND(worley2d);
    BIND(worley3d);
#undef BIND
#undef BIND_AS

    return module;
}

#endif
