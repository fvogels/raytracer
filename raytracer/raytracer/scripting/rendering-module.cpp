#include "scripting/rendering-module.h"
#include "rendering/renderers.h"
#include "raytracing/ray-tracer.h"
#include "sampling/samplers.h"
#include "imaging/wif-format.h"
#include "util/looper.h"

using namespace chaiscript;
using namespace raytracer;


namespace
{
    struct RendererLibrary
    {
        Renderer standard(unsigned width, unsigned height, Sampler sampler, RayTracer ray_tracer) const
        {
            return raytracer::rendering::standard(width, height, sampler, ray_tracer, util::loopers::looper(4));
        }

        Renderer standard2(unsigned width, unsigned height, Sampler sampler, RayTracer ray_tracer, unsigned thread_count) const
        {
            return raytracer::rendering::standard(width, height, sampler, ray_tracer, util::loopers::looper(thread_count));
        }

        Renderer edge(unsigned width, unsigned height, Sampler sampler, RayTracer ray_tracer, double edge_thickness) const
        {
            return raytracer::rendering::edge(width, height, sampler, ray_tracer, util::loopers::looper(4), edge_thickness);
        }

        Renderer edge2(unsigned width, unsigned height, Sampler sampler, RayTracer ray_tracer, double edge_thickness, unsigned thread_count) const
        {
            return raytracer::rendering::edge(width, height, sampler, ray_tracer, util::loopers::looper(thread_count), edge_thickness);
        }

        Renderer cartoon(unsigned width, unsigned height, Sampler sampler, RayTracer ray_tracer, unsigned shade_count, double edge_thickness) const
        {
            return raytracer::rendering::cartoon(width, height, sampler, ray_tracer, util::loopers::looper(4), shade_count, edge_thickness);
        }

        Renderer cartoon2(unsigned width, unsigned height, Sampler sampler, RayTracer ray_tracer, unsigned shade_count, double edge_thickness, unsigned thread_count) const
        {
            return raytracer::rendering::cartoon(width, height, sampler, ray_tracer, util::loopers::looper(thread_count), shade_count, edge_thickness);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_rendering_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    auto renderer_library = std::make_shared<RendererLibrary>();
    module->add_global_const(chaiscript::const_var(renderer_library), "Renderers");

#define RENDERER(INTERNAL, EXTERNAL) module->add(fun(&RendererLibrary::INTERNAL), #EXTERNAL)
    RENDERER(standard, standard);
    RENDERER(standard2, standard);
    RENDERER(edge, edge);
    RENDERER(edge2, edge);
    RENDERER(cartoon, cartoon);
    RENDERER(cartoon2, cartoon);
#undef COLOR

    return module;
}