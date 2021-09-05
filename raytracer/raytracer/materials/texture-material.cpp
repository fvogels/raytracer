#include "materials/texture-material.h"
#include "imaging/bitmap-function.h"
#include "imaging/wif/wif-image-reader.h"

using namespace raytracer;
using namespace imaging;
using namespace math;


Material raytracer::materials::texture(Function<Color(const Point2D&)> color_function)
{
    std::function<MaterialProperties(const Point2D&)> converter = [color_function](const Point2D& p) -> MaterialProperties {
        MaterialProperties properties = create_material_properties_with()
            .diffuse(color_function(p));

        return properties;
    };

    return make_2d_material(from_lambda(converter));
}

Material raytracer::materials::texture(std::shared_ptr<imaging::Bitmap> bitmap)
{
    return raytracer::materials::texture(bitmap_function(bitmap));
}

Material raytracer::materials::texture(const std::string& path)
{
    auto image = imaging::wif::load(path);
    auto p = std::make_shared<imaging::Bitmap>(std::move(image));

    return raytracer::materials::texture(p);
}
