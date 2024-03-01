#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MXN = 2e5 + 1;
const int MX = 2e5 + 1;

struct node {
	ll v;
	node *left, *right;
	node() { v = 0, left = right = 0; }
    void print(int lb, int rb) {
        if(lb == rb) cout << lb << ":" << v << " ";
        else {
            int m = (lb + rb) / 2;
            if(left) left->print(lb, m);
            if(right) right->print(m + 1, rb); 
        }
    }
    ll del(ll rem, int r, int lb, int rb) {
        r = min(r, rb);
        if(r < lb) return 0;
        if(rb == r && v <= rem) {
            ll d = v;
            v -= d;
            left = right = 0;
            return d;
        }
        if(rb == r && lb == rb) {
            v -= rem;
            return rem;
        }
        int m = (lb + rb) / 2;
        ll d = right ? right->del(rem, r, m + 1, rb) : 0;
        if(rem - d > 0) {
            d += left ? left->del(rem - d, r, lb, m) : 0;
        }
        v -= d;
        return d;
    }
};
void upd(node* cur, int k, ll v) {
	int lb = 1, rb = MX;
	while(lb != rb) {
		cur->v += v;
		int m = (lb + rb) / 2;
		if(k <= m) {
			if(!cur->left) cur->left = new node();
			cur = cur->left;
			rb = m;
		} else {
			if(!cur->right) cur->right = new node();
			cur = cur->right;
			lb = m + 1;
		}
	}
	cur->v += v;
}
ll query(node* cur, int k) {
    ll ans = 0;
    int lb = 1, rb = MX;
    while(lb != rb) {
        int m = (lb + rb) / 2;
        if(k <= m) {
            if(cur->right) ans += cur->right->v;
            if(!cur->left) return ans;
            cur = cur->left;
            rb = m;
        } else {
            if(!cur->right) return ans;
            cur = cur->right;
            lb = m + 1;
        }
    }
    return ans + cur->v;
}
void merge(node* cur, node* other) {
    other->v += cur->v;
    if(cur->left) {
        if(other->left) {
            merge(cur->left, other->left);
        } else {
            other->left = cur->left;
        }
    }
    if(cur->right) {
        if(other->right) {
            merge(cur->right, other->right);
        } else {
            other->right = cur->right;
        }
    }
    delete(cur);
}

int A[MXN], H[MXN], C[MXN], in[MXN];
node *segts[MXN];
int main() {
	int N; cin >> N;
    ll sm = 0;
    map<int, vector<int>> mp;
    for(int i = 1; i <= N; i++) {
        cin >> A[i] >> H[i] >> C[i];
        mp[H[i]].push_back(i);
        in[A[i]]++;
        segts[i] = new node();
        sm += C[i];
    }
    int rnk = 1;
    for(auto [u, v] : mp) {
        for(int u2 : v) H[u2] = rnk;
        rnk++;
    }
    queue<int> q;
    for(int i = 1; i <= N; i++) if(in[i] == 0) q.push(i);
    while(!q.empty()) {
        int s = q.front();
        q.pop();
        // cout << s << endl;
        // segts[s]->print(1, MX);
        // cout << endl;
        segts[s]->del(C[s], H[s] - 1, 1, MX);
        upd(segts[s], H[s], C[s]);
        merge(segts[s], segts[A[s]]);
        if(--in[A[s]] == 0) q.push(A[s]);
    }
    for(int i = 1; i <= N; i++) {
        if(in[i] != 0) {
            // cout << i << endl;
            vector<int> cyc; cyc.push_back(i);
            while(in[A[cyc.back()]]) {
                in[A[cyc.back()]] = 0;
                cyc.push_back(A[cyc.back()]);
            }
            cyc.pop_back();
            map<int, ll> cnt;
            for(int u : cyc) {
                cnt[H[u]] += C[u];
                if(u != i) {
                    merge(segts[u], segts[i]);
                }
            }
            ll best = segts[i]->v;
            for(auto [u, v] : cnt) {
                best = max(best, v + query(segts[i], u));
            }
            sm -= best;
        }
    }
    cout << sm << endl;
}
