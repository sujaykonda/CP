#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    ll N, K, M;
    cin >> N >> K >> M;
    vector<vector<pair<int, int>>> vK(N);
    vector<int> radj(N);
    for(int i = 0; i < N; i++) radj[i] = i;
    for(int k = 1; k <= K; k++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        vK[radj[a]].push_back({k, b});
        vK[radj[b]].push_back({k, a});
        swap(radj[a], radj[b]);
    }
    vector<int> adj(N);
    for(int i = 0; i < N; i++)
        adj[radj[i]] = i;

    vector<int> ans(N);
    for(int i = 0; i < N; i++) {
        if(ans[i] == 0) {
            vector<int> mp(N);
            ll t = 0;
            int x = i;
            mp[i] = 1;
            int sz = 1;
            do {
                for(auto &[u, v] : vK[x]) {
                    if(u + t > M) break;
                    if(mp[v]++ == 0) sz++;
                }
                if(t + K > M) break;
                x = adj[x];
                t += K;
            } while(x != i);
            bool fullcycle = x == i && t != 0;
            int y = i;
            do {
                ans[y] = sz;
                if(!fullcycle) {
                    if(--mp[y] == 0)
                        sz--;
                    for(auto &[u, v] : vK[x])
                        if(u + t > M)
                            if(mp[v]++ == 0)
                                sz++;
                    for(auto &[u, v] : vK[y])
                        if(--mp[v] == 0)
                            sz--;
                }
                y = adj[y];
                x = adj[x];
                if(!fullcycle) {
                    if(mp[y]++ == 0) sz++;
                    for(auto &[u, v] : vK[x]) {
                        if(u + t > M) break;
                        if(mp[v]++ == 0) sz++;
                    }
                }
            } while(y != i);
        }
    }
    for(int i = 0; i < N; i++)
        cout << ans[i] << endl;
}