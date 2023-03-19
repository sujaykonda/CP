#include <bits/stdc++.h>
using namespace std;

int N;
vector<pair<int, int>> particles;

int main()
{
    freopen("moop.in", "r", stdin);
    freopen("moop.out", "w", stdout);
    cin >> N;
    particles.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> particles[i].first >> particles[i].second;
    }
    sort(particles.begin(), particles.end());
    stack<int> comp;
    comp.push(particles[0].second);
    for (int i = 1; i < N; i++)
    {
        int ncomp = min(comp.top(), particles[i].second);
        while (comp.size() > 0 && comp.top() <= particles[i].second)
            comp.pop();
        comp.push(ncomp);
    }
    cout << comp.size() << endl;
}