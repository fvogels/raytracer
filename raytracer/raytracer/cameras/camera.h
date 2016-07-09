#pragma once

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
            math::Matrix4D create_transformation(const math::Point3D&, const math::Point3D&, const math::Vector3D&);
        }

        class CameraImplementation
        {
        public:
            virtual std::vector<math::Ray> create_rays(const math::Point2D&) const = 0;
        };

        class DisplacableCamera : public CameraImplementation
        {
        public:
            std::vector<math::Ray> create_rays(const math::Point2D& p) const
            {
                auto untransformed_rays = create_untransformed_rays(p);

                std::vector<math::Ray> transformed_rays;
                for (auto& untransformed_ray : untransformed_rays)
                {
                    auto transformed_ray = untransformed_ray.transform(m_transformation);

                    transformed_rays.push_back(transformed_ray);
                }
                
                return transformed_rays;
            }

        protected:
            DisplacableCamera(math::Matrix4D transformation)
                : m_transformation(transformation)
            {
                // NOP
            }

            virtual std::vector<math::Ray> create_untransformed_rays(const math::Point2D&) const = 0;

        private:
            math::Matrix4D m_transformation;
        };

        class Camera
        {
        public:
            Camera() : m_implementation(nullptr) { }

            Camera(std::shared_ptr<CameraImplementation> implementation)
                : m_implementation(implementation) { }

            CameraImplementation* operator ->() const
            {
                return m_implementation.get();
            }

        private:
            std::shared_ptr<CameraImplementation> m_implementation;
        };
    }
}