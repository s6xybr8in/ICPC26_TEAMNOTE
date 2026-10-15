/**
 * Author: Green Siro
 * License: CC0
 * Description: CCW hull without repeated endpoint; drops collinear interior points.
 * All-collinear -> endpoints. O(N log N).
 */
#pragma once

#include "Point.h"
vector<Point> convexHull(vector<Point> p) {
	sort(p.begin(), p.end());
	p.erase(unique(p.begin(), p.end()), p.end());
	if (p.size() < 2) return p;
	vector<Point> h;
	for (Point q : p) {
		while (h.size() > 1 && cross(h[h.size() - 2], h.back(), q) <= 0) h.pop_back();
		h.push_back(q);
	}
	int lower = (int)h.size();
	for (int i = (int)p.size() - 2; i >= 0; --i) {
		while ((int)h.size() > lower && cross(h[h.size() - 2], h.back(), p[i]) <= 0) h.pop_back();
		h.push_back(p[i]);
	}
	h.pop_back();
	return h;
}
