#include "scripting/imaging-module.h"
#include "imaging/color.h"

using namespace chaiscript;
using namespace imaging;


namespace
{
    struct ColorLibrary
    {
#define COLOR(NAME) Color NAME() const { return colors::NAME(); }
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
    module->add_global_const(chaiscript::const_var(color_library), "Colors");

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

    module->add(fun([](const Color& c1, const Color& c2) {
        return c1 + c2;
    }), "+");

    module->add(fun([](const Color& c1, const Color& c2) {
        return c1 * c2;
    }), "*");

    module->add(fun([](const Color& c, double f) {
        return c * f;
    }), "*");

    module->add(fun([](double f, const Color& c) {
        return c * f;
    }), "*");

    module->add(fun([](const Color& c, double f) {
        return c / f;
    }), "/");

    return module;
}
