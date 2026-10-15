#include <cassert>
#include "../utilities/template.h"
#include "../../content/data-structures/LazySegmentTree.h"
#include "../../content/data-structures/SparseTable.h"
#include "../../content/data-structures/UnionFindRollback.h"
#include "../../content/data-structures/LiChaoTree.h"
#include "../../content/graph/2sat.h"
#include "../../content/graph/BiconnectedComponents.h"
#include "../../content/graph/TopoSort.h"
#include "../../content/graph/EulerWalk.h"
#include "../../content/graph/HLD.h"
#include "../../content/graph/CompressTree.h"
#include "../../content/graph/CentroidDecomposition.h"
#include "../../content/graph/Dinic.h"
#include "../../content/graph/MinCostMaxFlow.h"
#include "../../content/graph/HopcroftKarp.h"
#include "../../content/graph/Hungarian.h"
#include "../../content/strings/KMP.h"
#include "../../content/strings/Zfunc.h"
#include "../../content/strings/Manacher.h"
#include "../../content/strings/AhoCorasick.h"
#include "../../content/strings/SuffixArray.h"
#include "../../content/strings/Hashing.h"
#include "../../content/number-theory/Modular.h"
#include "../../content/number-theory/Sieve.h"
#include "../../content/number-theory/Factor.h"
#include "../../content/combinatorial/Binomial.h"
#include "../../content/numerical/NumberTheoreticTransform.h"
#include "../../content/numerical/FastFourierTransform.h"
#include "../../content/numerical/SolveLinear.h"
#include "../../content/numerical/XorBasis.h"
#include "../../content/numerical/LinearRecurrence.h"
#include "../../content/geometry/ConvexHull.h"
#include "../../content/geometry/SegmentIntersection.h"
#include "../../content/geometry/InsidePolygon.h"
#include "../../content/geometry/HullDiameter.h"
#include "../../content/geometry/CircleIntersection.h"
#include "../../content/various/DivideAndConquerDP.h"
#include "../../content/various/KnuthDP.h"
#include "../../content/various/SubsetDP.h"
mt19937 rng(20261014);
int rnd(int n) {return (int)(rng()%(unsigned)n);}
void dataStructures() {
  for(int n=1;n<=50;++n) {
    LazySegmentTree t(n);vector<ll> a(n);
    for(int it=0;it<1000;++it) {
      int l=rnd(n+1),r=rnd(n+1);if(l>r) swap(l,r);
      int type=rnd(3);ll x=rnd(201)-100;
      if(type==2) assert(t.query(l,r-1)==accumulate(a.begin()+l,a.begin()+r,0LL));
      else {
        t.update(l,r-1,x,type==1);
        for(int i=l;i<r;++i) if(type) a[i]=x;else a[i]+=x;
      }
    }
    SparseTable s(a);
    for(int l=0;l<n;++l) for(int r=l+1;r<=n;++r)
      assert(s.query(l,r-1)==*min_element(a.begin()+l,a.begin()+r));
    LiChaoTree lc(-30,30);vector<pair<ll,ll>> lines;
    assert(lc.query(0)==LiChaoTree::inf);
    for(int it=0;it<100;++it) {
      ll m=rnd(101)-50,b=rnd(101)-50;lc.add(m,b);lines.push_back({m,b});
      for(ll x=-30;x<=30;++x) {
        ll want=LLONG_MAX;
        for(auto [slope,c]:lines) want=min(want,slope*x+c);
        assert(lc.query(x)==want);
      }
    }
  }
  RollbackDSU d(10);int t=d.snapshot();d.join(1,2);d.join(2,3);
  int t2=d.snapshot();d.join(1,4);d.join(1,3);d.rollback(t2);
  assert(d.find(1)==d.find(3) && d.find(1)!=d.find(4));
  d.rollback(t);assert(d.components==10);
}
void graphBasics() {
  for(int it=0;it<300;++it) {
    int n=1+rnd(8);SCC s(n);vector<vector<bool>> reach(n,vector<bool>(n));
    vector<vector<int>> g(n);
    for(int u=0;u<n;++u) {
      reach[u][u]=true;
      for(int v=0;v<n;++v) if(rnd(4)==0)
        s.addEdge(u,v),g[u].push_back(v),reach[u][v]=true;
    }
    for(int k=0;k<n;++k) for(int u=0;u<n;++u) for(int v=0;v<n;++v)
      reach[u][v]=reach[u][v] || (reach[u][k] && reach[k][v]);
    s.build();
    for(int u=0;u<n;++u) for(int v=0;v<n;++v)
      assert((s.comp[u]==s.comp[v])==(reach[u][v] && reach[v][u]));
    auto order=topoSort(g);
    bool cycle=false;
    for(int u=0;u<n;++u) for(int v:g[u]) if(reach[v][u]) cycle=true;
    assert(order.empty()==cycle);
    if(!cycle) {
      vector<int> pos(n);for(int i=0;i<n;++i) pos[order[i]]=i;
      for(int u=0;u<n;++u) for(int v:g[u]) assert(pos[u]<pos[v]);
    }
    TwoSAT sat(n);vector<pair<int,int>> clauses;
    for(int j=0;j<20;++j) {
      int a=rnd(2*n),b=rnd(2*n);sat.either(a,b);clauses.push_back({a,b});
    }
    auto valid=[&](int mask) {
      for(auto [a,b]:clauses)
        if(!(((mask>>(a/2)&1)^(a&1)) || ((mask>>(b/2)&1)^(b&1)))) return false;
      return true;
    };
    bool possible=false;for(int mask=0;mask<(1<<n);++mask) possible|=valid(mask);
    assert(sat.solve()==possible);
    if(possible) {
      int mask=0;for(int u=0;u<n;++u) mask|=(int)sat.value[u]<<u;
      assert(valid(mask));
    }
    LowLink low(n);vector<pair<int,int>> edges;
    for(int j=0;j<15;++j) {
      int u=rnd(n),v=rnd(n);low.addEdge(u,v);edges.push_back({u,v});
    }
    auto components=[&](int skipVertex,int skipEdge) {
      vector<bool> seen(n);int cnt=0;
      auto dfs=[&](auto& self,int u)->void {
        seen[u]=true;
        for(int j=0;j<(int)edges.size();++j) if(j!=skipEdge) {
          auto [a,b]=edges[j];int v=a==u ? b:b==u ? a:-1;
          if(v>=0 && v!=skipVertex && !seen[v]) self(self,v);
        }
      };
      for(int u=0;u<n;++u) if(u!=skipVertex && !seen[u]) ++cnt,dfs(dfs,u);
      return cnt;
    };
    int base=components(-1,-1);low.build();
    for(int u=0;u<n;++u) assert(low.cut[u]==(components(u,-1)>base));
    for(int j=0;j<(int)edges.size();++j)
      assert((find(low.bridges.begin(),low.bridges.end(),j)!=low.bridges.end())
          ==(components(-1,j)>base));
  }
  for(bool dir:{false,true}) for(int it=0;it<100;++it) {
    int n=8;EulerWalk e(n,dir);int u=rnd(n),start=u;
    multiset<pair<int,int>> edges;
    for(int j=0;j<100;++j) {
      int v=rnd(n);e.addEdge(u,v);
      edges.insert(dir ? make_pair(u,v):pair<int,int>(minmax(u,v)));u=v;
    }
    auto path=e.walk(start);assert(path.size()==101);
    for(int j=1;j<(int)path.size();++j) {
      auto edge=dir ? make_pair(path[j-1],path[j]):
          pair<int,int>(minmax(path[j-1],path[j]));
      auto found=edges.find(edge);assert(found!=edges.end());edges.erase(found);
    }
    assert(edges.empty());
  }
  EulerWalk bad(3,true);bad.addEdge(0,1);bad.addEdge(0,2);assert(bad.walk(0).empty());
}
void trees() {
  for(int it=0;it<100;++it) {
    int n=1+rnd(100),root=rnd(n);vector<vector<int>> g(n);
    for(int u=1;u<n;++u) {int p=rnd(u);g[u].push_back(p);g[p].push_back(u);}
    for(auto& adj:g) shuffle(adj.begin(),adj.end(),rng);
    auto original=g;
    LCA l(g,root);HLD h(g,root);CentroidDecomposition cd(g);
    for(int u=0;u<n;++u) {
      auto before=original[u],after=g[u];
      sort(before.begin(),before.end());sort(after.begin(),after.end());
      assert(before==after);
      for(int v:g[u]) if(v!=h.par[u]) {
        assert(g[u][0]!=h.par[u]);
        assert(h.sz[g[u][0]]>=h.sz[v]);
        assert(h.pos[g[u][0]]==h.pos[u]+1);
        assert(h.head[g[u][0]]==h.head[u]);
      }
    }
    for(int a=0;a<n;++a) for(int b=0;b<n;++b) {
      int u=a,v=b;
      while(l.depth[u]>l.depth[v]) u=l.up[0][u];
      while(l.depth[v]>l.depth[u]) v=l.up[0][v];
      while(u!=v) u=l.up[0][u],v=l.up[0][v];
      assert(l.lca(a,b)==u);
      set<int> want{u};
      for(int x=a;x!=u;x=l.up[0][x]) want.insert(x);
      for(int x=b;x!=u;x=l.up[0][x]) want.insert(x);
      set<int> got;vector<int> inv(n);
      for(int x=0;x<n;++x) inv[h.pos[x]]=x;
      h.path(a,b,[&](int x,int y){for(int k=x;k<=y;++k) got.insert(inv[k]);});
      assert(got==want);
      got.clear();h.path(a,b,[&](int x,int y){for(int k=x;k<=y;++k) got.insert(inv[k]);},true);
      want.erase(u);assert(got==want);
    }
    for(int u=0;u<n;++u) {
      assert(l.kth(u,l.depth[u])==root && l.kth(u,l.depth[u]+1)==-1);
      for(int v=0;v<n;++v)
        assert((h.pos[u]<=h.pos[v] && h.pos[v]<=h.pos[u]+h.sz[u]-1)==l.ancestor(u,v));
      int count=0;for(int x=u;x!=-1;x=cd.parent[x]) {++count;assert(count<20);}
      // Remove centroid ancestors; u must balance its component.
      vector<bool> blocked(n);
      for(int x=cd.parent[u];x!=-1;x=cd.parent[x]) blocked[x]=true;
      auto componentSize=[&](auto& self,int x,int p)->int {
        int result=1;
        for(int y:g[x]) if(y!=p && !blocked[y]) result+=self(self,y,x);
        return result;
      };
      int total=componentSize(componentSize,u,-1);
      blocked[u]=true;
      for(int v:g[u]) if(!blocked[v])
        assert(componentSize(componentSize,v,u)<=total/2);
    }
    vector<int> subset;for(int u=0;u<n;++u) if(rnd(4)==0) subset.push_back(u);
    auto edges=virtualTree(subset,l);set<int> vertices(subset.begin(),subset.end());
    for(auto [a,b]:edges) {assert(l.ancestor(a,b));vertices.insert(a);vertices.insert(b);}
    assert(vertices.empty() || edges.size()+1==vertices.size());
    for(int u:vertices) if(!edges.empty()) {
      int best=-1;
      for(int v:vertices) if(v!=u && l.ancestor(v,u))
        if(best<0 || l.depth[v]>l.depth[best]) best=v;
      if(best>=0) assert(find(edges.begin(),edges.end(),make_pair(best,u))!=edges.end());
    }
  }
}
void flowsMatching() {
  for(int it=0;it<250;++it) {
    int n=2+rnd(6);Dinic d(n);vector<tuple<int,int,ll>> edges;
    for(int j=0;j<20;++j) {
      int u=rnd(n),v=rnd(n);ll c=rnd(8);d.addEdge(u,v,c);edges.push_back({u,v,c});
    }
    ll want=LLONG_MAX;
    for(int mask=0;mask<(1<<n);++mask) if((mask&1) && !(mask>>(n-1)&1)) {
      ll cut=0;for(auto [u,v,c]:edges) if((mask>>u&1) && !(mask>>v&1)) cut+=c;
      want=min(want,cut);
    }
    assert(d.maxflow(0,n-1)==want);
    int a=1+rnd(5),b=a+rnd(3);vector<vector<ll>> cost(a,vector<ll>(b));
    HopcroftKarp hk(a,b);MinCostMaxFlow mc(a+b+2);
    int s=a+b,t=s+1;
    for(int u=0;u<a;++u) mc.addEdge(s,u,1,0);
    for(int v=0;v<b;++v) mc.addEdge(a+v,t,1,0);
    vector<vector<bool>> present(a,vector<bool>(b));
    for(int u=0;u<a;++u) for(int v=0;v<b;++v) {
      cost[u][v]=rnd(101)-50;
      if(rnd(3)) hk.addEdge(u,v),present[u][v]=true;
      mc.addEdge(u,a+v,1,cost[u][v]);
    }
    vector<int> perm(b);iota(perm.begin(),perm.end(),0);
    ll best=LLONG_MAX;int maxMatch=0;
    do {
      ll c=0;int matches=0;
      for(int u=0;u<a;++u) c+=cost[u][perm[u]],matches+=present[u][perm[u]];
      best=min(best,c);maxMatch=max(maxMatch,matches);
    } while(next_permutation(perm.begin(),perm.end()));
    auto assignment=hungarian(cost);assert(assignment.first==best);
    set<int> assigned;ll sum=0;
    for(int u=0;u<a;++u) assigned.insert(assignment.second[u]),sum+=cost[u][assignment.second[u]];
    assert((int)assigned.size()==a && sum==best);
    assert((mc.flow(s,t)==make_pair((ll)a,best)));
    assert(hk.maxMatching()==maxMatch);
    auto cover=hk.minCover();assert((int)(cover.first.size()+cover.second.size())==maxMatch);
    for(int u=0;u<a;++u) for(int v:hk.g[u])
      assert(find(cover.first.begin(),cover.first.end(),u)!=cover.first.end() ||
          find(cover.second.begin(),cover.second.end(),v)!=cover.second.end());
  }
  // Disconnected negative-cost edge; parallel/self-loop edges.
  MinCostMaxFlow mc(5);mc.addEdge(0,1,3,-2);mc.addEdge(1,2,2,4);
  mc.addEdge(0,2,1,7);mc.addEdge(3,4,1,-100);mc.addEdge(1,1,5,0);
  assert((mc.flow(0,2,2)==make_pair(2LL,4LL)));
}
void strings() {
  for(int it=0;it<500;++it) {
    string s(rnd(60),'a');for(char& c:s) c=(char)('a'+rnd(3));
    int n=(int)s.size();auto z=zFunction(s);auto rad=manacher(s);
    StringHash hash(s);SuffixArray sa(s);vector<int> order(n);iota(order.begin(),order.end(),0);
    sort(order.begin(),order.end(),[&](int a,int b){return s.substr(a)<s.substr(b);});
    assert(sa.sa==order);
    for(int i=0;i<n;++i) {
      int len=0;while(i+len<n && s[len]==s[i+len]) ++len;
      if(i) assert(z[i]==len);
      int odd=1;while(i-odd>=0 && i+odd<n && s[i-odd]==s[i+odd]) ++odd;
      int even=0;while(i-even-1>=0 && i+even<n && s[i-even-1]==s[i+even]) ++even;
      assert(rad.first[i]==odd && rad.second[i]==even);
      if(i) {
        int a=order[i-1],b=order[i],l=0;
        while(a+l<n && b+l<n && s[a+l]==s[b+l]) ++l;
        assert(sa.lcp[i]==l);
      }
    }
    AhoCorasick ac;vector<string> pats;
    for(int j=0;j<10;++j) {
      string p(1+rnd(8),'a');for(char& c:p) c=(char)('a'+rnd(3));
      ac.add(p);pats.push_back(p);
    }
    ac.build();ll count=0;
    pats.push_back("");
    for(auto p:pats) {
      vector<int> want;
      for(int i=0;i+(int)p.size()<=n;++i) if(s.substr(i,p.size())==p) want.push_back(i);
      assert(kmp(s,p)==want);if(!p.empty()) count+=(ll)want.size();
    }
    assert(ac.countMatches(s)==count);
    for(int j=0;j<100 && n;++j) {
      int a=rnd(n),b=rnd(n),len=rnd(n-max(a,b)+1);
      assert((hash.get(a,a+len-1)==hash.get(b,b+len-1))==(s.substr(a,len)==s.substr(b,len)));
    }
  }
}
void arithmetic() {
  Sieve s(10000);
  for(int n=1;n<=10000;++n) {
    bool prime=n>=2;for(int p=2;p*p<=n;++p) if(n%p==0) prime=false;
    assert(Factor64::prime(n)==prime);
    assert(n==1 || (n%s.spf[n]==0 && Factor64::prime(s.spf[n])));
    if(n<=100) {
      int phi=0,mu=1,x=n;
      for(int k=1;k<=n;++k) phi+=gcd(n,k)==1;
      for(int p=2;p<=x;++p) if(x%p==0) {
        int cnt=0;while(x%p==0) x/=p,++cnt;
        mu=cnt>1 ? 0:-mu;
      }
      assert(s.phi[n]==phi && s.mu[n]==mu);
    }
  }
  for(uint64_t n:{1ULL,2ULL,360ULL,1000000016000000063ULL,18446744073709551615ULL}) {
    auto f=Factor64::factor(n);__uint128_t prod=1;
    for(auto p:f) assert(Factor64::prime(p)),prod*=p;
    assert(prod==n);
  }
  assert(Factor64::prime(18446744073709551557ULL));
  assert(!Factor64::prime(341550071728321ULL));
  assert(NT::norm(LLONG_MIN,LLONG_MAX)==LLONG_MAX-1);
  assert(NT::power(LLONG_MAX-1,2,LLONG_MAX)==1);
  assert((NT::crt(LLONG_MAX-1,LLONG_MAX,0,1)==
      make_pair(LLONG_MAX-1,LLONG_MAX)));
  assert(NT::crt(0,LLONG_MAX,0,LLONG_MAX-1).second==0);
  for(int m=1;m<=30;++m) for(int n=1;n<=30;++n) for(int it=0;it<10;++it) {
    int a=rnd(101)-50,b=rnd(101)-50;auto result=NT::crt(a,m,b,n);
    ll want=-1,mod=lcm(m,n);
    for(int x=0;x<mod;++x) if((x-a)%m==0 && (x-b)%n==0) {want=x;break;}
    assert(want<0 ? result.second==-1 : result==make_pair(want,mod));
    ll inv=NT::inverse(a,m);
    assert((inv>=0)==(gcd(a,m)==1));
    if(inv>=0) assert(((a*inv)%m+m)%m==1%m);
  }
  for(int prime:{2,3,5,7,11}) {
    Binomial bin(prime-1,prime);vector<vector<ll>> c(101,vector<ll>(101));
    c[0][0]=1;for(int n=1;n<=100;++n) {
      c[n][0]=1;for(int r=1;r<=n;++r) c[n][r]=(c[n-1][r]+c[n-1][r-1])%prime;
    }
    for(int n=0;n<=100;++n) for(int r=0;r<=n+1;++r)
      assert(bin.lucas(n,r)==(r<=n ? c[n][r]:0));
  }
}
void numericalDP() {
  assert((FFT::convolution({-2,3},{4,-5})==vector<ll>{-8,22,-15}));
  for(int it=0;it<200;++it) {
    int n=rnd(25),m=rnd(25);vector<ll> a(n),b(m);vector<int> x(n),y(m);
    for(int i=0;i<n;++i) x[i]=(int)(a[i]=rnd(100));
    for(int i=0;i<m;++i) y[i]=(int)(b[i]=rnd(100));
    vector<ll> want(n && m ? n+m-1:0);
    for(int i=0;i<n;++i) for(int j=0;j<m;++j) want[i+j]+=a[i]*b[j];
    assert(FFT::convolution(a,b)==want);
    auto got=NTT::convolution(x,y);assert(vector<ll>(got.begin(),got.end())==want);
    for(int& v:x) v=rnd(NTT::mod);
    for(int& v:y) v=rnd(NTT::mod);
    auto modGot=NTT::convolution(x,y);vector<ll> modWant(want.size());
    for(int i=0;i<n;++i) for(int j=0;j<m;++j)
      modWant[i+j]=(modWant[i+j]+1LL*x[i]*y[j])%NTT::mod;
    assert(vector<ll>(modGot.begin(),modGot.end())==modWant);
    int k=1+rnd(8);vector<ll> init(k),coeff(k),seq(100);
    for(int j=0;j<k;++j) seq[j]=init[j]=rnd(100),coeff[j]=rnd(100);
    for(int j=k;j<100;++j) for(int t=0;t<k;++t)
      seq[j]=(seq[j]+coeff[t]*seq[j-1-t])%1000000007;
    for(int j=0;j<100;++j) assert(linearRecurrence(init,coeff,j,1000000007)==seq[j]);
    XorBasis basis;vector<uint64_t> values(10);set<uint64_t> span{0};
    for(auto& v:values) {
      v=rnd(1024);basis.insert(v);auto old=span;for(auto w:old) span.insert(w^v);
    }
    for(int v=0;v<1024;++v) assert(basis.contains(v)==(span.count(v)!=0));
    assert(basis.maxXor()==*span.rbegin());
    vector<ll> subset(1<<rnd(7));for(auto& v:subset) v=rnd(100)-50;
    auto orig=subset;subsetSum(subset);
    for(int mask=0;mask<(int)subset.size();++mask) {
      ll sum=0;for(int s=mask;;s=(s-1)&mask) {sum+=orig[s];if(!s) break;}
      assert(subset[mask]==sum);
    }
    subsetSum(subset,true);assert(subset==orig);
    int len=2+rnd(30);vector<ll> pref(len+1);
    for(int j=0;j<len;++j) pref[j+1]=pref[j]+rnd(20);
    auto cost=[&](int l,int r){return pref[r+1]-pref[l];};
    vector<vector<ll>> dp(len+1,vector<ll>(len+1));
    for(int size=2;size<=len;++size) for(int l=0;l+size<=len;++l) {
      int r=l+size;dp[l][r]=LLONG_MAX/4;
      for(int mid=l+1;mid<r;++mid) dp[l][r]=min(dp[l][r],dp[l][mid]+dp[mid][r]+cost(l,r-1));
    }
    assert(knuthDP(len,cost)==dp[0][len]);
    vector<ll> prev(len+1,LLONG_MAX/4);prev[0]=0;
    auto square=[&](int l,int r){ll z=cost(l,r);return z*z;};
    for(int layer=1;layer<=5;++layer) {
      auto fast=divideConquerDP(prev,square);vector<ll> slow(len+1,LLONG_MAX/4);
      for(int r=1;r<=len;++r) for(int l=0;l<r;++l)
        if(prev[l]!=LLONG_MAX/4) slow[r]=min(slow[r],prev[l]+square(l,r-1));
      assert(fast==slow);prev=slow;
    }
  }
  vector<double> sol;
  assert(solveLinear({{1,1,3},{1,-1,1}},2,sol)==0);
  assert(abs(sol[0]-2)<1e-8 && abs(sol[1]-1)<1e-8);
  assert(solveLinear({{1,1,3},{2,2,6}},2,sol)==1);
  assert(solveLinear({{1,1,3},{2,2,7}},2,sol)==-1);
}
void geometry() {
  for(int it=0;it<300;++it) {
    vector<Point> p(1+rnd(30));for(auto& q:p) q={rnd(21)-10,rnd(21)-10};
    auto h=convexHull(p);__int128 diameter=0;
    for(auto a:p) for(auto b:p) diameter=max(diameter,dist2(a,b));
    assert(hullDiameter(h)==diameter);
    for(auto q:p) assert(insidePolygon(h,q)>=0);
    if(h.size()>2) for(int j=0;j<(int)h.size();++j)
      assert(cross(h[j],h[(j+1)%h.size()],h[(j+2)%h.size()])>0);
  }
  assert(segmentIntersection({0,0},{2,2},{0,2},{2,0}));
  assert(segmentIntersection({0,0},{2,0},{1,0},{3,0}));
  assert(segmentIntersection({1,0},{1,0},{0,0},{2,0}));
  assert(!segmentIntersection({0,0},{1,0},{2,0},{3,0}));
  vector<Point> square{{0,0},{4,0},{4,4},{0,4}};
  assert(insidePolygon(square,{2,2})==1 && insidePolygon(square,{4,2})==0 && insidePolygon(square,{5,2})==-1);
  vector<DPoint> out;
  assert(circleIntersection({0,0},1,{1,0},1,out)==2);
  for(auto p:out) assert(fabsl(hypotl(p.x,p.y)-1)<1e-9L && fabsl(hypotl(p.x-1,p.y)-1)<1e-9L);
  assert(circleIntersection({0,0},1,{2,0},1,out)==1);
  assert(circleIntersection({0,0},1,{3,0},1,out)==0);
  assert(circleIntersection({0,0},2,{0,0},2,out)==-1);
  assert(circleIntersection({0,0},0,{0,0},0,out)==1);
}
int main() {
  dataStructures();cout<<"Data structures passed"<<endl;
  graphBasics();trees();flowsMatching();cout<<"Graph passed"<<endl;
  strings();cout<<"Strings passed"<<endl;
  arithmetic();cout<<"Number theory passed"<<endl;
  numericalDP();cout<<"Numerical / DP passed"<<endl;
  geometry();cout<<"Geometry passed"<<endl;
}

