#pragma once
// start
#include <cplib/general.h>

template<typename func>
ll bsmin(ll lo, ll hi, func f)
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

template<typename func>
ll bsmax(ll lo, ll hi, func f)
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
