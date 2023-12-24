#pragma once
// start
#include <cplib/general.h>
using P = std::pair<ll, ll>;
P operator+(const P& a, const P& b) { return P(a.first + b.first, a.second + b.first); }
P operator-(const P& a, const P& b) { return P(a.first - b.first, a.second - b.second); }
ll cross(const P& a, const P& b) {
    return a.first * b.second - a.second * b.first; 
}

std::vector<P> convHull(std::vector<P> v) {
    std::vector<P> hull;
    for(int i = 0; i < v.size(); i++) {
        while(hull.size() >= 2 && cross(hull.end()[-1] - v[i], hull.end()[-2] - v[i]) <= 0) {
            hull.pop_back();
        }
        hull.pb(v[i]);
    }
    return hull;
}