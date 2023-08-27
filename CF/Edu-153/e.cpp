#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
using namespace std;
const int MXV = 676;
const int INF = 1e7;
int main() {
    string s; rd(s);
    int n = s.length() - 1;
    vector<int> a(n);
    vector<vector<int>> b(MXV);
    for(int i = 0; i < n; i++) {
        a[i] = s[i] - 'a' + 26 * (s[i + 1] - 'a');
        b[a[i]].push_back(i);
    }
    
    vector<vector<int>> d(MXV, vector<int>(n, -1));
    for(int i = 0; i < MXV; i++) {
        if(b[i].size() == 0) continue;
        array<bool, 676> done {};
        queue<int> q;
        for(int j : b[i]) 
            d[i][j] = 0, q.push(j);
        while(!q.empty()) {
            int s = q.front();
            q.pop();
            if(s > 0 && d[i][s - 1] == -1) {
                d[i][s - 1] = d[i][s] + 1;
                q.push(s - 1);
            }
            if(s < n - 1 && d[i][s + 1] == -1) {
                d[i][s + 1] = d[i][s] + 1;
                q.push(s + 1);
            }
            if(!done[a[s]]) {
                for(int j : b[a[s]]) {
                    if(d[i][j] == -1) {
                        d[i][j] = d[i][s] + 1;
                        q.push(j);
                    }
                }
                done[a[s]] = true;
            } 
        }
    }

    int m; rd(m);
    for(int i = 0; i < m; i++) {
        int x, y; rd(x, y);
        x--, y--;
        int mnd = abs(y - x);
        for(int j = 0; j < MXV; j++) {
            if(d[j][x] != -1 && d[j][y] != -1) {
                mnd = min(mnd, d[j][x] + d[j][y] + 1);
            }
        }
        cout << mnd << '\n';
    }
}