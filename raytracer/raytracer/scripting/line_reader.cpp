#include "line_reader.h"
#include <assert.h>

using namespace scripting;

scripting::LineReader::LineReader(std::istream& in)
	: m_in(in), m_line_index(0), m_end_reached(false)
{
	next();
}

void scripting::LineReader::next()
{	
	assert(!end_reached());

	m_end_reached = std::getline(m_in, m_line).good();
	m_line_index++;
}

const std::string& scripting::LineReader::line() const
{
	assert(!end_reached());

	return m_line;
}

unsigned scripting::LineReader::index() const
{
	assert(!end_reached());

	return m_line_index;
}

bool scripting::LineReader::end_reached() const
{
	return m_end_reached;
}