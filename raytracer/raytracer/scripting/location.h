#pragma once

namespace scripting
{
    struct Location
    {
        unsigned line_index, char_index;

        Location() { }

        Location(unsigned line_index, unsigned char_index)
            : line_index(line_index), char_index(char_index) { }
    };

    struct LocationFactory
    {
    public:
        typedef Location t;

        static t create(unsigned line_index, unsigned char_index)
        {
            return Location(line_index, char_index);
        }
    };
}