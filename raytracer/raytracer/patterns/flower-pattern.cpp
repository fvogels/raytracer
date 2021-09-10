#include "patterns/flower-pattern.h"
#include "patterns/revolution-pattern.h"


using namespace patterns;
using namespace math;


Pattern2D patterns::flower(unsigned petals, bool thin)
{
    if (thin)
    {
        return revolution([=](Angle angle) {
            return sin(petals * angle);
        });
    }
    else
    {
        return revolution([=](Angle angle) {
            return fabs(sin(petals / 2.0 * angle));
        });
    }
}
