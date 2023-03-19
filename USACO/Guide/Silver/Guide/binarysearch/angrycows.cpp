#include <bits/stdc++.h>

using namespace std;

int N;

vector<int> haybales;
vector<int> left_exp;
vector<int> right_exp;

double calcPower(int i, int j) { return max(left_exp[i], right_exp[j]) + 1; }
double calcSpace(int i, int j) { return (haybales[j] - haybales[i]) / 2.0; }

int main()
{
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);
    cin >> N;

    haybales.resize(N);
    left_exp.resize(N);
    right_exp.resize(N);

    for (int i = 0; i < N; i++)
    {
        cin >> haybales[i];
    }

    sort(haybales.begin(), haybales.end());

    left_exp[0] = 0;

    int i = 1, j = 0;
    while (i < N)
    {
        if (j + 1 < i && max(left_exp[j] + 1, haybales[i] - haybales[j]) > max(left_exp[j + 1] + 1, haybales[i] - haybales[j + 1]))
        {
            j++;
            continue;
        }
        left_exp[i] = max(left_exp[j] + 1, haybales[i] - haybales[j]);
        i++;
    }

    right_exp[N - 1] = 0;
    i = N - 2;
    j = N - 1;
    while (i >= 0)
    {
        if (j - 1 > i && max(right_exp[j] + 1, haybales[j] - haybales[i]) > max(right_exp[j - 1] + 1, haybales[j - 1] - haybales[i]))
        {
            j--;
            continue;
        }
        right_exp[i] = max(right_exp[j] + 1, haybales[j] - haybales[i]);
        i--;
    }

    double minR = haybales[N - 1] - haybales[0];
    i = 0, j = 1;
    while (i < N)
    {
        if (j <= i || (j < N - 1 && max(calcPower(i, j), calcSpace(i, j)) > max(calcPower(i, j + 1), calcSpace(i, j + 1))))
        {
            j++;
            continue;
        }
        // cout << i << " " << j << ": " << max(calcPower(i, j), calcSpace(i, j)) << endl;
        minR = min(minR, max(calcPower(i, j), calcSpace(i, j)));
        i++;
    }
    cout << setprecision(1) << fixed;
    cout << minR << endl;
}