#include "imaging/bitmap.h"
#include "imaging/wif_format.h"
#include "primitives/Sphere.h"
#include "primitives/Plane.h"
#include "primitives/transformer.h"
#include "primitives/Decorator.h"
#include "cameras/PerspectiveCamera.h"
#include "math/rectangle2d.h"
#include "math/Rasterizer.h"
#include "rendering/GridSampler.h"
#include "materials/UniformMaterial.h"
#include "materials/CheckeredMaterial.h"
#include <assert.h>

using namespace math;
using namespace Raytracer;

struct Light
{
	Point3D position;

	Light(const Point3D& position) : position(position) { }
};

struct Scene
{
	std::shared_ptr<Primitive> root;
	std::vector<std::shared_ptr<Light>> lights;
} scene;

std::shared_ptr<Camera> camera = nullptr;

color determine_color(const Ray& r)
{
	Hit hit;
	color c = colors::black();

	if (scene.root->find_hit(r, &hit))
	{
		for (auto light : scene.lights)
		{
			Vector3D hit_to_light = (light->position - hit.position).normalized();
			double cos_angle = hit_to_light.dot(hit.normal);

			assert(hit.normal.is_unit());
			assert(-1 <= cos_angle && cos_angle <= 1);

			if (cos_angle > 0)
			{
				c += hit.c * cos_angle;
			}
		}
	}

	return c;
}

color render_pixel(const Rasterizer& window_rasteriser, int i, int j)
{
	GridSampler sampler(1, 1);
	Rectangle2D pixel_rectangle = window_rasteriser[position(i, j)];
	color c = colors::black();
	int sample_count = 0;

	sampler.sample(pixel_rectangle, [&c, &sample_count](const Point2D& p) {
		auto ray = camera->create_Ray(p);
		c += determine_color(ray);
		++sample_count;
	});

	return c / sample_count;
}

void create_root(double t)
{
	auto sphere = std::make_shared<Sphere>();
	auto material = std::make_shared<CheckeredMaterial>(colors::white(), colors::black());
	auto decorated_sphere = std::make_shared<Decorator>(material, sphere);
	scene.root = std::make_shared<Transformer>(scale(t + 1, t + 1, t + 1), decorated_sphere);
}

void create_lights(double t)
{
	scene.lights.clear();
	scene.lights.push_back(std::make_shared<Light>(Point3D(0, 5, 5)));
}

void create_scene(double t)
{
	create_root(t);
	create_lights(t);
}

#ifndef TEST_BUILD
int main()
{
	const int FRAME_COUNT = 30;
	WIF wif("e:/temp/output/test.wif");

	for (int frame = 0; frame != FRAME_COUNT; ++frame)
	{
		std::cout << "Rendering frame " << frame << std::endl;

		Bitmap bitmap(500, 500);
		camera = create_perspective_camera(Point3D(0, 0, 5), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
		create_scene(double(frame) / FRAME_COUNT);

		Rectangle2D window(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
		Rasterizer window_rasteriser(window, bitmap.width(), bitmap.height());

		bitmap.clear(colors::black());

		for (int j = 0; j != bitmap.height(); ++j)
		{
			for (int i = 0; i != bitmap.width(); ++i)
			{
				color c = render_pixel(window_rasteriser, i, j);

				bitmap[position(i, j)] = c;
			}
		}

		wif.write_frame(bitmap);
	}
}
#endif
