#include <cplib/general.h>
using namespace std;

void testcase() {
    string s; rd(s);
    bool place = false;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '1') place = true;
        else if(s[i] == '0') place = false;
        else s[i] = place ? '1' : '0';
    }
    cout << s << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) testcase();
}