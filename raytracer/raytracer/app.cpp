#ifndef TEST_BUILD

#include "imaging/bitmap.h"
#include "imaging/wif_format.h"
#include "primitives/primitives.h"
#include "cameras/cameras.h"
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

const int FRAME_COUNT = 30;
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
	raytracer::primitives::Primitive root;
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

color render_pixel(const Rasterizer& window_rasteriser, int x, int y)
{
	GridSampler sampler(1, 1);
	Rectangle2D pixel_rectangle = window_rasteriser[position(x, y)];
	color c = colors::black();
	int sample_count = 0;

	sampler.sample(pixel_rectangle, [&c, &sample_count](const Point2D& p) {
		auto ray = camera->create_ray(p);
		c += determine_color(ray);
		++sample_count;
	});

	return c / sample_count;
}

void create_root(double t)
{
	using namespace raytracer::primitives;
	using namespace raytracer::materials;

	auto material = raytracer::materials::uniform(colors::red());
	auto left = translate(Vector3D(-2, 0, 0), decorate(uniform(colors::red()), sphere()));
	auto middle = decorate(uniform(colors::green()), sphere());
	auto right = translate(Vector3D(2, 0, 0), decorate(uniform(colors::blue()), sphere()));
	auto spheres = decorate(material, translate(Vector3D(0, 0, 5), rotate_around_y(360_degrees, group(std::vector<Primitive> { left, middle, right }))));

	auto plane = decorate(raytracer::materials::grid(0.1, colors::white(), colors::black()), translate(Vector3D(0, -1, 0), xz_plane()));

	scene.root = group(std::vector<Primitive> { spheres, plane });
}

void create_lights(double t)
{
	scene.lights.clear();
	scene.lights.push_back(std::make_shared<Light>(Point3D(0, 2, 0)));
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

	WIF wif("e:/temp/output/test.wif");

	for (int frame = 0; frame != FRAME_COUNT; ++frame)
	{
		TIMED_SCOPE(timerObj, "single frame");

		double t = double(frame) / FRAME_COUNT;

		std::cout << "Rendering frame " << frame << std::endl;

		Bitmap bitmap(500, 500);

		// camera = raytracer::cameras::perspective(Point3D(0, t, 0), Point3D(0, 0, 5), Vector3D(0, 1, 0), 1, 1);
		// camera = raytracer::cameras::orthographic(Point3D(0, t, 0), Point3D(0, 0, 5), Vector3D(0, 1, 0), 10, 1);
		camera = raytracer::cameras::fisheye(Point3D(0, t, 0), Point3D(0, 0, 5), Vector3D(0, 1, 0));

		create_scene(t);

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
						int y = bitmap.height() - current - 1;

						for (int i = 0; i != bitmap.width(); ++i)
						{
							int x = i;

							color c = render_pixel(window_rasteriser, x, y);

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
				int y = bitmap.height() - j - 1;

				for (int i = 0; i != bitmap.width(); ++i)
				{
					int x = i;

					color c = render_pixel(window_rasteriser, x, y);

					bitmap[position(i, j)] = c;
				}
			}
		}

		wif.write_frame(bitmap);
	}
}

#endif
