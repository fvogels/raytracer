#include "scripting/rendering-module.h"
#include "scripting/scripting-util.h"
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

        Renderer standard_by_map(const std::map<std::string, Boxed_Value> argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(unsigned, width);
            ARGUMENT(unsigned, height);
            ARGUMENT(Sampler, sampler);
            ARGUMENT(RayTracer, ray_tracer);
            OPTIONAL_ARGUMENT(unsigned, thread_count, 4);
            END_ARGUMENTS();

            return standard2(width, height, sampler, ray_tracer, thread_count);
        }

        Renderer edge(unsigned width, unsigned height, Sampler sampler, RayTracer ray_tracer, double edge_thickness) const
        {
            return raytracer::rendering::edge(width, height, sampler, ray_tracer, util::loopers::looper(4), edge_thickness);
        }

        Renderer edge2(unsigned width, unsigned height, Sampler sampler, RayTracer ray_tracer, double edge_thickness, unsigned thread_count) const
        {
            return raytracer::rendering::edge(width, height, sampler, ray_tracer, util::loopers::looper(thread_count), edge_thickness);
        }

        Renderer edge_by_map(const std::map<std::string, Boxed_Value> argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(unsigned, width);
            ARGUMENT(unsigned, height);
            ARGUMENT(Sampler, sampler);
            ARGUMENT(RayTracer, ray_tracer);
            ARGUMENT(double, edge_thickness);
            OPTIONAL_ARGUMENT(unsigned, thread_count, 4);
            END_ARGUMENTS();

            return edge2(width, height, sampler, ray_tracer, edge_thickness, thread_count);
        }

        Renderer cartoon(unsigned width, unsigned height, Sampler sampler, RayTracer ray_tracer, unsigned shade_count, double edge_thickness) const
        {
            return raytracer::rendering::cartoon(width, height, sampler, ray_tracer, util::loopers::looper(4), shade_count, edge_thickness);
        }

        Renderer cartoon2(unsigned width, unsigned height, Sampler sampler, RayTracer ray_tracer, unsigned shade_count, double edge_thickness, unsigned thread_count) const
        {
            return raytracer::rendering::cartoon(width, height, sampler, ray_tracer, util::loopers::looper(thread_count), shade_count, edge_thickness);
        }

        Renderer cartoon_by_map(const std::map<std::string, Boxed_Value> argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(unsigned, width);
            ARGUMENT(unsigned, height);
            ARGUMENT(Sampler, sampler);
            ARGUMENT(RayTracer, ray_tracer);
            ARGUMENT(unsigned, shade_count);
            ARGUMENT(double, edge_thickness);
            OPTIONAL_ARGUMENT(unsigned, thread_count, 4);
            END_ARGUMENTS();

            return cartoon2(width, height, sampler, ray_tracer, shade_count, edge_thickness, thread_count);
        }

        Renderer split_depth(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, double split_thickness, double split_depth, unsigned thread_count) const
        {
            return raytracer::rendering::split_depth(horizontal_resolution, vertical_resolution, sampler, ray_tracer, util::loopers::looper(thread_count), split_thickness, split_depth);
        }

        Renderer split_depth_by_map(const std::map<std::string, Boxed_Value> argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(unsigned, width);
            ARGUMENT(unsigned, height);
            ARGUMENT(Sampler, sampler);
            ARGUMENT(RayTracer, ray_tracer);
            ARGUMENT(double, split_thickness);
            ARGUMENT(double, split_depth);
            OPTIONAL_ARGUMENT(unsigned, thread_count, 4);
            END_ARGUMENTS();

            return this->split_depth(width, height, sampler, ray_tracer, split_thickness, split_depth, thread_count);
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
    RENDERER(standard_by_map, standard);
    RENDERER(edge, edge);
    RENDERER(edge2, edge);
    RENDERER(edge_by_map, edge);
    RENDERER(cartoon, cartoon);
    RENDERER(cartoon2, cartoon);
    RENDERER(cartoon_by_map, cartoon);
#undef RENDERER

    return module;
}