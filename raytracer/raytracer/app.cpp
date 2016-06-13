#include "imaging/bitmap.h"
#include "imaging/wif_format.h"
#include "primitives/sphere.h"
#include "primitives/plane.h"
#include "primitives/transformer.h"
#include "primitives/decorator.h"
#include "cameras/perspective-camera.h"
#include "math/rectangle2d.h"
#include "math/rasterizer.h"
#include "rendering/grid-sampler.h"
#include "materials/uniform-material.h"
#include "materials/checkered-material.h"
#include "math/worley-noise2d.h"
#include "scripting/values.h"
#include "scripting/objects/function.h"
#include <assert.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <type_traits>
#include <list>

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

template<unsigned I, typename T>
struct Indexed
{
	static constexpr unsigned index = I;
	typedef T type;
};

template<typename T>
class NativeValue { };

template<typename T>
void print(const T& t)
{
	std::cout << t << std::endl;
}

template<unsigned... Ns>
struct Indices { };

template<unsigned I, unsigned... Ns>
struct BuildIndex : public BuildIndex<I - 1, I - 1, Ns...> { };

template<unsigned... Ns>
struct BuildIndex<0, Ns...> : public Indices<Ns...> { };

template<typename... Ts>
using CreateIndex = BuildIndex<sizeof...(Ts)>;

template<typename Tuple>
using CreateIndex2 = BuildIndex<std::tuple_size<Tuple>::value>;

class Foo
{
public:
	Foo(double, double, double) { }
};

std::shared_ptr<Foo> create_foo(double x, double y, double z)
{
	return std::make_shared<Foo>(x, y, z);
}

template<typename... Ts>
struct Indexate
{
	template<unsigned... Ns>
	struct with
	{
		typedef std::tuple<Indexed<Ns, Ts>...> pairs;
	};
};

template<typename... Ts, unsigned... Ns>
std::tuple<Indexed<Ns, Ts>...> Indexation(Indices<Ns...>)
{
	return std::tuple<Indexed<Ns, Ts>...>();
}




template<typename T>
class NativeObject : public scripting::Object
{
public:
	NativeObject(T value)
		: m_object(value) { }

	void write(std::ostream& out) const override { out << m_object; }

	bool operator ==(const scripting::Object& object) const override
	{
		return m_object == scripting::value_cast<NativeObject<T>>(object).m_object;
	}

	std::shared_ptr<scripting::Object> evaluate(std::shared_ptr<scripting::Environment>) override
	{
		return std::make_shared<NativeObject<T>>(this->m_object);
	}

	T extract() const { return m_object; }

protected:
	T m_object;
};

template<typename Pair>
typename Pair::type convert(const std::vector<std::shared_ptr<scripting::Object>>& objects)
{
	return scripting::value_cast<NativeObject<typename Pair::type>>(objects[Pair::index])->extract();
}

template<typename R, typename... Ps>
std::shared_ptr<R> create(const std::vector<std::shared_ptr<scripting::Object>>& objects, std::tuple<Ps...> pairs)
{
	return std::make_shared<R>(convert<Ps>(objects)...);
}

template<typename R, typename... Ts>
std::shared_ptr<R> create2(const std::vector<std::shared_ptr<scripting::Object>>& objects)
{
	CreateIndex<Ts...> indices;
	auto indexation = Indexation<Ts...>(indices);

	return create<R>(objects, indexation);
}



template<typename R, typename... Ts, typename... Ps>
std::shared_ptr<R> from_factory_aux(std::function<std::shared_ptr<R>(Ts...)> f, const std::vector<std::shared_ptr<scripting::Object>>& objects, std::tuple<Ps...> pairs)
{
	return f(convert<Ps>(objects)...);
}

template<typename R, typename... Ts>
std::shared_ptr<R> from_factory(std::function<std::shared_ptr<R>(Ts...)> f, const std::vector<std::shared_ptr<scripting::Object>>& objects)
{
	CreateIndex<Ts...> indices;
	auto indexation = Indexation<Ts...>(indices);

	return from_factory_aux<R, Ts...>(f, objects, indexation);
}

int main()
{
	auto x = std::make_shared<NativeObject<double>>(5);
	auto y = std::make_shared<NativeObject<double>>(5);
	auto z = std::make_shared<NativeObject<double>>(5);

	auto index = CreateIndex<double, double, double>();
	typedef Indexate<int, double>::with<0, 1>::pairs pairs;

	std::vector<std::shared_ptr<scripting::Object>> args { x,y,z };

	// std::tuple<Indexed<0, double>, Indexed<1, double>, Indexed<2, double>> tuple;

	// auto foo = create<Foo, Indexed<0, double>, Indexed<1, double>, Indexed<2, double>>(args, tuple);
	auto foo2 = create2<Foo, double, double, double>(args);
	// auto foo3 = from_factory<Foo, double, double, double>(create_foo, args);

	//const int FRAME_COUNT = 30;
	//WIF wif("e:/temp/output/test.wif");

	//Bitmap bitmap(500, 500);
	//auto noise = math::create_worley_noise2d();

	//for (int y = 0; y != bitmap.height(); ++y)
	//{
	//	for (int x = 0; x != bitmap.width(); ++x)
	//	{
	//		position pos(x, y);
	//		Point2D p(double(x) / bitmap.width() * 5, double(y) / bitmap.height() * 5);
	//		double value = (*noise)[p];

	//		value = value * 2;

	//		value = std::max<double>(value, 0);
	//		value = std::min<double>(value, 1);

	//		assert(0 <= value);
	//		assert(value <= 1);

	//		bitmap[pos] = colors::white() * value;
	//	}
	//}

	//wif.write_frame(bitmap);



	//for (int frame = 0; frame != FRAME_COUNT; ++frame)
	//{
	//	std::cout << "Rendering frame " << frame << std::endl;

	//	Bitmap bitmap(500, 500);
	//	camera = create_perspective_camera(Point3D(0, 0, 5), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);
	//	create_scene(double(frame) / FRAME_COUNT);

	//	Rectangle2D window(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
	//	Rasterizer window_rasteriser(window, bitmap.width(), bitmap.height());

	//	bitmap.clear(colors::black());

	//	for (int j = 0; j != bitmap.height(); ++j)
	//	{
	//		for (int i = 0; i != bitmap.width(); ++i)
	//		{
	//			color c = render_pixel(window_rasteriser, i, j);

	//			bitmap[position(i, j)] = c;
	//		}
	//	}

	//	wif.write_frame(bitmap);
	//}
}
#endif
