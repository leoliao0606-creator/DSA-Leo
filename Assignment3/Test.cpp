#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include "Problem81.hpp"

using namespace std;

void testMinHeap() {
    MinHeap<int> heap;
    assert(heap.empty());
    heap.addWithPriority(5, 5);
    heap.addWithPriority(1, 1);
    heap.addWithPriority(3, 3);
    assert(heap.next().value() == 1);
    assert(heap.next().value() == 3);
    assert(heap.next().value() == 5);
    assert(heap.empty());
}

void testMatrix2Graph() {
    vector<vector<int>> matrix = {{1, 2}, {4, 5}};
    auto graph = matrix2Graph(matrix);
    assert(graph.getEdges({0, 0}).size() == 2);
    assert(graph.getEdges({1, 1}).empty());
}

void testDijkstra() {
    // 1 2 3 / 4 5 6 / 7 8 9, best path 1->2->3->6->9 = 21
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto graph = matrix2Graph(matrix);
    auto path = dijkstra(graph, pair<int, int>{0, 0}, pair<int, int>{2, 2});
    int total = matrix[0][0];
    for (auto& n : path) total += matrix[n.first][n.second];
    assert(total == 21);
}

int main() {
    testMinHeap();
    testMatrix2Graph();
    testDijkstra();
    cout << "All tests passed." << endl;
    return 0;
}
