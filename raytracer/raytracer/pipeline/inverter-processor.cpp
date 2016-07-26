#include "pipeline/inverter-processor.h"
#include <list>

using namespace raytracer;
using namespace raytracer::pipeline;
using namespace imaging;


namespace
{
    class InverterProcessor : public Processor<std::shared_ptr<Bitmap>, std::shared_ptr<Bitmap>>
    {
    public:
        void consume(std::shared_ptr<Bitmap> bitmap) override
        {
            auto copy = std::make_shared<Bitmap>(*bitmap);
            copy->invert();

            produce(copy);
        }

    private:
        std::shared_ptr<Bitmap> m_result;
    };
}

std::shared_ptr<Processor<std::shared_ptr<imaging::Bitmap>, std::shared_ptr<imaging::Bitmap>>> raytracer::pipeline::invert()
{
    return std::make_shared<InverterProcessor>();
}