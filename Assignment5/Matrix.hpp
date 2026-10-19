#pragma once
#include <vector>
using namespace std;

class Matrix {
private:
    vector<vector<double>> m;

public:
    // n x n matrix filled with 0
    Matrix(int n) : m(n, vector<double>(n, 0.0)) {}

    int size() const { return m.size(); }

    void set(int r, int c, double v) { m[r][c] = v; }

    double get(int r, int c) const { return m[r][c]; }

    // split into four n/2 x n/2 blocks (n must be even)
    void split(Matrix& a11, Matrix& a12, Matrix& a21, Matrix& a22) const {
        int h = size() / 2;
        a11 = Matrix(h);
        a12 = Matrix(h);
        a21 = Matrix(h);
        a22 = Matrix(h);
        for (int i=0; i < h; i++) {
            for (int j=0; j < h; j++) {
                a11.m[i][j] = m[i][j];
                a12.m[i][j] = m[i][j + h];
                a21.m[i][j] = m[i + h][j];
                a22.m[i][j] = m[i + h][j + h];
            }
        }
    }

    static Matrix join(const Matrix& c11, const Matrix& c12,
                        const Matrix& c21, const Matrix& c22) {
        int h = c11.size();
        Matrix r(2 * h);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < h; j++) {
                r.m[i][j] = c11.m[i][j];
                r.m[i][j + h] = c12.m[i][j];
                r.m[i + h][j] = c21.m[i][j];
                r.m[i + h][j + h] = c22.m[i][j];
            }
        }
        return r;
    }


    Matrix operator+(const Matrix& o) const {
        int n = size();
        Matrix r(n);
        for (int i=0; i < n; i++)
            for (int j=0; j < n; j++)
                r.m[i][j] = m[i][j] + o.m[i][j];
        return r;
    }

    Matrix operator-(const Matrix& o) const {
        int n = size();
        Matrix r(n);
        for (int i=0; i < n; i++)
            for (int j=0; j < n; j++)
                r.m[i][j] = m[i][j] - o.m[i][j];
        return r;
    }

    Matrix multiply(const Matrix& o) const {
        int n = size();
        Matrix r(n);
        for (int i=0; i < n; i++) {
            for (int j=0; j < n; j++) {
                for (int k=0; k < n; k++) {
                    r.m[i][j] += m[i][k] * o.m[k][j];
                }
            }
        }
        return r;
    }

    // The Strassen Algorithm for matrix multiplication.
    Matrix strassenMultiply(const Matrix& o, const int thd) const {
        int n = size();
        if (n <= thd) return multiply(o);

        Matrix a11(n/2), a12(n/2), a21(n/2), a22(n/2);
        Matrix b11(n/2), b12(n/2), b21(n/2), b22(n/2);
        split(a11, a12, a21, a22);
        o.split(b11, b12, b21, b22);

        Matrix m1 = (a11 + a22).strassenMultiply(b11 + b22, thd);
        Matrix m2 = (a21 + a22).strassenMultiply(b11, thd);
        Matrix m3 = a11.strassenMultiply(b12 - b22, thd);
        Matrix m4 = a22.strassenMultiply(b21 - b11, thd);
        Matrix m5 = (a11 + a12).strassenMultiply(b22, thd);
        Matrix m6 = (a21 - a11).strassenMultiply(b11 + b12, thd);
        Matrix m7 = (a12 - a22).strassenMultiply(b21 + b22, thd);

        return join(m1 + m4 - m5 + m7, m3 + m5, m2 + m4, m1 - m2 + m3 + m6);
    }
};
