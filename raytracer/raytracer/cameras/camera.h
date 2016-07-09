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

            class CameraImplementation
            {
            public:
                virtual std::vector<math::Ray> create_rays(const math::Point2D&) const;
                virtual void enumerate_rays(const math::Point2D&, std::function<void(const math::Ray&)>) const = 0;
            };
        }

        class Camera
        {
        public:
            Camera() : m_implementation(nullptr) { }

            Camera(std::shared_ptr<_private_::CameraImplementation> implementation)
                : m_implementation(implementation) { }

            _private_::CameraImplementation* operator ->() const
            {
                return m_implementation.get();
            }

        private:
            std::shared_ptr<_private_::CameraImplementation> m_implementation;
        };
    }
}