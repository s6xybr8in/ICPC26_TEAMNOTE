/**
 * Author: Green Siro
 * License: CC0
 * Description: 64-bit unsigned XOR linear basis. insert returns independence; contains tests
 * span; maxXor(seed) maximizes seed XOR subset. O(64) each.
 */
#pragma once

struct XorBasis {
	array<uint64_t, 64> basis{};
	int rank = 0;
	bool insert(uint64_t x) {
		for (int b = 63; b >= 0; --b)
			if (x >> b & 1) {
				if (!basis[b]) {
					basis[b] = x;
					++rank;
					return true;
				}
				x ^= basis[b];
			}
		return false;
	}
	bool contains(uint64_t x) const {
		for (int b = 63; b >= 0; --b)
			if (x >> b & 1) x ^= basis[b];
		return x == 0;
	}
	uint64_t maxXor(uint64_t x = 0) const {
		for (int b = 63; b >= 0; --b) x = max(x, x ^ basis[b]);
		return x;
	}
};
