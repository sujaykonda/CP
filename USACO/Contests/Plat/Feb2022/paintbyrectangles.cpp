#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Data {
    int lp, rp, lc, rc;
    array<ll, 2> cnt;
    int invcnt;
};

int main() {
    int N, T; cin >> N >> T;
    int SZ = 2 * N;
    vector<Data> d(4 * SZ + 1);

    array<ll, 2> cnt{1, 0};
    vector<int> p(1, -1);
    vector<Data> init(SZ + 2);
    for(int i = 0; i <= SZ + 1; i++) {
        init[i].lp = 0, init[i].rp = 0;
        init[i].lc = 0, init[i].rc = 0;
        init[i].cnt[0] = 1, init[i].cnt[1] = 0;
        init[i].invcnt = 0;
    }

    auto getp = [&] (int a, auto&& getp) {
        if(p[a] < 0) return a;
        else return p[a] = getp(p[a], getp);
    };
    auto merge = [&] (int a, int b) {
        a = getp(a, getp), b = getp(b, getp);
        if(a == b) return false;
        if(p[a] > p[b]) swap(a, b);
        p[a] += p[b], p[b] = a; 
        return true;
    };
    auto pull = [&] (int s) {
        d[s].lc = d[2 * s].lc;
        d[s].lp = d[2 * s].lp;
        d[s].rc = d[2 * s + 1].rc;
        d[s].rp = d[2 * s + 1].rp;
        d[s].cnt[0] = d[2 * s].cnt[0] + d[2 * s + 1].cnt[0];
        d[s].cnt[1] = d[2 * s].cnt[1] + d[2 * s + 1].cnt[1];
        if(d[2 * s].rc == d[2 * s + 1].lc) {
            d[s].cnt[d[2 * s].rc]--;
            if(merge(d[2 * s].rp, d[2 * s + 1].lp))
                cnt[d[2 * s].rc]--;
        }
    };
    auto isone = [&] (int s) {
        return (d[s].cnt[0] + d[s].cnt[1] == 1);
    };
    auto push = [&] (int s) {
        if(d[s].invcnt == 0) return;
        d[2 * s].invcnt += d[s].invcnt;
        d[2 * s + 1].invcnt += d[s].invcnt;
        if(d[s].invcnt % 2) {
            swap(d[2 * s].cnt[0], d[2 * s].cnt[1]);
            d[2 * s].lc ^= 1, d[2 * s].rc ^= 1;
            swap(d[2 * s + 1].cnt[0], d[2 * s + 1].cnt[1]);
            d[2 * s + 1].lc ^= 1, d[2 * s + 1].rc ^= 1;
        }
        d[2 * s].lp = d[s].lp;
        if(isone(2 * s)) d[2 * s].rp = d[2 * s].lp;
        else d[2 * s].rp = p.size(), p.push_back(-1);
        d[2 * s + 1].rp = d[s].rp;
        if(isone(2 * s + 1)) d[2 * s + 1].lp = d[2 * s + 1].rp;
        else d[2 * s + 1].lp = p.size(), p.push_back(-1);
        if(d[2 * s].rc == d[2 * s + 1].lc) 
            merge(d[2 * s].rp, d[2 * s + 1].lp);
        d[s].invcnt = 0;
    };
    auto inv = [&] (int l, int r, int s, int lb, int rb, auto&& inv) {
        l = max(l, lb), r = min(r, rb);
        if(l > r) return;
        if(l == lb && r == rb) {
            d[s].lc ^= 1, d[s].rc ^= 1;
            swap(d[s].cnt[0], d[s].cnt[1]);
            cnt[0] += d[s].cnt[0];
            cnt[1] += d[s].cnt[1];
            d[s].invcnt++;
            d[s].lp = p.size(); p.push_back(-1);
            if(isone(s)) d[s].rp = d[s].lp;
            else d[s].rp = p.size(), p.push_back(-1);
            return;
        }
        int m = (lb + rb) / 2;
        push(s);
        inv(l, r, 2 * s, lb, m, inv);
        inv(l, r, 2 * s + 1, m + 1, rb, inv);
        pull(s);
    };
    auto build = [&] (int s, int lb, int rb, auto&& build) {
        if(lb == rb) {
            d[s] = init[lb];
            return;
        }
        int m = (lb + rb) / 2;
        build(2 * s, lb, m, build);
        build(2 * s + 1, m + 1, rb, build);
        pull(s);
    };
    auto print = [&] (int s, int lb, int rb, auto&& print) {
        //cout << s << " " << lb << " " << rb << ": ";
        //cout << d[s].lc << " " << d[s].rc << " " << d[s].cnt[0] << " " << d[s].cnt[1] << endl;
        if(lb == rb) {
            //cout << d[s].lc << " ";
            return;
        }
        push(s);
        int m = (lb + rb) / 2;
        print(2 * s, lb, m, print);
        print(2 * s + 1, m + 1, rb, print);
        pull(s);
    };
    build(1, 0, SZ + 1, build);

    vector<pair<int, int>> flip(SZ);
    for(int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1, y1--, x2--, y2--;
        flip[y1] = flip[y2] = {x1, x2};
    }
    array<ll, 2> last;
    for(int i = 0; i < SZ; i++) {
        //cout << flip[i].first << " " << flip[i].second << endl << endl;
        last = cnt;
        inv(flip[i].first, flip[i].second, 1, 0, SZ + 1, inv);
        //cout << "PRINT" << endl;
        //print(1, 0, SZ + 1, print);
        //cout << endl;
        //cout << cnt[0] << " " << cnt[1] << endl;
        //cout << endl;
    }
    if(T == 1) {
        cout << cnt[0] + cnt[1] << endl;
    } else {
        cout << cnt[0] << " " << cnt[1] << endl;
    }
}