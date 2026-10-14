#include <cassert>
#include "../utilities/template.h"
#include "../../content/data-structures/MoQueries.h"
int main() {
  srand(31);
  for (int n=0; n<=100; ++n) {
    vector<int> a(n); for(auto& x:a) x=rand()%100-50;
    for(int q : {0,1,100,1000}) {
      vector<pair<int,int>> qs(q); deque<int> state;
      ll sum=0;
      for(auto& [l,r]:qs) {
        l=rand()%(n+1); r=rand()%(n+1);
        if(l>r) swap(l,r);
        --r;
      }
      auto add=[&](int i,int end) {
        sum+=a[i];
        if(end) state.push_back(i); else state.push_front(i);
      };
      auto del=[&](int i,int end) {
        assert(!state.empty());
        assert((end ? state.back() : state.front())==i);
        if(end) state.pop_back(); else state.pop_front();
        sum-=a[i];
      };
      auto ans=mo(n,qs,add,del,[&](){return sum;});
      for(int i=0;i<q;++i)
        assert(ans[i]==accumulate(a.begin()+qs[i].first,a.begin()+qs[i].second+1,0LL));
    }
  }
  cout << "Mo tests passed!\n";
}
