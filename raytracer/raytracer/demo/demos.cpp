#include "demo/demos.h"
#include "math/function.h"
#include "imaging/color.h"
#include "materials/materials.h"
#include "cameras/cameras.h"
#include "easylogging++.h"
#include "imaging/wif_format.h"
#include "raytracing/ray-tracers.h"
#include "rendering/renderers.h"
#include "sampling/samplers.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;


namespace
{
    class MarbleAnimation
    {
    public:
        static void render(const std::string& output_path)
        {
            WIF wif(output_path);

            const unsigned fps = 30;
            auto scene_animation = create_scene_animation();
            auto ray_tracer = raytracer::raytracers::v6();
            auto renderer = raytracer::rendering::multithreaded(500, 500, raytracer::samplers::grid(2, 2), ray_tracer, 4);
            const unsigned frame_count = unsigned(round(fps * scene_animation.duration().seconds()));

            for (unsigned frame = 0; frame < frame_count; ++frame)
            {
                TIMED_SCOPE(timerObj, "single frame");

                double t = double(frame) / frame_count;
                TimeStamp now = TimeStamp::from_epoch(1_s * t);
                auto scene = scene_animation(now);

                std::cout << "Rendering frame " << frame << std::endl;

                auto bitmap = renderer->render(*scene);

                wif.write_frame(bitmap);
            }
        }

    private:
        static Animation<std::shared_ptr<Scene>> create_scene_animation()
        {
            std::function<std::shared_ptr<Scene>(TimeStamp)> lambda = [](TimeStamp now) {
                auto camera = create_camera(now);
                auto root = create_root(now);
                auto light_sources = create_light_sources(now);
                auto scene = std::make_shared<Scene>(camera, root, light_sources);

                return scene;
            };

            auto function = from_lambda(lambda);

            return make_animation<std::shared_ptr<Scene>>(function, Duration::from_seconds(1));
        }

        static raytracer::Primitive create_root(TimeStamp now)
        {
            using namespace raytracer::primitives;
            using namespace raytracer::materials;

            return decorate(to_animated_2d_material(marble3d(4, 2))(now), xz_plane());
        }

        static std::vector<raytracer::LightSource> create_light_sources(TimeStamp now)
        {
            using namespace raytracer::lights;

            std::vector<LightSource> light_sources;
            light_sources.push_back(omnidirectional(Point3D(0, 5, 5), colors::white()));

            return light_sources;
        }

        static raytracer::Camera create_camera(TimeStamp now)
        {
            auto camera = raytracer::cameras::perspective(Point3D(0, 5, 5), Point3D(0, 0, 0), Vector3D(0, 1, 0), 1, 1);

            return camera;
        }
    };
}

void demos::marble_animation(const std::string& output_path)
{
    MarbleAnimation::render(output_path);
}