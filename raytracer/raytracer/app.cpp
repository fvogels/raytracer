#ifndef TEST_BUILD

#include "imaging/bitmap.h"
#include "imaging/wif_format.h"
#include "primitives/primitives.h"
#include "cameras/cameras.h"
#include "math/rasterizer.h"
#include "math/functions/functions.h"
#include "math/functions/noise.h"
#include "sampling/grid-sampler.h"
#include "materials/materials.h"
#include "lights/lights.h"
#include "raytracing/ray-tracers.h"
#include "rendering/renderers.h"
#include "rendering/cartoon-renderer.h"
#include "animation/animation.h"
#include "demo/demos.h"
#include "logging.h"
#include "util/lazy.h"
#include "math/point.h"
#include "bitmap-consumers/bitmap-consumers.h"
// #include "scripting/scripting.h"
#include "easylogging++.h"
#include <assert.h>
#include <type_traits>
#include <list>
#undef IN

#ifdef NDEBUG
const int BITMAP_SIZE = 500;
const int SAMPLES = 2;
const int N_THREADS = 4;
#else
const int BITMAP_SIZE = 100;
const int SAMPLES = 1;
const int N_THREADS = 1;
#endif

using namespace math;
using namespace raytracer;
using namespace imaging;
using namespace animation;


Material create_lambert_material(const color& c, bool reflective = false)
{
    MaterialProperties properties(colors::black(), c, colors::black(), 0, 0, 0, 0);

    return raytracer::materials::uniform(properties);
}

Material create_phong_material(const color& ambient, const color& diffuse, const color& specular, double specular_exponent, double reflectivity)
{
    MaterialProperties properties(ambient, diffuse, specular, specular_exponent, reflectivity, 0, 0);

    return raytracer::materials::uniform(properties);
}

Material create_phong_material(const color& ambient, const color& diffuse, const color& specular, double specular_exponent, double reflectivity, double transparency, double refractive_index)
{
    MaterialProperties properties(ambient, diffuse, specular, specular_exponent, reflectivity, transparency, refractive_index);

    return raytracer::materials::uniform(properties);
}

Lazy<raytracer::Primitive> bunny([]() { return raytracer::primitives::fast_mesh_bin(std::ifstream("e:/temp/bunny.bmesh", std::ios::binary)); });
Lazy<raytracer::Primitive> buddha([]() { return raytracer::primitives::fast_mesh_bin(std::ifstream("e:/temp/buddha.bmesh", std::ios::binary)); });
Lazy<raytracer::Primitive> dragon([]() { return raytracer::primitives::fast_mesh_bin(std::ifstream("e:/temp/dragon.bmesh", std::ios::binary)); });
Lazy<raytracer::Primitive> statuette([]() { return raytracer::primitives::fast_mesh_bin(std::ifstream("e:/temp/statuette.bmesh", std::ios::binary)); });
Lazy<raytracer::Primitive> lucy([]() { return raytracer::primitives::fast_mesh_bin(std::ifstream("e:/temp/lucy.bmesh", std::ios::binary)); });

raytracer::Primitive create_root(TimeStamp now)
{
    using namespace raytracer::primitives;
    using namespace raytracer::materials;

    std::vector<Primitive> primitives;

    auto position_animation = animation::ease(animation::straight(Point3D(-2, 0, 0), Point3D(2, 0, 0), Duration::from_seconds(1)), math::functions::easing::easing_function<math::functions::easing::QUADRATIC, math::functions::easing::IN>());
    auto b = group(1, decorate(uniform(MaterialProperties(colors::white() * 0.1, colors::white() * 0.8, colors::white(), 20, 0.5, 0, 1.5)), translate(position_animation(now) - Point3D(0, 0, 0), sphere())));
    // auto plane = decorate(wood2d(4, 0.4), translate(Vector3D(0, -1, 0), xz_plane()));

    return make_union(std::vector<Primitive> { b });
}

std::vector<raytracer::LightSource> create_light_sources(TimeStamp now)
{
    using namespace raytracer::lights;

    std::vector<LightSource> light_sources;

    Point3D light_position = point(0, 5, 5);
    light_sources.push_back(omnidirectional(light_position, colors::white()));
    // light_sources.push_back(omnidirectional(point(0, 5, -5), colors::white()));
    // light_sources.push_back(spot(light_position, Point3D(0, 0, 0), 60_degrees, colors::white()));
    // light_sources.push_back(directional(Vector3D(1, 45_degrees, -45_degrees), colors::white()));
    // light_sources.push_back(area(Rectangle3D(Point3D(-0.5, 3, 5.5), Vector3D(1, 0, 0), Vector3D(0, 0, 1)), samplers::grid(3, 3), colors::white()));

    return light_sources;
}

