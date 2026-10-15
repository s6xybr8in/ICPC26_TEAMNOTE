/**
 * Author: Green Siro
 * License: CC0
 * Description: 0-indexed bipartite matching. addEdge(left,right). minCover() returns (left
 * IDs,right IDs) after maxMatching. Time: O(E sqrt(V)); recursive augmenting DFS.
 */
#pragma once

struct HopcroftKarp {
	int n, m;
	vector<vector<int>> g;
	vector<int> left, right, dist;
	HopcroftKarp(int n, int m) : n(n), m(m), g(n), left(n, -1), right(m, -1), dist(n) {}
	void addEdge(int u, int v) { g[u].push_back(v); }
	int shortest;
	bool bfs() {
		queue<int> q;
		shortest = INT_MAX;
		fill(dist.begin(), dist.end(), -1);
		for (int u = 0; u < n; ++u)
			if (left[u] < 0) dist[u] = 0, q.push(u);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			if (dist[u] >= shortest) continue;
			for (int v : g[u]) {
				int w = right[v];
				if (w < 0)
					shortest = dist[u] + 1;
				else if (dist[w] < 0)
					dist[w] = dist[u] + 1, q.push(w);
			}
		}
		return shortest != INT_MAX;
	}
	bool dfs(int u) {
		for (int v : g[u]) {
			int w = right[v];
			if ((w < 0 && dist[u] + 1 == shortest) || (w >= 0 && dist[w] == dist[u] + 1 && dfs(w))) {
				left[u] = v;
				right[v] = u;
				return true;
			}
		}
		dist[u] = -1;
		return false;
	}
	int maxMatching() {
		while (bfs())
			for (int u = 0; u < n; ++u)
				if (left[u] < 0) dfs(u);
		return n - (int)count(left.begin(), left.end(), -1);
	}
	pair<vector<int>, vector<int>> minCover() const {
		vector<bool> a(n), b(m);
		queue<int> q;
		for (int u = 0; u < n; ++u)
			if (left[u] < 0) a[u] = true, q.push(u);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int v : g[u])
				if (v != left[u] && !b[v]) {
					b[v] = true;
					int w = right[v];
					if (w >= 0 && !a[w]) a[w] = true, q.push(w);
				}
		}
		pair<vector<int>, vector<int>> ans;
		for (int u = 0; u < n; ++u)
			if (!a[u]) ans.first.push_back(u);
		for (int v = 0; v < m; ++v)
			if (b[v]) ans.second.push_back(v);
		return ans;
	}
};
