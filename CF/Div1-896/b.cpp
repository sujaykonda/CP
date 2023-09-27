#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    ll sm = 0;
    for(int i = 0; i < n; i++) sm += a[i];
    if(sm % n != 0) {
        cout << "NO" << endl;
        return;
    }
    int v = sm / n;
    bool good = true;
    vector<int> deg(31);
    vector<pair<int, int>> ch(31);
    for(int i = 0; i < n; i++) {
        int d = v - a[i];
        if(d == 0) continue;
        int absd = abs(d);
        int hb = lg(absd);
        int lb = lg(absd&-absd);
        if(absd != (1 << (hb + 1)) - (1 << lb)) good = false;
        if(d > 0) {
            deg[hb + 1]++;
            deg[lb]--;
            if(absd == (1 << hb))
                ch[hb + 1].first++;
        } else {
            deg[hb + 1]--;
            deg[lb]++;
            if(absd == (1 << hb))
                ch[hb + 1].second++;
        }
    }
    for(int i = 30; i > 0; i--) {
        if(deg[i] != 0) {
            if(deg[i] > 0) {
                if(ch[i].first < deg[i]) good = false;
            } else {
                if(ch[i].second < -deg[i]) good = false;
            }
            deg[i - 1] += 2 * deg[i];
            deg[i] = 0;
        }
    }
    for(int i = 0; i <= 30; i++) if(deg[i] != 0) good = false;
    if(!good) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}