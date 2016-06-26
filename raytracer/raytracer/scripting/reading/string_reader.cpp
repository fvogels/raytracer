#include "scripting/reading/string_reader.h"
#include <assert.h>

using namespace scripting;

scripting::StringReader::StringReader(const std::string& in)
    : m_in(in), m_index(0)
{
    // NOP
}

void scripting::StringReader::next()
{
    assert(!end_reached());

    m_index++;
}

char scripting::StringReader::current() const
{
    assert(!end_reached());

    return m_in[m_index];
}

unsigned scripting::StringReader::location() const
{
    assert(!end_reached());

    return m_index;
}

bool scripting::StringReader::end_reached() const
{
    return m_index == m_in.size();
}