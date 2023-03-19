#include <bits/stdc++.h>
using namespace std;
using ll = long long;
bool check(int i, int j) {
    bool g = true;
    for(int k = 1; k <= max(i, j); k *= 3)
        g &= ((((i / k) % 3) % 2) == (((j / k) % 3) % 2));
    return g;
}
int main() {
    int Q;
    cin >> Q;
    for(int q = 0; q < Q; q++) {
        ll d, x, y;
        cin >> d >> x >> y;
        vector<ll> pat;
        int lp = 0;
        while(!check(x, y) && lp < 1000 && d >= 0) x++, y++, d--, lp++;
        if(d == -1 || lp == 1000) {
            cout << 0 << endl;
            continue;
        }
        int p = 0;
        while(pat.size() < 30) {
            x++, y++, p++;
            if(check(x, y))
                pat.push_back(p), p = 0;    
        }
        int ps = 0;
        for(int s = 1; s <= pat.size(); s++) {
            bool good = true;
            for(int i = 0; i < pat.size(); i++) {
                if(pat[i] != pat[i % s]) {
                    good = false;
                    break;
                }
            }
            if(good) {
                ps = s;
                break;
            }
        }
        ll cnt = 1;
        int plen = 0;
        for(int i = 0; i < ps; i++)
            plen += pat[i];
        cnt += (d / plen) * ps;
        d %= plen;
        for(int i = 0; i < ps; i++)
            if(d - pat[i] >= 0)
                d -= pat[i], cnt++;
            else
                break;
        cout << cnt << endl;  
    }
}