#pragma once

#include <vector>
#include <utility>
using namespace std;

/**
 * Sort [arr] in place using radix sort, ascending. Only works for
 * non-negative ints.
 *
 * The time is O(d*n), where d is the number of digits in the largest number. 
 * Each iteration drops all n numbers into 10 buckets and reads them back, 
 * and there is one pass per digit. Since d is about log10(m) for values up 
 * to m, this is O(nlogm). The extra space is O(n + 10) for the buckets.
 */
void radixSort(vector<int> & arr) {
    int exp = 1;
    bool flag = true;
    while (flag) {
        flag = false;
        vector<vector<int>> buckets(10);
        for (int i=0; i<arr.size(); i++) {
            // int cur = (arr[i] % (exp * 10)) / exp;
            int cur = (arr[i] / exp) % 10;
            if (arr[i] / exp - cur) flag = true;
            buckets[cur].push_back(arr[i]);
        }
        arr.clear();
        for (int i=0; i<10; i++) {
            int j = 0;
            while(j < buckets[i].size()) {
                arr.push_back(buckets[i][j++]);
            }
        }
        exp *= 10;
    }
}