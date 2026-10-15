/**
 * Author: Green Siro
 * License: CC0
 * Description: Minimum line query at integer x in inclusive [lo,hi]. Set domain to actual query
 * coordinate bounds. Values evaluated in __int128. Empty result=2^126. Time: O(log(domain
 * width)) per add/query.
 */
#pragma once

struct LiChaoTree {
	using I = __int128;
	struct Line {
		ll m, b;
		I eval(ll x) const { return (I)m * x + b; }
	};
	struct Node {
		Line line;
		int left = -1, right = -1;
	};
	vector<Node> t;
	ll lo, hi;
	static constexpr I inf = (I)1 << 126;
	LiChaoTree(ll lo, ll hi) : lo(lo), hi(hi) { assert(lo <= hi); }
	void add(ll m, ll b) {
		if (t.empty())
			t.push_back({{m, b}, -1, -1});
		else
			add(0, lo, hi, {m, b});
	}
	void add(int v, ll l, ll r, Line line) {
		ll mid = (ll)((I)l + ((I)r - l) / 2);
		bool left = line.eval(l) < t[v].line.eval(l);
		bool middle = line.eval(mid) < t[v].line.eval(mid);
		if (middle) swap(line, t[v].line);
		if (l == r) return;
		bool goLeft = left != middle;
		int child = goLeft ? t[v].left : t[v].right;
		if (child < 0) {
			child = (int)t.size();
			if (goLeft)
				t[v].left = child;
			else
				t[v].right = child;
			t.push_back({line, -1, -1});
		} else if (goLeft)
			add(child, l, mid, line);
		else
			add(child, mid + 1, r, line);
	}
	I query(ll x) const {
		assert(lo <= x && x <= hi);
		int v = t.empty() ? -1 : 0;
		ll l = lo, r = hi;
		I ans = inf;
		while (v >= 0) {
			ans = min(ans, t[v].line.eval(x));
			if (l == r) break;
			ll mid = (ll)((I)l + ((I)r - l) / 2);
			if (x <= mid)
				v = t[v].left, r = mid;
			else
				v = t[v].right, l = mid + 1;
		}
		return ans;
	}
};
