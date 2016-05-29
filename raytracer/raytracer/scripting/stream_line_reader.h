#pragma once

#include "scripting/reader.h"
#include <istream>
#include <string>

namespace scripting
{
	class StreamLineReader : public Reader<std::string, unsigned>
	{
	public:
		StreamLineReader(std::istream&);

		std::string current() const override;
		unsigned location() const override;
		bool end_reached() const override;
		void next() override;

		typedef std::istream source_t;

	private:
		std::istream& m_in;
		unsigned m_index;
		std::string m_line;
		bool m_end_reached;
	};
}