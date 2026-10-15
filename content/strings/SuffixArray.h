/**
 * Author: Green Siro
 * License: CC0
 * Description: Suffix array and Kasai LCP; arbitrary bytes. rank[sa[i]]=i;
 * lcp[i]=LCP(sa[i-1],sa[i]), lcp[0]=0. Time: O(N log^2 N), memory O(N).
 */
#pragma once

struct SuffixArray {
	vector<int> sa, rank, lcp;
	SuffixArray(const string &s) {
		int n = (int)s.size();
		sa.resize(n);
		rank.resize(n);
		iota(sa.begin(), sa.end(), 0);
		for (int i = 0; i < n; ++i) rank[i] = (unsigned char)s[i];
		for (int k = 1; k < n; k *= 2) {
			auto key = [&](int i) { return pair<int, int>{rank[i], i + k < n ? rank[i + k] : -1}; };
			sort(sa.begin(), sa.end(), [&](int a, int b) { return key(a) < key(b); });
			vector<int> nr(n);
			for (int i = 1; i < n; ++i) nr[sa[i]] = nr[sa[i - 1]] + (key(sa[i - 1]) != key(sa[i]));
			rank.swap(nr);
			if (rank[sa.back()] == n - 1) break;
		}
		for (int i = 0; i < n; ++i) rank[sa[i]] = i;
		lcp.resize(n);
		for (int i = 0, h = 0; i < n; ++i) {
			if (!rank[i]) {
				h = 0;
				continue;
			}
			int j = sa[rank[i] - 1];
			while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
			lcp[rank[i]] = h;
			if (h) --h;
		}
	}
};
