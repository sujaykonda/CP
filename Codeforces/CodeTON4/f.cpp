#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T> string str(T a);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }

const int BLOCK_SIZE = 500;

struct Block {
    int m;
    int all;
    vector<int> cnt;
    Block(int m) : m(m), cnt(BLOCK_SIZE, 0) { all = 0; }
    bool add(int x) {
        if(x == 0 && all == m - 1) {
            all = 0;
            return true;
        }
        applyall();

        for(int i = x; i < BLOCK_SIZE; i++) {
            cnt[i] = (cnt[i] + 1) % m;
            //cout << "added: " << i << " " << cnt[i] << endl;
            if(cnt[i] != 0) { checkall(); return false; }
        }
        checkall(); 
        return true;

    }
    bool remove(int x) {
        if(x == 0 && all == 0) {
            all = m - 1;
            return true;
        }
        applyall();

        for(int i = x; i < BLOCK_SIZE; i++) {
            cnt[i] = (cnt[i] + m - 1) % m;
            //cout << "removed: " << i << " " << cnt[i] << endl;
            if(cnt[i] != m - 1) { checkall(); return false; }
        }
        checkall(); 
        return true;
    }
    void checkall() {
        if(all != -1) return;
        for(int i = 0; i < BLOCK_SIZE; i++)
            if(cnt[i] != cnt[0]) 
                return;
        all = cnt[0];
    }
    void applyall() {
        if(all == -1) return;
        for(int i = 0; i < BLOCK_SIZE; i++) 
            cnt[i] = all;
        all = -1;
    }
};

void testcase() {
    ll n, m, q; cin >> n >> m >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i]; 
    
    vector<Block> blocks(n / BLOCK_SIZE + 3, Block(m));
    for(int i = 0; i < n; i++) {
        int v = a[i] % BLOCK_SIZE;
        int j = a[i] / BLOCK_SIZE;
        while(blocks[j].add(v)) v = 0, j++;
    }
    for(int i = 0; i < q; i++) {
        int x, y; cin >> x >> y, x--;
        int v = a[x] % BLOCK_SIZE;
        int j = a[x] / BLOCK_SIZE;
        while(blocks[j].remove(v)) v = 0, j++;
        a[x] = y;
        v = a[x] % BLOCK_SIZE;
        j = a[x] / BLOCK_SIZE;
        while(blocks[j].add(v)) v = 0, j++;
        //for(int j = 0; j < blocks.size() - 2; j++)
        //    cout << str(blocks[j].cnt) << " " << blocks[j].all << endl;
        bool equal = true;
        int highest = -1;
        for(int j = 0; j < blocks.size(); j++)
            if(blocks[j].all != 0) {
                if(highest != -1) equal = false;
                highest = j;
            }
        blocks[highest].applyall();
        int highest2 = -1;
        for(int j = 0; j < BLOCK_SIZE; j++)
            if(blocks[highest].cnt[j] > 0){
                if(highest2 != -1) equal = false;
                highest2 = j;
            }
        cout << !equal + highest * BLOCK_SIZE + highest2 << " ";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}