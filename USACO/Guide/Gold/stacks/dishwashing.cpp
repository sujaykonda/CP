#include <bits/stdc++.h>
using namespace std;

int main()
{
    // freopen("dishes.in", "r", stdin);
    // freopen("dishes.out", "w", stdout);

    int N;
    cin >> N;

    stack<int> bstack;
    for (int i = 0; i < N; i++)
    {
        int n;
        cin >> n;
        bstack.push(n);
    }

    int m = 1;
    vector<int> bottom;
    vector<stack<int>> counter;
    while (!bstack.empty())
    {
        int top = bstack.top();
        if (top < m)
            break;
        // if we are > then everybody then add to the back
        if (counter.size() == 0 || bottom.back() < top)
        {
            stack<int> newstack;
            newstack.push(top);
            bottom.push_back(top);
            counter.push_back(newstack);
        }
        else if (bottom.front())
        {
        }
        bstack.pop();
    }
    cout << N - bstack.size() << endl;
}