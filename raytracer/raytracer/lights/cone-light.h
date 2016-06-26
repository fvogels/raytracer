#pragma once

#include "lights/light-source.h"


namespace raytracer
{
    class ConeLight : public LightSource
    {
    public:
        ConeLight(const math::Point3D&, const math::Vector3D&, math::Angle, const imaging::color&);

        std::vector<LightRay> lightrays_to(const math::Point3D& p) const override;

    private:
        math::Point3D m_position;
        math::Vector3D m_direction;
        double m_min_cos;
        imaging::color m_color;
    };
}