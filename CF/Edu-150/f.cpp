#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
using namespace std;
using ld = long double; 
typedef pair<ll, ll> pi;
pi add(pi a, pi b) {
    return {a.first + b.first, a.second + b.second}; 
}
pi sub(pi a, pi b) {
    return {a.first - b.first, a.second - b.second};
}
ld cross(pi a, pi b) {
    return a.first * b.second - a.second * b.first;
}

int main() {
    int n; rd(n);
    vector<vector<pi>> g;
    for(int i = 0; i < n; i++) {
        int a, b, c, d; rd(a, b, c, d);
        g.pb({{0, 0}, {a - b, c - d}});
    }
    auto rot = [&] (vector<pi>& p) {
        int j = 0;
        for(int i = 1; i < p.size(); i++) {
            if(p[i] < p[j]) j = i;
        }
        rotate(p.begin(), p.begin() + j, p.end());
    };
    for(vector<pi>& p : g) rot(p);
    function<void(int, int, vector<pi>&)> dc = [&] (int l, int r, vector<pi>& res) {
        if(l == r) {
            res = g[l];
            return;
        }
        int m = (l + r) / 2;
        vector<pi> lres, rres;
        dc(l, m, lres);
        dc(m + 1, r, rres);
        lres.pb(lres[0]);
        lres.pb(lres[1]);
        rres.pb(rres[0]);
        rres.pb(rres[1]);
        // merge lres and rres
        int i = 0, j = 0;
        while(i < lres.size() - 2 || j < rres.size() - 2) {
            res.pb(add(lres[i], rres[j]));
            ld cr = cross(sub(lres[i + 1], lres[i]), sub(rres[j + 1], rres[j]));
            if(cr >= 0 && i < lres.size() - 2) i++;
            if(cr <= 0 && j < rres.size() - 2) j++;
        }
    };
    vector<pi> hull;
    dc(0, n - 1, hull);
    ld mx = 0;
    for(int i = 0; i < hull.size(); i++) mx = max(mx, (ld)hull[i].first * hull[i].first + (ld)hull[i].second * hull[i].second);
    cout << setprecision(15);
    cout << mx << endl;
}