#ifndef GRAPH_H
#define GRAPH_H

#include <climits>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

// Public interface transcribed from the supplied Graph.h.png.
#define nodekey_t unsigned long long int
#define INVALID_NODE_KEY ULLONG_MAX

struct GraphEdge {
    nodekey_t from;
    nodekey_t to;
    unsigned int weight;
};

class Graph {
public:
    Graph() = default;
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    ~Graph();

    void AddNode(nodekey_t key = 0);
    const GraphEdge* AddEdge(nodekey_t fromNodeKey, nodekey_t toNodeKey, unsigned int weight = 0);
    bool IsPresent(nodekey_t key) const;
    std::string NodesToString() const;
    std::string EdgesToString() const;
    std::set<const GraphEdge*> GetOutwardEdgesFrom(nodekey_t nodeKey) const;
    std::set<nodekey_t> GetNodes() const;
    size_t Size() const;
    size_t Order() const;

private:
    std::vector<nodekey_t> nodes_;
    std::vector<std::unique_ptr<GraphEdge>> edges_;
};

#endif
