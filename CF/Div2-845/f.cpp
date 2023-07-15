#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/ds/sparse/segt.h>
using namespace std;

typedef _node_segt<int> node;

void dest(node* n) {
    if(n->left) dest(n->left);
    if(n->right) dest(n->right);
    delete(n);
}

int solve(vector<int> a) {
    int n = a.size();
    int mx = 0;
    for(int k = 1; k < n; k++) {
        node* segt = new node((1 << 30) - 1);
        int r = k&-k;
        int imx = 0, j = k - 1, curi = 0, curj = 0;
        segt->upd(0, 1);
        for(int i = k; i < k + r && i < n; i++) {
            curi ^= a[i];
            if(a[i] > imx) {
                imx = a[i];
                while(j >= k - r && a[j] <= imx)
                    curj ^= a[j--], segt->upd(curj, 1);
            }
            node* s = segt;
            int v = curi ^ imx;
            for(int i = 29; i >= 0; i--) {
                if(getbit(v, i)) {
                    if(s->left && s->left->val) s = s->left;
                    else s = s->right;
                } else {
                    if(s->right && s->right->val) s = s->right;
                    else s = s->left;
                }
            }
            mx = max(mx, s->lb ^ v);
        }
        dest(segt);
    }
    return mx;
}

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    int k; for(k = 1; k < n; k *= 2);
    a.resize(k);
    int mx = solve(a);
    reverse(a.begin(), a.end());
    mx = max(mx, solve(a));
    cout << mx << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}