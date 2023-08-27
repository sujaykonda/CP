#include <cplib/general.h>
using namespace std;

bool cmp(pair<int, int>& p1, pair<int, int>& p2) {
    return p1.first == p2.first ? (p1.second > p2.second) : (p1.first < p2.first);
}

int main() {
    int m, q; rd(m, q);
    vector<pair<int, int>> lr(m); rd(lr);
    sort(lr.begin(), lr.end(), cmp);
    
    map<int, vector<int>> rs; 
    for(int i = m - 1; i >= 0; i--) rs[lr[i].second].pb(i);

    vector<bool> rem(m);
    int mx = -1; 
    for(auto& [u, v] : rs) {
        for(int i : v) {
            if(i < mx) rem[i] = true;
            else mx = i; 
        }
    }
    vector<pair<int, int>> temp;
    for(int i = 0; i < m; i++)
        if(!rem[i]) temp.pb(lr[i]);
    
    lr = temp;
    m = lr.size();

    map<int, int> lmp, rmp;
    for(int i = 0; i < m; i++) lmp[lr[i].first] = i, rmp[lr[i].second] = i;
    vector<int> p(m), p2(m);
    for(int i = 1; i < m - 1; i++) p[i + 1] = p[i] + (lr[i - 1].second >= lr[i + 1].first);
    for(int i = 0; i < m - 1; i++) p2[i + 1] = p2[i] + (lr[i].second < lr[i + 1].first);
    
    for(int i = 0; i < q; i++) {
        int l, r; rd(l, r);
        if(lmp.find(l) != lmp.end() && rmp.find(r) != rmp.end()) {
            if(rmp[r] < lmp[l]) cout << 0 << endl;
            else if(lmp[l] == rmp[r]) {
                cout << 998244352 << endl;
            } else {
                if(p[rmp[r]] - p[lmp[l] + 1] > 0 || p2[rmp[r]] - p2[lmp[l]] > 0) {
                    cout << 0 << endl;
                } else {
                    cout << (((rmp[r] - lmp[l]) % 2) ? 1 : 998244352) << endl;
                }
            }
        } else {
            cout << 0 << endl;
        }
    }
}