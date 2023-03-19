#include <bits/stdc++.h>
using namespace std;

int N, K;
int d[1000001];
vector<int> a;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("stacking.in", "r", stdin);
    // freopen("stacking.out", "w", stdout);
    cin >> N >> K;
    for (int k = 1; k <= K; k++)
    {
        int a, b;
        cin >> a >> b;
        d[a]++;
        d[b]--;
    }
    int s = d[0];
    for (int i = 1; i <= N; i++)
    {
        s += d[i];
        a.push_back(s);
    }
    sort(a.begin(), a.end());
    cout << a[N / 2 + 1] << endl;
}