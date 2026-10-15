/**
 * Author: Green Siro
 * License: CC0
 * Description: Returns (odd,even) radii. odd[i]: [i-r+1,i+r-1]; even[i]: [i-r,i+r-1]. Number of
 * palindromes=sum(radii). Time: O(N).
 */
#pragma once

pair<vector<int>, vector<int>> manacher(const string &s) {
	int n = (int)s.size();
	vector<int> odd(n), even(n);
	for (int i = 0, l = 0, r = -1; i < n; ++i) {
		int k = i > r ? 1 : min(odd[l + r - i], r - i + 1);
		while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) ++k;
		odd[i] = k--;
		if (i + k > r) l = i - k, r = i + k;
	}
	for (int i = 0, l = 0, r = -1; i < n; ++i) {
		int k = i > r ? 0 : min(even[l + r - i + 1], r - i + 1);
		while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) ++k;
		even[i] = k--;
		if (i + k > r) l = i - k - 1, r = i + k;
	}
	return {odd, even};
}
