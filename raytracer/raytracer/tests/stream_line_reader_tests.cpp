#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/reader.h"
#include "scripting/stream_line_reader.h"
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

TEST_CASE("Empty stream", "[StreamLineReader]")
{
	std::stringstream ss("");
	StreamLineReader reader(ss);

	REQUIRE(reader.end_reached());
}

TEST_CASE("Single empty line", "[StreamLineReader]")
{
	std::stringstream ss("\n");
	StreamLineReader reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == "\n");
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("Single line stream, no newline at end", "[StreamLineReader]")
{
	std::stringstream ss("abc");
	StreamLineReader reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == "abc\n");
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("Single line stream, newline at end", "[StreamLineReader]")
{
	std::stringstream ss("abc\n");
	StreamLineReader reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == "abc\n");
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("Two lines, second not ending with newline", "[StreamLineReader]")
{
	std::stringstream ss("abc\nxyz");
	StreamLineReader reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == "abc\n");
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == "xyz\n");
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("Two lines, second ending with newline", "[StreamLineReader]")
{
	std::stringstream ss("abc\nxyz\n");
	StreamLineReader reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == "abc\n");
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == "xyz\n");
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("Three lines, second line empty", "[StreamLineReader]")
{
	std::stringstream ss("abc\n\nxyz");
	StreamLineReader reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == "abc\n");
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == "\n");
	reader.next();
	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == "xyz\n");
	reader.next();
	REQUIRE(reader.end_reached());
}

#endif