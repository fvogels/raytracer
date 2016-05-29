#pragma once

#include <istream>
#include <string>

namespace scripting
{
	class CharReader
	{
	public:
		CharReader(const std::string&);

		char current() const;
		unsigned index() const;
		bool end_reached() const;
		void next();

	private:
		const std::string& m_in;
		unsigned m_index;
	};
}