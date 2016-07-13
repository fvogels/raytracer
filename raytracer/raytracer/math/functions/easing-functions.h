#pragma once

#include "math/function.h"
#include "math/interval.h"


namespace math
{
    namespace functions
    {
        typedef math::Function<double, double> EasingFunction;

        namespace easing
        {
            template<typename T>
            struct is_shape_parameter;

#           define DEFINE_SHAPE(NAME) struct NAME { }; template<> struct is_shape_parameter<NAME> { typedef void t; }
            DEFINE_SHAPE(LINEAR);
            DEFINE_SHAPE(QUADRATIC);
#           undef DEFINE_SHAPE

            template<typename T>
            struct is_side_parameter;

#           define DEFINE_SIDE(NAME) struct NAME { }; template<> struct is_side_parameter<NAME> { typedef void t; }
            DEFINE_SIDE(IN);
            DEFINE_SIDE(OUT);
            DEFINE_SIDE(INOUT);
#           undef DEFINE_SIDE

            namespace _private_
            {
                math::functions::EasingFunction linear();
                math::functions::EasingFunction quadratic_in();
                math::functions::EasingFunction quadratic_out();
                math::functions::EasingFunction quadratic_inout();

                template<typename, typename, typename = void>
                struct EasingFunctionBuilder;

                template<>
                struct EasingFunctionBuilder<LINEAR, void>
                {
                    static math::functions::EasingFunction function()
                    {
                        return linear();
                    }
                };

                template<>
                struct EasingFunctionBuilder<QUADRATIC, IN>
                {
                    static math::functions::EasingFunction function()
                    {
                        return quadratic_in();
                    }
                };

                template<>
                struct EasingFunctionBuilder<QUADRATIC, OUT>
                {
                    static math::functions::EasingFunction function()
                    {
                        return quadratic_out();
                    }
                };

                template<>
                struct EasingFunctionBuilder<QUADRATIC, INOUT>
                {
                    static math::functions::EasingFunction function()
                    {
                        return quadratic_inout();
                    }
                };

                struct DeltaX
                {
                    double delta;
                };

                struct XInterval
                {
                    math::Interval<double> interval;
                };

                struct DeltaY
                {
                    double delta;
                };

                struct YInterval
                {
                    math::Interval<double> interval;
                };
            }

            constexpr _private_::DeltaX dx(double x)
            {
                return _private_::DeltaX{ x };
            }

            constexpr _private_::XInterval x_range(double from, double to)
            {
                return _private_::XInterval{ Interval<double>(from, to) };
            }

            constexpr _private_::DeltaY dy(double y)
            {
                return _private_::DeltaY{ y };
            }

            constexpr _private_::YInterval y_range(double from, double to)
            {
                return _private_::YInterval{ Interval<double>(from, to) };
            }

            template<typename SHAPE, typename SIDES = void>
            EasingFunction easing_function()
            {
                return _private_::EasingFunctionBuilder<SHAPE, SIDES>::function();
            }

            template<typename SHAPE, typename SIDES = void>
            EasingFunction easing_function(_private_::DeltaY dy)
            {
                return easing_function<SHAPE, SIDES>() * dy.delta;
            }

            template<typename SHAPE, typename SIDES = void>
            EasingFunction easing_function(_private_::YInterval y)
            {
                return easing_function<SHAPE, SIDES>(dy(y.interval.size())) + y.interval.lower;
            }

            template<typename SHAPE, typename SIDES = void>
            EasingFunction easing_function(_private_::DeltaX dx, _private_::YInterval y)
            {
                return (identity<double>() / dx.delta) >> easing_function<SHAPE, SIDES>(y);
            }

            template<typename SHAPE, typename SIDES = void>
            EasingFunction easing_function(_private_::XInterval x, _private_::YInterval y)
            {
                return (identity<double>() - x.interval.lower) >> easing_function<SHAPE, SIDES>(dx(x.interval.size()), y);
            }
        }
    }
}