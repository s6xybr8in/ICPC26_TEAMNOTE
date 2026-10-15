/**
 * Author: Green Siro
 * License: CC0
 * Description: Deterministic Miller-Rabin for uint64\_t, randomized Pollard-Rho factorization
 * n>=1. Uses unsigned \_\_int128. Factors sorted with multiplicity. Expected O(n^(1/4)) modular
 * operations for Rho; no worst-case guarantee.
 */
#pragma once

namespace Factor64 {
using U = uint64_t;
U mul(U a, U b, U m) { return (U)((__uint128_t)a * b % m); }
U power(U a, U e, U m) {
	U r = 1;
	for (; e; e >>= 1, a = mul(a, a, m))
		if (e & 1) r = mul(r, a, m);
	return r;
}
bool prime(U n) {
	if (n < 2) return false;
	for (U p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL})
		if (n % p == 0) return n == p;
	U d = n - 1;
	int s = 0;
	while (!(d & 1)) d >>= 1, ++s;
	for (U a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
		if (a % n == 0) continue;
		U x = power(a % n, d, n);
		if (x == 1 || x == n - 1) continue;
		bool ok = false;
		for (int r = 1; r < s; ++r) {
			x = mul(x, x, n);
			if (x == n - 1) {
				ok = true;
				break;
			}
		}
		if (!ok) return false;
	}
	return true;
}
U rho(U n) {
	if (n % 2 == 0) return 2;
	static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
	for (;;) {
		U c = 1 + rng() % (n - 1), x = rng() % n, y = x, d = 1;
		auto f = [&](U v) { return (U)(((__uint128_t)mul(v, v, n) + c) % n); };
		while (d == 1) {
			x = f(x);
			y = f(f(y));
			d = gcd(x > y ? x - y : y - x, n);
		}
		if (d != n) return d;
	}
}
void split(U n, vector<U> &out) {
	if (n == 1) return;
	if (prime(n)) {
		out.push_back(n);
		return;
	}
	U d = rho(n);
	split(d, out);
	split(n / d, out);
}
vector<U> factor(U n) {
	assert(n >= 1);
	vector<U> out;
	split(n, out);
	sort(out.begin(), out.end());
	return out;
}
} // namespace Factor64
