#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, K;
vector<int> berries;
vector<int> berriesnotn;

int check(int n)
{
    berriesnotn.clear();
    int numofn = 0;
    for (int i = 0; i < berries.size(); i++)
    {
        numofn += berries[i] / n;
        berriesnotn.push_back(berries[i] % n);
    }
    if (numofn >= K)
    {
        return n * K / 2;
    }
    sort(berriesnotn.begin(), berriesnotn.end(), greater<int>());
    int s = 0;
    if (numofn > K / 2)
    {
        s += (numofn - K / 2) * n;
    }
    for (int i = numofn; i < K; i++)
    {
        if (i > K / 2)
        {
            s += berriesnotn[i - numofn];
        }
    }
    return s;
}

int main()
{
    freopen("berries.in", "r", stdin);
    freopen("berries.out", "w", stdout);

    cin >> N >> K;
    for (int i = 0; i < N; i++)
    {
        int bi;
        cin >> bi;
        berries.push_back(bi);
    }

    sort(berries.begin(), berries.end(), greater<int>());

    int ma = berries[0];
    int mi = berries[berries.size() - 1];
    int maxv = 0;
    for (int n = mi; n < ma; n++)
    {
        int a = check(n);
        if (a > maxv)
        {
            maxv = a;
        }
        else
        {
            cout << maxv << endl;
            return 0;
        }
    }
}