

#include "Graph.h"
#include <iostream>
#include <cassert>

using namespace std;

template <typename Function>
void ExpectInvalidGraphArgument(Function action) {
    bool caught = false;
    try { action(); }
    catch (const invalid_argument&) { caught = true; }
    assert(caught);
}

void TestGraphEdgeCases() {
    Graph g;
    assert(g.NodesToString() == "[]");
    assert(g.EdgesToString() == "[]");
    ExpectInvalidGraphArgument([&]() { g.AddNode(INVALID_NODE_KEY); });
    ExpectInvalidGraphArgument([&]() { g.GetOutwardEdgesFrom(0); });
    ExpectInvalidGraphArgument([&]() { g.AddEdge(0, 1); });

    g.AddNode();
    g.AddNode(ULLONG_MAX - 1);
    g.AddNode(2);
    assert(g.IsPresent(0));
    assert(g.IsPresent(ULLONG_MAX - 1));
    assert(!g.IsPresent(INVALID_NODE_KEY));
    assert(g.Order() == 3);
    assert(g.Size() == 0);
    ExpectInvalidGraphArgument([&]() { g.AddNode(); });
    ExpectInvalidGraphArgument([&]() { g.AddEdge(0, 99); });
    ExpectInvalidGraphArgument([&]() { g.AddEdge(99, 0); });
    assert(g.Size() == 0);

    const GraphEdge* original = g.AddEdge(0, ULLONG_MAX - 1, UINT_MAX);
    g.AddEdge(ULLONG_MAX - 1, 0, 4);
    const GraphEdge* loop = g.AddEdge(0, 0, 0);
    assert(g.Size() == 3);
    assert(g.GetOutwardEdgesFrom(0) == set<const GraphEdge*>({original, loop}));
    assert(g.GetOutwardEdgesFrom(2).empty());
    ExpectInvalidGraphArgument([&]() { g.AddEdge(0, 0, 1); });

    // Copies own separate edges, so destroying or modifying one graph is safe.
    Graph copy(g);
    assert(copy.NodesToString() == g.NodesToString());
    assert(copy.EdgesToString() == g.EdgesToString());
    for (const GraphEdge* edge : copy.GetOutwardEdgesFrom(0)) {
        assert(edge != original && edge != loop);
    }
    copy.AddNode(3);
    copy.AddEdge(2, 3, 7);
    assert(!g.IsPresent(3));
    assert(g.Size() == 3);

    Graph assigned;
    assigned.AddNode(9);
    assigned.AddEdge(9, 9, 1);
    assigned = g;
    assert(assigned.EdgesToString() == g.EdgesToString());
    Graph& same = assigned;
    assigned = same;
    assert(assigned.Size() == 3);
    g = Graph();
    assert(assigned.Size() == 3);
    assert(assigned.GetOutwardEdgesFrom(0).size() == 2);

    // Heap allocation keeps pointers stable through vector reallocations.
    Graph growing;
    growing.AddNode(0);
    const GraphEdge* stable = growing.AddEdge(0, 0, 42);
    for (nodekey_t i = 1; i <= 200; ++i) {
        growing.AddNode(i);
        growing.AddEdge(0, i, static_cast<unsigned int>(i));
    }
    assert(stable->from == 0 && stable->to == 0 && stable->weight == 42);
    assert(growing.Size() == 201 && growing.Order() == 201);
    cout << "Graph edge cases and ownership tests PASSED!" << endl;
}


void TestAddNode(){
	cout << "Testing AddNode..." << endl;
	Graph g = Graph();


	g.AddNode(15);
	//cout << "nodes: " << g.NodesToString() << endl;
	assert(g.NodesToString() == "[(15)]");


	g.AddNode(12);
	//cout << "nodes: " << g.NodesToString() << endl;
	assert(g.NodesToString() == "[(15), (12)]");

	
	try
	{
		g.AddNode(12);
		assert(false);
	}
	catch( const invalid_argument& e ) { }

	
	cout << "PASSED!" << endl << endl;
}


