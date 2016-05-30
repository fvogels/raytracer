#pragma once

#include "scripting/reader.h"
#include <istream>
#include <string>

namespace scripting
{
	class CommentRemovingReader : public Reader<char, unsigned>
	{
	public:
		CommentRemovingReader(const std::string&);

		char current() const override;
		unsigned location() const override;
		bool end_reached() const override;
		void next() override;

		typedef std::string source_t;

	private:
		const std::string& m_in;
		unsigned m_index;
	};
}