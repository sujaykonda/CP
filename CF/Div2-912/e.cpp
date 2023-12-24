#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    int sx, sy; rd(sx, sy);
    vector<int> x(n), y(n);
    for(int i = 0; i < n; i++) cin >> x[i] >> y[i];
    set<int> even, odd;
    for(int i = 0; i < n; i++) {
        if((x[i] + y[i] + sx + sy) % 2 == 0) {
            even.insert(i);
        } else {
            odd.insert(i);
        }
    }
    if(even.size() >= odd.size()) {
        cout << "First" << endl;
        bool oddlast = false;
        for(int i = 0; i < n; i++) {
            if(i % 2 == 1) {
                int k; rd(k); k--;
                if(even.count(k)) {
                    even.erase(k);
                    oddlast = false;
                } else {
                    odd.erase(k);
                    oddlast = true;
                }
            } else {
                if((oddlast && even.size() > 0) || (odd.size() == 0)) {
                    cout << (*even.begin()) + 1 << endl;
                    even.erase(even.begin());
                } else {
                    cout << (*odd.begin()) + 1 << endl;
                    odd.erase(odd.begin());
                }
            }
        }
    } else {
        cout << "Second" << endl;
        bool oddlast = false;
        for(int i = 0; i < n; i++) {
            if(i % 2 == 0) {
                int k; rd(k); k--;
                if(even.count(k)) {
                    even.erase(k);
                    oddlast = false;
                } else {
                    odd.erase(k);
                    oddlast = true;
                }
            } else {
                if((oddlast && even.size() > 0) || (odd.size() == 0)) {
                    cout << (*even.begin()) + 1 << endl;
                    even.erase(even.begin());
                } else {
                    cout << (*odd.begin()) + 1 << endl;
                    odd.erase(odd.begin());
                }
            }
        }
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}