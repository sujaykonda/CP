#include <bits/stdc++.h>
using namespace std;
template<class T> struct Mat : vector<vector<T>> {
    int N, M;
    Mat(int N, int M) : vector<vector<T>>(N, vector<T>(M)), N(N), M(M) {}
    Mat(vector<vector<T>> v) : vector<vector<T>>{v}, N(v.size()), M(v.size() > 0 ? v[0].size() : 0) {}
    Mat(int N) : Mat(N, N) { for(int i = 0; i < N; i++) (*this)[i][i] = T(1); }
    friend Mat operator*(Mat a, Mat b) { 
        assert(a.M == b.N); Mat mat = Mat(a.N, b.M);
        for(int i = 0; i < mat.N; i++) for(int j = 0; j < mat.M; j++)
        for(int k = 0; k < a.M; k++) mat[i][j] += a[i][k] * b[k][j]; return mat; }
    friend Mat pow(Mat a, long long p) { assert(p >= 0 && a.N == a.M); return p == 0 ? 
        Mat(a.N) : pow(a * a, p / 2) * (p & 1 ? a : Mat(a.N)); }
};