#include <bits/stdc++.h>

using namespace std;

tuple<int, int, int> solveABC(int A, int B, int C, int AB, int BC, int AC, int ABC)
{
    if (ABC != 0 && BC != 0 && A == 0)
        A = ABC - BC;
    if (ABC != 0 && AC != 0 && B == 0)
        B = ABC - AC;
    if (ABC != 0 && AB != 0 && C == 0)
        C = ABC - AB;

    if (AB != 0 && A == 0 && B != 0)
        A = AB - B;
    if (AC != 0 && A == 0 && C != 0)
        A = AC - C;
    if (AB != 0 && B == 0 && A != 0)
        B = AB - A;
    if (BC != 0 && B == 0 && C != 0)
        B = BC - C;
    if (AC != 0 && C == 0 && A != 0)
        C = AC - A;
    if (BC != 0 && C == 0 && B != 0)
        C = BC - B;
    return {A, B, C};
}
void check(vector<tuple<int, int, int>> *sols, int n1, int n2, int n3, int n4)
{
    vector<int> ins;
    ins.resize(7);
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (j == i)
                continue;
            for (int k = 0; k < 7; k++)
            {
                if (k == i || k == j)
                    continue;
                for (int m = 0; m < 7; m++)
                {
                    if (m == i || m == j || m == k)
                        continue;
                    // cout << i << " " << j << " " << k << " " << m << endl;
                    ins[i] = n1, ins[j] = n2, ins[k] = n3, ins[m] = n4;
                    tuple<int, int, int> triple = solveABC(ins[0], ins[1], ins[2], ins[3], ins[4], ins[5], ins[6]);
                    bool good = get<0>(triple) >= 1 && get<1>(triple) >= 1 && get<2>(triple) >= 1;
                    if (ins[0] != 0 && ins[0] != get<0>(triple))
                        good = false;
                    if (ins[1] != 0 && ins[1] != get<1>(triple))
                        good = false;
                    if (ins[2] != 0 && ins[2] != get<2>(triple))
                        good = false;
                    if (ins[3] != 0 && ins[3] != get<0>(triple) + get<1>(triple))
                        good = false;
                    if (ins[4] != 0 && ins[4] != get<1>(triple) + get<2>(triple))
                        good = false;
                    if (ins[5] != 0 && ins[5] != get<0>(triple) + get<2>(triple))
                        good = false;
                    if (ins[6] != 0 && ins[6] != get<0>(triple) + get<1>(triple) + get<2>(triple))
                        good = false;
                    if (good)
                    {
                        sols->push_back(triple);
                    }
                    ins[i] = 0, ins[j] = 0, ins[k] = 0, ins[m] = 0;
                }
            }
        }
    }
}

void fix_sols(vector<tuple<int, int, int>> *sp)
{
    for (int i = 0; i < sp->size(); i++)
    {
        tuple<int, int, int> sorted;
        if (get<0>((*sp)[i]) > get<1>((*sp)[i]))
        {
            if (get<2>((*sp)[i]) > get<1>((*sp)[i]))
            {
                if (get<0>((*sp)[i]) > get<2>((*sp)[i]))
                {
                    get<0>(sorted) = get<0>((*sp)[i]);
                    get<1>(sorted) = get<2>((*sp)[i]);
                    get<2>(sorted) = get<1>((*sp)[i]);
                }
                else
                {
                    get<0>(sorted) = get<2>((*sp)[i]);
                    get<1>(sorted) = get<0>((*sp)[i]);
                    get<2>(sorted) = get<1>((*sp)[i]);
                }
            }
            else
            {
                get<0>(sorted) = get<0>((*sp)[i]);
                get<1>(sorted) = get<1>((*sp)[i]);
                get<2>(sorted) = get<2>((*sp)[i]);
            }
        }
        else
        {
            if (get<2>((*sp)[i]) > get<0>((*sp)[i]))
            {
                if (get<1>((*sp)[i]) > get<2>((*sp)[i]))
                {
                    get<0>(sorted) = get<1>((*sp)[i]);
                    get<1>(sorted) = get<2>((*sp)[i]);
                    get<2>(sorted) = get<0>((*sp)[i]);
                }
                else
                {
                    get<0>(sorted) = get<2>((*sp)[i]);
                    get<1>(sorted) = get<1>((*sp)[i]);
                    get<2>(sorted) = get<0>((*sp)[i]);
                }
            }
            else
            {
                get<0>(sorted) = get<1>((*sp)[i]);
                get<1>(sorted) = get<0>((*sp)[i]);
                get<2>(sorted) = get<2>((*sp)[i]);
            }
        }
        (*sp)[i] = sorted;
    }
}

int T;
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        int N;
        vector<int> xs;

        cin >> N;
        xs.resize(N);
        for (int i = 0; i < N; i++)
            cin >> xs[i];

        vector<tuple<int, int, int>> sols;
        check(&sols, xs[0], xs[1], xs[2], xs[3]);
        fix_sols(&sols);
        sort(sols.begin(), sols.end());

        for (int n1 = 0; n1 < N; n1++)
        {
            for (int n2 = n1 + 1; n2 < N; n2++)
            {
                for (int n3 = n2 + 1; n3 < N; n3++)
                {
                    for (int n4 = n3 + 1; n4 < N; n4++)
                    {
                        vector<tuple<int, int, int>> nsols;
                        check(&nsols, xs[n1], xs[n2], xs[n3], xs[n4]);
                        vector<tuple<int, int, int>> isols(nsols.size());
                        fix_sols(&nsols);
                        sort(nsols.begin(), nsols.end());
                        auto it = set_intersection(sols.begin(), sols.end(), nsols.begin(), nsols.end(), isols.begin());
                        isols.resize(it - isols.begin());
                        sols = isols;
                    }
                }
            }
        }
        sort(sols.begin(), sols.end());
        int c = sols.size() > 0;
        for (int i = 1; i < sols.size(); i++)
        {
            if (sols[i] != sols[i - 1])
            {
                c++;
            }
        }
        cout << c << endl;
    }
}