#include "demo/demos.h"
#include "math/function.h"
#include "imaging/color.h"
#include "materials/materials.h"
#include "cameras/cameras.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;


namespace
{
    class MarbleAnimation
    {
    public:
        static Animation<std::shared_ptr<Scene>> create()
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

    private:
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

Animation<std::shared_ptr<Scene>> demos::marble_animation()
{
    return MarbleAnimation::create();
}