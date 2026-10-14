/**
 * Author: Green Siro
 * License: CC0
 * Description: Virtual tree of requested vertices plus
 * their LCAs. Returns (parent,child) original vertex IDs.
 * Empty/single vertex -> no edges. Edge length =
 * LCA.dist(parent,child). Time: O(K log K + K log N).
 * Depends on LCA.h.
 */
#pragma once

#include "LCA.h"
vector<pair<int,int>> virtualTree(vector<int> v,const LCA& t) {
  if(v.empty()) return {};
  auto cmp=[&](int a,int b){return t.tin[a]<t.tin[b];};
  sort(v.begin(),v.end(),cmp);
  int k=(int)v.size();
  for(int i=1;i<k;++i) v.push_back(t.lca(v[i-1],v[i]));
  sort(v.begin(),v.end(),cmp);
  v.erase(unique(v.begin(),v.end()),v.end());
  vector<int> st;
  vector<pair<int,int>> edges;
  for(int u:v) {
    while(!st.empty() && !t.ancestor(st.back(),u))
      st.pop_back();
    if(!st.empty()) edges.push_back({st.back(),u});
    st.push_back(u);
  }
  return edges;
}
