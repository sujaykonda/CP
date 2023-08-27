#include <cplib/general.h>
using namespace std;

void tc() {
    string s; rd(s);
    if(s == "()") {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        if(s.find(")(") == string::npos) {
            string a = "";
            for(int i = 0; i < s.length(); i++) {
                a += "()";
            }
            cout << a << endl;
        } else {
            string a = "";
            for(int i = 0; i < s.length(); i++) {
                a += "(";
            }
            for(int i = 0; i < s.length(); i++) {
                a += ")";
            }
            cout << a << endl;
        }
    }
}

int main() {
    int t; rd(t);
    while(t--) tc();
}