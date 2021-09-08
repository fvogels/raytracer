#include "patterns/lines-pattern.h"
#include "patterns/lambda-pattern.h"
#include "patterns/pattern-tessellation.h"
#include "patterns/split-pattern.h"


using namespace math;
using namespace patterns;


Pattern2D patterns::lines(double thickness, double separation)
{
    return tessellate_y(ysplit(thickness), thickness + separation);
}
