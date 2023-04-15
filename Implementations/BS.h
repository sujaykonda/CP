#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#pragma once

ll bsmin(ll lo, ll hi, function<bool(ll)> f)
{
    hi++;
    while (lo < hi)
    {
        ll mid = lo + (hi - lo) / 2;
        if (f(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

ll bsmax(ll lo, ll hi, function<bool(ll)> f)
{
    lo--;
    while (hi > lo)
    {
        ll mid = (hi + lo + 1) / 2;
        if (f(mid))
            lo = mid;
        else
            hi = mid - 1;
    }
    return lo;
}
