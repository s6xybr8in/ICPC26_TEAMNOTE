/**
 * Author: s6xybr8in
 * Date: 2026-09-16
 * Description: 1-indexed Persistent Segment Tree with point update and range query. Roots store
 * version pointers.
 * Time: O(\log N) per update/query, Memory: O(N \log N)
 * Status: tested
 */
#pragma once

struct PST {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a + b; }

	struct Node {
		int lc = 0, rc = 0;
		T val = unit;
	};

	int n;
	vector<Node> tree;
	vector<int> roots;

	PST(int n = 0, int q_est = 0) : n(n) {
		tree.reserve(q_est ? q_est * 20 : 1);
		tree.push_back({0, 0, unit});
		roots.push_back(0);
	}

	int update(int prev, int s, int e, int pos, T val) {
		int cur = tree.size();
		tree.push_back(tree[prev]);
		if (s == e) {
			tree[cur].val = val;
			return cur;
		}
		int mid = (s + e) / 2;
		if (pos <= mid)
			tree[cur].lc = update(tree[prev].lc, s, mid, pos, val);
		else
			tree[cur].rc = update(tree[prev].rc, mid + 1, e, pos, val);
		tree[cur].val = f(tree[tree[cur].lc].val, tree[tree[cur].rc].val);
		return cur;
	}
	int update(int prev_root, int pos, T val) {
		int nroot = update(prev_root, 1, n, pos, val);
		roots.push_back(nroot);
		return nroot;
	}

	T query(int node, int s, int e, int l, int r) {
		if (!node || r < s || e < l) return unit;
		if (l <= s && e <= r) return tree[node].val;
		int mid = (s + e) / 2;
		return f(query(tree[node].lc, s, mid, l, r), query(tree[node].rc, mid + 1, e, l, r));
	}
	T query(int root, int l, int r) { return query(root, 1, n, l, r); }
};