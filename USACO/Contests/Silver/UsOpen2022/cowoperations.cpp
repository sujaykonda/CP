#include <bits/stdc++.h>
using namespace std;

int Cp[200001];
int Op[200001];
int Wp[200001];

int Q;
int main()
{
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++)
    {
        Cp[i + 1] = Cp[i] + (s[i] == 'C');
        Op[i + 1] = Op[i] + (s[i] == 'O');
        Wp[i + 1] = Wp[i] + (s[i] == 'W');
    }

    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        int s, e;
        cin >> s >> e;
        int c = (Cp[e] - Cp[s - 1]) % 2;
        int o = (Op[e] - Op[s - 1]) % 2;
        int w = (Wp[e] - Wp[s - 1]) % 2;
        if ((c == 0 && o == 1 && w == 1) || (c == 1 && o == 0 && w == 0))
        {
            cout << 'Y';
        }
        else
        {
            cout << 'N';
        }
    }
    cout << endl;
}