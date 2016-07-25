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
                PipelineBuilder(T1& value, std::shared_ptr<pipeline::Consumer<T1>> first, std::shared_ptr<pipeline::Producer<T2>> last)
                    : value(value), first(first), last(last) { }

                T1& value;
                std::shared_ptr<pipeline::Consumer<T1>> first;
                std::shared_ptr<pipeline::Producer<T2>> last;
            };

            template<typename T>
            struct PipelineBuilderStart
            {
                PipelineBuilderStart(T& value)
                    : value(value) { }

                template<typename T2>
                PipelineBuilder<T, T2> operator >> (std::shared_ptr<pipeline::Processor<T, T2>> processor) const
                {
                    return PipelineBuilder<T, T2>(value, processor, processor);
                }

                T& value;
            };

            template<typename T1, typename T2, typename C>
            std::enable_if_t<!pipeline::is_processor<C>::value> operator >> (const PipelineBuilder<T1, T2>& builder, std::shared_ptr<C> consumer)
            {
                builder.last->link_to(consumer);

                builder.first->consume(builder.value);
            }

            template<typename T1, typename T2, typename P>
            PipelineBuilder<T1, std::enable_if_t<pipeline::is_processor<P>::value, typename P::output_type>> operator >> (const PipelineBuilder<T1, T2>& builder, std::shared_ptr<P> processor)
            {
                builder.last->link_to(processor);

                return PipelineBuilder<T1, typename P::output_type>(builder.value, builder.first, processor);
            }
        }

        template<typename T>
        _private_::PipelineBuilderStart<T> build(T&& value)
        {
            return _private_::PipelineBuilderStart<T>(value);
        }
    }
}
