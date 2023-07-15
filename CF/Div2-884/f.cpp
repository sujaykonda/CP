#include <cplib/general.h>
using namespace std;

vector<int> solveinter(vector<int> a, int c) {
    int n = a.size();
    multiset<int> s;
    for(int i = 1; i < n; i++) s.insert(a[i]);
    vector<int> out; out.pb(a[0]);
    while(s.size() > 1) {
        for(auto it = s.lower_bound(out.back() - c);;it++) {
            if(it == s.begin() || out.back() - c > *it) continue;
            if(next(it) == s.end() || *next(it) - c <= *prev(it)) {
                out.pb(*it);
                s.erase(it);
                break;
            }
        }
    }
    out.pb(*s.begin());
    return out;
}

void tc() {
    int n, c; rd(n, c);
    vector<int> a(n); rd(a);
    if(c >= 0) {
        sort(a.begin(), a.end());
    } else {
        c = -c;
        sort(a.begin(), a.end(), greater<int>());
        vector<pair<int, int>> inter;
        inter.pb({0, -1});
        for(int i = 0; i < n - 1; i++) {
            if(a[i] - a[i + 1] > c) {
                if(inter.back().first == i) inter.back().first = i + 1;
                else inter.back().second = i, inter.push_back({i + 1, -1});
            }
        }
        inter.back().second = n - 1;
        for(auto [u, v] : inter) {
            vector<int> asub(v - u + 1);
            for(int i = u; i <= v; i++) asub[i - u] = a[i];
            asub = solveinter(asub, c);
            for(int i = u; i <= v; i++) a[i] = asub[i - u];
        }
    }
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}