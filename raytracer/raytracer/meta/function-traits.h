#pragma once

template<class F>
struct function_traits;

template<class R, class... Ts>
struct function_traits<R(Ts...)>
{
    using return_type = R;
    using parameter_types = std::tuple<Ts...>;

    static constexpr std::size_t arity = sizeof...(Ts);

    template <std::size_t N>
    struct parameter_type
    {
        static_assert(N < arity, "error: invalid parameter index.");
        using type = typename std::tuple_element<N, std::tuple<Ts...>>::type;
    };
};