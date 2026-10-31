CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g

.PHONY: all test clean

all: graph-tests bpq-tests dijkstra

graph-tests: Graph.cpp GraphTests.cpp Graph.h
	$(CXX) $(CXXFLAGS) Graph.cpp GraphTests.cpp -o graph-tests

bpq-tests: Graph.cpp BetterPriorityQueue.cpp BPQTests.cpp Graph.h BetterPriorityQueue.h
	$(CXX) $(CXXFLAGS) Graph.cpp BetterPriorityQueue.cpp BPQTests.cpp -o bpq-tests

dijkstra: Graph.cpp BetterPriorityQueue.cpp Dijkstra.cpp DijkstraTests.cpp Graph.h BetterPriorityQueue.h Dijkstra.h
	$(CXX) $(CXXFLAGS) Graph.cpp BetterPriorityQueue.cpp Dijkstra.cpp DijkstraTests.cpp -o dijkstra

test: all
	./graph-tests
	./bpq-tests
	./dijkstra

clean:
	rm -f graph-tests bpq-tests dijkstra
	rm -rf graph-tests.dSYM bpq-tests.dSYM dijkstra.dSYM
