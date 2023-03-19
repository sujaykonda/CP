/*
ID: kondasu1
LANG: C++
TASK: frac1
*/

#include <bits/stdc++.h>
using namespace std;

struct Fraction {
    int n, d;
};
bool operator<(const Fraction& a, const Fraction& b) { 
    return a.n * b.d > b.n * a.d; 
}

bool done[160][160];
int main() {
    freopen("frac1.in", "r", stdin);
    freopen("frac1.out", "w", stdout);
    priority_queue<Fraction> pq;
    int N;
    cin >> N;
    for(int i = 1; i <= N; i++) {
        for(int j = 0; j <= i; j++) {
            if((j == 0 && i == 1) || __gcd(j, i) == 1)
                pq.push(Fraction{j, i});
        }
    }
    while(!pq.empty()) {
        cout << pq.top().n << "/" << pq.top().d << endl;
        pq.pop();
    }
}