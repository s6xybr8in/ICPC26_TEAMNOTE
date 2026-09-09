/**
 * Author: s6xybr8in
 * Date: 2026-09-09
 * Description: 1-indexed recursive segment tree with point update and range query.
 * Time: O(\log N)
 * Status: none
 */
#pragma once

struct Tree {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a + b; } // (any associative fn)
	int n;
	vector<T> tree;
	Tree(int n = 0, T def = unit) : n(n), tree(4 * n + 5, def) {}

	void update(int node, int s, int e,int pos, T val) {
		if (s == e) { tree[node] = val; return; }
		int mid = (s + e) / 2;
		if (pos <= mid) update(node * 2, s, mid, pos, val);
		else update(node * 2 + 1, mid + 1, e, pos, val);
		tree[node] = f(tree[node * 2], tree[node * 2 + 1]);
	}
	void update(int pos, T val) { update(1, 1, n, pos, val); }

	T query(int node, int s, int e, int l, int r) {
		if (r < s || e < l) return unit;
		if (l <= s && e <= r) return tree[node];
		int mid = (s + e) / 2;
		return f(query(node * 2, s, mid, l, r),
		         query(node * 2 + 1, mid + 1, e, l, r));
	}
	T query(int l, int r) { return query(1, 1, n, l, r); }
};