#include <cplib/general.h>
using namespace std;
const int MX = 1e5;

int phi[MX + 1];
vector<int> dv[MX + 1];

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    sort(a.begin(), a.end());
    vector<int> divcnt(MX + 1);
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        for(int d : dv[a[i]]) {
            ans += (ll)phi[d] * divcnt[d] * (n - i - 1);
            divcnt[d]++;
        }
    }
    cout << ans << endl;
}

int main() {
    for (int i = 0; i <= MX; i++) phi[i] = i;
    for (int i = 2; i <= MX; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= MX; j += i)
                phi[j] -= phi[j] / i;
        }
    }

    for(int i = 1; i <= MX; i++) {
        for(int j = i; j <= MX; j += i) {
            dv[j].pb(i);
        }
    }

    int t; rd(t);
    while(t--) tc();
}