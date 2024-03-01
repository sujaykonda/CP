#include <cplib/general.h>
using namespace std;

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int t; rd(t);
    while(t--) {
        int n; rd(n);
        vector<int> ans(n);
        int x = 0;
        auto query = [&] (int i) {
            cout << "? " << i+1 << endl;
            string s; rd(s);
            int v = 0;
            if(s[0] == '>') v++;
            else if(s[0] == '<') v--;
            x += v;
            return v;
        };
        function<void(vector<int>)> solve = [&] (vector<int> is) {
            if(is.size() == 0) return;
            int i = is[uniform_int_distribution<int>(0, is.size()-1)(rng)];
            while(true) {
                if(query(i) == 0) 
                    break;
            }
            ans[i] = x;
            vector<int> sm, lg;
            for(int j : is) {
                if(j != i) {
                    if(query(j) == 1) lg.pb(j);
                    else sm.pb(j);
                    query(i);
                }
            }
            solve(sm);
            solve(lg);
        };
        vector<int> is(n);
        for(int i = 0; i < n; i++) is[i] = i;
        solve(is);
        int mn = 0;
        for(int i = 0; i < n; i++) mn = min(ans[i], mn);
        cout << "! ";
        for(int i = 0; i < n; i++) cout << ans[i] - mn + 1 << " ";
        cout << endl;
    }
}