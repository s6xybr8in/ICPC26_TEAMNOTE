/**
 * Author: Green Siro
 * License: CC0
 * Description: Minimum-cost assignment, n rows <= m
 * columns. Returns (minimum cost, row -> column),
 * 0-indexed. All costs finite, abs(cost) well below
 * LLONG\_MAX/4. Time: O(n^2 m). Empty
 * input supported.
 */
#pragma once

pair<ll,vector<int>> hungarian(const vector<vector<ll>>& a) {
  int n=(int)a.size(),m=n ? (int)a[0].size():0;
  assert(n<=m);
  vector<ll> u(n+1),v(m+1);
  vector<int> p(m+1),way(m+1);
  for(int i=1;i<=n;++i) {
    p[0]=i;int j0=0;
    vector<ll> best(m+1,LLONG_MAX/4);
    vector<bool> used(m+1);
    do {
      used[j0]=true;int i0=p[j0],j1=0;
      ll delta=LLONG_MAX/4;
      for(int j=1;j<=m;++j) if(!used[j]) {
        ll cur=a[i0-1][j-1]-u[i0]-v[j];
        if(cur<best[j]) best[j]=cur,way[j]=j0;
        if(best[j]<delta) delta=best[j],j1=j;
      }
      for(int j=0;j<=m;++j)
        if(used[j]) u[p[j]]+=delta,v[j]-=delta;
        else best[j]-=delta;
      j0=j1;
    } while(p[j0]);
    do {int j1=way[j0];p[j0]=p[j1];j0=j1;} while(j0);
  }
  vector<int> match(n);
  for(int j=1;j<=m;++j) if(p[j]) match[p[j]-1]=j-1;
  return {-v[0],match};
}
