#include <bits/stdc++.h>
using namespace std;
#define pb push_back
using ll = int;
typedef vector<ll> vi;
typedef pair<ll, ll> pi;

void fastio() { ios::sync_with_stdio(false), cin.tie(nullptr); }
istream& operator>>(istream& is, vi& v) { for(ll& i : v) is >> i; return is; }
ostream& operator<<(ostream& os, vi& v) { for(ll i : v) os << i << " "; return os; }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }

void testcase() {
    string s;
    cin >> s;
    array<ll, 26> cnt{};
    for(char c : s) cnt[c - 'a']++;
    string front, back;
    int o = -1;
    for(int i = 0; i < 26; i++) {
        while(cnt[i] > 1) front += i + 'a', back += i + 'a', cnt[i] -= 2;
        if(cnt[i] == 1) {
            int o = -1;
            for(int j = i + 1; j < 26; j++) {
                if(cnt[j] > 0) {
                    if(o == -1 && o != -2)
                        o = j;
                    else
                        o = -2;
                }
            }
            if(o == -1) front += i + 'a', cnt[i]--;
            else if(o == -2) {
                back += i + 'a', cnt[i]--;
                break;
            }
            else {
                for(int k = 0; k < cnt[o] / 2 + (cnt[o] % 2 != 0); k++)
                    front += o + 'a';
                front += i + 'a';
                for(int k = 0; k < cnt[o] / 2; k++)
                    front += o + 'a';
                cnt[o] = 0, cnt[i] = 0;
            }
        }
    }
    for(int i = 0; i < 26; i++) {
        while(cnt[i] > 0) front += i + 'a', cnt[i]--;
    }
    reverse(back.begin(), back.end());
    cout << front << back << endl;
}

int main() {
    fastio();
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) testcase();
}