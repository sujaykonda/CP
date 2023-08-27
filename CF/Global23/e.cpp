#include <cplib/general.h>
using namespace std;

const int MXLG = 16, MX = 1e5, INF = 1e9, MXDP = 100;
vector<vector<pair<int, pair<int, int>>>> dp;

void dpcompute() {
    dp.resize(MXDP, vector<pair<int, pair<int, int>>>(MXDP, {INF, {0, 0}}));
    for(int i = 0; i <= 2; i++)
        for(int j = 0; j <= i; j++) 
            dp[i][j] = {0, {0, 0}};
    
    for(int i = 0; i < MXDP; i++) {
        for(int j = 0; j <= i; j++) {
            for(int a = 0; a <= j; a++) {
                for(int b = 0; b <= i - j; b++) {
                    dp[i][j] = min(dp[i][j], {max(dp[j + b][a + b].first, dp[i - b][i - a - b].first) + 1, {a, b}});
                }
            }
        }
    }
}

pair<vector<int>, vector<int>> dpq(vector<int> poss1, vector<int> poss2) {
    int A = poss1.size(), B = poss2.size();
    int a, b;
    if(A + B < MXDP) {
        a = dp[A + B][A].second.first, b = dp[A + B][A].second.second;
    } else {
        a = A / 2, b = B / 2;
    }
    cout << "? " << a + b;
    for(int i = 0; i < a; i++) cout << " " << poss1[i];
    for(int i = 0; i < b; i++) cout << " " << poss2[i];
    cout << endl;
    string s; rd(s);
    vector<int> nposs1, nposs2;
    if(s == "YES") {
        for(int i = 0; i < a; i++) nposs1.pb(poss1[i]);
        for(int i = 0; i < b; i++) nposs1.pb(poss2[i]);
        for(int i = a; i < A; i++) nposs2.pb(poss1[i]);
    } else {
        for(int i = a; i < A; i++) nposs1.pb(poss1[i]);
        for(int i = b; i < B; i++) nposs1.pb(poss2[i]);
        for(int i = 0; i < a; i++) nposs2.pb(poss1[i]);
    }
    return {nposs1, nposs2};
}

int main() {
    int n; rd(n);
    dpcompute();
    vector<int> poss;
    for(int i = 1; i <= n; i++) poss.pb(i);
    vector<int> poss2{};
    while(poss.size() + poss2.size() > 2) {
        pair<vector<int>, vector<int>> res = dpq(poss, poss2);
        poss = res.first, poss2 = res.second;
    }
    for(int p : poss2) poss.pb(p);
    cout << "! " << poss[0] << endl;
    string s; rd(s);
    if(s == ":(") {
        cout << "! " << poss[1] << endl;
        string a; rd(a);
    }
}