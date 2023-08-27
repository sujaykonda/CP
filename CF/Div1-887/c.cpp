#include <cplib/general.h>
using namespace std;

void tc() {
    int n, k; rd(n, k);
    vector<int> a(n); rd(a);
    int prev = 0;
    priority_queue<ll> pq;
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        a[i] %= k;
        if(prev < a[i]) {
            pq.push(prev - a[i]);
            ans += pq.top();
            pq.pop();
        } else {
            pq.push(prev - a[i] - k);
        }
        prev = a[i];
    }
    cout << -ans << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}