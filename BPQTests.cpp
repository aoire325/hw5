

#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <cassert>
#include <iostream>
#include <algorithm>
#include <map>
#include <random>

using namespace std;

class InspectableQueue : public BetterPriorityQueue {
public:
    bool IsHeap() const { return is_heap(c.begin(), c.end(), comp); }
};

void DeepQueueTests() {
    InspectableQueue q;
    BPQNode node;
    node.gnode = 7;
    node.pri = 10;
    node.visited = true;
    assert(q.empty());
    assert(q.ToString() == "[]");
    assert(!q.Contains(node) && !q.Update(node));
    assert(BetterPriorityQueue::BPQNodeToString(node) == "(7, pri: 10)");
    q.push(node);
    assert(!q.Update(node));
    BPQNode dummy;
    dummy.gnode = 7;
    dummy.pri = -4;
    assert(q.Update(dummy));
    assert(q.top().pri == -4 && q.top().visited);
    q.pop();
    assert(!q.Update(dummy));

    // The independent map checks membership and minimum values after mixed
    // operations; inspecting the protected container checks the whole heap.
    map<nodekey_t, int> expected;
    mt19937 rng(5005);
    nodekey_t nextKey = 0;
    for (int step = 0; step < 3000; ++step) {
        const unsigned int operation = rng() % 4;
        if (operation == 0 || expected.empty()) {
            BPQNode item;
            item.gnode = nextKey++;
            item.pri = static_cast<int>(rng() % 2001) - 1000;
            q.push(item);
            expected[item.gnode] = item.pri;
        } else if (operation == 1) {
            BPQNode item;
            item.gnode = rng() % (nextKey + 5);
            item.pri = static_cast<int>(rng() % 4001) - 2000;
            const auto found = expected.find(item.gnode);
            const bool changes = found != expected.end() && item.pri < found->second;
            assert(q.Update(item) == changes);
            if (changes) found->second = item.pri;
        } else if (operation == 2) {
            BPQNode item;
            item.gnode = rng() % (nextKey + 5);
            assert(q.Contains(item) == (expected.count(item.gnode) != 0));
        } else {
            assert(expected.at(q.top().gnode) == q.top().pri);
            expected.erase(q.top().gnode);
            q.pop();
        }
        assert(q.IsHeap());
        assert(q.size() == expected.size());
        if (!q.empty()) {
            int minimum = INT_MAX;
            for (const auto& entry : expected) minimum = min(minimum, entry.second);
            assert(q.top().pri == minimum);
        }
    }
    int last = INT_MIN;
    while (!q.empty()) {
        assert(q.top().pri >= last);
        last = q.top().pri;
        q.pop();
    }
    assert(q.ToString() == "[]");
    cout << "Queue edge cases and 3000 mixed operations PASSED!" << endl;
}
void ContainsTest() {
	cout << "Testing Contains Helper Method..." << endl;
	
	Graph g = Graph();
	BetterPriorityQueue q;
	
	g.AddNode(1);
	g.AddNode(2);
	g.AddNode(3);
	g.AddNode(4);
	g.AddNode(5);
	g.AddNode(6);
	set<nodekey_t> nodes = g.GetNodes();
	for(nodekey_t n : nodes){
		BPQNode cur;
		cur.gnode = n;
		//cout << "inserting cur.pri: " << cur.pri << "  node: " << cur.node->key << endl;
		q.push(cur);
		//cout << "size: " << q.size() << endl;
	}
	
	
	// 1st test
	BPQNode positive;
	positive.gnode = 2;
	assert(q.Contains(positive) == true);
	
	// 2nd test
	BPQNode negative;
	assert(q.Contains(negative) == false);
	
	// 3rd test (just to ensure it still works after 2nd test finishes)
	assert(q.Contains(positive) == true);
	
	
	cout << "PASSED!" << endl;
}



void UpdateTest() {
	cout << "Testing Update Helper Method..." << endl;
	
	Graph g = Graph();
	BetterPriorityQueue q;
	
	g.AddNode(1);
	g.AddNode(2);
	g.AddNode(3);
	g.AddNode(4);
	g.AddNode(5);
	g.AddNode(6);
	set<nodekey_t> nodes = g.GetNodes();
	size_t i = 0;
	for(nodekey_t n : nodes){
		BPQNode cur;
		cur.pri = i;
		cur.gnode = n;
		//cout << "inserting cur.pri: " << cur.pri << "  node: " << cur.node->key << endl;
		q.push(cur);
		//cout << "size: " << q.size() << endl;
		i++;
	}
	

	//cout << "q before: " << queue_to_string(q) << endl;

	// Test 1: update a node with pri 0 (normal case)
	BPQNode positive;
	positive.gnode = 6;
	positive.pri = 0;
	cout << "q before: " << q.ToString() << endl;
	assert(q.Update(positive) == true);
	cout << "q after: " << q.ToString() << endl;



	// some students might have a slightly different order
	// please ensure the output is a valid priorityqueue as 
	// implemented by a binary heap.  Any valid order is fine!
	string soln1 = "[(6, pri: 0), (1, pri: 0), (2, pri: 1), (3, pri: 2), (4, pri: 3), (5, pri: 4)]";
	string soln2 = "[(1, pri: 0), (2, pri: 1), (6, pri: 0), (4, pri: 3), (5, pri: 4), (3, pri: 2)]";
	string soln3 = "[(1, pri: 0), (6, pri: 0), (2, pri: 1), (3, pri: 2), (4, pri: 3), (5, pri: 4)]";

	
	// Test 2: attempt to update with an empty / undefined input
	BPQNode negative;
	assert(q.Update(negative) == false);
	cout << "q after test 2: " << q.ToString() << endl;
	assert(q.ToString() == soln1 || q.ToString() == soln2 || q.ToString() == soln3);
	

	// Test 3: update a node with a larger priority
	// It must behave this way (ignoring larger priorities)
	// for compatibility with Dijkstra's algorithm
	BPQNode negative2;
	negative2.gnode = 5;
	negative2.pri = 80;
	assert(q.Update(negative2) == false);
	cout << "q after test 3: " << q.ToString() << endl;
	assert(q.ToString() == soln1 || q.ToString() == soln2 || q.ToString() == soln3);	
	
	cout << "PASSED!" << endl;
}

int main(){
	
	ContainsTest();
	UpdateTest();
	DeepQueueTests();
	
	cout << "ALL TESTS PASSED!!" << endl;
	
	return 0;
	
}
