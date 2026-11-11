#include <chrono>
#include <cstdio>
#include <iostream>
#include <random>
#include <tuple>
#include "BruteForce.hpp"
#include "KDTree.hpp"

using namespace std;

mt19937 gen(42);
volatile double sink; // so the compiler can't throw the queries away

// n random k-dim points between 0 and 1
vector<Point> randomPoints(int n, int k) {
    uniform_real_distribution<double> dist(0, 1);
    vector<Point> pts(n, Point(k));
    for (auto& p : pts)
        for (auto& x : p) x = dist(gen);
    return pts;
}

double msSince(chrono::high_resolution_clock::time_point start) {
    return chrono::duration<double, milli>(chrono::high_resolution_clock::now() - start).count();
}

// avg ms over 5 runs: (build, tree query for 1000 points, brute force for same 1000 points)
tuple<double, double, double> runExperiment(int k, int numPoints) {
    int runs = 5;
    vector<Point> pts = randomPoints(numPoints, k);
    vector<Point> queries = randomPoints(1000, k);

    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    for (int r = 0; r < runs; r++) {
        KDTree t(pts);
    }
    double build = msSince(start) / runs;

    KDTree tree(pts);
    start = chrono::high_resolution_clock::now();
    for (int r = 0; r < runs; r++)
        for (auto& q : queries) sink = tree.nearest(q)[0];
    double query = msSince(start) / runs;

    start = chrono::high_resolution_clock::now();
    for (int r = 0; r < runs; r++)
        for (auto& q : queries) sink = bruteForceNearest(pts, q)[0];
    double brute = msSince(start) / runs;

    return {build, query, brute};
}

int main() {
    vector<int> ks = {1, 2, 3, 5, 10, 20};

    // everything with gp is for the plot, done by AI like assignment 6
    FILE* gp = popen("gnuplot", "w");
    fprintf(gp, "set terminal pngcairo size 900,600\n");
    fprintf(gp, "set output 'speedup.png'\n");
    fprintf(gp, "set title 'k-d tree speedup over brute force (1000 queries)'\n");
    fprintf(gp, "set xlabel 'n (points in the tree)'\n");
    fprintf(gp, "set ylabel 'brute force time / tree query time'\n");
    fprintf(gp, "set logscale xy\n");
    fprintf(gp, "set format x '10^{%%L}'\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "plot ");
    for (int k : ks) fprintf(gp, "'-' with linespoints lw 2 title 'k = %d', ", k);  // '-' = data comes later
    fprintf(gp, "1 dt 2 lc rgb 'gray30' title 'break even'\n");

    cout << "k\tn\tbuild(ms)\ttree(ms)\tbrute(ms)\tspeedup" << endl;
    for (int k : ks) {
        for (int n : {10, 100, 1000, 10000, 100000}) {
            double build, tree, brute;
            tie(build, tree, brute) = runExperiment(k, n);
            cout << k << "\t" << n << "\t" << build << "\t" << tree << "\t" << brute << "\t" << brute / tree << endl;
            fprintf(gp, "%d %g\n", n, brute / tree);
        }
        fprintf(gp, "e\n");  // end of this k's line
    }
    pclose(gp);
    cout << "plot -> speedup.png" << endl;
}
