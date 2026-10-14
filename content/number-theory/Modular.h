/**
 * Author: Green Siro
 * License: CC0
 * Description: mod>0; mul via \_\_int128. CRT supports
 * noncoprime positive moduli. CRT: (residue,lcm), (0,-1)
 * impossible; (0,0) if lcm overflows ll. extGcd inputs
 * nonnegative; intermediates must fit ll (CRT uses 128-bit
 * internally).
 */
#pragma once

namespace NT {
ll norm(ll a,ll mod) {a%=mod;return a<0 ? a+mod:a;}
ll mul(ll a,ll b,ll mod) {return (ll)((__int128)a*b%mod);}
ll power(ll a,ll e,ll mod) {
  a=norm(a,mod);ll r=1%mod;
  for(;e;e>>=1,a=mul(a,a,mod)) if(e&1) r=mul(r,a,mod);
  return r;
}
ll extGcd(ll a,ll b,ll& x,ll& y) {
  if(!b) {x=1;y=0;return a;}
  ll g=extGcd(b,a%b,y,x);y-=a/b*x;return g;
}
ll inverse(ll a,ll mod) {
  a=norm(a,mod);ll x,y;
  if(extGcd(a,mod,x,y)!=1) return -1;
  return norm(x,mod);
}
pair<ll,ll> crt(ll a,ll m,ll b,ll n) {
  a=norm(a,m);b=norm(b,n);
  ll g=gcd(m,n),mg=m/g,ng=n/g;
  __int128 diff=(__int128)b-a;
  if(diff%g) return {0,-1};
  __int128 mod=(__int128)m*ng;
  if(mod>LLONG_MAX) return {0,0};
  ll k=ng==1 ? 0:mul((ll)((diff/g%ng+ng)%ng),
      inverse(mg%ng,ng),ng);
  return {(ll)((a+(__int128)m*k)%mod),(ll)mod};
}
}
