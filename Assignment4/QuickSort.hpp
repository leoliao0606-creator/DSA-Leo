#pragma once

#include <vector>
#include <utility>

using namespace std;

/**
 * Sort [arr] in place using quick sort, ascending. The pivot is arr[0],
 * smaller-or-equal elements go to small and bigger ones go to large.
 *
 * The average case is O(nlogn), when the input is random and the pivot is
 * roughly the median. Then each split is about half and half, giving log n
 * levels of n work each, so T(n) = 2T(n/2) + n. The worst case is O(n^2),
 * which happens on sorted, reverse sorted, or all-equal input. There the
 * pivot is always the min or max, so one side is empty and the other only
 * shrinks by 1. That means n levels and n + (n-1) + ... + 1 work in total,
 * so T(n) = T(n-1) + n.
 *
 * The extra space is O(n) on average for small and large, but O(n^2) in the
 * worst case, since every level keeps its copy alive until it returns. The
 * worst case also recurses n deep.
 */
template <typename T>
void quickSort(vector<T>& arr) {
    if (arr.size() == 1 || arr.size() == 0) return;
    T pivot = arr[0];
    vector<T> small;
    vector<T> large;
    for (int i=1; i<arr.size(); i++) {
        if (arr[i] <= pivot) {
            small.push_back(arr[i]);
        } else {
            large.push_back(arr[i]);
        }
    }

    quickSort(small);
    quickSort(large);

    int idx = 0;
    while (idx < small.size()) {
        arr[idx] = small[idx];
        idx++;
    }
    arr[idx++] = pivot;
    while (idx < arr.size()) {
        arr[idx] = large[idx - small.size() - 1 ];
        idx++;
    }
}
