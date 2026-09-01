#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

// This method has a time complexity of O(n^2) because there are two nested loops
// which both iterate through the whole array.
bool straightforward(vector<vector<int>> meetings) {
    for (int i=0; i<meetings.size(); i++){
        for (int j=i+1; j<meetings.size(); j++){
            // if ((meetings[i][0] > meetings[j][0] && meetings[i][0] < meetings[j][1]) ||
            //     (meetings[i][1] > meetings[j][0] && meetings[i][1] < meetings[j][1])){
            //     return true;
            // }
            if (!(meetings[i][0] >= meetings[j][1] || meetings[i][1] <= meetings[j][0])) {
                return true;
            }
        }
    }
    return false;
}

// This method has a time complexity of O(nlogn) because the sorting takes O(nlogn),
// and the loop follows only iterate through the whole array once, which is O(n).
// Hence it's O(nlogn) overall. 
bool sort_first(vector<vector<int>> meetings) {
    if (meetings.size() < 2) {
      return false;
    }

    sort(meetings.begin(), meetings.end(), [](const vector<int>& x, const vector<int>& y) {
        return x[0] < y[0];
    });
    for (int i=0; i<meetings.size()-1; i++){
        if (meetings[i+1][0] < meetings[i][1]) {
            return true;
        }
    }
    return false;
}

int main() {
    vector<vector<vector<int>>> testCases = {
        {{9, 10}},
        {{9, 10}, {10, 11}},
        {{9, 11}, {10, 12}},
        {{9, 12}, {10, 11}},
        {{9, 10}, {9, 11}},
        {{13, 14}, {9, 10}, {11, 12}}
    };

    vector<bool> expectedResults = {false, false, true, true, true, false};

    for (size_t i = 0; i < testCases.size(); i++) {
        assert(straightforward(testCases[i]) == expectedResults[i]);
        assert(sort_first(testCases[i]) == expectedResults[i]);
    }

}
