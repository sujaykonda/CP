#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    if(n == 1) {
        cout << 1 << endl;
    } else {
        int cnt = 0;
        int p = 0, sp = 0;
        while(cnt < n) {
            string s = "";
            if(p == 0) {
                s += "1";
                for(int i = 0; i < sp; i++) s += "0";
                s += "6";
                for(int i = 0; i < sp; i++) s += "0";
                s += "9";
            } else if(p == 1) {
                s += "9";
                for(int i = 0; i < sp; i++) s += "0";
                s += "6";
                for(int i = 0; i < sp; i++) s += "0";
                s += "1";
            } else if(p == 2) {
                s += "1";
                for(int i = 0; i < sp; i++) s += "0";
                s += "9";
                for(int i = 0; i < sp; i++) s += "0";
                s += "6";
            }
            while(s.size() < n) s += "0";
            cout << s << endl;
            cnt++;
            p++;
            if(p == 2 && sp >= 1) sp++, p = 0;
            if(p == 3) sp++, p = 0;
        }
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}