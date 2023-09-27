#include <bits/stdc++.h>
using namespace std;

vector<vector<bool>> adj;

bool are_connected(vector<int> a, vector<int> b) {
    for(int i : a) {
        for(int j : b) {
            if(adj[i][j]) {
                return true;
            }
        }
    }
    return false;
}

int bsmin(vector<int> A, vector<int> B) {
    int l = 0, r = A.size();
    while(l < r) {
        int m = l + (r - l) / 2;
        vector<int> C;
        for(int i = l; i <= m; i++) C.push_back(A[i]);
        if(are_connected(C, B)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

vector<int> longest_trip(int N, int D) {
    vector<int> o(N);
    for(int i = 0; i < N; i++) o[i] = i;
    int rng = N - 1;
    while(rng % 2 == 0) rng /= 2;
    for(int i = 0; i < N; i++) swap(o[i], o[(i * i * rng) % N]);
    vector<int> A, B;
    A.push_back(o[0]);
    bool not_con = false;
    for(int i = 1; i < N; i++) {
        if(are_connected({A.back()}, {o[i]})) {
            A.push_back(o[i]);
            not_con = false;
        } else {
            if(B.size() == 0 || not_con) {
                B.push_back(o[i]);
                not_con = true;
            } else {
                if(are_connected({B.back()}, {o[i]})) {
                    B.push_back(o[i]);
                    not_con = true;
                } else {
                    while(B.size() > 0) {
                        A.push_back(B.back());
                        B.pop_back();
                    }
                    B.push_back(o[i]);
                    not_con = false;
                }
            }
        }
    }
    if(A.size() < B.size()) swap(A, B);
    if(B.empty()) return A;
    if(are_connected({A[0]}, {B[0]})) reverse(A.begin(), A.end());
    if(are_connected({A.back()}, {B.back()})) reverse(B.begin(), B.end());
    if(are_connected({A[0]}, {B.back()})) reverse(A.begin(), A.end()), reverse(B.begin(), B.end());
    if(are_connected({A.back()}, {B[0]})) {
        for(int i : B) A.push_back(i);
        return A;
    }
    if(are_connected(A, B)) {
        int j = bsmin(A, B);
        int k = bsmin(B, {A[j]});
        rotate(A.begin(), A.begin() + (j + 1) % A.size(), A.end());
        rotate(B.begin(), B.begin() + k, B.end());
        for(int i : B) A.push_back(i);
        return A;
    }
    return A;
}

int main() {
    adj = vector<vector<bool>>(10, vector<bool>(10));
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            for(int k = 0; k < 10; k++) {
                if(i != j && j != k && k != i) {
                    if(!adj[i][j] && !adj[j][k] && !adj[k][i]) {
                        adj[k][i] = adj[i][k] = true;
                    }
                }
            }
        }
    }
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
    vector<int> a = longest_trip(10, 3);
    for(int i : a) cout << i << " ";
    cout << endl;
    for(int i = 1; i < a.size(); i++) {
        if(!adj[a[i]][a[i - 1]]) {
            cout << "BAD " << a[i - 1] << " " << a[i] << endl;
            return 0;
        }
    }
}