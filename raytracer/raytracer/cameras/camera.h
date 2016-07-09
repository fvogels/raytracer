#pragma once

#include "math/ray.h"
#include "math/point2d.h"
#include "math/ray.h"
#include "math/matrix4d.h"
#include <functional>
#include <memory>


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
            virtual math::Ray create_ray(const math::Point2D&) const = 0;
        };

        class DisplacableCamera : public CameraImplementation
        {
        public:
            math::Ray create_ray(const math::Point2D& p) const
            {
                auto untransformed_ray = create_untransformed_ray(p);
                auto transformed_ray = untransformed_ray.transform(m_transformation);

                return transformed_ray;
            }

        protected:
            DisplacableCamera(math::Matrix4D transformation)
                : m_transformation(transformation)
            {
                // NOP
            }

            virtual math::Ray create_untransformed_ray(const math::Point2D&) const = 0;

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