CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall -pipe  $(EXTRACXXFLAGS) -Ilibchess
LDFLAGS = -pthread -Wl, $(CXXFLAGS) $(EXTRALDFLAGS)

puzzler : puzzler.o
	g++ puzzler.o -o puzzler ${LDFLAGS}
	./puzzler

puzzle.o :
