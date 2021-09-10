#ifndef EXCLUDE_SCRIPTING

#include "scripting/patterns-module.h"
#include "scripting/scripting-util.h"
#include "patterns/patterns.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;
using namespace patterns;


namespace
{
    struct PatternLibrary
    {
        /*
        * 2D
        */
        
        Pattern2D translate2d(const Vector2D& displacement, Pattern2D pattern) const
        {
            return patterns::translate(displacement, pattern);
        }

        Pattern2D scale2d(double sx, double sy, Pattern2D pattern) const
        {
            return patterns::scale(sx, sy, pattern);
        }

        Pattern2D rotate(Angle angle, Pattern2D pattern) const
        {
            return patterns::rotate(angle, pattern);
        }

        Pattern2D conjunction2d(Pattern2D pattern1, Pattern2D pattern2) const
        {
            return patterns::conjunction(pattern1, pattern2);
        }

        Pattern2D disjunction2d(Pattern2D pattern1, Pattern2D pattern2) const
        {
            return patterns::disjunction(pattern1, pattern2);
        }

        Pattern2D exclusive_disjunction2d(Pattern2D pattern1, Pattern2D pattern2) const
        {
            return patterns::exclusive_disjunction(pattern1, pattern2);
        }

        Pattern2D negation2d(Pattern2D pattern) const
        {
            return patterns::negation(pattern);
        }

        Pattern2D tiling2d(Pattern2D pattern, double width, double height) const
        {
            return patterns::tiling(pattern, width, height);
        }

        Pattern2D wrong_tiling(Pattern2D pattern, double width, double height) const
        {
            return patterns::wrong_tiling(pattern, width, height);
        }

        Pattern2D tiling_x(Pattern2D pattern, double width) const
        {
            return patterns::tiling_x(pattern, width);
        }

        Pattern2D tiling_y(Pattern2D pattern, double height) const
        {
            return patterns::tiling_y(pattern, height);
        }

        Pattern2D xsplit(double boundary) const
        {
            return patterns::xsplit(boundary);
        }

        Pattern2D ysplit(double boundary) const
        {
            return patterns::ysplit(boundary);
        }

        Pattern2D lines(double thickness, double separation) const
        {
            return patterns::lines(thickness, separation);
        }

        Pattern2D grid(double xthickness, double ythickness, double xspacing, double yspacing) const
        {
            return patterns::grid(xthickness, ythickness, xspacing, yspacing);
        }

        Pattern2D checkered2d(double xthickness, double ythickness) const
        {
            return patterns::checkered(xthickness, ythickness);
        }

        Pattern2D wrong_checkered(double xthickness, double ythickness) const
        {
            return patterns::wrong_checkered(xthickness, ythickness);
        }

        Pattern3D checkered3d(double xthickness, double ythickness, double zthickness) const
        {
            return patterns::checkered(xthickness, ythickness, zthickness);
        }

        Pattern2D polka2d(double radius, double separation) const
        {
            return patterns::polka2d(radius, separation);
        }

        Pattern2D dalmatian2d(unsigned density, unsigned seed) const
        {
            return patterns::dalmatian2d(density, seed);
        }

        Pattern2D flower(unsigned petals) const
        {
            return patterns::flower(petals, false);
        }

        Pattern2D thin_flower(unsigned petals) const
        {
            return patterns::flower(petals, true);
        }

        Pattern2D mirror(Pattern2D pattern) const
        {
            return patterns::mirror(pattern);
        }

        Pattern2D mirror_x(Pattern2D pattern) const
        {
            return patterns::mirror_x(pattern);
        }

        Pattern2D mirror_y(Pattern2D pattern) const
        {
            return patterns::mirror_y(pattern);
        }

        Pattern2D spiral(double thickness) const
        {
            return patterns::spiral(thickness, 1, 1);
        }

        Pattern2D spiraln(double thickness, unsigned n, double spacing) const
        {
            return patterns::spiral(thickness, n, spacing);
        }

        /*
        * 3D
        */

        Pattern3D translate3d(const Vector3D& displacement, Pattern3D pattern) const
        {
            return patterns::translate(displacement, pattern);
        }

        Pattern3D scale3d(double sx, double sy, double sz, Pattern3D pattern) const
        {
            return patterns::scale(sx, sy, sz, pattern);
        }

        Pattern3D rotate_x(Angle angle, Pattern3D pattern) const
        {
            return patterns::rotate_x(angle, pattern);
        }

        Pattern3D rotate_y(Angle angle, Pattern3D pattern) const
        {
            return patterns::rotate_y(angle, pattern);
        }

        Pattern3D rotate_z(Angle angle, Pattern3D pattern) const
        {
            return patterns::rotate_z(angle, pattern);
        }

        Pattern3D conjunction3d(Pattern3D pattern1, Pattern3D pattern2) const
        {
            return patterns::conjunction(pattern1, pattern2);
        }

        Pattern3D disjunction3d(Pattern3D pattern1, Pattern3D pattern2) const
        {
            return patterns::disjunction(pattern1, pattern2);
        }

        Pattern3D exclusive_disjunction3d(Pattern3D pattern1, Pattern3D pattern2) const
        {
            return patterns::exclusive_disjunction(pattern1, pattern2);
        }

        Pattern3D negation3d(Pattern3D pattern) const
        {
            return patterns::negation(pattern);
        }

        Pattern3D tiling3d(Pattern3D pattern, double x_size, double y_size, double z_size) const
        {
            return patterns::tiling(pattern, x_size, y_size, z_size);
        }

        Pattern3D polka3d(double radius, double separation) const
        {
            return patterns::polka3d(radius, separation);
        }

        Pattern3D dalmatian3d(unsigned density, unsigned seed) const
        {
            return patterns::dalmatian3d(density, seed);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_pattern_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<Pattern2D>(*module, "Pattern2D");
    util::register_type<Pattern3D>(*module, "Pattern3D");

    auto pattern_library = std::make_shared<PatternLibrary>();
    module->add_global_const(chaiscript::const_var(pattern_library), "Patterns");

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

    BIND_2D_3D(tiling);
    BIND(wrong_tiling);
    BIND(tiling_x);
    BIND(tiling_y);

    BIND(xsplit);
    BIND(ysplit);
    BIND(lines);
    BIND(grid);
    BIND(wrong_checkered);
    BIND_2D_3D(checkered);
    BIND(polka2d);
    BIND(polka3d);
    BIND_2D_3D(dalmatian);

    BIND(flower);
    BIND(thin_flower);

    BIND(mirror);
    BIND(mirror_x);
    BIND(mirror_y);

    BIND(spiral);
    BIND_AS(spiraln, spiral);
#   undef BIND_AS
#   undef BIND

    return module;
}

#endif
