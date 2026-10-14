/**
 * Author: Green Siro
 * License: CC0
 * Description: 0-indexed [l,r]: range assign/add and sum.
 * Time: O(log N) per operation; O(N) memory. Empty ranges
 * OK.
 */
#pragma once

struct LazySegmentTree {
  int n;
  vector<ll> sum, add, setv;
  vector<bool> has;
  LazySegmentTree(int n) : n(n), sum(4*n+4), add(4*n+4),
      setv(4*n+4), has(4*n+4) {}
  void apply(int v,int len,ll x,bool assign) {
    if(assign) sum[v]=x*len, setv[v]=x, add[v]=0,
        has[v]=true;
    else sum[v]+=x*len, add[v]+=x;
  }
  void push(int v,int l,int r) {
    int m=(l+r)/2;
    for(int c : {v*2,v*2+1}) {
      int len=(c==v*2 ? m-l+1 : r-m);
      if(has[v]) apply(c,len,setv[v],true);
      if(add[v]) apply(c,len,add[v],false);
    }
    has[v]=false; add[v]=0;
  }
  void update(int a,int b,ll x,bool assign=false) {
    if(a<=b) update(1,0,n-1,a,b,x,assign);
  }
  void update(int v,int l,int r,int a,int b,ll x,bool as) {
    if(b<l || r<a) return;
    if(a<=l && r<=b) {apply(v,r-l+1,x,as); return;}
    push(v,l,r); int m=(l+r)/2;
    update(v*2,l,m,a,b,x,as);
    update(v*2+1,m+1,r,a,b,x,as);
    sum[v]=sum[v*2]+sum[v*2+1];
  }
  ll query(int a,int b) {return a<=b ? query(1,0,n-1,a,b):0;}
  ll query(int v,int l,int r,int a,int b) {
    if(b<l || r<a) return 0;
    if(a<=l && r<=b) return sum[v];
    push(v,l,r); int m=(l+r)/2;
    return query(v*2,l,m,a,b)+query(v*2+1,m+1,r,a,b);
  }
};
