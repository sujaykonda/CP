#include <bits/stdc++.h>
using namespace std;
int main() {
    string s; cin >> s;
    int n = s.length();
    long long ans = 0;
    auto solve = [&] (auto&& check) {
        for(int i = 0; i < n; i++) {
            if(s[i] == 'G') continue;
            int l = i, r = i + 1;
            while(r < n && s[r] == 'G') r++;
            if(r == n) break;
            
            vector<int> c(2 * n); c[l + r]++;
            int ll = l, lr = r;
            int cur = 0, pcnt = 0, ncnt = 0, p = l + r; 
            auto up = [&] () {
                ncnt += c[p];
                cur += ncnt - pcnt;
                pcnt -= c[++p];
            };
            auto down = [&] () {
                pcnt += c[p];
                cur += pcnt - ncnt;
                ncnt -= c[--p];
            };
            l--, r++;
            while(true) {
                while(l >= 0 && s[l] == 'G') l--;
                while(r < n && s[r] == 'G') r++;
                for(int a = ll; a > l; a--) {
                    for(int b = lr; b < r; b++) {
                        if(check(a, b)) {
                            //cout << a << " " << b << ": " << cur << endl;
                            ans += cur;
                        }
                        up();
                    } 
                    for(int b = lr; b < r; b++) down();
                    down();
                }
                if(l == -1 || r == n) break;
                for(int b = lr; b < r; b++) up();
                c[l + r]++;
                ll = l, lr = r;
                l--, r++;
            }
        }
    };
    solve([&] (int a, int b) { return true; });
    for(int i = 0; i < n; i++) s[i] = s[i] == 'H' ? 'G' : 'H';
    solve([&] (int a, int b) { return (b - a) % 2 == 0; });
    for(int i = 0; i < n; i++) {
        int hcnt = 0, gcnt = 0;
        for(int j = i; j < n; j++) {
            (s[j] == 'H' ? hcnt : gcnt)++;
            if(hcnt % 2 == 1 && gcnt % 2 == 1) {
                ans--;
            }
        }
    }
    cout << ans << endl;
}
