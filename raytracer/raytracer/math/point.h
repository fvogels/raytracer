#pragma once

#include "math/vector.h"
#include <array>
#include <iostream>


namespace math
{
    template<unsigned N>
    class Point
    {
    public:
        template<typename... Ts>
        Point(Ts... args)
            : Point( std::array<double, sizeof...(Ts)> {{double(args)...}})
        {
            static_assert(sizeof...(Ts) == N, "Invalid number of arguments");
        }

        Point(std::array<double, N>&& coords)
            : m_coords(coords) { }

        Point()
            : m_coords()
        {
            for (unsigned i = 0; i != N; ++i)
            {
                m_coords[i] = 0;
            }
        }

        Point(const Point<N>&) = default;
        Point(Point<N>&&) = default;

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

        Point<N> operator +(const Vector<N>& v) const
        {
            std::array<double, N> result;

            for (unsigned i = 0; i != N; ++i)
            {
                result[i] = m_coords[i] + v[i];
            }

            return Point<N>(std::move(result));
        }

        Point<N> operator -(const Vector<N>& v) const
        {
            std::array<double, N> result;

            for (unsigned i = 0; i != N; ++i)
            {
                result[i] = m_coords[i] - v[i];
            }

            return Point<N>(std::move(result));
        }

        Vector<N> operator -(const Point<N>& p) const
        {
            std::array<double, N> result;

            for (unsigned i = 0; i != N; ++i)
            {
                result[i] = m_coords[i] - p.m_coords[i];
            }

            return Vector<N>(std::move(result));
        }

        Point<N>& operator +=(const Vector<N>& p)
        {
            return *this = *this + p;
        }

        Point<N>& operator -=(const Vector<N>& p)
        {
            return *this = *this - p;
        }

        Point<N>& operator =(const Point<N>& p)
        {
            m_coords = p.m_coords;
            
            return *this;
        }

        bool operator ==(const Point<N>& p) const
        {
            return m_coords == p.m_coords;
        }

        bool operator !=(const Point<N>& p) const
        {
            return !(*this == p);
        }

    private:
        std::array<double, N> m_coords;
    };

    template<unsigned N>
    Point<N> operator +(const Vector<N>& v, const Point<N> p)
    {
        return p + v;
    }

    namespace _private_
    {
        template<unsigned I, unsigned N>
        struct PointOutputHelper
        {
            static void write(std::ostream& out, const Point<N>& p)
            {
                out << ",";
                out << p.coord<I>();

                PointOutputHelper<I + 1, N>::write(out, p);
            }
        };

        template<unsigned N>
        struct PointOutputHelper<0, N>
        {
            static void write(std::ostream& out, const Point<N>& p)
            {
                out << "(";
                out << p.coord<0>();

                PointOutputHelper<1, N>::write(out, p);
            }
        };

        template<unsigned N>
        struct PointOutputHelper<N, N>
        {
            static void write(std::ostream& out, const Point<N>& p)
            {
                out << ")";
            }
        };
    }

    template<unsigned N>
    std::ostream& operator <<(std::ostream& out, const Point<N>& p)
    {
        _private_::PointOutputHelper<0, N>::write(out, p);

        return out;
    }

    template<unsigned N>
    double distance(const Point<N>& p, const Point<N>& q)
    {
        return (p - q).norm();
    }

    inline Point<2> point(double x, double y)
    {
        std::array<double, 2> coordinates = { x, y };

        return Point<2>(std::move(coordinates));
    }

    inline Point<3> point(double x, double y, double z)
    {
        std::array<double, 3> coordinates = { x, y, z };

        return Point<3>(std::move(coordinates));
    }

    inline Point<3> point(double r, math::Angle azimuth, math::Angle altitude)
    {
        return point(r * cos(azimuth) * cos(altitude), r * sin(altitude), r * sin(azimuth) * cos(altitude));
    }
}