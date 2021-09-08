#include "patterns/flower-pattern.h"
#include "patterns/revolution-pattern.h"


using namespace patterns;
using namespace math;


Pattern2D patterns::flower(double size, unsigned petals, bool thin)
{
    if (thin)
    {
        return revolution([=](Angle angle) {
            return size * sin(petals * angle);
        });
    }
    else
    {
        return revolution([=](Angle angle) {
            return size * fabs(sin(petals / 2.0 * angle));
        });
    }
}
