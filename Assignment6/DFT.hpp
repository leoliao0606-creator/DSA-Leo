#pragma once
#include <cmath>
#include <complex>
#include <vector>
using namespace std;

using cd = complex<double>;

// naive dft, O(n^2)
vector<cd> dft(const vector<cd>& x) {
    int n = x.size();
    const double PI = 3.1415926535897932384626;
    vector<cd> X(n);
    for (int k=0; k < n; k++) {
        for (int j=0; j < n; j++) {
            X[k] += x[j] * polar(1.0, -2*PI*k*j/n);
        }
    }
    return X;
}
