#ifndef TEST_BUILD

#include "imaging/bitmap.h"
#include "imaging/wif_format.h"
#include "primitives/primitives.h"
#include "cameras/perspective-camera.h"
#include "math/rectangle2d.h"
#include "math/rasterizer.h"
#include "rendering/grid-sampler.h"
#include "materials/materials.h"
#include "math/functions/noise.h"
#include "scripting/objects.h"
#include "scripting/objects/function.h"
#include "meta/function-traits.h"
#include "easylogging++.h"
#include "logging.h"
#include <assert.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <type_traits>
#include <list>
#include <thread>
#include <atomic>

const int N_THREADS = 4;

using namespace math;
using namespace raytracer;
using namespace imaging;


struct Light
{
	Point3D position;

	Light(const Point3D& position) : position(position) { }
};

struct Scene
{
	std::shared_ptr<raytracer::primitives::Primitive> root;
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

			if (cos_angle > 0 && hit.material)
			{
				color hit_color = hit.material->at(hit.local_position).color;

				c += hit_color * cos_angle;
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
	auto shape = raytracer::primitives::sphere();
	auto material = raytracer::materials::checkered(colors::red(), colors::blue());
	auto decorated_shape = raytracer::primitives::decorate(material, shape);
	auto s1 = raytracer::primitives::rotate_around_y(180_degrees * t, decorated_shape);

	auto all = raytracer::primitives::group(std::vector<std::shared_ptr<raytracer::primitives::Primitive>> { s1 });

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

	Bitmap bitmap(200, 200);
	auto noise = math::functions::worley_noise2d();

	for (int y = 0; y != bitmap.height(); ++y)
	{
		for (int x = 0; x != bitmap.width(); ++x)
		{
			position pos(x, y);
			Point2D p(double(x) / bitmap.width() * 5, double(y) / bitmap.height() * 5);
			double value = noise(p);

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
	TIMED_FUNC(timerObj);

	logging::configure();

	const int FRAME_COUNT = 30;
	WIF wif("e:/temp/output/test.wif");

	for (int frame = 0; frame != FRAME_COUNT; ++frame)
	{
		TIMED_SCOPE(timerObj, "single frame");

		std::cout << "Rendering frame " << frame << std::endl;

		Bitmap bitmap(500, 500);
		camera = create_perspective_camera(Point3D(0, 0, 5), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
		create_scene(double(frame) / FRAME_COUNT);

		Rectangle2D window(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
		Rasterizer window_rasteriser(window, bitmap.width(), bitmap.height());

		bitmap.clear(colors::black());

		if (N_THREADS > 1)
		{
			std::atomic<unsigned> j = 0;
			std::vector<std::thread> threads;

			for (int k = 0; k != N_THREADS; ++k)
			{
				threads.push_back(std::thread([&]() {
					unsigned current;

					while ((current = j++) < bitmap.height())
					{
						for (int i = 0; i != bitmap.width(); ++i)
						{
							color c = render_pixel(window_rasteriser, i, current);

							bitmap[position(i, current)] = c;
						}
					}
				}));
			}

			for (auto& thread : threads)
			{
				thread.join();
			}
		}
		else
		{
			for (int j = 0; j != bitmap.height(); ++j)
			{
				for (int i = 0; i != bitmap.width(); ++i)
				{
					color c = render_pixel(window_rasteriser, i, j);

					bitmap[position(i, j)] = c;
				}
			}
		}

		wif.write_frame(bitmap);
	}
}
#endif
