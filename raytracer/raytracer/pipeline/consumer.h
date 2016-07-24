#pragma once


namespace raytracer
{
    namespace pipeline
    {
        template<typename INPUT>
        class Consumer
        {
        public:
            using input_type = INPUT;

            virtual void consume(INPUT) = 0;
        };
    }
}