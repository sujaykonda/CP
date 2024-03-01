#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;
const int BS = 5000;
const int INF = 1e9;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int N, M; cin >> N >> M;
    vector<int> A(N);
    vector<int> cnt(M);
    vector<int> dup(1 << M);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            int a; cin >> a;
            A[i] += a << j;
            cnt[j] += a;
        }
        dup[A[i]]++;
    }
    vector<pair<int, int>> D1(1 << M, {INF, INF}), D2(1 << M, {INF, INF});
    auto upd = [&] (int i, pair<int, int> p) {
        if(D1[i].second != p.second) {
            if(D1[i].first > p.first) {
                D2[i] = D1[i];
                D1[i] = p;
            } else if(D2[i].first > p.first) {
                D2[i] = p;
            }
        } else {
            if(D1[i].first > p.first) {
                D1[i] = p;
            }
        }
    };
    for(int i = 0; i < N; i++) D1[A[i]] = {0, A[i]};
    for(int i = 0; i < (1 << M); i++) {
        for(int j = 0; j < M; j++) {
            if((i & (1 << j)) > 0) {
                upd(i, D1[i ^ (1 << j)]);
                upd(i, D2[i ^ (1 << j)]);
            }
        }
    }
    for(int i = (1 << M) - 1; i >= 0; i--) {
        for(int j = 0; j < M; j++) {
            if((i & (1 << j)) == 0) {
                upd(i, {D1[i ^ (1 << j)].first + 1, D1[i ^ (1 << j)].second});
                upd(i, {D2[i ^ (1 << j)].first + 1, D2[i ^ (1 << j)].second});
            }
        }
    }
    for(int i = 0; i < N; i++) {
        int v = (1 << M) - 1;
        int ans = 0;
        for(int j = 0; j < M; j++) {
            int c = (cnt[j] - ((A[i] & (1 << j)) > 0));
            if(c == N / 2) {
                v ^= 1 << j;
            }
            if(c >= N / 2) ans++;
        }
        int best = (dup[A[i]] == 1 && D1[v].second == A[i]) ? D2[v].first : D1[v].first;
        cout << ans - best << '\n';
    }
}