#pragma once

#include "cameras/camera.h"
#include "math/vector.h"
#include "math/point.h"
#include "math/point.h"
#include "math/rectangle2d.h"
#include "math/rectangle3d.h"
#include "samplers/sampler.h"
#include <memory>


namespace raytracer
{
    namespace cameras
    {
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