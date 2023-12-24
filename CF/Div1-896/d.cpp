#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> d(n); rd(d);
    ll sm = 0;
    for(int i : d) sm += i;
    if(sm != 2 * n) {
        cout << "NO" << '\n';
        return;
    }
    vector<int> o(n);
    for(int i = 0; i < n; i++) o[i] = i;
    sort(o.begin(), o.end(), [&] (int a, int b) { return d[a] < d[b]; });
    if(d[o.back()] == 2) {
        cout << "YES" << '\n';
        for(int i = 0; i < n; i++) {
            cout << i + 1 << " " << (i + 1) % n + 1 << '\n';
        }
    } else {
        if(d[o.back()] == 3){
            vector<int> ones, twos, threes;
            for(int i = 0; i < n; i++) {
                if(d[o[i]] == 1) ones.pb(o[i]);
                else if(d[o[i]] == 2) twos.pb(o[i]);
                else threes.pb(o[i]);
            }
            if(threes.size() == 1) {
                cout << "NO" << '\n';
                return;
            }
            if(threes.size() == 2 && twos.size() % 2 == 1) {
                cout << "NO" << '\n';
                return;
            }
            if(threes.size() == 3 && twos.size() == 2) {
                cout << "NO" << '\n';
                return;
            }
            if(threes.size() == 4 && twos.size() == 1) {
                cout << "NO" << '\n';
                return;
            }
            if(twos.size() == 0) {
                cout << "YES" << '\n';
                for(int i = 0; i < threes.size(); i++) {
                    cout << threes[i] + 1 << " " << threes[(i + 1) % threes.size()] + 1 << '\n';
                    cout << threes[i] + 1 << " " << ones[i] + 1 << '\n';
                }
                return;
            }
            cout << "YES" << '\n';
            int left = threes.back();
            threes.pop_back();
            int right = threes.back();
            threes.pop_back();
            cout << left + 1 << " " << right + 1 << '\n';
            cout << right + 1 << " " << left + 1 << '\n';

            int b = 0;
            if((threes.size() + twos.size()) % 2 == 1) {
                cout << left + 1 << " " << threes.back() + 1 << '\n';
                left = threes.back();
                threes.pop_back();
                cout << left + 1 << " " << twos.back() + 1 << '\n';
                cout << twos.back() + 1 << " " << ones.back() + 1 << '\n';
                twos.pop_back();
                ones.pop_back();
                b = 1;
            }

            while(threes.size() > 0) {
                if(b) {
                    cout << right + 1 << " " << threes.back() + 1 << '\n';
                    right = threes.back();
                    cout << right + 1 << " " << ones.back() + 1 << '\n';
                } else {
                    cout << left + 1 << " " << threes.back() + 1 << '\n';
                    left = threes.back();
                    cout << left + 1 << " " << ones.back() + 1 << '\n';
                }
                threes.pop_back();
                ones.pop_back();
                b ^= 1;
            }
            while(twos.size() > 0) {
                if(b) {
                    cout << right + 1 << " " << twos.back() + 1 << '\n';
                    right = twos.back();
                } else {
                    cout << left + 1 << " " << twos.back() + 1 << '\n';
                    left = twos.back();
                }
                twos.pop_back();
                b ^= 1;
            }
            cout << right + 1 << " " << ones.back() + 1 << '\n';
            ones.pop_back();
            cout << left + 1 << " " << ones.back() + 1 << '\n';
            ones.pop_back();
        } else {
            int othersm = 0;
            vector<int> ones, twos, other;
            for(int i = 0; i < n - 1; i++) {
                if(d[o[i]] == 1) ones.pb(o[i]);
                else if(d[o[i]] == 2) twos.pb(o[i]);
                else {
                    int k = n - i;
                    int m = (twos.size() + ones.size() + othersm - 1) / ones.size();
                    if((m * k - other.size() <= twos.size())) {
                        cout << "YES" << '\n';
                        vector<int> good, bad;
                        int need = m * k - other.size();
                        for(int j : other) {
                            for(int l = 0; l < d[j] - 1; l++) {
                                int last = ones.back();
                                ones.pop_back();
                                int c = m - 1;
                                while(c-- && twos.size() > (l == 0 ? need : --need)) {
                                    cout << twos.back() + 1 << " " << last + 1 << '\n';
                                    last = twos.back();
                                    twos.pop_back();
                                }
                                cout << last + 1 << " " << j + 1 << '\n';
                            }
                            good.pb(j);
                        }
                        for(int j : ones) {
                            int last = j;
                            int c = min(m, (int)twos.size());
                            while(c--) {
                                cout << twos.back() + 1 << " " << last + 1 << '\n';
                                last = twos.back();
                                twos.pop_back();
                            }
                            if(good.size() < n - i) good.push_back(last);
                            else bad.push_back(last);
                        }
                        vector<int> cyc;
                        for(int j = i; j < n; j++) cyc.pb(o[j]);
                        for(int j = 0; j < cyc.size(); j++) {
                            cout << cyc[j] + 1 << " " << cyc[(j + 1) % cyc.size()] + 1 << '\n';
                            cout << cyc[j] + 1 << " " << good.back() + 1 << '\n';
                            good.pop_back();
                            int c = d[cyc[j]] - 3;
                            while(c--) {
                                cout << cyc[j] + 1 << " " << bad.back() + 1 << '\n';
                                bad.pop_back();
                            }
                        }
                        return;
                    }
                    other.pb(o[i]);
                    othersm += d[o[i]] - 1;
                }
            }
            cout << "NO" << '\n';
        }
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}