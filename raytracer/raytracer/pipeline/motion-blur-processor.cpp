#include "pipeline/motion-blur-processor.h"
#include <list>

using namespace raytracer;
using namespace raytracer::pipeline;
using namespace imaging;


namespace
{
    class MotionBlurProcessor : public Processor<std::shared_ptr<Bitmap>, std::shared_ptr<Bitmap>>
    {
    public:
        MotionBlurProcessor(unsigned frame_count, unsigned frame_offset, unsigned last_extra_weight)
            : m_frame_count(frame_count), m_frame_offset(frame_offset), m_last_extra_weight(last_extra_weight) { }

        void consume(std::shared_ptr<Bitmap> bitmap) override
        {
            m_frames.push_back(bitmap);

            if (m_frames.size() == m_frame_count)
            {
                produce(compute_blur_of_current_frames());

                for (unsigned i = 0; i != m_frame_offset; ++i)
                {
                    m_frames.pop_front();
                }
            }
        }

    private:
        std::shared_ptr<Bitmap> compute_blur_of_current_frames()
        {
            auto result = std::make_shared<Bitmap>(m_frames.front()->width(), m_frames.front()->height());
            result->clear(colors::black());

            *result += *m_frames.back();
            *result *= m_last_extra_weight;

            for (auto frame : m_frames)
            {
                *result += *frame;
            }

            *result /= (m_frame_count + m_last_extra_weight);

            return result;
        }

        std::list<std::shared_ptr<Bitmap>> m_frames;
        unsigned m_frame_count;
        unsigned m_frame_offset;
        unsigned m_last_extra_weight;
    };
}

std::shared_ptr<Processor<std::shared_ptr<imaging::Bitmap>, std::shared_ptr<imaging::Bitmap>>> raytracer::pipeline::motion_blur(unsigned frame_count, unsigned frame_offset, unsigned last_extra_weight)
{
    return std::make_shared<MotionBlurProcessor>(frame_count, frame_offset, last_extra_weight);
}