void TestAddEdge(){
	cout << "Testing AddEdge..." << endl;
	Graph g = Graph();

	g.AddNode(15);
	g.AddNode(12);
	g.AddNode(9);
	// cout << "nodes: " << g.NodesToString() << endl;
	assert(g.NodesToString() == "[(15), (12), (9)]");

	
	const GraphEdge *ge1 = g.AddEdge(15, 9, 2);
	assert(g.NodesToString() == "[(15), (12), (9)]");
	//cout << "edges:" <<  g.EdgesToString() << endl;
	assert(g.EdgesToString() == "[((15)->(9) w:2)]");
	assert(ge1->from == 15);
	assert(ge1->to == 9);
	assert(ge1->weight == 2);
	
	const GraphEdge *ge2 = g.AddEdge(9, 12); // this makes the weight 0, since default value for weight is 0
	assert(g.NodesToString() == "[(15), (12), (9)]");
	//cout << "edges:" <<  g.EdgesToString() << endl;
	assert(g.EdgesToString() == "[((15)->(9) w:2), ((9)->(12) w:0)]");
	assert(ge2->from == 9);
	assert(ge2->to == 12);
	assert(ge2->weight == 0);
	
	try
	{
		const GraphEdge *ge3 = g.AddEdge(20, 12);
		cout << "ge3: (" + to_string(ge3->from) + "->" + to_string(ge3->to) + "  w: " + to_string(ge3->weight) + ")" << endl;
		assert(false);
	} catch (const invalid_argument& e) {}


	try
	{
		const GraphEdge *ge3 = g.AddEdge(15, 9, 7);
		// edge already exists!
		cout << "ge3: (" + to_string(ge3->from) + "->" + to_string(ge3->to) + "  w: " + to_string(ge3->weight) + ")" << endl;
		assert(false);
	} catch (const invalid_argument& e) {}


	// more tests go here!
	
	cout << "PASSED!" << endl << endl;
}


void TestIsPresentSizeAndOrder() {
	cout << "Testing IsPresent, Size, and Order..." << endl;
	
	// more tests go here!

	Graph g2 = Graph();
	assert(g2.Size() == 0);
	assert(g2.Order() == 0);
	assert(g2.IsPresent(17) == false);


	cout << "PASSED!" << endl << endl;
}



void TestGetOutwardEdgesFrom(){
	cout << "Testing GetOutwardEdgesFrom..." << endl;
	Graph g = Graph();
	g.AddNode(17);
	g.AddNode(18);
	g.AddNode(22);
	g.AddNode(34);

	const GraphEdge* ge1 = g.AddEdge(17, 18, 3);
	g.AddEdge(22, 18); // weight will be 0 of course
	const GraphEdge* ge3 = g.AddEdge(17, 34, 8);
	g.AddEdge(22, 17, 6); // note, 22 is not a neighbor of 17, but 17 is a neighbor of 22
	
	set<const GraphEdge*> soln;
	soln.insert(ge3);
	soln.insert(ge1);
	
	set<const GraphEdge*> result = g.GetOutwardEdgesFrom(17);
	assert(result.size() == soln.size());
	assert(result == soln);


	// more tests go here!
	
	
	cout << "PASSED!" << endl << endl;
}


void TestGetNodes(){
	cout << "Testing GetNodes..." << endl;
		
	Graph g = Graph();
	g.AddNode(51);
	g.AddNode(24);
	g.AddNode(73);

	
	set<nodekey_t> nodes = g.GetNodes();
	set<nodekey_t> soln = {24, 73, 51};
	assert(nodes.size() == soln.size());
	assert(nodes == soln);


	g = Graph();
	nodes = g.GetNodes();
	soln.clear();
	assert(nodes.size() == soln.size());
	assert(nodes == soln);
		
	cout << "PASSED!" << endl << endl;
}




void TestDestructor(){
	cout << "Testing Destructor..." << endl;
	Graph *g = new Graph();

	g->AddNode(3);
	g->AddNode(5);
	g->AddEdge(3, 5, 15);
	delete g;
	
	
	Graph *g2 = new Graph();
	g2->AddNode(12);
	g2->AddNode(11);
	delete g2;


	Graph *g3 = new Graph();
	delete g3;
	
	
	Graph g4 = Graph(); // deconstructed automatically when this funciton ends
	
	cout << "NO ERRORS.  Use valgrind to check!" << endl << endl;
}



int main(){
	
	TestAddNode();
	TestAddEdge();
	TestIsPresentSizeAndOrder();
	TestGetOutwardEdgesFrom();
	TestGetNodes();
	TestDestructor();
	TestGraphEdgeCases();

	
	cout << "ALL TESTS PASSED!" << endl;
	return 0;
}
