#include "pipeline/base64-processor.h"
#include "util/base64.h"
#include <list>
#include <sstream>
#include <assert.h>

using namespace raytracer::pipeline;


namespace
{
    const std::string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    class Base64Processor : public Processor<std::shared_ptr<std::vector<uint8_t>>, std::string>
    {
    public:
        void consume(std::shared_ptr<std::vector<uint8_t>> buffer) override
        {
            LOG(INFO) << "Received " << buffer->size() << " bytes to convert to base64";

            for (auto datum : *buffer)
            {
                m_base64.feed(datum);

                if (m_base64.chars_ready() > 80)
                {
                    produce(m_base64.extract());
                }
            }
        }

        void end() override
        {
            m_base64.close();
            
            if (m_base64.chars_ready() > 0)
            {
                produce(m_base64.extract());
            }

            produce_end();
        }

    private:
        Base64 m_base64;
    };
}

std::shared_ptr<Processor<std::shared_ptr<std::vector<uint8_t>>, std::string>> raytracer::pipeline::base64()
{
    return std::make_shared<Base64Processor>();
}
