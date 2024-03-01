#include <bits/stdc++.h>
using namespace std;
const long long BSZ = 500;
struct DS {
    long long n;
    vector<long long> x, y;
    vector<vector<long long>> blocks;
    DS(vector<pair<long long, long long>>& p) {
        n = p.size();
        x.resize(n), y.resize(n);
        for(long long i = 0; i < n; i++) x[i] = p[i].first, y[i] = p[i].second;
        blocks.resize((n - 1) / BSZ + 1, vector<long long>(n, n));
        for(long long i = 0; i < n; i++) {
            blocks[i / BSZ][x[i]] = min(blocks[i / BSZ][x[i]], y[i]); 
        }
        for(long long i = 0; i < blocks.size(); i++) {
            for(long long j = 1; j < n; j++) {
                blocks[i][j] = min(blocks[i][j], blocks[i][j - 1]);
            }
        }
    }

    long long find_prev(long long i, long long lx, long long ly) {
        while(i--) {
            if(i % BSZ == BSZ - 1) {
                if(blocks[i / BSZ][lx] > ly) {
                    i -= BSZ - 1;
                    continue;
                }
            }
            if(x[i] <= lx && y[i] <= ly) return i;
        }
        return i;
    }
};

int main() {
    long long N, K; cin >> N >> K;
    vector<pair<long long, long long>> p(N);
    for(long long i = 0; i < N; i++) cin >> p[i].first >> p[i].second;
    vector<long long> sx(N), sy(N);
    for(long long i = 0; i < N; i++) sx[i] = sy[i] = i;
    sort(sx.begin(), sx.end(), [&] (long long a, long long b) { return p[a].first == p[b].first ? p[a].second < p[b].second : p[a].first < p[b].first; });
    sort(sy.begin(), sy.end(), [&] (long long a, long long b) { return p[a].second == p[b].second ? p[a].first < p[b].first : p[a].second < p[b].second; });
    vector<long long> cx(N), cy(N);
    for(long long i = 0; i < N; i++) cx[sx[i]] = cy[sy[i]] = i;
    vector<long long> o1(N), o2(N);
    for(long long i = 0; i < N; i++) o1[i] = o2[i] = i;
    sort(o1.begin(), o1.end(), [&] (long long a, long long b) { return p[a].first + p[a].second < p[b].first + p[b].second; });
    sort(o2.begin(), o2.end(), [&] (long long a, long long b) { return p[a].first - p[a].second < p[b].first - p[b].second; });
    vector<pair<long long, long long>> c1(N), c2(N);
    for(long long i = 0; i < N; i++) c1[i] = {cx[o1[i]], cy[o1[i]]}, c2[i] = {cx[o2[i]], N - 1 - cy[o2[i]]};
    DS ds1(c1), ds2(c2);
    priority_queue<pair<long long, pair<long long, long long>>> pq1;
    priority_queue<pair<long long, pair<long long, long long>>> pq2;
    auto diff1 = [&] (long long i, long long j) {
        return (p[o1[i]].first + p[o1[i]].second) - (p[o1[j]].first + p[o1[j]].second);
    };
    auto diff2 = [&] (long long i, long long j) {
        return (p[o2[i]].first - p[o2[i]].second) - (p[o2[j]].first - p[o2[j]].second);
    };
    for(long long i = 0; i < N; i++) {
        long long n1 = ds1.find_prev(i, c1[i].first, c1[i].second);
        long long n2 = ds2.find_prev(i, c2[i].first, c2[i].second);
        if(n1 != -1)
            pq1.push({-diff1(i, n1), {i, n1}});
        if(n2 != -1)
            pq2.push({-diff2(i, n2), {i, n2}});
    }
    while(K--) {
        if(pq1.size() != 0 && (pq2.size() == 0 || pq1.top().first > pq2.top().first)) {
            auto [v, ij] = pq1.top();
            cout << -v << '\n';
            pq1.pop();
            long long n1 = ds1.find_prev(ij.second, c1[ij.first].first, c1[ij.first].second);
            if(n1 != -1)
                pq1.push({-diff1(ij.first, n1), {ij.first, n1}});
        } else {
            auto [v, ij] = pq2.top();
            cout << -v << '\n';
            pq2.pop();
            long long n2 = ds2.find_prev(ij.second, c2[ij.first].first, c2[ij.first].second);
            if(n2 != -1)
                pq2.push({-diff2(ij.first, n2), {ij.first, n2}});
        }
    }
}