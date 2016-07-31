#pragma once

#include "cameras/displaceable-camera.h"
#include "math/vector.h"
#include "math/point.h"
#include "math/point.h"
#include "math/rectangle3d.h"

#include <memory>

namespace raytracer
{
    namespace cameras
    {
        namespace _private_
        {
            class OrthographicCamera : public DisplaceableCamera
            {
            public:
                OrthographicCamera(const math::Matrix4D&, double, double);

            protected:
                void enumerate_untransformed_rays(const math::Point2D& point, std::function<void(const math::Ray&)>) const override;

            private:
                math::Rectangle3D m_eye_window;
            };
        }

        Camera orthographic(
            const math::Point3D& eye,
            const math::Point3D& look_at,
            const math::Vector3D& up,
            double window_width,
            double aspect_ratio);
    }
}