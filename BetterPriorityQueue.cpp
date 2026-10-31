#include "BetterPriorityQueue.h"

#include <algorithm>
#include <sstream>

bool BetterPriorityQueue::Contains(const BPQNode& node) const {
    return std::find(c.begin(), c.end(), node) != c.end();
}

bool BetterPriorityQueue::Update(const BPQNode& node) {
    for (size_t i = 0; i < c.size(); ++i) {
        if (!(c[i] == node)) continue;
        if (node.pri >= c[i].pri) return false;

        c[i].pri = node.pri;
        while (i > 0) {
            const size_t parent = (i - 1) / 2;
            if (!comp(c[parent], c[i])) break; 
            std::swap(c[parent], c[i]);
            i = parent;
        }
        return true;
    }
    return false;
}

std::string BetterPriorityQueue::ToString() const {
    std::ostringstream out;
    out << '[';
    for (size_t i = 0; i < c.size(); ++i) {
        if (i != 0) out << ", ";
        out << BPQNodeToString(c[i]);
    }
    out << ']';
    return out.str();
}

std::string BetterPriorityQueue::BPQNodeToString(const BPQNode& node) {
    return "(" + std::to_string(node.gnode) + ", pri: " +
           std::to_string(node.pri) + ")";
}
