#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/reading/reader.h"
#include "scripting/location.h"
#include "scripting/reading/string_reader.h"
#include "scripting/reading/stream_line_reader.h"
#include "scripting/reading/combined_reader.h"
#include <sstream>

using namespace scripting;


TEST_CASE("[CombinedReader] Empty stream", "[CombinedReader]")
{
	std::istringstream ss("");
	CombinedReader<StreamLineReader, StringReader, LocationFactory> reader(ss);

	REQUIRE(reader.end_reached());
}

TEST_CASE("[CombinedReader] Single line, without newline", "[CombinedReader]")
{
	std::istringstream ss("abc");
	CombinedReader<StreamLineReader, StringReader, LocationFactory> reader(ss);

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
	CombinedReader<StreamLineReader, StringReader, LocationFactory> reader(ss);

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
	CombinedReader<StreamLineReader, StringReader, LocationFactory> reader(ss);

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
