#include <cplib/general.h>
using namespace std;

struct BIT {
    vector<int> tree;
    BIT(int n) { tree = vector<int>(n + 1); }
    int mx(int k) { int s = 0; while(k >= 1) s = max(s, tree[k]), k -= k&-k; return s; }
    void add(int k, int x) { while (k < (int)tree.size()) tree[k] = max(tree[k], x), k += k&-k; }
};

void tc() {
    int n; rd(n);
    vector<int> p(n); rd(p);
    BIT bit(n);
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        int v = bit.mx(p[i]) + 1;
        bit.add(p[i], v);
        if(v == 2) {
            cnt++;
        }
    }
    cout << cnt << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}