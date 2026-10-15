/**
 * Author: Green Siro
 * License: CC0
 * Description: One layer: cur[j]=min(prev[k]+cost(k,j-1)), k<j. States count prefix lengths;
 * cost uses closed ranges. j=1..n, prev[0..n]; monotone optimal k required. INF=LLONG\_MAX/4,
 * finite sums must stay in (-INF,INF).
 * Time: O(N log N) cost calls per layer.
 */
#pragma once

template <class Cost> vector<ll> divideConquerDP(const vector<ll> &prev, Cost cost) {
	int n = (int)prev.size() - 1;
	const ll inf = LLONG_MAX / 4;
	vector<ll> cur(n + 1, inf);
	auto solve = [&](auto &self, int l, int r, int a, int b) -> void {
		if (l > r) return;
		int mid = (l + r) / 2, best = a;
		for (int k = a; k <= min(b, mid - 1); ++k)
			if (prev[k] != inf) {
				ll v = prev[k] + cost(k, mid - 1);
				if (v < cur[mid]) cur[mid] = v, best = k;
			}
		self(self, l, mid - 1, a, best);
		self(self, mid + 1, r, best, b);
	};
	solve(solve, 1, n, 0, n - 1);
	return cur;
}
