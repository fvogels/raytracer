#ifndef EXCLUDE_SCRIPTING

#include "scripting/rendering-module.h"
#include "scripting/scripting-util.h"
#include "renderers/renderers.h"
#include "raytracers/ray-tracer.h"
#include "samplers/samplers.h"
#include "imaging/wif-format.h"
#include "imaging/color.h"
#include "tasks/task-schedulers.h"

using namespace chaiscript;
using namespace raytracer;
using namespace imaging;


namespace
{
#   ifdef NDEBUG
    const int DEFAULT_THREAD_COUNT = 2;
#   else
    const int DEFAULT_THREAD_COUNT = 1;
#   endif

    struct RendererLibrary
    {
        Renderer standard(unsigned width, unsigned height, Sampler sampler, RayTracer ray_tracer) const
        {
            auto thread_count = DEFAULT_THREAD_COUNT;

            return raytracer::renderers::standard(width, height, sampler, ray_tracer, tasks::schedulers::load_balancing_parallel(thread_count));
        }

        Renderer standard2(unsigned width, unsigned height, Sampler sampler, RayTracer ray_tracer, unsigned thread_count) const
        {
            return raytracer::renderers::standard(width, height, sampler, ray_tracer, tasks::schedulers::load_balancing_parallel(thread_count));
        }

        Renderer standard_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(unsigned, width);
            ARGUMENT(unsigned, height);
            ARGUMENT(Sampler, sampler);
            ARGUMENT(RayTracer, ray_tracer);
            OPTIONAL_ARGUMENT(unsigned, thread_count, DEFAULT_THREAD_COUNT);
            END_ARGUMENTS();

            return standard2(width, height, sampler, ray_tracer, thread_count);
        }

        Renderer edge(unsigned width, unsigned height, Sampler sampler, RayTracer ray_tracer, double edge_thickness, const Color& stroke_color, const Color& background_color) const
        {
            return raytracer::renderers::edge(width, height, sampler, ray_tracer, tasks::schedulers::load_balancing_parallel(DEFAULT_THREAD_COUNT), edge_thickness, stroke_color, background_color);
        }

        Renderer edge_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(unsigned, width);
            ARGUMENT(unsigned, height);
            ARGUMENT(Sampler, sampler);
            ARGUMENT(RayTracer, ray_tracer);
            ARGUMENT(double, stroke_thickness);
            ARGUMENT(Color, stroke_color);
            ARGUMENT(Color, background_color);
            END_ARGUMENTS();

            return edge(width, height, sampler, ray_tracer, stroke_thickness, stroke_color, background_color);
        }

        Renderer cartoon(unsigned width, unsigned height, Sampler sampler, RayTracer ray_tracer, unsigned shade_count) const
        {
            return raytracer::renderers::cartoon(width, height, sampler, ray_tracer, tasks::schedulers::load_balancing_parallel(DEFAULT_THREAD_COUNT), shade_count);
        }

        Renderer cartoon_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(unsigned, width);
            ARGUMENT(unsigned, height);
            ARGUMENT(Sampler, sampler);
            ARGUMENT(RayTracer, ray_tracer);
            ARGUMENT(unsigned, shade_count);
            END_ARGUMENTS();

            return cartoon(width, height, sampler, ray_tracer, shade_count);
        }

        Renderer masking(Renderer image_renderer, Renderer mask_renderer) const
        {
            return raytracer::renderers::masking(image_renderer, mask_renderer);
        }

        Renderer split_depth(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, double split_thickness, const math::Point3D& eye, const math::Point3D& look_at, unsigned thread_count) const
        {
            return raytracer::renderers::split_depth(horizontal_resolution, vertical_resolution, sampler, ray_tracer, tasks::schedulers::load_balancing_parallel(thread_count), split_thickness, eye, look_at);
        }

        Renderer split_depth2(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, double split_thickness, const math::Point3D& eye, const math::Point3D& look_at) const
        {
            return this->split_depth(horizontal_resolution, vertical_resolution, sampler, ray_tracer, split_thickness, eye, look_at, DEFAULT_THREAD_COUNT);
        }

        Renderer split_depth_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(unsigned, width);
            ARGUMENT(unsigned, height);
            ARGUMENT(Sampler, sampler);
            ARGUMENT(RayTracer, ray_tracer);
            ARGUMENT(double, split_thickness);
            ARGUMENT(math::Point3D, eye);
            ARGUMENT(math::Point3D, look_at);
            OPTIONAL_ARGUMENT(unsigned, thread_count, DEFAULT_THREAD_COUNT);
            END_ARGUMENTS();

            return this->split_depth(width, height, sampler, ray_tracer, split_thickness, eye, look_at, thread_count);
        }

        Renderer distance(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, const math::Point3D& eye, double factor, double exponent) const
        {
            return raytracer::renderers::distance(horizontal_resolution, vertical_resolution, sampler, ray_tracer, tasks::schedulers::load_balancing_parallel(DEFAULT_THREAD_COUNT), eye, factor, exponent);
        }

        Renderer distance_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(unsigned, width);
            ARGUMENT(unsigned, height);
            ARGUMENT(Sampler, sampler);
            ARGUMENT(RayTracer, ray_tracer);
            ARGUMENT(math::Point3D, eye);
            ARGUMENT(double, factor);
            ARGUMENT(double, exponent);
            END_ARGUMENTS();

            return this->distance(width, height, sampler, ray_tracer, eye, factor, exponent);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_rendering_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<Renderer>(*module, "Renderer");

    auto renderer_library = std::make_shared<RendererLibrary>();
    module->add_global_const(chaiscript::const_var(renderer_library), "Renderers");

#   define BIND_AS(INTERNAL, EXTERNAL) module->add(fun(&RendererLibrary::INTERNAL), #EXTERNAL)
    BIND_AS(standard, standard);
    BIND_AS(standard2, standard);
    BIND_AS(standard_by_map, standard);
    BIND_AS(edge, edge);
    BIND_AS(edge_by_map, edge);
    BIND_AS(cartoon, cartoon);
    BIND_AS(cartoon_by_map, cartoon);
    BIND_AS(masking, masking);
    BIND_AS(split_depth, split_depth);
    BIND_AS(split_depth2, split_depth);
    BIND_AS(split_depth_by_map, split_depth);
    BIND_AS(distance, distance);
    BIND_AS(distance_by_map, distance);
#   undef BIND_AS

    return module;
}

#endif
