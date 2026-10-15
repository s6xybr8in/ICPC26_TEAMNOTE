/**
 * Author: Green Siro
 * License: CC0
 * Description: Connected nonempty tree, 0-indexed. Vertex path segments [l,r]; callback order
 * is unspecified. Use only commutative aggregates with path(). edge=true excludes the LCA (edge
 * value stored at child). Subtree [pos[u],pos[u]+sz[u]-1]. O(log N) segments.
 * Reorders g: g[u][0] is the largest child when u has a child. Parent edges are kept.
 */
#pragma once

struct HLD {
	vector<int> par, dep, sz, head, in;
	HLD(vector<vector<int>> &g, int root = 0) {
		int n = (int)g.size();
		par.assign(n, -1);
		dep.resize(n);
		sz.assign(n, 1);
		head.resize(n);
		in.resize(n);
		vector<int> order{root};
		par[root] = root;
		for (int i = 0; i < n; ++i) {
			int u = order[i];
			for (int v : g[u])
				if (v != par[u]) {
					par[v] = u;
					dep[v] = dep[u] + 1;
					order.push_back(v);
				}
		}
		for (int i = n - 1; i >= 0; --i) {
			int u = order[i], best = -1;
			for (int j = 0; j < (int)g[u].size(); ++j) {
				int v = g[u][j];
				if (v == par[u]) continue;
				sz[u] += sz[v];
				if (best == -1 || sz[v] > sz[g[u][best]]) best = j;
			}
			if (best != -1) swap(g[u][0], g[u][best]);
		}
		int timer = 0;
		vector<pair<int, int>> st{{root, root}};
		while (!st.empty()) {
			auto [u, h] = st.back();
			st.pop_back();
			head[u] = h;
			in[u] = timer++;
			for (int i = (int)g[u].size() - 1; i >= 0; --i) {
				int v = g[u][i];
				if (v != par[u]) st.push_back({v, i == 0 ? h : v});
			}
		}
	}
	template <class F> void path(int u, int v, F f, bool edge = false) {
		while (head[u] != head[v]) {
			if (dep[head[u]] < dep[head[v]]) swap(u, v);
			f(in[head[u]], in[u]);
			u = par[head[u]];
		}
		if (dep[u] > dep[v]) swap(u, v);
		if (in[u] + edge <= in[v]) f(in[u] + edge, in[v]);
	}
};
