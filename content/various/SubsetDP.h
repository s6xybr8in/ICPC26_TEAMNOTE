/**
 * Author: Green Siro
 * License: CC0
 * Description: In-place subset zeta sum; length must be
 * 2^k > 0. inverse=true: Mobius inversion.
 * Time: O(k*2^k). For supersets, replace
 * set-bit condition by unset-bit and use a[mask | (1<<b)]
 * as source.
 */
#pragma once

template<class T> void subsetSum(vector<T>& a,bool
  inverse=false) {
  int n=(int)a.size();assert(n>0 && !(n&(n-1)));
  for(int bit=1;bit<n;bit*=2) for(int mask=0;mask<n;++mask)
    if(mask&bit) {
      if(inverse) a[mask]-=a[mask^bit];
      else a[mask]+=a[mask^bit];
    }
}
