#include "chai/scripting.h"
#include "primitives/sphere.h"
#include "cameras/cameras.h"
#include "math/vector3d.h"
#include "math/point3d.h"
#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>

using namespace scripting;
using namespace chaiscript;
using namespace math;

namespace
{
    Point3D create_point(double x, double y, double z)
    {
        return Point3D(x, y, z);
    }

    Vector3D create_vector(double x, double y, double z)
    {
        return Vector3D(x, y, z);
    }

    ModulePtr create_math_module()
    {
        auto module = std::make_shared<chaiscript::Module>();

        module->add(fun(create_point), "pt");
        module->add(fun(create_vector), "vec");
    }

    ModulePtr create_primitives_module()
    {
        auto module = std::make_shared<chaiscript::Module>();

        module->add(fun(raytracer::primitives::sphere), "sphere");        
    }

    ModulePtr create_cameras_module()
    {
        auto module = std::make_shared<chaiscript::Module>();

        module->add(fun(raytracer::cameras::perspective), "perspective_camera");
    }
}

void run_script(const std::string& path)
{
    ChaiScript chai(Std_Lib::library());
    chai.add(create_primitives_module());
    chai.add(create_cameras_module());
    chai.eval_file(path);
}
