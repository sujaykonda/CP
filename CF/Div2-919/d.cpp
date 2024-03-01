#include <cplib/general.h>
using namespace std;
const ll INF = 1e18;
void tc() {
    int n, q; rd(n, q);
    ll sz = 0;
    vector<pair<ll, ll>> szes(1);
    szes[0] = {0, 0};
    vector<vector<int>> adds(1);
    for(int i = 0; i < n; i++) {
        int b, x; rd(b, x);
        if(b == 1) {
            if(sz == INF) {
                continue;
            }
            sz++;
            adds.back().push_back(x);
        } else {
            if(sz == 0) continue;
            if(sz > INF / (x + 1)) {
                if(sz != INF) {
                    szes.push_back({INF, sz});
                    adds.push_back({});
                }
                sz = INF;
                continue;
            }
            szes.push_back({sz * (x + 1), sz});
            sz *= (x + 1);
            adds.push_back({});
        }
    }
    for(int i = 0; i < q; i++) {
        ll k; rd(k); k--;
        ll v;
        for(int j = szes.size() - 1; j >= 0; j--) {
            if(k >= szes[j].first) {
                v = adds[j][k - szes[j].first];
                break;
            }
            k %= szes[j].second;
        }
        cout << v << " ";
    }
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}