/**
 * Author: Green Siro
 * License: CC0
 * Description: Squared diameter of strict CCW convex hull. Empty/single point returns 0. Time:
 * O(N).
 */
#pragma once

#include "Point.h"
__int128 hullDiameter(const vector<Point> &h) {
	int n = (int)h.size();
	if (n < 2) return 0;
	if (n == 2) return dist2(h[0], h[1]);
	__int128 ans = 0;
	int j = 1;
	for (int i = 0; i < n; ++i) {
		int k = (i + 1) % n;
		while (cross(h[i], h[k], h[(j + 1) % n]) > cross(h[i], h[k], h[j])) j = (j + 1) % n;
		ans = max(ans, max(dist2(h[i], h[j]), dist2(h[k], h[j])));
	}
	return ans;
}
