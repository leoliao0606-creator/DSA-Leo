#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <utility>
using namespace std;

template <typename Node>
class Graph {
private:
    unordered_set<Node> nodes;
    unordered_map<Node, vector<pair<Node, double>>> adjacency_list;

public:
    /**
     * @return the vertices in the graph
     */
    unordered_set<Node> getNodes() const {
        return nodes;
    }

    /**
     * Add an edge between [from] and [to] with edge weight [cost]
     */
    void addEdge(Node from, Node to, double weight) {
        nodes.insert(from);
        nodes.insert(to);
        adjacency_list[from].push_back({to, weight});
    }

    /**
     * Get all the edges that begin at [from]
     * @return a map where each key represents a vertex connected to [from] and the value represents the edge weight.
     */
    vector<pair<Node, double>> getEdges(Node from) {
        return adjacency_list[from];
    }

    /**
     * Remove all edges and vertices from the graph
     */
    void clear() {
        nodes.clear();
        adjacency_list.clear();
    }
};