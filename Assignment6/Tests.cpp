#include <cassert>
#include <iostream>
#include <random>
#include "FFT.hpp"

using namespace std;

// doubles never match exactly, so compare with a tolerance
bool same(const vector<cd>& a, const vector<cd>& b) {
    double eps = 1e-9;
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); i++)
        if (abs(a[i] - b[i]) > eps) return false;
    return true;
}

void testByHand() {
    vector<vector<cd>> in = {{0, 1, 0, -1}, {1, 0, 0, 0}, {1, 1, 1, 1}, {1, 2, 3, 4}};
    vector<vector<cd>> out = {{0, cd(0, -2), 0, cd(0, 2)}, {1, 1, 1, 1}, {4, 0, 0, 0}, {10, cd(-2, 2), -2, cd(-2, -2)}};
    for (int i = 0; i < in.size(); i++) {
        assert(same(dft(in[i]), out[i]));
        assert(same(fft(in[i]), out[i]));
    }
}

void testCosine() {
    // cos with 3 cycles in 16 samples -> only X[3] and X[13] are nonzero, both n/2
    int n = 16;
    vector<cd> x(n);
    for (int j = 0; j < n; j++) x[j] = cos(2 * M_PI * 3 * j / n);
    vector<cd> expected(n, 0);
    expected[3] = expected[13] = n / 2;
    assert(same(dft(x), expected));
    assert(same(fft(x), expected));
}

void testMatchesDft() {
    // random complex input, fft should give the same thing as dft
    mt19937 gen(42);
    uniform_real_distribution<double> dist(-1, 1);
    for (int n = 1; n <= 1024; n *= 2) {
        vector<cd> x(n);
        for (auto& v : x) v = cd(dist(gen), dist(gen));
        assert(same(dft(x), fft(x)));
    }
}

int main() {
    testByHand();
    testCosine();
    testMatchesDft();
    cout << "all tests passed" << endl;
}
