#include <cplib/general.h>
using namespace std;

void tc() {
    int n, m, k; rd(n, m, k);
    vector<vector<int>> st(n + 1);
    vector<vector<int>> en(n + 1);
    for(int i = 1; i <= m; i++) {
        int l, r;
        rd(l, r);
        st[l - 1].push_back(i);
        en[r].push_back(i);
    }
    vector<vector<int>> dp;
    vector<int> iv;
    vector<bool> rem(m + 1);

    dp.pb(vector<int>(k + 1));
    iv.pb(0);

    int a = 0;
    for(int i = 0; i < n; i++) {
        
        while(!en[i].empty()) {
            a--;
            rem[en[i].back()] = true;
            en[i].pop_back();
        }

        while(!st[i].empty()) {
            a++;
            dp.pb(vector<int>(k + 1));
            iv.pb(st[i].back());
            for(int j = 0; j < a && j <= k; j++) dp.back()[j] = -1;
            st[i].pop_back();
        }

        bool check = true;
        while(check) {
            check = false;
            for(int j = 0; j <= k && j < dp.size(); j++) {
                if(rem[iv.end()[-1 - j]]) {
                    check = true;
                    vector<int> prev = dp.end()[-1 - j];
                    dp.erase(dp.end() - 1 - j);
                    iv.erase(iv.end() - 1 - j);
                    for(int l = 0; l < prev.size(); l++)
                        dp.end()[-1 - j][l] = max(dp.end()[-1 - j][l], prev[l]); 

                    break;
                }
            }
        }

        vector<int> ndp(k + 1, -1);
        for(int j = 0; j <= k && j < dp.size(); j++) {
            for(int l = j; l <= k; l++) {
                if(dp[dp.size() - j - 1][l - j] != -1)
                    ndp[l] = max(ndp[l], dp[dp.size() - j - 1][l - j] + 1);
            }
        }
        dp.back() = ndp;
    }
    int ans = 0;
    for(vector<int>& rw : dp) ans = max(ans, rw[k]);
    cout << ans << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}