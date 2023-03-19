#include <bits/stdc++.h>
using namespace std;

#define lgN 18
int N, Q;
vector<int> l, r, sp_pre;
vector<vector<int>> ljmp, rjmp, lv, rv;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr); 
	cin >> N >> Q;
	l.resize(N), r.resize(N);
	string eps;
	cin >> eps;
	int li = 0, ri = 0;
	for(int i = 0; i < 2 * N; i++) {
		if(eps[i] == 'L')
			l[li++] = i;
		else
			r[ri++] = i;
	}
	string special;
	cin >> special;
    sp_pre.resize(N + 1);
	for(int i = 0; i < N; i++)
		sp_pre[i + 1] = sp_pre[i] + (special[i] == '1');

	
	ljmp.resize(lgN, vector<int>(N, -1));
	int lj = 0;
	for(int i = 0; i < N; i++) {
		while(l[i] > r[lj]) lj++;
		ljmp[0][i] = lj;
	}
	rjmp.resize(lgN, vector<int>(N, -1));
	int rj = N - 1;
	for(int i = N - 1; i >= 0; i--) {
		while(l[rj] > r[i]) rj--;
		rjmp[0][i] = rj;
	}
	ljmp[0][0] = -1, rjmp[0][N - 1] = -1;

    lv.resize(lgN, vector<int>(N));
    rv.resize(lgN, vector<int>(N));
    for(int j = 0; j < N; j++) {
        if(ljmp[0][j] != -1)
            lv[0][j] = sp_pre[ljmp[0][j]];
        if(rjmp[0][j] != -1)
            rv[0][j] = sp_pre[rjmp[0][j] + 1];
    }

	// calculate jmp
	for(int i = 1; i < lgN; i++) {
		for(int j = 0; j < N; j++) {
			ljmp[i][j] = (ljmp[i - 1][j] == -1) ? -1 : ljmp[i - 1][ljmp[i - 1][j]];
			rjmp[i][j] = (rjmp[i - 1][j] == -1) ? -1 : rjmp[i - 1][rjmp[i - 1][j]];
            if(ljmp[i][j] != -1) 
                lv[i][j] = lv[i - 1][j] + lv[i - 1][ljmp[i - 1][j]];
            if(rjmp[i][j] != -1)
                rv[i][j] = rv[i - 1][j] + rv[i - 1][rjmp[i - 1][j]];
		}
	}


    for(int q = 0; q < Q; q++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        int v = 0;
        int dist = 0;
        int cl = a, cr = b;
        for(int lg = lgN - 1; lg >= 0; lg--) {
            if(rjmp[lg][cl] != -1 && rjmp[lg][cl] < b) {
                v += rv[lg][cl] - lv[lg][cr];
                cl = rjmp[lg][cl], cr = ljmp[lg][cr];
                dist += (1 << lg);
            }
        }
        cout << dist + 1 << " " << v + (special[a] == '1') + (special[b] == '1') << endl;
    }
}
