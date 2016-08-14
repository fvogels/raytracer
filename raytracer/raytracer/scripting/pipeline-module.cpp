#ifndef EXCLUDE_SCRIPTING

#include "scripting/pipeline-module.h"
#include "pipeline/pipelines.h"
#include "scripting/scripting-util.h"
#include "imaging/bitmap.h"
#include "rendering/renderers.h"
#include "sampling/samplers.h"
#include "raytracing/ray-tracers.h"
#include "util/looper.h"
#include "animation/animation.h"
#include "easylogging++.h"
#include <typeinfo>
#include <algorithm>

using namespace chaiscript;
using namespace raytracer;
using namespace raytracer::pipeline;
using namespace math;
using namespace imaging;


namespace
{
    struct Wrapper
    {
        Wrapper(std::shared_ptr<Pipeline> wrapped)
            : wrapped(wrapped) { }

        virtual void link_to(Wrapper*) = 0;
        virtual void consume(Boxed_Value) = 0;

        std::shared_ptr<Pipeline> wrapped;
    };

    template<typename T>
    struct SpecializedWrapper;

    template<typename T>
    struct SpecializedWrapper<Consumer<T>> : public Wrapper
    {
        SpecializedWrapper(std::shared_ptr<Consumer<T>> wrapped)
            : Wrapper(wrapped) { }

        void link_to(Wrapper*) override
        {
            LOG(ERROR) << "Nonproducers are only allowed at the end of the pipeline";
            abort();
        }

        void consume(Boxed_Value boxed) override
        {
            auto unboxed = boxed_cast<T>(boxed);
            auto consumer = std::dynamic_pointer_cast<Consumer<T>>(this->wrapped);

            consumer->consume(unboxed);
        }
    };

    template<typename T>
    struct SpecializedWrapper<Producer<T>> : public Wrapper
    {
        SpecializedWrapper(std::shared_ptr<Producer<T>> wrapped)
            : Wrapper(wrapped) { }

        void link_to(Wrapper* wrapper) override
        {
            auto producer = std::dynamic_pointer_cast<Producer<T>>(this->wrapped);
            auto consumer = std::dynamic_pointer_cast<Consumer<T>>(wrapper->wrapped);

            if (producer == nullptr || consumer == nullptr)
            {
                LOG(ERROR) << "Pipeline should only contain producers and consumers";
                abort();
            }
            else
            {
                producer->link_to(consumer);
            }
        }

        void consume(Boxed_Value boxed) override
        {
            LOG(ERROR) << "Pipeline cannot start with nonconsumer";
            abort();
        }
    };

    template<typename T1, typename T2>
    struct SpecializedWrapper<Processor<T1, T2>> : public Wrapper
    {
        SpecializedWrapper(std::shared_ptr<Processor<T1, T2>> wrapped)
            : Wrapper(wrapped) { }

        void link_to(Wrapper* wrapper) override
        {
            auto producer = std::dynamic_pointer_cast<Producer<T2>>(this->wrapped);
            auto consumer = std::dynamic_pointer_cast<Consumer<T2>>(wrapper->wrapped);

            if (producer == nullptr || consumer == nullptr)
            {
                LOG(ERROR) << "Pipeline should only contain producers and consumers";
                abort();
            }
            else
            {
                producer->link_to(consumer);
            }
        }

        void consume(Boxed_Value boxed) override
        {
            auto unboxed = boxed_cast<T1>(boxed);
            auto consumer = std::dynamic_pointer_cast<Consumer<T1>>(this->wrapped);

            consumer->consume(unboxed);
        }
    };

    template<typename T>
    std::shared_ptr<Wrapper> wrap(std::shared_ptr<T> x)
    {
        return std::make_shared<SpecializedWrapper<T>>(x);
    }

    struct PipelineLibrary
    {
        std::shared_ptr<Wrapper> wif(const std::string& path) const
        {
            return wrap(raytracer::pipeline::wif(path));
        }

        std::shared_ptr<Wrapper> ppm() const
        {
            return wrap(raytracer::pipeline::ppm());
        }

        std::shared_ptr<Wrapper> bmp(const std::string& path) const
        {
            return wrap(raytracer::pipeline::bmp(path));
        }

        std::shared_ptr<Wrapper> renderer(Renderer renderer) const
        {
            return wrap(raytracer::pipeline::renderer(renderer));
        }

        std::shared_ptr<Wrapper> inverter() const
        {
            return wrap(raytracer::pipeline::invert());
        }

        std::shared_ptr<Wrapper> motion_blur(unsigned frame_count, unsigned frame_offset, unsigned last_extra_weight) const
        {
            return wrap(raytracer::pipeline::motion_blur(frame_count, frame_offset, last_extra_weight));
        }

        std::shared_ptr<Wrapper> motion_blur_zerolew(unsigned frame_count, unsigned frame_offset) const
        {
            return motion_blur(frame_count, frame_offset, 0);
        }

        std::shared_ptr<Wrapper> overprint() const
        {
            return wrap(raytracer::pipeline::overprint());
        }

        std::shared_ptr<Wrapper> animation(double fps) const
        {
            return wrap(pipeline::animation(fps));
        }

        std::shared_ptr<Wrapper> null_bitmap_consumer() const
        {
            return wrap(pipeline::null<std::shared_ptr<Bitmap>>());
        }
    };

    void pipeline_builder(Boxed_Value initial, const std::vector<Boxed_Value>& pipeline_segments)
    {
        if (pipeline_segments.size() == 0)
        {
            LOG(ERROR) << "Pipeline requires at least one segment";
            abort();
        }
        else
        {
            std::vector<Wrapper*> wrappers(pipeline_segments.size());

            std::transform(pipeline_segments.begin(), pipeline_segments.end(), wrappers.begin(), [](Boxed_Value value) {
                return boxed_cast<Wrapper*>(value);
            });

            for (auto it = wrappers.begin(); it + 1 != wrappers.end(); ++it)
            {
                auto current = *it;
                auto next = *(it + 1);

                current->link_to(next);
            }

            wrappers.front()->consume(initial);
        }
    }
}

ModulePtr raytracer::scripting::_private_::create_pipeline_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    auto pipeline_library = std::make_shared<PipelineLibrary>();
    module->add_global_const(chaiscript::const_var(pipeline_library), "Pipeline");

#define BIND(NAME)                      BIND_AS(NAME, NAME)
#define BIND_AS(INTERNAL, EXTERNAL)     module->add(fun(&PipelineLibrary::INTERNAL), #EXTERNAL)
    BIND(wif);
    BIND(ppm);
    BIND(bmp);
    BIND(animation);
    BIND(renderer);
    BIND(inverter);
    BIND(motion_blur);
    BIND_AS(motion_blur_zerolew, motion_blur);
    BIND(overprint);
    BIND(null_bitmap_consumer);
#undef BIND_AS
#undef BIND

    module->add(fun(&pipeline_builder), "pipeline");

    return module;
}

#endif
