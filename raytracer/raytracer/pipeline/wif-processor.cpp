#include "pipeline/wif-processor.h"
#include "imaging/wif-format.h"

using namespace raytracer;
using namespace raytracer::pipeline;


namespace
{
    class WifProcessor : public Processor<std::shared_ptr<imaging::Bitmap>, std::shared_ptr<std::vector<uint8_t>>>
    {
    public:
        void consume(std::shared_ptr<imaging::Bitmap> frame) override
        {
            auto buffer = std::make_shared<std::vector<uint8_t>>();
            imaging::wif::convert_frame(*buffer, *frame);

            produce(buffer);
        }

        void end() override
        {
            auto buffer = std::make_shared<std::vector<uint8_t>>();
            imaging::wif::mark_eof(*buffer);

            produce(buffer);
            produce_end();
        }
    };
}

std::shared_ptr<Processor<std::shared_ptr<imaging::Bitmap>, std::shared_ptr<std::vector<uint8_t>>>> wif()
{
    return std::make_shared<WifProcessor>();
}
