#pragma once

#include <vector>
#include <utility>

using namespace std;

/**
 * Sort [arr] in place using merge sort, ascending.
 *
 * The time is Theta(nlogn) for every input. Splitting in half gives logn
 * levels, and merging all the pieces on same level touches n elements, so
 * T(n) = 2T(n/2) + n. The extra space is O(n) because the original array
 * is copied into the left and right arrays.
 */
template <typename T>
void mergeSort(vector<T>& arr) {
    if (arr.size() == 1 || arr.size() == 0) return;
    vector<T> left(arr.begin(), arr.begin() + arr.size() / 2);
    vector<T> right(arr.begin() + arr.size() / 2, arr.end());

    mergeSort(left);
    mergeSort(right);

    int idx_l = 0;
    int idx_r = 0;
    int idx = 0;

    while (idx_l < left.size() && idx_r < right.size()) {
        if (left[idx_l] <= right[idx_r]) {
            arr[idx++] = left[idx_l++];
        } else {
            arr[idx++] = right[idx_r++];
        }
    }

    while (idx_l < left.size()) {
        arr[idx++] = left[idx_l++];
    }
    while (idx_r < right.size()) {
        arr[idx++] = right[idx_r++];
    }
}
