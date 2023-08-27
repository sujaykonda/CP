#include <cplib/graph/flow.h>
using namespace std;

int getcyc(vector<int>& a, vector<int>& ca) {
    int n = a.size();
    int cc = 0;
    for(int i = 0; i < n; i++) {
        if(ca[i] == -1) {
            int j = i;
            do {
                ca[j] = cc;
                j = a[j];
            } while (j != i);
            cc++;
        }
    }
    return cc;
}

int main() {
    int n; rd(n);
    vector<int> a(n), b(n); rd(a, b);
    for(int i = 0; i < n; i++) a[i]--, b[i]--;
    vector<int> ca(n, -1), cb(n, -1);
    int A = getcyc(a, ca), B = getcyc(b, cb);
    wadjlist adj = wadjlist(A + B + 2);
    int st = 0, si = A + B + 1;
    for(int i = 1; i <= A; i++) adj[st].pb({i, 1});
    for(int i = 1; i <= B; i++) adj[A + i].pb({si, 1});
    for(int i = 0; i < n; i++)
        adj[ca[i] + 1].pb({A + cb[i] + 1, 1});
    ffdfs(adj, st, si);
    vector<int> cnt(A);
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        if(adj[ca[i] + 1][cnt[ca[i]]++].second == 0) ans.pb(i + 1);
    }
    cout << ans.size() << endl;
    for(int ai : ans) cout << ai << " ";
    cout << endl;
}