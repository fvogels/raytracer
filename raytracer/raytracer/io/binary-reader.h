#pragma once

#include <cstdint>
#include <cstddef>


namespace io
{
    class BinaryReader
    {
    public:
        virtual void read(unsigned byte_count, uint8_t* buffer) = 0;

        template<typename T>
        void read(T* p, size_t n = 1)
        {
            this->read(unsigned(sizeof(T) * n), reinterpret_cast<uint8_t*>(p));
        }

        template<typename T>
        T read()
        {
            T value;

            this->read<T>(&value);

            return value;
        }
    };
}
