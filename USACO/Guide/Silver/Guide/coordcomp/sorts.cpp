#include <bits/stdc++.h>
using namespace std;

int N;
vector<pair<int, int>> S;
vector<int> A;

int main()
{
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    cin >> N;
    A.resize(N);
    S.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        S[i].first = A[i];
        S[i].second = i;
    }

    sort(S.begin(), S.end());
    for (int i = 0; i < N; i++)
    {
        A[S[i].second] = i;
    }
    int md = 0;
    for (int i = 0; i < N; i++)
    {
        md = max(md, abs(A[i] - i) + 1);
    }

    cout << md << endl;
}