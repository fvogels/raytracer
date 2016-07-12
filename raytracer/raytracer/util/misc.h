#pragma once

template<typename T>
void swap(T& x, T& y)
{
    T temp = x;
    x = y;
    y = temp;
}

template<typename T>
void sort(T& x, T& y)
{
    if (x > y)
    {
        swap(x, y);
    }
}

template<typename T>
bool smallest_greater_than_zero(T x, T y, T* result)
{
    sort(x, y);

    if (0 < x)
    {
        *result = x;

        return true;
    }
    else if (0 < y)
    {
        *result = y;

        return true;
    }
    else
    {
        return false;
    }
}
