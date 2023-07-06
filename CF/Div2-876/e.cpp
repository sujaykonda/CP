#include <cplib/general.h>
using namespace std;

int main() {
    int n; rd(n);    
    vector<int> a(n); rd(a);
    int sm = 0;
    for(int i = 0; i < n; i++) sm += a[i];
    bool second = false;
    if(sm % 2 == 0) {
        vector<vector<int>> dp(n + 1, vector<int>(300 * n + 1, -1));
        dp[0][0] = n;
        for(int i = 0; i < n; i++) {
            dp[i + 1] = dp[i];
            for(int j = 0; j < dp[i].size(); j++)
                if(dp[i][j] != -1 && dp[i + 1][j + a[i]] == -1)
                    dp[i + 1][j + a[i]] = i;
        }
        if(dp[n][sm / 2] != -1) {
            cout << "Second" << endl;
            vector<bool> st(n);
            int c = sm / 2;
            int i = dp[n][c];
            while(i != n) {
                st[i] = true;
                c -= a[i];
                i = dp[i + 1][c];
            }
            bool done = false;
            while(!done) {
                int j; rd(j); j--;
                for(int i = 0; i < n; i++) {
                    if(a[i] != 0 && st[j] != st[i]) {
                        cout << i + 1 << endl;
                        int mn = min(a[i], a[j]);
                        a[i] -= mn, a[j] -= mn;
                        break;
                    }
                }
                done = true;
                for(int i = 0; i < n; i++) 
                    if(a[i] != 0)
                        done = false;
            }
            
            return 0;
        } 
    }
    cout << "First" << endl;
    bool done = false;
    while(!done) {
        for(int i = 0; i < n; i++) {
            if(a[i] != 0) {
                cout << i + 1 << endl;
                int j; rd(j); j--;
                if(j == -1) return 0;
                int mn = min(a[i], a[j]);
                a[i] -= mn, a[j] -= mn;
                break;
            }
        }
        done = true;
        for(int i = 0; i < n; i++) 
            if(a[i] != 0)
                done = false;
    }
}