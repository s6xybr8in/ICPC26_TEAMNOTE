/**
 * Author: s6xybr8in
 * Date: 2026-09-13
 * Description: 1-indexed tree with point update and range query.
 * Time: O(\log N)
 * Status: tested
 */
#pragma once

struct Tree {
  typedef int T;
  static constexpr T unit = 0;
  T f(T a, T b) { return a + b; } // (any associative fn)
  int n;
  vector<T> tree;

  Tree(int n = 0, T def = unit) : n(n), tree(2 * n, def) {}

  // 1-indexed point update
  void update(int pos, T val) {
    for (tree[pos += n - 1] = val; pos > 1; pos >>= 1)
      tree[pos >> 1] = f(tree[pos], tree[pos ^ 1]);
  }

  // 1-indexed [l, r] inclusive query
  T query(int l, int r) {
    T ra = unit, rb = unit;
    for (l += n - 1, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ra = f(ra, tree[l++]);
      if (r & 1) rb = f(tree[--r], rb);
    }
    return f(ra, rb);
  }
};