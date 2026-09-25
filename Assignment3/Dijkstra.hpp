#include "Graph.hpp"
#include "MinHeap.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <optional>

using namespace std;

/**
 * Find the shortest path from [start] to [end] in [graph], where edge
 * weights represent distance.
 * @return the path from [start] to [end] as an ordered list of nodes,
 *   or an empty vector if [end] is not reachable from [start].
 */
template <typename Node>
vector<Node> dijkstra(Graph<Node> graph, Node start, Node end) {
    unordered_map<Node, double> distance;
    unordered_map<Node, Node> predecessor;
    unordered_set<Node> visited;
    MinHeap<Node> toVisit;

    distance[start] = 0;
    toVisit.addWithPriority(start, 0);

    while (!toVisit.empty()) {
        Node current = toVisit.next().value();

        if (visited.count(current)) {
            continue;
        }
        visited.insert(current);

        if (current == end) break;

        vector<pair<Node, double>> neighbors = graph.getEdges(current);
        for (const auto& neighbor : neighbors) {
            double newDist = distance[current] + neighbor.second;
            if (!distance.count(neighbor.first) || distance[neighbor.first] > newDist) {
                distance[neighbor.first] = newDist;
                predecessor[neighbor.first] = current;
                toVisit.addWithPriority(neighbor.first, newDist);
            }
        }
    }

    vector<Node> result;
    stack<Node> backTrack;
    if (visited.count(end)) {
        Node current = end;
        while (current != start) {
            backTrack.push(current);
            current = predecessor[current];
        }
        while (!backTrack.empty()) {
            result.push_back(backTrack.top());
            backTrack.pop();
        }
        return result;
    } else {
        return {};
    }
}
