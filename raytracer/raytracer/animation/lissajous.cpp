#include "animation/lissajous.h"
#include "animation/interval-animation.h"
#include "math/function.h"

using namespace animation;
using namespace math;

namespace
{
    Animation<double> create_from_parameters(const LissajousParameters& parameters, Duration duration)
    {
        auto angle_animation = animation::interval<Angle>(math::interval(0_degrees, 360_degrees), duration);

        std::function<double(TimeStamp)> lambda = [=](TimeStamp now) -> double
        {
            auto angle = angle_animation(now);

            return parameters.amplitude * sin(parameters.frequency * angle + parameters.phase);
        };
        
        return make_animation(from_lambda(lambda), duration);
    }
}


Animation<math::Point3D> animation::lissajous(const LissajousParameters& x_parameters, const LissajousParameters& y_parameters, const LissajousParameters& z_parameters, Duration duration)
{
    auto x_anim = create_from_parameters(x_parameters, duration);
    auto y_anim = create_from_parameters(y_parameters, duration);
    auto z_anim = create_from_parameters(z_parameters, duration);

    std::function<Point3D(TimeStamp)> lambda = [=](TimeStamp now)
    {
        return Point3D(x_anim(now), y_anim(now), z_anim(now));
    };

    return make_animation(from_lambda(lambda), duration);
}