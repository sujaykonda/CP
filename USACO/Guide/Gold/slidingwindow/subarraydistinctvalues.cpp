#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (int i = 0; i < n; i++)
        cin >> x[i];
    long long ans = 0;
    map<int, int> cnt;
    int j = 0;
    cnt[x[j]]++;
    int s = 1;
    for (int i = 0; i < n; i++)
    {
        while (j < n && s <= k)
        {
            j++;
            if (cnt[x[j]] == 0)
                s++;
            cnt[x[j]]++;
        }
        ans += j - i;
        cnt[x[i]]--;
        if (cnt[x[i]] == 0)
            s--;
    }
    cout << ans << endl;
}