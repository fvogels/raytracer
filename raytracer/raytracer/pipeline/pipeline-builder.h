#pragma once

#include "pipeline/consumer.h"
#include "pipeline/producer.h"
#include "pipeline/processor.h"


namespace raytracer
{
    namespace pipeline
    {
        namespace _private_
        {
            template<typename T1, typename T2>
            struct PipelineBuilder
            {
                PipelineBuilder(std::shared_ptr<pipeline::Consumer<T1>> first, std::shared_ptr<pipeline::Producer<T2>> last)
                    : first(first), last(last) { }

                std::shared_ptr<pipeline::Consumer<T1>> first;
                std::shared_ptr<pipeline::Producer<T2>> last;
            };

            struct PipelineBuilderStart
            {
                template<typename T1, typename T2>
                PipelineBuilder<T1, T2> operator >> (std::shared_ptr<pipeline::Processor<T1, T2>> processor) const
                {
                    return PipelineBuilder<T1, T2>(processor, processor);
                }
            };

            template<typename T1, typename T2, typename C>
            std::shared_ptr<std::enable_if_t<!pipeline::is_producer<C>::value, pipeline::Consumer<T1>>> operator >> (const PipelineBuilder<T1, T2>& builder, std::shared_ptr<C> consumer)
            {
                builder.last->link_to(consumer);

                return builder.first;
            }

            template<typename T1, typename T2, typename P>
            PipelineBuilder<T1, std::enable_if_t<pipeline::is_processor<P>::value, typename P::output_type>> operator >> (const PipelineBuilder<T1, T2>& builder, std::shared_ptr<P> processor)
            {
                builder.last->link_to(processor);

                return PipelineBuilder<T1, typename P::output_type>(builder.first, processor);
            }
        }

        _private_::PipelineBuilderStart build()
        {
            return _private_::PipelineBuilderStart();
        }
    }
}
