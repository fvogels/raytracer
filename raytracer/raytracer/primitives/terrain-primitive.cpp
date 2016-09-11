#include "primitives/terrain-primitive.h"
#include "primitives/primitives.h"
#include "math/misc.h"
#include "math/interval.h"
#include "math/functions.h"
#include "easylogging++.h"
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


Primitive raytracer::primitives::terrain()
{
    TIMED_FUNC(timerObj);
    LOG(INFO) << "Building terrain...";

    const double delta = 0.1;
    const double size = 10;
    std::vector<Primitive> terrain_mesh;
    auto perlin = math::functions::perlin<double, Point2D>(5, 46873);

    for (double x = 0.0; x < size; x += delta)
    {
        for (double z = 0; z < size; z += delta)
        {
            Point2D lower_left_2d(x, z);
            Point2D lower_right_2d = lower_left_2d + Vector2D(delta, 0);
            Point2D upper_left_2d = lower_left_2d + Vector2D(0, delta);
            Point2D upper_right_2d = lower_left_2d + Vector2D(delta, delta);

#           define COMPUTE_Y(POS)   double POS ## _y = perlin( POS ## _2d )
            COMPUTE_Y(lower_left);
            COMPUTE_Y(lower_right);
            COMPUTE_Y(upper_left);
            COMPUTE_Y(upper_right);
#           undef COMPUTE_Y

#           define COMPUTE_VERTEX(POS)   Point3D POS( POS ## _2d.x(), POS ## _y, POS ## _2d.y() )
            COMPUTE_VERTEX(lower_left);
            COMPUTE_VERTEX(lower_right);
            COMPUTE_VERTEX(upper_left);
            COMPUTE_VERTEX(upper_right);
#           undef COMPUTE_VERTEX

            Primitive triangle1 = triangle(lower_left, upper_right, lower_right);
            Primitive triangle2 = triangle(lower_left, upper_left, upper_right);

            terrain_mesh.push_back(triangle1);
            terrain_mesh.push_back(triangle2);
        }
    }

    LOG(INFO) << "Created terrain with " << terrain_mesh.size() << " triangles";

    return accelerated_mesh(terrain_mesh);
}