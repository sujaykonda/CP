#include <cplib/general.h>
using namespace std;

vector<int> solve(int n, int k, string s) {
    vector<vector<int>> dp1(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        int f = 0;
        for(int j = i - 1; j >= 0; j--) {
            if(s[j] == '0') {
                dp1[i][f] = i - j - 1;
                f++;
            }
        }
        for(int j = f; j <= n; j++) dp1[i][j] = i;
        for(int j = 0; j <= n; j++) dp1[i][j] = max(dp1[i][j], dp1[i - 1][j]);
    }
    vector<int> ans(n);
    for(int i = 1; i <= n; i++) {
        vector<pair<int, int>> curans(n);
        vector<int> f(i + 1);
        for(int j = i - 1; j >= 0; j--) {
            f[j] = f[j + 1] + (s[j] == '1');
        }
        auto solve2 = [&] (int a, int lb, int rb) {
            pair<int, int> best;
            for(int j = lb; j <= rb; j++) {
                if(f[j] <= k) {
                    best = max(best, {dp1[j][k - f[j]] + (i - j) * a, j});
                }
            }
            return best;
        };
        
        auto dc = [&] (int l, int r, auto&& dc) {
            if(r - l <= 1) return;
            int m = (l + r) / 2;
            curans[m] = solve2(m + 1, curans[r].second, curans[l].second);
            dc(l, m, dc);
            dc(m, r, dc);
        };
        curans[0] = solve2(1, 0, i);
        curans[n - 1] = solve2(n, 0, i);
        dc(0, n - 1, dc);
        for(int j = 0; j < n; j++) ans[j] = max(ans[j], curans[j].first);
    }
    return ans;
}

void tc() {
    int n, k; rd(n, k);
    string s; rd(s);
    vector<int> a1 = solve(n, k, s);
    reverse(s.begin(), s.end());
    vector<int> a2 = solve(n, k, s);
    for(int i = 0; i < n; i++) {
        cout << max(a1[i], a2[i]) << " ";
    }
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}