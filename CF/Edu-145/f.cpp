#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }

void testcase() {
    int n, k; cin >> n >> k;
    vector<ll> a(n), b(n);
    ll total = 0;
    for(int i = 0; i < n; i++) cin >> a[i], total += a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    // solve all twos case
    bool easy = true;
    for(int i = 0; i < n; i++)
        easy &= b[i] == 2;
    if(easy) {
        for(int i = 0; i < n; i++)
            cout << 2 * total << " ";
        cout << endl;
        return;
    }

    // solve all other cases
    vector<ll> c(n);
    for(int i = 0; i < n; i++) {
        if(b[i] == 1) {
            int j = (i + n - 1) % n;
            ll dist = 0;
            while(b[j] == 2) {
                dist += a[j];
                c[j] = dist;
                j = (j + n - 1) % n;
            }
            dist += a[j];
            c[j] = max(0ll, dist - k);
        }
    }
    ll onecost = 0;
    for(int i = 0; i < n; i++)
        onecost += b[i] == 1 ? c[i] : 0;
    int lastone = 0;
    ll dist = 0;
    for(int i = 0; i < n; i++) {
        if(b[i] == 1) lastone = i, dist = 0;
        dist += a[i];
    }
    for(int i = 0; i < n; i++) {
        if(b[i] == 1) {
            lastone = i, dist = 0;
            cout << onecost + total << " ";
        } else {
            cout << onecost - c[lastone] + c[i] + total + max(0ll, dist - k) << " ";
        }
        dist += a[i];
    }
    cout << endl;
    //cout << str(c) << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}