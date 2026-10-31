
#include "Graph.h"
#include "BetterPriorityQueue.h"
#include "Dijkstra.h"

#include <iostream>
#include <cassert>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

template <typename Function>
void ExpectInvalidDijkstraArgument(Function action) {
    bool caught = false;
    try { action(); }
    catch (const invalid_argument&) { caught = true; }
    assert(caught);
}

void FullAssignmentGraphTest() {
    Graph g;
    for (nodekey_t key = 1; key <= 6; ++key) g.AddNode(key);
    const unsigned int edges[][3] = {
        {1, 2, 7}, {1, 3, 9}, {1, 6, 14},
        {2, 3, 10}, {2, 4, 15}, {3, 6, 2},
        {3, 4, 11}, {4, 5, 6}, {5, 6, 9}
    };
    for (const auto& edge : edges) {
        g.AddEdge(edge[0], edge[1], edge[2]);
        g.AddEdge(edge[1], edge[0], edge[2]);
    }
    assert(dijkstra(1, 5, &g) == 20);
    assert(dijkstra(5, 1, &g) == 20);
    assert(dijkstra(1, 4, &g) == 20);
    assert(dijkstra(1, 6, &g) == 11);
    cout << "Full assignment graph: shortest distance 1 -> 5 = "
         << dijkstra(1, 5, &g) << endl;
}

void DijkstraEdgeCases() {
    Graph g;
    ExpectInvalidDijkstraArgument([&]() { dijkstra(0, 0, nullptr); });
    ExpectInvalidDijkstraArgument([&]() { dijkstra(0, 0, &g); });
    g.AddNode(0);
    g.AddNode(1);
    g.AddNode(2);
    g.AddNode(ULLONG_MAX - 1);
    assert(dijkstra(0, 0, &g) == 0);
    assert(dijkstra(0, 1, &g) == INT_MAX);
    ExpectInvalidDijkstraArgument([&]() { dijkstra(99, 0, &g); });
    ExpectInvalidDijkstraArgument([&]() { dijkstra(0, 99, &g); });
    ExpectInvalidDijkstraArgument([&]() { dijkstra(99, 99, &g); });
    ExpectInvalidDijkstraArgument([&]() { dijkstra(INVALID_NODE_KEY, 0, &g); });

    g.AddEdge(0, 1, 10);
    g.AddEdge(0, 2, 1);
    g.AddEdge(2, 1, 0);
    g.AddEdge(1, 2, 0);
    g.AddEdge(1, 1, 0);
    g.AddEdge(1, ULLONG_MAX - 1, 2);
    const string before = g.EdgesToString();
    assert(dijkstra(0, 1, &g) == 1);
    assert(dijkstra(0, ULLONG_MAX - 1, &g) == 3);
    assert(dijkstra(1, 0, &g) == INT_MAX);
    assert(g.EdgesToString() == before);

    Graph limits;
    for (nodekey_t key = 0; key < 7; ++key) limits.AddNode(key);
    limits.AddEdge(0, 1, INT_MAX - 2);
    limits.AddEdge(1, 2, 1);
    limits.AddEdge(1, 3, 2);
    limits.AddEdge(1, 4, 3);
    limits.AddEdge(0, 5, UINT_MAX);
    limits.AddEdge(0, 6, 5);
    limits.AddEdge(6, 5, 1);
    assert(dijkstra(0, 1, &limits) == INT_MAX - 2);
    assert(dijkstra(0, 2, &limits) == INT_MAX - 1);
    assert(dijkstra(0, 3, &limits) == INT_MAX);
    assert(dijkstra(0, 4, &limits) == INT_MAX);
    assert(dijkstra(0, 5, &limits) == 6);
    Graph huge;
    huge.AddNode(0);
    huge.AddNode(1);
    huge.AddEdge(0, 1, UINT_MAX);
    assert(dijkstra(0, 1, &huge) == INT_MAX);
    cout << "Dijkstra edge cases PASSED!" << endl;
}

int DijkstraTest(){
	cout << "Testing Dijkstra Algorithm..." << endl;
	
	// Test 1: graph from assignment
	Graph *g = new Graph();
	
	g->AddNode(1);
	g->AddNode(2);
	g->AddNode(3);
	
	g->AddEdge(1, 2, 7);
	g->AddEdge(2, 1, 7);
	g->AddEdge(1, 3, 9);
	g->AddEdge(3, 1, 9);

	
	cout <<  "---Graph---" << endl;
	cout << "\tnodes: " << g->NodesToString() << endl;
	cout << "\tedges: " << g->EdgesToString() << endl;
	cout << "---Graph---" << endl << endl;

	nodekey_t start = 1;
	nodekey_t end = 3;

	cout << "start: " << to_string(start) << "  goal: " << to_string(end) << endl;
	
	int ans = dijkstra(start, end, g);
	cout << "Output from Dijkstra(" << to_string(start) << ", " << to_string(end) << ") => " << ans << endl;
	assert(ans == 9);

	delete g;
	
	cout << "DONE with basic testing of Dijkstra algorithm" << endl;
	
	return ans;
}



int main(){
	
	DijkstraTest(); // this one by itself tests the graph on the assignment
	FullAssignmentGraphTest();
	DijkstraEdgeCases();
	cout << endl;
	cout << "ALL TESTS PASSED!" << endl;

	return 0;
}
