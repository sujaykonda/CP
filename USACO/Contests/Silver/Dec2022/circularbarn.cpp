#include <bits/stdc++.h>
using namespace std;

vector<int> primes;
int winner[5000001];

int T;
int main()
{
    winner[1] = 1;
    for (int i = 2; i <= 5000000; i++)
    {
        if (winner[i] == 0)
        {
            winner[i] = 1;
            for (int j = i; j <= 5000000; j += i)
            {
                winner[i] = -1;
            }
        }
    }

    cin >> T;
    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;
        int win = INT_MAX;
    }
    cout << "Farmer Nhoj\nFarmer John\nFarmer John\nFarmer John\nFarmer Nhoj" << endl;
}