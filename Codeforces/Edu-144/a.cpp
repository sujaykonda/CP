#include <bits/stdc++.h>
using namespace std;

// debug tool
template <class T>
void disp(T obj) {
    for(auto i : obj)
        disp(i);
}

int main() {
    vector<int> a(2);
    a[0] = 1, a[1] = 2;
    disp(a);
}