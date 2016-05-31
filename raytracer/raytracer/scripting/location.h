#pragma once

namespace scripting
{
	struct Location
	{
		unsigned line_index, char_index;

		Location() { }

		Location(unsigned line_index, unsigned char_index)
			: line_index(line_index), char_index(char_index) { }
	};
}