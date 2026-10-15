/**
 * Author: s6xybr8in
 * Date: 2026-09-12
 * Description: 1-indexed Fenwick tree: point add, inclusive range sum.
 * Time: O(\log N)
 * Status: tested
 */
#pragma once

struct FenwickTree {
	int n;
	vector<ll> tree;
	FenwickTree(int n = 0, ll def = 0) : n(n), tree(n + 1, def) {}

	void update(int i, int diff) {
		for (; i <= n; i += i & -i) tree[i] += diff;
	}

	ll query(int i) {
		ll sum = 0;
		for (; i > 0; i -= i & -i) sum += tree[i];
		return sum;
	}
	ll query(int l, int r) { return query(r) - query(l - 1); }
};