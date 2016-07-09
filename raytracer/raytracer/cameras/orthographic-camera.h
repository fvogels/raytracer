#pragma once

#include "cameras/camera.h"
#include "math/vector3d.h"
#include "math/point2d.h"
#include "math/point3d.h"
#include "math/rectangle3d.h"

#include <memory>

namespace raytracer
{
    namespace cameras
    {
        namespace _private_
        {
            class OrthographicCamera : public DisplacableCamera
            {
            public:
                OrthographicCamera(const math::Matrix4D&, double, double);

            protected:
                std::vector<math::Ray> create_untransformed_rays(const math::Point2D& point) const override;

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