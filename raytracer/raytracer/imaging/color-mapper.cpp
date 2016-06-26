#include "imaging/color-mapper.h"

using namespace imaging;


math::Function<color, double> imaging::color_mapping::grayscale()
{
    std::function<color(double)> lambda = [](double x) -> color
    {
        return colors::white() * x;
    };

    return math::from_lambda(lambda);
}