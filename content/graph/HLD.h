/**
 * Author: Green Siro
 * License: CC0
 * Description: Connected nonempty tree, 0-indexed. Vertex
 * path segments [l,r]; callback order is unspecified. Use
 * only commutative aggregates with path(). edge=true
 * excludes the LCA (edge value stored at child). Subtree
 * [pos[u],pos[u]+size[u]-1]. O(log N) segments.
 */
#pragma once

struct HLD {
  vector<int> parent,depth,size,heavy,head,pos;
  HLD(const vector<vector<int>>& g,int root=0) {
    int n=(int)g.size();
    parent.assign(n,-1); depth.resize(n); size.assign(n,1);
    heavy.assign(n,-1); head.resize(n); pos.resize(n);
    vector<int> order{root}; parent[root]=root;
    for(int i=0;i<n;++i) {
      int u=order[i];
      for(int v:g[u]) if(v!=parent[u]) {
        parent[v]=u; depth[v]=depth[u]+1; order.push_back(v);
      }
    }
    for(int i=n-1;i>0;--i) {
      int u=order[i],p=parent[u]; size[p]+=size[u];
      if(heavy[p]<0 || size[u]>size[heavy[p]]) heavy[p]=u;
    }
    int timer=0; vector<pair<int,int>> st{{root,root}};
    while(!st.empty()) {
      auto [u,h]=st.back();st.pop_back();
      for(;u!=-1;u=heavy[u]) {
        head[u]=h;pos[u]=timer++;
        for(int v:g[u]) if(v!=parent[u] && v!=heavy[u])
          st.push_back({v,v});
      }
    }
  }
  template<class F> void path(int u,int v,F f,bool
    edge=false) {
    while(head[u]!=head[v]) {
      if(depth[head[u]]<depth[head[v]]) swap(u,v);
      f(pos[head[u]],pos[u]);u=parent[head[u]];
    }
    if(depth[u]>depth[v]) swap(u,v);
    if(pos[u]+edge<=pos[v]) f(pos[u]+edge,pos[v]);
  }
};
