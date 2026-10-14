/**
 * Author: Green Siro
 * License: CC0
 * Description: 0-indexed directed graph; Kosaraju. comp[u]
 * <= comp[v] on condensation edges u -> v. Time: O(V+E).
 * Recursive DFS: watch stack depth.
 */
#pragma once

struct SCC {
  int n, count=0;
  vector<vector<int>> g,rg;
  vector<int> comp,order;
  vector<bool> seen;
  SCC(int n) : n(n), g(n),rg(n),comp(n,-1),seen(n) {}
  void addEdge(int u,int v) {g[u].push_back(v);
    rg[v].push_back(u);}
  void dfs(int u) {
    seen[u]=true;
    for(int v:g[u]) if(!seen[v]) dfs(v);
    order.push_back(u);
  }
  void dfs2(int u) {
    comp[u]=count;
    for(int v:rg[u]) if(comp[v]<0) dfs2(v);
  }
  int build() {
    count=0; order.clear();
    fill(seen.begin(),seen.end(),false);
    fill(comp.begin(),comp.end(),-1);
    for(int u=0;u<n;++u) if(!seen[u]) dfs(u);
    reverse(order.begin(),order.end());
    for(int u:order) if(comp[u]<0) {dfs2(u);++count;}
    return count;
  }
};
