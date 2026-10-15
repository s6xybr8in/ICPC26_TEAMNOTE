#include <cassert>
#include "../utilities/template.h"
#include "../../content/graph/CentroidDecomposition.h"

void check(const vector<vector<int>> &g, int root) {
	int n = (int)g.size();
	auto before = g;
	CentroidDecomposition cd(g, root);
	assert(before == g);
	assert(count(cd.parent.begin(), cd.parent.end(), -1) == 1);
	for (int c = 0; c < n; ++c) {
		vector<bool> blocked(n);
		int depth = 0;
		for (int u = cd.parent[c]; u != -1; u = cd.parent[u]) {
			assert(u >= 0 && u < n && !blocked[u]);
			blocked[u] = true;
			++depth;
		}
		assert(depth <= 1 + (int)log2(n));
		auto component = [&](int start) {
			vector<int> order{start};
			vector<bool> seen = blocked;
			seen[start] = true;
			for (int i = 0; i < (int)order.size(); ++i)
				for (int v : g[order[i]])
					if (!seen[v]) {
						seen[v] = true;
						order.push_back(v);
					}
			return (int)order.size();
		};
		int total = component(c);
		blocked[c] = true;
		for (int v : g[c])
			if (!blocked[v]) assert(component(v) <= total / 2);
	}
}
int main() {
	mt19937 rng(123);
	for (int it = 0; it < 300; ++it) {
		int n = 1 + rng() % 100;
		vector<vector<int>> g(n);
		for (int u = 1; u < n; ++u) {
			int p = rng() % u;
			g[u].push_back(p);
			g[p].push_back(u);
		}
		check(g, rng() % n);
	}
	for (bool star : {false, true}) {
		int n = 2000;
		vector<vector<int>> g(n);
		for (int u = 1; u < n; ++u) {
			int p = star ? 0 : u - 1;
			g[p].push_back(u);
			g[u].push_back(p);
		}
		check(g, n - 1);
	}
	cout << "Centroid decomposition tests passed!\n";
}
