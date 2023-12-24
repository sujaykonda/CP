#include <cplib/general.h>
using namespace std;

vector<vector<int>> pre(20);

void tc() {
    int n, m; rd(n, m);
    vector<pair<int, int>> e;
    for(int i = 0; i < m; i++) {
        int a, b; rd(a, b);
        e.pb({a, b});
    }
    if(n >= 20) {
        cout << n << endl;
        for(int i = 1; i <= n; i++) cout << i << " ";
        cout << endl;
        return;
    } else {
        vector<int> adj(n);
        for(auto [a, b] : e) {
            a--, b--;
            adj[a] += (1 << b);
        }
        for(int i : pre[n]) {
            bool good = true;
            int sz = 0;
            for(int j = 0; j < n; j++) {
                if(getbit(i, j)) {
                    sz++;
                    if(((~i) & adj[j]) > 0) {
                        good = false;
                        break;
                    }
                }
            }
            if(good) {
                cout << sz << endl;
                for(int j = 0; j < n; j++) {
                    if(getbit(i, j)) cout << j + 1 << " ";
                }
                cout << endl;
                return;
            }
        }
        cout << -1 << endl;
    }
}

int main() {
    for(int n = 1; n <= 19; n++) {
        vector<int> op(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if((j + 1) % (i + 1) == 0) op[i] += (1 << j);
            }
        }
        for(int i = (1 << n) - 1; i >= 1; i--) {
            int v = 0;
            int sz = 0;
            for(int j = 0; j < n; j++) {
                if(getbit(i, j)) {
                    sz++;
                    v ^= op[j];
                }
            }
            int cnt = 0;
            for(int j = 0; j < n; j++) if(getbit(v, j)) cnt++;
            if(cnt <= n / 5) {
                pre[n].pb(i);
            }
        }
    }
    int t; rd(t);
    while(t--) tc();
}

