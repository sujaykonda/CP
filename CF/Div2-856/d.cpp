#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll M = 998244353;

ll fe(ll a, ll b, ll m) { return b == 0 ? 1 : ((fe((a * a) % m, b / 2, m) % m) * ((b % 2 ? a : 1) % m) % m); }
ll minv(ll a, ll p) { return fe(a, p - 2, p); }

vector<int> prime;
vector<bool> iscomp;

void sieve(int n)
{
    iscomp.resize(n);
    iscomp[1] = true;
    for (int i = 2; i < n; ++i)
    {
        if (!iscomp[i])
            prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] < n; ++j)
        {
            iscomp[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
}

vector<ll> f;
vector<ll> invf;


void factorials(ll mx, ll m)
{
    f.resize(mx);
    invf.resize(mx);
    f[0] = 1, invf[0] = 1;
    for (int i = 1; i < mx; i++)
        f[i] = (f[i - 1] * i) % m;
    invf[mx - 1] = minv(f[mx - 1], m);
    for (int i = mx - 1; i >= 1; i--)
        invf[i - 1] = (invf[i] * i) % m;
}

int main() {
    int n;
    cin >> n;

    sieve(1000001);
    factorials(2 * n + 1, M);

    vector<int> a(2 * n);
    for(int i = 0; i < 2 * n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    
    ll picke = f[2 * n];
    int cnt = 1;
    for(int i = 0; i < 2 * n; i++) {
        if(i > 0 && a[i] == a[i - 1])
            cnt++;
        else
            picke = (picke * invf[cnt]) % M, cnt = 1;
    }
    picke = (picke * invf[cnt]) % M;
    
    vector<pair<int, int>> uprimes;
    for(int i = 0; i < 2 * n; i++)
        if(!iscomp[a[i]])
            if(uprimes.size() == 0 || uprimes.back().first != a[i])
                uprimes.push_back({a[i], 1});
            else
                uprimes.back().second++;
    if(uprimes.size() < n) {
        cout << 0 << endl;
        return 0;
    }
    vector<ll> inv(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        inv[i] = minv(i, M);
    }
    vector<vector<ll>> dp(uprimes.size() + 1, vector<ll>(n + 1));
    dp[0][0] = picke;
    for(int i = 0; i < uprimes.size(); i++) {
        for(int j = 0; j <= n; j++) {
            if(dp[i][j] == 0) continue;
            dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % M;
            if(j < n) {
                dp[i + 1][j + 1] += (dp[i + 1][j + 1] + ((dp[i][j] * inv[2 * n - j] % M) * uprimes[i].second % M)) % M;
            }
        }
    }
    cout << dp[uprimes.size()][n] << endl;
}