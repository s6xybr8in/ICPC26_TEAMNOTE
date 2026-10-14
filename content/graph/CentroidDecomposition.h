/**
 * Author: Green Siro
 * License: CC0
 * Description: Centroid parent tree, root parent=-1.
 * Original graph must be a connected nonempty tree. Time:
 * O(N log N). Component scans are iterative.
 */
#pragma once

struct CentroidDecomposition {
  vector<int> parent,size,scanParent;
  vector<bool> removed;
  const vector<vector<int>>& g;
  CentroidDecomposition(const vector<vector<int>>& g)
      : parent(g.size(),-1),size(g.size()),
        scanParent(g.size()),removed(g.size()),g(g)
          {build(0,-1);}
  void build(int start,int p) {
    vector<int> order{start};scanParent[start]=-1;
    for(int i=0;i<(int)order.size();++i) {
      int u=order[i];size[u]=1;
      for(int v:g[u]) if(!removed[v] && v!=scanParent[u])
        scanParent[v]=u,order.push_back(v);
    }
    int total=(int)order.size(),c=start;
    for(int i=total-1;i>=0;--i) {
      int u=order[i],big=total-size[u];
      for(int v:g[u]) if(!removed[v] && scanParent[v]==u)
        big=max(big,size[v]);
      if(big<=total/2) c=u;
      if(scanParent[u]!=-1) size[scanParent[u]]+=size[u];
    }
    parent[c]=p;removed[c]=true;
    for(int v:g[c]) if(!removed[v]) build(v,c);
  }
};
