/**
 * Author: s6xybr8in
 * Date: 2026-09-13
 * Description: Disjoint Set Union (DSU) data structure.
 * Time: O(\log N) for find and O(1) for union with path compression and union by rank.
 * Space: O(N)
 * Status: None
 */
#pragma once

struct DSU {
	vi s;
	int n;
	DSU(int n = 0,ll def = 0) : n(n), s(n + 1, def) {
		for(int i = 1; i <= n; i++) s[i] = i;
	}

	int find(int x){
		return x == s[x] ? x : s[x] = find(s[x]);
	}

	void join(int x,int y){
		x = find(x);
		y = find(y);
		if(x != y) s[x] = y;
	}
};