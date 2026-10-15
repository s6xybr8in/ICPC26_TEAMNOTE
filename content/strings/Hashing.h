/**
 * Author: Green Siro
 * License: CC0
 * Description: Double modular substring hash, 0-indexed [l,r]. Empty range: l>r. Compare only
 * hashes built with the same base. Collision remains possible; verify equality if correctness
 * demands. Time: O(N) build, O(1) query.
 */
#pragma once

struct StringHash {
	static constexpr ll m1 = 1000000007, m2 = 1000000009;
	vector<ll> h1, h2, p1, p2;
	StringHash(const string &s, ll base = 911382323)
	    : h1(s.size() + 1), h2(s.size() + 1), p1(s.size() + 1, 1), p2(s.size() + 1, 1) {
		for (int i = 0; i < (int)s.size(); ++i) {
			ll c = (unsigned char)s[i] + 1;
			h1[i + 1] = (h1[i] * base + c) % m1;
			h2[i + 1] = (h2[i] * base + c) % m2;
			p1[i + 1] = p1[i] * base % m1;
			p2[i + 1] = p2[i] * base % m2;
		}
	}
	pair<ll, ll> get(int l, int r) const {
		if (l > r) return {0, 0};
		return {(h1[r + 1] - h1[l] * p1[r - l + 1] % m1 + m1) % m1,
		        (h2[r + 1] - h2[l] * p2[r - l + 1] % m2 + m2) % m2};
	}
};
