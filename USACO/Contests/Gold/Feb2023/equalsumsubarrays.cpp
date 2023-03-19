#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N;
vector<ll> a;

vector<ll> solve() {
    vector<ll> sol(N, LONG_LONG_MAX);
    set<ll> bsums;
    bsums.insert(0);
    for(int i = 1; i < N; i++) {
        ll sum = 0;
        for(int j = i - 1; j >= 0; j--) {
            sum += a[j];
            bsums.insert(sum);
        }
        sum = 0;
        for(int j = i; j < N; j++)
            sum += a[j];
        ll b = LONG_LONG_MAX;
        for(int j = N - 1; j >= i; j--) {
            auto lb = bsums.lower_bound(sum);
            if(lb != bsums.end())
                b = min(llabs((*lb) - sum), b);
            if(lb != bsums.begin())
                b = min(llabs((*(--lb)) - sum), b);
            sol[j] = min(sol[j], b);
            sum -= a[j];
        }
    }
    bsums.clear();
    for(int i = 2; i < N; i++) {
        ll sum = 0;
        for(int j = i - 2; j >= 0; j--) {
            sum += a[j];
            bsums.insert(sum);
        }
        sum = 0;
        for(int j = i; j < N; j++)
            sum += a[j];
        ll b = LONG_LONG_MAX;
        for(int j = N - 1; j >= i; j--) {
            auto lb = bsums.lower_bound(-sum);
            if(lb != bsums.end())
                b = min(llabs((*lb) + sum), b);
            if(lb != bsums.begin())
                b = min(llabs((*(--lb)) + sum), b);
            sol[j] = min(sol[j], b);
            sum -= a[j];
        }
    }
    return sol;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

    cin >> N;
    a.resize(N);
    for(int i = 0; i < N; i++)
        cin >> a[i];
    
    vector<ll> sol = solve();
    reverse(a.begin(), a.end());
    vector<ll> rsol = solve();
    reverse(rsol.begin(), rsol.end());
    for(int i = 0; i < N; i++)
        cout << min(sol[i], rsol[i]) << endl;
}