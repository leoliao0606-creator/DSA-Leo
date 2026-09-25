#include "Problem81.hpp"
#include <iostream>

/**
 * Read the Problem 81 matrix, build the graph, and print the
 * minimum path sum from the top-left element to the bottom-right element
 */
int main() {
    vector<vector<int>> matrix = readMatrix("0081_matrix.txt");
    Graph<pair<int, int>> graph = matrix2Graph(matrix);

    pair<int, int> start = {0, 0};
    pair<int, int> end = {matrix.size() - 1, matrix[0].size() - 1};
    vector<pair<int, int>> path = dijkstra(graph, start, end);

    int total = matrix[0][0];
    for (const auto& node : path) {
        total += matrix[node.first][node.second];
    }
    cout << "Minimum path sum: " << total << endl;

    return 0;
}
