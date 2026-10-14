/**
 * Author: Green Siro
 * Description: Randomized integer hash for unordered containers.
 * Reduces predictable collisions; worst case is still O(N).
 * Usage: unordered_set<ll, CustomHash> s;
 * unordered_map<ll, int, CustomHash> m;
 * Set max_load_factor(0.7f) before reserve(expected_size).
 * reserve reduces rehashing, not adversarial collisions.
 */
#pragma once

struct CustomHash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t seed = chrono::steady_clock::now()
        .time_since_epoch().count();
    return (size_t)splitmix64(x + seed);
  }
};