raytracer::Camera create_camera(TimeStamp now)
{
    using namespace math::functions::easing;

    // auto camera_position_animation = circular(Point3D(0, 1, 5), Point3D(0, 0, 0), Vector3D::y_axis(), Interval<Angle>(0_degrees, 360_degrees), 1_s);

    // auto camera_position_animation = circular(point(0, 0, 5), point(0, 0, 0), vector(0, 1, 0), math::Interval<Angle>(0_degrees, 360_degrees), Duration::from_seconds(1));
    Point3D camera_position(0, 0, 5);
    auto camera = raytracer::cameras::perspective(camera_position, point(0, 0.5, 0), vector(0, 1, 0), 1, 1);
    // auto camera = raytracer::cameras::orthographic(Point3D(-5+10*t, 0, 0), Point3D(0, 0, 0), Vector3D(0, 1, 0), 10, 1);
    // auto camera = raytracer::cameras::fisheye(Point3D(0, 0, 0), Point3D(0, 0, 5), Vector3D(0, 1, 0), 180_degrees + 180_degrees * t, 180_degrees);
    // auto camera = raytracer::cameras::depth_of_field_perspective(camera_position, Point3D(0, 1, -5 * now.seconds()), Vector3D(0, 1, 0), 1, 1, 0.5, samplers::grid(4, 4));

    return camera;
}

Animation<std::shared_ptr<Scene>> create_scene_animation()
{
    std::function<std::shared_ptr<Scene>(TimeStamp)> lambda = [](TimeStamp now) -> std::shared_ptr<Scene> {
        auto camera = create_camera(now);
        auto root = create_root(now);
        auto light_sources = create_light_sources(now);
        auto scene = std::make_shared<Scene>(camera, root, light_sources);

        return scene;
    };

    return make_animation<std::shared_ptr<Scene>>(from_lambda<std::shared_ptr<Scene>, TimeStamp>(lambda), Duration::from_seconds(1));
}

void render_animation(Animation<std::shared_ptr<Scene>> scene_animation, unsigned fps, std::shared_ptr<imaging::BitmapConsumer> bitmap_consumer)
{
    auto ray_tracer = raytracer::raytracers::v6();

    auto renderer = N_THREADS > 1 ? raytracer::rendering::multithreaded(BITMAP_SIZE, BITMAP_SIZE, raytracer::samplers::grid(SAMPLES, SAMPLES), ray_tracer, N_THREADS) :
        raytracer::rendering::single_threaded(BITMAP_SIZE, BITMAP_SIZE, raytracer::samplers::grid(SAMPLES, SAMPLES), ray_tracer);
    // auto renderer = raytracer::rendering::cartoon(BITMAP_SIZE, BITMAP_SIZE, raytracer::samplers::grid(2, 2), ray_tracer, N_THREADS, 4, 0.005);

    for (int frame = 0; frame < scene_animation.duration().seconds() * fps; ++frame)
    {
        TIMED_SCOPE(timerObj, "single frame");

        double t = double(frame) / fps;
        TimeStamp now = TimeStamp::from_epoch(1_s * t);
        auto scene = scene_animation(now);

        LOG(INFO) << "Rendering frame " << frame << std::endl;

        auto bitmap = renderer->render(*scene);

        bitmap_consumer->consume(bitmap);
    }
}

void render_animation(Animation<std::shared_ptr<Scene>> scene_animation, unsigned fps)
{
    using namespace imaging::bitmap_consumers;

    std::string output_path = "e:/temp/output/test.wif";

    render_animation(scene_animation, fps, wif(output_path));
    // render_animation(scene_animation, fps, motion_blur(output_path));
}


template<typename INPUT>
class Consumer
{
public:
    using input_type = INPUT;

    virtual void consume(INPUT) = 0;
};

template<typename OUTPUT>
class Producer
{
public:
    using output_type = OUTPUT;

    template<typename T>
    T link_to(T receiver)
    {
        m_receiver = receiver;

        return receiver;
    }

protected:
    void produce(const OUTPUT& output)
    {
        if (m_receiver != nullptr)
        {
            m_receiver->consume(output);
        }
        else
        {
            throw std::runtime_error("Missing receiver");
        }
    }

private:
    std::shared_ptr<Consumer<OUTPUT>> m_receiver;
};

