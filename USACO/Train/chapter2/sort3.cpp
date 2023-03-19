/*
ID: kondasu1
LANG: C++
TASK: sort3
*/

#include <bits/stdc++.h>
using namespace std;

int a[1000];
int b[1000];
int main() {
    freopen("sort3.in", "r", stdin);
    freopen("sort3.out", "w", stdout);
    int N;
    cin >> N;
    for(int i = 0; i < N; i++)
        cin >> a[i], b[i] = a[i];
    int swaps = 0;
    int j = 0;
    for(int i = 0; i < N; i++)
        if(a[i] == 1 && i != j)
            swap(a[i], a[j++]), swaps++;
    for(int i = j; i < N; i++)
        if(a[i] == 2 && i != j)
            swap(a[i], a[j++]), swaps++;
    int swaps2 = 0;
    j = 0;
    for(int i = 0; i < N; i++)
        if(b[i] == 3 && i != j)
            swap(b[i], b[j++]), swaps2++;
    for(int i = j; i < N; i++)
        if(b[i] == 2 && i != j)
            swap(b[i], b[j++]), swaps2++;
    cout << min(swaps, swaps2) << endl;
}