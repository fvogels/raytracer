#pragma once

#include "lights/light-source.h"
#include "imaging/color.h"
#include "math/point3d.h"


namespace raytracer
{
    class PointLight : public LightSource
    {
    public:
        PointLight(const math::Point3D&, const imaging::color&);

        std::vector<LightRay> lightrays_to(const math::Point3D&) const override;

    private:
        math::Point3D position;
        imaging::color m_color;
    };
}