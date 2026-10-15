/**
 * Author: s6xybr8in
 * Date: 2026-09-13
 * Description: Disjoint Set Union (DSU) data structure.
 * Time: Amortized O(alpha(N)) with path compression and union by size.
 * Memory: O(N)
 * Status: stress-tested
 */
#pragma once

struct DSU {
	int n;
	vector<int> s, size;
	DSU(int n = 0) : n(n), s(n + 1), size(n + 1, 1) {
		for (int i = 1; i <= n; i++) s[i] = i;
	}

	int find(int x) { return x == s[x] ? x : s[x] = find(s[x]); }

	void join(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) return;
		if (size[x] < size[y]) swap(x, y);
		s[y] = x;
		size[x] += size[y];
	}
};
