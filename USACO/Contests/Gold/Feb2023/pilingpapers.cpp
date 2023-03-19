#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll M = 1000000007;
int N;
vector<int> a;

vector<vector<ll>> calc_dp(ll A) {
    vector<int> digits(18);
    int nd = 0;
    for(int i = 0; i < 18; i++, A /= 10)
        digits[i] = A % 10, nd += A != 0;
    vector<vector<ll>> dp2(N, vector<ll>(N + 1));
    for(int j = 0; j < N; j++) {
        array<array<array<ll, 3>, 19>, 19> curdp {};
        array<array<array<ll, 3>, 19>, 19> prevdp;
        for(int i = 0; i <= nd; i++)
            curdp[i][i][1] = 1;
        for(int i = j; i < N; i++) {
            prevdp = curdp;
            for(int l = 0; l < nd; l++) {
                for(int r = l + 1; r <= nd; r++) {
                    if(digits[l] > a[i]) {
                        curdp[l][r][0] = (curdp[l][r][0] + prevdp[l + 1][r][0] + prevdp[l + 1][r][1]) % M;
                        curdp[l][r][2] = (curdp[l][r][2]+ prevdp[l + 1][r][2]) % M;
                    }
                    if(digits[l] == a[i]) {
                        curdp[l][r][0] = (curdp[l][r][0] + prevdp[l + 1][r][0]) % M;
                        curdp[l][r][1] = (curdp[l][r][1] + prevdp[l + 1][r][1]) % M;
                        curdp[l][r][2] = (curdp[l][r][2] + prevdp[l + 1][r][2]) % M;
                    }
                    if(digits[l] < a[i]) {
                        curdp[l][r][0] = (curdp[l][r][0] + prevdp[l + 1][r][0]) % M;
                        curdp[l][r][2] = (curdp[l][r][2] + prevdp[l + 1][r][1] + prevdp[l + 1][r][2]) % M;
                    }
                    if(digits[r - 1] > a[i]) {
                        curdp[l][r][0] = (curdp[l][r][0] + prevdp[l][r - 1][0] + prevdp[l][r - 1][1] + prevdp[l][r - 1][2]) % M;
                    }
                    if(digits[r - 1] == a[i]) {
                        curdp[l][r][0] = (curdp[l][r][0] + prevdp[l][r - 1][0]) % M;
                        curdp[l][r][1] = (curdp[l][r][1] + prevdp[l][r - 1][1]) % M;
                        curdp[l][r][2] = (curdp[l][r][2] + prevdp[l][r - 1][2]) % M;
                    }
                    if(digits[r - 1] < a[i]) {
                        curdp[l][r][2] = (curdp[l][r][2] + prevdp[l][r - 1][0] + prevdp[l][r - 1][1] + prevdp[l][r - 1][2]) % M;
                    }
                }
            }
            for(int k = 0; k <= nd; k++) {
                dp2[j][i + 1] = (dp2[j][i + 1] + curdp[0][k][0] + curdp[0][k][1] + curdp[0][k][2]) % M;
            }
            dp2[j][i + 1] = (dp2[j][i + 1] - curdp[0][nd][2] + M) % M;
        }
    }
    return dp2;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
    ll A, B;
    cin >> N >> A >> B;
    a.resize(N);
    for(int i = 0; i < N; i++)
        cin >> a[i];
    vector<vector<ll>> dpA = calc_dp(A - 1);
    vector<vector<ll>> dpB = calc_dp(B); 
    int Q;
    cin >> Q;
    for(int i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        cout << (dpB[a][b] - dpA[a][b] + M) % M << endl;
    }
}