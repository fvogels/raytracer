#include "patterns/lines-pattern.h"
#include "patterns/lambda-pattern.h"
#include "patterns/pattern-tiling.h"
#include "patterns/split-pattern.h"


using namespace math;
using namespace patterns;


Pattern2D patterns::lines(double thickness, double separation)
{
    return tiling_y(ysplit(thickness), thickness + separation);
}
