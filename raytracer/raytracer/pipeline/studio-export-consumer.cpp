#include "pipeline/studio-export-consumer.h"
#include "pipeline/wif-processor.h"
#include "pipeline/base64-processor.h"
#include "pipeline/text-writer-consumer.h"
#include <iostream>

using namespace raytracer::pipeline;


namespace
{
    class StudioExport : public Consumer<std::shared_ptr<imaging::Bitmap>>
    {
    public:
        StudioExport()
        {
            auto wif = raytracer::pipeline::wif();
            auto b64 = raytracer::pipeline::base64();
            auto out = raytracer::pipeline::text_writer(std::cout);

            wif->link_to(b64);
            b64->link_to(out);

            this->m_consumer = wif;
        }

        void consume(std::shared_ptr<imaging::Bitmap> bitmap) override
        {
            this->m_consumer->consume(bitmap);
        }

        void end() override
        {
            this->m_consumer->end();
        }

    private:
        std::shared_ptr<Consumer<std::shared_ptr<imaging::Bitmap>>> m_consumer;
    };
}

std::shared_ptr<Consumer<std::shared_ptr<imaging::Bitmap>>> raytracer::pipeline::studio_exporter()
{
    return std::make_shared<StudioExport>();
}