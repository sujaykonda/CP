#include <cplib/general.h>
using namespace std;

bool valid() {
    int n; rd(n);
    vector<int> d(n); rd(d);
    vector<pair<int, int>> ll(n);
    for(int i = 0; i < n; i++) ll[i] = {i - 1, i + 1};
    priority_queue<pair<int, int>> pq;
    auto good = [&] (int i) {
        return (ll[i].first != -1 && (d[i] - d[ll[i].first]) == 1) || (ll[i].second != n && (d[i] - d[ll[i].second]) == 1);
    };
    vector<int> added(n);
    for(int i = 0; i < n; i++) {
        if(good(i)) {
            pq.push({d[i], i});
            added[i] = true;
        }
    }
    while(pq.size() > 0) {
        int i = pq.top().second;
        pq.pop();
        if(ll[i].first != -1) {
            ll[ll[i].first].second = ll[i].second;
            if(!added[ll[i].first] && good(ll[i].first)) {
                pq.push({d[ll[i].first], ll[i].first});
                added[ll[i].first] = true;
            }
        }
        if(ll[i].second != n) {
            ll[ll[i].second].first = ll[i].first;
            if(!added[ll[i].second] && good(ll[i].second)) {
                pq.push({d[ll[i].second], ll[i].second});
                added[ll[i].second] = true;
            }
        }
    }
    int left = 0, leftcnt = 0;
    for(int i = 0; i < n; i++) {
        leftcnt += !added[i];
        if(!added[i]) left = d[i];
    }
    return left == 0 && leftcnt == 1;
}

int main() {
    int t; rd(t);
    while(t--) {
        if(valid()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}