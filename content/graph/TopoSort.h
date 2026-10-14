/**
 * Author: Green Siro
 * License: CC0
 * Description: Kahn topological ordering. Empty if a cycle
 * exists. Time: O(V+E). Empty graph also returns empty.
 */
#pragma once

vector<int> topoSort(const vector<vector<int>>& g) {
  vector<int> deg(g.size()),order;
  queue<int> q;
  for(auto& adj:g) for(int v:adj) ++deg[v];
  for(int i=0;i<(int)g.size();++i) if(!deg[i]) q.push(i);
  while(!q.empty()) {
    int u=q.front(); q.pop(); order.push_back(u);
    for(int v:g[u]) if(!--deg[v]) q.push(v);
  }
  if(order.size()!=g.size()) return {};
  return order;
}
