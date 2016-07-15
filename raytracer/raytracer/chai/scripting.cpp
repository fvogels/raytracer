#include "chai/scripting.h"
#include "primitives/primitives.h"
#include "cameras/cameras.h"
#include "math/vector3d.h"
#include "math/point3d.h"
#include "chai/imaging-module.h"
#include "chai/primitives-module.h"
#include "chai/cameras-module.h"
#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>

using namespace raytracer::scripting;
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

    ModulePtr create_math_module()
    {
        auto module = std::make_shared<chaiscript::Module>();

        module->add(fun(create_point3d), "pos");
        module->add(fun(create_vector3d), "vec");
        module->add(fun([](const Vector3D& u, const Vector3D& v) { return u + v; }), "+");
        module->add(fun([](const Point3D& u, const Vector3D& v) { return u + v; }), "+");
        module->add(fun([](const Vector3D& u, const Point3D& v) { return u + v; }), "+");

        return module;
    }
}

namespace raytracer
{
    namespace scripting
    {
        ModulePtr create_modules()
        {
            using namespace raytracer::scripting::_private_;

            auto module = std::make_shared<chaiscript::Module>();

            module->add(create_imaging_module());
            module->add(create_math_module());
            module->add(create_primitives_module());
            module->add(create_cameras_module());

            return module;
        }
    }
}

void raytracer::scripting::run_script(const std::string& path)
{
    ChaiScript chai(Std_Lib::library());
    chai.add(create_modules());
    chai.eval_file(path);
}

void raytracer::scripting::run(const std::string& source)
{
    ChaiScript chai(Std_Lib::library());
    chai.add(create_modules());
    chai.eval(source);
}

