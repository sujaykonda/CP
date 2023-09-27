#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define pb push_back
const int MX = 5e6, JMPSZ = 5;

int jmp[MX][JMPSZ];
int x[MX], y[MX];
ll v[MX];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr); 
    int N;
    cin >> N;
    vector<int> a(N);
    for(int i = 0; i < N; i++) cin >> a[i];

    vector<pair<int, int>> rev(N);
    vector<int> s(N);
    int j = 0;
    ll ans = 0;
    function<void(int, int)> f = [&] (int a, int b) {
        if(a == N) {
            rev[N] = {b, j};
            x[j] = a, y[j] = b;
            for(int d = 0; d < JMPSZ; d++) jmp[j][d] = j;
            j++;
            return;
        }
        if(rev[a].first == b) return;
        int i = j;
        x[i] = a, y[i] = b; j++;
        int k = s[a];
        while(y[jmp[k][0]] <= b) {
            for(int d = JMPSZ - 1; d >= 0; d--) 
                if(y[jmp[k][d]] <= b) 
                    k = jmp[k][d];
            if(x[k] == N) break;
        }
        f(x[k], max(b, y[k]) + 1);
        jmp[i][0] = rev[x[k]].second;
        v[i] = (ll)(x[k] - a) * (y[jmp[i][0]]) + v[jmp[i][0]];
        for(int d = 0; d < JMPSZ - 1; d++) {
            jmp[i][d + 1] = jmp[jmp[i][d]][d];
        }
        rev[a] = {b, i};
    };
    for(int i = N - 1; i >= 0; i--) {
        f(i + 1, a[i]);
        s[i] = rev[i + 1].second;
        ans += a[i] + v[s[i]];
    }
    cout << ans << endl;

}