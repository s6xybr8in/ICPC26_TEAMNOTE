/**
 * Author: Green Siro
 * License: CC0
 * Description: Literal 2*i = x\_i, 2*i+1 = NOT x\_i.
 * either(a,b) adds (a OR b); force(a) adds a. Time: O(V+E).
 * Depends on SCC.h.
 */
#pragma once

#include "SCC.h"
struct TwoSAT {
  SCC scc;
  vector<bool> value;
  TwoSAT(int n) : scc(2*n),value(n) {}
  void either(int a,int b) {
    scc.addEdge(a^1,b); scc.addEdge(b^1,a);
  }
  void force(int a) {either(a,a);}
  bool solve() {
    scc.build();
    for(int i=0;i<(int)value.size();++i) {
      if(scc.comp[2*i]==scc.comp[2*i+1]) return false;
      value[i]=scc.comp[2*i]>scc.comp[2*i+1];
    }
    return true;
  }
};
