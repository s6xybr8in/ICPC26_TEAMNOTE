#include <cassert>
#include "../utilities/template.h"
#include "../../content/data-structures/SegmentTree.h"
#include "../../content/data-structures/SegmentTreeRecursive.h"
int main() {
  srand(23);
  for (int n=1; n<=100; ++n) {
    SegmentTree st(n); SegmentTreeRecursive rec(n);
    vector<int> a(n+1);
    for (int it=0; it<2000; ++it) {
      int i=1+rand()%n, j=1+rand()%n;
      if(i>j) swap(i,j);
      if(rand()%2) {
        int v=rand()%2001-1000; a[i]=v;
        st.update(i,v); rec.update(i,v);
      } else {
        int want=accumulate(a.begin()+i,a.begin()+j+1,0);
        assert(st.query(i,j)==want);
        assert(rec.query(i,j)==want);
      }
    }
  }
  cout << "Segment tree tests passed!\n";
}
