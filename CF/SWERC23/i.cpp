#include <cplib/general.h>
using namespace std;

int main() {
    int n; rd(n);
    vector<pair<int, int>> p(n); rd(p);
    auto cross = [&] (int i, int j) {
        return (ll)p[i].first * p[j].second - (ll)p[i].second * p[j].first;
    };
    auto area = [&] (int i, int j, int k) {
        return llabs(cross(i, j) + cross(j, k) + cross(k, i));
    };
    int t = 1;
    ll A = 0, B = 0;
    vector<int> left(n);
    for(int i = 0; i < n; i++) left[i] = i; 
    while(left.size() > 2) {
        ll minarea = 1e18;
        int pick = 0;
        int lsize = left.size();
        for(int i = 0; i < lsize; i++) {
            ll curarea = area(left[(i - 1 + lsize) % lsize], left[i], left[(i + 1) % lsize]);
            if(curarea < minarea) {
                minarea = curarea;
                pick = i;
            }
        }
        A += minarea * t, B += minarea * (t ^ 1);
        left.erase(left.begin() + pick);
        t ^= 1;
    }
    left = vector<int>(n);
    for(int i = 0; i < n; i++) left[i] = i; 
    if(A < B) {
        t = 1;
        cout << "Alberto" << endl;
    } else {
        t = 0;
        cout << "Beatrice" << endl;
    }
    while(left.size() > 2) {
        int pick = 0;
        if(t == 1) {
            ll minarea = 1e18;
            int lsize = left.size();
            for(int i = 0; i < lsize; i++) {
                ll curarea = area(left[(i - 1 + lsize) % lsize], left[i], left[(i + 1) % lsize]);
                if(curarea < minarea) {
                    minarea = curarea;
                    pick = left[i];
                }
            }
            cout << pick + 1 << endl;
        } else {
            rd(pick);
            pick--;
        }
        for(auto it = left.begin();;it++) {
            if(*it == pick) {
                left.erase(it);
                break;
            }
        }
        t ^= 1;
    }
}