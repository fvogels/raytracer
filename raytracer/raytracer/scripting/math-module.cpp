#include "scripting/math-module.h"
#include "scripting/scripting-util.h"
#include "math/point.h"
#include "math/vector.h"

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

    Angle degrees(double x)
    {
        return Angle::degrees(x);
    }

    Interval<Angle> angle_interval(Angle lower, Angle upper)
    {
        return Interval<Angle>(lower, upper);
    }
}

ModulePtr raytracer::scripting::_private_::create_math_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<math::Angle>(*module, "Angle");
    util::register_type<math::Point3D>(*module, "Point3D");
    util::register_type<math::Vector3D>(*module, "Vector3D");

    module->add(fun(create_point3d), "pos");
    module->add(fun(create_vector3d), "vec");
    module->add(fun([](const Vector3D& u, const Vector3D& v) { return u + v; }), "+");
    module->add(fun([](const Point3D& p, const Vector3D& v) { return p + v; }), "+");
    module->add(fun([](const Vector3D& u, const Point3D& p) { return u + p; }), "+");
    module->add(fun([](const Vector3D& u, const Vector3D& v) { return u - v; }), "-");
    module->add(fun([](const Point3D& p, const Vector3D& v) { return p - v; }), "-");
    module->add(fun([](const Point3D& p, const Point3D& q) { return p - q; }), "-");
    module->add(fun(&degrees), "degrees");
    module->add(fun(&angle_interval), "interval");

    return module;
}