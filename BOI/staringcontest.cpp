#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> p(n + 1);
    for(int i = 1; i <= n; i++) p[i] = i;
    random_shuffle(p.begin()+1, p.end());
    vector<int> rp(n + 1);
    for(int i = 1; i <= n; i++) rp[p[i]] = i;
    auto query = [&] (int a, int b) {
        cout << "? " + to_string(p[a]) + " " + to_string(p[b]) << endl;
        int x; cin >> x;
        return x;
    };
    int a = 1;
    int b = 2;
    int ab = query(a, b);
    vector<int> ans(n + 1);
    for(int c = 3; c <= n; c++) {
        int ac = query(a, c);
        if(ac > ab) {
            ans[b] = ab;
            b = c;
            ab = ac;
        } else if(ac == ab) {
            ans[a] = ac;
            a = c;
            ab = query(a, b);
        } else {
            ans[c] = ac;
        }
    }
    ans[a] = ans[b] = ab;
    cout << "!";
    for(int i = 1; i < n; i++) cout << ans[rp[i]] << " ";
    cout << ans[rp[n]] << endl;
}