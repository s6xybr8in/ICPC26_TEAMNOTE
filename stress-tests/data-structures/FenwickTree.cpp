#include <cassert>
#include "../utilities/template.h"
#include "../../content/data-structures/FenwickTree.h"
int main() {
  srand(17);
  for (int n=1; n<=100; ++n) {
    FenwickTree fw(n); vector<ll> a(n+1);
    for (int it=0; it<2000; ++it) {
      int i=1+rand()%n, j=1+rand()%n;
      if (i>j) swap(i,j);
      if (rand()%2) {
        int d=rand()%2001-1000; fw.update(i,d); a[i]+=d;
      } else assert(fw.query(i,j)==accumulate(a.begin()+i,a.begin()+j+1,0LL));
    }
  }
  cout << "Fenwick tests passed!\n";
}
