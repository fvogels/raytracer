#include "pipeline/bmp-consumer.h"
#include "imaging/bmp-format.h"
#include <iostream>

using namespace raytracer::pipeline;
using namespace imaging;


namespace
{
    class Bmp : public Consumer<std::shared_ptr<imaging::Bitmap>>
    {
    public:
        Bmp(const std::string& path)
            : path(path) { }

        void consume(std::shared_ptr<imaging::Bitmap> bitmap) override
        {
            save_bitmap(path, *bitmap);
        }

    private:
        std::string path;
    };
}

std::shared_ptr<Consumer<std::shared_ptr<imaging::Bitmap>>> raytracer::pipeline::bmp(const std::string& path)
{
    return std::make_shared<Bmp>(path);
}