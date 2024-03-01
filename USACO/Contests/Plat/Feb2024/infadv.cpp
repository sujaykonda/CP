#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
const int LGSZ = 61;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int N, Q; cin >> N >> Q;
    int mxt = 0;
    vector<int> T(N);
    for(int i = 0; i < N; i++) cin >> T[i], mxt = max(T[i], mxt);
    vector<vector<vector<pair<int, ll>>>> jmp(N);
    for(int i = 0; i < N; i++) {
        jmp[i].resize(T[i], vector<pair<int, ll>>(1));
        for(int j = 0; j < T[i]; j++) {
            cin >> jmp[i][j][0].first;
            jmp[i][j][0].first--;
            jmp[i][j][0].second = 1;
        }
    }
    function<pair<int, ll>(int, int, ll, ll)> query = [&] (int ti, int i, ll t, ll sz)  {
        while(sz > 0 && T[i] <= ti) {
            int v = t % T[i];
            int k = min((int)(jmp[i][v].size() - 1), lg(sz));
            t += jmp[i][v][k].second;
            sz -= jmp[i][v][k].second;
            i = jmp[i][v][k].first;
        }
        return make_pair(i, t);
    };
    for(int k = 1; k < LGSZ; k++) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < T[i]; j++) {
                if(T[jmp[i][j].back().first] <= T[i]) {
                    jmp[i][j].push_back(query(T[i], jmp[i][j].back().first, j + (1LL << (k - 1)), (1LL << (k - 1))));
                    jmp[i][j].back().second -= j;
                }
            }
        }
    }
    for(int i = 0; i < Q; i++) {
        int v;
        ll t, d; 
        cin >> v >> t >> d;
        v--;
        cout << query((1<<16), v, t, d).first + 1 << '\n';
    }
}