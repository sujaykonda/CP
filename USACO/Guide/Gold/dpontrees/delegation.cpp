#include <bits/stdc++.h>
using namespace std;
int N;
vector<vector<int>> adj;
vector<int> cnt;

int dfs(int s, int e, int K) {
    vector<int> cv;
    for(int u : adj[s]) {
        if(u != e) {
            int v = dfs(u, s, K);
            if(v == -1) return -1;

            v = (v + 1) % K;
            if(v == 0) continue;
            cv.push_back(v);
        }
    }
    for(int v : cv) {
        if(cnt[K - v] > 0) cnt[K - v]--;
        else cnt[v]++;
    }
    int left = 0;
    int lcnt = 0;
    for(int v : cv) {
        if(cnt[v] > 0)
            lcnt += cnt[v], left = v, cnt[v] = 0;
    }
    if(lcnt <= 1) return left;
    return -1;

}

int main() {
	cin.tie(0)->sync_with_stdio(false);
    freopen("deleg.in", "r", stdin);
    freopen("deleg.out", "w", stdout);
    cin >> N;
    cnt.resize(N + 1);
    adj.resize(N + 1);
    for(int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cout << "1";
    vector<bool> skip(N - 1);
    for(int i = 2; i <= N - 1; i++) {
        if((N - 1) % i == 0)
            if(!skip[i] && dfs(1, 0, i) == 0)
                cout << "1";
            else {
                for(int j = 2 * i; j <= N - 1; j += i) skip[j] = true;
                cout << "0";
            }
        else
            cout << "0";
    }
    cout << endl;
}