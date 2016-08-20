#pragma once

#include "math/vector.h"
#include "math/point.h"
#include "math/angle.h"
#include "math/approx.h"
#include <iostream>
#include <memory>
#include <array>


namespace math
{
    class Matrix4D
    {
    public:
        Matrix4D(std::array<double, 16>& elements)
            : m_elements(std::make_unique<std::array<double, 16>>(elements)) { }

        Matrix4D(std::unique_ptr<std::array<double, 16>> elements)
            : m_elements(std::move(elements)) { }

        Matrix4D(const Matrix4D& m)
            : m_elements(std::make_unique<std::array<double, 16>>(*m.m_elements)) { }

        Matrix4D(Matrix4D&& m)
            : m_elements(std::move(m.m_elements)) { }

        Matrix4D& operator =(const Matrix4D& m)
        {
            *m_elements = *m.m_elements;
        }

        double& at(unsigned row, unsigned col)
        {
            return (*m_elements)[row * 4 + col];
        }

        double at(unsigned row, unsigned col) const
        {
            return (*m_elements)[row * 4 + col];
        }

    private:
        std::unique_ptr<std::array<double, 16>> m_elements;
    };

    Matrix4D operator *(const Matrix4D&, const Matrix4D&);
    Vector3D operator *(const Matrix4D&, const Vector3D&);
    Point3D operator *(const Matrix4D&, const Point3D&);
    Matrix4D transpose(const Matrix4D&);

    std::ostream& operator <<(std::ostream&, const Matrix4D&);

    namespace transformation_matrices
    {
        Matrix4D zero();
        Matrix4D identity();
        Matrix4D coordinate_system(const Point3D&, const Vector3D&, const Vector3D&, const Vector3D&);
        Matrix4D translation(const Vector3D&);
        Matrix4D scaling(double sx, double sy, double sz);
        Matrix4D rotation_around_x(const Angle&);
        Matrix4D rotation_around_y(const Angle&);
        Matrix4D rotation_around_z(const Angle&);
    }

    template<>
    struct approximately<Matrix4D>
    {
        Matrix4D value;
        double delta;

        explicit approximately(const Matrix4D& value, double delta = 0.00001)
            :value(value), delta(delta)
        {
            // NOP
        }

        bool close_enough(const Matrix4D& other) const
        {
            for (unsigned row = 0; row != 4; ++row)
            {
                for (unsigned col = 0; col != 4; ++col)
                {
                    if (value.at(row, col) != approx(other.at(row, col)))
                    {
                        return false;
                    }
                }
            }

            return true;
        }
    };
}