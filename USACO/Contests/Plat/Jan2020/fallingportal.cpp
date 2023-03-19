#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool cmp_frac(pair<ll, ll> f1, pair<ll, ll> f2) {
    return (f1.first * f2.second < f2.first * f1.second);
}

pair<ll, ll> get_inter(pair<ll, ll> l1, pair<ll, ll> l2) {
    return {l2.second - l1.second, l1.first - l2.first};
}

struct CHT {
    vector<pair<ll, ll>> lines;
    vector<pair<ll, ll>> xs; 

    void add(pair<ll, ll> line, bool flipped) {
        while(!lines.empty() && ((lines.back().first < line.first != flipped) || (xs.empty() ? false : cmp_frac(xs.back(), get_inter(lines.back(), line))))) {
            lines.pop_back();
            if(!lines.empty()) xs.pop_back();
        }
        if(!lines.empty()) xs.push_back(get_inter(lines.back(), line));
        lines.push_back(line);
    }
    void clear() { lines.clear(), xs.clear(); }
    void print() { 
        for(pair<ll, ll> line : lines) 
            cout << line.first << " " << line.second << "  "; 
        cout << endl;
        for(pair<ll, ll> x : xs)
            cout << x.first << "/" << x.second << "  ";
        cout << endl;
    }
};

int main() {
    freopen("falling.in", "r", stdin);
    freopen("falling.out", "w", stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);
    ll N;
    cin >> N;
    vector<ll> A(N);
    for(ll i = 0; i < N; i++)
        cin >> A[i];
    vector<ll> Q(N);
    for(ll i = 0; i < N; i++)
        cin >> Q[i];
    vector<ll> o(N);
    for(ll i = 0; i < N; i++) o[i] = i;
    sort(o.begin(), o.end(), [&] (ll a, ll b) { return A[a] < A[b] || (A[a] == A[b] && a < b); });
    CHT cht;
    vector<pair<ll, ll>> sol(N);
    for(ll i : o) {
        cht.add({-i - 1, A[i]}, false);
        if(A[Q[i] - 1] > A[i]) {
            pair<ll, ll> Qline = {-Q[i], A[Q[i] - 1]};
            //cout << i << " " << Qline.first << " " << Qline.second << endl;
            ll hi = cht.xs.size(), lo = 0;
            while (lo < hi)
            {
                ll mid = lo + (hi - lo) / 2;
                //cout << mid << " ";
                if (cmp_frac(cht.xs[mid], get_inter(cht.lines[mid], Qline)))
                    hi = mid;
                else
                    lo = mid + 1;
            }
            //cout << endl;
            //cht.print();
            sol[i] = get_inter(cht.lines[lo], Qline);
            //cout << i << " " << sol[i].first << "/" << sol[i].second << endl;
        }
    }
    sort(o.begin(), o.end(), [&] (ll a, ll b) { return A[a] > A[b] || (A[a] == A[b] && a < b); });
    cht.clear();
    for(ll i : o) {
        cht.add({-i - 1, A[i]}, true);
        if(A[Q[i] - 1] < A[i]) {
            pair<ll, ll> Qline = {-Q[i], A[Q[i] - 1]};
            //cout << i << " " << Qline.first << " " << Qline.second << endl;
            ll hi = cht.xs.size(), lo = 0;
            while (lo < hi)
            {
                ll mid = lo + (hi - lo) / 2;
                //cout << mid << " ";

                if (cmp_frac(cht.xs[mid], get_inter(cht.lines[mid], Qline)))
                    hi = mid;
                else
                    lo = mid + 1;
            }
            //cout << endl;
            //cht.print();
            sol[i] = get_inter(cht.lines[lo], Qline);
            //cout << i << " " << sol[i].first << "/" << sol[i].second << endl;
        }
    }
    for(ll i = 0; i < N; i++) {
        ll n = sol[i].first, d = sol[i].second;
        ll g = gcd(n, d);
        n /= g, d /= g;
        if(n < 0 && d < 0) n *= -1, d *= -1;
        if(n < 0 || d < 0) cout << -1 << endl;
        else cout << n << "/" << d << endl;
    }
}