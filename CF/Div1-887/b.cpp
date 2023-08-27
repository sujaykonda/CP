#include <cplib/general.h>
using namespace std;

adjlist adj;
vector<int> ts;
vector<bool> done;

void dfs(int s) {
	for (int i : adj[s]) {
		if (!done[i]) {
			done[i] = true;
			dfs(i);
		}
	}
	ts.pb(s);
}

void tc() {
    int n; rd(n);
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++)
        rd(a[i].first), a[i].second = i;
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++) {
        if(a[i].first < n && i >= n - a[n - a[i].first - 1].first) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
    vector<int> sgn(n, -1);
    for(int i = 0; i < n; i++) {
        if(i >= n - a[i].first) sgn[a[i].second] = 1;
    }
    adj = adjlist(n);
    for(int i = 0; i < n; i++) {
        if(sgn[a[i].second] == 1) {
            if(a[i].first < n) {
                adj[a[i].second].pb(a[n - a[i].first - 1].second);
            }
        } else {
            if(a[i].first > 0) {
                adj[a[i].second].pb(a[n - a[i].first].second);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        if(i < n - 1 && sgn[a[i + 1].second] == -1) {
            adj[a[i + 1].second].pb(a[i].second);
        }
        if(i > 0 && sgn[a[i - 1].second] == 1) {
            adj[a[i - 1].second].pb(a[i].second);
        }
    }
    ts.clear();
    done = vector<bool>(n);
    for(int i = 0; i < n; i++) {
        if(!done[i]) {
            done[i] = true;
            dfs(i);
        }
    }
    reverse(ts.begin(), ts.end());
    vector<int> ans(n);
    for(int i = 0; i < n; i++) {
        ans[ts[i]] = (i + 1) * sgn[ts[i]];
    }
    for(int a : ans) cout << a << " ";
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}