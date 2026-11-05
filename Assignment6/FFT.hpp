#pragma once
#include "DFT.hpp"   // reuse cd

// recursive cooley-tukey, n must be a power of 2
vector<cd> fft(const vector<cd>& x) {
    int n = x.size();
    if (n == 1) return x;

    const double PI = 3.1415926535897932384626;

    // split by index: x0 x2 x4 ... / x1 x3 x5 ...
    vector<cd> even(n / 2), odd(n / 2);
    for (int j = 0; j < n / 2; j++) {
        even[j] = x[2 * j];
        odd[j] = x[2 * j + 1];
    }

    vector<cd> E = fft(even);
    vector<cd> O = fft(odd);

    vector<cd> X(n);
    for (int k = 0; k < n / 2; k++) {
        cd t = polar(1.0, -2*PI*k/n) * O[k];
        X[k] = E[k] + t;
        X[k + n/2] = E[k] - t;
    }
    return X;
}
