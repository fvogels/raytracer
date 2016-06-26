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
        class PerspectiveCamera : public DisplacableCamera
        {
        public:
            PerspectiveCamera(const math::Matrix4D transformation, const math::Rectangle3D&);

        protected:
            math::Ray create_untransformed_ray(const math::Point2D&) const;

        private:
            math::Rectangle3D m_view_window;
        };
    }
}