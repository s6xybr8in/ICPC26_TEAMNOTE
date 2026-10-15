/**
 * Author: Green Siro
 * License: CC0
 * Description: Lowercase a-z, nonempty patterns. Add all then build once. out counts patterns
 * ending here incl. suffixes. Keep returned terminal node; duplicates share a node. Per-pattern
 * counts: count visited states, then propagate counts to link in reverse BFS order. O(26N +
 * text).
 */
#pragma once

struct AhoCorasick {
	struct Node {
		array<int, 26> next;
		int link = 0, out = 0;
		Node() { next.fill(-1); }
	};
	vector<Node> t{Node()};
	vector<int> order;
	int add(const string &s) {
		assert(!s.empty());
		int u = 0;
		for (char ch : s) {
			int c = ch - 'a';
			if (t[u].next[c] < 0) {
				t[u].next[c] = (int)t.size();
				t.emplace_back();
			}
			u = t[u].next[c];
		}
		++t[u].out;
		return u;
	}
	void build() {
		queue<int> q;
		for (int c = 0; c < 26; ++c) {
			int v = t[0].next[c];
			if (v < 0)
				t[0].next[c] = 0;
			else
				q.push(v);
		}
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			order.push_back(u);
			t[u].out += t[t[u].link].out;
			for (int c = 0; c < 26; ++c) {
				int v = t[u].next[c], w = t[t[u].link].next[c];
				if (v < 0)
					t[u].next[c] = w;
				else
					t[v].link = w, q.push(v);
			}
		}
	}
	ll countMatches(const string &s) const {
		ll ans = 0;
		int u = 0;
		for (char c : s) u = t[u].next[c - 'a'], ans += t[u].out;
		return ans;
	}
};
