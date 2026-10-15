/**
 * Author: Green Siro
 * License: CC0
 * Description: Connected nonempty tree, 0-indexed; root parent=root. up[k][u] is the 2^k
 * ancestor; kth returns -1 above root. tin/tout: subtree [tin[u],tout[u]]. Time: O(N log N)
 * build, O(log N) LCA/kth.
 */
#pragma once

struct LCA {
	int n, lg = 1;
	vector<vector<int>> up;
	vector<int> depth, tin, tout;
	LCA(const vector<vector<int>> &g, int root = 0)
	    : n((int)g.size()), depth(n), tin(n), tout(n) {
		while ((1LL << lg) <= n) ++lg;
		up.assign(lg, vector<int>(n, root));
		vector<int> order{root};
		for (int i = 0; i < n; ++i) {
			int u = order[i];
			for (int v : g[u])
				if (v != up[0][u]) {
					up[0][v] = u;
					depth[v] = depth[u] + 1;
					order.push_back(v);
				}
		}
		for (int k = 1; k < lg; ++k)
			for (int u = 0; u < n; ++u) up[k][u] = up[k - 1][up[k - 1][u]];
		int timer = 0;
		vector<pair<int, bool>> st{{root, false}};
		while (!st.empty()) {
			auto [u, exit] = st.back();
			st.pop_back();
			if (exit) {
				tout[u] = timer - 1;
				continue;
			}
			tin[u] = timer++;
			st.push_back({u, true});
			for (int v : g[u])
				if (v != up[0][u]) st.push_back({v, false});
		}
	}
	int kth(int u, int k) const {
		if (k < 0 || k > depth[u]) return -1;
		for (int b = 0; b < lg; ++b)
			if (k >> b & 1) u = up[b][u];
		return u;
	}
	int lca(int a, int b) const {
		if (depth[a] < depth[b]) swap(a, b);
		a = kth(a, depth[a] - depth[b]);
		if (a == b) return a;
		for (int k = lg - 1; k >= 0; --k)
			if (up[k][a] != up[k][b]) a = up[k][a], b = up[k][b];
		return up[0][a];
	}
	int dist(int a, int b) const { return depth[a] + depth[b] - 2 * depth[lca(a, b)]; }
	bool ancestor(int a, int b) const { return tin[a] <= tin[b] && tin[b] <= tout[a]; }
};
