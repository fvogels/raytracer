#include "chai/math-module.h"
#include "math/point2d.h"
#include "math/point3d.h"
#include "math/vector2d.h"
#include "math/vector3d.h"

using namespace chaiscript;
using namespace raytracer;
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
}

ModulePtr raytracer::scripting::_private_::create_math_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    module->add(fun(create_point3d), "pos");
    module->add(fun(create_vector3d), "vec");
    module->add(fun([](const Vector3D& u, const Vector3D& v) { return u + v; }), "+");
    module->add(fun([](const Point3D& p, const Vector3D& v) { return p + v; }), "+");
    module->add(fun([](const Vector3D& u, const Point3D& p) { return u + p; }), "+");
    module->add(fun([](const Vector3D& u, const Vector3D& v) { return u - v; }), "-");
    module->add(fun([](const Point3D& p, const Vector3D& v) { return p - v; }), "-");
    module->add(fun([](const Point3D& p, const Point3D& q) { return p - q; }), "-");

    return module;
}