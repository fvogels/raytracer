#include "pipeline/overprint-processor.h"
#include <list>

using namespace raytracer;
using namespace raytracer::pipeline;
using namespace imaging;


namespace
{
    class OverprintProcessor : public Processor<std::shared_ptr<Bitmap>, std::shared_ptr<Bitmap>>
    {
    public:
        void consume(std::shared_ptr<Bitmap> bitmap) override
        {
            if (m_result == nullptr)
            {
                m_result = std::make_shared<Bitmap>(*bitmap);
            }
            else
            {
                m_result->for_each_position([this, bitmap](const Position2D& position) {
                    (*m_result)[position] += (*bitmap)[position];
                });
            }
        }

        void end() override
        {
            produce(m_result);
            Processor<std::shared_ptr<Bitmap>, std::shared_ptr<Bitmap>>::end();
        }

    private:
        std::shared_ptr<Bitmap> m_result;
    };
}

std::shared_ptr<Processor<std::shared_ptr<imaging::Bitmap>, std::shared_ptr<imaging::Bitmap>>> raytracer::pipeline::overprint()
{
    return std::make_shared<OverprintProcessor>();
}