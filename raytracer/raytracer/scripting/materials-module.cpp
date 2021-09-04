#ifndef EXCLUDE_SCRIPTING

#include "scripting/materials-module.h"
#include "scripting/scripting-util.h"
#include "materials/materials.h"
#include "materials/material-transformer.h"
#include "imaging/color.h"
#include "patterns/pattern.h"


using namespace chaiscript;
using namespace raytracer;
using namespace math;
using namespace imaging;


namespace
{
    /// <summary>
    /// Material Library. Groups all material-related functions together.
    /// </summary>
    struct MaterialLibrary
    {
        Material uniform(const Color& ambient,
                         const Color& diffuse,
                         const Color& specular,
                         double specular_exponent,
                         const Color& light_filtering,
                         double reflectivity,
                         double opacity,
                         double transparency,
                         double refractive_index) const
        {
            MaterialProperties properties = MaterialPropertiesBuilder()
                .ambient(ambient)
                .diffuse(diffuse)
                .specular(specular, specular_exponent)
                .light_filtering(light_filtering)
                .reflectivity(reflectivity)
                .opacity(opacity)
                .transparency(transparency, refractive_index)
                .build();

            return raytracer::materials::uniform(properties);
        }

        Material uniform_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
        {
            START_ARGUMENTS(argument_map);
            OPTIONAL_ARGUMENT(Color, ambient, colors::black());
            OPTIONAL_ARGUMENT(Color, diffuse, colors::black());
            OPTIONAL_ARGUMENT(Color, specular, colors::black());
            OPTIONAL_ARGUMENT(double, specular_exponent, 10);
            OPTIONAL_ARGUMENT(Color, light_filtering, colors::black());
            OPTIONAL_ARGUMENT(double, reflectivity, 0.0);
            OPTIONAL_ARGUMENT(double, opacity, 1.0);
            OPTIONAL_ARGUMENT(double, transparency, 0.0);
            OPTIONAL_ARGUMENT(double, refractive_index, 1.0);
            END_ARGUMENTS();

            MaterialProperties properties = MaterialPropertiesBuilder()
                .ambient(ambient)
                .diffuse(diffuse)
                .specular(specular, specular_exponent)
                .light_filtering(light_filtering)
                .reflectivity(reflectivity)
                .opacity(opacity)
                .transparency(transparency, refractive_index)
                .build();

            return raytracer::materials::uniform(properties);
        }

        Material texture(const std::string& path) const
        {
            return raytracer::materials::texture(path);
        }

        Material from_pattern2d(patterns::Pattern2D pattern, Material m1, Material m2) const
        {
            return raytracer::materials::pattern2d(pattern, m1, m2);
        }

        Material from_pattern3d(patterns::Pattern3D pattern, Material m1, Material m2) const
        {
            return raytracer::materials::pattern3d(pattern, m1, m2);
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

        Material scale2d(double sx, double sy, Material material) const
        {
            return raytracer::materials::scale(sx, sy, material);
        }

        Material scale3d(double sx, double sy, double sz, Material material) const
        {
            return raytracer::materials::scale(sx, sy, sz, material);
        }

        Material translate2d(const Vector2D& v, Material material) const
        {
            return raytracer::materials::translate(v, material);
        }

        Material translate3d(const Vector3D& v, Material material) const
        {
            return raytracer::materials::translate(v, material);
        }

        Material rotate(Angle angle, Material material) const
        {
            return raytracer::materials::rotate(angle, material);
        }

        Material rotate_around_x(Angle angle, Material material) const
        {
            return raytracer::materials::rotate_around_x(angle, material);
        }

        Material rotate_around_y(Angle angle, Material material) const
        {
            return raytracer::materials::rotate_around_y(angle, material);
        }

        Material rotate_around_z(Angle angle, Material material) const
        {
            return raytracer::materials::rotate_around_z(angle, material);
        }

        Material slice(Material material, animation::TimeStamp ts) const
        {
            return raytracer::to_animated_2d_material(material)(ts);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_materials_module()
{
    // Create new module
    auto module = std::make_shared<chaiscript::Module>();

    // Tell chaiscript about Material type
    util::register_type<Material>(*module, "Material");

    // Create library
    auto material_library = std::make_shared<MaterialLibrary>();

    // Expose library (member functions still need to be exposed separately)
    module->add_global_const(chaiscript::const_var(material_library), "Materials");

    // Exposes library function named INTERNAL as chaiscript function named EXTERNAL
#   define BIND_AS(INTERNAL, EXTERNAL)     module->add(fun(&MaterialLibrary::INTERNAL), #EXTERNAL)

    // Exposes library function under the same name
#   define BIND(NAME)                      BIND_AS(NAME, NAME)
    BIND(uniform);
    BIND_AS(uniform_by_map, uniform);
    BIND(texture);
    BIND_AS(from_pattern2d, from_pattern);
    BIND_AS(from_pattern3d, from_pattern);
    BIND(marble2d);
    BIND(marble3d);
    BIND(wood2d);
    BIND(worley2d);
    BIND(worley3d);
    BIND_AS(scale2d, scale);
    BIND_AS(scale3d, scale);
    BIND_AS(translate2d, translate);
    BIND_AS(translate3d, translate);
    BIND(rotate);
    BIND(rotate_around_x);
    BIND(rotate_around_y);
    BIND(rotate_around_z);
    BIND(slice);
#   undef BIND
#   undef BIND_AS

    return module;
}

#endif
