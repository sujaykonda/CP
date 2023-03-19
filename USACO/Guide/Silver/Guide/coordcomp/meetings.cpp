// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int N, L;
int W = 0;

vector<pair<int, pair<int, int>>> cows;

int getNextI(int i)
{
    while (i < N && cows[i].second.second == 1)
        i++;
    return i;
}
int getNextJ(int j)
{
    while (j >= 0 && cows[j].second.second == -1)
        j--;
    return j;
}

int getT()
{
    int cW = 0;
    int iC = 0;
    int i = getNextI(0);
    int jC = 0;
    int j = getNextJ(N - 1);
    int t = 0;
    while (cW < W / 2.0)
    {
        if (cows[i].first < L - cows[j].first)
        {
            t = cows[i].first;
            cW += cows[iC].second.first;
            i = getNextI(i + 1);
            iC++;
        }
        else
        {
            t = L - cows[j].first;
            cW += cows[N - 1 - jC].second.first;
            j = getNextJ(j - 1);
            jC++;
        }
    }
    return t;
}

int main()
{
    ifstream fin("meetings.in");
    ofstream fout("meetings.out");

    fin >> N >> L;
    cows.resize(N);
    for (int i = 0; i < N; i++)
        fin >> cows[i].second.first >> cows[i].first >> cows[i].second.second;
    sort(cows.begin(), cows.end());
    for (int i = 0; i < N; i++)
        W += cows[i].second.first;

    int t = getT();

    vector<int> poscows;
    vector<int> negcows;

    for (int i = 0; i < N; i++)
    {
        if (cows[i].second.second == 1)
            poscows.push_back(cows[i].first);
        else
            negcows.push_back(cows[i].first);
    }

    int m = 0;

    for (int i = 0; i < poscows.size(); i++)
        m += upper_bound(negcows.begin(), negcows.end(), 2 * t + poscows[i]) - lower_bound(negcows.begin(), negcows.end(), poscows[i]);
    // for (int i = 0; i < negcows.size(); i++)
    // m += upper_bound(poscows.begin(), poscows.end(), negcows[i]) - lower_bound(poscows.begin(), poscows.end(), -2 * t + negcows[i]);

    fout << m << endl;
}
