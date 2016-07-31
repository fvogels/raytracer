#pragma once

#include "math/angle.h"
#include "math/approx.h"
#include <array>


namespace math
{
    template<unsigned N>
    class Vector
    {
    public:
        template<typename... Ts>
        Vector(Ts... args)
            : Vector(std::array<double, sizeof...(Ts)> { {double(args)...}}) { }

        Vector(std::array<double, N>&& coords)
            : m_coords(coords) { }

        Vector()
            : m_coords()
        {
            for (unsigned i = 0; i != N; ++i)
            {
                m_coords[i] = 0;
            }
        }

        Vector(const Vector<N>&) = default;
        Vector(Vector<N>&&) = default;

        template<unsigned I>
        double& coord()
        {
            static_assert(I < N, "Invalid coordinate index");

            return m_coords[I];
        }

        template<unsigned I>
        double coord() const
        {
            static_assert(I < N, "Invalid coordinate index");

            return m_coords[I];
        }

        double& operator [](unsigned i)
        {
            return m_coords[i];
        }

        double operator [](unsigned i) const
        {
            return m_coords[i];
        }

        double& x()
        {
            static_assert(N >= 1, "X-coordinate requires at least one dimension");
            return m_coords[0];
        }

        double x() const
        {
            static_assert(N >= 1, "X-coordinate requires at least one dimension");
            return m_coords[0];
        }

        double& y()
        {
            static_assert(N >= 2, "Y-coordinate requires at least two dimensions");
            return m_coords[1];
        }

        double y() const
        {
            static_assert(N >= 2, "Y-coordinate requires at least two dimensions");
            return m_coords[1];
        }

        double& z()
        {
            static_assert(N >= 3, "Z-coordinate requires at least three dimensions");
            return m_coords[2];
        }

        double z() const
        {
            static_assert(N >= 3, "Z-coordinate requires at least three dimensions");
            return m_coords[2];
        }

        Vector<N> operator +(const Vector<N>& p) const
        {
            std::array<double, N> result;

            for (unsigned i = 0; i != N; ++i)
            {
                result[i] = m_coords[i] + p.m_coords[i];
            }

            return Vector<N>(std::move(result));
        }

        Vector<N> operator -() const
        {
            std::array<double, N> result;

            for (unsigned i = 0; i != N; ++i)
            {
                result[i] = -m_coords[i];
            }

            return Vector<N>(std::move(result));
        }

        Vector<N> operator -(const Vector<N>& p) const
        {
            return (*this) + -p;
        }

        Vector<N> operator *(double constant) const
        {
            std::array<double, N> result;

            for (unsigned i = 0; i != N; ++i)
            {
                result[i] = m_coords[i] * constant;
            }

            return Vector<N>(std::move(result));
        }

        Vector<N> operator /(double constant) const
        {
            return (*this) * (1.0 / constant);
        }

        Vector<N>& operator +=(const Vector<N>& p)
        {
            return *this = *this + p;
        }

        Vector<N>& operator -=(const Vector<N>& p)
        {
            return *this = *this - p;
        }

        Vector<N>& operator *=(double constant)
        {
            return *this = *this * constant;
        }

        Vector<N>& operator /=(double constant)
        {
            return *this = *this / constant;
        }

        double dot(const Vector<N>& p) const
        {
            double total = 0;

            for (unsigned i = 0; i != N; ++i)
            {
                total += m_coords[i] * p.m_coords[i];
            }

            return total;
        }

        double norm_sqr() const
        {
            return dot(*this);
        }

        double norm() const
        {
            return sqrt(norm_sqr());
        }

        Vector<N>& operator =(const Vector<N>& p)
        {
            m_coords = p.m_coords;

            return *this;
        }

        bool operator ==(const Vector<N>& p) const
        {
            return m_coords == p.m_coords;
        }

        bool operator !=(const Vector<N>& p) const
        {
            return !(*this == p);
        }

        void normalize()
        {
            *this /= norm();
        }

        Vector<N> normalized() const
        {
            return *this / norm();
        }

        bool is_unit() const
        {
            return norm_sqr() == approx(1.0);
        }

        Vector<3> cross(const Vector<3>& v) const
        {
            static_assert(N == 3, "Cross product is only defined on 3D vectors");

            const Vector3D& u = *this;

            double x = u.y() * v.z() - u.z() * v.y();
            double y = -(u.x() * v.z() - u.z() * v.x());
            double z = u.x() * v.y() - u.y() * v.x();

            return vector(x, y, z);
        }

        bool is_perpendicular_on(const Vector<N>& v) const
        {
            return dot(v) == approx(0.0);
        }

        Vector<N> reflect_by(const Vector<N>& n) const
        {
            auto& v = *this;

            return v - 2 * v.dot(n) * n;
        }

    private:        
        std::array<double, N> m_coords;
    };

    inline Vector<2> vector(double x, double y)
    {
        std::array<double, 2> coordinates = { x, y };

        return Vector<2>(std::move(coordinates));
    }

    inline Vector<3> vector(double x, double y, double z)
    {
        std::array<double, 3> coordinates = { x, y, z };

        return Vector<3>(std::move(coordinates));
    }

    inline Vector<4> vector(double x, double y, double z, double w)
    {
        std::array<double, 4> coordinates = { x, y, z, w };

        return Vector<4>(std::move(coordinates));
    }

    inline Vector<2> vector(double radius, Angle theta)
    {
        return vector(radius * cos(theta), radius * sin(theta));
    }

    inline Vector<3> vector(double r, math::Angle azimuth, math::Angle altitude)
    {
        return vector(r * cos(azimuth) * cos(altitude), r * sin(altitude), r * sin(azimuth) * cos(altitude));
    }

    template<unsigned N>
    Vector<N> operator *(double constant, const Vector<N>& p)
    {
        return p * constant;
    }

    namespace _private_
    {
        template<unsigned I, unsigned N>
        struct VectorOutputHelper
        {
            static void write(std::ostream& out, const Vector<N>& p)
            {
                out << ",";
                out << p.coord<I>();

                VectorOutputHelper<I + 1, N>::write(out, p);
            }
        };

        template<unsigned N>
        struct VectorOutputHelper<0, N>
        {
            static void write(std::ostream& out, const Vector<N>& p)
            {
                out << "(";
                out << p.coord<0>();

                VectorOutputHelper<1, N>::write(out, p);
            }
        };

        template<unsigned N>
        struct VectorOutputHelper<N, N>
        {
            static void write(std::ostream& out, const Vector<N>& p)
            {
                out << ")";
            }
        };
    }

    template<unsigned N>
    std::ostream& operator <<(std::ostream& out, const Vector<N>& p)
    {
        _private_::VectorOutputHelper<0, N>::write(out, p);

        return out;
    }

    using Vector2D = Vector<2>;
}