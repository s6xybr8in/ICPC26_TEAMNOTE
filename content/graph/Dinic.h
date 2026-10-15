/**
 * Author: Green Siro
 * License: CC0
 * Description: 0-indexed directed max flow, nonnegative capacities. maxflow(s,t) returns
 * additional flow; s != t. Residual cap>0 reachability from s gives a min cut. Time: O(V^2 E).
 * Recursive DFS: watch stack depth.
 */
#pragma once

struct Dinic {
	struct Edge {
		int to, rev;
		ll cap;
	};
	vector<vector<Edge>> g;
	vector<int> level, ptr;
	Dinic(int n) : g(n), level(n), ptr(n) {}
	void addEdge(int u, int v, ll cap) {
		int a = (int)g[u].size(), b = (int)g[v].size();
		g[u].push_back({v, b + (u == v), cap});
		g[v].push_back({u, a, 0});
	}
	bool bfs(int s, int t) {
		fill(level.begin(), level.end(), -1);
		queue<int> q;
		q.push(s);
		level[s] = 0;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (auto e : g[u])
				if (e.cap && level[e.to] < 0) level[e.to] = level[u] + 1, q.push(e.to);
		}
		return level[t] >= 0;
	}
	ll dfs(int u, int t, ll f) {
		if (u == t) return f;
		for (int &i = ptr[u]; i < (int)g[u].size(); ++i) {
			Edge &e = g[u][i];
			if (e.cap && level[e.to] == level[u] + 1) {
				ll got = dfs(e.to, t, min(f, e.cap));
				if (got) {
					e.cap -= got;
					g[e.to][e.rev].cap += got;
					return got;
				}
			}
		}
		return 0;
	}
	ll maxflow(int s, int t) {
		assert(s != t);
		ll ans = 0;
		while (bfs(s, t)) {
			fill(ptr.begin(), ptr.end(), 0);
			while (ll f = dfs(s, t, LLONG_MAX)) ans += f;
		}
		return ans;
	}
};
