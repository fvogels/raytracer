#pragma once

#include <assert.h>

template<typename T>
class Maybe
{
public:
    static Maybe<T> just(T value) { return Maybe<T>(value); }
    static Maybe<T> nothing()     { return Maybe<T>(); }

    T value() const 
    {
        assert(m_has_value);

        return m_value;
    }

    bool has_value() const
    {
        return m_has_value;
    }

private:
    Maybe() : m_has_value(false) { }
    Maybe(const T& value) : m_has_value(true), m_value(value) { }

    bool m_has_value;
    T m_value;
};