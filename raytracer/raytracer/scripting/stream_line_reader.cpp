#include "stream_line_reader.h"
#include <assert.h>

using namespace scripting;

scripting::StreamLineReader::StreamLineReader(std::istream& in)
	: m_in(in), m_line_index(0)
{
	m_end_reached = std::getline(m_in, m_line).good();
}

void scripting::StreamLineReader::next()
{	
	assert(!end_reached());

	m_end_reached = std::getline(m_in, m_line).good();
	m_line_index++;
}

std::string scripting::StreamLineReader::current() const
{
	assert(!end_reached());

	return m_line;
}

unsigned scripting::StreamLineReader::location() const
{
	assert(!end_reached());

	return m_line_index;
}

bool scripting::StreamLineReader::end_reached() const
{
	return m_end_reached;
}