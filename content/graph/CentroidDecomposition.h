/**
 * Author: Green Siro
 * License: CC0
 * Source: Algorithm reference: https://usaco.guide/plat/centroid
 * Description: 0-indexed connected nonempty tree. parent stores the centroid tree;
 * its root has parent=-1. Recursive DFS may use O(N) stack space on a chain.
 * Time: O(N log N).
 */
#pragma once

struct CentroidDecomposition {
	const vector<vector<int>> &g;
	vector<int> par, sz;
	vector<bool> removed;

	CentroidDecomposition(const vector<vector<int>> &g, int root = 0)
	    : g(g), par(g.size(), -1), sz(g.size()), removed(g.size()) {
		build(root, -1);
	}

	int calcSize(int u, int p) {
		sz[u] = 1;
		for (int v : g[u])
			if (v != p && !removed[v]) sz[u] += calcSize(v, u);
		return sz[u];
	}

	int findCentroid(int u, int p, int total) {
		for (int v : g[u])
			if (v != p && !removed[v] && sz[v] > total / 2) return findCentroid(v, u, total);
		return u;
	}

	void build(int u, int p) {
		int total = calcSize(u, -1);
		int c = findCentroid(u, -1, total);
		par[c] = p;
		removed[c] = true;
		// Process paths through c here, before recursing.
		for (int v : g[c])
			if (!removed[v]) build(v, c);
	}
};
