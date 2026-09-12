/**
 * Author: s6xybr8in
 * Date: 2026-09-12
 * Description: 1-indexed recursive segment tree with point update and range query.
 * Time: O(\log N)
 * Status: tested
 */
#pragma once

struct Tree {
	vi tree;
	int n;
	Tree(int n = 0,ll def = 0) : n(n), tree(n + 1, def) {}

	void update(int pos,int diff){
		for(int i=pos; i <= n; i += i & -i) tree[i] += diff;
	}

	ll query(int pos){
		ll sum = 0;
		for(int i=pos; i > 0; i -= i & -i) sum += tree[i];
		return sum;
	}
	ll query(int l,int r){
		return query(r) - query(l-1);
	}
};