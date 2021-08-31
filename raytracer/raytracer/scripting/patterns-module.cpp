#ifndef EXCLUDE_SCRIPTING

#include "scripting/patterns-module.h"
#include "scripting/scripting-util.h"
#include "patterns/patterns.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;


namespace
{
    struct PatternLibrary
    {
        /*
        * 2D
        */
        
        math::functions::Pattern2D translate2d(const Vector2D& displacement, math::functions::Pattern2D pattern) const
        {
            return math::functions::patterns::translate(displacement, pattern);
        }

        math::functions::Pattern2D scale2d(double sx, double sy, math::functions::Pattern2D pattern) const
        {
            return math::functions::patterns::scale(sx, sy, pattern);
        }

        math::functions::Pattern2D rotate(Angle angle, math::functions::Pattern2D pattern) const
        {
            return math::functions::patterns::rotate(angle, pattern);
        }

        math::functions::Pattern2D conjunction2d(math::functions::Pattern2D pattern1, math::functions::Pattern2D pattern2) const
        {
            return math::functions::patterns::conjunction(pattern1, pattern2);
        }

        math::functions::Pattern2D disjunction2d(math::functions::Pattern2D pattern1, math::functions::Pattern2D pattern2) const
        {
            return math::functions::patterns::disjunction(pattern1, pattern2);
        }

        math::functions::Pattern2D exclusive_disjunction2d(math::functions::Pattern2D pattern1, math::functions::Pattern2D pattern2) const
        {
            return math::functions::patterns::exclusive_disjunction(pattern1, pattern2);
        }

        math::functions::Pattern2D negation2d(math::functions::Pattern2D pattern) const
        {
            return math::functions::patterns::negation(pattern);
        }

        math::functions::Pattern2D tessellate2d(math::functions::Pattern2D pattern, double width, double height) const
        {
            return math::functions::patterns::tessellate(pattern, width, height);
        }

        math::functions::Pattern2D tessellate_x(math::functions::Pattern2D pattern, double width) const
        {
            return math::functions::patterns::tessellate_x(pattern, width);
        }

        math::functions::Pattern2D tessellate_y(math::functions::Pattern2D pattern, double height) const
        {
            return math::functions::patterns::tessellate_y(pattern, height);
        }

        math::functions::Pattern2D lines(double thickness, double separation) const
        {
            return math::functions::patterns::lines(thickness, separation);
        }

        math::functions::Pattern2D grid(double xthickness, double ythickness, double xspacing, double yspacing) const
        {
            return math::functions::patterns::grid(xthickness, ythickness, xspacing, yspacing);
        }

        math::functions::Pattern2D checkered(double xthickness, double ythickness) const
        {
            return math::functions::patterns::checkered(xthickness, ythickness);
        }

        math::functions::Pattern2D polka(double radius, double separation) const
        {
            return math::functions::patterns::polka(radius, separation);
        }

        /*
        * 3D
        */

        math::functions::Pattern3D translate3d(const Vector3D& displacement, math::functions::Pattern3D pattern) const
        {
            return math::functions::patterns::translate(displacement, pattern);
        }

        math::functions::Pattern3D scale3d(double sx, double sy, double sz, math::functions::Pattern3D pattern) const
        {
            return math::functions::patterns::scale(sx, sy, sz, pattern);
        }

        math::functions::Pattern3D rotate_x(Angle angle, math::functions::Pattern3D pattern) const
        {
            return math::functions::patterns::rotate_x(angle, pattern);
        }

        math::functions::Pattern3D rotate_y(Angle angle, math::functions::Pattern3D pattern) const
        {
            return math::functions::patterns::rotate_y(angle, pattern);
        }

        math::functions::Pattern3D rotate_z(Angle angle, math::functions::Pattern3D pattern) const
        {
            return math::functions::patterns::rotate_z(angle, pattern);
        }

        math::functions::Pattern3D conjunction3d(math::functions::Pattern3D pattern1, math::functions::Pattern3D pattern2) const
        {
            return math::functions::patterns::conjunction(pattern1, pattern2);
        }

        math::functions::Pattern3D disjunction3d(math::functions::Pattern3D pattern1, math::functions::Pattern3D pattern2) const
        {
            return math::functions::patterns::disjunction(pattern1, pattern2);
        }

        math::functions::Pattern3D exclusive_disjunction3d(math::functions::Pattern3D pattern1, math::functions::Pattern3D pattern2) const
        {
            return math::functions::patterns::exclusive_disjunction(pattern1, pattern2);
        }

        math::functions::Pattern3D negation3d(math::functions::Pattern3D pattern) const
        {
            return math::functions::patterns::negation(pattern);
        }

        math::functions::Pattern3D tessellate3d(math::functions::Pattern3D pattern, double x_size, double y_size, double z_size) const
        {
            return math::functions::patterns::tessellate(pattern, x_size, y_size, z_size);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_pattern_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<math::functions::Pattern2D>(*module, "Pattern2D");
    util::register_type<math::functions::Pattern3D>(*module, "Pattern3D");

    auto lights_library = std::make_shared<PatternLibrary>();
    module->add_global_const(chaiscript::const_var(lights_library), "Patterns");

#   define BIND_2D_3D(NAME)                BIND_AS(NAME ## 2d, NAME); BIND_AS(NAME ## 3d, NAME)
#   define BIND(NAME)                      BIND_AS(NAME, NAME)
#   define BIND_AS(INTERNAL, EXTERNAL)     module->add(fun(&PatternLibrary::INTERNAL), #EXTERNAL)
    BIND_2D_3D(translate);
    BIND_2D_3D(scale);
    BIND(rotate);
    BIND(rotate_x);
    BIND(rotate_y);
    BIND(rotate_z);

    BIND_2D_3D(conjunction);
    BIND_2D_3D(disjunction);
    BIND_2D_3D(exclusive_disjunction);
    BIND_2D_3D(negation);

    BIND_2D_3D(tessellate);
    BIND(tessellate_x);
    BIND(tessellate_y);

    BIND(lines);
    BIND(grid);
    BIND(checkered);
    BIND(polka);
#   undef BIND_AS
#   undef BIND

    return module;
}

#endif
