#pragma once

#include "math/function.h"
#include "math/functions.h"
#include "math/interval.h"


namespace math
{
    namespace functions
    {
        typedef math::Function<double(double)> EasingFunction;

        namespace easing
        {
            template<typename T>
            struct is_shape_parameter;

#           define DEFINE_SHAPE(NAME) struct NAME { }; template<> struct is_shape_parameter<NAME> { typedef void t; }
            DEFINE_SHAPE(linear);
            DEFINE_SHAPE(quadratic);
            DEFINE_SHAPE(cubic);
            DEFINE_SHAPE(quintic);
            DEFINE_SHAPE(bounce);
#           undef DEFINE_SHAPE

            template<typename T>
            struct is_side_parameter;

#           define DEFINE_SIDE(NAME) struct NAME { }; template<> struct is_side_parameter<NAME> { typedef void t; }
            DEFINE_SIDE(in);
            DEFINE_SIDE(out);
            DEFINE_SIDE(inout);
#           undef DEFINE_SIDE

            namespace _private_
            {
                math::functions::EasingFunction linear();
                math::functions::EasingFunction quadratic_in();
                math::functions::EasingFunction quadratic_out();
                math::functions::EasingFunction quadratic_inout();
                math::functions::EasingFunction cubic_in();
                math::functions::EasingFunction cubic_out();
                math::functions::EasingFunction cubic_inout();
                math::functions::EasingFunction quintic_in();
                math::functions::EasingFunction quintic_out();
                math::functions::EasingFunction quintic_inout();
                math::functions::EasingFunction bounce();

                template<typename, typename, typename = void>
                struct EasingFunctionBuilder;

                template<>
                struct EasingFunctionBuilder<math::functions::easing::linear, void>
                {
                    static math::functions::EasingFunction function()
                    {
                        return linear();
                    }
                };

                template<>
                struct EasingFunctionBuilder<math::functions::easing::quadratic, math::functions::easing::in>
                {
                    static math::functions::EasingFunction function()
                    {
                        return quadratic_in();
                    }
                };

                template<>
                struct EasingFunctionBuilder<math::functions::easing::quadratic, math::functions::easing::out>
                {
                    static math::functions::EasingFunction function()
                    {
                        return quadratic_out();
                    }
                };

                template<>
                struct EasingFunctionBuilder<math::functions::easing::quadratic, math::functions::easing::inout>
                {
                    static math::functions::EasingFunction function()
                    {
                        return quadratic_inout();
                    }
                };

                template<>
                struct EasingFunctionBuilder<math::functions::easing::cubic, math::functions::easing::in>
                {
                    static math::functions::EasingFunction function()
                    {
                        return cubic_in();
                    }
                };

                template<>
                struct EasingFunctionBuilder<math::functions::easing::cubic, math::functions::easing::out>
                {
                    static math::functions::EasingFunction function()
                    {
                        return cubic_out();
                    }
                };

                template<>
                struct EasingFunctionBuilder<math::functions::easing::cubic, math::functions::easing::inout>
                {
                    static math::functions::EasingFunction function()
                    {
                        return cubic_inout();
                    }
                };

                template<>
                struct EasingFunctionBuilder<math::functions::easing::quintic, math::functions::easing::in>
                {
                    static math::functions::EasingFunction function()
                    {
                        return quintic_in();
                    }
                };

                template<>
                struct EasingFunctionBuilder<math::functions::easing::quintic, math::functions::easing::out>
                {
                    static math::functions::EasingFunction function()
                    {
                        return quintic_out();
                    }
                };

                template<>
                struct EasingFunctionBuilder<math::functions::easing::quintic, math::functions::easing::inout>
                {
                    static math::functions::EasingFunction function()
                    {
                        return quintic_inout();
                    }
                };

                template<>
                struct EasingFunctionBuilder<math::functions::easing::bounce, void>
                {
                    static math::functions::EasingFunction function()
                    {
                        return bounce();
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