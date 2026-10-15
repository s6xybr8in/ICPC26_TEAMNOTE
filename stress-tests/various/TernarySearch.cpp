#include <cassert>
#include "../utilities/template.h"
#include "../../content/various/TernarySearch.h"

int main() {
	mt19937 rng(12345);
	for (int it = 0; it < 1000; ++it) {
		int n = 1 + rng() % 100, a = rng() % n, b = rng() % n;
		if (a > b) swap(a, b);
		vector<ll> v(n);
		for (int i = a - 1; i >= 0; --i) v[i] = v[i + 1] + 1 + rng() % 100;
		for (int i = b + 1; i < n; ++i) v[i] = v[i - 1] + 1 + rng() % 100;
		for (int q = 0; q < 30; ++q) {
			int l = rng() % n, r = rng() % n;
			if (l > r) swap(l, r);
			auto f = [&](ll x) { return v[x]; };
			ll x = ternaryInt(l, r, f);
			assert(l <= x && x <= r);
			assert(f(x) == *min_element(v.begin() + l, v.begin() + r + 1));
		}
		long double l = -100, r = 100, c = (int)(rng() % 1000) - 500;
		auto f = [&](long double x) { return (x - c) * (x - c); };
		long double x = ternaryReal(l, r, f);
		assert(l <= x && x <= r);
		assert(fabsl(x - clamp(c, l, r)) < 1e-5L);
		assert(ternaryReal(c, c, f) == c);
	}
	for (ll l : {LLONG_MIN, LLONG_MAX - 100}) {
		ll r = l + 100;
		auto f = [&](ll x) { return (x - l - 60) * (x - l - 60); };
		assert(ternaryInt(l, r, f) == l + 60);
	}
	cout << "Ternary search tests passed!\n";
}
