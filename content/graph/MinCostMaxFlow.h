/**
 * Author: Green Siro
 * License: CC0
 * Description: Successive shortest paths with initial
 * Bellman-Ford. No negative-cost cycle in initial residual
 * graph. s != t. flow(s,t,limit) returns (flow,cost); call
 * once per graph. Costs/distances/products must fit ll.
 * Time: O(VE + augmentations * E log V).
 */
#pragma once

struct MinCostMaxFlow {
  struct Edge {int to,rev;ll cap,cost;};
  vector<vector<Edge>> g;
  MinCostMaxFlow(int n):g(n) {}
  void addEdge(int u,int v,ll cap,ll cost) {
    int a=(int)g[u].size(),b=(int)g[v].size();
    g[u].push_back({v,b+(u==v),cap,cost});
    g[v].push_back({u,a,0,-cost});
  }
  pair<ll,ll> flow(int s,int t,ll limit=LLONG_MAX) {
    assert(s!=t);
    int n=(int)g.size(); const ll inf=LLONG_MAX/4;
    vector<ll> pot(n),d(n);
    vector<int> pv(n),pe(n);
    // Super-source of zero cost to all vertices.
    for(int it=0;it<n;++it) {
      bool changed=false;
      for(int u=0;u<n;++u) for(auto e:g[u])
        if(e.cap && pot[e.to]>pot[u]+e.cost)
          pot[e.to]=pot[u]+e.cost,changed=true;
      if(!changed) break;
      assert(it!=n-1); // negative cycle
    }
    ll total=0,cost=0;
    while(total<limit) {
      fill(d.begin(),d.end(),inf);d[s]=0;
      priority_queue<pair<ll,int>,vector<pair<ll,int>>,
          greater<pair<ll,int>>> q;q.push({0,s});
      while(!q.empty()) {
        auto [du,u]=q.top();q.pop();if(du!=d[u]) continue;
        for(int i=0;i<(int)g[u].size();++i) {
          auto e=g[u][i];
          ll nd=du+e.cost+pot[u]-pot[e.to];
          if(e.cap && nd<d[e.to]) {
            d[e.to]=nd;pv[e.to]=u;pe[e.to]=i;
            q.push({nd,e.to});
          }
        }
      }
      if(d[t]==inf) break;
      for(int u=0;u<n;++u) if(d[u]<inf) pot[u]+=d[u];
      ll f=limit-total;
      for(int v=t;v!=s;v=pv[v]) f=min(f,g[pv[v]][pe[v]].cap);
      for(int v=t;v!=s;v=pv[v]) {
        Edge& e=g[pv[v]][pe[v]];
        cost+=f*e.cost;e.cap-=f;g[v][e.rev].cap+=f;
      }
      total+=f;
    }
    return {total,cost};
  }
};
