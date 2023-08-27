
#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<vector<bool>> adj(n, vector<bool>(n));
    for(int i = 0; i < n; i++) {
        string s; rd(s);
        for(int j = 0; j < n; j++) {
            adj[i][j] = s[j] == '1';
        }
    }
    vector<int> comp(n, -1);
    auto dfs = [&] (int s, int c, auto&& dfs) {
        if(comp[s] == c) return;
        comp[s] = c;
        for(int i = 0; i < n; i++)
            if(adj[s][i])
                dfs(i, c, dfs);
    };
    int cc = 0;
    for(int i = 0; i < n; i++)
        if(comp[i] == -1)
            dfs(i, cc++, dfs);
    if(cc == 1) {
        cout << 0 << endl;
        return;
    }

    int good = -1;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(i != j && comp[i] == comp[j] && !adj[i][j])
                good = i;
    vector<int> ans;
    // all complete graphs case
    if(good == -1) {
        int mnsz = n;
        int k = -1;
        for(int i = 0; i < n; i++) {
            int cnt = 1;
            for(int j = 0; j < n; j++)
                cnt += adj[i][j];
            if(mnsz > cnt) k = i, mnsz = cnt;
        }
        if(cc != 2 && mnsz > 2) {
            ans.pb(0);
            good = 0;
            for(int i = 1; i < n; i++)
                adj[0][i] = adj[i][0] = !adj[0][i];
        } else {    
            cout << mnsz << endl;
            for(int i = 0; i < n; i++) {
                if(i == k || adj[k][i])
                    cout << i + 1 << " ";
            }
            cout << endl;
            return;
        }
    }

    vector<int> subcomp(n, -1);
    auto dfs2 = [&] (int s, int c, auto&& dfs2) {
        if(subcomp[s] == c) return;
        subcomp[s] = c;
        for(int i = 0; i < n; i++) {
            if(i != good && adj[s][i]) 
                dfs2(i, c, dfs2);
        }
    };
    int subcc = 0;
    for(int i = 0; i < n; i++) {
        if(adj[good][i] && subcomp[i] == -1)
            dfs2(i, subcc++, dfs2);
    }
    vector<bool> badsubc(subcc, true);
    for(int i = 0; i < n; i++) {
        if(!adj[good][i] && subcomp[i] != -1) 
            badsubc[subcomp[i]] = false;
    }
    ans.pb(good);
    for(int i = 0; i < subcc; i++) {
        if(badsubc[i]) {
            ans.pop_back();
            for(int j = 0; j < n; j++) {
                if(subcomp[j] == i) {
                    ans.pb(j);
                    break;
                }
            }
            break;
        }
    }
    cout << ans.size() << endl;
    for(int ai : ans) cout << ai + 1 << " ";
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}