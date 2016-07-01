#pragma once

namespace math
{
    class QuadraticEquation
    {
    public:
        QuadraticEquation(double a, double b, double c);

        bool has_solution() const;

        double x1() const;
        double x2() const;

    private:
        double m_x1, m_x2;
        bool m_has_solution;
    };
}