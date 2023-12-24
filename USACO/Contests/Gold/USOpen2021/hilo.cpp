#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<int> p(N);
    for(int i = 0; i < N; i++) {
        cin >> p[i];
    }
    vector<int> re(N + 2), e(N + 1);
    vector<int> m(N + 1);
    for(int i = 0; i <= N; i++) m[i] = i + 1;
    for(int i = 0; i <= N; i++) e[i] = i + 1;
    for(int i = 1; i <= N + 1; i++) re[i] = i - 1;

    vector<int> d(N + 2);
    for(int i = N - 1; i >= 0; i--) {
        int hi = p[i];
        int lo = re[hi];
        d[m[lo]]++;
        d[hi]--;

        m[lo] = hi;
        re[e[hi]] = lo;
        e[lo] = e[hi];
    }
    int v = 0;
    for(int i = 0; i <= N; i++) {
        v += d[i];
        cout << v << endl;
    }
}