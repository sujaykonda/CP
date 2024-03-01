#include <bits/stdc++.h>
using namespace std;

const int MX = 1 << 20;

struct node {
    int v = 0;
    vector<int> upd;
    node* left;
    node* right;
    node() { left = right = 0; v = 0; }
    void add(int k) {
        v++;
        upd.push_back(k);
    }
    void push(int lb, int rb) {
        int m = (lb + rb) / 2;
        for(int k : exchange(upd, {})) {
            if(k <= m) {
                if(!left) left = new node();
                left->add(k);
            } else {
                if(!right) right = new node();
                right->add(k);
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n; cin >> n;
    vector<int> mu(MX + 1, 1);
    vector<bool> prime(MX + 1, true);
    for(int i = 2; i <= MX; i++) {
        if(prime[i]) {
            for(int j = i; j <= MX; j += i)
                mu[j] *= -1, prime[j] = false;
        }
    }
    for(int i = 2; i * i <= MX; i++) {
        for(int j = i * i; j <= MX; j += i * i)
            mu[j] = 0;
    }
    vector<vector<int>> div(MX + 1);
    for(int i = 1; i <= MX; i++) {
        if(mu[i] != 0) {
            for(int j = i; j <= MX; j += i) div[j].push_back(i);
        }
    }
    int ans = 0;
    vector<bool> added(MX + 1);
    vector<node*> segts(MX + 1);
    node* empty = new node();
    for(int i = 1; i <= MX; i++) segts[i] = new node();
    for(int i = 0; i < n; i++) {
        int t, x; cin >> t >> x;
        if(t == 1) {
            if(!added[x]) {
                added[x] = true;
                for(int u : div[x]) {
                    segts[u]->add(x);
                }
            }
        } else {
            // zero check
            int sm = 0;
            for(int j = 0; j < div[x].size(); j++) {
                sm += mu[div[x][j]] * segts[div[x][j]]->v;
            }
            if(sm != 0) {
                vector<node*> cur(div[x].size());
                for(int j = 0; j < div[x].size(); j++) {
                    cur[j] = segts[div[x][j]];
                }
                int l = 1, r = MX;
                while(l != r) {
                    int rsm = 0;
                    for(int j = 0; j < div[x].size(); j++) {
                        if(cur[j] != empty) {
                            cur[j]->push(l, r);
                            if(cur[j]->right) {
                                rsm += mu[div[x][j]] * cur[j]->right->v;
                            }
                        }
                    }
                    int m = (l + r) / 2;
                    if(rsm == 0) {
                        r = m;
                        for(int j = 0; j < div[x].size(); j++) {
                            if(!cur[j]->left) cur[j] = empty;
                            else cur[j] = cur[j]->left;
                        }
                    } else {
                        l = m + 1;
                        for(int j = 0; j < div[x].size(); j++) {
                            if(!cur[j]->right) cur[j] = empty;
                            else cur[j] = cur[j]->right;
                        }
                    }
                }
                ans ^= l;
            }
        }
    }
    cout << ans << endl;
}