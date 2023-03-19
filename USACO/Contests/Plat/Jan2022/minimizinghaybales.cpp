#include <bits/stdc++.h>
using namespace std;
#define pb emplace_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
using ll = long long;
typedef pair<ll, ll> pi;
typedef vector<ll> vi;
typedef vector<pi> vpi;

void setio(string name = "") { 
    ios::sync_with_stdio(false), cin.tie(nullptr); 
    if(name.length()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}
istream& operator>>(istream& is, vi& a) { for(ll& v : a) is >> v; return is; }
ostream& operator<<(ostream& os, vi& a) { for(ll v : a) os << v << " "; return os; }
vi& operator--(vi& a) { for(ll& v : a) v--; return a;}
vi range(int s, int e) { vi r(e - s); for(int i = s; i < e; i++) r[i - s] = i; return r; }
vi range(int e) { return range(0, e); }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }

int N, K;
struct Block {
    vi v;
    int mn = 1000000001, mx = 0;
    Block() {}
    Block(vi& v_) : v(v_) {
        for(int h : v) mn = min(mn, h), mx = max(mx, h);
    }
    bool passable(int h) {
        return h - K <= mn && mx <= h + K;
    }
    bool badinsert(int h) {
        for(int i = v.size() - 1; i >= 0; i--) {
            if(h - K > v[i] || h + K < v[i]) return true;
            if(v[i] > h) return false;
        }
        return true;
    }
    void insert(int h) {
        mn = min(mn, h), mx = max(mx, h);
        v.push_back(h);
        int j = v.size() - 1;
        while(j > 0 && h - K <= v[j - 1] && v[j - 1] <= h + K) j--;
        while(j < v.size() - 1 && v[j] <= h) j++;
        rotate(v.begin() + j, v.end() - 1, v.end());
    }
};

int main() {
    setio();
    cin >> N >> K;
    vector<Block> blocks;
    blocks.pb();
    for(int i = 0; i < N; i++) {
        int h;
        cin >> h;
        int j = blocks.size() - 1;
        while(j > 0 && blocks[j].passable(h)) j--;
        if(j < blocks.size() - 1 && blocks[j].badinsert(h)) j++;
        while(j < blocks.size() - 1 && blocks[j].mx <= h) j++;
        blocks[j].insert(h);
        if(blocks[j].v.size() * blocks[j].v.size() > N) {
            const int mid = ((int) blocks[j].v.size()) / 2;
            vi l(blocks[j].v.begin(), blocks[j].v.begin() + mid);
            vi r(blocks[j].v.begin() + mid, blocks[j].v.end());
            blocks[j] = Block(r);
            blocks.insert(blocks.begin() + j, Block(l));
        }
    }
    for(Block& b : blocks)
        for(int j : b.v)
            cout << j << "\n";
}