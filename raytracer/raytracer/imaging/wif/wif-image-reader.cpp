#include "imaging/wif/rgb.h"
#include "io/file-binary-reader.h"
#include "imaging/wif/wif-image-reader.h"

using namespace imaging;
using namespace imaging::wif;
using namespace imaging::wif::_private_;


namespace
{
    class WifImageReader : public imaging::ImageReader
    {
    public:
        imaging::Bitmap read(io::BinaryReader& reader) const override
        {
            auto width = reader.read<uint32_t>();
            auto height = reader.read<uint32_t>();
            auto ncolors = size_t(width) * size_t(height);
            auto colors = std::make_unique<RGB[]>(ncolors);
            auto pcolors = colors.get();

            reader.read(colors.get(), ncolors);

            return Bitmap(width, height, [pcolors, width](const Position2D& position, Color* p) {
                auto index = position.y * width + position.x;
                convert(pcolors[index], p);
            });
        }
    };
}

std::unique_ptr<imaging::ImageReader> imaging::wif::create_image_reader()
{
    return std::make_unique<WifImageReader>();
}

imaging::Bitmap imaging::wif::load(const std::string& path)
{
    auto binary_reader = io::create_file_binary_reader(path);
    auto image_reader = imaging::wif::create_image_reader();
    auto image = image_reader->read(*binary_reader);

    return image;
}