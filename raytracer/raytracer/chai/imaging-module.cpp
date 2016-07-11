#include "chai/imaging-module.h"
#include "imaging/color.h"

using namespace chaiscript;
using namespace imaging;


namespace
{
    struct ColorLibrary
    {
#define COLOR(NAME) color NAME() const { return colors::NAME(); }
        COLOR(black)
        COLOR(white)
        COLOR(red)
        COLOR(green)
        COLOR(blue)
        COLOR(yellow)
        COLOR(magenta)
        COLOR(cyan)
#undef COLOR
    };
}

ModulePtr raytracer::scripting::_private_::create_imaging_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    auto color_library = std::make_shared<ColorLibrary>();
    module->add_global_const(chaiscript::const_var(color_library), "colors");

#define COLOR(NAME) module->add(fun(&ColorLibrary::NAME), #NAME)
    COLOR(black);
    COLOR(white);
    COLOR(red);
    COLOR(green);
    COLOR(blue);
    COLOR(yellow);
    COLOR(magenta);
    COLOR(cyan);
#undef COLOR

    module->add(fun([](const color& c1, const color& c2) {
        return c1 + c2;
    }), "+");

    module->add(fun([](const color& c1, const color& c2) {
        return c1 * c2;
    }), "*");

    module->add(fun([](const color& c, double f) {
        return c * f;
    }), "*");

    module->add(fun([](double f, const color& c) {
        return c * f;
    }), "*");

    module->add(fun([](const color& c, double f) {
        return c / f;
    }), "/");

    return module;
}