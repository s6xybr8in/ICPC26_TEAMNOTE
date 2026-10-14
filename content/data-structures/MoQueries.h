/**
 * Author: Green Siro
 * Description: Offline queries on 0-indexed [l, r].
 * Empty range: r=l-1.
 * add/del(index, end): end=0 left, end=1 right.
 * Start with an empty state; calc() returns its answer.
 * Time: O(Q log Q + N sqrt(Q)) state changes.
 * Status: stress-tested
 */
#pragma once

template<class Add, class Del, class Calc>
auto mo(int n, const vector<pair<int,int>>& qs,
        Add add, Del del, Calc calc) {
  int q = (int)qs.size();
  int block = max(1, (int)(n / sqrt(max(1, q))));
  vector<int> order(q);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int a, int b) {
    int x = qs[a].first / block, y = qs[b].first / block;
    if (x != y) return x < y;
    return (x & 1) ? qs[a].second > qs[b].second
                   : qs[a].second < qs[b].second;
  });
  vector<decltype(calc())> ans(q);
  int l = 0, r = -1;
  for (int i : order) {
    auto [a, b] = qs[i];
    while (l > a) add(--l, 0);
    while (r < b) add(++r, 1);
    while (l < a) del(l++, 0);
    while (r > b) del(r--, 1);
    ans[i] = calc();
  }
  return ans;
}
