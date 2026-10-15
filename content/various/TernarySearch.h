/**
 * Author: Green Siro
 * License: CC0
 * Description: Argmin on closed [l,r], l<=r. Function must strictly decrease, possibly
 * have a flat minimum, then strictly increase. Monotone functions also work.
 * Integer version requires r-l to fit ll. Real version uses 200 iterations; precision
 * depends on the interval scale and floating-point rounding. For maximum, negate f.
 * Usage: ll x = ternaryInt(l, r, f); // minimum value is f(x)
 * long double y = ternaryReal(l, r, f);
 * Time: O(log(r-l+1)) integer / 200 iterations real; O(1) per f evaluation assumed.
 */
#pragma once

template <class F> ll ternaryInt(ll l, ll r, F f) {
	while (r - l > 3) {
		ll d = (r - l) / 3, a = l + d, b = r - d;
		if (f(a) <= f(b))
			r = b - 1;
		else
			l = a + 1;
	}
	ll best = l;
	for (ll x = l; x < r;) {
		++x;
		if (f(x) < f(best)) best = x;
	}
	return best;
}

template <class F> long double ternaryReal(long double l, long double r, F f) {
	for (int it = 0; it < 200; ++it) {
		long double d = (r - l) / 3, a = l + d, b = r - d;
		if (f(a) <= f(b))
			r = b;
		else
			l = a;
	}
	return l + (r - l) / 2;
}
