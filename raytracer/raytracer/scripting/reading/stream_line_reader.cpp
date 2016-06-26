#include "stream_line_reader.h"
#include <assert.h>

using namespace scripting;

scripting::StreamLineReader::StreamLineReader(std::istream& in)
    : m_in(in), m_index(0)
{
    if (in)
    {
        m_end_reached = !std::getline(m_in, m_line);
        m_line += "\n";
    }
    else
    {
        m_end_reached = true;
    }
}

void scripting::StreamLineReader::next()
{    
    assert(!end_reached());

    m_end_reached = !std::getline(m_in, m_line);
    m_line += "\n";
    m_index++;
}

std::string scripting::StreamLineReader::current() const
{
    assert(!end_reached());

    return m_line;
}

unsigned scripting::StreamLineReader::location() const
{
    assert(!end_reached());

    return m_index;
}

bool scripting::StreamLineReader::end_reached() const
{
    return m_end_reached;
}