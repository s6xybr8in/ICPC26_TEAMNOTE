#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<long long> pref(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> pref[i];
    pref[i] += pref[i - 1];
  }
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << pref[r] - pref[l - 1] << '\n';
  }
}
