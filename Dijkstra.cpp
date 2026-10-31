#include "Dijkstra.h"
#include "BetterPriorityQueue.h"

#include <climits>
#include <stdexcept>

int dijkstra(nodekey_t start, nodekey_t end, const Graph* g) {
    if (g == nullptr || !g->IsPresent(start) || !g->IsPresent(end)) {
        throw std::invalid_argument("Dijkstra requires a graph and valid endpoints");
    }
    if (start == end) return 0;

    BetterPriorityQueue queue;
    for (nodekey_t key : g->GetNodes()) {
        BPQNode node;
        node.gnode = key;
        node.pri = (key == start) ? 0 : INT_MAX;
        queue.push(node);
    }

    while (!queue.empty()) {
        const BPQNode current = queue.top();
        queue.pop();

        if (current.pri == INT_MAX) return INT_MAX;
        if (current.gnode == end) return current.pri;

        for (const GraphEdge* edge : g->GetOutwardEdgesFrom(current.gnode)) {

            if (edge->weight > static_cast<unsigned int>(INT_MAX - current.pri)) {
                continue;
            }
            BPQNode candidate;
            candidate.gnode = edge->to;
            candidate.pri = current.pri + static_cast<int>(edge->weight);

            queue.Update(candidate);
        }
    }
    return INT_MAX;
}
