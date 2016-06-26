#pragma once

template<unsigned I, typename T>
struct Indexed
{
    static constexpr unsigned index = I;
    typedef T type;
};

template<unsigned... Ns>
struct Indices { };

template<unsigned I, unsigned... Ns>
struct BuildIndex : public BuildIndex<I - 1, I - 1, Ns...> { };

template<unsigned... Ns>
struct BuildIndex<0, Ns...> : public Indices<Ns...> { };

template<typename... Ts>
using CreateIndex = BuildIndex<sizeof...(Ts)>;

template<typename... Ts>
struct Indexate
{
    template<unsigned... Ns>
    struct with
    {
        typedef std::tuple<Indexed<Ns, Ts>...> pairs;
    };
};

template<typename... Ts, unsigned... Ns>
std::tuple<Indexed<Ns, Ts>...> Indexation(Indices<Ns...>)
{
    return std::tuple<Indexed<Ns, Ts>...>();
}