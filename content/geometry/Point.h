/**
 * Author: Green Siro
 * License: CC0
 * Description: Integer geometry. Coordinates abs <= 1e9;
 * products and squared distances use \_\_int128. No
 * floating EPS.
 */
#pragma once

struct Point {
  ll x=0,y=0;
  bool operator<(const Point& p) const {
    return tie(x,y)<tie(p.x,p.y);
  }
  bool operator==(const Point& p) const {return x==p.x &&
    y==p.y;}
  Point operator-(Point p) const {return {x-p.x,y-p.y};}
};
__int128 cross(Point a,Point b) {
  return (__int128)a.x*b.y-(__int128)a.y*b.x;
}
__int128 cross(Point a,Point b,Point c) {return cross(b-a,
  c-a);}
__int128 dot(Point a,Point b) {
  return (__int128)a.x*b.x+(__int128)a.y*b.y;
}
__int128 dist2(Point a,Point b) {return dot(a-b,a-b);}
int sign128(__int128 x) {return (x>0)-(x<0);}
bool onSegment(Point a,Point b,Point p) {
  return cross(a,b,p)==0 && dot(p-a,p-b)<=0;
}
