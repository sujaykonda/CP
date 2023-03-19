#include <bits/stdc++.h>

using namespace std;

int N;
int M;

vector<int> s;
vector<int> e;

long long sf[5001];
long long ef[5001];
long long sa[10001];
long long ea[10001];

int main()
{
    cin >> N >> M;

    s.resize(N);
    e.resize(N);
    for (int i = 0; i < N; i++)
        cin >> s[i] >> e[i];

    for (int i = 0; i < N; i++)
        sf[s[i]]++, ef[e[i]]++;

    for (int i = 0; i <= M; i++)
        for (int j = 0; j <= M; j++)
            sa[i + j] += sf[i] * sf[j], ea[i + j] += ef[i] * ef[j];

    long long a = 0;
    for (int i = 0; i <= 2 * M; i++)
    {
        a += sa[i];
        cout << a << endl;
        a -= ea[i];
    }
}