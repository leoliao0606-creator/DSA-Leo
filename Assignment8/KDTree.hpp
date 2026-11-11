#pragma once
#include <cmath>
#include <memory>
#include <random>
#include <vector>
#include <limits>
using namespace std;

using Point = vector<double>;

// euclidean distance between two k-dim points
double distance(const Point& a, const Point& b) {
    int k = a.size();
    double sum = 0;
    for (int i=0; i<k; i++) {
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sqrt(sum);
}

// lomuto partition on pts[lo, hi) by coord axis, returns where the pivot ends up
int partition(vector<Point>& pts, int lo, int hi, int axis) {
    static mt19937 gen(42);
    int r = uniform_int_distribution<int>(lo, hi - 1)(gen);  // random pivot, avoids n^2 on sorted input
    swap(pts[r], pts[hi - 1]);  // move the pivot to the right end for convenience
    double pivotVal = pts[hi - 1][axis];

    int i = lo;  // pts[lo, i) are all < pivot
    for (int j = lo; j < hi - 1; j++) {
        if (pts[j][axis] < pivotVal) {
            swap(pts[i], pts[j]);
            i++;
        }
    }
    swap(pts[i], pts[hi - 1]);  // pivot goes right after the small ones
    return i;
}

// reorder pts[lo, hi) so pts[nth] is what sorting by axis would put there,
// everything left of it <= it, everything right >= it (like std::nth_element)
void quickselect(vector<Point>& pts, int lo, int hi, int nth, int axis) {
    while (hi > lo) {
        int cur = partition(pts, lo, hi, axis);
        if (cur == nth) {
            return;
        } else if (cur > nth) {
            hi = cur;
        } else if (cur < nth) {
            lo = cur + 1;
        }
    }
}

class KDTree {
private:
    struct Node {
        Point point;
        int axis;  // which coordinate this node splits on
        unique_ptr<Node> left, right; // I learned this smart pointer from AI
    };

    unique_ptr<Node> root;
    int k = 0;

    // build a subtree from pts[lo, hi), split on depth % k
    unique_ptr<Node> build(vector<Point>& pts, int lo, int hi, int depth) {
        if (lo >= hi) return nullptr;
        quickselect(pts, lo, hi, (hi-lo) / 2 + lo, depth % k);
        unique_ptr<Node> cur = make_unique<Node>();
        cur->point = pts[(hi-lo) / 2 + lo];
        cur->axis = depth % k;
        cur->left = build(pts, lo, (hi-lo) / 2 + lo, depth+1);
        cur->right = build(pts, (hi-lo) / 2 + lo + 1, hi, depth+1);
        return cur;
    }

    // walk down toward query, then check the other side only if it could be closer
    void nearest(const Node* node, const Point& query, const Point*& best, double& bestDist) const {
        if (!node) return;
        double curDist = distance(node->point, query);
        if (curDist < bestDist) {
            bestDist = curDist;
            best = &node->point;
        }
        int axis = node->axis;
        if (node->point[axis] > query[axis]) {
            nearest(node->left.get(), query, best, bestDist);
            if (bestDist > abs(query[axis] - node->point[axis])) 
                nearest(node->right.get(), query, best, bestDist);
        } else {
            nearest(node->right.get(), query, best, bestDist);
            if (bestDist > abs(query[axis] - node->point[axis])) 
                nearest(node->left.get(), query, best, bestDist);
        }
        
    }

public:
    KDTree(vector<Point> pts) {
        k = pts[0].size();
        root = build(pts, 0, pts.size(), 0);
    }

    Point nearest(const Point& query) const {
        const Point* best = nullptr;
        double bestDist = numeric_limits<double>::infinity();
        nearest(root.get(), query, best, bestDist);
        return *best;
    }
};
