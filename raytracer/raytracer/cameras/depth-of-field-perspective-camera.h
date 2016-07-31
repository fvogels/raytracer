#pragma once

#include "cameras/displaceable-camera.h"
#include "math/vector.h"
#include "math/point.h"
#include "math/point.h"
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
                DepthOfFieldPerspectiveCamera(const math::Matrix4D, const std::vector<Camera>&);

            protected:
                void enumerate_untransformed_rays(const math::Point2D&, std::function<void(const math::Ray&)>) const;

            private:
                std::vector<Camera> m_cameras;
            };
        }

        Camera depth_of_field_perspective(
            const math::Point3D& eye,
            const math::Point3D& look_at,
            const math::Vector3D& up,
            double distance,
            double aspect_ratio,
            double eye_size,
            raytracer::Sampler eye_sampler);
    }
}