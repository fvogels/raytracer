#include "patterns/grid-pattern.h"
#include "patterns/lines-pattern.h"
#include "patterns/lambda-pattern.h"
#include "patterns/pattern-transformations.h"
#include "patterns/pattern-logic-operations.h"
#include <cmath>


using namespace math;
using namespace patterns;


Pattern2D patterns::grid(double xthickness, double ythickness, double xspacing, double yspacing)
{
    auto hline = lines(xthickness, xspacing);
    auto vline = rotate(90_degrees, lines(ythickness, yspacing));

    return disjunction(hline, vline);
}
