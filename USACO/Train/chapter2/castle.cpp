/*
ID: kondasu1
LANG: C++
TASK: castle
*/

#include <bits/stdc++.h>
using namespace std;

bitset<4> walls[50][50];
bitset<2500> done;
int get_size(int x, int y){
    //cout << x << " " << y << endl;
    if(done[50 * x + y]) return 0;
    done[50 * x + y] = 1;
    int sz = 1;
    if(!walls[x][y][0])
        sz += get_size(x, y - 1);
    if(!walls[x][y][1])
        sz += get_size(x - 1, y);
    if(!walls[x][y][2])
        sz += get_size(x, y + 1);
    if(!walls[x][y][3])
        sz += get_size(x + 1, y);
    return sz;
}

int main() {
    freopen("castle.in", "r", stdin);
    freopen("castle.out", "w", stdout);
    int N, M;
    cin >> M >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            int w;
            cin >> w;
            walls[i][j] = bitset<4>(w);
        }
    }
    done.reset();
    int rooms = 0;
    int mxsz = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            if(!done[50 * i + j])
                mxsz = max(mxsz, get_size(i, j)), rooms++;
    cout << rooms << endl;
    cout << mxsz << endl;
    int mxsz2 = 0;
    int mxx = 0, mxy = 0, mxd = 0;
    for(int j = 0; j < M; j++)
        for(int i = N - 1; i >= 0; i--)
            for(int d = 1; d <= 2; d++) {
                if(d == 1 && i == 0) continue;
                if(d == 2 && j == M - 1) continue;
                if(walls[i][j][d] == 0) continue;
                walls[i][j][d] = 0;
                done.reset();
                int sz = get_size(i, j);
                //cout << i << " " << j << ": " << sz << endl;
                if(mxsz2 < sz)
                    mxsz2 = sz, mxx = i, mxy = j, mxd = d;
                walls[i][j][d] = 1;
            }

    cout << mxsz2 << endl;
    cout << mxx + 1 << " " << mxy + 1 << " ";
    if(mxd == 2)
        cout << "E" << endl;
    else
        cout << "N" << endl;
}