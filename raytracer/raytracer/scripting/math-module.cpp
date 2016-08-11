#ifndef EXCLUDE_SCRIPTING

#include "scripting/math-module.h"
#include "scripting/scripting-util.h"
#include "math/point.h"
#include "math/vector.h"
#include "math/rectangle3d.h"
#include "math/functions.h"


using namespace chaiscript;
using namespace raytracer;
using namespace math;
using namespace math::functions;


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

    Rectangle3D create_rectangle3d(const Point3D& origin, const Vector3D& x_axis, const Vector3D& y_axis)
    {
        return Rectangle3D(origin, x_axis, y_axis);
    }

    Interval<Angle> angle_interval(Angle lower, Angle upper)
    {
        return Interval<Angle>(lower, upper);
    }

    struct Perlin1DLibrary
    {
        Noise1D scalar(unsigned octaves) const
        {
            return math::functions::perlin<double, double>(octaves, 45623);
        }
    };

    struct Perlin2DLibrary
    {
        Noise2D scalar(unsigned octaves) const
        {
            return math::functions::perlin<double, Point2D>(octaves, 78465);
        }
    };

    struct Perlin3DLibrary
    {
        Noise3D scalar(unsigned octaves) const
        {
            return math::functions::perlin<double, Point3D>(octaves, 12319);
        }

        Function<Vector3D(const Point3D&)> vector3d(unsigned octaves) const
        {
            return math::functions::perlin<Vector3D, Point3D>(octaves, 98101);
        }
    };

    struct PointFactories
    {
        Point2D cartesian2d(double x, double y) const { return Point2D::cartesian(x, y); }
        Point2D polar(double radius, Angle theta) const { return Point2D::polar(radius, theta); }
        Point3D cartesian3d(double x, double y, double z) const { return Point3D::cartesian(x, y, z); }
        Point3D spherical(double radius, Angle azimuth, Angle elevation) const { return Point3D::spherical(radius, azimuth, elevation); }
        Point3D cylindrical_x(double radius, Angle azimuth, double x) const { return Point3D::cylindrical_x(radius, azimuth, x); }
        Point3D cylindrical_y(double radius, Angle azimuth, double y) const { return Point3D::cylindrical_x(radius, azimuth, y); }
        Point3D cylindrical_z(double radius, Angle azimuth, double z) const { return Point3D::cylindrical_x(radius, azimuth, z); }
    };

    struct VectorFactories
    {
        Vector2D cartesian2d(double x, double y) const { return Vector2D::cartesian(x, y); }
        Vector2D polar(double radius, Angle theta) const { return Vector2D::polar(radius, theta); }
        Vector3D cartesian3d(double x, double y, double z) const { return Vector3D::cartesian(x, y, z); }
        Vector3D spherical(double radius, Angle azimuth, Angle elevation) const { return Vector3D::spherical(radius, azimuth, elevation); }
        Vector3D cylindrical_x(double radius, Angle azimuth, double x) const { return Vector3D::cylindrical_x(radius, azimuth, x); }
        Vector3D cylindrical_y(double radius, Angle azimuth, double y) const { return Vector3D::cylindrical_x(radius, azimuth, y); }
        Vector3D cylindrical_z(double radius, Angle azimuth, double z) const { return Vector3D::cylindrical_x(radius, azimuth, z); }
    };

    void add_points_and_vectors(Module& module)
    {
        raytracer::scripting::util::register_type<math::Point3D>(module, "Point3D");
        raytracer::scripting::util::register_type<math::Vector3D>(module, "Vector3D");

        raytracer::scripting::util::register_to_string<math::Point3D>(module);
        raytracer::scripting::util::register_to_string<math::Vector3D>(module);

        module.add(fun(create_point3d), "pos");
        module.add(fun(create_vector3d), "vec");
        module.add(fun([](const Vector3D& u, const Vector3D& v) { return u + v; }), "+");
        module.add(fun([](const Point3D& p, const Vector3D& v) { return p + v; }), "+");
        module.add(fun([](const Vector3D& u, const Point3D& p) { return u + p; }), "+");
        module.add(fun([](const Vector3D& u, const Vector3D& v) { return u - v; }), "-");
        module.add(fun([](const Point3D& p, const Vector3D& v) { return p - v; }), "-");
        module.add(fun([](const Point3D& p, const Point3D& q) { return p - q; }), "-");

        module.add(fun(&Vector3D::norm), "norm");
        module.add(fun(&Vector3D::normalize), "normalize");
        module.add(fun(&Vector3D::normalized), "normalized");

        auto point_factories = std::make_shared<PointFactories>();
        auto vector_factories = std::make_shared<VectorFactories>();

#define BIND(NAME)                  module.add(fun(&PointFactories::NAME), #NAME); module.add(fun(&VectorFactories::NAME), #NAME)
        BIND(cartesian2d);
        BIND(polar);
        BIND(cartesian3d);
        BIND(spherical);
        BIND(cylindrical_x);
        BIND(cylindrical_y);
        BIND(cylindrical_z);
#undef BIND
    }

    void add_angle(Module& module)
    {
        raytracer::scripting::util::register_type<math::Angle>(module, "Angle");
        raytracer::scripting::util::register_to_string<math::Angle>(module);

        module.add(fun([](double x) { return Angle::degrees(x); }), "degrees");
        module.add(fun([](double x) { return Angle::radians(x); }), "radians");
        module.add(fun([](const Angle& a, const Angle& b) { return a + b; }), "+");
        module.add(fun([](const Angle& a, double constant) { return a * constant; }), "*");
        module.add(fun([](double constant, const Angle& a) { return constant * a; }), "*");
        module.add(fun([](const Angle& a, const Angle& b) { return a - b; }), "-");
        module.add(fun([](const Angle& a) { return sin(a); }), "sin");
        module.add(fun([](const Angle& a) { return cos(a); }), "cos");
    }

    void add_perlin(Module& module)
    {
        auto perlin1d_library = std::make_shared<Perlin1DLibrary>();
        module.add_global_const(chaiscript::const_var(perlin1d_library), "Perlin1D");

        auto perlin2d_library = std::make_shared<Perlin2DLibrary>();
        module.add_global_const(chaiscript::const_var(perlin2d_library), "Perlin2D");

        auto perlin3d_library = std::make_shared<Perlin3DLibrary>();
        module.add_global_const(chaiscript::const_var(perlin3d_library), "Perlin3D");

#define BIND(N, NAME)                 BIND_AS(N, NAME, NAME)
#define BIND_AS(N, FACTORY, NAME)     module.add(fun(&Perlin ## N ## Library::FACTORY), #NAME)
        BIND(1D, scalar);
        BIND(2D, scalar);
        BIND(3D, scalar);
        BIND(3D, vector3d);
#undef BIND_AS
#undef BIND
    }

    void add_interval(Module& module)
    {
        raytracer::scripting::util::register_type<math::Interval<Angle>>(module, "Angle");
        raytracer::scripting::util::register_to_string<math::Interval<Angle>>(module);

        module.add(fun(&angle_interval), "interval");
    }

    void add_rectangle3d(Module& module)
    {
        module.add(fun(&create_rectangle3d), "rect3d");
    }
}

ModulePtr raytracer::scripting::_private_::create_math_module()
{
    auto module = std::make_shared<chaiscript::Module>();
    
    add_points_and_vectors(*module);
    add_rectangle3d(*module);
    add_angle(*module);
    add_perlin(*module);
    add_interval(*module);

    return module;
}

#endif
