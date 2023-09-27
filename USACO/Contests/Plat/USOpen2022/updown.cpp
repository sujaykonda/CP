#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<int> p(N);
    for(int i = 0; i < N; i++) cin >> p[i];

    int cur = 0;
    vector<int> dp;
    auto insert = [&] (int i, int pos) {
        if (pos == dp.size()) dp.push_back(i), cur++;
		else dp[pos] = i;
    };
    auto insertLIS = [&] (int i) {
		int pos = lower_bound(dp.begin(), dp.end(), i) - dp.begin();
        insert(i, pos);
    };
    auto insertLDS = [&] (int i) {
		int pos = lower_bound(dp.begin(), dp.end(), i, [&] (int a, int b) { return b < a; }) - dp.begin();
        insert(i, pos);
    };
    string s; cin >> s;
    vector<int> seq; seq.push_back(1);
    for(int i = 1; i < N - 1; i++) {
        if(s[i] == s[i - 1]) seq.back()++;
        else seq.push_back(1);
    }
    bool lis = s[0] == 'U';
    dp.push_back(p[0]);
    int i = 1;
    for(int v : seq) {
        int need = v + cur;
        while(i < N && cur < need) {
            if(lis) {
                insertLIS(p[i]);
            } else {
                insertLDS(p[i]);
            }
            i++;
        }
        if(cur < need) break;
        dp.clear();
        dp.push_back(p[i - 1]);
        lis = !lis;
    }
    cout << cur << endl;
}