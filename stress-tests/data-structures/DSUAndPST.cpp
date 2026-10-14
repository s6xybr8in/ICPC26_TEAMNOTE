#include <cassert>
#include "../utilities/template.h"
#include "../../content/data-structures/DSU.h"
#include "../../content/data-structures/PST.h"
int main() {
  srand(43);
  for(int n=1;n<=50;++n) {
    DSU d(n); vector<int> labels(n+1);
    iota(all(labels),0);
    PST pst(n); vector<vector<int>> versions(1,vector<int>(n+1));
    for(int it=0;it<1000;++it) {
      int x=1+rand()%n,y=1+rand()%n;
      d.join(x,y); int old=labels[y], replacement=labels[x];
      for(int& v:labels) if(v==old) v=replacement;
      for(int k=1;k<=n;++k) assert((d.find(x)==d.find(k))==(labels[x]==labels[k]));
      int prev=rand()%(int)versions.size(), val=rand()%2001-1000;
      auto next=versions[prev]; next[x]=val;
      pst.update(pst.roots[prev],x,val); versions.push_back(next);
      int version=rand()%(int)versions.size();
      if(x>y) swap(x,y);
      assert(pst.query(pst.roots[version],x,y)==accumulate(versions[version].begin()+x,versions[version].begin()+y+1,0));
    }
  }
  cout << "DSU/PST tests passed!\n";
}
