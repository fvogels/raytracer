#include "imaging/bitmap.h"
#include "imaging/wif_format.h"
#include "primitives/Sphere.h"
#include "primitives/Plane.h"
#include "primitives/Transformer.h"
#include "primitives/Decorator.h"
#include "cameras/PerspectiveCamera.h"
#include "math/rectangle2d.h"
#include "math/rasteriser.h"
#include "rendering/GridSampler.h"
#include "materials/UniformMaterial.h"
#include "materials/CheckeredMaterial.h"

using namespace math;
using namespace raytracer;

struct Light
{
	point3d position;

	Light(const point3d& position) : position(position) { }
};

struct Scene
{
	std::shared_ptr<Primitive> root;
	std::vector<std::shared_ptr<Light>> lights;
} scene;

std::shared_ptr<Camera> camera = nullptr;

color determine_color(const ray& r)
{
	Hit hit;
	color c = colors::black();

	if (scene.root->find_hit(r, &hit))
	{
		for (auto light : scene.lights)
		{
			vector3d hit_to_light = (light->position - hit.position).normalized();
			double cos_angle = hit_to_light.dot(hit.normal);

			if (cos_angle > 0)
			{
				c += hit.c * cos_angle;
			}
		}
	}

	return c;
}

color render_pixel(const rasteriser& window_rasteriser, int i, int j)
{
	GridSampler sampler(1, 1);
	rectangle2d pixel_rectangle = window_rasteriser[position(i, j)];
	color c = colors::black();
	int sample_count = 0;

	sampler.sample(pixel_rectangle, [&c, &sample_count](const point2d& p) {
		auto r = camera->create_ray(p);
		c += determine_color(r);
		++sample_count;
	});

	return c / sample_count;
}

void create_root()
{
	auto sphere = std::make_shared<Sphere>();
	auto material = std::make_shared<CheckeredMaterial>(colors::white(), colors::black());
	auto decorated_sphere = std::make_shared<Decorator>(material, sphere);
	scene.root = std::make_shared<Transformer>(scale(2, 2, 2), decorated_sphere);
}

void create_lights()
{
	scene.lights.push_back(std::make_shared<Light>(point3d(0, 5, 5)));
}

void create_scene()
{
	create_root();
	create_lights();
}

#ifndef TEST_BUILD
int main()
{
	Bitmap bitmap(500, 500);
	camera = create_perspective_camera(point3d(0, 0, 5), point3d(0, 0, 0), vector3d(0, 1, 0), 1, 1);
	create_scene();

	rectangle2d window(point2d(0, 0), vector2d(1, 0), vector2d(0, 1));
	rasteriser window_rasteriser(window, bitmap.width(), bitmap.height());

	bitmap.clear(colors::black());

	for (int j = 0; j != bitmap.height(); ++j)
	{
		for (int i = 0; i != bitmap.width(); ++i)
		{
			color c = render_pixel(window_rasteriser, i, j);

			bitmap[position(i, j)] = c;
		}
	}

	save_bitmap("e:/temp/output/test.bmp", bitmap);
	WIF wif("e:/temp/output/test.wif");
	wif.write_frame(bitmap);
}
#endif
