#include "imaging/bitmap.h"
#include "primitives/Sphere.h"
#include "cameras/PerspectiveCamera.h"

using namespace math;
using namespace raytracer;

int main()
{
	Bitmap bitmap(500, 500);	
	auto camera = create_perspective_camera(point3d(0, 0, 5), point3d(0, 0, 0), vector3d(0, 1, 0), 1, 1);
	Sphere sphere;

	bitmap.clear(colors::black());

	for (int j = 0; j != bitmap.height(); ++j)
	{
		for (int i = 0; i != bitmap.width(); ++i)
		{
			double x = double(i) / bitmap.width();
			double y = double(j) / bitmap.height();

			auto r = camera->create_ray(point2d(x, y));

			Hit hit;
			if (sphere.find_hit(r, &hit))
			{
				bitmap[position(i, j)] = colors::red();
			}
		}
	}

	save_bitmap("e:/temp/test.bmp", bitmap);
}