#pragma once

#include "scripting/reading/reader.h"
#include <istream>
#include <string>

namespace scripting
{
    class StringReader : public Reader<char, unsigned>
    {
    public:
        StringReader(const std::string&);

        char current() const override;
        unsigned location() const override;
        bool end_reached() const override;
        void next() override;

        typedef std::string source_t;

    private:
        std::string m_in;
        unsigned m_index;
    };
}