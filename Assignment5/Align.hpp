#pragma once
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

// Needleman-Wunsch global alignment constants
const int MATCH = 1;
const int MISMATCH = -1;
const int GAP = -2;

// A struct that holds the result
struct Alignment {
    int score;
    string a;
    string b;
};

// The Needleman Wunsch Algorithm, which can align 2 DNA sequence globally
inline Alignment needlemanWunsch(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // first row and column (only gaps)
    for (int i=1; i < n+1; i++) {
        dp[i][0] = GAP * i;
    }
    for (int j=1; j < m+1; j++) {
        dp[0][j] = GAP * j;
    }

    // fill dp, best score among: diagonal (match/mismatch), up (gap in b), left (gap in a)
    for (int i=1; i < n+1; i++) {
        for (int j=1; j < m+1; j++) {
            dp[i][j] = max(dp[i-1][j-1] + (a[i-1] == b[j-1] ? MATCH : MISMATCH), max(dp[i][j-1] + GAP, dp[i-1][j] + GAP));
        }
    }

    // backtrace from dp[n][m] to dp[0][0], build the two aligned strings
    string ra, rb;
    int i = n, j = m;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && dp[i][j] == dp[i-1][j-1] + (a[i-1] == b[j-1] ? MATCH : MISMATCH)) {
            ra.push_back(a[i-1]);
            rb.push_back(b[j-1]);
            i--; j--;
        } else if (i > 0 && dp[i][j] == dp[i-1][j] + GAP) {
            ra.push_back(a[i-1]);
            rb.push_back('-');
            i--;
        } else {
            ra.push_back('-');
            rb.push_back(b[j-1]);
            j--;
        }
    }
    reverse(ra.begin(), ra.end());
    reverse(rb.begin(), rb.end());
    return Alignment{dp[n][m], ra, rb};
}
