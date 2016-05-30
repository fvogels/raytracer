#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/reader.h"
#include "scripting/string_reader.h"
#include "scripting/stream_line_reader.h"
#include "scripting/combined_reader.h"
#include <sstream>

using namespace scripting;

struct Loc
{
	Loc(unsigned line, unsigned ch)
		: line(line), ch(ch)
	{
		// NOP
	}

	unsigned line, ch;
};

TEST_CASE("[CombinedReader] Empty stream", "[CombinedReader]")
{
	std::istringstream ss("");
	CombinedReader<StreamLineReader, StringReader, Loc> reader(ss);

	REQUIRE(reader.end_reached());
}

TEST_CASE("[CombinedReader] Single line, without newline", "[CombinedReader]")
{
	std::istringstream ss("abc");
	CombinedReader<StreamLineReader, StringReader, Loc> reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == 'a');
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == 'b');
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == 'c');
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == '\n');
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[CombinedReader] Single line, with newline", "[CombinedReader]")
{
	std::istringstream ss("abc\n");
	CombinedReader<StreamLineReader, StringReader, Loc> reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == 'a');
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == 'b');
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == 'c');
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == '\n');
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[CombinedReader] Two lines", "[CombinedReader]")
{
	std::istringstream ss("a\nb");
	CombinedReader<StreamLineReader, StringReader, Loc> reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == 'a');
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == '\n');
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == 'b');
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == '\n');
	reader.next();
	REQUIRE(reader.end_reached());
}

#endif
