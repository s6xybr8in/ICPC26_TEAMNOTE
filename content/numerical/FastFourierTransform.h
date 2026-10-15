/**
 * Author: Green Siro
 * License: CC0
 * Description: Integer convolution via complex<double>. Precision depends on size/magnitude;
 * use NTT for exact modular answers. Values and answers must fit ll. Time: O(N log N).
 */
#pragma once

namespace FFT {
using C = complex<double>;
void transform(vector<C> &a, bool inverse) {
	int n = (int)a.size();
	for (int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len *= 2) {
		double angle = 2 * acos(-1.0) / len * (inverse ? -1 : 1);
		C root = polar(1.0, angle);
		for (int i = 0; i < n; i += len) {
			C w = 1;
			for (int j = 0; j < len / 2; ++j, w *= root) {
				C u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
			}
		}
	}
	if (inverse)
		for (C &x : a) x /= n;
}
vector<ll> convolution(const vector<ll> &a, const vector<ll> &b) {
	if (a.empty() || b.empty()) return {};
	int size = (int)(a.size() + b.size() - 1), n = 1;
	while (n < size) n *= 2;
	vector<C> x(n), y(n);
	copy(a.begin(), a.end(), x.begin());
	copy(b.begin(), b.end(), y.begin());
	transform(x, false);
	transform(y, false);
	for (int i = 0; i < n; ++i) x[i] *= y[i];
	transform(x, true);
	vector<ll> ans(size);
	for (int i = 0; i < size; ++i) ans[i] = llround(x[i].real());
	return ans;
}
} // namespace FFT
