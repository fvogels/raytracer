#pragma once

#include "lights/light-source.h"
#include "imaging/color.h"
#include "math/point3d.h"
#include "util/maybe.h"


namespace raytracer
{
    class PointLight : public LightSource
    {
    public:
        PointLight(const math::Point3D&);

        std::vector<LightRay> lightrays_to(const math::Point3D&) const override;

    protected:
        virtual LightRay cast_lightray_to(const math::Point3D&) const = 0;

        math::Point3D m_position;
    };
}