#pragma once

#include "cameras/camera.h"
#include "math/ray.h"
#include "math/point2d.h"
#include "math/ray.h"
#include "math/matrix4d.h"
#include <functional>
#include <memory>
#include <vector>


namespace raytracer
{
    namespace cameras
    {
        namespace _private_
        {
            class DisplaceableCamera : public CameraImplementation
            {
            public:
                std::vector<math::Ray> create_rays(const math::Point2D&) const;

            protected:
                DisplaceableCamera(const math::Matrix4D&);

                virtual std::vector<math::Ray> create_untransformed_rays(const math::Point2D&) const = 0;

            private:
                math::Matrix4D m_transformation;
            };
        }
    }
}