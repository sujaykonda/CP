#include <cplib/general.h>
using namespace std;

void tc() {
    int n, m; rd(n, m);
    /*
    5 0 1 2 3 4
    4 5 0 1 2 3
    5 4 3 0 1 2
    5 4 3 2 0 1
    5 4 3 2 1 0
    */
    int x = min(n + 1, m);
    if(m == 1) {
        cout << 0 << endl;
        for(int i = 0; i < n; i++) {
            cout << 0 << endl;
        }
        return;
    }
    cout << x << endl;
    vector<vector<int>> ans(x - 1, vector<int>(x));
    for(int i = 0; i < x - 1; i++) {
        for(int j = 0; j < x; j++)
            ans[i][j] = (j - (i + 1) + x) % x;
    }
    while(ans.size() < n) ans.push_back(ans[0]);
    for(int i = 0; i < n; i++) {
        if(ans[i].size() < m) {
            for(int j = ans[i].size(); j < m; j++) ans[i].pb(j);
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}