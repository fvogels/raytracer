#include "math/functions/patterns/grid-pattern.h"
#include "math/functions/patterns/lines-pattern.h"
#include "math/functions/patterns/lambda-pattern.h"
#include "math/functions/patterns/pattern-transformations.h"
#include "math/functions/patterns/pattern-logic-operations.h"
#include <cmath>


using namespace math::functions;
using namespace math::functions::patterns;


Pattern2D math::functions::patterns::grid(double xthickness, double ythickness, double xspacing, double yspacing)
{
    auto hline = lines(xthickness, xspacing);
    auto vline = rotate(90_degrees, lines(ythickness, yspacing));

    return disjunction(hline, vline);
}
