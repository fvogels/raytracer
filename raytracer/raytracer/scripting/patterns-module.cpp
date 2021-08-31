#ifndef EXCLUDE_SCRIPTING

#include "scripting/patterns-module.h"
#include "scripting/scripting-util.h"
#include "math/functions/patterns/patterns.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;


namespace
{
    struct PatternLibrary
    {
        math::functions::Pattern2D translate(const Vector2D& displacement, math::functions::Pattern2D pattern) const
        {
            return math::functions::patterns::translate(displacement, pattern);
        }

        math::functions::Pattern2D scale(double sx, double sy, math::functions::Pattern2D pattern) const
        {
            return math::functions::patterns::scale(sx, sy, pattern);
        }

        math::functions::Pattern2D rotate(Angle angle, math::functions::Pattern2D pattern) const
        {
            return math::functions::patterns::rotate(angle, pattern);
        }

        math::functions::Pattern2D conjunction(math::functions::Pattern2D pattern1, math::functions::Pattern2D pattern2) const
        {
            return math::functions::patterns::conjunction(pattern1, pattern2);
        }

        math::functions::Pattern2D disjunction(math::functions::Pattern2D pattern1, math::functions::Pattern2D pattern2) const
        {
            return math::functions::patterns::disjunction(pattern1, pattern2);
        }

        math::functions::Pattern2D negation(math::functions::Pattern2D pattern) const
        {
            return math::functions::patterns::negation(pattern);
        }

        math::functions::Pattern2D tessellate(math::functions::Pattern2D pattern, double width, double height) const
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

        math::functions::Pattern2D lines(double thickness, double separation, math::Angle angle) const
        {
            return math::functions::patterns::lines(thickness, separation, angle);
        }

        math::functions::Pattern2D grid(double xthickness, double ythickness, double xspacing, double yspacing, math::Angle angle) const
        {
            return math::functions::patterns::grid(xthickness, ythickness, xspacing, yspacing, angle);
        }

        math::functions::Pattern2D checkered(double xthickness, double ythickness, math::Angle angle) const
        {
            return math::functions::patterns::checkered(xthickness, ythickness);
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

#   define BIND(NAME)                      BIND_AS(NAME, NAME)
#   define BIND_AS(INTERNAL, EXTERNAL)     module->add(fun(&PatternLibrary::INTERNAL), #EXTERNAL)
    BIND(translate);
    BIND(scale);
    BIND(rotate);

    BIND(conjunction);
    BIND(disjunction);
    BIND(negation);

    BIND(tessellate);
    BIND(tessellate_x);
    BIND(tessellate_y);

    BIND(lines);
    BIND(grid);
    BIND(checkered);
#   undef BIND_AS
#   undef BIND

    return module;
}

#endif
