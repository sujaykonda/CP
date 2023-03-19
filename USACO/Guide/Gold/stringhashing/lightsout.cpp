#include <bits/stdc++.h>
using namespace std;
struct Point {
    int x, y;
    Point operator+ (const Point& o) { return Point{x + o.x, y + o.y}; }
    Point operator- (const Point& o) { return Point{x - o.x, y - o.y}; }
};
#define ll long long
#define sign(x) (x == 0 ? 0 : (x > 0 ? 1 : -1))
#define modn 1000000009
int main() {
    freopen("lightsout.in", "r", stdin);
    freopen("lightsout.out", "w", stdout);
    int N;
    cin >> N;
    vector<Point> poly(N);
    for(int i = 0; i < N; i++)
        cin >> poly[i].x >> poly[i].y;
    vector<int> intang(N);
    for(int i = 0; i < N; i++) {
        Point before = poly[i] - poly[(i + N - 1) % N]; 
        Point after = poly[(i + 1) % N] - poly[i];
        intang[i] = ((sign(before.y) * sign(after.x) + sign(before.x) * sign(-after.y)) > 0) + 1;
    }
    vector<int> bckdst(N);
    vector<int> bckdstid(N);
    map<int, int> mp;
    for(int i = 0; i < N; i++) {
        Point before = poly[(i + N - 1) % N] - poly[i]; 
        bckdst[i] = abs(before.x + before.y);
        if(!mp.count(bckdst[i]))
            mp[bckdst[i]] = i + 1;
        bckdstid[i] = mp[bckdst[i]];
    }

    vector<ll> dist(N);
    dist[0] = 0;
    for(int i = 1; i < N; i++) {
        Point before = poly[i - 1] - poly[i];
        dist[i] = dist[i - 1] + abs(before.x + before.y);
    }
    for(int i = N - 1; i > 0; i--) {
        Point after = poly[(i + 1) % N] - poly[i];
        dist[i] = min(dist[i], dist[(i + 1) % N] + abs(after.x + after.y));
    }
    map<ll, int> cnt;
    for(int i = 1; i < N; i++) {
        ll hsh = intang[i];
        ll p = 3;
        cnt[hsh]++;
        for(int j = i + 1; j != 1; j = (j + 1) % N) {
            hsh = (hsh + ((N + 1) * (p * intang[j] % modn)) % modn + p * bckdstid[j]) % modn;
            cnt[hsh]++;
            p = (p * 3 * (N + 1)) % modn;
        }
    }
    
    ll mx = 0;
    for(int i = 1; i < N; i++) {
        ll hsh = intang[i];
        ll p = 3;
        ll dt = 0;
        int j;
        for(j = (i + 1) % N; cnt[hsh] > 1 && j != 1; j = (j + 1) % N) {
            dt += bckdst[j];
            hsh = (hsh + ((N + 1) * (p * intang[j] % modn)) % modn + p * bckdstid[j]) % modn;
            p = (p * 3 * (N + 1)) % modn;
        }
        j = (j + N - 1) % N;
        mx = max(mx, dist[j] + dt - dist[i]);
    }
    cout << mx << endl;
}