#include <bits/stdc++.h>
using namespace std;
const int MXN = 100001;
const int MXLG = 19;
int l[MXN], r[MXN];
int ljmp[MXN][MXLG], rjmp[MXN][MXLG];
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int N, K; cin >> N >> K;
    for(int i = 1; i <= N; i++) {
        cin >> l[i] >> r[i];
    }
    {
        map<int, vector<int>> eve;
        for(int i = 1; i <= N; i++) eve[l[i]].push_back(i), eve[r[i]].push_back(-i);
        multiset<pair<int, int>> rs;
        for(int i = 1; i <= N; i++) rs.insert({r[i], i});
        for(auto [u, v] : eve) {
            for(int i : v) {
                if(i < 0) {
                    rjmp[-i][0] = (rs.size() > 0) ? (*rs.begin()).second : 0;
                }
            }
            for(int i : v) {
                if(i > 0) {
                    rs.erase(rs.find({r[i], i}));
                }
            }
        }
    }
    {
        map<int, vector<int>> eve;
        for(int i = 1; i <= N; i++) eve[-l[i]].push_back(-i), eve[-r[i]].push_back(i);
        multiset<pair<int, int>> ls;
        for(int i = 1; i <= N; i++) ls.insert({l[i], i});
        for(auto [u, v] : eve) {
            for(int i : v) {
                if(i < 0) {
                    ljmp[-i][0] = (ls.size() > 0) ? (*ls.rbegin()).second : 0;
                }
            }
            for(int i : v) {
                if(i > 0) {
                    ls.erase(ls.find({l[i], i}));
                }
            }
        }
    }
    for(int i = 0; i < MXLG - 1; i++) {
        for(int j = 1; j <= N; j++) {
            ljmp[j][i + 1] = ljmp[ljmp[j][i]][i];
            rjmp[j][i + 1] = rjmp[rjmp[j][i]][i];
        }
    }
    vector<int> ans;
    set<pair<int, int>> ls, rs;
    ls.insert({0, N});
    rs.insert({0, N});
    ls.insert({1e9+1, N});
    rs.insert({1e9+1, N});
    int curv = N;
    for(int i = 1; i <= N; i++) {
        auto [lb, pv1] = *prev(rs.upper_bound({r[i], N}));
        auto [rb, pv2] = *ls.lower_bound({l[i], 0});
        auto [firstr, _] = *rs.upper_bound({l[i], N});
        auto [firstl, _2] = *ls.upper_bound({l[i], N});
        if(l[i] < lb || rb < r[i] || firstr < firstl) {
            continue;
        }
        int lv = 0, rv = 0;
        int li = i, ri = i;
        for(int j = MXLG - 1; j >= 0; j--) {
            if(ljmp[li][j] != 0 && lb <= l[ljmp[li][j]]) {
                li = ljmp[li][j];
                lv += 1 << j;
            }
            if(rjmp[ri][j] != 0 && r[rjmp[ri][j]] <= rb) {
                ri = rjmp[ri][j];
                rv += 1 << j;
            }
        }
        if(curv - min(pv1, pv2) + lv + rv + 1 >= K) {
            ans.push_back(i);
            curv = curv - min(pv1, pv2) + lv + rv + 1;
            ls.insert({l[i], lv});
            rs.insert({r[i], rv});
        }
        if(ans.size() == K) break;
    }
    if(ans.size() == 0) cout << "-1\n";
    else {
        for(int i : ans) cout << i << "\n";    
    }
}