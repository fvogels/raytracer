#include "imaging/bitmap.h"
#include "primitives/Sphere.h"
#include "cameras/PerspectiveCamera.h"
#include "math/rectangle2d.h"
#include "math/rasteriser.h"
#include "rendering/GridSampler.h"

using namespace math;
using namespace raytracer;

int main()
{
	Bitmap bitmap(500, 500);	
	auto camera = create_perspective_camera(point3d(0, 0, 5), point3d(0, 0, 0), vector3d(0, 1, 0), 1, 1);
	Sphere sphere;
	rectangle2d window(point2d(0, 1), vector2d(1, 0), vector2d(0, -1));
	rasteriser window_rasteriser(window, bitmap.width(), bitmap.height());
	GridSampler sampler(3, 3);

	bitmap.clear(colors::black());

	for (int j = 0; j != bitmap.height(); ++j)
	{
		for (int i = 0; i != bitmap.width(); ++i)
		{
			rectangle2d pixel_rectangle = window_rasteriser[position(i, j)];
			color c = colors::black();
			int sample_count = 0;

			sampler.sample(pixel_rectangle, [&camera, &sphere, &c, &sample_count](const point2d& p) {
				auto r = camera->create_ray(p);

				Hit hit;
				if (sphere.find_hit(r, &hit))
				{
					c += colors::red();
				}

				++sample_count;
			});

			bitmap[position(i, j)] = c / sample_count;
		}
	}

	save_bitmap("e:/temp/test.bmp", bitmap);
}