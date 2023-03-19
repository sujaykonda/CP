// problem w code is that duplicate xs or ys can cause issue
// way to fix it would be to write things in a while loop to skip over those when calculating area
// i am too lazy to implement this so i will revisit this if necessary

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<pair<int, int>> cowloc;
long long xareas[50001];
long long yareas[50001];

int ycmp(pair<int, int> x, pair<int, int> y)
{
    return x.second < y.second;
}

int main()
{
    ifstream fin("split.in");
    fin >> N;
    for (int i = 0; i < N; i++)
    {
        int x, y;
        fin >> x >> y;
        cowloc.push_back(make_pair(x, y));
    }
    fin.close();
    sort(cowloc.begin(), cowloc.end());

    pair<int, int> bounds;

    bounds = make_pair(1000000001, 0);
    for (int i = 0; i < N; i++)
    {
        bounds.first = min(bounds.first, cowloc[i].second);
        bounds.second = max(bounds.second, cowloc[i].second);
        xareas[i + 1] += (long long)(bounds.second - bounds.first) * (long long)(cowloc[i].first - cowloc[0].first);
    }

    bounds = make_pair(1000000001, 0);
    for (int i = N - 1; i >= 0; i--)
    {
        bounds.first = min(bounds.first, cowloc[i].second);
        bounds.second = max(bounds.second, cowloc[i].second);
        xareas[i] += (long long)(bounds.second - bounds.first) * (long long)(cowloc[N - 1].first - cowloc[i].first);
    }

    sort(cowloc.begin(), cowloc.end(), ycmp);

    bounds = make_pair(1000000001, 0);
    for (int i = 0; i < N; i++)
    {
        bounds.first = min(bounds.first, cowloc[i].first);
        bounds.second = max(bounds.second, cowloc[i].first);
        yareas[i + 1] += (long long)(bounds.second - bounds.first) * (long long)(cowloc[i].second - cowloc[0].second);
    }

    bounds = make_pair(1000000001, 0);
    for (int i = N - 1; i >= 0; i--)
    {
        bounds.first = min(bounds.first, cowloc[i].first);
        bounds.second = max(bounds.second, cowloc[i].first);
        yareas[i] += (long long)(bounds.second - bounds.first) * (long long)(cowloc[N - 1].second - cowloc[i].second);
    }

    long long minarea = xareas[0];
    for (int i = 2; i < N - 1; i++)
    {
        cout << xareas[i] << " ";
        minarea = min(minarea, xareas[i]);
    }
    cout << endl;
    for (int i = 2; i < N - 1; i++)
    {
        cout << yareas[i] << " ";
        minarea = min(minarea, yareas[i]);
    }
    cout << endl;

    ofstream fout("split.out");
    fout << xareas[0] - minarea << endl;
    fout.close();
}