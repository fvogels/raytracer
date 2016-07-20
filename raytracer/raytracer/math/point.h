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
        double& x()
        {
            static_assert(I < N, "Invalid coordinate index");

            return m_coords[I];
        }

        Point<N> operator +(const Vector<N>& p) const
        {
            std::array<double, N> result;

            for (unsigned i = 0; i != N; ++i)
            {
                result[i] = m_coords[i] + p.m_coords[i];
            }

            return Point<N>(std::move(result));
        }

        Point<N> operator -(const Vector<N>& p) const
        {
            std::array<double, N> result;

            for (unsigned i = 0; i != N; ++i)
            {
                result[i] = m_coords[i] - p.m_coords[i];
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
        Point(std::array<double, N>&& coords)
            : m_coords(coords) { }

        std::array<double, N> m_coords;

        template<typename... Ts>
        friend Point<sizeof...(Ts)> point(Ts...);
    };

    template<typename... Ts>
    Point<sizeof...(Ts)> point(Ts... coordinates)
    {
        constexpr unsigned n_dimensions = sizeof...(Ts);
        std::array<double, n_dimensions> coordinates = { double(coordinates)... };

        return Point<n_dimensions>(std::move(coordinates));
    }

    template<unsigned N>
    Point<N> operator +(const Vector<N>& v, const Point<N> p)
    {
        return p + v;
    }

    namespace _private_
    {
        template<unsigned I, unsigned N>
        struct VectorOutputHelper
        {
            static void write(std::ostream& out, const Point<N>& p)
            {
                out << ",";
                out << p.coord<I>();

                VectorOutputHelper<I + 1, N>::write();
            }
        };

        template<unsigned N>
        struct VectorOutputHelper<0, N>
        {
            static void write(std::ostream& out, const Point<N>& p)
            {
                out << "(";
                out << p.coord<0>();

                VectorOutputHelper<1, N>::write();
            }
        };

        template<unsigned N>
        struct VectorOutputHelper<N, N>
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
        _private_::OutputHelper<0, N>::write(out, p);

        return out;
    }
}