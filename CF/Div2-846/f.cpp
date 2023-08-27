#include <cplib/general.h>
using namespace std;

const int MX = 3e5 + 1;

array<int, MX> cnt, pcnt, dcnt;
array<bool, MX> pp;
int main() {
    for(int i = 2; i < MX; i++) {
        if(dcnt[i] == 0) {
            for(ll j = (ll)i * i; j < MX; j *= i)
                for(int k = j; k < MX; k += j)
                    pp[k] = true;
            for(int j = i; j < MX; j += i)
                dcnt[j]++;
        }
    }
    int n; rd(n);
    vector<int> a(n); rd(a);
    for(int ai : a) cnt[ai]++;
    for(int i = 1; i < MX; i++) pcnt[i] = cnt[i] + pcnt[i - 1];
    ll ans = 0;
    for(int i = 1; i < MX; i++) {
        if(pp[i]) continue;
        int m = (dcnt[i] % 2 ? -1 : 1);
        int curcnt = 0;
        ll cursm = 0;
        for(int j = i; j < MX; j += i) {
            if(cnt[j]) {
                ans += m * ((ll)pcnt[j - 1] * curcnt - cursm);
            }
            curcnt += cnt[j];
            cursm += (ll)pcnt[j] * cnt[j];
        }
    }
    cout << ans << endl;
}