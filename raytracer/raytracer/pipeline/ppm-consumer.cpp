#include "pipeline/ppm-consumer.h"
#include "imaging/ppm-format.h"
#include <iostream>

using namespace raytracer::pipeline;
using namespace imaging;


namespace
{
    class Ppm : public Consumer<std::shared_ptr<imaging::Bitmap>>
    {
    public:
        void consume(std::shared_ptr<imaging::Bitmap> bitmap) override
        {
            imaging::write_text_ppm(*bitmap, std::cout);
        }
    };
}

std::shared_ptr<Consumer<std::shared_ptr<imaging::Bitmap>>> raytracer::pipeline::ppm()
{
    return std::make_shared<Ppm>();
}