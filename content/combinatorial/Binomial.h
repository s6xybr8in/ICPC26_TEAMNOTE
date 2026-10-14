/**
 * Author: Green Siro
 * License: CC0
 * Description: Prime mod; precompute through N < mod. nCr:
 * O(1), Lucas: O(log\_mod n) after precompute mod-1. Lucas
 * requires N=mod-1, impractical for large mod. Time: O(N +
 * log mod) build. Depends on Modular.h.
 */
#pragma once

#include "../number-theory/Modular.h"
struct Binomial {
  ll mod;vector<ll> fac,invfac;
  Binomial(int n,ll mod):mod(mod),fac(n+1,1),invfac(n+1,1) {
    assert(n<mod);
    for(int i=1;i<=n;++i) fac[i]=NT::mul(fac[i-1],i,mod);
    invfac[n]=NT::power(fac[n],mod-2,mod);
    for(int i=n;i>0;--i) invfac[i-1]=NT::mul(invfac[i],i,mod);
  }
  ll choose(int n,int r) const {
    if(r<0 || r>n) return 0;
    assert(n<(int)fac.size());
    return NT::mul(NT::mul(fac[n],invfac[r],mod),
      invfac[n-r],mod);
  }
  ll lucas(ll n,ll r) const {
    assert((ll)fac.size()==mod);ll ans=1;
    for(;n || r;n/=mod,r/=mod)
      ans=NT::mul(ans,choose((int)(n%mod),(int)(r%mod)),mod);
    return ans;
  }
};
