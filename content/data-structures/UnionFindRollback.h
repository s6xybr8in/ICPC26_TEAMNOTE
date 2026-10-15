/**
 * Author: Green Siro
 * License: CC0
 * Description: 0-indexed DSU; snapshot() then rollback(snapshot). No path compression. Time:
 * O(log N) find/join.
 */
#pragma once

struct RollbackDSU {
	vector<int> p;
	vector<array<int, 4>> history;
	int components;
	RollbackDSU(int n) : p(n, -1), components(n) {}
	int find(int x) const { return p[x] < 0 ? x : find(p[x]); }
	int snapshot() const { return (int)history.size(); }
	bool join(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return false;
		if (p[a] > p[b]) swap(a, b);
		history.push_back({a, p[a], b, p[b]});
		p[a] += p[b];
		p[b] = a;
		--components;
		return true;
	}
	void rollback(int t) {
		while (snapshot() > t) {
			auto h = history.back();
			history.pop_back();
			p[h[0]] = h[1];
			p[h[2]] = h[3];
			++components;
		}
	}
};