template<typename INPUT, typename OUTPUT>
class Processor : public Consumer<INPUT>, public Producer<OUTPUT>
{
    // EMPTY
};

class SceneProducer : public Processor<Animation<std::shared_ptr<Scene>>, std::shared_ptr<Scene>>
{
public:
    SceneProducer(double fps)
        : m_fps(fps) { }

    void consume(animation::Animation<std::shared_ptr<Scene>> animation) override
    {
        Duration frame_duration = Duration::from_seconds(1.0 / m_fps);
        TimeStamp now = TimeStamp::zero();
        TimeStamp end = TimeStamp::from_epoch(animation.duration());

        while (now <= end)
        {
            std::shared_ptr<Scene> current_frame_scene = animation(now);
            produce(current_frame_scene);
            now += frame_duration;
        }
    }

private:
    double m_fps;
};

class Wif : public Consumer<std::shared_ptr<imaging::Bitmap>>
{
public:
    Wif(const std::string& path)
        : m_wif(path) { }

    void consume(std::shared_ptr<imaging::Bitmap> bitmap) override
    {
        m_wif.write_frame(*bitmap);
    }

private:
    WIF m_wif;
};

class RendererProcessor : public Processor<std::shared_ptr<Scene>, std::shared_ptr<Bitmap>>
{
public:
    RendererProcessor(Renderer renderer)
        : m_renderer(renderer) { }

    void consume(std::shared_ptr<Scene> scene) override
    {
        TIMED_SCOPE(timer, "Rendering single frame");

        assert(scene);

        auto result = m_renderer->render(*scene);
        produce(std::make_shared<Bitmap>(result)); // TODO!!
    }

private:
    Renderer m_renderer;
};

class MotionBlurProcessor : public Processor<std::shared_ptr<Bitmap>, std::shared_ptr<Bitmap>>
{
public:
    MotionBlurProcessor(unsigned frame_count, unsigned frame_offset, unsigned last_extra_weight)
        : m_frame_count(frame_count), m_frame_offset(frame_offset), m_last_extra_weight(last_extra_weight) { }

    void consume(std::shared_ptr<Bitmap> bitmap) override
    {
        m_frames.push_back(bitmap);

        if (m_frames.size() == m_frame_count)
        {
            produce(compute_blur_of_current_frames());

            for (unsigned i = 0; i != m_frame_offset; ++i)
            {
                m_frames.pop_front();
            }
        }
    }

private:
    std::shared_ptr<Bitmap> compute_blur_of_current_frames()
    {
        auto result = std::make_shared<Bitmap>(m_frames.front()->width(), m_frames.front()->height());
        result->clear(colors::black());

        *result += *m_frames.back();
        *result *= m_last_extra_weight;

        for (auto frame : m_frames)
        {
            *result += *frame;
        }        

        *result /= (m_frame_count + m_last_extra_weight);

        return result;
    }

    std::list<std::shared_ptr<Bitmap>> m_frames;
    unsigned m_frame_count;
    unsigned m_frame_offset;
    unsigned m_last_extra_weight;
};



void render()
{
    // render_animation(create_scene_animation(), 1);
    const std::string path = "e:/temp/output/test.wif";

    auto scenes = std::make_shared<SceneProducer>(30);
    // auto renderer = std::make_shared<RendererProcessor>(rendering::multithreaded(500, 500, samplers::grid(2, 2), raytracers::v6(), 4));
    auto renderer = std::make_shared<RendererProcessor>(rendering::edge(BITMAP_SIZE, BITMAP_SIZE, samplers::grid(2, 2), raytracers::v6(), 4, 0.01));
    auto motion_blur = std::make_shared<MotionBlurProcessor>(30, 30, 10);
    auto wif = std::make_shared<Wif>(path);

    scenes->link_to(renderer)->link_to(motion_blur)->link_to(wif);
    scenes->consume(create_scene_animation());
}

int main()
{
    logging::configure();

    // TIMED_FUNC(timerObj);

    //using namespace imaging::bitmap_consumers;
    //demos::fisheye(wif("e:/temp/output/test.wif"));

    render();
    // scripting::run_script("e:/repos/ucll/3dcg/raytracer2/scripts/test.chai");
}

#endif
