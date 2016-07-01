#include "math/quadratic_equation.h"
#include <math.h>
#include <assert.h>


math::QuadraticEquation::QuadraticEquation(double a, double b, double c)
{
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        m_has_solution = false;
    }
    else
    {
        m_has_solution = true;

        double sqrt_d = sqrt(discriminant);

        x1 = (-b - sqrt_d) / (2 * a);
        x2 = (-b + sqrt_d) / (2 * a);
    }
}

bool math::QuadraticEquation::has_solution() const
{
    return m_has_solution;
}

double math::QuadraticEquation::x1() const
{
    assert(has_solution());

    return m_x1;
}

double math::QuadraticEquation::x2() const
{
    assert(has_solution());

    return m_x2;

}
