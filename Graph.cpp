#include "Graph.h"

#include <algorithm>
#include <sstream>
#include <utility>

Graph::Graph(const Graph& other) : nodes_(other.nodes_) {
    for (const auto& edge : other.edges_) {
        std::unique_ptr<GraphEdge> copy(new GraphEdge(*edge));
        edges_.push_back(std::move(copy));
    }
}

Graph& Graph::operator=(const Graph& other) {
    // Copy first so allocation failure leaves the original graph intact.
    if (this != &other) {
        Graph copy(other);
        nodes_.swap(copy.nodes_);
        edges_.swap(copy.edges_);
    }
    return *this;
}

Graph::~Graph() = default;

void Graph::AddNode(nodekey_t key) {
    if (key == INVALID_NODE_KEY || IsPresent(key)) {
        throw std::invalid_argument("Invalid or duplicate node key");
    }
    nodes_.push_back(key);
}

const GraphEdge* Graph::AddEdge(nodekey_t fromNodeKey, nodekey_t toNodeKey,
                                unsigned int weight) {
    if (!IsPresent(fromNodeKey) || !IsPresent(toNodeKey)) {
        throw std::invalid_argument("Both edge endpoints must exist");
    }
    for (const auto& edge : edges_) {
        if (edge->from == fromNodeKey && edge->to == toNodeKey) {
            throw std::invalid_argument("Directed edge already exists");
        }
    }
    std::unique_ptr<GraphEdge> edge(new GraphEdge{fromNodeKey, toNodeKey, weight});
    const GraphEdge* result = edge.get();
    edges_.push_back(std::move(edge));
    return result;
}

bool Graph::IsPresent(nodekey_t key) const {
    return std::find(nodes_.begin(), nodes_.end(), key) != nodes_.end();
}

std::string Graph::NodesToString() const {
    std::ostringstream out;
    out << '[';
    for (size_t i = 0; i < nodes_.size(); ++i) {
        if (i != 0) out << ", ";
        out << '(' << nodes_[i] << ')';
    }
    out << ']';
    return out.str();
}

std::string Graph::EdgesToString() const {
    std::ostringstream out;
    out << '[';
    for (size_t i = 0; i < edges_.size(); ++i) {
        if (i != 0) out << ", ";
        const GraphEdge& edge = *edges_[i];
        out << "((" << edge.from << ")->(" << edge.to << ") w:"
            << edge.weight << ')';
    }
    out << ']';
    return out.str();
}

std::set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t nodeKey) const {
    if (!IsPresent(nodeKey)) {
        throw std::invalid_argument("Node does not exist");
    }
    std::set<const GraphEdge*> result;
    for (const auto& edge : edges_) {
        if (edge->from == nodeKey) result.insert(edge.get());
    }
    return result;
}

std::set<nodekey_t> Graph::GetNodes() const {
    return std::set<nodekey_t>(nodes_.begin(), nodes_.end());
}

size_t Graph::Size() const { return edges_.size(); }
size_t Graph::Order() const { return nodes_.size(); }
