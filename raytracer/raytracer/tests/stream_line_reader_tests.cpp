#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/reading/reader.h"
#include "scripting/reading/stream_line_reader.h"
#include <sstream>

using namespace scripting;

TEST_CASE("[StreamLineReader] Empty stream", "[StreamLineReader]")
{
	std::stringstream ss("");
	StreamLineReader reader(ss);

	REQUIRE(reader.end_reached());
}

TEST_CASE("[StreamLineReader] Single empty line", "[StreamLineReader]")
{
	std::stringstream ss("\n");
	StreamLineReader reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == "\n");
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[StreamLineReader] Single line stream, no newline at end", "[StreamLineReader]")
{
	std::stringstream ss("abc");
	StreamLineReader reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == "abc\n");
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[StreamLineReader] Single line stream, newline at end", "[StreamLineReader]")
{
	std::stringstream ss("abc\n");
	StreamLineReader reader(ss);

	REQUIRE(!reader.end_reached());
	REQUIRE(reader.current() == "abc\n");
	reader.next();
	REQUIRE(reader.end_reached());
}

TEST_CASE("[StreamLineReader] Two lines, second not ending with newline", "[StreamLineReader]")
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

TEST_CASE("[StreamLineReader] Two lines, second ending with newline", "[StreamLineReader]")
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

TEST_CASE("[StreamLineReader] Three lines, second line empty", "[StreamLineReader]")
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
