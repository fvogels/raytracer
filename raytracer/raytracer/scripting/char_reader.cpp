#include "char_reader.h"
#include <assert.h>

using namespace scripting;

scripting::CharReader::CharReader(const std::string& in)
	: m_in(in), m_index(0)
{
	// NOP
}

void scripting::CharReader::next()
{
	assert(!end_reached());

	m_index++;
}

const char& scripting::CharReader::current() const
{
	assert(!end_reached());

	return m_in[m_index];
}

const unsigned& scripting::CharReader::location() const
{
	assert(!end_reached());

	return m_index;
}

bool scripting::CharReader::end_reached() const
{
	return m_index == m_in.size();
}