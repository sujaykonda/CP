#include <cplib/general.h>
using namespace std;

vector<int> solveAll(vector<int> p) {
    int n = p.size();
    vector<int> pref(n + 1);
    for(int i = 0; i < n; i++) {
        if(i <= p[i]) {
            pref[p[i] - i + 1]++;
            pref[n - i]--;
        } else {
            pref[0]++;
            pref[n - i]--;
            pref[p[i] + n - i + 1]++;
            pref[n]--;
        }
    }
    vector<int> ans(n);
    ans[0] = pref[0];
    for(int i = 1; i < n; i++) ans[i] = ans[i - 1] + pref[i];
    return ans;
}

int main() {
    int n; rd(n);
    vector<int> p(n); rd(p);
    for(int& i : p) i--;
    vector<int> ans = solveAll(p);
    reverse(p.begin(), p.end());
    vector<int> rans = solveAll(p);
    int r = 0; int s = 0;
    int q; rd(q);
    cout << ans[0] << '\n';
    for(int i = 0; i < q; i++) {
        int t; rd(t);
        if(t == 3) {
            s = (n - s) % n;
            r ^= 1;
        } else {
            int k; rd(k);
            if(t == 1) k = n - k;
            s = (s + k) % n;
        }
        if(r == 0) cout << ans[s] << '\n';
        else cout << rans[s] << '\n';
    }
}