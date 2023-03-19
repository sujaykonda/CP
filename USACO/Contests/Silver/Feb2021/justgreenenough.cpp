#include <bits/stdc++.h>
using namespace std;

int N;
long long h[501][501];
long long l[501][501];
int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            int g;
            cin >> g;
            h[i][j] = h[i - 1][j];
            l[i][j] = l[i - 1][j];
            if (g < 100)
                l[i][j]++;
            if (g == 100)
                h[i][j]++;
        }
    }
    long long c = 0;
    for (int i = 0; i <= N; i++)
    {
        for (int j = i + 1; j <= N; j++)
        {
            vector<int> lv;
            vector<int> hv;
            lv.push_back(0);
            for (int k = 1; k <= N; k++)
            {
                if (l[j][k] > l[i][k])
                {
                    lv.push_back(k);
                }
                if (h[j][k] > h[i][k])
                {
                    hv.push_back(k);
                }
            }
            lv.push_back(N + 1);
            hv.push_back(N + 1);

            int p1 = 0;
            int p2 = 0;
            while (p2 < lv.size() - 1 && p1 < hv.size() - 1)
            {
                if (lv[p2 + 1] <= hv[p1])
                {
                    p2++;
                    continue;
                }
                long long right = min(hv[p1 + 1], lv[p2 + 1]) - hv[p1];
                long long left = hv[p1] - lv[p2];
                // cout << hv[p1] << " " << min(hv[p1 + 1], lv[p2 + 1]) << endl;
                // cout << i << " " << j << " " << left << " " << right << endl;

                c += right * left;
                p1++;
            }
        }
    }
    cout << c << endl;
}
