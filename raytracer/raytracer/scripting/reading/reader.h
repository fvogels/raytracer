#pragma once
namespace scripting
{
    template<typename T, typename LOC>
    class Reader
    {
    public:
        virtual bool end_reached() const = 0;
        virtual T current() const = 0;
        virtual LOC location() const = 0;
        virtual void next() = 0;

        typedef T datum_t;
        typedef LOC location_t;
    };
}