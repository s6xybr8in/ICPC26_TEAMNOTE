/**
 * Author: Green Siro
 * License: CC0
 * Description: Nonnegative radii. Returns -1 for coincident
 * circles; otherwise 0/1/2 intersections in out. Absolute
 * EPS must suit coordinate scale. Point circles supported.
 * O(1).
 */
#pragma once

struct DPoint {
  long double x,y;
  DPoint operator+(DPoint b) const {return {x+b.x,y+b.y};}
  DPoint operator-(DPoint b) const {return {x-b.x,y-b.y};}
  DPoint operator*(long double k) const {return {x*k,y*k};}
};
int circleIntersection(DPoint a,long double r,DPoint b,
    long double s,vector<DPoint>& out,long double eps=1e-12L) {
  out.clear();DPoint v=b-a;long double d=hypotl(v.x,v.y);
  if(d<eps) {
    if(fabsl(r-s)>eps) return 0;
    if(r<eps) {out.push_back(a);return 1;}
    return -1;
  }
  if(d>r+s+eps || d<fabsl(r-s)-eps) return 0;
  long double x=(d*d+r*r-s*s)/(2*d);
  long double h=sqrtl(max(0.0L,r*r-x*x));
  DPoint mid=a+v*(x/d),off={-v.y*h/d,v.x*h/d};
  out.push_back(mid+off);
  if(h>eps) out.push_back(mid-off);
  return (int)out.size();
}
