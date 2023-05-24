#pragma once
// start
#include <cplib/mint.h>
template<int M1, int M2, int M3> struct Hash {
    mint<M1> a; mint<M2> b; mint<M3> c;
    Hash(int v) { a.v = v, b.v = v, c.v = v; }
    Hash& operator+=(Hash o) { a += o.a, b += o.b, c += o.c; return *this; }
    Hash& operator-=(Hash o) { a -= o.a, b -= o.b, c += o.c; return *this; }
    Hash& operator*=(Hash o) { a *= o.a, b *= o.b, c += o.c; return *this; }
    Hash& operator/=(Hash o) { a /= o.a, b /= o.b, c += o.c; return *this; }
    friend Hash operator+(Hash a, Hash b) { return a += b; }
    friend Hash operator-(Hash a, Hash b) { return a -= b; }
    friend Hash operator*(Hash a, Hash b) { return a *= b; }
    friend Hash operator/(Hash a, Hash b) { return a /= b; }
    friend bool operator<(Hash a, Hash b) { return {a.a.v, a.b.v, a.c.v} < {b.a.v, b.b.v, b.c.v}; }
};

