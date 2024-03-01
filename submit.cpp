#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define getbit(msk, i) ((msk & (1LL << i)) > 0)

int getpar(ll n) {
	int parity = 0;
	for(int i = 0; i < 63; i++) parity ^= getbit(n, i);
	return parity;
}

void split(ll n) {
    int hb = 0;
    for(int i = 63; i >= 0; i--) {
        if(getbit(n, i)) {
            hb = i;
            break;
        }
    }
    cout << (n ^ (1LL << hb)) << " " << (1LL << hb) << endl;
}

void tc() {
	ll n; cin >> n;
	if(getpar(n)) {
		cout << "second" << endl;
        while(true) {
            ll p1, p2; cin >> p1 >> p2;
            if(p1 == 0 && p2 == 0) return;
            if(getpar(p1)) {
                split(p2);
            } else {
                split(p1);
            }
        }
	} else {
		cout << "first" << endl;
        split(n);
        while(true) {
            ll p1, p2; cin >> p1 >> p2;
            if(p1 == 0 && p2 == 0) return;
            if(getpar(p1)) {
                split(p2);
            } else {
                split(p1);
            }
        }
	}

}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);
	int t; cin >> t;
	while(t--) tc();
}
