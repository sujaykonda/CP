#include <cplib/ds/rurq.h>
using namespace std;

struct LZ { ll set, add; };
struct U { ll set, add; };
typedef _node<ll, LZ, U> node;
void apply(U u, node* n) {
    if(u.set == 0) {
        n->d += u.add * (n->rb - n->lb + 1);
        if(n->lz.set == 0) {
            n->lz.add += u.add;
        } else {
            n->lz.set += u.add;
        }
    } else {
        n->d = u.set * (n->rb - n->lb + 1);
        n->lz.add = 0;
        n->lz.set = u.set;
    }
}
void push(node* n) {
    if(n->lz.set != 0) {
        n->left->d = (n->left->rb - n->left->lb + 1) * n->lz.set;
        n->right->d = (n->right->rb - n->right->lb + 1) * n->lz.set;
        n->left->lz.set = n->right->lz.set = n->lz.set;
        n->left->lz.add = n->right->lz.add = 0;
        n->lz.set = 0;
    }
    else {
        n->left->d += (n->left->rb - n->left->lb + 1) * n->lz.add;
        n->right->d += (n->right->rb - n->right->lb + 1) * n->lz.add;
        if(n->left->lz.set != 0) n->left->lz.set += n->lz.add;
        else n->left->lz.add += n->lz.add;
        if(n->right->lz.set != 0) n->right->lz.set += n->lz.add;
        else n->right->lz.add += n->lz.add;
        n->lz.add = 0;
    }
}

int main() {
    int n, q; rd(n), rd(q);
    node* segt = new node(n - 1);
    for(int i = 0; i < n; i++) {
        int v; rd(v);
        segt->upd(U{v, 0}, i, i);
    }
    for(int i = 0; i < q; i++) {
        int t, a, b; rd(t), rd(a), rd(b);
        a--, b--;
        if(t == 3)
            cout << segt->query(a, b) << endl;
        else {
            int x; rd(x);
            if(t == 1)
                segt->upd(U{0, x}, a, b);
            else
                segt->upd(U{x, 0}, a, b);
        }
    }
}