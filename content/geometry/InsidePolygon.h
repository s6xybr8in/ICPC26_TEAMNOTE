/**
 * Author: Green Siro
 * License: CC0
 * Description: Simple polygon, either orientation. Returns
 * -1 outside, 0 boundary, 1 inside. Empty polygon -> -1.
 * Time: O(N).
 */
#pragma once

#include "Point.h"
int insidePolygon(const vector<Point>& p,Point q) {
  bool in=false;int n=(int)p.size();
  for(int i=0;i<n;++i) {
    Point a=p[i],b=p[(i+1)%n];
    if(onSegment(a,b,q)) return 0;
    if((a.y>q.y)!=(b.y>q.y))
      if((cross(a,b,q)>0)==(b.y>a.y)) in=!in;
  }
  return in ? 1:-1;
}
