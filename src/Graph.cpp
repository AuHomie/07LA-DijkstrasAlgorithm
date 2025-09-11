#include "Graph.h"
#include <fstream>
#include <stdexcept>
#include <list>
#include <climits>   // for INT_MAX
#include <utility>   // optional, for clarity

using std::list;
using std::ifstream;
using std::invalid_argument;

Graph::Graph(std::string filename) {
    ifstream input(filename);
    if (!input) {
        throw invalid_argument("Could not read file");
    }

    input >> numNodes;
    adjList = new list<Pair>[numNodes];

    // Each of the next numNodes lines:
    // value cost value cost ... -1
    for (int i = 0; i < numNodes; i++) {
        int value;
        input >> value;
        while (value >= 0) {
            int cost;
            input >> cost;
            adjList[i].push_back(Pair(value, cost));
            input >> value;
        }
    }
}

int Graph::shortestCost(int start, int finish) {
    if (start < 0 || start >= numNodes || finish < 0 || finish >= numNodes) {
        return INT_MAX; // invalid nodes
    }

    // Distances initialized to "infinity", except start = 0
    int* dist = new int[numNodes];
    list<int> remaining;
    for (int i = 0; i < numNodes; i++) {
        dist[i] = (i == start) ? 0 : INT_MAX;
        remaining.push_back(i);
    }

    // Dijkstra with a simple "remaining" set (O(V^2), fine for small graphs)
    while (!remaining.empty()) {
        // Pick node with smallest tentative distance
        int minDist = INT_MAX;
        list<int>::iterator minIt = remaining.end();
        for (auto it = remaining.begin(); it != remaining.end(); ++it) {
            if (dist[*it] < minDist) {
                minDist = dist[*it];
                minIt = it;
            }
        }

        // If all remaining nodes are unreachable, we're done
        if (minIt == remaining.end()) break;

        int cur = *minIt;
        remaining.erase(minIt);

        // Early exit: once we pop 'finish', its distance is final
        if (cur == finish) {
            int answer = dist[cur];
            delete[] dist;
            return answer;
        }

        // Relax edges from cur -> neighbors
        if (dist[cur] != INT_MAX) { // guard against overflow/meaningless relax
            for (auto &p : adjList[cur]) {
                int next = p.node;
                int w = p.weight;
                if (dist[next] > dist[cur] + w && dist[cur] + w >= 0) {
                    dist[next] = dist[cur] + w;
                }
            }
        }
    }

    int answer = dist[finish]; // may be INT_MAX if unreachable
    delete[] dist;
    return answer;
}
