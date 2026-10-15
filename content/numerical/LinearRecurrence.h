/**
 * Author: Green Siro
 * License: CC0
 * Description: a[n] = c[0]*a[n-1]+...+c[k-1]*a[n-k]. init has k>=1 values, c same size. n>=0,
 * mod>0. Normalize inputs to [0,mod-1]. Time: O(k^2 log n).
 */
#pragma once

ll linearRecurrence(const vector<ll> &init, const vector<ll> &c, ll n, ll mod) {
	int k = (int)c.size();
	assert(k > 0 && (int)init.size() == k);
	auto combine = [&](const vector<ll> &a, const vector<ll> &b) {
		vector<ll> t(2 * k - 1);
		for (int i = 0; i < k; ++i)
			for (int j = 0; j < k; ++j) t[i + j] = (ll)((t[i + j] + (__int128)a[i] * b[j]) % mod);
		for (int i = 2 * k - 2; i >= k; --i)
			for (int j = 1; j <= k; ++j)
				t[i - j] = (ll)((t[i - j] + (__int128)t[i] * c[j - 1]) % mod);
		t.resize(k);
		return t;
	};
	vector<ll> ans(k), x(k);
	ans[0] = 1 % mod;
	if (k == 1)
		x[0] = c[0];
	else
		x[1] = 1;
	for (; n; n >>= 1, x = combine(x, x))
		if (n & 1) ans = combine(ans, x);
	ll out = 0;
	for (int i = 0; i < k; ++i) out = (ll)((out + (__int128)ans[i] * init[i]) % mod);
	return out;
}
