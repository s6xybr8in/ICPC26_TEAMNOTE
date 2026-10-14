/**
 * Author: Green Siro
 * License: CC0
 * Description: Linear sieve: smallest prime, phi, Mobius up
 * to n. Time and memory: O(N).
 */
#pragma once

struct Sieve {
  vector<int> primes,spf,phi,mu;
  Sieve(int n):spf(n+1),phi(n+1),mu(n+1) {
    if(n>=1) phi[1]=mu[1]=1;
    for(int i=2;i<=n;++i) {
      if(!spf[i]) spf[i]=i,primes.push_back(i),
          phi[i]=i-1,mu[i]=-1;
      for(int p:primes) {
        if(1LL*i*p>n) break;
        spf[i*p]=p;
        if(i%p==0) {phi[i*p]=phi[i]*p;break;}
        phi[i*p]=phi[i]*(p-1);mu[i*p]=-mu[i];
      }
    }
  }
};
