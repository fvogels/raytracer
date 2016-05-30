#include "scripting/comment_removing_reader.h"
#include <assert.h>

using namespace scripting;

scripting::CommentRemovingReader::CommentRemovingReader(const std::string& in)
	: m_in(in), m_index(0)
{
	// NOP
}

void scripting::CommentRemovingReader::next()
{
	assert(!end_reached());

	m_index++;
}

char scripting::CommentRemovingReader::current() const
{
	assert(!end_reached());

	return m_in[m_index];
}

unsigned scripting::CommentRemovingReader::location() const
{
	assert(!end_reached());

	return m_index;
}

bool scripting::CommentRemovingReader::end_reached() const
{
	return m_index == m_in.size() || m_in[m_index] == ';';
}