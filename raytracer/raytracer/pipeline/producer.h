#pragma once

#include "pipeline/consumer.h"
#include <memory>


namespace raytracer
{
    namespace pipeline
    {
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

    }
}