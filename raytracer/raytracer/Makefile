all: gpp

clang:
	clang++-3.8 -I. -std=c++14 -stdlib=libc++ -lpthread -Wno-potentially-evaluated-expression `find -type f -name "*.cpp"`

gpp:
	g++ -I. -std=c++14 -pthread `find -type f -name "*.cpp"`
