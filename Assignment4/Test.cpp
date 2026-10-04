#include <cassert>
#include <iostream>
#include "InsertionSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"
#include "RadixSort.hpp"

using namespace std;

int main() {
    vector<int> sorted = {1, 2, 3, 5, 7, 8};

    vector<int> a = {3, 7, 1, 8, 2, 5};
    insertionSort(a);
    assert(a == sorted);

    a = {3, 7, 1, 8, 2, 5};
    mergeSort(a);
    assert(a == sorted);
    a = {4, 5, 6, 1, 2, 3};
    mergeSort(a);
    assert((a == vector<int>{1, 2, 3, 4, 5, 6}));

    a = {3, 7, 1, 8, 2, 5};
    quickSort(a);
    assert(a == sorted);
    a = {5, 5, 5};
    quickSort(a);
    a = {170, 45, 75, 90, 802, 24, 2, 66};
    radixSort(a);
    assert((a == vector<int>{2, 24, 45, 66, 75, 90, 170, 802}));
    a = {1000, 5, 200};
    radixSort(a);
    assert((a == vector<int>{5, 200, 1000}));

    cout << "ok" << endl;
    return 0;
}
