#pragma once

#include "scripting/reader.h"
#include <istream>
#include <string>

namespace scripting
{
	class CharReader : Reader<char, unsigned>
	{
	public:
		CharReader(const std::string&);

		const char& current() const override;
		const unsigned& location() const override;
		bool end_reached() const override;
		void next() override;

	private:
		const std::string& m_in;
		unsigned m_index;
	};
}