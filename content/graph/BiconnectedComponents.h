/**
 * Author: Green Siro
 * License: CC0
 * Description: Undirected articulation points and bridge
 * edge IDs. Handles parallel edges and self-loops.
 * 0-indexed. Time: O(V+E). Recursive DFS: watch stack
 * depth.
 */
#pragma once

struct LowLink {
  int timer=0, edges=0;
  vector<vector<pair<int,int>>> g;
  vector<int> tin,low,bridges;
  vector<bool> cut;
  LowLink(int n) : g(n),tin(n,-1),low(n),cut(n) {}
  int addEdge(int a,int b) {
    g[a].push_back({b,edges}); g[b].push_back({a,edges});
    return edges++;
  }
  void dfs(int u,int pe=-1) {
    tin[u]=low[u]=timer++; int children=0;
    for(auto [v,id]:g[u]) {
      if(id==pe) continue;
      if(tin[v]>=0) low[u]=min(low[u],tin[v]);
      else {
        dfs(v,id); ++children; low[u]=min(low[u],low[v]);
        if(low[v]>tin[u]) bridges.push_back(id);
        if(pe!=-1 && low[v]>=tin[u]) cut[u]=true;
      }
    }
    if(pe==-1) cut[u]=children>1;
  }
  void build() {
    timer=0; bridges.clear();
    fill(tin.begin(),tin.end(),-1);
    fill(cut.begin(),cut.end(),false);
    for(int u=0;u<(int)g.size();++u) if(tin[u]<0) dfs(u);
  }
};
