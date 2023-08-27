#include <cplib/general.h>
using namespace std;

const int HSHCNT = 3;
typedef array<ll, HSHCNT> hsh;

hsh operator^(hsh a, hsh b) { for(int i = 0; i < HSHCNT; i++)  a[i] ^= b[i]; return a; }

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    int n, k; rd(n, k);
    vector<vector<int>> j(k, vector<int>(n)); rd(j);
    for(vector<int>& vi : j) for(int& i : vi) i--;
    vector<int> p(n);
    vector<hsh> hshs(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < HSHCNT; j++)
            hshs[i][j] = uniform_int_distribution<ll>(0, (1LL << 60) - 1)(rng);
    }
    vector<vector<hsh>> phsh(k, vector<hsh>(n + 1));
    for(int i = 0; i < k; i++) {
        for(int z = 0; z < n; z++) {
            phsh[i][z + 1] = phsh[i][z] ^ hshs[j[i][z]];
        }
    }

    function<void(int, vector<pair<int, int>>)> solve = [&] (int e, vector<pair<int, int>> b) {
        if(b[0].first == b[0].second) {
            p[j[0][b[0].first]] = e;
            return;
        }
        vector<bool> poss(n);
        vector<pair<hsh, hsh>> lrhshes(n);
        for(int i = b[0].first; i <= b[0].second; i++) {
            lrhshes[j[0][i]].first = phsh[0][b[0].first] ^ phsh[0][i];
            lrhshes[j[0][i]].second = phsh[0][b[0].second + 1] ^ phsh[0][i + 1];
            poss[j[0][i]] = true;
        }
        for(int i = 0; i < k; i++) {
            for(int z = b[i].first; z <= b[i].second; z++) {
                pair<hsh, hsh> cur = {phsh[i][b[i].first] ^ phsh[i][z], phsh[i][b[i].second + 1] ^ phsh[i][z + 1]};
                pair<hsh, hsh> curswp = {cur.second, cur.first};
                if(lrhshes[j[i][z]] != cur && lrhshes[j[i][z]] != curswp) {
                    poss[j[i][z]] = false;
                }
            }
            poss[j[i][b[i].first]] = poss[j[i][b[i].second]] = false;
        }
        int s = -1;
        for(int i = 0; i < n; i++) if(poss[i]) s = i;
        assert(s != -1);
        p[s] = e;
        vector<pair<int, int>> b1(k), b2(k);
        for(int i = 0; i < k; i++) {
            int si = -1;
            for(int z = b[i].first; z <= b[i].second; z++) if(j[i][z] == s) si = z;
            assert(si != -1);
            pair<hsh, hsh> cur = {phsh[i][b[i].first] ^ phsh[i][si], phsh[i][b[i].second + 1] ^ phsh[i][si + 1]};
            if(lrhshes[s] == cur) {
                b1[i] = {b[i].first, si - 1};
                b2[i] = {si + 1, b[i].second};
            } else {
                b2[i] = {b[i].first, si - 1};
                b1[i] = {si + 1, b[i].second};
            }
        }
        solve(s, b1);
        solve(s, b2);
    };
    solve(-2, vector<pair<int, int>>(k, {0, n - 1}));
    for(int pi : p) cout << pi + 1 << " ";
    cout << endl;
}