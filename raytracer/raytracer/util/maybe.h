#pragma once

#include <assert.h>

template<typename T>
class Maybe
{
public:
    Maybe() : m_has_value(false) { }
    Maybe(const T& value) : m_has_value(true), m_value(value) { }
    
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
    bool m_has_value;
    T m_value;
};