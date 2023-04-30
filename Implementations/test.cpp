#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void rd(char& x) { x = getchar(); }
void rd(ll& x) {
    x = 0; int mult = 1; char c; rd(c);
    for (; (c <= 47 || 58 <= c) && c != '-'; rd(c));
    if(c == '-') mult = -1, rd(c);
    for (; (c>47 && c<58); rd(c))
        x = 10 * x + c - 48;
    x *= mult;
}
void rd(int& x) {
    x = 0; int mult = 1; char c; rd(c);
    for (; (c <= 47 || 58 <= c) && c != '-'; rd(c));
    if(c == '-') mult = -1, rd(c);
    for (; (c>47 && c<58); rd(c))
        x = 10 * x + c - 48;
    x *= mult;
}
template<class T> void rd(T& o) { for(auto& v : o) rd(v); }

int main() {
	int n, k; rd(n), rd(k);
	int cnt = 0, t;
	for(int i = 0; i < n; i++)
		rd(t), cnt += (t % k == 0);
	cout << cnt << '\n';
}