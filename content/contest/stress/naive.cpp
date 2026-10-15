#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<long long> a(n + 1);
  for (int i = 1; i <= n; ++i) cin >> a[i];
  while (q--) {
    int l, r;
    cin >> l >> r;
    long long sum = 0;
    for (int i = l; i <= r; ++i) sum += a[i];
    cout << sum << '\n';
  }
}
