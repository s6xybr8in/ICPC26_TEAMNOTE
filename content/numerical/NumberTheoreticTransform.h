/**
 * Author: Green Siro
 * License: CC0
 * Description: Convolution mod 998244353; primitive root 3. Inputs normalized to [0,mod-1].
 * Result length <= 2^23. Time: O(N log N), memory O(N).
 */
#pragma once

namespace NTT {
const int mod = 998244353;
int power(ll a, int e) {
	ll r = 1;
	for (; e; e >>= 1, a = a * a % mod)
		if (e & 1) r = r * a % mod;
	return (int)r;
}
void transform(vector<int> &a, bool inverse) {
	int n = (int)a.size();
	for (int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len *= 2) {
		int root = power(3, (mod - 1) / len);
		if (inverse) root = power(root, mod - 2);
		for (int i = 0; i < n; i += len) {
			ll w = 1;
			for (int j = 0; j < len / 2; ++j, w = w * root % mod) {
				int u = a[i + j], v = (int)(a[i + j + len / 2] * w % mod);
				a[i + j] = u + v;
				if (a[i + j] >= mod) a[i + j] -= mod;
				a[i + j + len / 2] = u - v;
				if (a[i + j + len / 2] < 0) a[i + j + len / 2] += mod;
			}
		}
	}
	if (inverse) {
		ll inv = power(n, mod - 2);
		for (int &x : a) x = (int)(x * inv % mod);
	}
}
vector<int> convolution(vector<int> a, vector<int> b) {
	if (a.empty() || b.empty()) return {};
	int size = (int)(a.size() + b.size() - 1), n = 1;
	while (n < size) n *= 2;
	assert(n <= (1 << 23));
	a.resize(n);
	b.resize(n);
	transform(a, false);
	transform(b, false);
	for (int i = 0; i < n; ++i) a[i] = (int)(1LL * a[i] * b[i] % mod);
	transform(a, true);
	a.resize(size);
	return a;
}
} // namespace NTT
