#include "chai/scripting.h"
#include "primitives/sphere.h"
#include "cameras/cameras.h"
#include "math/vector3d.h"
#include "math/point3d.h"
#include "imaging/color.h"
#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>

using namespace scripting;
using namespace chaiscript;
using namespace math;

namespace
{
    Point3D create_point3d(double x, double y, double z)
    {
        return Point3D(x, y, z);
    }

    Vector3D create_vector3d(double x, double y, double z)
    {
        return Vector3D(x, y, z);
    }

    struct ColorLibrary
    {
#define COLOR(NAME) imaging::color NAME() const { return imaging::colors::NAME(); }
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

    ModulePtr create_imaging_module()
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

        module->add(fun([](const imaging::color& c1, const imaging::color& c2) {
            return c1 + c2;
        }), "+");

        module->add(fun([](const imaging::color& c1, const imaging::color& c2) {
            return c1 * c2;
        }), "*");

        module->add(fun([](const imaging::color& c, double f) {
            return c * f;
        }), "*");

        module->add(fun([](double f, const imaging::color& c) {
            return c * f;
        }), "*");

        module->add(fun([](const imaging::color& c, double f) {
            return c / f;
        }), "/");

        return module;
    }

    ModulePtr create_math_module()
    {
        auto module = std::make_shared<chaiscript::Module>();

        module->add(fun(create_point3d), "pt");
        module->add(fun(create_vector3d), "vec");
        module->add(fun([](const Vector3D& u, const Vector3D& v) { return u + v; }), "+");
        module->add(fun([](const Point3D& u, const Vector3D& v) { return u + v; }), "+");
        module->add(fun([](const Vector3D& u, const Point3D& v) { return u + v; }), "+");

        return module;
    }

    ModulePtr create_primitives_module()
    {
        auto module = std::make_shared<chaiscript::Module>();

        module->add(fun(raytracer::primitives::sphere), "sphere");

        return module;
    }

    ModulePtr create_cameras_module()
    {
        auto module = std::make_shared<chaiscript::Module>();

        module->add(fun(raytracer::cameras::perspective), "perspective_camera");

        return module;
    }
}

namespace scripting
{
    ModulePtr create_modules()
    {
        auto module = std::make_shared<chaiscript::Module>();

        module->add(create_imaging_module());
        module->add(create_math_module());
        module->add(create_primitives_module());
        module->add(create_cameras_module());

        return module;
    }
}

void scripting::run_script(const std::string& path)
{
    ChaiScript chai(Std_Lib::library());
    chai.add(create_modules());
    chai.eval_file(path);
}

void scripting::run(const std::string& source)
{
    ChaiScript chai(Std_Lib::library());
    chai.add(create_modules());
    chai.eval(source);
}

