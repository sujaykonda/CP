#include <bits/stdc++.h>
using namespace std;
#define MAX_N 100000
int N, Q;
string color;
int prefix[MAX_N + 1];
int suffix[MAX_N + 1];
int main()
{
    cin >> N >> Q;
    cin >> color;
    stack<char> coats;
    coats.push(0);
    prefix[0] = 0;
    for (int i = 1; i <= N; i++)
    {
        prefix[i] = prefix[i - 1];
        while (coats.top() > color[i - 1])
            coats.pop();
        if (coats.top() < color[i - 1])
            coats.push(color[i - 1]), prefix[i]++;
    }
    coats.empty();
    coats.push(0);
    for (int i = N - 1; i >= 0; i--)
    {
        suffix[i] = suffix[i + 1];
        while (coats.top() > color[i])
            coats.pop();
        if (coats.top() < color[i])
            coats.push(color[i]), suffix[i]++;
    }

    for (int q = 0; q < Q; q++)
    {
        int a, b;
        cin >> a >> b;
        cout << prefix[a - 1] + suffix[b] << endl;
    }
}