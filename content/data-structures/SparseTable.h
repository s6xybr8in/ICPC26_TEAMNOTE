/**
 * Author: Green Siro
 * License: CC0
 * Description: Static range minimum, 0-indexed nonempty [l,r]. Time: O(N log N) build, O(1)
 * query.
 */
#pragma once

struct SparseTable {
	vector<vector<ll>> st;
	SparseTable(const vector<ll> &a) {
		int n = (int)a.size();
		if (!n) return;
		st.push_back(a);
		for (int k = 1; (1LL << k) <= n; ++k) {
			st.emplace_back(n - (1 << k) + 1);
			for (int i = 0; i + (1 << k) <= n; ++i)
				st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
		}
	}
	ll query(int l, int r) const {
		int k = 31 - __builtin_clz((unsigned)(r - l + 1));
		return min(st[k][l], st[k][r - (1 << k) + 1]);
	}
};
