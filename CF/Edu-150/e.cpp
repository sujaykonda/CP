#include <cplib/general.h>
using namespace std;

void testcase() {
    int n; rd(n);
    vector<ll> a(n); rd(a);

    stack<pair<ll, ll>> s; s.push({0, 0});
    vector<ll> cnt(n + 1);
    for(int i = 0; i < n; i++) {
        ll h = n - a[i];
        ll j = i;
        while(s.top().second > h) {
            j = s.top().first;
            ll hj = s.top().second;
            s.pop();
            cnt[i - j] += hj - max(s.top().second, h);
        }
        s.push({j, h});
    }
    while(s.top().second > 0) {
        ll j = s.top().first;
        ll hj = s.top().second;
        s.pop();
        cnt[n - j] += hj - max(s.top().second, 0ll);
    }
    ll m; rd(m);
    ll cm = m;
    ll ex = 0;
    for(int i = n; i >= 1; i--) {
        if(cm >= i * cnt[i]) {
            cm -= i * cnt[i];
            ex += cnt[i];
        } else {
            ex += (cm + i - 1) / i;
            break;
        }
    }
    cout << m - ex << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++)
        testcase();
}