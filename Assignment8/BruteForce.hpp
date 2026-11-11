#pragma once
#include "KDTree.hpp"

// check every point, return the closest one
Point bruteForceNearest(const vector<Point>& pts, const Point& query) {
    double closest_dist = numeric_limits<double>::infinity();
    Point closest_pnt;
    for (int i=0; i<pts.size(); i++) {
        double current_dist = distance(pts[i], query);
        if (current_dist < closest_dist) {
            closest_pnt = pts[i];
            closest_dist = current_dist;
        }
    }
    return closest_pnt;
}
