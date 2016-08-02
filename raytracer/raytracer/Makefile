CC=g++
COMMONFLAGS=-I. -std=c++14 -pthread
DEBUG_FLAGS=$(COMMONFLAGS) -g -ort-debug -O0 -Wall -Wextra
RELEASE_FLAGS=$(COMMONFLAGS) -DNDEBUG -O3 -s -ort-release
TEST_FLAGS=$(DEBUG_FLAGS) -DTEST_BUILD

FILES=`find -type f -name "*.cpp"`

all: debug_build release_build test_build

debug_build:
	g++ $(DEBUG_FLAGS) $(FILES) -ldl

release_build:
	g++ $(RELEASE_FLAGS) $(FILES) -ldl

test_build:
	g++ $(TEST_FLAGS) $(FILES) -ldl

