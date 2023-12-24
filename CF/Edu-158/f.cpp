#include <cplib/general.h>
#include <cplib/math/geo.h>
#include <cplib/bs.h>
using namespace std;

P qmax(P p, vector<P>& hull, bool rev) {
    return hull[bsmax(0, hull.size() - 1, [&] (int x) { return x == 0 || ((cross(hull[x] - p, hull[x - 1] - p) <= 0) != rev); })];
}

int main() {
    cout << setprecision(15);
    int n; rd(n);
    vector<int> a(n); rd(a);
    vector<int> b(n); rd(b);
    vector<P> hf2;
    for(int i = (n + 1) / 2; i < n; i++) hf2.pb({i, a[i]});
    vector<P> hf2hull = convHull(hf2);
    multiset<double> hf1poss;
    vector<double> hf1cur(n);
    if(n % 2 == 1) {
        hf1poss.insert(a[n / 2] * 2);
    }
    for(int i = 0; i < n / 2; i++) {
        P mx = qmax({i, a[i]}, hf2hull, false);
        hf1cur[i] = (((double)mx.second - a[i]) / ((double)mx.first - i) * ((n - 1) / 2.0 - i) + a[i]) * 2;
        hf1poss.insert(hf1cur[i]);
    }
    for(int i = 0; i < n / 2; i++) {
        P mx = qmax({i, b[i]}, hf2hull, false);
        hf1poss.erase(hf1poss.find(hf1cur[i]));
        hf1cur[i] = (((double)mx.second - b[i]) / ((double)mx.first - i) * ((n - 1) / 2.0 - i) + b[i]) * 2;
        hf1poss.insert(hf1cur[i]);
        cout << (*hf1poss.rbegin()) << " ";
    }
    if(n % 2 == 1) {
        hf1poss.erase(hf1poss.find(a[n / 2] * 2));
        hf1poss.insert(b[n / 2] * 2);
        cout << (*hf1poss.rbegin()) << " ";
    }
    vector<P> hf1;
    for(int i = 0; i < n / 2; i++) hf1.pb({i, b[i]});
    vector<P> hf1hull = convHull(hf1);
    multiset<double> hf2poss;
    vector<double> hf2cur(n);
    if(n % 2 == 1) {
        hf2poss.insert(b[n / 2] * 2);
    }
    for(int i = (n + 1) / 2; i < n; i++) {
        P mx = qmax({i, a[i]}, hf1hull, true);
        hf2cur[i] = (((double)mx.second - a[i]) / ((double)mx.first - i) * ((n - 1) / 2.0 - i) + a[i]) * 2;
        hf2poss.insert(hf2cur[i]);
    }
    for(int i = (n + 1) / 2; i < n; i++) {
        P mx = qmax({i, b[i]}, hf1hull, true);
        hf2poss.erase(hf2poss.find(hf2cur[i]));
        hf2cur[i] = (((double)mx.second - b[i]) / ((double)mx.first - i) * ((n - 1) / 2.0 - i) + b[i]) * 2;
        hf2poss.insert(hf2cur[i]);
        cout << (*hf2poss.rbegin()) << " ";
    }
    cout << endl;
}