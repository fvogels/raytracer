#pragma once

#include "imaging/color.h"


namespace raytracer
{
    struct MaterialProperties
    {
        MaterialProperties(const imaging::Color& ambient, const imaging::Color& diffuse, const imaging::Color& specular, double specular_exponent, double reflectivity, double opacity, double transparency, double refractive_index);

        const imaging::Color ambient;
        const imaging::Color diffuse;
        const imaging::Color specular;
        const double specular_exponent;
        const double reflectivity;
        const double opacity;
        const double transparency;
        const double refractive_index;
    };

    class MaterialPropertiesBuilder
    {
    public:
        MaterialPropertiesBuilder();

        MaterialPropertiesBuilder& ambient(const imaging::Color& color);
        MaterialPropertiesBuilder& diffuse(const imaging::Color& color);
        MaterialPropertiesBuilder& specular(const imaging::Color& color, double exponent);
        MaterialPropertiesBuilder& reflectivity(double reflectivity);
        MaterialPropertiesBuilder& opacity(double opacity);
        MaterialPropertiesBuilder& transparency(double transparency, double refractive_index);

        MaterialProperties build() const;

    private:
        imaging::Color m_ambient;
        imaging::Color m_diffuse;
        imaging::Color m_specular;
        double m_specular_exponent;
        double m_reflectivity;
        double m_opacity;
        double m_transparency;
        double m_refractive_index;
    };
}