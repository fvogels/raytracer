#pragma once

#include "cameras/displaceable-camera.h"
#include "math/vector3d.h"
#include "math/point2d.h"
#include "math/point3d.h"
#include "math/rectangle2d.h"
#include "math/rectangle3d.h"
#include "sampling/sampler.h"
#include <memory>


namespace raytracer
{
    namespace cameras
    {
        namespace _private_
        {
            class DepthOfFieldPerspectiveCamera : public DisplaceableCamera
            {
            public:
                DepthOfFieldPerspectiveCamera(const math::Matrix4D, const math::Point3D&, double, double, double, raytracer::samplers::Sampler);

            protected:
                void enumerate_untransformed_rays(const math::Point2D&, std::function<void(const math::Ray&)>) const;

            private:
                math::Rectangle2D m_eye_window;
                raytracer::samplers::Sampler m_eye_sampler;
                math::Point3D m_look_at;
                double m_focal_distance;
                double m_distance;
                double m_aspect_ratio;
            };
        }

        Camera depth_of_field_perspective(
            const math::Point3D& eye,
            const math::Point3D& look_at,
            const math::Vector3D& up,
            double distance,
            double aspect_ratio,
            double eye_size,
            raytracer::samplers::Sampler eye_sampler);
    }
}