#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int N;
map<int, vector<int>> xmap;
map<int, vector<long>> xpmap;

map<int, vector<int>> ymap;
map<int, vector<long>> ypmap;
vector<pair<int, int>> fences;

bool ycmp(pair<int, int> x, pair<int, int> y)
{
    return x.second < y.second;
}

int main()
{
    ifstream fin("triangles.in");
    fin >> N;
    for (int i = 0; i < N; i++)
    {
        int x, y;
        fin >> x >> y;
        fences.push_back(make_pair(x, y));
    }
    fin.close();
    sort(fences.begin(), fences.end());
    int i = 0;
    while (i < N)
    {
        int x = fences[i].first;
        while (fences[i].first == x)
        {
            xmap[x].push_back(fences[i].second);
            i++;
        }
    }
    sort(fences.begin(), fences.end(), ycmp);
    int n = 0;
    while (n < N)
    {
        int y = fences[n].second;
        while (fences[n].second == y)
        {
            ymap[y].push_back(fences[n].first);
            n++;
        }
    }

    for (auto it = xmap.begin(); it != xmap.end(); it++)
    {
        sort(it->second.begin(), it->second.end());
        xpmap[it->first].push_back(0);
        for (int i = 0; i < it->second.size(); i++)
        {
            xpmap[it->first].push_back(it->second[i] + xpmap[it->first].back());
        }
    }
    for (auto it = ymap.begin(); it != ymap.end(); it++)
    {
        sort(it->second.begin(), it->second.end());
        ypmap[it->first].push_back(0);
        for (int i = 0; i < it->second.size(); i++)
        {
            ypmap[it->first].push_back(it->second[i] + ypmap[it->first].back());
        }
    };

    unsigned long long a = 0;
    for (int i = 0; i < N; i++)
    {
        int x = fences[i].first;
        int y = fences[i].second;
        int xi = lower_bound(xmap[x].begin(), xmap[x].end(), y) - xmap[x].begin();
        int yi = lower_bound(ymap[y].begin(), ymap[y].end(), x) - ymap[y].begin();
        int xsize = xmap[x].size();
        int ysize = ymap[y].size();
        unsigned long long adsy = xpmap[x][xsize] - xpmap[x][xi + 1] - xpmap[x][xi] + y * (2 * xi - xsize + 1);
        unsigned long long adsx = ypmap[y][ysize] - ypmap[y][yi + 1] - ypmap[y][yi] + x * (2 * yi - ysize + 1);
        a += adsy * adsx;
        a = a % 1000000007;
    }
    ofstream fout("triangles.out");
    fout << a << endl;
    fout.close();
}