#include "Matrix.hpp"
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <iostream>

// true if every entry is equal
bool same(Matrix a, Matrix b) {
    for (int i=0; i < a.size(); i++)
        for (int j=0; j < a.size(); j++)
            if (a.get(i, j) != b.get(i, j)) return false;
    return true;
}

Matrix randomMatrix(int n) {
    Matrix a(n);
    for (int i=0; i < n; i++)
        for (int j=0; j < n; j++)
            a.set(i, j, rand() % 10);
    return a;
}

int main() {
    int thd = 1; // default threshold that switch between Strassen and regular
    // known answer: [1 2;3 4] * [5 6;7 8] = [19 22;43 50]
    Matrix a(2), b(2), c(2);
    a.set(0, 0, 1); a.set(0, 1, 2); a.set(1, 0, 3); a.set(1, 1, 4);
    b.set(0, 0, 5); b.set(0, 1, 6); b.set(1, 0, 7); b.set(1, 1, 8);
    c.set(0, 0, 19); c.set(0, 1, 22); c.set(1, 0, 43); c.set(1, 1, 50);
    assert(same(a.multiply(b), c));
    assert(same(a.strassenMultiply(b, thd), c));

    // both methods should give the same answer
    for (int n=1; n <= 64; n *= 2) {
        Matrix x = randomMatrix(n), y = randomMatrix(n);
        assert(same(x.multiply(y), x.strassenMultiply(y, thd)));
    }
    cout << "all tests passed" << endl;

    // timing for pure regular and pure Strassen
    for (int n=16; n <= 512; n *= 2) {
        Matrix x = randomMatrix(n), y = randomMatrix(n);

        auto t0 = chrono::steady_clock::now();
        x.multiply(y);
        auto t1 = chrono::steady_clock::now();
        x.strassenMultiply(y, thd);
        auto t2 = chrono::steady_clock::now();

        cout << "n=" << n
             << " regular=" << chrono::duration<double>(t1 - t0).count() << " s"
             << " strassen=" << chrono::duration<double>(t2 - t1).count() << " s" << endl;
    }
    /* output
    n=16 regular=1.7882e-05 s strassen=0.00230067 s
    n=32 regular=0.000123273 s strassen=0.0158596 s
    n=64 regular=0.000985892 s strassen=0.111616 s
    n=128 regular=0.00796246 s strassen=0.806511 s
    n=256 regular=0.065037 s strassen=5.58162 s
    n=512 regular=0.536555 s strassen=39.1671 s
    */

    // Test for the optimal threshold to switch to regular
    int n = 1024;
    Matrix x = randomMatrix(n), y = randomMatrix(n);
    for (int t=2; t <= 512; t *= 2) {

        auto t0 = chrono::steady_clock::now();
        x.multiply(y);
        auto t1 = chrono::steady_clock::now();
        x.strassenMultiply(y, t);
        auto t2 = chrono::steady_clock::now();

        cout << "n=" << n
            << " t=" << t
            << " regular=" << chrono::duration<double>(t1 - t0).count() << " s"
            << " strassen=" << chrono::duration<double>(t2 - t1).count() << " s" 
            << endl;
    }
    /* output: 
    n=1024 t=2 regular=5.10117 s strassen=59.9491 s
    n=1024 t=4 regular=5.04592 s strassen=18.3888 s
    n=1024 t=8 regular=5.0746 s strassen=7.25299 s
    n=1024 t=16 regular=5.40065 s strassen=4.03433 s
    n=1024 t=32 regular=5.11679 s strassen=3.03435 s
    n=1024 t=64 regular=5.1324 s strassen=2.86275 s
    n=1024 t=128 regular=5.09204 s strassen=3.04192 s
    n=1024 t=256 regular=5.09633 s strassen=3.33363 s
    n=1024 t=512 regular=5.06564 s strassen=3.83471 s
    */
}
