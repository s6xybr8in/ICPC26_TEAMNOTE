/**
 * Author: Green Siro
 * License: CC0
 * Description: Closed interval DP, dp[i][i]=0.
 * dp[l][r]=cost(l,r)+min(dp[l][k]+dp[k+1][r]), l<=k<r.
 * Requires opt[l][r-1]<=opt[l][r]<=opt[l+1][r].
 * Time: O(N^2).
 * Memory: O(N^2).
 */
#pragma once

template<class Cost> ll knuthDP(int n,Cost cost) {
  if(n<2) return 0;
  vector<vector<ll>> dp(n,vector<ll>(n));
  vector<vector<int>> opt(n,vector<int>(n));
  for(int i=0;i<n;++i) opt[i][i]=i;
  for(int len=2;len<=n;++len) for(int l=0;l+len<=n;++l) {
    int r=l+len-1;dp[l][r]=LLONG_MAX/4;
    for(int k=opt[l][r-1];k<=min(r-1,opt[l+1][r]);++k) {
      ll v=dp[l][k]+dp[k+1][r]+cost(l,r);
      if(v<dp[l][r]) dp[l][r]=v,opt[l][r]=k;
    }
  }
  return dp[0][n-1];
}
