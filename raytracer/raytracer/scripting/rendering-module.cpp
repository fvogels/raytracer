#include "scripting/rendering-module.h"
#include "rendering/renderers.h"
#include "raytracing/ray-tracer.h"
#include "sampling/samplers.h"
#include "imaging/wif-format.h"

using namespace chaiscript;
using namespace raytracer;


namespace
{
    struct RendererLibrary
    {
        Renderer single_threaded(unsigned width, unsigned height, RayTracer ray_tracer) const
        {
            return raytracer::rendering::single_threaded(width, height, raytracer::samplers::single(), ray_tracer);
        }
    };

    std::shared_ptr<imaging::Bitmap> render(unsigned width, unsigned height, RayTracer ray_tracer, const Scene& scene)
    {
        auto renderer = raytracer::rendering::single_threaded(width, height, samplers::single(), ray_tracer);

        return renderer->render(scene);
    }

    void save_as_wif(imaging::Bitmap bitmap, std::string path)
    {
        imaging::WIF wif(path);
        wif.write_frame(bitmap);
    }
}

ModulePtr raytracer::scripting::_private_::create_rendering_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    auto renderer_library = std::make_shared<RendererLibrary>();
    module->add_global_const(chaiscript::const_var(renderer_library), "Renderers");

#define RENDERER(NAME) module->add(fun(&RendererLibrary::NAME), #NAME)
    RENDERER(single_threaded);
#undef COLOR

    module->add(fun(&render), "render");
    module->add(fun(&save_as_wif), "save_as_wif");

    return module;
}