/**
 * Author: Green Siro
 * License: CC0
 * Description: 0-indexed directed/undirected Euler trail from start. Returns vertices or empty
 * on failure; no edges -> {start}. Time: O(V+E). Each undirected edge is added once.
 */
#pragma once

struct EulerWalk {
	bool directed;
	int edges = 0;
	vector<vector<pair<int, int>>> g;
	vector<int> degree;
	EulerWalk(int n, bool directed = false) : directed(directed), g(n), degree(n) {}
	void addEdge(int u, int v) {
		g[u].push_back({v, edges});
		if (directed)
			++degree[u], --degree[v];
		else
			g[v].push_back({u, edges}), ++degree[u], ++degree[v];
		++edges;
	}
	vector<int> walk(int start) const {
		int special = 0;
		for (int u = 0; u < (int)g.size(); ++u) {
			if (directed) {
				if (abs(degree[u]) > 1) return {};
				special += degree[u] != 0;
			} else
				special += degree[u] % 2;
		}
		if (special != 0 && special != 2) return {};
		if (special && (directed ? degree[start] != 1 : degree[start] % 2 != 1)) return {};
		vector<int> pos(g.size()), stack{start}, ans;
		vector<bool> used(edges);
		while (!stack.empty()) {
			int u = stack.back();
			while (pos[u] < (int)g[u].size() && used[g[u][pos[u]].second]) ++pos[u];
			if (pos[u] == (int)g[u].size()) {
				ans.push_back(u);
				stack.pop_back();
			} else {
				auto [v, id] = g[u][pos[u]++];
				used[id] = true;
				stack.push_back(v);
			}
		}
		if ((int)ans.size() != edges + 1) return {};
		reverse(ans.begin(), ans.end());
		return ans;
	}
};
