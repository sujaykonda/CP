#include <cplib/bs.h>
using namespace std;

const int BSZ = 30;

struct node {
    node *left, *right; 
    int cnt, last;
    node() { left = right = NULL; cnt = 0, last = -1; }
};

int n; 
vector<int> a;
adjlist adj;
vector<int> color;
node* segt;

bool try_k(int k) {
    bool good = true;
    for(int i = 0; i < n; i++) {
        node* cur = segt;
        int fb = 1;
        for(int j = BSZ - 1; j >= 0; j--) {
            if(getbit(k, j)) {
                if(getbit(a[i], j)) {
                    if(cur->right) {
                        if(cur->right->cnt > 1 + fb) {
                            good = false;
                            break;
                        }
                        int u = cur->right->last;
                        if(u != -1 && u != i) {
                            adj[i].pb(u), adj[u].pb(i);
                        }
                    }
                    if(!cur->left) break;
                    cur = cur->left;
                } else {
                    if(cur->left) {
                        if(cur->left->cnt > 1 + fb) {
                            good = false;
                            break;
                        }
                        int u = cur->left->last;
                        if(u != -1 && u != i) {
                            adj[i].pb(u), adj[u].pb(i);
                        }
                    }
                    if(!cur->right) break;
                    cur = cur->right;
                }
                fb = 0;
            } else {
                if(getbit(a[i], j)) {
                    if(!cur->right) break;
                    cur = cur->right;
                } else {
                    if(!cur->left) break;
                    cur = cur->left;
                }
            }
        }
        if(!good) break;
    }
    if(!good) {
        for(int i = 0; i < n; i++) adj[i].clear();
        return false;
    }
    for(int i = 0; i < n; i++) color[i] = -1;
    function<void(int)> dfs = [&] (int s) {
        for(int u : adj[s]) {
            if(color[u] == -1) {
                color[u] = color[s] ^ 1;
                dfs(u);
            } else if(color[u] == color[s]) {
                good = false;
            }
        }
    };
    for(int i = 0; i < n; i++) {
        if(color[i] == -1) {
            color[i] = 0;
            dfs(i);
        }
    }
    for(int i = 0; i < n; i++) adj[i].clear();
    return good;
}

int main() {
    rd(n);
    a.resize(n);
    rd(a);
    if(n == 2) {
        cout << "01" << endl;
        return 0;
    }
    color.resize(n);
    adj.resize(n);
    segt = new node();
    for(int i = 0; i < n; i++) {
        node* cur = segt;
        cur->cnt++, cur->last = i;
        for(int j = BSZ - 1; j >= 0; j--) {
            if(getbit(a[i], j)) {
                if(!cur->right) cur->right = new node();
                cur = cur->right;
            } else {
                if(!cur->left) cur->left = new node();
                cur = cur->left;
            }
            cur->cnt++, cur->last = i;
        }
    }
    int k = bsmax(1, (1 << 30) - 1, try_k);
    try_k(k);
    for(int i = 0; i < n; i++) cout << color[i];
    cout << endl;
}