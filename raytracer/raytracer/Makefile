CC=g++
COMMONFLAGS=-I. -std=c++14 -pthread -DELPP_CUSTOM_OUT=std::cerr -DELPP_THREAD_SAFE
DEBUG_FLAGS=$(COMMONFLAGS) -g -ort-debug -O0 -Wall -Wextra
RELEASE_FLAGS=$(COMMONFLAGS) -DNDEBUG -O3 -s -ort-release
TEST_FLAGS=$(DEBUG_FLAGS) -DTEST_BUILD -ort-test

FILES=`find -type f -name "*.cpp"`

all: debug_build release_build test_build

debug_build:
	$(CC) $(DEBUG_FLAGS) $(FILES) -ldl

release_build:
	$(CC) $(RELEASE_FLAGS) $(FILES) -ldl

test_build:
	$(CC) $(TEST_FLAGS) $(FILES) -ldl

