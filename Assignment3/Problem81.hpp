#pragma once

#include "Dijkstra.hpp"
#include <fstream>
#include <sstream>
#include <string>

/** pair<int,int> has no default hash, so unordered_map/set can't use it as a key
 *  So I asked AI how do I enable this:
*/
namespace std {
    template<>
    struct hash<pair<int, int>> {
        size_t operator()(const pair<int, int>& p) const {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };
}

/** reads the matrix file, returns empty if it can't */
inline vector<vector<int>> readMatrix(const string& filename) {
    vector<vector<int>> matrix;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<int> row;
        stringstream lineStream(line);
        string cell;
        while (getline(lineStream, cell, ',')) {
            row.push_back(stoi(cell));
        }
        matrix.push_back(row);
    }
    return matrix;
}

/** turns the matrix into a graph, each cell a node linked right/down, edge weight = target cell value */
inline Graph<pair<int, int>> matrix2Graph(vector<vector<int>> matrix) {
    if (matrix.size() == 0 || matrix[0].size() == 0) return {};
    Graph<pair<int, int>> result;
    for (int i=1; i<matrix.size(); i++) {
        result.addEdge({i-1, 0}, {i, 0}, matrix[i][0]);
    }
    for (int i=1; i<matrix[0].size(); i++) {
        result.addEdge({0, i-1}, {0, i}, matrix[0][i]);
    }
    for (int i=1; i<matrix.size(); i++) {
        for (int j=1; j<matrix[0].size(); j++) {
            result.addEdge({i-1, j}, {i, j}, matrix[i][j]);
            result.addEdge({i, j-1}, {i, j}, matrix[i][j]);
        }
    }
    return result;
}
