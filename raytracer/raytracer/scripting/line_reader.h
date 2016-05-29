#pragma once

#include "scripting/reader.h"
#include <istream>
#include <string>

namespace scripting
{
	class LineReader : Reader<std::string, unsigned>
	{
	public:
		LineReader(std::istream&);

		const std::string& current() const override;
		const unsigned& location() const override;
		bool end_reached() const override;
		void next() override;

	private:
		std::istream& m_in;
		unsigned m_line_index;
		std::string m_line;
		bool m_end_reached;
	};
}