#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include "BruteForce.hpp"
#include "KDTree.hpp"

using namespace std;

mt19937 gen(42);

vector<Point> randomPoints(int n, int k) {
    uniform_real_distribution<double> dist(0, 1);
    vector<Point> pts(n, Point(k));
    for (auto& p : pts)
        for (auto& x : p) x = dist(gen);
    return pts;
}

void testQuickselect() {
    int n = 50, axis = 1;
    vector<Point> pts = randomPoints(n, 2);
    vector<Point> sorted = pts;
    sort(sorted.begin(), sorted.end(), [&](const Point& a, const Point& b) { return a[axis] < b[axis]; });
    for (int nth = 0; nth < n; nth++) {
        vector<Point> p = pts;
        quickselect(p, 0, n, nth, axis);
        assert(p[nth] == sorted[nth]);
        for (int i = 0; i < nth; i++) assert(p[i][axis] <= p[nth][axis]);
        for (int i = nth + 1; i < n; i++) assert(p[i][axis] >= p[nth][axis]);
    }
}

void testExercise2() {
    // points from the in-class exercise
    vector<Point> pts = {{1, 5}, {-1, 2}, {4, 4}, {2, 0}, {-3, -3}, {9, 1}, {4, 1}, {3, 8}};
    KDTree tree(pts);
    for (auto& p : pts) assert(tree.nearest(p) == p);
    assert(tree.nearest({2.5, 4}) == Point({4, 4}));  // goes left of the root first, real answer is on the right
    assert(tree.nearest({0, 1}) == Point({-1, 2}));
    assert(tree.nearest({8, 3}) == Point({9, 1}));
}

void testMatchesBruteForce() {
    for (int k : {1, 2, 3, 5, 10})
        for (int n : {1, 2, 7, 100, 1000}) {
            vector<Point> pts = randomPoints(n, k);
            KDTree tree(pts);
            for (auto& q : randomPoints(100, k))  // compare distances, ties could give different points
                assert(distance(tree.nearest(q), q) == distance(bruteForceNearest(pts, q), q));
        }
}

int main() {
    testQuickselect();
    testExercise2();
    testMatchesBruteForce();
    cout << "all tests passed" << endl;
}
