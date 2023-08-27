#include <cplib/math/mint.h>
using namespace std;
#define getbit(mask, i) ((mask & (1 << i)) > 0)
const int MOD = 998244353;

struct node {
    node *left, *right;
    int v;
    node() { v = 0, left = 0, right = 0; }
};

void tc() {
    map<int, int> cnt;
    int n; rd(n);
    for(int i = 0; i < n; i++) {
        int v; rd(v);
        cnt[v]++;
    }
    node* segt = new node();
    mint<MOD> ans;
    int donecnt = 0;
    for(auto [u, v] : cnt) {
        int bitcnt = 0;
        node* s = segt;
        ans += mint<MOD>(donecnt) * v * 3;
        for(int i = 29; i >= 0; i--) {
            if(getbit(u, i)) {
                bitcnt++;
                if(!s->right) s->right = new node();
                s = s->right;
                ans += mint<MOD>(s->v) * v * 2;
                s->v += v;
            } else {
                if(!s->left) s->left = new node();
                s = s->left;
            }
        }
        ans += mint<MOD>(bitcnt + 1) * v * v;
        donecnt += v;
    }
    cout << ((ans / n) / n).v << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}