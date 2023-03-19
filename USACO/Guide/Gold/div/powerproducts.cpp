#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 100001

ll n, k;
vector<ll> poss[MAXN];

ll spf[MAXN];

void sieve(ll N)
{
    for (ll i = 1; i < N; i++)
        spf[i] = i;
    for (ll i = 2; i < N; i++)
        if (spf[i] == i)
            for (ll j = i; j < N; j += i)
                spf[j] = i;
}

vector<pair<ll, ll>> pf(ll x)
{
    vector<pair<ll, ll>> f;
    while (x != 1)
    {
        if (f.size() > 0 && f.back().first == spf[x])
        {
            f.back().second = (f.back().second + 1) % k;
            if (f.back().second == 0)
                f.pop_back();
        }
        else
            f.push_back({spf[x], 1});
        x /= spf[x];
    }
    return f;
}

vector<pair<ll, ll>> rf(vector<pair<ll, ll>> f)
{
    vector<pair<ll, ll>> inv(f.size());
    for (int i = 0; i < inv.size(); i++)
        inv[i].first = f[i].first, inv[i].second = k - f[i].second;
    return inv;
}

int acount[MAXN];

int main()
{
    cin >> n >> k;

    sieve(MAXN);

    map<vector<pair<ll, ll>>, int> freq;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        freq[pf(arr[i])]++;
    }
    ll num_of_pairs = 0;
    for (int i = 0; i < n; i++)
    {
        if (pf(arr[i]) == rf(pf(arr[i])))
            num_of_pairs += (freq[pf(arr[i])] - 1);
        else
            num_of_pairs += freq[rf(pf(arr[i]))];
    }
    cout << num_of_pairs / 2 << endl;
}