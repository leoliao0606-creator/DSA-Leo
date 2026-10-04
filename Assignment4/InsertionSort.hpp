#pragma once

#include <vector>
#include <utility>

using namespace std;

/**
 * Sort [arr] in place using insertion sort, ascending.
 *
 * The best case is O(n), when the input is already sorted and the inner
 * loop stops right away for every element. The worst case is O(n^2), when
 * the input is reverse sorted and element i has to move back i spots. On 
 * random input each element moves back about half way, which is still O(n^2). 
 * It only swaps elements inside arr, so the extra space is O(1).
 */
template <typename T>
void insertionSort(vector<T>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        // carry arr[i] to its left until it fits
        for (int j = i; j > 0 && arr[j] < arr[j-1]; j--) {
            swap(arr[j], arr[j-1]);
        }
    }
}
