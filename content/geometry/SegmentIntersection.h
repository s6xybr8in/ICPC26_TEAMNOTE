/**
 * Author: Green Siro
 * License: CC0
 * Description: Closed-segment intersection, includes touches and overlaps, degenerate points.
 * Time: O(1). Depends Point.h.
 */
#pragma once

#include "Point.h"
bool segmentIntersection(Point a, Point b, Point c, Point d) {
	if (onSegment(a, b, c) || onSegment(a, b, d) || onSegment(c, d, a) || onSegment(c, d, b))
		return true;
	return sign128(cross(a, b, c)) * sign128(cross(a, b, d)) < 0 &&
	       sign128(cross(c, d, a)) * sign128(cross(c, d, b)) < 0;
}
