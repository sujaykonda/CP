#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> paths[100000];
bool farms[100000] = {false};
int min_days(int f)
{
    int p;
    int d;
    for (d = 0, p = 1; p < paths[f].size(); p *= 2, d++)
        ;
    farms[f] = true;
    for (int i = 0; i < paths[f].size(); i++)
    {
        if (!farms[paths[f][i]])
        {
            d += min_days(paths[f][i]) + 1;
        }
    }
    return d;
}
int main()
{
    cin >> N;
    for (int i = 0; i < (N - 1); i++)
    {
        int sf;
        int ef;
        cin >> sf;
        cin >> ef;
        paths[sf - 1].push_back(ef - 1);
        paths[ef - 1].push_back(sf - 1);
    }
    cout << min_days(0) << endl;
}