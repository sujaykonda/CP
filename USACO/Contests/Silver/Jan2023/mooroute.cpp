#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;

    cin >> N;
    int T = 0;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i], T += A[i];

    int Ls = T / 2;
    int Rs = T / 2;

    int mC = 0;
    int x = 0;
    char dir = 'R';
    int end = N;
    vector<char> ans(T);
    while (mC < T)
    {
        if (dir == 'R')
        {
            if (Rs == 0 || x == N || A[x] - 1 <= 0)
                dir = 'L';
            else
            {
                ans[mC] = dir;
                A[x]--;
                x++;
                mC++;
            }
        }
        else
        {
            if (Ls == 0 || x == 0 || A[x - 1] - 1 < 0 || (A[x - 1] - 1 == 0 && end > x))
                dir = 'R';
            else
            {
                ans[mC] = dir;
                x--;
                A[x]--;
                if (A[x] == 0)
                    end--;
                mC++;
            }
        }
    }
    for (char c : ans)
        cout << c;
    cout << endl;
}