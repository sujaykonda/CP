#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int N, M, R;
vector<long long> c;
vector<pair<long long, long long>> pq;
vector<long long> r;
long long mcp[100000];
long long rcp[100000];

int main()
{
    ifstream fin("rental.in");
    fin >> N >> M >> R;
    for (int i = 0; i < N; i++)
    {
        long long ci;
        fin >> ci;
        c.push_back(ci);
    }
    for (int i = 0; i < M; i++)
    {
        long long qi, pi;
        fin >> qi >> pi;
        pq.push_back(make_pair(pi, qi));
    }
    for (int i = 0; i < R; i++)
    {
        long long ri;
        fin >> ri;
        r.push_back(ri);
    }
    fin.close();
    sort(c.begin(), c.end());
    sort(pq.begin(), pq.end());
    sort(r.begin(), r.end());
    for (int i = c.size() - 1; i >= 0; i--)
    {
        long long ci = c[i];
        while (pq.size() > 0)
        {
            if (ci < pq.back().second)
            {
                mcp[i] += pq.back().first * ci;
                pq.back().second -= ci;
                break;
            }
            mcp[i] += pq.back().first * pq.back().second;
            ci -= pq.back().second;
            pq.pop_back();
        }
    }
    for (int i = 0; i < c.size(); i++)
    {
        if (r.size() > 0)
        {
            rcp[i] = r.back();
            r.pop_back();
        }
    }

    long long maxp = 0;
    long long mcpvalue = 0;
    for (int i = 0; i < N; i++)
        mcpvalue += mcp[i];
    long long rcpvalue = 0;
    for (int split = 0; split <= c.size(); split++)
    {
        maxp = max(maxp, mcpvalue + rcpvalue);
        if (split == c.size())
            break;
        rcpvalue += rcp[split];
        mcpvalue -= mcp[split];
    }

    ofstream fout("rental.out");
    fout << maxp << endl;
    fout.close();
}