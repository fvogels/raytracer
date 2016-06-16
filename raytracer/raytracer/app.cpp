#ifndef TEST_BUILD

#include "imaging/bitmap.h"
#include "imaging/wif_format.h"
#include "primitives/primitives.h"
#include "cameras/perspective-camera.h"
#include "math/rectangle2d.h"
#include "math/rasterizer.h"
#include "rendering/grid-sampler.h"
#include "materials/uniform-material.h"
#include "materials/materials.h"
#include "math/worley-noise2d.h"
#include "scripting/objects.h"
#include "scripting/objects/function.h"
#include "easylogging++.h"
#include <assert.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <type_traits>
#include <list>

using namespace math;
using namespace raytracer;

void initialize_logger()
{
	el::Configurations defaultConf;
	defaultConf.setToDefault();
	defaultConf.set(el::Level::Debug, el::ConfigurationType::Format, "[%level] (%fbase:%line) %msg");
	defaultConf.set(el::Level::Debug, el::ConfigurationType::Enabled, "false");
	el::Loggers::reconfigureLogger("stdlib", defaultConf);
}

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
	GridSampler sampler(2, 2);
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
	
	auto material = raytracer::materials::checkered(colors::white(), colors::black());
	auto decorated_sphere = std::make_shared<Decorator>(material, sphere);
	auto s1 = std::make_shared<Transformer>(rotate_y(degrees(180 * t)), decorated_sphere);

	//auto sphere2 = std::make_shared<Sphere>();
	//auto decorated_sphere2 = std::make_shared<Decorator>(material, sphere2);
	//auto s2 = std::make_shared<Transformer>(translation(Vector3D(-2, 0, 0)), decorated_sphere2);

	auto all = std::make_shared<Union>(std::vector<std::shared_ptr<Primitive>> { s1 } );

	scene.root = all;
}

void create_lights(double t)
{
	scene.lights.clear();
	scene.lights.push_back(std::make_shared<Light>(Point3D(0, 2, 5)));
}

void create_scene(double t)
{
	create_root(t);
	create_lights(t);
}


void worley()
{
	WIF wif("e:/temp/output/test.wif");

	Bitmap bitmap(500, 500);
	auto noise = math::create_worley_noise2d();

	for (int y = 0; y != bitmap.height(); ++y)
	{
		for (int x = 0; x != bitmap.width(); ++x)
		{
			position pos(x, y);
			Point2D p(double(x) / bitmap.width() * 5, double(y) / bitmap.height() * 5);
			double value = (*noise)(p);

			value = value * 2;

			value = std::max<double>(value, 0);
			value = std::min<double>(value, 1);

			assert(0 <= value);
			assert(value <= 1);

			bitmap[pos] = colors::white() * value;
		}
	}

	wif.write_frame(bitmap);
}


int main()
{
	auto x = atan2(-1, 0.001);
	x = atan2(-1, -0.001);

	initialize_logger();

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
