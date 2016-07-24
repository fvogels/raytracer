#include "pipeline/animation-processor.h"

using namespace animation;
using namespace raytracer;
using namespace raytracer::pipeline;


namespace
{
    class AnimationProducer : public Processor<animation::Animation<std::shared_ptr<Scene>>, std::shared_ptr<Scene>>
    {
    public:
        AnimationProducer(double fps)
            : m_fps(fps) { }

        void consume(animation::Animation<std::shared_ptr<Scene>> animation) override
        {
            Duration frame_duration = Duration::from_seconds(1.0 / m_fps);
            TimeStamp now = TimeStamp::zero();
            TimeStamp end = TimeStamp::from_epoch(animation.duration());

            while (now <= end)
            {
                std::shared_ptr<Scene> current_frame_scene = animation(now);
                produce(current_frame_scene);
                now += frame_duration;
            }
        }

    private:
        double m_fps;
    };
}

std::shared_ptr<Processor<animation::Animation<std::shared_ptr<Scene>>, std::shared_ptr<Scene>>> raytracer::pipeline::animation(double fps)
{
    return std::make_shared<AnimationProducer>(fps);
}